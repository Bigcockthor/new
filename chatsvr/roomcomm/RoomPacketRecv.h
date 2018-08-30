 #pragma once
#include "include/icqtypes.h"
#include "include/corethread.h"
#include "include/udppacket.h"
#include "include/baseServer.h"
#include "include/tcpServer.h"

//class TransportPacket : public UdpInPacket 
//{
//public:
//	TransportPacket(ICQ_STR &buf, uint32 userIP, uint16 userPort, uint32 mProxyIP,
//		uint16 mProxyPort, uint8 cl) : proxyIP(mProxyIP), proxyPort(mProxyPort), 
//		channel(cl), data(0)
//	{
//		ip = userIP;
//		port = userPort;
//		setdata(buf.text, buf.len);
//	}
//
//	const uint32 proxyIP;				//登陆点服务器IP
//	const uint16 proxyPort;				//登陆点向真实服务器传送数据的port
//	const uint8 channel;
//	void *data;
//
//
//	DECLARE_SLAB(TransportPacket);
//};

class RecvPacketHandle;

class RecvPacketRecv :
	public CoreThreadHandle
{
public:
	RecvPacketRecv();
	~RecvPacketRecv(void);
	
	
	bool Init(uint32 bindIP, uint16 bindPort, RecvPacketHandle *mHandle);


	virtual void run(void *mParameter);
	inline int GetSock()
	{
		return sock;
	}
private:
	int sock;						//数据读取sock

	RecvPacketHandle *handle;
};


enum
{
	ROOM_TCPSERVER,
	ROOM_TCPPROXY,
	ROOM_UDPSERVER,
	ROOM_TCPWEB
};

typedef union IpPort
{
	uint64 data;
	struct {
		uint32 ip;					//ip
		uint16 port;				//端口
		uint16 verify;				//是否验证通过
	};
	IpPort()
	{
		data = 0;
	}
}IpPort;
typedef std::map<uint64, IpPort> ConnectIpInfoList;
class RecvPacketHandle
{
public:
	RecvPacketHandle();
	virtual ~RecvPacketHandle();

	
	virtual bool OnData(UdpInPacket *in) = 0;

	int SendData(OutPacket *out, uint32 ip, uint16 port, uint32 proxyIP, uint16 proxyPort);
	RecvPacketRecv &GetDirectRecv(void) { return receiverForDirect; }
	RecvPacketRecv &GetProxyRecv(void) { return receiverForProxy; } 
private:
	RecvPacketRecv receiverForDirect;
	RecvPacketRecv receiverForProxy;	
};

#define ROOM_MAXSERVER	3

class TcpServer:public CTLEventTcpServer
{
public:
	TcpServer(int idx, uint32 bindIP, uint16 bindPort);
	virtual ~TcpServer();

public:
	//必须在libevent线程中调用
	inline int SendBroadcast(const char *buf, int len, void *param);
};
class TcpRecvPacketHandle:public CTLTcpEventCustomer
{
public:
	TcpRecvPacketHandle();
	virtual ~TcpRecvPacketHandle();


	//////////////////////////////////////////////////////////////////////////
	virtual void OnClose(int serverIndex, const CTLConnection *cn);
	virtual void OnNewConnection(int serverIndex, const CTLConnection *cn);
	virtual void OnTcpDataReceived(int serverIndex, const CTLConnection *cn, const char *buf, int len);
	virtual void OnSendError(int err_no, void *param);
	virtual void OnTimer(uint16 timerid){};
	virtual void OnUserEvent(uint32 eventid, void* para);
	//////////////////////////////////////////////////////////////////////////
	virtual bool OnData(UdpInPacket *in, int nIndex) = 0;
	int SendTcpData(int serverIndex, OutPacket *out, uint32 ip, uint16 port, uint32 proxyIP, uint16 proxyPort);
	int	SendTcpDataAll(int serverIndex, OutPacket *out);
	bool InitTcpServer(uint32 ip, uint16 port, uint32 proxyIp, uint16 proxyPort, uint32 webIp = 0, uint16 webPort = 0);


private:
	TcpServer*		m_servers[ROOM_MAXSERVER];
	ConnectIpInfoList	m_connectList;
	Mutex				m_lock;
};

