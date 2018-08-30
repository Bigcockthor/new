#ifndef IM_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#define IM_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF

#include "include/icqtypes.h"
#include <string>
#include <map>
#include "include/TinyMarkup.h"
#include "include/base64.h"
#define BASE_ROOM_BINDSOCKET 64000
using namespace std;

#define MAX_SEARCH					10
#define PARTNER_DEFAULT				1							//系统默认的合伙商,即自己
#define MAX_NICK_LEN				36


enum
{
	NEW_UIN_SUCCESS,
	NEW_UIN_LOWER_VER,
	NEW_UIN_FAILED,
	NEW_UIN_BLOCKED,											//被封锁
};
class ImGiveGiftErr
{
public:
	enum
	{
		IM_GIFT_GIVE_SUCCESS,
		IM_GIFT_GIVE_FAILD,
		IM_GIFT_NOT_THIS_GIFT,					//加好友门槛不是这个礼物
		IM_GIFT_IS_NOT_CHARM_GIFT,				//不是魅力礼物
		IM_GIFT_NOT_HAVE_ENOUGH_MONEY,			//钱不够
		IM_GIFT_GIVE_GIFT_IN_GAME,				//游戏中不能送礼物
		IM_GIFT_NO_HAVE_THIS_GIFT,				//没有这个礼物
		IM_GIFT_WITHOUT_ADDFRIEND,				//不需要需要添加好友
		IM_GIFT_WITH_ADDFRIEND,					//需要添加好友
		IM_GIFT_IN_BLACKLIST,					//在黑名单中
		IM_GIFT_IS_NOT_FRIEND,					//不是好友关系
		IM_GIFT_IS_REPORTED,					//被举报
	};
};

class ImDeleteFriendErr
{
public:
	enum
	{
		IM_DELETE_SUCCESS,				//删除好友成功
		IM_DELETE_FAIL,					//删除好友失败
		IM_DELETE_FRIEND,				//主动删除好友
		IM_FRIEND_DELETE_ME,			//被好友删除
		IM_IS_NOT_FRINED,				//不在好友列表中
	};
};

class ImBlackListHandleErr
{
public:
	enum
	{
		IM_BLACKLIST_HANDLE_SUCCESS,		//添加或删除黑名单成功
		IM_BLACKLIST_HANDLE_IN_BLACKLIST,	//对方已在黑名单中
		IM_BLACKLIST_HANDLE_NOT_IN_BLACKLIST,	//对方不在你的黑名单中
	};
};
class ImMsgErr
{
public:
	enum
	{
		IM_SEND_MSG,					//发消息
		IM_PRESENT_GIFT,				//送礼物
		IM_IS_NOT_FRIEND,				//不是好友关系
		IM_IN_BLACKLIST,				//在黑名单中		
	};
};
class ImNotifyInfo
{
public:
	enum
	{
		IM_NOTIFY_SYNC_MONEY,			//资金账户同步
		IM_NOTIFY_SYS_MSG,				//新的系统通知
	};
};

enum 
{
	POPUPMSG_TYPE_PRESENTMONEY = 0x0002,						//有新资金赠送
};

class ForceOffline
{
public:
	enum 
	{
		FORCEOFF_ANOTHER = 0x10,		//被踢下线
		FORCEOFF_BLOCKED,				//账号封锁
		FORCEOFF_MODIFY_PASSWORD,		//修改密码
	};
};

class CTinyLordLevel
{
public:
	enum
	{
		LORD_LEVEL_NONE,										//无爵位
		LORD_LEVEL_BARON,										//男爵
		LORD_LEVEL_VISCOUNT,									//子爵
		LORD_LEVEL_EARL,										//伯爵
		LORD_LEVEL_MARQUESS,									//侯爵
		LORD_LEVEL_DUKE,										//公爵
		LORD_LEVEL_KING,										//国王
		LORD_LEVEL_LIMIT,										//爵位限制
	};
	static std::string LordLevelName[LORD_LEVEL_LIMIT];
	static string GetLordLevelName(uint8 lordLevel)
	{
		string lordstr = "爵位";
		switch (lordLevel)
		{
		case CTinyLordLevel::LORD_LEVEL_NONE:		
			lordstr="非爵位";
			break;
		case CTinyLordLevel::LORD_LEVEL_BARON:		
			lordstr="男爵";
			break;
		case CTinyLordLevel::LORD_LEVEL_VISCOUNT:	
			lordstr="子爵";
			break;
		case CTinyLordLevel::LORD_LEVEL_EARL:		
			lordstr="伯爵";
			break;
		case CTinyLordLevel::LORD_LEVEL_MARQUESS:	
			lordstr="侯爵";
			break;
		case CTinyLordLevel::LORD_LEVEL_DUKE:	
			lordstr="公爵";
			break;
		case CTinyLordLevel::LORD_LEVEL_KING:	
			lordstr="国王";
			break;
		}
		return lordstr;
	}
};




class CTaoleGlobleUserType
{
public:
	enum
	{
		USER_GLOBLE_TYPE_NONE			= 0,					//无身份
		USER_GLOBLE_TYPE_SINGER			= 1,					//公司签约歌手
		USER_GLOBLE_TYPE_AGENT			= 2,					//公司签约代理
		USER_GLOBLE_TYPE_CONTACT_STAFF	= 4,					//公司客服
		USER_GLOBLE_TYPE_SALES			= 8,					//公司销售
		USER_GLOBLE_TYPE_PRIVILEGES		= 16,					//特权标志
		USER_GLOBLE_TYPE_COO_ASSISTANT	= 20,					//副站长标志
		USER_GLOBLE_TYPE_COO			= 22,					//站长标志
		USER_GLOBLE_TYPE_MUSIC_SOCIETY  = 24,					//乐团标志
		USER_GLOBLE_TYPE_DANCER			= 26,					//舞蹈演员标志
		USER_GLOBLE_TYPE_FUHAO			= 28,					//富豪标志
		USER_GLOBLE_TYPE_STAR			= 30,					//艺人明星
		USER_GLOBLE_TYPE_COMPERE		= 32,					//超级主持
		USER_GLOBLE_TYPE_COMPEREMAN		= 34,					//MC男主持
		USER_GLOBLE_TYPE_PATROL			= 36,					//巡查
		USER_GLOBLE_TYPE_OPERATION		= 38,					//运营
		USER_GLOBLE_TYPE_BABY1			= 40,					//宝贝1
		USER_GLOBLE_TYPE_BABY2			= 42,					//宝贝2
		USER_GLOBLE_TYPE_BABY3			= 44,					//宝贝3
		USER_GLOBLE_TYPE_BABY4			= 46,					//宝贝4
		USER_GLOBLE_TYPE_BABY5			= 48,					//宝贝5
		USER_GLOBLE_TYPE_BABY6			= 50,					//宝贝6
	};
	static bool IsActor(uint8 usertype)
	{
		return (usertype == USER_GLOBLE_TYPE_SINGER 
			 || usertype == USER_GLOBLE_TYPE_MUSIC_SOCIETY 
			 || usertype == USER_GLOBLE_TYPE_DANCER 
			 || usertype == USER_GLOBLE_TYPE_STAR) ;
	}

