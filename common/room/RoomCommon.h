#pragma once
#ifndef _ROOMCONNON_SDKFJDLKFJLSDJFLSFJD_
#define _ROOMCONNON_SDKFJDLKFJLSDJFLSFJD_
#include <string>
#include <vector>
#include <map>
#include <list>
#include "include/icqtypes.h"
#include "include/slab.h"
#include "im/imdefine.h"
#include "media/mediatype.h"
#include "room/RoomCmdDef.h"
#include "include/log.h"
#include "include/TinyMarkup.h"
#include "include/base64.h"

#ifdef _ACE_SOCK
#undef _ACE_SOCK
#endif // _ACE_SOCK

#include "include/udppacket.h"

#ifndef MAX_ASSIST_USER_NUM
#	define MAX_ASSIST_USER_NUM				100					//最大副室数
#endif

#ifndef MAX_AWARD_ITEM_NUM
#define MAX_AWARD_ITEM_NUM 22
#endif

#ifndef MAX_NICK_LEN
#define MAX_NICK_LEN					36
#endif


#ifndef MAX_SONG_LEN
#define MAX_SONG_LEN	450
#endif

using namespace std;

class UdpInPacket;
class MemberUnit;
typedef std::map<uint32 ,uint8> UinMap;
typedef std::map<uint32 ,uint32> UinMap32;
typedef std::map<uint64, uint32> UINT64Map;
typedef std::map<uint32, uint64> UinMap64;
typedef std::vector<uint32>		UintVector;
typedef std::vector<MemberUnit> MEMBERUNIT_VECTOR; 
typedef std::map<std::string, std::string> FieldNameValueMap; 


class RoomUnit
{
public:
	uint32 id;
	uint16 type;
	uint32 ip;
	uint16 port;
	string param;
};


//用户会员级别及爵位等级
#pragma pack(1)
typedef union UserLevel
{
	struct
	{
		uint8 level:4;
		uint8 lordLevel:4;
	};
	uint8 value;
}UserLevel;

typedef union MicAVStatus
{
	struct
	{
		uint8 disableAudio:4;
		uint8 disableVideo:4;
	};
	uint8 value;
}MicAVStatus;

typedef union PpcViewInfo
{
	struct
	{
		uint8 name:1;
		uint8 id:1;
		uint8 money:1;
		uint8 level:1;
		uint8 exp:1;
	};
	uint16 value;
	PpcViewInfo()
	{
		value =1;
	}
}PpcViewInfo;


//房间相关开关,后面开关全部使用此数据代替
typedef union RoomCtrl
{
	struct
	{
		uint64 disablePrivateMic:1;			//私麦开关
		uint64 disableOpenBox:1;			//挖宝开关
		uint64 disableColorBal:1;			//彩条开关
		uint64 disableRedpaper:1;			//随播红包开关
		uint64 disableAutoLetao:1;			//乐淘自动领取开关
		uint64 disableAutoGernal:1;			//商家自动领取开关
		uint64 disableDiamonGift:1;			//钻石礼物开关
		uint64 disableDuoBao:1;				//一元夺宝开关
	};
	uint64 value;
}RoomCtrl;

typedef union PidBlackInfo
{
	struct
	{
		uint8 bBlackIp:1;
		uint8 bBlackMac:1;
		uint8 bBlackuin:1;
	};
	uint8 value;
}PidBlackInfo;


typedef union SystempMsgInfo
{
	struct
	{
		uint16 bEchoPublic:1;	//是否公屏显示
		uint16 bEchoPrive:1;	//是否私屏显示
		uint16 bWithLink:1;		//是否需要客户端附加超链接
		uint16 bRoomShareInfo:1; //室主查询房间分享人数
		uint16 bNotEnoughIp:1;//房间人数不足，无法领取上麦奖励
		//扩展
	};
	SystempMsgInfo()
	{
		value = 0;
	}
	uint16 value;


}SystempMsgInfo;

#pragma pack()

#pragma pack(1)
union MicInfo
{
	struct
	{
		uint16 micIndex:2;		//是否有麦,0表示没有，1表示在1号麦上，2表示在2号麦上
		uint16 maxMicTime:14;
	};
	uint16 micInfo;
};
#pragma pack()

#pragma pack(1)

class MemberUnit
{
public:
	uint32 uin;
	uint32 status;
	string nick;
	uint16 face;
	uint32 rank;
	uint8 g_userType;		//全部用户类型（代理、销售、客服等）
	uint8 flag;		//flag指示该用户是有麦克,是否有摄像头,是否在会议中
	uint8 devType;
	uint16 forBidTime;			//禁言剩余时间 
	uint64 money;		//用户资金
	UserLevel level;		//是否会员
	uint64 received;
	MicInfo micInfo;

	Customface customface;//自定义头像版本
	uint8 richerOrder;  //富翁排行, 未进入排行则为0, 否则为相应排行值
	MemberUnit()
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
		level.value = 0;
		received = 0;
		micInfo.micInfo = 0;
		customface.customFace = 0;
		richerOrder = 0;
		nick = "";
	}
	MemberUnit(const MemberUnit &m)
	{
		*this = m;
	}
	MemberUnit& operator = (const MemberUnit &m)
	{
		this->uin = m.uin;
		this->nick = m.nick;
		this->status = m.status;
		this->face = m.face;
		this->rank = m.rank;
		this->g_userType = m.g_userType;
		this->flag = m.flag;
		this->money = m.money;
		this->level.value = m.level.value;
		this->received = m.received;
		this->micInfo.micInfo = m.micInfo.micInfo;
		this->customface.customFace = m.customface.customFace;
		this->richerOrder = m.richerOrder;
		this->devType = m.devType;
		this->forBidTime = m.forBidTime;
		return *this;
	}
};

#pragma pack()

struct USER_INFO
{
	uint32 uin;
	uint32 status;
	string nick;
	uint16 face;
	uint32 rank;
	uint8 g_usertype;
	uint64 money;
	UserLevel  level;
	uint64 received;
	Customface customface;//自定义头像版本
	uint8 richerOrder;  //富翁排行, 未进入排行则为0, 否则为相应排行值
};

//聊天区游戏
struct ChatGame
{
	uint8 randNum1;	//掷骰子随机数1
	uint8 randNum2;	//掷骰子随机数2
	ChatGame()
	{
		memset(this, 0, sizeof(ChatGame));
	}
};



//收费表情
struct ExpressionInfo
{
	unsigned int packetid;
	unsigned int expressionid;
	unsigned char num;
};

typedef std::vector<ExpressionInfo> ExpressionInfoList;


typedef struct GuardInfo
{
	char   userNick[MAX_NICK_LEN+1];
	uint16 order;
	uint32 money;
	uint32 uin;

	GuardInfo()
	{
		memset(userNick, 0, sizeof(userNick));
		order = 0; 
		money = 0;
		uin	  = 0;
	}
	void operator = (const GuardInfo &u)
	{
		memcpy(userNick, u.userNick, MAX_NICK_LEN);
		order = u.order; 
		money = u.money;
		uin = u.uin;
	}
}GuardInfo;

typedef std::map<uint32,GuardInfo>	GuardInfoMap;
typedef std::vector<GuardInfo> GuardInfoList;



typedef struct SingeInfo
{
	char nickname[MAX_NICK_LEN+1];
	char songname[MAX_SONG_LEN+1];
	unsigned int opruin;
	unsigned int addtime;
	SingeInfo()
	{
		memset(nickname, 0, MAX_NICK_LEN + 1);
		memset(songname, 0, MAX_SONG_LEN + 1);
	}
	void operator = (const SingeInfo &u)
	{
		memcpy(nickname, u.nickname, MAX_NICK_LEN);
		memcpy(songname, u.songname, MAX_SONG_LEN);

		opruin = u.opruin; 
		addtime = u.addtime;
	}
}SingeInfo;
typedef std::vector<SingeInfo> SingeInfoList;

