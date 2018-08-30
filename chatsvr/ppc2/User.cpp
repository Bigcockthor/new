 #include "User.h"
#include "BigRoomServer.h"
#include "include/log.h"
#include "room/RoomCmdDef.h"
#include "include/debug_new.h"
#include "include/socketaddress.h"
//#include "UserSession.h"


IMPLEMENT_SLAB(User, 64)

#define DESTROY_USER_WAIT_TIME  3
#define EVERYPACKETUSERNUM		30								//分包发送好友列表


#define KEY_KEEPALIVE_TIMEOUT	60




namespace BigRoom
{
	User::User(uint32 initUin, uint32 initSid, uint8 android) : isAndroid(android), uin(initUin), m_sid(initSid)
	{
		prized = false;

		onMicStartTime = 0;
		filterWordTimes = 0;
		m_window = 0;

		customFace = 0;
		richOrder = 0;
		forbidChat = 0;
		lastBetRound = 0;

		m_roomid = 0;											//默认为聊天室大厅
		ip = 0;													//外部ip
		port = 0;												//udp端口
		proxyIP = 0;
		proxyPort = 0;
		m_seq = 0;
		earnMoney = 0;											//初始化中奖偏好
		chatUserType = chat_user_general;
		isGameLimit = 0;
		unBetCount = 0;
		kickLimitTimes = 0;
		m_loginStart = talk_base::TimeStamp();
		m_timertime	= DESTROY_USER_WAIT_TIME;
		rank		= USER_RANK_GENERAL; 
		g_userType = 0;
		levelInfo.value = 0;
		m_lastText = 0;
		money = 0;
		received = 0;
		starttime = time(NULL);
		ResetKeepAlive();	
		m_nChannelState = ROOM_UDPSERVER;
		memset(userNick, 0, sizeof(userNick));
		m_bBindLogin = 0;
		m_passType   = 0;	
		m_nState = NORMAL_STATE;
		earning = 0;
	}

	User::~User(void)
	{
		micWait.remove();											//从排麦列表中退出

		ClearSendQueue();

		item.remove();
	}

	void User::ClearSendQueue()
	{
		ClearSendQueue(sendQueue);
		ClearSendQueue(sendQueueEx);
	}

	void User::ClearSendQueue(PACKETLIST& sendList)
	{
		while (sendList.size())
		{
			UdpOutPacket *p = *sendList.begin();

			p->sendItem.remove();
			p->globalSendItem.remove();
			delete p;
			sendList.pop_front();
		}

	}


	bool User::RankIsSuperMan()
	{
		if(rank & USER_RANK_SUPERMAN)
			return true;
		else
			return false;
	}

	bool User::RankIsRoomOwner()
	{
		return (uin == m_pMyRoom->ownuin);
	}

	bool User::RankIsManager()
	{
		if(rank & USER_RANK_ROOMMAN)
			return true;
		else
			return false;
	}

	bool User::RankIsVisitor()
	{
		if(rank & USER_RANK_VISITOR)
			return true;
		else 
			return false;
	}


	bool User::ValidatePacket( UdpInPacket* in )
	{
		if(in->header.sid != m_sid) 
			return false;

		if(port != in->port)
			port = in->port;

		if(m_nState != NORMAL_STATE)
		{
			LOG(4)("Notify IM_CHAT_KEEP_ALIVE failed room %d uin %d seq %d insid %d usersid %d\n", m_pMyRoom->roomid, uin, in->header.seq, in->header.sid, m_sid);
			return false;
		}
		ResetKeepAlive();


		if (in->header.cmd != IM_CHAT_ACK)
		{
			SendAckPacket(in->header.seq);
		}

		if (in->header.cc)
		{
			this->OnRcvAck(in->header.cc);
		}

		if (in->header.cmd == IM_CHAT_ACK)
		{

			return false;
		}

		if(in->header.cmd == IM_CHAT_KEEP_ALIVE) 
		{
			if (m_pMyRoom && m_pMyRoom != RoomManager::gRoot)
			{
				this->OnRcvKeepAlive(in);
			}

			LOG(7)("Notify IM_CHAT_KEEP_ALIVE room %d uin %d seq %d insid %d usersid %d\n", m_pMyRoom->roomid, uin, in->header.seq, in->header.sid, m_sid);
			return false;
		}

		return setWindow(in->header.seq);
	}





