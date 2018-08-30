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
//移动端注册接口
typedef void (*ONRECV)(const char* pData, int nLen);
//应用数据转换成到协议数据
typedef void (*ONSEND)(const char* pData, int nLen);
typedef void (*ONDISCONNECT)(int nState);
typedef void (*ONCONNECT)(int nState);
typedef void (*ONTIMER)();
//////////////////////////////////////////////////////////////////////////

//唯一标识
class SerialBuild
{
public:
	uint16 m_buildType;			//类型(种类)
	uint8 m_num;			//等级
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
//注意时间设置一般为 5 10, 这是一次keepalive的时长（共六次）设置为5 超时时间就是30s
	uint8 SetTimeoutInteval(uint8 interval);

public:
//主动请求
	int SendRequireUserInfoPacket(uint32 pid, uint32 uin, uint16 cmd, const char* packetId);
	int SendUserCmdPacket(uint16 cmd, const char* packetId);
	//获取地图信息
	int SendGetUserMapData(Json::Value &val);
	//获取升级的士兵队列
	int SendGetUpdateSoldierInfo(Json::Value &val);
	//工人队列
	int sendGetWorkerList(Json::Value &val);
	//训练生产队列
	int sendGetProduceList(Json::Value &val);
	//当前拥有的士兵队列
	int sendGetSoldierList(Json::Value &val);
	//当前士兵等级队列
	int sendGetSoldierLevelList(Json::Value &val);
	//加速列表
	int sendGetSpeedUpList(Json::Value &val);
	//成就列表
	int sendAchievementList(Json::Value &val);
	//成就列表
	int sendGetServetPushList(Json::Value &val);
	//战斗历史记录
	int sendAttackHistoryList(Json::Value &val);
	//关卡历史记录
	int sendTollGateHistoryList(Json::Value &val);
	//查看关卡
	int sendGetTollGateMapInfo(Json::Value &val);
	int sendGetTollGateMapInfo(uint8 gateIndex, const char* packetId);	
	//获取用户个人信息
	int SendGetUserInfoData(Json::Value &val);
	//获取用户个人信息
	int SendGetRankList(Json::Value &val);
	//查询兑换功能
	int SendSelectStationMoney(Json::Value &val);
	int SendPlatformMoneyBuyGemston(Json::Value &val);
	int SendStationMoneyBuyResource(Json::Value &val);
	//获取护盾冷却剩余时间列表
	int SendGetShieldCoolTimeLeftList(Json::Value &val);
	//获取邮件列表
	int SendGetMailMsgList(Json::Value &val);	
	//获取在线奖励配置信息（包括当前以获取的奖励和时长信息）
	int SendGetOnlinePrizeList(Json::Value &val);	
	int SendGetCurrOnlinePrize(Json::Value &val);	
	//获取日活跃配置
	int SendGetDayActiveTaskPrizeInfo(Json::Value &val);	
	//获取日活进度
	int SendGetDayActiveTaskList(Json::Value &val);	
	//获取日活奖励
	int SendGetCurrDayActivePrize(Json::Value &val);
	//胜利留言
	int	SendWinnerMsg(Json::Value &val);
	//请求购买宝石信息
	int ReqBuyGemstoneInfo(Json::Value &val);
public:
	//命令发送
	//登录
	int SendUserLogin(Json::Value& val);
	//建造建筑物
	int SendCreatBuilding(Json::Value &val);
	int SendCreatBuilding(uint16 buildingType, uint8 xPos, uint8 yPos, uint8 useGemston, const char* packetId);
	//立刻完成
	int SendCompletedImmediately(Json::Value &val);
	int SendCompletedImmediately(uint16 buildingType, uint8 buildingNum, uint8 type, const char* packetId);
	//升级建筑物
	int SendUpdateBuilding(Json::Value &val);
	int SendUpdateBuilding(uint16 buildingType, uint8 buildingNum, uint8 useGemston, const char* packetId);
	//取消建造 升级
	int SendCancelBuilding(Json::Value &val);
	int SendCancelBuilding(uint16 buildingType, uint8 buildingNum, const char* packetId);
	//移动建筑
	int SendMoveBuilding(Json::Value &val);
	int SendMoveBuilding(uint16 buildType, uint8 buildingNum, uint8 dstXPos, uint8 dstYPos, const char* packetId);
	//移除建筑
	int SendRemoveBuilding(Json::Value &val);
	//取消移除
	int SendCancelRemoveBuilding(Json::Value &val);
	//收集资源
	int SendCollectResources(Json::Value &val);
	int SendCollectResources(uint16 buildingType, uint8 builddingNum, const char* packetId);
	//宝石买资源
	int SendGemstoneBuyResource(Json::Value &val);
	int SendGemstoneBuyResource(uint8 resType, uint32 resNum, const char* packetId);
	//训练士兵
	int SendTrainSoldier(Json::Value &val);
	int SendTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, uint8 useGemston, const char* packetId);
	//生产法术
	int SendProduceMagic(Json::Value &val);
	int SendProduceMagic(uint8 magicFactoryIndex, uint16 soldierType, uint8 num, const char* packetId);
	//生产加速
	int SendSpeedUp(Json::Value &val);
	int SendSpeedUp(std::vector<SerialBuild> &vecBuild, const char* packetId);
	//取消训练士兵
	int SendCancelTrainSoldier(Json::Value &val);
	int SendCancelTrainSoldier(uint8 trainingCampIndex, uint16 soldierType, uint8 num, const char* packetId);
	//升级士兵
	int SendUpdateSoldierLevel(Json::Value &val);
	int SendUpdateSoldierLevel(uint16 soldierType, uint8 useGemston, const char* packetId);
	//获取军队信息	
	int SendGetCanUseSoldier(Json::Value &val);
	int SendGetCanUseSoldier(const char* packetId);
	//派兵功能
	int SendSoldiers(Json::Value &val);
	int SendSoldiers(uint32 soldierId, uint8 group, uint8 soldierNum, uint8 xpos, uint8 ypos, uint32 timeOffset, const char* packetId);
	//释放法术
	int SendMagic(Json::Value &val);
	//删除士兵
	int SendRemoveSoldiers(Json::Value &val);
	//匹配
	int SendMachingUser(Json::Value &val);
	void OnRecvMachingUserMap(InPacketEx &in, uint16 cmd);
	int SendCancelMaching(Json::Value &val);
	int SendCancelMaching(uint32 pid, uint32 uin, const char* packetId);	
	//获取进攻历史地图
	int SendGetAttackHistoryMap(Json::Value &val);
	//void OnRecvSvrPushWorkingList(InPacketEx &in);
	//领取成就
	int SendApplyToGetAchievement(Json::Value &val);
	int SendApplyToGetAchievement(uint16 achvType, uint8 achvLevel, const char* packetId);
	//领取奖励
	int SendApplyToGetMailPrize(Json::Value &val);
	//删除邮件接口
	int SendDeleteMailMsg(Json::Value &val);
	//获取派兵记录
	int SendGetSoldierRecord(Json::Value &val);	
	//城墙批量移动
	int SendWallMutiMove(Json::Value &val);
	//城墙批量升级
	int SendWallMutiUpdate(Json::Value &val);
	int SendWallMutiUpdate(std::vector<uint8> &wall, uint8 useGemston, const char* packetId);
	//购买护盾
	int SendBuyShield(Json::Value &val);
	//购买装饰
	int SendBuyOrnament(Json::Value &val);
	int SendBuyOrnament(uint16 buildType, uint8 xpos, uint8 ypos, uint8 useGemstone, const char* packetId);
	int SendSellOrnament(Json::Value &val);
	int SendSellOrnament(uint16 buildingType, uint8 builddingNum, const char* packetId);
	//阵型复制
	int SendMapCopy(Json::Value &val);
	int SendMapCopy(uint8 srcMode, uint8 srcIndex, uint8 dstMode, uint8 dstIndex, const char* packetId);
	//阵型编辑
	int SendMapEdite(Json::Value &val);
	//战报
	int SendBuildingReport(Json::Value &val);
	int SendResourceReport(Json::Value &val);
	int SendTerminatAttack(Json::Value &val);
	int SendTerminatTollGate(Json::Value &val);
	//登出
	int SendLogoutRoom(Json::Value& val);
	inline void SetConnectionStatus(MB_CHAT_CONN_STATUS status){m_ConnectionStatus = status;}
	inline MB_CHAT_CONN_STATUS  GetConnectionStatus(){ return m_ConnectionStatus;};
	//陷阱回复
	int SendRecoverTrap(Json::Value &val);
	//新手教程步骤
	int SendSetNewUserStep(Json::Value &val);
	//设置名称
	int SendSetUserName(Json::Value &val);
	//更改名称
	int SendChangeUserName(Json::Value &val);
	//复仇
	int SendUserRevenge(Json::Value &val);
	 //指定账号匹配
	int SendMachingUserWithId(Json::Value &val);
	int SendGameChallenge(Json::Value &val);
	int SendOrnamentUpPercent(Json::Value &val);
	int SendGetChallengeRankingList(Json::Value &val);
	int SendFinishFistCharge(Json::Value &val);

	//请求兄弟关系完成状态 COC_BROTHERHOOD_INFO
	int SendBrotherhoodReq(Json::Value &val);

	//请求兄弟关系列表 COC_BROTHERLSIT_INFO
	int SendBrotherListReq(Json::Value& val);

	//领取兄弟任务奖励
	int SendBrotherTaskReward(Json::Value& val);

	int SendBindBrother(Json::Value& val);

	//请求部落信息列表
	int SendClanListInfoReq(Json::Value& val);

	//请求我的部落信息 和  请求申请列表 cmd值不同其他相同
	int SendClanInfoReq(Json::Value& val);

	//申请加入部落，取消申请 action 1 申请，0取消申请
	int SendClanOperate(Json::Value& val);

	//离开 ，踢出工会  操作者和dst相同为主动离开，反之为被操作者踢出
	int SendClanLeave(Json::Value& val);

	//创建部落
	int SendCreateClan(Json::Value& val);

	//删除部落
	int SendDeleteClan(Json::Value& val);
	
	//修改部落信息 包括申请加入条件和部落公告
	int SendModifyClanInfo(Json::Value& val);

	//搜索部落
	int SendSearchClan(Json::Value& val);

	//任命操作
	int SendChangeRank(Json::Value& val);

	//处理工会申请请求 action 1 同意，0拒绝
	int SendClanConfimReq(Json::Value& val);

	//请求全站部落排行
	int SendPidClanList(Json::Value& val);

	//请求部落捐献
	int SendClanDonate(Json::Value& val);
	//部落捐献
	void OnRecvClanDonate( InPacketEx &in, uint16 cmd );

	//请求部落捐献募兵
	int SendClanRecruit(Json::Value& val);
	//部落捐献募兵
	void OnRecvClanRecruit( InPacketEx &in, uint16 cmd );

	//部落捐献通知
	void OnRecvClanDonateNotify( InPacketEx &in, uint16 cmd );

	//请求部落捐献时间等信息通知
	int OnSendClanDonateTimeInfoNotify( Json::Value& val );
	//部落捐献时间等信息通知
	void OnRecvClanDonateTimeInfoNotify( InPacketEx &in, uint16 cmd );

	//--------------------------战争堡垒-----------------------------------
	//部落上赛季胜点排行通知
	void OnRecvClanLastWimpointRankNotify( InPacketEx &in, uint16 cmd );
	//部落本赛季胜点排行通知
	void OnRecvClanCurWimpointRankNotify( InPacketEx &in, uint16 cmd );
	//部落总胜点推送
	void OnRecvClanTotalWinPointNotify(InPacketEx &in, uint16 cmd);
	//战利品创库物品推送
	void OnRecvClanAwardListNotify(InPacketEx &in, uint16 cmd);
	//分发战利品公告推送
	void OnRecvClanAwardAllotNotify(InPacketEx &in, uint16 cmd);
	void ParseClanAwardAllot(InPacketEx& in, Json::Value& jsValue);
	//赛季排行奖励邮件
	void OnRecvClanRankAwardMailNotify(InPacketEx &in, uint16 cmd);
	//部落战报推送
	void OnRecvClanAttackHistoryNotify(InPacketEx &in, uint16 cmd);

	//请求战争堡垒
	int SendClanWarBastionInfo(Json::Value& val);

	//战争堡垒基本信息
	void OnRecvClanWarBastionInfo(InPacketEx &in, uint16 cmd);
	//请求分发奖励
	int SendClanAllotToUserReq(Json::Value& val);
	//分发奖励返回
	void OnRecvClanAllotToUserResp(InPacketEx &in, uint16 cmd);
	
	

