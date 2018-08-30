#ifndef		COC_STRUCT_H
#define		COC_STRUCT_H
#include <list>
#include <map>
#include <time.h>
#include "CocCmdDefine.h"

#define   MAP_MAX  3
#define  MAX_LEN_WIDE 8
#define	 MAX_TRAINS 8
#define	 MAP_POS 2
#define  MAX_RESEARCH	2
#define MAP_LENGTH  44
#define MAP_WIDTH	44
#define EDGE_LEN	2
#define MAP_PACKET_SIZE 80
#define SOLDIER_PACKET_SIZE 128
#define ATTACK_PACKET_SIZE 10						//���������10��

#define     WEIGHT_NORMAL	100
#define     WEIGHT_WALL	1000
#define		CHANGENAME_COST	100
enum
{
	COC_ERRO,
	COC_DEBUG,
	COC_NORMAL,
	COC_INFO,
	COC_SHOW,
};
enum
{
	MONEY_STATION = 0,		//վ���˻�
	MONEY_PLATFORM,			//ƽ̨�˻�
};
namespace COCStruct
{
	//ս��״̬״̬
	enum WarType
	{
		WAR_NORMAL,
		WAR_ATTACK,
		WAR_CHALLENGE,
	};
	enum state
	{
		USER_STATE_OFFLINE,
		USER_STATE_ONLINE,
		USER_STATE_WAIT,
		USER_STATE_ONATTACK,
		USER_STATE_CHALLENGE,
		USER_STATE_ADROID = 0x10,
	};
	//ʿ������
	enum
	{
		SOLDIER_GROUP_BARRACK,		//��Ӫ
		SOLDIER_GROUP_CASTLE,		//�Ǳ�
	};
	//��Դ����
	enum
	{
		RESOURCE_GOLD,
		RESOURCE_HOLYWARTER,
		RESOURCE_BLACKWATER,
		RESOURCE_GEMSTONE,
		RESOURCE_MAX,
		RESOURCE_TIME,
	};
	//������״̬
	enum BuildState
	{
		STATE_NORMAL = 0,
		STATE_BUILD,
		STATE_UPDATE,
		STATE_REMOVE,
		STATE_PRODUCE,		//���������ܱ�ʹ��
		STATE_DESTROY,
		STATE_LOSE_EFFICACY,
	};
	//��������
	enum BuildType
	{
		//��ǽ
		TYPE_WALL = 10,
		//
		TYPE_MAGIC_FACTORY = 11,				//��������
		TYPE_LAB,								//ʵ����
		TYPE_TRAINS,							//ѵ��Ӫ
		TYPE_ARMY,								//��Ӫ
		TYPE_CLAN_CASTLE,						//����Ǳ�
		TYPE_MAGE_TOWER,						//��ʦ��
		TYPE_BOWS_TOWER,						//����
		TYPE_CANNON,							//��ũ��
		TYPE_MORTAR,							//�Ȼ���
		TYPE_XREPEANG_CROSSBOW,					//X����
		TYPE_WORKERHOUSE,						//��������С��
		TYPE_BASE_CAMP,							//��Ӫ
		TYPE_GOLD_ORE,							//���		
		TYPE_HOLY_WATER_COLLECT,				//ʥˮ�ռ���
		TYPE_GOLD_POT,							//�����
		TYPE_ANTI_AIRCRAFT_ROCKET,				//���ջ��
		TYPE_DARK_HEAVYOIL_WELL,				//���������꾮
		TYPE_DARK_HEAVYOIL_POT,					//�������͹�
		TYPE_DARK_TRAINS_CAMP,					//����ѵ��Ӫ
		TYPE_HELL_TOWER,						//����֮��
		TYPE_HOLY_WATER_BOTTLE,					//ʥˮƿ
		TYPE_TESLA_TOWE,						//��˹�������
		TYPE_BARBARIAN_KING,					//Ұ����֮��
		TYPE_ARCHERQUEEN,						//����Ů��

		//����
		TYPE_TRAP_SKELETON,						//��������
		TYPE_BOMB_INVISIBLE,					//����ը��
		TYPE_BOMB_GIANTISM,						//����ը��
		TYPE_BOMB_SKY,							//����ը��
		TYPE_MINE_SERCH_SKY,					//�ѿյ���
		TYPE_SPRING_INVISIBLE,					//���ε���

