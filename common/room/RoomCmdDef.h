#ifndef ROOM_CMD_DEF_KDLFJSDLFJSDLFJDSF
#define ROOM_CMD_DEF_KDLFJSDLFJSDLFJDSF

enum 
{
	IM_CHAT_VER1		=	0,
	IM_CHAT_VER2		=	1,
	IM_CHAT_VER3		=	2,
	IM_CHAT_VER4		=	3,
	IM_CHAT_VER5		=   4,
	IM_CHAT_VER6		=	6,
	IM_CHAT_VER7		=   7,
	IM_CHAT_VER8		=   8,
	IM_CHAT_VER9		=   9,
	IM_CHAT_VER10		=   10,
	IM_CHAT_VER11		=   11,
	IM_CHAT_VER12		=   12,						//协议增加了爵位等,
	IM_CHAT_VER13		=	13,						//麦序调整增加了操作人,改进中奖提示
	IM_CHAT_VER14		=	14,						//换成新媒体服务器，只下发媒体分析网关
	IM_CHAT_VER15		=	15,						//进房间下发在麦信息时带上麦时,用户列表不再带用户麦信息
	IM_CHAT_VER16		=	16,						//进房间点歌礼物
	IM_CHAT_VER17		=   17,						//增加印章功能
	IM_CHAT_VER18		=   18,						//增加免费开箱次数
	IM_CHAT_VER19		=	19,						//增加钻石会员等新的身份  2013-09-28
	IM_CHAT_VER20		=   20,						//增加聊天游戏
	IM_CHAT_VER21		=   21,						//增加登录密码des校验
	IM_CHAT_VER22		=   22,						//调整上麦奖励
	IM_CHAT_VER23		=   23,						//用户列表增加设备类型字段，禁言剩余时间字段
	IM_CHAT_VER24		=   24,						//聊天增加收费表情
	IM_CHAT_VER25		=	25,                     //下发新礼物版本号：与老的区分
	IM_CHAT_VER26		=   26,						//修改全量麦序协议以兼容 新老点歌礼物麦序中的显示
	IM_CHAT_VER27		=	27,						//麦上信息增加nick
	IM_CHAT_VER28		=	28,						//房间信息增加最大麦时
	IM_CHAT_VER30		=	30,						//登录返回增加mic限制字段
	IM_CHAT_VER31		=	31,						//登录返回增加私麦开关
	IM_CHAT_VER32		=	32,						//礼物相关接口调整为uint64
	IM_CHAT_VER33		=	33,
	IM_CHAT_VER34		=	34,						//增加活动身份
	IM_CHAT_VER35		=	35,						//修复rank为uint16字段
	IM_CHAT_VER36		=	36,						//身份兼容
	IM_CHAT_VER37		=   37,						//红包列表兼容
	IM_CHAT_VER38		=   38,						//rank uint32
	IM_CHAT_VER40		=	40,						//皮肤信息 客户端版本
	IM_CHAT_VER41		=	41,						//送礼上私麦带礼物ID，红包改为uint64，增加坐骑，下发多个配车的数组
	IM_CHAT_VER_CURR	=	IM_CHAT_VER38,			
	
	IM_CHAT_VERPROT		=	100,
	//IM_CHAT_VER_CURR	=	IM_CHAT_VER16, 
	IM_PPC_PROTO		=	200,					//ppc使用proto版本号
};

class CChatMsgType
{
public:
	 enum ChatMsgType
	{
		ChatUinMsg,
		SystemMsg,
		ImportMsg,
		SystemUinMsg,
		UnitMsg,
		GiftChatUinMsg,
		ShowGiftName,
		ShowGift,
		PromptMsg ,
		BroadMsg,
		VipEnterMsg,
		WinPrizeMsg,
		ShowReceviedGift,
		ShowColorTip,
		ColorTip,
		Msg_Auto_Reply,//自动回复的消息
		ShowHtmlMsg,
		GneralMsg, //
		SystemWarmPromptMsg,
		ExpressionMsg,
	};
};


//聊天游戏
class CChatGameType
{
public:
	enum ChatMsgType
	{
		ChatDicing,		//掷骰子
	};
};


class RoomInfoItemStr
{
public:
	static std::string CHAT_PRIVATE_ACCESS;							//私聊属性修改
	static std::string CHAT_PUBLIC_ACCESS;							//公聊属性修改
};



typedef enum RoomType
{
	IMROOM_TYPE_SMALL			= 1,							//Ｐ２Ｐ中转小房间
	IMROOM_TYPE_BIG				= 2,							//音视频中转大房间
	IMROOM_TYPE_GAME_STAR		= 3,							//转转
	IMROOM_TYPE_GAME_POKER		= 4,							//
	IMROOM_TYPE_GAME_POKER_100	= 5,
	IMROOM_TYPE_BIG_3			= 6,                            //1大2小视频
	IMROOM_TYPE_BIG_3_SH		= 7,                            //3小横视频
	IMROOM_TYPE_BIG_3_SV		= 8,							//3小竖视频
	IMROOM_TYPE_BIG_3_F			= 9,							//2大一浮动视频
	IMROOM_TYPE_BIG_3_NEW		= 10,                           //新开视频房间
	IMROOM_TYPE_GAME_BOX		= 11,							//开宝箱游戏
	IMROOM_TYPE_GAME_RICHMAN	= 12,							//大富翁
	IMROOM_TYPE_BIG_UC			= 13,
	IMROOM_TYPE_BIG_BIGONE		= 21,							//单视屏
	IMROOM_TYPE_ANCHOR			= 22,							//主播房间
	IMROOM_TYPE_GUAGUA			= 23,							//呱呱房间类型
	IMROOM_TYPE_GAME_COC        = 26,                           // COC游戏
	IMROOM_TYPE_GAME_NEW_POKER  = 27,                           // 新版车行
	IMROOM_TYPE_GAME_REDPACKETS = 28,							//红包游戏
	IMROOM_TYPE_DIAMOND			= 29,							//钻石守护主播房间

	//新加游戏roomtype范围定义为100-200
	IMROOM_TYPE_GAME_BASE       = 100,
	IMROOM_TYPE_GAME_MAX        = 200,
}RoomType;

//日志采集
typedef enum EventID 
{
	//房间内部事件
	EV_LOGIN_ROOM = 0x100, //登录房间
	EV_LOGOUT_ROOM,      //退出房间
	EV_BIND_MIC,		 //上麦
	EV_UNBIND_MIC,       //下麦
	EV_BIND_PRIVATE_MIC,//上私卖
	EV_UNBIND_PRIVATE_MIC,//下私卖
	EV_MIC_PRSENTR,       //发上麦奖励
	EV_SENDGIT,          // 刷花送礼
	EV_DIG_GEM,          //挖宝
	EV_PRINT_GIFT_PRIZE_POOL,//刷花奖池
	EV_PRINT_GEM_POOL,//挖宝奖池
	//DB返回事件
	EV_LOGIN_ROOM_DB_RES = 0x200,
}EventID;
typedef enum KickOutType
{
	ROOM_KICKTYPE_KICKOUT		= 0,							//踢出去
	ROOM_KICKTYPE_PUSHOUT,										//挤出去的
	ROOM_KICKTYPE_SVR_RELOGIN,									//房间信息发生变化，客户端需要退出重进。
	ROOM_KICKTYPE_ONLY_ALLOW_VIP,								//试用期已过，只允许VIP用户继续使用
	ROOM_KICKTYPE_ADDPID_BLACK,									//加入站点黑名单	
	ROOM_KICKTYPE_FORCE_VIEWEND,								//强制结束直播
	ROOM_KICKTYPE_KICKOUT_TABLE,								//踢出当前桌
	ROOM_KICKTYPE_NOENOUGH_MONEY,								//余额不足
	ROOM_KICKTYPE_UPPER_TODAYLIMIT,								//达到车行当天被踢出上限
	ROOM_KICKTYPE_NOBET_TIMES,									//该用户被限制，达到连续没下注次数

}KickOutType;

typedef enum RoomAuth
{
	ROOM_AUTH_ALLOW_ALL = 0,									//允许所有人进入
	ROOM_AUTH_ALLOW_AUTH,										//密码访问
}RoomAuth;

enum
{
	AWARD_STATUS_STOP,
	AWARD_STATUS_BETTING,										//下注时间
	AWARD_STATUS_WAITING,										//确认下注，
	AWARD_STATUS_AWARDING,										//等待开奖时间
	AWARD_STATUS_AWARDED,										//开奖
	AWARD_STATUS_AWARD_WAIT,									//迟缓发奖
};



enum
{
	REDPACKETS_STOP,		//停止状态
	REDPACKETS_WAIT,		//等待状态
	REDPACKETS_RUN,			//游戏状态
	REDPACKETS_END,			//本轮结束下轮开始状态
};

