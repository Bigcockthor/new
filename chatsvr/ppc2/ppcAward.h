#ifndef INC_PPCAWARD_H
#define INC_PPCAWARD_H

#include "include/icqtypes.h"
#include "room/RoomCommon.h"
#include "User.h"
#include <vector>
#include <map>
#include <string>
#define TL_MAX(a, b) (((a) > (b)) ? (a) : (b)) 
#define TL_MIN(a, b) (((a) < (b)) ? (a) : (b)) 
using namespace  BigRoom;
#define JETTON_AREA_COUNT		8									//8个区域
#define BET_TIME				30									//30秒
#define RUN_TIME				22									//22秒
#define WAIT_TIME				180

#define MAX_REPERTORY			100									//100盘规律
#define MAX_REPERTORY40			4									//默认规律
#define MIN_REPERTORY40			3									//默认规律
#define MAX_REPERTORY30			5									//默认规律
#define MIN_REPERTORY30			4									//默认规律
#define MAX_REPERTORY20			7									//默认规律
#define MIN_REPERTORY20			5									//默认规律
#define MAX_REPERTORY10			12									//默认规律
#define MIN_REPERTORY10			10									//默认规律


#define MAX_SCORE_HISTORY			300									//历史个数
#define MAX_SHOW_HISTORY			8									//一次最多显示的历史记录个数
#define MAX_PPC_JETTONITEM			6

//游戏状态
#define GS_FREE							0								//空闲状态
#define GS_PLAYING						100								//游戏状态
#define	GS_PLACE_JETTON					GS_PLAYING						//下注状态
#define	GS_GAME_END						GS_PLAYING+1					//结束状态


//玩家索引
enum
{
	ID_BIG_TIGER		=	0,									//大奔
	ID_SMALL_TIGER		=	1,									//小奔
	ID_BIG_DOG			=	2,									//大狗索引
	ID_SMALL_DOG		=	3,									//小狗索引
	ID_BIG_HORSE		=	4,									//大马索引
	ID_SMALL_HORSE		=	5,									//小马索引
	ID_BIG_SNAKE		=	6,									//大蛇索引
	ID_SMALL_SNAKE		=	7,									//小蛇索引
	ID_CANCLE			=	9,									//取消
};

//记录信息
struct ppcGameRecord
{
	uint32 	aRound;										//第几局
	uint8	awardId;									//范围在ID_BIG_TIGER到ID_SMALL_SNAKE
};

typedef std::list<ppcGameRecord> PPCHistoryList;

struct CMD_S_CARRUN
{
	uint8 cbTimeLeave;
	uint8 cbGoalAnimal;						//本次停止的位置
};

//struct CMD_S_GameStart
//{
//	uint16							wBankerUser;						//庄家位置
//	uint32							bankerUIN;							//庄家ＩＤ号
//	uint64							iBankerScore;						//庄家银子
//	uint64							iUserMaxScore;						//我的银子
//	uint8							cbTimeLeave;						//剩余时间
//
//	uint64							iAreaLimitScore[JETTON_AREA_COUNT];		//各区域可下分
//};



typedef std::vector<uint64> JettonVector;
class PPCOption
{
public:
	PPCOption();

	void operator = (const PPCOption &opt)
	{
		
		this->m_nKai40MaxCount		= opt.m_nKai40MaxCount;
		this->m_nKai40MinCount		= opt.m_nKai40MinCount;
		this->m_nKai30MaxCount		= opt.m_nKai30MaxCount;
		this->m_nKai30MinCount		= opt.m_nKai30MinCount;
		this->m_nKai20MaxCount		= opt.m_nKai20MaxCount;
		this->m_nKai20MinCount		= opt.m_nKai20MinCount;
		this->m_nKai10MaxCount		= opt.m_nKai10MaxCount;
		this->m_nKai10MinCount		= opt.m_nKai10MinCount;

		this->m_taxRate				= opt.m_taxRate;				
		this->m_profitrate			= opt.m_profitrate;		
		this->m_betTime				= opt.m_betTime;				
		this->m_bFreeTime			= opt.m_bFreeTime;			
		this->m_bankTimes			= opt.m_bankTimes;			
		this->m_bankerCondition		= opt.m_bankerCondition;
		this->m_bankerLeaveMoney	= opt.m_bankerLeaveMoney;
		this->m_areaLimitMoney		= opt.m_areaLimitMoney;		
		this->m_userLimitMoney		= opt.m_userLimitMoney;		
		this->m_broadMsgMoney		= opt.m_broadMsgMoney;	
		this->m_maxHistory			= opt.m_maxHistory;
		this->m_jettonList			= opt.m_jettonList;
		this->m_maxLine				= opt.m_maxLine;
		this->m_retryRate			= opt.m_retryRate;
		this->m_bRunTime			= opt.m_bRunTime;
		//this->m_limitType			= 0;
	}
	void Init();
	int			m_nKai40MaxCount;
	int			m_nKai40MinCount;
	int			m_nKai30MaxCount;
	int			m_nKai30MinCount;
	int			m_nKai20MaxCount;
	int			m_nKai20MinCount;
	int			m_nKai10MaxCount;
	int			m_nKai10MinCount;

