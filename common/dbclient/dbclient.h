/*
 * Copyright (C) TinySoft, Inc. All rights reserved.
 */
#ifndef _DATAPORT_CLIENT_H_
#define _DATAPORT_CLIENT_H_
#include "include/log.h"
#include "include/icqsocket.h"
#include <string.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include "GameStruct/CocStruct.h"
#include "include/coretime.h"
#ifdef _MSC_VER

#ifdef DBCLIENT_EXPORTS
# define DATAPORT_PUBLIC __declspec(dllexport)
#else
# define DATAPORT_PUBLIC __declspec(dllimport)
#endif
#else
# define DATAPORT_PUBLIC
#endif




struct RedPacketsItem
{
	RedPacketsItem()
	{
		money = id = 0;
	}
	uint64 id;
	uint64 money;
};


struct RedPacketsLevelInfo
{
	RedPacketsLevelInfo()
	{
		maxNums = minMoneyLimit = level = flag = openState = 0;
		tableName = "";
	}
	uint8 level;
	uint8 flag;
	uint8 openState;
	uint32 minMoneyLimit;
	uint32 maxNums;
	std::string tableName;

};
typedef std::vector<RedPacketsLevelInfo> RedPacketsLevelList;
typedef std::map<uint8, RedPacketsLevelInfo> RedPacketsLevelMap;

struct CBoxItemInfo
{
	uint32 id;
	uint32 rate;
	uint64 price;
	string name;

};

class AndroidInfo
{
public:
	AndroidInfo()
	{
		customFace = 0;
		uin = 0;
		nick = "";
	}
	virtual ~AndroidInfo(){}

	uint16 customFace;
	uint32 uin;
	string nick;

};

struct ViewMemInfo
{
	uint32 uin;
	uint32 viewTime;
	ViewMemInfo()
	{
		uin = 0;
		viewTime = 0;
	}
};

typedef std::map<uint32, ViewMemInfo> ViewMemInfoList;


//coc
struct CocGemstonePriceInfo
{
	uint32 gemstoneNum;			//宝石个数
	uint32 cashMoney;			//充值现金 单位 分
	uint16 discount;			//折扣
};


class BrotherInfo
{
public:
	BrotherInfo()
	{
		nick = "";
		gameid = 0;
		totalStars = 0;
		offlineTime = 0;
		pid = 0;
		uin = 0;
	}
	string nick;
	uint32 gameid;
	uint32 totalStars;
	uint32 offlineTime;
	uint32 pid;
	uint32 uin;
};


struct DiamondWeekStarInfo
{
	uint32 uin;
	uint32 giftid;
	uint64 diamond;
	string strNick;

	DiamondWeekStarInfo()
	{
		uin = 0;
		diamond = 0;
		giftid = 0;
		strNick = "";
	}
	bool operator == (const DiamondWeekStarInfo & info)
	{
		return uin == info.uin && giftid == info.giftid && diamond == info.diamond && strNick == info.strNick;
	}
};

typedef std::map<uint32, DiamondWeekStarInfo>	DiamondWeekStarList;

typedef std::vector<BrotherInfo>	BrotherInfoList;

typedef std::vector<AndroidInfo> AndroidList;
typedef std::map<uint16,CBoxItemInfo> BoxItemInfoList;
typedef BoxItemInfoList::iterator BoxItemInfoListIter;

typedef std::vector<uint64> SpandMoneyList;
typedef std::vector<CocGemstonePriceInfo> CocGemstonePriceInfoList;
namespace dataport {

//返回错误结果
//    0~100是接口返回错误

enum ErrorCode {
    CLT_ERROR_SUCCESS = 0,						         // 返回结果成功

    CLT_ERROR_MISSING_ARGUMENT					= 7,   // 缺少参数
    CLT_ERROR_INSERT_DATABASE					= 9,   // 插入数据库错误
    CLT_ERROR_USER_NOT_EXISTS					= 12,  // 用户不存在
    CLT_ERROR_INVALID_PASSWORD					= 13,  // 密码错误
    CLT_ERROR_INVALID_SESSION					= 14,  // session错误
    CLT_ERROR_INVALID_OLDPWD					= 16,  // 原始密码错误
    CLT_ERROR_UPDATE_DATABASE					= 17,  // 更新数据库记录错误
    CLT_ERROR_QUERY_DATABASE					= 19,  // 数据库记录查询错误
    CLT_ERROR_RECORD_CONFLICT					= 20,  // 插入数据库记录错误
    CLT_ERROR_DELETE_DATABASE					= 21,  // 删除数据库记录错误
    CLT_ERROR_USER_BLOCK_IP						= 22,  // IP被封锁
    CLT_ERROR_USER_BLOCK_MAC					= 23,  // MAC被封锁
    CLT_ERROR_USER_BLOCK_UIN					= 24,  // 用户ID被封锁
    CLT_ERROR_ROOM_NOT_EXISTS					= 25,  // 房间不存在
	CLT_ERROR_USEGIFT_INGAME			        = 28,  // 在游戏中
	CLT_ERROR_USEGIFT_NOENOUGHMONEY             = 30,  // 刷花金额不足
	CLT_ERROR_FAILED						    = 31,  // 失败
	CLT_ERROR_INVALID_UIN						= 32,  // 加好友用户不存在
	CLT_ERROR_HUAZHANG_NOTENOUTHMONEY			= 33,  // 划账金币不足
	CLT_ERROR_USER_NO_STAMP_INFO                = 35,  // 用户没有被盖章信息,
	CTL_ERROR_MICPRESENT_MAX					= 36,  // 上麦奖励已经达到上线
	CTL_ERROR_LOGIN_PID_LIMIT					= 37,  // mac登录超出当前站点的最大限制
	CTL_ERROR_LOGIN_LIMIT						= 38,  // mac登录超出所有站点的最大限制	
	CTL_ERROR_NONE_EXPRESSION					= 39,  // 表情id不存在
	CTL_ERROR_NOTIN_MICTIME						= 40,  //  不再上麦奖励的时间范围
	CTL_ERROR_IDENTITY_LIMIT					= 41,  // 单个身份登录限制
	CTL_ERROR_MAX_ASSISTANT_NUM					= 42,  //相关操作超过限制	
	CTL_ERROR_GET_LETAO							= 43,  //乐淘帐号已经领取过
	CTL_ERROR_GET_YULE							= 44,  //娱乐站帐号已经领取过
	CTL_ERROR_GET_MAC							= 45,  //mac已经领取过	
	CTL_ERROR_NONE_BIND							= 46,  //未绑定用户 
	CTL_ERROR_SUIBO_END							= 47,	//直播结束
	CTL_ERROR_MONEY_LOCKED						= 48,	//金币被游戏锁定
	CTL_ERROR_NO_FREECOUNT						= 49,	//没有剩余的免费次数
	CLT_ERROR_REPEAT_MAC                        = 50,   //重复的MAC
    CLT_ERROR_GET_SERVERURL						= 100, // 返回结果没有目标服务器地址
    CLT_ERROR_HTTP_CONN  						= 101, // 连接失败
	CLT_ERROR_CONVERT_ERR,							//类型转换错误

    CLT_ERROR_FAIL = 200,						       //返回结果失败
    CLT_ERROR_PARAM_PARSE,						       //json解析失败  新的接口不再使用
	CLT_ERROR_UNKNOW_ERROR,							   //未知异常
	CLT_ERROR_DATA_INVALID,                             //错误的数据
	CLT_ERROR_DEST_IS_EXIT_BLACKLIST,					//对方已存在
	CLT_ERROR_USER_IS_NOT_ONLINE,						//用户不在线
	CLT_ERROR_NOT_THIS_GIFT,						//加好友门槛不是这个礼物
	CLI_ERROR_FRIEND_IS_NOT_EXIT,					//好友不存在
	CLT_ERROR_NO_HAVE_THIS_GIFT,					//没有这个礼物
	
	//转转相关定义
	CLT_ERROR_ZZ_INGAME,								//已经在游戏中
	CLT_ERROR_ZZ_NOACCOUNT,								//帐号不存在		
	CLT_ERROR_ZZ_NOENOUGHMONEY,							//没有足够的钱
	CLT_ERROR_ZZ_REDISEXCEPTION,						//redis异常
	CLT_ERROR_ZZ_FAILED,								//调用接口失败
	CTL_ERROR_ZZ_NOPARTNERID,							//没有此服务商id
	CTL_ERROR_ZZ_UNKNOW,								//未知错误
	CLT_ERROR_OTHER_DEVICE_LOGIN,						//移动用户提示在其他设备登陆
	CTL_ERROR_USER_LAST_SCAN,							// 上次扫描登录
	CTL_ERROR_USER_LAST_ACCREDIT,						// 上次授权登录
	CTL_ERROR_THIRDPARTY_REAUTH,						// 需要重新授权

	//碰碰车相关定义
	CTL_STORAGE_PROCEDURE_FAILED,						//存储过程失败
	CTL_MONEY_LACK,										//未知
	CTL_MONEY_LACK_FAILED,								//金币已锁定失败
	CTL_FLOW_RECORD_FAILED,								//流水写入失败
	CTL_ADD_COUNT_RECORD_FAILED,						//添加统计失败
	CTL_MONEY_QUERY_FAILED,								//金币查询失败
	CTL_SCORE_QUERY_FAILED,								//得分查询失败
	CTL_HISTORY_QUERY_FAILED,							//中奖历史记录查询失败
	CTL_UNKOW,											//未知错误
};

//返回结果类型(resultType)
enum {
	DB_LOGIN = 0x0001,
	DB_FORBID_CHAT,
    DB_LOGOUT,
	DB_CHANGE_PASSWORD,
    DB_QUERY_MONEY,
    DB_ADD_FRIEND,
    DB_DEL_FRIEND,
    DB_GET_FRIEND,
    DB_CHANGE_USER_INFO,
    DB_CHECK_ROOM_BLOCK,
    DB_GET_ROOM_INFO,
    DB_GET_GIFT,
    DB_GET_RICH,
    DB_SAVE_BROAD_CAST,
    DB_GET_SUPER_MANAGE,
    DB_LOAD_ACL,
    DB_MODIFY_CURR_USER,
    DB_MODIFY_ROOM_INFO,
    DB_GET_SERVER_INFO,
    DB_ADD_ROOM_BLACK,
    DB_MODIFY_ROOM_PASS,
    DB_ROOM_CHANGE_STATUS,
    DB_UPDATE_USER_TIME_EXT3,
    DB_UPDATE_USER_TIME,
    DB_USE_GIFT,
    DB_BUY_GLOBAL_MSG,
    DB_NOTIFY_OTHER,
    DB_NOTIFY_OTHER2,
    DB_MODIFY_MGR,
    DB_LOG_ONMIC,            //房间上麦记录
    DB_MIC_PRESENT,          //房间上麦赠送
    DB_GET_ENTER_INFO,
    DB_LOAD_ANDROID,
    DB_GET_PARTNER_INFO,
	DB_INSERT_POPUP_MSG,
	DB_INSERT_OFFLINE_MSG,
	DB_MSG_GET_NEW_BCMSG,
	DB_ADD_FAV_ROOM,
	DB_GET_FAV_ROOM,
	DB_DEL_FAV_ROOM,
	DB_GET_ADD_MYFRIEND,
	DB_QUERY_AUTH,
	DB_DEL_FRIENDMY_AND_ADD,
	DB_DEL_ADD_FRIEND,
    DB_GET_OFFLINE_MSG,
	DB_GET_OFFLINE_BCMSG,
	DB_GET_OFFLINE_POPUPMSG,
	DB_MONEY_NEW_UIN,
	DB_GET_CONTACT,
	DB_USER_OFFLINE,
	DB_INSERT_ONLINE,
	DB_TRANSFER_MONEY,
	DB_CHECK_USER_BLOCK,
	DB_GET_ROOM_ADDR,
	DB_GET_PARTNERINFO_FOR_IM,
	DB_GET_PARTNERINFO_LIST,
	DB_SEARCH_UIN,
	DB_SEARCH_SECTION,
	DB_SEARCH_SERVICE,
	DB_SEARCH_CUSTOM,
	DB_USER_STAMP,
	DB_ERASE_STAMP,
	DB_GET_USER_STAMP_INFO,
	DB_ADD_FORBID_CHAT,
	DB_GET_STAMP_LIST,
	DB_QUERY_USER_INFO,
	DB_INSERT_OFFLINE_MSG_NEW,
	DB_GET_OFFLINE_MSG_NEW,
	DB_UPDATE_OFFLINEMSG_NEW,
	DB_GET_LASTTIME,
	DB_USE_GIFT_FORMANY,
	DB_DEL_FORBID_CHAT,
	DB_INSERT_BLACKLIST,
	DB_GET_BLACKLIST,
	DB_DELETE_BLACKLIST,
	DB_GET_SESSIONKEY,		//用户重新认证时获取sessionkey
	DB_UPDATE_REMARK,
	DB_USER_DETAIL_INFO_GET,
	DB_USER_DETAIL_INFO_UPDATE,
	DB_DEVICE_INFO_UPDATE,
	DB_DEVICE_INFO_GET,
	DB_DEVICE_PUSH_TOKEN_UPDATE,
	DB_DEVICE_PUSH_TOKEN_GET,
	DB_IM_GET_GIFT_LIST,
	DB_IM_PRESENT_GIFT,
	DB_IM_GET_LAST_CHAT_SERVICE_UIN,//获取最近一次聊天的客服
	DB_IM_INSERT_CHAT_RECORDS,		//存聊天记录
	DB_IM_GET_USER_ALL_INFO,		//获取用户全部信息
	DB_IM_GET_NEW_SITUATION_NOTIFY,	//获取新推播通知
	DB_IM_SAVE_NEW_SITUATION_NOTIFY,//插入新推播通知
	DB_IM_GET_OFFLINE_GIFT,			//获取离线礼物
	DB_IM_INSERT_OFFLINE_GIFT,		//插入离线礼物
	DB_WRITE_INTEGTAL,				//chat积分记录接口
	DB_IM_INSER_NEW_REVIEW_NOTIFY,  //新评论通知
	DB_IM_GET_NEW_REVIEW_NOTIFY,	//获取新评论通知
	DB_GETPCINFO,
	DB_WRITE_MICPRESENTINFO,		//记录上麦奖励信息
	DB_GET_MICPRESENTINFO,			//获取上麦奖励信息
	DB_IM_GET_USER_LOCATION_BY_IP,	//获取用户地理位置
	DB_CHECK_ROOM_BLOCK_NEW,		//房间新封锁接口，带封锁时间
	DB_USER_ROOM_ONLINE,			//房间在线表
	DB_USER_ROOM_OFFLINE,			//房间离线
	DB_USER_ROOM_CLEAR,				//清理房间在线表
	DB_USER_ROOM_GETONLINE,			//获取指定uin在线记录
	DB_SEND_EXPRESSION,				//发送收费表情
	DB_IM_CLEAR_ONLINE_TABLE,		//服务启动清理online表
	DB_ROOM_LOGIN,					//房间登录
	DB_GET_PARTNERINFO_IM_ALL,
	DB_GET_FRIEND_ROOM_COMBINE,
	DB_GET_OFFLINE_MSG_COMBINE,
	DB_NEW_MICPRESSENT,				//新上麦奖励
	DB_ROOM_ADD_ANCHORREQ,			//添加主播
	DB_ROOM_DEL_ANCHORREQ,			//删除主播
	DB_ROOM_GET_ANCHORREQ,			//获取主播列表
	DB_ROOM_GET_GUARDREQ,			//请求守护列表
	DB_ROOM_WRITE_GUARD,			//统计对主播刷花
	DB_ROOM_ADD_ASSISTANT,			//添加副室主
	DB_ROOM_DEL_ASSISTANT,			//删除副室主
	DB_PID_ADD_BLOCK,				//添加全站封锁
	DB_BUY_ROOMBROADCAST,			//购买房间广播
	DB_ROOM_HOLIDAY_PRESENT,		//节日奖励领取
	DB_SAVE_MICINFO,
	DB_GET_SINGER_ORDER,			//获取歌单列表
	DB_VOD,							//点歌
	DB_RESET_VIEWSTATE,				//服务升级重置直播状态
	DB_GET_VID,						//获取随波vid
	DB_WRITE_GITCOUT,				//写入随播统计榜
	DB_GET_MONTH_ORDER,				//获取随播刷花月榜
	DB_GET_VID_ORDER,				//获取vid刷花榜

