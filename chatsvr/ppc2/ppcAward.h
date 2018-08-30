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
#define JETTON_AREA_COUNT		8									//8������
#define BET_TIME				30									//30��
#define RUN_TIME				22									//22��
#define WAIT_TIME				180

#define MAX_REPERTORY			100									//100�̹���
#define MAX_REPERTORY40			4									//Ĭ�Ϲ���
#define MIN_REPERTORY40			3									//Ĭ�Ϲ���
#define MAX_REPERTORY30			5									//Ĭ�Ϲ���
#define MIN_REPERTORY30			4									//Ĭ�Ϲ���
#define MAX_REPERTORY20			7									//Ĭ�Ϲ���
#define MIN_REPERTORY20			5									//Ĭ�Ϲ���
#define MAX_REPERTORY10			12									//Ĭ�Ϲ���
#define MIN_REPERTORY10			10									//Ĭ�Ϲ���


#define MAX_SCORE_HISTORY			300									//��ʷ����
#define MAX_SHOW_HISTORY			8									//һ�������ʾ����ʷ��¼����
#define MAX_PPC_JETTONITEM			6

//��Ϸ״̬
#define GS_FREE							0								//����״̬
#define GS_PLAYING						100								//��Ϸ״̬
#define	GS_PLACE_JETTON					GS_PLAYING						//��ע״̬
#define	GS_GAME_END						GS_PLAYING+1					//����״̬


//�������
enum
{
	ID_BIG_TIGER		=	0,									//��
	ID_SMALL_TIGER		=	1,									//С��
	ID_BIG_DOG			=	2,									//������
	ID_SMALL_DOG		=	3,									//С������
	ID_BIG_HORSE		=	4,									//��������
	ID_SMALL_HORSE		=	5,									//С������
	ID_BIG_SNAKE		=	6,									//��������
	ID_SMALL_SNAKE		=	7,									//С������
	ID_CANCLE			=	9,									//ȡ��
};

//��¼��Ϣ
struct ppcGameRecord
{
	uint32 	aRound;										//�ڼ���
	uint8	awardId;									//��Χ��ID_BIG_TIGER��ID_SMALL_SNAKE
};

typedef std::list<ppcGameRecord> PPCHistoryList;

struct CMD_S_CARRUN
{
	uint8 cbTimeLeave;
	uint8 cbGoalAnimal;						//����ֹͣ��λ��
};

//struct CMD_S_GameStart
//{
//	uint16							wBankerUser;						//ׯ��λ��
//	uint32							bankerUIN;							//ׯ�ңɣĺ�
//	uint64							iBankerScore;						//ׯ������
//	uint64							iUserMaxScore;						//�ҵ�����
//	uint8							cbTimeLeave;						//ʣ��ʱ��
//
//	uint64							iAreaLimitScore[JETTON_AREA_COUNT];		//��������·�
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

	uint32			m_taxRate;				//˰��
	uint32			m_profitrate;			//������ ǧ��֮xx
	uint32			m_betTime;				//Ѻעʱ��
	uint32			m_bFreeTime;			//����ʱ��
	uint32			m_bRunTime;				//��������ʱ��
	uint32			m_bankTimes;			//��ׯ������
	uint64			m_bankerCondition;		//��ׯ��ͽ��
	uint64			m_bankerLeaveMoney;		//ׯ�ϵ��ڸý�Ҿ���ׯ
	uint64			m_areaLimitMoney;		//ÿ��������ע����
	uint64			m_userLimitMoney;		//�û���ע����
	uint64			m_broadMsgMoney;		//���͹㲥�������
	uint32			m_maxHistory;			//�����ʷ��¼
	JettonVector	m_jettonList;			//�����б�
	uint16			m_maxJetton;			//���������
	int64			m_maxLine;				//���ӮǮ��
	uint32			m_retryRate;			//����ӮǮ������ؿ�����
	uint16			m_limitType;			//��Ӯ�������ͣ�0��ʾ��mac��1��ʾ���˺ſ��ƣ�
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
	uint8 m_id; //ѹע�ĸ���ID
	int64 m_money;//ѹע�Ľ��
};

typedef std::vector<CJeTton> JettonArray;

//��������
enum enScoreKind
{
	enScoreKind_Win,					//ʤ
	enScoreKind_Lost,					//��
	enScoreKind_Draw,					//��
	enScoreKind_Flee,					//��
	enScoreKind_Service,				//����
	enScoreKind_Present,				//����
	enScoreKind_Own_Tax,				///< ����˰��
};

