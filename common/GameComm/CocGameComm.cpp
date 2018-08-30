#include "CocGameComm.h"
#include "jsoncmd.hpp"
#include "include/icqsocket.h"
#include "include/socketaddress.h"
#include "tlcrypto/tlcrypto.h"
#include "GameStruct/CocStruct.h"

#ifdef WIN32
#include "include/log.h"
#endif
#define  GAME_TM	10
#define DES_KEY		"tlcrytpo"

static uint32 g_lastTime = 0; 



CTLMoblieSocket::CTLMoblieSocket()
{
	UnRegistCallBack();

	m_lastKeepAliveReply = time(NULL);

	m_lastCheckSendQueue = time(NULL);
	m_lastKeepAlive = time(NULL);
	m_uin = 0;
	m_roomid = 0;
	m_roomid = 0;
	m_uin = 0;
	m_timer = 0;
	m_channelStatus = 0;
	memset(m_confuserllist.onMicUser,0,sizeof(m_confuserllist.onMicUser));
	memset(micSeqBuf, 0, sizeof(micSeqBuf));
	m_interval = GAME_TM;
	Initialize();
	LOG(0)("||CTLMoblieSocket(): %p ============================== ||\n", this);
}


CTLMoblieSocket::~CTLMoblieSocket()
{
	LOG(0)("||~CTLMoblieSocket()%p BEGIN============================== ||\n",this);
	ClearSendQueue();
	LOG(0)("||~CTLMoblieSocket()%p END ============================== ||\n",this);
}
void CTLMoblieSocket::OnDisConnect(int nState)
{
	LOG(0)("%s nstate:%d %p\n", __FUNCTION__, nState, m_funOnDisConnect);
	if(m_funOnDisConnect)
	{
		m_funOnDisConnect(nState);
	}
}
void CTLMoblieSocket::OnConnect(int nState)
{
	LOG(0)("%s nstate:%d %p\n", __FUNCTION__, nState, m_funOnDisConnect);
	m_lastKeepAliveReply = time(NULL); 
	ClearSendQueue();

	if(m_funOnConnect)
	{
		m_funOnConnect(nState);
	}
}
void CTLMoblieSocket::ClearSendQueue()
{
	MutexObject lock(&m_mutextSend);
	while (sendQueue.size()) 
	{
		OutPacketEx *p = (OutPacketEx *) sendQueue.front();
		sendQueue.pop_front();
		delete p;
	}

}


