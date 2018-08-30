 #if !defined BIG_ROOMMANAGER_H_
#define BIG_ROOMMANAGER_H_

#include "Room.h"
#include "option.h"
#include "User.h"
#include "ace/Synch_T.h"
#include "../roomcomm/RoomPacketRecv.h"
#include "include/coretime.h"
#include <list>
#include "include/BlockManager.h"
#include "beanstalkdef.h"
#include "beanstalkMsg.h"
#include "dbAccess.h"
#include "../tools/performance.h"
#include "../tools/kafkaProducter.h"
#include "kafkalog.h"

using namespace WingUtil;

typedef std::vector<string> FilterList;

enum {
	DBINIT_SUPERMGR = 0x0001,
	DBINIT_ALL		= 0x0002 - 1,
};




typedef ACE_Hash_Map_Manager<ACE_UINT32,ACE_TString, ACE_SYNCH_MUTEX> CacheUserMap;	






//用户登陆消息类
//#define LOGINMAP_MAXTOTAL 10
#define MAX_LOGIN_TIMES	  15		//次数
#define MAX_LOGIN_TIME	  60		//时间
#define LOCK_TIME		  20		//时间




#define TUBENAME_FORMAT			"BigRoom%u_%u"

namespace BigRoom
{


	typedef ACE_Hash_Map_Manager<ACE_UINT32, Room*,ACE_SYNCH_NULL_MUTEX> RoomMap;
	class RoomManager: public Room, public RecvPacketHandle, public TcpRecvPacketHandle, public	ACE_Task<ACE_MT_SYNCH>
	{
	public:
		RoomManager();
		virtual			~RoomManager(void);

		static RoomManager *gRoot;

		AclCtrl		aclCtrlsChat;			//游戏聊天权限
		AclCtrl		aclCtrlsKickOut;		//踢人权限 add 17.04.7
		AclCtrl		aclCtrlsGameLimit;		//添加限制权限(防挂)
		Mutex		giftCountMutex;

		BlockManager blockMgr;


		ParterInfo partner;
		SvridList  svridList;
		FilterList filters;

		Mutex partnerLock;
		bool GetPartnerAutoMic();


		bool		inited;
		time_t		lastBusyTime;


		virtual bool OnData(UdpInPacket *in);
		virtual bool OnData(UdpInPacket *in, int nIndex);
		int SendDataByChannel(uint8 nChannel, OutPacket *out, uint32 ip, uint16 port, uint32 proxyIP, uint16 proxyPort);
		virtual void OnHandleDBResult(dataport::CDBClientResult * result);//dbclient

		virtual void OnBeanstalkMsg(BCMessageBase* bcMsg);

		virtual int		open (void * = 0);
		bool			init();
		virtual int		svc (void);
		virtual int		close(u_long);

		virtual int		handle_timeout(const ACE_Time_Value &tv,const void *arg);

		virtual int		RemoveUser(User* pUser);
		virtual void	RemoveAllUsers();
		virtual int		AddUser(User *pUser);
		bool			HasUser(User *pUser);
		bool CheckWordFilter(char *txt);

		int		Dispose();
		User*	CreateUser(UdpInPacket *in);

		Room *	GetFirstRoom();
		Room *	GetNextRoom();
		Room *	GetRoomByID(uint32 roomid);
		int		GetTotalUserNumber();
		int		GetTotalRoomNumber();

		int64	GetSysBalanceInfo();
		int64	GetSysTodayBetCount();
		void	OnLogin(User* pUser,ACE_Message_Block* mb, UdpInPacket *in, bool &releaseByRoom);

		inline	std::string BuildBeanstalkMsg(uint32 nMsgType, std::string& strData);
		inline  std::string BuildBeanstalkTubeName(uint32 nPartnerid, uint32 nSrvid);
		void BeanstalkNotify(uint32 msgType, std::string& strMsg, UinMap& kind);
		void SendGlobleMsg(UdpInPacket *in, bool sendOther);
		void SendGlobleGreatGiftMsg(OutPacket &p, bool writeToDB);
		bool VerifyLoginPacket(ICQ_STR& strCheckPass, ICQ_STR& strPass, uint32 sid);
	protected:
		int		m_timerID;
		
		void	OnLogout(User* pUser,ACE_Message_Block* mb, int& releasebyroom);
		

		virtual int OnHandleTimeout();
		
	private:
		int64	inCount_company;											//当天进帐总额
		int64	outCount_company;											//当天出总总额
	public:
		
		UinMap richerMap;
		Mutex richerLock;

		uint8	GetRichOrder(uint32 uin);
		void DBhLoadPartnerInfo();
		void DBhLoadAwardItemsInfo();
		
		void DBhLoadAcl(uint8 act);

		void DBhLoadRicherList();

		void DBHLockMoney(uint32 roomid, uint32 uin, uint8 nState);
		//获取玩家金币钻石数
		void DBHGetUserCurMoney(uint32 roomid, uint32 uin);
		

		void DBHModifyPass(uint32 roomid, const char* pass);
		
	
		void DBHModifyCurrUser(uint32 roomid, uint16 curruser, uint16 currconfuser, uint16 virturlUser = 0);