	uint32			m_taxRate;				//税收
	uint32			m_profitrate;			//利润率 千分之xx
	uint32			m_betTime;				//押注时间
	uint32			m_bFreeTime;			//空闲时间
	uint32			m_bRunTime;				//开奖动画时间
	uint32			m_bankTimes;			//连庄最大次数
	uint64			m_bankerCondition;		//上庄最低金币
	uint64			m_bankerLeaveMoney;		//庄上低于该金币就下庄
	uint64			m_areaLimitMoney;		//每个区域下注上限
	uint64			m_userLimitMoney;		//用户下注上限
	uint64			m_broadMsgMoney;		//发送广播金币下限
	uint32			m_maxHistory;			//最大历史记录
	JettonVector	m_jettonList;			//筹码列表
	uint16			m_maxJetton;			//最大筹码个数
	int64			m_maxLine;				//最大赢钱线
	uint32			m_retryRate;			//超过赢钱线最大重开几率
	uint16			m_limitType;			//输赢控制类型（0表示按mac，1表示按账号控制）
};




class CJeTton
{
public:
	CJeTton()
	{
		Init();
	}
	void Init(uint8 id = 0)
	{
		m_id = id;
		m_money = 0;
	}
public:
	uint8 m_id; //压注哪个的ID
	int64 m_money;//压注的金额
};

typedef std::vector<CJeTton> JettonArray;

//分数类型
enum enScoreKind
{
	enScoreKind_Win,					//胜
	enScoreKind_Lost,					//输
	enScoreKind_Draw,					//和
	enScoreKind_Flee,					//逃
	enScoreKind_Service,				//服务
	enScoreKind_Present,				//赠送
	enScoreKind_Own_Tax,				///< 室主税收
};

///< 所有玩家写数据库的金额信息
class UserMoneyMessage
{
public:
	UserMoneyMessage()
	{
		Initail();
	}
	UserMoneyMessage& operator = (const UserMoneyMessage& u)
	{
		szUserName	= u.szUserName;
		uin			= u.uin;
		bSuccess	= u.bSuccess;
		lScore		= u.lScore;
		lRevenue	= u.lRevenue;
		ScoreKind	= u.ScoreKind;
		userLastMoney=u.userLastMoney;
		incExp		= u.incExp;
		userMac		= u.userMac;

		return *this;
	}
	void Initail()
	{
		szUserName = "";
		uin = 0;
		bSuccess = false;
		lScore = 0;
		lRevenue = 0;
		ScoreKind = enScoreKind_Win;
		userLastMoney = 0;
		incExp = 0;
		userMac = 0;
	}
	string	szUserName;					///< 玩家名
	uint32 uin;							///< uin
	bool  bSuccess;						///< 写数据库成功返回值
	int64 lScore;							///< 玩家赢得或者扣除的金币数，可为负
	int64 lRevenue;						///< 对应玩家的税收，赢家有值，输家为0
	enScoreKind ScoreKind;				///< 命令字
	uint64 userLastMoney;				///< 玩家上一轮的金币
	uint64 userMac;
	uint8 incExp;
};

class UserWriteMoney2 :public UserMoneyMessage
{
public:
	enum WriteKind
	{
		WRETIE_INVAILD,WRITE_JETTON,WRITE_MONEY,WRITE_BANKER,
	};

	UserWriteMoney2(uint8 jetSize) : maxJetSize(jetSize)
	{
		m_rounds = 0;
		loseOrWin = 0;
		m_nstate = UserWriteMoney2::WRETIE_INVAILD;

		for (uint8 i=0; i<maxJetSize; i++)
		{
			CJeTton item;
			item.Init(i);
			m_JeTtovec.push_back(item);
		}
	}