	DB_GET_REDPACKETS_CONFIG,		//获取红包游戏配置
	DB_SEND_REDPACKETS,				//发送红包
	DB_ROB_REDPACKETS,				//抢红包
	DB_CREATE_TABLE,				//创建游戏桌
	DB_DESTORY_TABLE,				//销毁游戏桌
	DB_REFUNMONEY,					//返还未抢完的红包
	DB_REFUNMONEYALL,				//返还所有为抢完的红包（服务重启）
	DB_FOREGIFT,					//收取返还押金
	DB_FOREGIFTALL,					//返还所有押金（服务重启）
	DB_CLEARTABLEALL,				//清理所有桌（服务重启）
	DB_REDUSERINFO,					//统计游戏数据
	DB_GET_BOX_CONFIG,				//宝箱配置
	DB_GET_BOX_ITEMLIST,			//获取宝箱中奖项目
	DB_GET_BOX_BLANCE,				//获取进入奖池和出奖池的钱
	DB_SAVE_OPENBOX,				//保存开宝箱结果
	DB_GET_BOX_FREECOUNT,			//获取开宝箱免费次数
	DB_ANDROID_LIST_VIEW,			//随播加载机器人
	DB_PROMOTION_AWARD,             //通知DB给推广用户奖励
	DB_ROOM_SHARE_INFO,             //房间当天分享人数查询
	DB_SAVE_VIEWINFO_LIST,			//保存用户观看时长列表
	DB_GET_ANYCAST_MONEY,			//获取随播金币相关信息
	DB_MODIFY_REDGAME,				//修改红包游戏状态
	DB_MODIFY_ALL_REDGAME,			//服务重启调用
	DB_ANYCAST_REDUCEMONEY,			//随播扣钱公共接口
	DB_UPDATE_SESSION_COUNT,		//更新服务人数
	DB_UPDATE_SERVER_STATE,			//更新服务状态
	DB_USE_GIFTANYCAST,				//随播刷花
	DB_GET_WEEKSTAR_LIST,			//获取周星列表
	DB_GETDIAMON_CONF,				//获取钻石配置
	DB_UPDATE_DIAMON,				//更新周星
	DB_DIAMON_USEGIFT,				//刷钻石礼物
	DB_UPDATE_MICSTATE,				//修改在麦状态
	DB_DIAMON_GUARDWEEKLIST,		//钻石守护周列表
	DB_LOAD_GIFT_POOL,				//获取刷花奖池
	DB_LOAD_SIEGEINFO,				//攻城礼物信息
	DB_VIP_LOGIN,					//会员站登录
	DB_LOAD_GIFTDAYRANK,			//获取收送礼每日排行榜第一名数据


	//转转游戏相关定义
	DB_ZZ_BETMONEY	=0x0200,	//转转押注
	DB_ZZ_AWARD,				//转转中奖
	DB_ZZ_SAVEAWARD,			//转转保存中奖结果
	DB_ZZ_AWARDHISTORY,			//当天中奖信息
	DB_ZZ_LOADPOOL,				//转转奖池获取
	DB_ZZ_LOADITEMINFO,			//转转获取各奖项信息
	DB_ZZ_GET_BLANCE,			//转转中奖偏好

	//碰碰车相关定义
	DB_LOCK_MONEY = 0x300,		//锁定解锁金币
	DB_PPC_GET_BALANCE,			//获取盈亏数据
	DB_PPC_BETMONEYALL,			//碰碰车批量押注
	DB_PPC_AWARD,				//碰碰车开奖
	DB_PPC_HISTORY,				//碰碰车中奖记录
	DB_PPC_SAVE_EXPERIENCE,		//累加保存游戏积分
	DB_PPC_GET_EXPERIENCE,		//获取游戏积分
	DB_PPC_GET_CONFIG,			//获取碰碰车配置
	DB_PPC_SAVE_BANKER,			//用户坐庄盈亏
	DB_PPC_USER_BLANCE,			//用户疯狂车行押注和中奖情况
	DB_PPC_GET_USER_MONEY,		//获取玩家当前金币钻石

	DB_PPC_ADD_GAMELIMIT,	//添加到限制名单
	DB_PPC_CHECK_BLOCK,		//用户是否被限制
	DB_PPC_GET_DISCONNECT_TIMES,//当天被强制断开连接次数
	DB_PPC_INC_DISCONNECT_TIMES,//增加被强制断开连接次数


	

	DB_NETEST,					//网络测试

	DB_MULTI_LOGIN = 0x400, //多任务 聊天室登录
	DB_MULTI_LOGIN_ZZ,		//转转多任务登录
	DB_MULTI_LOGIN_ROOM,	//房间不存在登录，加载房间信息
	DB_MULTI_PPC_LOGIN,		//疯狂车行多任务登录
	DB_MULTI_PPC_VIP,		//水果车行登录
			

};

enum DbTimeCount
{
	DB_COUNT_TIME_STAMP = 0,		//!< 时间戳
	DB_COUNT_THREAD,				//!< 线程池队列等待时间
	DB_COUNT_DB_CONNECT,				//!< DB连接时间
	DB_COUNT_DB_PROCESS,			//!< DB处理的时间
	DB_COUNT_GET_RESULT,			//!< 取到处理结果的延时
	DB_COUNT_CONNECT_SIZE,			//连接池个数
	MAX_COUT_NUM  = 8,
};

#define DATAPORT_PASSWD_LEN                   64
#define DATAPORT_NICK_LEN                     32
#define DATAPORT_PROVINCE_LEN                 32
#define DATAPORT_COUNTRY_LEN                  32
#define DATAPORT_COLLEGE_LEN                  64
#define DATAPORT_CITY_LEN                     32
#define DATAPORT_EMAIL_LEN                    64
#define DATAPORT_ADDRESS_LEN                  64
#define DATAPORT_ZIPCODE_LEN                  16
#define DATAPORT_TEL_LEN                      24
#define DATAPORT_NAME_LEN                     32
#define DATAPORT_PROFESSION_LEN               16
#define DATAPORT_HOMEPAGE_LEN                 64
#define DATAPORT_INTRO_LEN                    128
#define DATAPORT_MAX_FRIENDS	              512	//好友数量限制
#define DATAPORT_TITLE_LEN	                  64
#define DATAPORT_PIC_LEN	                  60
#define DATAPORT_MOUNT_LEN					  128	//坐骑
#define DATAPORT_ROOM_NAME_LEN                50
#define DATAPORT_DESCRIPT_LEN                 300 
#define DATAPORT_BROADCAST_LEN                450
#define DATAPORT_ROOM_PASSWD_LEN              16
#define DATAPORT_KIND_LEN                     50
#define DATAPORT_PRGNAME_LEN                  24
#define DATAPORT_MAX_ROOMMGR                  1024
#define DATAPORT_MAX_ASSIST_USER_NUM          100         //最大副区管数量
#define DATAPORT_ENTER_TITLE_LEN              36
#define DATAPORT_LEVEL_TYPE_LEN               16
#define DATAPORT_ENTER_PIC_LEN                256
#define DATAPORT_ENTER_INFO_MAX               256
#define DATAPORT_ANDROID_MAX_LEN              1024
#define DATAPORT_SUPER_MANAGER_MAX            300
#define DATAPORT_FILTER_WORDS_MAX             2048
#define DATAPORT_FILTER_WORD_LEN              2048      
#define DATAPORT_TEXT_LEN					  1024
#define DATAPOER_MSG_FORM_LEN                 32
#define DATAPOER_FAV_ROOM_MAX				  50
#define DATAPOER_GET_ADDMY_FRIENDS_MAX        2048  
#define DATAPORT_ACLS_LEN					  64
#define DATAPORT_DOMAIN_NAME_EX_LEN           64
#define DATAPORT_DOMAIN_NAME_LEN              64
#define DATAPORT_PARTNER_NAME_LEN             64
#define DATAPORT_RICH_LEN                     32
#define DATAPORT_SUPER_MANAGER_MAX            300
#define DATAPORT_ACLS_MAX                     1024
#define DATAPORT_MAX_AWARD_INFO				  1024
#define DATAPORT_GIFTNAME_LEN                 24
#define DATAPORT_GIFT_URL_LEN                 2048
#define DATAPORT_SKIN_MD5_LEN				  1024
#define DATAPORT_SKIN_COLOR_LEN				  1024
#define DATAPORT_MAX_GIFT                     1024
#define DATAPORT_ROOM_NAME_LEN				  50   
#define DATAPORT_MESSAGE_MAX                  500
#define DATAPORT_BCMSG_MAX                    50
#define DATAPORT_MSG_LEN                      512
#define DATAPORT_URL_LEN                      512
#define DATAPORT_MONEY_NAME_LEN               12
#define DATAPORT_SROOM_ACCESS_LEN             32
#define DATAPORT_PARTNERID_MAX                256
#define DATAPORT_MAX_FRAME_VER_LEN            15
#define DATAPORT_SEARCH_LIMIT_MAX             10
#define DATAPORT_RESULT_MAX                   5          //多任务返回最大数
#define DATAPORT_STAMP_EXPIRE_LEN             16
#define DATAPORT_VERSION_LEN                  32
#define DATAPORT_STAMP_GIFT_MAX               256
#define DATAPOER_ASSISTANT_MAX                100
#define DATAPORT_DSTUIN_MAX                   1024       //最大的刷花数量
#define DATAPORT_DATE_LEN					  100
#define DATAPORT_PUSH_TOKEN_LEN				  70
#define DATAPORT_MAX_ADDFRIENDS				  2000
#define DATAPORT_MAX_PCINFO_LEN				  64
#define DATAPORT_TIME_LEN					  32
#define DATAPORT_MAX_TRY_TIMES				  3
#define DATAPORT_VID_LEN					  64	

struct IMUserInfo
{
	unsigned int pid;
    unsigned int uin;
    unsigned char level;
    unsigned int LevelEndtime;
    unsigned char lordLevel;
    unsigned char face;       
    unsigned int oldMsgID;
    unsigned char gender;
    unsigned char age;
    unsigned int onlinetimes;
    unsigned char locked;
    unsigned char hide;
    unsigned short customFace;
    char passwd[DATAPORT_PASSWD_LEN+1];
    char nickname[DATAPORT_NICK_LEN+1];
    char province[DATAPORT_PROVINCE_LEN+1];
    char country[DATAPORT_COUNTRY_LEN+1];
    char college[DATAPORT_COLLEGE_LEN+1];
    char city[DATAPORT_CITY_LEN+1];
    char email[DATAPORT_EMAIL_LEN+1];
    char address[DATAPORT_ADDRESS_LEN+1];
    char zipcode[DATAPORT_ZIPCODE_LEN+1];
    char tel[DATAPORT_TEL_LEN+1];
    char name[DATAPORT_NAME_LEN+1];
    char profession[DATAPORT_PROFESSION_LEN+1];
    char homepage[DATAPORT_HOMEPAGE_LEN+1];
    char intro[DATAPORT_INTRO_LEN+1];
    unsigned char auth;
    unsigned char blood;
    unsigned char  flowinout;
    unsigned char accstat;
    unsigned long long money;
    unsigned long long received;
    unsigned int promoteid;

