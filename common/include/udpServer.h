#ifndef _TAOLE_UDPSERVER_H_
#define _TAOLE_UDPSERVER_H_

#include "baseServer.h"



class CTLUdpEventCustomer :public CTLEventCustomer
{
public:
	virtual ~CTLUdpEventCustomer() {}
	//new packet to received data
	virtual InPacket *AllocNewPacket(int svrIndex) 
	{
		return new UdpInPacket;
	}
	virtual void OnUdpDataReceived(int serverIndex, InPacket *in) = 0;

	virtual void OnTimer(uint16 timerid) = 0;

};



class CTLEventUdpServer : public CTLEventServerBase
{
public:

	CTLEventUdpServer(int idx, uint32 bindIP, uint16 bindPort);
	~CTLEventUdpServer();
	virtual bool NetWorkReady()
	{
		return bindSock != INVALID_SOCKET;
	}
public:
	void OnUdpPacketReceive(evutil_socket_t fd, short event, void *ctx);
	virtual void OnTimer(uint16 timerid);
    virtual bool Start(CTLEventCustomer *newCustomer)
    {
        CTLUdpEventCustomer *cust = dynamic_cast<CTLUdpEventCustomer *>(newCustomer);
        if (NULL == cust)
            return false;
        if (NULL == udpEvent)
            return false;
        return CTLEventServerBase::Start(newCustomer);
    }
	const int GetSocket(void)
	{
		return bindSock;
	}
protected:
	virtual void SendData(uint32 dstIP, uint16 dstPort, const char *buf, int len, void *param);
	CTLUdpEventCustomer *GetCustomer() const 
	{
		return (CTLUdpEventCustomer *)CTLEventServerBase::GetCustomer();
	}
private:
	int bindSock;
private:

	struct event *udpEvent;
};


#endif