	~UserWriteMoney2()
	{

	}
	void Initail()
	{
		UserMoneyMessage::Initail();

		for (uint8 i=0; i<maxJetSize; i++)
		{
			m_JeTtovec[i].Init(i);

		}

		m_nstate = UserWriteMoney2::WRETIE_INVAILD;
		m_rounds = 0;
		m_desc = "";
	}
	//计算某项开奖赔付额
	int64 GetItemWin(uint8 idx, uint8 up)
	{
		if(idx < m_JeTtovec.size())
		{
			return abs(m_JeTtovec[idx].m_money * up);
		}
		return 0;
	}
	//开奖, 返回中奖数额, 0表示没有中奖, -1表示押注失败,不能够开奖
	uint64 SetWinItem(uint8 winIndex, uint8 up)
	{
		//if (m_JeTtovec[winIndex].m_money == 0)
		//	return 0;

		if (!bSuccess)
		{
			for (uint8 i=0;i<m_JeTtovec.size(); i++)
			{
				m_JeTtovec[i].m_money = 0;
			}
			lScore = 0;
			loseOrWin = 0;
			bSuccess = true;
			m_desc = "";
			return 0;
		}


		//输赢差额
		loseOrWin = abs(m_JeTtovec[winIndex].m_money) * up + lScore;
		lScore = abs(m_JeTtovec[winIndex].m_money) * up;


		

		m_JeTtovec[winIndex].m_money = lScore;

		for (uint8 i=0; i<m_JeTtovec.size(); i++)
		{
			if (i != winIndex)
			{
				m_JeTtovec[i].m_money = 0;
			}
		}

		bSuccess = (lScore == 0);
		m_nstate = WRITE_MONEY;

		return lScore;
	}
	string GetDesc()
	{
		string desc="";
		char buf[1024] = {0};
		
		for (uint8 i=0; i < m_JeTtovec.size(); i++)
		{
			if (m_JeTtovec[i].m_money)
			{
#ifdef WIN32
				snprintf(buf, sizeof(buf)-1, "\"%d\":%I64d", m_JeTtovec[i].m_id, m_JeTtovec[i].m_money); 
#else
				snprintf(buf, sizeof(buf)-1, "\"%d\":%lld", m_JeTtovec[i].m_id, m_JeTtovec[i].m_money); 
#endif
				if (desc.length() != 0)
					desc = desc + ", " + buf;
				else
					desc = buf;
			}

		}
		desc = "{" + desc + "}";
		return desc;
	}

	uint64 GetJettonCount()
	{
		uint64 count = 0;
		for (uint8 i=0; i<m_JeTtovec.size(); i++)
		{
			count += abs(m_JeTtovec[i].m_money);
		}

		return count;
	}

	bool AddJetton(uint8 idx, uint64 jetton)
	{
		if (abs(lScore) + jetton <= userLastMoney)
		{
			m_JeTtovec[idx].m_money -= jetton;
			lScore -= jetton;
			return true;
		}

		return false;

	}
	const JettonArray &GetJetton()
	{
		return m_JeTtovec;
	}




public:
	int64			loseOrWin;									//本局输赢记录
	uint8			m_nstate;
	uint32			m_rounds;
	const uint8		maxJetSize;
	string			m_desc;										//描述
private:
	JettonArray		m_JeTtovec;			//押注列表
};

typedef std::vector<UserWriteMoney2 *> UserMoneyVec2;
typedef std::map<uint32, UserWriteMoney2 *> UserMoneyMap;
typedef std::vector<User*>	BankerWaitList;
typedef BankerWaitList::iterator BankerWaitListIter;

class JettonManager
{
public:
	JettonManager(uint8 iMax, const int *upValue, Room *pRoom);

	enum
	{
		PPC_NORMAL=1,
		PPC_AODIAN,
	};
	enum
	{
		PPC_40_TIMES = 0,		//40倍
		PPC_30_TIMES,			//30倍
		PPC_20_TIMES,			//20倍
		PPC_10_TIMES,			//10倍


		PPC_TIMES_LIMIT
	};

	enum
	{
		PPC_LEAVE_BANKER = 0,	//下庄
		PPC_TAKE_BANKER,		//上庄
	};

	//设置某项最大最小出现次数
	void	SetItemTimes(uint8 itemIndex, uint8 itemMinTimes, uint8 itemMaxTimes);	


	void	UpdateOption(PPCOption& option);


	//洗牌
	void	RandCardData(uint8 cbCardData[]);

	//开启新一局
	void NewRound(uint32 roundid, User* pUser, int64 sysBankLimit, uint16 bankerTaxRate, uint64 userLimit);