public:	
	//登录返回
	void OnRecvLoginRoomReply(InPacketEx &in, uint16 cmd);
	//向服务端发送命令，服务端处理之后下发的结果
	void OnRecvUserMapData(InPacketEx &in, uint16 cmd);
	void OnCreatBuilding(InPacketEx &in);
	void OnRecvMoveBuilding(InPacketEx &in);
	void OnRecvReMoveBuilding(InPacketEx &in);
	void OnRecvUpDateBuilding(InPacketEx &in);
	void OnRecvCollectResources(InPacketEx &in);
	void OnRecvTrainSoldier(InPacketEx &in);
	void OnRecvCanUseSoldier(InPacketEx &in, uint16 comd);
	void OnRecvRankList(InPacketEx &in, uint16 cmd);

	//士兵等级
	void OnRecvSoldierLevel(InPacketEx &in, uint16 cmd);
	void OnRecvSoldierUpdate(InPacketEx &in, uint16 cmd);
	void OnRecvUserInfo(InPacketEx &in, uint16 cmd);
	void OnRecvFindUserMap(InPacketEx &in);
	//进攻历史地图
	void OnRecvAttackHistoryMap(InPacketEx &in, uint16 cmd);
	//关卡地图
	void OnRecvTollGateMap(InPacketEx &in, uint16 cmd);
	void OnRecvTollInfoList(InPacketEx &in, uint16 cmd);
	//服务下发的生产队列
	void OnRecvSvrPushProduceList(InPacketEx &in, uint16 cmd);
	//收到成就完成通知
	void OnRecvAchievementComplete(InPacketEx &in);
	//收到成绩信息
	void OnRecvAchievementInfo(InPacketEx &in, uint16 cmd);
	//服务下发建筑队列信息
	void OnRecvWorkingList(InPacketEx &in, uint16 cmd);
	//收到服务的通知消息
	void OnRecvGameNotifyMessage(InPacketEx &in);
	//战斗历史
	void OnRecvAttackHistory(InPacketEx &in, uint16 cmd);
	//防守方 历史信息
	void OnRecvDefendUserOnAttackInfo(InPacketEx &in, uint16 cmd);
	void OnRecvOffendUserSoldierInfo(InPacketEx &in, uint16 cmd);
	//收到派兵记录
	void OnRecvSoldierRecord(InPacketEx &in);
	/**
	* @file   <CocGameComm.h>
	* @fn  - OnRecvSpeedUpList
	* @brief -  接收对应建筑的加速列表
	* @param[in] in  二进制数据
	* @param[in] cmd  对应的cmd
	* @attention  
	* @remark 1.2015/11/12 11 : 18 created by SHIQINGHUI version 1.0  
	* @return  
	*/
	void OnRecvSpeedUpList(InPacketEx &in, uint16 cmd);
	//金币账户查询
	void OnRecvSelectPlatformMoney(InPacketEx &in, uint16 cmd);
	void OnRecvSelectStationMoney(InPacketEx &in, uint16 cmd);
	void OnRecvChangeUserName(InPacketEx &in, uint16 cmd);
	//护盾冷却剩余时间列表
	void OnRecvShieldCoolTimeLeftList(InPacketEx &in, uint16 cmd);
	//系统消息
	void OnRecvSystemMsg(InPacketEx &in, uint16 cmd);
	//邮件
	void OnRecvMailMsg(InPacketEx &in, uint16 cmd);
	void OnRecvForceOffLine(InPacketEx &in, uint16 cmd);
	//收到在线奖励列表
	void OnRecvOnlinePrizeListInfo(InPacketEx &in, uint16 cmd);
	void OnRecvOrnamentUpPercent(InPacketEx &in, uint16 cmd);
	//日活进度
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



	//修改部落信息返回值
	void OnRecvModifyClanInfoReplay(InPacketEx &in, uint16 cmd);

	//部落信息发生变更
	void OnRecvUpdateClanInfo(InPacketEx &in, uint16 cmd);

	//用户进入部落通知
	void OnRecvClanJon(InPacketEx &in, uint16 cmd);
	void ParseClanJoin(InPacketEx &in, Json::Value& jsVal);

	//用户离开部落通知
	void OnRecvClanLeave(InPacketEx &in, uint16 cmd);
	void ParseClanLeave(InPacketEx &in, Json::Value& jsVal);

	//踢人 离开处理结果
	void OnRecvClanResult(InPacketEx &in, uint16 cmd);

	//我的部落信息
	void OnRecvClanInfo(InPacketEx &in, uint16 cmd);

	//部落信息列表
	void OnRecvClanList(InPacketEx &in, uint16 cmd);

	//创建删除部落结果通知
	void OnRecvCreateDelClan(InPacketEx &in, uint16 cmd);

	//申请加入部落列表增量增加
	void OnRecvClanReqAdd(InPacketEx &in, uint16 cmd);

	//申请加入部落列表增量删除
	void OnRecvClanReqDel(InPacketEx &in, uint16 cmd);

	//申请加入部落列表全量数据
	void OnRecvClanReqAllList(InPacketEx &in, uint16 cmd);

	//部落成员列表
	void OnRecvClanMemList(InPacketEx &in, uint16 cmd);
	
	//部落升级通知
	void OnRecvClanUpdateLevel(InPacketEx &in, uint16 cmd);

	//部落身份变更广播所有部落成员
	void OnRecvClanChangeNotify(InPacketEx &in, uint16 cmd);
	void ParseClanChangeNotify(InPacketEx &in, Json::Value& jsVal);
	
	void ParseClanDonate(InPacketEx& in, Json::Value& jsValue);
	//部落身份修改结果 通知操作人
	void OnRecvClanChangeRankResult(InPacketEx &in, uint16 cmd);
	
	//部落状态缓存数据
	void OnRecvClanStateCache(InPacketEx &in, uint16 cmd);
	
	//申请取消申请
	void OnRecvClanOperate(InPacketEx &in, uint16 cmd);

	//接收拒绝加入部落申请处理结果
	void OnRecvClanConfimReq(InPacketEx &in, uint16 cmd);

	
	
	
	
	
	
