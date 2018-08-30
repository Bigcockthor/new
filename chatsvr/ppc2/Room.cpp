
#include "ace/Reactor.h"
#include "Room.h"
#include "RoomManager.h"
#include "BigRoomServer.h"
#include "include/base64.h"
#include <algorithm>
#include "include/log.h"
#include "include/socketaddress.h"
#include "include/debug_new.h"
#include <vector>
#include "include/Markup.h"
#include "cache/cachedefine.h"
#include "include/coretime.h"
#include "im/imdefine.h"
#include "../tools/common.h"


const int countSize = 3000;

const uint64 BASE_POOL = int64(1000000) * int64(10000);

#ifdef WIN32
const size_t default_stack_size = 				0;
#else
const size_t default_stack_size	=				256 * 1024;		//�̶߳�ջ��С(k)
#endif

using namespace std;

std::string LogonRoomMsg[] = 
{
		"LOGON_SUCCESS",
		"LOGON_ROOM_FAILED",
		"LOGON_INVALID_UIN",
		"LOGON_WRONG_PASSWD",
		"LOGIN_NO_ROOM_MEMBER",
		"LOGON_ROOM_IS_BUSY",
		"LOGON_NO_THIS_ROOM",
		"LOGON_REJECT",
		"LOGON_REQ",
		"LOGON_VISITOR_ISFULL",
		"LOGON_ROOM_CLOSE",
		"LOGON_WRONG_ROOM_PASSWD",
		"LOGON_ROOM_ISFULL",	
		"LOGON_BLACKLIST_UIN",
		"LOGON_BLACKLIST_IP",
		"LOGON_FORBID_JOIN",	
		"LOGON_NO_QSMEMBER",
		"LOGON_NO_FXSMEMBER",
		"LOGON_NO_LOWERGRADEFXSMEMBER",
		"LOGON_REQUEST_DATA",
		"LOGON_REQUEST_SUCESS",
		"LOGON_ROOM_ONLY_SUBSCRIBER",
		"LOGON_ROOM_ONLY_VIP",
		"LOGON_ROOM_PAY_ERROR",
		"","","","","","","","",""
};



string ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH			= "����Ȩ�޲���";
string ChatRoomMsg::STR_MSG_ACL_IF_HIGH_VIP			= "�Է��Ǹ߻��Ա��������ܹ����˲�����";
string ChatRoomMsg::STR_MSG_NOT_ONLINE				= "�Է�������";
string ChatRoomMsg::STR_MSG_HAS_GOT_MIC				= "�Է��������";
string ChatRoomMsg::STR_MSG_NO_FREE_MIC				= "û��ʣ�����";
string ChatRoomMsg::STR_MSG_DRAG_MIC_SUCCESS			= "�ɹ����Է����Ϲ���";
string ChatRoomMsg::STR_MSG_NO_MONEY					= "����";
string ChatRoomMsg::STR_MSG_PRESENT_GIFT_FAIL		= "����ʧ��";
string ChatRoomMsg::STR_MSG_PRESENT_GIFT_SUCCESS		= "����ɹ�";
string ChatRoomMsg::STR_MSG_SEND_G_MSG_ERROR			= "����С����ʧ��";
string ChatRoomMsg::STR_MSG_SEND_G_MSG_SUCCESS		= "����С���ȳɹ�!";
string ChatRoomMsg::STR_MSG_PRIZE_MSG				= "�û� %s(%lu) ��%s(%lu)����ˢ����������Ʒ������ˢ%lu, ��� %lu �� %lu ���Ĵ󽱣��ڴ˱�ʾף�أ�";
string ChatRoomMsg::STR_MSG_SYSTEM_MSG				= "ϵͳ��Ϣ";
string ChatRoomMsg::STR_MSG_PUBLIC_TEXT_DENY			= "�������û�б�����:��ǰ�����ֹ�ǻ�Ա���ֹ��ġ�";
string ChatRoomMsg::STR_MSG_VIP_PUBLIC_TEXT_DENY		= "�������û�б�����:��ǰ�����ֹ��Ա���ֹ��ġ�";
string ChatRoomMsg::STR_MSG_PRIVATE_TEXT_DENY		= "�������û�б�����:��ǰ�����ֹ�ǻ�Ա�������Ļ���";
string ChatRoomMsg::STR_MSG_VIP_PRIVATE_TEXT_DENY	= "�������û�б�����:��ǰ�����ֹ��Ա�������Ļ���";
string ChatRoomMsg::STR_MSG_FORBID_CHAT				= "�㱻��ֹ�ڴ˷��䷢�ԣ�";
string ChatRoomMsg::STR_MSG_PRESENT_ONMIC			= "��Ϊ������ݣ�ϵͳ�������� %lu �����!";


string ChatRoomMsg::STR_MSG_CLIENT_VER_LOW			= "���Ŀͻ��˰汾���ͣ����������ػ�������";
string ChatRoomMsg::STR_MSG_AWARD_NOT_BETTING		= "����עʱ�䣬���ܹ���ע��";
string ChatRoomMsg::STR_MSG_BET_FAIL					= "��עʧ��!";
string ChatRoomMsg::STR_MSG_GAME_START				=	"[%d��]��ʼ...";
string ChatRoomMsg::STR_MSG_BET_SUCCESS				= "��ע�ɹ�!";
string ChatRoomMsg::STR_MSG_AWARD_FAIL				= "����ʧ�ܣ����ס���ֺ��벢��ͷ���ϵ��";
string ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG			= "%s(%u)��Ʒ����������������Ϸ��%d���е�%d���󽱣��ڴ˱�ʾף�أ�";
string ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG2			= "%s(%u)��Ʒ����������������Ϸ��%d���е�%lu�󽱣��ڴ˱�ʾף�أ�";
string ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG3			= "%s(%lu)��Ʒ����������������Ϸ��ׯ׬��%lu���ڴ˱�ʾף�أ�";
string ChatRoomMsg::STR_MSG_ZZ_BET_ALREADY			= "�����Ѿ���ע�����ܹ��ظ���ע��";
string ChatRoomMsg::STR_MSG_BET_FAIL_IN_GAME_FAIL	= "��עʧ��,�ʽ���������Ϸ�����������˳���Ϸ������Ѳ�����Ϸ�У������½�����Ϸ���˳�����ˢ����";
string ChatRoomMsg::STR_MSG_FILTER					= "��ֹ����վ���ӣ����򽫻ᱻϵͳ�Զ�����һ��ʱ�䣡";
string ChatRoomMsg::STR_MSG_BAKER_NOMONEY			= "������Ӳ���������ׯ�ң�����ʧ�ܣ�";
string ChatRoomMsg::STR_MSG_BANKER_RETRY			= "���Ѿ�������ׯ�ң�����Ҫ�ٴ����룡";
string ChatRoomMsg::STR_MSG_CHANGE_BAKER_NOMONEY	= "[ %s(%u) ]�Ʋ�����(%llu)��ǿ�л�ׯ!";
string ChatRoomMsg::STR_MSG_CHANGE_BAKER_NOTIMES	= "[ %s(%u) ]��ׯ�����ﵽ(%d)��ǿ�л�ׯ!";
string ChatRoomMsg::STR_MSG_TAKE_BAKER				= "��ϲ[ %s(%u) ]��ׯ!";
string ChatRoomMsg::STR_MSG_CHANGE_BANKER_ERROR		= "��Ϸ�Ѿ���ʼ��������ȡ����ׯ��";
string ChatRoomMsg::STR_MSG_NOT_CHAT				= "��Ǹ������Ϸ���䲻������������Ϣ��";
string ChatRoomMsg::STR_MSG_PROMOTED				= "";
string ChatRoomMsg::STR_MSG_BROADCAST_LINK			= "";
string ChatRoomMsg::STR_MSG_BETFAILED_CODE			= "��עʧ�ܣ�����ׯ���⸶����";
string ChatRoomMsg::STR_MSG_BETFAILED_LIMIT			= "��עʧ�ܣ����������ע����";
string ChatRoomMsg::STR_MSG_BETFAILED_INFO			= "��עʧ��";





#define GIFTID_BEGIN		1000000
#define GIFTID_END			2999999
#define MAX_USERINFO		50



namespace BigRoom
{


	Room::Room(uint32 mRoomID, RoomManager *roomMgr) : m_timertime(0), roomid(mRoomID),ppcBetMgr(JETTON_AREA_COUNT, JettonManager::m_iOddsArray, this)
	{
		awardStatus = PPC_STOP;
		curStatusStart = talk_base::TimeStamp();
		prized = 0;
        lastUpdateUserNum = 0;
		roomTax = 1;
		roomsize		= DEFAULT_ROOM_SIZE;
		maxMicQueue		= DEFAULT_MIC_QUEUE;
		maxMic			= DEFAULT_MIC_SIZE;
		textChatStatus	= TEXT_ALL;

		autoMgrForRicher= 0;
		awardRound = 1;

		
		time_t now = time(NULL);
		struct tm *tm = localtime(&now);
		tm_yday = tm->tm_yday;

		memset(currRoundAward, 0, sizeof(currRoundAward));
		memset(currRoundBet, 0, sizeof(currRoundBet));

		memset(roomName, 0, sizeof(roomName));
		memset(descript, 0, sizeof(descript));
		memset(broadcast, 0, sizeof(broadcast));
		memset(m_pass, 0, sizeof(m_pass));
		


		ppcBetMgr.SetItemTimes(JettonManager::PPC_40_TIMES, 7, 3);			//5
		ppcBetMgr.SetItemTimes(JettonManager::PPC_30_TIMES, 10, 6);			//2
		ppcBetMgr.SetItemTimes(JettonManager::PPC_20_TIMES, 10, 4);			//4
		ppcBetMgr.SetItemTimes(JettonManager::PPC_10_TIMES, 10, 4);			//3


		
	
	}



	Room::~Room(void)
	{	

	}


	int Room::open(void *)
	{
		//RoomManager::gRoot->DbhLoadZZPool(this);
		//RoomManager::gRoot->DBhLoadZZAwaredHistory(this);
		return 0;
	}



	/*
	ÿ��10m����RoomManager��һ�����Ĺ���
	*/
	int Room::OnHandleTimeout()
	{
		m_timertime = (m_timertime + 1) % ROOM_TIMER_MAX_LIMIT;


		//if (m_timertime == 0)
		//{
		//	RoomManager::gRoot->DbhLoadZZPool(this);
		//}


		if(GetCurrentUserNum() == 0 && (awardStatus == PPC_STOP||awardStatus == PPC_END))							//���û���˲������ֿ����Ѿ���ɣ���ɶ�²�����
			return 0;

		OnHandlePPC();

		if(m_timertime % ROOM_HANDLETIMEOUT_INTERVAL == 0) 
		{
			for(UinList::iterator it = logoutMap.begin(); it!=logoutMap.end(); it++)
			{
				uint32 userid = *it;
				User* pUser = GetUser(userid);
				if(pUser)
				{
					logout(pUser, true, 10000, ROOM_KICKTYPE_KICKOUT, true);
				}
			}
			logoutMap.clear();
		}


		if(m_timertime % ROOM_CHECK_KEEPALIVE_INTERVAL == 0) 
		{
			CheckKeepAlive();
		}

		//��ʱ���·�������, ������ͬ�Ͳ�����
		if (m_timertime % ROOM_UPDATE_USER_NUM_INTERVAL == 0 && GetCurrentUserNum() != lastUpdateUserNum)
		{
            lastUpdateUserNum = GetCurrentUserNum();
            RoomManager::gRoot->DBHModifyCurrUser(roomid, lastUpdateUserNum, 0);
		}

		return 0;
	}



	void Room::CheckSendQueue()
	{
		ListHead *pos, *head = &globalSendQueue;

		uint16 iSendTimes = 0;
		uint32 tempTimeout = BigRoomOption::instance()->m_packetTimeout;
		uint32 now = talk_base::TimeStamp();
		while ((pos = head->next) != head && ++iSendTimes < 1000) {
			UdpOutPacket *p = LIST_ENTRY(pos, UdpOutPacket, globalSendItem);
			if (p){
				if(TIME_DIFF_U(now, p->expire) < tempTimeout)
					break;
			}

			pos->remove();
			if(p)
			{
				((User *)(p->session))->SendThePacket(p);
			}
		}
	}



	void Room::CheckKeepAlive()
	{

		ListHead *pos, *head = &usersTop;

		while ((pos = head->next) != head) {
			User *pUser = LIST_ENTRY(pos, User, item);
			if(pUser){
				if (pUser->CheckKeepAlive() == false)
					OnKeepAliveTimeout(pUser);
				else
					break;
			}
		}
	}

	void Room::UpdateRoomCurrUser(uint16 curruser, uint16 currconfuser)
	{
		RoomManager::gRoot->DBHModifyCurrUser(roomid, curruser, currconfuser);
	}

