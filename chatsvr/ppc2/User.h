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
	uint8	betIdx;												//��ע��Ŀ
	uint32	betAmount;											//��ע���
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
		BetList bets;												//�ۿ�ɹ���Ѻע
		uint64 betCount;
		uint64 awardCount;
		uint32 awardRound;	
		uint8 awardID;
		uint8 tryTimes;
		int64 balance;
	};

	//�����û���
	class User
	{
	public:

		User(uint32 initUin, uint32 initSid, uint8 android);
		virtual ~User(void);
		enum UserOutState
		{
			NORMAL_STATE = 0,	//����״̬
			FOURCE_OFLINE,		//��������
		};

		enum SendQueueState
		{
			NORMAL_SENDQUEUE = 0,	//�������Ͷ���
			GIFT_SENDQUEUE,			//�����Ͷ���
		};
		ChatAclCtrl userAcl;										//�û�����Ȩ�޴���
		uint64 userMac;												//�û�MAC��ַ
		uint16 customFace;											//�û��Զ���ͼ��
		uint8	richOrder;											//��������, Ĭ��Ϊ0,����������, ��0Ϊ��Ӧ����ֵ
		uint8	forbidChat;											//��ֹ����
		uint8 filterWordTimes;
		int64	earning;											//��Ӯ״̬(mac��uinӮǮ���ֵ)
		ListHead micWait;
		uint32 onMicStartTime;										//����ʼʱ��
		const uint8 isAndroid;										//�����˱�־
		ChatUserType	chatUserType;	
		uint8 isGameLimit;											//�Ƿ񱻷��һ�����
		uint32 unBetCount;											//����ûѺע����
		uint8 kickLimitTimes;                                       //����ûѺע���ߴ���
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
		 *	For תת
		 */

		//BetList bets;												//δ�ۿ�ɹ���Ѻע
		//BetList beteds;											//�ۿ�ɹ���Ѻע
		uint32 lastBetRound;
		int64  earnMoney;											//����Ϊ׬Ǯ�ˣ�����Ϊ��Ǯ��
		string enter_title;
		string enter_pic;
		uint8  m_nState;											//�����û��Ƿ񱻶�����
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
		// Parameter: uint32 roomid				//��������ϢΪ0, ת������Ϊ��Ӧ����ID
		//************************************
		int SendTextData(uint32 srcUin,uint32 destUin,uint8 ispublic,uint32 curtime,
			const char* msg, uint8 type = 0);

		//��������ʷ�н���¼
		int NotifyPPCHistory(OutPacket& outData);

		int NotifyPPCBankerChange(OutPacket& extData);
		//��һ�ֿ�ʼ֪ͨ
		int NotifyPPCStart(uint32 roundID, uint16 delayTime, OutPacket& extData);


		//����������֪ͨ
		int NotifyPPCAward(uint32 aRound, uint16 winItem, uint16 delayTime, OutPacket& outData);



		//�û���ע���֪ͨ
		int NotifyBetResult(uint8 betResult, uint32 aRound);

		int NotifyUpdateUserInfo(OutPacket& outData);
		//��ע����֪ͨ
		int NotifyBetAction(uint8 areaIndex, uint32 betMoney, uint64 maxPlaceArea, uint32 betUin, uint32 around, OutPacket& outData, uint16 betLimit);

		//��Ϸ����������Ϣ
		int NotifyGameEndInfo(OutPacket& extData);


		int NotifyOnline(User* pUser);							//�����û����뷿����Ϣ
		int NotifyOffline(uint32 dstUin);						//�����û��뿪������Ϣ
		int NotifyAutoMicStatus(bool autoMic, uint32 opr);					//��ʾ�Զ����״̬

		//��ʾ�û����߳�
		int NotifyKickOut(uint32 uin, uint32 actionSrc, uint8 actionType);
		int NotifyConfKickOut(uint32 uin, uint32 opr);
	

		int SendLogonResult(uint16 result, Room* pRoom, uint32 blockTime = 0);

		
		int NotifyConfJoin(uint32 uin, uint8 micIndex, uint32 opr);			//�����û�������Ϣ
		int NotifyConfExit(uint32 uin, uint32 opr);							//�����û�������Ϣ

		int	NotifyAddCfWait(uint32 uin);						//�����û�������Ϣ
		int	NotifyRemoveCfWait(uint32 uin);						//�����û��˳�������Ϣ

		int NotifyRoomOpen(uint32 uin);							//���ͷ������Ϣ�������ٽ���
		int NotifyRoomClose(uint32 uin);						//���ͷ���ر���Ϣ�����Խ���

		int SendMicQueue(Room* pRoom, uint16 cmd);
		int SendRoomInfo(Room* pRoom);							//���ͷ�����Ϣ
		int SendRoomBroadCast(Room* pRoom);						//�·�����㲥��Ϣ
		int SendGlobleMsg(UdpInPacket *in);						//�·�����㲥��Ϣ
		int SendGreatGiftMsg(UdpInPacket *in);					//�·�ˢ������Ϣ
		




		//���ͷ����û��б�
		int SendRoomUserList(Room* pRoom, uint16 cmd);

		

		//��������б�
		int SendMicList(Room* pRoom, uint16 cmd);

		//��ʾˢ������Ϣ
		int NotifyUseGift(uint32 srcuin,uint32 dstuin, uint32 giftid, uint32 giftamount);

		//��ʾˢ������Ϣ
		int NotifyUserBet(uint32 round, uint32 srcuin, uint32 betCount, BetList &l);
		int NotifyAwardStatus(uint32 round, uint16 cmd, uint16 delayTime);
		int NotifyAwardInfo(uint32 roundID, uint16 cmd,  uint8 awardID);
		int NotifTodayAwardInfo(uint16 *awdInfo);
		//��������
		int NotifyForceOffline(uint32 newroomid, uint32 newip, uint16 newport, uint8 newdevType);

		//��ʾˢ������Ϣ
		//************************************
		// Method:    NotifyPrize
		// FullName:  BigRoom::User::NotifyPrize
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: uint32 srcuin
		// Parameter: uint32 dstuin
		// Parameter: uint32 prize		����
		// Parameter: uint32 prizeCount �����ܶ�
		//************************************
		int NotifyPrize(uint32 srcuin, uint32 dstuin, uint32 prize, uint32 prizeCount);

		bool CheckKeepAlive();


		int OnLogon(Room* pRoom);
		void OnLogonFail(Room* pRoom,uint16 failCode, uint32 blockTime = 0);

		void OnLogout(Room* pRoom);
		uint16 SetRank (uint16 rank);

		//�ж��û�Ȩ�޼���,���г���Ȩ�޻�����ϸ�� 
		bool RankIsSuperMan();
		bool RankIsRoomOwner();
		bool RankIsManager();
		bool RankIsVisitor();

		Room* m_pMyRoom;


		ListHead item;											//�ڷ����û��б���

		char userNick[MAX_NICK_LEN+1];
		const uint32 uin;
		uint16 face;
		uint16 rank;											//�ȼ�
		uint8 g_userType;										//�����˾���۵ȱ�־
		uint8 gender;
		UserLevel levelInfo;									//��Ա��ǣ�0,�ǻ�Ա 1,��Ա
		uint32	lExperience;									//�û�����
		uint64 money;											//�ʽ�
		uint64 received;										//����
		uint8 accountState;
		uint16 m_ver;
		uint32 m_roomid;
		time_t starttime;										//��¼��½��ʼʱ��
		bool prized;											//�Ƿ��н�

		//���ڽ�������session
		const uint32  m_sid;											//session ID
		uint32	ip;												//�ⲿip
		uint16	port;											//udp�˿�
		uint32 proxyIP;											//�����������ַ
		uint16 proxyPort;										//����������˿�

		uint32 m_window;										//window
		uint16	m_seq;											//�û�����cms session,ack�õ�seq
		uint16 m_recvseq;										//recv req
		string m_Passwd;										//�û�����
		string m_roomPasswd;
		uint16 m_timertime;										//�û������Ҫ�ȴ�ʱ��
		time_t m_lastText;										//�ı������ʱ��
		uint8 m_netType;										//�û�ѡ�����������
		uint8 m_nChannelState;									//����ͨ��
		uint8 m_bBindLogin;
		uint8 m_passType;		
		uint32 m_loginStart;									//��¼��ʵ��¼ʱ���
		OutPacket m_userAllBet;									//�û�����Ѻע
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
		int SendThePacket(UdpOutPacket *out);					//���ͱ��Ĳ��������Ͷ���
	private:


		time_t m_keepaliveExpire;



		PACKETLIST	sendQueue;									//�û����Ͷ���
		PACKETLIST	sendQueueEx;								//����Ѻע֪ͨ����

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
