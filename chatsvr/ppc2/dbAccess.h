#ifndef DB_ACCESS_H
#define DB_ACCESS_H

#pragma once

#include "dbclient/dbclient.h"
#include "ace/Singleton.h"
#include "User.h"

typedef std::vector<uint32> Uint32Vector;

namespace BigRoom
{
	class RoomManager;

	//4月3号添加：数据库访问中的额外参数
	class DbAccessPara
	{
	public:
		DbAccessPara();

		virtual ~DbAccessPara();

		RoomManager * m_room_man; //房间管理器

		uint32 GetPassTime();

	private:

		uint32 m_start_time; //开始访问数据库的时间
	};


	class DbLogonPara:public DbAccessPara
	{
	public:
		DbLogonPara();

		virtual ~DbLogonPara();

		User * m_user; //用户信息

		uint32 userid;	 //用户id

		uint32 m_room_id; //房间号
	};

	class DbGettingRoomPara:public DbAccessPara
	{
	public:
		DbGettingRoomPara()
		{
			m_room_id = 0;
			m_handle_type = FIRST_LOAD;
		}
		enum HANDLE_TYPE{
			FIRST_LOAD,
			RELOAD
		};

		uint32 m_room_id; //房间号

		HANDLE_TYPE m_handle_type;
	};

	class DbGetAuthListPara:public DbAccessPara
	{

	public:
		unsigned int m_action;
	};

	class DBParaHandleByRoom:public DbAccessPara
	{
	public:
		uint32 m_error_code;
		uint32 m_room_id;
	};

	//返回结果需要进入房间进一步处理
	class DbZZAwardPara : public DBParaHandleByRoom
	{
	public:
		DbZZAwardPara()
		{
			memset(this, sizeof(DbZZAwardPara), 0);
		}

		virtual ~DbZZAwardPara()
		{

		}
		uint32	m_userid;		//用户id
		Room*	m_pRoom;		//房间
		uint32	m_awardRound;	//局号
		uint8	m_awardID;		//奖项id
		uint32  m_Count;		//押注金额 中奖金额

	};

	class DbZZPoolPara : public DBParaHandleByRoom
	{
	public:
		DbZZPoolPara()
		{
			memset(this, sizeof(DbZZPoolPara), 0);
		}

		virtual ~DbZZPoolPara()
		{

		}
		Room*	m_pRoom;		//房间

	};

	class DbParaUseGift:public DBParaHandleByRoom
	{
	public: 
		DbParaUseGift()
		{
			m_src_usr_id = m_dst_usr_id = m_gift_id = m_price = m_amount = 0;
			m_prize_money = m_company_tax = m_gift_kind = m_receive_count = 0;
			m_pool_money = 0;
			m_host_tax = 0;
			roomOwner = 0;
			dstType = 0;
		}
		uint32 m_src_usr_id;
		uint32 m_dst_usr_id;
		uint8 dstType;
		uint32 m_gift_id;
		uint32 m_price;
		uint32 roomOwner;
		uint32 m_amount;
		uint32 m_prize_money;
		uint32 m_pool_money;
		uint32 m_company_tax;
		uint32 m_gift_kind;
		uint32 m_receive_count;
		uint32 m_host_tax;
		Uint32Vector m_prize_multiple;
		Uint32Vector dstUinList;
	};

	class DbParaUserStamp:public DBParaHandleByRoom
	{
	public:
		DbParaUserStamp ()
		{
			m_src_usr_id = 0;
			m_dst_usr_id = 0;
			m_stamp_id = 0;
			expire_time = 0;
			m_stamptime = 0;
		}
		uint32 m_src_usr_id;	//送出章的人
		uint32 m_dst_usr_id;	//被盖章的人
		uint16 m_stamp_id;
		uint32 expire_time;
		uint32 m_stamptime;		//从盖章信息表中读取的印章时间，单位分钟
		string text;
	};

	class DbParaMicPresent:public DBParaHandleByRoom
	{
	public:
		DbParaMicPresent()
		{
			uin = gotGift = gotChat = 0;
		}
		uint32 uin;
		uint32 gotGift;
		uint32 gotChat;
	};

	class DbParaBuyGlobalMsg:public DBParaHandleByRoom
	{
	public:
		DbParaBuyGlobalMsg()
		{
			m_udp_pack = NULL;
			m_usr_id = m_fee = 0;
		}
		UdpInPacket * m_udp_pack;
		uint32 m_usr_id;
		uint32 m_fee;
	};

	class DbParaUin:public DBParaHandleByRoom
	{
	public:
		DbParaUin()
		{
			uin  = 0;
			mac = 0;
		}
		uint32 uin;
		uint64 mac;
	};
	
	class DbParaIpPort:public DBParaHandleByRoom
	{
	public:
		DbParaIpPort()
		{
			uin = 0;
			mac = 0;
			ip = 0;
			port = 0;
		}
		uint32 uin;
		uint64 mac;
		uint32 ip;
		uint16 port;
	};

	class DbParaLockMoney:public DBParaHandleByRoom
	{
	public:
		DbParaLockMoney()
		{
			uin  = 0;
		}
		uint32 uin;
		uint8 nState;
	};

	class DbParaPPCBet:public DBParaHandleByRoom
	{
	public:
		DbParaPPCBet()
		{
			around  = 0;
		}
		uint32 around;

	};

	class DbParaPPCBanker:public DBParaHandleByRoom
	{
	public:
		DbParaPPCBanker()
		{
			around  = 0;
			uin = 0;
		}
		uint32 around;
		uint32 uin;
	};

	class DbAccess:public dataport::CDBClientBase
	{
	public:
		DbAccess();

		virtual ~DbAccess();

		virtual void OnResult (dataport::CDBClientResult *result);
	};

	typedef ACE_Singleton<DbAccess,ACE_Null_Mutex> SingleDbAccess;
}

#endif

