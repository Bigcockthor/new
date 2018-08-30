#ifndef INC_MOBILEDEF_H
#define INC_MOBILEDEF_H


#include <list>
#include <vector>

#ifdef WIN32
#include <Windows.h>
#endif

#include "include/icqtypes.h"
#include "TcpPacket.h"


//错误代码
enum MB_CHAT_ERROR_CODE
{
	E_SUCCESS = 0,				//成功
	E_CANNOT_LINK_SERVER,		//不能连接服务器（登录时）
	E_OUT_OF_CONNECTION,		//失去与服务器连接
	E_NOT_IN_ROOM,				//尚未进入房间
	E_TIMEOUT,					//发送超时
};

enum MB_CHANNEL_SVC_STATUS
{
	CHANNEL_DISCONNECTED,		//已断开状态
	CHANNEL_CONNECTED,			//已连接状态
};

//用户与房间之间的状态
enum MB_CHAT_CONN_STATUS
{
	CHAT_OUTOF_ROOM,		//未进入房间状态
	CHAT_ENTERING_ROOM,		//正在登录,等待服务器的回应
	CHAT_IN_ROOM,			//已进入房间		
};

#define T_PACKET_SENT_TIMEOUT				(60)			//报文超时时间，指存放在发送对列未收到ack包到下次得发之间间隔
#define T_SEND_QUEUE_CHECK_INTERVAL			(1)				//发送对列检查时间间隔
#define T_KEEPALIVE_INTERVAL				(5)				//保持连接报文发送时间间隔


#define T_KEEPALIVE_TIMEOUT_TRY_TIMES		15			//keepalive重发次数
#define PACKET_SEND_KEY_TIMEOUT				800

#define INVALID_USER_ID						0
#define TIMER_INTERVAL						180


#ifndef MAX_MIC_USER_NUM
#	define MAX_MIC_USER_NUM					4						//最大麦数
#endif


typedef list<uint32>	UinList;

//限制拆包不能超过16个包.16太小，换成160
#define MAX_PACKET_NUM	160
#define WINDOW_SIZE		(MAX_PACKET_NUM / 8)	
#define MAXPACKETUIN	200		//一个数据包最大发送的uin个数

//////////////////////////////////////////////////////////////////////////
//jsonkey define
#define JSKEY_CMD					"cmd"				//命令号
#define JSKEY_SEQ					"seq"				//seq
#define JSKEY_SUBCMD				"subcmd"			//子命令号
#define JSKEY_RESULT				"result"			//返回值
#define JSKEY_PRORATE				"prorate"			//兑换比例
#define JSKEY_PACKETID				"packetid"			//应用层发包时间戳
#define JSKEY_DEVTYPE				"deviceType"		//设备类型
#define JSKEY_PID					"pid"
#define JSKEY_UIN					"uin"
#define JSKEY_NICK					"nick"
#define JSKEY_PASS					"password"			//用户密码
#define JSKEY_ROOM_PASS				"roomPassword"		//room密码
#define JSKEY_NET_TYPE				"nettype"			//网络类型
#define JSKEY_DEV_TYPE				"devType"			//设备类型
#define JSKEY_MACADDR				"macaddr"			//设备id
#define JSKEY_DEVNUM				"devNum"			//移动设备唯一识别码
#define JSKEY_COCVER				"cocver"			//游戏版本号
#define JSKEY_BINDLOGIN				"bindLogin"			//是否乐淘绑定登录
#define JSKEY_PASSTYPE				"passType"			//密码类型
#define JSKEY_SRCUIN				"srcUin"			//源uin
#define JSKEY_SRCPID				"srcPid"			//源PID
#define JSKEY_SRCNICK				"srcNick"
#define JSKEY_DSTUIN				"dstUin"			//目标uin
#define JSKEY_DSTPID				"dstPid"			//目标pid
#define JSKEY_DSTNICK				"dstNick"		
#define JSKEY_MICUIN				"micUin"			//在麦uin
#define JSKEY_MICTIME				"micTime"			//在麦剩余时间
#define JSKEY_MICQUEUEINDEX			"micQueueIndex"		//麦序列表中的第几位 从零开始
#define JSKEY_ROOMID				"roomid"			//房间id
#define JSKEY_USERNICK				"userNick"			//用户昵称
#define JSKEY_MONEY					"money"				//用户虚拟币
#define JSKEY_PRIZEMONEY			"prizeCount"		//奖励总金额
#define JSKEY_PRIZELIST				"prizeList"			//奖励列表
#define JSKEY_LIST					"list"			//奖励列表
#define JSKEY_MSG_ID				"msgId"				//消息ID
#define JSKEY_KEY					"Key"				//KEY 
#define JSKEY_VAL					"Val"				//VAL 
#define JSKEY_MSG_DATE				"msgDate"			//消息日期
#define JSKEY_MSG_FROM				"msgFrom"			//消息来源
#define JSKEY_MSG_URL				"msgUrl"			//消息URL
#define JSKEY_MSG					"msgText"			//文本信息
#define JSKEY_MSG_TYPE				"msgType"			//文本类型
#define JSKEY_MAIL_LIST				"mailList"			//邮件列表
#define JSKEY_STAMPLIST				"stampList"
#define JSKEY_IP					"ip"			
#define JSKEY_PORT					"port"		
#define JSKEY_FLAG					"flag"				//通用标识符