		TYPE_TRAP_MAX,	//����ֵ�߽�
		//װ��
		/////��Ҫ����
		//�ϰ���
		TYPE_GRASS = 501,		//�ݶ�
		TYPE_BUSH,				//��ľ
		TYPE_TRUNK,				//����
		TYPE_WOOD_CHIP,			//ľƬ
		TYPE_TREE1,
		TYPE_TREE2,
		TYPE_TREE3,
		TYPE_GRAVEL,					//��ʯ
		TYPE_PERISTELE,					//ʯ��
		TYPE_STONE,						//ʯ��
		TYPE_GRAVESTONE,				//Ĺ��
		TYPE_BLACK_GRAVESTONE,			//��Ĺ��
		TYPE_GEMSTONE_BOX,				//��ʯ��
	};
	enum mode
	{
		MODE_CLAN,
		MODE_WAR,
		MODE_MAX,
	};
	enum soldierMode
	{
		SOLDIER_OWN,
		SOLDIER_CANUSE,
	};
	class ProduceItem
	{
	public:
		ProduceItem()
		{
			m_num = 0;
			m_useSpace = 0;
			m_produceType = 0;
			m_useTime = 0;
			m_produceId = 0;
			m_startTime = 0;
		};
		ProduceItem(uint16 type, uint8 num, uint32 useTime, uint8 useSpace, uint32 produceId, uint32 startTime)
		{
			m_num = num;
			m_useSpace = useSpace;
			m_produceType = type;
			m_useTime = useTime;
			m_produceId = produceId;
			m_startTime = startTime;
		}
		ProduceItem & operator = (const ProduceItem &rhs)
		{
			if (this == &rhs)
			{
				return *this;
			}
			m_num = rhs.m_num;
			m_produceType = rhs.m_produceType;
			m_useSpace = rhs.m_useSpace;
			m_useTime = rhs.m_useTime;
			m_produceId = rhs.m_produceId;
			m_startTime = rhs.m_startTime;
			return *this;
		}
	public:
		uint8 m_num; 
		uint8 m_useSpace;
		uint16 m_produceType; 	
		uint32 m_useTime;
		uint32 m_produceId;
		uint32 m_startTime;
	};
	//����������
	class EndProduced
	{
	public:
		static bool LessThan(EndProduced lhd, EndProduced rhd)
		{
			return lhd.m_endTime < rhd.m_endTime;
		}
	public:
		EndProduced(){};
		EndProduced(uint16 produceType, uint32 endTime, uint8 useSpace,uint32 produceId)
		{
			m_useSpace = useSpace;
			m_produceType = produceType;
			m_produceId = produceId;		
			m_endTime = endTime;
			m_startTime = 0;
		}
		EndProduced & operator = (const EndProduced &rhs)
		{
			if (this == &rhs)
			{
				return *this;
			}
			m_useSpace = rhs.m_useSpace;
			m_produceType = rhs.m_produceType;
			m_produceId = rhs.m_produceId;		
			m_endTime = rhs.m_endTime;
			m_startTime = rhs.m_startTime;
			return *this;
		}
	public:
		uint8 m_useSpace;
		uint16 m_produceType;
		uint32 m_produceId;	
		uint32 m_endTime;
		uint32 m_startTime;
	};
	typedef std::list<COCStruct::ProduceItem *>  ProducetItemList;
	typedef std::list<COCStruct::EndProduced *>  EndProducetList;
	//ʿ��
	class Soldiers
	{
	public:
		Soldiers()
		{ 
			m_type = 0; 
			m_level = 1; 
			m_num = 0; 
			m_group = 0;
			m_timeOffset = 0;
		}
		Soldiers(uint16 type, uint8 level, uint8 num, uint8 group,uint8 xpos, uint8 ypos, uint32 timeOffset)
		{ 
			m_type = type; 
			m_level = level; 
			m_num = num; 
			m_group = group;
			m_xpos = xpos;
			m_ypos = ypos;
			m_timeOffset = timeOffset;
		}