	void AddBanktimes();
	//常规发牌
	void NormalDispatchCard();

	//胜率计算
	int	CalculateWinOdds(bool uptozero);

	//重新开奖用户中奖最少，而且系统盈利的区域
	int CalculateWinoddsEx(uint32 uin);

	int CalculateWinOddsNormal(uint8 currItem);

	uint32 GetMaxWinUin();

	//开奖
	void CheckWinner();
	//加注
	int AddJetton(User *userInfo, uint8 jetItemIndex, uint64 jetton);

	//取单项余额
	uint64 GetItemJettonLastLimit(uint8 idx);
	//取总押注额
	uint64 GetJettonCount();

	uint64 GetItemJettonCount(uint8 itemIndex);

	UserWriteMoney2 *GetUserJettonInfo(uint32 uin);

	UserMoneyMap &GetUserJettonInfo() 
	{
		return m_UserMoney;
	}
	UserMoneyMap &GetBankerMap() 
	{
		return bankers;
	}

	int64 GetBankerWin()
	{
		return currRoundJettonCount - currRoundUserWinCount;
	}

	int64 GetConfusionBankerWin();

	uint64 GetTotalBankMoney() const
	{
		return m_currBanker.m_bankerMoney;
	}
	uint8 bIsSysBanker()
	{
		return m_currBanker.uin ? 0:1;
	}

	uint32	GetBetTime();

	uint32  GetFreeTime();

	uint32	GetRunTime();

	uint32	GetBankerTimes();

	uint32  GetProfitrate();

	uint64  GetAreaLimitMoney();

	uint64  GetUserLimitMoney();

	uint32	GetTaxRate();

	uint16	GetGoalAnimal();

	int64   GetBroadMsgMoney();

	void	ChangeBanker();

	uint64	GetBankerCondition();

	void	RemoveUserJettonInfo(uint32 uin);

	int		GetWinningMultiple(); 
	//申请上庄列表
	int		AddBankerWait(User* pUser);

	int		RemoveBankerWait(uint32 uin);
	//下庄
	void	ResetBankerInfo();

	//是否已经在申请队列
	bool	IsInBakerWaitList(uint32 uin);

	int		GetBankerWaitSize();

	BankerInfo& GetBankerInfo();
	void	SetBankerMoney(uint64 bankerMoney)
	{
		m_currBanker.m_bankerMoney = bankerMoney;
	}

	BankerWaitList& GetBankerWaitList();

	PPCHistoryList& GetPPCHistory();

	uint16		GetMaxHistory();

	void	AddHistroy(uint32 awradID, uint8 awardItem);

	void	CheckAddConfound();

public:
	const static uint8	m_cbCardDataArray[MAX_REPERTORY];	//100盘的规律数据
	const static int	m_iOddsArray[JETTON_AREA_COUNT];	//各区域赔率



	uint8 maxTimes[PPC_TIMES_LIMIT];			//某项最大开奖次数
	uint8 minTimes[PPC_TIMES_LIMIT];			//某项最小开奖次数

private:
	
	void SetBankerInfo(User* pUser);

private:
	UserMoneyMap		bankers;										//用户押注信息,以用户ID为Key
	UserMoneyMap		m_UserMoney;									//用户押注信息,以用户ID为Key
	const uint8			maxItem;										//最大押注项
	const int			*upInfo;										//各押注项倍数
	uint16				m_nCountSel	;
	uint64				currRoundJettonCount;							//本局押注总额
	uint64				currRoundUserWinCount;
	
	uint32				currRound;
	uint16				taxRate;										//庄家税收
	uint64				currUserLimit;
	BankerWaitList		m_ApplyUserArray;								//申请上庄玩家列表
	BankerInfo			m_currBanker;									//当前坐庄
	
	uint16				m_iGoalAnimal;									//本次游戏会开出的动物
	uint8				m_cbPlayCardDataArray[MAX_REPERTORY];
	uint8				m_lastAwardid;									//上局开奖项目
	uint32				m_repeatTimes;									//排除概率
	int					m_nHasWinTimes;									//某庄家做庄以来，共赢了多少次
	Room*				m_pRoom;
	PPCHistoryList		m_awardHistory;									//游戏记录
	int					m_nRecordFirst;									//开始记录
	PPCOption			m_ppcOption;
	uint64				m_iGameTimes;									//当前是游戏启动以来的第几局
	uint32				m_curMaxRepeatTime;								//当前最大连开次数
};


#endif
