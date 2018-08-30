#include "kafkaProducter.h"
#include "include/log.h"
#include <time.h>
#include <errno.h>
#include <exception>
IMPLEMENT_SLAB(CTLKafkaProductData, 32)

#define KAFKA_AROUND		180
#define KAFKA_CHECK_CONN	5

CTLKafaProducter::CTLKafaProducter()
{
	m_pipeEv = NULL;
	m_timerEvent = NULL;
	m_base = NULL;
	m_timer = 0;

}



CTLKafaProducter::~CTLKafaProducter()
{
	
}

int CTLKafaProducter::Init()
{
	if(InitEvent())
	{
		LOG(1)("InitEvent failed\n");
		return -1;
	}
	
	return 0;
}


bool CTLKafkaClient::UpdateHost(const char* host, const char* tic)
{
	if(m_host != host || m_tic != tic)
	{
		m_host  = host;
		m_tic = tic;
		if(m_process)
		{
			m_process->NotifyUpdateHost(this);
		}
		return true;
	}
	return false;
}



void CTLKafaProducter::NotifyProducterMsg(CTLKafkaProductData* pData)
{
	CTLKafkPipeData data;
	int nLen = sizeof(CTLKafkPipeData);
	MutexObject obj(&m_pipeMutex);
	data.cmd = KAFKA_PRODUCT;
	data.para = pData;
	int writed = m_pipe.WriteData((const char*)&data, nLen); 
	if (writed != nLen)
	{
		LOG(Log::LOG_LEVEL_ERROR)("ERR write pipe writed=%d err=%d  line=%d\n", writed, errno, __LINE__);
	}
	return ;
}

void CTLKafaProducter::NotifyUpdateHost(CTLKafkaClient* pClient)
{
	CTLKafkPipeData data;
	int nLen = sizeof(CTLKafkPipeData);
	MutexObject obj(&m_pipeMutex);
	data.cmd = KAFKA_UPDATE;
	data.para = pClient;
	int writed = m_pipe.WriteData((const char*)&data, nLen); 
	if (writed != nLen)
	{
		LOG(Log::LOG_LEVEL_ERROR)("ERR write pipe writed=%d err=%d  line=%d\n", writed, errno, __LINE__);
	}
	return ;
}

int CTLKafkaClient::InitProducer () 
{
	LOG(4)("InitProducer tic %s broker %s\n", m_host.c_str(), m_tic.c_str());
	
#ifndef WIN32 

	rd_kafka_conf_t *conf;
	char errstr[512];

	/* Kafka configuration */
	conf = rd_kafka_conf_new();

	/* Topic configuration */
	topic_conf = rd_kafka_topic_conf_new();

	if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr)))) 
	{
		LOG(1)("Failed to create new producer: %s\n", errstr);
		return -1;
	}
	//rd_kafka_set_log_level(rk, LOG_DEBUG);
	/* Add brokers */
	if (rd_kafka_brokers_add(rk, m_host.c_str()) == 0) 
	{
		LOG(1)("No valid brokers specified\n");
		return -1;
	}
	/* Create topic */
	rkt = rd_kafka_topic_new(rk, m_tic.c_str(), topic_conf);
	topic_conf = NULL; /* Now owned by topic */
	
	m_bLink = true;
	return 0;

	

#else
	m_bLink = true;
	return 0;
#endif
}


void CTLKafkaClient::ProducterMsg(const char* key, Json::Value* val)
{
	if(m_process)
	{
		CTLKafkaProductData* pData = new CTLKafkaProductData;
		pData->key = key;
		pData->val = val;
		pData->pClient = this;
		m_process->NotifyProducterMsg(pData);
	}
	return ;
}
int CTLKafkaClient::FreeProducer()
{
	m_bLink = false;
#ifndef WIN32
	
	/* Destroy topic */
	if(rkt)
	{
		rd_kafka_topic_destroy(rkt);
		rkt = NULL;
	}
	
	/* Destroy the handle */
	if(rk)
	{
		rd_kafka_destroy(rk);
		rk = NULL;
	}
	
	if (topic_conf)
	{
		rd_kafka_topic_conf_destroy(topic_conf);
		topic_conf = NULL;
	}
		
	/* Let background threads clean up and terminate cleanly. */
	int run = 5;
	while (run-- > 0 && rd_kafka_wait_destroyed(1000) == -1)
		LOG(1)("Waiting for librdkafka to decommission\n");
	
	return 0;
#else
	return 0;
#endif

}

CTLKafkaClient::CTLKafkaClient(CTLKafaProducter* processKafka)
{
	m_process = processKafka;
	m_bLink = false;
#ifndef WIN32 
	rk = NULL;
	rkt = NULL;
	partition = RD_KAFKA_PARTITION_UA;
	topic_conf = NULL;
#endif
}

CTLKafkaClient::~CTLKafkaClient()
{
	FreeProducer();
}