    char enter_title[DATAPORT_TITLE_LEN+1];
    char enter_pic[DATAPORT_PIC_LEN+1];
	unsigned short usertype;
	unsigned char CompanyMgr;
	unsigned short EnterCarType;
	unsigned long long charm;
	unsigned long charm_level;
	unsigned long long charm_next;
	unsigned long long wealth;
	unsigned long wealth_level;
	unsigned long long wealth_next;
	unsigned long active_day;
	unsigned long active_day_level;
	unsigned long active_day_next;
	char birthday[DATAPORT_DATE_LEN + 1];
	char wallpaper[DATAPORT_DATE_LEN + 1];
	char signature[DATAPORT_PARTNERID_MAX + 1];
	unsigned short majorGroup;
	unsigned long lastLoginTime;
	char hobby[DATAPORT_PARTNERID_MAX + 1];
	char company[DATAPORT_PARTNERID_MAX +1];
	unsigned long userInfoVer;
	unsigned long friendListVer;
	char pushToken[DATAPORT_PUSH_TOKEN_LEN + 1];
	char channelNumber[DATAPORT_PUSH_TOKEN_LEN + 1];
	int mobileDeviceType;
	unsigned int reportTime;
	uint32 m_attPartnerListVer;
};


struct RoomUserInfo
{
	unsigned int pid;
	unsigned int uin;
	unsigned int promotion_uin;
	unsigned char level;
	unsigned char lordLevel;
	unsigned char face;       
	unsigned short customFace;
	unsigned short usertype;
	unsigned short EnterCarType;
	unsigned long userInfoVer;
	unsigned char accstat;
	unsigned long long money;
	unsigned long long received;
	unsigned long long diamond;
	unsigned long long diamondReceived;
	unsigned long long diamondTotal;
	char nickname[DATAPORT_NICK_LEN+1];
	char onlyNick[DATAPORT_NICK_LEN+1];
	char enter_title[DATAPORT_TITLE_LEN+1];
	char enter_pic[DATAPORT_PIC_LEN+1];
	char enter_mount[DATAPORT_MOUNT_LEN+1];
};


class DetailUserInfo
{
public:
	unsigned int uin;
	std::string signature;											//个人签名										
	unsigned int lastLoginTime;										//上次登录时间
	unsigned long long usercp;												//魅力值
	std::string hobby;												//兴趣爱好
	unsigned short majorGroup;										//职业类别
	std::string company;												//公司
	unsigned long long wealthValue;
	unsigned int charmLevel;
	unsigned int wealthLevel;
	unsigned long long needCharmValue;
	unsigned long long needWealthValue;
	unsigned int active_day;
	unsigned int active_day_level;
	unsigned int active_day_next;
	std::string wallpaper;
};

struct BlackInfo 
{
public:
	BlackInfo(){m_uin = 0; m_addTime = 0;}
	BlackInfo(unsigned long uin, unsigned long addtime)
	{
		m_uin = uin;
		m_addTime = addtime;
	}
	unsigned long m_uin;
	unsigned long m_addTime;
};
struct AclInfo
{
    unsigned char src;
	int discount;
	unsigned char authority;
	unsigned int  max_times;
    char acls[DATAPORT_ACLS_LEN+1];
};

struct RoomInfo
{
	unsigned char openstatus;
	unsigned char maxmicqueue;
	unsigned char auth;   
	unsigned char micMode; 
	unsigned char colourbar_open;
	unsigned char autoMgrForRicher;
	unsigned char chatstatus;  
	unsigned char maxMicQPerUser;
	unsigned char show_enter_pic;
	unsigned char ispublic;
	unsigned char privateMicFlag;
	unsigned short roomtype;
	unsigned short maxManager;
	unsigned short roomsize;
	unsigned short maxmic;    
	unsigned short micMaxTime;
	unsigned short roomtax; 
	unsigned int serverid;
	unsigned int ownuin;
	unsigned int host_type;
	unsigned int relayRoomid;
	unsigned int assistant[DATAPOER_ASSISTANT_MAX];
	char roomname[DATAPORT_ROOM_NAME_LEN+1];
	char descript[DATAPORT_DESCRIPT_LEN+1];
	char broadcast[DATAPORT_BROADCAST_LEN+1];
	char passwd[DATAPORT_ROOM_PASSWD_LEN+1];
	char prgName[DATAPORT_PRGNAME_LEN+1];
	unsigned int roomMgr[DATAPORT_MAX_ROOMMGR];
	unsigned int regionMaster;										        //区管
	unsigned int regionAssistant[DATAPORT_MAX_ASSIST_USER_NUM];				//副区管
	unsigned long long awardRound;
	unsigned char bOnMicPresent;
	unsigned char bRedPaper;
	unsigned short redGameLevel;
	unsigned int   redGameNum;
	unsigned char  redGameFlag;
	unsigned int roomStream;		//add by 2016.11.08   
	unsigned int frameRate;			//add by 2016.11.08
	unsigned int roomStreamPri;		//2016.11.10
	unsigned int frameRatePri;		//2016.11.10 .
	char skin_md5[DATAPORT_SKIN_MD5_LEN+1];//2017.04.7
	char skin_color[DATAPORT_SKIN_COLOR_LEN+1];
	RoomInfo()
	{
		roomtype = 0;
		memset(regionAssistant, 0, sizeof(regionAssistant));
		memset(roomMgr, 0, sizeof(roomMgr));
		memset(prgName, 0, sizeof(prgName));
		memset(passwd, 0, sizeof(passwd));
		memset(broadcast, 0, sizeof(broadcast));
		memset(descript, 0, sizeof(descript));
		memset(roomname, 0, sizeof(roomname));
		memset(assistant, 0, sizeof(assistant));
		bRedPaper = 0;
		redGameLevel = 0;
		redGameNum = 0;
		redGameFlag = 0;
		roomStream = 0;		//2016.11.08 
		frameRate = 0;		//2016.11.08 
		roomStreamPri = 0;
		frameRatePri  =0;
		memset(skin_md5, 0, sizeof(skin_md5));
		memset(skin_color, 0, sizeof(skin_color));

	}
		
};

struct AwardInfo
{
	unsigned int awardid;
	unsigned int count;
};

struct RoomEnterInfo
{
    char enter_title[DATAPORT_ENTER_TITLE_LEN+1];
    char levelType[DATAPORT_LEVEL_TYPE_LEN+1];
    char enter_pic[DATAPORT_ENTER_PIC_LEN+1];
    unsigned int level;
};

struct Android
{
    unsigned int uin;
    unsigned char face;
	unsigned int customFace;
    unsigned char level;
    unsigned char lordlevel;
    unsigned long long money;
    unsigned long long received; 
	char nickname[DATAPORT_NICK_LEN+1];
};
enum
{
	NOT_LUKY_GIFT,			//非幸运礼物
	LUKY_GIFT,				//1幸运礼物
	KTV_GIFT,				//是点歌礼物
	CHARM_GIFT				//魅力礼物
};
class OfflineMsgKind
{
public:
	enum 
	{
		ALL_KIND = 1,
		OFF_LINE_MSG,
		OFF_LINE_POP,
		OFF_LINE_BC
	};
};

class FriendRoomCombineKind 
{
public:
	enum 
	{
		ALL_KIND = 1,
		GET_FRIEND,
		ADD_MY_FRIEND,
		BLACKLIST,
		FAV_ROOM
	};
};

struct GiftInfo
{
	unsigned int giftid;
	unsigned long long giftprice;
	char giftname[DATAPORT_GIFTNAME_LEN+1];
	char gift_url[DATAPORT_GIFT_URL_LEN+1];
	unsigned char giflucky;
	unsigned char startstate;
	unsigned int recvRate;
	unsigned int compRate;
	unsigned int hostRate;
};

struct PartnerInfo
{
    unsigned char greate_disp_times;
    unsigned char automic;
    unsigned char companyTaxRatio;
    unsigned char roomHostTaxRatio;
    unsigned char gift_vod;
    unsigned char prize_recv_ratio;
    unsigned char prize_comp_ratio;
    unsigned char prize_host_ratio;
    unsigned char prize_pool_ratio;
    unsigned char presentOnMicTimelimit;
	unsigned char privateMicFlag;
	unsigned char onmic_share_limit;//强制上麦分享开关
    unsigned short automic_start;
    unsigned short prize_rate2;
	unsigned char present_radioType;
	unsigned int greate_giftprice;
    unsigned int greate_present;
	unsigned int globle_redpaper;
	bool		bRedpaperOff;
    unsigned int automic_end;
    unsigned int currPrizedRatio;
    unsigned int broadCasePrice;
    unsigned int presentOnMicPerMin;
    unsigned int  receiverRatio;
	unsigned int partnerID;
	unsigned int host_type;
	unsigned int micPresentTimeout;
    unsigned int transTax; // [JWJ]
	unsigned int micPresentRate;
	unsigned int holidayPresent;
	unsigned int guard_expense;
	unsigned int song_prize;
	unsigned int promotion_reward;
	unsigned char onmic_sent_money_way;
	unsigned char diamon_gift_flag;	//钻石礼物开关
	unsigned char diamon_action_flag;//钻石礼物特效开关
	unsigned int diamon_action_limit;	//钻石礼物
	unsigned char duobao_treasure_open;//夺宝活动开关
    char domainNameEx[DATAPORT_DOMAIN_NAME_EX_LEN+1];
    char domainName[DATAPORT_DOMAIN_NAME_LEN+1];
    char partnerName[DATAPORT_PARTNER_NAME_LEN+1];
	char mountsVer[DATAPORT_VERSION_LEN];
	char sRoomAccess[DATAPORT_SROOM_ACCESS_LEN+1];

