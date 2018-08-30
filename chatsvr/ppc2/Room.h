#if !defined  BIGROOM__ROOM_H_
#define  BIGROOM__ROOM_H_

#include "ace/OS.h"
#include "ace/Reactor.h"
#include "ace/Task.h"
#include "ace/SOCK_Dgram.h"
#include "ace/INET_Addr.h"
#include "ace/Vector_T.h"

#include "User.h"
#include "UserManager.h"
#include "include/icqtypes.h"
#include <string>
#include <list>
#include "include/list.h"
#include "room/RoomCommon.h"
#include "ppcAward.h"

#include "dbAccess.h"

typedef std::vector<uint32> UinList;
typedef std::map<uint32,User*>	UserGameMap;
typedef UserGameMap::iterator UserGameMapIter;

#define MAX_MEMBERS_PER_PACKET			15		//ÿ��������Ա�������Ϊ30,�ڰ���������,���׳���1024�Ĵ�С���ƣ���ɿͻ��˽��ܵ�
#define MAX_VISITORS					800		//����Ա��
#define	ROOM_TIMER_INTERVAL				1

#define ROOM_HANDLETIMEOUT_INTERVAL		100						//���䳬ʱ��麯�����ü����100����
#define ROOM_RESEND_KEY_QUEUE			3000
#define ROOM_CHECK_KEEPALIVE_INTERVAL	12						//�����û���ʱ���ʱ������12����һ�Σ�һ����5��
#define ROOM_TIMER_MAX_LIMIT			18000						
#define ROOM_TIMER_MEDIA_CHECKROOM		30
#define ROOM_UPDATE_USER_NUM_INTERVAL	60						//���·�������ʱ����

#define MAX_NICK_LEN					36
#define MAX_ROOM_DESCRIPT_LEN			120						//˵��������
#define MAX_CHATTEXT_LEN  				450
#define MAX_ROOM_BROADCAST_LEN	  		256
#define MAX_FLCFPASS_LEN				32
#define MAX_MIC_USER_NUM				4

#define MAX_SEND_KEY_ATTEMPTS			10						//����ʹ���
#define PACKET_SEND_KEY_TIMEOUT			300						//���ķ��ͳ�ʱʱ��3000ms,�㹻������

#define MAX_FORBID_CHAT_TIME			1800					//����ʱ�䣨�룩

extern uint32 last_logon_failing_IP;
extern time_t last_logon_failing_time;

extern ACE_Time_Value g_puttimeout;


enum {
	TEXT_NONE = 0x00,	//ȫ����ֹ
	TEXT_PTSL = 0x01,	//��ͨ(�ǻ�Ա)���Ļ�
	TEXT_PTGL = 0x02,	//��ͨ(�ǻ�Ա)����
	TEXT_HYSL = 0x04,	//��Ա���Ļ�
	TEXT_HYGL = 0x08,	//��Ա����
	TEXT_ALL  = 0x0F,	//ȫ������
};



enum
{
	MAX_ROOM_NAME_LEN	= 50,
	MAX_ROOM_PWD_LEN	= 50,
	MAX_ROOMDESCRIPT_LEN= 256,
	MAX_ROOM_DESC_LEN	= 250,

	DEFAULT_ROOM_SIZE	= 100,
	DEFAULT_MIC_SIZE	= 2,
	DEFAULT_MIC_QUEUE	= 20,

	ROOT_ROOM_ID = 0,
};






# define IMCHAT_SEND_COMMAND_PARAM(ITERATOR,ENTRY,CLASS,FUNC,PARAM) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	pointer->FUNC(PARAM); \
} \
	} \
	while (0)

# define IMCHAT_SEND_COMMAND_PARAM1(ITERATOR,ENTRY,CLASS,FUNC,PARAM1) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	pointer->FUNC(PARAM1); \
} \
	} \
	while (0)

# define IMCHAT_SEND_COMMAND_PARAM2(ITERATOR,ENTRY,CLASS,FUNC,PARAM1, PARAM2) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	pointer->FUNC(PARAM1, PARAM2); \
} \
	} \
	while (0)



