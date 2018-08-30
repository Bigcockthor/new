#pragma once

#include "include/icqtypes.h"
#include "ace/SString.h"
#include "ace/Malloc.h"
#include "ace/Malloc_T.h"
#include "ace/Task_T.h"
#include "ace/Vector_T.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/Local_Memory_Pool.h"
#include "room/RoomCmdDef.h"


enum 
{
	CHAT_KEEPALIVE_CMD_TIMEOUT	= 0x01,

};


enum 
{
	CHAT_SEND_ERROR_SESSION_CMD	= 0x01,
};







enum	//ͨ����������
{
	CHANNEL_SVC_UNKNOWN = 0x00,	//δ����ͨ��
	CHANNEL_SVC_CMD = 0x01,		//����ͨ��
	CHANNEL_SVC_MEDIA,
};

enum 
{
	MB_INPACKET	= ACE_Message_Block::MB_USER +1,				//���Ĵ���
	MB_D_TIMEOUT,												//���䳬ʱ������
	MB_CACHEREQ,												//db cache������
	MB_SWITCH_MSG,												//Msg Switch��Ϣ
	MB_RELOADROOMINFO,											//�ض�������Ϣ
	MB_GLOBLE_MSG,												//ȫ��С����
	MG_GLOBLE_GREAT_GIFT,										//ȫ�ִ���㲥
	MB_DB_RESULT_HANDLE,											//dbclient
	MB_TCPINPACKET,
	MB_TCPINPROXY,
	MB_BEANSTALK,												//beanstalk��Ϣ����
};








#define DEFAULT_QUENE_HIGH_WATER_MARK		51200
#define DEFAULT_QUENE_LOW_WATER_MARK		25600
#define DEFAULT_RETRY_TIME					10			//��������ʱ����

typedef	 ACE_Task<ACE_MT_SYNCH> ActiveObj;
typedef  ACE_Malloc<ACE_LOCAL_MEMORY_POOL,ACE_SYNCH_MUTEX> MUTEX_MALLOC;
typedef ACE_Allocator_Adapter<MUTEX_MALLOC> Mutex_Allocator;


#define LOGNAME	"newppc_server"
#define LOGVER	"1.0.0.1"

//typedef  ACE_Malloc<ACE_LOCAL_MEMORY_POOL,ACE_SYNCH_NULL_MUTEX> NULLMUTEX_MALLOC;
//typedef ACE_Allocator_Adapter<NULLMUTEX_MALLOC> NullMutex_Allocator;