	unsigned long long prizeIncoming;
	unsigned long long prizeOutgoing;
	unsigned int diamondmsg;
	unsigned long long diamondPresentLimit;
	unsigned char diamond_present_radioType;
	unsigned long long diamond_greate_giftprice;
	char giftVer[DATAPORT_VERSION_LEN+1];
	char stampVer[DATAPORT_VERSION_LEN+1];
	char sortVer[DATAPORT_VERSION_LEN+1];
	char giftVerNew[DATAPORT_VERSION_LEN+1];
	char broadcastVer[DATAPORT_VERSION_LEN+1];
	char weskitVer[DATAPORT_VERSION_LEN+1];
	PartnerInfo()
	{
		memset(sRoomAccess, 0 , sizeof(sRoomAccess));	
		memset(mountsVer, 0 , sizeof(mountsVer));
		onmic_sent_money_way = 0;
		diamon_gift_flag = 0;
		diamon_action_flag = 0;//钻石礼物特效开关
		diamon_action_limit = 0;	//钻石礼物
		duobao_treasure_open = 0;
		diamondmsg = 0;
		diamondPresentLimit = 0;
		diamond_present_radioType = 0;
		diamond_greate_giftprice = 1000000;
	}
	
};
  
struct FavRoomInfo
{
	unsigned int roomtype;
	unsigned int roomid;
	char roomname[DATAPORT_ROOM_NAME_LEN + 1];
	char roomFace[DATAPORT_ROOM_NAME_LEN + 1];
	char roomShow[DATAPORT_ROOM_NAME_LEN * 2 + 1];//房间说明
	unsigned int m_hostUin;
	unsigned int m_roomInfoVer;
	unsigned int m_pid;
};

struct OffLineMsgInfo
{
	unsigned int dst;
	unsigned int type;
	unsigned int when;
	char  text[DATAPORT_TEXT_LEN+1];
};


class BcMsgInfo
{
public:
	BcMsgInfo()
	{
		id = 0;
		time = 0;
		memset(title, 0, sizeof(title));
		memset(text, 0, sizeof(text));
		memset(msgform, 0, sizeof(msgform));
		memset(m_url, 0, sizeof(m_url));
		expire = 0;
		partnerid = 0;
	}
	unsigned int id;
	unsigned int time;
	char title[DATAPORT_TITLE_LEN+1];
	char text[DATAPORT_TEXT_LEN+1];
	char msgform[DATAPOER_MSG_FORM_LEN+1];
	char m_url[DATAPORT_TEXT_LEN / 2];
	unsigned int expire;
	unsigned int partnerid;
};


struct OffLineMsgInfoNew
{
	unsigned long long msgId;
	unsigned int pid;
	unsigned int dst;
	unsigned int src;
	unsigned int type;
	unsigned int when;
	unsigned int status;
	unsigned int srcPid;
	char  text[DATAPORT_TEXT_LEN+1];
	unsigned int m_subUin;
};

struct PopupMsg
{
	unsigned int dst;
	unsigned int type;
	unsigned int fid;
	unsigned int src;
	char msg[DATAPORT_MSG_LEN+1];
	char url[DATAPORT_URL_LEN+1];
	unsigned int pid;
};

struct SearchUserInfo
{
	unsigned int uin;
	unsigned char pic;
	char nick[DATAPORT_NICK_LEN+1];
	unsigned char age;
	unsigned char gender;
	char province[DATAPORT_PROVINCE_LEN+1];
	char city[DATAPORT_CITY_LEN+1];
};


struct StampGiftinfo
{
	unsigned int stamp_id;
	unsigned int stamp_price;
	unsigned int stamp_time;
};
class ReviewNotifyUserInfo
{
public:
	ReviewNotifyUserInfo(){}
	ReviewNotifyUserInfo(unsigned int uin, unsigned int pid)
	{
		m_uin = uin;
		m_pid = pid;
	}
public:
	unsigned int m_uin;
	unsigned int m_pid;
};

class DATAPORT_PUBLIC CDBClientResult   //返回的结果类
{
public:
    int resultType;                     //结果类型
    int errorCode;
    void * arg;
	unsigned int dbStamp[MAX_COUT_NUM];
public:
    virtual void release();
	virtual ~CDBClientResult(){};
	void formatStatistics(char* pBuf, size_t len)
	{
		snprintf(pBuf,  len, "message = %u connSize = %u, DbTotal = %u threadQueue = %u DbConnect = %u inDbProcess = %u getDbResult = %u",
			resultType,
			dbStamp[DB_COUNT_CONNECT_SIZE],
			TIME_DIFF_U(dbStamp[dataport::DB_COUNT_GET_RESULT], dbStamp[dataport::DB_COUNT_TIME_STAMP]), 
			TIME_DIFF_U(dbStamp[dataport::DB_COUNT_THREAD], dbStamp[dataport::DB_COUNT_TIME_STAMP]), 
			TIME_DIFF_U(dbStamp[dataport::DB_COUNT_DB_CONNECT], dbStamp[dataport::DB_COUNT_THREAD]) ,
			TIME_DIFF_U(dbStamp[dataport::DB_COUNT_DB_PROCESS], dbStamp[dataport::DB_COUNT_DB_CONNECT]) ,
			TIME_DIFF_U(dbStamp[dataport::DB_COUNT_GET_RESULT], dbStamp[dataport::DB_COUNT_DB_PROCESS]));
	};
	
public:
	CDBClientResult()
	{
		resultType = 0;
		errorCode = 0;
		arg = NULL;
		memset(dbStamp, 0, sizeof(dbStamp));
	}
};

class CDGetStampGiftList:
	public CDBClientResult
{
public:
	int giftlen;
	StampGiftinfo giftinfo[DATAPORT_STAMP_GIFT_MAX];
	CDGetStampGiftList()
	{
		giftlen = 0;
		memset(giftinfo, 0, sizeof(giftinfo));
	}
};


class CDBMutiResult:
	public CDBClientResult
{
public:
	CDBClientResult * baseResults[DATAPORT_RESULT_MAX];
	virtual void release();
	CDBClientResult *GetChildResult(int resultType)
	{
		for (int i = 0; i<DATAPORT_RESULT_MAX && baseResults[i]; i++)
		{
			if (baseResults[i]->resultType == resultType)
				return baseResults[i];
		}
		return NULL;
	}

public:
	CDBMutiResult()
	{
		memset(baseResults, 0, sizeof(baseResults));
	}

	~CDBMutiResult()
	{
		for(int i = 0; this->baseResults[i]!=NULL && i < DATAPORT_RESULT_MAX; ++i)
		{
			delete this->baseResults[i];
		}
	}
};

class CDBLoginResult:
    public CDBClientResult
{
public:
    IMUserInfo userInfo;
    CDBLoginResult()
	{
		memset(&userInfo, 0, sizeof(userInfo));
	}
};



class CDBforbidStatus:
    public CDBClientResult
{
public:
    unsigned int forbidStatus;
public:
	CDBforbidStatus()
	{
		forbidStatus =0;
	}
};

class CDBQueryMoneyResult:
    public CDBClientResult
{
public:
    unsigned long long money;
	unsigned char accstat;
	unsigned long long received;
	CDBQueryMoneyResult()
	{
		money = 0;
		accstat = 0;
		received = 0;
	}
};

class PartnerInfoEx
{
public:
	PartnerInfoEx()
	{
		partnerId = 0;
		newUserPresent = 0;
		greatePresent = 0;
		greateDistTimes = 0;
		roomaccess = 0;
		status = 0;
		transTax = 0;
		lastupdate = 0;
		broadPrice = 0;
		memset(partnerName, 0 , sizeof(partnerName));
		memset(domainname, 0 , sizeof(domainname));
		memset(domainNameEx, 0 , sizeof(domainNameEx));
		memset(moneyName, 0 , sizeof(moneyName));
		memset(sRoomAccess, 0 , sizeof(sRoomAccess));
		memset(configUrl, 0, sizeof(configUrl));
		memset(tubeName, 0, sizeof(tubeName));
		gitfVer = "";
		charmValueRatio = "";
		m_openQRCode = 0;
		m_openUpLoadLog =0;
		m_urlVer = 0;
	}
public:
	unsigned int partnerId;
	char partnerName[DATAPORT_PARTNER_NAME_LEN+1];
	char domainname[DATAPORT_DOMAIN_NAME_LEN+1];
	char domainNameEx[DATAPORT_DOMAIN_NAME_EX_LEN+1];
	char moneyName[DATAPORT_MONEY_NAME_LEN+1];
	unsigned short newUserPresent;
	unsigned char greateDistTimes;
	unsigned char roomaccess;
	unsigned char status;
	unsigned int greatePresent;
	unsigned int transTax;
	unsigned int lastupdate;
	unsigned int broadPrice;
	char sRoomAccess[DATAPORT_SROOM_ACCESS_LEN+1];
	std::string gitfVer;
	std::string charmValueRatio;
	std::string wealthValueRatio;
	unsigned int companyTaxRatio;
	char configUrl[DATAPORT_MAX_AWARD_INFO];
	char tubeName[DATAPORT_ROOM_NAME_LEN];
	unsigned char m_openQRCode;
	unsigned char m_openUpLoadLog;
	uint32 m_urlVer;
	   
};
class CDBGetFriendInfo
{
public:
	unsigned int fid;
	char remark[DATAPORT_ENTER_PIC_LEN];
};

class GetFriendInfoEx
{
public:
	GetFriendInfoEx()
	{
		fidsNum = 0;
		memset(fids, 0, sizeof(fids));
	}
public:
	CDBGetFriendInfo fids[DATAPORT_MAX_FRIENDS];					//以0或上限结尾
	unsigned int fidsNum;
};
class CDBHandleFriendResult : public CDBClientResult
{
public:
	unsigned int m_friendListVer;
	unsigned int m_expireTime;
};

class CDBGetFriendResultNew : public CDBClientResult
{
public:
	GetFriendInfoEx m_FriendInfo;
};

class CDBGetFriendResult:
	public CDBClientResult
{
public:
	CDBGetFriendResult()
	{
		fidsNum = 0;
		memset(fids, 0, sizeof(fids));
	}
	unsigned int fids[DATAPORT_MAX_FRIENDS];					//以0或上限结尾
	unsigned int fidsNum;
};

class CDBGetRoomInfo:
    public CDBClientResult
{
public:
    RoomInfo roominfo;

	//游戏房间
	unsigned int roundID;
	unsigned int awardinfocount;					//返回结果数量
    AwardInfo awardinfo[DATAPORT_MAX_AWARD_INFO];   //返回奖励信息
    CDBGetRoomInfo()
	{
		roundID = 0;
		memset(&roominfo, 0, sizeof(roominfo));
		awardinfocount = 0;
	}
};

class CDBGetGift:
	public CDBClientResult
{
public:
	GiftInfo giftInfo[DATAPORT_MAX_GIFT];
	int gift_length;
	CDBGetGift()
	{
		gift_length = 0;
		memset(&giftInfo, 0, sizeof(GiftInfo)*DATAPORT_MAX_GIFT);
	}
};


class CDGetRich:
    public CDBClientResult
{
public:
    unsigned int uins[DATAPORT_RICH_LEN];
    int uins_num;
    CDGetRich()
    {
		uins_num = 0;
        memset(&uins, 0, sizeof(uins));
    }
};

class CDGetSuperManager:
    public CDBClientResult
{
public:
    unsigned int uins[DATAPORT_SUPER_MANAGER_MAX];
    int manager_num;
    CDGetSuperManager()
    {
		manager_num = 0;
        memset(&uins, 0, sizeof(uins));
    }
};

class CDLoadAcl:
    public CDBClientResult
{
public:
    AclInfo aclInfo[DATAPORT_ACLS_MAX];
    int acl_number;
	
    CDLoadAcl()
    {
		acl_number = 0;
        memset(aclInfo, 0, sizeof(aclInfo));
    }
};

class CDGetServerInfo:
    public CDBClientResult
{
public:
    unsigned short port;
	CDGetServerInfo()
	{
		port = 0;
	}
};

class CDGetEnterInfo:
    public CDBClientResult
{
public:
    unsigned int infoNum;
    RoomEnterInfo roomInfo[DATAPORT_ENTER_INFO_MAX];
    CDGetEnterInfo()
    {
		infoNum = 0;
        memset(roomInfo, 0, sizeof(roomInfo));
    }
};


class CDLoadAndroid:
    public CDBClientResult
{
public:
    Android android[DATAPORT_ANDROID_MAX_LEN];
	unsigned int androidNum;
    CDLoadAndroid()
    {
		androidNum = 0;
        memset(android, 0 ,sizeof(android));
    }
};

class CDTransferMoney:
	public CDBClientResult
{
public:
	unsigned long long remaining;
	unsigned int willtax;
public:
	CDTransferMoney()
	{
		remaining = 0;
		willtax = 0;
	}
};

struct Rebate
{
	Rebate()
	{
		normal_rebateRatio = 0;
		prize_rebateRatio  = 0;
		type			   = 0;
	}
	uint8 normal_rebateRatio;
	uint8 prize_rebateRatio;
	uint8 type;
};

typedef std::vector<Rebate>	RebateList;
typedef std::vector<unsigned int> SvridList; 
class GetPartnerInfo:
    public CDBClientResult
{
public:
    PartnerInfo partnerInfo;
	SvridList	svridList;
	SvridList   svridKind;
	RebateList  rebateList;
    unsigned int supermanager[DATAPORT_SUPER_MANAGER_MAX];
    unsigned int manager_count;
    char filterwords[DATAPORT_FILTER_WORDS_MAX][DATAPORT_FILTER_WORD_LEN+1];
    unsigned int words_count;              
    GetPartnerInfo()
    {
        manager_count= 0;
		words_count= 0;
        memset(&partnerInfo, 0 , sizeof(partnerInfo));
        memset(supermanager, 0 , sizeof(supermanager));
        memset(filterwords, 0, sizeof(filterwords));
    }
};

class FavRoomInfoEx
{
public:
	FavRoomInfoEx()
	{
		roomNum= 0;
		memset(favRoomInfo, 0, sizeof(favRoomInfo));
	}
public:
	FavRoomInfo favRoomInfo[DATAPOER_FAV_ROOM_MAX];
	unsigned int roomNum;

};
class AddMyFriendInfoEx
{
public:
	AddMyFriendInfoEx()
	{
		friendsNum= 0;
		memset(friends, 0, sizeof(friends));
	}
public:
	unsigned int friends [DATAPORT_MAX_ADDFRIENDS];
	unsigned int friendsNum;
};
class MsgGetNewBCMsg:
	public  CDBClientResult
{
public:
	BcMsgInfo bcmsgInfo;
	MsgGetNewBCMsg(){
		memset(& bcmsgInfo, 0, sizeof(bcmsgInfo));
	}
};


class CDGetFavRoom:
	public  CDBClientResult
{
public:
	FavRoomInfoEx m_favRoomInfo;	
};

class CDGetAddMyFriend:
	public  CDBClientResult
{
public:
	AddMyFriendInfoEx m_addMyFriend;
};

class CDMicPresent:
	public  CDBClientResult
{
public:
	unsigned int num;
	CDMicPresent()
	{
		num = 0;
	}
};
class OffLineBcMsgInfoEx
{
public:
	OffLineBcMsgInfoEx()
	{
		msgNum= 0;
		memset(msginfo, 0, sizeof(msginfo));
	}
public:
	BcMsgInfo msginfo[DATAPORT_BCMSG_MAX];
	unsigned int msgNum;	
};
class OffLinePopupMsgEx
{
public:
	OffLinePopupMsgEx()
	{
		msgNum = 0;
		memset(popupMsgs,0 ,sizeof(popupMsgs));
	}
public:
	PopupMsg popupMsgs[DATAPORT_BCMSG_MAX];
	unsigned int msgNum;
};
class CDGetOffLineMsg:
	public  CDBClientResult
{
public:
	OffLineMsgInfo msginfo[DATAPORT_MESSAGE_MAX];
	unsigned int msgNum;
	CDGetOffLineMsg()
	{
		msgNum= 0;
		memset(msginfo, 0, sizeof(msginfo));
	}
};

class CDGetOffLineBCMsg:
	public  CDBClientResult
{
public:
	OffLineBcMsgInfoEx m_bcMsginfo;	
};


class CDGetPopupMsg:
	public  CDBClientResult
{
public:
	OffLinePopupMsgEx m_popupMsgs;
};


class CDAueryAuth:
	public  CDBClientResult
{
public:
	unsigned char auth;
public:
	CDAueryAuth()
	{
		auth= 0;
	}
};


class CDGetContact:                                                                 
	public  CDBClientResult
{
public:
	IMUserInfo userInfo;
	CDGetContact()
	{
		memset(&userInfo, 0, sizeof(userInfo));
	}
};


class CDPartnerInfoForIM:
	public CDBClientResult
{
public:
	PartnerInfoEx m_vecPaternerInfo;
};
class CDgetPartnerInfoIMAll:public CDBClientResult
{
public:
	std::vector<PartnerInfoEx> m_partnerInfoAll;
};
class BlackListInfoEx
{
public:
	std::vector<BlackInfo> blackList;
	std::vector<BlackInfo> addMyBlackList;
};
class FriendInfoEx
{
public:
	GetFriendInfoEx getFriendInfo;
	AddMyFriendInfoEx addMyFriend;
};

class AttentionPartnerInfo
{
public:
	AttentionPartnerInfo(){}
	AttentionPartnerInfo(uint32 pid, uint32 lastMsgId)
	{
		m_pid = pid;
		m_lastMsgId = lastMsgId;
	}
public:
	uint32 m_pid;
	uint32 m_lastMsgId;
};

class CDgetFriendAndRoomCombine:public CDBClientResult
{
public:
	BlackListInfoEx m_blackListInfo;
	FavRoomInfoEx m_favRoomInfo;	
	FriendInfoEx m_friendInfo;
	uint8 kind;
	std::vector<AttentionPartnerInfo> m_attPartnerList;
	OffLineBcMsgInfoEx m_attPartnerBCMsg;
};
class OffLineMsgInfoEx
{
public:
	OffLineMsgInfoEx()
	{
		memset(offlineMsg, 0, sizeof(offlineMsg));
	}
public:
	OffLineMsgInfoNew offlineMsg[DATAPORT_MESSAGE_MAX+1];
};

class CDgetOffLineMsgCombine:public CDBClientResult
{
public:
	OffLineMsgInfoEx m_offLineMsgInfo;
	OffLinePopupMsgEx m_offLinePopupMsgInfo;
	OffLineBcMsgInfoEx m_offLineBcMsgInfo;
	uint8 kind ;
};


class CDBGetImGitfListResult : public CDBClientResult
{
public:
	std::vector<GiftInfo> giftList;
};


class CDGetRoomAddr:
	public CDBClientResult
{
public:
	unsigned int ip;
	unsigned int roomid;
	unsigned int port;
	unsigned short roomtype;
	char roomName[DATAPORT_ROOM_NAME_LEN+1]; 
    char prgName[DATAPORT_PRGNAME_LEN+1];
	unsigned int  prgVer;
    unsigned int  frameVer;
	unsigned int  maxprgVer;
	unsigned int  maxframeVer;
	unsigned char useproxy;
	int voicecode1;
	int voicecode2;
	int voicecode3;
	int useTcp;
	char minChatLetao[DATAPORT_PRGNAME_LEN];
	char maxChatLetao[DATAPORT_PRGNAME_LEN];
	char minVerResource[DATAPORT_PRGNAME_LEN];
	//char maxVerResource[DATAPORT_PRGNAME_LEN];
	//char minVerResource[DATAPORT_PRGNAME_LEN];
	char maxVerResource[DATAPORT_PRGNAME_LEN];
	char minVerPubSource[DATAPORT_PRGNAME_LEN];
	char maxVerPubSource[DATAPORT_PRGNAME_LEN];
	char minVerConfig[DATAPORT_PRGNAME_LEN];
	char maxVerConfig[DATAPORT_PRGNAME_LEN];
	char minGameFrameVer[DATAPORT_PRGNAME_LEN];
	char maxGameFrameVer[DATAPORT_PRGNAME_LEN];
	char programPathName[DATAPORT_PRGNAME_LEN];
	uint8 isVipPartner;
	CDGetRoomAddr()
	{
		ip = 0;
		roomid = 0;
		port =0;
		roomtype = 0;
		memset(roomName, 0 , sizeof(roomName));
		memset(prgName,0 , sizeof(prgName));
		prgVer = 0;
		frameVer = 0;
		maxprgVer = 0;
		maxframeVer = 0;
		useproxy = 0;
		voicecode1 = 0;
		voicecode2 = 0;
		voicecode3 = 0;
		useTcp  = 0;
		memset(minChatLetao, 0, sizeof(minChatLetao));
		memset(maxChatLetao, 0, sizeof(maxChatLetao));
		memset(minVerPubSource, 0, sizeof(minVerPubSource));
		memset(maxVerPubSource, 0, sizeof(maxVerPubSource));
		memset(minVerResource, 0, sizeof(minVerResource));
		memset(maxVerResource, 0, sizeof(maxVerResource));
		memset(minVerConfig, 0, sizeof(minVerConfig));
		memset(maxVerConfig, 0, sizeof(maxVerConfig));
		memset(minGameFrameVer, 0, sizeof(minGameFrameVer));
		memset(maxGameFrameVer, 0, sizeof(maxGameFrameVer));
		memset(programPathName, 0, sizeof(programPathName));
		isVipPartner = 0;
	}
};


class CDLastUpdatePartnerList:
	public CDBClientResult
{
public:
	unsigned int partnerids[DATAPORT_PARTNERID_MAX];
	unsigned int partner_num;
	CDLastUpdatePartnerList()
	{
		partner_num = 0;
		memset(partnerids, 0, sizeof(partnerids));
	}
};



class CDSearchUin:
	public CDBClientResult
{
public:
	SearchUserInfo userInfo;
	CDSearchUin()
	{
		memset(&userInfo, 0, sizeof(userInfo));
	}
};

class CDSearchSection:
	public CDBClientResult
{
public:
	SearchUserInfo userInfos[DATAPORT_SEARCH_LIMIT_MAX];
	int user_num;
	CDSearchSection()
	{
		user_num = 0;
		memset(userInfos, 0, sizeof(userInfos));
	}
};

class CDUserStampInfo:           //返回用户盖章的信息
	public CDBClientResult
{
public:
	CDUserStampInfo()
	{
		srcOrDst = stampExpire = stampID = 0;
		memset(stampMsg, 0, sizeof(stampMsg));
	}
	unsigned  srcOrDst;
	unsigned int stampID;
	unsigned  stampExpire;
	char stampMsg[DATAPORT_STAMP_EXPIRE_LEN+1];
};

class CDUserStamp:
	public CDBClientResult
{
public:
	unsigned long long lastmony;
	CDUserStamp()
	{
		lastmony = 0;
	}
};

class CDQueryUserInfo:
	public CDBClientResult
{
public:
	unsigned char level;
	unsigned short levelend;
	unsigned char lordlevel;
	unsigned short customface;
	CDQueryUserInfo()
	{
		level = 0;
		levelend = 0;
		lordlevel = 0; 
		customface = 0;
	}
};

class OffLineMsgNew:
	public CDBClientResult
{
public:
	OffLineMsgInfoEx m_offlineMsg;
};


class GetLastTime:
	public CDBClientResult
{
public:
	unsigned int lasttime;
public:	
	GetLastTime()
	{
		lasttime = 0;
	}
};

class InsertToBlackListResult : public CDBClientResult
{

};

class DeleteBlackListResult : public CDBClientResult
{
};

class GetBlackListFromDBResult : public CDBClientResult
{
public:
	BlackListInfoEx m_blackList;
};

class UpdateRemarkFromDBResult : public CDBClientResult
{

};


class UserDetailInfoGetFromDBResult : public CDBClientResult
{
public:
	DetailUserInfo info;
};

class UserDetailInfoUpdateFromDBResult : public CDBClientResult
{
public:
	unsigned long infoVer;
	std::map<std::string, std::string> changeInfo;
};


class GetSessionKeyFromDBResult : public CDBClientResult
{
public:
	std:: string m_sessionKey;
};
class DeviceInfoUpdateFromDBResult : public CDBClientResult
{
};
class DeviceInfoGetFromDBResult : public CDBClientResult
{
public:
	std::string uniqueIdentifier;
};

class DeviceMsgPushTokenUpdateFromDBResult : public CDBClientResult
{
};

class DeviceMsgPushTokenGetFromDBResult : public CDBClientResult
{
public:
	std::string msgPushToken;
	std::string channelNumber;
	std::string remark;
	int deviceType;
};

class CDBImPresentGiftResult : public CDBClientResult
{
public:
	unsigned long long srcMoney;
	unsigned long long dstMoney;
	unsigned long long dstReceived;
	unsigned long long srcWealth;
	unsigned long long srcWealthAdd;
	unsigned long long dstCharm;
	unsigned long long dstCharmAdd;
	unsigned long long sendMoney;
	unsigned int m_expireTime;
};

class CDBImGetLastServiceUinResult : public CDBClientResult
{
public:
	unsigned int destPid;
	unsigned int destUin;
};

class CDBImInsertChatRecordsResult : public CDBClientResult
{

};

////////////////////////////////////////////////////转转相关定义start
class MoneyResult : public CDBClientResult
{
public:
	MoneyResult()
	{
		m_lMoneyExt = m_lRemaining = 0;
		uin = 0;
	}
	unsigned long long m_lRemaining;	//押注的余额 或者 奖池余额 或者奖池余额
	unsigned long long m_lMoneyExt;
	unsigned int uin;
	
};

class MoneyResultList:public CDBClientResult
{
public:
	MoneyResultList()
	{

	}
	std::vector<MoneyResult>	m_moneyList;
};

class GetBalanceInfo:public CDBClientResult
{
public:
	GetBalanceInfo()
	{
		m_inCount_company = m_outCount_company = 0;
	}
	long long m_inCount_company;
	long long m_outCount_company;
};

class GetUserCurMoney:public CDBClientResult
{
public:
	GetUserCurMoney()
	{
		m_curMoney = m_curDiamond = 0;
	}
	long long m_curMoney;
	long long m_curDiamond;
};
class GetUserPpcLimited:public CDBClientResult
{
public:
	GetUserPpcLimited()
	{
		islimited = 0;
	}
	uint32 islimited;
};
class GetDisconnectTimes:public CDBClientResult
{
public:
	GetDisconnectTimes()
	{
		mac_limitNum = uin_limitNum = 0;
	}
	uint32 mac_limitNum;
	uint32 uin_limitNum;
};






class ServerClearOnlineTblResult : public CDBClientResult
{
public:
};

struct ItemInfo
{
	unsigned int nItemID;				//中奖id
	unsigned int nItemCount;			//开奖数量
};

typedef std::vector<ItemInfo> ItemList;
typedef ItemList::iterator ItemIter;
class AwaredHistoryResult: public CDBClientResult
{
public:
	ItemList itemList;
};

typedef std::vector<uint64> JettonList;
class PPCConfigResult:public CDBClientResult
{
public:
	PPCConfigResult()
	{
		bankerCondition = bankerLeaveMoney = userLimitMoney = 0;
		game_rate  = ppcRate = 0;
		maxLine = 0;
		retryRate = 0;
	}
	uint64 bankerCondition;
	uint64 bankerLeaveMoney;
	uint64 userLimitMoney;
	uint64 maxLine;
	uint32 retryRate;
	uint32 ppcRate;
	uint32 game_rate;
	JettonList jettonList;
};





class RedPacketsListResult: public CDBClientResult
{
public:
	RedPacketsListResult()
	{
		m_nRedPacketsID = 0;
		m_flag = false;
	}
	~RedPacketsListResult(){}