# define IMCHAT_SEND_COMMAND_PARAM3(ITERATOR,ENTRY,CLASS,FUNC,PARAM1,PARAM2,PARAM3) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	pointer->FUNC(PARAM1,PARAM2,PARAM3); \
} \
	} \
	while (0)

# define IMCHAT_SEND_COMMAND_PARAM4(ITERATOR,ENTRY,CLASS,FUNC,PARAM1,PARAM2,PARAM3,PARAM4) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	if(pointer) \
	pointer->FUNC(PARAM1,PARAM2,PARAM3,PARAM4); \
} \
	} \
	while (0)


# define IMCHAT_SEND_COMMAND_PARAM5(ITERATOR,ENTRY,CLASS,FUNC,PARAM1,PARAM2,PARAM3,PARAM4, PATAM5) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	if(pointer) \
	pointer->FUNC(PARAM1,PARAM2,PARAM3,PARAM4, PATAM5); \
	} \
	} \
	while (0)

# define IMCHAT_SEND_COMMAND_PARAM6(ITERATOR,ENTRY,CLASS,FUNC,PARAM1,PARAM2,PARAM3,PARAM4, PATAM5, PATAM6) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	if(pointer) \
	pointer->FUNC(PARAM1,PARAM2,PARAM3,PARAM4, PATAM5, PATAM6); \
	} \
	} \
	while (0)

# define IMCHAT_SEND_COMMAND_PARAM7(ITERATOR,ENTRY,CLASS,FUNC,PARAM1,PARAM2,PARAM3,PARAM4, PATAM5, PATAM6, PATAM7) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	if(pointer) \
	pointer->FUNC(PARAM1,PARAM2,PARAM3,PARAM4, PATAM5, PATAM6, PATAM7); \
	} \
	} \
	while (0)

# define IMCHAT_SEND_TEXT(ITERATOR,ENTRY,CLASS,FUNC, UIN1,UIN2,PARAM1,PARAM2,PARAM3,PARAM4) \
	do { \
	CLASS *pointer;\
	while (ITERATOR.next(ENTRY) != 0) \
{ \
	pointer = (*ENTRY).int_id_;\
	ITERATOR.advance(); \
	if(pointer && pointer->uin != UIN1) \
	pointer->FUNC(UIN1,UIN2, PARAM1, PARAM2, PARAM3, PARAM4); \
} \
	} \
	while (0)




enum
{
	ROOM_STATUS_CLOSED = 0x00,
	ROOM_STATUS_OPENED = 0x01,
	ROOM_STATUS_FREEZED= 0x02,
	ROOM_STATUS_DELETED= 0x03,	//delete flag
};

enum
{
	ROOM_STATUS_WORK,
	ROOM_STATUS_DESTROY,
};
enum 
{
	MEDIAFLAG_OEPNALL  = 0x00,	//������
	MEDIAFLAG_OPENPUB  = 0x01,	//����˽�ģ�������
	MEDIAFLAG_OPENPRI  = 0x02,  //���ι��ģ���˽��
	MEDIAFLAG_CLOSEALL = 0x03,	//ȫ����
};


enum 
{
	OPENSTATUS_CLOSE,
	OPENSTATUS_OPEN,
	OPENSTATUS_DISABLE,
};

class ChatRoomMsg
{
public:
	static string STR_MSG_ACL_NOT_ENOUGH;
	static string STR_MSG_ACL_IF_HIGH_VIP;
	static string STR_MSG_NOT_ONLINE;
	static string STR_MSG_HAS_GOT_MIC;
	static string STR_MSG_NO_FREE_MIC;
	static string STR_MSG_DRAG_MIC_SUCCESS;
	static string STR_MSG_NO_MONEY;
	static string STR_MSG_PRESENT_GIFT_FAIL;
	static string STR_MSG_PRESENT_GIFT_SUCCESS;
	static string STR_MSG_SEND_G_MSG_ERROR;
	static string STR_MSG_SEND_G_MSG_SUCCESS;
	static string STR_MSG_PRIZE_MSG;
	static string STR_MSG_SYSTEM_MSG;
	static string STR_MSG_PUBLIC_TEXT_DENY;
	static string STR_MSG_VIP_PUBLIC_TEXT_DENY;
	static string STR_MSG_PRIVATE_TEXT_DENY;
	static string STR_MSG_VIP_PRIVATE_TEXT_DENY;
	static string STR_MSG_FORBID_CHAT;
	static string STR_MSG_PRESENT_ONMIC;


