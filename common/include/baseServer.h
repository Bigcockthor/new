#ifndef _TAOLE_BASESERVER_H_
#define _TAOLE_BASESERVER_H_

//#ifdef WIN32
//#	include "winsock2.h"  
//#else
//#	include <sys/socket.h>
//#	include <arpa/inet.h>
//#	include <unistd.h>
//#	include <err.h>
//#	include <netinet/in.h>
//#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <event2/event.h>
#include <string.h> 
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>

#include <map>
#include "include/corethread.h"
#include "include/icqtypes.h"
#include "packet.h"
#include "udppacket.h"
#include <vector>
#include <list>
#include <algorithm>


#include "include/list.h"
#include "pipe.h"
#include <map>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/event_compat.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>


#define MAX_IMSERVER_IP_PORT_MEMBER 1024
//hash相关定义
#define HASH_SIZE		(1 << 20)
#define HASH_MASK		(HASH_SIZE - 1)

//#ifndef INVALID_HANDLE_VALUE
//#define INVALID_HANDLE_VALUE	(~0)
//#endif



class CTLEventCustomer
{
public:
	virtual ~CTLEventCustomer(){}
	//用户自己实现
	virtual void OnUserEvent(uint32 eventid, void* para){}

};

class EvBufferEx
{
public:
	EvBufferEx(uint32 ip, uint16 port);
	~EvBufferEx();


	uint32 dstIP;
	uint16 dstPort;

	void *parameter;

	int AddBuffer(const char *buf, int len);
	int AddBuffer(struct evbuffer *buf);
	char *GetData();
	int Getdatalen();

private:
	struct evbuffer *evBuf;
};

#pragma pack(1)

typedef struct PIPE_CMD
{
	uint8	cmd;
	uint32	ip;
	uint16	port;
	void*	para;		//附加参数
}PIPE_CMD;

#pragma pack()



class CTLEventServerBase : public CoreThreadHandle
{
private:
	enum
	{
		EVENT_PIPE_DATA = 1,				//有数据需要发送
		EVENT_PIPE_CLOSE_SOCKET,			//有socket需要关闭
		EVENT_PIPE_EXIT,					//退出event_loop
		EVENT_PIPE_ADD_TIMER,				//增加定时器
		EVENT_PIPE_DEL_TIMER,				//删除定时器
		EVENT_PIPE_USER_EVENT,				//用户事件
	};
public:
	typedef std::list<EvBufferEx *> SmartList;
	virtual ~CTLEventServerBase();
	virtual void run(void *mParameter);

	void		 ShutDown();
	bool		 IsWorking();
	//添加用户自定义事件
	int			 NotifyUserEvent(uint32 eventid, void* para);
public:
	virtual void OnReadPipe(int fd, short which, void *ctx);
	virtual void ___OnCheckTimeOut();
	virtual void OnTimer(uint16 timerid);
	
public:
	int	AddTimer(uint32 timeoutms);
	int	RemoveTimer();

	void PushData(const uint32 dstIP, const uint16 dstPort, const char *buf, int len, void *param = NULL);

	/*
	 *	OutPcket will delete by CEventServerBase;
	 */
	void PushData(EvBufferEx *p);

	virtual bool Start(CTLEventCustomer *newCustomer)
	{
        if (!m_pipe.CheckValid())
            return false;

        if (newCustomer && GetEventBase() && customer == NULL)
            SetCustomer(newCustomer);
        else
            return false;

        if (NULL == timeoutEV || NULL == pipeEv)
            return false;

        m_handle = CoreThread::CreateNewThread(this, NULL);
        if (INVALID_HANDLE_VALUE == m_handle)
            return false;
        m_bWorking = true;
        return true;
	}
protected:
	int serverIndex;
	volatile bool	m_bWorking;
	CTLEventServerBase(int idx);

	void SetCustomer(CTLEventCustomer *newCustomer);

	void SwapSendList(SmartList &tempList);
	virtual void SendData(uint32 dstIP, uint16 dstPort, const char *buf, int len, void *param) = 0;
	CTLEventCustomer *GetCustomer() const 
	{
		return customer;
	}
protected:
	virtual void CloseTcpSocket(const uint32 ip, const uint16 port) {}
	void PushCloseTcpConnectionCommand(const uint32 ip, const uint16 port);
	void PushExitPipe();
public:
	struct event_base* GetEventBase() const
	{
		return base;
	}


	virtual bool NetWorkReady() = 0;
private:
	void _AddUserTimer(struct timeval& tv);
	void _RemoveUserTimer();
private:
	struct event_base *base;
	CTLEventCustomer *customer;
	struct event *timeoutEV;
	struct event *pipeEv;
	struct event *userTimer;
	//int pipefd[2];
	CTLPipe	m_pipe;
	
private:
	Mutex listLock;
    Mutex pipeLock;
	SmartList sendList;
	bool			m_loopExit;
	ThreadHandle	m_handle;
	//bool PushList(EvBufferEx *p);
};





class CTLConnection
{
public:
	enum
	{
		MAX_TIME_OUT = 60,
	};

	CTLConnection(uint32 _ip, uint16 _port, struct bufferevent *_evt, int _fd, CTLEventServerBase *baseSvr);
	virtual ~CTLConnection();

	struct bufferevent *GetBufferEvent() const 
	{
		return buffevent;
	}

	time_t lastKeepLive;
	ListHead item;

	const uint32 ip;
	const uint16 port;

	const CTLEventServerBase *svr;
	int GetSock() const
	{
		return fd;
	}
	void SetSock(int sock)
	{
		fd = sock;
	}
public:
	uint32 roomid;
private:
	struct bufferevent *buffevent;
	int fd;
};


/*
 *	Session管理模板类
 */

typedef uint64 SessionKey;	
typedef std::map<SessionKey, CTLConnection *> ConnectionMap;
class SessionConnectionMgr
{
public:
	

	bool AddConnection(SessionKey key, CTLConnection *cn);
	CTLConnection *GetConnection(SessionKey key);
	bool RemoveConnection(SessionKey key);
	ConnectionMap* GetConnMap(){return & cnmap;}
private:
	ConnectionMap cnmap;
};






#endif