	uint64				m_nRedPacketsID;
	bool				m_flag;
	std::vector<RedPacketsItem> m_nRedPacketsList;

};

class CreateTableResult: public CDBClientResult
{
public:
	CreateTableResult()
	{
		m_tableid = 0;
	}
	~CreateTableResult(){}

	uint32		m_tableid;
	

};



struct AwareNameInfo
{
	unsigned short nItemID;
	std::string strItemName;
};
typedef std::vector<AwareNameInfo> AwareNameList;
typedef AwareNameList::iterator AwareNameIter;

class AwaredNameInfoResult: public CDBClientResult
{
public:
	AwareNameList nameInfoList;
	unsigned short nCount;
};

struct GiftCountInfo
{
	unsigned int srcuin;
	unsigned long long amount;
	unsigned short customfae;
	string		 nick;
	GiftCountInfo()
	{
		nick = "";
		amount = 0;
		srcuin = 0;
		customfae = 0;
	}

};

typedef std::vector<GiftCountInfo> GiftCountList;
typedef GiftCountList::iterator GiftCountIter;

class CDBGiftCountList: public CDBClientResult
{
public:
	CDBGiftCountList()
	{
		dstuin = 0;
	}
	~CDBGiftCountList()
	{
	
	}
	GiftCountList infoList;
	unsigned dstuin;
};



class CDBBoxConfig:public CDBClientResult
{
public:
	CDBBoxConfig()
	{
		rate = freeInterval = freeCount = openFlag = notifyPrice = 0;
		spandMoneyList.clear();
	}
	~CDBBoxConfig()
	{

	}
	unsigned char openFlag;
	unsigned short freeCount;
	unsigned short freeInterval;
	unsigned long long notifyPrice;
	unsigned short rate;
	SpandMoneyList spandMoneyList;

};

class CDBBoxItemList:public CDBClientResult
{
public:
	CDBBoxItemList(){m_maxMoney = 0;};
	~CDBBoxItemList(){};
	BoxItemInfoList	m_itemList;
	uint64			m_maxMoney;
};



class BlanceResult : public CDBClientResult
{
public:
	long long m_lBlance;	//中奖偏好
};
////////////////////////////////////////////////////转转相关定义end

class CDBNewSituationSaveResult : public CDBClientResult
{

};
class CDBImSertOfflineGiftResult : public CDBClientResult
{

};

class CDBNewSituationGetResult : public CDBClientResult
{
public:
	CDBNewSituationGetResult()
	{
		m_haveNewSituation = 0;
	}
	int m_haveNewSituation;
};

class CDBNewReviewNotifyGetInfo
{
public:
	unsigned int m_srcUin;
	unsigned int m_srcPid;
	unsigned short m_faceVer;
	std::string m_reviewText;
	unsigned int m_reviewTime;
	unsigned int m_tuiboId;
	std::string m_tuiboPhotoUrl;
	unsigned int m_destUin;
	unsigned int m_destPid;
	std::string m_destNick;
	unsigned int m_reviewId;
	std::string m_srcNick;
};

class CDBNewReviewNotifyGetResult : public CDBClientResult
{
public:
	std::vector<CDBNewReviewNotifyGetInfo> infoList;
};

class OfflineGiftInfo
{
public:
	OfflineGiftInfo();
	OfflineGiftInfo(unsigned long srcId, unsigned long srcPid, unsigned long destId, unsigned long destPid,
					unsigned long giftId,  unsigned long giftNum, std::string giftName, unsigned long long charValue,
					unsigned short type, unsigned long currTime)
	{
		m_srcUin = srcId;
		m_srcPid = srcPid;
		m_dstUin = destId;
		m_dstPid = destPid;
		m_giftId = giftId;
		m_giftNum = giftNum;
		m_giftName = giftName;
		m_charmAdd = charValue;
		m_type = type;
		m_currTime = currTime;		
	}
public:
	unsigned int m_srcUin;
	unsigned int m_srcPid;
	unsigned int m_dstUin;
	unsigned int m_dstPid;
	unsigned int m_giftId;
	unsigned int m_giftNum;
	std::string   m_giftName;
	unsigned long long m_charmAdd;
	unsigned short m_type;
	unsigned int m_currTime;
};
class CDBImGetOfflineGiftResult : public CDBClientResult
{
public:
	std::vector<OfflineGiftInfo> m_giftList;
};


		

class CDBWritePresentResult: public CDBClientResult
{
public:
	CDBWritePresentResult()
	{
		m_saveId = 0;
	}
	unsigned long long m_saveId;
};

class CDBNewMicPressentResult: public CDBClientResult
{
public:
	CDBNewMicPressentResult()
	{
		presentMoney = 0;
		m_saveId = 0;
		memset(szStart, 0, sizeof(DATAPORT_TIME_LEN));
		memset(szEnd, 0, sizeof(DATAPORT_TIME_LEN));
	}
	char szStart[DATAPORT_TIME_LEN];
	char szEnd[DATAPORT_TIME_LEN];
	uint32 presentMoney;
	unsigned long long m_saveId;
};

struct PresentInfo
{
	unsigned long uin;
	unsigned long roomid;
	unsigned long remineMinutes;
	unsigned long presentMoney;
	unsigned short gotGift;
	unsigned short gotTextChat;
	unsigned long long presentid;
};
typedef std::vector<PresentInfo> PresentInfoList;
class CDBGetPresentResult: public CDBClientResult
{
public:
	CDBGetPresentResult()
	{
		m_presentMoney = 0;
	}
	unsigned long   m_presentMoney;
	unsigned long   m_errCode;
	PresentInfoList m_presentInfo;
};

class CDBRoomBlockCheckNew:public CDBClientResult
{
public:
	CDBRoomBlockCheckNew()
	{
		m_nBlockTime = 0;
		m_nBlockType = 0;
	}
	unsigned int m_nBlockTime;
	int m_nBlockType;
};

class CDBImUserLocationGetByIpResult : public CDBClientResult
{
public:
	CDBImUserLocationGetByIpResult()
	{
		memset(m_location, 0 ,sizeof(m_location));
		m_longitude = 0.0;
		m_latitude = 0.0;
	}
public:
	char m_location[DATAPORT_DATE_LEN];
	double m_longitude;
	double m_latitude;
}; 


struct RoomOnlineInfo
{
	unsigned long uin;
	unsigned long roomid;
	unsigned long svrid;
	unsigned long ip;
	unsigned short port;
	unsigned short devType;
	RoomOnlineInfo()
	{
		uin = 0;
		roomid = 0;
		svrid = 0;
		ip = 0;
		port = 0;
		devType = 0;
	}
};
typedef std::vector<RoomOnlineInfo> RoomOnlineInfoList;

class CDBGetRoomOnlineList : public CDBClientResult
{
public:
	CDBGetRoomOnlineList(){}
	virtual ~CDBGetRoomOnlineList(){};
public:
	RoomOnlineInfoList onlineInfoList;
}; 

struct ExpressionInfo
{
	unsigned int packetid;
	unsigned int expressionid;
	unsigned char num;
};

typedef std::vector<ExpressionInfo> ExpressionInfoList;

class CDBRoomLoginResult:
	public CDBClientResult
{
public:
	RoomUserInfo roomUserInfo;
	CDUserStampInfo stampInfo;
	CDBRoomBlockCheckNew blockInfo;
	CDBGetRoomOnlineList onLineList;
	unsigned int forbidStatus;
	unsigned int notalk_time;
	CDBRoomLoginResult()
	{
		memset(&roomUserInfo, 0, sizeof(roomUserInfo));
		forbidStatus = 0;
		notalk_time = 0;
	}
};

struct RoomAnchorInfo
{
	unsigned int uin;
	unsigned int roomid;
	RoomAnchorInfo()
	{
		uin = 0;
		roomid = 0;
	}
};
typedef std::vector<RoomAnchorInfo> RoomAnchorList;

class CDBRoomAnchorList: public CDBClientResult
{
public:
	CDBRoomAnchorList(){}
	virtual ~CDBRoomAnchorList(){}
	RoomAnchorList	roomAnchorList;
};


struct RoomGuardInfo
{
	unsigned int uin;
	unsigned int money;
	unsigned short order;
	char nickname[DATAPORT_NICK_LEN+1];