	static string STR_MSG_CLIENT_VER_LOW;
	static string STR_MSG_AWARD_NOT_BETTING;
	static string STR_MSG_BET_FAIL;
	static string STR_MSG_BET_SUCCESS;
	static string STR_MSG_AWARD_FAIL;
	static string STR_MSG_ZZ_AWARD_MSG;
	static string STR_MSG_ZZ_AWARD_MSG2;
	static string STR_MSG_ZZ_AWARD_MSG3;
	static string STR_MSG_ZZ_BET_ALREADY;
	static string STR_MSG_BET_FAIL_IN_GAME_FAIL;
	static string STR_MSG_FILTER;
	static string STR_MSG_GAME_START;
	static string STR_MSG_BAKER_NOMONEY;
	static string STR_MSG_BANKER_RETRY;
	static string STR_MSG_CHANGE_BAKER_NOMONEY;
	static string STR_MSG_CHANGE_BAKER_NOTIMES;
	static string STR_MSG_TAKE_BAKER;
	static string STR_MSG_CHANGE_BANKER_ERROR;
	static string STR_MSG_NOT_CHAT;
	static string STR_MSG_PROMOTED;
	static string STR_MSG_BROADCAST_LINK;

	static string STR_MSG_BETFAILED_CODE;
	static string STR_MSG_BETFAILED_LIMIT;
	static string STR_MSG_BETFAILED_INFO;

	

	
};





typedef std::vector<int64> BetCountList;



namespace BigRoom
{
	class RoomManager;

	typedef std::map<uint32, UserBetTemp *> UserBetMap;

	//macѺע��¼
	typedef std::map<uint64,uint32>			MacBetMap;
	typedef MacBetMap::iterator				MacBetMapIter;

	class RobotBetInfo
	{
	public:
		uint8		areaIndex;		//��ע����
		uint64		betMoney;		//��ע���
		uint32		betUin;
		uint32		around;			//����
		uint64		maxPlaceArea;

		RobotBetInfo()
		{
			areaIndex = 0;
			betMoney = 0;
			betUin = 0;
			around = 0;
			maxPlaceArea = 0;
		}
	};


	class GameCount
	{
	public:
		void CountIt(int64 currRoundInfo, uint16 roundSize)
		{
			for (uint32 i=0; i<roundInfo.size(); i++)
			{
				roundInfo[i] += currRoundInfo;
			}

			roundInfo.insert(roundInfo.begin(), currRoundInfo);
			
			if (roundInfo.size() > roundSize)
				roundInfo.erase(roundInfo.begin() + roundInfo.size() - 1);
		}

		bool Test(int64 remaining, uint16 roundPos)
		{
			if (roundInfo.size() == 0)
				return remaining > 0;

			if (roundInfo.size() < roundPos)
				roundPos = roundInfo.size();

			return roundInfo[roundPos-1] + remaining > 0;
		}
		uint32 GetCountSize()
		{
			return roundInfo.size();
		}
	private:
		std::vector<int64> roundInfo;
	};




	class Room	
	{
	public:
		Room(uint32 mRoomID, RoomManager *roomMgr);
		virtual ~Room(void); 

		uint32 regionMaster;											//����
		uint32 regionAssistant[MAX_ASSIST_USER_NUM];					//������
	private:
		
	protected:
		uint32 m_timertime;

	public:
		bool prized;
		
		virtual int open (void * = 0);


		/*
		*����������
		*/
		User *GetPushOutTarget(void);

		//
		void PushUser(User *user);