	static bool IsGlobalMsgFree(uint8 usertype)
	{
		
		return (usertype == USER_GLOBLE_TYPE_CONTACT_STAFF 
			 || usertype == USER_GLOBLE_TYPE_SALES 
			 || usertype == USER_GLOBLE_TYPE_COO 
			 || usertype == USER_GLOBLE_TYPE_COO_ASSISTANT);
	}

	static string GetLordLevelName(uint8 usertype)
	{
		string userTypeStr = "";
		switch (usertype)
		{
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_NONE:		
			userTypeStr="无特殊身份";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SINGER:		
			userTypeStr="艺人";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_AGENT:		
			userTypeStr="代理";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF:		
			userTypeStr="客服";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES:		
			userTypeStr="商务代表";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES:		
			userTypeStr="特权";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO:		
			userTypeStr="站长";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO_ASSISTANT:		
			userTypeStr="副站长";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_MUSIC_SOCIETY:		
			userTypeStr="乐团";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_DANCER:		
			userTypeStr="舞星";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_FUHAO:		
			userTypeStr="富豪";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_STAR:		
			userTypeStr="明星";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPERE:		
			userTypeStr="超级主持";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPEREMAN:		
			userTypeStr="MC男主持";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PATROL:		
			userTypeStr="巡查";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_OPERATION:		
			userTypeStr="运营";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY1:		
			userTypeStr="宝贝1";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY2:		
			userTypeStr="宝贝2";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY3:		
			userTypeStr="宝贝3";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY4:		
			userTypeStr="宝贝4";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY5:		
			userTypeStr="宝贝5";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY6:		
			userTypeStr="宝贝6";
			break;
		

		}
		return userTypeStr;
	}
	
	static uint8 GetLordLevelType(string typeName)
	{
		uint8 userType = USER_GLOBLE_TYPE_NONE;
		if (typeName == "无特殊身份")
		{
			userType = USER_GLOBLE_TYPE_NONE;
		}
		else if (typeName == "艺人")
		{
			userType = USER_GLOBLE_TYPE_SINGER;
		}
		else if (typeName == "代理")
		{
			userType = USER_GLOBLE_TYPE_AGENT;
		}
		else if (typeName == "客服")
		{
			userType = USER_GLOBLE_TYPE_CONTACT_STAFF;
		}
		else if (typeName == "商务代表")
		{
			userType = USER_GLOBLE_TYPE_SALES;
		}
		else if (typeName == "特权")
		{
			userType = USER_GLOBLE_TYPE_PRIVILEGES;
		}
		else if (typeName == "站长")
		{
			userType = USER_GLOBLE_TYPE_COO;
		}
		else if (typeName == "副站长")
		{
			userType = USER_GLOBLE_TYPE_COO_ASSISTANT;
		}
		else if (typeName == "乐团")
		{
			userType = USER_GLOBLE_TYPE_MUSIC_SOCIETY;
		}
		else if (typeName == "舞星")
		{
			userType = USER_GLOBLE_TYPE_DANCER;
		}
		else if (typeName == "富豪")
		{
			userType = USER_GLOBLE_TYPE_FUHAO;
		}
		else if (typeName == "明星")
		{
			userType = USER_GLOBLE_TYPE_STAR;
		}
		else if (typeName == "超级主持")
		{
			userType = USER_GLOBLE_TYPE_COMPERE;
		}
		else if (typeName == "MC男主持")
		{
			userType = USER_GLOBLE_TYPE_COMPEREMAN;
		}
		else if (typeName == "巡查")
		{
			userType = USER_GLOBLE_TYPE_PATROL;
		}
		else if (typeName == "运营")
		{
			userType = USER_GLOBLE_TYPE_OPERATION;
		}
		else if (typeName == "宝贝1")
		{
			userType = USER_GLOBLE_TYPE_BABY1;
		}
		else if (typeName == "宝贝2")
		{
			userType = USER_GLOBLE_TYPE_BABY2;
		}
		else if (typeName == "宝贝3")
		{
			userType = USER_GLOBLE_TYPE_BABY3;
		}
		else if (typeName == "宝贝4")
		{
			userType = USER_GLOBLE_TYPE_BABY4;
		}
		else if (typeName == "宝贝5")
		{
			userType = USER_GLOBLE_TYPE_BABY5;
		}
		else if (typeName == "宝贝6")
		{
			userType = USER_GLOBLE_TYPE_BABY6;
		}

		return userType;
	}
};


enum {
	CHANGE_MONEY_SUCCESS,										//划账成功
	CHANGE_MONEY_FAILED,										//划账失败
};  


enum
{
	UDP_VER_01				=		0x001,
	UDP_VER_02				=       0x002,
	UDP_VER_03				=		0x003,
	UDP_VER_04				=		0x004,						//增加网站后台功能.
	UDP_VER_05				=		0x005,						//增加网站后台功能.
	UDP_VER_O6				=		0x006,						//简化添加好友流程		2013/7/22
	UDP_VER_07				=		0x007,						//消息已读
	UDP_VER_08				=		0x008,						//增加彩钻用户进房间数目限制
	UDP_VER_09				=		0x009,						//移动IM
	UDP_VER_10				=		0x010,						//客服聊天增加subUin
	UDP_VER_11				=		0x011,						//收藏房间，返回室主uin 我的创建的房间 踢下线提示
	UDP_VER_12				=		0x012,						//收藏房间返回房间信息版本号
	UDP_VER_13				=		0x013,
	UDP_VER_14				=		0x014,
	UDP_VER_15				=		0x015,						//取消绑定通知
	UDP_VER_16				=		0X016,						//乐滔分离
	UDP_VER_CURRENT			=       UDP_VER_16,
};

enum
{
	TCP_VER_01				=		0x002,
	TCP_VER_CURRENT			=       TCP_VER_01,
};

enum
{
	//MSG_STATUS_DEFAULT = 0,			
	MSG_STATUS_SENDED = 0,											//已送达
	MSG_STATUS_READED,											//已读
};

typedef enum
{
	NET_TYPE_DX,												//电信
	NET_TYPE_WT,												//电信
}NetTypeDefine;

enum
{
	UDP_SEND_TIMEOUT		=		3000,			//3 secs
	UDP_KEEPALIVE_INTERVAL	=		20*1000,		//20 secs
	UDP_MAX_SEND_ATTEMPTS	=		5,				//5 times
};

