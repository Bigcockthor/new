// ChatServer.h: interface for the ChatServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined BIGROOM_SERVER_H_SKSDKFS_H_
#define BIGROOM_SERVER_H_SKSDKFS_H_


#include "ace/Reactor.h" 
#include "ace/Svc_Handler.h" 
#include "ace/Acceptor.h" 
#include "ace/Synch.h" 
#include "ace/Asynch_IO.h" 
#include "ace/SOCK_Acceptor.h" 
#include "ace/Thread.h" 
#include "ace/SOCK_Dgram.h"
#include "ace/Event_Handler.h" 
#include "ace/Hash_Map_Manager.h"
#include "ace/Task.h"


#include "RoomManager.h"


class ChatServer;
typedef ACE_Singleton<ChatServer,ACE_Null_Mutex> ChatSvrD; 

class ChatServer :public ACE_Task<ACE_NULL_SYNCH>
{
public:
	RoomManager*		m_pRoomManager;

	int Stop();


	virtual int svc (void);
	
	ChatServer();
	virtual ~ChatServer();
	int Start(int argc, char* argv[]);
	int handle_signal(int signum, siginfo_t*,ucontext_t*);
	char m_sLogStr[1024];
	
public:
	ACE_SOCK_Dgram* m_cmdSock;
private:
	bool m_bRunning;
};

#endif