	void Room::OnKeepAliveTimeout(User* pUser)
	{
		LOG(0)("KPTO roomid %u user %u  OnKeepAliveTimeout nState %d\n", roomid,  pUser->uin, pUser->m_nState);

		pUser->item.remove();
		if(pUser->m_nState != User::NORMAL_STATE)
		{
			pUser->Release();
			return;
		}
		logout(pUser, false, 0, 0, true);	
	}



	int Room::OnLogon(DbLogonPara * para)
	{
		int tmp_result;
		if (m_open_state == OPENSTATUS_DISABLE)
			return -1;

		User * tmp_usr=para->m_user;
		uint16 res=ValidateUser(tmp_usr);
		if(res==LOGON_SUCCESS)
		{
			tmp_result=OnRcvNewUserLogon(tmp_usr);
			if(tmp_result)
				return -1;
			else 
				return 0;
		}
		else
		{
			LOG(1)( "%d begin login room %d  fail by ValidateUser error, code = %d msg=%s\n",tmp_usr->uin,para->m_room_id,res, LogonRoomMsg[res].c_str());
			tmp_usr->OnLogonFail(this, res);
			DeleteUserFromMap(tmp_usr);
			tmp_usr->Release();
			return -1;
		}
	}


	void Room::OnReceiveCmdPacket(UdpInPacket* in)
	{
		//LOG(1)("get roompacket cmd=%d seq=%d\n", in->header.cmd, in->header.seq);

		uint16 cmd = in->header.cmd;


		if (m_openStatus == OPENSTATUS_DISABLE)
			return;

		User* pUser = NULL;
		//��½����
		if(cmd == IM_CHAT_LOGON_ROOM)
		{
			pUser = (User *)in->session;

			if (pUser)
				OnRcvLogon(in);	
			return;
		}
		//�鿴��û���û��ڷ�����
		pUser = this->GetUser(in->header.uin);


		if(pUser && pUser->m_sid == in->header.sid)
		{
			if(pUser->port != in->port || pUser->ip != in->ip)
			{
				LOG(2)("LP %u(%u) %x change from %s to %s\n", pUser->uin, in->header.uin,  (uint32)pUser, 
					talk_base::SocketAddress(ntohl(pUser->ip), ntohs(pUser->port)).ToString().c_str(),
					talk_base::SocketAddress(ntohl(in->ip), ntohs(in->port)).ToString().c_str());

				RoomManager::gRoot->RemoveUser(pUser);

				pUser->port = in->port;
				pUser->ip = in->ip;
				RoomManager::gRoot->AddUser(pUser);
			}

			if (pUser->proxyIP != in->proxyIP || pUser->proxyPort != in->proxyPort|| pUser->m_nChannelState != in->channel)
			{
				LOG(2)("LP %u(%u) %x change proxy from %s to %s change channel from %d to %d\n", pUser->uin, in->header.uin,  (uint32)pUser, 
					talk_base::SocketAddress(ntohl(pUser->proxyIP), ntohs(pUser->proxyPort)).ToString().c_str(),
					talk_base::SocketAddress(ntohl(in->proxyIP), ntohs(in->proxyPort)).ToString().c_str(), pUser->m_nChannelState, in->channel);
				pUser->proxyIP = in->proxyIP;
				pUser->proxyPort = in->proxyPort;
				pUser->m_nChannelState = in->channel;
				

			}

			if(pUser->ValidatePacket(in))
			{
				
				AUTO_PERF_NAME("USER", cmd);
					//AUTO_PERF();
				
				switch(cmd)
				{
				case IM_CHAT_PPC_BET:
					OnRecvPPCBet(in, pUser);
					break;
				case IM_CHAT_PPC_SYNC_SCENE:
					OnSyncScene(in, pUser);
					break;
				case IM_CHAT_PPC_BANKER_REQ:
					OnBakerReq(in, pUser);
					break;

				case IM_CHAT_TEXT:								//��������
					On_TextChat(in, pUser);
					break;

				case IM_CHAT_ROOM_OPEN:
					On_RcvRoomOpen(in, pUser);
					break;

				case IM_CHAT_ROOM_CLOSE:
					On_RcvRoomClose(in, pUser);
					break;

				case IM_CHAT_VISITOR:
					pUser->SendRoomUserList(this, in->header.cmd);
					break;
	

				case IM_CHAT_MODIFYPASS:
					On_RcvModifyPass(in, pUser);
					break;
				case IM_CHAT_GET_ROOMINFO:
					On_RcvUpdateRoomInfo(in, pUser);
					break;
				case IM_CHAT_LOGOUT_ROOM:
					this->OnRcvLogout(in, pUser);			
					break;

				case IM_CHAT_GLOBLE_MSG:
					On_RcvGlobleMsg(in, pUser);
					break;
				case IM_CHAT_KICKOUT:
					On_RcvKickOut(in, pUser);
					break;
				case IM_CHAT_FORBID_CHAT:
					OnRecvForbidChat(in, pUser);
					break;
				case IM_CHAT_PPC_GAMELIMIT:
					On_RcvAddGameLimit(in, pUser);
					break;

				default:
					break;
				}
			}
		}
	}


	void Room::Dispose()
	{


	}


	int Room::AddUser(User *user)
	{
		if (roomid == 0)
			return -1;

		if (m_UserManager.GetUser(user->uin))
			return -1;

		int ret = m_UserManager.AddUser(user, user->uin);

		if (ret == 0)
		{
			PushUser(user);
		}

		return ret;
	}


	inline int Room::DeleteUserFromMap(User* pUser)
	{
		RoomManager::gRoot->RemoveUser(pUser);

		pUser->item.remove();

		if (GetUser(pUser->uin) == pUser)
			return m_UserManager.RemoveUser(pUser->uin);

		return 0;
	}

	void Room::RemoveAllUsers()
	{
		m_UserManager.RemoveAllUsers();
	}

	uint16 Room::GetCurrentUserNum()
	{
		return m_UserManager.GetUserCount();
	}



	uint8 Room::IsSuperMgr(uint32 uin)	// SuperManInfo** pInfo)
	{
		return RoomManager::gRoot->IsSuperMgr(uin);	//(uin, pInfo);
	}


	User* Room::GetUser(uint32 uin)
	{
		return m_UserManager.GetUser(uin);
	}


	/************************************************************
	*															*
	*					general room operate					*
	************************************************************/

	void Room::clearOldUser(User* newUser, User* oldUser)
	{
		LOG(1)("room %lu, clear old %lu\n", GetRoomID(), oldUser->uin);
		logout(oldUser, false, 0, 0, false,true);
	}

	//called when receive IM_CHAT_LOGON_ROOM packet
	int Room::OnRcvNewUserLogon(User *s)
	{
		User* pUser = NULL;
		uint32 uin = s->uin;
		pUser = this->GetUser(uin);
		OutPacket out;	

		if(pUser && pUser != s)
		{
			//whether is the same use or not
			if(pUser->m_sid == s->m_sid && pUser->port == s->port && pUser->ip == s->ip)
			{
				LOG(1)( "%d begin login room %d  ok but is duplicate packet\n", s->uin, GetRoomID());
				DeleteUserFromMap(pUser);
				s->Release();
				return -1;
			}
			else	//���򣬱���������û�
			{
				if(pUser->userMac != s->userMac)//ͬһmac��˵��������ip���ˣ����������
				{
					if(pUser->userMac != s->userMac)
					{
						pUser->m_nState = User::FOURCE_OFLINE;
						pUser->NotifyForceOffline(s->m_roomid, s->ip, s->port, s->chatUserType);
					}
				}
				clearOldUser(s, pUser);
			}
		}
		//���¿�ʼs�ĵ�¼��
		pUser = s;

		if(this->AddUser(pUser) != 0)
		{
			LOG(1)( "%d begin login room %d  fail by add user error\n", pUser->uin, GetRoomID());

			pUser->OnLogonFail(this, LOGON_ROOM_FAILED);
			last_logon_failing_IP = pUser->ip;
			last_logon_failing_time = time(NULL);	//ACE_OS::time();
			DeleteUserFromMap(pUser);
			pUser->Release();
			return -1;
		}

		//user logon success
		if(pUser->OnLogon(this) == -1)
		{
			LOG(1)( "%d begin login room %d  fail by OnLogon error\n", pUser->uin, GetRoomID());
			goto LOGINFAIL;
		}

		//UpdateRoomUserTime(uin, pUser->starttime, pUser->ip, 1);
		NotifyOnline(pUser);

		ProcessPPCScene(pUser);

		//��ʷ�н���Ϣ����
		BuildPPCHistory(out);
		pUser->NotifyPPCHistory(out);

		//������ʱ�˳���
		{
			UinList::iterator it = find(logoutMap.begin(),logoutMap.end(),pUser->uin);
			if (it != logoutMap.end())
			{
				logoutMap.erase(it);
			}
		}

		return 0;

LOGINFAIL:


		pUser->OnLogonFail(this, LOGON_ROOM_FAILED);
		last_logon_failing_IP = pUser->ip;
		last_logon_failing_time = time(NULL);	
		DeleteUserFromMap(pUser);
		pUser->Release();

		return -1;
	}


	void Room::OnRcvLogon(UdpInPacket* in)
	{
		User *pUser = (User *)in->session;

		//��У�鷿�俪��״̬,������Ҫ����
		uint16 res = 0;
		res = ValidateUser(pUser);

		if(res == LOGON_SUCCESS)
			OnRcvNewUserLogon(pUser);
		else
		{
			LOG(1)( "%d begin login room %d  fail by ValidateUser error, code = %d msg=%s\n", in->header.uin, 
				in->header.reserved,  res, LogonRoomMsg[res].c_str());

			pUser->OnLogonFail(this, res);
			DeleteUserFromMap(pUser);
			pUser->Release();
		}
	}

	void Room::OnRcvLogout(UdpInPacket* in, User* pUser)
	{
		logout(pUser, false, 0, 0, true);
	}

	void Room::shutdownUser(User* pUser) 
	{
		DeleteUserFromMap(pUser);
		pUser->Release();
	}

	void Room::RemoveGameInfo(uint32 uin)
	{
		UserGameMapIter iter = m_userBetList.find(uin);
		if(iter != m_userBetList.end())
		{
			m_userBetList.erase(iter);
		}

		iter = m_userAwardList.find(uin);
		if(iter != m_userAwardList.end())
		{
			m_userAwardList.erase(iter);
		}
			
	}

	//ͬһ�����ﺯ���������ߴ���,Ϊ�������ܣ�ֻ֪ͨ���ߣ���֪ͨ�����������
	void Room::logout(User* pUser, bool kickOrPush , uint32 srcuin , uint8 actionType, uint8 unLock,bool oldSession)
	{

		time_t now = time(NULL);
#ifdef WIN32
		LOG(0)("LO room %u, logout %u  ver%d  ip %s:%d proxy %s:%d mac=%s start %s end %s keep %I64d\n", GetRoomID(), pUser->uin, pUser->m_ver, NIP2CHAR(pUser->ip), ntohs(pUser->port), 
			NIP2CHAR(pUser->proxyIP), ntohs(pUser->proxyPort), CoreSocket::TransMacAddr(pUser->userMac).c_str(), GetDateOfString(pUser->starttime).c_str(), GetDateOfString(now).c_str(), now - pUser->starttime);

#else

		LOG(0)("LO room %u, logout %u  ver%d  ip %s:%d proxy %s:%d mac=%s start %s end %s keep %lu\n", GetRoomID(), pUser->uin, pUser->m_ver, NIP2CHAR(pUser->ip), ntohs(pUser->port), 
			NIP2CHAR(pUser->proxyIP), ntohs(pUser->proxyPort), CoreSocket::TransMacAddr(pUser->userMac).c_str(), GetDateOfString(pUser->starttime).c_str(), GetDateOfString(now).c_str(), now - pUser->starttime);
#endif

		//	������û��Ĳ���ֵ
		uint32 uin = pUser->uin;


		//UpdateRoomUserTime(uin, pUser->starttime, pUser->ip, 2);


		int ret = ppcBetMgr.RemoveBankerWait(pUser->uin);
		if (ret == 0)
		{
			NotifyChangeBanker(pUser->uin,JettonManager::PPC_LEAVE_BANKER,"");
		}
		RemoveGameInfo(pUser->uin);

		if (!kickOrPush)
			NotifyOffline(pUser->uin);
		else
			NotifyKickOut(pUser->uin, srcuin, actionType);

		if(BigRoomOption::instance()->m_bkafkaLog)
		{
			RoomManager::gRoot->m_kafkalog.AddLoginOut(roomid, pUser->uin, pUser->m_ver, NIP2CHAREX(pUser->ip), ntohs(pUser->port),
				NIP2CHAREX(pUser->proxyIP), ntohs(pUser->proxyPort), CoreSocket::TransMacAddr(pUser->userMac).c_str(), pUser->starttime, now,awardRound);
		}

		DeleteUserFromMap(pUser);
		
		if(pUser->m_nState == User::FOURCE_OFLINE)
		{
			RoomManager::gRoot->RemoveUser(pUser);
			pUser->ClearSendQueue();
		}
		else
		{
			pUser->Release();	
			
		}

		if(/*unLock &&*/ ppcBetMgr.GetBankerInfo().uin != uin && !oldSession)
		{
			RoomManager::gRoot->DBHLockMoney(roomid, uin, 0);
		}
		
		

	}


	