		void AddRoomManager(uint32 dstuin, string dstNick);

		void DelRoomManager(uint32 uin);

		bool FindRoomManager(uint32 uin)
		{
			return (roomMgr.find(uin) != roomMgr.end());
		}

		int AddUser(User* user);
		int DeleteUserFromMap(User* pUser);

		User* GetUser(uint32 uin);
		void RemoveAllUsers();
		uint16 GetCurrentUserNum();

		uint8 IsSuperMgr(uint32 uin);

		int OnLogon(DbLogonPara * para);
	public:
		const uint32	roomid;
		uint32			ownuin;										//����ID
		uint8			roomTax;									//�Ƿ�����˰�շֳ�
		bool			bPause;										//
        
        uint16          lastUpdateUserNum;                          //���һ�θ��������û���
		uint32			m_lastlogintime;							//���һ�ε�¼ʱ��
		uint8			auth;										//���ŷ�ʽ
		char			m_pass[MAX_FLCFPASS_LEN+1];					//��������

		uint8			m_open_state;								//0:���俪 1:�����
		
		volatile bool   exitFlag;

		/*
		 *	For ppc
		 */
		uint32 curStatusStart;										//��ʼͶעʱ��
		uint8 awardStatus;											//��ǰ��Ϸ״̬
		uint32 awardRound;											//�ڶ�������Ϸ
		uint64 currRoundAward[MAX_AWARD_ITEM_NUM];					//�н�
		uint64 currRoundBet[MAX_AWARD_ITEM_NUM];					//�н�


		JettonManager ppcBetMgr;									
		
			
		ZZSetting zzsetting;

		int tm_yday;
		/*
		 *	For תת End
		 */

		string			m_roomLink;
		char			roomName[MAX_ROOM_NAME_LEN+1];
		char			descript[MAX_ROOM_DESC_LEN+1];
		char			broadcast[MAX_ROOM_BROADCAST_LEN+1];
		uint8			ispublic;

		uint16			roomsize;
		uint16			maxMic;
		uint16			maxMicQueue;	

		uint8			m_openStatus;								//0:���俪 1:�����
		uint8			textChatStatus;								//��������֧��(����Ա������): 0x01:��ͨ��˽��,0x02:��ͨ�˹���,0x04:��Ա˽��,0x08:��Ա����


		
		UserManager		m_UserManager;								//�����û�����	
		UserBetMap		bets;										//��ע�û��б�
		UserBetMap		beteds;										//��ע�û��б�
		UserBetMap		awards;										//��ע�û��б�
		UserGameMap		m_userBetList;								//��ע�ɹ����û�
		UserGameMap		m_userAwardList;							//�н����û�
		UinMap			roomMgr;									//�������Ա
		OutPacket		m_lastAllBet;								//��һ�ָ�����Ѻע�ܶ�
		uint8			autoMgrForRicher;							//�����Զ�Ϊ����ԱȨ�ޡ�
		UinList			logoutMap;									//�û���ʱ��ʱ�ͷ�

		ListHead        usersTop;									//�û��б��ѡ��
		ListHead		globalSendQueue;							//�����û�ȫ�ַ����б�

		MacBetMap		m_macBetMap;								//һ��macѺעmap
		uint64			m_robotBetArray[JETTON_AREA_COUNT];			//������ע�ܽ��
		uint64			m_robotCurBetArray[JETTON_AREA_COUNT];		//������ǰ�Ѿ���ע���
		vector<RobotBetInfo>	m_robotBetInfos;					//������ע�б�

	//��������
	public:
		void			AddMacUserBet(uint64 mac,uint32 uin);
		//��ȡ��ǰѺעmac��
		uint32			GetBetMacCount(){ return m_macBetMap.size(); }
		//��ӻ���Ѻע
		void			AddRobotBet(uint8 areaIndex, uint64 betMoney, uint32 betUin, uint32 around, uint64 maxPlaceArea);
		//���û�������
		void			ResetRobotBetInfo();
		//�����ӻ���Ѻע��Ѻע�б�
		void			CheckAndAddRobotBetInfo(uint32 surplusEndTime );
		//��鷢�ͻ���Ѻע��Ϣ@surplusEndTime:ʣ��Ѻע����ʱ��
		void			CheckSendRobotBetInfo(uint32 surplusEndTime);