/////////////////////////////////////////////////////////////
//coc游戏json  key 定义
#define JSKEY_MODEL							"modelIndex"				//场景编号
#define JSKEY_MAP_INDEX						"mapIndex"					//地图编号
#define JSKEY_SRC_MODEL						"modelSrcIndex"				//场景编号
#define JSKEY_SRC_MAP_INDEX					"mapDstIndex"				//地图编号
#define JSKEY_DST_MODEL						"modelDstIndex"				//场景编号
#define JSKEY_DST_MAP_INDEX					"mapSrcIndex"				//地图编号
#define JSKEY_BUILD_TYPE					"buildType"					//建筑类型
#define JSKEY_BUILD_NUM						"buildNum"					//建筑编号
#define JSKEY_BUILD_STATE					"buildState"				//建筑编号
#define JSKEY_X_POS							"xPos"						//x坐标
#define JSKEY_Y_POS							"yPos"						//y坐标
#define JSKEY_LEVEL							"level"						//等级
#define	JSKEY_STATE							"state"						//状态
#define	JSKEY_MAP_ID						"mapId"						//挑战赛mapId
#define JSKEY_START_TIME					"startTime"					//建造开始时间
#define JSKEY_SPAN_TIME						"spanTime"					//已经花费的时间
#define JSKEY_BUILDING_LIST					"buildingList"				//建筑物列表
#define JSKEY_CHECK_SUCC					"checkSucc"					//校验是否完成
#define JSKEY_NEED_TIME						"needTime"					//需要多少时间
#define JSKEY_NEED_NUM						"needNum"					//需要多少数量
#define JSKEY_USE_RES_TYPE					"restype"					//使用资源类型 0：游戏币 1.站点币
#define JSKEY_SOLDIER_GROUP					"soldier_group"				//士兵分组
#define JSKEY_SOLDIER_TYPE					"soldier_type"				//士兵类型
#define JSKEY_SOLDIER_LEVEL					"soldier_level"				//士兵等级
#define JSKEY_SOLDIER_NUM					"soldier_num"				//士兵数量
#define JSKEY_SOLDIER_ID					"soldier_id"				//士兵id
#define JSKEY_MAGIC_ID						"magicId"					//法术id
#define JSKEY_SOLDIER_LIST					"soldier_list"				//士兵列表
#define JSKEY_TRAINING_CAMP_INDEX			"training_camp_index"		//训练营编号
#define JSKEY_LAB_INDEX						"labindex"					//训练营编号
#define JSKEY_MAIL_ID						"mailId"					//成就Id
#define JSKEY_ACHIEVEMENT_ID				"achvId"					//成就Id
#define JSKEY_ACHIEVEMENT_LEVEL				"achvLevel"					//成就Level
#define JSKEY_ACHIEVEMENT_VALUE				"achvValue"					//当前成就
#define JSKEY_ACHIEVEMENT_COMPLETE			"achvcompleteLevel"			//已经领取的成就
#define JSKEY_ACHIEVEMENT_LIST				"achvcompleteList"			//已经领取的成就
#define JSKEY_RES							"resourse"					//资源
#define JSKEY_RES_NUM						"resoursenum"				//资源数量
#define JSKEY_RES_ID						"resourceId"				//资源的种类
#define JSKEY_RES_CURR						"resourceCurr"				//资源的当前数量
#define JSKEY_RES_MAX						"resourceMax"				//资源的存储限制
#define JSKEY_RES_PLUNDER_MAX				"resourcePlunderMax"		//资源掠夺总量上线
#define JSKEY_RES_PLUNDER_PRODUCE			"resourcePlunderProduce"	//资源掠夺生产上限
#define JSKEY_RES_PLUNDER_COLLECT			"resourcePlunderCollect"	//资源掠夺收集上限
#define JSKEY_NUM							"num"						//用于表示数量
#define JSKEY_SPEED_UP_KEY					"speedup"					//加速生产key
#define JSKEY_COMPLETE_TYPE					"complete_type"				//立即完成类型
#define JSKEY_CUP							"cup"						//奖杯数量
#define JSKEY_WAR_CUP						"warCup"					//奖杯数量（战场）
#define JSKEY_PERCENT						"percent"					//百分比
#define JSKEY_LEAGUELEVEL					"leagueLevel"				//联赛级别
#define JSKEY_USER_EXP						"userExp"					//用户经验值
#define JSKEY_SHIELD_LEFT					"shiledLeft"				//护盾剩余时间
#define JSKEY_SHIELD_COOL_LEFT				"shieldCoolLeft"			//护盾冷却时间
#define JSKEY_SEEKHELP_LEFT					"seekhelpLeft"				//求援剩余时间
#define JSKEY_SEEKHELPCOOL_LEFT				"seekhelpcollLeft"			//求援冷却剩余时间
#define JSKEY_WORKER_TIME_LEFT				"workerTimeLeft"			//剩余要工作时间
#define JSKEY_GAME_NOTIFY_TYPE				"gameNotifyType"			//游戏通知类型
#define JSKEY_GAME_NOTIFY_MSG				"gameNotifyMsg"				//游戏通知消息
#define JSKEY_BUILD_ARRAY					"buildArray"				//城墙数组
#define JSKEY_SHIELD_ID						"shieldId"					//护盾
#define JSKEY_USE_RES_TYPEE					"useGemstone"				//使用宝石
#define JSKEY_TIME_OFFSET					"timeOffset"				//时间偏移量
#define JSKEY_TIME_ID						"timeId"					//时间ID
#define JSKEY_TIMES							"times"						//次数
#define JSKEY_TIME_TYPE						"timeType"					//时间类型
#define JSKEY_TIME_LIST						"timeList"					//时间列表
#define JSKEY_TIME_REMAIN					"timeRemain"				//时间剩余
#define JSKEY_TIME_LAST						"timeLast"					//时间剩余
#define JSKEY_SHOW_SPAN						"showSpan"					//展示时间间隔
#define JSKEY_WAR_STAR_NUM					"warstarNum"				//战星
#define JSKEY_END_WAR						"timeEndWar"				//时间偏移量
#define JSKEY_PACKET_TOTAL_NUM				"packetTotalNum"			//总包的数量
#define JSKEY_PACKET_TOTAL_INDEX			"packetIndex"				//包的id
#define JSKEY_START_TIME					"startTime"					//开始时间
#define JSKEY_END_TIME						"endTime"					//结束时间
#define JSKEY_WORKING_LIST					"workingList"				//建筑队列
#define JSKEY_PRODUCE_LIST					"produceList"				//生产队列
#define JSKEY_PRODUCE_TYPE					"produceType"				//生产类型
#define JSKEY_ON_PRODUCE					"onProduce"					//正在生产
#define JSKEY_END_PRODUCE					"endProduce"				//完成生产
#define JSKEY_START_TIME_LIST				"startTimeList"				//开始生产时间列表
#define JSKEY_REFRESH_INDEX					"refreshIndex"				//宝石刷新index
#define JSKEY_CLAN_ID						"clanId"					//所属部落
#define JSKEY_CLAN_JOB						"clanJob"					//部落职位
#define JSKEY_CLAN_NAME						"clanName"					//部落名称
#define JSKEY_ATTACK_LIST					"attackList"				//战斗历史
#define JSKEY_OFFENSE_USER					"offenseUser"				//进攻方信息
#define JSKEY_USER_INFO						"userInfo"					//用户信息
#define JSKEY_OFFENSE_PID					"offensePid"				//进攻方Pid
#define JSKEY_OFFENSE_UIN					"offenseUin"				//进攻方Uin
#define JSKEY_DEFEND_USER					"defendUser"				//防守方信息
#define JSKEY_DEFEND_PID					"defendPid"					//防守方Pid
#define JSKEY_DEFEND_UIN					"defendUin"					//防守方Uin
#define JSKEY_SEND_SOLDIER					"sendSoldier"				//派兵信息
#define JSKEY_ATTACK_TIME					"attackTime"				//进攻时间
#define JSKEY_DB_KEYID						"DBkeyId"					//db keyId
#define JSKEY_RES_GOLD						"resGold"					//金币
#define JSKEY_RES_HOLYWARTER				"resHolywarter"				//圣水
#define JSKEY_RES_BLACKWATER				"resBlackwater"				//黑水
#define JSKEY_RES_GEMSTONE					"resGemstone"				//宝石
#define JSKEY_RES_GOLD_STORE				"resGoldStore"				//金币(存储)
#define JSKEY_RES_HOLYWARTER_STORE			"resHolywarterStore"		//圣水(存储)
#define JSKEY_RES_BLACKWATER_STORE			"resBlackwaterStore"		//黑水(存储)
#define STORE_CAN_PLUNDER_NUM				"canPlunderNum"				//可掠夺数量
#define JSKEY_GATE_INDEX					"tollGateIndex"				//关卡编号
#define JSKEY_GATE_NAEM						"tollGateName"				//关卡名字
#define JSKEY_GATE_LIST						"tollGateList"				//关卡列表
#define JSKEY_CUP_STATE						"cupState"					//防守方奖杯状态 （0 失去， 1 获得）
#define JSKEY_NEW_USER_STEP					"newUserStep"				//新手教程进行步骤
#define JSKEY_CANREVENGE					"canRevenge"				//是否可以复仇
#define JSKEY_DEFEND_SUCESS					"defendSucess"				//成功防守次数
#define JSKEY_OFFENCE_SUCESS				"offenceSucess"				//成功次数
#define JSKEY_OFFLINE_TIME					"offlineTime"				//上一次离线时间
#define JSKEY_RANK_LIST						"rankList"					//排名列表
#define JSKEY_CLAN_ICON_NUM					"clanIconNum"				//部落icon编号
#define JSKEY_RANK_NUM						"rankNum"					//名次
#define JSKEY_EXCHANGE_TMES					"exchangeTimes"				//兑换次数
#define JSKEY_ZERO_SPAN						"zeroSpan"					//相对当日零点偏移
#define JSKEY_TIME_MAX						"timeMax"					//时间最大偏移
#define JSKEY_PRIZE_ID						"prizeId"					//奖励id
#define JSKEY_RESOURCE						"resource"					//资源
#define JSKEY_WEEK_ID						"weekId"				    //周id（当年的第n周）
#define JSKEY_MAP_ID						"mapId"						//地图编号
#define JSKEY_DESCRIBE						"describe"				    //描述信息
#define JSKEY_INFO							"info"						//信息
#define JSKEY_CHALLENGE_TIME				"challengeTime"				//挑战时间
#define JSKEY_GAME_ID						"gameid"					//游戏id
#define JSKEY_OFFENSE_GAMEID				"offenseGameid"				//攻击方游戏id
#define JSKEY_DEFEND_GAMEID					"defendGameid"				//防守方游戏id
#define JSKEY_CASH_RMB						"cashRMB"					//现金RMB
#define JSKEY_GEMSTONE_DISCOUNT				"gemstoneDiscount"			//折后宝石数量
#define JSKEY_GEMSTONE_ALL					"gemstoneAll"				//服务当前剩余宝石总数
#define JSKEY_DISCOUNT						"discount"					//折扣
#define JSKEY_BUY_GEMSTONE_INFO				"gemstoneInfoList"			//购买宝石折扣列表
#define JSKEY_BROTHER_TASKLIST				"brotherhoodList"			//兄弟关系当前进度列表
#define JEKEY_BROTHER_TYPE					"brotherhoodType"			//兄弟关系类型， 兄弟个数，兄弟成就星级个数
#define JSKEY_BROTHER_ID					"brotherCurrKey"			//当前等级（id）
#define JSKEY_BROTHER_VALUE					"brotherCurrVal"			//当前值（兄弟个数，成就星级个数）

