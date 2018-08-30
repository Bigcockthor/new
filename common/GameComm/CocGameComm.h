#ifndef INC_MOBLIECHATCOMM_H
#define INC_MOBLIECHATCOMM_H

#include "tcpChatComm.h"
#include "mobiledef.h"
#include "TcpPacket.h"
#include "json/json.h"
#include <list>
#include "Singleton.h"
#include "GameStruct/CocCmdDefine.h"
#include "include/coretime.h"

//////////////////////////////////////////////////////////////////////////
//�ƶ���ע��ӿ�
typedef void (*ONRECV)(const char* pData, int nLen);
//Ӧ������ת���ɵ�Э������
typedef void (*ONSEND)(const char* pData, int nLen);
typedef void (*ONDISCONNECT)(int nState);
typedef void (*ONCONNECT)(int nState);
typedef void (*ONTIMER)();
//////////////////////////////////////////////////////////////////////////

//Ψһ��ʶ
class SerialBuild
{
public:
	uint16 m_buildType;			//����(����)
	uint8 m_num;			//�ȼ�
};

class CTLMoblieSocket:public CTLConnector
{
public:
	enum
	{
		TINER_ON,
		TIMER_OFF,
	};
	CTLMoblieSocket();
	virtual ~CTLMoblieSocket();
	void RegistCallBack(ONRECV funOnRecv, ONSEND funOnSend, ONCONNECT funOnConnect, ONDISCONNECT funOnDisConnect, ONTIMER funOnTimer);
	void UnRegistCallBack();
	int SendJsonData(void* pData, int nLen);
	virtual void OnRecvKeepalive(InPacketEx &in);
//ע��ʱ������һ��Ϊ 5 10, ����һ��keepalive��ʱ���������Σ�����Ϊ5 ��ʱʱ�����30s
	uint8 SetTimeoutInteval(uint8 interval);

public:
//��������
	int SendRequireUserInfoPacket(uint32 pid, uint32 uin, uint16 cmd, const char* packetId);
	int SendUserCmdPacket(uint16 cmd, const char* packetId);
	//��ȡ��ͼ��Ϣ
	int SendGetUserMapData(Json::Value &val);
	//��ȡ������ʿ������
	int SendGetUpdateSoldierInfo(Json::Value &val);
	//���˶���
	int sendGetWorkerList(Json::Value &val);
	//ѵ����������
	int sendGetProduceList(Json::Value &val);
	//��ǰӵ�е�ʿ������
	int sendGetSoldierList(Json::Value &val);
	//��ǰʿ���ȼ�����
	int sendGetSoldierLevelList(Json::Value &val);
	//�����б�
	int sendGetSpeedUpList(Json::Value &val);
	//�ɾ��б�
	int sendAchievementList(Json::Value &val);
	//�ɾ��б�
	int sendGetServetPushList(Json::Value &val);
	//ս����ʷ��¼
	int sendAttackHistoryList(Json::Value &val);
	//�ؿ���ʷ��¼
	int sendTollGateHistoryList(Json::Value &val);
	//�鿴�ؿ�
	int sendGetTollGateMapInfo(Json::Value &val);
	int sendGetTollGateMapInfo(uint8 gateIndex, const char* packetId);	
	//��ȡ�û�������Ϣ
	int SendGetUserInfoData(Json::Value &val);
	//��ȡ�û�������Ϣ
	int SendGetRankList(Json::Value &val);
	//��ѯ�һ�����
	int SendSelectStationMoney(Json::Value &val);
	int SendPlatformMoneyBuyGemston(Json::Value &val);
	int SendStationMoneyBuyResource(Json::Value &val);
	//��ȡ������ȴʣ��ʱ���б�
	int SendGetShieldCoolTimeLeftList(Json::Value &val);
	//��ȡ�ʼ��б�
	int SendGetMailMsgList(Json::Value &val);	
	//��ȡ���߽���������Ϣ��������ǰ�Ի�ȡ�Ľ�����ʱ����Ϣ��
	int SendGetOnlinePrizeList(Json::Value &val);	
	int SendGetCurrOnlinePrize(Json::Value &val);	
	//��ȡ�ջ�Ծ����
	int SendGetDayActiveTaskPrizeInfo(Json::Value &val);	
	//��ȡ�ջ����
	int SendGetDayActiveTaskList(Json::Value &val);	
	//��ȡ�ջ��
	int SendGetCurrDayActivePrize(Json::Value &val);
	//ʤ������
	int	SendWinnerMsg(Json::Value &val);
	//������ʯ��Ϣ
	int ReqBuyGemstoneInfo(Json::Value &val);
public:
	//�����
	//��¼
	int SendUserLogin(Json::Value& val);
	//���콨����
	int SendCreatBuilding(Json::Value &val);
	int SendCreatBuilding(uint16 buildingType, uint8 xPos, uint8 yPos, uint8 useGemston, const char* packetId);
	//�������
	int SendCompletedImmediately(Json::Value &val);
	int SendCompletedImmediately(uint16 buildingType, uint8 buildingNum, uint8 type, const char* packetId);
	//����������
	int SendUpdateBuilding(Json::Value &val);
	int SendUpdateBuilding(uint16 buildingType, uint8 buildingNum, uint8 useGemston, const char* packetId);
	//ȡ������ ����
	int SendCancelBuilding(Json::Value &val);
	int SendCancelBuilding(uint16 buildingType, uint8 buildingNum, const char* packetId);
	//�ƶ�����
	int SendMoveBuilding(Json::Value &val);
	int SendMoveBuilding(uint16 buildType, uint8 buildingNum, uint8 dstXPos, uint8 dstYPos, const char* packetId);
	//�Ƴ�����
	int SendRemoveBuilding(Json::Value &val);
	//ȡ���Ƴ�
	int SendCancelRemoveBuilding(Json::Value &val);
	//�ռ���Դ
	int SendCollectResources(Json::Value &val);
	int SendCollectResources(uint16 buildingType, uint8 builddingNum, const char* packetId);
	//��ʯ����Դ
	int SendGemstoneBuyResource(Json::Value &val);
	int SendGemstoneBuyResource(uint8 resType, uint32 resNum, const char* packetId);
	//ѵ��ʿ��
	int SendTrainSoldier(Json::Value &val);
	int SendTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, uint8 useGemston, const char* packetId);
	//��������
	int SendProduceMagic(Json::Value &val);
	int SendProduceMagic(uint8 magicFactoryIndex, uint16 soldierType, uint8 num, const char* packetId);
	//��������
	int SendSpeedUp(Json::Value &val);
	int SendSpeedUp(std::vector<SerialBuild> &vecBuild, const char* packetId);
	//ȡ��ѵ��ʿ��
	int SendCancelTrainSoldier(Json::Value &val);
	int SendCancelTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, const char* packetId);
	//����ʿ��
	int SendUpdateSoldierLevel(Json::Value &val);
	int SendUpdateSoldierLevel(uint16 soldierType, uint8 useGemston, const char* packetId);
	//��ȡ������Ϣ	
	int SendGetCanUseSoldier(Json::Value &val);
	int SendGetCanUseSoldier(const char* packetId);
	//�ɱ�����
	int SendSoldiers(Json::Value &val);
	int SendSoldiers(uint32 soldierId, uint8 group, uint8 soldierNum, uint8 xpos, uint8 ypos, uint32 timeOffset, const char* packetId);
	//�ͷŷ���
	int SendMagic(Json::Value &val);
	//ɾ��ʿ��
	int SendRemoveSoldiers(Json::Value &val);
	//ƥ��
	int SendMachingUser(Json::Value &val);
	void OnRecvMachingUserMap(InPacketEx &in, uint16 cmd);
	int SendCancelMaching(Json::Value &val);
	int SendCancelMaching(uint32 pid, uint32 uin, const char* packetId);	
	//��ȡ������ʷ��ͼ
	int SendGetAttackHistoryMap(Json::Value &val);
	//void OnRecvSvrPushWorkingList(InPacketEx &in);
	//��ȡ�ɾ�
	int SendApplyToGetAchievement(Json::Value &val);
	int SendApplyToGetAchievement(uint16 achvType, uint8 achvLevel, const char* packetId);
	//��ȡ����
	int SendApplyToGetMailPrize(Json::Value &val);
	//ɾ���ʼ��ӿ�
	int SendDeleteMailMsg(Json::Value &val);
	//��ȡ�ɱ���¼
	int SendGetSoldierRecord(Json::Value &val);	
	//��ǽ�����ƶ�
	int SendWallMutiMove(Json::Value &val);
	//��ǽ��������
	int SendWallMutiUpdate(Json::Value &val);
	int SendWallMutiUpdate(std::vector<uint8> &wall, uint8 useGemston, const char* packetId);
	//���򻤶�
	int SendBuyShield(Json::Value &val);
	//����װ��
	int SendBuyOrnament(Json::Value &val);
	int SendBuyOrnament(uint16 buildType, uint8 xpos, uint8 ypos, uint8 useGemstone, const char* packetId);
	int SendSellOrnament(Json::Value &val);
	int SendSellOrnament(uint16 buildingType, uint8 builddingNum, const char* packetId);
	//���͸���
	int SendMapCopy(Json::Value &val);
	int SendMapCopy(uint8 srcMode, uint8 srcIndex, uint8 dstMode, uint8 dstIndex, const char* packetId);
	//���ͱ༭
	int SendMapEdite(Json::Value &val);
	//ս��
	int SendBuildingReport(Json::Value &val);
	int SendResourceReport(Json::Value &val);
	int SendTerminatAttack(Json::Value &val);
	int SendTerminatTollGate(Json::Value &val);
	//�ǳ�
	int SendLogoutRoom(Json::Value& val);
	inline void SetConnectionStatus(MB_CHAT_CONN_STATUS status){m_ConnectionStatus = status;}
	inline MB_CHAT_CONN_STATUS  GetConnectionStatus(){ return m_ConnectionStatus;};
	//����ظ�
	int SendRecoverTrap(Json::Value &val);
	//���ֽ̳̲���
	int SendSetNewUserStep(Json::Value &val);
	//��������
	int SendSetUserName(Json::Value &val);
	//��������
	int SendChangeUserName(Json::Value &val);
	//����
	int SendUserRevenge(Json::Value &val);
	 //ָ���˺�ƥ��
	int SendMachingUserWithId(Json::Value &val);
	int SendGameChallenge(Json::Value &val);
	int SendOrnamentUpPercent(Json::Value &val);
	int SendGetChallengeRankingList(Json::Value &val);
	int SendFinishFistCharge(Json::Value &val);

	//�����ֵܹ�ϵ���״̬ COC_BROTHERHOOD_INFO
	int SendBrotherhoodReq(Json::Value &val);

	//�����ֵܹ�ϵ�б� COC_BROTHERLSIT_INFO
	int SendBrotherListReq(Json::Value& val);

	//��ȡ�ֵ�������
	int SendBrotherTaskReward(Json::Value& val);

	int SendBindBrother(Json::Value& val);

	//��������Ϣ�б�
	int SendClanListInfoReq(Json::Value& val);

	//�����ҵĲ�����Ϣ ��  ���������б� cmdֵ��ͬ������ͬ
	int SendClanInfoReq(Json::Value& val);

	//������벿�䣬ȡ������ action 1 ���룬0ȡ������
	int SendClanOperate(Json::Value& val);

	//�뿪 ���߳�����  �����ߺ�dst��ͬΪ�����뿪����֮Ϊ���������߳�
	int SendClanLeave(Json::Value& val);

	//��������
	int SendCreateClan(Json::Value& val);

	//ɾ������
	int SendDeleteClan(Json::Value& val);
	
	//�޸Ĳ�����Ϣ ����������������Ͳ��乫��
	int SendModifyClanInfo(Json::Value& val);

	//��������
	int SendSearchClan(Json::Value& val);

	//��������
	int SendChangeRank(Json::Value& val);

	//�������������� action 1 ͬ�⣬0�ܾ�
	int SendClanConfimReq(Json::Value& val);

	//����ȫվ��������
	int SendPidClanList(Json::Value& val);

	//���������
	int SendClanDonate(Json::Value& val);
	//�������
	void OnRecvClanDonate( InPacketEx &in, uint16 cmd );

	//���������ļ��
	int SendClanRecruit(Json::Value& val);
	//�������ļ��
	void OnRecvClanRecruit( InPacketEx &in, uint16 cmd );

	//�������֪ͨ
	void OnRecvClanDonateNotify( InPacketEx &in, uint16 cmd );

	//���������ʱ�����Ϣ֪ͨ
	int OnSendClanDonateTimeInfoNotify( Json::Value& val );
	//�������ʱ�����Ϣ֪ͨ
	void OnRecvClanDonateTimeInfoNotify( InPacketEx &in, uint16 cmd );

	//--------------------------ս������-----------------------------------
	//����������ʤ������֪ͨ
	void OnRecvClanLastWimpointRankNotify( InPacketEx &in, uint16 cmd );
	//���䱾����ʤ������֪ͨ
	void OnRecvClanCurWimpointRankNotify( InPacketEx &in, uint16 cmd );
	//������ʤ������
	void OnRecvClanTotalWinPointNotify(InPacketEx &in, uint16 cmd);
	//ս��Ʒ������Ʒ����
	void OnRecvClanAwardListNotify(InPacketEx &in, uint16 cmd);
	//�ַ�ս��Ʒ��������
	void OnRecvClanAwardAllotNotify(InPacketEx &in, uint16 cmd);
	void ParseClanAwardAllot(InPacketEx& in, Json::Value& jsValue);
	//�������н����ʼ�
	void OnRecvClanRankAwardMailNotify(InPacketEx &in, uint16 cmd);
	//����ս������
	void OnRecvClanAttackHistoryNotify(InPacketEx &in, uint16 cmd);

	//����ս������
	int SendClanWarBastionInfo(Json::Value& val);

	//ս�����ݻ�����Ϣ
	void OnRecvClanWarBastionInfo(InPacketEx &in, uint16 cmd);
	//����ַ�����
	int SendClanAllotToUserReq(Json::Value& val);
	//�ַ���������
	void OnRecvClanAllotToUserResp(InPacketEx &in, uint16 cmd);
	
	

