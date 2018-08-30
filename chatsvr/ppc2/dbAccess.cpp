#include "dbAccess.h"
#include "RoomManager.h"
#include "../tools/common.h"
#include "ace/ACE.h"
#include "include/coretime.h"

namespace BigRoom
{
	DbAccessPara::DbAccessPara()
		:m_room_man(NULL),
		m_start_time(talk_base::TimeStamp())
	{

	}

	DbAccessPara::~DbAccessPara()
	{

	}

	uint32 DbAccessPara::GetPassTime()
	{
		return TIME_DIFF_U(talk_base::TimeStamp(),  m_start_time);
	}

	DbLogonPara::DbLogonPara()
		:m_user(NULL),
		m_room_id(0)
	{

	}

	DbLogonPara::~DbLogonPara()
	{

	}

	DbAccess::DbAccess()
	{
	}

	DbAccess::~DbAccess()
	{

	}

	void DbAccess::OnResult(dataport::CDBClientResult * result)
	{
		ACE_Message_Block* mb = NULL;
		ACE_NEW_MALLOC_NORETURN (mb,
			ACE_static_cast
			(	ACE_Message_Block*,
			RoomManager::_buf_allocator->malloc (sizeof (ACE_Message_Block))
			),
			ACE_Message_Block
			(sizeof(dataport::CDBClientResult*), // size
			MB_DB_RESULT_HANDLE, // type
			0,
			0,
			RoomManager::_buf_allocator, // allocator_strategy
			0, // locking strategy
			ACE_DEFAULT_MESSAGE_BLOCK_PRIORITY, // priority
			ACE_Time_Value::zero,
			ACE_Time_Value::max_time,
			RoomManager::_buf_allocator,
			RoomManager::_buf_allocator
			)
			);	

		if(!mb)
			return;

		RoomManager * room_man=((DbAccessPara *)result->arg)->m_room_man;
		dataport::CDBClientResult ** loadin = (dataport::CDBClientResult**)mb->base();
		*loadin = result;
		ACE_Time_Value xtime(ACE_OS::gettimeofday()+g_puttimeout);
		if(room_man->putq(mb, &xtime) == -1)
		{
			mb->release();
			return;
		}
	}
}