enum
{
	REDPACKETS_SUCCESS,			//抢，发红包成功
	ROB_REDPACKETS_REPEAT,		//已经抢过红包
	ROB_REDPACKETS_NOTENOUGH,	//红包已经抢完
	ROB_REDPACKETS_EXPIRE,		//红包已经过期
	ROB_REDPACKETS_FAILED,		//抢红包失败
	SEND_REDPACKETS_FILED,		//发送红包失败
	SEND_NOTENOUGH_UIN,			//没有足够的人
	SEND_STATE_ERR,				//没有到发送红包的状态
	SEND_UIN_ERR,				//此轮不属于当前用户发送红包
	MONEY_LOCKED,				//金币被游戏锁定
	RED_CLOSED,					//游戏关闭
};

enum
{
	PPC_STOP,												//停止状态
	PPC_FREE,												//空闲时间
	PPC_BETTING,											//碰碰车下注时间
	PPC_WAIT,												//等待时间
	PPC_CARRUN,												//碰碰车开转
	PPC_END,												//此局结束

};
class LimitEnterRoom
{
public:
	enum LimitList
	{
		LIMIT_ROOM_VISISTOR,									//普通游客
		LIMIT_ROOM_JUNION_VIP,									//初会
		LIMIT_ROOM_MIDDLE_VIP,									//中会
		LIMIT_ROOM_HIGHER_VIP,									//高会
		LIMIT_ROOM_GOLD_VIP,									//白金会员
		LIMIT_ROOM_LORD,										//爵位
		LIMIT_ROOM_RICHER,										//大款
		LIMIT_ROOM_SINGER,										//艺人
		LIMIT_ROOM_AGENT,										//代理
		LIMIT_ROOM_SALES,										//商务
		LIMTI_ROOM_STAFF,										//客服
		LIMIT_ROOM_PRIVILEGES,									//特权
		LIMIT_ROOM_COO,											//站长
		LIMIT_ROOM_COO_ASSISTANT,								//副站长
		LIMIT_ROOM_MUSIC_SOCIETY,								//乐团
		LIMIT_ROOM_DANCER,										//舞星
		LIMIT_ROOM_FUHAO,										//富豪
		LIMIT_ROOM_STAR,										//明星
		LIMIT_ROOM_DIAMOND_BLACK_VIP,							//黑钻VIP
		LIMIT_ROOM_DIAMOND_RED_VIP,								//红钻VIP
		LIMIT_ROOM_DIAMOND_YELLOW_VIP,							//黄钻VIP
		LIMIT_ROOM_DIAMOND_GREEN_VIP,							//绿钻VIP
		LIMIT_ROOM_DIAMOND_BLUE_VIP,							//蓝钻VIP
		LIMIT_ROOM_DIAMOND_PINK_VIP,							//粉钻VIP
		LIMIT_ROOM_DIAMOND_PURPLE_VIP,							//紫钻VIP 
		LIMIT_ROOM_DIAMOND_COLOUR_VIP,							//彩钻VIP
		LIMIT_ROOM_LIMIT,
	};
};




class CChatRankList
{
public:
	enum RankList
	{
		RANK_GENERAL,											//普通用户
		RANK_ROOM_JUNION_VIP,									//低会	
		RANK_ROOM_MIDDLE_VIP,									//中会
		RANK_ROOM_HIGHER_VIP,									//高会
		RANK_ROOM_GOLD_VIP,										//钻会
		RANK_ROOM_LORD_BARON,									//男爵
		RANK_ROOM_LORD_VISCOUNT,								//子爵
		RANK_ROOM_LORD_EARL,									//伯爵
		RANK_ROOM_LORD_MARQUESS,								//侯爵
		RANK_ROOM_LORD_DUKE,									//公爵
		RANK_ROOM_LORD_KING,									//国王
		RANK_ROOM_MANAGER,										//房间管理
		RANK_ROOM_ASSISTANT,									//副室
		RANK_ROOM_OWNER,										//室主
		RANK_ROOM_SUPPER,										//超管
		RANK_ROOM_SINGER,										//艺人
		RANK_ROOM_AGENT,										//代理
		RANK_ROOM_CONTACT_STAFF,								//客服
		RANK_ROOM_SALES,										//商务
		RANK_ROOM_PRIVILEGES,									//特权
		RANK_ROOM_COO,											//站长
		RANK_ROOM_RICHER1,										//消费之星第1名
		RANK_ROOM_RICHER2,										//消费之星第2名
		RANK_ROOM_RICHER3,										//消费之星第3名
		RANK_ROOM_RICHER4,										//消费之星第4名
		RANK_ROOM_RICHER5,										//消费之星第5名
		RANK_ROOM_RICHER6,										//消费之星第6名
		RANK_ROOM_RICHER7,										//消费之星第7名
		RANK_ROOM_RICHER8,										//消费之星第8名
		RANK_ROOM_RICHER9,										//消费之星第9名
		RANK_ROOM_RICHER10,										//消费之星第10名
		RANK_ROOM_AREA_MASTER,									//区长
		RANK_ROOM_AREA_ASSISTANT,								//区长助理，副区
		RANK_ROOM_COO_ASSISTANT,								//助理站长
		RANK_ROOM_MUSIC_SOCIETY,								//乐团
		RANK_ROOM_DANCER,										//舞蹈演员
		RANK_ROOM_FUHAO,										//豪字标志
		RANK_ROOM_STAR,											//星级艺人
		RANK_ROOM_DIAMOND_BLACK_VIP,							//黑钻VIP
		RANK_ROOM_DIAMOND_RED_VIP,								//红钻VIP
		RANK_ROOM_DIAMOND_YELLOW_VIP,							//黄钻VIP
		RANK_ROOM_DIAMOND_GREEN_VIP,							//绿钻VIP
		RANK_ROOM_DIAMOND_BLUE_VIP,								//蓝钻VIP
		RANK_ROOM_DIAMOND_PINK_VIP,								//粉钻VIP
		RANK_ROOM_DIAMOND_PURPLE_VIP,							//紫钻VIP
		RANK_ROOM_DIAMOND_COLOUR_VIP,							//彩钻VIP
		RANK_ROOM_GUARD,										//守护
		RANK_ROOM_CARETAKER,									//临管
		RANK_ROOM_LIMIT,
	};