	public:
		uint16 m_type;		//ʿ������
		uint8  m_level;		//ʿ���ȼ�
		uint8  m_num;		//��Ŀ
		uint8  m_group;		//ʿ��������
		uint8  m_xpos;		
		uint8  m_ypos;
		uint32 m_timeOffset; //ʱ��ƫ����
	}; 
	//�ڵ�ͼ�ϵ�����
	class Position
	{
	public:
		Position()
		{
			m_xpos = 0;
			m_ypos = 0;
		};
		Position(uint8 xpos,uint8 ypos)
		{
			m_xpos = xpos;
			m_ypos = ypos;
		};
		uint8 m_xpos;					//��ͼ������x
		uint8 m_ypos;					//��ͼ������y
	};
	//�ڵ�ͼ�ϵ�����
	class BuildPosition : public Position
	{
	public:
		BuildPosition():Position()
		{
			m_num = 0;
			m_type = 0;
		};
		BuildPosition(uint8 xpos,uint8 ypos, uint16 type, uint8 num):Position(xpos, ypos)
		{
			m_type = type;
			m_num = num;
		};
		uint8 m_num;					//���
		uint16 m_type;					//��������
	};
	//����������
	class BuildingAttribute
	{
	public:
		virtual ~BuildingAttribute(){};
		BuildingAttribute(){};
		BuildingAttribute(uint8 num, uint8 xpos, uint8 ypos, uint8 length, uint8 width, uint8 group, uint8 level = 0)
		{
			m_level = level;			
			m_num = num;
			m_pos[0][0].m_xpos = xpos;
			m_pos[0][0].m_ypos = ypos;
			m_group = group,
			m_length = length;
			m_width = width;
			m_state = STATE_NORMAL;
			m_startTime = time(NULL);
			m_canPlunder = 0;
		}
		virtual std::string PositionToJsonString(uint8 mapMode){ return "";};
		virtual void JsonStringToPosition(){};
		virtual std::string DefendPositionToJsonString(uint8 mapMode, uint8 index){ return "";};
		void ClearCanPlunder()
		{
			m_canPlunder = 0;
		}
	public:
		uint16 m_type;					//����(�����)
		uint8 m_level;					//�ȼ�
		uint8 m_num;					//������
		uint8 m_state;					//��ǰ��״̬(�������������Ƴ�������)	
		uint8 m_length;					//ռ�÷���ĳ���
		uint8 m_width;					//ռ�÷���Ŀ��
		uint8 m_group;					//������������
		Position m_pos[MODE_MAX][MAP_MAX];	//�ڵ�ͼ�ϵ�����(����ģʽ)
		uint32 m_startTime;				//������ʼʱ��
		uint32 m_canPlunder;									//���Ӷ�������
		std::string m_strPos[MODE_MAX];		//json ��ʽ����
		std::string m_strPosDefend;			//���ص�ͼ ����
	};	
	typedef std::map<uint32, BuildingAttribute*> BuildingAttributeMap;
	typedef std::list<BuildingAttribute> BuildingAttributeList;
	class GateMapInfo
	{
	public:
		GateMapInfo()
		{
			m_type = 0;
			m_num = 0;
			m_level = 0;
			m_xpos = 0;
			m_ypos = 0;
		}
	public:
		uint16 m_type;					//����(�����)
		uint8 m_num;					//������
		uint8 m_level;					//�ȼ�		
		uint8 m_xpos;					//x����
		uint8 m_ypos;					//y����
	};
	typedef std::list<GateMapInfo> GateMapInfoList; 
	class CocUserInfo
	{
	public:
		CocUserInfo()
		{
			m_userstate = USER_STATE_WAIT;
			m_step = 0;
			m_cup = 0;
			m_leagueLevel = 1;
			m_level = 0;
			m_expCurr = 0;
			m_shieldEndTime = 0;
			m_shieldCoolEndTime = 0;
			m_seekHelpEndTime = 0;
			m_seekHelpCoolEndTime = 0;
			m_clanName = "";
			m_clanId = 0;
			m_clanJob = 0;
			m_exchangeTimes = 0;
			m_zeroTime = 0;
			m_mapIndexClan = 0;
			m_mapIndexWar = 0;
			m_obstacleLastTime = 0;
			m_gemstoneLastTime = 0;
			m_refreshIndex = 0;
			m_soldierCapacityMax = 20;
			m_soldierCapacityCurr = 0;
			m_CastleCapacityCurr = 0;
			m_CastleCapacityMax = 0;
			m_offLineTime = 0;
			m_loginTime = time(NULL);
			m_offenceSuccess = 0;
			m_defendSuccess = 0;
			m_clanIconNum = 0;
			m_attackTime = 0;
			m_prepareAttackTime = 0;
			m_firstCharge = COC_FIRSTCHARGE_NOT_ACTIVE;
			m_gameid = 0;
			m_clanState = COCClanState::CLAN_NORMAL_STATE;
			m_clanTime = 0;
		}

