#include "UserManager.h"
#include "include/debug_new.h"

UserManager::UserManager(int size) : m_UserMap(size)
{
}

UserManager::~UserManager(void)
{
}


int UserManager::AddUser(User *user, uint32 ip, uint16 port,uint32 roomid)
{
	ACE_TString key;
	char keystr[60];

	ACE_OS::sprintf(keystr,"%u-%u-%u",ip,port,roomid);
	key.set(keystr);

	int res = m_UserMap.bind (key, user);

	return res;
}


int UserManager::AddUser(User *user, uint32 uin)
{
	ACE_TString key;
	char keystr[20];
	
	ACE_OS::sprintf(keystr,"%u",uin);
	key.set(keystr);
	
   int res = -1;

   MutexObject mu(&mapLock);

   res = m_UserMap.bind (key, user);

	return res;
}


int UserManager::RemoveUser(uint32 ip, uint16 port, uint32 roomid)
{
	ACE_TString key;
	char keystr[60];
	
	ACE_OS::sprintf(keystr,"%u-%u-%u",ip,port,roomid);
	key.set(keystr);

	MutexObject mu(&mapLock);


	return m_UserMap.unbind (key);
}


int UserManager::RemoveUser(uint32 uin)
{

	ACE_TString key;
	char keystr[20];
	
	ACE_OS::sprintf(keystr,"%u",uin);
	key.set(keystr);

	MutexObject mu(&mapLock);

	return m_UserMap.unbind (key);
}

void UserManager::RemoveAllUsers()
{
	MutexObject mu(&mapLock);

	m_UserMap.unbind_all();
}

User* UserManager::GetUser(uint32 ip, uint16 port, uint32 roomid)
{

	User *pUser = NULL;
	ACE_TString key;
	char keystr[60];
	
	ACE_OS::sprintf(keystr,"%u-%u-%u",ip,port,roomid);
	key.set(keystr);

	int res;
	MutexObject mu(&mapLock);

	res = this->m_UserMap.find (key,pUser);
	if (res != 0)
		return NULL;
	else
		return pUser;
}

User* UserManager::GetUser(uint32 uin)
{
	User *pUser;
	ACE_TString key;
	char keystr[20];
	
	ACE_OS::sprintf(keystr,"%u",uin);
	key.set(keystr);

	MutexObject mu(&mapLock);

	if (this->m_UserMap.find (key, pUser) != 0)
	{
		return NULL;  
	}
	else
		return pUser;
}

uint16 UserManager::GetUserCount()
{
	MutexObject mu(&mapLock);

	return (uint16)m_UserMap.current_size();

}