	static std::string GetRankName(uint8 usertype)
	{
		std::string rankStr = "";
		switch (usertype)
		{
		case CChatRankList::RANK_GENERAL:		
			rankStr="普通用户";
			break;
		case CChatRankList::RANK_ROOM_JUNION_VIP:				//低会	
			rankStr="初级会员";
			break;
		case CChatRankList::RANK_ROOM_MIDDLE_VIP:				//中会
			rankStr="中级会员";
			break;
		case CChatRankList::RANK_ROOM_HIGHER_VIP:				//高会
			rankStr="高级会员";
			break;
		case CChatRankList::RANK_ROOM_GOLD_VIP:					//钻会
			rankStr="白金会员";
			break;
		case CChatRankList::RANK_ROOM_LORD_BARON:				//男爵
			rankStr="男爵";
			break;
		case CChatRankList::RANK_ROOM_LORD_VISCOUNT:			//子爵
			rankStr="子爵";
			break;
		case CChatRankList::RANK_ROOM_LORD_EARL:				//伯爵
			rankStr="伯爵";
			break;
		case CChatRankList::RANK_ROOM_LORD_MARQUESS:			//侯爵
			rankStr="侯爵";
			break;
		case CChatRankList::RANK_ROOM_LORD_DUKE:				//公爵
			rankStr="公爵";
			break;
		case CChatRankList::RANK_ROOM_LORD_KING:				//国王
			rankStr="国王";
			break;
		case CChatRankList::RANK_ROOM_MANAGER:					//房间管理
			rankStr="房间管理";
			break;
		case CChatRankList::RANK_ROOM_ASSISTANT:				//副室
			rankStr="副室";
			break;
		case CChatRankList::RANK_ROOM_OWNER:					//室主
			rankStr="室主";
			break;
		case CChatRankList::RANK_ROOM_SUPPER:					//超管
			rankStr="超管";
			break;
		case CChatRankList::RANK_ROOM_SINGER:					//艺人
			rankStr="艺人";
			break;
		case CChatRankList::RANK_ROOM_AGENT:					//代理
			rankStr="代理";
			break;
		case CChatRankList::RANK_ROOM_CONTACT_STAFF:			//客服
			rankStr="客服";
			break;
		case CChatRankList::RANK_ROOM_SALES:					//商务
			rankStr="商务代表";
			break;
		case CChatRankList::RANK_ROOM_PRIVILEGES:				//特权
			rankStr="特权";
			break;
		case CChatRankList::RANK_ROOM_COO:						//站长
			rankStr="站长";
			break;
		case CChatRankList::RANK_ROOM_RICHER1:					//消费之星第1名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER2:					//消费之星第2名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER3:					//消费之星第3名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER4:					//消费之星第4名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER5:					//消费之星第5名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER6:					//消费之星第6名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER7:					//消费之星第7名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER8:					//消费之星第8名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER9:					//消费之星第9名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_RICHER10:					//消费之星第10名
			rankStr="消费之星";
			break;
		case CChatRankList::RANK_ROOM_AREA_MASTER:				//区长
			rankStr="区长";
			break;
		case CChatRankList::RANK_ROOM_AREA_ASSISTANT:			//区长助理，副区
			rankStr="副区长";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_BLACK_VIP:		//黑钻VIP
			rankStr="黑钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_RED_VIP:			//红钻VIP
			rankStr="红钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_YELLOW_VIP:		//黄钻VIP
			rankStr="黄钻会员";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_GREEN_VIP:		//绿钻VIP
			rankStr="绿钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_BLUE_VIP:			//蓝钻VIP
			rankStr="蓝钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_PINK_VIP:			//粉钻VIP
			rankStr="粉钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_PURPLE_VIP:		//紫钻VIP
			rankStr="紫钻VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_COLOUR_VIP:		//紫钻VIP
			rankStr="彩钻VIP";
			break;
		case CChatRankList::RANK_ROOM_COO_ASSISTANT:			//助理站长
			rankStr="副站长";
			break;
		case CChatRankList::RANK_ROOM_MUSIC_SOCIETY:			//乐团
			rankStr="乐手";
			break;
		case CChatRankList::RANK_ROOM_DANCER:					//舞蹈演员
			rankStr="舞星";
			break;
		case CChatRankList::RANK_ROOM_FUHAO:					//豪字标志
			rankStr="富豪";
			break;
		case CChatRankList::RANK_ROOM_STAR:						//星级艺人
			rankStr = "明星";
			break;

		case CChatRankList::RANK_ROOM_GUARD:					//守护
			rankStr = "守护";
			break;
		case CChatRankList::RANK_ROOM_CARETAKER:					//临管
			rankStr = "临管";
			break;
		}
		return rankStr;
	}


};



class CChatRankListVip
{
public:
	enum RankListVip
	{
		RANK_GENERAL,											//普通用户
		RANK_ROOM_JUNION_VIP,									//低会	
		RANK_ROOM_MIDDLE_VIP,									//中会
		RANK_ROOM_HIGHER_VIP,									//高会
		RANK_ROOM_GOLD_VIP,										//白金会
		RANK_ROOM_LORD_BARON,									//男爵
		RANK_ROOM_LORD_VISCOUNT,								//子爵
		RANK_ROOM_LORD_EARL,									//伯爵
		RANK_ROOM_LORD_MARQUESS,								//侯爵
		RANK_ROOM_LORD_DUKE,									//公爵
		RANK_ROOM_LORD_KING,									//国王
		RANK_ROOM_MANAGER,										//房间管理
		RANK_ROOM_ASSISTANT,									//副室
		RANK_ROOM_OWNER,										//室主
		RANK_ROOM_SUPPER,										//超管
		RANK_ROOM_CONTACT_STAFF,								//客服
		RANK_ROOM_PRIVILEGES,									//特权
		RANK_ROOM_COO,											//站长
		RANK_ROOM_COO_ASSISTANT,								//副站长
		RANK_ROOM_CASTEALLAN,									//城主
		RANK_ROOM_CASTEALLAN_MRS,								//城主夫人
		RANK_ROOM_COMPERE,										//超级主持
		RANK_ROOM_COMPEREMAN,									//MC男主持
		RANK_ROOM_BABY1,										//宝贝1
		RANK_ROOM_BABY2,										//宝贝2
		RANK_ROOM_BABY3,										//宝贝3
		RANK_ROOM_BABY4,										//宝贝4
		RANK_ROOM_BABY5,										//宝贝5
		RANK_ROOM_BABY6,										//宝贝6
		RANK_ROOM_PATROL,										//巡查
		RANK_ROOM_OPERATION,									//运营
		RANK_ROOM_DIAMOND_BLACK_VIP,							//黑钻VIP
		RANK_ROOM_DIAMOND_RED_VIP,								//红钻VIP
		RANK_ROOM_DIAMOND_YELLOW_VIP,							//黄钻VIP
		RANK_ROOM_DIAMOND_GREEN_VIP,							//绿钻VIP
		RANK_ROOM_DIAMOND_BLUE_VIP,								//蓝钻VIP
		RANK_ROOM_DIAMOND_PINK_VIP,								//粉钻VIP
		RANK_ROOM_DIAMOND_PURPLE_VIP,							//紫钻VIP
		RANK_ROOM_DIAMOND_COLOUR_VIP,							//彩钻VIP
		RANK_ROOM_CARETAKER,									//临管
		RANK_ROOM_LIMIT,
	};

	static std::string GetRankName(uint8 usertype)
	{
		std::string rankStr = "";
		switch (usertype)
		{
		case CChatRankListVip::RANK_GENERAL:		
			rankStr="普通用户";
			break;
		case CChatRankListVip::RANK_ROOM_JUNION_VIP:				//低会	
			rankStr="初级会员";
			break;
		case CChatRankListVip::RANK_ROOM_MIDDLE_VIP:				//中会
			rankStr="中级会员";
			break;
		case CChatRankListVip::RANK_ROOM_HIGHER_VIP:				//高会
			rankStr="高级会员";
			break;
		case CChatRankListVip::RANK_ROOM_GOLD_VIP:					//钻会
			rankStr="白金会员";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_BARON:				//男爵
			rankStr="地主";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_VISCOUNT:			//子爵
			rankStr="超级土豪";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_EARL:				//伯爵
			rankStr="富豪";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_MARQUESS:			//侯爵
			rankStr="皇帝";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_DUKE:				//公爵
			rankStr="天王";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_KING:				//国王
			rankStr="大帝";
			break;
		case CChatRankListVip::RANK_ROOM_MANAGER:					//房间管理
			rankStr="房间管理";
			break;
		case CChatRankListVip::RANK_ROOM_ASSISTANT:				//副室
			rankStr="副室";
			break;
		case CChatRankListVip::RANK_ROOM_OWNER:					//室主
			rankStr="室主";
			break;
		case CChatRankListVip::RANK_ROOM_SUPPER:					//超管
			rankStr="超管";
			break;
		case CChatRankListVip::RANK_ROOM_CONTACT_STAFF:			//客服
			rankStr="客服";
			break;
		case CChatRankListVip::RANK_ROOM_PRIVILEGES:				//特权
			rankStr="特权";
			break;
		case CChatRankListVip::RANK_ROOM_COO:						//站长
			rankStr="站长";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_BLACK_VIP:		//黑钻VIP
			rankStr="黑钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_RED_VIP:			//红钻VIP
			rankStr="红钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_YELLOW_VIP:		//黄钻VIP
			rankStr="黄钻会员";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_GREEN_VIP:		//绿钻VIP
			rankStr="绿钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_BLUE_VIP:			//蓝钻VIP
			rankStr="蓝钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_PINK_VIP:			//粉钻VIP
			rankStr="粉钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_PURPLE_VIP:		//紫钻VIP
			rankStr="紫钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_COLOUR_VIP:		//紫钻VIP
			rankStr="彩钻VIP";
			break;
		case CChatRankListVip::RANK_ROOM_COO_ASSISTANT:			//助理站长
			rankStr="副站长";
			break;
		case CChatRankListVip::RANK_ROOM_CASTEALLAN:				//城主
			rankStr="城主";
			break;
		case CChatRankListVip::RANK_ROOM_CASTEALLAN_MRS:			//城主夫人
			rankStr="城主夫人";
			break;

		case CChatRankListVip::RANK_ROOM_COMPEREMAN:			////MC男主持
			rankStr="MC男主持";
			break;
		case CChatRankListVip::RANK_ROOM_COMPERE:			//超级主持
			rankStr="超级主持";
			break;
		case CChatRankListVip::RANK_ROOM_BABY1:			//宝贝1
			rankStr="宝贝1";
			break;
		case CChatRankListVip::RANK_ROOM_BABY2:			//宝贝2
			rankStr="宝贝2";
			break;
		case CChatRankListVip::RANK_ROOM_BABY3:			//宝贝3
			rankStr="宝贝3";
			break;
		case CChatRankListVip::RANK_ROOM_BABY4:			//宝贝4
			rankStr="宝贝4";
			break;
		case CChatRankListVip::RANK_ROOM_BABY5:			//宝贝5
			rankStr="宝贝5";
			break;
		case CChatRankListVip::RANK_ROOM_BABY6:			//宝贝6
			rankStr="宝贝6";
			break;
		case CChatRankListVip::RANK_ROOM_PATROL:			//巡查
			rankStr="巡查";
			break;
		case CChatRankListVip::RANK_ROOM_OPERATION:			//运营
			rankStr="运营";
			break;
		case CChatRankListVip::RANK_ROOM_CARETAKER:			//临管
			rankStr="临管";
			break;
			
		}
		return rankStr;
	}


};



