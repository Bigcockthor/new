#if !defined BIG_ROOM_USER_H_
#define BIG_ROOM_USER_H_

#include "include/icqtypes.h"
#include "include/udppacket.h"
#include "ace/SOCK_Dgram.h"
#include "ace/INET_Addr.h"
#include <list>
#include "include/sync.h"
#include "bigroomdef.h"
#include "room/RoomCommon.h"
#include "include/slab.h"
#include "include/list.h"
#include "include/coretime.h"
#include "include/queue.h"

struct BetItem
{
	uint8	betIdx;												//下注项目
	uint32	betAmount;											//下注金额
};

typedef std::vector<BetItem> BetList;

 
typedef std::list<UdpOutPacket *> PACKETLIST;


typedef RMUin * PRMUIN;




namespace BigRoom
{
	class Room;
	class RoomManager;


	class UserBetTemp
	{
	public:
		UserBetTemp(uint32 userid, uint32 iUserIP, uint64 iUserMac, int64 iBalance): uin(userid), userIP(iUserIP), userMac(iUserMac), balance(iBalance)
		{
			betCount = 0;
			awardCount = 0;
			awardRound = 0;
			awardID = uint8(-1);
			tryTimes = 0;
			
		}
		
		const uint32 uin;
		uint32 userIP;
		uint64 userMac;
		BetList bets;												//扣款成功的押注
		uint64 betCount;
		uint64 awardCount;
		uint32 awardRound;	
		uint8 awardID;
		uint8 tryTimes;
		int64 balance;
	};

	//在线用户类
	class User
	{
	public:

		User(uint32 initUin, uint32 initSid, uint8 android);
		virtual ~User(void);
		enum UserOutState
		{
			NORMAL_STATE = 0,	//正常状态
			FOURCE_OFLINE,		//被顶下线
		};

		enum SendQueueState
		{
			NORMAL_SENDQUEUE = 0,	//正常发送队列
			GIFT_SENDQUEUE,			//送礼发送队列
		};
		ChatAclCtrl userAcl;										//用户各种权限处理
		uint64 userMac;												//用户MAC地址
		uint16 customFace;											//用户自定义图像
		uint8	richOrder;											//富翁排行, 默认为0,不进入排行, 非0为相应排行值
		uint8	forbidChat;											//禁止发言
		uint8 filterWordTimes;
		int64	earning;											//输赢状态(mac和uin赢钱最大值)
		ListHead micWait;
		uint32 onMicStartTime;										//在麦开始时间
		const uint8 isAndroid;										//机器人标志
		ChatUserType	chatUserType;	
		uint8 isGameLimit;											//是否被防挂机限制
		uint32 unBetCount;											//连续没押注次数
		uint8 kickLimitTimes;                                       //当天没押注被踢次数
		uint16 GetRank()
		{
			uint16 newRank = rank;
			if (rank  & USER_RANK_ROOMMAN)
			{
				if (!isManager)
					newRank &= ~USER_RANK_ROOMMAN;
			}

			return newRank;
		}

		uint8  isManager;
		/*
		 *	For 转转
		 */

		//BetList bets;												//未扣款成功的押注
		//BetList beteds;											//扣款成功的押注
		uint32 lastBetRound;
		int64  earnMoney;											//正的为赚钱了，负的为输钱了
		string enter_title;
		string enter_pic;
		uint8  m_nState;											//保存用户是否被顶下线
	public:
		void OnOffline(bool pushOut = false, uint32 newEnter = 0);

	
		int sendNtyMsg(const char* ntymsg);
		//	int sendSysMsg(const char* sysmsg);
		int SendCmdResult(uint16 cmd, uint16 msgcode);

		int Dispose();
		//************************************
		// Method:    SendTextData
		// FullName:  User::SendTextData
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: uint32 msgid
		// Parameter: uint32 srcUin
		// Parameter: uint32 destUin
		// Parameter: uint8 ispublic
		// Parameter: uint32 curtime
		// Parameter: const char * textData
		// Parameter: uint8 type
		// Parameter: uint32 roomid				//本房间信息为0, 转播房间为相应房间ID
		//************************************
		int SendTextData(uint32 srcUin,uint32 destUin,uint8 ispublic,uint32 curtime,
			const char* msg, uint8 type = 0);

		//碰碰车历史中奖记录
		int NotifyPPCHistory(OutPacket& outData);

		int NotifyPPCBankerChange(OutPacket& extData);
		//新一轮开始通知
		int NotifyPPCStart(uint32 roundID, uint16 delayTime, OutPacket& extData);


		//碰碰车开奖通知
		int NotifyPPCAward(uint32 aRound, uint16 winItem, uint16 delayTime, OutPacket& outData);



		//用户下注结果通知
		int NotifyBetResult(uint8 betResult, uint32 aRound);

		int NotifyUpdateUserInfo(OutPacket& outData);
		//下注动作通知
		int NotifyBetAction(uint8 areaIndex, uint32 betMoney, uint64 maxPlaceArea, uint32 betUin, uint32 around, OutPacket& outData, uint16 betLimit);

		//游戏结束结算信息
		int NotifyGameEndInfo(OutPacket& extData);


		int NotifyOnline(User* pUser);							//发送用户进入房间消息
		int NotifyOffline(uint32 dstUin);						//发送用户离开房间消息
		int NotifyAutoMicStatus(bool autoMic, uint32 opr);					//提示自动麦克状态

		//提示用户被踢出
		int NotifyKickOut(uint32 uin, uint32 actionSrc, uint8 actionType);
		int NotifyConfKickOut(uint32 uin, uint32 opr);
	