typedef struct SiegeInfo
{
	unsigned int srcuin;
	unsigned int dstuin;
	unsigned int amount;
	unsigned int giftid;
	unsigned int leftTime;
	unsigned int startTime;
	string		 srcNick;
	string		 dstNick;
	string		 srcRankName;
	string		 dstRankName;
	SiegeInfo()
	{
		Reset();
	}

	void Reset()
	{
		srcuin = 0;
		dstuin = 0;
		amount = 0;
		giftid = 0;
		leftTime = 0;
		startTime = 0;
		srcNick = "";
		dstNick = "";
		srcRankName = "";
		dstRankName = "";
	}

}SiegeInfo;

typedef struct GiftFirstInfo
{
	unsigned int type;
	unsigned int srcuin;
	string		 srcNick;
	string		 toltalnum;
	unsigned int endTime;
	int		 nNeedUpdate;

	GiftFirstInfo()
	{
		Reset();
	}

	void Reset()
	{
		srcuin = 0;
		type = 0;
		toltalnum = "0";
		srcNick = "";
		endTime = 0;
		nNeedUpdate = 0;
	}

}GiftFirstInfo;


class BankerInfo
{
public:
	BankerInfo()
	{
		Reset();
	}
	void Reset()
	{
		m_bankerMoney = m_iBankerWinScore = uin  = m_wBankerTimes = 0;
	}
	uint32		uin;									//庄家帐号
	uint8		m_wBankerTimes;							//做庄次数
	int64		m_iBankerWinScore;						//累计成绩
	uint64		m_bankerMoney;							//当前庄家本金(用户或系统庄家)
};


//游戏结束
class ppcGameEndInfo
{
public:
	ppcGameEndInfo()
	{
		m_bWin					= 0;
		m_money					= 0;
		iRevenue				= 0;
		m_rounds				= 0;
		m_bSucess				= 0;
		iUserScore				= 0;	
		nBankerTime				= 0;
		cbGoalAnimal			= 0;
		iBankerScore			= 0;
		m_lExperience			= 0;	
		iBankerTotallScore		= 0;	
		

	}
	bool							m_bSucess;
	bool							m_bWin;
	uint8							nBankerTime;						//做庄次数
	uint16							cbGoalAnimal;						//本次停止的位置
	uint32							m_lExperience;
	uint32							m_rounds;
	uint64							iBankerScore;						//庄家成绩
	uint64							iBankerTotallScore;					//庄家成绩
	uint64							iUserScore;							//玩家成绩
	uint64							iRevenue;							//游戏税收
	uint64							m_money;

	
};
/*
*	以下是定义将来统一处理用, 进行房间整理
*/



//群成员类
class RMUin 
{
public:
	uint32		uin;
	string		nick;	
	uint16		face;
	uint32		rank;
public:
	RMUin() {}
	RMUin(uint32 tuin, const char* tnick, uint16 tface, uint32 trank) 
	{
		uin = tuin;
		nick = tnick;
		face = tface;
		rank = trank;

	}
	~RMUin() {}
#ifndef WIN32
	DECLARE_SLAB(RMUin)
#endif
};

typedef std::map<uint32, RMUin*> RMUinMap;


class MediaServerItem
{
public:
	uint32		srvid;
	uint32		m_AVSvrIp;
	uint8		m_nettype;
	uint16      m_AVSvrport;
public:
	MediaServerItem()
	{
		srvid = m_AVSvrIp = m_AVSvrport =  m_nettype = 0;
	}
	template <class T>
		void BuildPacket(T &out)
	{
		out << srvid << m_AVSvrIp << m_AVSvrport << m_nettype;
	}
	MediaServerItem(const MediaServerItem& item)
	{
		srvid=item.srvid;
		m_AVSvrIp=item.m_AVSvrIp;
		m_nettype=item.m_nettype;
		m_AVSvrport=item.m_AVSvrport;
	}
	MediaServerItem& operator=(const MediaServerItem& item)
	{
		this->srvid=item.srvid;
		this->m_AVSvrIp=item.m_AVSvrIp;
		this->m_nettype=item.m_nettype;
		this->m_AVSvrport=item.m_AVSvrport;
		return *this;
	}
	template <class T>
		void ParsePacket(T &in)
	{
		in >> srvid >> m_AVSvrIp >> m_AVSvrport >> m_nettype;
	}

};

typedef std::vector<MediaServerItem> MediaSvrList;



class RoomInfo
{
public:
	RoomInfo(uint32 mFid) : fid(mFid)
	{
		ownuin			= 0;
		memset(assistant, 0, sizeof(assistant));
		kindid			= 0;

		roomtax			= 1;
		roomtype		= 0;
		ispublic		= 0;
		openstatus		= 0;
		chatStatus		= 0;

		auth			= 0;
		maxmic			= 0;
		roomsize		= 0;
		maxMicQueue		= 0;
		maxMicQPerUser	= 0;
		maxManager		= 0;
								

		idctype			= 0;
		
		uSupportGts		= 0;
	
		pubText			= 0;

		micMaxTime		= 0;
		autoMgrForRicher= 0;
		regionMaster	= 0;
		showEnterPic	= 1;
		enableColorBar	= 1;
		memset(regionAssistant, 0, sizeof(regionAssistant));
		micMode			= CRoomMicMode::GENERAL_MODE;
	}
	const uint32 fid;											//房间号
	uint32 ownuin;												//室主ＩＤ
	uint32 assistant[MAX_ASSIST_USER_NUM];						//副室主

	uint32 kindid;												//房间所属分类ID


	uint8 roomtax;												//税收性质
	uint16 roomtype;											//
	string roomName;											//房间名
	string descript;											//房间描述
	string broadcast;
	uint8 ispublic;												//是否是公开房间
	uint8 openstatus;											//房间状态
	uint8 chatStatus;											//房间文字聊天状态

	uint8 auth;													//房间进入限制
	uint16 maxmic;												//麦数
	uint16 roomsize;											//房间最大人数
	uint16 maxMicQueue;											//最大排麦对列
	uint8 maxMicQPerUser;										//最大个人排麦数
	uint16 maxManager;											//最大管理员人数
	UinMap roomMgr;												//房间管理员

	uint8	idctype;											//房间通讯类型
	uint8	uSupportGts;										//是否支持视频转发
	MediaSvrList mediaSvrs;										//音视频转发服务器
	uint8	pubText;

	string  password;											//进房间密码
	uint16	micMaxTime;											//最大麦时时间
	uint8	autoMgrForRicher;									//富翁自动为处理员
	uint32	regionMaster;										//区管
	uint32	regionAssistant[MAX_ASSIST_USER_NUM];				//副区管
	uint8	enableColorBar;										//是否允许房间彩条
	uint8 showEnterPic;											//显示进房间信息

	uint32 serverid;											//服务ＩＤ
	string prgName;												//客户端程序名
	uint8	micMode;											//是否允许房间彩条