#define JSKEY_BROTHERINFO_LIST				"brotherInfoList"			//兄弟信息列表
#define JSKEY_TOTAL_STARS					"totalStars"				//成就总星级个数
#define JSKEY_TIME							"time"						//时间


#define JSKEY_ACTION						"action"					//动作
//部落相关

//////////////////////////////////////////////////////////////////////////
#define JSKEY_CLAN_DESC						"clanDesc"					//部落名称
#define JSKEY_CLAN_LEADER_NAME				"leaderNick"				//首领昵称
#define JSKEY_CLAN_CURR_MEMBER				"currMember"				//当前人数
#define JSKEY_CLAN_MAX_MEMBER				"maxMember"					//最大人数
#define JSKEY_CLAN_EXPERIENCE				"clanExperience"			//经验
#define JSKEY_CLAN_LIST						"clanList"					//部落列表
#define JSKEY_CLAN_REQ_LIST					"clanReqList"				//申请列表
#define JSKEY_ORDER_ID						"orderid"					//序号
#define JSKEY_CLAN_MEMLIST					"clanMemlist"				//部落成员列表
#define JSKEY_CLAN_CONSTRIBUION				"totalContribution"			//累计贡献值
#define JSKEY_CLAN_YESTERDAY				"yesterdayContribution"		//昨日贡献值		
#define JSKEY_OLD_RANK						"oldRank"					//老的身份
#define JSKEY_NEW_RANK						"newRank"					//新身份
#define JSKEY_CLAN_MIN_CUPNUM				"cupNumLimit"				//最小奖杯限制
#define JSKEY_CLAN_STATECACHE				"clanStateCache"			//缓存
#define JSKEY_REQ_STATE						"reqState"					//申请状态
#define JSKEY_KICK_TIMES					"kickTimes"					//踢出部落剩余次数
#define JSKEY_CLAN_DONATE_TYPE				"clandonateType"			//部落捐献类型
#define JSKEY_CLAN_DONATE_NEXTTIME			"clandonateNextTime"		//部落捐献类型
#define JSKEY_CLAN_AVAILABLE_CONTRIBUTE		"clanAvailableContribute"	//部落可用贡献点
#define JSKEY_CLAN_BUILD_NUM				"buildDonateNum"			//今日可用免费建筑部落次数
#define JSKEY_CLAN_BUILD_TIME				"buildDonatTime"			//建筑部落
#define JSKEY_CLAN_DONATE_WATER_TIME		"donateWaterTime"			//部落捐献圣水
#define JSKEY_CLAN_DONATE_DIAMOND_TIME		"donateDiamondTime"			//部落捐献宝石
#define JSKEY_CLAN_WINPOINT					"winPoint"					//胜点
#define JSKEY_CLAN_LAST_WINPOINT			"lastWinPoint"				//上赛季胜点
#define JSKEY_CLAN_WINPOINT_RANKLIST		"winPointRankList"			//胜点排行列表
#define JSKEY_CLAN_SEASON_NUM				"clanSeasonNum"				//战争堡垒当前赛季数
#define JSKEY_CLAN_RESOURCE_LIST			"clanResourceList"			//部落仓库资源列表
#define JSKEY_CLAN_WINPOINT_RANK_LIST		"WinPointRankList"			//进攻方信息
#define JSKEY_CLAN_DEFEND_USER_INFO			"defendUserInfo"			//部落战斗日志防守方信息
#define JSKEY_CLAN_TIME						"clanTime"					//战争堡垒赛季结束时间


