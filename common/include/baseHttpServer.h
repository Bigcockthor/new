#ifndef INC_BASEHTTPSERVER_H
#define INC_BASEHTTPSERVER_H

#include "include/corethread.h"
#include "include/icqtypes.h"
#include "pipe.h"

#include <event2/event.h>
#include <event2/http.h>
#include <event2/http_compat.h>
#include <event2/http_struct.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/event_compat.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <map>

struct CTLPipeParm
{
	uint16 cmd;
	uint32 errcode;
	void*  paraReq;
	void*  paraResp;
	CTLPipeParm()
	{
		cmd = 0;
		errcode = HTTP_OK;
		paraReq = NULL;
		paraResp = NULL;
	}
};


class CTLHttpCallBack
{
public:
	virtual ~CTLHttpCallBack() {};
	virtual void OnHandleReq(struct evhttp_request *req, void* para) const = 0;
};


template <typename TCLSSS>
class CTLHttpCallbackT : public CTLHttpCallBack
{
public:
	typedef void (TCLSSS::*HttpReqCallback)(struct evhttp_request *req, void* para);

	CTLHttpCallbackT(TCLSSS* pClass, const HttpReqCallback& callback)
		: m_callback(callback),m_pClass(pClass)
	{
	}

	virtual void OnHandleReq(struct evhttp_request *req, void* para) const
	{
		(m_pClass->*m_callback)(req, para);
	}

private:
	HttpReqCallback			m_callback;
	TCLSSS*					m_pClass;
};



class CTLBaseHttpServer:public CoreThreadHandle
{
public:
	CTLBaseHttpServer();
	virtual ~CTLBaseHttpServer();

	enum
	{
		HTTP_EXIT,
		HTTP_REQ,
		HTTP_RSP,
	};

	struct ptrCmp
	{
		bool operator()( const char * s1, const char * s2 ) const
		{
			return strcmp( s1, s2 ) < 0;
		}
	};  
	typedef std::map<const char* , CTLHttpCallBack*,ptrCmp> HttpCallbackMap;

public:
	int			 StartHttpServer(const char* addr, uint16 port, uint16 threadNums, uint32 timeout);

	template<typename TCLASS>
	int			 RegeditReqCallBack(const char* path, TCLASS* pClass, const typename CTLHttpCallbackT<TCLASS>::HttpReqCallback& callback)
	{
				  CTLHttpCallBack* pd = new  CTLHttpCallbackT<TCLASS>(pClass, callback);

				   m_callBackMap[path] = pd;
				   return 0;
	}
	virtual void OnHandleReq(struct evhttp_request *req);
	void		 StopServer();
	virtual void OnReadPipe(int fd, short which);
	
	int			 NotifyPipeResp(struct evhttp_request *req, struct evbuffer *resp, uint16 errorCode);

	void		 PushTask(struct evhttp_request *req);	 
	void		 DefaultResp(struct evhttp_request *req);
private:
	int			 NotifyResp(struct evhttp_request *req, struct evbuffer *resp, uint32 errcode);
	int			 NotifyExit();
	virtual void run(void *mParameter);
	
	
private:
	uint16				m_port; 
	string				m_strAddr;
	struct evhttp*		m_httpServer;
	CTLPipe				m_pipe;
	struct event *		m_pipeEv;
	struct event_base * m_base;
	Mutex				m_pipeLock;
	CoreThreadPool*		m_threadPool;
	bool				m_bStart;
	HttpCallbackMap			m_callBackMap;
};





#endif

