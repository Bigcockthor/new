#if !defined BIGROOM_USER_MANAGER_H_
#define BIGROOM_USER_MANAGER_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Singleton.h"
#include "User.h"

#define DEFAULT_USER_SIZE	20

using namespace BigRoom;

//typedef ACE_Hash_Map_Manager<ACE_TString, User*, ACE_SYNCH_MUTEX> MuteUserMap;
typedef ACE_Hash_Map_Manager<ACE_TString, User*, ACE_SYNCH_NULL_MUTEX> UserMap;
//typedef ACE_Hash_Map_Manager<ACE_UINT32, User*, ACE_SYNCH_NULL_MUTEX> UserMap;

class UserManager
{
public:
	UserMap		m_UserMap;		//在线用户


public:
	UserManager(int size = DEFAULT_USER_SIZE);
	virtual ~UserManager(void);

	User* GetUser(uint32 uin);
	int RemoveUser(uint32 uin);
	int AddUser(User *user, uint32 uin);
	User* GetUser(uint32 ip,uint16 port,uint32 roomid);
	int RemoveUser(uint32 ip,uint16 port,uint32 roomid);
	int AddUser(User* user,uint32 ip,uint16 port,uint32 roomid);
	void RemoveAllUsers();
	uint16	GetUserCount();

private:
	Mutex mapLock;	
};

#endif  //BIGROOM_USER_MANAGER_H_
