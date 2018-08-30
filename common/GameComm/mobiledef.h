#ifndef INC_MOBILEDEF_H
#define INC_MOBILEDEF_H


#include <list>
#include <vector>

#ifdef WIN32
#include <Windows.h>
#endif

#include "include/icqtypes.h"
#include "TcpPacket.h"


//�������
enum MB_CHAT_ERROR_CODE
{
	E_SUCCESS = 0,				//�ɹ�
	E_CANNOT_LINK_SERVER,		//�������ӷ���������¼ʱ��
	E_OUT_OF_CONNECTION,		//ʧȥ�����������
	E_NOT_IN_ROOM,				//��δ���뷿��
	E_TIMEOUT,					//���ͳ�ʱ
};

enum MB_CHANNEL_SVC_STATUS
{
	CHANNEL_DISCONNECTED,		//�ѶϿ�״̬
	CHANNEL_CONNECTED,			//������״̬
};

//�û��뷿��֮���״̬
enum MB_CHAT_CONN_STATUS
{
	CHAT_OUTOF_ROOM,		//δ���뷿��״̬
	CHAT_ENTERING_ROOM,		//���ڵ�¼,�ȴ��������Ļ�Ӧ
	CHAT_IN_ROOM,			//�ѽ��뷿��		
};

#define T_PACKET_SENT_TIMEOUT				(60)			//���ĳ�ʱʱ�䣬ָ����ڷ��Ͷ���δ�յ�ack�����´ε÷�֮����
#define T_SEND_QUEUE_CHECK_INTERVAL			(1)				//���Ͷ��м��ʱ����
#define T_KEEPALIVE_INTERVAL				(5)				//�������ӱ��ķ���ʱ����


#define T_KEEPALIVE_TIMEOUT_TRY_TIMES		15			//keepalive�ط�����
#define PACKET_SEND_KEY_TIMEOUT				800

#define INVALID_USER_ID						0
#define TIMER_INTERVAL						180


#ifndef MAX_MIC_USER_NUM
#	define MAX_MIC_USER_NUM					4						//�������
#endif


typedef list<uint32>	UinList;

//���Ʋ�����ܳ���16����.16̫С������160
#define MAX_PACKET_NUM	160
#define WINDOW_SIZE		(MAX_PACKET_NUM / 8)	
#define MAXPACKETUIN	200		//һ�����ݰ�����͵�uin����

//////////////////////////////////////////////////////////////////////////
//jsonkey define
#define JSKEY_CMD					"cmd"				//�����
#define JSKEY_SEQ					"seq"				//seq
#define JSKEY_SUBCMD				"subcmd"			//�������
#define JSKEY_RESULT				"result"			//����ֵ
#define JSKEY_PRORATE				"prorate"			//�һ�����
#define JSKEY_PACKETID				"packetid"			//Ӧ�ò㷢��ʱ���
#define JSKEY_DEVTYPE				"deviceType"		//�豸����
#define JSKEY_PID					"pid"
#define JSKEY_UIN					"uin"
#define JSKEY_NICK					"nick"
#define JSKEY_PASS					"password"			//�û�����
#define JSKEY_ROOM_PASS				"roomPassword"		//room����
#define JSKEY_NET_TYPE				"nettype"			//��������
#define JSKEY_DEV_TYPE				"devType"			//�豸����
#define JSKEY_MACADDR				"macaddr"			//�豸id
#define JSKEY_DEVNUM				"devNum"			//�ƶ��豸Ψһʶ����
#define JSKEY_COCVER				"cocver"			//��Ϸ�汾��
#define JSKEY_BINDLOGIN				"bindLogin"			//�Ƿ����԰󶨵�¼
#define JSKEY_PASSTYPE				"passType"			//��������
#define JSKEY_SRCUIN				"srcUin"			//Դuin
#define JSKEY_SRCPID				"srcPid"			//ԴPID
#define JSKEY_SRCNICK				"srcNick"
#define JSKEY_DSTUIN				"dstUin"			//Ŀ��uin
#define JSKEY_DSTPID				"dstPid"			//Ŀ��pid
#define JSKEY_DSTNICK				"dstNick"		
#define JSKEY_MICUIN				"micUin"			//����uin
#define JSKEY_MICTIME				"micTime"			//����ʣ��ʱ��
#define JSKEY_MICQUEUEINDEX			"micQueueIndex"		//�����б��еĵڼ�λ ���㿪ʼ
#define JSKEY_ROOMID				"roomid"			//����id
#define JSKEY_USERNICK				"userNick"			//�û��ǳ�
#define JSKEY_MONEY					"money"				//�û������
#define JSKEY_PRIZEMONEY			"prizeCount"		//�����ܽ��
#define JSKEY_PRIZELIST				"prizeList"			//�����б�
#define JSKEY_LIST					"list"			//�����б�
#define JSKEY_MSG_ID				"msgId"				//��ϢID
#define JSKEY_KEY					"Key"				//KEY 
#define JSKEY_VAL					"Val"				//VAL 
#define JSKEY_MSG_DATE				"msgDate"			//��Ϣ����
#define JSKEY_MSG_FROM				"msgFrom"			//��Ϣ��Դ
#define JSKEY_MSG_URL				"msgUrl"			//��ϢURL
#define JSKEY_MSG					"msgText"			//�ı���Ϣ
#define JSKEY_MSG_TYPE				"msgType"			//�ı�����
#define JSKEY_MAIL_LIST				"mailList"			//�ʼ��б�
#define JSKEY_STAMPLIST				"stampList"
#define JSKEY_IP					"ip"			
#define JSKEY_PORT					"port"		
#define JSKEY_FLAG					"flag"				//ͨ�ñ�ʶ��

/////////////////////////////////////////////////////////////
//coc��Ϸjson  key ����
#define JSKEY_MODEL							"modelIndex"				//�������
#define JSKEY_MAP_INDEX						"mapIndex"					//��ͼ���
#define JSKEY_SRC_MODEL						"modelSrcIndex"				//�������
#define JSKEY_SRC_MAP_INDEX					"mapDstIndex"				//��ͼ���
#define JSKEY_DST_MODEL						"modelDstIndex"				//�������
#define JSKEY_DST_MAP_INDEX					"mapSrcIndex"				//��ͼ���
#define JSKEY_BUILD_TYPE					"buildType"					//��������
#define JSKEY_BUILD_NUM						"buildNum"					//�������
#define JSKEY_BUILD_STATE					"buildState"				//�������
#define JSKEY_X_POS							"xPos"						//x����
#define JSKEY_Y_POS							"yPos"						//y����
#define JSKEY_LEVEL							"level"						//�ȼ�
#define	JSKEY_STATE							"state"						//״̬
#define	JSKEY_MAP_ID						"mapId"						//��ս��mapId
#define JSKEY_START_TIME					"startTime"					//���쿪ʼʱ��
#define JSKEY_SPAN_TIME						"spanTime"					//�Ѿ����ѵ�ʱ��
#define JSKEY_BUILDING_LIST					"buildingList"				//�������б�
#define JSKEY_CHECK_SUCC					"checkSucc"					//У���Ƿ����
#define JSKEY_NEED_TIME						"needTime"					//��Ҫ����ʱ��
#define JSKEY_NEED_NUM						"needNum"					//��Ҫ��������
#define JSKEY_USE_RES_TYPE					"restype"					//ʹ����Դ���� 0����Ϸ�� 1.վ���
#define JSKEY_SOLDIER_GROUP					"soldier_group"				//ʿ������
#define JSKEY_SOLDIER_TYPE					"soldier_type"				//ʿ������
#define JSKEY_SOLDIER_LEVEL					"soldier_level"				//ʿ���ȼ�
#define JSKEY_SOLDIER_NUM					"soldier_num"				//ʿ������
#define JSKEY_SOLDIER_ID					"soldier_id"				//ʿ��id
#define JSKEY_MAGIC_ID						"magicId"					//����id
#define JSKEY_SOLDIER_LIST					"soldier_list"				//ʿ���б�
#define JSKEY_TRAINING_CAMP_INDEX			"training_camp_index"		//ѵ��Ӫ���
#define JSKEY_LAB_INDEX						"labindex"					//ѵ��Ӫ���
#define JSKEY_MAIL_ID						"mailId"					//�ɾ�Id
#define JSKEY_ACHIEVEMENT_ID				"achvId"					//�ɾ�Id
#define JSKEY_ACHIEVEMENT_LEVEL				"achvLevel"					//�ɾ�Level
#define JSKEY_ACHIEVEMENT_VALUE				"achvValue"					//��ǰ�ɾ�
#define JSKEY_ACHIEVEMENT_COMPLETE			"achvcompleteLevel"			//�Ѿ���ȡ�ĳɾ�
#define JSKEY_ACHIEVEMENT_LIST				"achvcompleteList"			//�Ѿ���ȡ�ĳɾ�
#define JSKEY_RES							"resourse"					//��Դ
#define JSKEY_RES_NUM						"resoursenum"				//��Դ����
#define JSKEY_RES_ID						"resourceId"				//��Դ������
#define JSKEY_RES_CURR						"resourceCurr"				//��Դ�ĵ�ǰ����
#define JSKEY_RES_MAX						"resourceMax"				//��Դ�Ĵ洢����
#define JSKEY_RES_PLUNDER_MAX				"resourcePlunderMax"		//��Դ�Ӷ���������
#define JSKEY_RES_PLUNDER_PRODUCE			"resourcePlunderProduce"	//��Դ�Ӷ���������
#define JSKEY_RES_PLUNDER_COLLECT			"resourcePlunderCollect"	//��Դ�Ӷ��ռ�����
#define JSKEY_NUM							"num"						//���ڱ�ʾ����
#define JSKEY_SPEED_UP_KEY					"speedup"					//��������key
#define JSKEY_COMPLETE_TYPE					"complete_type"				//�����������
#define JSKEY_CUP							"cup"						//��������
#define JSKEY_WAR_CUP						"warCup"					//����������ս����
#define JSKEY_PERCENT						"percent"					//�ٷֱ�
#define JSKEY_LEAGUELEVEL					"leagueLevel"				//��������
#define JSKEY_USER_EXP						"userExp"					//�û�����ֵ
#define JSKEY_SHIELD_LEFT					"shiledLeft"				//����ʣ��ʱ��
#define JSKEY_SHIELD_COOL_LEFT				"shieldCoolLeft"			//������ȴʱ��
#define JSKEY_SEEKHELP_LEFT					"seekhelpLeft"				//��Ԯʣ��ʱ��
#define JSKEY_SEEKHELPCOOL_LEFT				"seekhelpcollLeft"			//��Ԯ��ȴʣ��ʱ��
#define JSKEY_WORKER_TIME_LEFT				"workerTimeLeft"			//ʣ��Ҫ����ʱ��
#define JSKEY_GAME_NOTIFY_TYPE				"gameNotifyType"			//��Ϸ֪ͨ����
#define JSKEY_GAME_NOTIFY_MSG				"gameNotifyMsg"				//��Ϸ֪ͨ��Ϣ
#define JSKEY_BUILD_ARRAY					"buildArray"				//��ǽ����
#define JSKEY_SHIELD_ID						"shieldId"					//����
#define JSKEY_USE_RES_TYPEE					"useGemstone"				//ʹ�ñ�ʯ
#define JSKEY_TIME_OFFSET					"timeOffset"				//ʱ��ƫ����
#define JSKEY_TIME_ID						"timeId"					//ʱ��ID
#define JSKEY_TIMES							"times"						//����
#define JSKEY_TIME_TYPE						"timeType"					//ʱ������
#define JSKEY_TIME_LIST						"timeList"					//ʱ���б�
#define JSKEY_TIME_REMAIN					"timeRemain"				//ʱ��ʣ��
#define JSKEY_TIME_LAST						"timeLast"					//ʱ��ʣ��
#define JSKEY_SHOW_SPAN						"showSpan"					//չʾʱ����
#define JSKEY_WAR_STAR_NUM					"warstarNum"				//ս��
#define JSKEY_END_WAR						"timeEndWar"				//ʱ��ƫ����
#define JSKEY_PACKET_TOTAL_NUM				"packetTotalNum"			//�ܰ�������
#define JSKEY_PACKET_TOTAL_INDEX			"packetIndex"				//����id
#define JSKEY_START_TIME					"startTime"					//��ʼʱ��
#define JSKEY_END_TIME						"endTime"					//����ʱ��
#define JSKEY_WORKING_LIST					"workingList"				//��������
#define JSKEY_PRODUCE_LIST					"produceList"				//��������
#define JSKEY_PRODUCE_TYPE					"produceType"				//��������
#define JSKEY_ON_PRODUCE					"onProduce"					//��������
#define JSKEY_END_PRODUCE					"endProduce"				//�������
#define JSKEY_START_TIME_LIST				"startTimeList"				//��ʼ����ʱ���б�
#define JSKEY_REFRESH_INDEX					"refreshIndex"				//��ʯˢ��index
#define JSKEY_CLAN_ID						"clanId"					//��������
#define JSKEY_CLAN_JOB						"clanJob"					//����ְλ
#define JSKEY_CLAN_NAME						"clanName"					//��������
#define JSKEY_ATTACK_LIST					"attackList"				//ս����ʷ
#define JSKEY_OFFENSE_USER					"offenseUser"				//��������Ϣ
#define JSKEY_USER_INFO						"userInfo"					//�û���Ϣ
#define JSKEY_OFFENSE_PID					"offensePid"				//������Pid
#define JSKEY_OFFENSE_UIN					"offenseUin"				//������Uin
#define JSKEY_DEFEND_USER					"defendUser"				//���ط���Ϣ
#define JSKEY_DEFEND_PID					"defendPid"					//���ط�Pid
#define JSKEY_DEFEND_UIN					"defendUin"					//���ط�Uin
#define JSKEY_SEND_SOLDIER					"sendSoldier"				//�ɱ���Ϣ
#define JSKEY_ATTACK_TIME					"attackTime"				//����ʱ��
#define JSKEY_DB_KEYID						"DBkeyId"					//db keyId
#define JSKEY_RES_GOLD						"resGold"					//���
#define JSKEY_RES_HOLYWARTER				"resHolywarter"				//ʥˮ
#define JSKEY_RES_BLACKWATER				"resBlackwater"				//��ˮ
#define JSKEY_RES_GEMSTONE					"resGemstone"				//��ʯ
#define JSKEY_RES_GOLD_STORE				"resGoldStore"				//���(�洢)
#define JSKEY_RES_HOLYWARTER_STORE			"resHolywarterStore"		//ʥˮ(�洢)
#define JSKEY_RES_BLACKWATER_STORE			"resBlackwaterStore"		//��ˮ(�洢)
#define STORE_CAN_PLUNDER_NUM				"canPlunderNum"				//���Ӷ�����
#define JSKEY_GATE_INDEX					"tollGateIndex"				//�ؿ����
#define JSKEY_GATE_NAEM						"tollGateName"				//�ؿ�����
#define JSKEY_GATE_LIST						"tollGateList"				//�ؿ��б�
#define JSKEY_CUP_STATE						"cupState"					//���ط�����״̬ ��0 ʧȥ�� 1 ��ã�
#define JSKEY_NEW_USER_STEP					"newUserStep"				//���ֽ̳̽��в���
#define JSKEY_CANREVENGE					"canRevenge"				//�Ƿ���Ը���
#define JSKEY_DEFEND_SUCESS					"defendSucess"				//�ɹ����ش���
#define JSKEY_OFFENCE_SUCESS				"offenceSucess"				//�ɹ�����
#define JSKEY_OFFLINE_TIME					"offlineTime"				//��һ������ʱ��
#define JSKEY_RANK_LIST						"rankList"					//�����б�
#define JSKEY_CLAN_ICON_NUM					"clanIconNum"				//����icon���
#define JSKEY_RANK_NUM						"rankNum"					//����
#define JSKEY_EXCHANGE_TMES					"exchangeTimes"				//�һ�����
#define JSKEY_ZERO_SPAN						"zeroSpan"					//��Ե������ƫ��
#define JSKEY_TIME_MAX						"timeMax"					//ʱ�����ƫ��
#define JSKEY_PRIZE_ID						"prizeId"					//����id
#define JSKEY_RESOURCE						"resource"					//��Դ
#define JSKEY_WEEK_ID						"weekId"				    //��id������ĵ�n�ܣ�
#define JSKEY_MAP_ID						"mapId"						//��ͼ���
#define JSKEY_DESCRIBE						"describe"				    //������Ϣ
#define JSKEY_INFO							"info"						//��Ϣ
#define JSKEY_CHALLENGE_TIME				"challengeTime"				//��սʱ��
#define JSKEY_GAME_ID						"gameid"					//��Ϸid
#define JSKEY_OFFENSE_GAMEID				"offenseGameid"				//��������Ϸid
#define JSKEY_DEFEND_GAMEID					"defendGameid"				//���ط���Ϸid
#define JSKEY_CASH_RMB						"cashRMB"					//�ֽ�RMB
#define JSKEY_GEMSTONE_DISCOUNT				"gemstoneDiscount"			//�ۺ�ʯ����
#define JSKEY_GEMSTONE_ALL					"gemstoneAll"				//����ǰʣ�౦ʯ����
#define JSKEY_DISCOUNT						"discount"					//�ۿ�
#define JSKEY_BUY_GEMSTONE_INFO				"gemstoneInfoList"			//����ʯ�ۿ��б�
#define JSKEY_BROTHER_TASKLIST				"brotherhoodList"			//�ֵܹ�ϵ��ǰ�����б�
#define JEKEY_BROTHER_TYPE					"brotherhoodType"			//�ֵܹ�ϵ���ͣ� �ֵܸ������ֵܳɾ��Ǽ�����
#define JSKEY_BROTHER_ID					"brotherCurrKey"			//��ǰ�ȼ���id��
#define JSKEY_BROTHER_VALUE					"brotherCurrVal"			//��ǰֵ���ֵܸ������ɾ��Ǽ�������

#define JSKEY_BROTHERINFO_LIST				"brotherInfoList"			//�ֵ���Ϣ�б�
#define JSKEY_TOTAL_STARS					"totalStars"				//�ɾ����Ǽ�����
#define JSKEY_TIME							"time"						//ʱ��


#define JSKEY_ACTION						"action"					//����
//�������

//////////////////////////////////////////////////////////////////////////
#define JSKEY_CLAN_DESC						"clanDesc"					//��������
#define JSKEY_CLAN_LEADER_NAME				"leaderNick"				//�����ǳ�
#define JSKEY_CLAN_CURR_MEMBER				"currMember"				//��ǰ����
#define JSKEY_CLAN_MAX_MEMBER				"maxMember"					//�������
#define JSKEY_CLAN_EXPERIENCE				"clanExperience"			//����
#define JSKEY_CLAN_LIST						"clanList"					//�����б�
#define JSKEY_CLAN_REQ_LIST					"clanReqList"				//�����б�
#define JSKEY_ORDER_ID						"orderid"					//���
#define JSKEY_CLAN_MEMLIST					"clanMemlist"				//�����Ա�б�
#define JSKEY_CLAN_CONSTRIBUION				"totalContribution"			//�ۼƹ���ֵ
#define JSKEY_CLAN_YESTERDAY				"yesterdayContribution"		//���չ���ֵ		
#define JSKEY_OLD_RANK						"oldRank"					//�ϵ����
#define JSKEY_NEW_RANK						"newRank"					//�����
#define JSKEY_CLAN_MIN_CUPNUM				"cupNumLimit"				//��С��������
#define JSKEY_CLAN_STATECACHE				"clanStateCache"			//����
#define JSKEY_REQ_STATE						"reqState"					//����״̬
#define JSKEY_KICK_TIMES					"kickTimes"					//�߳�����ʣ�����
#define JSKEY_CLAN_DONATE_TYPE				"clandonateType"			//�����������
#define JSKEY_CLAN_DONATE_NEXTTIME			"clandonateNextTime"		//�����������
#define JSKEY_CLAN_AVAILABLE_CONTRIBUTE		"clanAvailableContribute"	//������ù��׵�
#define JSKEY_CLAN_BUILD_NUM				"buildDonateNum"			//���տ�����ѽ����������
#define JSKEY_CLAN_BUILD_TIME				"buildDonatTime"			//��������
#define JSKEY_CLAN_DONATE_WATER_TIME		"donateWaterTime"			//�������ʥˮ
#define JSKEY_CLAN_DONATE_DIAMOND_TIME		"donateDiamondTime"			//������ױ�ʯ
#define JSKEY_CLAN_WINPOINT					"winPoint"					//ʤ��
#define JSKEY_CLAN_LAST_WINPOINT			"lastWinPoint"				//������ʤ��
#define JSKEY_CLAN_WINPOINT_RANKLIST		"winPointRankList"			//ʤ�������б�
#define JSKEY_CLAN_SEASON_NUM				"clanSeasonNum"				//ս�����ݵ�ǰ������
#define JSKEY_CLAN_RESOURCE_LIST			"clanResourceList"			//����ֿ���Դ�б�
#define JSKEY_CLAN_WINPOINT_RANK_LIST		"WinPointRankList"			//��������Ϣ
#define JSKEY_CLAN_DEFEND_USER_INFO			"defendUserInfo"			//����ս����־���ط���Ϣ
#define JSKEY_CLAN_TIME						"clanTime"					//ս��������������ʱ��


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
    uint8 g_userType;		//ȫ���û����ͣ��������ۡ��ͷ��ȣ�
    uint8 flag;		//flagָʾ���û��������,�Ƿ�������ͷ,�Ƿ��ڻ�����
    uint8 devType;
    uint16 forBidTime;			//����ʣ��ʱ��
    uint64 money;		//�û��ʽ�
   // UserLevel level;		//�Ƿ��Ա
    uint64 received;
    //MicInfo micInfo;
    
    //Customface customface;//�Զ���ͷ��汾
    uint8 richerOrder;  //��������, δ����������Ϊ0, ����Ϊ��Ӧ����ֵ
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

	//���ظð��Ƿ��ظ�,����ظ�,����false;������ظ�,����true
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
	uint8   userType;				//ȫ�����û����ԣ��������ۡ��ͷ��ȣ�
	uint32	flag;
	uint64  money;
	uint64 received;
	uint8	richOrder;
	uint8   accountState;
	uint8	msgsetup;
	uint16  textPort;
	uint16  audioPort;
	uint16	boxfreetime; //������ѿ���ʱ��
	uint16	videoPort;
	uint32  textIp;
	uint32  audioIp;
	uint32  videoIp;

	string enter_title;
	string enter_pic;
	string aclctrlstr; //Ȩ�޿���
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
	uint16			maxcfuser;									//�������
	uint16			maxMicQueue;
	uint16			maxmanager;
	uint16			roomSize;
	uint8			ispublic;
	uint8			auth;
	string			singnature;									//ý������ǩ��
	uint8			openstatus;
	bool			autoMic;
	uint8			m_audiosampleindex;		
	uint8			m_audiobitrateindex;
	//MediaSvrList	avSrvList;									//�˷�������Ƶ�������ɣе�ַ
	uint16			avPort;										//���������ƵƵ��������Ƶ�˿�
	bool			bEnableColorBar;//�Ƿ��Ͳ��� true���� 
	uint32			micArray[MAX_MIC_USER_NUM];					//��ǰ�����û�
	uint16          micmaxtime[MAX_MIC_USER_NUM];				//���������û�����ʱ
	uint8			micDevType[MAX_MIC_USER_NUM];				//��ǰ���û��豸����
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


//�ȴ����ṹ,ֻ�ڵȴ���ʱ����Ч����ChatConnection��Init��ʱ���������
class WATI_STRUCT {
public:
	LOGONINFO		m_logoninfo;
	ROOMINFO		m_rminfo;
	//TENROOMINFO		m_tenrminfo;//
	//	ROOMADV			m_rmadv;
	RoomMember		m_roomMember;
	RoomMember		m_roomVisitor;
	//	WebInfo			m_webInfo;	
	//USER_VECTOR		m_userVector;		  //�û��б�
	UINT_VECTOR		m_micVec;			    //����б�
	UINT_VECTOR		m_blackUinVec;		//�������û��б�
	MicQueueVector		m_cfWaitVec;		  //����ȴ��û��б�

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