		int SendLogonResult(uint16 result, Room* pRoom, uint32 blockTime = 0);

		
		int NotifyConfJoin(uint32 uin, uint8 micIndex, uint32 opr);			//发送用户上麦消息
		int NotifyConfExit(uint32 uin, uint32 opr);							//发送用户下麦消息

		int	NotifyAddCfWait(uint32 uin);						//发送用户排麦消息
		int	NotifyRemoveCfWait(uint32 uin);						//发送用户退出排麦消息

		int NotifyRoomOpen(uint32 uin);							//发送房间打开消息，不可再进入
		int NotifyRoomClose(uint32 uin);						//发送房间关闭消息，可以进人

		int SendMicQueue(Room* pRoom, uint16 cmd);
		int SendRoomInfo(Room* pRoom);							//发送房间信息
		int SendRoomBroadCast(Room* pRoom);						//下发房间广播消息
		int SendGlobleMsg(UdpInPacket *in);						//下发房间广播消息
		int SendGreatGiftMsg(UdpInPacket *in);					//下发刷大礼消息
		




		//发送房间用户列表
		int SendRoomUserList(Room* pRoom, uint16 cmd);

		

		//发送麦克列表
		int SendMicList(Room* pRoom, uint16 cmd);

		//提示刷礼物信息
		int NotifyUseGift(uint32 srcuin,uint32 dstuin, uint32 giftid, uint32 giftamount);

		//提示刷礼物信息
		int NotifyUserBet(uint32 round, uint32 srcuin, uint32 betCount, BetList &l);
		int NotifyAwardStatus(uint32 round, uint16 cmd, uint16 delayTime);
		int NotifyAwardInfo(uint32 roundID, uint16 cmd,  uint8 awardID);
		int NotifTodayAwardInfo(uint16 *awdInfo);
		//被顶掉线
		int NotifyForceOffline(uint32 newroomid, uint32 newip, uint16 newport, uint8 newdevType);

		//提示刷礼物信息
		//************************************
		// Method:    NotifyPrize
		// FullName:  BigRoom::User::NotifyPrize
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: uint32 srcuin
		// Parameter: uint32 dstuin
		// Parameter: uint32 prize		倍数
		// Parameter: uint32 prizeCount 奖金总额
		//************************************
		int NotifyPrize(uint32 srcuin, uint32 dstuin, uint32 prize, uint32 prizeCount);

		bool CheckKeepAlive();


		int OnLogon(Room* pRoom);
		void OnLogonFail(Room* pRoom,uint16 failCode, uint32 blockTime = 0);

		void OnLogout(Room* pRoom);
		uint16 SetRank (uint16 rank);

		//判断用户权限级别,其中超管权限还可以细分 
		bool RankIsSuperMan();
		bool RankIsRoomOwner();
		bool RankIsManager();
		bool RankIsVisitor();

		Room* m_pMyRoom;


		ListHead item;											//在房间用户列表项

		char userNick[MAX_NICK_LEN+1];
		const uint32 uin;
		uint16 face;
		uint16 rank;											//等级
		uint8 g_userType;										//代理或公司销售等标志
		uint8 gender;
		UserLevel levelInfo;									//会员标记：0,非会员 1,会员
		uint32	lExperience;									//用户经验
		uint64 money;											//资金
		uint64 received;										//收礼
		uint8 accountState;
		uint16 m_ver;
		uint32 m_roomid;
		time_t starttime;										//记录登陆起始时间
		bool prized;											//是否中奖

		//用于建立命令session
		const uint32  m_sid;											//session ID
		uint32	ip;												//外部ip
		uint16	port;											//udp端口
		uint32 proxyIP;											//代理服务器地址
		uint16 proxyPort;										//代理服务器端口

		uint32 m_window;										//window
		uint16	m_seq;											//用户建立cms session,ack用的seq
		uint16 m_recvseq;										//recv req
		string m_Passwd;										//用户口令
		string m_roomPasswd;
		uint16 m_timertime;										//用户清除需要等待时间
		time_t m_lastText;										//文本最后发送时间
		uint8 m_netType;										//用户选择的网络类型
		uint8 m_nChannelState;									//发送通道
		uint8 m_bBindLogin;
		uint8 m_passType;		
		uint32 m_loginStart;									//记录其实登录时间戳
		OutPacket m_userAllBet;									//用户最终押注
		DECLARE_SLAB(User)

	public:
		void ClearSendQueue(PACKETLIST& sendList);
		void ClearSendQueue();
		void Release();
		
		/*
		*	 from session
		*/
		int SendKeepAlive(uint16 seq);
		bool ValidatePacket(UdpInPacket* in);
		int SendThePacket(UdpOutPacket *out);					//发送报文并调整发送对列
	private:


		time_t m_keepaliveExpire;



		PACKETLIST	sendQueue;									//用户发送对列
		PACKETLIST	sendQueueEx;								//他人押注通知队列

		void OnRcvAck(uint16 seq);
		bool setWindow(uint16 seq);
		bool ResetKeepAlive();
		void OnRcvKeepAlive(UdpInPacket *in);
		int SendAckPacket(uint16 seq);

		UdpOutPacket* CreatePacket_Head(bool needAck,uint32 roomid,uint32 uin,uint32 sid,uint16 cmd);
		UdpOutPacket* CreatePacket_Head(bool needAck,uint16 cmd);
		UdpOutPacket* CreatePacket_Head(uint16 cmd);

		void SendPacket(UdpOutPacket *out, int nSendQueueState = NORMAL_SENDQUEUE);
		void SendNextPacket(int nSendQueueState);
		int SendDirect(UdpOutPacket *out);


		void AppendUserInfo(UdpOutPacket &out, uint16 packetVer);
	};


}
#endif // BIG_ROOM_USER_H_
