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

	//4��3����ӣ����ݿ�����еĶ������
	class DbAccessPara
	{
	public:
		DbAccessPara();

		virtual ~DbAccessPara();

		RoomManager * m_room_man; //���������

		uint32 GetPassTime();

	private:

		uint32 m_start_time; //��ʼ�������ݿ��ʱ��
	};


	class DbLogonPara:public DbAccessPara
	{
	public:
		DbLogonPara();

		virtual ~DbLogonPara();

		User * m_user; //�û���Ϣ

		uint32 userid;	 //�û�id

		uint32 m_room_id; //�����
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

		uint32 m_room_id; //�����

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

	//���ؽ����Ҫ���뷿���һ������
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
		uint32	m_userid;		//�û�id
		Room*	m_pRoom;		//����
		uint32	m_awardRound;	//�ֺ�
		uint8	m_awardID;		//����id
		uint32  m_Count;		//Ѻע��� �н����

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
		Room*	m_pRoom;		//����

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
		uint32 m_src_usr_id;	//�ͳ��µ���
		uint32 m_dst_usr_id;	//�����µ���
		uint16 m_stamp_id;
		uint32 expire_time;
		uint32 m_stamptime;		//�Ӹ�����Ϣ���ж�ȡ��ӡ��ʱ�䣬��λ����
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

