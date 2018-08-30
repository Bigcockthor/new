
#include "ace/Reactor.h"
#include "BigRoomServer.h"
#include "option.h"
#include "include/CrashCatch.h"
#include "include/debug_new.h"
#include "include/icqsocket.h"
#include "RoomManager.h"
#include "ace/Signal.h"
#include "dbAccess.h"

#include "include/log.h"

#define DEFAULT_CONFIG_FILE "ppc.xml"


string configFile;


int main_(int argc, char* argv[])
{ 
	CoreSocket::SocketStartUp();

	


	if (CoreSocket::SocketStartUp() == false)
		return false;


	if(argc >1 )
		configFile = argv[1];
	else
		configFile = DEFAULT_CONFIG_FILE;

	BigRoomOption::instance()->ReadConfig(configFile.c_str()) ;

	char buf[256] = {0};
	snprintf(buf, sizeof(buf)-1, "%s%u", BigRoomOption::instance()->logFile.c_str(), BigRoomOption::instance()->servid);

#ifdef _WIN32
	Log::open(buf, LOGNAME, LOGVER, BigRoomOption::instance()->logLevel, true);
#else
	Log::open(buf,BigRoomOption::instance()->logLevel, false);
#endif

	//初始化数据访问接口
	dataport::CDBClientBase::GlobalDbCltInit();
	std::string http_url="http://";
	http_url+=BigRoomOption::instance()->m_db_ip;
	http_url+=":";
	http_url+=BigRoomOption::instance()->m_db_port;

	//开启数库访问接口	
	int t = SingleDbAccess::instance()->open(BigRoomOption::instance()->m_db_thread_num,http_url.c_str(),BigRoomOption::instance()->m_db_passwd.c_str(),BigRoomOption::instance()->m_db_appkey.c_str());
	if(t != 0)
	{
		LOG(1)("create dbclient dbpool error\n");
		return 1;
	}


	if (BigRoomOption::instance()->servid != 0)
		Log::ChangeLevel(BigRoomOption::instance()->logLevel);
	
	
	ACE_OS::srand (time(NULL));	//(u_int) ACE_OS::time (0));

	if(ChatSvrD::instance()->Start(argc,argv) == -1)
		return -1;
	
	ChatSvrD::instance()->svc();

	ACE_Time_Value sleeptime(0,1000000);
	ACE_OS::sleep(sleeptime);
	//关闭数据库访问接口
	SingleDbAccess::instance()->close();
	return 0; 
} 


int main(int argc, char **argv)
{
	int times = 0;
	while(times++ < 10)
	{
#ifdef _WIN32
		int pid=0;
#else
		pid_t pid = fork();
#endif
		switch (pid)
		{
		case -1:
			mysleep(2000);
			break;
		case 0:
			{
				main_(argc, argv);
				exit(0);
			}
			break;
		default:
			{
#ifndef _WIN32
				int i;
				wait(&i);
				mysleep(2000);
#endif
			}
		}
	}
	return 0;
}