	std::string BuildXml()
	{
		CMarkup xmldoc;
		xmldoc.AddElem("fid", fid);
		xmldoc.AddElem("ownuin", ownuin);
		xmldoc.AddElem("assistants");
		for (uint8 i=0; i<MAX_ASSIST_USER_NUM; i++)
		{
			if (assistant[i])
				xmldoc.AddChildElem("ast", assistant[i]);
		}
		xmldoc.AddElem("roomtax", roomtax);
		xmldoc.AddElem("roomtype", roomtype);
		xmldoc.AddElem("roomName", talk_base::Base64::encode(roomName).c_str());
		xmldoc.AddElem("descript", talk_base::Base64::encode(descript).c_str());
		xmldoc.AddElem("broadcast", talk_base::Base64::encode(broadcast).c_str());
		xmldoc.AddElem("ispublic", ispublic);
		xmldoc.AddElem("openstatus", openstatus);
		xmldoc.AddElem("chatStatus", chatStatus);

		xmldoc.AddElem("auth", auth);
		xmldoc.AddElem("maxmic", maxmic);
		xmldoc.AddElem("roomsize", roomsize);
		xmldoc.AddElem("maxMicQueue", maxMicQueue);
		xmldoc.AddElem("maxMicQPerUser", maxMicQPerUser);

		xmldoc.AddElem("maxManager", maxManager);
		xmldoc.AddElem("roomMgrs");
		for (UinMap::iterator it=roomMgr.begin(); it != roomMgr.end(); it++)
			xmldoc.AddChildElem("mgr", it->first);

		xmldoc.AddElem("idctype", idctype);
		xmldoc.AddElem("uSupportGts", uSupportGts);
		xmldoc.AddElem("pubText", pubText);
		xmldoc.AddElem("password", password.c_str());
		xmldoc.AddElem("micMaxTime", micMaxTime);
		xmldoc.AddElem("autoMgrForRicher", autoMgrForRicher);
		xmldoc.AddElem("enableColorBar", enableColorBar);
		xmldoc.AddElem("areaMaster", regionMaster);
		xmldoc.AddElem("regionAssistant");
		for (uint8 i=0; i<MAX_ASSIST_USER_NUM; i++)
		{
			if (regionAssistant[i])
				xmldoc.AddChildElem("regionast", regionAssistant[i]);
		}

		xmldoc.AddElem("showEnterPic", showEnterPic);
		xmldoc.AddElem("micMode", micMode);



	#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
	#else
		return (LPCTSTR)xmldoc.GetDoc();
	#endif
	}

	void ParseXML(std::string xmlStr)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(xmlStr.c_str());


		xmldoc.GetChildValue("ownuin", ownuin);

		if (xmldoc.FindElem("assistants"))
		{
			xmldoc.IntoElem();
			
			for (uint8 i=0; i<MAX_ASSIST_USER_NUM; i++)
			{
				assistant[i] = GetChildIntValue(xmldoc, "ast");
				if (!assistant[i])
					break;
			}
			xmldoc.OutOfElem();
		}
		xmldoc.ResetPos();

		roomtax = xmldoc.GetChildValue("roomtax");
		roomtype = xmldoc.GetChildValue("roomtype");
		roomName = talk_base::Base64::decode(GetChildStrValue(xmldoc, "roomName"));
		descript = talk_base::Base64::decode(GetChildStrValue(xmldoc, "descript"));
		broadcast = talk_base::Base64::decode(GetChildStrValue(xmldoc, "broadcast"));
		ispublic = xmldoc.GetChildValue("ispublic");
		openstatus = xmldoc.GetChildValue("openstatus");
		chatStatus = xmldoc.GetChildValue("chatStatus");

		auth = xmldoc.GetChildValue("auth");
		maxmic = xmldoc.GetChildValue("maxmic");
		roomsize = xmldoc.GetChildValue("roomsize");
		maxMicQueue = xmldoc.GetChildValue("maxMicQueue");
		maxMicQPerUser = xmldoc.GetChildValue("maxMicQPerUser");
		maxManager = xmldoc.GetChildValue("maxManager");
		if (xmldoc.FindElem("roomMgrs"))
		{
			xmldoc.IntoElem();

			uint32 uin = xmldoc.GetChildValue("mgr");
			while(uin)
			{
				roomMgr[uin] = 1;

				uin = xmldoc.GetChildValue("mgr");
			}
			xmldoc.OutOfElem();
		}

		idctype = xmldoc.GetChildValue("idctype");
		uSupportGts = xmldoc.GetChildValue("uSupportGts");
		pubText = xmldoc.GetChildValue("pubText");
		password = xmldoc.GetChildValue("password");
		micMaxTime = xmldoc.GetChildValue("micMaxTime");
		autoMgrForRicher = xmldoc.GetChildValue("autoMgrForRicher");
		enableColorBar = xmldoc.GetChildValue("enableColorBar");
		regionMaster = xmldoc.GetChildValue("areaMaster");

		if (xmldoc.FindElem("regionAssistant"))
		{
			xmldoc.IntoElem();

			for (uint8 i=0; i<MAX_ASSIST_USER_NUM; i++)
			{
				regionAssistant[i] = xmldoc.GetChildValue("regionast");
				if (!regionAssistant[i])
					break;
			}
			xmldoc.OutOfElem();
		}
		
		showEnterPic	= xmldoc.GetChildValue("showEnterPic");
		micMode			= xmldoc.GetChildValue("micMode");
		
	}
public:
	static std::string GetChildStrValue(CMarkup &xmlDoc, std::string key)
	{
		if (xmlDoc.FindElem( key.c_str() ))
		#if defined(MARKUP_STL)
			return xmlDoc.GetData();
		#else
			return (LPCTSTR)xmlDoc.GetData();
		#endif
		
		return "";
	}

	static int GetChildIntValue(CMarkup &xmlDoc, std::string key)
	{

		if (xmlDoc.FindElem( key.c_str() ))
		#if defined(MARKUP_STL)
			return atol(xmlDoc.GetData().c_str());
		#else
			return atol((LPCTSTR)xmlDoc.GetData());
		#endif

		return 0;
	}

};

struct ROOM_INFO
{
	string name;
	string descript;
	string passwd;
	uint8 member;
	uint32	manager;
	uint16	flag;
	uint32	validcode;						//房间验证码
	uint32  ownuin;
	uint8	permitknock;
	uint8	idauth;
};

struct ROOM_STATUS
{
	string name;
	string descript;
	uint16 maxUserNum;
	uint16 maxMicNum;
	uint16 textPort;
	uint16 audioPort;
	uint16 videoPort;
	uint16 flag;
	uint8  mediaflag ;
	uint8  audioquality ;						//音频质量
	uint8  videoquality ;						//视频质量
	uint8  estatus;                             //i-space状态拓展 add by xnh 20050307
	uint16 max_manager_num;
	uint16 max_member_num;
	uint16 max_deny_num;
	uint8 iSky;
};

typedef class MicerMediaStatusItem
{
public:
	uint8 lost;
	uint16 averageAckTime;
	uint32 mediaSvrIP;
	uint32 sendLostPacketCount;

	uint8 localrecvlost;//本地接收者收包率
	MicerMediaStatusItem()
	{
		this->lost = 0;
		this->averageAckTime = 0;
		this->mediaSvrIP = 0;
		this->localrecvlost = 0;
		sendLostPacketCount = 0;
	}
	MicerMediaStatusItem(const MicerMediaStatusItem& item)
	{
		this->lost = item.lost;
		this->averageAckTime = item.averageAckTime;
		this->mediaSvrIP = item.mediaSvrIP;
		this->localrecvlost = item.localrecvlost;
		sendLostPacketCount = item.sendLostPacketCount;
	}
	MicerMediaStatusItem& operator=(const MicerMediaStatusItem& item)
	{
		this->lost = item.lost;
		this->averageAckTime = item.averageAckTime;
		this->mediaSvrIP = item.mediaSvrIP;
		this->localrecvlost = item.localrecvlost;
		sendLostPacketCount = item.sendLostPacketCount;
		return *this;
	}

}MicerMediaStatusItem;




class ZZHistoryInfo
{
public:
	ZZHistoryInfo()	
	{
		lastRoundID = 1;

		memset(itemCount, 0, sizeof(itemCount));
	}