class Music 
{
public:
	string name;
	string url;
};
class MicQueueCliItem
{
public:
	MicQueueCliItem()
	{
		uin = -1;
		giftmoney =0;
		//memset(giftid,0,sizeof(giftid));
		//memset(giftnum,0,sizeof(giftnum));
	}

	MicQueueCliItem(const MicQueueCliItem& item)
	{
		*this = item;
	}
	MicQueueCliItem& operator = (const MicQueueCliItem& item)
	{
		this->uin = item.uin;
		this->nick = item.nick;
		this->giftmoney = item.giftmoney;
		//memcpy(this->giftid,item.giftid,sizeof(this->giftid));
		//memcpy(this->giftnum,item.giftnum,sizeof(this->giftnum));
		return *this;
	}
	uint32 uin;
	NickString nick;
	uint64 giftmoney;
	//uint32 giftid[2];
	//uint16 giftnum[2];
};


typedef struct OnMicUerList
{
	uint32 onMicUser[MAX_MIC_USER_NUM];
}OnMicUerList;

// typedef std::vector<RoomUnit> ROOMUNIT_VECTOR;
// 
// typedef std::vector<USER_INFO> USER_VECTOR;
typedef std::vector<uint32> UINT_VECTOR;
typedef std::vector<MicQueueCliItem> MicQueueVector;
typedef std::vector<uint16> USHORT_VECTOR;
typedef std::map<uint32,uint32> UINT_MAP;
typedef UINT_VECTOR MIKE_VECTOR; 
typedef UINT_VECTOR MEMBERORDENY_VECTOR;
typedef UINT_VECTOR MANAGER_VECTOR; 
typedef UINT_VECTOR ROOMMANAGER_VECTOR; 
typedef UINT_MAP MANAGER_MAP; 
typedef UINT_MAP MIKE_MAP;
typedef std::vector<Music> MUSICVEC;