class ChatAct
{
public:
	enum Act
	{
		ActKickOut = 1,											//踢人
		ActBlock,												//拉黑功能
		ActMic,													//抱麦
		ActForbidChat,											//禁言他人功能
		ActModifyRoomInfo,										//修改房间信息
		ActGetUserIP,											//查看用户IP权限
		ActShake,												//震屏功能
		ActPublicChat,											//在关闭后,是否还有公聊功能
		ActPrivateChat,											//在关闭后,是否还有私聊功能,
		ActRoomBroadcast,										//房间广播功能
		ActRoomGlobalMsg,										//全站喇叭
		ActVipRoom,												//进入vip房间权限
		ActVipRoomFull,											//进入vip满员房间权限
		ActRoomBlock,											//加入房间黑名单权限
		ActPidBlock,											//加入站点黑名单权限
		ActModifyMgr,											//设置管理员权限
		ActModifyOwner,											//设置副室主权限
		ActChatLenLimit,										//聊天字数限制
		ActChatDiy,												//允许自定义字体
		ActChatFace,											//表情权限
		ActChatPicture,											//图片权限
		ActChatColor,											//彩条权限
		ActModifyCaretaker,										//修改临管	
		ActTakeMic,												//夺麦
		ActGreeter,												//迎宾词
		ActOtherPrivateChat,									//第三方悄悄话权限
		ActTransfer,											//转账
		ActPrivateMic,											//上私麦权限
		ActPrivateWatch,										//看私麦指定权限
		ActSpecialWatch,										//不受限制的私麦观看权限
		ActGetRed,												//抢红包
		ActSendRed,												//发红包

		ActLimit,

		ActGameStart = 100,
		ActChat,												//游戏聊天
		ActKick,												//车行踢人
		ActGameLimit,											//添加限制权限(防挂机)
	};
	static std::string GetActionName(uint8 actid)
	{
		std::string actNameStr = "";
		switch (actid)
		{
		case ActKickOut:										//踢人
			actNameStr = "kickout";
			break;
		case ActBlock:											//拉黑功能
			actNameStr = "block";
			break;
		case ActMic:											//抱麦
			actNameStr = "mic";
			break;
		case ActForbidChat: 									//禁言他人功能
			actNameStr = "forbidchat";
			break;
		case ActModifyRoomInfo: 								//修改房间信息
			actNameStr = "modifyinfo";
			break;
		case ActGetUserIP: 										//查看用户IP权限
			actNameStr = "getuserip";
			break;
		case ActShake:											//震屏功能
			actNameStr = "shark";
			break;
		case ActPublicChat: 									//在关闭后:是否还有公聊功能
			actNameStr = "publicchat";
			break;
		case ActPrivateChat:									//在关闭后:是否还有私聊功能:
			actNameStr = "privatechat";
			break;
		case ActRoomBroadcast: 									//房间广播功能
			actNameStr = "broadcast";
			break;
		case ActRoomGlobalMsg: 									//全站喇叭
			actNameStr = "ActRoomGlobalMsg";
			break;

		case ActVipRoom:										//进入vip房间权限
			actNameStr = "ActVipRoom";
			break;

		case ActVipRoomFull:									//进入vip满员房间权限
			actNameStr = "ActVipRoomFull";
			break;

		case ActRoomBlock:										//加入房间黑名单权限
			actNameStr = "ActRoomBlock";
			break;

		case ActPidBlock:										//加入站点黑名单权限
			actNameStr = "ActPidBlock";						
			break;
			
		case ActModifyMgr:										//设置管理员权限
			actNameStr = "ActModifyMgr";						
			break;
		
		case ActModifyOwner:									//设置副室主权限
			actNameStr = "ActModifyOwner";						
			break;
		
		case ActChatLenLimit:									//聊天字数限制
			actNameStr = "ActChatLenLimit";						
			break;

		case ActChatDiy:										//允许自定义字体
			actNameStr = "ActChatDiy";						
			break;
		
		case ActChatFace:										//表情权限
			actNameStr = "ActChatFace";						
			break;
				
		case ActChatPicture:									//图片权限
			actNameStr = "ActChatPicture";						
			break;	

		case ActChatColor:										//彩条权限
			actNameStr = "ActChatColor";						
			break;	
				
		case ActModifyCaretaker:								//修改临管
			actNameStr = "ActModifyCaretaker";						
			break;	

		case ActTakeMic:										//夺麦
			actNameStr = "ActTakeMic";						
			break;	

		case ActGreeter:										//迎宾词
			actNameStr = "ActGreeter";						
			break;	
		case ActOtherPrivateChat:								//第三方悄悄话权限
			actNameStr = "ActOtherPrivateChat";						
			break;	
		case ActTransfer:										//转账
			actNameStr = "ActTransfer";						
			break;	
		case ActPrivateMic:										//上私麦权限
			actNameStr = "ActPrivateMic";						
			break;	
		case ActPrivateWatch:										//看私麦指定权限
			actNameStr = "ActPrivateWatch";						
			break;	
		case ActSpecialWatch:										//不受限制的私麦观看权限
			actNameStr = "ActSpecialWatch";						
			break;	
		case ActGetRed:												//抢红包
			actNameStr = "ActGetRed";
			break;
		case ActSendRed:											//发红包
			actNameStr = "ActSendRed";
			break;


		//游戏100以后的
		case ActChat:
			actNameStr = "ActGameChat";						
			break;
		case ActKick:
			actNameStr = "ActGameKick";
			break;
		case ActGameLimit:
			actNameStr = "ActGameLimit";
			break;
		}
		return actNameStr;
	};

};

#pragma pack(push, 1)