	uint32 lastRoundID;											//最后一局号

	uint16 itemCount[MAX_AWARD_ITEM_NUM];

	std::string BuildXMLInfo()
	{
		CMarkup xmldoc;
		xmldoc.AddElem("lastRoundID", lastRoundID);
		for (uint8 i=0; i<MAX_AWARD_ITEM_NUM; i++)
		{
			if (itemCount[i])
			{
				char buf[32] = {0};

				snprintf(buf, sizeof(buf)-1, "item%d", i);

				xmldoc.AddElem(buf, itemCount[i]);
			}
		}

#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}

	void ParseXML(std::string infoXml)
	{
		CMarkup xmldoc;
		xmldoc.SetDoc(infoXml.c_str());

		lastRoundID = RoomInfo::GetChildIntValue(xmldoc, "lastRoundID");
		for (uint8 i=0; i<MAX_AWARD_ITEM_NUM; i++)
		{
			char buf[32] = {0};

			snprintf(buf, sizeof(buf)-1, "item%d", i);

			itemCount[i] = RoomInfo::GetChildIntValue(xmldoc, buf);
		}

	}

};



class PacketCache
{
	#define MAX_CACHE_NUM 500
public:
	PacketCache()
	{
		memset(cacheArray, 0, sizeof(cacheArray));
		count = 0;
	}
	~PacketCache()
	{
		ClearPackets();
	}
	inline void PushPacket(UdpInPacket *in)
	{
		RtpHeader *hdr = (RtpHeader *)in->getcursor();
		if (cacheArray[hdr->seq])
		{
			delete cacheArray[hdr->seq];
			count--;
		}

		cacheArray[hdr->seq] = in;
		top.add(&in->Q_Item);
		count++;

		if (count > MAX_CACHE_NUM)
		{
			DelTimeoutPacket();
		}
	}
	inline UdpInPacket *GetCachePacket(uint16 seq)
	{
		return cacheArray[seq];
	}
	void ClearPackets()
	{
		while (!top.isEmpty())
		{
			UdpInPacket *p = LIST_ENTRY(top.next, UdpInPacket, Q_Item);

			RtpHeader *oldHdr = (RtpHeader *)p->getcursor();

			cacheArray[oldHdr->seq] = NULL;

			delete p;

			count--;
		}
		
		if (count != 0)
		{
			count = 0;
		}
	}
private:
	ListHead top;
	uint16 count;
	UdpInPacket *cacheArray[1 << 16];

	inline void DelTimeoutPacket(void)
	{
		if (!top.isEmpty())
		{
			UdpInPacket *p = LIST_ENTRY(top.next, UdpInPacket, Q_Item);

			RtpHeader *oldHdr = (RtpHeader *)p->getcursor();

			cacheArray[oldHdr->seq] = NULL;

			delete p;

			count--;
		}
		else if (count != 0)
		{
			count = 0;
		}
	}
};


class ZZSetting
{
public:

	ZZSetting()
	{
		betTime = 60;
		maxLoss	 = 0;
		memset(itemNum, 0, sizeof(itemNum));


		uint8 idx = 0;
		itemNum[idx++] = 8;
		itemNum[idx++] = 8;
		itemNum[idx++] = 9;
		itemNum[idx++] = 8;
		itemNum[idx++] = 8;
		itemNum[idx++] = 9;
		itemNum[idx++] = 8;
		itemNum[idx++] = 8;
		itemNum[idx++] = 2;
		idx+=4;
		itemNum[idx++] = 3;
		itemNum[idx++] = 4;
		itemNum[idx++] = 3;
		itemNum[idx++] = 3;
		itemNum[idx++] = 3;
		itemNum[idx++] = 3;
		itemNum[idx++] = 3;
		itemNum[idx++] = 2;
		itemNum[idx++] = 1;

		
	}
	ZZSetting(ZZSetting &s)
	{
		*this = s;
	}
	ZZSetting& operator=(const ZZSetting& item)
	{
		betTime		=   item.betTime;
		//smallItems	=   item.smallItems;
		//mediumItems	=	item.mediumItems;
		//largeItems	=   item.largeItems;
		//hugeItems	=   item.hugeItems;
		maxLoss		=	item.maxLoss;

		memcpy(itemNum, item.itemNum, sizeof(itemNum));

		return *this;
	}
	uint32 betTime;
	//uint32 smallItems;
	//uint32 mediumItems;
	//uint32 largeItems;
	//uint32 hugeItems;
	uint64 maxLoss;
	
	uint32 itemNum[MAX_AWARD_ITEM_NUM];
};

class Authrtity
{
public:
	Authrtity(){};
public:
	static uint32 GetData(uint32 n)
	{
		int table[]=
		{
			1, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,               
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,                
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,               
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,                
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,               
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,                
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,               
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,                
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,                
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,                
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 
		};
		unsigned char *p=(unsigned char *)&n;
		return table[*p]+table[*(p+1)]+table[*(p+2)]+table[*(p+3)];
	}
};

#define MAX_URL_LEN												256
#define MAX_RICHER												30
#define MAXDISCOUNT												100

typedef enum
{
	FUHAO_INDEX = 1,
	PRIVILEGES_INDEX,
	SALES_INDEX,
	BAND_INDEX,
	COO_INDEX,
	COO_ASSISTANT_INDEX,
	DANCING_INDEX,
	STAR_INDEX,
	STAFF_INDEX,
	SINGER_INDEX,
	AGENT_INDEX,
	COMPERE_INDEX,									//超级主持
	COMPEREMAN_INDEX,				//MC男主持
	PATROL_INDEX,					//巡查
	OPERATION_INDEX,					//运营
	BABY1_INDEX,						//宝贝1
	BABY2_INDEX,						//宝贝2
	BABY3_INDEX,						//宝贝3
	BABY4_INDEX,						//宝贝4
	BABY5_INDEX,						//宝贝5
	BABY6_INDEX,						//宝贝6
	INDEX_LIMIT,
}EnterIndex;



typedef struct EnterRoomMsgItem
{
	char enter_title[MAX_URL_LEN+1];
	char enter_pic[MAX_URL_LEN+1];
}EnterRoomMsgItem;
typedef std::map<uint32, EnterRoomMsgItem>	DiamondInfoMap;
class EnterRoom
{
public:
	enum
	{
		SIEGE_KING,
		SIEGE_QUEEN,

		SIEGE_LIMIT,
	};

