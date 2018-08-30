#ifndef INC_BASEHTTPCLIENT_H
#define INC_BASEHTTPCLIENT_H
#include <string>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/event_compat.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/http_compat.h>
#include <event2/buffer.h>
#include <event.h>
#include "include/SmartBuffer.h"
#include "include/icqtypes.h"
#include "include/pipe.h"
#include "include/sync.h"
#include "include/corethread.h"
struct event_base;
struct evhttp_connection;
struct evhttp_request;

class CTLhttpClientChannel;

class CTLHttpReqBase:public DFSmartBuffer
{
public:
	CTLHttpReqBase(CTLhttpClientChannel* channel, const char* host, const char* path, uint16 port);
	virtual ~CTLHttpReqBase();
	enum
	{
		HTTP_REQ_OK,			//请求无错误
		HTTP_REQ_CONNECTFAILED, //连接失败
		HTTP_REQ_EXCEPTION,		//异常
		HTTP_REQ_CREATEFAILED,	
	};
public:
	void SetReqData(const char* sendData, int nLen);

	void SetPath(const char* path);
	//请求回调 线程不安全
	virtual void OnResp(int nCode, const void* pData, int nLen) = 0;
private:
	void FreeConnect();
	void ProcessedSendReq(struct event_base* base);
	static void Response(struct evhttp_request* req, void* arg);
private:
	struct evhttp_connection* m_conn;
	std::string				  m_host;
	std::string				  m_path;
	std::string				  m_sendData;
	uint16					  m_port;
	CTLhttpClientChannel*	  m_channel;
	friend class CTLhttpClientChannel;
};
struct HttpPipeData
{
	HttpPipeData()
	{
		cmd = 0;
		para = NULL;
	}
	uint16 cmd;
	void*  para;
};

class CTLhttpClientChannel :public CoreThreadHandle 
{
public:
	CTLhttpClientChannel();
	~CTLhttpClientChannel();

	enum 
	{
		HTTPCHANNEL_HTTPREQ,
		HTTPCHANNEL_STOP,	
	};
	int			 PutHttpReq(CTLHttpReqBase* req);

	virtual void ProcessTimeout(){};
	bool		 Init();
	virtual void run(void *mParameter);
	virtual void OnReadPipe(int fd, short which);
	void		 StopWork();
private:
	void		 ProcessStop();
	void		 ProcessReq(CTLHttpReqBase* req);
private:
	CTLPipe				m_pipe;
	Mutex				m_pipeMutex;
	struct event *		m_pipeEv;
	struct event*		m_timerEvent;
	struct event_base * m_base;

};
#endif