class ChatAclCtrl
{
public:
	ChatAclCtrl()
	{
		actKickOut = actMic = actForbidChat = actModifyRoomInfo \
			= actGetUserIP = actShake = actPublicChat = actPrivateChat = actRoomBroadcast = 0;
		actRoomGlobalMsg = 0;
		actVipRoom		 = 0;											//进入vip房间权限										
		actVipRoomFull	 = 0;;										//进入vip满员房间权限
		actRoomBlock	 = 0;										//加入房间黑名单权限
		actPidBlock      = 0;											//加入站点黑名单权限
		actModifyMgr     = 0;										//设置管理员权限(黄马)
		actModifyOwner   = 0;										//设置副室主权限(绿马)
		actChatLenLimit  = 0;										//聊天字数限制
		actChatDiy       = 0;										//允许自定义字体
		actChatFace		 = 0;											//表情权限
		actChatPicture	 = 0;										//图片权限
		actChatColor	 = 0;								
		actModifyCaretaker= 0;
		actTakeMic		 = 0;											
		actGreeter		 = 0;;											
		actOtherPrivateChat = 0;								
		actTransfer = 0;	
		actPrivateMic = 0;										
		actPrivateWatch = 0;									
		actSpecialWatch = 0;
		actGetRed = 0;
		actSendRed = 0;
	}
	uint8 actKickOut:1;											//踢人
	uint8 actMic:1;												//抱麦
	uint8 actForbidChat:1;										//禁言
	uint8 actModifyRoomInfo:1;									//修改房间信息
	uint8 actGetUserIP:1;										//查看用户IP权限
	uint8 actShake:1;											//震屏功能
	uint8 actPublicChat:1;										//公聊功能
	uint8 actPrivateChat:1;										//私聊功能
	uint8 actRoomBroadcast:1;									//房间广播功能
	uint8 actRoomGlobalMsg:1;									//全站喇叭
	uint8 actVipRoom:1;											//进入vip房间权限										
	uint8 actVipRoomFull:1;										//进入vip满员房间权限
	uint8 actRoomBlock:1;										//加入房间黑名单权限
	uint8 actPidBlock:1;										//加入站点黑名单权限
	uint8 actModifyMgr:1;										//设置管理员权限(黄马)
	uint8 actModifyOwner:1;										//设置副室主权限(绿马)
	uint8 actChatLenLimit:1;									//聊天字数限制
	uint8 actChatDiy:1;											//允许自定义字体
	uint8 actChatFace:1;										//表情权限
	uint8 actChatPicture:1;										//图片权限
	uint8 actChatColor:1;										//彩条权限
	uint8 actModifyCaretaker:1;									//修改临管
	uint8 actTakeMic:1;											//夺麦权限
	uint8 actGreeter:1;											//迎宾词权限
	uint8 actOtherPrivateChat:1;								//其他人悄悄话
	uint8 actTransfer:1;										//转账
	uint8 actPrivateMic:1;										//上私麦
	uint8 actPrivateWatch:1;									//私麦仅指定权限观看
	uint8 actSpecialWatch:1;									//不受任何限制观看私麦权限
	uint8 actGetRed:1;											//抢红包权限
	uint8 actSendRed:1;											//发红包权限

	
	std::string GetAclStr()
	{
		std::string aclStr;
		
		aclStr += actKickOut?"1":"0";
		aclStr += actMic?"1":"0";
		aclStr += actForbidChat?"1":"0";
		aclStr += actModifyRoomInfo?"1":"0";
		aclStr += actGetUserIP?"1":"0";
		aclStr += actShake?"1":"0";
		aclStr += actPublicChat?"1":"0";
		aclStr += actPrivateChat?"1":"0";
		aclStr += actRoomBroadcast? "1":"0";
		aclStr += actRoomGlobalMsg? "1":"0";
		aclStr += actVipRoom? "1":"0";
		aclStr += actVipRoomFull? "1":"0";
		aclStr += actRoomBlock? "1":"0";
		aclStr += actPidBlock? "1":"0";
		aclStr += actModifyMgr? "1":"0";
		aclStr += actModifyOwner? "1":"0";
		aclStr += actChatLenLimit? "1":"0";
		aclStr += actChatDiy? "1":"0";
		aclStr += actChatFace? "1":"0";
		aclStr += actChatPicture? "1":"0";
		aclStr += actChatColor? "1":"0";
		aclStr += actModifyCaretaker?"1":"0";
		aclStr += actTakeMic?"1":"0";
		aclStr += actGreeter?"1":"0";
		aclStr += actOtherPrivateChat?"1":"0";
		aclStr += actTransfer?"1":"0";
		aclStr += actPrivateMic?"1":"0";
		aclStr += actPrivateWatch?"1":"0";
		aclStr += actSpecialWatch?"1":"0";
		aclStr += actGetRed?"1":"0";
		aclStr += actSendRed?"1":"0";

		return aclStr;
	}
	void SetAcl(std::string aclStr)
	{
		uint8 i=0;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actKickOut = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actMic = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actForbidChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyRoomInfo = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGetUserIP = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actShake = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPublicChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomBroadcast = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomGlobalMsg = 1;


		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actVipRoom = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actVipRoomFull = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomBlock = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPidBlock = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyMgr = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyOwner = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatLenLimit = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatDiy = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatFace = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatPicture = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatColor = 1;
		
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyCaretaker = 1;
	
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actTakeMic = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGreeter = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actOtherPrivateChat = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actTransfer = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateMic = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateWatch = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actSpecialWatch = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGetRed = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actSendRed = 1;

	}
	bool ISManager()
	{
		return (actKickOut || actMic);
	}
} ;

#pragma pack(pop)




class CGiftKind
{
public:
	enum
	{
		MAX_SINGER_GIFT_NUM = 2,								//最多两个有效点歌礼物
	};

	enum
	{
		SINGER_GIFT_FOR_SINGER = 0,								//点歌礼物只对歌手有效
		SINGER_GIFT_FOR_ALL,									//点歌礼物对所有人有效
	};

	enum Giftkind
	{
		GENERAL_GIFT = 0,										//普通礼物
		LUCKY_GIFT,												//幸运礼物
		SINGER_GIFT,											//歌手礼物
		WELFARE_GIFT,											//群刷礼物，房间发福利
        TRANSFER_GIFT = 5,                                      //转账礼物 [JWJ]
		VOD_GIFT,												//点歌
		SMALL_FIREWORKS,										//小烟花
		BIG_FIREWORKS,											//大烟花
		DIAMOND_GIFT,											//钻石礼物
		WEEKSTAR_GFIT,											//周星钻石礼物
		SIEGE_GIFT_KIND,										//攻城礼物	
		DIAMOND_TRANSFER,										//钻石转账礼物		
	};
};

class CRebateKind
{
public:
	enum
	{
		NORMAL_USER = 1,	//普通用户
		SINGER_USER,		//艺人
	};
};

class CRoomMicMode
{
public:
	enum MicMode
	{
		GENERAL_MODE = 0,										//普通模式
		SINGER_MODE,											//歌手模式
	};
};

enum PrivateMicType
{
	NONEED_AUTH,				//不需要验证，或者验证通过
	ONLY_VIP_AUTH,				//会员用户可观看
	USER_AGREE_AUTH,			//需要用户确定可连接
	GIFT_AUTH,					//送礼可连接

	AUTH_LIMIT,					//私卖类型上线
};

enum PrivateMicConfirmAction
{
	CONFIRM_ANSWER_AGREE,			//私麦用户同意连接
	CONFIRM_ANSWER_REFUSE,			//私麦用户拒绝连接
};


enum ChatUserType
{
	chat_user_general,									//普通用户
	chat_user_virtual,									//虚拟用户，后期希望能够发展成机器人
	chat_user_ios,										//移动ios用户
	chat_user_android,									//移动andorid用户
	chat_user_web,										//web用户
	chat_user_letao,									//pc版本		
	chat_user_iospad,									//ios pad版本	
	chat_user_androidpad,								//安卓pad
};


enum BeanstalkNotifyType
{
	//游戏
	BNT_PPC_NEW				= 1,					//新碰碰车中奖消息广播
	BNT_PPC_FKCH,									//疯狂车行中奖消息广播
	BNT_PPC_FRUIT,									//幸运水果机中奖消息广播
	BNT_PPC_DIAMOND,								//砖石车行中奖消息广播
	BNT_ZZ_LE,										//转转乐中奖消息广播
	BNT_OPEN_BOX,									//房间开宝箱中奖消息广播
	BNT_DUG_TREASURE,								//房间挖宝中奖消息广播
	BNT_NN_CARD,									//牛牛中奖消息广播

	//礼物
	BNT_LUCKY_GIFT			= 101,					//幸运礼物中奖中奖消息
	BNT_DUOBAO_WIN,									//一元夺宝中奖消息
	BNT_ACTIVIT_PROMOTE,							//捕鱼推广活动消息
	//玩家广播消息
	BNT_NORMAL_USER_MSG			= 201,				//普通房间玩家发送广播消息
	BNT_VIP_USRE_MSG,								//VIP房间玩家发送广播消息
};

enum GiftDayRankFirstType
{
	GDRFT_SSEND_GIFT = 1,				//送礼第一名
	GDRFT_RECIVE_GIFT = 2,				//收礼第一名

	GDRFT_LIMIT,
};