	bool GetEnterInfoByType(uint8 gUserType, string& strEnterPic, string&  strEnterTitle)
	{
		switch(gUserType)
		{
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_FUHAO:
			{
				strEnterPic = type[FUHAO_INDEX].enter_pic;
				strEnterTitle = type[FUHAO_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES:
			{
				strEnterPic = type[PRIVILEGES_INDEX].enter_pic;
				strEnterTitle = type[PRIVILEGES_INDEX].enter_title;
				break;
			}
		case  CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES:
			{
				strEnterPic = type[SALES_INDEX].enter_pic;
				strEnterTitle = type[SALES_INDEX].enter_title;
				break;
			}
		case  CTaoleGlobleUserType::USER_GLOBLE_TYPE_MUSIC_SOCIETY:
			{
				strEnterPic = type[BAND_INDEX].enter_pic;
				strEnterTitle = type[BAND_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO:
			{
				strEnterPic = type[COO_INDEX].enter_pic;
				strEnterTitle = type[COO_INDEX].enter_title;
				break;

			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO_ASSISTANT:
			{
				strEnterPic = type[COO_ASSISTANT_INDEX].enter_pic;
				strEnterTitle = type[COO_ASSISTANT_INDEX].enter_title;
				break;
			}
		case  CTaoleGlobleUserType::USER_GLOBLE_TYPE_DANCER:
			{
				strEnterPic = type[DANCING_INDEX].enter_pic;
				strEnterTitle = type[DANCING_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_STAR:
			{
				strEnterPic = type[STAR_INDEX].enter_pic;
				strEnterTitle = type[STAR_INDEX].enter_title;
				break;

			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF:
			{
				strEnterPic = type[STAFF_INDEX].enter_pic;
				strEnterTitle = type[STAFF_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SINGER:
			{
				strEnterPic = type[SINGER_INDEX].enter_pic;
				strEnterTitle = type[SINGER_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_AGENT:
			{
				strEnterPic = type[AGENT_INDEX].enter_pic;
				strEnterTitle = type[AGENT_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY6:
			{
				strEnterPic = type[BABY6_INDEX].enter_pic;
				strEnterTitle = type[BABY6_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY5:
			{
				strEnterPic = type[BABY5_INDEX].enter_pic;
				strEnterTitle = type[BABY5_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY4:
			{
				strEnterPic = type[BABY4_INDEX].enter_pic;
				strEnterTitle = type[BABY4_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY3:
			{
				strEnterPic = type[BABY3_INDEX].enter_pic;
				strEnterTitle = type[BABY3_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY2:
			{
				strEnterPic = type[BABY2_INDEX].enter_pic;
				strEnterTitle = type[BABY2_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY1:
			{
				strEnterPic = type[BABY1_INDEX].enter_pic;
				strEnterTitle = type[BABY1_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_OPERATION:
			{
				strEnterPic = type[OPERATION_INDEX].enter_pic;
				strEnterTitle = type[OPERATION_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PATROL:
			{
				strEnterPic = type[PATROL_INDEX].enter_pic;
				strEnterTitle = type[PATROL_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPEREMAN:
			{
				strEnterPic = type[COMPEREMAN_INDEX].enter_pic;
				strEnterTitle = type[COMPEREMAN_INDEX].enter_title;
				break;
			}
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPERE:
			{
				strEnterPic = type[COMPERE_INDEX].enter_pic;
				strEnterTitle = type[COMPERE_INDEX].enter_title;
				break;
			}
		default:
			return false;
		}
		return true;
	}
	EnterRoom()
	{
// 		memset(vip, 0, sizeof(vip));
// 		memset(lorder, 0, sizeof(lorder));
// 		memset(richer, 0, sizeof(richer));
// 		memset(type, 0, sizeof(type));
// 		memset(siege, 0, sizeof(siege));
		ResetInfo();
		
	}
	void ResetInfo()
	{
		memset(vip, 0, sizeof(vip));
		memset(lorder, 0, sizeof(lorder));
		memset(richer, 0, sizeof(richer));
		memset(type, 0, sizeof(type));
		memset(siege, 0, sizeof(siege));
	}
	Mutex lock;

	EnterRoomMsgItem vip[VipLevel::LIMIT_VIP];
	EnterRoomMsgItem lorder[CTinyLordLevel::LORD_LEVEL_LIMIT];
	EnterRoomMsgItem richer[MAX_RICHER+1];
	EnterRoomMsgItem type[INDEX_LIMIT];
	EnterRoomMsgItem siege[SIEGE_LIMIT];
	DiamondInfoMap	 giftMap;
};

typedef class GlobalMsgInfo
{
public:
	uint16 discount;
	uint8  authrtity;
	GlobalMsgInfo()
	{
		discount = 0;
		authrtity = 0;
	}
}GlobalMsgInfo;

class AclCtrl
{
public:
	AclCtrl()
	{
		memset(beenManager, 0, sizeof(beenManager));
		memset(ranksetting, 0, sizeof(ranksetting));
		memset(maxTimes, 0 , sizeof(maxTimes));
	}
	bool IsManager(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner, uint8 srcRichOrder)
	{
		uint8 srcRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};

		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner, srcRichOrder,  srcRankLevel);

		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && beenManager[i])
			{
				return true;
			}
		}

		return false;
	}

	uint16 GetDisCount(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner, uint8 srcRichOrder)
	{
		uint8 srcRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};
		uint16 discount = MAXDISCOUNT + 1;
		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner, srcRichOrder,  srcRankLevel);
		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && globalMsg[i].authrtity)
			{
				discount = min(discount, globalMsg[i].discount);
			}
		}

		return discount;
	}





	uint32 GetMaxTimes(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner, uint8 srcRichOrder)
	{
		uint8 srcRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};
		uint32 max_times = 0;
		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner, srcRichOrder,  srcRankLevel);

		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && beenManager[i])
			{
				max_times = max(max_times, maxTimes[i]);
			}
		}

		return max_times;
	}

	void Set(uint8 rankIndex, char *rankSet, uint16 discount, uint8 authrtity, uint32 max_times)
	{
		if (rankIndex < CChatRankList::RANK_ROOM_LIMIT)
		{
			srcAclStr[rankIndex] = rankSet;
			uint8 canManage = 0;
			memset(ranksetting[rankIndex], 0, CChatRankList::RANK_ROOM_LIMIT);
			for(uint8 i=0; i<CChatRankList::RANK_ROOM_LIMIT && *rankSet; i++, rankSet++)
			{
				if (*rankSet != '0')
					canManage = ranksetting[rankIndex][i] = 1;
			}

			beenManager[rankIndex] = canManage;
			globalMsg[rankIndex].discount = discount;
			globalMsg[rankIndex].authrtity = authrtity;
			maxTimes[rankIndex] = max_times;
			
		}
	}

	bool Check(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner, uint8 srcRichOrder,
		uint8 dstLevel, uint8 dstUserType, uint8 dstLordLevel, uint32 dstManager, bool dstIsOwner, uint8 dstRichOrder, string &rankName)
	{
		uint8 srcRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};
		uint8 srcRankSetting[CChatRankList::RANK_ROOM_LIMIT] = {0};
		uint8 dstRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};

		bool canDoit = false;

		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner, srcRichOrder,  srcRankLevel);
		GetRankLevel(dstLevel, dstUserType, dstLordLevel, dstManager, dstIsOwner, dstRichOrder, dstRankLevel);

		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && beenManager[i])
			{
				for (uint8 j=CChatRankList::RANK_GENERAL; j<CChatRankList::RANK_ROOM_LIMIT; j++)
				{
					if (ranksetting[i][j])
					{
						srcRankSetting[j] = 1;
						canDoit = true;
					}
				}
			}
		}

		if (!canDoit)
			return false;


		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (dstRankLevel[i] && srcRankSetting[i] == 0)
			{
				rankName = CChatRankList::GetRankName(i);

				return false;
			}
		}

		return true;
	}
	
	string GetSrcAclStr(uint8 act)
	{
		if (act < CChatRankList::RANK_ROOM_LIMIT)
			return srcAclStr[act];
		else
			return "";
	}
private:
	uint8 beenManager[CChatRankList::RANK_ROOM_LIMIT];										//是否具备管理资格
	uint8 ranksetting[CChatRankList::RANK_ROOM_LIMIT][CChatRankList::RANK_ROOM_LIMIT];		//相应的管理权限
	string srcAclStr[CChatRankList::RANK_ROOM_LIMIT];
	GlobalMsgInfo globalMsg[CChatRankList::RANK_ROOM_LIMIT];
	uint32 maxTimes[CChatRankList::RANK_ROOM_LIMIT];

	void GetRankLevel(uint8 usrLevel, uint8 userType, uint8 lordLevel, uint32 managerLevel, bool isOwner, uint8 richOrder, uint8 *srcRank)
	{

		switch (richOrder)
		{
		case 1:
			srcRank[CChatRankList::RANK_ROOM_RICHER1] = 1;
			break;
		case 2:
			srcRank[CChatRankList::RANK_ROOM_RICHER2] = 1;
			break;
		case 3:
			srcRank[CChatRankList::RANK_ROOM_RICHER3] = 1;
			break;
		case 4:
			srcRank[CChatRankList::RANK_ROOM_RICHER4] = 1;
			break;
		case 5:
			srcRank[CChatRankList::RANK_ROOM_RICHER5] = 1;
			break;
		case 6:
			srcRank[CChatRankList::RANK_ROOM_RICHER6] = 1;
			break;
		case 7:
			srcRank[CChatRankList::RANK_ROOM_RICHER7] = 1;
			break;
		case 8:
			srcRank[CChatRankList::RANK_ROOM_RICHER8] = 1;
			break;
		case 9:
			srcRank[CChatRankList::RANK_ROOM_RICHER9] = 1;
			break;
		case 10:
			srcRank[CChatRankList::RANK_ROOM_RICHER10] = 1;
			break;
		}


		switch (usrLevel)
		{
		case VipLevel::JUNION_VIP:
			srcRank[CChatRankList::RANK_ROOM_JUNION_VIP] = 1;
			break;
		case VipLevel::MIDDLE_VIP:
			srcRank[CChatRankList::RANK_ROOM_MIDDLE_VIP] = 1;
			break;
		case VipLevel::HIGHER_VIP:
			srcRank[CChatRankList::RANK_ROOM_HIGHER_VIP] = 1;
			break;
		case VipLevel::GOLD_VIP:
			srcRank[CChatRankList::RANK_ROOM_GOLD_VIP] = 1;
			break;
		case VipLevel::DIAMOND_BLACK_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_BLACK_VIP] = 1;
			break;
		case VipLevel::DIAMOND_RED_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_RED_VIP] = 1;
			break;
		case VipLevel::DIAMOND_YELLOW_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_YELLOW_VIP] = 1;
			break;
		case VipLevel::DIAMOND_GREEN_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_GREEN_VIP] = 1;
			break;
		case VipLevel::DIAMOND_BLUE_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_BLUE_VIP] = 1;
			break;
		case VipLevel::DIAMOND_PINK_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_PINK_VIP] = 1;
			break;
		case VipLevel::DIAMOND_PURPLE_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_PURPLE_VIP] = 1;
			break;
		case VipLevel::DIAMOND_COLOUR_VIP:
			srcRank[CChatRankList::RANK_ROOM_DIAMOND_COLOUR_VIP] = 1;
			break;



		}

		switch (lordLevel)
		{
		case CTinyLordLevel::LORD_LEVEL_BARON:
			srcRank[CChatRankList::RANK_ROOM_LORD_BARON] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_VISCOUNT:
			srcRank[CChatRankList::RANK_ROOM_LORD_VISCOUNT] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_EARL:
			srcRank[CChatRankList::RANK_ROOM_LORD_EARL] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_MARQUESS:
			srcRank[CChatRankList::RANK_ROOM_LORD_MARQUESS] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_DUKE:
			srcRank[CChatRankList::RANK_ROOM_LORD_DUKE] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_KING:
			srcRank[CChatRankList::RANK_ROOM_LORD_KING] = 1;
			break;
		}

		switch (userType)
		{
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SINGER:
			srcRank[CChatRankList::RANK_ROOM_SINGER] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_AGENT:
			srcRank[CChatRankList::RANK_ROOM_AGENT] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF:
			srcRank[CChatRankList::RANK_ROOM_CONTACT_STAFF] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES:
			srcRank[CChatRankList::RANK_ROOM_SALES] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES:
			srcRank[CChatRankList::RANK_ROOM_PRIVILEGES] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO:		
			srcRank[CChatRankList::RANK_ROOM_COO] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO_ASSISTANT:		
			srcRank[CChatRankList::RANK_ROOM_COO_ASSISTANT] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_MUSIC_SOCIETY:		
			srcRank[CChatRankList::RANK_ROOM_MUSIC_SOCIETY] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_DANCER:		
			srcRank[CChatRankList::RANK_ROOM_DANCER] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_FUHAO:		
			srcRank[CChatRankList::RANK_ROOM_FUHAO] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_STAR:
			srcRank[CChatRankList::RANK_ROOM_STAR] = 1;
			break;
		}

		
		if (managerLevel & USER_RANK_ROOMMAN)
			srcRank[CChatRankList::RANK_ROOM_MANAGER] = 1;

		if (managerLevel & USER_RANK_ROOMOWNER)
		{
			if (isOwner)
				srcRank[CChatRankList::RANK_ROOM_OWNER] = 1;
			else
				srcRank[CChatRankList::RANK_ROOM_ASSISTANT] = 1;
		}

		if(managerLevel & USER_RANK_SUPERMAN)
			srcRank[CChatRankList::RANK_ROOM_SUPPER] = 1;
		
		if (managerLevel & USER_RANK_AREA_MASTER)
			srcRank[CChatRankList::RANK_ROOM_AREA_MASTER] = 1;
		
		if (managerLevel & USER_RANK_AREA_ASSISTANT)
			srcRank[CChatRankList::RANK_ROOM_AREA_ASSISTANT] = 1;

		if(managerLevel& USER_RANK_GUARD)
		{
			srcRank[CChatRankList::RANK_ROOM_GUARD] = 1;
		}

		if(managerLevel& USER_RANK_CARETAKER)
		{
			srcRank[CChatRankList::RANK_ROOM_CARETAKER] = 1;
		}


	
		for(uint8 i = CChatRankList::RANK_GENERAL; i < CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if(srcRank[i] == 1)
			{
				return;
			}
		}
		//普通用户
		srcRank[CChatRankList::RANK_GENERAL] = 1;

	}

	

};



class AclCtrlVip
{
public:
	AclCtrlVip()
	{
		memset(beenManager, 0, sizeof(beenManager));
		memset(ranksetting, 0, sizeof(ranksetting));
	}
	bool IsManager(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner)
	{
		uint8 srcRankLevel[CChatRankListVip::RANK_ROOM_LIMIT] = {0};

		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner,  srcRankLevel);

		for (uint8 i=CChatRankListVip::RANK_GENERAL; i<CChatRankListVip::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && beenManager[i])
			{
				return true;
			}
		}

		return false;
	}

	uint16 GetDisCount(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner, uint8 srcRichOrder)
	{
		uint8 srcRankLevel[CChatRankList::RANK_ROOM_LIMIT] = {0};
		uint16 discount = MAXDISCOUNT + 1;
		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner, srcRankLevel);
		for (uint8 i=CChatRankList::RANK_GENERAL; i<CChatRankList::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && globalMsg[i].authrtity)
			{
				discount = min(discount, globalMsg[i].discount);
			}
		}

		return discount;
	}





	void Set(uint8 rankIndex, char *rankSet, uint16 discount, uint8 authrtity)
	{
		if (rankIndex < CChatRankListVip::RANK_ROOM_LIMIT)
		{
			srcAclStr[rankIndex] = rankSet;
			uint8 canManage = 0;
			memset(ranksetting[rankIndex], 0, CChatRankListVip::RANK_ROOM_LIMIT);
			for(uint8 i=0; i<CChatRankListVip::RANK_ROOM_LIMIT && *rankSet; i++, rankSet++)
			{
				if (*rankSet != '0')
					canManage = ranksetting[rankIndex][i] = 1;
			}

			beenManager[rankIndex] = canManage;
			globalMsg[rankIndex].discount = discount;
			globalMsg[rankIndex].authrtity = authrtity;
		

		}
	}

	bool Check(uint8 srcLevel, uint8 srcUserType, uint8 srcLordLevel, uint32 srcManager, bool srcIsOwner,
		uint8 dstLevel, uint8 dstUserType, uint8 dstLordLevel, uint32 dstManager, bool dstIsOwner)
	{
		uint8 srcRankLevel[CChatRankListVip::RANK_ROOM_LIMIT] = {0};
		uint8 srcRankSetting[CChatRankListVip::RANK_ROOM_LIMIT] = {0};
		uint8 dstRankLevel[CChatRankListVip::RANK_ROOM_LIMIT] = {0};

		bool canDoit = false;

		GetRankLevel(srcLevel, srcUserType, srcLordLevel, srcManager, srcIsOwner,  srcRankLevel);
		GetRankLevel(dstLevel, dstUserType, dstLordLevel, dstManager, dstIsOwner, dstRankLevel);

		for (uint8 i=CChatRankListVip::RANK_GENERAL; i<CChatRankListVip::RANK_ROOM_LIMIT; i++)
		{
			if (srcRankLevel[i] && beenManager[i])
			{
				for (uint8 j=CChatRankListVip::RANK_GENERAL; j<CChatRankListVip::RANK_ROOM_LIMIT; j++)
				{
					if (ranksetting[i][j])
					{
						srcRankSetting[j] = 1;
						canDoit = true;
					}
				}
			}
		}

		if (!canDoit)
			return false;


		for (uint8 i=CChatRankListVip::RANK_GENERAL; i<CChatRankListVip::RANK_ROOM_LIMIT; i++)
		{
			if (dstRankLevel[i] && srcRankSetting[i] == 0)
			{
				//rankName = CChatRankListVip::GetRankName(i);

				return false;
			}
		}

		return true;
	}

	string GetSrcAclStr(uint8 act)
	{
		if (act < CChatRankListVip::RANK_ROOM_LIMIT)
			return srcAclStr[act];
		else
			return "";
	}
private:
	uint8 beenManager[CChatRankListVip::RANK_ROOM_LIMIT];										//是否具备管理资格
	uint8 ranksetting[CChatRankListVip::RANK_ROOM_LIMIT][CChatRankListVip::RANK_ROOM_LIMIT];		//相应的管理权限
	string srcAclStr[CChatRankListVip::RANK_ROOM_LIMIT];
	GlobalMsgInfo globalMsg[CChatRankList::RANK_ROOM_LIMIT];


	void GetRankLevel(uint8 usrLevel, uint8 userType, uint8 lordLevel, uint32 managerLevel, bool isOwner, uint8 *srcRank)
	{

		
		switch (usrLevel)
		{
		case VipLevel::JUNION_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_JUNION_VIP] = 1;
			break;
		case VipLevel::MIDDLE_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_MIDDLE_VIP] = 1;
			break;
		case VipLevel::HIGHER_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_HIGHER_VIP] = 1;
			break;
		case VipLevel::GOLD_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_GOLD_VIP] = 1;
			break;
		case VipLevel::DIAMOND_BLACK_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_BLACK_VIP] = 1;
			break;
		case VipLevel::DIAMOND_RED_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_RED_VIP] = 1;
			break;
		case VipLevel::DIAMOND_YELLOW_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_YELLOW_VIP] = 1;
			break;
		case VipLevel::DIAMOND_GREEN_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_GREEN_VIP] = 1;
			break;
		case VipLevel::DIAMOND_BLUE_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_BLUE_VIP] = 1;
			break;
		case VipLevel::DIAMOND_PINK_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_PINK_VIP] = 1;
			break;
		case VipLevel::DIAMOND_PURPLE_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_PURPLE_VIP] = 1;
			break;
		case VipLevel::DIAMOND_COLOUR_VIP:
			srcRank[CChatRankListVip::RANK_ROOM_DIAMOND_COLOUR_VIP] = 1;
			break;

		}

		switch (lordLevel)
		{
		case CTinyLordLevel::LORD_LEVEL_BARON:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_BARON] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_VISCOUNT:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_VISCOUNT] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_EARL:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_EARL] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_MARQUESS:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_MARQUESS] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_DUKE:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_DUKE] = 1;
			break;
		case CTinyLordLevel::LORD_LEVEL_KING:
			srcRank[CChatRankListVip::RANK_ROOM_LORD_KING] = 1;
			break;
		}

		switch (userType)
		{
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF:
			srcRank[CChatRankListVip::RANK_ROOM_CONTACT_STAFF] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES:
			srcRank[CChatRankListVip::RANK_ROOM_PRIVILEGES] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO:		
			srcRank[CChatRankListVip::RANK_ROOM_COO] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO_ASSISTANT:		
			srcRank[CChatRankListVip::RANK_ROOM_COO_ASSISTANT] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPERE:		
			srcRank[CChatRankListVip::RANK_ROOM_COMPERE] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPEREMAN:		
			srcRank[CChatRankListVip::RANK_ROOM_COMPEREMAN] = 1;
			break;
		
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PATROL:		
			srcRank[CChatRankListVip::RANK_ROOM_PATROL] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_OPERATION:		
			srcRank[CChatRankListVip::RANK_ROOM_OPERATION] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY1:		
			srcRank[CChatRankListVip::RANK_ROOM_BABY1] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY2:		
			srcRank[CChatRankListVip::RANK_ROOM_BABY2] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY3:		
			srcRank[CChatRankListVip::RANK_ROOM_BABY3] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY4:		
			srcRank[CChatRankListVip::RANK_ROOM_BABY4] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY5:		
			srcRank[CChatRankListVip::RANK_ROOM_BABY5] = 1;
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY6:
			srcRank[CChatRankListVip::RANK_ROOM_BABY6] = 1;
			break;
			
		}
			

		if (managerLevel & USER_RANK_ROOMMAN)
			srcRank[CChatRankListVip::RANK_ROOM_MANAGER] = 1;

		if (managerLevel & USER_RANK_ROOMOWNER)
		{
			if (isOwner)
				srcRank[CChatRankListVip::RANK_ROOM_OWNER] = 1;
			else
				srcRank[CChatRankListVip::RANK_ROOM_ASSISTANT] = 1;
		}

		if(managerLevel & USER_RANK_SUPERMAN)
			srcRank[CChatRankListVip::RANK_ROOM_SUPPER] = 1;

		if (managerLevel & USER_RANK_CASTELLAN)
			srcRank[CChatRankListVip::RANK_ROOM_CASTEALLAN] = 1;

		if (managerLevel & USER_RANK_CASTELLAN_MRS)
			srcRank[CChatRankListVip::RANK_ROOM_CASTEALLAN_MRS] = 1;

		if (managerLevel & USER_RANK_CARETAKER)
			srcRank[CChatRankListVip::RANK_ROOM_CARETAKER] = 1;

		for(uint8 i = CChatRankListVip::RANK_GENERAL; i < CChatRankListVip::RANK_ROOM_LIMIT; i++)
		{
			if(srcRank[i] == 1)
			{
				return;
			}
		}
		//普通用户
		srcRank[CChatRankListVip::RANK_GENERAL] = 1;

	}



};

