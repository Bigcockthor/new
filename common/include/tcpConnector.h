#ifndef _TAOLE_TCPCONNECTOR_H_
#define _TAOLE_TCPCONNECTOR_H_


#include "baseServer.h"



class ClientConnection : public CTLConnection
{
public:
	ClientConnection(uint32 _ip, uint16 _port, struct bufferevent *_evt, int _fd, CTLEventServerBase *baseSvr, int oldS, int times  = 1);

	int tryTimes;
	int oldStatus;
	int status;
	uint32 localIP;
	uint16 localPort;

};

class CTcpConnectorCustomer : public CTLEventCustomer
{
public:
	enum
	{
		ERROR_NO_CN_NOFOUND = 1,  //cant found connection
	};
	virtual ~CTcpConnectorCustomer() {}
		/*
	 *	当连接被关闭时使用
	 */
	virtual void OnClose(int serverIndex, const ClientConnection *cn) = 0;

	virtual void OnConnectError(int serverIndex, const ClientConnection *cn, int tryTimes) = 0;

	/*
	 *	收到数据时调用 
	 */
	virtual void OnTcpDataReceived(int serverIndex, const ClientConnection *cn, const char *buf, int len) = 0;

	/*
	 *	当新连接建立时调用
	 */
	virtual void OnNewConnection(int serverIndex, const ClientConnection *cn) = 0;
	virtual void OnSendError(int err_no, void *param) = 0;
};



//#include "SmartBuffer.h"
class CTcpConnector : public CTLEventServerBase
{
public:
	CTcpConnector(int idx);
	~CTcpConnector();

public:  
	virtual bool NetWorkReady()
	{
		return listener != NULL;
	}
	void CloseConnection(uint32 ip, uint16 port);
	void ConnectTo( uint32 ip, uint16 port );
public:

	virtual void ___OnCheckTimeOut();
	virtual void ___onRead(struct bufferevent *bev, void *ctx);
	
	virtual void ___OnAccept_conn(struct evconnlistener *listener, evutil_socket_t fd, 
	struct sockaddr *address, int socklen, void *ctx);
	virtual void ___OnEvent(struct bufferevent *bev, short events, void *ctx);
protected:
	virtual void SendData(uint32 dstIP, uint16 dstPort, const char *buf, int len, void *param);
	CTcpConnectorCustomer *GetCustomer() const 
	{
		return (CTcpConnectorCustomer *)CTLEventServerBase::GetCustomer();
	}
	virtual void CloseTcpSocket(const uint32 ip, const uint16 port);
	void ConnectTo(uint32 ip, uint16 port, int hasConnectioned, int _retry_times);
public:
	SessionConnectionMgr sessionMgr;
	ListHead top;



private:
	struct evconnlistener *listener;
	char readBuffer[uint16(-1) + sizeof(uint16)];
private:
	void ResetKeepLive(CTLConnection *conn);
};




#endif