///< �������д���ݿ�Ľ����Ϣ
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
	string	szUserName;					///< �����
	uint32 uin;							///< uin
	bool  bSuccess;						///< д���ݿ�ɹ�����ֵ
	int64 lScore;							///< ���Ӯ�û��߿۳��Ľ��������Ϊ��
	int64 lRevenue;						///< ��Ӧ��ҵ�˰�գ�Ӯ����ֵ�����Ϊ0
	enScoreKind ScoreKind;				///< ������
	uint64 userLastMoney;				///< �����һ�ֵĽ��
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
	//����ĳ����⸶��
	int64 GetItemWin(uint8 idx, uint8 up)
	{
		if(idx < m_JeTtovec.size())
		{
			return abs(m_JeTtovec[idx].m_money * up);
		}
		return 0;
	}
	//����, �����н�����, 0��ʾû���н�, -1��ʾѺעʧ��,���ܹ�����
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


		//��Ӯ���
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
	int64			loseOrWin;									//������Ӯ��¼
	uint8			m_nstate;
	uint32			m_rounds;
	const uint8		maxJetSize;
	string			m_desc;										//����
private:
	JettonArray		m_JeTtovec;			//Ѻע�б�
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
		PPC_40_TIMES = 0,		//40��
		PPC_30_TIMES,			//30��
		PPC_20_TIMES,			//20��
		PPC_10_TIMES,			//10��


		PPC_TIMES_LIMIT
	};

	enum
	{
		PPC_LEAVE_BANKER = 0,	//��ׯ
		PPC_TAKE_BANKER,		//��ׯ
	};

	//����ĳ�������С���ִ���
	void	SetItemTimes(uint8 itemIndex, uint8 itemMinTimes, uint8 itemMaxTimes);	


	void	UpdateOption(PPCOption& option);


	//ϴ��
	void	RandCardData(uint8 cbCardData[]);

	//������һ��
	void NewRound(uint32 roundid, User* pUser, int64 sysBankLimit, uint16 bankerTaxRate, uint64 userLimit);


	void AddBanktimes();
	//���淢��
	void NormalDispatchCard();

	//ʤ�ʼ���
	int	CalculateWinOdds(bool uptozero);

	//���¿����û��н����٣�����ϵͳӯ��������
	int CalculateWinoddsEx(uint32 uin);

	int CalculateWinOddsNormal(uint8 currItem);

	uint32 GetMaxWinUin();

	//����
	void CheckWinner();
	//��ע
	int AddJetton(User *userInfo, uint8 jetItemIndex, uint64 jetton);

	//ȡ�������
	uint64 GetItemJettonLastLimit(uint8 idx);
	//ȡ��Ѻע��
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
	//������ׯ�б�
	int		AddBankerWait(User* pUser);

	int		RemoveBankerWait(uint32 uin);
	//��ׯ
	void	ResetBankerInfo();

	//�Ƿ��Ѿ����������
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
	const static uint8	m_cbCardDataArray[MAX_REPERTORY];	//100�̵Ĺ�������
	const static int	m_iOddsArray[JETTON_AREA_COUNT];	//����������



	uint8 maxTimes[PPC_TIMES_LIMIT];			//ĳ����󿪽�����
	uint8 minTimes[PPC_TIMES_LIMIT];			//ĳ����С��������

private:
	
	void SetBankerInfo(User* pUser);

private:
	UserMoneyMap		bankers;										//�û�Ѻע��Ϣ,���û�IDΪKey
	UserMoneyMap		m_UserMoney;									//�û�Ѻע��Ϣ,���û�IDΪKey
	const uint8			maxItem;										//���Ѻע��
	const int			*upInfo;										//��Ѻע���
	uint16				m_nCountSel	;
	uint64				currRoundJettonCount;							//����Ѻע�ܶ�
	uint64				currRoundUserWinCount;
	
	uint32				currRound;
	uint16				taxRate;										//ׯ��˰��
	uint64				currUserLimit;
	BankerWaitList		m_ApplyUserArray;								//������ׯ����б�
	BankerInfo			m_currBanker;									//��ǰ��ׯ
	
	uint16				m_iGoalAnimal;									//������Ϸ�Ὺ���Ķ���
	uint8				m_cbPlayCardDataArray[MAX_REPERTORY];
	uint8				m_lastAwardid;									//�Ͼֿ�����Ŀ
	uint32				m_repeatTimes;									//�ų�����
	int					m_nHasWinTimes;									//ĳׯ����ׯ��������Ӯ�˶��ٴ�
	Room*				m_pRoom;
	PPCHistoryList		m_awardHistory;									//��Ϸ��¼
	int					m_nRecordFirst;									//��ʼ��¼
	PPCOption			m_ppcOption;
	uint64				m_iGameTimes;									//��ǰ����Ϸ���������ĵڼ���
	uint32				m_curMaxRepeatTime;								//��ǰ�����������
};


#endif