class RMManager {
public:
	uint32 uin;
	uint16 rank;
};
typedef std::vector<RMManager> RMMANAGERVEC;






#define NICK_LENGTH 32

class TLMemberUnit
{
public:
    uint32 uin;
    uint32 status;
    NickString nick;
    uint16 face;
    uint8 rank;
    uint8 g_userType;		//全部用户类型（代理、销售、客服等）
    uint8 flag;		//flag指示该用户是有麦克,是否有摄像头,是否在会议中
    uint8 devType;
    uint16 forBidTime;			//禁言剩余时间
    uint64 money;		//用户资金
   // UserLevel level;		//是否会员
    uint64 received;
    //MicInfo micInfo;
    
    //Customface customface;//自定义头像版本
    uint8 richerOrder;  //富翁排行, 未进入排行则为0, 否则为相应排行值
    TLMemberUnit()
    {
        uin = 0;
        status = 0;
        face = 0;
        rank = 0;
        g_userType = 0;
        forBidTime = 0;
        flag = 0;
        money = 0;
        devType = 0;
        //level.value = 0;
        received = 0;
        //micInfo.micInfo = 0;
        //customface.customFace = 0;
        richerOrder = 0;
        //memset(nick, 0, NICK_LENGTH);
    }
    TLMemberUnit(const TLMemberUnit &m)
    {
        *this = m;
    }
    TLMemberUnit& operator = (const TLMemberUnit &m)
    {
        this->uin = m.uin;
		this->nick = m.nick;
        //memcpy(this->nick, m.nick, NICK_LENGTH);
        this->status = m.status;
        this->face = m.face;
        this->rank = m.rank;
        this->g_userType = m.g_userType;
        this->flag = m.flag;
        this->money = m.money;
        //this->level.value = m.level.value;
        this->received = m.received;
        //this->micInfo.micInfo = m.micInfo.micInfo;
        //this->customface.customFace = m.customface.customFace;
        this->richerOrder = m.richerOrder;
        this->devType = m.devType;
        this->forBidTime = m.forBidTime;
        return *this;
    }
};