	RoomGuardInfo()
	{
		uin = 0;
		order = 0;
		money = 0;
		memset(nickname, 0, DATAPORT_NICK_LEN);
	}
	void operator = (const RoomGuardInfo &u)
	{
		memcpy(nickname, u.nickname, DATAPORT_NICK_LEN);

		uin = u.uin; 
		money = u.money;
		order = u.order;
	}
};
typedef std::vector<RoomGuardInfo> GuardUinList;

class CDBGuardUinList:public CDBClientResult
{
public:
	CDBGuardUinList(){}
	virtual ~CDBGuardUinList(){}
	unsigned int roomid;
	unsigned int anchorUin;
	GuardUinList guardUinList;
};

struct SingeInfo
{
	char nickname[DATAPORT_NICK_LEN+1];
	char songname[DATAPORT_TEXT_LEN+1];
	unsigned int opruin;
	unsigned int addtime;
	SingeInfo()
	{
		memset(nickname, 0, DATAPORT_NICK_LEN + 1);
		memset(songname, 0, DATAPORT_TEXT_LEN + 1);
	}
	void operator = (const SingeInfo &u)
	{
		memcpy(nickname, u.nickname, DATAPORT_NICK_LEN);
		memcpy(songname, u.songname, DATAPORT_TEXT_LEN);

		opruin = u.opruin; 
		addtime = u.addtime;
	}
};
typedef std::vector<SingeInfo> SingeInfoList;
class CDBSingeList:public CDBClientResult
{
public:
	CDBSingeList(){}
	virtual ~CDBSingeList(){}

	SingeInfoList singeInfoList;
};

class RedPacketsConfResult: public CDBClientResult
{
public:
	RedPacketsConfResult()
	{
		uinMaxLimit = uinMinLimit = redPacketRatio = minPlayTimesLimit = 0;
	}
	~RedPacketsConfResult(){}

	unsigned short uinMaxLimit;
	unsigned short uinMinLimit;
	unsigned short redPacketRatio;
	unsigned short minPlayTimesLimit;
	RedPacketsLevelList redPacketsLevelList;
};


class CDBGetVid: public CDBClientResult
{
public:
	CDBGetVid()
	{
		memset(chVid, 0, DATAPORT_VID_LEN);
	}
	virtual ~CDBGetVid(){}
	char	chVid[DATAPORT_VID_LEN]	;
};

class CDBOpenBoxResult: public CDBClientResult
{
public:
	CDBOpenBoxResult()
	{
		freeCount = 0;
	}
	virtual ~CDBOpenBoxResult(){}
	
	uint16 freeCount;
};


class CDBWeekStartList: public CDBClientResult
{
public:
	CDBWeekStartList()
	{
		
	}
	virtual ~CDBWeekStartList(){}

	DiamondWeekStarList weekList;
};

class CDBDiamondConf: public CDBClientResult
{
public:
	CDBDiamondConf()
	{
		diamon_receiver = 0;									//收礼人收入比
		diamon_company = 0;										//公司收入比例
		diamon_host = 0;										//室主比例
		diamon_pid = 0;											//站点比例
	};
	virtual ~CDBDiamondConf(){};


	uint8	diamon_receiver;									//收礼人收入比
	uint8	diamon_company;										//公司收入比例
	uint8	diamon_host;										//室主比例
	uint8	diamon_pid;											//站点比例
};




class CDBAndroidList: public CDBClientResult
{
public:
	CDBAndroidList(){}
	~CDBAndroidList(){}

	AndroidList m_androidList;

};
class CDBsentMonyResult: public CDBClientResult
{
public:
	CDBsentMonyResult()
	{
		promotion_uin = 0;
		newUserUin = 0;
		letaoUin  = 0;
	}
	~CDBsentMonyResult(){}
	unsigned int promotion_uin;
	unsigned int newUserUin;
	unsigned int letaoUin;
	//std::vector<unsigned int>ImBCSvrList;
	std::map <unsigned int,unsigned int>ImBCSvrList;
};
class CDBRoomShareResult: public CDBClientResult
{
public:
	CDBRoomShareResult()
	{
		share_num = 0;
	}
	~CDBRoomShareResult(){}
	int share_num;
};


class CDBGiftPool:public CDBClientResult
{
public:
	CDBGiftPool()
	{
		inMoney = outMoney = 0;
	}
	~CDBGiftPool(){}
	long long  inMoney;
	long long  outMoney;
};

class CDBSiegeInfo:public CDBClientResult
{
public:
	CDBSiegeInfo()
	{
		srcuin = 0;
		dstuin = 0;
		amount = 0;
		giftid = 0;
		starttime = 0;
		expiretime = 0;
		memset(srcnick, 0, sizeof(srcnick));
		memset(dstnick, 0, sizeof(dstnick));
	}
	~CDBSiegeInfo(){}
	char srcnick[DATAPORT_NICK_LEN+1];
	char dstnick[DATAPORT_NICK_LEN+1];
	unsigned int srcuin;
	unsigned int dstuin;
	unsigned int amount;
	unsigned int giftid;
	unsigned int starttime;
	unsigned int expiretime;
};

class CDBGiftDayRankInfo:public CDBClientResult
{
public:
	CDBGiftDayRankInfo()
	{
		srcuin = 0;
		diamond = "0";
		customface = 0;
		type = 0;
		memset(nick, 0, sizeof(nick));
	}
	~CDBGiftDayRankInfo(){}
	char nick[DATAPORT_NICK_LEN+1];
	unsigned int srcuin;
	string diamond;
	unsigned int customface;
	unsigned int type;
};


class DATAPORT_PUBLIC CDBClientBase
{
public:
    CDBClientBase (void);
    virtual ~CDBClientBase (void);

public:
    //在操作必须调用，且调用调用之后必须调用close关闭
    int open (int maxThreadNum,        //最大工作线程数量 100
               const char *url,         //目标服务器地址  例如 http://192.168.20.21:9101
			   const char *secret,      //md5加密的签名密码 例如 "123456"
			   const char * appkey = NULL,     //判断用户的权限一个用户对应一个secret
			   int direct = 0);          

    //调用open之后才需要调用并且在销毁实例之前调用
    void close (void);

public:
    // origin: 登录方式("PC"或"WEB")
    // place: 登陆地点
    void Login (unsigned int pid,
                std::string uin,
                unsigned int roomid,
                const char *passwd,
                const char *vcode,
                const char *ip,
                const char *mac,
                const char *origin,
				unsigned char passType,
				unsigned char checkLastDevice,
				unsigned int deviceType,
				unsigned char authType,
                void * arg);
	// 查询禁言
	void ForbidChat(unsigned int partnerid,
					unsigned int roomid,
					unsigned int uin,
					void * arg);
    //登出
    void Logout (unsigned int pid,
                 unsigned int uin,
                 unsigned int roomid,
                 const char *ip,
                 const char *mac,
                 const char *origin,
				 int logoutType,
                 void * arg);
    //更改密码
    void ChangePassword (unsigned int pid,
                         unsigned int uin,
                         const char *old_pwd,       //旧的密码
                         const char *new_pwd,       //新的密码
						 const unsigned char type,
                         void * arg);
    //查询帐号资金余额
    void QueryMoney (unsigned int pid,
                     unsigned int uin,
                     void * arg);
    //添加好友
    void AddFriend (unsigned int pid,
                    unsigned int uin,
                    unsigned int fid,
					int isUpdate,
					unsigned long long sendMoney,
                    void * arg);
    //删除好友
    void DelFriend (unsigned int pid,
                    unsigned int uin,
                    unsigned int fid,
					int isUpdate,
                    void * arg);
    //得到好友列表
    void GetFriend (unsigned int pid,
                    unsigned int uin,
                    void * arg);
    //更改用户信息
    void ChangeUserInfo (unsigned int pid,
                         unsigned int uin,
                         const IMUserInfo & userInfo,         //返回用户信息

                         void * arg);
    //检查是否被封锁的 
    void CheckRoomBlock (unsigned int pid,
                         unsigned int uin,
                         unsigned int roomid,                                  
                         const char *ip,
                         const char *mac,
                         void * arg);

	//检查是否被封锁的 (新接口)
	void CheckRoomBlockNew (unsigned int pid,
		unsigned int uin,
		unsigned int roomid,                                  
		const char *ip,
		const char *mac,
		void * arg);

    //获取房间信息
    void GetRoomInfo ( unsigned int pid,
                       unsigned int roomid,
                       unsigned int serverid,
                       void * arg);
    //获取礼物列表
    void GetGiftInfo (unsigned int pid,
                      void * arg);
    //获取刷花排行
    void GetRichInfo (unsigned int pid,
                      void * arg);
    //保存房间广播或全站广播
    void SaveBroadCast(unsigned int pid,
                       unsigned int roomid,
                       unsigned int uin,
                       unsigned int broadcastDone,
                       const char * broadcast,
					   unsigned short flag_vip,
                       void * arg);
    // 获取超管名单 
    void GetSuperManager (unsigned int pid,
                          void * arg);
    //加载权限
    void LoadAcl ( unsigned int pid,
                   unsigned int act,    //操作类型1踢人/2封锁/3抱麦/4禁言
				   unsigned short vip_flag,
                   void * arg);
    //更改用户数量
    void ModifyCurrUser( unsigned int pid,
                         unsigned int roomid,
                         unsigned int srvid,
                         unsigned int curruser,
                         unsigned int currVuser,
						 unsigned int uin_num,
						 unsigned int black_user,
                         void * arg);
    //更改房间信息
    void ModifyRoomInfo(unsigned int pid,
						unsigned int roomid,
                        const char * name,
                        const char * descript,                //房间描述
                        const char * adv,                     //房间广播
                        unsigned char auth,             //??
                        unsigned char ispublic,
						unsigned short micMaxTime,
                        void * arg);
    //获取服务器信息
    void GetServerInfo(unsigned int serverid,
                       void * arg);
    //添加黑名单
    void AddRoomBlack(unsigned int roomid,
                      unsigned int dst,
                      unsigned int operatorUin,
                      unsigned int pid,
					  unsigned int blockTime,
                      const char * nick,
                      const char * mac,
                      const char * ip,
					  const char * memo,
					  unsigned short vip_flag,
					  unsigned int max_num,
                      void * arg);
	//车行添加到限制名单
	void AddGameLimit(unsigned int roomid,
                      unsigned int dst,
					  unsigned int operatorUin,
					  unsigned int pid,
					  void * arg);
    //更改房间密码
    void ModifyRoomPass(unsigned int roomid,
                        const char * pass,
                        void * arg);
    //更改房间状态
    void RoomChangeStatus(unsigned int roomid,
                          unsigned char openstatus,
                          void * arg);
    //房间时间
    void UpdateUserTimeExt3(unsigned int uin,
                            unsigned int pid,
	                        unsigned int flashtime,
	                        unsigned int lastMsgID,
	                        const char * lastip,
	                        const char * mac,
							const unsigned int logouttime,
							std::map<uint32, AttentionPartnerInfo> attList,
                            void * arg);
    void UpdateUserTime(unsigned int roomid,
	                    unsigned int uin,
                        unsigned int pid,
	                    unsigned int flashtime,
	                    unsigned int ip,
	                    unsigned char flag,
                        void * arg);
    //刷花
    void UseGift(unsigned int srcPid, 
                 unsigned int roomid,
                 unsigned int hostUin,
                 unsigned int srcuin,
                 unsigned int dstuin,
                 unsigned int dstType,
                 unsigned long long sendCount,
                 unsigned long long recverCount,
                 unsigned long long companyTax,
                 unsigned long long hostTax,
                 unsigned long long poolCount,
                 unsigned long long prizeCount,
                 unsigned int giftid,
                 unsigned int giftnum,
				 unsigned int host_type,
				 unsigned long long rebate,
	             const char * desc,
				 const char * vid,
                 void * arg);