typedef struct PrizeItem
{
	uint32 upValue;												//中奖倍数
	uint32 num;													//中奖倍数对应数量
}PrizeItem;


typedef std::vector<PrizeItem> PrizeList;

class PrizeRatioCtrl
{
private:
	enum
	{
		RATIO_SEED = 9999,
		RATIO_BIGNUM = 3000,
	};
public:
	PrizeRatioCtrl()
	{
		seedValue = 0;
		srand((unsigned int)time(NULL) * (unsigned int)time(NULL));
	}

	//设置中奖倍数(金额)及个数
	void SetNewSeed(uint32 upValue, uint16 number)
	{
		UinMap32::iterator it = prizeSeed.find(upValue);
		if (it != prizeSeed.end())
			it->second = number;
		else
			prizeSeed[upValue] = number;
	}

	void SetSeedValue(uint16 seedV, uint8 poolRatio)
	{
		//if (prizeSeed.size() == 0)
		//	return;

		//uint32 upCount = 0;
		//for (UinMap32::iterator it = prizeSeed.begin(); it != prizeSeed.end(); it++)
		//{
		//	upCount += it->second * it->first;
		//}
 
		//if (upCount > 10000)
		//	seedValue = 0;

		//else if (upCount / 10000 * seedV > poolRatio * RATIO_SEED / 100)
		//{
		//	
		//}


		seedValue = seedV;
	}