public:	
	//��¼����
	void OnRecvLoginRoomReply(InPacketEx &in, uint16 cmd);
	//�����˷����������˴���֮���·��Ľ��
	void OnRecvUserMapData(InPacketEx &in, uint16 cmd);
	void OnCreatBuilding(InPacketEx &in);
	void OnRecvMoveBuilding(InPacketEx &in);
	void OnRecvReMoveBuilding(InPacketEx &in);
	void OnRecvUpDateBuilding(InPacketEx &in);
	void OnRecvCollectResources(InPacketEx &in);
	void OnRecvTrainSoldier(InPacketEx &in);
	void OnRecvCanUseSoldier(InPacketEx &in, uint16 comd);
	void OnRecvRankList(InPacketEx &in, uint16 cmd);

	//ʿ���ȼ�
	void OnRecvSoldierLevel(InPacketEx &in, uint16 cmd);
	void OnRecvSoldierUpdate(InPacketEx &in, uint16 cmd);
	void OnRecvUserInfo(InPacketEx &in, uint16 cmd);
	void OnRecvFindUserMap(InPacketEx &in);
	//������ʷ��ͼ
	void OnRecvAttackHistoryMap(InPacketEx &in, uint16 cmd);
	//�ؿ���ͼ
	void OnRecvTollGateMap(InPacketEx &in, uint16 cmd);
	void OnRecvTollInfoList(InPacketEx &in, uint16 cmd);
	//�����·�����������
	void OnRecvSvrPushProduceList(InPacketEx &in, uint16 cmd);
	//�յ��ɾ����֪ͨ
	void OnRecvAchievementComplete(InPacketEx &in);
	//�յ��ɼ���Ϣ
	void OnRecvAchievementInfo(InPacketEx &in, uint16 cmd);
	//�����·�����������Ϣ
	void OnRecvWorkingList(InPacketEx &in, uint16 cmd);
	//�յ������֪ͨ��Ϣ
	void OnRecvGameNotifyMessage(InPacketEx &in);
	//ս����ʷ
	void OnRecvAttackHistory(InPacketEx &in, uint16 cmd);
	//���ط� ��ʷ��Ϣ
	void OnRecvDefendUserOnAttackInfo(InPacketEx &in, uint16 cmd);
	void OnRecvOffendUserSoldierInfo(InPacketEx &in, uint16 cmd);
	//�յ��ɱ���¼
	void OnRecvSoldierRecord(InPacketEx &in);
	/**
	* @file   <CocGameComm.h>
	* @fn  - OnRecvSpeedUpList
	* @brief -  ���ն�Ӧ�����ļ����б�
	* @param[in] in  ����������
	* @param[in] cmd  ��Ӧ��cmd
	* @attention  
	* @remark 1.2015/11/12 11 : 18 created by SHIQINGHUI version 1.0  
	* @return  
	*/
	void OnRecvSpeedUpList(InPacketEx &in, uint16 cmd);
	//����˻���ѯ
	void OnRecvSelectPlatformMoney(InPacketEx &in, uint16 cmd);
	void OnRecvSelectStationMoney(InPacketEx &in, uint16 cmd);
	void OnRecvChangeUserName(InPacketEx &in, uint16 cmd);
	//������ȴʣ��ʱ���б�
	void OnRecvShieldCoolTimeLeftList(InPacketEx &in, uint16 cmd);
	//ϵͳ��Ϣ
	void OnRecvSystemMsg(InPacketEx &in, uint16 cmd);
	//�ʼ�
	void OnRecvMailMsg(InPacketEx &in, uint16 cmd);
	void OnRecvForceOffLine(InPacketEx &in, uint16 cmd);
	//�յ����߽����б�
	void OnRecvOnlinePrizeListInfo(InPacketEx &in, uint16 cmd);
	void OnRecvOrnamentUpPercent(InPacketEx &in, uint16 cmd);
	//�ջ����
	void OnRecvDayActiveTaskList(InPacketEx &in, uint16 cmd);
	void OnRecvDayActiveTaskPrizeInfo(InPacketEx &in, uint16 cmd);
	void OnRecvChallengeRankingList(InPacketEx &in, uint16 cmd);
	void OnRecvChallengeDescribe(InPacketEx &in, uint16 cmd);
	void OnRecvWinnerMsg(InPacketEx &in, uint16 cmd);
	void OnRecvBuyGemstoneInfo(InPacketEx &in, uint16 cmd);
	void OnRecvChargeGemstone(InPacketEx &in, uint16 cmd);
	void OnRecvFirstChargeNotify(InPacketEx &in, uint16 cmd);
	void OnRecvFinishFisttChargeNotify(InPacketEx &in, uint16 cmd);
	void OnRecvBrotherhood(InPacketEx &in, uint16 cmd);
	void OnRecvBrotherList(InPacketEx &in, uint16 cmd);
	void OnRecvBrotheTaskReward(InPacketEx &in, uint16 cmd);
	void OnRecvBindBrotherResult(InPacketEx &in, uint16 cmd);



	//�޸Ĳ�����Ϣ����ֵ
	void OnRecvModifyClanInfoReplay(InPacketEx &in, uint16 cmd);

	//������Ϣ�������
	void OnRecvUpdateClanInfo(InPacketEx &in, uint16 cmd);

	//�û����벿��֪ͨ
	void OnRecvClanJon(InPacketEx &in, uint16 cmd);
	void ParseClanJoin(InPacketEx &in, Json::Value& jsVal);

	//�û��뿪����֪ͨ
	void OnRecvClanLeave(InPacketEx &in, uint16 cmd);
	void ParseClanLeave(InPacketEx &in, Json::Value& jsVal);

	//���� �뿪������
	void OnRecvClanResult(InPacketEx &in, uint16 cmd);

	//�ҵĲ�����Ϣ
	void OnRecvClanInfo(InPacketEx &in, uint16 cmd);

	//������Ϣ�б�
	void OnRecvClanList(InPacketEx &in, uint16 cmd);

	//����ɾ��������֪ͨ
	void OnRecvCreateDelClan(InPacketEx &in, uint16 cmd);

	//������벿���б���������
	void OnRecvClanReqAdd(InPacketEx &in, uint16 cmd);

	//������벿���б�����ɾ��
	void OnRecvClanReqDel(InPacketEx &in, uint16 cmd);

	//������벿���б�ȫ������
	void OnRecvClanReqAllList(InPacketEx &in, uint16 cmd);

	//�����Ա�б�
	void OnRecvClanMemList(InPacketEx &in, uint16 cmd);
	
	//��������֪ͨ
	void OnRecvClanUpdateLevel(InPacketEx &in, uint16 cmd);

	//������ݱ���㲥���в����Ա
	void OnRecvClanChangeNotify(InPacketEx &in, uint16 cmd);
	void ParseClanChangeNotify(InPacketEx &in, Json::Value& jsVal);
	
	void ParseClanDonate(InPacketEx& in, Json::Value& jsValue);
	//��������޸Ľ�� ֪ͨ������
	void OnRecvClanChangeRankResult(InPacketEx &in, uint16 cmd);
	
	//����״̬��������
	void OnRecvClanStateCache(InPacketEx &in, uint16 cmd);
	
	//����ȡ������
	void OnRecvClanOperate(InPacketEx &in, uint16 cmd);

	//���վܾ����벿�����봦����
	void OnRecvClanConfimReq(InPacketEx &in, uint16 cmd);

	
	
	
	
	
	