enum {
	UDP_ACK = 1,
	UDP_NEW_UIN,
	UDP_GET_CONTACTLIST,
	UDP_LOGIN,
	UDP_LOGOUT,
	UDP_KEEPALIVE,
	UDP_CHANGE_STATUS,
	UDP_UPDATE_CONTACT,
	UDP_MODIFY_USER,
	UDP_UPDATE_USER,
	UDP_SEND_MSG,
	UDP_SEARCH_RANDOM,
	UDP_SEARCH_CUSTOM,
	UDP_ADD_FRIEND,
	UDP_DEL_FRIEND,
	UDP_SEARCH_CUSTOM_ONLINE,
	UDP_SEARCH_SERVICE,

	UDP_CHANGE_PASSWD,		
	UDP_SEARCH_SECTION,
	UDP_CHANGE_MONEY,											//划帐
	UDP_GET_ROOM_ADDR,											//获得地址

	UDP_ADD_FAV_ROOM,											//增加房间收藏
	UDP_DEL_FAV_ROOM,											//删除房间收藏

	UDP_DEL_ADDFRIEND,
	UDP_DEL_FREIND_MYANDADD,

	UDP_HUAJB,													//划金币
	UDP_ZHUANYXB,												//金币转游戏币
	UDP_ANDROID_LOGIN,											//机器人登陆
	UDP_SEND_MSG_2,												//新的文字消息接口
	UDP_MODIFY_PASS,											//新增移动端修改密码接口

	UDP_SRV_USER_ONLINE = 0x0100,
	UDP_SRV_USER_OFFLINE,
	UDP_SRV_MULTI_ONLINE,
	UDP_SRV_STATUS_CHANGED,
	UDP_SRV_MESSAGE,
	UDP_SRV_SEARCH,
	UDP_SRV_IPCMD,
	UDP_SRV_IPCMD_RESPOND,

	//account
	UDP_SRV_ACCOUNT,

	UDP_SRV_NEW_VER,
	UDP_SRV_FORCE_OFFLINE,										//强制用户离线
	UDP_SRV_CHANGE_MONEY,										//通知划帐

	UDP_SRV_WEB_NOTIFY,											//通过web打开的通知
	UDP_SRV_ALBUM,												//下推相册
	UDP_SRV_FAVBLOG,											//下推Blog收藏列表
	UDP_SRV_POPUP_MSG,											//下推弹出消息

	UDP_SRV_FAVROOM,
	UDP_SRV_MINIMSG,											//通知迷你消息
	UDP_SRV_CUSTOM_SYSMSG,										//用户定制的系统消息
	UDP_SRV_LJXF,												//礼金消费金额

	UDP_MANCMD = 0x0400,										//管理指令

	UDP_SIG_START  = 0x0500,

	UDP_SIG_REQRES,												//请求通讯资源
	UDP_SIG_INVITE,
	UDP_SIG_NOTIFY,
	UDP_SIG_ACCEPT,
	UDP_SIG_REFUSE,
	UDP_SIG_ACK,
	UDP_SIG_BYE,
	UDP_SIG_CANCELINVITE,

	UDP_REQ_RES = 0x0600,										//请求资源
	UDP_GET_VCODE,												//请求验证码

	UDP_SIG_END  = 0x0700,
	UDP_SEND_ISINPUT,											//正在输入
	UDP_USER_INFO_UPDATE,										//后台修改用户信息
	UDP_MESSAGE_IS_READED,										//消息已读
	UDP_GIVE_GIFT,												//送礼物
	UDP_ADD_BLACKLIST,											//添加黑名单
	UDP_GET_BLACKLIST,
	UDP_DELETE_BLACKLIST,
	UDP_UPDATE_REMARK,											//修改备注
	UDP_UPDATE_COORDINATE,										//更新坐标
	UDP_USER_DETAIL_INFO_GET,									//获取用户详情
	UDP_USER_DETAIL_INFO_UPDATE,								//修改用户详情
	UDP_S2C_RELOGIN,											//用户重新认证
	UDP_C2S_RELOGIN,											//客户端认证请求
	UDP_S2C_RELOGIN_REPLY,										//认证结果0 成功， 1 失败
	UDP_C2S_RELOGIN_REPLY,										//认证成功之后，客户端上传状态
	UDP_ISNOT_FRIEND,											//不是好友关系
	UDP_C2S_UPLOAD_DEVICE_INFO,									//上传设备唯一识别码，和设备类型
	UDP_S2C_UPLOAD_DEVICE_INFO,									//下发用户唯一识别码
	UDP_C2S_UPLOAD_PUSH_TOKEN,									//上传消息推送ID
	UDP_S2C_UPLOAD_PUSH_TOKEN,									//下发消息推送ID
	UDP_S2C_GIVE_GIFT,											//服务器下发送礼物是否成功
	UDP_S2C_NEW_GIFT,											//收到新礼物
	UDP_S2C_MISSION_COMPLETED_NOTICE,							//任务完成通知
	UDP_C2S_GET_SERVICE_LIST,									//获取客服列表
	UDP_S2C_GET_SERVICE_LIST,									//返回客服列表
	UDP_C2S_GET_PREROGATIVE_ICON,								//特权图标
	UDP_S2C_GET_PREROGATIVE_ICON,								//下发特权图标
	UDP_C2S_MOBILE_NUMBER_LOGIN,								//手机号登陆
	UDP_C2S_GET_URL,											//动态下发url
	UDP_S2C_GET_URL,
	UDP_S2C_WEATH_AND_CHARM_VALUE,								//下发魅力值和财富值相关信息
	UDP_C2S_UPDATE_PUSH_TIMES,									//跟新消息推送计数器
	UD_S2C_NEW_SITUATION_NOTIFY_USER,							//新动态通知好友
	UDP_S2C_NEW_REVIEW_NOTIFY_USER,								//新评论通知
	UDP_S2C_NOTICE_NEW,											//通知
	UDP_C2S_BINGDING_NOTIFY,									//绑定通知
	UDP_S2C_BINGDING_NOTIFY,	
	UDP_S2C_ROOM_PORT_LIST,											//房间绿色通道端口号
	UDP_C2S_ADD_NEW_CONN,										//授权登录前像session中增加connection
	UDP_S2C_ATTPARTNER_LIST,									//关注列表
	UDP_C2S_GET_URL_IP,											//获取url对应iP
	UDP_S2C_CANCEL_BINGDING_NOTIFY,								//取消绑定通知
};

enum
{
	UDP_UPDATE_CUSTOMFACE,										//修改自定义头像
	UDP_UPDATE_LORDLEVEL,										//修改爵位
	UDP_UPDATE_LEVEL,											//修改会员
};