	void ReSetPoolValue(uint64 poolSizeValue)
	{
		poolSize = poolSizeValue;
	}

	unsigned int GetPrize(unsigned int v, short upSeed, short richRatio)
	{
		if (seedValue == 0)
			return 0;

		if (upSeed > 400)//调整增大上限
			upSeed = 400;

		InitRatioList();
		

		int currSeed = seedValue + upSeed;
		if (currSeed < 0)
			currSeed = 50;
		currSeed = currSeed * richRatio/100;
		uint32 sed = rand32() % RATIO_SEED;

		srand(sed * (uint32)time(NULL));
		
		if (sed < uint32(currSeed))
		{
			uint32 ret = ratioList[0];

			if (ret * v * 2 > poolSize)
			{
				LOG(1)("ET too large prize = %d\n", ratioList[0]);
				return 0;
			}
			
			ratioList.erase(ratioList.begin());

			return ret;
		}

		return 0;
	}

private:
	UinMap32 prizeSeed;
	uint16 seedValue;

	uint64 poolSize;

	std::vector<uint32> ratioList;


	void InitRatioList()
	{		
		if (ratioList.size())
			return;

		std::vector<uint32> tempList;

		for (UinMap32::iterator it = prizeSeed.begin(); it != prizeSeed.end(); it++)
		{
			uint32 count = it->second;
			uint32 upValue = it->first;
			for (uint32 i=0; i<count; i++)
				tempList.push_back(upValue);

		}
		
		while(tempList.size())
		{
			int idx = rand() % tempList.size();
			ratioList.push_back(tempList[idx]);

			tempList.erase(tempList.begin()+idx);
		}

	}

