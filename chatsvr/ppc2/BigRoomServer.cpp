#include "BigRoomServer.h"
#include "option.h"
#include "bigroomdef.h"
#include "include/log.h"
#include "include/debug_new.h"
#include "ace/Signal.h"


ChatServer::ChatServer()
{
	m_pRoomManager = 0;
	m_cmdSock = 0;
}

ChatServer::~ChatServer()
{
 
}

int ChatServer::handle_signal(int signum, siginfo_t*,ucontext_t*)
{
	switch(signum)
	{
	case SIGINT:
		LOG(4)("You pressed SIGINT\n");

		this->Stop();
		break;
	}
	return 0;
}

int ChatServer::svc (void)
{

	ACE_Sig_Action sig ((ACE_SignalHandler) SIG_IGN, SIGPIPE);
	ACE_UNUSED_ARG (sig);
	
	ACE_Reactor::instance()->register_handler(SIGINT,this);
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}


int ChatServer::Start(int , char** )
{
	m_pRoomManager = new RoomManager();
	if(m_pRoomManager->open() != -1)
	{
		m_pRoomManager->inited = true;

		m_bRunning = true;

		LOG(0)("ChatServer started successfully\n");


		return 0;

	}
	else
	{
		LOG(0)("ChatServer can not open roommanager,start failed\n");

		return -1;
	}
}



int ChatServer::Stop()
{
	LOG(4)("ChatServer stopping......\n");


	m_bRunning = false;
	ACE_Reactor::instance()->end_event_loop();


	LOG(4)("BigRoom Service %d stoped\n", BigRoomOption::instance()->servid);
	return 1;
}