typedef std::vector<TLMemberUnit> TLMEMBERUNIT_VECTOR;


class RoomMember 
{
public:
	uint32			packetmark;
	uint16			packetnum;
	uint16			recved;
	//	uint8			  window[WINDOW_SIZE];
	TLMEMBERUNIT_VECTOR vecMember;

	RoomMember()
	{
		Clear();
		//		memset(window, 0,  WINDOW_SIZE * sizeof(uint8));
	}

	void Clear()
	{
		packetmark = 0;
		packetnum = 0;
		recved = 0;
		//	memset(window, 0, WINDOW_SIZE * sizeof(uint8));
		vecMember.clear();
	}

	~RoomMember()
	{
		Clear();
	}	

	bool IsIntegrate()
	{
		return  (recved >= packetnum);

	}

	//返回该包是否重复,如果重复,返回false;如果不重复,返回true
	bool SetWindow(uint32 mark, uint16 num, uint16 index)
	{
		if (packetnum == 0)
			packetnum = num;

		recved++;

		return true;
	}
};


class LOGONINFO {
public:
	NickString	nick;
	uint16	face;
	//Customface customFace;
	uint8	rank;
	uint8   userType;				//全局性用户属性（代理、销售、客服等）
	uint32	flag;
	uint64  money;
	uint64 received;
	uint8	richOrder;
	uint8   accountState;
	uint8	msgsetup;
	uint16  textPort;
	uint16  audioPort;
	uint16	boxfreetime; //宝箱免费开箱时间
	uint16	videoPort;
	uint32  textIp;
	uint32  audioIp;
	uint32  videoIp;