/************************************************************************/
/* 服务器和客户端共用命令字集合，其他地方不得再定义命令字,所有以此为准*/
/************************************************************************/
typedef enum RoomCmdType
{	
	IM_CHAT_KEEP_ALIVE = 0x0001,
	IM_CHAT_ACK,
	IM_CHAT_PING,												//网速检测报文
	IM_CHAT_OBTAIN_IP,											//获得用户ＩＰ
	IM_CHAT_ANDROID_LOGON,										//机器人登陆
	IM_CHAT_ANDROID_LOGON2,

	IM_CHAT_LOGON_ROOM			= 0x0100,						//登陆房间
	IM_CHAT_LOGOUT_ROOM,										//退出房间
	IM_CHAT_KICKOUT,											//踢出
	IM_CHAT_VISITOR,											//获取房间当前用户列表
	IM_CHAT_FORBID_CHAT,                                        //禁言某用户 
	IM_CHAT_EXTRA_MICTIME,										//延长麦时
	IM_CHAT_MAC_PRESENTLIST,									//客户端请求可以领取的上麦奖励列表
	IM_CHAT_PRIVATE_BIND,										//上私麦
	IM_CHAT_PRIVATE_UNBIND,										//下私麦
	IM_CHAT_PRIVATE_WATCH,										//观看私麦
	IM_CHAT_PRIVATE_UNWATCH,									//退出观看私麦
	IM_CHAT_PRIVATE_WATCHLIST,									//请求私麦观看列表
	IM_CHAT_PRIVATE_LIST_REQ,									//请求私麦列表
	IM_CHAT_KICKOUT_PRIVATE,									//抱下私麦	
	IM_CHAT_PRIVATE_AVSTATE,									//私麦音视频状态修改
	IM_CHAT_FORBID_CHAT_BY_ANCHOR,                               //主播禁言操作
	
	IM_CHAT_MODIFY_INFO			= 0x0200,						//修改房间信息
	IM_CHAT_GET_ROOMINFO,										//获取房间信息
	IM_CHAT_MODIFYPASS,											//修改房间密码
	IM_CHAT_ROOM_OPEN,											//打开房间
	IM_CHAT_ROOM_CLOSE,											//关闭房间

	IM_CHAT_MODIFY_MANGER,										//修改管理员权限
	IM_CHAT_ROOM_MSG,											//发送房间内部广播
	IM_CHAT_MODIFY_ROOM_INFO_ITEM,								//逐项修改房间信息
	IM_CHAT_SUIBO_PAUSE,										//主播切换到后台
	IM_CHAT_MGRLIMIT_CONFIRM,									//房管超过限制确认框推送

	IM_CHAT_CONF_JOIN			= 0x0250,						//拿麦
	IM_CHAT_CONF_EXIT,											//主动下麦
	IM_CHAT_CONF_KICKOUT,										//踢下麦			
	IM_CHAT_CONF_DRAGIN,										//把人拉进会议
	IM_CHAT_CANCEL_CFWAIT,										//取消等待会议
	IM_CHAT_GET_MIC_LIST,										//获取当前在麦列表
	IM_CHAT_CFWAITLIST,											//获取排麦列表
	IM_CHAT_CHANGE_AUTOMIC,										//变更自动排麦状态
	IM_CHAT_ADJUST_MIC_QUEUE,									//调整排麦的对列
	IM_CHAT_DRAG_SETTING,										//设置防抱麦选项
	IM_CHAT_SHAKE,												//晃动对方
	IM_CHAT_STAMP,												//印章
	IM_CHAT_GET_USER_STAMP_INFO,								//获取盖章列表
	IM_CHAT_ERASESTAMP,											//擦除盖章
	IM_CHAT_REQUEST_OPENBOX,									//增加免费开宝箱请求
	IM_CHAT_VIEWSTATE,											//直播状态变更
	IM_CHAT_LAUDCOUNT,											//点赞
	IM_CHAT_TAKEMIC,											//夺麦
	IM_CHAT_MODIFYCARETAKER,									//修改临时管理
	IM_CHAT_FILLUPMICQUEUE,										//补麦序
	IM_CHAT_MODIFYMICTIME,										//修改最大麦时
	IM_CHAT_CHANGE_MACLIMIT,									//限麦设置
	IM_CHAT_GET_VID,											//获取vid
	IM_CHAT_OPEN_BOX,											//挖宝请求
	IM_CHAT_MICINFO_REQ,										//请求麦上用户信息
	IM_CHAT_INVITE_FRIENDS,                                     //邀请QQ好友
	IM_CHAT_REQ_REDLIST,										//请求红包列表


	IM_CHAT_TEXT				= 0x0300,						//文字信息
	IM_CHAT_USEGIFT,											//送礼
	IM_CHAT_AUDIO,												//音频
	IM_CHAT_VIDEO,												//视频
	IM_CHAT_GLOBLE_MSG,											//发送小喇叭信息
	IM_CHAT_RTP,												//RTP报文
	IM_CHAT_RTP_ACK,											//RTP报文ACK
	IM_CHAT_RTP_REQ,											//RTP重新请求丢失报文
	IM_CHAT_RTP_REQ_DIRECT,										//直接请求某报文
	IM_CHAT_USEGIFT_LIST,										//群刷功能．
	IM_CHAT_GAME,												//聊天游戏
	IM_CHAT_GETPRESENT_MONEY,									//领取上麦奖励
    IM_CHAT_TRANS_TAX_RATE,                                     //获取转账税率和权限 // [JWJ]
	IM_CHAT_ADDBLOCK,											//加入全站封锁
	IM_CHAT_MODIFYOWNER,										//修改副室主
	IM_CHAT_GUARD_LIST,											//守护列表
	IM_CHAT_GUARD_ACL,											//守护权限接口
	IM_CHAT_FANS_LIST,											//粉丝列表
	IM_CHAT_SINGE_ORDER,										//点歌列表
	IM_CHAT_VOD,												//点歌
	IM_CHAT_VID_GIFTORDER,										//直播榜单
	IM_CHAT_MONTH_GIFTORDER,									//月榜单
	IM_CHAT_SUIBO_REDUCEMONEY,									//随播扣钱消费通用接口
	IM_CHAT_ANYCAST_INFO,										//随播进入房间数据获取接口
	IM_CHAT_REQ_MGRLIST,										//请求房间管理列表
	IM_CHAT_ANYCAST_BLOCK,										//随播拉黑
	IM_CHAT_ANYCAST_REDLIST,									//随播红包列表


	IM_CHAT_ZZ_BET					= 0x350,					//转转下注
	IM_CHAT_RELAY_MSG,											//转发信息


	IM_CHAT_SRV_USER_ONLINE		= 0x0400,						//用户进入房间
	IM_CHAT_SRV_USER_OFFLINE,									//离线
	IM_CHAT_SRV_KICKOUT,										//强制离线
	IM_CHAT_SRV_FORCE_OFFLINE,									//多地登录强制离线

	IM_CHAT_SRV_MODIFY_MANGER,
	IM_CHAT_SRV_FORBIDCHAT_NTY,									//禁言通知接口
	IM_CHAT_SRV_MODIFYCARETAKER,								//修改临管
	IM_CHAT_SRV_PRIVATE_LIST,									//下发私麦列表
	IM_CHAT_SRV_CONFIRM_ASK,									//私麦请求连接通知
	IM_CHAT_SRV_CONFIRM_ANSWER,									//私确认连接
	IM_CHAT_SRV_WATCHLIST,										//下发私麦观看列表
	IM_CHAT_SRV_PRIVATEJOIN,									//上私麦通知
	IM_CHAT_SRV_PRIVATEEXIT,									//下私麦通知
	IM_CHAT_SRV_GUARDWEEKLIST,									//周守护列表
	


	IM_CHAT_SRV_CONF_JOIN		= 0x0500,						//上麦
	IM_CHAT_SRV_CONF_EXIT,										//下麦
	IM_CHAT_SRV_CONF_KICKOUT,									//被下麦
	IM_CHAT_SRV_ADDCFWAIT,										//被加入会议等待
	IM_CHAT_SRV_REMOVECFWAIT,									//被从会议等待中清除
	IM_CHAT_SRV_AUTOMIC_STATUS_CHANGE,							//自动排麦状态变化
	IM_CHAT_SRV_MICTIME_CHANGE,									//通知剩余新麦时
	IM_CHAT_SRV_MICPRESENT,										//通知领取上麦奖励
	IM_CHAT_SRV_LAUDCOUNT,										//更新点赞
	IM_CHAT_SRV_SHARE,											//分享
	IM_CHAT_SVR_FIREWORKS,										//礼花通知
	IM_CHAT_SVR_TOTALRECV,										//随播主播总收益广播



	IM_CHAT_SRV_ROOMINFO		= 0x0600,						//更新房间信息, 用于管理员修改房间信息后
	IM_CHAT_SRV_ROOM_BROADCAST,									//发送房间广播
	IM_CHAT_SRV_ROOM_OPEN,										//房间被打开
	IM_CHAT_SRV_ROOM_CLOSE,										//房间被关闭

	IM_CHAT_SRV_USEGIFT			= 0x0700,						//送礼
	IM_CHAT_SRV_NTY_MSG,										//通知消息
	IM_CHAT_SRV_GLOBLE_MSG,										//小嗽叭消息
	IM_CHAT_SRV_PRIZE,											//中奖消息
	IM_CHAT_SRV_GREAT_GIFT,										//大礼消息
	IM_CHAT_SRV_IP_INFO,										//用户的IP消息
	IM_CHAT_SRV_MARQUEE_MSG,									//房间飘文字消息,只下发文字
	IM_CHAT_SRV_GENERAL_MSG,									//房间大奖消息广播信息
	IM_CHAT_SRV_STAMP,											//印章
	IM_CHAT_SRV_ERASESTAMP,										//擦除印章
	IM_CHAT_SRV_GET_USER_STAMP_INFO,							//获取房间内用户盖章列表
	IM_CHAT_SRV_REQUEST_OPENBOX,								//处理完免费开箱
	IM_CHAT_SRV_ROOMINFO_CHANGE,								//通知房间属性被修改
	IM_CHAT_SRV_GET_REDPAPER,									//抢到红包通知消息	//---sqh
	IM_CHAT_SRV_SEND_REDPAPER,									//发放红包通知消息	//---sqh
    IM_CHAT_SRV_TRANS_TAX_RATE,                                 //转账税率 // [JWJ]
	IM_CHAT_SRV_USEGIFTNEW,										//送礼和中奖消息
	IM_CHAT_SRV_NTY_MSGEX,										//扩展通知消息
	IM_CHAT_SRV_BOX_NOTIFY,										//宝箱通知消息
	IM_CHAT_SRV_OPENBOX_NOTIFY,									//挖宝通知
	IM_CHAT_SRV_ONMIC_INFO,										//通知麦上用户信息
	IM_CHAT_SRV_ROOM_INVITE,                                     //房间邀请消息
	IM_CHAT_SRV_WEEKSTAR_CHANGE,								//周星变更通知消息
	IM_CHAT_SRV_DIAMOND_GIFT,									//钻石礼物通知
	IM_CHAT_SRV_WEEKSTAR_LIST,									//全量周星列表
	IM_CHAT_SRV_REDLIST,										//推送红包列表
	IM_CHAT_SRV_SIEGEGIFT,										//更新攻城礼物
	IM_CHAT_SRV_UPDATEDAY_GIFTRANK,								//更新日排行收送礼第一名

	IM_CHAT_SRV_ZZ_BET_START	= 0x0750,						//转转新一轮开始投注，下发投注时间
	IM_CHAT_SRV_ZZ_BETMSG,										//转转某人下注消息
	IM_CHAT_SRV_ZZ_WAITING,										//确认下注，等待开奖过程
	IM_CHAT_SRV_ZZ_AWARDING,									//转转开始开奖
	IM_CHAT_SRV_ZZ_AWARDED,										//转转开奖信息，开始下发下一轮投注开始
	IM_CHAT_SRV_ZZ_AWARDMSG,									//转发某人中奖信息
	IM_CHAT_SRV_ZZ_STOP,										//停止开奖
	IM_CHAT_SRV_ZZ_AWARD_TODAY,									//当天开奖信息


	IM_CHAT_SRV2SRV_RTP			= 0x800,						//服务器之间传送RTP报文
	IM_CHAT_SRV2SRV_RTP_REQ,									//服务器之间丢包重发请求

	IM_CHAT_PPC_BET				= 0x900,						//用户PPC押注
	IM_CHAT_PPC_BANKER_REQ,										//用户庄家操作
	IM_CHAT_SVR_PPC_HISTORY,									//开奖历史下发
	IM_CHAT_SVR_PPC_BETSTART,									//新一轮开始
	IM_CHAT_SVR_PPC_SCENE,										//当前场景下发
	IM_CHAT_SVR_PPC_AWARD_ITEM,									//开奖结果
	IM_CHAT_SVR_PPC_BET_ACTION,									//下注动作通知
	IM_CHAT_SVR_PPC_BET_RESULT,									//用户下注结果返回,并通知新的金币数量
	IM_CHAT_SVR_PPC_AWARD_RESULT,								//用户中奖后结果通知.
	IM_CHAT_SVR_PPC_BANKER_CHANGE,								//PPC庄家信息变更
	IM_CAHT_SVR_PPC_STOP,										//停止开奖
	IM_CAHT_SVR_PPC_FREE,										//等待处理结果
	IM_CHAT_SVR_PPC_GAMEEND,									//游戏结束通知
	IM_CHAT_PPC_SYNC_SCENE,										//同步场景请求
	IM_CHAT_PPC_SYNC_USERINFO,									//更新用户列表数据
	IM_CHAT_PPC_GAMELIMIT,										//添加车行限制(防挂机)


	REDPACKETS_GAME_START		= 0x1000,						//新一轮游戏开始									
	REDPACKETS_SEND_REDPACKETS,									//发送红包
	REDPACKETS_SEND_REDPACKETS_NTY,								//发红包通知
	REDPACKETS_ROB_REDPACKETS,									//抢红包
	REDPACKETS_ROB_REDPACKETS_NTY,								//抢红包通知
	REDPACKETS_SENCE_STATE,										//游戏场景状态（正在游戏中 新用户加入推送此消息）
	REDPACKETS_GAME_END,										//游戏结束下发抢的最多和最少的用户
								


	
	IM_CHAT_WEB_USERINFO	= 0x2000,							//web用户上下线消息
	IM_CHAT_WEB_CHATTEXT,										//聊天消息
	IM_CHAT_WEB_VIEWSTATE,										//直播状态

	DIS_SERVER_REGIST			= 0x3000,						//添加服务
	DIS_SERVER_ADD_DELETE_ROOM,									//添加或删除房间
	DIS_SERVERINFO				,						//服务数据上报
	DIS_SERVER_ROOMINFO			,						//上报房间数据

	//客户端与调度服务
	DIS_CLIENT_GETSERVER,										//客户端获取需要登录的服务信息

	IM_CHAT_CMD_LIMIT

}RoomCmdType;