		void DBHAddBlackUin(uint32 roomid, uint32 opr, uint32 uin, uint32 ip, string mac, string nickName);
		void DBHForbidChat(uint32 roomid, uint32 opr, uint32 uin, string nickName);
		void DBHAddGameLimit(uint32 roomid, uint32 opr, uint32 uin);
		void DBHSetOpenStatus(uint32 roomid, uint8 openstatus);
		
	
		void DBHBuyGlobleMsgServcie(Room* pRoom, uint32 uin, uint8 userlevel, UdpInPacket *in);
		void DBHSaveBankerResult(uint32 roomid, uint32 awardRound, uint32 awardid, UserMoneyMap& bankerMoney);
		void DBPPCHBet(uint32 roomid, uint32 awardRound, UserMoneyMap& writeMoney, uint8 bSysBanker);
		void DBHLoadBalanceInfo(uint32 roomid);
		void DBHPPCAward(uint32 roomid, uint32 awardRound, UserMoneyMap& userMoney, uint8 bSysBanker);
		//void DbhLoadZZPool(Room* pRoom);
		void ZZSaveAward(uint32 roomid, uint32 awardRound, uint8 awardID);
		//void DBhLoadZZAwaredHistory(Room* pRoom);
		void DBHLoadPPCHistory(uint32 roomid);

		void DBHGetPPCExprience(uint32 roomid, uint32 uin);
		void DBHSavePPCExprience(uint32 roomid, uint32 uin);
		void DBHLoadPPCConfig();
		//@byUin:false表根据mac查，true表示根据账号查
		void DBHGetUserBlance(uint32 roomid, uint32 uin, uint64 mac,bool byUin = false);
		void DBHCheckPpcBlock(uint32 roomid, uint32 pid, uint64 mac, uint32 uin, uint32 ip, uint16 port);
		void DBHGetDisconnectTimes(uint32 roomid, uint32 pid, uint64 mac, uint32 uin, uint32 ip, uint16 port);
		void DBHIncrDisconnectTimes(uint32 roomid, uint32 pid, uint64 mac, uint32 uin);

		//dbclient
		void OnZZSaveAward(dataport::CDBClientResult* tempResult);
		//进一步到房间处理
		void OnHandleByRoomInstance(dataport::CDBClientResult * tmpResult);

		

		void OnCommonHandlerFromDB(dataport::CDBClientResult * tmpResult);
		void OnGetServerInfo(dataport::CDGetServerInfo * tmpResult);
		void OnGetRoomInfoFromDB(dataport::CDBGetRoomInfo * tmpResult);
		void OnGetSuperManagerListFromDB(dataport::CDGetSuperManager * tmpResult);
		void OnGetRichListFromDB(dataport::CDGetRich * tmpResult);
		void DBHSaveBroadcast(uint32 roomid, uint32 uin, const char *broadcast, uint32 done);
		void OnDoMultiTask(dataport::CDBMutiResult* tmpresult);
		//以下是数据库访问结果处理接口
		int OnDoRoomLoginNew(dataport::CDBRoomLoginResult* tmpresult, dataport::MoneyResult *blanceResult);//独立登录接口
		int  OnLogonFromDBNew(dataport::CDBRoomLoginResult * tmpResult, dataport::MoneyResult *blanceResult); //登录房间操作
		int  OnCheckRoomBlockNew(dataport::CDBClientResult * tmpResult);//房间被封锁
		void OnGetAuthorityListFromDB(dataport::CDLoadAcl * tmpResult); //获取权限列表
		
		////////////////////////////////////////////////////////多任务登录
		//房间被封锁
		int		OnCheckRoomBlock(dataport::CDBClientResult * tmpResult);
		//登录
		int		OnLogonFromDB(dataport::CDBLoginResult * tmpResult);


		//获取盈亏信息
		void	OnGetBalanceInfo(dataport::GetBalanceInfo * tmpResult);

		void	OnGetPPCConfig(dataport::PPCConfigResult* tmpResult);


		void	OnGetPartnerInfo(dataport::GetPartnerInfo *tmpResult);//获取服务商信息


	

		void OnUpdateAllSupperMgr();
		void GetServerInfo();

		void OnUpdateRoomUserNum(uint32 roomid,uint32 num,uint32 cfnum);
		void OnUpdateRoomStatus(uint32 roomid,uint16 status);
		void InitAcl(ChatAclCtrl& userAcl, UserLevel& levelInfo, uint8 userType,uint16 rank, bool bOwner, uint8 richOrder);

	public:
		void UpdateRoomInfo(uint32 fid);
		void DBHGetRoomInfo(uint32 fid, DbGettingRoomPara::HANDLE_TYPE type);
		static void ParseRoominfo(TcpLargeInPacket &in, RoomInfo *mInfo);
	private:

	
	public:

		ACE_SOCK_Dgram* GetCmdSocket();
		int Initialize();
		int RemoveRoom(Room *pRoom);
		int RemoveRoom(uint32 roomid);
		int AddRoom(Room* pRoom);


		bool IsSuperMgr(uint32 uin);

		virtual void OnReceiveCmdPacket(ACE_Message_Block* mb, UdpInPacket* in, bool& releasebyroom);




		uint32 m_logintimelimit;
		RoomMap				m_RoomMap;
		

		BeanstalkMsg*				m_pBeanstalkMsg;	//beanstalk模块，替换所有的msgswitch

		//	StaticRoomInfoMap	m_staticRoomInfoMap;

		//	礼物表

		UinMap				superMgr;


		ACE_UINT32 m_nLoginLimit;				//每秒登陆次数限制
	public:
		static Mutex_Allocator* _buf_allocator; 

		void		  initFreePort();
		uint16		  allocFreePort();
		void		  releasePort(uint16 port);

		ACE_Thread_Mutex freeport_mutex;				//端口锁
		std::list<uint16> m_freePort;

		//新加kafka
		CTLKafaProducter m_kafkaProducer;
		CTLKafkalog		 m_kafkalog;
	};


}

#endif