	string enter_title;
	string enter_pic;
	string aclctrlstr; //权限控制
	void Init() {
		textPort = 0;
		audioPort = 0;
		videoPort = 0;
		nick = "";
		face = rank = 0;
		flag = 0;
		msgsetup = 0;
		textIp = 0;
		audioIp = 0;
		videoIp = 0;
		accountState = 0;
		boxfreetime = 0;
	}
};
class ROOMINFO {
public:
	uint32			roomid;
	uint32			ownuin;
	string			name;
	string			descript;
	string			broadcast;
	uint16			maxmember;
	uint16			maxcfuser;									//最大麦数
	uint16			maxMicQueue;
	uint16			maxmanager;
	uint16			roomSize;
	uint8			ispublic;
	uint8			auth;
	string			singnature;									//媒体数字签名
	uint8			openstatus;
	bool			autoMic;
	uint8			m_audiosampleindex;		
	uint8			m_audiobitrateindex;
	//MediaSvrList	avSrvList;									//此房间音视频服务器ＩＰ地址
	uint16			avPort;										//房间的音视频频服务器音频端口
	bool			bEnableColorBar;//是否发送彩条 true允许 
	uint32			micArray[MAX_MIC_USER_NUM];					//当前在麦用户
	uint16          micmaxtime[MAX_MIC_USER_NUM];				//当用在麦用户的麦时
	uint8			micDevType[MAX_MIC_USER_NUM];				//当前麦用户设备类型
	ROOMINFO()
	{
		Init();
	}
	void Init()
	{
		memset(micArray, 0, sizeof(micArray));
		memset(micmaxtime,0,sizeof(micmaxtime));
		memset(micDevType,0,sizeof(micDevType));
		roomid = 0;
		name = "";
		descript = "";
		broadcast = "";
		maxmember = maxcfuser = maxMicQueue = maxmanager = roomSize = 0;
		m_audiosampleindex = m_audiosampleindex=ispublic = auth = openstatus = 0;

		avPort =  0; 
		//avSrvList.clear();
		bEnableColorBar = true;
		// audioQuality = 0;
	}
};


//等待包结构,只在等待的时候有效，在ChatConnection的Init的时候必须清理
class WATI_STRUCT {
public:
	LOGONINFO		m_logoninfo;
	ROOMINFO		m_rminfo;
	//TENROOMINFO		m_tenrminfo;//
	//	ROOMADV			m_rmadv;
	RoomMember		m_roomMember;
	RoomMember		m_roomVisitor;
	//	WebInfo			m_webInfo;	
	//USER_VECTOR		m_userVector;		  //用户列表
	UINT_VECTOR		m_micVec;			    //麦克列表
	UINT_VECTOR		m_blackUinVec;		//黑名单用户列表
	MicQueueVector		m_cfWaitVec;		  //会议等待用户列表

	RMMANAGERVEC	m_vecManagerList;

	void Init() {
		m_logoninfo.Init();
		m_rminfo.Init();
		//	m_tenrminfo.Init();//
		//		m_rmadv.Init();
		m_roomMember.Clear();
		m_micVec.clear();
	
	}
public:
	~WATI_STRUCT()
	{
		Init();
	}
};
#endif