typedef enum Language
{
	TL_ZH_CN,	//简体中文
	TL_ZH_TW,	//繁体中文台湾
	TL_ZH_HK,	//繁体中文香港
	TL_EN,		//英文

	TL_LANGUAGE_LIMIT	//语言限制
}Language;

//系统消息类型
typedef enum SystemMsgType
{
	TL_CHAT_MSG,	//房间内显示的消息
	TL_BOX_MSG,		//弹框消息
};

typedef enum RoomMsgType
{
	IM_SVR_MSG_SUCCESS = 0x0001,

	IM_SVR_MSG_NO_PRIVILEGE = 0x1000,

	IM_SVR_MSG_CONF_IS_FULL,									//会议已满员
	IM_SVR_MSG_CONF_NOT_IN,										//你不在会议中
	IM_SVR_MSG_CONF_HAS_IN,										//你已在会议中	
	IM_SVR_MSG_CONF_HAS_MIC,									//你已有麦克
	IM_SVR_MSG_CONF_NO_MIC,										//你没有麦克
	IM_SVR_MSG_CONF_NO_MIC_REMAIN,								//没有多余麦克
	IM_SVR_MSG_CONF_BE_CLOSE,									//会议室是关闭的
	IM_SVR_MSG_CONF_NEED_PASS,									//需要密码
	IM_SVR_MSG_CONF_ERR_PASS,									//错误密码
	IM_SVR_MSG_CONF_ERR_OLDPASS,								//错误旧密码
	IM_SVR_MSG_MEMBER_HAS_IN,									//你已是成员
	IM_SVR_MSG_MEMBER_NOT_IN,									//你不是成员
	IM_SVR_MSG_CONF_HAS_OPEN,									//会议已经是打开的
	IM_SVR_MSG_CONF_HAS_CLOSE,									//会议已经是关闭的
	IM_SVR_MSG_CONF_HAS_FROZEN,									//会议已经是冻结的
	IM_SVR_MSG_CONF_HAS_UNFROZEN,								//会议已经是非冻结的
	IM_SVR_MSG_NOT_ONLINE,										//你不是在线，无法进行本操作
	IM_SVR_MSG_HAS_OPEN,										//房间已经是打开的
	IM_SVR_MSG_HAS_CLOSE,										//房间已经是关闭的
	IM_SVR_MSG_ERR_OLDPASS,										//错误旧密码
	IM_SVR_MSG_CFWAIT_HAS_IN,									//你已在麦序中
	IM_SVR_MSG_CFWAIT_IS_FULL,									//麦序已满
	IM_SVR_MSG_CFWAIT_NOT_IN,									//对方麦序已满

	IM_SVR_MSG_OPP_CONF_NOT_IN = 0x1100,						//对方不在会议
	IM_SVR_MSG_OPP_CONF_HAS_IN,									//对方已在会议
	IM_SVR_MSG_OPP_CONF_HAS_MIC,								//对方已有麦克
	IM_SVR_MSG_OPP_CONF_NO_MIC,									//对方没有麦克
	IM_SVR_MSG_OPP_HAS_BE_MEMBER,								//对方已是成员
	IM_SVR_MSG_OPP_NOT_BE_MEMBER,								//对方不是成员
	IM_SVR_MSG_OPP_HAS_BE_MANAGER,								//对方已是管理员			
	IM_SVR_MSG_OPP_NOT_BE_MANAGER,								//对方不是管理员
	IM_SVR_MSG_OPP_NOT_ONLINE,									//对方不在线
	IM_SVR_MSG_OPP_HAS_INBLACKLIST,								//对方已在黑名单中
	IM_SVR_MSG_OPP_NOT_INBLACKLIST,								//对方不在黑名单中
	IM_SVR_MSG_OPP_CFWAIT_NOT_IN,								//对方不在麦序中

	IM_SVR_MSG_NOT_IN,											//你不在圈中
	IM_SVR_MSG_OPP_NOT_IN,										//对方不在圈中
	IM_SVR_MSG_CANNOT_KICKOUT_NOVISITOR,						//不能将成员踢出圈

	IM_SVR_MSG_GIFT_NOMONEY,									//资金余额不足
	IM_SVR_MSG_GIFT_FAILED,										//送礼失败

	IM_SVR_MSG_OVER_MEMBER_LIMIT = 0x1200,						//超过成员个数限制，无法添加成员
	IM_SVR_MSG_OVER_MANAGER_LIMIT,								//超过管理员个数限制，无法再加管理员
	IM_SVR_MSG_OVER_IMPMES_LIMIT,								//超过当天重大消息最大条数限制
	IM_SVR_MSG_OVER_PIC_LIMIT,									//超过当天图片最大条数限制
	IM_SVR_MSG_OVER_BLACKLIST_LIMIT,							//黑名单已超过最大限制
	
	IM_SVR_MSG_NOT_IN_SYS_ALLOW_TIME,							//不在系统设置允许时间范围内



	ANYCAST_ACL_NOT_ENOUGH	 = 0x1300,							//权限不足
	ANYCAST_USER_NUM_LIMIT,										//超过人数限制
	ANYCAST_DB_ERROR,											//db接口错误

}RoomMsgType;