enum {
	MSG_TEXT,
	MSG_AUTO_REPLY,
	MSG_AUTH_ACCEPTED,
	MSG_AUTH_REQ,
	MSG_AUTH_REJECTED,
	MSG_ADDED,
	MSG_TCP_REQUEST,
	MSG_TCP_ACCEPTED,
	MSG_TCP_REJECTED,
	MSG_XML,
	MSG_UPGRADE,
	MSG_FILTER,
	MSG_FILTER_ONLINE,
	MSG_XML_AUTH,												//xml权限消息，用于会员服务
	MSG_NOTIFY,													//系统通知消息,立即弹出notify wnd
	MSG_PLUGIN,													// 插件之间通信的消息 [8/5/2003 9:49 why]
	MSG_NEW_SYSMSG,
	MSG_PLUGIN_NEW,												//插件之间通信的消息，需要进行限制，如频率限制等　
	MSG_POPMSG, //

	MSG_IMAGE,											//图片
	MSG_VOICE,											//音频
	MSG_VIDEO,											//视屏
	MSG_LOCATION,										//位置
	MSG_CONTACT,										//名片
	MSG_GIFT,											//礼物
	MSG_SNAP_PICTURE,									//阅后即焚
	MSG_IMAGE_TEXT,										//文字和图片组合消息
	MSG_NEED_TRANS_SRCUIN,								//需要把srcuin替换成10000
	MSG_NOT_NEED_TRANS_SRCUIN,							//不需要把srcuin替换成10000
	MSG_NEWS,											//公众账号消息
	MSG_ROOM,											//推进房间消息
	MSG_EXPRESSION,										//表情消息
	MSG_TUIBO,

	MSG_COMPLEX = 249,										//复合类型，定义时没有充足的理由不要越过此字段
};

enum
{
	VCODE_ACTION_TYPE_ADDFRIEND,								//添加好友
	VCODE_ACTION_TYPE_INVITE,									//邀请

	VCODE_ACTION_TYPE_MAX = VCODE_ACTION_TYPE_INVITE,
};

enum {
	ADD_FRIEND_ACCEPTED,
	ADD_FRIEND_AUTH_REQ,
	ADD_FRIEND_REJECTED,
	ADD_FRIEND_TOO_FAST,
	ADD_FRIEND_VCODE_NOT_MATCH,
	ADD_FRIEND_VCODE_OUT_TIME,
	ADD_FRIEND_IS_REPORTED,			//被举报
};

enum {
	LOGIN_SUCCESS,
	LOGIN_INVALID_UIN,
	LOGIN_WRONG_PASSWD,
	LOGIN_LOCKED,
	LOGIN_FAILED,
	LOGIN_LOW_VER,
	LOGIN_OTHER_DEVICE_LOGIN,
	LOGIN_USER_LAST_SCAN,					//最后一次是扫描登录
	LOGIN_USER_LAST_ACCREDIT,						//最后一次是授权登录
	LOGIN_THIRDPARTY_REAUTH,				//需要重新授权
};



enum {
	STATUS_ONLINE,
	STATUS_OFFLINE,
	STATUS_AWAY,
	STATUS_INVIS,
	NR_STATUS
};

enum
{
	LOGIN_DEVICE_PC = 1<<1,
	LOGIN_DEVICE_IOS = 1<<2,
	LOGIN_DEVICE_ANDROID = 1<<3,
};

union TransTaxRate
{
	struct
	{
		uint8 generalTrans:1;								//普通用户是否允许划帐
		uint8 generalTax:7;									//普通用户允许划帐税率%
		uint8 lowVipTrans:1;								//低会用户是否允许划帐
		uint8 lowVipTax:7;									//低会用户允许划帐税率%
		uint8 midVipTrans:1;								//中会用户是否允许划帐
		uint8 midVipTax:7;									//中会用户允许划帐税率%
		uint8 higherVipTrans:1;								//高会用户是否允许划帐			
		uint8 higherVipTax:7;								//高会用户允许划帐税率%		
	};
	uint32 transTax;										//会员划帐税率
};


class PassWdType
{
public:
	enum
	{
		IM_UIN_PASSWD,		//用户ID登录
		IM_PHONE_NUMBER_PASSWD,		//模糊登录(uin/phonenum登录)
	};
};
enum
{
	//附加参数的枚举值
	IM_USER_LOGIN,			 //客户端登陆(获取好友列表/PC登陆/手机用户从登陆界面登陆/)
	IM_USER_RELOGIN,		 //用户重新认证
	IM_USER_GET_CONTACT,	 //客户端主动获取好友列表
	IM_USER_NOT_FIRST_LOGIN, //手机用户打开屏幕之后直接login
};

class AuthorizationLogin
{
public:
	enum
	{
		AUTHORIZATION_LOGIN,	//授权登录
		BINGDING_UIN,			//绑定帐号
		CANCEL_BINGING,			//解除绑定
		MANUAL_BINDING,			//手动修改绑定
	};
};


#pragma pack(1)
union	Customface						
{
	unsigned short customFace;
	struct {
		unsigned short userNew:1;								//是否设置了自定义头像			
		unsigned short newFace:15;								//头像版本号
	};
};
#pragma pack()

class LoginResult {
public:
	uint16		state;											//返回状态
	uint32		ip;												//公网IP
	uint8		level;											//用户级别
	uint16		levelEndDays;									//会员还有多长时间结束,用于提醒用户续费
	uint8		lordLevel;										//爵位级别
	uint32		right;											//权限
	uint32		onlinetime;										//总在线时长
	uint64		cash;											//现金
	uint32		infoVer;										//用户资料版本
	uint32		friendVer;										//好友信息版本	
	uint32		friendListVer;									//好友列表版本号
	Customface  customFace;
	string		sessionKey;										
	uint16		usertype;										//用户类型，客服，歌手之类
	uint8		richerOrder;									//富翁排行
	uint32		m_urlVer;										//url版本号
	
	LoginResult()
	{
		init();
	}
	void init()
	{
		state = 0;
		ip = 0;
		right = level = 0;
		onlinetime = 0;
		cash = 0;
		infoVer = 0;
		friendVer = 0;
		friendListVer = 0;
		sessionKey = "";
		usertype = 0;
		richerOrder = 0;
		m_urlVer = 0;
	}
};



#pragma pack(1)

class ParterInfo
{
	
public:

	ParterInfo(uint32 pid = 0) : partnerID(pid)
	{
		newUserPresent		= 500;
		receiverRatio		= 50;
		companyTaxRatio		= 20;
		roomHostTaxRatio	= 5;
		prizePoolRatio		= 100 - receiverRatio - companyTaxRatio - roomHostTaxRatio;

		prize_recv_ratio	= 40;
		prize_comp_ratio	= 15;
		prize_host_ratio	= 20;
		prize_pool_ratio	= 100 - prize_recv_ratio - prize_comp_ratio - prize_host_ratio;

		diamon_receiver		= 70;									//收礼人收入比
		diamon_host			= 1;										//室主比例
		diamon_pid			= 15;											//站点比例
		diamon_company		= 100 - diamon_receiver - diamon_host -diamon_pid;										//公司收入比例
		present_radioType	= 0;
		greate_giftprice	= 1000000;
		greate_present		= 1000000;
		globle_redpaper		= 5000000;
		greate_disp_times	= 2;
		bRedpaperOff		= false;		
		currPrizedRatio		= 800;
		prizeIncoming		= 0;
		prizeOutgoing		= 0;

		automic				= true;
		automic_start		= 660;
		automic_end			= 1020;

		generalAccessMultiRoom=0;
		lowVipAccessMultiRoom=0;
		midVipAccessMultiRoom=0;
		hightVipAccessMultiRoom=1;
		richerAccessMultiRoom=1;
		agentAccessMultiRoom=1;
		supperAccessMultiRoom=1;

		generalTrans		= 0;								//普通用户是否允许划帐
		generalTax			= 0;								//普通用户允许划帐税率%
		lowVipTrans			= 1;								//低会用户是否允许划帐
		lowVipTax			= 8;								//低会用户允许划帐税率%
		midVipTrans			= 1;								//中会用户是否允许划帐
		midVipTax			= 5;								//中会用户允许划帐税率%
		higherVipTrans		= 1;								//高会用户是否允许划帐			
		higherVipTax		= 0;								//高会用户允许划帐税率%		


		lastMonthTax		= 0;
		currMonthTax		= 0;
		broadCasePrice		= 100000;
		lastUpdate			= 0;

		presentOnMicTimelimit= 0;
		presentOnMicPerMin	= 0;

		status				= 2;
		micPresentTimeout   = 0;
		sRoomAccess			= "";

		diamon_gift_flag	= 0;									//钻石礼物开关
		diamon_action_flag	= 0;									//钻石礼物特效开关
		diamon_action_limit	= 0;									//钻石礼物
		duobao_treasure_open= 0;
	}
	virtual ~ParterInfo(){}
	uint32	partnerID;											//合作商ID
	string	username;											//合作商登陆用户名，注册后，默认指配username.XXXXXX.com域名给商家
	string	partnerName;										//合作商全称
	string	domainName;											//合作商自用域名
	string	domainNameEx;										//备用域名
	string	moneyName;											//虚拟币名称
	uint32 lastUpdate;

	uint16	newUserPresent;										//新注册用户赠送虚拟币金额
	uint8	receiverRatio;										//收礼人收入比例
	uint8	companyTaxRatio;									//公司税率设置
	uint8	roomHostTaxRatio;									//室主比例设置
	uint8	prizePoolRatio;										//奖池比例

	uint8	diamon_receiver;									//收礼人收入比
	uint8	diamon_company;										//公司收入比例
	uint8	diamon_host;										//室主比例
	uint8	diamon_pid;											//站点比例

	uint8   prize_recv_ratio;									//幸运礼物收礼人比例
	uint8	prize_comp_ratio;									//幸运礼物公司比例
	uint8	prize_host_ratio;									//幸运礼物室主比例
	uint8	prize_pool_ratio;									//幸运礼物奖池比例

	uint8	present_radioType;									//大奖广播类型,0默认是根据刷礼总额大于greate_present, 1是根据礼物单价大于
	uint32	greate_giftprice;									//大奖广播类型为1时,当礼物单价大于该值发送广播
	uint32	greate_present;										//广播大奖值默认１００Ｗ
	uint32	greate_disp_times;									//大奖播放奖数
	uint32  globle_redpaper;									//全站飘礼金额
	bool	bRedpaperOff;										//红包开关

	uint8	automic;											//自动排麦
	uint16	automic_start;										//自动排麦开始时间（当天的第Ｎ分钟）
	uint16	automic_end;										//自动排麦结束时间（当天的第Ｎ分钟)

	uint16	currPrizedRatio;									//中奖比例
	uint16	prize_rate2;										//幸运礼物中奖比例
	uint64	prizeIncoming;										//奖池收入
	uint64	prizeOutgoing;										//奖池支出


	uint64	lastMonthTax;										//上个月税收
	uint64	currMonthTax;										//本月税收	
	uint32  broadCasePrice;										//小喇叭价格

	uint8	presentOnMicTimelimit;								//上麦送虚拟币起始时间，0为不送，小于此值不送，时间分钟
	uint32	presentOnMicPerMin;									//达到或超过presentOnMicTime时，每分钟送虚拟币数额

	string  sRoomAccess;											//字符串形态进房间限制
	string	giftVer;											//虚拟礼物版本号
	string  stampVer;											//印章版本号
	string  sortVer;											//富豪排序版本号
	string	giftVerNew;											//新礼物版本号
	uint8	gift_vod;											//点歌礼物适用范围

	uint8  status;												//0:关闭状态 1:试运营期 2:正式运营

	uint32	host_type;											//室主税收是否进入礼金账户总开关
	uint32  micPresentTimeout;									//上麦奖励领取超时时间

	uint8  diamon_gift_flag;									//钻石礼物开关
	uint8  diamon_action_flag;									//钻石礼物特效开关
	uint32 diamon_action_limit;									//钻石礼物
	uint8  duobao_treasure_open;								//夺宝活动开关

	union
	{
		struct
		{
			uint8 generalAccessMultiRoom:1;						//普通用户进入多个房间许可
			uint8 lowVipAccessMultiRoom:1;						//低会进入多个房间许可
			uint8 midVipAccessMultiRoom:1;						//中会进入多个房间许可
			uint8 hightVipAccessMultiRoom:1;					//高会进入多个房间许可
			uint8 richerAccessMultiRoom:1;						//富翁进入多个房间许可
			uint8 agentAccessMultiRoom:1;						//代理进入多个房间许可
			uint8 supperAccessMultiRoom:1;						//超管进入多个房间许可
			uint8 reserved:1;					
		};
		uint8	roomAccess;										//同一机器进多个房间限制
	};
	union 
	{
		struct
		{
			uint8 generalTrans:1;								//普通用户是否允许划帐
			uint8 generalTax:7;									//普通用户允许划帐税率%
			uint8 lowVipTrans:1;								//低会用户是否允许划帐
			uint8 lowVipTax:7;									//低会用户允许划帐税率%
			uint8 midVipTrans:1;								//中会用户是否允许划帐
			uint8 midVipTax:7;									//中会用户允许划帐税率%
			uint8 higherVipTrans:1;								//高会用户是否允许划帐			
			uint8 higherVipTax:7;								//高会用户允许划帐税率%		
		};
		uint32 transTax;										//会员划帐税率
	};