	bool User::CheckKeepAlive()
	{
		return m_keepaliveExpire > time(0);
	}




	/************************************************************
	*															*
	*					general room operate					*
	************************************************************/
	//called by room when a validated user enter room
	int User::OnLogon(Room* pRoom)
	{
		SendAckPacket(m_seq);

		if(this->SendLogonResult((uint16)LOGON_SUCCESS, pRoom) == -1)
			return -1;
		
		starttime = time(NULL);

		return 1;
	}

	//called by room when a invalidated user enter room
	void User::OnLogonFail(Room* pRoom,uint16 failCode, uint32 blockTime)
	{
		if (!pRoom)
			return;

		switch(failCode)
		{	
		case LOGON_INVALID_UIN:
			LOG(4)("Logon fail because of LOGON_INVALID_UIN\n");
			break;
		case LOGON_WRONG_PASSWD:
			LOG(4)("Logon fail because of LOGON_WRONG_PASSWD\n");
			break;
		case LOGON_ROOM_FAILED:
			LOG(4)("Logon fail because of LOGON_ROOM_FAILED %u, %u\n", pRoom->roomid, uin);
			break;
		case LOGON_ROOM_IS_BUSY:
			LOG(4)("Logon fail because of LOGON_ROOM_IS_BUSY");
			break;
		case LOGON_REJECT:
			LOG(4)("Logon fail because of LOGON_NO_THIS_ROOM\n");
			break;
		case LOGON_REQ:
			LOG(4)("Logon fail because of LOGON_REQ\n");
			break;
		case LOGON_VISITOR_ISFULL:
			LOG(4)("Logon fail because of LOGON_VISITOR_ISFULL\n");
			break;
		case LOGON_ROOM_CLOSE:							    //房间是关闭的
			LOG(4)("Logon fail because of LOGON_ROOM_CLOSE\n");
			break;
		case LOGON_WRONG_ROOM_PASSWD:						//需要密码
			LOG(4)("Logon fail because of LOGON_WRONG_ROOM_PASSWD\n");
			break;
		case LOGON_ROOM_ISFULL:								//房间已满
			LOG(4)("Logon fail because of LOGON_ROOM_ISFULL\n");
			break;
		case LOGON_BLACKLIST_UIN:							//用户在黑名单中
			LOG(4)("Logon fail because of LOGON_BLACKLIST_UIN blocktime %u\n", blockTime);
			break;
		case LOGON_BLACKLIST_IP:							//IP在黑名单中
			LOG(4)("Logon fail because of LOGON_BLACKLIST_IP blocktime %u\n", blockTime);
			break;
		case LOGON_BLACKLIST_MAC:							//MAC在黑名单中
			LOG(4)("Logon fail because of LOGON_BLACKLIST_MAC blocktime %u\n", blockTime);
			break;
		case LOGON_FORBID_JOIN:								//该房间不允许您进入
			LOG(4)("Logon fail because of LOGON_FORBID_JOIN\n");
			break;
		case LOGON_ROOM_INGAME:							//正在游戏房间不容许进入
			LOG(4)("Logon fail because of LOGON_ROOM_INGAME\n");
			break;
		case LOGIN_NOENOUGH_MONEY:
			LOG(4)("Logon fail because of LOGIN_NOENOUGH_MONEY\n");
			break;
		case LOGIN_KICK_LIMITTIMES:
			LOG(4)("Logon fail because of LOGIN_KICK_LIMITTIMES\n");
			break;
		default:
			LOG(4)("Logon fail because of %d\n", failCode);
			break;
		}
		m_pMyRoom = pRoom;


		SendLogonResult((uint16)failCode, pRoom, blockTime);
	}

	//called by room when a validated user leave room
	void User::OnLogout(Room* pRoom)
	{
		ACE_UNUSED_ARG (pRoom);

		this->Dispose();
	}

	//called by room when offline because of network problem
	void User::OnOffline(bool pushOut /* = false */, uint32 newEnter /* = 0 */)
	{

	}

