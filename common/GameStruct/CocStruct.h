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
#define ATTACK_PACKET_SIZE 10						//单个包最大10条

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
	MONEY_STATION = 0,		//站点账户
	MONEY_PLATFORM,			//平台账户
};
namespace COCStruct
{
	//战争状态状态
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
	//士兵属组
	enum
	{
		SOLDIER_GROUP_BARRACK,		//军营
		SOLDIER_GROUP_CASTLE,		//城堡
	};
	//资源类型
	enum
	{
		RESOURCE_GOLD,
		RESOURCE_HOLYWARTER,
		RESOURCE_BLACKWATER,
		RESOURCE_GEMSTONE,
		RESOURCE_MAX,
		RESOURCE_TIME,
	};
	//建筑物状态
	enum BuildState
	{
		STATE_NORMAL = 0,
		STATE_BUILD,
		STATE_UPDATE,
		STATE_REMOVE,
		STATE_PRODUCE,		//废弃，不能被使用
		STATE_DESTROY,
		STATE_LOSE_EFFICACY,
	};
	//物体种类
	enum BuildType
	{
		//城墙
		TYPE_WALL = 10,
		//
		TYPE_MAGIC_FACTORY = 11,				//法术工厂
		TYPE_LAB,								//实验室
		TYPE_TRAINS,							//训练营
		TYPE_ARMY,								//兵营
		TYPE_CLAN_CASTLE,						//部落城堡
		TYPE_MAGE_TOWER,						//法师塔
		TYPE_BOWS_TOWER,						//箭塔
		TYPE_CANNON,							//加农炮
		TYPE_MORTAR,							//迫击炮
		TYPE_XREPEANG_CROSSBOW,					//X连弩
		TYPE_WORKERHOUSE,						//建筑工人小屋
		TYPE_BASE_CAMP,							//大本营
		TYPE_GOLD_ORE,							//金矿		
		TYPE_HOLY_WATER_COLLECT,				//圣水收集器
		TYPE_GOLD_POT,							//储金罐
		TYPE_ANTI_AIRCRAFT_ROCKET,				//防空火箭
		TYPE_DARK_HEAVYOIL_WELL,				//暗黑重油钻井
		TYPE_DARK_HEAVYOIL_POT,					//暗黑重油罐
		TYPE_DARK_TRAINS_CAMP,					//暗黑训练营
		TYPE_HELL_TOWER,						//地狱之塔
		TYPE_HOLY_WATER_BOTTLE,					//圣水瓶
		TYPE_TESLA_TOWE,						//特斯拉电磁塔
		TYPE_BARBARIAN_KING,					//野蛮人之王
		TYPE_ARCHERQUEEN,						//弓箭女皇

		//陷阱
		TYPE_TRAP_SKELETON,						//骷髅陷阱
		TYPE_BOMB_INVISIBLE,					//隐形炸弹
		TYPE_BOMB_GIANTISM,						//巨型炸弹
		TYPE_BOMB_SKY,							//空中炸弹
		TYPE_MINE_SERCH_SKY,					//搜空地雷
		TYPE_SPRING_INVISIBLE,					//隐形弹簧