protected:
	//////////////////////////////////////////////////////////////////////////
	void ParseClanInfo(InPacketEx &in, Json::Value& valRet, bool bAddState);
	bool IsMySelf(uint32 pid, uint32 uin);
	void OnFailComm();
	//通讯层自身调用
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
	//数据包检测
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
	//应用数据转换成到协议数据
	ONSEND				m_funOnSend;
	ONDISCONNECT		m_funOnDisConnect;
	ONCONNECT			m_funOnConnect;
	ONTIMER				m_funOnTimer;

	uint32				m_lastCheckSendQueue;		//最后一次检查发送对列
	uint32				m_lastKeepAlive;				//最好一次进行开始新的keepalive动作
	uint32				m_lastKeepAliveReply;
	uint16				m_ver;
	uint16				m_CurrentSeq;			//当前包序号
	uint32				m_SessionID;			//本次连接对应的Session编号
	uint8				m_window[1 << 16];
	uint8				m_channelStatus;
	uint32				m_roomid;
	uint32				m_uin;
	uint32				m_pid;
	uint32				m_timer;
	list<OutPacketEx *> sendQueue;						//发送数据缓冲区，存放需要确认的数据
	Mutex				m_mutextSend;
	MB_CHAT_CONN_STATUS m_ConnectionStatus;
	OnMicUerList m_confuserllist; //用户在麦
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