	//点歌
	void UseVod(unsigned int srcPid, 
				unsigned int roomid,
				unsigned int hostUin,
				unsigned int srcuin,
				unsigned int dstuin,
				unsigned int dstType,
				unsigned int sendCount,
				unsigned int recverCount,
				unsigned int companyTax,
				unsigned int hostTax,
				unsigned int poolCount,
				unsigned int prizeCount,
				unsigned int giftid,
				unsigned int giftnum,
				unsigned int host_type,
				unsigned int rebate,
				const char* songName,
				const char* nickName,
				void * arg);
    //购买小喇叭
    void BuyGlobleMsg ( unsigned int uin,
                        unsigned int pid,
                        unsigned int price,
                        void * arg);

	void BuyRoomBroadcast (unsigned int pid,
						unsigned int roomid,
						unsigned int uin,
						unsigned int max_times,
						unsigned int diamond,
						void * arg);
    //通知其他人
    void NotifyOther ( unsigned int partnerid,
                       unsigned int svid,
                       const char * msg,
                       void * arg);
    ////通知其他人
    void NotifyOther2 ( unsigned int partnerid,
                        unsigned int svid,
                        const char * msg,
                        void * arg);
    //更改管理员
    void ModifyMgr( unsigned int act,
                    unsigned int roomid,
                    unsigned int uin,
                    const char * nickName,
                    unsigned int partnerid,
                    void * arg);
	//上麦
    void LogOnMic( unsigned int partnerid,
                   unsigned int roomid,
                   unsigned int dst, 
                   unsigned int starttime,
                   unsigned int onmicTime,
                   unsigned int micIndex,
                   void * arg);
	////上麦送币  废弃  新接口替代
 //   void PersentMicUserMoney( unsigned int uin,
 //                             unsigned int pid,
 //                             unsigned int num,
 //                             unsigned int ip,
 //                             unsigned long long userStrMac,
 //                             void * arg);
    //获取登陆消息
    void GetEnterInfo( unsigned int partnerid,
                       void * arg);
    //加载机器人
    void LoadAndRoid( unsigned int pid,
                      unsigned int roomid,
                      void * arg);
    //获取合作商信息
    void GetPartnerInfo( unsigned int partnerid, 
                         unsigned int svrid,
						 void * arg);
	//插入弹出消息
	void InsertPopupMsg( unsigned int dst,
						 unsigned int type,
						 unsigned int fid,
						 unsigned int src,
						 const char * msg,
						 const char * url,
						 unsigned int pid,
						 void * arg);
	//发送离线消息
	void InsertOfflineMsg( unsigned int dst,
						   unsigned int type,
						   unsigned int when,
						   unsigned int src,
						   const char * text,
						   unsigned int partnerid,
						   void * arg);

	//获取消息
	void GetNewBCMsg( unsigned int msgid,
						 void * arg);
	//获取娱乐币信息
	void MoneyGetMoney( unsigned int uin,
						unsigned int pid,
						void * arg);
	//用户上线信息
	void InsertOnline( unsigned int uin,
					   const char * skey,
					   unsigned int loginmainver,
					   const char * loginip,
					   const char * loginmac,
					   unsigned int  partnerid,
					   std::string mobileSessionKey,
					   std::string mobileIp,
					   std::string mobileMacAddr,
					   std::string pcMacID,
					   std::string cpuID,
					   std::string boardSerNum,
					   std::string biosSerNum,
					   std::string diskSerNum,
					   unsigned int serverId,
					   void * arg);

	//用户离线
	void UserOffLine( unsigned int uin,
					  unsigned int pid,
					  const char * ip,
					  const char * mac,
					  void * arg);

	void UserRoomOnline(unsigned int pid,
						unsigned int uin,
						unsigned int svrid,
						unsigned int roomid,
						unsigned int ip,
						unsigned int port,
						unsigned char devType,
						const char *mac,
						unsigned char level,
						unsigned char lordlevel,
						unsigned short usertype,
						unsigned char richOrder,
						unsigned char wayType,
						void *arg);

	void UserRoomOffline(unsigned int pid,
						 unsigned int uin,
						 unsigned int svrid,
						 unsigned int roomid,
						 void *arg);

	void UserClearRoomOnline(unsigned int pid,
							 unsigned int svrid,
							 void *arg);

	void UserGetRoomOnline(unsigned int pid,
						   unsigned int uin,
						   void *arg);

	//获取最喜欢的房间信息
	void GetFavRoom( unsigned int uin,
					 unsigned int pid,
					 void * arg);
	//添加喜欢的房间
	void AddFavRoom( unsigned int uin,
					 unsigned int roomid,
					 unsigned int pid,
					 void * arg);
	//删除喜欢房间
	void DelFavRoom( unsigned int uin,
					 unsigned int roomid,
					 unsigned int pid,
					 void * arg);

	// 验证好友添加请求	
	void QueryAuth( unsigned int dst,
					unsigned int pid,
					void * arg);
	// 删除我加的和加我的好友
	void DelFriendMyAndAdd( unsigned int src,
						    unsigned int dst,
						    unsigned int pid,
							void * arg);
	//将我从对方好友列表中删除
	void DelAddFriend( unsigned int src,
					   unsigned int dst,
					   unsigned int pid,
					   void * arg);

	//获取加我的好友
	void GetAddMyFriend( unsigned int uin,
						 unsigned int pid,
						 void * arg);
	//获取离线消息
	void GetOfflineMsg(unsigned int pid,
					   unsigned int uin,
					   void * arg);

	//获取离线系统消息
	void GetOfflineBCMsg( unsigned int msgid,
						  unsigned int pid,
						  void * arg);

	//获取离线弹出式系统消息
	void GetOfflinePopupMsg( unsigned int uin,
							 unsigned int pid,
							 unsigned char deviceType,
							 void * arg);

	//新用户送金币
	void MoneyNewUin( unsigned int uin,
					  unsigned int pid,
					  const char *desc,
					  unsigned int num,
					  void * arg);
	//获取联系人信息
	void GetContact( unsigned int pid,
					 unsigned int dst,
					 void * arg);
	//是否是新用户
	void UserNewUin( const char * passwd,
					 const char * ip,
					 const char * mac,
					 unsigned int partnerid,
					 unsigned int presentMoney,
					 void * arg);

	//更新联系人列表
	void UpdateContact( unsigned int dst,
						unsigned int pid,
						void * arg);


	//金币转账
	void TransferMoney( unsigned uin,
					    unsigned int dstuin,
					    unsigned long long transferMoney,
					    unsigned long long willTax,
					    const char * passwd,
					    unsigned int pid,
					    void * arg);

	//检查用户是否被封锁
	void CheckUserBlock( unsigned int pid,
						 unsigned int uin,
						 const char * mac,
						 const char * ip,
						 void * arg);
	//获取房间地址
	void GetFlockAddr( unsigned int roomid,
					   unsigned int pid,
					   unsigned int partnerId,
					   void * arg);
	//IM获取合作商信息
	void GetPartnerInfoForIM( unsigned int pid,
							  void * arg);
	//IM获取所有合作商信息
	void GetPartnerInfoAll(void * arg);
	//获取为用户保存的信息(合并的接口)
	void GetFriendRoomCombine(unsigned int pid,
					unsigned int uin,
					uint8 kind,
					void * arg);
	//获取离线消息(合并的接口)
	void GetOffLineMsgCombine(unsigned int pid,
					unsigned int uin,
					uint8 kind,
					unsigned int lastTime,
					unsigned int status,
					unsigned short devicType,
					unsigned long msgid,
					unsigned short msgType,					
					void * arg);
	//搜索用户
	void SearchService( unsigned int start,
						const char * province,
						unsigned int partnerid,
						void * arg);

	//获取更新的合作商信息
	void GetPartnerInfoList( unsigned int lastupdate,
							 void * arg);
	//搜索用户
	void SearchUin( unsigned int uin,
				    unsigned int partnerid,
					void * arg);
	//搜索区域用户
	void SearchSection( unsigned int start,
						unsigned int end,
						unsigned int partnerid,
						void * arg);
	//查找在线用户
    void SearchService( unsigned int start,
					    unsigned int province,
					    unsigned partnerid,
						void * arg);
	//自定义搜索
	void SearchCustom( unsigned int start,
					   const char * nick,
					   const char * email,
					   unsigned int partnerid,
					   void * arg);
	//获取用户盖章信息
	void GetUserStampInfo( unsigned int pid,
						   unsigned int uin,
						   void * arg);      //返回结果类 CDUserStampInfo
	
	//用户盖章
	void UserStamp( unsigned int dst,
				    unsigned int src,
					unsigned int pid,
					unsigned int stampID,
					unsigned int stampExpire,
					unsigned int stamptype,  //盖章类型 0是盖章 1是反盖
					const char * stampMsg,
					void * arg);       //返回结果类CDUserStamp


	//用户清除盖章
	void EarseStamp(unsigned int pid,
					unsigned int uin,
					void * arg);       //返回结果类CDUserStamp


	////多任务多次获取信息
	//void MultiLogin(unsigned int pid,
	//	           unsigned int uin,
	//	           unsigned int roomid,
	//	           const char *passwd,
	//	           const char *vcode,
	//	           const char *ip,
	//	           const char *mac,
	//	           const char *origin,
	//			   unsigned char loginType,
	//			   unsigned char wayType,
	//			   unsigned char passType,
	//	           void * arg);

	//多任务多次获取信息
	void RoomLogin(unsigned int pid,
		unsigned int uin,
		unsigned int roomid,
		const char *passwd,
		const char *vcode,
		const char *ip,
		const char *mac,
		const char *origin,
		const char *sRoomAccess,
		unsigned char loginType,
		unsigned char wayType,
		unsigned char passType,
		void * arg);

	//多任务多次获取信息
	void VipRoomLogin(unsigned int pid,
		unsigned int uin,
		unsigned int roomid,
		const char *passwd,
		const char *vcode,
		const char *ip,
		const char *mac,
		const char *origin,
		const char *sRoomAccess,
		unsigned char loginType,
		unsigned char wayType,
		unsigned char passType,
		void * arg);

	//zz多任务多次获取信息
	void MultiLoginZZ(unsigned int pid,
		unsigned int uin,
		unsigned int roomid,
		const char *passwd,
		const char *vcode,
		const char *ip,
		const char *mac,
		const char *origin,
		void * arg);

	void MultiLoginPPC(unsigned int pid,
						unsigned int uin,
						unsigned int roomid,
						const char *passwd,
						const char *vcode,
						const char *ip,
						const char *mac,
						const char *origin,
						const char *sRoomAccess,
						unsigned char loginType,
						unsigned char wayType,
						unsigned char passType,
						void * arg);


	void MultiLoginPPCVip(unsigned int pid,
							unsigned int uin,
							unsigned int roomid,
							const char *passwd,
							const char *vcode,
							const char *ip,
							const char *mac,
							const char *origin,
							const char *sRoomAccess,
							unsigned char loginType,
							unsigned char wayType,
							unsigned char passType,
							void * arg);


	void MultiLoginRoom(unsigned int pid,
		unsigned int servid,
		unsigned int uin,
		unsigned int roomid,
		const char *passwd,
		const char *vcode,
		const char *ip,
		const char *mac,
		const char *origin,
		const char *sRoomAccess,
		unsigned char loginType,
		unsigned char wayType,
		unsigned char passType,
		void * arg);


	// 添加禁言
	void AddForbidChat(unsigned int uin,
					   unsigned int pid,
					   unsigned int roomid,
					   const char * nick,
					   unsigned int operatorUin,
					   unsigned int expire_time,
					   const char * strMsg,
					   unsigned short vip_flag,
					   unsigned int  max_num,
					   void * arg);

	void AddRoomAssistant(unsigned int pid,
							unsigned int roomid,
							unsigned int uin,
							void * arg);

	void DelRoomAssistant(unsigned int pid,
							unsigned int roomid,
							unsigned int uin,
							void * arg);

	void GetStampGiftList( unsigned int pid,
						   void *arg);


	void QueryUserInfo( unsigned int pid,
						unsigned int uin,
						void * arg);

	
	void InsertOfflineMsg_new( unsigned long long msgId,
							   unsigned int dst,
							   unsigned int type,
							   unsigned int when,
							   unsigned int src,
							   const char * text,
							   unsigned int dstPid,
							   unsigned int status,
							   unsigned long srcPid,
							   unsigned long subUin,
							   void * arg);
	void GetOfflineMsg_new( unsigned int lastTime,
							unsigned int status,
							unsigned int pid,
							unsigned int uin,
							void * arg);

	void UpdateOfflineMsg_new( unsigned long long msgId[DATAPORT_MESSAGE_MAX],
		                       unsigned int status,
							   unsigned int pid,
							   unsigned int uin,
		                       void * arg);

	void GetLastLogOutTime( unsigned int pid,
						    unsigned int uin,
						    void *arg);

	void AddPidBlock(unsigned int pid,
					  unsigned int srcuin,
					  unsigned int dstuin,
					  const char* blockItem,
					  const char* blockNick,
					  const char* msg,
					  void *arg);

	

	//添加到黑名单
	void InsertToBlackList(std::list<unsigned int> &destList,
		unsigned long pid,
		unsigned long uin,
		void *arg);
	void DeleteFromBlackList(std::list<unsigned int> &destList,
		unsigned long pid,
		unsigned long uin,
		void *arg);
	void GetBlackListFormDB(unsigned long pid, unsigned long uin, void *arg);
	void GetSessionKeyFromDB(unsigned int pid, unsigned int uin, void *arg);

	void UpdateRemarkFromeDB(unsigned long pid, unsigned long uin, unsigned long destid, std::string &remark, void* arg);
	//获取用户详情
	void UserDetailInfoGetFromDB(unsigned long pid, unsigned long uin, void *arg);