	private:
		

		
		bool			ValidateRoomPass(const char* pass);

		int				NotifyModifyBroadCast();
	
		bool			CheckChatText(User *srcUser, char *buf);

		uint8			GetBalanceAwardID(int64 balanceLine);
		void			RemoveGameInfo(uint32 uin);

	public:
		
		virtual int		OnHandleTimeout();
		void logout(User* pUser, bool kickOrPush, uint32 srcuin, uint8 actionType, uint8 unLock,bool oldSession = false);
		void shutdownUser(User* pUser); 
		uint16 ValidateUser(User* pUser);
		void On_TextChat(UdpInPacket* in, User* pSrcUser);



		void SetRoomInfoDB(const dataport::RoomInfo & room_info);
		void UpdateRoomInfoDB(const dataport::RoomInfo & room_info);
		void UpdateUserInfo(OutPacket& outData);
		void SyncUserInfo(UserGameMap& gameMap);
		
	
		void NotifyPPCWinItem(uint32 aRound, uint16 winItem, uint16 delayTime);
		void NotifyBetAction(uint8 areaIndex, uint32 betMoney, uint64 maxPlaceArea, uint32 betUin, uint32 around);
		void NotifyPPCStart(uint32 aRound, uint16 delayTime);

		void NotifyState(uint32 aRound, uint16 cmd, uint16 delayTime);

		void NotifyChangeBanker(uint32 uin, uint8 action, const char* msg);

		void NotifyPPCHistory();

		void NotifyAwardMsg();
		//������Ѻע
		void OnRecvPPCBet(UdpInPacket* in, User* pUser);

		void OnSyncScene(UdpInPacket* in, User* pUser);

		//�û�ׯ�Ҳ���
		void OnBakerReq(UdpInPacket* in, User* pUser);


		void OnEventGameStart();

		void OnEventGameEnd();

		void InitialUserMoneyArry();
		
		void BuildBankerInfo(OutPacket& outData);
		void BuildBankerWaitList(OutPacket& outData);
		void BuildAreaLimitInfo(OutPacket& outData);
		void BuildJetonItem(OutPacket& outData);
		void BuildGameEndInfo(OutPacket& outData, ppcGameEndInfo& endInfo);
		void BuildPPCHistory(OutPacket& outData);
		void BuildAllBetInfo(OutPacket& outData);
		void BuildUserBetInfo(UserWriteMoney2* userBetInfo, OutPacket& outData);
		

		void OnHandlePPC();

		void ProcessPPCScene(User* pUser);

		//תת�½ӿ� dbclient
	


		//�������½ӿ�
		void OnHandleLockMoney(dataport::MoneyResult* tmpResult);
		void OnHandlePPCBetMoney(dataport::MoneyResultList* tmpResult);
		void OnHandlePPCAwardMoney(dataport::MoneyResultList* tmpResult);
		void OnHandlePPCHistory(dataport::AwaredHistoryResult* tmpResult);
		void OnHandlePPSaveExperience(dataport::CDBClientResult* tmpResult);
		void OnHandlePPGetExperience(dataport::MoneyResult* tmpResult);
		void OnHandlePPSaveBankerResult(dataport::MoneyResult* tmpResult);
		void OnHandlePPGetUserBlance(dataport::GetBalanceInfo * tmpResult);
		void OnHandlePPGetUserCurMoneyBC(dataport::GetUserCurMoney * tmpResult);
		void OnHandlePPAddGameLimit(dataport::CDBClientResult* tmpResult);
		void OnHandlePPCheckGameLimit(dataport::GetUserPpcLimited* tmpResult);
		void OnHandleGetDisconnectTimes(dataport::GetDisconnectTimes* tmpResult);
		