	std::string BuildXMLInfoForClient(uint16 udpver)
	{
		CMarkup xmldoc;
		xmldoc.AddElem("pid", partnerID);
		xmldoc.AddElem("dm", domainName.length() ? domainName.c_str() : domainNameEx.c_str());
		xmldoc.AddElem("gdt", greate_disp_times);
		xmldoc.AddElem("bpc", broadCasePrice);
		string strAccess;
		if (udpver < UDP_VER_08)
		{
			if(sRoomAccess.length() > 13)
			{
				strAccess = sRoomAccess.substr(0, 13);
			}
			else
			{
				strAccess = sRoomAccess;
			}	
		}
		else
		{
			strAccess = sRoomAccess;
		}
		xmldoc.AddElem("rAc", strAccess.c_str());
		xmldoc.AddElem("tax", transTax);
		xmldoc.AddElem("pot", presentOnMicTimelimit);
		xmldoc.AddElem("ppm", presentOnMicPerMin);
		xmldoc.AddElem("mnn", moneyName.c_str());
		xmldoc.AddElem("giftv", giftVer.c_str());
		xmldoc.AddElem("dmex", domainNameEx.c_str());

#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}

	void ClientParseXML(std::string infoXml)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(infoXml.c_str());
		xmldoc.GetChildValue("pid", partnerID);
		xmldoc.GetChildValue("dm", domainName);
		xmldoc.GetChildValue("gdt", greate_disp_times);
		xmldoc.GetChildValue("bpc", broadCasePrice);
		xmldoc.GetChildValue("rAc", sRoomAccess);
		xmldoc.GetChildValue("tax", transTax);
		xmldoc.GetChildValue("pot", presentOnMicTimelimit);
		xmldoc.GetChildValue("ppm", presentOnMicPerMin);
		xmldoc.GetChildValue("mnn", moneyName);
		xmldoc.GetChildValue("giftv", giftVer);
		xmldoc.GetChildValue("dmex", domainNameEx);
	}


	std::string BuildXMLInfo()
	{
		TinyMarkup xmldoc;

		xmldoc.AddElem("pid", partnerID);			 
		xmldoc.AddElem("pname", talk_base::Base64::encode(partnerName).c_str());		
		xmldoc.AddElem("domain", domainName.c_str());			
		xmldoc.AddElem("money", talk_base::Base64::encode(moneyName).c_str());			
		xmldoc.AddElem("lastup", lastUpdate);

		xmldoc.AddElem("present", newUserPresent);		
		xmldoc.AddElem("recvRatio", receiverRatio);		
		xmldoc.AddElem("comRatio", companyTaxRatio);	
		xmldoc.AddElem("hostRatio", roomHostTaxRatio);	
		xmldoc.AddElem("poolRatio", prizePoolRatio);		
		xmldoc.AddElem("broadprice", broadCasePrice);
										
		xmldoc.AddElem("greategift", greate_present);		
		xmldoc.AddElem("greatedisp", greate_disp_times);	
										
		xmldoc.AddElem("automic", automic);			
		xmldoc.AddElem("automic_start", automic_start);		
		xmldoc.AddElem("automic_end", automic_end);		
										
		xmldoc.AddElem("currPrizedRatio", currPrizedRatio);
		xmldoc.AddElemInt64("prizeIncoming", prizeIncoming);
		xmldoc.AddElemInt64("prizeOutgoing", prizeOutgoing);
										
		xmldoc.AddElem("roomAccess", roomAccess);
		xmldoc.AddElem("transTax", transTax);
										
		xmldoc.AddElemInt64("lastMonthTax", lastMonthTax);
		xmldoc.AddElemInt64("currMonthTax", currMonthTax);
										
		xmldoc.AddElem("presentOnMicTimelimit", presentOnMicTimelimit);
		xmldoc.AddElem("presentOnMicPerMin", presentOnMicPerMin);
										
		xmldoc.AddElem("recv_ratio", prize_recv_ratio);
		xmldoc.AddElem("comp_ratio", prize_comp_ratio);
		xmldoc.AddElem("host_ratio", prize_host_ratio);
		xmldoc.AddElem("pool_ratio", prize_pool_ratio);
										
		xmldoc.AddElem("prize_rate2", prize_rate2);
										
		xmldoc.AddElem("domainNameEx", domainNameEx.c_str());

		xmldoc.AddElem("giftVer", giftVer.c_str());
		xmldoc.AddElem("gift_vod", gift_vod);
		xmldoc.AddElem("sRoomAccess", sRoomAccess.c_str());

#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}

	void ParseXML(std::string &infoXml)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(infoXml.c_str());

		xmldoc.GetChildValue("pid", partnerID);			 
		xmldoc.GetChildValue("pname", partnerName);	
		partnerName = talk_base::Base64::decode(partnerName);
		xmldoc.GetChildValue("domain", domainName);	
		xmldoc.GetChildValue("money", moneyName);
		moneyName = talk_base::Base64::decode(moneyName);
		xmldoc.GetChildValue("lastup", lastUpdate);

		xmldoc.GetChildValue("present", newUserPresent);		
		xmldoc.GetChildValue("recvRatio", receiverRatio);		
		xmldoc.GetChildValue("comRatio", companyTaxRatio);	
		xmldoc.GetChildValue("hostRatio", roomHostTaxRatio);	
		xmldoc.GetChildValue("poolRatio", prizePoolRatio);		
		xmldoc.GetChildValue("broadprice", broadCasePrice);

		xmldoc.GetChildValue("greategift", greate_present);		
		xmldoc.GetChildValue("greatedisp", greate_disp_times);	

		xmldoc.GetChildValue("automic", automic);			
		xmldoc.GetChildValue("automic_start", automic_start);		
		xmldoc.GetChildValue("automic_end", automic_end);		

		xmldoc.GetChildValue("currPrizedRatio", currPrizedRatio);
		xmldoc.GetChildValue("prizeIncoming", prizeIncoming);
		xmldoc.GetChildValue("prizeOutgoing", prizeOutgoing);

		xmldoc.GetChildValue("roomAccess", roomAccess);
		xmldoc.GetChildValue("transTax", transTax);

		xmldoc.GetChildValue("lastMonthTax", lastMonthTax);
		xmldoc.GetChildValue("currMonthTax", currMonthTax);

		xmldoc.GetChildValue("presentOnMicTimelimit", presentOnMicTimelimit);
		xmldoc.GetChildValue("presentOnMicPerMin", presentOnMicPerMin);

		xmldoc.GetChildValue("recv_ratio", prize_recv_ratio);
		xmldoc.GetChildValue("comp_ratio", prize_comp_ratio);
		xmldoc.GetChildValue("host_ratio", prize_host_ratio);
		xmldoc.GetChildValue("pool_ratio", prize_pool_ratio);

		xmldoc.GetChildValue("prize_rate2", prize_rate2);

		xmldoc.GetChildValue("domainNameEx", domainNameEx);

		xmldoc.GetChildValue("giftVer", giftVer);
		xmldoc.GetChildValue("gift_vod", gift_vod);
		xmldoc.GetChildValue("sRoomAccess", sRoomAccess);



	}