protected:
	//////////////////////////////////////////////////////////////////////////
	void ParseClanInfo(InPacketEx &in, Json::Value& valRet, bool bAddState);
	bool IsMySelf(uint32 pid, uint32 uin);
	void OnFailComm();
	//ͨѶ���������
	int SendKeepAlive();
	bool checkTimeOut();
	void ClearSendKeyQueue();

	OutPacketEx * createPacket_ACK(uint16 seq);
	OutPacketEx * createPacket_Head(bool needAck,uint16 cmd, const char* packetid = "");
	void CreatePacketHead(OutPacketEx &out,uint16 cmd,uint16 seq = 0);
	void InitSessionID();
	void Initialize();
	void Dispose();
	int SendAck(uint16 seq);
	bool OnRecvAck(uint32 seq);
	bool setWindow(uint16 seq);

	int sendDirect(OutPacketEx *out);

	int SendPacket(bool needAck = false,OutPacketEx *p=NULL);
	bool OnPacketReceived(InPacketEx &in);
	//���ݰ����
	bool ValidatePacket(InPacketEx &in);
	bool CheckSendPackerInQueue();
private:
	
	virtual void OnTimer();
	virtual void OnRecv(const char* pData, int nLen);
	void ClearSendQueue();
	virtual void OnDisConnect(int nState);
	virtual void OnConnect(int nState);