//通知码
typedef enum RoomCmdStateType
{
	LOGON_SUCCESS = 0x0001,										//登陆成功
	LOGON_ROOM_FAILED,											//对于不明确错误,统一以此返回
	LOGON_INVALID_UIN,											//uin不存在
	LOGON_WRONG_PASSWD,											//密码错误
	LOGIN_NO_ROOM_MEMBER,										//不是房间成员
	LOGON_ROOM_IS_BUSY,											//房间正繁忙,提示客户端稍后再连
	LOGON_NO_THIS_ROOM,  										//该房间不存在(可能已解散,或被临时冻结)
	LOGON_REJECT,												//被拒绝登录
	LOGON_REQ,													//正在请求登陆中
	LOGON_VISITOR_ISFULL,										//房间已满
	LOGON_ROOM_CLOSE,											//房间是关闭的
	LOGON_WRONG_ROOM_PASSWD,									//房间密码错误
	LOGON_ROOM_ISFULL,											//游客已满
	LOGON_BLACKLIST_UIN,										//用户在黑名单中
	LOGON_BLACKLIST_IP,											//IP在黑名单中
	LOGON_FORBID_JOIN,											//该房间不允许您进入
	LOGON_REQUEST_DATA,											//登录成功后，请求数据中故//借用下 whg 20090604
	LOGON_REQUEST_SUCESS,										//登录成功后，请求数据中全部返回//借用下 whg 20090604
	LOGON_ROOM_ONLY_SUBSCRIBER,									//只允许订阅者进入
	LOGON_ROOM_ONLY_VIP,										//收费房间，只允许缴费用户进入（包括已经订阅者）
	LOGON_ROOM_PAY_ERROR,										//扣费不失败（系统错误或余额不足)
	LOGON_ROOM_INGAME,											//正在游戏房间
	LOGON_BLACKLIST_MAC,										//机器码在黑名单中
	LOGON_MAX_LIMIT,											//单个mac登录超过最大限制
	LOGON_ENTIRY_LIMIT,											//单个身份超过最大登录限制
	LOGON_SUIBO_END,
	LOGIN_SUIBO_VIDERROR,
	LOGIN_TABLE_ERROR,											//桌号不存在
	LOGIN_TABLE_LOCKED,											//此桌已锁定
	LOGIN_TABLE_MONEY_LOCKED,									//虚拟币被游戏冻结
	LOGIN_NOENOUGH_MONEY,										//没有足够的虚拟币
	LOGIN_KICK_LIMITTIMES,                                      //超过当天没押注被踢最大次数
}RoomCmdStateType;


//通知码
typedef enum TableState
{
	TABLE_SUCCESS = 0x0001,										//成功
	TABLE_NOENOUTH_MONEY,										//余额不足
	TABLE_API_ERROR,											//接口错误
	TABLE_ID_EXIST,												//此id桌已经存在
	TABLE_MONEY_LOCKED,											//虚拟币被游戏锁定

}TableState;

typedef enum OpenBoxState
{
	OPENBOX_SUCCESS,			//挖宝成功
	OPENBOX_NOT_FREETIME,		//非免费时间
	OPENBOX_NO_FREECOUNT,		//免费次数用完
	OPENBOX_FAILED,				//接口错误
	OPENBOX_NO_ENOUGHMONEY,		//没有足够的钱
	OPENBOX_MONEYLOCK			//金币被游戏锁定
};

typedef enum RoomUserRankType
{
	USER_RANK_GENERAL		= 0x0000,							//None
	USER_RANK_VISITOR		= 0x0001,							//游客
	USER_RANK_MEMBER		= 0x0002,							//普通成员
	USER_RANK_ROOMMAN		= 0x0004,							//管理员
	USER_RANK_ROOMOWNER		= 0x0008,							//室长
	USER_RANK_SUPERMAN		= 0x0010,							//一级超管
	USER_RANK_AREA_MASTER	= 0x0020,							//区管
	USER_RANK_AREA_ASSISTANT= 0x0040,							//助理区管
	USER_RANK_ANCHOR		= 0x0080,							//主播
	USER_RANK_GUARD			= 0x0100,							//守护
	USER_RANK_CARETAKER		= 0x0200,							//临管
	USER_RANK_CASTELLAN		= 0x0400,							//城主
	USER_RANK_CASTELLAN_MRS = 0x0800,							//城主夫人
	USER_RANK_LIMIT,
}RoomUserRankType;

typedef enum ViewRuningAction
{
	RUN_FRONT		= 0,							//前端正常运行
	RUN_BACK,										//后台挂起																
}ViewRuningAction;
//typedef enum GlobleUserType
//{
//	USER_GLOBLE_TYPE_SINGER			= 1,					//公司签约歌手
//	USER_GLOBLE_TYPE_AGENT			= 2,					//公司签约代理
//	USER_GLOBLE_TYPE_CONTACT_STAFF	= 4,					//公司客服
//	USER_GLOBLE_TYPE_SALES			= 8,					//公司销售
//	USER_GLOBLE_TYPE_PRIVILEGES		= 16,					//特权标志
//	USER_GLOBLE_TYPE_COO			= 32,					//站长标志
//}GlobleUserType;



typedef enum USER_RIGHT_FLAG
{
	USER_FLAG_MIC		= 0x0001,								//是否带麦克，指用户终端插有麦克，不是说其拥有说话权限
	USER_FLAG_CAMERA	= 0x0002,								//是否有摄像头，指用户终端插有摄像头，不是说其拥有视频权限
	USER_FLAG_INCONF	= 0x0004,								//是否在会议中
	USER_FLAG_ROOM_VIP	= 0x0008,								//是否是房间已收费用户
}USER_RIGHT_FLAG;



enum
{
	CONF_STATUS_CLOSE,
	CONF_STATUS_OPEN,
	CONF_STATUS_FROZEN,
};

enum
{
	RES_CONF_INVITE_ACCEPT,										//接受邀请
	RES_CONF_INVITE_REFUSE,										//拒绝邀请
	RES_CONF_INVITE_CANT_ACCEPT,								//无法接受邀请,所有的无法明确归类的无法接受邀请
	RES_CONF_INVITE_BUSY,										//用户忙碌无法接受邀请
	RES_CONF_INVITE_AV_BUSY,									//音视频占用,无法接受邀请
	RES_CONF_INVITE_A_BUSY,										//音频占用,无法接受邀请
	RES_CONF_INVITE_V_BUSY,										//视频占用,无法接受邀请
};

#ifndef MAX_MIC_USER_NUM
#	define MAX_MIC_USER_NUM				4						//最大麦数
#endif

class StampUserItem           //用户盖章的信息
{
public:
	enum
	{
		MAX_STAMP_TEXT = 12,									//最大盖章文字信息数		
	};
public:
	StampUserItem()
	{
		src = dst = stampTime = stampID = 0;
		memset(stampMsg, 0, sizeof(stampMsg));
	}

	StampUserItem& operator=(const StampUserItem& smpItem)
	{
		if(this == &smpItem)
			return *this;

		src = smpItem.src;
		dst = smpItem.dst;
		stampID = smpItem.stampID;
		stampTime = smpItem.stampTime;
		memcpy(stampMsg,smpItem.stampMsg,sizeof(stampMsg));
		return *this;
	}

	StampUserItem(const StampUserItem& smpItem)
	{
		*this = smpItem;
	}
public:
	uint32 src;				//表示送出盖章请求的人
	uint32 dst;				//表示被盖章的人
	uint16 stampID;
	uint32 stampTime;
	char   stampMsg[MAX_STAMP_TEXT+1];
};

#endif