	void Room::On_RcvRoomOpen(UdpInPacket* in, User* pUser)
	{
		if(pUser->rank < USER_RANK_ROOMMAN)
		{
			pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_NO_PRIVILEGE);
			return;		
		}

		if(this->m_openStatus == OPENSTATUS_OPEN)
		{
			pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_HAS_OPEN);
			return;
		}

		m_openStatus = OPENSTATUS_OPEN;
		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);


		NotifyRoomOpen(pUser->uin);
		RoomManager::gRoot->DBHSetOpenStatus(roomid, m_openStatus);
	}

	void Room::On_RcvRoomClose(UdpInPacket* in, User* pUser)
	{
		if(pUser->rank < USER_RANK_ROOMMAN) {
			pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_NO_PRIVILEGE);
			return;		
		}

		if(this->m_openStatus == OPENSTATUS_CLOSE) {
			pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_HAS_CLOSE);
			return;
		}
		m_openStatus = OPENSTATUS_CLOSE;
		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
		NotifyRoomClose(pUser->uin);
		RoomManager::gRoot->DBHSetOpenStatus(roomid, m_openStatus);
	}


	

	void Room::On_RcvUpdateRoomInfo(UdpInPacket* in, User* pUser)
	{
		pUser->SendRoomInfo(this);		//�Ѿ�������auth��Ϣ
	}

	

	void Room::On_RcvModifyPass(UdpInPacket* in, User* pUser)
	{	
		if(pUser->rank < USER_RANK_ROOMMAN) return;

		ICQ_STR oldpass, newpass;

		*in >> oldpass >> newpass;

		//����Ա����ֱ���޸�
		if(newpass.len > MAX_FLCFPASS_LEN)
			return;

		//m_pass = newpass.text
		memcpy(m_pass, newpass.text, newpass.len);

		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
		RoomManager::gRoot->DBHModifyPass(roomid, m_pass);
	}
	/************************************************************
	*															*
	*						chat data    						*
	************************************************************/





	uint16 Room::ValidateUser(User* pUser)
	{
		if(!pUser){
			LOG(4)("Room::ValidateUser fail! [if(!pUser)]\n");
			return LOGON_INVALID_UIN;
		}

		uint32 uin = pUser->uin;

		if(IsSuperMgr(uin))
			return LOGON_SUCCESS;
		if(pUser->RankIsSuperMan())	{
			return LOGON_SUCCESS;
		}
		if(pUser->RankIsRoomOwner()) {
			return LOGON_SUCCESS;
		}
		if((pUser->RankIsManager())) {
			return LOGON_SUCCESS;
		}

		if(roomsize <= GetCurrentUserNum())
		{
			//���������ǻ�Ա����ű�����Ƿǻ�Ա��ֱ�ӷ��ط�������
			if (!pUser->levelInfo.level && !pUser->levelInfo.lordLevel && !pUser->richOrder)
				return LOGON_VISITOR_ISFULL;

			User *pushOut = GetPushOutTarget();
			if (pushOut && pushOut != pUser)
			{
				//�򱻼��û���������Ϣ
				pushOut->NotifyKickOut(pushOut->uin, pUser->uin, ROOM_KICKTYPE_PUSHOUT);

				//����session��֪ͨ�����û�
				logout(pushOut, true, pUser->uin, ROOM_KICKTYPE_PUSHOUT, true);
			}
			else
				return LOGON_ROOM_ISFULL;
		}



		if(!ValidateRoomPass(pUser->m_roomPasswd.c_str()))
			return LOGON_WRONG_ROOM_PASSWD;

		if(m_openStatus == OPENSTATUS_CLOSE)
			return LOGON_ROOM_CLOSE;

		if(auth > 0) 
		{
			//else if (auth == ROOM_AUTH_ALLOW_VIP)
			//{
			//	if (!(pUser->rank & USER_FLAG_ROOM_VIP))

			//		return LOGON_ROOM_ONLY_VIP;
			//}
		}

		return LOGON_SUCCESS;
	}


	bool Room::ValidateRoomPass(const char* pass)
	{
		if(strcmp(this->m_pass, pass))
			return false;

		return true;
	}



	int Room::NotifyOnline(User *pNewUser)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyOnline,pNewUser);

		return 0;
	}


	int Room::NotifyRoomOpen(uint32 uin)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyRoomOpen,uin);

		return 0;
	}

	int Room::NotifyRoomClose(uint32 uin)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyRoomClose,uin);

		return 0;
	}





	int Room::NotifyOffline(uint32 dstuin)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator, entry, User, NotifyOffline, dstuin);

		return 0;
	}
	//
	//int Room::NotifyStatusChange(User *pNewUser)
	//{
	//	UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
	//	UserMap::ENTRY *entry = 0;
	//	IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyStatusChange,pNewUser);
	//
	//	return 0;
	//}




	int Room::NotifyModifyInfo()
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,SendRoomInfo,this);

		return 0;
	}


	int Room::NotifyKickOut(uint32 uin, uint32 srcuin, uint8 actionType)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM3(iterator,entry,User,NotifyKickOut, uin, srcuin, actionType);

		return 0;
	}



	

	string keys[] = {"Bold=", "Italic=", "Underline=", "FontColor=", "FontSize=", "FontName=", "SendUIN=", "ReceiveUIN=", "IsStealth=", "Action=&", "FMT_END#>"};

	string GetValue(char *&pos, string key)
	{
		char *dst = strstr(pos, key.c_str());
		if (dst)
		{
			if (key == keys[10])
				return dst + key.length();

			char *newp = strchr(dst + key.length(), ' ');
			if (!newp)
				newp = strchr(dst + key.length(), '&');
			if (newp && newp - (dst + key.length()) < 10)
			{
				*newp = 0;
				pos = newp + 1;

				return (dst + key.length());
			}
		}

		return "";
	}


	
	const string xmlkeys[] = {"Bold", "Italic", "Underline", "FontColor", "FontSize=", "FontName", "from", "to", "IsStealth", "Action"};

	void mytolower(char *str)
	{
		int i=0;
		char c;
		while (str[i])
		{
			c = str[i];
			str[i] = tolower(c);
			i++;
		}
	}

	void Room::On_TextChat(UdpInPacket* in, User* pSrcUser)
	{
		if (!pSrcUser)
			return;

		if (pSrcUser->forbidChat)
		{
			pSrcUser->sendNtyMsg(ChatRoomMsg::STR_MSG_FORBID_CHAT.c_str());

			return;
		}

		ICQ_STR textD;
		uint32 srcUin,destUin;
		uint8  ispublic;
		srcUin = in->header.uin;
		uint8 msgtype;
		*in >> msgtype >> destUin >> ispublic >> textD;


		clock_t start = clock();

		LOG(0)("LC room(%u) src(%u) dst(%u) msgtype(%d), public(%u), %s\n", roomid, srcUin, destUin, msgtype, ispublic,  textD.text);
		char buf[2048] = {0};
		strncpy(buf, textD.text, sizeof(buf)-1);
		mytolower(buf);

		if (CheckChatText(pSrcUser, buf))
		{
			LOG(0)("LF pid=%d room(%u) src(%u) dst(%u) msgtype(%d), public(%u), %s\n", BigRoomOption::instance()->partnerid, roomid,
				srcUin, destUin, msgtype, ispublic,  buf);

			return;
		}



		LOG(4)("check lc spand %ld\n", clock() - start);



		if(textD.len > MAX_CHATTEXT_LEN) return;
		if(ispublic == 0 && destUin == 0) return;

		time_t curtime = time(NULL);

		if(!pSrcUser->userAcl.actPublicChat)
		{
			pSrcUser->sendNtyMsg(ChatRoomMsg::STR_MSG_NOT_CHAT.c_str());
			return;
		}
		


		if(ispublic == 0)			//private chat	
		{
			User* pUser = this->GetUser(destUin);
			if(pUser)
			{
				if(msgtype == 0 || msgtype == 4) 
					pUser->SendTextData(srcUin,destUin,ispublic,curtime, textD.text, msgtype);

			}
		}
		else		//public chat
		{

			if(msgtype == 0 || msgtype == 4) 
			{
				UserMap::ITERATOR iterator = m_UserManager.m_UserMap.begin();
				UserMap::ENTRY* entry = 0;

				IMCHAT_SEND_TEXT(iterator, entry, User, SendTextData, srcUin,destUin,ispublic,curtime,
					textD.text, msgtype);
			}
			else if(msgtype == 2){

			}
		}



		pSrcUser->m_lastText = curtime;
		char *chatT = strchr((char *)textD.text, '>');
		if(BigRoomOption::instance()->m_bkafkaLog &&chatT)
		{
			RoomManager::gRoot->m_kafkalog.AddChatText(roomid, srcUin, destUin, msgtype, chatT,awardRound);
		}
	}




	void Room::AppendRoomInfo(UdpOutPacket *out, int m_localnet, User *pUser)
	{
		if (!out) return;

		*out << roomName;
		*out << ownuin;
		*out << descript << broadcast;
		*out << ispublic << auth;
		*out << maxMic << maxMicQueue << roomsize;
		*out << m_openStatus;
	
	}

	User *Room::GetPushOutTarget( void )
	{

		ListHead *pos, *head = &usersTop;

		LIST_FOR_EACH(pos, head) 
		{
			User *pUser = LIST_ENTRY(pos, User, item);

			if (!pUser->levelInfo.level && !pUser->levelInfo.lordLevel && !pUser->richOrder && pUser->rank < USER_RANK_ROOMMAN)				//�ǻ�Ա���Է����������Ȩ�޵��û��ɱ�������
			{
				return pUser;			
			}

		}

		return 0;
	}

	void Room::On_RcvKickOut( UdpInPacket* in, User* pUser )
	{
		uint32 dst = 0;
		uint8 acctionType;
		uint32 nBlockTime = 0;
		string strMsg;
		string rankName;

		*in >> dst >> acctionType >> nBlockTime >> strMsg;
		LOG(1)("kickout roomid %u srcuin %u dstuin %u nBlockTime %u actionType %d \n", roomid, pUser->uin, dst, nBlockTime, acctionType);	
		if (!pUser->userAcl.actKickOut)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
			return;
		}

		User* pDstUser = GetUser(dst);
		if(!pDstUser)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_NOT_ONLINE.c_str());
			return;
		}
		
		if (RoomManager::gRoot->aclCtrlsKickOut.Check(pUser->levelInfo.level,pUser->g_userType,pUser->levelInfo.lordLevel,pUser->GetRank(),pUser->uin == ownuin,pUser->richOrder,
			pDstUser->levelInfo.level,pDstUser->g_userType,pDstUser->levelInfo.lordLevel,pDstUser->GetRank(),pDstUser->uin == ownuin,pDstUser->richOrder,rankName) == false)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
			return;
		}

		string strReason; 
		if (!pUser->userAcl.actKickOut)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
			return;
		}


		if(acctionType)
		{
			RoomManager::gRoot->DBHAddBlackUin(roomid, pUser->uin,  dst, 0, pDstUser->userMac ? CoreSocket::TransMacAddr(pDstUser->userMac).c_str(): "", pDstUser->userNick);
		}

		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
		pDstUser->NotifyKickOut(dst, pUser->uin, ROOM_KICKTYPE_KICKOUT);
		logout(pDstUser, true, pUser->uin, ROOM_KICKTYPE_KICKOUT, true);
	}

	void Room::On_RcvAddGameLimit(UdpInPacket* in, User* pUser)
	{
		uint32 dst = 0;
		uint8 actionType;
		string rankName;

		*in >> dst >> actionType;
		LOG(1)("GameLimit roomid %u srcuin %u dstuin %u actionType %d \n", roomid, pUser->uin, dst, actionType);
		if(!pUser->userAcl.actPidBlock)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
			return;
		}

		User* pDstUser = GetUser(dst);
		if(!pDstUser)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_NOT_ONLINE.c_str());
			return;
		}else
		{
			if(pDstUser->isGameLimit == 1)
			{
				pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
				return;
			}
		}


		if(actionType)
		{
			RoomManager::gRoot->DBHAddGameLimit(roomid, pUser->uin, dst);
		}
		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
	}

	void Room::OnReloadRoomInfo(RoomInfo &info)
	{

		auth			= info.auth;
		ownuin			= info.ownuin;
		ispublic		= info.ispublic;
		textChatStatus	= info.chatStatus;
		roomsize		= info.roomsize;
		autoMgrForRicher= info.autoMgrForRicher;
		




		if (m_pass != info.password.c_str())
		{
			strncpy(m_pass, info.password.c_str(), sizeof(m_pass)-1);

			LOG(4)("room %lu  change pass to %s\n", roomid, info.password.c_str());
		}


		if (textChatStatus != info.chatStatus || roomName != info.roomName.c_str() || descript != info.descript)
		{
			textChatStatus = info.chatStatus;

			strncpy(roomName, info.roomName.c_str(), sizeof(roomName)-1);
			strncpy(descript, info.descript.c_str(), sizeof(descript)-1);


			ChangeStatus();

			NotifyModifyInfo();
		}

		//����򿪹رմ���
		if(m_openStatus != info.openstatus) 
		{
			m_openStatus = info.openstatus;
			if(m_openStatus == OPENSTATUS_OPEN)
				NotifyRoomOpen(ownuin);
			else
				NotifyRoomClose(ownuin);
		}



		if (broadcast != info.broadcast)
		{

			strncpy(broadcast, info.broadcast.c_str(), sizeof(broadcast)-1);

			LOG(4)("change roominfo %lu, broadcast = %s\n", roomid, broadcast);
			if (info.broadcast != "")
				NotifyModifyBroadCast();
		}
		
		for (UinMap::iterator it=roomMgr.begin(); it != roomMgr.end(); it++)
		{
			uint32 dst =  it->first;
			if (info.roomMgr.find(dst) == info.roomMgr.end())	//�ɹ���ɾ��,�����Ӧ�û�Ȩ��
			{
				User *dstUsr = GetUser(dst);
				if (dstUsr)
				{
					dstUsr->rank = USER_RANK_VISITOR;
				}

				//NotifyDelManager(dst);
			}
		}

		for (UinMap::iterator it=info.roomMgr.begin(); it != info.roomMgr.end(); it++)
		{
			uint32 dst =  it->first;
			if (roomMgr.find(dst) == roomMgr.end())				//�¼ӹ���,������ӦȨ��
			{
				User *dstUsr = GetUser(dst);
				if (dstUsr)
				{
					dstUsr->rank |= USER_RANK_ROOMMAN;
				}

				//NotifyAddManager(dst);
			}
		}

		roomMgr = info.roomMgr;									//���ͬ��

	}



	/*֪ͨ������ĳ���ˣ����淢���˱仯*/
	int Room::NotifyModifyBroadCast()
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator, entry, User, SendRoomBroadCast, this);

		return 0;
	}

	void Room::DelRoomManager( uint32 uin )
	{
		UinMap::iterator it = roomMgr.find(uin);
		if (it != roomMgr.end())
		{
			roomMgr.erase(it);
		}
	}

	void Room::AddRoomManager( uint32 dstuin, string dstNick )
	{
		roomMgr[dstuin] = 1;
	}

	void Room::On_RcvGlobleMsg( UdpInPacket* in, User* pUser )
	{
		UdpInPacket *tempPack = new UdpInPacket;
		if (tempPack)
		{
			tempPack->setdata(in->getcursor(), in->getRemain());
			if (pUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF || pUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES || pUser->RankIsSuperMan())
			{
				RoomManager::gRoot->SendGlobleMsg(tempPack, true);
				delete tempPack;
			}
			else 
				RoomManager::gRoot->DBHBuyGlobleMsgServcie(this, pUser->uin, pUser->levelInfo.level, tempPack);		
		}
	}


	void Room::OnReceiveGlobleMsg( UdpInPacket* in )
	{
		if (!in)
			return;

		//֪ͨ������ĳĳ��ĳĳ����������
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User, SendGlobleMsg, in);
	}

	void Room::ChangeStatus()
	{
	}

	void Room::OnReceiveGreatGiftMsg( UdpInPacket* in )
	{
		if (!in)
			return;

		//֪ͨ������ĳĳ��ĳĳ����������
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User, SendGreatGiftMsg, in);
	}

	void Room::SetRoomInfoDB(const dataport::RoomInfo & info)
	{
		UpdateRoomLink();
		ownuin			= info.ownuin;
		roomTax			= info.roomtax;
		memset(roomName,0,sizeof(roomName));
		strncpy(roomName, info.roomname,sizeof(roomName)-1);

		ispublic		= info.ispublic;
		auth			= info.auth;
		m_openStatus	= info.openstatus;
		memset(broadcast,0,sizeof(broadcast));
		strncpy(broadcast, info.broadcast,sizeof(broadcast)-1);

		textChatStatus	= info.chatstatus;
		awardRound      = info.awardRound;
		LOG(1)("SetRoomInfoDB roomid %u around %d \n", roomid, awardRound);
		roomsize		= info.roomsize;
		maxMic			= info.maxmic;
		maxMicQueue		= info.maxmicqueue;

		autoMgrForRicher= info.autoMgrForRicher;
		ownuin=info.ownuin;
		roomTax=(uint8)info.roomtax;
		auth=info.auth;
		m_open_state=info.openstatus;
	
		textChatStatus=info.chatstatus;
		roomsize=info.roomsize;
		ispublic=info.ispublic;
		maxMic=info.maxmic;
		maxMicQueue=info.maxmicqueue;
		

		ppcBetMgr.UpdateOption(BigRoomOption::instance()->m_ppcOption);

		if(!this->roomMgr.empty())
			this->roomMgr.clear();
		for (uint32 i=0;i<DATAPORT_MAX_ROOMMGR;i++)
		{
			this->roomMgr.insert(map<uint32,uint8>::value_type((uint32)(info.roomMgr[i]),(uint8)1));
		}

		RoomManager::gRoot->DBHLoadPPCHistory(roomid);
	}

	//���ķ�����Ϣ
	void Room::UpdateRoomInfoDB(const dataport::RoomInfo & room_info)
	{
		auth			= room_info.auth;
		ownuin			= room_info.ownuin;
		ispublic		= room_info.ispublic;
		textChatStatus	= room_info.chatstatus;
		roomsize		= room_info.roomsize;
		maxMic			= room_info.maxmic;

		roomTax			= 1;


		LOG(1)("Reload room information:%d\n", roomid);


		autoMgrForRicher= room_info.autoMgrForRicher;

		//����򿪹رմ���
		if(m_open_state != room_info.openstatus) 
		{
			m_open_state = room_info.openstatus;
			if(m_open_state == OPENSTATUS_OPEN)
				NotifyRoomOpen(ownuin);
			else
				NotifyRoomClose(ownuin);
		}


		size_t len1=strlen(room_info.passwd);
		size_t len2=strlen(m_pass);
		size_t len=len1>len2?len2:len1;
		bool pwd_equ=(len1==len2)?(strncmp(m_pass,room_info.passwd,len1)==0):false;
		if (!pwd_equ)
		{
			memset(m_pass,0,strlen(m_pass));
			strncpy(m_pass, room_info.passwd,len);
			LOG(4)("Password of room %u has been changed to %s\n", roomid,m_pass);
		}

		//�ȽϷ�������
		len1=strlen(roomName);
		len2=strlen(room_info.roomname);
		bool name_equ=(len1==len2)?(strncmp(roomName,room_info.roomname,len1)==0):false;

		//�ȽϷ�������
		len1=strlen(descript);
		len2=strlen(room_info.descript);
		bool des_equ=(len1==len2)?(strncmp(descript,room_info.descript,len1)==0):false;
		if (textChatStatus != room_info.chatstatus || !name_equ || !des_equ)
		{
			textChatStatus = room_info.chatstatus;
			//���·�������
			memset(roomName,0,sizeof(roomName));
			strncpy(roomName, room_info.roomname,sizeof(roomName)-1);

			//��������
			memset(descript,0,sizeof(descript));
			strncpy(descript, room_info.descript,sizeof(descript)-1);

			ChangeStatus();
			NotifyModifyInfo();
		}

		//����򿪹رմ���
		if(m_open_state != room_info.openstatus) 
		{
			m_open_state = room_info.openstatus;
			if(m_open_state == OPENSTATUS_OPEN)
				NotifyRoomOpen(ownuin);
			else
				NotifyRoomClose(ownuin);
		}

		len1=strlen(broadcast);
		len2=strlen(room_info.broadcast);
		len=len1>len2?len1:len2;
		bool bro_equ=(len1==len2)?(strncmp(broadcast,room_info.broadcast,len1)==0):false;
		if (!bro_equ)
		{
			memset(broadcast,0,sizeof(broadcast));
			strncpy(broadcast, room_info.broadcast,sizeof(broadcast)-1);

			LOG(4)("change roominfo %lu, broadcast = %s\n", roomid, broadcast);
			if (strlen(room_info.broadcast)!=0)
				NotifyModifyBroadCast();
		}

		//���»�õĹ���Ա�б��������
		std::vector<unsigned int> v_manager(room_info.roomMgr,room_info.roomMgr+DATAPORT_MAX_ROOMMGR);
		uint32 manager_id;
		for (UinMap::iterator it=roomMgr.begin(); it != roomMgr.end(); it++)
		{
			manager_id =  it->first;
			std::vector<unsigned int>::iterator fit=std::find(v_manager.begin(),v_manager.end(),manager_id);
			if (fit == v_manager.end())	//�ɹ���ɾ��,�����Ӧ�û�Ȩ��
			{
				User *dstUsr = GetUser(manager_id);
				if (dstUsr)
				{
					dstUsr->rank = USER_RANK_VISITOR;
				}
				//NotifyDelManager(dst);
			}
		}

		for (std::vector<unsigned int>::iterator tmp_it=v_manager.begin();tmp_it!= v_manager.end();tmp_it++)
		{
			manager_id=*tmp_it;
			if (roomMgr.find(manager_id) == roomMgr.end())//�¼ӹ���,������ӦȨ��
			{
				User *dstUsr = GetUser(manager_id);
				if (dstUsr)
				{
					dstUsr->rank |= USER_RANK_ROOMMAN;
				}
				//NotifyAddManager(dst);
			}
		}

		roomMgr.clear();
		for (std::vector<unsigned int>::iterator tmp_it=v_manager.begin();tmp_it!= v_manager.end();tmp_it++)
		{
			manager_id=*tmp_it;
			roomMgr.insert(UinMap::value_type((uint32)manager_id,(uint8)1));
		}
		
	}





	void Room::OnRecvForbidChat( UdpInPacket* in, User* pUser )
	{
		uint32 dst;

		*in >> dst;
				
		User *pDstUser = GetUser(dst);
		if(!pDstUser) {
			pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_OPP_NOT_IN);
			return;
		}
			
		if (!RoomManager::gRoot->IsSuperMgr(pUser->uin))
		{
			//����Ȩ�����ϲ��ܹ��в���, ���ҹ���Ȩ��С�ڶԷ�����Ȩ����
			if (pUser->rank < USER_RANK_ROOMMAN || pUser->rank < pDstUser->rank)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
				return;	
			}

			//�ͷ�����˾���۲��ܹ�T
			if (pDstUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF || pDstUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
				return;	
			}

			if (
				(
				pDstUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES							//��Ȩֻ�пͷ��ܹ�T,��ֹ��Ȩ��T
				|| pDstUser->uin == ownuin													//����ֻ�пͷ����ԣ�
				|| (pDstUser->richOrder && pDstUser->richOrder <= 10)						//���ֻ�пͷ����ԣ�
				)  
				&& !(pUser->g_userType & CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF)
				)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_NOT_ENOUGH.c_str());
				return;	
			}

			//��ͨ�����ܹ�T�߻��ͬ����Ĺ���,�����Ҫ���ԣ�
			if (pUser->rank < USER_RANK_ROOMOWNER && pUser->richOrder == 0 && (pDstUser->levelInfo.level >= VipLevel::HIGHER_VIP || pDstUser->rank >= USER_RANK_ROOMMAN))
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_ACL_IF_HIGH_VIP.c_str());

				return;				
			}
		}

		pDstUser->forbidChat = 1;

		RoomManager::gRoot->DBHForbidChat(roomid, pUser->uin,  dst, pDstUser?pDstUser->userNick:"");

		pUser->SendCmdResult(in->header.cmd, IM_SVR_MSG_SUCCESS);
	}

	
	void Room::OnRecvPPCBet( UdpInPacket* in, User* pUser )
	{
		if (awardStatus != PPC_BETTING)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_AWARD_NOT_BETTING.c_str());
			if (BigRoomOption::instance()->m_bkafkaLog)
			{
				RoomManager::gRoot->m_kafkalog.AddPPCBet(roomid,pUser->uin,pUser->userNick,awardRound, 0, 0,-1);
			}
			return;
		}

		
		uint8	areaIndex;
		uint32	betMoney;
		uint32  tempAround;
		*in >> areaIndex >> betMoney >> tempAround;
		LOG(1)("OnRecvPPCBet roomid %u uin %u aRound %u %u betMoney %u areaIndex %d\n", roomid, pUser->uin, awardRound, tempAround, betMoney, areaIndex);
		if(awardRound != tempAround)
		{
			LOG(1)("OnRecvPPCBet roomid %u uin %u around %u %u", roomid, pUser->uin, awardRound, tempAround);
			//return;
		}

		//�ж�user�Ƿ���ׯ��
		if(pUser->uin == ppcBetMgr.GetBankerInfo().uin)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BETFAILED_INFO.c_str());
			return;
		}
		////�ж���ע�����Ƿ���ȷ
		//JettonVector::iterator it =BigRoomOption::instance()->m_ppcOption.m_jettonList.begin();
		//bool inJettonList	= false;
		//for(; it != BigRoomOption::instance()->m_ppcOption.m_jettonList.end(); it++)
		//{
		//	if(betMoney == *it)
		//	{
		//		inJettonList = true;
		//	}

		//}
		//if(!inJettonList)
		//{
		//	pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BET_FAIL.c_str());
		//	return;
		//}

		if(pUser->money < betMoney)
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_NO_MONEY.c_str());
			if(BigRoomOption::instance()->m_bkafkaLog)
			{
				RoomManager::gRoot->m_kafkalog.AddPPCBet(roomid,pUser->uin,pUser->userNick,awardRound, 0, 0,-3);
			}
			return ;
		}
		
		int nRet = ppcBetMgr.AddJetton(pUser, areaIndex, betMoney);
		if(nRet > 0)
		{
			uint64 nMaxPlaceArea = ppcBetMgr.GetItemJettonLastLimit(areaIndex);
#ifdef WIN32
			LOG(1)("chair %u, area %d count %u iMaxArea %I64d\n", pUser->uin, areaIndex, betMoney, nMaxPlaceArea);
#else
			LOG(1)("chair %u, area %d count %u iMaxArea %llu\n", pUser->uin, areaIndex, betMoney, nMaxPlaceArea);
#endif
			
			NotifyBetAction(areaIndex, betMoney, nMaxPlaceArea, in->header.uin, awardRound);
			pUser->unBetCount = 0;//���û�����ûѺע������0
			if (BigRoomOption::instance()->m_confusionOpen)
			{
				AddMacUserBet(pUser->userMac,pUser->uin);
			}
		}
		else
		{
			LOG(1)("AddJetton err %d\n", nRet);
			if(BigRoomOption::instance()->m_bkafkaLog)
			{
				RoomManager::gRoot->m_kafkalog.AddPPCBet(roomid,pUser->uin,pUser->userNick,awardRound, betMoney, areaIndex,nRet);
			}
			if(nRet == -6)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BETFAILED_CODE.c_str());
			}
			else if (nRet == -7)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_NO_MONEY.c_str());
			}
			else if (nRet == -5)
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BETFAILED_LIMIT.c_str());
			}
			else
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BETFAILED_INFO.c_str());
			}
		}
	}

	void Room::ProcessPPCScene(User* pUser)
	{
		if(!pUser)
		{
			return;
		}
		OutPacket extData2;
		BuildBankerInfo(extData2);
		BuildBankerWaitList(extData2);
		if (awardStatus == PPC_BETTING)
		{
			OutPacket outData;
			BuildBankerInfo(outData);
			BuildAreaLimitInfo(outData);
			BuildJetonItem(outData);
			pUser->NotifyPPCStart(awardRound, ppcBetMgr.GetBetTime() - (TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart))/1000, outData);
		}	
		else if (awardStatus == PPC_FREE)
		{
			pUser->NotifyAwardStatus(awardRound, IM_CAHT_SVR_PPC_FREE, ppcBetMgr.GetFreeTime() - (TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart)) / 1000);
		}
		else if (awardStatus == PPC_CARRUN)
		{
			pUser->NotifyPPCAward(awardRound, ppcBetMgr.GetGoalAnimal(), ppcBetMgr.GetRunTime() - (TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart)) / 1000, m_lastAllBet);
		}
 		extData2 << ppcBetMgr.GetBankerInfo().uin;
		extData2 << uint8(1);
		extData2 << "";
		pUser->NotifyPPCBankerChange(extData2);
	}

	void Room::OnSyncScene(UdpInPacket* in, User* pUser)
	{
		LOG(1)("OnSyncScene uin %d\n", pUser->uin);
		ProcessPPCScene(pUser);
	}

	void Room::OnBakerReq(UdpInPacket* in, User* pUser)
	{
		uint8 action ;
		*in >> action;
		LOG(1)("OnBakerReq uin %u action %d\n", pUser->uin, action);
		if(BigRoomOption::instance()->m_bkafkaLog)
		{
			RoomManager::gRoot->m_kafkalog.AddPPCBankerAction(roomid,pUser->uin,pUser->userNick,action,awardRound);
		}
		if(action == JettonManager::PPC_LEAVE_BANKER)
		{
			if(pUser->uin == ppcBetMgr.GetBankerInfo().uin)
			{
				if(awardStatus == PPC_FREE)
				{
					ppcBetMgr.ResetBankerInfo(); // ��ׯ
					
				}
				else
				{
					pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_CHANGE_BANKER_ERROR.c_str());
					return;
				}
				
			}
			else
			{
				ppcBetMgr.RemoveBankerWait(pUser->uin);
				NotifyChangeBanker(pUser->uin, action, "");
				//����������
				if(BigRoomOption::instance()->m_nolock)
				{
					RoomManager::gRoot->DBHLockMoney(roomid, pUser->uin, 0);
				}
				
				return;
			}
		}
		else
		{
			//�Ϸ��ж�
			if (pUser->money < ppcBetMgr.GetBankerCondition())
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BAKER_NOMONEY.c_str());
				return;
			}

			//�����ж�
			if(ppcBetMgr.IsInBakerWaitList(pUser->uin))
			{
				pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BANKER_RETRY.c_str());
				return;
			}
			//������Ϣ 
			//ppcBetMgr.AddBankerWait(pUser);
			//��ȡ��ǰ��Ҽ���Ƿ��㹻��ׯ
			RoomManager::gRoot->DBHGetUserCurMoney(roomid,pUser->uin);
			//�����
			if(BigRoomOption::instance()->m_nolock)
			{
				RoomManager::gRoot->DBHLockMoney(roomid, pUser->uin, 1);
			}			
		
		}

		//�л��ж�
		if (awardStatus == PPC_FREE )
		{
			NotifyChangeBanker(pUser->uin, action, "");
			ppcBetMgr.ChangeBanker();
		}
		else
		{
			NotifyChangeBanker(pUser->uin, action, "");
		}
	}


	void Room::OnHandleLockMoney(dataport::MoneyResult* tmpResult)
	{
		DbParaLockMoney * para = (DbParaLockMoney *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandleLockMoney para isNULL  roomid %u\n",  roomid);
			return;
		}

		LOG(1)("OnHandleLockMoney  roomid %u uin %u nState %d errcode %d\n",  roomid, para->uin, para->nState, tmpResult->errorCode);
	}

	void Room::OnHandlePPCBetMoney(dataport::MoneyResultList* tmpResult)
	{

		DbParaPPCBet * para = (DbParaPPCBet *)tmpResult->arg;
		if(!para)
		{
			LOG(1)("OnHandlePPCBetMoney para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPCBetMoney failed %d around %u\n", tmpResult->errorCode, para->around);
			UserMoneyMap& userBet = ppcBetMgr.GetUserJettonInfo();
			for (UserMoneyMap::iterator it = userBet.begin(); it != userBet.end(); it++)
			{
				User* pUser = GetUser(it->second->uin);
				if(pUser)
				{
					pUser->NotifyBetResult(tmpResult->errorCode, awardRound);
				}
			}
			UserMoneyMap& bankerBet = ppcBetMgr.GetBankerMap();
			for (UserMoneyMap::iterator it = bankerBet.begin(); it != bankerBet.end(); it++)
			{
				User* pUser = GetUser(it->second->uin);
				if(pUser)
				{
					pUser->NotifyBetResult(tmpResult->errorCode, awardRound);
				}
			}
			OnEventGameEnd();
			return;
		}
		

		if(awardStatus != PPC_WAIT || para->around !=  awardRound)
		{
			LOG(1)("OnHandlePPCBetMoney around %u %u awardStatus\n", awardRound, para->around, awardStatus);
			return;
		}
		m_userBetList.clear();
		int nCount = tmpResult->m_moneyList.size();
		for(int i = 0; i < nCount; i++)
		{
			
			UserWriteMoney2* pTemp = ppcBetMgr.GetUserJettonInfo(tmpResult->m_moneyList[i].uin);
			if(!pTemp)
			{
				LOG(1)("OnHandlePPCBetMoney jettonInfo not exist roomid %u around %u uin %u\n", roomid, awardRound, tmpResult->m_moneyList[i].uin);
				continue;
			}

			if(tmpResult->m_moneyList[i].errorCode)
			{
				pTemp->bSuccess = false;
				ppcBetMgr.RemoveUserJettonInfo(tmpResult->m_moneyList[i].uin);
				LOG(1)("roomid %u around %u uin %u bet failed %d\n", roomid, awardRound, tmpResult->m_moneyList[i].uin, tmpResult->m_moneyList[i].errorCode);
			}
			else
			{
				
				pTemp->bSuccess = true;

			}

			User* pUser = GetUser(tmpResult->m_moneyList[i].uin);
			if(!pUser)
			{
				continue;
			}
			m_userBetList[pUser->uin] = pUser;
			pUser->earning += pTemp->lScore;
			pUser->money = tmpResult->m_moneyList[i].m_lRemaining;
			pUser->NotifyBetResult(tmpResult->m_moneyList[i].errorCode, awardRound);
			
			

		}
		OnEventGameEnd();

		
		SyncUserInfo(m_userBetList);


	}


	void Room::OnHandlePPCAwardMoney(dataport::MoneyResultList* tmpResult)
	{
		DbParaPPCBet * para = (DbParaPPCBet *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPCAwardMoney para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPCAwardMoney failed %d \n", tmpResult->errorCode);
		}
		if(para->around != awardRound)
		{
			LOG(1)("OnHandlePPCAwardMoney around %u %u\n", awardRound, para->around);
			return;
		}
		m_userAwardList.clear();
		int nCount = tmpResult->m_moneyList.size();
		for(int i = 0; i < nCount; i++)
		{
			
	
			UserWriteMoney2* pTemp = ppcBetMgr.GetUserJettonInfo(tmpResult->m_moneyList[i].uin);
			if(!pTemp)
			{
				LOG(1)("OnHandlePPCAwardMoney jettonInfo not exist roomid %u around %u uin %u\n", roomid, awardRound, tmpResult->m_moneyList[i].uin);
				continue;
			}

			if(tmpResult->m_moneyList[i].errorCode)
			{
				LOG(1)("roomid %u around %u uin %u award failed %d\n", roomid, awardRound, tmpResult->m_moneyList[i].uin, tmpResult->m_moneyList[i].errorCode);
				pTemp->bSuccess = false;
			}
			else
			{
				pTemp->bSuccess = true;
				User* pUser = GetUser(tmpResult->m_moneyList[i].uin);
				if(pUser)
				{
					pUser->money = tmpResult->m_moneyList[i].m_lRemaining;
					pUser->earning += pTemp->lScore;
					m_userAwardList[pUser->uin] = pUser;
				}
				
				BankerInfo& bankerInfo = ppcBetMgr.GetBankerInfo();
				if(pTemp->m_nstate == UserWriteMoney2::WRITE_BANKER)
				{
					if(pTemp)
					{
						bankerInfo.m_iBankerWinScore += pTemp->lScore;
					}
				}
				//pUser->NotifyPPCAward(awardRound, ppcBetMgr.GetGoalAnimal());
			}

		}

		
		
		
	}

	void Room::OnHandlePPGetUserBlance(dataport::GetBalanceInfo * tmpResult)
	{
		DbParaUin * para = (DbParaUin *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPGetUserBlance para isNULL  roomid %u\n",  roomid);
			return;
		}
		User* pUser = GetUser(para->uin);
		if(pUser)
		{
			int64 winNum = tmpResult->m_outCount_company - tmpResult->m_inCount_company;
			if (pUser->earning < winNum)
			{
				pUser->earning = winNum;
			}
			if(BigRoomOption::instance()->m_bkafkaLog)
			{
				RoomManager::gRoot->m_kafkalog.AddWinLimit(roomid,awardRound,para->uin,CoreSocket::TransMacAddr(para->mac).c_str(),winNum);
			}
		}
#ifdef WIN32
		LOG(1)("OnHandlePPGetUserBlance uin %u mac %s win %I64d\n", para->uin, CoreSocket::TransMacAddr(para->mac).c_str(), tmpResult->m_outCount_company - tmpResult->m_inCount_company);
#else
		LOG(1)("OnHandlePPGetUserBlance uin %u mac %s win %lld\n", para->uin, CoreSocket::TransMacAddr(para->mac).c_str(), tmpResult->m_outCount_company - tmpResult->m_inCount_company);
#endif
		
		
	}



	void Room::OnHandlePPGetUserCurMoneyBC(dataport::GetUserCurMoney * tmpResult)
	{
		DbParaUin * para = (DbParaUin *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPGetUserBlance para isNULL  roomid %u\n",  roomid);
			return;
		}
		User* pUser = GetUser(para->uin);
		if (NULL == pUser)
		{
			LOG(4)("Room::OnHandlePPGetUserCurMoneyBC not have user uin:%u \n",para->uin);
			return;
		}
		pUser->money = tmpResult->m_curMoney;

		//�Ϸ��ж�
		if (pUser->money < ppcBetMgr.GetBankerCondition())
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BAKER_NOMONEY.c_str());
			//�������
			if(BigRoomOption::instance()->m_nolock)
			{
				RoomManager::gRoot->DBHLockMoney(roomid, pUser->uin, 0);
			}
			return;
		}

		//�����ж�
		if(ppcBetMgr.IsInBakerWaitList(pUser->uin))
		{
			pUser->sendNtyMsg(ChatRoomMsg::STR_MSG_BANKER_RETRY.c_str());
			return;
		}
		//������Ϣ 
		ppcBetMgr.AddBankerWait(pUser);
		uint8 action = JettonManager::PPC_TAKE_BANKER;
		NotifyChangeBanker(pUser->uin, action, "");
	}

	void Room::OnHandlePPAddGameLimit(dataport::CDBClientResult* tmpResult)
	{
		DbParaUin* para = (DbParaUin *)tmpResult->arg;
		if(!para)
		{
			LOG(1)("OnHandlePPAddGameLimit para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPCAddGameLimit roomid %u uin %u failed %d\n", roomid, para->uin,  tmpResult->errorCode);
			return;
		}

		User* dstUser = GetUser(para->uin);
		if(dstUser)
		{
			dstUser->isGameLimit = 1;
		}
	}

	void Room::OnHandlePPCheckGameLimit(dataport::GetUserPpcLimited* tmpResult)
	{
		DbParaIpPort* para = (DbParaIpPort *)tmpResult->arg;
		if(!para)
		{
			LOG(1)("OnHandlePPCheckGameLimit para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPCheckGameLimit roomid %u uin %u failed %d\n", roomid, para->uin,  tmpResult->errorCode);
			return;
		}

		if(tmpResult->islimited == 1)
		{
			User* user = para->m_room_man->m_UserManager.GetUser(para->ip, para->port,para->m_room_id);
			if(user)
			{
				user->isGameLimit = 1;
			}
		}
		
	}
	
	void Room::OnHandleGetDisconnectTimes(dataport::GetDisconnectTimes* tmpResult)
	{
		DbParaIpPort* para = (DbParaIpPort *)tmpResult->arg;
		if(!para)
		{
			LOG(1)("OnHandleGetDisconnectTimes para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandleGetDisconnectTimes roomid %u uin %u failed %d\n", roomid, para->uin,  tmpResult->errorCode);
			return;
		}
		
		int times = tmpResult->mac_limitNum > tmpResult->uin_limitNum ? tmpResult->mac_limitNum:tmpResult->uin_limitNum;
		if(times >= BigRoomOption::instance()->m_kickLimitTimes)
		{
			User* pUser = para->m_room_man->m_UserManager.GetUser(para->ip, para->port,para->m_room_id);
			if(pUser)
			{
				pUser->kickLimitTimes = 1;
				//pUser->NotifyKickOut(para->uin, 10000, ROOM_KICKTYPE_UPPER_TODAYLIMIT);
				LOG(1)("user %d reach today m_kickLimitTimes %d dont allow enter game\n",pUser->uin, times);
				//logoutMap.push_back(pUser->uin);
			}
		}
	}

	void Room::OnHandlePPSaveBankerResult(dataport::MoneyResult* tmpResult)
	{
		DbParaPPCBanker * para = (DbParaPPCBanker *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPSaveBankerResult para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(para->around != awardRound)
		{
			LOG(1)("OnHandlePPSaveBankerResult around %u %u uin %u\n", awardRound, para->around, para->uin);
			return;
		}

		UserWriteMoney2* pTemp = ppcBetMgr.GetUserJettonInfo(para->uin);
		if(!pTemp)
		{
			LOG(1)("OnHandlePPSaveBankerResult jettonInfo not exist roomid %u around %u uin %u\n", roomid, awardRound, para->uin);
			return;
		}

		if(tmpResult->errorCode)
		{
			LOG(1)("OnHandlePPSaveBankerResult roomid %u around %u uin %u award failed %d\n", roomid, awardRound, para->uin, tmpResult->errorCode);
			pTemp->bSuccess = false;
		}
		else
		{
			pTemp->bSuccess = true;
			User* pUser = GetUser(para->uin);
			if(pUser)
			{
				pUser->money = tmpResult->m_lRemaining;
				ppcBetMgr.SetBankerMoney(pUser->money);
			}
			BankerInfo& bankerInfo = ppcBetMgr.GetBankerInfo();
			bankerInfo.m_iBankerWinScore += pTemp->lScore;
			
		}
		
	
	}

	void Room::OnHandlePPCHistory(dataport::AwaredHistoryResult* tmpResult)
	{
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPCHistory failed %d \n", tmpResult->errorCode);
			RoomManager::gRoot->DBHLoadPPCHistory(roomid);
			return;
		}
		
		int nCount = tmpResult->itemList.size();
		for(int i = nCount -1 ; i >= 0; i--)
		{
			ppcBetMgr.AddHistroy(tmpResult->itemList[i].nItemID, tmpResult->itemList[i].nItemCount);
		}


		
	}



	void Room::OnHandlePPSaveExperience(dataport::CDBClientResult* tmpResult)
	{
		DbParaUin * para = (DbParaUin *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPGetExperience para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPSaveExperience roomid %u uin %u failed %d\n", roomid, para->uin,  tmpResult->errorCode);
			return;
		}

		User* pUser = GetUser(para->uin);
		if(pUser)
		{
			pUser->received ++;
			pUser->sendNtyMsg("");
		}

	}


	void Room::OnHandlePPGetExperience(dataport::MoneyResult* tmpResult)
	{
		DbParaUin * para = (DbParaUin *)tmpResult->arg;

		if(!para)
		{
			LOG(1)("OnHandlePPGetExperience para isNULL  roomid %u\n",  roomid);
			return;
		}
		if(tmpResult->errorCode != 0)
		{
			LOG(1)("OnHandlePPGetExperience roomid %u uin %u failed %d\n", roomid, para->uin,  tmpResult->errorCode);
			return;
		}
		User* pUser = GetUser(para->uin);
		if(pUser)
		{
			pUser->received  = tmpResult->m_lRemaining;
			pUser->sendNtyMsg("");
		}


	}


	
	
	



	void Room::OnHandlePPC()
	{
		
		uint32 timeDelay = TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart);

		if (awardStatus == PPC_FREE)
		{
			if (timeDelay >= ppcBetMgr.GetFreeTime()*1000 && awardRound)
			{
				awardStatus = PPC_BETTING;
				curStatusStart = talk_base::TimeStamp();
				LOG(1)("ppc PPC_BETTING around %d --\n", awardRound);

				OnEventGameStart();


			}
		}	
		else if (awardStatus == PPC_BETTING)
		{
			if (timeDelay >= uint32(ppcBetMgr.GetBetTime() * 1000))//��עʱ�����
			{
				curStatusStart = talk_base::TimeStamp();
				awardStatus = PPC_WAIT;
				LOG(1)("ppc PPC_WAIT  around %d --\n", awardRound);
				
				RoomManager::gRoot->DBPPCHBet(roomid, awardRound, ppcBetMgr.GetUserJettonInfo(), ppcBetMgr.bIsSysBanker());
				
			}
			else
			{
				uint32 tm = timeDelay/1000;
				if ( tm != 0 && tm%BigRoomOption::instance()->m_confusionCheckTime == 0)
				{
					CheckAndAddRobotBetInfo(timeDelay/1000);
				}
				CheckSendRobotBetInfo(timeDelay/1000);
			}
			
		}
		else if(awardStatus == PPC_WAIT)
		{
			if (timeDelay >= uint32(WAIT_TIME * 1000))//180��֮�󲻹�Ѻע����Ƿ񷵻�
			{
				curStatusStart = talk_base::TimeStamp();
				awardStatus = PPC_CARRUN;
				LOG(1)("ppc wait timeout OnEventGameEnd roomid %u aRound %u --\n", roomid, awardRound);
				OnEventGameEnd();//ǿ�ƽ���
			}
		
		}
		else if(awardStatus == PPC_CARRUN)
		{
			if (timeDelay >= ppcBetMgr.GetRunTime()*1000)
			{
				awardStatus = PPC_END;
				//��Ϸ��¼
				ppcBetMgr.AddHistroy(awardRound, ppcBetMgr.GetGoalAnimal() % (JETTON_AREA_COUNT));
				curStatusStart = talk_base::TimeStamp();
				NotifyAwardMsg();
				
			
			}
		}
		else if(awardStatus == PPC_END)
		{
			if (timeDelay >= 8*1000)
			{
				awardStatus = PPC_FREE;
				curStatusStart = talk_base::TimeStamp();
				NotifyState(awardRound, IM_CAHT_SVR_PPC_FREE, ppcBetMgr.GetFreeTime() - (TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart)) / 1000);
				ppcBetMgr.ChangeBanker();
				SyncUserInfo(m_userAwardList);

				if(BigRoomOption::instance()->m_bSyncHist)
				{
					NotifyPPCHistory();
				}
				ResetRobotBetInfo();
			}
		}
		else if(awardStatus == PPC_STOP)
		{
			if(timeDelay >= ppcBetMgr.GetFreeTime()*1000)
			{
				awardStatus = PPC_FREE;
				curStatusStart = talk_base::TimeStamp();
				NotifyState(awardRound, IM_CAHT_SVR_PPC_FREE, ppcBetMgr.GetFreeTime() - (TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart)) / 1000);
				ppcBetMgr.ChangeBanker();

				ResetRobotBetInfo();
			}
		}
		
	}

	bool myCompare(uint64 a, uint64 b)
	{
		return a < b;
	}

	






	void Room::PushUser( User *user )
	{
		if (this == RoomManager::gRoot || roomid == 0)
			return;

		user->item.remove();

		usersTop.add(&user->item);
	}

	bool Room::CheckChatText( User *srcUser, char *buf )
	{
		if (RoomManager::gRoot->CheckWordFilter(buf))
		{
			srcUser->filterWordTimes++;
			if (srcUser->filterWordTimes >= 2)
			{
				RoomManager::gRoot->blockMgr.AddBlockItem(srcUser->uin, time(NULL) + 60 * 10);	
				RoomManager::gRoot->blockMgr.AddBlockItem(srcUser->ip, time(NULL) + 60 * 10);	
				RoomManager::gRoot->blockMgr.AddBlockItem(srcUser->userMac, time(NULL) + 60 * 10);	

				srcUser->NotifyKickOut(srcUser->uin, 10000, ROOM_KICKTYPE_KICKOUT);
				logout(srcUser, true, 10000, ROOM_KICKTYPE_KICKOUT, true);
			}
			else
			{
				srcUser->sendNtyMsg(ChatRoomMsg::STR_MSG_FILTER.c_str());
			}

			return true;
		}

		return false;
	}


	uint8 Room::GetBalanceAwardID( int64 balanceLine )
	{
//		UserBetTemp *theMostLoser = NULL;
//			
//		for (UserBetMap::iterator it = beteds.begin(); it != beteds.end(); it++)
//		{
//			if (it->second->balance < balanceLine && (theMostLoser == NULL || it->second->balance < theMostLoser->balance))
//			{
//				theMostLoser = it->second;
//			}
//		}
//
//
//		if (theMostLoser)
//		{
//
//#ifndef _WIN32
//			LOG(4)("%d  loser = %d %lld\n", awardRound , theMostLoser->uin, theMostLoser->balance);
//#else
//			LOG(4)("%d  loser = %d %I64d\n", awardRound , theMostLoser->uin, theMostLoser->balance);
//#endif
//
//			uint8 awardIndex = -1;
//			std::vector<uint8> awardKeyList;
//			for (uint8 i=0; i<theMostLoser->bets.size(); i++)
//			{
//				if (theMostLoser->bets[i].betIdx <= ZZAward::STAR_XIAO_TIANWAN_25 )
//				{
//					//С����
//					if (uint64(theMostLoser->bets[i].betAmount * ZZAward::upValue[theMostLoser->bets[i].betIdx]) > theMostLoser->betCount)
//					{
//						awardKeyList.push_back(theMostLoser->bets[i].betIdx);
//					}
//					
//					//����
//					uint64 itemAward = uint64(theMostLoser->bets[i].betAmount * ZZAward::upValue[theMostLoser->bets[i].betIdx + ZZAward::STAR_DA_LIUHUAN_15]);
//					if (itemAward > theMostLoser->betCount)
//					{
//						
//						awardKeyList.push_back(theMostLoser->bets[i].betIdx + ZZAward::STAR_DA_LIUHUAN_15);
//
//					}
//
//				}
//			}
//
//			if (awardKeyList.size())
//			{
//				awardIndex = awardKeyList[(rand() * (uint32)talk_base::TimeStamp()) % awardKeyList.size()];
//				LOG(1)("%d  balance awardid = %d\n", theMostLoser->uin, awardIndex);
//
//				return awardIndex;
//			}
//
//		}
//
//		return ZZAward::STAR_DA_TIANWAN_50+1;
		return 0;
	}

	void Room::NotifyBetAction( uint8 areaIndex, uint32 betMoney, uint64 maxPlaceArea , uint32 betUin, uint32 around)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		OutPacket outData;
		BuildAllBetInfo(outData);
		IMCHAT_SEND_COMMAND_PARAM7(iterator,entry,User,NotifyBetAction, areaIndex, betMoney, maxPlaceArea, betUin, around, outData, BigRoomOption::instance()->m_bSyncBet);
	}

	void Room::NotifyPPCWinItem(uint32 aRound, uint16 winItem, uint16 delayTime)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		IMCHAT_SEND_COMMAND_PARAM4(iterator,entry,User,NotifyPPCAward, aRound, winItem,delayTime, m_lastAllBet);
	}

	void Room::InitialUserMoneyArry()
	{
		while(ppcBetMgr.GetUserJettonInfo().size())
		{
			delete ppcBetMgr.GetUserJettonInfo().begin()->second;
			ppcBetMgr.GetUserJettonInfo().erase(ppcBetMgr.GetUserJettonInfo().begin());
		}

	}

	void  Room::OnEventGameStart()
	{
		BigRoomOption::instance()->ReadPPCConfig();
		UpdateRoomLink();
		awardRound++;
		InitialUserMoneyArry();
		m_lastAllBet.reinit();

		//��������
		//CMD_S_GameStart GameStart;
		//ZeroMemory(&GameStart,sizeof(GameStart));



		//GameStart.cbTimeLeave=ppcBetMgr.GetBetTime();
		//GameStart.wBankerUser=ppcBetMgr.GetBankerInfo().uin;
		//GameStart.bankerUIN = ppcBetMgr.GetBankerInfo().uin;
		//GameStart.iBankerScore = ppcBetMgr.GetTotalBankMoney();

		//GameStart.iAreaLimitScore
		// 	//if (pIBankerServerUserItem!=NULL) 
		// 	//	GameStart.iBankerScore=pIBankerServerUserItem->GetUserData()->m_money;

		//ÿ����Ϸ��ʼʱ�̣�����������ʼ���·�ֵ


		//TCHAR szTipMsg[128] = _T("");
		//_sntprintf(szTipMsg,CountArray(szTipMsg),TEXT("[%d��]��ʼ...\n"),m_rounds);
		////���͸���Ϸ���
		//for (WORD wChairID=0; wChairID<GAME_PLAYER; ++wChairID)
		//{

		//	IServerUserItem *pIServerUserItem=m_pITableFrame->GetServerUserItem(wChairID);
		//	if (pIServerUserItem==NULL) 
		//		continue;


		//	//		m_UserMoney[wChairID].uin = pIServerUserItem->GetUserData()->m_uin;
		//	//���û���
		//	GameStart.iUserMaxScore=min(pIServerUserItem->GetUserData()->m_money,ppcBetMgr.GetUserLimitMoney());
		//	LOG(1)("wChairID %d, GameStart.iUserMaxScore %I64d , userMoney %I64d, m_iUserLimitScore %I64d line %d\n",
		//		pIServerUserItem->GetUserData()->m_uin,
		//		GameStart.iUserMaxScore, pIServerUserItem->GetUserData()->m_money, 
		//		ppcBetMgr.GetUserLimitMoney(), __LINE__);
		//	m_pITableFrame->SendTableData(wChairID, SUB_S_GAME_START, &GameStart,sizeof(GameStart));	
		//	m_pITableFrame->SendGameMessage(pIServerUserItem,szTipMsg,SMT_INFO);
		//}

		User* pBanker = GetUser(ppcBetMgr.GetBankerInfo().uin);
		ppcBetMgr.NewRound(awardRound, pBanker, ppcBetMgr.GetAreaLimitMoney(), ppcBetMgr.GetTaxRate(), ppcBetMgr.GetUserLimitMoney());

		//֪ͨ�����˿��Կ�ʼͶע
		NotifyPPCStart(awardRound, ppcBetMgr.GetBetTime());
		return;
	}




	void Room::OnEventGameEnd()
	{
		m_lastAllBet.reinit();
		BuildAllBetInfo(m_lastAllBet);


		for (UserMoneyMap::iterator it = ppcBetMgr.GetUserJettonInfo().begin(); it != ppcBetMgr.GetUserJettonInfo().end(); it++)
		{
			if (it->second->lScore != 0)
			{
				User* pUser = GetUser(it->second->uin);
				if(pUser)
				{
					BuildUserBetInfo(it->second, pUser->m_userAllBet);
				}
			}

		}
		//�ɷ��˿�
		ppcBetMgr.NormalDispatchCard();


		ppcBetMgr.AddBanktimes();



		ppcBetMgr.CheckWinner();

		//m_nWriteState = UserWriteMoney2::WRITE_MONEY;
		UserMoneyVec2 writeMoneyArray;

		for (UserMoneyMap::iterator it = ppcBetMgr.GetUserJettonInfo().begin(); it != ppcBetMgr.GetUserJettonInfo().end(); it++)
		{
			


			if (it->second->lScore > 0)
			{
#ifdef WIN32
				LOG(1)("OnEventGameEnd user %I64d\n", it->second->lScore);
#else
				LOG(1)("OnEventGameEnd user %lld\n", it->second->lScore);
#endif
				writeMoneyArray.push_back(it->second);
				User* pUser = GetUser(it->second->uin);
				if(pUser)
				{
					BuildUserBetInfo(it->second, pUser->m_userAllBet);
				}
				
				
			}
			
		}
		for (UserMoneyMap::iterator it = ppcBetMgr.GetBankerMap().begin(); it != ppcBetMgr.GetBankerMap().end(); it++)
		{
			if (it->second->lScore != 0)
			{
#ifdef WIN32
				LOG(1)("OnEventGameEnd banker %I64d uin %u\n", it->second->lScore, it->second->uin);
#else
				LOG(1)("OnEventGameEnd banker %lld uin %u\n", it->second->lScore, it->second->uin);
#endif
			}
		}
		
		//���¸��û��н���Ǯ
		RoomManager::gRoot->DBHPPCAward(roomid, awardRound,  ppcBetMgr.GetUserJettonInfo(), ppcBetMgr.bIsSysBanker());
		
		//�����û�ׯ�������
		RoomManager::gRoot->DBHSaveBankerResult(roomid, awardRound, ppcBetMgr.GetGoalAnimal()%JETTON_AREA_COUNT, ppcBetMgr.GetBankerMap());
		

		RoomManager::gRoot->DBHLoadBalanceInfo(roomid);
		


		//��ת
		awardStatus = PPC_CARRUN;
		curStatusStart = talk_base::TimeStamp();
		NotifyPPCWinItem(awardRound, ppcBetMgr.GetGoalAnimal(), ppcBetMgr.GetRunTime() - TIME_DIFF_U(talk_base::TimeStamp(), curStatusStart)/1000);


		return ;
	}


	void Room::SyncUserInfo(UserGameMap& gameMap)
	{
		uint16 num = 0;
		uint16 total = gameMap.size();
		uint16 old = 0;
		UdpOutPacket outData;
		int	ci = 0;
		uint32 packetmark = time(NULL);

		uint32 bankerUin = ppcBetMgr.GetBankerInfo().uin;
		//����У���
		if(total == 0 && bankerUin == 0)
		{
			return;
		}

		uint16 packetnum = (total + MAX_USERINFO - 1) / MAX_USERINFO;
		int pkindex = 0;
		UserGameMapIter iter;
		for(iter = gameMap.begin(); iter != gameMap.end(); iter++)
		{
			User* pDstUser = iter->second;

			if (!num)
			{
				outData.reinit();
				outData << packetmark << packetnum << (uint16)pkindex;
				pkindex ++;
				//old = out->skip(sizeof(num));
				old = outData.GetPosition(sizeof(num));
			}

			outData << pDstUser->uin << pDstUser->money << (uint32)pDstUser->received;//uin/money/����

			if (++num >= MAX_USERINFO)
			{
				//old = out->setCursor(old);
				old = outData.SetPosition(old);
				outData << num;
				outData.SetPosition(old);
				//out->setCursor(old);

				UpdateUserInfo(outData);

				num = 0;
			}

			ci++;
			if(ci >= MAX_VISITORS)
				break;
		}

		if (num) {
			//old = out->setCursor(old);
			old = outData.SetPosition(old);
			outData << num;
			outData.SetPosition(old);
			//out->setCursor(old);
			UpdateUserInfo(outData);
		}

		if (bankerUin)
		{
			User* pBanker = m_UserManager.GetUser(bankerUin);
			if (pBanker != NULL)
			{
				pkindex = 0;
				num = 0;
				if (!num)
				{
					outData.reinit();
					outData << packetmark << packetnum << (uint16)pkindex;
					pkindex ++;
					//old = out->skip(sizeof(num));
					old = outData.GetPosition(sizeof(num));
				}
				outData << pBanker->uin << pBanker->money << (uint32)pBanker->received;
				++num;
				old = outData.SetPosition(old);
				outData << num;
				outData.SetPosition(old);
				//out->setCursor(old);

				UpdateUserInfo(outData);
			}
		}
		gameMap.clear();
	}

	void Room::UpdateUserInfo(OutPacket& outData)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry, User, NotifyUpdateUserInfo, outData);
	}
	//ׯ����Ϣ
	void Room::BuildBankerInfo( OutPacket& outData )
	{
		BankerInfo& info = ppcBetMgr.GetBankerInfo();

		outData << info.uin;
		outData << info.m_wBankerTimes;
		outData << (uint64)info.m_iBankerWinScore;
		if(info.uin)
		{
			outData << ppcBetMgr.GetTotalBankMoney();
		}
		else
		{
			outData << (uint64)0;
		}

	}

	void Room::BuildBankerWaitList(OutPacket& outData)
	{
		BankerWaitList bankerWatiList = ppcBetMgr.GetBankerWaitList();
		uint16 nCount = bankerWatiList.size();
		BankerWaitList::iterator iter;
		outData << nCount;
		
		for(uint16 i = 0; i < nCount; i++)
		{
			outData << bankerWatiList[i]->uin << bankerWatiList[i]->userNick;
		}
	}

	void Room::BuildAreaLimitInfo( OutPacket& outData )
	{
		uint16 areaSize = JETTON_AREA_COUNT;
		outData << areaSize;
		for( int i=0; i<JETTON_AREA_COUNT; i++)
		{
			outData << ppcBetMgr.GetItemJettonLastLimit(i);
		}
	}

	void Room::BuildJetonItem(OutPacket& outData)
	{
		uint16 jettonSize = BigRoomOption::instance()->m_ppcOption.m_maxJetton;
		outData << jettonSize;
		for(int i = 0; i < jettonSize; i++)
		{
			outData << BigRoomOption::instance()->m_ppcOption.m_jettonList[i];
		}

		outData << BigRoomOption::instance()->m_ppcOption.m_bankerCondition;
		outData << BigRoomOption::instance()->m_ppcOption.m_userLimitMoney;

	}

	void Room::BuildAllBetInfo(OutPacket& outData)
	{
		uint16 areaSize = JETTON_AREA_COUNT;
		outData << areaSize;
		for( uint8 i=0; i< JETTON_AREA_COUNT; i++)
		{
			outData << i;
			outData << (ppcBetMgr.GetItemJettonCount(i) + m_robotCurBetArray[i]);
		}
	}

	void Room::BuildUserBetInfo(UserWriteMoney2* userBetInfo, OutPacket& outData)
	{
		uint16 areaSize = JETTON_AREA_COUNT;
		outData << areaSize;
		const JettonArray& jetton = userBetInfo->GetJetton();
		for( uint8 i=0; i< JETTON_AREA_COUNT; i++)
		{
			outData << (uint64)abs(jetton[i].m_money);
		}
	}

	

	void Room::BuildPPCHistory(OutPacket& outData)
	{
		PPCHistoryList historyList = ppcBetMgr.GetPPCHistory();
		uint16 maxHistory = ppcBetMgr.GetMaxHistory();
		uint16 nCount = historyList.size();
		outData << maxHistory;
		outData << nCount;
		PPCHistoryList::iterator iter;
		for(iter = historyList.begin(); iter != historyList.end(); iter++)
		{
			outData << iter->awardId;
		}
	}

	void Room::NotifyPPCStart( uint32 aRound, uint16 delayTime )
	{
		OutPacket outData;
		BuildBankerInfo(outData);
		BuildAreaLimitInfo(outData);
		BuildJetonItem(outData);
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM3(iterator,entry, User, NotifyPPCStart, aRound,  delayTime, outData);
	}

	void Room::NotifyState( uint32 aRound, uint16 cmd, uint16 delayTime )
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;
		IMCHAT_SEND_COMMAND_PARAM3(iterator,entry, User, NotifyAwardStatus, aRound,  cmd, delayTime);
	}

	void Room::NotifyAwardMsg()
	{
		UserMap::ITERATOR it(m_UserManager.m_UserMap);
		UserMap::ENTRY* entry = 0;

		ppcGameEndInfo GameEnd;  
		BankerInfo& info = ppcBetMgr.GetBankerInfo();
		GameEnd.nBankerTime = info.uin ? info.m_wBankerTimes : 0;
		GameEnd.iBankerTotallScore = info.uin ? info.m_iBankerWinScore : 0;
		GameEnd.iBankerScore = ppcBetMgr.GetBankerWin();
		if (BigRoomOption::instance()->m_confusionOpen)
		{
			GameEnd.iBankerScore = ppcBetMgr.GetConfusionBankerWin();
		}

		GameEnd.m_bWin = false;
		GameEnd.cbGoalAnimal = ppcBetMgr.GetGoalAnimal();

		while(it.next(entry) != 0) 
		{
			User* pUser = (*entry).int_id_;
			it.advance();

			UserWriteMoney2 *item = ppcBetMgr.GetUserJettonInfo(pUser->uin);
			if (item)
			{
				GameEnd.m_bSucess = item->bSuccess || item->lScore == 0;
				GameEnd.iUserScore = item->loseOrWin;
				GameEnd.iRevenue = item->lRevenue;
				GameEnd.m_rounds = item->m_rounds;
				GameEnd.m_bWin =  GameEnd.iUserScore > 0 ? true : false;	

				if (item->m_nstate == UserWriteMoney2::WRITE_MONEY)
				{
					if (item->lScore >= ppcBetMgr.GetBroadMsgMoney() && item->lScore >= 1000000)
					{
						char tip[512]={0};
						snprintf(tip,sizeof(tip),ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG2.c_str(), 
							pUser ? pUser->userNick : "",
							item->uin, awardRound,
							item->lScore);
						string strWinMsg = tip;
						strWinMsg += m_roomLink;
						OutPacket out;
						out << uint32(10000) << ChatRoomMsg::STR_MSG_SYSTEM_MSG << roomid;
						out << uint32(255) << uint8(BigRoomOption::instance()->m_notifyMsgType) << uint8(1) << uint8(0) << uint32(280) << strWinMsg.c_str();

						UdpInPacket in;
						LOG(1)("winmsg %s\n", strWinMsg.c_str());
						in.setdata(out.GetData(), out.getdatalen());

						RoomManager::gRoot->SendGlobleMsg(&in, true);
					}
					else if (item->lScore > 0 && ppcBetMgr.GetWinningMultiple() > 5)
					{
						char tip[512]={0};
						snprintf(tip,sizeof(tip),ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG.c_str(),
							pUser ? pUser->userNick : "",
							item->uin, awardRound,
							 ppcBetMgr.GetWinningMultiple()
							 );
						string strWinMsg = tip;
						strWinMsg += m_roomLink;
						OutPacket out;
						out << uint32(10000) << ChatRoomMsg::STR_MSG_SYSTEM_MSG << roomid;
						out << uint32(255) << uint8(BigRoomOption::instance()->m_notifyMsgType) << uint8(1) << uint8(0) << uint32(280) << strWinMsg.c_str();

						UdpInPacket in;
						LOG(1)("winmsg %s\n", strWinMsg.c_str());
						in.setdata(out.GetData(), out.getdatalen());

						RoomManager::gRoot->SendGlobleMsg(&in, true);
					}
				}
				else if (item->m_nstate == UserWriteMoney2::WRITE_BANKER)
				{

					
					if (item->lScore >= ppcBetMgr.GetBroadMsgMoney())
					{
						char tip[512];
						snprintf(tip,sizeof(tip),ChatRoomMsg::STR_MSG_ZZ_AWARD_MSG3.c_str(), 
							pUser ? pUser->userNick : "",
							item->uin,
							item->lScore
							);
						string strWinMsg = tip;
						strWinMsg += m_roomLink;
						OutPacket out;
						out << uint32(10000) << ChatRoomMsg::STR_MSG_SYSTEM_MSG << roomid;
						out << uint32(255) << uint8(uint8(BigRoomOption::instance()->m_notifyMsgType)) << uint8(1) << uint8(0) << uint32(280) << strWinMsg.c_str();

						UdpInPacket in;
						LOG(1)("winmsg %s\n", strWinMsg.c_str());
						in.setdata(out.GetData(), out.getdatalen());

						RoomManager::gRoot->SendGlobleMsg(&in, true);
					}
				}



			}
			else
			{
				GameEnd.m_bSucess = true;
				GameEnd.iUserScore = 0;
				GameEnd.iRevenue = 0;
				GameEnd.m_rounds = awardRound;
				if(pUser->isGameLimit)//����Ƿ񱻷��һ�����
				{
					pUser->unBetCount +=1;//����ûѺע������1
				}
			}	
			GameEnd.m_money = pUser->money;
			GameEnd.m_lExperience = pUser->received;
#ifdef WIN32
			LOG(1)("user %d  bank %I64d  %I64d, user %I64d\n",pUser->uin,  GameEnd.iBankerScore, GameEnd.iBankerTotallScore, 
				GameEnd.iUserScore );
#else
			LOG(1)("user %d  bank %lld  %lld, user %lld\n",pUser->uin,  GameEnd.iBankerScore, GameEnd.iBankerTotallScore, 
				GameEnd.iUserScore);
#endif
			OutPacket outData;
			BuildGameEndInfo(outData, GameEnd);
			pUser->NotifyGameEndInfo(outData);

			if(pUser->isGameLimit)
			{
				if(pUser->unBetCount >= BigRoomOption::instance()->m_nobetMaxTimes)//�������ûѺע������������
				{
					pUser->NotifyKickOut(pUser->uin, 10000, ROOM_KICKTYPE_NOBET_TIMES);
					//��¼�����߳�����
					RoomManager::gRoot->DBHIncrDisconnectTimes(roomid, BigRoomOption::instance()->partnerid, pUser->userMac, pUser->uin);
					LOG(1)("user %d unBetCout %d time kickedOut\n", pUser->uin, pUser->unBetCount);
					logoutMap.push_back(pUser->uin);
				}
			}

			if(BigRoomOption::instance()->m_bkafkaLog)
			{
				RoomManager::gRoot->m_kafkalog.AddGameEndInfo(roomid,awardRound,(uint32)ppcBetMgr.GetGoalAnimal()%JETTON_AREA_COUNT,GameEnd.iBankerScore,pUser->uin,GameEnd.iBankerTotallScore);
			}
		}
	}

	void Room::BuildGameEndInfo(OutPacket& outData, ppcGameEndInfo& endInfo )
	{

		outData << endInfo.m_rounds << endInfo.cbGoalAnimal;
		outData << endInfo.iBankerScore << endInfo.iBankerTotallScore << endInfo.nBankerTime;
		outData << endInfo.iUserScore << endInfo.iRevenue << endInfo.m_bSucess << endInfo.m_bWin;
		outData << endInfo.m_money << endInfo.m_lExperience;
	}

	void Room::NotifyChangeBanker(uint32 uin, uint8 action, const char* msg)
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		OutPacket extData;
		BuildBankerInfo(extData);
		BuildBankerWaitList(extData);
		extData << uin;
		extData << action;
		extData << msg;
		iterator = m_UserManager.m_UserMap.begin();
		entry = 0;
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyPPCBankerChange, extData);
	}

	void Room::NotifyPPCHistory()
	{
		UserMap::ITERATOR iterator(m_UserManager.m_UserMap);
		UserMap::ENTRY *entry = 0;

		OutPacket extData;
		BuildPPCHistory(extData);
	
		IMCHAT_SEND_COMMAND_PARAM(iterator,entry,User,NotifyPPCHistory, extData);
		
	}

	void Room::UpdateRoomLink()
	{
		char buf[512] = {0};
		sprintf(buf, ChatRoomMsg::STR_MSG_BROADCAST_LINK.c_str(), roomid);
		m_roomLink = "";
		m_roomLink = buf;
	}

	void Room::AddMacUserBet( uint64 mac,uint32 uin )
	{
		MacBetMapIter iter = m_macBetMap.find(mac);
		if (iter == m_macBetMap.end())
		{
			m_macBetMap.insert(pair<uint64,uint32>(mac,uin));
		}
	}

	void Room::AddRobotBet( uint8 areaIndex, uint64 betMoney, uint32 betUin, uint32 around, uint64 maxPlaceArea )
	{
		LOG(4)("Room::AddRobotBet around:%u areaIndex:%u betMoney:%llu \n",around,areaIndex,betMoney);
		RobotBetInfo info;
		info.areaIndex = areaIndex;
		info.betMoney = betMoney;
		info.betUin = betUin;
		info.around = around;
		info.maxPlaceArea = maxPlaceArea;
		m_robotBetInfos.push_back(info);
	}

	void Room::ResetRobotBetInfo()
	{
		LOG(4)("Room::ResetRobotBetInfo \n");
		m_robotBetInfos.clear();
		m_macBetMap.clear();
		for (uint8 i = 0; i < JETTON_AREA_COUNT; i++)
		{
			m_robotBetArray[i] = 0;
			m_robotCurBetArray[i] = 0;
		}
	}

	void Room::CheckAndAddRobotBetInfo(uint32 surplusEndTime)
	{
		if (PPC_BETTING != awardStatus)
		{
			return;
		}
		if (BigRoomOption::instance()->m_confusionOpen && GetBetMacCount() >= BigRoomOption::instance()->m_confusionOpenMacLimit)
		{
			LOG(4)("ppcBetMgr.CheckAddConfound currentMac:%u \n",GetBetMacCount());
			if(surplusEndTime > BigRoomOption::instance()->m_ppcOption.m_betTime - 2)
			{
				return;
			}
			ppcBetMgr.CheckAddConfound();
		}
	}

	void Room::CheckSendRobotBetInfo( uint32 surplusEndTime )
	{
		uint32 betSize = m_robotBetInfos.size();
		if (PPC_BETTING != awardStatus || betSize < 1)
		{
			return;
		}
		uint32 sendNum = betSize/3;
		random_shuffle (m_robotBetInfos.begin(), m_robotBetInfos.end());

		//ʣ�����һ����ֱ���·����е�
		if (sendNum < 1 || surplusEndTime > BigRoomOption::instance()->m_ppcOption.m_betTime - 2)
		{
			vector<RobotBetInfo>::iterator it = m_robotBetInfos.begin();
			while (it != m_robotBetInfos.end())
			{
				RobotBetInfo info = *it;
				//����Ѻע֪ͨ
				NotifyBetAction(info.areaIndex,info.betMoney,info.maxPlaceArea,info.betUin,awardRound);
				m_robotCurBetArray[info.areaIndex] += info.betMoney;
				it = m_robotBetInfos.erase(it);
			}
		}
		else
		{
			vector<RobotBetInfo>::iterator it = m_robotBetInfos.begin();
			for(uint32 i = 0; i<sendNum;i++)
			{
				RobotBetInfo info = *it;
				//����Ѻע֪ͨ
				NotifyBetAction(info.areaIndex,info.betMoney,info.maxPlaceArea,info.betUin,awardRound);
				m_robotCurBetArray[info.areaIndex] += info.betMoney;
				it = m_robotBetInfos.erase(it);
				if (it == m_robotBetInfos.end())
				{
					return;
				}
			}
		}
	}


}