		TYPE_TRAP_MAX,	//陷阱值边界
		//装饰
		/////需要补充
		//障碍物
		TYPE_GRASS = 501,		//草堆
		TYPE_BUSH,				//灌木
		TYPE_TRUNK,				//树干
		TYPE_WOOD_CHIP,			//木片
		TYPE_TREE1,
		TYPE_TREE2,
		TYPE_TREE3,
		TYPE_GRAVEL,					//碎石
		TYPE_PERISTELE,					//石柱
		TYPE_STONE,						//石块
		TYPE_GRAVESTONE,				//墓碑
		TYPE_BLACK_GRAVESTONE,			//黑墓碑
		TYPE_GEMSTONE_BOX,				//宝石盒
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
	//结束生产项
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
	//士兵
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
		uint16 m_type;		//士兵类型
		uint8  m_level;		//士兵等级
		uint8  m_num;		//数目
		uint8  m_group;		//士兵所属组
		uint8  m_xpos;		
		uint8  m_ypos;
		uint32 m_timeOffset; //时间偏移量
	}; 
	//在地图上的坐标
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
		uint8 m_xpos;					//地图上坐标x
		uint8 m_ypos;					//地图上坐标y
	};
	//在地图上的坐标
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
		uint8 m_num;					//编号
		uint16 m_type;					//建筑类型
	};
	//建筑物属性
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
		uint16 m_type;					//类型(物件的)
		uint8 m_level;					//等级
		uint8 m_num;					//物体编号
		uint8 m_state;					//当前的状态(建筑，生产，移除，升级)	
		uint8 m_length;					//占用方格的长度
		uint8 m_width;					//占用方格的宽度
		uint8 m_group;					//建筑所属分组
		Position m_pos[MODE_MAX][MAP_MAX];	//在地图上的坐标(部落模式)
		uint32 m_startTime;				//生产起始时间
		uint32 m_canPlunder;									//可掠夺的最大数
		std::string m_strPos[MODE_MAX];		//json 格式坐标
		std::string m_strPosDefend;			//防守地图 坐标
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
		uint16 m_type;					//类型(物件的)
		uint8 m_num;					//物体编号
		uint8 m_level;					//等级		
		uint8 m_xpos;					//x坐标
		uint8 m_ypos;					//y坐标
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
			COC_FIRSTCHARGE_NOT_ACTIVE,		//任务未激活
			COC_FIRSTCHARGE_ACTIVE,			//任务激活
			COC_FIRSTCHARGE_FINISHED,		//任务完成
		};
	public:
		uint8 m_firstCharge;						//首冲标志
		uint8 m_userstate;							//在线状态
		uint8 m_step;								//新手教程步骤
		uint16 m_cup;								//奖杯数量
		uint8 m_leagueLevel;						//联赛级别
		uint8 m_level;								//游戏等级
		uint32 m_expCurr;							//经验值
		uint32 m_shieldEndTime;						//护盾时间
		uint32 m_shieldCoolEndTime;					//护盾冷却时间
		uint32 m_seekHelpEndTime;					//求援结束时间
		uint32 m_seekHelpCoolEndTime;				//求援冷却结束时间
		std::string m_name;							//角色名称
		std::string m_clanName;						//所属部落名称
		uint32 m_clanId;							//所属部落
		uint8  m_clanJob;							//部落职位
		uint8  m_clanState;
		uint32	m_clanTime;							//部落操作冷却
		uint8 m_exchangeTimes;						//兑换次数
		uint32 m_zeroTime;							//当日凌晨时间戳
		uint32 m_clanIconNum;						//部落图标编号
		uint8 m_mapIndexClan;						//部落模式使用的地图id	
		uint8 m_mapIndexWar;						//战争模式下使用地图id
		uint32 m_obstacleLastTime;					//上一次刷新障碍物的时间
		uint32 m_gemstoneLastTime;					//上一次刷新障碍物的时间
		uint8 m_refreshIndex;						//每次刷新都递增 （20 一循环）
		uint16 m_soldierCapacityMax;				//最大容纳人口数量
		uint16 m_soldierCapacityCurr;				//军营当前的人口数量
		uint16 m_CastleCapacityCurr;				//当前援兵数量
		uint16 m_CastleCapacityMax;					//最大容纳人口数量
		uint32 m_attackTime;						//攻打的时间
		uint32 m_offLineTime;						//离线时间
		uint32 m_loginTime;							//上线时间戳
		uint32 m_offenceSuccess;					//成功进攻次数
		uint32 m_defendSuccess;						//成功防守次数
		uint32 m_prepareAttackTime;					//被匹配到了, 准备时间
		uint32 m_gameid;							//游戏唯一id						
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
		uint32 m_currNum;						//当前数量
		uint32 m_max;						//最大存储数量
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
		uint32 m_produce;						//当前数量
		uint32 m_store;						//最大存储数量
		uint32 m_max;						//最大存储数量
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
		uint32 m_workId;				//服务对象 
		uint32 m_startTime;				//工作开始时间
		uint32 m_endTime;				//结束工作的时间 升级/建造/删除 完成时间	
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
		std::string str_offenseUser;		//进攻方信息
		std::string str_defendUser;			//防守方信息
		std::string str_sendsoldier;		//派兵信息
		std::string str_battleRepor;		//战斗记录		
		uint32 attackTime;					//进攻时间
		uint32 offensePid;					//进攻方pid
		uint32 offenseUin;					//进攻方uin
		uint32 defendPid;					//防守方pid
		uint32 defendUin;					//防守方uin
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
		uint32 m_currValue;					//当前完成的数量（或者等级）
		uint16 m_achvId;					//成就id
		uint8  m_level;						//当前的成就任务（进行中或已完成）
		uint8  m_completeLevel;				//已经领取
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
		uint8 m_gateIndex;		//关卡编号
		uint8 m_star;			//战星
		uint32 m_gold;			//金币
		uint32 m_holywater;		//圣水
		uint32 m_blackwater;	//黑水	

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
		uint16 m_cup;								//奖杯数量
		uint8 m_leagueLevel;						//联赛级别
		uint8 m_level;								//游戏等级
		uint16 m_rankNum;							//排名
		uint32 m_pid;								//pid
		uint32 m_uin;								//uin
		std::string m_name;							//角色昵称
		uint32 m_offenceSuccess;					//成功进攻次数
		uint32 m_defendSuccess;						//成功防守次数
		uint32 m_clanId;							//所属部落
		uint32 m_clanIconNum;						//部落图标编号
		std::string m_clanName;						//所属部落名称		
	};
	enum MsgType
	{
		SYSTEM,		//系统邮件
		PRIZE,		//系统奖励邮件
		USER,		//用户邮件
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
		std::string from;		//消息来源
		std::string msg;		//消息内容
		std::string url;		//url
		uint32 startTime;		//消息开始时间
		uint32 dueTime;			//有效期
		uint32 msgId;			//消息id
		uint32 pid;
		uint32 uin;				
		uint32 gold;			//金币
		uint32 holyWater;		//圣水
		uint32 blackWater;		//黑水
		uint32 gemstone;		//宝石
		uint8 msgType;			//消息类型
		uint32 addTime;			//添加时间
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
		uint8 msgType;			//消息类型
		uint32 startTime;		//消息开始时间
		uint16 showSpan;		//显示间隔时间
		uint32 msgId;			//消息id
		uint32 dueTime;			//有效期
		uint32 pid;				//站点id
		std::string msg;		//消息内容
		uint32 addTime;			//添加时间
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