private:
	ONRECV				m_funOnRecv;
	//Ӧ������ת���ɵ�Э������
	ONSEND				m_funOnSend;
	ONDISCONNECT		m_funOnDisConnect;
	ONCONNECT			m_funOnConnect;
	ONTIMER				m_funOnTimer;

	uint32				m_lastCheckSendQueue;		//���һ�μ�鷢�Ͷ���
	uint32				m_lastKeepAlive;				//���һ�ν��п�ʼ�µ�keepalive����
	uint32				m_lastKeepAliveReply;
	uint16				m_ver;
	uint16				m_CurrentSeq;			//��ǰ�����
	uint32				m_SessionID;			//�������Ӷ�Ӧ��Session���
	uint8				m_window[1 << 16];
	uint8				m_channelStatus;
	uint32				m_roomid;
	uint32				m_uin;
	uint32				m_pid;
	uint32				m_timer;
	list<OutPacketEx *> sendQueue;						//�������ݻ������������Ҫȷ�ϵ�����
	Mutex				m_mutextSend;
	MB_CHAT_CONN_STATUS m_ConnectionStatus;
	OnMicUerList m_confuserllist; //�û�����
	uint16 micSeqBuf[MAX_MIC_USER_NUM];
	WATI_STRUCT	m_waitData;
	RoomMember			m_roomMember;
	int m_interval;
	
};

#define GlobalMobile CTLSingleton<CTLMoblieSocket>::GetInstance() 

class CAutoFree
{
public:
	CAutoFree()
	{
#ifdef WIN32
		CoreSocket::SocketStartUp();
#endif
		GlobalMobile->StartUp();
	}
	~CAutoFree()
	{
		CTLSingleton<CTLMoblieSocket>::Distroy();
#ifdef WIN32
		CoreSocket::SocketCleanUp();
#endif
	}

};



#endif