int CTLKafkaClient::ProcessKafkaProduct(CTLKafkaProductData* data)
{
	if(!data)
	{
		return 0;
	}
	(*(data->val))["timeStamp"] = Json::Value((int)time(NULL));
#ifndef WIN32
	if(!rkt)
	{
		return 0;
	}
	const string& str = data->val->toStyledString();
	char* pMsg = (char*)(str.c_str());
	if(rd_kafka_produce(rkt, partition, RD_KAFKA_MSG_F_COPY, pMsg, str.length(), (char*)(data->key.c_str()), data->key.length(), NULL) == -1)
	{
		LOG(4)("Failed to produce to topic %s broker %s partition %i: %s\n", m_tic.c_str(), m_host.c_str(), partition, rd_kafka_err2str(rd_kafka_last_error()));
		m_bLink = false;
	}
	else
	{
		LOG(5)("Sent %s  to  topic %s broker %s partition %i\n", pMsg, m_tic.c_str(), m_host.c_str(), partition);
	}
#else
	LOG(5)("Sent %s  to topic %s broker %s\n", data->val->toStyledString().c_str(), m_tic.c_str(), m_host.c_str());

#endif



	return 0;
}

static void KafkaReadPipe(int fd, short which, void *ctx)
{
	if (!ctx)
	{
		LOG2(1)("ctx is NULL while Event_ReadPipe %d\n", __LINE__);
		return;
	}



	((CTLKafaProducter *)ctx)->OnReadPipe(fd, which);
}

void KafkaOnTimer(int fd,short ev,void *ctx)
{
	if (!ctx)
	{
		LOG2(1)("ctx is NULL while Event_ReadPipe %d\n", __LINE__);
		return;
	}

	((CTLKafaProducter *)ctx)->ProcessTimeout();
}



int CTLKafaProducter::InitEvent()
{
	m_base = event_base_new();
	if (m_base)
	{
		m_pipeEv = event_new(m_base, m_pipe.ReadFd(), EV_READ | EV_PERSIST, KafkaReadPipe, this);
		if (!m_pipeEv)
		{
			LOG2(1)("CTLKafaProducter: create pipe read event failed\n");
			return -1;
		}
		else if (0 != event_add(m_pipeEv, NULL))
		{
			LOG2(1)("CTLKafaProducter: add pipe event failed\n");
			event_free(m_pipeEv);
			m_pipeEv = NULL;
			return -1;
		}
	}

	if(m_timerEvent)
	{
		event_del(m_timerEvent);
		event_free(m_timerEvent);
		m_timerEvent = NULL;
	}

	m_timerEvent = event_new(m_base, -1, EV_TIMEOUT|EV_READ|EV_PERSIST, KafkaOnTimer, (void*)this);
	if(!m_timerEvent)
	{
		LOG(Log::LOG_LEVEL_ERROR)("CTLKafaProducter::InitTimer event_new return null\n");
		return -1;
	}
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (0 != event_add(m_timerEvent, &tv))
	{
		LOG(Log::LOG_LEVEL_ERROR)("CTLKafaProducter::InitTimer event_add failed\n");
		event_free(m_timerEvent);
		m_timerEvent = NULL;
		return false;
	}

	CoreThread::CreateNewThread(this, NULL);
	return 0;
}


void CTLKafaProducter::StopWork()
{
	CTLKafkPipeData data;
	int nLen = sizeof(CTLKafkPipeData);
	MutexObject obj(&m_pipeMutex);
	data.cmd = KAFKA_STOP;
	int writed = m_pipe.WriteData((const char*)&data, nLen); 
	if (writed != nLen)
	{
		LOG(Log::LOG_LEVEL_ERROR)("ERR write pipe writed=%d err=%d  line=%d\n", writed, errno, __LINE__);
	}
	return ;
}




void CTLKafaProducter::OnReadPipe( int fd, short which )
{
	CTLKafkPipeData data;
	m_pipe.ReadData((char*)&data, sizeof(CTLKafkPipeData));

	switch(data.cmd)
	{
	case KAFKA_STOP:
		ProcessStop();
		break;
	case KAFKA_PRODUCT:
		{
			CTLKafkaProductData* in = (CTLKafkaProductData*) data.para;
			if(in)
			{
				in->pClient->ProcessKafkaProduct(in);
				delete in->val;
				delete in;
			}
			break;
		}
	case KAFKA_UPDATE:
		{
			CTLKafkaClient* pClient = (CTLKafkaClient*) data.para;
			ProcessUpdateHost(pClient);
			break;
		}
	default:
		LOG2(1)("CTLWorkQueue::OnReadPipe undefine cmd %u\n", data.cmd);
		break;
	}

}

void CTLKafaProducter::ProcessUpdateHost(CTLKafkaClient* pClient)
{
	if(!pClient)
	{
		return;
	}
	pClient->FreeProducer();
	pClient->InitProducer();
	
}

void CTLKafaProducter::ProcessStop()
{
	event_base_loopexit(m_base, NULL);
}

void CTLKafaProducter::ProcessTimeout()
{
	m_timer = (m_timer + 1) % KAFKA_AROUND;

	if(m_timer % KAFKA_CHECK_CONN == 0)
	{
		
		//if(!m_bLink)
		//{
		//	ProcessUpdateHost();
		//}
		
	}
	
	
	
};



void CTLKafaProducter::run( void *mParameter )
{
	if (m_base)
	{
		LOG2(1)("CTLKafaProducter begin event_base_dispatch  line=%d\n", __LINE__);
		int retval = event_base_dispatch(m_base);
		LOG2(1)("CTLKafaProducter end event_base_dispatch  line=%d return=%d\n", __LINE__, retval);
	}
}