int CTLMoblieSocket::SendJsonData(void* pData, int nLen)
{
	Json::Reader jsReader;
	Json::Value jsValue;
	uint32 curr = time(NULL);
	int rtn = 0;
	if(jsReader.parse((const char*)pData, (const char*)pData+nLen, jsValue))
	{
		Json::FastWriter testWirter;
		uint16 cmd = jsValue[JSKEY_CMD].asInt();
		LOG(1)("CTLMoblieSocket::SendJsonData %s ||time:%u cmd:%d\n", testWirter.write(jsValue).c_str(), curr, cmd);
	
		switch(cmd)
		{
		case CocCmdType::COC_USER_LOGIN:
			rtn = SendUserLogin(jsValue);
			break;
		case CocCmdType::COC_USER_LOGOUT:
			rtn = SendLogoutRoom(jsValue);
			break;
		case CocCmdType::COC_SCENE_BUILD:
			rtn = SendCreatBuilding(jsValue);
			break;
		case CocCmdType::COC_GET_SERVER_PUSH_LIST:
			rtn = sendGetServetPushList(jsValue);
			break;
		case CocCmdType::COC_SCENE_UPDATE_LEVEL:
			rtn = SendUpdateBuilding(jsValue);
			break;
		case CocCmdType::COC_SCENE_MOVE:
			rtn = SendMoveBuilding(jsValue);
			break;
		case CocCmdType::COC_SCENE_REMOVE:
			rtn = SendRemoveBuilding(jsValue);
			break;
		case  CocCmdType::COC_CANCEL_REMOVE:
			rtn = SendCancelRemoveBuilding(jsValue);
			break;
		case CocCmdType::COC_SCENE_RESOURCE_COLLECT:
			rtn = SendCollectResources(jsValue);
			break;
		case CocCmdType::COC_TRAIN_SOLDIER:
			rtn = SendTrainSoldier(jsValue);
			break;
		case CocCmdType::COC_PRODUCE_MAGIC:
			rtn = SendProduceMagic(jsValue);
			break;
		case CocCmdType::COC_CANCEL_TRAIN_SOLDIER:
			rtn = SendCancelTrainSoldier(jsValue);
			break;
		case CocCmdType::COC_UPDATE_SOLDIER_LEVEL:
			rtn = SendUpdateSoldierLevel(jsValue);
		case CocCmdType::COC_SCENE_INFO:
			break;
		case CocCmdType::COC_SCENE_CHECK_UPDATE:
			break;
		case CocCmdType::COC_COMPLETEDIMMEDIATELY:
			rtn = SendCompletedImmediately(jsValue);
			break;
		case CocCmdType::COC_ACHIEVEMENT_APPLY:
			rtn = SendApplyToGetAchievement(jsValue);
			break;
		case CocCmdType::COC_MAIL_PRIZE_APPLY:
			rtn = SendApplyToGetMailPrize(jsValue);
			break;
		case CocCmdType::COC_DELETE_MAILMSG_LIST:
			rtn = SendDeleteMailMsg(jsValue);
			break;
		case CocCmdType::COC_SPEED_UP:
			rtn = SendSpeedUp(jsValue);
			break;
		case CocCmdType::COC_PICKET_SOLDIERS:
			rtn = SendSoldiers(jsValue);
			break;
		case CocCmdType::COC_WALL_MUTI_MOVE:
			rtn = SendWallMutiMove(jsValue);
			break;
		case CocCmdType::COC_WALL_MUTI_UPDATE:
			rtn = SendWallMutiUpdate(jsValue);
			break;
		case  CocCmdType::COC_MAP_COPY:
			rtn = SendMapCopy(jsValue);
			break;
		case CocCmdType::COC_MAP_EDITE:
			rtn = SendMapEdite(jsValue);
			break;
		case  CocCmdType::COC_REPORT_BUILD_CHALLENGE:
		case  CocCmdType::COC_REPORT_BUILD:
			rtn = SendBuildingReport(jsValue);
			break;
		case CocCmdType::COC_REPORT_RESOURCE:
			rtn = SendResourceReport(jsValue);
			break;
		case CocCmdType::COC_TERMINAT_CHALLENGE:
		case CocCmdType::COC_TERMINAT_ATTACK:
			rtn = SendTerminatAttack(jsValue);
			break;
		case CocCmdType::COC_TERMINAT_TOLLGATE:
			rtn = SendTerminatTollGate(jsValue);
			break;
		case  CocCmdType::COC_GET_SOLDIER_RECORD:
			rtn = SendGetSoldierRecord(jsValue);
			break;
		case CocCmdType::COC_RECOVER_TRAP:
			rtn = SendRecoverTrap(jsValue);
			break;
		case CocCmdType::COC_CANCEL_BUILD:
			rtn = SendCancelBuilding(jsValue);
			break;
		case CocCmdType::COC_BUY_ORNAMENT:
			rtn = SendBuyOrnament(jsValue);
			break;
		case CocCmdType::COC_SELL_ORNAMENT:
			rtn = SendSellOrnament(jsValue);
			break;
		case CocCmdType::COC_MACHING_USER:
			rtn = SendMachingUser(jsValue);
			break;
		case  CocCmdType::COC_CANCEL_MACHING:
			rtn = SendCancelMaching(jsValue);
			break;
		case CocCmdType::COC_GEMSTONE_BUY_RESOURCE:
			rtn = SendGemstoneBuyResource(jsValue);
			break;

		case CocCmdType::COC_GET_CHALLENGE_ATTACK_INFO:
		case CocCmdType::COC_GET_ATTACK_HISTORY_MAP:
		case CocCmdType::COC_GET_CLAN_CHALLENGE_ATTACK_INFO:
			rtn = SendGetAttackHistoryMap(jsValue);
			break;
		case CocCmdType::COC_SET_NEW_USER_STEP:
			rtn = SendSetNewUserStep(jsValue);
			break;
		case CocCmdType::COC_SET_USER_NAME:
			rtn = SendSetUserName(jsValue);
			break;
		case CocCmdType::COC_CHANGE_USER_NAME:
			rtn = SendChangeUserName(jsValue);
			break;
		case CocCmdType::COC_GET_USER_MAP_DATA:
		case CocCmdType::COC_GET_USER_MAP_DATA_VISIT:
			rtn = SendGetUserMapData(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_UPDATE_SOLDIER:
		case CocCmdType::COC_GET_USER_UPDATE_SOLDIER_VISIT:
			rtn = SendGetUpdateSoldierInfo(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_WORKER_LIST:
		case CocCmdType::COC_GET_USER_WORKER_LIST_VISIT:
			rtn = sendGetWorkerList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_PRODUCE_LIST:
		case CocCmdType::COC_GET_USER_PRODUCE_LIST_VISIT:
			rtn = sendGetProduceList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_OWN_SOLDIER_LIST:
		case CocCmdType::COC_GET_USER_OWN_SOLDIER_LIST_VISIT:
			rtn = sendGetSoldierList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_SOLDIER_LEVEL:
		case CocCmdType::COC_GET_USER_SOLDIER_LEVEL_VISIT:
			rtn = sendGetSoldierLevelList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_SPPEDUP_INFO:
			rtn = sendGetSpeedUpList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_ACHIEVEMEN:
			rtn = sendAchievementList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_ATTACK_HISTORY_LIST:
			rtn = sendAttackHistoryList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_TOLLGATE_lIST:
			rtn = sendTollGateHistoryList(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_TOLLGATE_MAP:
			rtn = sendGetTollGateMapInfo(jsValue);
			break;	
		case CocCmdType::COC_GET_USER_INFO_DATA:
			rtn = SendGetUserInfoData(jsValue);
			break;	
		case CocCmdType::COC_USER_REVENGE:
			rtn = SendUserRevenge(jsValue);
			break;
		case CocCmdType::COC_MACHING_USER_WITH_ID:
			rtn = SendMachingUserWithId(jsValue);
			break;
		case CocCmdType::COC_GAME_CHALLENGE:
			rtn = SendGameChallenge(jsValue);
			break;
		case CocCmdType::COC_GET_CHALLENGE_RANKING_LIST:
			rtn = SendGetChallengeRankingList(jsValue);
			break;
		case CocCmdType::COC_GET_RANKING_LIST:
			rtn = SendGetRankList(jsValue);
			break;
		case CocCmdType::COC_SELECT_PLATFORM_MONEY:
		case CocCmdType::COC_SELECT_STATION_MONEY:
			rtn = SendSelectStationMoney(jsValue);
			break;
		case CocCmdType::COC_PLATFORM_MONEY_BUY_GEMSTONE:
			rtn = SendPlatformMoneyBuyGemston(jsValue);
			break;
		case CocCmdType::COC_STATION_MONEY_BUY_RESOURCE:
			rtn = SendStationMoneyBuyResource(jsValue);
			break;
		case  CocCmdType::COC_GET_SHIELD_LIST:
			rtn = SendGetShieldCoolTimeLeftList(jsValue);
			break;
		case  CocCmdType::COC_GET_MAILMSG_LIST:
			rtn = SendGetMailMsgList(jsValue);
			break;
		case  CocCmdType::COC_BUY_SHILED:
			rtn = SendBuyShield(jsValue);
			break;
		case  CocCmdType::COC_GET_ONLINEPRIZE_INFO:
			rtn = SendGetOnlinePrizeList(jsValue);
			break;
		case  CocCmdType::COC_GET_CURR_ONLINEPRIZE:
			rtn = SendGetCurrOnlinePrize(jsValue);
			break;
		case  CocCmdType::COC_GET_DAY_ACTIVE_TASK_PRIZE_INFO:
			rtn = SendGetDayActiveTaskPrizeInfo(jsValue);
			break;
		case  CocCmdType::COC_GET_DAY_ACTIVE_TASK_lIST:
			rtn = SendGetDayActiveTaskList(jsValue);
			break;
		case  CocCmdType::COC_GET_CURR_DAY_ACTIVE_PRIZE:
			rtn = SendGetCurrDayActivePrize(jsValue);
			break;
		case CocCmdType::COC_ADD_WINNER_MSG:
			rtn = SendWinnerMsg(jsValue);
			break;
		case CocCmdType::COC_BUY_GEMSTONE_INFO:
			rtn = ReqBuyGemstoneInfo(jsValue);
			break;
		case CocCmdType::COC_FINISH_FIRST_CHARGE:
			rtn = SendFinishFistCharge(jsValue);
			break;
		case CocCmdType::COC_BROTHERHOOD_INFO:
			rtn = SendBrotherhoodReq(jsValue);
			break;
		case CocCmdType::COC_BROTHERLSIT_INFO:
			rtn = SendBrotherListReq(jsValue);
			break;
		case CocCmdType::COC_BROTHER_TASK_REWARD:
			rtn = SendBrotherTaskReward(jsValue);
			break;
		case CocCmdType::COC_BIND_BROTHER:
			rtn = SendBindBrother(jsValue);
			break;
		case CocCmdType::COC_CLANLIST_INFO:
			rtn = SendClanListInfoReq(jsValue);
			break;

		case CocCmdType::COC_CLANINFO://no need break;
		case CocCmdType::COC_CLAN_ASKFOR_LIST:
			rtn = SendClanInfoReq(jsValue);
			break;

		case CocCmdType::COC_CLAN_OPERATE:
			rtn = SendClanOperate(jsValue);
			break;
		case CocCmdType::COC_CLAN_KICK_USER:
			rtn = SendClanLeave(jsValue);
			break;
		case CocCmdType::COC_CLAN_CREATE:
			rtn = SendCreateClan(jsValue);
			break;
		case CocCmdType::COC_CLAN_DELETE:
			rtn = SendDeleteClan(jsValue);
			break;
		case CocCmdType::COC_CLAN_MODIFY:
			rtn = SendModifyClanInfo(jsValue);
			break;
		case CocCmdType::COC_CLAN_SEARCH:
			rtn = SendSearchClan(jsValue);
			break;
		case CocCmdType::COC_CLAN_CHANGE_RANK:
			rtn = SendChangeRank(jsValue);
			break;
		case CocCmdType::COC_CLAN_CONFIRM_REQ:
			rtn = SendClanConfimReq(jsValue);
			break;
		case CocCmdType::COC_CLAN_PID_ORDER:
			rtn = SendPidClanList(jsValue);
			break;
		case CocCmdType::COC_CLAN_DONATE:
			rtn = SendClanDonate(jsValue);
			break;
		case CocCmdType::COC_CLAN_RECRUIT:
			rtn = SendClanRecruit(jsValue);
			break;
		case CocCmdType::COC_CLAN_DONATE_INFO:
			rtn = OnSendClanDonateTimeInfoNotify(jsValue);
			break;
		case CocCmdType::COC_CLAN_WARBASTION_INFO:
			rtn = SendClanWarBastionInfo(jsValue);
			break;
		case CocCmdType::COC_CLAN_ALLOT:
			SendClanAllotToUserReq(jsValue);
			break;
		default:
			LOG(4)("CTLMoblieSocket::ERRO cmd:%d\n\n", cmd);
			break;
		}
	}
	else
	{
		char buff[2048] = {0};
#ifdef WIN32
		sprintf_s(buff, sizeof(buff -1), "%s\n",pData, nLen);
#else
		snprintf(buff, sizeof(buff -1), "%s\n",pData, nLen);
#endif
		LOG(0)("%s invalid send data: %s\n", __FUNCTION__, buff);
	}
	return rtn;
}

void CTLMoblieSocket::RegistCallBack(ONRECV funOnRecv, ONSEND funOnSend, ONCONNECT funOnConnect, ONDISCONNECT funOnDisConnect, ONTIMER funOnTimer)
{
	m_funOnRecv = funOnRecv;
	//应用数据转换成到协议数据
	m_funOnSend = funOnSend;;
	m_funOnDisConnect = funOnDisConnect;
	m_funOnConnect = funOnConnect;
	m_funOnTimer = funOnTimer;
}

void CTLMoblieSocket::UnRegistCallBack()
{
	m_funOnRecv = NULL;
	//应用数据转换成到协议数据
	m_funOnSend = NULL;;
	m_funOnDisConnect = NULL;
	m_funOnConnect = NULL;
	m_funOnTimer = NULL;
}





//初始化Connection
void CTLMoblieSocket::Initialize()
{
	m_CurrentSeq = 0;//初始包序号为0，第一包应该为1
	memset(m_window, 0, sizeof(m_window));
	srand((unsigned)time( NULL ));
	InitSessionID();
	m_uin = INVALID_USER_ID;
	m_ConnectionStatus = CHAT_OUTOF_ROOM;
	m_ver =  MB_CHAT_VER_CURR;
	LOG(0)("%s sessionId:%u\n", __FUNCTION__, m_SessionID);
}

void CTLMoblieSocket::InitSessionID()
{
	m_SessionID = (rand() & 0x7fffffff) + 1;
}


int CTLMoblieSocket::SendPacket(bool needAck,OutPacketEx *p)
{
	int seq = p->seq;
	p->attempts = 0;
	p->expire = 0;
	if(CocCmdType::COC_KEEP_ALIVE == p->cmd)
	{
		sendDirect(p);
	}

	if(needAck)
	{
		MutexObject lock(&m_mutextSend);
		sendQueue.push_back(p);
	}

	CheckSendPackerInQueue();
	return seq;
}

int CTLMoblieSocket::sendDirect(OutPacketEx *out)
{
	LOG(0)("ChatChannel::%s,cmd = %d ,times:%d timeSpan:%u\n",__FUNCTION__ ,out->cmd, out->attempts, TIME_DIFF_U(talk_base::TimeStamp(), out->expire));
	return  SendData((void*)out->GetData(), out->getdatalen());
}

bool CTLMoblieSocket::CheckSendPackerInQueue()
{ 
	bool flag = true;
	MB_CHAT_ERROR_CODE  erroCode;
	OutPacketEx *p = NULL;
	{
		MutexObject lock(&m_mutextSend);
		uint32 curr = talk_base::TimeStamp();
		int size = sendQueue.size();
		if (size) 
		{
			p = (OutPacketEx *) sendQueue.front();
			uint32 remainTime = TIME_DIFF_U(curr, p->expire);
			if (remainTime > PACKET_SEND_KEY_TIMEOUT)
			{
				p->expire = curr;
				p->attempts ++;
				if(sendDirect(p) == -1) 
				{
					LOG(0)("ChatChannel::SendPacket ERRO ,cmd = %d ,remote ip = %s sid:%u\n",p->cmd,HIP2CHAR(GetServerIp()), m_SessionID);
					erroCode = E_OUT_OF_CONNECTION;
					flag = false;	
				}
			}

			if(p->attempts >= T_KEEPALIVE_TIMEOUT_TRY_TIMES)
			{
				erroCode = E_TIMEOUT;
				LOG(0)("%s queue size:%d sid:%u\n", __FUNCTION__, size, m_SessionID);
			}
		}
	}
	
	if(false == flag || (p && T_KEEPALIVE_TIMEOUT_TRY_TIMES == p->attempts))
	{
		CTLSendResult sendRet;
		std::string strRet = sendRet(*p, erroCode);

		if(m_funOnRecv)
		{
			m_funOnRecv(strRet.c_str(), strRet.length());
		}
	}
	return flag;
}

bool CTLMoblieSocket::OnRecvAck(uint32 seq)
{
	list<OutPacketEx *>::iterator iter;
	OutPacketEx *p = NULL;
	{
		MutexObject lock(&m_mutextSend);
		for (iter = sendQueue.begin(); iter != sendQueue.end(); iter++)
		{
			if ((*iter)->seq == seq) 
			{
				p = *iter;
				sendQueue.erase(iter);
				break;
			}
		}
	}

	if (p)
	{
		CTLSendResult sendRet;
		string strRet = sendRet(*p, E_SUCCESS);
		int cmd = p->cmd;
		delete p;
		if(cmd != CocCmdType::COC_KEEP_ALIVE)
		{
			if(m_funOnRecv)
			{
				m_funOnRecv(strRet.c_str(), strRet.length());	
			}
		}	
	}
	else
	{
		LOG(0)("%s seq:%d no packet", __FUNCTION__, seq);
		return false;
	}
	return true;
}
bool CTLMoblieSocket::IsMySelf(uint32 pid, uint32 uin)
{
	if (0 == pid)
	{
		return false;
	}
	return uin == m_uin && m_pid == pid;
}
int CTLMoblieSocket::SendKeepAlive()
{
	int flag = 0;
	OutPacketEx* p = createPacket_Head(false,CocCmdType::COC_KEEP_ALIVE);
	if(p)
	{
		uint8 lost = 0;
		uint16 ackTime = 0;
		uint32 mediaSvrIP = 0;
		uint32 sendLost = 0;
		flag =  SendPacket(false,p);
		LOG(3)("ChatChannel::SendKeepAlive sid:%u flag:%d\n", m_SessionID, flag);
		delete p;
	}
	return flag;
}

int CTLMoblieSocket::SendAck(uint16 seq)
{
	OutPacketEx out;
	CreatePacketHead(out, CocCmdType::COC_ACK, seq);
	out.packetid = "0x00";
	return sendDirect(&out);

}





void CTLMoblieSocket::OnRecv(const char* pData, int nLen)
{
	if(nLen > 0)
	{
		InPacketEx in;
		in.setdata(pData, nLen);
		OnPacketReceived(in);
	}
}



//定期重发相关报文及检测连接状态,true表示通道有问题
bool CTLMoblieSocket::checkTimeOut()
{
	uint32 now = time(NULL);
	//３分钟未收到keepalive报文，则报退出。
	if (m_lastKeepAliveReply + T_PACKET_SENT_TIMEOUT < now)
	{
		LOG(0)("%s TL_NET_TIMEOUT sid:%u\n", __FUNCTION__ , m_SessionID);
		CTLSendResult sendRet;
		OutPacketEx p;
		p.packetid = "0x00";
		MB_CHAT_ERROR_CODE  erroCode ;
		erroCode = E_TIMEOUT;
		std::string strRet = sendRet(p, erroCode);
		if(m_funOnRecv)
		{
			m_funOnRecv(strRet.c_str(), strRet.length());
		}

		return true;
	}
	return false;
}

void CTLMoblieSocket::OnTimer()
{
	m_timer = (m_timer+1)%TIMER_INTERVAL;
	if(m_timer % T_SEND_QUEUE_CHECK_INTERVAL == 0)
	{
		CheckSendPackerInQueue();
	}

	if(m_timer % T_KEEPALIVE_INTERVAL == 0)
	{	
		SendKeepAlive();
	}
	checkTimeOut();
	if(m_funOnTimer)
		m_funOnTimer();
}


bool CTLMoblieSocket::ValidatePacket(InPacketEx &in)
{
	if (in.getdatalen() < sizeof(UDP_SRV_HDR))
		return false;

	if (in.m_head.ver != m_ver)
	{
		//回调版本号错误
		//m_pChannelConn->OnRoomMessage(CTLMoblieSocket::E_WRONG_CHAT_VER);
		LOG(0)("ChatChannel::OnPacketReceived in.m_head.ver != m_Ver recv from %s:%d \n", HIP2CHAR(GetServerIp()), GetServerPort());
		return false;
	}

	// The session ID must match, otherwise, this is a cracking packet
	if (in.m_head.sid != m_SessionID)
	{
		LOG(0)("ChatChannel::OnPacketReceived packedt is discarded ,paceket cmd = 0x%04x,sessionid is not eqaul in.m_head.sid = %d,m_sessionid = %d\r\n",in.m_head.cmd,in.m_head.sid,m_SessionID);
		return false;
	}


	uint16 ackseq = in.m_head.cc;
	uint16 seq = in.m_head.seq;

	//对所有Session ID正确的报文进行无条件重置KeepAlive时间
	if (m_channelStatus != CHANNEL_CONNECTED)
		m_channelStatus = CHANNEL_CONNECTED;

	m_lastKeepAliveReply = time(NULL);

	//对ack报文进行ack处理，并对keepalive的附加信息进行处理
	if (ackseq)
		OnRecvAck(ackseq); 

	if(in.m_head.cmd == CocCmdType::COC_ACK)
		return false;

	if(in.m_head.cmd == CocCmdType::COC_KEEP_ALIVE)
	{
		return true;
	}


	if (seq)
		SendAck(seq);

	return setWindow(seq);
}

//处理接收的报文
bool CTLMoblieSocket::OnPacketReceived(InPacketEx &in)
{
	in.ResolvHead();	
	uint32 curr = time(NULL);
	uint16 cmd = in.m_head.cmd;
	LOG(2)("CTLMoblieSocket::OnPacketReceived cmd = %d cc:%d seq:%d uin:%u sid:%u\r\n", cmd, in.m_head.cc, in.m_head.seq, in.m_head.uin, in.m_head.sid);
	if(!ValidatePacket(in) && CocCmdType::COC_ACK != cmd)
	{
		LOG(0)("ChatCmdChannel::HandlePakcet ValidatePacket erro cmd:%d cc:%u seq:%d uin:%u  sid:%u \n", cmd, in.m_head.cc, in.m_head.seq, in.m_head.uin, in.m_head.sid);
		return false;
	}
	switch (cmd) 
	{
	case CocCmdType::COC_USER_LOGIN:
	case CocCmdType::COC_GET_USER_INFO_DATA:
		OnRecvLoginRoomReply(in, cmd);
		break;
	case CocCmdType::COC_KEEP_ALIVE:
		OnRecvKeepalive(in);
		break;
	case CocCmdType::COC_GET_USER_MAP_DATA:
		OnRecvUserMapData(in, cmd);
		break;
	case CocCmdType::COC_GET_USER_SPPEDUP_INFO:
		OnRecvSpeedUpList(in, cmd);
		break;
	case CocCmdType::COC_SCENE_BUILD:
		OnCreatBuilding(in);
		break;
	case CocCmdType::COC_SCENE_MOVE:
		OnRecvMoveBuilding(in);
		break;
	case CocCmdType::COC_SCENE_REMOVE:
		OnRecvReMoveBuilding(in);
		break;
	case CocCmdType::COC_SCENE_RESOURCE_COLLECT:
		OnRecvCollectResources(in);
		break;
	case  CocCmdType::COC_SCENE_UPDATE_LEVEL:
		OnRecvUpDateBuilding(in);
		break;
	case CocCmdType::COC_TRAIN_SOLDIER:
		OnRecvTrainSoldier(in);
		break;
	case CocCmdType::COC_FIND_USER_MAP:
		OnRecvFindUserMap(in);
		break;
	case CocCmdType::COC_MACHING_USER:
	case CocCmdType::COC_USER_REVENGE:
	case CocCmdType::COC_MACHING_USER_WITH_ID:
	case CocCmdType::COC_GAME_CHALLENGE:
		OnRecvMachingUserMap(in, cmd);
		break;
	case CocCmdType::COC_SERVER_ACHIEVEMENT_COMPLETE:
		OnRecvAchievementComplete(in);
		break;
	case CocCmdType::COC_PUSH_SOLDIER_LIST:
	case CocCmdType::COC_GET_USER_OWN_SOLDIER_LIST:
		OnRecvCanUseSoldier(in, cmd);
		break;
	case CocCmdType::COC_GET_RANKING_LIST:
		OnRecvRankList(in, cmd);
		break;
	case  CocCmdType::COC_GET_USER_WORKER_LIST:
		OnRecvWorkingList(in, cmd);
		break;
	case  CocCmdType::COC_SERVER_NOTIFY_MSG:
		OnRecvGameNotifyMessage(in);
		break;
	case CocCmdType::COC_GET_USER_ACHIEVEMEN:
		OnRecvAchievementInfo(in, cmd);
		break;
	case  CocCmdType::COC_GET_SOLDIER_RECORD:
		OnRecvSoldierRecord(in);
		break;
	case  CocCmdType::COC_GET_USER_PRODUCE_LIST:
		OnRecvSvrPushProduceList(in, cmd);
		break;
	case CocCmdType::COC_SVR_USER_INFO:
		OnRecvUserInfo(in, cmd);
		break;
	case CocCmdType::COC_GET_USER_SOLDIER_LEVEL:
		OnRecvSoldierLevel(in, cmd);
		break;
	case  CocCmdType::COC_GET_USER_UPDATE_SOLDIER:
		OnRecvSoldierUpdate(in, cmd);
		break;
	case  CocCmdType::COC_GET_USER_ATTACK_HISTORY_LIST:
	case  CocCmdType::COC_SERVER_USER_ATTACK_HISTORY_LIST:
		OnRecvAttackHistory(in, cmd);
		break;
	case  CocCmdType::COC_GET_ATTACK_HISTORY_MAP:
	case CocCmdType::COC_GET_CHALLENGE_ATTACK_INFO:
		case CocCmdType::COC_GET_CLAN_CHALLENGE_ATTACK_INFO:
		OnRecvAttackHistoryMap(in, cmd);
		break;
	case  CocCmdType::COC_GET_USER_TOLLGATE_lIST:
	case  CocCmdType::COC_SERVER_PUSH_LAST_TOLLGATE:
		OnRecvTollInfoList(in, cmd);
		break;
	case  CocCmdType::COC_GET_USER_TOLLGATE_MAP:
		OnRecvTollGateMap(in, cmd);
		break;
	case CocCmdType::COC_GET_USER_DEFEND_ONATTACK_INFO:
		OnRecvDefendUserOnAttackInfo(in, cmd);
		break;
	case CocCmdType::COC_GET_OFFEND_SOLDIER_INFO:
		OnRecvOffendUserSoldierInfo(in, cmd);
		break;
	case CocCmdType::COC_SELECT_PLATFORM_MONEY:
		OnRecvSelectPlatformMoney(in, cmd);
		break;
	case CocCmdType::COC_SELECT_STATION_MONEY:
		OnRecvSelectStationMoney(in, cmd);
		break;
	case CocCmdType::COC_CHANGE_USER_NAME:
		OnRecvChangeUserName(in, cmd);
		break;
	case CocCmdType::COC_GET_SHIELD_LIST:
		OnRecvShieldCoolTimeLeftList(in, cmd);
		break;
	case CocCmdType::COC_SERVER_SYS_MSG:
		OnRecvSystemMsg(in, cmd);
		break;
	case CocCmdType::COC_SERVER_MAIL_MSG:
		OnRecvMailMsg(in, cmd);
		break;
	case CocCmdType::COC_FORCE_OFFLINE:
		OnRecvForceOffLine(in, cmd);
		break;
	case CocCmdType::COC_GET_ONLINEPRIZE_INFO:
		OnRecvOnlinePrizeListInfo(in, cmd);
		break;
	case CocCmdType::COC_PUSH_ORNAMENT_UP_PERCENT:
		OnRecvOrnamentUpPercent(in, cmd);
		break;
	case CocCmdType::COC_GET_DAY_ACTIVE_TASK_lIST:
		OnRecvDayActiveTaskList(in, cmd);
		break;
	case CocCmdType::COC_GET_DAY_ACTIVE_TASK_PRIZE_INFO:
		OnRecvDayActiveTaskPrizeInfo(in, cmd);
		break;
	case CocCmdType::COC_GET_CHALLENGE_RANKING_LIST:
		OnRecvChallengeRankingList(in, cmd);
		break;
	case  CocCmdType::COC_SERVER_CHALLENGE_DESCRIBE:
		OnRecvChallengeDescribe(in, cmd);
		break;
	case CocCmdType::COC_ADD_WINNER_MSG:
		OnRecvWinnerMsg(in, cmd);
		break;
	case CocCmdType::COC_BUY_GEMSTONE_INFO:
		OnRecvBuyGemstoneInfo(in, cmd);
		break;
	case CocCmdType::COC_CHARE_GEMSTONE:
		OnRecvChargeGemstone(in, cmd);
		break;
	case CocCmdType::COC_FIRST_CHARGE_GEMSTONE:
		OnRecvFirstChargeNotify(in, cmd);
		break;
	case CocCmdType::COC_FINISH_FIRST_CHARGE:
		OnRecvFinishFisttChargeNotify(in, cmd);
		break;
	case CocCmdType::COC_BROTHERHOOD_INFO:
		OnRecvBrotherhood(in, cmd);
		break;
	case CocCmdType::COC_BROTHERLSIT_INFO:
		OnRecvBrotherList(in, cmd);
		break;
	case CocCmdType::COC_BROTHER_TASK_REWARD:
		OnRecvBrotheTaskReward(in, cmd);
		break;
	case CocCmdType::COC_BIND_BROTHER:
		OnRecvBindBrotherResult(in, cmd);
		break;
	case CocCmdType::COC_CLAN_MODIFY:
		OnRecvModifyClanInfoReplay(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_CHANGED:
		OnRecvUpdateClanInfo(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_JOIN:
		OnRecvClanJon(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_LEAVE:
		OnRecvClanLeave(in, cmd);
		break;
	case CocCmdType::COC_CLAN_KICK_USER:
		OnRecvClanResult(in, cmd);
		break;
	case CocCmdType::COC_CLANINFO:
		OnRecvClanInfo(in, cmd);
		break;
	case CocCmdType::COC_CLANLIST_INFO:
	case CocCmdType::COC_CLAN_SEARCH://no need break
	case CocCmdType::COC_CLAN_PID_ORDER://no need break
		OnRecvClanList(in, cmd);
		break;
	case CocCmdType::COC_CLAN_CREATE://no need break;
	case CocCmdType::COC_CLAN_DELETE:
		OnRecvCreateDelClan(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLANREQ_ADD:
		OnRecvClanReqAdd(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLANREQ_DEL:
		OnRecvClanReqDel(in, cmd);
		break;
	case CocCmdType::COC_CLAN_ASKFOR_LIST:
		OnRecvClanReqAllList(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_UPDATELEVEL:
		OnRecvClanUpdateLevel(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_MEMLIST:
		OnRecvClanMemList(in, cmd);
		break;
	case CocCmdType::COC_CLAN_CHANGE_RANK:
		OnRecvClanChangeRankResult(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_CHANGERANK:
		OnRecvClanChangeNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_STATEACHE:
		OnRecvClanStateCache(in, cmd);
		break;
	case CocCmdType::COC_CLAN_OPERATE:
		OnRecvClanOperate(in, cmd);
		break;
	case CocCmdType::COC_CLAN_CONFIRM_REQ:
		OnRecvClanConfimReq(in, cmd);
		break;
	case CocCmdType::COC_CLAN_DONATE:
		OnRecvClanDonate(in,cmd);
		break;
	case CocCmdType::COC_CLAN_RECRUIT:
		OnRecvClanRecruit(in,cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_DONATE:
		OnRecvClanDonateNotify(in,cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_DONATE_INFO:
		OnRecvClanDonateTimeInfoNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_LAST_WINPOINT_RANK:
		OnRecvClanLastWimpointRankNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CUR_WINPOINT_RANK:
		OnRecvClanCurWimpointRankNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_WINPIONT:
		OnRecvClanTotalWinPointNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_AWARD_LIST:
		OnRecvClanAwardListNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_AWARD_ALLOT:
		OnRecvClanAwardAllotNotify(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_RANKAWARD_MAIL:
		OnRecvClanRankAwardMailNotify(in, cmd);
		break;
	case CocCmdType::COC_CLAN_WARBASTION_INFO:
		OnRecvClanWarBastionInfo(in, cmd);
		break;
	case CocCmdType::COC_CLAN_ALLOT:
		OnRecvClanAllotToUserResp(in, cmd);
		break;
	case CocCmdType::COC_SVR_CLAN_ATTACK_HISTORY_LIST:
		OnRecvClanAttackHistoryNotify(in, cmd);
		break;
	default:
		if (CocCmdType::COC_ACK != cmd)
		{
			LOG(4)("CTLMoblieSocket::ERRO cmd:%d\n\n", cmd);
		}
	}
	return true;

}

bool CTLMoblieSocket::setWindow(uint16 seq)
{
	if (m_window[seq])
		return false;
	m_window[seq] = 1;
	uint16 preSeq = 0;
	if(seq <64)
		preSeq =((1<<16)-64+seq);
	else
		preSeq-=64;
	m_window[preSeq] = 0;
	return true;

}

//生成对服务器报文的应答包
OutPacketEx * CTLMoblieSocket::createPacket_ACK(uint16 seq)
{
	try
	{
		OutPacketEx *p = new OutPacketEx();
		p->cmd = CocCmdType::COC_ACK;
		p->seq = seq;
		*p << (uint16) m_ver << (uint32)m_roomid;
		*p << (uint32)m_uin << (uint32)m_SessionID << (uint16)CocCmdType::COC_ACK << (uint16)seq;
		*p << (uint16) 0;		// Checkcode will be calculated later
		return p;	
	}
	catch(...)
	{
		return NULL;
	}
}

//生成发往服务器报文的包头
OutPacketEx * CTLMoblieSocket::createPacket_Head(bool needAck,uint16 cmd, const char* packetid)
{
	try
	{
		OutPacketEx *p = new OutPacketEx();
		if (p)
		{
			p->cmd = cmd;
			if(needAck)
			{
				p->seq = ++m_CurrentSeq;	//该包需要确认
				if (0 == p->seq)
				{
					p->seq = ++m_CurrentSeq;	//该包需要确认
				}
			}
			else
			{
				p->seq = 0;					//该包不需要确认
			}
			*p << (uint16)m_ver << (uint32)m_roomid;
			*p << (uint32)m_uin << (uint32)m_SessionID << (uint16)cmd << (uint16)p->seq;
			*p << (uint16) 0;		// Checkcode will be calculated later
		}
		return p;	
	}
	catch(...)
	{
		return NULL;
	}
}

void CTLMoblieSocket::CreatePacketHead(OutPacketEx &out,uint16 cmd,uint16 seq /*= 0*/)
{
	out.cmd = cmd;
	out.seq = seq;
	out << (uint16)m_ver << (uint32)m_roomid;
	out << (uint32)m_uin << (uint32)m_SessionID << (uint16)cmd << (uint16)0;
	out << (uint16) seq;		// Checkcode will be calculated later
}


void CTLMoblieSocket::OnRecvKeepalive(InPacketEx &in)
{
	if(CHAT_OUTOF_ROOM == m_ConnectionStatus) return;

	// 	CTLKeepAlive keepAlive;
	// 	std::string strRet = keepAlive(in);
	// 
	// 	if(m_funOnRecv)
	// 		m_funOnRecv(strRet.c_str(),  strRet.length());
}
uint8 CTLMoblieSocket::SetTimeoutInteval(uint8 inteval)
{
	uint8 lastval = m_interval;
	m_interval = inteval;
	return lastval;
}

int CTLMoblieSocket::SendUserLogin(Json::Value& val)
{
	m_uin = val[JSKEY_UIN].asUInt();
	m_pid = val[JSKEY_PID].asUInt();
	m_roomid = val[JSKEY_ROOMID].asUInt();
	std::string userPass = val[JSKEY_PASS].asString();
	std::string roomPass = val[JSKEY_ROOM_PASS].asString();
	uint64 macaddr = StringToUll(val[JSKEY_MACADDR].asString().c_str(), 10);
	uint8 m_netType = val[JSKEY_NET_TYPE].asUInt();
	uint8 spaceData = val[JSKEY_DEV_TYPE].asUInt();
	char buf[256] = {0};
	sprintf(buf, "%u", m_SessionID^ m_uin);
	std::string userPassCheck = CTLCrypto::DesEncrptyWithBase64(buf, strlen(buf), DES_KEY, userPass.c_str());
	std::string devNum = val[JSKEY_DEVNUM].asString();
	std::string cocver = val[JSKEY_COCVER].asString();
	uint8 bBindLogin =  val[JSKEY_BINDLOGIN].asUInt();
	uint8 passType = val[JSKEY_PASSTYPE].asUInt();//普通用户为0，占位数据		

	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_USER_LOGIN);
	*out << userPass.c_str() << roomPass.c_str() << (uint64)macaddr;
	*out << m_netType;	
	*out << spaceData;
	*out << userPassCheck.c_str();
	*out << devNum.c_str();
	*out << bBindLogin;	
	*out << passType;
	*out << cocver;
	out->packetid = val[JSKEY_PACKETID].asString();
	LOG(4)("CTLMoblieSocket::SendLogonRoom uin = %u roomid = %u pass = %s mac = %llu devNum = %s \n", m_uin, m_roomid, userPass.c_str(), macaddr, devNum.c_str());
	SetConnectionStatus(CHAT_ENTERING_ROOM);
	return SendPacket(true,out);

	// 	return SendUserLogin(val[JSKEY_UIN].asUInt(), 
	// 						 val[JSKEY_ROOMID].asUInt(), 
	// 						 val[JSKEY_PASS].asString().c_str(), 
	// 						 macaddr,
	// 						 val[JSKEY_DEVTYPE].asInt(),
	// 						 val[JSKEY_DEVNUM].asString().c_str(),
	// 						 val[JSKEY_PACKETID].asString().c_str());
}
//主动请求
int CTLMoblieSocket::SendRequireUserInfoPacket(uint32 pid, uint32 uin, uint16 cmd, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << pid << uin;
	out->packetid = packetId;
	return SendPacket(true, out);
}
//主动请求
int CTLMoblieSocket::SendUserCmdPacket(uint16 cmd, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = packetId;
	return SendPacket(true, out);
}
//获取地图信息
int CTLMoblieSocket::SendGetUserMapData(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//获取升级的士兵队列
int CTLMoblieSocket::SendGetUpdateSoldierInfo(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//工人队列
int CTLMoblieSocket::sendGetWorkerList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//训练生产队列
int CTLMoblieSocket::sendGetProduceList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//当前拥有的士兵队列
int CTLMoblieSocket::sendGetSoldierList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//当前拥有的士兵的等级队列
int CTLMoblieSocket::sendGetSoldierLevelList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//加速列表
int CTLMoblieSocket::sendGetSpeedUpList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//成就列表
int CTLMoblieSocket::sendAchievementList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << pid << uin;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
//成就列表
int CTLMoblieSocket::sendGetServetPushList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket( cmd, val[JSKEY_PACKETID].asString().c_str());
}
//战斗历史记录
int CTLMoblieSocket::sendAttackHistoryList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket( cmd, val[JSKEY_PACKETID].asString().c_str());
}
//关卡历史记录
int CTLMoblieSocket::sendTollGateHistoryList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket( cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::sendGetTollGateMapInfo(Json::Value &val)
{
	return sendGetTollGateMapInfo((uint8)val[JSKEY_GATE_INDEX].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::sendGetTollGateMapInfo(uint8 gateIndex, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_GET_USER_TOLLGATE_MAP);
	*out << gateIndex;
	out->packetid = packetId;
	return SendPacket(true, out);
}
//获取地图信息
int CTLMoblieSocket::SendGetUserInfoData(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
//获取排行榜
int CTLMoblieSocket::SendGetRankList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket(cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendSelectStationMoney(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendPlatformMoneyBuyGemston(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint32 num = val[JSKEY_RES_NUM].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << pid << uin << num;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendStationMoneyBuyResource(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint32 resType = val[JSKEY_RES_ID].asInt();
	uint32 resNum = val[JSKEY_RES_NUM].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << pid << uin << resType << resNum;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetShieldCoolTimeLeftList(Json::Value &val)
{
	uint32 pid = val[JSKEY_PID].asUInt();
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendRequireUserInfoPacket(pid, uin, cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendGetMailMsgList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint32 lastMailTime = val[JSKEY_START_TIME].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << lastMailTime;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetOnlinePrizeList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetCurrOnlinePrize(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint8 prizeId =  val[JSKEY_PRIZE_ID].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << prizeId;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetDayActiveTaskPrizeInfo(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	std::string packetId = val[JSKEY_PACKETID].asString();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetDayActiveTaskList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}

//胜利留言
int	CTLMoblieSocket::SendWinnerMsg(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << (uint32)val[JSKEY_GAME_ID].asInt();
	*out << val[JSKEY_MSG].asString().c_str();
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::ReqBuyGemstoneInfo(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendGetCurrDayActivePrize(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	uint8 prizeId = val[JSKEY_PRIZE_ID].asUInt();
	*out << prizeId;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
void CTLMoblieSocket::OnRecvUserMapData(InPacketEx &in,  uint16 cmd)
{
	uint8 model = 0, mapIndex = 0, num = 0, state = 0, xpos = 0, ypos = 0, length = 0, width = 0;
	uint16 tatolThing = 0, type = 0;
	uint8 level = 0;
	uint32 health = 0, healthCurr = 0, startTime = 0, tmSpan = 0;
	uint32 pid = 0;
	uint32 uin = 0;
	Json::Value jsValue;
	Json::FastWriter fastWirter;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint8 sendNum  = 0;
	in >> model >> mapIndex >> packetNum >> packetIndex >> sendNum;
	jsValue[JSKEY_MODEL] = Json::Value(model);
	jsValue[JSKEY_MAP_INDEX] = Json::Value(mapIndex);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for(int i = 0; i < sendNum; i++)
	{
		in >> type >> num >> xpos >> ypos >> level >> state;
		in >> startTime >> tmSpan;
		Json::Value jsVal;
		jsVal[JSKEY_BUILD_TYPE] = Json::Value(type);
		jsVal[JSKEY_BUILD_NUM] = Json::Value(num);
		jsVal[JSKEY_X_POS] = Json::Value(xpos);
		jsVal[JSKEY_Y_POS] = Json::Value(ypos);
		jsVal[JSKEY_LEVEL] = Json::Value(level);
		jsVal[JSKEY_STATE] = Json::Value(state);
		jsVal[JSKEY_START_TIME] = Json::Value(startTime);
		jsVal[JSKEY_SPAN_TIME]	= Json::Value(tmSpan);
		jsValue[JSKEY_BUILDING_LIST].append(jsVal);
	}
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_MAP_DATA_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	std::string retString = fastWirter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnGetMapData %s\n", retString.c_str());
}
void CTLMoblieSocket::OnCreatBuilding(InPacketEx &in)
{
	uint16 buildingType = 0;
	uint16 result = 0;
	uint8 buildingNum = 0;
	uint8 xpos = 0, ypos = 0, level = 0;
	uint32 needTime = 0;
	in >> result>>  buildingType >> xpos >> ypos >> buildingNum >>  needTime >> level;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_BUILD);
	jsValue[JSKEY_RESULT] = Json::Value(result);;
	jsValue[JSKEY_NEED_TIME] = Json::Value(needTime);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
	jsValue[JSKEY_X_POS] = Json::Value(xpos);
	jsValue[JSKEY_Y_POS] = Json::Value(ypos);
	jsValue[JSKEY_LEVEL] = Json::Value(level);
	Json::FastWriter fastWriter;
	std::string retString = fastWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnCreatBuilding %s\n", retString.c_str());
}
void CTLMoblieSocket::OnRecvMoveBuilding(InPacketEx &in)
{
	uint16 buildingType = 0;
	uint16 result = 0;
	uint8 buildingNum = 0;
	uint8 xpos = 0, ypos = 0;
	in >> result >>  buildingType >> buildingNum;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_MOVE);
	jsValue[JSKEY_RESULT] = Json::Value(result);;
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
	jsValue[JSKEY_X_POS] = Json::Value(xpos);
	jsValue[JSKEY_Y_POS] = Json::Value(ypos);
	Json::FastWriter fastWriter;
	std::string retString = fastWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvMoveBuilding %s\n", retString.c_str());
}
void CTLMoblieSocket::OnRecvReMoveBuilding(InPacketEx &in)
{
	uint16 buildingType = 0;
	uint16 result = 0;
	uint8 buildingNum = 0;
	uint8 modeIndex = 0;
	uint8 mapIndex = 0;
	in >> result >>  buildingType >> buildingNum;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_REMOVE);
	jsValue[JSKEY_RESULT] = Json::Value(result);;
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
	jsValue[JSKEY_MODEL] = Json::Value(modeIndex);
	jsValue[JSKEY_MAP_INDEX] = Json::Value(mapIndex);
	Json::FastWriter fastWriter;
	std::string retString = fastWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvReMoveBuilding %s\n", retString.c_str());
}
void CTLMoblieSocket::OnRecvUpDateBuilding(InPacketEx &in)
{
	uint16 buildingType = 0;
	uint16 result = 0;
	uint8 buildingNum = 0;
	uint32 seconds = 0;
	in >> result >>  buildingType >> buildingNum >> seconds;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_UPDATE_LEVEL);
	jsValue[JSKEY_RESULT] = Json::Value(result);;
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(buildingNum);

	Json::FastWriter fastWriter;
	std::string retString = fastWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvUpDateBuilding %s\n", retString.c_str());
}
void CTLMoblieSocket::OnRecvCollectResources(InPacketEx &in)
{
	uint16 buildingType = 0;
	uint16 result = 0;
	uint8 buildingNum = 0;
	uint32 resNum = 0;
	in >> result >>  buildingType >> buildingNum >> resNum;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_REMOVE);
	jsValue[JSKEY_RESULT] = Json::Value(result);;
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
	jsValue[JSKEY_RES_NUM] = Json::Value(resNum);
	Json::FastWriter fastWriter;
	std::string retString = fastWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvCollectResources %s\n", retString.c_str());
}
int CTLMoblieSocket::SendCreatBuilding(Json::Value &val)
{
	return SendCreatBuilding((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_X_POS].asUInt(),
		(uint8)val[JSKEY_Y_POS].asUInt(), (uint8)val[JSKEY_USE_RES_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendCreatBuilding(uint16 buildingType, uint8 xPos, uint8 yPos, uint8 useGemston, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SCENE_BUILD);
	out->packetid = packetId;
	*out << buildingType << xPos << yPos << useGemston;
	return SendPacket(true, out);
}



int CTLMoblieSocket::SendCompletedImmediately(Json::Value &val)
{
	return SendCompletedImmediately((uint16)val[JSKEY_BUILD_TYPE].asUInt(),(uint8)val[JSKEY_BUILD_NUM].asUInt() , (uint8)val[JSKEY_COMPLETE_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendCompletedImmediately(uint16 buildingType, uint8 buildingNum, uint8 type, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_COMPLETEDIMMEDIATELY);
	out->packetid = packetId;
	*out << buildingType << buildingNum << type;
	return SendPacket(true,out);
}

int CTLMoblieSocket::SendUpdateBuilding(Json::Value &val)
{
	return SendUpdateBuilding((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_BUILD_NUM].asUInt(), (uint8)val[JSKEY_USE_RES_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendUpdateBuilding(uint16 buildingType, uint8 buildingNum, uint8 useGemston, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SCENE_UPDATE_LEVEL);
	out->packetid = packetId;
	*out << buildingType << buildingNum << useGemston;
	return SendPacket(true,out);
}
int CTLMoblieSocket::SendCancelBuilding(Json::Value &val)
{
	return SendCancelBuilding((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_BUILD_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendCancelBuilding(uint16 buildingType, uint8 buildingNum, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_CANCEL_BUILD);
	out->packetid = packetId;
	*out << buildingType << buildingNum ;
	return SendPacket(true,out);
}

int CTLMoblieSocket::SendMoveBuilding(Json::Value &val)
{
	return SendMoveBuilding((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_BUILD_NUM].asUInt(),
		(uint8)val[JSKEY_X_POS].asUInt(), (uint8)val[JSKEY_Y_POS].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendMoveBuilding(uint16 buildType, uint8 buildingNum, uint8 dstXPos, uint8 dstYPos, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SCENE_MOVE);
	*out << buildType << buildingNum << dstXPos << dstYPos;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendRemoveBuilding(Json::Value &val)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SCENE_REMOVE);
	out->packetid = val[JSKEY_PACKETID].asString();
	uint16 buildingType = val[JSKEY_BUILD_TYPE].asUInt();
	uint8 buildingNum = val[JSKEY_BUILD_NUM].asUInt();
	uint8 useGemston = val[JSKEY_USE_RES_TYPE].asUInt();
	*out << buildingType << buildingNum << useGemston;
	return SendPacket(true,out);
}

int CTLMoblieSocket::SendCancelRemoveBuilding(Json::Value &val)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_CANCEL_REMOVE);
	out->packetid = val[JSKEY_PACKETID].asString();
	uint16 buildingType = val[JSKEY_BUILD_TYPE].asUInt();
	uint8 buildingNum = val[JSKEY_BUILD_NUM].asUInt();
	*out << buildingType << buildingNum;
	return SendPacket(true,out);
}
int CTLMoblieSocket::SendCollectResources(Json::Value &val)
{
	return SendCollectResources((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_BUILD_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendCollectResources(uint16 buildingType, uint8 builddingNum, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SCENE_RESOURCE_COLLECT);
	out->packetid = packetId;
	*out << buildingType << builddingNum;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendGemstoneBuyResource(Json::Value &val)
{
	return SendGemstoneBuyResource((uint8)val[JSKEY_RES_ID].asUInt(), (uint32)val[JSKEY_RES_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendGemstoneBuyResource(uint8 resType, uint32 resNum, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_GEMSTONE_BUY_RESOURCE);
	out->packetid = packetId;
	*out << resType << resNum;
	return SendPacket(true, out);
}


int CTLMoblieSocket::SendTrainSoldier(Json::Value &val)
{
	return SendTrainSoldier((uint8)val[JSKEY_TRAINING_CAMP_INDEX].asUInt(), (uint16)val[JSKEY_SOLDIER_TYPE].asUInt(), (uint8)val[JSKEY_SOLDIER_NUM].asUInt(), 
		(uint8)val[JSKEY_USE_RES_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, uint8 useGemston, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_TRAIN_SOLDIER);
	*out << trainingCampIndex << soldierType << num << useGemston;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendProduceMagic(Json::Value &val)
{
	return SendProduceMagic((uint8)val[JSKEY_LAB_INDEX].asUInt(), (uint16)val[JSKEY_SOLDIER_TYPE].asUInt(), (uint8)val[JSKEY_SOLDIER_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendProduceMagic(uint8 magicFactoryIndex, uint16 soldierType, uint8 num, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_PRODUCE_MAGIC);
	*out << magicFactoryIndex << soldierType << num;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendSpeedUp(Json::Value &val)
{
	Json::Value jsSpeed = val[JSKEY_SPEED_UP_KEY];
	int size = jsSpeed.size();
	std::vector<SerialBuild> vecBuild;
	SerialBuild build;
	for (int i = 0; i < size; ++i)
	{
		build.m_buildType = jsSpeed[i][JSKEY_BUILD_TYPE].asUInt();
		build.m_num = jsSpeed[i][JSKEY_BUILD_NUM].asUInt();
		vecBuild.push_back(build);
	}	std::string packetId = val[JSKEY_PACKETID].asString();
	return SendSpeedUp(vecBuild, val[JSKEY_PACKETID].asString().c_str());	
}
int CTLMoblieSocket::SendSpeedUp(std::vector<SerialBuild> &vecBuild, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SPEED_UP);
	int size = vecBuild.size();
	if(size <= 0)
	{
		return -1;
	}
	*out << (uint8)size;
	for (int i = 0; i < size; ++i)
	{
		*out << vecBuild[i].m_buildType;
		*out << vecBuild[i].m_num;
	}
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendCancelTrainSoldier(Json::Value &val)
{
	return SendCancelTrainSoldier((uint8)val[JSKEY_TRAINING_CAMP_INDEX].asUInt(), (uint16)val[JSKEY_SOLDIER_TYPE].asUInt(), (uint8)val[JSKEY_SOLDIER_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendCancelTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_CANCEL_TRAIN_SOLDIER);
	*out << trainingCampIndex << soldierType << num;
	out->packetid = packetId;
	return SendPacket(true, out);
}

void CTLMoblieSocket::OnRecvTrainSoldier(InPacketEx &in)
{
	uint8 trainingCampIndex = 0;
	uint16 ret = 0;
	uint32 needTime = 0;
	in >> ret >> trainingCampIndex;
	if (ret == CocCmdStateType::COC_HANDLE_SUCCESS)
	{
		in >> needTime;
	}
	Json::Value jsValue;
	Json::FastWriter fastWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_TRAIN_SOLDIER);
	jsValue[JSKEY_RESULT] = Json::Value(ret);
	jsValue[JSKEY_TRAINING_CAMP_INDEX] = Json::Value(trainingCampIndex);
	jsValue[JSKEY_NEED_TIME] = Json::Value(needTime);
	std::string retString = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(retString.c_str(), retString.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvTrainSoldier %s\n", retString.c_str());
}


int CTLMoblieSocket::SendUpdateSoldierLevel(Json::Value &val)
{
	return SendUpdateSoldierLevel((uint16)val[JSKEY_SOLDIER_TYPE].asUInt(),(uint8)val[JSKEY_USE_RES_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendUpdateSoldierLevel(uint16 soldierType, uint8 useGemston, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_UPDATE_SOLDIER_LEVEL);
	*out << soldierType << useGemston;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetCanUseSoldier(Json::Value &val)
{
	return SendGetCanUseSoldier(val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendGetCanUseSoldier(const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_PUSH_SOLDIER_LIST);
	out->packetid = packetId;
	return SendPacket(true, out);
}



int CTLMoblieSocket::SendApplyToGetAchievement(Json::Value &val)
{
	return SendApplyToGetAchievement((uint16)val[JSKEY_ACHIEVEMENT_ID].asUInt(),(uint8)val[JSKEY_ACHIEVEMENT_LEVEL].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendApplyToGetAchievement(uint16 achvType, uint8 achvLevel, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_ACHIEVEMENT_APPLY);
	*out << achvType << achvLevel ;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendApplyToGetMailPrize(Json::Value &val)
{
	std::string packetId = val[JSKEY_PACKETID].asString();
	uint32 mailId = val[JSKEY_MAIL_ID].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_MAIL_PRIZE_APPLY);
	*out <<  mailId;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendDeleteMailMsg(Json::Value &val)
{
	std::string packetId = val[JSKEY_PACKETID].asString();
	uint32 mailId = val[JSKEY_MAIL_ID].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_DELETE_MAILMSG_LIST);
	*out <<  mailId;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendGetSoldierRecord(Json::Value &val)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_GET_SOLDIER_RECORD);
	uint32 srcPid = val[JSKEY_SRCPID].asUInt();
	uint32 srcUIn = val[JSKEY_SRCUIN].asUInt();
	uint32 dstPid = val[JSKEY_DSTPID].asUInt();
	uint32 dstUin = val[JSKEY_DSTUIN].asUInt();
	*out <<srcPid <<srcUIn << dstPid << dstUin;
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true, out);
}
void CTLMoblieSocket::OnRecvSoldierRecord(InPacketEx &in)
{
	uint8 size = 0;
	in >> size;
	uint32 soldierId = 0;
	uint8 group = 0;
	uint8 soldierNum;
	uint8 xpos = 0;
	uint8 ypos = 0; 
	uint32 timeOffset = 0;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_SOLDIER_RECORD);
	for (int i = 0; i < size; ++i)
	{
		Json::Value val;
		in >> soldierId  >> group >> soldierNum >> xpos >> ypos >> timeOffset;
		val[JSKEY_SOLDIER_ID] = Json::Value(soldierId);
		val[JSKEY_SOLDIER_GROUP] = Json::Value(group);
		val[JSKEY_SOLDIER_NUM] = Json::Value(soldierNum);
		val[JSKEY_X_POS] = Json::Value(xpos);
		val[JSKEY_Y_POS] = Json::Value(ypos);
		val[JSKEY_TIME_OFFSET] = Json::Value(timeOffset);
		jsValue[JSKEY_SOLDIER_LIST].append(val); 
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSoldierRecord %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSpeedUpList(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 size = 0;
	in >> size;
	for (int i = 0; i < size; ++i)
	{
		Json::Value jsTime;
		uint16 buildType = 0;
		uint8 buildNum = 0;
		uint32 timeRemain = 0;
		uint8 type =0;
		in >> buildType >> buildNum >> timeRemain >> type;
		if (0 == buildType || 0 == timeRemain)
		{
			continue;
		}
		jsTime[JSKEY_BUILD_TYPE] = Json::Value(buildType);
		jsTime[JSKEY_BUILD_NUM] = Json::Value(buildNum);
		jsTime[JSKEY_TIME_REMAIN] = Json::Value(timeRemain);
		jsTime[JSKEY_TIME_TYPE] = Json::Value(type);
		jsValue[JSKEY_TIME_LIST].append(jsTime);
	}
	uint32 pid = 0;
	uint32 uin = 0;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSpeedUpList %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSelectPlatformMoney(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 erroCode = 0;
	uint64 money = 0;
	uint32 pid = 0;
	uint32 uin = 0;
	in >> erroCode;
	in >> money;
	in >> pid >> uin;
	jsValue[JSKEY_RESULT] = Json::Value(erroCode);
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	char buf[256] = {0};
	sprintf(buf, "%llu", money);
	jsValue[JSKEY_MONEY] = Json::Value(buf);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("%s\n millisecond:%u", __FUNCTION__, talk_base::TimeStamp());
	LOG(4)("TLMoblieSocket::OnRecvSelectPlatformMoney %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSelectStationMoney(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 erroCode = 0;
	uint64 money = 0;
	uint32 pid = 0;
	uint32 uin = 0;
	in >> erroCode;
	in >> money;
	in >> pid >> uin;
	uint16 prorate = 0;		//百分比
	in >> prorate;
	if(0 == prorate)
	{
		prorate = 100;
	}
	jsValue[JSKEY_RESULT] = Json::Value(erroCode);
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	jsValue[JSKEY_PRORATE] = Json::Value(prorate);
	char buf[256] = {0};
	sprintf(buf, "%llu", money);
	jsValue[JSKEY_MONEY] = Json::Value(buf);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("[%s millisecond:%u\n]", __FUNCTION__, talk_base::TimeStamp());
	LOG(4)("TLMoblieSocket::OnRecvSelectStationMoney %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvChangeUserName(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 erroCode = 0;
	uint32 pid = 0;
	uint32 uin = 0;
	in >> erroCode;
	jsValue[JSKEY_RESULT] = Json::Value(erroCode);
	char buf[256] = {0};
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSelectPlatformMoney %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvShieldCoolTimeLeftList(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 size = 0;
	in >> size;
	for (int i = 0; i < size; ++i)
	{
		Json::Value jsTime;
		uint8 shieldId = 0;
		uint32 timeRemain = 0;
		in >> shieldId >> timeRemain;
		if (0 == timeRemain)
		{
			continue;
		}
		jsTime[JSKEY_SHIELD_ID] = Json::Value(shieldId);
		jsTime[JSKEY_TIME_REMAIN] = Json::Value(timeRemain);
		jsValue[JSKEY_TIME_LIST].append(jsTime);
	}
	uint32 pid = 0;
	uint32 uin = 0;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvShieldCoolTimeLeftList %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSystemMsg(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	std::string msg;
	uint8 msgType = 0;
	uint32 msgId = 0;
	uint32 remainTime = 0;
	uint16 showSpan = 0;
	uint32 pid = 0;
	in >> msg;
	in >>msgType;
	in >> msgId >> remainTime >> showSpan >> pid;
	jsValue[JSKEY_MSG] = Json::Value(msg);
	jsValue[JSKEY_MSG_TYPE] = Json::Value(msgType);
	jsValue[JSKEY_MSG_ID] = Json::Value(msgId);
	jsValue[JSKEY_TIME_REMAIN] = Json::Value(remainTime);
	jsValue[JSKEY_SHOW_SPAN] = Json::Value(showSpan);
	jsValue[JSKEY_PID] = Json::Value(pid);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSystemMsg %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvMailMsg(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 sendNum = 0;
	in >> sendNum;
	for (int i = 0; i < sendNum; ++ i)
	{
		uint32 msgId = 0;
		uint32 startTime;
		std::string from;
		std::string msg;
		std::string url;
		uint8 msgType = 0;
		uint32 remainTime = 0;
		uint32 pid = 0;
		uint32 uin = 0;
		in >> msgId >> startTime >> from >> msg >> url >> msgType >> remainTime;
		in >> pid >> uin;
		jsItem[JSKEY_MSG_ID] = Json::Value(msgId);
		jsItem[JSKEY_MSG_DATE] = Json::Value(startTime);
		jsItem[JSKEY_MSG_FROM] = Json::Value(from);
		jsItem[JSKEY_MSG_URL] = Json::Value(url);
		jsItem[JSKEY_MSG] = Json::Value(msg);
		jsItem[JSKEY_MSG_TYPE] = Json::Value(msgType);
		jsItem[JSKEY_TIME_REMAIN] = Json::Value(remainTime);
		jsItem[JSKEY_PID] = Json::Value(pid);
		jsItem[JSKEY_UIN] = Json::Value(uin);
		if (COCStruct::PRIZE == msgType)
		{
			uint32 gold = 0;
			uint32 holyWater = 0;
			uint32 blackWater = 0;
			uint32 gemstone = 0;
			in >> gold >> holyWater >> blackWater >> gemstone;
			jsItem[JSKEY_RES_GOLD] = Json::Value(gold);
			jsItem[JSKEY_RES_HOLYWARTER] = Json::Value(holyWater);
			jsItem[JSKEY_RES_BLACKWATER] = Json::Value(blackWater);
			jsItem[JSKEY_RES_GEMSTONE] = Json::Value(gemstone);
		}
		uint8 packetNum = 0;
		uint8 packetIndex = 0;
		in >> packetNum >> packetIndex;
		jsValue[JSKEY_MAIL_LIST].append(jsItem);
		jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
		jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvMailMsg %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvOnlinePrizeListInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint32 prizeTime = 0;
	uint8 prizeId = 0;
	in >> prizeId;
	in >> prizeTime;
	uint8 size = 0;
	in >> size;
	jsValue[JSKEY_PRIZE_ID] = Json::Value(prizeId);
	jsValue[JSKEY_TIME_LAST] = Json::Value(prizeTime);
	for (int i = 0; i < size; ++i)
	{
		uint32 duration;
		uint8 num = 0;
		in >> duration >> num;
		uint32 prizeNum = 0;
		Json::Value jsRes;
		jsItem[JSKEY_TIME_MAX] = Json::Value(duration);
		for (int j = 0; j < num; ++ j)
		{
			in >> prizeNum;
			jsRes.append(Json::Value(prizeNum));
		}
		jsItem[JSKEY_RESOURCE] = jsRes;
		jsValue[JSKEY_PRIZELIST].append(jsItem);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvOnlinePrizeListInfo %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvOrnamentUpPercent(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 size = 0;
	in >> size;
	for (int i = 0; i < size; ++i)
	{
		uint16 precent = 0;
		in >> precent;
		jsValue[JSKEY_PERCENT].append(Json::Value(precent));
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvOrnamentUpPercent %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvDayActiveTaskList(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 prizeId = 0;
	uint8 size = 0;
	in >> prizeId;
	jsValue[JSKEY_PRIZE_ID] = Json::Value(prizeId);
	in >> size;
	uint8 taskId = 0;
	uint32 Val = 0;
	for (int i = 0; i < size; ++i)
	{
		in >> taskId >> Val;
		jsItem[JSKEY_KEY] = Json::Value(taskId);
		jsItem[JSKEY_VAL] = Json::Value(Val);
		jsValue[JSKEY_PRIZELIST].append(jsItem);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvDayActiveTaskList %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvDayActiveTaskPrizeInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 size = 0;
	in >> size;
	for (int i = 0; i < size; ++i)
	{
		uint16 needNum = 0;
		uint8 num = 0;
		in >> needNum;
		in >> num;
		Json::Value jsRes;
		uint32 prizeNum = 0;
		jsItem[JSKEY_NEED_NUM] = Json::Value(needNum);
		for (int j = 0; j < num; ++ j)
		{
			in >> prizeNum;
			jsRes.append(Json::Value(prizeNum));
		}
		jsItem[JSKEY_RESOURCE] = jsRes;
		jsValue[JSKEY_PRIZELIST].append(jsItem);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}
void CTLMoblieSocket::OnRecvChallengeRankingList(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 state = 0;
	uint8 size = 0;
	uint32 mapId = 0;
	in >> state >> mapId >>size;
	jsValue[JSKEY_STATE] = Json::Value(state);
	jsValue[JSKEY_MAP_ID] = Json::Value(mapId);
	for (int i = 0; i < size; ++i)
	{
		uint32 pid;
		uint32 uin;
		uint8 percent;
		std::string name;
		uint32 starttime = 0;
		in >> pid >> uin  >> percent >> name >> starttime;
		jsItem[JSKEY_PID] = Json::Value(pid);
		jsItem[JSKEY_UIN] = Json::Value(uin);
		jsItem[JSKEY_PERCENT] = Json::Value(percent);
		jsItem[JSKEY_USERNICK] = Json::Value(name);
		jsItem[JSKEY_START_TIME] = Json::Value(starttime);
		jsValue[JSKEY_RANK_LIST].append(jsItem);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}
void CTLMoblieSocket::OnRecvChallengeDescribe(InPacketEx &in, uint16 cmd)
{

	Json::Value jsValue;
	Json::Value jsItem;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint32 pid = 0;
	in >> pid;
	jsValue[JSKEY_PID] = Json::Value(pid);

	uint32 uin = 0;
	in >> uin;
	jsValue[JSKEY_UIN] = Json::Value(uin);

	uint8 weekId = 0;
	in >> weekId;
	jsValue[JSKEY_WEEK_ID] = Json::Value(weekId);

	uint32 mapId = 0;
	in >> mapId;
	jsValue[JSKEY_MAP_ID] = Json::Value(mapId);

	uint8 open = 0;
	in >> open;
	jsValue[JSKEY_STATE] = Json::Value(open);

	std::string name;
	in >> name;
	jsValue[JSKEY_USERNICK] = Json::Value(name);

	std::string describe;
	in >> describe;
	jsValue[JSKEY_DESCRIBE] = Json::Value(describe);

	std::string mchallengeTime;
	in >> mchallengeTime;
	jsValue[JSKEY_CHALLENGE_TIME] = Json::Value(mchallengeTime);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}

void CTLMoblieSocket::OnRecvWinnerMsg(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 ret;
	in >> ret;
	jsValue[JSKEY_RESULT] = Json::Value(ret);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}

void CTLMoblieSocket::OnRecvBuyGemstoneInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	
	uint32 cash_RMB;	//人民币
	uint32 gemstone;	//折后宝石
	uint16 discount;	//折扣

	uint16 num = 0;
	in >> num;
	Json::Value jsList;
	for(uint16 i = 0; i < num; i++)
	{
		Json::Value jsItem;
		in >> cash_RMB >> gemstone >> discount;
		jsItem[JSKEY_CASH_RMB] = Json::Value(cash_RMB);
		jsItem[JSKEY_GEMSTONE_DISCOUNT] = Json::Value(gemstone);
		jsItem[JSKEY_DISCOUNT] = Json::Value(discount);
		jsList.append(jsItem);
	}
	jsValue[JSKEY_BUY_GEMSTONE_INFO] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}


void CTLMoblieSocket::OnRecvChargeGemstone(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);


	uint32 gemstone;	//折后重置宝石个数
	uint32 gemstoneAll;	//剩余宝石总个数

	uint16 num = 0;
	in >> gemstone >> gemstoneAll;
		
	jsValue[JSKEY_GEMSTONE_DISCOUNT] = Json::Value(gemstone);
	jsValue[JSKEY_GEMSTONE_ALL] = Json::Value(gemstoneAll);
		
	

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}


void CTLMoblieSocket::OnRecvFirstChargeNotify(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);


	uint32 pid;
	uint32 uin;
	uint8  nState;
	
	in >> pid >> uin >>nState;

	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	jsValue[JSKEY_STATE] = Json::Value(nState);


	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}


void CTLMoblieSocket::OnRecvFinishFisttChargeNotify(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);


	uint32 pid;
	uint32 uin;
	uint8 nState = 0;
	in >> pid >> uin >> nState;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	jsValue[JSKEY_RESULT] = Json::Value(nState);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}


void CTLMoblieSocket::OnRecvBrotherhood(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);


	uint16 nSize = 0;
	in >> nSize;

	Json::Value jsList;
	uint32 key;
	uint32 val;
	uint8 nType;
	for(uint16 i = 0; i < nSize; i++)
	{
		Json::Value jsItem;
		in >> key >> val >> nType;
		jsItem[JSKEY_BROTHER_ID] = Json::Value(key);
		jsItem[JSKEY_BROTHER_VALUE] = Json::Value(val);
		jsItem[JSKEY_BUILD_TYPE] = Json::Value(nType);
		jsList.append(jsItem);
	}
	jsValue[JSKEY_BROTHER_TASKLIST] = jsList;
	

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}

void CTLMoblieSocket::OnRecvBrotherList(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);


	uint32 gameid;
	uint32 pid;
	uint32 uin;
	uint32 time;
	uint32 totalStars;
	uint16 nSize;
	Json::Value jsList;
	in >> nSize;
	for(uint16 i = 0; i < nSize; i++)
	{
		Json::Value jsItem;
		string nick;
		in >> pid >> uin >> gameid >> nick >> totalStars >> time;
		jsItem[JSKEY_PID] = Json::Value(pid);
		jsItem[JSKEY_UIN] = Json::Value(uin);
		jsItem[JSKEY_GAME_ID] = Json::Value(gameid);
		jsItem[JSKEY_USERNICK] = Json::Value(nick.c_str());
		jsItem[JSKEY_TOTAL_STARS] = Json::Value(totalStars);
		jsItem[JSKEY_TIME]	= Json::Value(time);
		jsList.append(jsItem);
	}
	jsValue[JSKEY_BROTHERINFO_LIST] = jsList;
	

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());

}


void CTLMoblieSocket::OnRecvBrotheTaskReward(InPacketEx &in, uint16 cmd)
{
	uint32 newKey;
	uint32 currVal;
	uint8 nType;
	uint8 nResult;
	in >> newKey >> currVal >> nType >> nResult;
	Json::Value jsValue;
	jsValue[JSKEY_BROTHER_ID] = Json::Value(newKey);
	jsValue[JSKEY_BROTHER_VALUE]  = Json::Value(currVal);
	jsValue[JEKEY_BROTHER_TYPE] = Json::Value(nType);
	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CMD]	= Json::Value(cmd);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());
}


void CTLMoblieSocket::OnRecvBindBrotherResult(InPacketEx &in, uint16 cmd)
{
	uint8 nResult;
	uint32 dstGameid;
	in >> dstGameid >> nResult;
	Json::Value jsValue;
	jsValue[JSKEY_GAME_ID] = Json::Value(dstGameid);
	jsValue[JSKEY_RESULT]  = Json::Value(nResult);
	jsValue[JSKEY_CMD]	= Json::Value(cmd);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::%s %s\n", __FUNCTION__, strRet.c_str());

}

void CTLMoblieSocket::OnRecvForceOffLine(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint32 newroomid =0;
	uint32 newip = 0;
	uint16 newport = 0;
	uint8 newdevType = 0;
	uint8 state;		//保存用户是否被顶下线
	in >> newip >> newport >> state >> newdevType >> newroomid;
	jsValue[JSKEY_IP] = Json::Value(newip);
	jsValue[JSKEY_PORT] = Json::Value(newport);
	jsValue[JSKEY_STATE] = Json::Value(state);
	jsValue[JSKEY_DEV_TYPE] = Json::Value(newdevType);
	jsValue[JSKEY_ROOMID] = Json::Value(newroomid);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvForceOffLine %s\n", strRet.c_str());	
}
int CTLMoblieSocket::SendWallMutiMove(Json::Value &val)
{
	Json::Value jsNum = val[JSKEY_BUILD_ARRAY];
	int size = jsNum.size();
	std::vector<uint8> wall;
	if (size == 0)
	{
		return -1;
	}
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_WALL_MUTI_MOVE);
	uint8 model = val[JSKEY_MODEL].asUInt();
	uint8 mapIndex = val[JSKEY_MAP_INDEX].asUInt();
	*out << model << mapIndex << uint8(size);
	uint8 serialNum = 0;
	uint8 xpos = 0; 
	uint8 ypos = 0;
	for (int i = 0; i < size; ++i)
	{
		serialNum = jsNum[i][JSKEY_BUILD_NUM].asUInt();
		xpos = jsNum[i][JSKEY_X_POS].asUInt();
		ypos = jsNum[i][JSKEY_Y_POS].asUInt();
		*out << serialNum << xpos << ypos;
	}	
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	std::string str = val.toStyledString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendWallMutiUpdate(Json::Value &val)
{
	Json::Value jsNum = val[JSKEY_BUILD_ARRAY];
	int size = jsNum.size();
	std::vector<uint8> wall;
	for (int i = 0; i < size; ++i)
	{
		uint8 num = jsNum[i].asUInt();
		wall.push_back(num);
	}
	return SendWallMutiUpdate(wall, (uint8)val[JSKEY_USE_RES_TYPE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendWallMutiUpdate(std::vector<uint8> &wall, uint8 useGemston, const char* packetId)
{
	int size = wall.size();
	if(size == 0)
	{
		return -1;
	}
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_WALL_MUTI_UPDATE);
	*out << uint8(size) << useGemston;
	for (int i = 0; i < size; ++i)
	{
		*out << wall[i];
	}	
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendBuyShield(Json::Value &val)
{
	uint8 shiledId = val[JSKEY_SHIELD_ID].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_BUY_SHILED);
	*out << shiledId  ;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendBuyOrnament(Json::Value &val)
{
	return SendBuyOrnament((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_X_POS].asUInt(), 
		(uint8)val[JSKEY_Y_POS].asUInt(), (uint8)val[JSKEY_USE_RES_TYPEE].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendBuyOrnament(uint16 buildType, uint8 xpos, uint8 ypos, uint8 useGemstone, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_BUY_ORNAMENT);
	*out << buildType << xpos << ypos << useGemstone ;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendSellOrnament(Json::Value &val)
{
	return SendSellOrnament((uint16)val[JSKEY_BUILD_TYPE].asUInt(), (uint8)val[JSKEY_BUILD_NUM].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendSellOrnament(uint16 buildingType, uint8 builddingNum, const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SELL_ORNAMENT);
	out->packetid = packetId;
	*out << buildingType << builddingNum;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendMapCopy(Json::Value &val)
{
	return SendMapCopy((uint8)val[JSKEY_SRC_MODEL].asUInt(), (uint8)val[JSKEY_SRC_MAP_INDEX].asUInt(), 
		(uint8)val[JSKEY_DST_MODEL].asUInt(), (uint8)val[JSKEY_DST_MAP_INDEX].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendMapCopy(uint8 srcMode, uint8 srcIndex, uint8 dstMode, uint8 dstIndex,  const char* packetId)
{
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_MAP_COPY);
	out->packetid = packetId;
	*out << srcMode << srcIndex << dstMode << dstIndex;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendMapEdite(Json::Value &val)
{
	uint8 mode = val[JSKEY_MODEL].asUInt();
	uint8 mapIndex = val[JSKEY_MAP_INDEX].asUInt();
	Json::Value jBuild = val[JSKEY_BUILD_ARRAY];
	uint16 num = jBuild.size();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_MAP_EDITE);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	*out << mode << mapIndex << num;
	for (int i = 0; i < num; ++i)
	{
		uint16 buildType = jBuild[i][JSKEY_BUILD_TYPE].asUInt();
		uint8 serialNum = jBuild[i][JSKEY_BUILD_NUM].asUInt();
		uint8 xpos = jBuild[i][JSKEY_X_POS].asUInt();
		uint8 ypos = jBuild[i][JSKEY_Y_POS].asUInt();
		*out << buildType << serialNum << xpos << ypos;
	}
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendBuildingReport(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint16 buildType = val[JSKEY_BUILD_TYPE].asUInt();
	uint8 buildNum = val[JSKEY_BUILD_NUM].asUInt();
	uint32 timeOffset = val[JSKEY_TIME_OFFSET].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	*out << buildType << buildNum << timeOffset;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendResourceReport(Json::Value &val)
{
	uint32 resGold = val[JSKEY_RES_GOLD].asUInt();
	uint32 resHolyWater = val[JSKEY_RES_HOLYWARTER].asUInt();
	uint32 resBlackWater = val[JSKEY_RES_BLACKWATER].asUInt();
	uint32 resGoldStore = val[JSKEY_RES_GOLD_STORE].asUInt();
	uint32 resHolyWaterStore = val[JSKEY_RES_HOLYWARTER_STORE].asUInt();
	uint32 resBlackWaterStore = val[JSKEY_RES_BLACKWATER_STORE].asUInt();
	uint32 timeOffset = val[JSKEY_TIME_OFFSET].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_REPORT_RESOURCE);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	*out << resGold << resHolyWater << resBlackWater<< resGoldStore << resHolyWaterStore << resBlackWaterStore  << timeOffset;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendTerminatAttack(Json::Value &val)
{
	
	uint32 timeOffset = (uint32)val[JSKEY_TIME_OFFSET].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	*out  << timeOffset ;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendTerminatTollGate(Json::Value &val)
{
	uint8 tollGateIndex = (uint8)val[JSKEY_GATE_INDEX].asUInt();
	uint32 resGold = (uint32)val[JSKEY_RES_GOLD].asUInt(); 
	uint32 resHolyWater = (uint32)val[JSKEY_RES_HOLYWARTER].asUInt();
	uint32 resBlackWater = (uint32)val[JSKEY_RES_BLACKWATER].asUInt();
	uint8 star = (uint8)val[JSKEY_WAR_STAR_NUM].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_TERMINAT_TOLLGATE);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();

	Json::Value jSoldier = val[JSKEY_SOLDIER_LIST];
	int size = jSoldier.size();
	*out << (uint8)size;
	for (int i = 0; i < size; ++i)
	{
		uint16 soldierType = jSoldier[i][JSKEY_SOLDIER_TYPE].asUInt();
		uint8 soldierNum = jSoldier[i][JSKEY_SOLDIER_NUM].asUInt();
		*out << soldierType;
		*out << soldierNum;
	}
	*out <<tollGateIndex<<  resGold << resHolyWater << resBlackWater << star;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendRecoverTrap(Json::Value &val)
{
	Json::Value jBuild = val[JSKEY_BUILD_ARRAY];
	uint16 num = jBuild.size();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_MAP_EDITE);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	*out <<  num;
	for (int i = 0; i < num; ++i)
	{
		uint16 buildType = jBuild[i][JSKEY_BUILD_TYPE].asUInt();
		uint8 serialNum = jBuild[i][JSKEY_BUILD_NUM].asUInt();
		*out << buildType << serialNum ;
	}
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendSetNewUserStep(Json::Value &val)
{
	uint8 step = val[JSKEY_NEW_USER_STEP].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SET_NEW_USER_STEP);
	*out << step;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendSetUserName(Json::Value &val)
{
	std::string name = val[JSKEY_USERNICK].asString();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_SET_USER_NAME);
	*out << name;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendChangeUserName(Json::Value &val)
{
	std::string name = val[JSKEY_USERNICK].asString();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_CHANGE_USER_NAME);
	*out << name;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendUserRevenge(Json::Value &val)
{
	uint32 defendPid = val[JSKEY_DEFEND_PID].asUInt();
	uint32 defendUin = val[JSKEY_DEFEND_UIN].asUInt();
	uint32 attackTime = val[JSKEY_ATTACK_TIME].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_USER_REVENGE);
	*out << defendPid << defendUin << attackTime;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendMachingUserWithId(Json::Value &val)
{
	uint32 defendPid = val[JSKEY_DEFEND_PID].asUInt();
	uint32 defendUin = val[JSKEY_DEFEND_UIN].asUInt();
	uint32 defendGameid = val[JSKEY_DEFEND_GAMEID].asUInt();
	OutPacketEx *out = createPacket_Head(true, CocCmdType::COC_MACHING_USER_WITH_ID);
	*out << defendPid << defendUin << defendGameid;
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}


int CTLMoblieSocket::SendGameChallenge(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket(cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendOrnamentUpPercent(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket(cmd, val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendGetChallengeRankingList(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	return SendUserCmdPacket(cmd, val[JSKEY_PACKETID].asString().c_str());
}

int CTLMoblieSocket::SendFinishFistCharge(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	
	return SendPacket(true, out);
}


//请求兄弟关系完成状态 COC_BROTHERHOOD_INFO
int CTLMoblieSocket::SendBrotherhoodReq(Json::Value &val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true, out);
}

//请求兄弟关系列表 COC_BROTHERLSIT_INFO
int CTLMoblieSocket::SendBrotherListReq(Json::Value& val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendBrotherTaskReward(Json::Value& val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint8 nType = val[JEKEY_BROTHER_TYPE].asInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << nType;
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true, out);
}


int CTLMoblieSocket::SendBindBrother(Json::Value& val)
{
	uint16 cmd = val[JSKEY_CMD].asUInt();
	uint32 gameid = val[JSKEY_GAME_ID].asInt();
	OutPacketEx *out = createPacket_Head(true, cmd);
	*out << gameid;
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true, out);
}

void CTLMoblieSocket::OnRecvSoldierLevel(InPacketEx &in, uint16 cmd)
{
	uint16 soldierType = 0;
	uint8 soldierLevel = 0;
	uint8 size = 0;
	in >> size;
	Json::Value jsValue;
	Json::Value jsSoldier;
	for (int i = 0;i < size; ++i)
	{
		in >> soldierType >> soldierLevel;
		jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
		jsSoldier[JSKEY_LEVEL] = Json::Value(soldierLevel);
		jsValue[JSKEY_SOLDIER_LIST].append(jsSoldier);
	}
	uint32 pid  =0;
	uint32 uin = 0;
	in >> pid >> uin;
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_SOLDIER_LEVEL_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSoldierLevel %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSoldierUpdate(InPacketEx &in, uint16 cmd)
{
	uint16 soldierType = 0;
	//uint8 soldierLevel = 0;
	uint32 spanTime = 0;
	uint32 pid  =0;
	uint32 uin = 0;
	Json::Value jsValue;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	in >> soldierType >> spanTime;	
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_UPDATE_SOLDIER_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	if (0 != soldierType)
	{
		jsValue[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
		jsValue[JSKEY_SPAN_TIME] = Json::Value(spanTime);
	}		
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvSoldierUpdate %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvFindUserMap(InPacketEx &in)
{
	uint32 dstUin = 0;
	uint32 dstPid = 0;
	uint16 buildingType = 0;
	uint8 level = 0;
	uint8 buildingNum = 0, xpos = 0, ypos = 0;
	uint8 state = 0;
	in >> dstPid ;
	in >> dstUin ;
	Json::Value jsValue;
	Json::FastWriter fastWriter;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint8 sendNum  = 0;
	in >> packetNum >> packetIndex >> sendNum;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_TOLLGATE_MAP);
	jsValue[JSKEY_DSTPID] = Json::Value(dstPid);
	jsValue[JSKEY_DSTUIN] = Json::Value(dstUin);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for (int i = 0; i < sendNum; ++ i)
	{
		in >> buildingType >> buildingNum >> xpos >> ypos >> level >> state;
		Json::Value val;
		val[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
		val[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
		val[JSKEY_BUILD_STATE] = Json::Value(state);
		val[JSKEY_X_POS] = Json::Value(xpos);
		val[JSKEY_Y_POS] = Json::Value(ypos);
		val[JSKEY_LEVEL] = Json::Value(level);
		jsValue[JSKEY_BUILDING_LIST].append(val);
		buildingType = level = 0;
		buildingNum = xpos = ypos = 0;
	}
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvFindUserMap %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvAttackHistoryMap(InPacketEx &in, uint16 cmd)
{
	uint32 defendPid = 0;
	uint32 defendUin = 0; 
	uint32 attackTime = 0;
	uint16 buildingType = 0;
	uint8 level = 0;
	uint8 buildingNum = 0, xpos = 0, ypos = 0;
	uint8 state = 0;
	uint32 canPluder = 0;
	in >>  defendPid >> defendUin >> attackTime;
	Json::Value jsValue;
	Json::FastWriter fastWriter;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint8 sendNum  = 0;
	in >> packetNum >> packetIndex >> sendNum;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_DEFEND_PID] = Json::Value(defendPid);
	jsValue[JSKEY_DEFEND_UIN] = Json::Value(defendUin);
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(attackTime);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for (int i = 0; i < sendNum; ++ i)
	{
		in >> buildingType >> buildingNum >> xpos >> ypos >> level >> state >> canPluder;
		Json::Value val;
		val[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
		val[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
		val[JSKEY_BUILD_STATE] = Json::Value(state);
		val[JSKEY_X_POS] = Json::Value(xpos);
		val[JSKEY_Y_POS] = Json::Value(ypos);
		val[JSKEY_LEVEL] = Json::Value(level);
		val[STORE_CAN_PLUNDER_NUM] = Json::Value(canPluder);
		jsValue[JSKEY_BUILDING_LIST].append(val);
	}
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvAttackHistoryMap %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvMachingUserMap(InPacketEx &in ,uint16 cmd)
{
	uint32 dstUin = 0;
	uint32 dstPid = 0;
	uint16 buildingType = 0;
	uint8 level = 0;
	uint8 buildingNum = 0, xpos = 0, ypos = 0;
	uint8 state = 0;
	uint32 canPlunder = 0;
	in >> dstPid ;
	in >> dstUin ;
	Json::Value jsValue;
	Json::FastWriter fastWriter;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint8 sendNum  = 0;
	in >> packetNum >> packetIndex >> sendNum;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_DSTPID] = Json::Value(dstPid);
	jsValue[JSKEY_DSTUIN] = Json::Value(dstUin);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for (int i = 0; i < sendNum; ++ i)
	{
		in >> buildingType >> buildingNum >> xpos >> ypos >> level >> state >> canPlunder;
		Json::Value val;
		val[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
		val[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
		val[JSKEY_BUILD_STATE] = Json::Value(state);
		val[JSKEY_X_POS] = Json::Value(xpos);
		val[JSKEY_Y_POS] = Json::Value(ypos);
		val[JSKEY_LEVEL] = Json::Value(level);
		val[STORE_CAN_PLUNDER_NUM] = Json::Value(canPlunder);
		jsValue[JSKEY_BUILDING_LIST].append(val);

	}
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvMachingUserMap %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvTollGateMap(InPacketEx &in, uint16 cmd)
{
	uint16 buildingType = 0;
	uint8 level = 0;
	uint8 buildingNum = 0, xpos = 0, ypos = 0;
	uint8 gateIndex = 0;
	std::string gateName;
	uint32 gold = 0;
	uint32 holywarter = 0;
	uint32 blackwater = 0;

	Json::Value jsValue;
	Json::FastWriter fastWriter;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint8 sendNum  = 0;
	in >> packetNum >> packetIndex >> sendNum;
	in >>gateIndex >> gateName >> gold >> holywarter >> blackwater;	
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	jsValue[JSKEY_RES_GOLD] = Json::Value(gold);
	jsValue[JSKEY_RES_HOLYWARTER] = Json::Value(holywarter);
	jsValue[JSKEY_RES_BLACKWATER] = Json::Value(blackwater);
	jsValue[JSKEY_GATE_INDEX] = Json::Value(gateIndex);
	jsValue[JSKEY_GATE_NAEM] = Json::Value(gateName);
	for (int i = 0; i < sendNum; ++ i)
	{
		in >> buildingType >> buildingNum >> level >> xpos >> ypos ;
		Json::Value val;
		val[JSKEY_BUILD_TYPE] = Json::Value(buildingType);
		val[JSKEY_BUILD_NUM] = Json::Value(buildingNum);
		val[JSKEY_X_POS] = Json::Value(xpos);
		val[JSKEY_Y_POS] = Json::Value(ypos);
		val[JSKEY_LEVEL] = Json::Value(level);
		jsValue[JSKEY_BUILDING_LIST].append(val);
	}
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvTollGateMap %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvTollInfoList(InPacketEx &in, uint16 cmd)
{
	uint8 gateIndex = 0;		
	uint8 star = 0;			
	uint32 gold = 0;			
	uint32 holywater = 0;		
	uint32 blackwater = 0;	
	uint8 size = 0;
	in >> size;
	Json::Value jsValue;	
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	for (int i = 0; i < size; ++ i)
	{
		in >> gateIndex >> star >> gold >> holywater >> blackwater ;
		Json::Value val;		
		val[JSKEY_RES_GOLD] = Json::Value(gold);
		val[JSKEY_RES_HOLYWARTER] = Json::Value(holywater);
		val[JSKEY_RES_BLACKWATER] = Json::Value(blackwater);
		val[JSKEY_GATE_INDEX] = Json::Value(gateIndex);
		val[JSKEY_WAR_STAR_NUM] = Json::Value(star);
		jsValue[JSKEY_GATE_LIST].append(val);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvTollInfoListMap %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvUserInfo(InPacketEx &in, uint16 cmd)
{	
	Json::Value jsValue;
	Json::FastWriter fsWriter;
	uint16 cup = 0;	
	uint8  leagueLevel = 0;
	uint8 sourceNum = 0;
	uint32 dstUin = 0;
	uint32 dstPid = 0;
	in >> dstPid ;
	in >> dstUin ;
	in >> sourceNum;
	for (int i = 0; i < sourceNum; ++i)
	{		
		uint32 plunderProduce = 0;
		uint32 plunderCollect = 0;
		uint32 plunderMax = 0;		
		in >> plunderProduce >> plunderCollect >>plunderMax;
		Json::Value jres;
		jres[JSKEY_RES_ID] = Json::Value(uint8(i));
		jres[JSKEY_RES_PLUNDER_PRODUCE] = Json::Value(plunderProduce);
		jres[JSKEY_RES_PLUNDER_COLLECT] = Json::Value(plunderCollect);
		jres[JSKEY_RES_PLUNDER_MAX] = Json::Value(plunderMax);
		jsValue[JSKEY_RES].append(jres);
	}
	in >> cup >> leagueLevel;	
	uint8 level = 0;
	uint32 exp = 0;
	in >> level >> exp;
	uint32 shieldLeft = 0;
	uint32 shieldCoolLeft = 0;
	in >> shieldLeft >> shieldCoolLeft;

	uint32 seekHelpLeft = 0;
	uint32 seekHelpCoolLeft = 0;
	in >> seekHelpLeft >> seekHelpCoolLeft;
	//
	std::string nick;
	uint8 refreshId = 0;
	uint32 clanId = 0;
	uint8 clanJob =0;
	std::string clanName;
	in >> nick;
	in >> refreshId;
	in >> clanId;
	in >> clanJob;
	in >> clanName;

	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_DSTPID] = Json::Value(dstPid);
	jsValue[JSKEY_DSTUIN] = Json::Value(dstUin);
	jsValue[JSKEY_CUP] =  Json::Value(cup);
	jsValue[JSKEY_LEAGUELEVEL] =  Json::Value(leagueLevel);

	jsValue[JSKEY_LEVEL] =  Json::Value(level);
	jsValue[JSKEY_USER_EXP] =  Json::Value(exp);

	jsValue[JSKEY_SHIELD_LEFT] =  Json::Value(shieldLeft);
	jsValue[JSKEY_SHIELD_COOL_LEFT] =  Json::Value(shieldCoolLeft);

	jsValue[JSKEY_SEEKHELP_LEFT] =  Json::Value(seekHelpLeft);
	jsValue[JSKEY_SHIELD_COOL_LEFT] =  Json::Value(seekHelpCoolLeft);
	jsValue[JSKEY_USERNICK] = Json::Value(nick);
	jsValue[JSKEY_REFRESH_INDEX] = Json::Value(refreshId);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanId);
	jsValue[JSKEY_CLAN_JOB] = Json::Value(clanJob);
	jsValue[JSKEY_CLAN_NAME] = Json::Value(clanName);

	std::string strRet = fsWriter.write(jsValue);
	if(m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(),  strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvUserInfo %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvSvrPushProduceList(InPacketEx &in, uint16 cmd)
{	
	Json::Value jsValue;
	Json::FastWriter fastWriter;	
	uint8 size = 0;
	uint16 produceType = 0;
	uint16 buildType = 0;
	uint8 produceNum = 0;
	uint8 buildNum = 0;
	uint32 spanTime = 0;
	uint32 endTime = 0;
	in >> size;
	for (int i = 0; i < size ; ++i)
	{
		Json::Value jsStartTime;
		uint8 produceSize = 0;
		in >> buildType >> buildNum >> spanTime >> produceSize;
		jsStartTime[JSKEY_BUILD_TYPE] = Json::Value(buildType);
		jsStartTime[JSKEY_BUILD_NUM] = Json::Value(buildNum);
		jsStartTime[JSKEY_SPAN_TIME] = Json::Value(spanTime);		
		for (int i = 0; i < produceSize; ++i)
		{			
			Json::Value jsProduce;
			in >> produceType >> produceNum;
			jsProduce[JSKEY_PRODUCE_TYPE] = Json::Value(produceType);
			jsProduce[JSKEY_NUM] = Json::Value(produceNum);
			jsStartTime[JSKEY_PRODUCE_LIST].append(jsProduce);
		}		
		jsValue[JSKEY_START_TIME_LIST].append(jsStartTime);
	}	
	uint32 pid  =0;
	uint32 uin = 0;
	in >> pid >> uin;
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_PRODUCE_LIST_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);	
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}

	LOG(4)("TLMoblieSocket::OnRecvSvrPushProduceList %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvAchievementComplete(InPacketEx &in)
{
	uint16 achvType= 0;
	uint8 achvLevel = 0;
	in >> achvType >> achvLevel;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SERVER_ACHIEVEMENT_COMPLETE);
	jsValue[JSKEY_ACHIEVEMENT_ID] = Json::Value(achvType);
	jsValue[JSKEY_ACHIEVEMENT_LEVEL] = Json::Value(achvLevel);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvAchievementComplete %s\n", strRet.c_str());
} 
void CTLMoblieSocket::OnRecvAchievementInfo(InPacketEx &in, uint16 cmd)
{
	uint16 achvId= 0;
	uint8 achvLevel = 0;
	uint8 completeLevel = 0;
	uint32 currValue;
	uint16 size = 0;
	in >> size;
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	for (int i = 0; i < size; ++i)
	{
		Json::Value jsAchive;
		in >> achvId >> achvLevel >> currValue >> completeLevel;		
		jsAchive[JSKEY_ACHIEVEMENT_ID] = Json::Value(achvId);
		jsAchive[JSKEY_ACHIEVEMENT_LEVEL] = Json::Value(achvLevel);
		jsAchive[JSKEY_ACHIEVEMENT_VALUE] = Json::Value(currValue);
		jsAchive[JSKEY_ACHIEVEMENT_COMPLETE] = Json::Value(completeLevel);
		jsValue[JSKEY_ACHIEVEMENT_LIST].append(jsAchive);
	}
	uint32 pid = 0;
	uint32 uin = 0;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid); 
	jsValue[JSKEY_UIN] = Json::Value(uin); 
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvAchievementComplete %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvWorkingList(InPacketEx &in, uint16 cmd)
{
	uint16 buildType = 0;
	uint8 num = 0;
	uint32 timeLeft = 0;
	Json::Value jsValue;
	Json::Value jsWork;
	uint32 pid  =0;
	uint32 uin = 0;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	in >> buildType ;
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_WORKER_LIST_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	while(buildType)
	{
		in >> num >> timeLeft;
		jsWork[JSKEY_BUILD_TYPE] = Json::Value(buildType);
		jsWork[JSKEY_BUILD_NUM] =  Json::Value(num);
		jsWork[JSKEY_WORKER_TIME_LEFT] =  Json::Value(timeLeft);
		jsValue[JSKEY_WORKING_LIST].append(jsWork);		
		in >> buildType ;
	}

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvWorkingList %s\n", strRet.c_str());	
}
void CTLMoblieSocket::OnRecvGameNotifyMessage(InPacketEx &in)
{
	uint8 msgType = 0;
	std::string msg;
	uint16 subcmd = 0;
	in >> msgType;
	in >> msg;
	in >> subcmd;

	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SERVER_NOTIFY_MSG);
	jsValue[JSKEY_GAME_NOTIFY_TYPE] = Json::Value(msgType);
	jsValue[JSKEY_GAME_NOTIFY_MSG] = Json::Value(msg);
	jsValue[JSKEY_SUBCMD] = Json::Value(subcmd);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvGameNotifyMessage %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvAttackHistory(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	uint32 offensePid = 0;
	uint32 offenseUin = 0; 
	uint32 defendPid = 0;
	uint32 defendUin = 0; 
	uint32 attackTime = 0;
	uint32 keyId = 0;
	uint32 offenseGameid = 0;
	uint32 defendGameid = 0;

	uint16 cup = 0;
	uint8 percent = 0;
	uint8  leagueLevel = 0;

	uint32 clanId = 0;
	uint32 gold = 0;
	uint32 holywarter = 0;
	uint32 blackwater = 0;
	uint8 size = 0;
	uint8 packetNum = 1;
	uint8 packetIndex = 1;
	in >> packetNum >> packetIndex;
	in >> size;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for (int i = 0; i < size; ++i)
	{
		std::string name ;	
		std::string clanName ;
		Json::Value attack;
		in >> offensePid;
		in >> offenseUin;
		in >> defendPid;
		in >> defendUin;
		in >> attackTime;
		in >> keyId;
		in >> offenseGameid;
		in >> defendGameid;

		//掠夺资源
		in >> gold;
		in >> holywarter;
		in >> blackwater;
		attack[JSKEY_RES_GOLD] = Json::Value(gold);
		attack[JSKEY_RES_HOLYWARTER] = Json::Value(holywarter);
		attack[JSKEY_RES_BLACKWATER] = Json::Value(blackwater);
		//对方用户信息
		in >> cup;
		in >> leagueLevel;
		in >> name;		
		in >> clanName;
		in >> clanId;
		attack[JSKEY_OFFENSE_PID] = Json::Value(offensePid);
		attack[JSKEY_OFFENSE_UIN] = Json::Value(offenseUin);
		attack[JSKEY_OFFENSE_GAMEID] = Json::Value(offenseGameid);
		attack[JSKEY_DEFEND_PID] = Json::Value(defendPid);
		attack[JSKEY_DEFEND_UIN] = Json::Value(defendUin);
		attack[JSKEY_DEFEND_GAMEID] = Json::Value(defendGameid);
		attack[JSKEY_ATTACK_TIME] = Json::Value(attackTime);
		attack[JSKEY_DB_KEYID] = Json::Value(keyId);
		Json::Value userInfo;
		userInfo[JSKEY_CUP] = Json::Value(cup);
		userInfo[JSKEY_LEAGUELEVEL] = Json::Value(leagueLevel);
		userInfo[JSKEY_USERNICK] = Json::Value(name);
		userInfo[JSKEY_CLAN_NAME] = Json::Value(clanName);

		attack[JSKEY_USER_INFO] = userInfo;

		//派兵户信息
		uint8 soldierSize = 0;
		in >> soldierSize;
		Json::Value jsSoldier;
		for (int j =0; j < soldierSize; ++j)
		{
			uint16 soldierType = 0;
			uint8 soldierNum = 0;
			uint8 soldierLevel = 0;
			in >> soldierType;
			in >> soldierNum;
			in >> soldierLevel;
			jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
			jsSoldier[JSKEY_SOLDIER_NUM] = Json::Value(soldierNum);
			jsSoldier[JSKEY_SOLDIER_LEVEL] = Json::Value(soldierLevel);
			attack[JSKEY_SEND_SOLDIER].append(jsSoldier);
		}
		uint8 cupNum = 0;
		uint8 warStar = 0;
		uint8 canRevenge = 0;
		in >> cupNum >> warStar >> percent >> canRevenge;
		attack[JSKEY_CUP] = Json::Value(cupNum);
		attack[JSKEY_WAR_STAR_NUM] = Json::Value(warStar);
		attack[JSKEY_PERCENT] = Json::Value(percent);
		attack[JSKEY_CANREVENGE] = Json::Value(canRevenge);
		jsValue[JSKEY_ATTACK_LIST].append(attack);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvAttackHistory %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvDefendUserOnAttackInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	uint32 dstPid = 0;
	uint32 dstUin = 0;
	uint32 attackTime = 0;

	uint16 cup = 0;
	uint8  leagueLevel = 0;

	uint32 clanId = 0;
	uint32 gold = 0;
	uint32 holywarter = 0;
	uint32 blackwater = 0;
	in >> attackTime;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	std::string name ;	
	std::string clanName ;
	in >> dstPid;
	in >> dstUin;

	//对方用户信息
	in >> cup;
	in >> leagueLevel;
	in >> name;		
	in >> clanName;
	in >> clanId;
	//资源
	in >> gold;
	in >> holywarter;
	in >> blackwater;
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(attackTime);
	jsValue[JSKEY_DSTPID] = Json::Value(dstPid);
	jsValue[JSKEY_DSTUIN] = Json::Value(dstUin);	
	Json::Value userInfo;
	userInfo[JSKEY_CUP] = Json::Value(cup);
	userInfo[JSKEY_LEAGUELEVEL] = Json::Value(leagueLevel);
	userInfo[JSKEY_USERNICK] = Json::Value(name);
	userInfo[JSKEY_CLAN_NAME] = Json::Value(clanName);
	userInfo[JSKEY_RES_GOLD] = Json::Value(gold);
	userInfo[JSKEY_RES_HOLYWARTER] = Json::Value(holywarter);
	userInfo[JSKEY_RES_BLACKWATER] = Json::Value(blackwater);
	jsValue[JSKEY_USER_INFO] = userInfo;

	//用户派兵信息
	uint8 soldierSize = 0;
	in >> soldierSize;
	Json::Value jsSoldier;
	for (int j =0; j < soldierSize; ++j)
	{
		uint16 soldierType = 0;
		uint32 timeOffset = 0;
		uint8 soldierLevel = 0;
		uint8 xpos = 0;
		uint8 ypos = 0;
		in >> soldierType;		
		in >> soldierLevel;
		in >> xpos;
		in >> ypos;
		in >> timeOffset;
		jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);		
		jsSoldier[JSKEY_SOLDIER_LEVEL] = Json::Value(soldierLevel);
		jsSoldier[JSKEY_X_POS] = Json::Value(xpos);
		jsSoldier[JSKEY_Y_POS] = Json::Value(ypos);
		jsSoldier[JSKEY_TIME_OFFSET] = Json::Value(timeOffset);
		jsValue[JSKEY_SEND_SOLDIER].append(jsSoldier);
	}
	//被掠夺的资源
	uint32 resGold = 0;
	uint32 resHolyWater = 0;
	uint32 resBlackWater = 0;
	uint32 timeMax = 0;
	in >> resGold >> resHolyWater >> resBlackWater >> timeMax;
	uint8 warCup = 0;
	uint8 percent = 0;
	in >> warCup >> percent;
	jsValue[JSKEY_RES_GOLD] = Json::Value(resGold);
	jsValue[JSKEY_RES_HOLYWARTER] = Json::Value(resHolyWater);
	jsValue[JSKEY_RES_BLACKWATER] = Json::Value(resBlackWater);
	jsValue[JSKEY_TIME_MAX] = Json::Value(timeMax);
	jsValue[JSKEY_WAR_CUP] = Json::Value(warCup);
	jsValue[JSKEY_PERCENT] = Json::Value(percent);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvDefendUserOnAttackInfo %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvOffendUserSoldierInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	//用户派兵信息
	uint8 soldierSize = 0;
	uint32 attackTime = 0;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	in >> attackTime;
	in >> packetNum >> packetIndex;
	in >> soldierSize;
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(attackTime);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	Json::Value jsSoldier;
	for (int j =0; j < soldierSize; ++j)
	{
		uint16 soldierType = 0;
		uint32 timeOffset = 0;
		uint8 soldierLevel = 0;
		uint8 xpos = 0;
		uint8 ypos = 0;
		in >> soldierType;		
		in >> soldierLevel;
		in >> xpos;
		in >> ypos;
		in >> timeOffset;
		jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);		
		jsSoldier[JSKEY_SOLDIER_LEVEL] = Json::Value(soldierLevel);
		jsSoldier[JSKEY_X_POS] = Json::Value(xpos);
		jsSoldier[JSKEY_Y_POS] = Json::Value(ypos);
		jsSoldier[JSKEY_TIME_OFFSET] = Json::Value(timeOffset);
		jsValue[JSKEY_SEND_SOLDIER].append(jsSoldier);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("%s %s\n", __FUNCTION__, strRet.c_str());
}
void CTLMoblieSocket::OnRecvCanUseSoldier(InPacketEx &in, uint16 cmd)
{
	uint16 type = 0;
	uint8 group = 0;
	uint8 level = 0, soldierNum = 0;
	uint8 size = 0;
	in >> size;
	Json::Value jsValue;
	Json::Value jsSoldier;
	for (int i = 0;i < size; ++i)
	{
		in >> type >> level >> soldierNum >> group;	
		if(0 == soldierNum)
		{
			continue;
		}
		jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(type);
		jsSoldier[JSKEY_LEVEL] = Json::Value(level);
		jsSoldier[JSKEY_SOLDIER_NUM] = Json::Value(soldierNum);
		jsSoldier[JSKEY_SOLDIER_GROUP] = Json::Value(group);
		jsValue[JSKEY_SOLDIER_LIST].append(jsSoldier);
	}
	uint32 pid  =0;
	uint32 uin = 0;
	in >> pid >> uin;
	jsValue[JSKEY_PID] = Json::Value(pid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	if (!IsMySelf(pid, uin))
	{
		cmd = CocCmdType::COC_GET_USER_OWN_SOLDIER_LIST_VISIT;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvCanUseSoldier %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvRankList(InPacketEx &in, uint16 cmd)
{
	uint8 size = 0;
	uint8 packetNum = 0;
	uint8 packetIndex = 0;
	uint16 cup = 0;								//奖杯数量
	uint8 leagueLevel = 0;						//联赛级别
	uint8 level = 0;								//游戏等级
	uint16 rankNum = 0;							//排名
	uint32 pid = 0;								//pid
	uint32 uin = 0;								//uin
	uint32 offenceSuccess = 0;					//成功进攻次数
	uint32 defendSuccess = 0;						//成功防守次数
	uint32 clanId = 0;							//所属部落
	uint32 clanIconNum = 0;						//部落图标编号
	Json::Value jsValue;
	in >> packetNum >> packetIndex;
	in >> size;
	for (int i = 0; i < size; ++i)
	{
		std::string name;							//角色昵称
		std::string clanName;						//所属部落名称	
		Json::Value jsItem;
		in >> cup;
		in >> leagueLevel;
		in >> level;
		in >> rankNum;
		in >> pid;
		in >> uin;
		in >> offenceSuccess;
		in >> defendSuccess;
		in >> clanId;
		in >> clanIconNum;
		in >> name;
		in >> clanName;
		jsItem[JSKEY_CUP] = Json::Value(cup);
		jsItem[JSKEY_LEAGUELEVEL] = Json::Value(leagueLevel);
		jsItem[JSKEY_LEVEL] = Json::Value(level);
		jsItem[JSKEY_RANK_NUM] = Json::Value(rankNum);
		jsItem[JSKEY_PID] = Json::Value(pid);
		jsItem[JSKEY_UIN] = Json::Value(uin);
		jsItem[JSKEY_OFFENCE_SUCESS] = Json::Value(offenceSuccess);
		jsItem[JSKEY_DEFEND_SUCESS] = Json::Value(defendSuccess);
		jsItem[JSKEY_CLAN_ID] = Json::Value(clanId);
		jsItem[JSKEY_CLAN_ICON_NUM] = Json::Value(clanIconNum);
		jsItem[JSKEY_USERNICK] = Json::Value(name);
		jsItem[JSKEY_CLAN_NAME] = Json::Value(clanName);
		jsValue[JSKEY_RANK_LIST].append(jsItem);
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvRankList %s\n", strRet.c_str());
}


//////////////////////////////////////////////////////////////////////////

int CTLMoblieSocket::SendLogoutRoom(Json::Value& val)
{
	LOG(4)("CTLMoblieSocket::SendLogoutRoom\r\n");
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_USER_LOGOUT);
	out->packetid = val[JSKEY_PACKETID].asString();
	return SendPacket(true,out);
}

//收到对进入房间roomid命令的回复,只在CHAT_ENTERING_ROOM状态下响应此消息
void CTLMoblieSocket::OnRecvLoginRoomReply(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	Json::FastWriter fsWriter;
	uint16 logonResult;
	uint16 cup = 0;	
	uint8  leagueLevel = 0;
	uint8 step = 0;
	in >> logonResult;
	uint8 sourceNum = 0;
	in >> sourceNum;
	for (int i = 0; i < sourceNum; ++i)
	{		
		uint32 resCurr = 0;
		uint32 resMax = 0;
		in >> resCurr >> resMax;
		Json::Value jres;
		jres[JSKEY_RES_ID] = Json::Value(uint8(i));
		jres[JSKEY_RES_CURR] = Json::Value(resCurr);
		jres[JSKEY_RES_MAX] = Json::Value(resMax);
		jsValue[JSKEY_RES].append(jres);
	}

	in >> cup >> leagueLevel;	
	if(logonResult != CocCmdStateType::COC_HANDLE_SUCCESS) 
	{
		SetConnectionStatus(CHAT_OUTOF_ROOM);
	}
	else
	{
		SetConnectionStatus(CHAT_IN_ROOM);
	}
	uint8 level = 0;
	uint32 exp = 0;
	in >> level >> exp;
	uint32 shieldLeft = 0;
	uint32 shieldCoolLeft = 0;
	in >> shieldLeft >> shieldCoolLeft;

	uint32 seekHelpLeft = 0;
	uint32 seekHelpCoolLeft = 0;
	uint32 offenceSucess = 0;
	uint32 defendSucess = 0;
	uint32 offLineTime = 0;
	in >> seekHelpLeft >> seekHelpCoolLeft;
	//
	std::string nick;
	uint8 refreshId = 0;
	uint32 clanId = 0;
	uint8 clanJob =0;
	uint8 exchangeTimes;
	uint32 zeroSpan;
	uint32 gameid;
	std::string clanName;
	in >> nick;
	in >> refreshId;
	in >> clanId;
	in >> clanJob;
	in >> clanName;
	in >> step;
	in >> defendSucess >> offenceSucess >> offLineTime;
	in >> exchangeTimes >> zeroSpan >> gameid;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_RESULT] = Json::Value(logonResult);
	jsValue[JSKEY_CUP] =  Json::Value(cup);
	jsValue[JSKEY_LEAGUELEVEL] =  Json::Value(leagueLevel);

	jsValue[JSKEY_LEVEL] =  Json::Value(level);
	jsValue[JSKEY_USER_EXP] =  Json::Value(exp);

	jsValue[JSKEY_SHIELD_LEFT] =  Json::Value(shieldLeft);
	jsValue[JSKEY_SHIELD_COOL_LEFT] =  Json::Value(shieldCoolLeft);

	jsValue[JSKEY_SEEKHELP_LEFT] =  Json::Value(seekHelpLeft);
	jsValue[JSKEY_SHIELD_COOL_LEFT] =  Json::Value(seekHelpCoolLeft);
	jsValue[JSKEY_USERNICK] = Json::Value(nick);
	jsValue[JSKEY_REFRESH_INDEX] = Json::Value(refreshId);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanId);
	jsValue[JSKEY_CLAN_JOB] = Json::Value(clanJob);
	jsValue[JSKEY_CLAN_NAME] = Json::Value(clanName);
	jsValue[JSKEY_NEW_USER_STEP] = Json::Value(step);
	jsValue[JSKEY_DEFEND_SUCESS] = Json::Value(defendSucess);
	jsValue[JSKEY_OFFENCE_SUCESS] = Json::Value(offenceSucess);
	jsValue[JSKEY_OFFLINE_TIME] = Json::Value(offLineTime);
	jsValue[JSKEY_ZERO_SPAN] = Json::Value(zeroSpan);
	jsValue[JSKEY_EXCHANGE_TMES] = Json::Value(exchangeTimes);
	jsValue[JSKEY_GAME_ID]	= Json::Value(gameid);
	std::string strRet = fsWriter.write(jsValue);

	if(m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(),  strRet.length());
	}
	LOG(4)("CTLMoblieSocket::OnRecvLogonRoomReply：%s\r\n", strRet.c_str());	
}
int CTLMoblieSocket::SendRemoveSoldiers(Json::Value &val)
{
	uint32 soldierId = val[JSKEY_SOLDIER_ID].asUInt();
	uint8 group = val[JSKEY_SOLDIER_GROUP].asUInt();
	uint8 soldierNum = (uint8)val[JSKEY_SOLDIER_NUM].asUInt();
	std::string packetId =  val[JSKEY_PACKETID].asString();
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_REMOVE_SOLDIER);
	*out << soldierId << group << soldierNum ;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendSoldiers(Json::Value &val)
{

	return SendSoldiers((uint32)val[JSKEY_SOLDIER_ID].asUInt(),(uint8)val[JSKEY_SOLDIER_GROUP].asUInt(), (uint8)val[JSKEY_SOLDIER_NUM].asUInt(), (uint8)val[JSKEY_X_POS].asUInt(),
		(uint8)val[JSKEY_Y_POS].asUInt(), (uint32)val[JSKEY_TIME_OFFSET].asUInt(),  val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendMagic(Json::Value &val)
{
	uint32 magicId = val[JSKEY_MAGIC_ID].asUInt();
	uint32 timeOffset = val[JSKEY_TIME_OFFSET].asUInt();
	uint8 xpos = (uint8)val[JSKEY_X_POS].asUInt();
	uint8 ypos = (uint8)val[JSKEY_Y_POS].asUInt();
	std::string packetId =  val[JSKEY_PACKETID].asString();
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_SEND_MAGIC);
	*out << magicId << xpos << ypos << timeOffset;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendSoldiers(uint32 soldierId, uint8 group, uint8 soldierNum, uint8 xpos, uint8 ypos, uint32 timeOffset, const char* packetId)
{
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_PICKET_SOLDIERS);
	*out << soldierId << group << soldierNum << xpos << ypos << timeOffset;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendMachingUser(Json::Value &val)
{
	uint32 pid = val[JSKEY_DSTPID].asUInt();
	uint32 uin = val[JSKEY_DSTUIN].asUInt();
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_MACHING_USER);
	out->packetid = val[JSKEY_PACKETID].asString();
	*out << pid << uin;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendGetAttackHistoryMap(Json::Value &val)
{
	std::string packetId = val[JSKEY_PACKETID].asString();
	uint32 defendPid = val[JSKEY_DEFEND_PID].asUInt();
	uint32 defendUin = val[JSKEY_DEFEND_UIN].asUInt(); 
	uint32 attacktime = val[JSKEY_ATTACK_TIME].asUInt();
	uint16 cmd = val[JSKEY_CMD].asUInt();
	if(0 == cmd)
	{
		cmd = CocCmdType::COC_GET_ATTACK_HISTORY_MAP;
	}
	OutPacketEx* out = createPacket_Head(true, cmd);
	*out << defendPid << defendUin << attacktime;
	out->packetid = packetId;
	return SendPacket(true, out);
}
int CTLMoblieSocket::SendCancelMaching(Json::Value &val)
{
	return SendCancelMaching(val[JSKEY_DSTPID].asUInt(), val[JSKEY_DSTUIN].asUInt(), val[JSKEY_PACKETID].asString().c_str());
}
int CTLMoblieSocket::SendCancelMaching(uint32 pid, uint32 uin, const char* packetId)
{
	OutPacketEx* out = createPacket_Head(true,CocCmdType::COC_CANCEL_MACHING);
	*out << pid << uin;
	out->packetid = packetId;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanListInfoReq( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanInfoReq( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	*out << clanid;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanOperate( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	uint8  nAction = (uint8)val[JSKEY_ACTION].asUInt();
	*out << clanid << nAction;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanLeave( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	uint32  dstuin = (uint32)val[JSKEY_DSTUIN].asUInt();
	*out << clanid << dstuin;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendCreateClan( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	*out << clanid << val[JSKEY_CLAN_NAME].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendModifyClanInfo( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	uint32 minCupNumLimit = (uint32)val[JSKEY_CUP].asUInt();

	*out << clanid << minCupNumLimit << val[JSKEY_CLAN_DESC].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendSearchClan( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	
	*out << val[JSKEY_CLAN_NAME].asString().c_str();
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendChangeRank( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint8  nRank = (uint8)val[JSKEY_CLAN_JOB].asUInt();
	uint32 dstuin = val[JSKEY_DSTUIN].asUInt();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asUInt();
	*out << clanid << dstuin << nRank;
	return SendPacket(true, out);
}

void CTLMoblieSocket::OnRecvModifyClanInfoReplay( InPacketEx &in, uint16 cmd )
{
	uint16 nResult;
	uint16 clanid;

	in >> nResult >> clanid;

	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvModifyClanInfoReplay %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvUpdateClanInfo( InPacketEx &in, uint16 cmd )
{
	
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 order = 0;
	in >> order;
	jsValue[JSKEY_ORDER_ID] = Json::Value(order);
	ParseClanInfo(in, jsValue, false);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvUpdateClanInfo %s\n", strRet.c_str());
}


void CTLMoblieSocket::ParseClanJoin(InPacketEx &in, Json::Value& jsVal)
{
	uint32 opruin;
	uint16 clanid;
	uint32 dstuin;
	string strNick;
	uint32 pid;
	uint32 cupNum;

	in >> clanid >> opruin  >> dstuin >> strNick >> pid >> cupNum;
	jsVal[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsVal[JSKEY_SRCUIN] = Json::Value(opruin);
	jsVal[JSKEY_DSTUIN] = Json::Value(dstuin);
	jsVal[JSKEY_DSTNICK] = Json::Value(strNick.c_str());
	jsVal[JSKEY_DSTPID] = Json::Value(pid);
	jsVal[JSKEY_CUP] = Json::Value(cupNum);

}

void CTLMoblieSocket::OnRecvClanJon( InPacketEx &in, uint16 cmd )
{
	

	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	
	ParseClanJoin(in, jsValue);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanJon %s\n", strRet.c_str());
}

void CTLMoblieSocket::ParseClanLeave(InPacketEx &in, Json::Value& jsVal)
{
	uint32 opruin;
	uint16 clanid;
	uint32 dstuin;
	string srcNick;
	string dstNick;
	uint8   oprRank;
	in >> clanid >> opruin  >> dstuin >> srcNick >> dstNick >> oprRank;
	jsVal[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsVal[JSKEY_SRCUIN] = Json::Value(opruin);
	jsVal[JSKEY_DSTUIN] = Json::Value(dstuin);
	jsVal[JSKEY_SRCNICK] = Json::Value(srcNick.c_str());
	jsVal[JSKEY_DSTNICK] = Json::Value(dstNick.c_str());
	jsVal[JSKEY_CLAN_JOB] = Json::Value(oprRank);
}

void CTLMoblieSocket::OnRecvClanLeave( InPacketEx &in, uint16 cmd )
{
	

	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	ParseClanLeave(in, jsValue);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanLeave %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanInfo( InPacketEx &in, uint16 cmd )
{
	

	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	
	uint16 orderid;
	in >> orderid;
	jsValue[JSKEY_ORDER_ID] = Json::Value(orderid);
	ParseClanInfo(in, jsValue, true);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanInfo %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanList( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 nSize = 0;
	in >> nSize;

	Json::Value jsList;
	for(uint16 i = 0; i < nSize; i++)
	{
		Json::Value jsItem;
		uint16 orderid;
		in >> orderid;
		jsItem[JSKEY_ORDER_ID] = Json::Value(orderid);
		ParseClanInfo(in, jsItem, true);
		jsList.append(jsItem);
	}
	jsValue[JSKEY_CLAN_LIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanList %s\n", strRet.c_str());
}

void CTLMoblieSocket::ParseClanInfo( InPacketEx &in, Json::Value& valRet, bool bAddState)
{
	uint16 clanid;
	string clanName;
	string desc;
	string leaderName;
	uint8 level;
	uint16 currNum;
	uint16 maxSize;
	uint32 totalCupNum;
	uint32 experience;
	uint32 minLimit;
	uint8  reqState;
	uint8  kickTimes;
	string strDesc;
	in >> clanid >> clanName >> leaderName >> level;
	in >> currNum >> maxSize;
	in >> totalCupNum >> experience;
	in >> minLimit >> reqState >> kickTimes >> strDesc;
	valRet[JSKEY_CLAN_ID] = Json::Value(clanid);
	valRet[JSKEY_CLAN_NAME] = Json::Value(clanName.c_str());
	valRet[JSKEY_CLAN_DESC] = Json::Value(desc.c_str());
	valRet[JSKEY_CLAN_LEADER_NAME] = Json::Value(leaderName.c_str());
	valRet[JSKEY_LEVEL]			= Json::Value(level);
	valRet[JSKEY_CLAN_CURR_MEMBER]	= Json::Value(currNum);
	valRet[JSKEY_CLAN_MAX_MEMBER] = Json::Value(maxSize);
	valRet[JSKEY_CUP]			   = Json::Value(totalCupNum);
	valRet[JSKEY_CLAN_EXPERIENCE] = Json::Value(experience);
	valRet[JSKEY_CLAN_MIN_CUPNUM] = Json::Value(minLimit);
	valRet[JSKEY_KICK_TIMES]	  = Json::Value(kickTimes);
	valRet[JSKEY_CLAN_DESC]		  = Json::Value(strDesc.c_str());	
	if(bAddState)
	{
		valRet[JSKEY_REQ_STATE] = Json::Value(reqState);
	}
	
}

int CTLMoblieSocket::SendDeleteClan( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	out->packetid = val[JSKEY_PACKETID].asString().c_str();
	uint16 clanid = (uint16)val[JSKEY_CLAN_ID].asInt();
	*out << clanid;
	return SendPacket(true, out);
}



void CTLMoblieSocket::OnRecvCreateDelClan( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 clanid = 0;
	uint16 nResult = 0;
	in >> nResult >> clanid;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvCreateDelClan %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanReqAdd( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 clanid = 0;
	uint32 opruin;
	uint32 requin;
	string reqNick = "";
	uint32 reqTime;
	uint32 reqCupNums;
	in >> clanid >> opruin >> requin >> reqNick >> reqTime >> reqCupNums;

	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_SRCUIN] = Json::Value(opruin);
	jsValue[JSKEY_DSTUIN] = Json::Value(requin);
	jsValue[JSKEY_DSTNICK] = Json::Value(reqNick.c_str());
	jsValue[JSKEY_TIME] = Json::Value(reqTime);
	jsValue[JSKEY_CUP] = Json::Value(reqCupNums);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanReqAdd %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanReqDel( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 clanid = 0;
	uint32 opruin;
	uint32 requin;
	
	in >> clanid >> opruin >> requin;

	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_SRCUIN] = Json::Value(opruin);
	jsValue[JSKEY_DSTUIN] = Json::Value(requin);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanReqDel %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanReqAllList( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 clanid = 0;
	uint16 nSize = 0;
	

	in >> clanid >> nSize;
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	Json::Value jsList;
	for(uint16 i = 0; i < nSize; i++)
	{
		Json::Value item;
		uint32 requin;
		uint32 reqpid;
		string reqNick = "";
		uint32 reqTime;
		uint32 reqCupNums;
		in   >>reqpid >> requin >> reqNick >> reqTime >> reqCupNums;

		item[JSKEY_CLAN_ID] = Json::Value(clanid);
		item[JSKEY_PID] = Json::Value(reqpid);
		item[JSKEY_UIN] = Json::Value(requin);
		item[JSKEY_NICK] = Json::Value(reqNick.c_str());
		item[JSKEY_TIME] = Json::Value(reqTime);
		item[JSKEY_CUP] = Json::Value(reqCupNums);
		jsList.append(item);
	}

	jsValue[JSKEY_CLAN_REQ_LIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanReqAllList %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanMemList( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 nSize = 0;

	in  >> nSize;
	Json::Value jsList;
	for(uint16 i = 0; i < nSize; i++)
	{
		Json::Value item;
		uint32 pid;
		uint32 uin;
		string nick = "";
		uint8 clanRank;
		uint32 totalContributionVal;
		uint32 totalcupNums;
		uint16 yesterdayVal;
		in  >> pid >> uin >> nick >> clanRank >> totalContributionVal >> yesterdayVal >> totalcupNums;

		item[JSKEY_PID] = Json::Value(pid);
		item[JSKEY_UIN] = Json::Value(uin);
		item[JSKEY_NICK] = Json::Value(nick);
		item[JSKEY_CLAN_JOB] = Json::Value(clanRank);
		item[JSKEY_CLAN_CONSTRIBUION] = Json::Value(totalContributionVal);
		item[JSKEY_CLAN_YESTERDAY] = Json::Value(yesterdayVal);
		item[JSKEY_CUP] = Json::Value(totalcupNums);
		jsList.append(item);
	}

	jsValue[JSKEY_CLAN_MEMLIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanMemList %s\n", strRet.c_str());
}


void CTLMoblieSocket::OnRecvClanUpdateLevel( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	
	ParseClanInfo(in, jsValue, false);
	
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanUpdateLevel %s\n", strRet.c_str());
}


void CTLMoblieSocket::ParseClanChangeNotify(InPacketEx &in, Json::Value& jsVal)
{
	uint16 clanid;
	uint32 opr;
	string oprNick;
	uint32 dst;
	string dstNick;
	uint8 oldRank;
	uint8 newRank;

	in >> clanid >> opr >> oprNick >> dst >> dstNick >> oldRank >> newRank;

	jsVal[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsVal[JSKEY_SRCUIN] = Json::Value(opr);
	jsVal[JSKEY_SRCNICK] = Json::Value(oprNick);
	jsVal[JSKEY_DSTUIN] = Json::Value(dst);
	jsVal[JSKEY_DSTNICK] = Json::Value(dstNick);
	jsVal[JSKEY_OLD_RANK] = Json::Value(oldRank);
	jsVal[JSKEY_NEW_RANK] = Json::Value(newRank);
}

void CTLMoblieSocket::OnRecvClanChangeNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	ParseClanChangeNotify(in, jsValue);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanUpdateLevel %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanChangeRankResult( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;

	in >> nResult;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanChangeRankResult %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanStateCache( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nSize;
	uint16 len;
	uint16 subcmd;
	in >> nSize;
	char buf[_MAX_PACKET_SIZE];
	Json::Value jsList;
	for(uint16 i = 0; i < nSize; i++)
	{
		memset(buf, 0, _MAX_PACKET_SIZE);
		in >> subcmd >> len;
		in.ReadData(buf, len);
		InPacketEx temp;
		temp.setdata(buf, len);
		Json::Value jsItem;
		jsItem[JSKEY_SUBCMD] = Json::Value(subcmd);
		switch(subcmd)
		{
		case CocCmdType::COC_SVR_CLAN_JOIN:
			ParseClanJoin(temp, jsItem);
			break;
		case CocCmdType::COC_SVR_CLAN_LEAVE:
			ParseClanLeave(temp, jsItem);
			break;
		case CocCmdType::COC_SVR_CLAN_UPDATELEVEL:
			ParseClanInfo(temp, jsItem, false);
			break;
		case CocCmdType::COC_SVR_CLAN_CHANGERANK:
			ParseClanChangeNotify(temp, jsItem);
			break;
		case CocCmdType::COC_SVR_CLAN_DONATE:
			ParseClanDonate(temp, jsItem);
			break;
		case CocCmdType::COC_SVR_CLAN_AWARD_ALLOT:
			ParseClanAwardAllot(temp, jsItem);
			break;


		}
		jsList.append(jsItem);
	}
	jsValue[JSKEY_CLAN_STATECACHE] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanStateCache %s\n", strRet.c_str());

}

void CTLMoblieSocket::OnRecvClanOperate( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;
	uint16 clanid;
	uint8  action;

	in >> clanid >> action >> nResult;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_ACTION] = Json::Value(action);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanOperate %s\n", strRet.c_str());
}

int CTLMoblieSocket::SendClanConfimReq( Json::Value& val )
{
	
	uint16 clanid = val[JSKEY_CLAN_ID].asUInt();
	uint8  action = val[JSKEY_ACTION].asUInt();
	uint32 dstuin = val[JSKEY_DSTUIN].asUInt();
	
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	

	*out << clanid << action << dstuin;
	return SendPacket(true, out);
	
}


int CTLMoblieSocket::SendPidClanList( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	return SendPacket(true, out);
}

//请求部落捐献
int CTLMoblieSocket::SendClanDonate(Json::Value& val)
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	uint8 donateType = val[JSKEY_CLAN_DONATE_TYPE].asUInt();
	*out << donateType;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanRecruit(Json::Value& val)
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	return SendPacket(true, out);
}
int CTLMoblieSocket::OnSendClanDonateTimeInfoNotify( Json::Value& val )
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanWarBastionInfo(Json::Value& val)
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	uint16 clanid = val[JSKEY_CLAN_ID].asUInt();
	*out << clanid;
	return SendPacket(true, out);
}

int CTLMoblieSocket::SendClanAllotToUserReq(Json::Value& val)
{
	OutPacketEx* out = createPacket_Head(true,val[JSKEY_CMD].asUInt());
	uint32 uin = val[JSKEY_UIN].asUInt();
	uint16 clanid = val[JSKEY_CLAN_ID].asUInt();
	uint32 goldNum = val[JSKEY_RES_GOLD].asUInt();
	uint32 holyWater = val[JSKEY_RES_HOLYWARTER].asUInt();
	uint32 gemstone = val[JSKEY_RES_GEMSTONE].asUInt();
	*out << uin << clanid << goldNum << holyWater << gemstone;
	return SendPacket(true, out);
}

void CTLMoblieSocket::OnRecvClanAllotToUserResp(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 result;
	uint32 gold;
	uint32 holyWater;
	uint32 gemstone;

	in >> result >> gold >> holyWater >> gemstone;

	jsValue[JSKEY_RESULT] = Json::Value(result);
	jsValue[JSKEY_RES_GOLD] = Json::Value(gold);
	jsValue[JSKEY_RES_HOLYWARTER] = Json::Value(holyWater);
	jsValue[JSKEY_RES_GEMSTONE] = Json::Value(gemstone);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanAllotToUserResp %s\n", strRet.c_str());
}
void CTLMoblieSocket::OnRecvClanConfimReq( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;
	uint16 clanid;
	uint32 dst;
	uint8  action;

	in >> clanid >> dst >> action >> nResult;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_ACTION] = Json::Value(action);
	jsValue[JSKEY_DSTUIN] = Json::Value(dst);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanConfimReq %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanResult( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;
	uint16 clanid;
	uint32 dst;

	in >> clanid >> dst >> nResult;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_DSTUIN] = Json::Value(dst);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanResult %s\n", strRet.c_str());
}

//请求部落捐献
void CTLMoblieSocket::OnRecvClanDonate( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;
	uint8	donateType;
	uint32 nextTime;

	in >> nResult >> donateType >> nextTime;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_CLAN_DONATE_TYPE] = Json::Value(donateType);
	jsValue[JSKEY_CLAN_DONATE_NEXTTIME] = Json::Value(nextTime);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanDonate %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanRecruit( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint16 nResult;
	uint16 soldierType;
	uint8 soldierNum;
	uint32 contributionVal;

	in >> nResult >> soldierType >> soldierNum >> contributionVal;

	jsValue[JSKEY_RESULT] = Json::Value(nResult);
	jsValue[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
	jsValue[JSKEY_SOLDIER_NUM] = Json::Value(soldierNum);
	jsValue[JSKEY_CLAN_AVAILABLE_CONTRIBUTE] = Json::Value(contributionVal);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanRecruit %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanDonateNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	ParseClanDonate(in, jsValue);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanDonateNotify %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanDonateTimeInfoNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint32 contributionVal;		//可用贡献
	uint16 todayVal;			//今日贡献
	uint16 buildNum;			//免费课操作次数
	uint32 nextBuildTime;
	uint32 nextDonateTime;	
	uint32 nextDonateDiamondTime;	


	in >> contributionVal >> todayVal >> buildNum >> nextBuildTime >> nextDonateTime >> nextDonateDiamondTime;

	jsValue[JSKEY_CLAN_AVAILABLE_CONTRIBUTE] = Json::Value(contributionVal);
	jsValue[JSKEY_CLAN_CONSTRIBUION] = Json::Value(todayVal);
	jsValue[JSKEY_CLAN_BUILD_NUM] = Json::Value(buildNum);
	jsValue[JSKEY_CLAN_BUILD_TIME] = Json::Value(nextBuildTime);
	jsValue[JSKEY_CLAN_DONATE_WATER_TIME] = Json::Value(nextDonateTime);
	jsValue[JSKEY_CLAN_DONATE_DIAMOND_TIME] = Json::Value(nextDonateDiamondTime);
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanDonateTimeInfoNotify %s\n", strRet.c_str());

}

void CTLMoblieSocket::ParseClanDonate( InPacketEx& in, Json::Value& jsValue )
{

	uint16 clanID;
	uint32 uin;
	string strNick;
	in >> clanID >> uin >> strNick;

	jsValue[JSKEY_CLAN_ID] = Json::Value(clanID);
	jsValue[JSKEY_DSTUIN] = Json::Value(uin);
	jsValue[JSKEY_DSTNICK] = Json::Value(strNick);
}

void CTLMoblieSocket::OnRecvClanLastWimpointRankNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 num = 0;

	in >> num;
	Json::Value jsList;
	for(uint16 i = 0; i < num; i++)
	{
		Json::Value item;
		uint32 uin;
		string nick = "";
		uint32 winPoint;
		in  >> uin >> nick >> winPoint;

		item[JSKEY_UIN] = Json::Value(uin);
		item[JSKEY_NICK] = Json::Value(nick);
		item[JSKEY_CLAN_WINPOINT] = Json::Value(winPoint);
		jsList.append(item);
	}

	jsValue[JSKEY_CLAN_WINPOINT_RANKLIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanLastWimpointRankNotify %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanCurWimpointRankNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 num = 0;

	in >> num;
	Json::Value jsList;
	for(uint16 i = 0; i < num; i++)
	{
		Json::Value item;
		uint32 uin;
		string nick = "";
		uint32 winPoint;
		in  >> uin >> nick >> winPoint;

		item[JSKEY_UIN] = Json::Value(uin);
		item[JSKEY_NICK] = Json::Value(nick);
		item[JSKEY_CLAN_WINPOINT] = Json::Value(winPoint);
		jsList.append(item);
	}

	jsValue[JSKEY_CLAN_WINPOINT_RANKLIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanCurWimpointRankNotify %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanTotalWinPointNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);

	uint32 seasonNum;				//赛季
	uint32 totalWinPointVal;		//部落总胜点
	uint32 rankNum;					//预计排名
	uint32 sizeNum;
	uint64 nextSeasonTime;

	in >> seasonNum >> totalWinPointVal >> rankNum >>  nextSeasonTime >> sizeNum;

	jsValue[JSKEY_CLAN_SEASON_NUM] = Json::Value(seasonNum);
	jsValue[JSKEY_CLAN_WINPOINT] = Json::Value(totalWinPointVal);
	jsValue[JSKEY_RANK_NUM] = Json::Value(rankNum);

	char buf[256] = {0};
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%llu", nextSeasonTime);
	jsValue[JSKEY_CLAN_TIME] = Json::Value(buf);

	Json::Value jsList;
	for(uint8 i = 0; i < sizeNum; i++)
	{
		Json::Value item;
		uint16 clanid;
		string clanName;
		uint32 clanRankNum;
		uint32 clanPoint;				
		in  >> clanid >> clanName >> clanRankNum >> clanPoint;

		item[JSKEY_CLAN_ID] = Json::Value(clanid);
		item[JSKEY_CLAN_NAME] = Json::Value(clanName);
		item[JSKEY_RANK_NUM] = Json::Value(clanRankNum);
		item[JSKEY_CLAN_WINPOINT] = Json::Value(clanPoint);
		jsList.append(item);
	}
	jsValue[JSKEY_CLAN_WINPOINT_RANK_LIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanTotalWinPointNotify %s\n", strRet.c_str());

}

void CTLMoblieSocket::OnRecvClanAwardListNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint8 nSize = 0;
	uint64 goldNum;
	uint64 holyWaterNum;
	uint64 gemstoneNum;
	in >> goldNum >> holyWaterNum >> gemstoneNum;
	char buf[256] = {0};
	sprintf(buf, "%llu", goldNum);
	jsValue[JSKEY_RES_GOLD] = Json::Value(buf);
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%llu", holyWaterNum);
	jsValue[JSKEY_RES_HOLYWARTER] = Json::Value(buf);
	//jsValue[JSKEY_RES_BLACKWATER] = Json::Value(blackWater);
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%llu", gemstoneNum);
	jsValue[JSKEY_RES_GEMSTONE] = Json::Value(buf);

// 	in >> nSize;
// 	Json::Value jsList;
// 	for(uint16 i = 0; i < nSize; i++)
// 	{
// 		Json::Value item;
// 		uint16 typeID;			//资源类型
// 		uint32 num;				//资源数量
// 		in  >> typeID >> num;
// 
// 		item[JSKEY_RES_ID] = Json::Value(typeID);
// 		item[JSKEY_RES_CURR] = Json::Value(num);
// 		jsList.append(item);
// 	}
// 
// 	jsValue[JSKEY_CLAN_RESOURCE_LIST] = jsList;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanAwardListNotify %s\n", strRet.c_str());
}
void CTLMoblieSocket::ParseClanAwardAllot(InPacketEx& in, Json::Value& jsValue)
{
	uint16 clanid;
	uint32 uin = 0;
	string nickName = "";
	uint32 goldNum;
	uint32 holyWaterNum;
	uint32 gemstoneNum;
	in >> clanid >> uin >> nickName >> goldNum >> holyWaterNum >> gemstoneNum;

	jsValue[JSKEY_CLAN_ID] = Json::Value(clanid);
	jsValue[JSKEY_UIN] = Json::Value(uin);
	jsValue[JSKEY_NICK] = Json::Value(nickName);
	jsValue[JSKEY_RES_GOLD] = Json::Value(goldNum);
	jsValue[JSKEY_RES_HOLYWARTER] = Json::Value(holyWaterNum);
	jsValue[JSKEY_RES_GEMSTONE] = Json::Value(gemstoneNum);	
}
void CTLMoblieSocket::OnRecvClanAwardAllotNotify( InPacketEx &in, uint16 cmd )
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	ParseClanAwardAllot(in,jsValue);

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanAwardAllotNotify %s\n", strRet.c_str());

}

void CTLMoblieSocket::OnRecvClanRankAwardMailNotify(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint32 seasonNum;
	uint32 rankNum;
	uint8 nSize = 0;
	in >> seasonNum >> rankNum >> nSize;

	Json::Value jsList;
	for(uint8 i = 0; i < nSize; i++)
	{
		Json::Value item;
		uint16 typeID;			//资源类型
		uint32 num;				//资源数量
		in  >> typeID >> num;

		item[JSKEY_RES_ID] = Json::Value(typeID);
		item[JSKEY_RES_CURR] = Json::Value(num);
		jsList.append(item);
	}

	jsValue[JSKEY_CLAN_RESOURCE_LIST] = jsList;
	jsValue[JSKEY_CLAN_SEASON_NUM] = seasonNum;
	jsValue[JSKEY_RANK_NUM] = rankNum;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanAwardAllotNotify %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanAttackHistoryNotify(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	uint32 offensePid = 0;
	uint32 offenseUin = 0; 
	uint32 defendPid = 0;
	uint32 defendUin = 0; 
	uint32 attackTime = 0;
	uint32 keyId = 0;
	uint32 offenseGameid = 0;
	uint32 defendGameid = 0;

	uint16 cup = 0;
	uint8 percent = 0;
	uint8  leagueLevel = 0;

	uint32 clanId = 0;
	uint32 gold = 0;
	uint32 holywarter = 0;
	uint32 blackwater = 0;
	uint8 size = 0;
	uint8 packetNum = 1;
	uint8 packetIndex = 1;


	in >> packetNum >> packetIndex;
	in >> size;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PACKET_TOTAL_NUM] = Json::Value(packetNum);
	jsValue[JSKEY_PACKET_TOTAL_INDEX] = Json::Value(packetIndex);
	for (int i = 0; i < size; ++i)
	{
		std::string name ;	
		std::string clanName ;
		Json::Value attack;
		in >> offensePid;
		in >> offenseUin;
		in >> defendPid;
		in >> defendUin;
		in >> attackTime;
		in >> keyId;
		in >> offenseGameid;
		in >> defendGameid;
		attack[JSKEY_OFFENSE_PID] = Json::Value(offensePid);
		attack[JSKEY_OFFENSE_UIN] = Json::Value(offenseUin);
		attack[JSKEY_OFFENSE_GAMEID] = Json::Value(offenseGameid);
		attack[JSKEY_DEFEND_PID] = Json::Value(defendPid);
		attack[JSKEY_DEFEND_UIN] = Json::Value(defendUin);
		attack[JSKEY_DEFEND_GAMEID] = Json::Value(defendGameid);
		attack[JSKEY_ATTACK_TIME] = Json::Value(attackTime);
		attack[JSKEY_DB_KEYID] = Json::Value(keyId);

		//掠夺资源
		in >> gold;
		in >> holywarter;
		in >> blackwater;
		attack[JSKEY_RES_GOLD] = Json::Value(gold);
		attack[JSKEY_RES_HOLYWARTER] = Json::Value(holywarter);
		attack[JSKEY_RES_BLACKWATER] = Json::Value(blackwater);
		//进攻方信息（本部落成员信息）
		in >> cup;
		in >> leagueLevel;
		in >> name;		
		in >> clanName;
		in >> clanId;
		Json::Value userInfo;
		userInfo[JSKEY_CUP] = Json::Value(cup);
		userInfo[JSKEY_LEAGUELEVEL] = Json::Value(leagueLevel);
		userInfo[JSKEY_USERNICK] = Json::Value(name);
		userInfo[JSKEY_CLAN_NAME] = Json::Value(clanName);

		attack[JSKEY_USER_INFO] = userInfo;
		//防守方信息

		uint16 defend_cup;
		uint8 defend_leagueLevel;
		string defend_name;
		string defend_clanName;
		uint32 defend_clanID; 
		in >> defend_cup;
		in >> defend_leagueLevel;
		in >> defend_name;
		in >> defend_clanName;
		in >> defend_clanID;
		Json::Value defend_userInfo;
		defend_userInfo[JSKEY_CUP] = Json::Value(defend_cup);
		defend_userInfo[JSKEY_LEAGUELEVEL] = Json::Value(defend_leagueLevel);
		defend_userInfo[JSKEY_USERNICK] = Json::Value(defend_name);
		defend_userInfo[JSKEY_CLAN_NAME] = Json::Value(defend_clanName);
		attack[JSKEY_CLAN_DEFEND_USER_INFO] = defend_userInfo;
		//派兵户信息
		uint8 soldierSize = 0;
		in >> soldierSize;
		Json::Value jsSoldier;
		for (int j =0; j < soldierSize; ++j)
		{
			uint16 soldierType = 0;
			uint8 soldierNum = 0;
			uint8 soldierLevel = 0;
			in >> soldierType;
			in >> soldierNum;
			in >> soldierLevel;
			jsSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
			jsSoldier[JSKEY_SOLDIER_NUM] = Json::Value(soldierNum);
			jsSoldier[JSKEY_SOLDIER_LEVEL] = Json::Value(soldierLevel);
			attack[JSKEY_SEND_SOLDIER].append(jsSoldier);
		}
		uint8 cupNum = 0;
		uint8 warStar = 0;
		uint8 canRevenge = 0;
		in >> cupNum >> warStar >> percent >> canRevenge;
		attack[JSKEY_CUP] = Json::Value(cupNum);
		attack[JSKEY_WAR_STAR_NUM] = Json::Value(warStar);
		attack[JSKEY_PERCENT] = Json::Value(percent);
		attack[JSKEY_CANREVENGE] = Json::Value(canRevenge);
		jsValue[JSKEY_ATTACK_LIST].append(attack);
	}
	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanAttackHistoryNotify %s\n", strRet.c_str());
}

void CTLMoblieSocket::OnRecvClanWarBastionInfo(InPacketEx &in, uint16 cmd)
{
	Json::Value jsValue;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	uint16 result;
	uint32 curWinPointVal;
	uint32 lastWinPointVal;
	in >> result >> curWinPointVal >> lastWinPointVal;
	jsValue[JSKEY_RESULT] = result;
	jsValue[JSKEY_CLAN_WINPOINT] = curWinPointVal;
	jsValue[JSKEY_CLAN_LAST_WINPOINT] = lastWinPointVal;

	Json::FastWriter fastWriter;
	std::string strRet = fastWriter.write(jsValue);
	if (m_funOnRecv)
	{
		m_funOnRecv(strRet.c_str(), strRet.length());
	}
	LOG(4)("TLMoblieSocket::OnRecvClanWarBastionInfo %s\n", strRet.c_str());
}