		int NotifyOnline(User *pNewUser);
		int NotifyOffline(uint32 dstuin);
		int NotifyStatusChange(User* pUser);
		int NotifyModifyInfo();
		int NotifyKickOut(uint32 uin, uint32 srcuin, uint8 actionType);

		int NotifyRoomOpen(uint32 uin);
		int NotifyRoomClose(uint32 uin);

		void CheckKeepAlive();
		void CheckSendQueue();
		

		void UpdateCurrUserNum(int num);
		void UpdateRoomCurrUser(uint16 curruser, uint16 currconfuser);
		void UpdateRoomLink();
	
		void clearOldUser(User* newUser, User* oldUser);
		int  OnRcvNewUserLogon(User *s);
		void OnRcvLogout(UdpInPacket* in, User* pUser);
		void OnRcvLogon(UdpInPacket* in);

		
		void On_RcvRoomOpen(UdpInPacket* in, User* pUser);
		void On_RcvRoomClose(UdpInPacket* in, User* pUser);
		

		void On_RcvModifyPass(UdpInPacket* in, User* pUser);
		
		void On_RcvUpdateRoomInfo(UdpInPacket* in, User* pUser);
		
		void On_RcvGlobleMsg(UdpInPacket* in, User* pUser);
		void On_RcvKickOut(UdpInPacket* in, User* pUser);
		void OnRecvForbidChat(UdpInPacket* in, User* pUser);
		void On_RcvAddGameLimit(UdpInPacket* in, User* pUser);
		void OnChangeAutoMicStatus(UdpInPacket* in, User* pUser);
		void OnAdjustMicQueue(UdpInPacket* in, User* pUser);

		
		
		void Dispose();

		virtual void OnReceiveCmdPacket(UdpInPacket* in);
		virtual void OnReceiveGlobleMsg(UdpInPacket* in);
		virtual void OnReceiveGreatGiftMsg(UdpInPacket* in);
		virtual void OnKeepAliveTimeout(User* pUser);

		inline string GetUserNick(uint32 uin)
		{
			User* pUser = GetUser(uin);
			string strNick;
			if(pUser)
			{
				strNick = pUser->userNick;
			}
			return strNick;
		}

		inline uint32 GetRoomID(void)
		{
			return roomid;
		}

	public:



		inline void SetInfo(RoomInfo &info)						//only from first load
		{
			ownuin			= info.ownuin;
			roomTax			= info.roomtax;
			memset(roomName,0,sizeof(roomName));
			strncpy(roomName, info.roomName.c_str(),sizeof(roomName)-1);

			ispublic		= info.ispublic;
			auth			= info.auth;
			m_openStatus	= info.openstatus;
			memset(broadcast,0,sizeof(broadcast));
			strncpy(broadcast, info.broadcast.c_str(),sizeof(broadcast)-1);

			textChatStatus	= info.chatStatus;

			roomsize		= info.roomsize;
			maxMic			= info.maxmic;
			maxMicQueue		= info.maxMicQueue;

			
			autoMgrForRicher= info.autoMgrForRicher;


			roomMgr.clear();

			roomMgr = info.roomMgr;
		}

		inline void ModifyInfo(const char* name,const char* descript,const char* adv,uint8 ispublic,uint8 auth)
		{
			memset(roomName,0,sizeof(roomName));
			strncpy(roomName, name,sizeof(roomName)-1);
			descript = descript;
			ispublic = ispublic;
			memset(broadcast,0,sizeof(broadcast));
			strncpy(broadcast, adv,sizeof(broadcast)-1);
			auth = auth;
		}	

		void ChangeStatus();

		//************************************
		// Method:    AppendRoomInfo 
		// FullName:  Room::AppendRoomInfo
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: UdpOutPacket * out		
		// Parameter: int m_localnet
		//************************************
		void AppendRoomInfo(UdpOutPacket *out, int m_localnet, User *pUser);
	public:
		void OnReloadRoomInfo(RoomInfo &info);				//����������Ϣ
	};



}

#endif // !defined  BIGROOM__ROOM_H_
