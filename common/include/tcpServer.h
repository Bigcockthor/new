#ifndef _TAOLE_TCPSERVER_H_
#define _TAOLE_TCPSERVER_H_


#include "baseServer.h"


class CTLTcpEventCustomer : public CTLEventCustomer
{
public:
	enum
	{
		ERROR_NO_CN_NOFOUND = 1,  //cant found connection
	};
	virtual ~CTLTcpEventCustomer() {}

	/*
	 *	当连接被关闭时使用
	 */
	virtual void OnClose(int serverIndex, const CTLConnection *cn) = 0;

	/*
	 *	收到数据时调用 
	 */
	virtual void OnTcpDataReceived(int serverIndex, const CTLConnection *cn, const char *buf, int len) = 0;

	/*
	 *	当新连接建立时调用
	 */
	virtual void OnNewConnection(int serverIndex, const CTLConnection *cn) = 0;

	virtual void OnSendError(int err_no, void *param) = 0;

	virtual void OnTimer(uint16 timerid) = 0;
};



//#include "SmartBuffer.h"
class CTLEventTcpServer : public CTLEventServerBase
{
public:
	CTLEventTcpServer(int idx, uint32 bindIP, uint16 bindPort);
	~CTLEventTcpServer();

public:  
	virtual bool NetWorkReady()
	{
		return listener != NULL;
	}
	void CloseConnection(uint32 ip, uint16 port);

    virtual bool Start(CTLEventCustomer *newCustomer)
    {
        CTLTcpEventCustomer *cust = dynamic_cast<CTLTcpEventCustomer *>(newCustomer);
        if (NULL == cust)
            return false;
        return CTLEventServerBase::Start(newCustomer);
    }

public:
	virtual void OnTimer(uint16 timerid);
	virtual void ___OnCheckTimeOut();
	virtual void ___onRead(struct bufferevent *bev, void *ctx);
	
	virtual void ___OnAccept_conn(struct evconnlistener *listener, evutil_socket_t fd, 
	struct sockaddr *address, int socklen, void *ctx);
	virtual void ___OnEvent(struct bufferevent *bev, short events, void *ctx);
protected:
	virtual void SendData(uint32 dstIP, uint16 dstPort, const char *buf, int len, void *param);
	virtual void SendData(CTLConnection *cn, const char *buf, int len, void *param);
	CTLTcpEventCustomer *GetCustomer() const 
	{
		return (CTLTcpEventCustomer *)CTLEventServerBase::GetCustomer();
	}
	virtual void CloseTcpSocket(const uint32 ip, const uint16 port);

	evutil_socket_t CreateSocket(int af,int type, int protocol);

	bool	TcpBind(int af,int type, int protocol, uint16 port);

public:
	SessionConnectionMgr sessionMgr;
	ListHead top;



private:
	struct evconnlistener *listener;
	struct evconnlistener *listener6;
	evutil_socket_t listenSocket;
	evutil_socket_t listenSocket6;
	char readBuffer[uint16(-1) + sizeof(uint16)];
private:
	void ResetKeepLive(CTLConnection *conn);
};




#endif