	void UserDetailInfoUpdateFromDB(unsigned long pid, unsigned long uin, std::string &info, void *arg);
	void MobileUpdataDeviceInfoFromDB(unsigned long pid, unsigned long long uin, std::string uniqueIdentifier, void *arg);
	void MobileDeviceInfoGetFromDB(unsigned long pid, unsigned long uin, void *arg);
	void MobileUpdataPushTokenFromDB(unsigned long pid, unsigned long uin, std::string pushToken, std::string channerlNumber, void *arg);
	void MobilePushTokenGetFromDB(unsigned long pid, unsigned long uin, unsigned long uinRemark,  void *arg);
	void ImGetGiftListFromDB(unsigned long pid, void * arg);
	void ImPresentGift( unsigned long pid, 
						unsigned long srcUin, 
						unsigned long destUin, 
						unsigned long giftId, 
						unsigned long giftNum,
						unsigned long roomid,
						unsigned long hostUin,
						unsigned long destType,
						unsigned long prizeCnt,
						short poolTaxFlag,
						short needAddFriend,
						void *arg);
	void ImGetLastChatServiceUin(unsigned long pid, unsigned long uin, unsigned char userType, void *arg);
	void ImInsertChatRecords(unsigned long srcId, unsigned long srcPid, unsigned long destId, unsigned long destPid, 
							 unsigned short type, std::string &text, unsigned long long msgId, unsigned short status,
							 unsigned long msgTime, void *arg);
	void ImGetUserAllInfo(unsigned long pid, unsigned long uin, void *arg);
	void InsertNewSituationNotify(unsigned long pid, std::vector<unsigned int> &uinList, void *arg);
	void GetNewSituationNotify(unsigned long pid, unsigned long uin, void*arg);
	void ImInsertOfflineGift(unsigned long srcUin, unsigned long srcPid, unsigned long destUin, unsigned long destPid,
							 unsigned long giftId, std::string giftName, unsigned long long charmValue,
							 unsigned long giftNum, unsigned short type, unsigned long currTime, void *arg);
	void ImGetOfflineGift(unsigned long uin, unsigned long pid, void *arg);
	void ImGetUserLocationByIp(unsigned int uin, unsigned int pid, std::string ip, void *arg);
	void ImClearOnlineTable(unsigned int svrId, void *arg);
	/*
	* << reviewNotify->m_destNick;
	*/
	
	//向群体刷花 
	void UseGiftForMany( unsigned int srcPid,         
				         unsigned int roomid,
				         unsigned int hostUin,      //室主uin
				         unsigned int srcuin,       //刷花用户id
				         unsigned int * dstuins,         //以uin==0 时计算数量 最大 DATAPORT_DSTUIN_MAX
				         unsigned int sendCount,    //向单个用户刷花送币
				         unsigned int companyTax,   //单个用户的公司税收
				         unsigned int hostTax,      //单个用户的室主税收
				         unsigned int giftid,       //礼物id  
				         unsigned int giftnum,      //单个用户收到的礼物数量  
				         void * arg,
						 unsigned int poolCount = 0,  //单个用户的奖池数量
						 unsigned int prizeCount = 0  //中奖金额
						 );
        //删除禁言
	void DelForbidChat( unsigned int partnerid,
						unsigned int uin,
						unsigned int roomid,
						void * arg);


	


	//转转游戏相关接口定义
	//押注
	void ZZBetMoney(unsigned int partnerid,
					unsigned int roomid,
					unsigned int uin,
					unsigned long awardRound,
					unsigned long awardAmount,	//押注金额
					unsigned int taxRate,	//利润率 税率
					const char* pDesc,
					unsigned long userip,
					unsigned long long userMac,
					void * arg
					);
	//中奖
	void ZZAwarded(unsigned int partnerid,
				 unsigned int roomid,
				 unsigned int uin,
				 unsigned long awardRound,
				 unsigned int awardid,		//开奖结果
				 unsigned long awardAmount,	//中奖金额
				 const char* pDesc,
				 unsigned long userip,
				 unsigned long long userMac,
				 void * arg
				 );

	//保存中奖结果
	void ZZSaveAwared(unsigned int partnerid,
					unsigned int roomid,
					unsigned long awardRound,
					unsigned int awardid,		//开奖结果
					void * arg);
	
	//获取当天开奖结果
	void ZZAwaredHistory(unsigned int partnerid, unsigned int roomid, void * arg);

	//奖池读取
	void ZZLoadPool(unsigned int partnerid, unsigned int roomid, void * arg);
	
	//读取各奖项信息
	void ZZLoadAwardItemsInfo(unsigned int partnerid, void * arg);


	//void GetPCinfo(unsigned int partnerid, unsigned int uin, void * arg);
	//ppc相关定义
	void LockMoney(unsigned int partnerid,
				   unsigned int uin,
				   unsigned char lockState,
				   void * arg,
				   unsigned int gameKind = 0);

	void GetUserCurMoney(unsigned int partnerid,
		unsigned int uin,
		void * arg);

	void SaveExperience(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						void * arg);
	
	void GetExperience(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						void * arg);

	void LoadPPCHistory(unsigned int partnerid,
						unsigned int roomid,
						unsigned int pageCount,
						void * arg);

	void PPCBetMoneyList(unsigned int partnerid,
						unsigned int roomid,
						unsigned long awardRound,
						unsigned char bSysBanker,
						std::vector<unsigned int>& uinList,
						std::vector<long long>& moneyList,
						std::vector<long long>& taxList,
						std::vector<std::string>& descList,
						std::vector<unsigned long long>& macList,
						unsigned short userKind,
						unsigned short roomBetKind,
						unsigned short roomAwardKind,
						unsigned short macBetKind,
						unsigned short macAwardKind,
						unsigned short gametickKind,
						void * arg,
						unsigned int gameKind = 0);

	void PPCSaveAwardList(unsigned int partnerid,
							unsigned int roomid,
							unsigned long awardRound,
							unsigned char bSysBanker,
							std::vector<unsigned int>& uinList,
							std::vector<long long>& moneyList,
							std::vector<long long>& taxList,
							std::vector<std::string>& descList,
							std::vector<unsigned long long>& macList,
							unsigned short userKind,
							unsigned short roomBetKind,
							unsigned short roomAwardKind,
							unsigned short macBetKind,
							unsigned short macAwardKind,
							unsigned short gametickKind,
							void * arg,
							unsigned short taxKind,
							unsigned int gameKind = 0);

	void PPCGetBalanceInfo(unsigned int partnerid,
							unsigned int roomid,
							unsigned short roomBetKind,
							unsigned short roomAwardKind,
							void * arg);

	void PPCGetConfig(unsigned int partnerid,
					  char type,
					  void * arg);

	void PPCGetUserBlance(unsigned int partnerid,
						unsigned long long mac,
						unsigned short macBetKind,
						unsigned short macAwardKind,
						void * arg);
	
	void PPCCheckPpcBlock(unsigned int partnerid,
		                 unsigned long long mac,
						 unsigned int uin,
						 void * arg);

	void PPCGetDisconnectTimes(unsigned int partnerid,
		                      unsigned long long mac,
							  unsigned int uin,
							  void * arg);

	void PPCIncrDisconnectTimes(unsigned int partnerid,
		                       unsigned long long mac,
							   unsigned int uin,
							   void * arg);

	void PPCSaveBankerResult(unsigned int partnerid,
							unsigned int roomid,
							unsigned long awardRound,
							unsigned int awardid,
							unsigned int uin,
							long long money,
							long long tax,
							unsigned short bankerKind,
							unsigned short taxKind,
							void * arg,
							unsigned int gameKind);

	
	void WriteOnMicPresent(unsigned int partnerid,
						   unsigned int roomid,
						   unsigned int uin,
						   unsigned long presentMoney,
						   unsigned long ip,
						   unsigned long long userMac,
						   unsigned short gotGift,
						   unsigned short gotTextChat,
						   void * arg);

	void GetOnMicPresent(unsigned int partnerid,
						 unsigned int roomid,
						 unsigned int uin,
						 long long presentid,
						 unsigned int expire_time,
						 unsigned int micPresentRate,
						 void *arg);

	void NewMicPressent(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						unsigned long presentMoney,
						unsigned long ip,
						unsigned long long userMac,
						unsigned short gotGift,
						unsigned short gotTextChat,
						unsigned short ips,
						unsigned short macs,
						unsigned char  type,
						void * arg);


	void SendExpression(unsigned int partnerid,
						unsigned int uin,
						ExpressionInfoList* infoList,
						int coinType,
						void *arg);

	void AddRoomAnchor(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						void *arg
					  );

	void DelRoomAnchor(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						void *arg
						);

	void GetRoomAnchorList(unsigned int partnerid,
							unsigned int roomid,
							unsigned int uin,
							void *arg
							);

	void GetRoomGuardList(unsigned int partnerid,
							unsigned int roomid,
							unsigned int anchorUin,
							unsigned int count,
							unsigned int kind,
							void *arg
							);

	void GetSingerOrderList(unsigned int partnerid,
							unsigned int anchorUin,
							void *arg);


	void WriteRoomGuard(unsigned int partnerid,
							unsigned int roomid,
							unsigned int uin,
							unsigned int anchorUin,
							unsigned int money,
							const char* nick,
							unsigned int kind,
							void *arg
							);






	void HolidayPresent(unsigned int partnerid,
						unsigned int uin,
						unsigned int money,
						const char *mac,
						void *arg
						);


	void GetRedPacketsConf(unsigned int partnerid, void *arg);

	void SendRedPackets(unsigned int partnerid,
						unsigned int servid,
						unsigned int tableid,
						unsigned int uin,
						unsigned int nums,
						unsigned char flag,
						unsigned int startTime,
						unsigned char redLevel,
						unsigned long long money,
						const char* msg,
						void *arg);

	void RobRedPackets(unsigned int partnerid,
						unsigned int servid,
						unsigned int tableid,
						unsigned char level,
						unsigned int uin,
						unsigned long long redid,
						unsigned long long childid,
						unsigned long long redMoney,
						unsigned int taxMoney,
						unsigned int startTime,
						const char* mac,
						void *arg);


	void RefundMoney(unsigned int partnerid,
					unsigned int tableid,
					unsigned int uin,
					unsigned long long redid,
					void *arg);

	void Foregift(unsigned int partnerid,
					unsigned int servid,
					unsigned int uin,
					unsigned short kind,
					unsigned char flag,
					unsigned long long money,
					void *arg);

	void RefundMoneyAll(unsigned int partnerid,
						unsigned int servid,
						void *arg);

	void ForegiftAll(unsigned int partnerid,
					 unsigned int servid,
					 void *arg);

	void ClearTableAll(unsigned int partnerid,
						unsigned int servid,
						void *arg);

	void ModifyRedGameInfo(unsigned int partnerid,
							unsigned int servid,
							unsigned int roomid,
							unsigned int owner,
							unsigned char level,
							unsigned int startTime,
							unsigned int endTime,
							void *arg);

	void ModifyAllRedGame(unsigned int partnerid, unsigned int servid,unsigned int endTime, void *arg);


	void GetBoxConfig(unsigned partnerid, void *arg);

	void GetBoxItemInfo(unsigned partnerid, void *arg);

	void GetBoxBlance(unsigned partnerid, void *arg);

	void SaveOpenBoxInfo(unsigned int partnerid,
						unsigned int roomid,
						unsigned int uin,
						unsigned char isFree,
						unsigned long long spanMoney,
						unsigned int awardid,
						unsigned long long awardMoney,
						unsigned long long rateMoney,
						unsigned short freeCount,
						unsigned int ip,
						unsigned long long mac,
						void *arg);

	void GetBoxFreeCount(unsigned int partnerid,
						 unsigned long long mac,
						 void *arg);
	
	void RedUserInfo(unsigned int partnerid,
					 unsigned int servid,
					 unsigned int roomid,
					 unsigned char level,
					 unsigned int nums,
					 unsigned int startTime,
					 void *arg);


	void GetWeekStarList(unsigned int partnerid,
						 void *arg);

	void GetDiamondConfig(unsigned int partnerid,
						  void *arg);

	void UpdateWeekStar(unsigned int partnerid,
						 unsigned int uin,
						 unsigned int giftid,
						 unsigned long long num,
						 void *arg);

	void DiamondUseGift(unsigned int srcPid, 
						unsigned int roomid,
						unsigned int hostUin,
						unsigned int srcuin,
						unsigned int dstuin,
						unsigned long long sendCount,
						unsigned long long recverCount,
						unsigned long long companyTax,
						unsigned long long hostTax,
						unsigned long long siteTax,
						unsigned int giftid,
						unsigned int giftnum,
						const char * desc,
						unsigned char btransfer,
						void * arg);

	void UpdateMicState(unsigned int pid,
							 unsigned int uin,
							 unsigned int roomid,
							 unsigned short micState,
							 unsigned int timeStamp,
							 unsigned int micIndex,
							 void* arg);


	void DiamonGuadWeekList(unsigned int pid,
							unsigned int roomid,
							unsigned int num,
							void* arg);
	

	//给推广用户发奖励接口
	void SentMonyToPromotionUser(unsigned int partnerid,
		                         unsigned int letaoPid,
								 unsigned int promotion_uin,
								 unsigned int new_uin,
								 unsigned int sentmony,
								 unsigned long long newUserMac,
								 void *arg);

	void GetRoomPromotionInfo(unsigned int partnerid,
		                      unsigned int roomid,
							  void * arg);

	


	//更新服务人数
	void UpdateSessionCount(unsigned int pid,
							unsigned int servid,
							unsigned int sessionCount,
							unsigned int roomNum,
							void* arg);

	void UpdateServerState(unsigned int pid,
						   unsigned int servid,
						   unsigned char state,
						   void* arg);

	void LoadGiftPool(unsigned int pid,
							void* arg);

	void LoadSiegeInfo(unsigned int pid, void* arg);

	void LoadGiftDayRankFirst(unsigned int pid,
							  unsigned int rommid,
							  unsigned int type,
							  void* arg);
	inline void SafePushTask();

	void NetTest(void* arg);
    /*
        异步调用返回接口
        result->errorCode结果为0 时成功
    */
    virtual void OnResult (CDBClientResult *result) = 0;

	void HotUpdate(bool bKeepConnected);

    
public:
    /*
    每30秒从负载均衡服务器定时获取目标服务器的地址url
    url == NULL时说明本次获取目标服务器地址失败
    池函数现在现在不使用
    */
    virtual void OnSrvUrlReturn (const char * url);
    /*
    初始化全局的运行环境，在调用接口之前必须且只能调用一次
    返回结果为零时调用成功
    */
    static bool GlobalDbCltInit (void);

    //保存接口信息,不需要使用
    class CDBClientBaseImpl;
private:
    CDBClientBaseImpl *impl;
};

} /* namespace dataport */

#endif /* _DATAPORT_CLIENT_H_ */