		enum COCFistChargeState
		{
			COC_FIRSTCHARGE_NOT_ACTIVE,		//����δ����
			COC_FIRSTCHARGE_ACTIVE,			//���񼤻�
			COC_FIRSTCHARGE_FINISHED,		//�������
		};
	public:
		uint8 m_firstCharge;						//�׳��־
		uint8 m_userstate;							//����״̬
		uint8 m_step;								//���ֽ̳̲���
		uint16 m_cup;								//��������
		uint8 m_leagueLevel;						//��������
		uint8 m_level;								//��Ϸ�ȼ�
		uint32 m_expCurr;							//����ֵ
		uint32 m_shieldEndTime;						//����ʱ��
		uint32 m_shieldCoolEndTime;					//������ȴʱ��
		uint32 m_seekHelpEndTime;					//��Ԯ����ʱ��
		uint32 m_seekHelpCoolEndTime;				//��Ԯ��ȴ����ʱ��
		std::string m_name;							//��ɫ����
		std::string m_clanName;						//������������
		uint32 m_clanId;							//��������
		uint8  m_clanJob;							//����ְλ
		uint8  m_clanState;
		uint32	m_clanTime;							//���������ȴ
		uint8 m_exchangeTimes;						//�һ�����
		uint32 m_zeroTime;							//�����賿ʱ���
		uint32 m_clanIconNum;						//����ͼ����
		uint8 m_mapIndexClan;						//����ģʽʹ�õĵ�ͼid	
		uint8 m_mapIndexWar;						//ս��ģʽ��ʹ�õ�ͼid
		uint32 m_obstacleLastTime;					//��һ��ˢ���ϰ����ʱ��
		uint32 m_gemstoneLastTime;					//��һ��ˢ���ϰ����ʱ��
		uint8 m_refreshIndex;						//ÿ��ˢ�¶����� ��20 һѭ����
		uint16 m_soldierCapacityMax;				//��������˿�����
		uint16 m_soldierCapacityCurr;				//��Ӫ��ǰ���˿�����
		uint16 m_CastleCapacityCurr;				//��ǰԮ������
		uint16 m_CastleCapacityMax;					//��������˿�����
		uint32 m_attackTime;						//�����ʱ��
		uint32 m_offLineTime;						//����ʱ��
		uint32 m_loginTime;							//����ʱ���
		uint32 m_offenceSuccess;					//�ɹ���������
		uint32 m_defendSuccess;						//�ɹ����ش���
		uint32 m_prepareAttackTime;					//��ƥ�䵽��, ׼��ʱ��
		uint32 m_gameid;							//��ϷΨһid						
	};
	class Resourse
	{
	public:
		Resourse()
		{
			m_currNum = 0;
			m_max = 0;
		}
		Resourse & operator = (const Resourse & res)
		{
			m_currNum = res.m_currNum;
			m_max = res.m_max;
			return *this;
		}
	public:
		uint32 m_currNum;						//��ǰ����
		uint32 m_max;						//���洢����
	};
	class Plunder
	{
	public:
		Plunder()
		{
			Clear();
		}
		Plunder & operator = (const Plunder & res)
		{
			m_produce = res.m_produce;
			m_store = res.m_store;
			m_max = res.m_max;
			return *this;
		}
		void Clear()
		{
			m_produce = 0;
			m_store = 0;
			m_max = 0;
		}
	public:
		uint32 m_produce;						//��ǰ����
		uint32 m_store;						//���洢����
		uint32 m_max;						//���洢����
	};
	class WorkingInfo
	{	
	public:
		WorkingInfo()
		{
			m_workId = 0;
			m_startTime = 0;
			m_endTime = 0;
		}
		WorkingInfo(const WorkingInfo & info)
		{
			m_workId = info.m_workId;
			m_startTime = info.m_startTime;
			m_endTime = info.m_endTime;
		}
		// 		WorkingInfo(uint32 workId, uint32 startTime, uint32 endTime)
		// 		{
		// 			m_workId = workId;
		// 			m_startTime = startTime;
		// 			m_endTime = endTime;
		// 		}
	public:
		uint32 m_workId;				//������� 
		uint32 m_startTime;				//������ʼʱ��
		uint32 m_endTime;				//����������ʱ�� ����/����/ɾ�� ���ʱ��	
	};
	typedef std::list<WorkingInfo> WorkingInfoList;
	// 	struct TimeRamge
	// 	{
	// 		TimeRamge()
	// 		{
	// 			startTime = 0;
	// 			endTime = 0;
	// 		}
	// 		uint32 startTime;
	// 		uint32 endTime;
	// 	};
	enum TimeNodeType
	{
		NODE_SPEED_BUILD,
		NODE_SPEED_PRODUCE,
		//	NODE_TIME,
	};
	struct TimeSlot
	{
		TimeSlot()
		{
			timeNodeId = 0;
			startTime = 0;
			endTime = 0;
			timeType = 0;
		}
		uint32 timeNodeId;
		uint32 startTime;
		uint32 endTime;
		uint8 timeType;
	};
	typedef std::map <uint32, TimeSlot> TimeSlotMap;
	typedef std::map <uint32, TimeSlot> TimeNodeMap;
	typedef std::map <uint16, uint8> SoldierMap;
	class AttackHistory
	{
		std::string str_offenseUser;		//��������Ϣ
		std::string str_defendUser;			//���ط���Ϣ
		std::string str_sendsoldier;		//�ɱ���Ϣ
		std::string str_battleRepor;		//ս����¼		
		uint32 attackTime;					//����ʱ��
		uint32 offensePid;					//������pid
		uint32 offenseUin;					//������uin
		uint32 defendPid;					//���ط�pid
		uint32 defendUin;					//���ط�uin
	};
	typedef std::map<uint32 ,AttackHistory *> AttackHistoryMap;
	class Achievement
	{
	public:
		Achievement(const Achievement &rhs)
		{
			m_achvId = rhs.m_achvId;
			m_completeLevel = rhs.m_completeLevel;
			m_currValue = rhs.m_currValue;
			m_level = rhs.m_level;
		}
		Achievement(uint16 achvId)
		{
			m_currValue = 0;
			m_level = 1;
			m_completeLevel = 0;
			m_achvId = achvId;
		}
	public:
		uint32 m_currValue;					//��ǰ��ɵ����������ߵȼ���
		uint16 m_achvId;					//�ɾ�id
		uint8  m_level;						//��ǰ�ĳɾ����񣨽����л�����ɣ�
		uint8  m_completeLevel;				//�Ѿ���ȡ
	};
	typedef std::map<uint16, Achievement*> AchievementMap;
	class AttackHistoryInfo
	{
	public:
		AttackHistoryInfo()
		{
			offenseGameid = 0;
			offensePid = 0;
			offenseUin = 0;
			defendGameid = 0;
			defendPid = 0;
			defendUin = 0;
			attackTime = 0;
			keyId = 0;
			m_canRevenge = 1;
		}
	public:
		uint32 offenseGameid;
		uint32 offensePid;
		uint32 offenseUin; 
		uint32 defendGameid;
		uint32 defendPid;
		uint32 defendUin; 
		uint32 attackTime;
		uint32 keyId;
		uint8 m_canRevenge;
		std::string strSendsoldier;
		std::string strOffenseUser; 
		std::string strDefendUser;
		std::string strBattleReport;
	};
	class TollGateInfo
	{
	public:
		TollGateInfo()
		{
			Init();
		}
		inline void Init(uint8 gateIndex, uint8 star, uint32 gold, uint32 holywater, uint32 m_blackwater)
		{
			m_gateIndex = gateIndex;
			m_star = star;
			m_gold = gold;
			m_holywater = holywater;
			m_blackwater = m_blackwater;
		}
		inline void Init()
		{
			m_gateIndex = 0;
			m_gold = 0;
			m_holywater = 0;
			m_blackwater = 0;
			m_star = 0;
		}
	public:
		uint8 m_gateIndex;		//�ؿ����
		uint8 m_star;			//ս��
		uint32 m_gold;			//���
		uint32 m_holywater;		//ʥˮ
		uint32 m_blackwater;	//��ˮ	

	};
	typedef std::list<TollGateInfo> TollGateList; 
	class RankingItem
	{
	public:
		RankingItem()
		{
			Init();
		}
		RankingItem & operator = (const RankingItem & res)
		{
			m_cup = res.m_cup;
			m_leagueLevel = res.m_leagueLevel;
			m_level = res.m_level;
			m_rankNum = res.m_rankNum;
			m_pid = res.m_pid;
			m_uin = res.m_uin;
			m_name = res.m_name.c_str();
			m_offenceSuccess = res.m_offenceSuccess;
			m_defendSuccess = res.m_defendSuccess;
			m_clanId = res.m_clanId;
			m_clanIconNum = res.m_clanIconNum;
			m_clanName = res.m_clanName.c_str();
			return *this;
		}
		void Init()
		{
			m_cup = 0;
			m_leagueLevel = 0;
			m_level = 0;
			m_rankNum = 0;
			m_pid = 0;
			m_uin = 0;
			m_offenceSuccess = 0;
			m_defendSuccess = 0;
			m_clanId = 0;
			m_clanIconNum = 0;
			m_name.clear();
			m_clanName.clear();
		}
	public:
		uint16 m_cup;								//��������
		uint8 m_leagueLevel;						//��������
		uint8 m_level;								//��Ϸ�ȼ�
		uint16 m_rankNum;							//����
		uint32 m_pid;								//pid
		uint32 m_uin;								//uin
		std::string m_name;							//��ɫ�ǳ�
		uint32 m_offenceSuccess;					//�ɹ���������
		uint32 m_defendSuccess;						//�ɹ����ش���
		uint32 m_clanId;							//��������
		uint32 m_clanIconNum;						//����ͼ����
		std::string m_clanName;						//������������		
	};
	enum MsgType
	{
		SYSTEM,		//ϵͳ�ʼ�
		PRIZE,		//ϵͳ�����ʼ�
		USER,		//�û��ʼ�
	};
	class MailMsg
	{
	public:
		MailMsg()
		{
			startTime = 0;
			dueTime = 0;
			msgId = 0;
			pid = 0;
			uin = 0;	
			gold = 0;
			holyWater = 0;
			blackWater = 0;
			gemstone = 0;
			msgType = 0;	
			addTime = 0;
		};
	public:
		std::string from;		//��Ϣ��Դ
		std::string msg;		//��Ϣ����
		std::string url;		//url
		uint32 startTime;		//��Ϣ��ʼʱ��
		uint32 dueTime;			//��Ч��
		uint32 msgId;			//��Ϣid
		uint32 pid;
		uint32 uin;				
		uint32 gold;			//���
		uint32 holyWater;		//ʥˮ
		uint32 blackWater;		//��ˮ
		uint32 gemstone;		//��ʯ
		uint8 msgType;			//��Ϣ����
		uint32 addTime;			//���ʱ��
	};
	class SysMsg
	{
	public:		
		SysMsg()
		{
			msgType = 0;
			showSpan = 0;
			startTime = 0;
			msgId = 0;
			dueTime = 0;
			pid = 0;
			addTime = 0;
		}
	public:
		uint8 msgType;			//��Ϣ����
		uint32 startTime;		//��Ϣ��ʼʱ��
		uint16 showSpan;		//��ʾ���ʱ��
		uint32 msgId;			//��Ϣid
		uint32 dueTime;			//��Ч��
		uint32 pid;				//վ��id
		std::string msg;		//��Ϣ����
		uint32 addTime;			//���ʱ��
	};
	class ClanSeasonInfo
	{
	public:
		ClanSeasonInfo()
		{
			clanid = 0;
			clan_rank = 0;
			clan_point = 0;
			clan_name = "";
		}
		uint16 clanid;
		uint32 clan_rank;
		uint32 clan_point;
		std::string clan_name;
	};
};
#endif

