#ifndef BEANSTALK_CLENT_H
#define BEANSTALK_CLENT_H


#ifdef WIN32
	#include <winsock2.h>
#else

#include "beanstalk.h"
#endif
#include "include/corethread.h"
#include "include/log.h"
#include "include/icqtypes.h"

#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;



namespace  Beanstalk {
    typedef std::vector<std::string> info_list_t;
    typedef std::map<std::string, std::string> info_hash_t;
	class  Job {
        public:
            uint64 id();
            std::string& body();
            Job(uint64, char*, size_t);
#ifndef WIN32
			Job(BSJ*);
#endif
            Job();
			~Job();
            operator bool() { return _id > 0; }
        protected:
            uint64 _id;
            std::string _body;
    };

	class  Client{
        public:
			virtual ~Client();
            Client();
            Client(std::string host, int port, float timeout_secs = 0);
            int ping();
            int use(std::string);
            int watch(std::string);
            int ignore(std::string);
            uint64 put(std::string body, uint32 priority = 0, uint32 delay = 0, uint32 ttr = 60);
            uint64 put(char *data, size_t bytes, uint32 priority, uint32 delay, uint32 ttr);
            int del(uint64 id);
            int del(Job&);
            int reserve(Job &job);
            int reserve(Job &job, uint32 timeout);
            int release(Job &job, uint32 priority = 1, uint32 delay = 0);
            int release(uint64 id, uint32 priority = 1, uint32 delay = 0);
            int bury(Job &, uint32 priority = 1);
            int bury(uint64 id, uint32 priority = 1);
            int touch(Job &);
            int touch(uint64 id);
            int peek(Job &, uint64 id);
            int peek_ready(Job &);
            int peek_delayed(Job &);
            int peek_buried(Job &);
            int kick(int bound);
            int connect(std::string host, int port, float timeout_secs = 0);
            int reconnect();
            int disconnect();
            std::string list_tube_used();
            info_list_t list_tubes();
            info_list_t list_tubes_watched();
            info_hash_t stats();
            info_hash_t stats_job(uint64);
            info_hash_t stats_tube(std::string);
        protected:
            float timeout_secs;
            int handle, port;
            std::string host;
    };

	class  BCMessageBase
	{
	public:

		BCMessageBase(uint32 msgType);
		virtual ~BCMessageBase();
	public:
		uint32 m_msgType;
	};

	class JobPush
	{
	public:
		JobPush(const std::string &tubeName, const std::string &data, const uint32 priority, const uint32 delay, const uint32 ttr)
			:m_tubeName(tubeName),m_data(data),m_priority(priority),m_delay(delay),m_ttr(ttr)
		{

		}
	public:
		std::string m_tubeName;
		std::string m_data;
		uint32 m_priority;
		uint32 m_delay;
		uint32 m_ttr;
	};
	class  BeanstanlkdClient : public Client , public CoreThreadHandle
	{
	public:
		BeanstanlkdClient(){}
		virtual ~BeanstanlkdClient(){}
		int WatchTube();
		std::string GetJobBody(uint32 _timeout_secs);
		uint32 OpenClient(std::string host, uint32 port, float timeout_secs, std::list<std::string> *tubeList);
		static int SplitMsg(std::string &src, std::string splitStr, std::string &childStr);
		virtual BCMessageBase * ResolvData(std::string &strData) = 0;//解析job，把job转换成message,返回消息对象的指针
		virtual uint32 HandleBCMsg() = 0;//从消息队列中去数据,然后处理
		uint32 PutMsgToServer(const std::string &tubeName, const string &data, uint32 priority = 0, uint32 delay = 0, uint32 ttr = 60);

	protected:
		virtual void run(void *mParameter);
		BCMessageBase *GetOneMsg();
		uint32 PushMsgToServer();

	protected:
		std::list<BCMessageBase *> m_msgList;//从server接收过来的msg队列
		std::list<JobPush *> m_jobList;//需要发送到server的队列
		Mutex g_msgMutex;
		Mutex g_jobMutex;
		//Mutex g_putOrPush;
		static uint64 pingTimeOut;
		std::string m_host;
		uint16 m_port;
		std::list<std::string> m_tubeList;
	};
}

#endif
