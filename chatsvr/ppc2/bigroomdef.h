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







enum	//通道服务类型
{
	CHANNEL_SVC_UNKNOWN = 0x00,	//未定义通道
	CHANNEL_SVC_CMD = 0x01,		//命令通道
	CHANNEL_SVC_MEDIA,
};

enum 
{
	MB_INPACKET	= ACE_Message_Block::MB_USER +1,				//报文处理
	MB_D_TIMEOUT,												//房间超时检查机制
	MB_CACHEREQ,												//db cache处理返回
	MB_SWITCH_MSG,												//Msg Switch消息
	MB_RELOADROOMINFO,											//重读房间信息
	MB_GLOBLE_MSG,												//全局小喇叭
	MG_GLOBLE_GREAT_GIFT,										//全局大礼广播
	MB_DB_RESULT_HANDLE,											//dbclient
	MB_TCPINPACKET,
	MB_TCPINPROXY,
	MB_BEANSTALK,												//beanstalk消息处理
};








#define DEFAULT_QUENE_HIGH_WATER_MARK		51200
#define DEFAULT_QUENE_LOW_WATER_MARK		25600
#define DEFAULT_RETRY_TIME					10			//连接重试时间间隔

typedef	 ACE_Task<ACE_MT_SYNCH> ActiveObj;
typedef  ACE_Malloc<ACE_LOCAL_MEMORY_POOL,ACE_SYNCH_MUTEX> MUTEX_MALLOC;
typedef ACE_Allocator_Adapter<MUTEX_MALLOC> Mutex_Allocator;


#define LOGNAME	"newppc_server"
#define LOGVER	"1.0.0.1"

//typedef  ACE_Malloc<ACE_LOCAL_MEMORY_POOL,ACE_SYNCH_NULL_MUTEX> NULLMUTEX_MALLOC;
//typedef ACE_Allocator_Adapter<NULLMUTEX_MALLOC> NullMutex_Allocator;