	inline uint32 rand32()
	{
		return ((rand() << 15) | (rand() & 0x7fff));
	}
};


struct GiftItemBase
{
	uint32	giftID;												//礼物id
	uint64	price;												//价格
	uint8	giftKind;											//是否是幸运礼物,0普通礼物,1幸运礼物,2点歌礼物
	uint8	status;
};

class GiftItemInfo
{
public:
	GiftItemInfo(uint64 p, uint8 g = 0)
	{
		price = p;
		giftKind = g;
		giftRate = 500;
		hostRate = 0;
		compRate = 0;
		sendExp = 0;
		recvExp = 0;


	}

	bool operator != (const GiftItemInfo &u)
	{
		return (price != price || giftKind != u.giftKind || giftName != u.giftName
			|| giftUrl != u.giftUrl || status != u.status || giftRate != u.giftRate|| 
			compRate != u.compRate ||hostRate!=u.hostRate || sendExp != u.sendExp || recvExp != u.recvExp);
	}
	uint32	giftID;												//礼物id
	uint64	price;												//价格
	uint8	giftKind;											//是否是幸运礼物,0普通礼物,1幸运礼物,2点歌礼物
	string	giftName;											//礼物名称
	string	giftUrl;											//礼物图片地址
	uint8	status;												//是否启用
	uint32	giftRate;											//收礼所得比例
	uint32  hostRate;											//室主比例
	uint32  compRate;											//公司比例
	uint32  sendExp;											//送礼经验
	uint32	recvExp;											//收礼经验
};
class RedPaperInfo
{
public:
	RedPaperInfo()
	{
		redPaperId	= 0;												//红包ID
		uin			= 0;														//红包发放者	
		money		= 0;													//总钱数
		totalNum	= 0;												//红包总数
		endTime		= 0;												//发放时间
		msg			= "";
		srcNick		= "";
		srcFace		= 0;
	}	
	uint32 redPaperId;												//红包ID
	uint32 uin;														//红包发放者	
	uint64 money;													//总钱数
	int  totalNum;												//红包总数
	time_t endTime;												//发放时间
	string msg;														//问候语
	string srcNick;
	uint16 srcFace;
};
class StampInfo
{
public:
	StampInfo(uint32 p = 0)
	{
		stamp_price = p;
	}
	uint32 stamp_id;	
	uint32 stamp_time;											//盖章的有效时间，单位分钟
	uint32 stamp_price;
	string stampMsg;
	uint32 srcuin;
};

class ChatRoomGlobalMsg
{
public:
	ChatRoomGlobalMsg()
	{
		uin	=	0;
		roomid	=	0;
		color	= 0;
		isbold	= false;
		isitalic	=	false;
		actionType	= 0;
		fontsize	=	0;
		showOnTopPlace = 0;
	}
	uint32 uin;
	string nickname;
	uint32 roomid;
	uint32 color;
	uint8  isbold;
	uint8  isitalic;
	uint8 actionType;
	uint32 fontsize;
	string msgText;
	uint8 showOnTopPlace;

	template <class T>
		void BuildPacket(T &out)
	{
		out << uin << nickname << roomid << color << actionType << isbold << isitalic <<fontsize<< msgText << showOnTopPlace;
	}

	template <class T>
		void ParsePacket(T &in)
	{
		in >> uin >> nickname >> roomid >> color >> actionType >> isbold >> isitalic >>fontsize>> msgText >> showOnTopPlace;
	}

	void ParseXML(std::string xmlStr)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(xmlStr.c_str());

		xmldoc.GetChildValue("uin", uin);
		xmldoc.GetChildValue("nick", nickname);
		xmldoc.GetChildValue("roomid", roomid);
		xmldoc.GetChildValue("color", color);
		xmldoc.GetChildValue("isbold", isbold);
		xmldoc.GetChildValue("isitalic", isitalic);
		xmldoc.GetChildValue("actionType", actionType);
		xmldoc.GetChildValue("fontsize", fontsize);
		xmldoc.GetChildValue("msg", msgText);
		xmldoc.GetChildValue("showOnTopPlace", showOnTopPlace);
	}

	std::string BuildXMLInfo()
	{
		CMarkup xmldoc;
		xmldoc.AddElem("uin", uin);
		xmldoc.AddElem("nick", nickname.c_str());
		xmldoc.AddElem("roomid", roomid);
		xmldoc.AddElem("color", color);
		xmldoc.AddElem("isbold", isbold);
		xmldoc.AddElem("isitalic", isitalic);
		xmldoc.AddElem("actionType", actionType);
		xmldoc.AddElem("fontsize", fontsize);
		xmldoc.AddElem("msg", msgText.c_str());
		xmldoc.AddElem("showOnTopPlace", showOnTopPlace);


#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}
};

#pragma pack(1)
union Rebate
{
	Rebate()
	{
		m_rebate = 0;
	}
	struct
	{
		uint8	m_normal_rebateRatio;									//普通礼物站内返点
		uint8	m_prize_rebate_ratio;									//幸运礼物站内返点
	};
	uint16 m_rebate;													//站内返点
};
#pragma pack()

typedef std::map<uint16, Rebate> RebateMap;


#endif

