#ifndef INC_KAFKAPRODUCTER_H
#define INC_KAFKAPRODUCTER_H


#ifndef WIN32
#include "librdkafka/rdkafka.h"  /* for Kafka driver */
#endif
#include "include/corethread.h"
#include <event2/event.h>
#include "include/pipe.h"
#include "json/value.h"
#include "include/slab.h"
#include "include/icqtypes.h"
class CTLKafaProducter;
class CTLKafkaClient;


struct CTLKafkaProductData
{
	string key;
	Json::Value* val;
	CTLKafkaClient* pClient;
	CTLKafkaProductData()
	{
		pClient = NULL;
		val = NULL;
	}
	DECLARE_SLAB(CTLKafkaProductData);
};

struct CTLKafkPipeData
{
	uint16 cmd;
	void*  para;
	CTLKafkPipeData()
	{
		cmd = 0;
		para = NULL;
	}
};

class CTLKafaProducter;

class CTLKafkaClient
{
public:
	CTLKafkaClient(CTLKafaProducter* processKafka);
	~CTLKafkaClient();

public:
	int		InitProducer (); 
	int		FreeProducer();
	bool	UpdateHost(const char* host, const char* tic); 
	void	ProducterMsg(const char* key, Json::Value* val);
private:
	int		ProcessKafkaProduct(CTLKafkaProductData* data);
private:
#ifndef WIN32
	rd_kafka_t *rk;
	rd_kafka_topic_t *rkt;
	int partition;
	rd_kafka_topic_conf_t *topic_conf;

#endif
	string				m_host;
	string				m_tic;
	bool				m_bLink;
	CTLKafaProducter*	m_process;
	friend class CTLKafaProducter;
};

class CTLKafaProducter:public CoreThreadHandle
{
public:
	CTLKafaProducter();
	~CTLKafaProducter();
	enum 
	{
		KAFKA_PRODUCT,
		KAFKA_UPDATE,
		KAFKA_STOP,	
	};
public:
	void ProcessTimeout();
public:
	int		Init();
	

	void	NotifyProducterMsg(CTLKafkaProductData* pData);
	void	NotifyUpdateHost(CTLKafkaClient* pClient);
	void	OnReadPipe(int fd, short which);
protected:
	virtual void run(void *mParameter);


private:
	

	//int		InitProducer (const char* host, const char* tic); 
	//int		FreeProducer();
	int		InitEvent();
	
	void	ProcessUpdateHost(CTLKafkaClient* pClient);
	void	StopWork();
	bool	CheckReconnect();


private:
	void		 ProcessStop();

private:

	CTLPipe				m_pipe;
	Mutex				m_pipeMutex;
	struct event *		m_pipeEv;
	struct event*		m_timerEvent;
	struct event_base * m_base;
	uint32				m_timer;
};



#endif