	void equal(ParterInfo &info)
	{
		partnerID			= info.partnerID;
		username			= info.username;
		partnerName			= info.partnerName;
		domainName			= info.domainName;		
		domainNameEx		= info.domainNameEx;
		moneyName			= info.moneyName;			
		lastUpdate			= info.lastUpdate;

		newUserPresent		= info.newUserPresent;		
		receiverRatio		= info.receiverRatio;		
		companyTaxRatio		= info.companyTaxRatio;	
		roomHostTaxRatio	= info.roomHostTaxRatio;	
		prizePoolRatio		= info.prizePoolRatio;		
		broadCasePrice		= info.broadCasePrice;

		prize_recv_ratio	= info.prize_recv_ratio;
		prize_comp_ratio	= info.prize_comp_ratio;
		prize_host_ratio	= info.prize_host_ratio;
		prize_pool_ratio	= info.prize_pool_ratio;

		prize_rate2			= info.prize_rate2;

		greate_present		= info.greate_present;		
		greate_disp_times	= info.greate_disp_times;
		globle_redpaper		= info.globle_redpaper;

		automic				= info.automic;					
		automic_start		= info.automic_start;		
		automic_end			= info.automic_end;		

		currPrizedRatio		= info.currPrizedRatio;
		prizeIncoming		= info.prizeIncoming;
		prizeOutgoing		= info.prizeOutgoing;
		roomAccess			= info.roomAccess;
		transTax			= info.transTax;


		lastMonthTax		= info.lastMonthTax;
		currMonthTax		= info.currMonthTax;
		presentOnMicTimelimit	= info.presentOnMicTimelimit;
		presentOnMicPerMin	= info.presentOnMicPerMin;

		giftVer				= info.giftVer;
		gift_vod			= info.gift_vod;
		sRoomAccess			= info.sRoomAccess;
	}
	template <class T>
	void BuildPacketForClient(T &out)
	{
		out <<	partnerID;
		if (domainName.length())
			out << domainName;
		else
			out << domainNameEx;
		out << 	greate_disp_times;
		out <<  broadCasePrice;
		out <<	roomAccess;
		out <<	transTax;
		out <<	presentOnMicTimelimit;
		out <<	presentOnMicPerMin;
		out <<	moneyName;
	}
	template <class T>
	void BuildPacket(T &out)
	{
		out << 	partnerID;			
		out << 	username;			
		out << 	partnerName;		
		out <<	domainName;			
		out << 	moneyName;			
		out <<	lastUpdate;

		out << 	newUserPresent;		
		out << 	receiverRatio;		
		out << 	companyTaxRatio;	
		out << 	roomHostTaxRatio;	
		out << 	prizePoolRatio;		
		out <<  broadCasePrice;

		out << 	greate_present;	
		out << 	greate_disp_times;	

		out << 	automic;				
		out << 	automic_start;		
		out << 	automic_end;		

		out << 	currPrizedRatio;
		out <<	prizeIncoming;
		out	<<	prizeOutgoing;

		out <<	roomAccess;
		out <<	transTax;

		out << lastMonthTax;
		out << currMonthTax;

		out << presentOnMicTimelimit;
		out << presentOnMicPerMin;

		out << prize_recv_ratio;
		out << prize_comp_ratio;
		out << prize_host_ratio;
		out << prize_pool_ratio;

		out << prize_rate2;

		out << domainNameEx;
		
		out << giftVer;
		out << gift_vod;
		out << sRoomAccess;
		out << status;
	}

	template <class T>
	void ClientParsePacket(T &in)
	{
		in >>	partnerID;
		in >> 	domainName;
		in >> 	greate_disp_times;
		in >>	broadCasePrice;
		in >>	roomAccess;
		in >>	transTax;
		in >>	presentOnMicTimelimit;
		in >>	presentOnMicPerMin;
		in >>   moneyName;

	}


	template <class T>
		void ParsePacket(T &in)
	{
		in >> partnerID;			
		in >> username;			
		in >> partnerName;		
		in >> domainName;			
		in >> moneyName;
		in >> lastUpdate;


		in >> newUserPresent;		
		in >> receiverRatio;		
		in >> companyTaxRatio;	
		in >> roomHostTaxRatio;	
		in >> prizePoolRatio;
		in >> broadCasePrice;

		in >> greate_present;		
		in >> greate_disp_times;	

		in >> automic;				
		in >> automic_start;		
		in >> automic_end;		

		in >> currPrizedRatio;		
		in >> prizeIncoming;
		in >> prizeOutgoing;

		in >> roomAccess;
		in >> transTax;

		in >> lastMonthTax;
		in >> currMonthTax;

		in >> presentOnMicTimelimit;
		in >> presentOnMicPerMin;

		in >> prize_recv_ratio;
		in >> prize_comp_ratio;
		in >> prize_host_ratio;
		in >> prize_pool_ratio;

		in >> prize_rate2;
		 
		in >> domainNameEx;

		in >> giftVer;
		in >> gift_vod;
		in >> sRoomAccess;
		in >> status;
	}

};



class TinyUserInfo
{
	typedef union TinyUserKey
	{
		uint32 pid;												//商家id
		uint32 uin;												//用户id
		uint64 userKey;											//联合key
	}TinyUserKey;
public:
	TinyUserKey uid;											//用户ＩＤ
	string passwd;												//password
	uint8 face;													//头像
	string nickname;											//昵称
	string province;											//省份
	uint8 auth;													//好友添加认证方式 0, 不需要认证; 1需要认证;2不允许任何人添加
	uint32 oldMsgID;											//读取信息ID											
	uint8 gender;												//性别
	uint8 age;													//年龄
	string city;												//城市
	string country;												//国家
	string email;												//邮箱地址
	uint32 onlinetimes;											//总在线时长
	uint8 locked;												//帐号是否被锁定
	uint8 hide;													//是否随身

	string address;												//地址
	string zipcode;												//邮编
	string tel;													//电话
	string name;												//名字
	uint8 blood;												//血型
	string college;												//学校
	string profession;											//职业
	string homepage;											//个人网页
	string intro;												//个人介绍
	uint8 level;												//会员级别0, 普通用户 1低会2中会3高会4白金会员
	uint16 LevelEndtime;										//会员结束时间
	uint8 lordLevel;											//用户爵位
	uint16 customFace;											//自定义图像
	uint32 promoteid;											//推广人ID

	uint64 money;												//用户资金
	uint64 received;											//用户收礼帐户余额
	uint8 accountStatus;										//用户资金帐户状态
	uint8  flowinout;											//资金进出限制



	template <class T>
		void BuildPacket(T &out)
	{
		out << uid.pid << uid.uin << passwd << face << nickname << province << auth << oldMsgID << gender << age << city << country;
		out << email <<  onlinetimes << locked << hide;
		out << address << zipcode << tel << name << blood << college << profession << homepage;
		out << intro << level << LevelEndtime << lordLevel << customFace;

		out << money << received << accountStatus << flowinout;
	}