	int User::SendLogonResult(uint16 result, Room* pRoom, uint32 blockTime)
	{

		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_LOGON_ROOM);
		if(out)
		{
			*out << result;

			switch(result)
			{
			case LOGON_SUCCESS:
				{
					*out << userNick << face << customFace;
					*out << uint8(rank);
					*out << uint8(g_userType);
					*out << money << received << richOrder << accountState;
					*out << ""  << "" << userAcl.GetAclStr();
					

					pRoom->AppendRoomInfo(out, m_netType, this);
					uint32 now = talk_base::TimeStamp();

#ifdef _WIN32
					LOG(0)("LL %u logon room %u  devType = %d %s:%d  money = %I64d, recv = %I64d accountState=%d, customFace=%d, rank =%d  %I64d mac=%s proxy%s:%d, enterpic=%s newpic=%s level = %d ver=%d loginSpan %u\n", uin, 
						m_pMyRoom->GetRoomID(),  chatUserType, NIP2CHAR(ip), ntohs(port), money, received, accountState, customFace, rank, userMac, CoreSocket::TransMacAddr(userMac).c_str(),
						NIP2CHAR(proxyIP), ntohs(proxyPort),enter_pic.c_str(), "", levelInfo.level, m_ver, TIME_DIFF_U(now, m_loginStart));
#else
					LOG(0)("LL %u logon room %u  devType = %d %s:%d  money = %llu, recv = %llu accountState=%d, customFace=%d, rank =%d %llu, mac=%s proxy%s:%d enterpic=%s newpic=%s level = %d  ver=%d loginSpan %u\n", uin, 
						m_pMyRoom->GetRoomID(),  chatUserType, NIP2CHAR(ip), ntohs(port), money, received, accountState, customFace, rank, userMac, CoreSocket::TransMacAddr(userMac).c_str(), 
						NIP2CHAR(proxyIP), ntohs(proxyPort), enter_pic.c_str(), "", levelInfo.level, m_ver, TIME_DIFF_U(now, m_loginStart));

#endif

				}
				break;
			default:
				*out << blockTime;
				LOG(1)("Send to user %lu LOGIN_FAILED login %lu  mac=%s, ip=%s\n", uin, m_pMyRoom->GetRoomID(),
					CoreSocket::TransMacAddr(userMac).c_str(), NIP2CHAR(ip));
				break;
			}

			SendPacket(out);

			if(BigRoomOption::instance()->m_pPromotedPc&& (chatUserType ==  chat_user_general || chatUserType ==  chat_user_letao))
			{
				sendNtyMsg(ChatRoomMsg::STR_MSG_PROMOTED.c_str());
			}

			if(BigRoomOption::instance()->m_pPromotedMobile&& (chatUserType !=  chat_user_general && chatUserType !=  chat_user_letao))
			{
				sendNtyMsg(ChatRoomMsg::STR_MSG_PROMOTED.c_str());
			}

			

			return 0;
		}
		else
			return -1;

	}

	int User::NotifyOnline(User* pUser)
	{
		if (pUser == this)
			return 0;

		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_USER_ONLINE);
		if(!out) return -1;

		pUser->AppendUserInfo(*out, m_ver);
		*out << pUser->enter_title << pUser->enter_pic;

		 SendPacket(out);

		 return 0;
	}

	int	User::NotifyAddCfWait(uint32 uin)
	{

		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ADDCFWAIT);
		if(!out) return -1;

		*out << uin;

		 SendPacket(out);

		 return 0;
	}

	int	User::NotifyRemoveCfWait(uint32 uin)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_REMOVECFWAIT);
		if(!out) return -1;

		*out << uin;

		 SendPacket(out);

		 return 0;
	}

	int User::NotifyRoomOpen(uint32 srcuin)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ROOM_OPEN);
		if(!out) return -1;

		*out << srcuin;

		 SendPacket(out);

		 return 0;
	}

	int User::NotifyRoomClose(uint32 srcuin)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ROOM_CLOSE);
		if(!out) return -1;

		*out << srcuin;

		 SendPacket(out);

		 return 0;
	}

	int User::NotifyOffline(uint32 dstUin)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_USER_OFFLINE);
		if(!out) return -1;

		*out << dstUin;

		 SendPacket(out);

		 return 0;
	}


	int User::NotifyConfKickOut(uint32 uin, uint32 opr)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_CONF_KICKOUT);
		if(!out) return -1;

		*out << uin << opr;

		 SendPacket(out);

		 return 0;
	}

	int User::NotifyForceOffline(uint32 newroomid, uint32 newip, uint16 newport, uint8 newdevType)
	{
		if (chatUserType == chat_user_virtual)
			return 0;


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_FORCE_OFFLINE);
		if(!out) return -1;

		*out  << newip << newport << m_nState << newdevType << newroomid;

		//如果是强制自己被踢了或被挤出房间，就多发送几次命令，以防丢包收不到。
		SendPacket(out);

		return 0;
	}


	int User::NotifyKickOut(uint32 uin, uint32 actionSrc, uint8 actionType)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_KICKOUT);
		if(!out) return -1;

		*out << uin << actionSrc << actionType;

		//如果是强制自己被踢了或被挤出房间，就多发送几次命令，以防丢包收不到。
		 SendPacket(out);

		 return 0;
	}


	//通知用户某人进入会议
	int User::NotifyConfJoin(uint32 uin, uint8 micIndex, uint32 opr)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_CONF_JOIN);
		if(!out) return -1;

		*out << uin << micIndex << uint16(0) << opr;

		 SendPacket(out);

		 return 0;
	}

	//通知用户某人离开会议
	int User::NotifyConfExit(uint32 uin, uint32 opr)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_CONF_EXIT);
		if(!out) return -1;

		*out << uin << opr;

		 SendPacket(out);

		 return 0;
	}


	
	int User::SendRoomInfo(Room* pRoom)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ROOMINFO);
		if(!out) return -1;

		pRoom->AppendRoomInfo(out, m_netType, this);

		SendPacket(out);

		 return 0;
	}





	
	int User::SendRoomUserList(Room* pRoom, uint16 cmd /* = IM_CHAT_SRV_VISITOR */)
	{
		uint16 num = 0;
		uint16 total = m_pMyRoom->m_UserManager.GetUserCount();
		uint16 old = 0;
		UdpOutPacket *out = NULL;
		int	ci = 0;
		uint32 packetmark = time(NULL);

		//包的校验戳
		if(total == 0)	{
			out = CreatePacket_Head(cmd);
			if(!out) return -1;
			*out << packetmark << (uint16)1 << (uint16)0 << (uint16)0;
			SendPacket(out);

			return 0;
		}

		uint16 packetnum = (total + MAX_MEMBERS_PER_PACKET - 1) / MAX_MEMBERS_PER_PACKET;
		int pkindex = 0;

		UserMap::ITERATOR it(m_pMyRoom->m_UserManager.m_UserMap);
		UserMap::ENTRY* entry = 0;
		while(it.next(entry) != 0) 
		{
			User* pDstUser = (*entry).int_id_;
			it.advance();

			if (!num)
			{
				out = CreatePacket_Head(cmd);
				if(!out) return -1;
				*out << packetmark << packetnum << (uint16)pkindex;
				pkindex ++;
				//old = out->skip(sizeof(num));
				old = out->GetPosition(sizeof(num));
			}

			pDstUser->AppendUserInfo(*out, m_ver);
	
			if (++num >= MAX_MEMBERS_PER_PACKET)
			{
				//old = out->setCursor(old);
				old = out->SetPosition(old);
				*out << num;
				out->SetPosition(old);
				//out->setCursor(old);

				SendPacket(out);

				num = 0;
			}

			ci++;
			if(ci >= MAX_VISITORS)
				break;
		}

		if (num) {
			//old = out->setCursor(old);
			old = out->SetPosition(old);
			*out << num;
			out->SetPosition(old);
			//out->setCursor(old);
			SendPacket(out);
		}

		return 0;
	}

	int User::NotifyUseGift(uint32 srcuin,uint32 dstuin, uint32 giftid, uint32 giftamount)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_USEGIFT);
		if(out) {
			*out << srcuin  << dstuin << giftid << giftamount;
			if (srcuin == uin || dstuin == uin)
				*out << money << received;
			 SendPacket(out);

			 return 0;
		}

		return -1;
	}

	
	int User::SendTextData(uint32 srcUin,uint32 destUin,uint8 ispublic,uint32 curtime, const char* msg, uint8 type /* = 0 */)
	{

		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_TEXT);
		if(out)
		{
			*out << type << srcUin << destUin << ispublic << curtime;
			*out << msg;

			SendPacket(out);

			return 0;
		}
		else
			return -1;

	}


	int User::Dispose()
	{
		return 1;
	}



	int User::SendCmdResult(uint16 cmd, uint16 msgcode)
	{
		UdpOutPacket* out = CreatePacket_Head(cmd);
		if(!out) return -1;

		*out << msgcode;

		 SendPacket(out);

		 return 0;
	}

	void User::AppendUserInfo(UdpOutPacket &out, uint16 packetVer)
	{
		out << uin  << userNick << face << customFace;
		out << levelInfo.value;
		out << uint8(rank);
		out << uint8(g_userType);
		out << money << received << richOrder;


		//设备类型
		out << (uint8)chatUserType;
		//禁言剩余时间
		out << (uint16)(0); 
		
	}



	//通知消息
	int User::sendNtyMsg(const char* ntymsg)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_NTY_MSG);
		if(out)
		{
			*out << ntymsg << money << received;

			SendPacket(out);

			return 0;
		}
		else
			return -1;

	}

	


	void User::Release()
	{
		delete this;
	}

	//发送房间公告
	int User::SendRoomBroadCast(Room* pRoom)
	{


		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ROOM_BROADCAST);
		if(!out) return -1;

		*out << pRoom->broadcast;


		 SendPacket(out);

		 return 0;
	}

	/*
	*	from session
	*/

	int User::SendKeepAlive( uint16 seq)
	{
		UdpOutPacket out;

		out.cmd = IM_CHAT_KEEP_ALIVE;
		out.seq = 0;

		if (proxyIP)
			out << ip << port << uint8(0);

		out << m_ver << m_roomid;
		out << uin << m_sid << (uint16)IM_CHAT_KEEP_ALIVE << (uint16)0;
		out << seq;	

		out << m_pMyRoom->GetCurrentUserNum();
		out << BigRoomOption::instance()->m_ppcViewInfo.value;
		out << m_pMyRoom->awardStatus;

		return SendDirect(&out);;
	}

	int User::SendDirect( UdpOutPacket *out )
	{
		if (proxyIP)
		{
			uint32 old = out->SetPosition(0);
			*out << ip << port;
			out->SetPosition(old);
		}
		return RoomManager::gRoot->SendDataByChannel(m_nChannelState,out, ip, port, proxyIP, proxyPort);
	}


	void User::OnRcvAck( uint16 seq )
	{
		if(sendQueue.size())
		{
			UdpOutPacket *p = *sendQueue.begin();
			if(p->seq == seq) 
			{
				p->globalSendItem.remove();
				sendQueue.pop_front();
				delete p;
			}
			SendNextPacket(NORMAL_SENDQUEUE);
		}

		if(sendQueueEx.size())
		{
			UdpOutPacket *p = *sendQueueEx.begin();
			if(p->seq == seq) 
			{

				p->globalSendItem.remove();
				sendQueueEx.pop_front();
				delete p;
			}
			SendNextPacket(GIFT_SENDQUEUE);
		}

		
	}

	bool User::setWindow( uint16 seq )
	{
		const int SEQ_WIN_SIZE = 32;

		int d = seq - m_recvseq;
		if (d < 0 && abs(d) > SEQ_WIN_SIZE * 2)
			d = (unsigned short)d;
		if (d < 0)
			return false;

		if (d >= SEQ_WIN_SIZE) {
			do {
				++m_recvseq;
				m_window >>= 1;

				d = (unsigned short)(seq - m_recvseq);
			} while (m_window & 0x01 ||  d >= SEQ_WIN_SIZE);

			d = (unsigned short)(seq - m_recvseq);
		}

		if (!d) {
			do {
				++m_recvseq;
				m_window >>= 1;
			} while (m_window & 0x01);

			return true;
		}

		unsigned int mask = (1 << d);
		if (m_window & mask)
			return false;

		m_window |= mask;
		return true;

	}

	bool User::ResetKeepAlive()
	{
		m_keepaliveExpire = time(0) + KEY_KEEPALIVE_TIMEOUT;

		return true;

	}

	void User::OnRcvKeepAlive(UdpInPacket *in)
	{
		//LOG(1)("User::OnRcvKeepAlive %lu\n", uin);
		ResetKeepAlive();

		SendKeepAlive(in->header.seq);
		item.remove();

		

		m_pMyRoom->usersTop.add(&item);

		SendNextPacket(NORMAL_SENDQUEUE);
		SendNextPacket(GIFT_SENDQUEUE);
	}

	UdpOutPacket* User::CreatePacket_Head( bool needAck,uint32 roomid,uint32 uin,uint32 sid,uint16 cmd )
	{
		UdpOutPacket* out = NULL;
		try
		{
			out = new UdpOutPacket();
			if (out)
			{
				out->cmd = cmd;

				if(needAck)
					out->seq = ++m_seq;				//该包需要确认
				else
					out->seq = 0;					//该包不需要确认

				if (proxyIP)
					*out << ip << port << uint8(0);
				*out << m_ver << roomid;
				*out << uin << sid << cmd << out->seq;
				*out << (uint16) 0;		// Checkcode will be calculated later

				out->session = this;
			}

			return out;	
		}
		catch(...)
		{
			if(out)
				delete out;

			return NULL;
		}
	}

	UdpOutPacket* User::CreatePacket_Head( bool needAck,uint16 cmd )
	{
		UdpOutPacket* out = NULL;
		try
		{
			out = new UdpOutPacket();
			if (out)
			{		
				out->cmd = cmd;

				if(needAck)
					out->seq = ++m_seq;				//该包需要确认
				else
					out->seq = 0;					//该包不需要确认

				if (proxyIP)
					*out << ip << port << uint8(0);

				*out << m_ver << m_roomid;
				*out << uin << m_sid << cmd << out->seq;
				*out << (uint16) 0;		// Checkcode will be calculated later

				out->session = this;
			}
			return out;	
		}
		catch(...)
		{
			if(out)
				delete out;

			return NULL;
		}
	}

	UdpOutPacket* User::CreatePacket_Head( uint16 cmd )
	{
		UdpOutPacket* out = NULL;
		try
		{

			out = new UdpOutPacket();
			if (out)
			{			
				out->cmd = cmd;

				//if(m_bReliable)
				out->seq = ++m_seq;		

				if (proxyIP)
					*out << ip << port << uint8(0);
				*out << m_ver << m_roomid;
				*out << uin << m_sid << cmd << out->seq;
				*out << (uint16) 0;		// Checkcode will be calculated later

				out->session = this;
			}
			return out;	
		}
		catch(...)
		{
			if(out)
				delete out;
			return NULL;
		}
	}

	int User::SendAckPacket( uint16 seq )
	{
		UdpOutPacket out;


		out.cmd = IM_CHAT_ACK;
		out.seq = 0;
		if (proxyIP)
			out << ip << port << uint8(0);
		out << m_ver << m_roomid;
		out << uin << m_sid << (uint16)out.cmd << (uint16)out.seq;
		out << (uint16) seq;		// Checkcode will be calculated later

		int result =  SendDirect(&out);
		//delete out;

		return result;
	}

	void User::SendPacket( UdpOutPacket *out, int nSendQueueState)
	{

		if(!out) return;

		if (out->getdatalen() > _MAX_PACKET_SIZE - 128)
			LOG(1)("out of packet buffer size %d, cmd = %d\n", out->getdatalen(), out->cmd);


		if(sendQueue.size() > BigRoomOption::instance()->m_maxSendQueue)
		{
			ClearSendQueue();
			LOG(1)("out of packet count uin %u roomid %u\n", uin, m_pMyRoom->roomid);
		}

		out->attempts = 0;

		if(nSendQueueState == NORMAL_SENDQUEUE)
		{
			sendQueue.push_back(out);
		}
		else
		{
			sendQueueEx.push_back(out);
		}

		
		SendNextPacket(nSendQueueState);
		
	}

	int User::NotifyPrize( uint32 srcuin, uint32 dstuin, uint32 prize, uint32 prizeCount )
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_PRIZE);
		if(out) {
			*out << srcuin  << dstuin << prize << prizeCount;
			if (srcuin == uin)
				*out << money;

			SendPacket(out);
			return 0;
		}

		return -1;
	}

	int User::SendGlobleMsg( UdpInPacket *in )
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_GLOBLE_MSG);
		if(out)
		{
			out->writeBinary(in->GetData(), in->getdatalen());

			SendPacket(out);

			return 0;
		}

		return -1;
		
	}

	int User::SendGreatGiftMsg( UdpInPacket *in )
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_GREAT_GIFT);
		if(out)
		{
			out->writeBinary(in->GetData(), in->getdatalen());

			SendPacket(out);

			return 0;
		}

		return -1;
	}

	int User::NotifyAutoMicStatus(bool autoMic, uint32 opr)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_AUTOMIC_STATUS_CHANGE);
		if(out)
		{
			*out << autoMic << opr;

			SendPacket(out);

			return 0;
		}

		return -1;

	}

	int User::NotifyUserBet(uint32 round, uint32 srcuin, uint32 betCount, BetList &l)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ZZ_BETMSG);
		if(out) {
			if (m_ver >= IM_CHAT_VER7)
				*out << round;

			*out << srcuin << betCount;

			*out << uint8(l.size());

			for (uint8 i=0; i<l.size(); i++)
				*out << l[i].betIdx;

			SendPacket(out);

			return 0;
		}

		return -1;
	}

	int User::NotifyAwardStatus(uint32 round, uint16 cmd, uint16 delayTime)
	{
		UdpOutPacket* out = CreatePacket_Head(cmd);
		if(out) 
		{
			*out << round;
			*out << delayTime;
			SendPacket(out);

			return 0;
		}	
		return -1;
	}

	

	int User::NotifyAwardInfo(uint32 roundID, uint16 cmd, uint8 awardID)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ZZ_AWARDMSG);
		if(out) 
		{
			*out << roundID << awardID;

			SendPacket(out);

			return 0;
		}

		return 0;
	}



	int User::NotifTodayAwardInfo( uint16 *awdInfo )
	{
		
		//UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SRV_ZZ_AWARD_TODAY);
		//if(out) 
		//{
		//	*out << m_pMyRoom->awardRound;

		//	for (uint8 i=0; i<(ZZAward::STAR_DA_TIANWAN_50+1); i++, awdInfo++)
		//		*out << *awdInfo;

		//	SendPacket(out);

		//	return 0;
		//}	
		return -1;

	}

	void User::SendNextPacket(int nSendQueueState)
	{
		PACKETLIST* pSendQueue = NULL;
		if(nSendQueueState == NORMAL_SENDQUEUE)
		{
			pSendQueue = &sendQueue;
		}
		else
		{
			pSendQueue = &sendQueueEx;
		}

		if (!pSendQueue->size())
			return;

		UdpOutPacket *p = *pSendQueue->begin();

		//过超时一半时间就再次发送PACKET_SEND_KEY_TIMEOUT
		uint32 now = talk_base::TimeStamp();
		if (TIME_DIFF_U(now, p->expire) > BigRoomOption::instance()->m_packetTimeout/2)
		{
			SendThePacket(p);
		}
	}

	int User::SendThePacket( UdpOutPacket *out)
	{
		if (!out)
			return 0;

		out->expire = talk_base::TimeStamp();
		out->globalSendItem.remove();
		out->attempts++;
		if (out->attempts <= BigRoomOption::instance()->m_packetTimes) 
		{
			m_pMyRoom->globalSendQueue.add(&out->globalSendItem);
			return SendDirect(out);
		}


#ifdef WIN32
		LOG(4)("send packet up to max times cmd = %d roomid=%d  userid=%d proxy=%s userip=%s lastKeepAlive=%I64d attempts %d\n", out->cmd, m_pMyRoom->roomid, uin, NIP2CHAR(proxyIP),
			NIP2CHAR(ip), m_keepaliveExpire, out->attempts);
#else
		LOG(4)("send packet up to max times cmd = %d roomid=%d  userid=%d proxy=%s userip=%s lastKeepAlive=%ld attempts %d\n", out->cmd, m_pMyRoom->roomid, uin, NIP2CHAR(proxyIP),
			NIP2CHAR(ip), m_keepaliveExpire, out->attempts);
#endif
		if(sendQueue.size() && out == *sendQueue.begin())
		{
			sendQueue.pop_front();
			SendNextPacket(NORMAL_SENDQUEUE);
		}
		else if(sendQueueEx.size() && out == *sendQueueEx.begin())
		{
			sendQueueEx.pop_front();
			SendNextPacket(GIFT_SENDQUEUE);
		}

		out->globalSendItem.remove();
		out->sendItem.remove();
		delete out;
		return 0;
	}

	int User::NotifyPPCHistory(OutPacket& outData)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_HISTORY);
		if(!out) 
		{
			return -1;
		}	
		out->writeBinary(outData.GetData(), outData.getdatalen());
		SendPacket(out);
		return 0;
	}

	
	int User::NotifyPPCStart(uint32 roundID, uint16 delayTime, OutPacket& extData)
	{
		m_userAllBet.reinit();
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_BETSTART);
		if(!out) 
		{
			return -1;
		}	
		
		*out << roundID << delayTime;
		out->writeBinary(extData.GetData(), extData.getdatalen());
		SendPacket(out);

		return 0;
		
		//uint32 nRound,uint32 nstartTime,uint32 betTime,uint32 ncheckTime,uint32 awardingTime,uint32 awardTime,uint32 nFreeTime,uint32* areaLimit;
	}

	

	int User::NotifyBetResult(uint8 betResult, uint32 aRound)
	{
		
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_BET_RESULT);
		if(!out) 
		{
			return -1;
		}	

		*out << betResult << money << (uint32)received << aRound;
		SendPacket(out);
		return 0;
	}

	int User::NotifyBetAction(uint8 areaIndex, uint32 betMoney, uint64 maxPlaceArea, uint32 betUin, uint32 around, OutPacket& outData, uint16 betLimit)
	{

		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_BET_ACTION);
		if(!out) 
		{
			return -1;
		}	
		int nState = (betUin == uin) ? NORMAL_SENDQUEUE:GIFT_SENDQUEUE;
		*out << areaIndex << betMoney << maxPlaceArea << betUin << around;

		if(betLimit && sendQueueEx.size() > betLimit)
		{
			ClearSendQueue(sendQueueEx);
			out->writeBinary(outData.GetData(), outData.getdatalen());
			LOG(5)("uin %u SyncBetLimit\n", uin);
		}
		else
		{
			*out << uint16 (0);//协议占位数据 不可移动，增加字段在后面增加
		}
		
		
		SendPacket(out, nState);
		
		return 0;
	}

	int User::NotifyUpdateUserInfo(OutPacket& outData)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_PPC_SYNC_USERINFO);
		if(!out) 
		{
			return -1;
		}	

		out->writeBinary(outData.GetData(), outData.getdatalen());

		SendPacket(out);
		return 0;
	}

	int User::NotifyPPCAward(uint32 aRound, uint16 winItem, uint16 delayTime, OutPacket& outData)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_AWARD_ITEM);
		if(!out) 
		{
			return -1;
		}	

		*out << aRound << winItem << delayTime;
		out->writeBinary(outData.GetData(), outData.getdatalen());
		out->writeBinary(m_userAllBet.GetData(), m_userAllBet.getdatalen());
		SendPacket(out);
		ClearSendQueue(sendQueueEx);
		m_userAllBet.reinit();
		return 0;
	}

	int User::NotifyGameEndInfo(OutPacket& extData )
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_GAMEEND);
		if(!out) 
		{
			return -1;
		}	

		out->writeBinary(extData.GetData(), extData.getdatalen());
		SendPacket(out);

		return 0;
	}

	int User::NotifyPPCBankerChange(OutPacket& extData)
	{
		UdpOutPacket* out = CreatePacket_Head(IM_CHAT_SVR_PPC_BANKER_CHANGE);
		if(!out) 
		{
			return -1;
		}	

		out->writeBinary(extData.GetData(), extData.getdatalen());
		SendPacket(out);

		return 0;
	}


}