	template <class T>
		void ParsePacket(T &in)
	{
		in >> uid.pid >> uid.uin >> passwd >> face >> nickname >> province >> auth >> oldMsgID >> gender >> age >> city >> country;
		in >> email >>  onlinetimes >> locked >> hide;
		in >> address >> zipcode >> tel >> name >> blood >> college >> profession >> homepage;
		in >> intro >> level >> LevelEndtime >> lordLevel >> customFace;

		in >> money >> received >> accountStatus >> flowinout;
	}
};



#pragma pack()

class VipLevel
{
private:
	VipLevel(){};
public:
	enum{
		NOT_VIP,
		JUNION_VIP,
		MIDDLE_VIP,
		HIGHER_VIP,
		GOLD_VIP,										//白金VIP
		DIAMOND_BLACK_VIP,								//黑钻VIP
		DIAMOND_RED_VIP,								//红钻VIP
		DIAMOND_YELLOW_VIP,								//黄钻VIP
		DIAMOND_GREEN_VIP,								//绿钻VIP
		DIAMOND_BLUE_VIP,								//蓝钻VIP
		DIAMOND_PINK_VIP,								//粉钻VIP
		DIAMOND_PURPLE_VIP,								//紫钻VIP 
		DIAMOND_COLOUR_VIP,								//彩钻VIP
		LIMIT_VIP
	};
	static string GetLevelName(uint8 nlevel)
	{
		string levelname = "会员";
		switch (nlevel)
		{
		case  VipLevel::NOT_VIP:
			levelname = "非会员";
			break;
		case VipLevel::JUNION_VIP:
			levelname="初级会员";
			break;
		case VipLevel::MIDDLE_VIP:
			levelname = "中级会员";
			break;
		case VipLevel::HIGHER_VIP:
			levelname = "高级会员";
			break;
		case VipLevel::GOLD_VIP:
			levelname = "白金会员";
			break;
		case VipLevel::DIAMOND_BLACK_VIP:
			levelname = "黑钻会员";
			break;
		case VipLevel::DIAMOND_RED_VIP:
			levelname = "红钻会员";
			break;
		case VipLevel::DIAMOND_YELLOW_VIP:
			levelname = "黄钻会员";
			break;
		case VipLevel::DIAMOND_GREEN_VIP:
			levelname = "绿钻会员";
			break;
		case VipLevel::DIAMOND_BLUE_VIP:
			levelname = "蓝钻会员";
			break;
		case VipLevel::DIAMOND_PINK_VIP:
			levelname = "粉钻会员";
			break;
		case VipLevel::DIAMOND_PURPLE_VIP:
			levelname = "紫钻会员";
			break;
		case  VipLevel::DIAMOND_COLOUR_VIP:
			levelname = "彩钻会员";
			break;
		}
		return levelname;
	}
};


/************************************************************************/
/*                   请求网站房间所在的URL                         */
/************************************************************************/
enum REQ_URL_ROOMTYPE
{
	URL_VIDEOROOM,				//视频聊天的大厅
	URL_GAMEROOM,
	URL_SELF,
	URL_MANGER,					//网站管理后台
};
class IM_UIN
{
private:
	IM_UIN();
public:
	enum RANGE
	{
		SYSTEM_UIN = 10000,			//系统号码
		SERVICE_UIN = 10001,		//客服号
	};
};


class BlockType
{
public:
	enum 
	{
		BLOCK_TYPE_UIN	= 0,										//号码被封锁
		BLOCK_TYPE_IP,												//IP被封锁
		BLOCK_TYPE_MAC,												//机器被封锁
	};
};

class CWingPCInfo
{
public:
	CWingPCInfo()
	{
		Reset();
	};
	void Reset()
	{
		m_sPCMacID = "";
		m_nWingMac = 0;
		m_diskSerNum = "";
		m_sBoardSerNum = "";
		m_sCpuID = "";
		m_sBiosSerNum = "";
	}
	string	m_sPCMacID;
	uint64	m_nWingMac;
	string  m_diskSerNum;
	string	m_sBoardSerNum;
	string  m_sCpuID;
	string	m_sBiosSerNum;

};


enum MAC_PRESENT_MONEY_STATE
{
	MAC_PRESENT_GET_OK,				//上麦奖励 领取成功
	MAC_PRESENT_TIMEOUT,			//上麦奖励 过期状态
	MAC_PRESENT_GOT,				//上麦奖励 已经领取状态
	MAC_PRESENT_FAILED,				//上麦奖励 领取失败
	MAC_PRESENT_READY,				//上麦奖励 等待领取状态
};


class MonitorServerType
{
public:
	enum 
	{
		SERVER_TYPE_IM,
		SERVER_TYPE_IM_PROXY,
		SERVER_TYPE_ROOM,
		SERVER_TYPE_ROOM_PROXY,
        SERVER_TYPE_MEDIA,
	};
};

class ServerMonitorCmd
{
public:
	enum
	{
		//IM相关
		IM_SERVER_RUN_STATUS_MONITOR,
		IM_SERVER_USER_LOGIN_OR_LOGTOU,//统计用户登录或者退出
		IM_SERVER_USER_PRESENT_GIFT,		//统计用户发消息和送礼物次数
		IM_PROXY_CONNECT_STATUS,			//监控代理和IM之间的连接状态
		//房间相关
		ROOM_SERVER_RUNSTATUS_MONITOR = 0x500,
	};
};

class MonitorVer
{
public:
	enum
	{
		MONITOR_VER_1 = 1,
	};
};

class UserLogoutType
{
public:
	enum
	{
		MONITOR_USER_REQ_LOGOUT = 1,//用户主动离线
		MONITOR_USER_FOURCE_OFFLINE,//用户被强制下线
		MONITOR_USER_OTHRE_LOGIN_OFLINE,//用户被其他地方顶下线
		MONITOR_USER_KPTO_OFFLINE,		//用户掉线.

		MONITOR_USER_LOGOUT = 400,//这个没用,我这边有些废弃的接口用

	};
};


class MD_cmd
{
public:
	enum
	{
		//要统计耗时的api
		MD_IM_LOG_IN = 0,	// 登录耗时cmd
		MD_GET_URL,		//get url耗时cmd
		MD_GET_CONTACTLIST,	//获取好友列表耗时cmd 
		MD_GET_ROOM_ADDR,		//获取房间ip port耗时cmd
		MD_NET_ERRO = 0x20,	//网路错误cmd
		MD_KEEPALIVE_DELAY, //keepalive 延时
		MD_DETECT_IP,		//探测登陆点耗时
		MD_MISS_PACKET,		//丢包率
	};
};

class TuiboReviewType
{
public:
	enum
	{
		TUIBO_REVIEW_DING = 0,      //顶推播
		TUIBO_REVIEW_PINGLUN,   //评论推播
		TUIBO_REVIEW_HUIFU,	    //回复评论
	};
};


#endif

