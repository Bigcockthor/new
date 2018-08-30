#ifndef CACHEDEFINE_SLDKFJSLDFJSLDKFLSDFJSD
#define CACHEDEFINE_SLDKFJSLDFJSLDKFLSDFJSD
#include "include/xmlconfig.h"
#include <string>
#include "include/icqtypes.h"
#include "include/log.h"

using namespace std;

enum
{
	CACHE_TCP_VER = 1
};

enum
{
	DBHANDLE_SUCCESS = 0x0001,									//操作成功
	DBHANDLE_FAILED,											//操作失败
	DBHANDLE_WRONG_PASSWD,
	DBHANDLE_NOT_FIND_ROOM,

	DBH_INVALID_UIN,
};

enum 
{
	CHECKUSER_SUCCESS = 0x0001,
	CHECKUSER_FAILED,
	CHECKUSER_INVALID_UIN,
	CHECKUSER_WRONG_PASSWD,
	CHECKUSER_NO_MEMBER,
	CHECKUSER_BLOCKED,											//被封锁，弃用
	CHECKUSER_NEEDPAY,											//需要支付
	CHECKUSER_PAYFAILED_INGAME,									//付款失败,当前在游戏中
	CHECKUSER_PAYFAILED_NOENOUGH,								//付款失败,余额不足
	CHECKUSER_NEEDPAYBUTFAILED,									//付款失败
	CHECKUSER_NOTCLASSMEMBER,									//非班级成员,不能以班级成员身份进入
	CHECKUSER_NOT_SUBSCRIBER,									//非房主订阅用户
	CHECKUSER_INGAME,											//当前在游戏房间
	CHECKUSER_BLOCK_IP,											//ＩＰ被封锁
	CHECKUSER_BLOCK_MAC,										//MAC被封锁
	CHECKUSER_BLOCK_UIN,										//UIN被封锁

	CHECKROOM_SUCCESS = 0x0100,
	CHECKROOM_INVAILD_ROOM,  	
	CHECKROOM_WRONG_PASSWD,	
};

enum {
	CACHE_TCPSRV_LOGIN = 0x0001,
	CACHE_TCPSRV_LOGOUT,
	CACHE_TCPSRV_KEEPALIVE,

	CACHE_IM_GET_BLACKLIST			= 0x0100,					//获取网站黑名单


	CACHE_IM_NEWUIN = 0x0150,									//新增用户
	CACHE_IM_USER_LOGIN,
	CACHE_IM_OFFLINE,
	CACHE_IM_INSERT_ONLINE,
	CACHE_IM_CLEAR_MEM_CACHE,									//清理用户缓存



	CACHE_IM_SEARCHSERVICE			= 0x0200,
	CACHE_IM_SEARCHSECTION,
	CACHE_IM_SEARCHUIN,
	CACHE_IM_SEARCHCUSTOM,
	CACHE_IM_QUERYAUTH,

	CACHE_IM_CONTACTLIST			= 0x250,
	CACHE_IM_ADDFRIEND,
	CACHE_IM_DELFRIEND,
	CACHE_IM_DELADDFRIEND,
	CACHE_IM_GET_MYFRIEND,
	CACHE_IM_GET_ADDFRIEND,
	CACHE_IM_DELFRIENDMYANDADD,



	CACHE_IM_MODIFY_USERINFO		= 0x300 ,
	CACHE_IM_GET_MONEY,
	CACHE_IM_UPDATEPASSWD,
	CACHE_IM_UPDATE_ONLINETIME,
	CACHE_IM_GET_CONTACT,
	CACHE_IM_UPDATE_BLOCK,										//更新封锁重试信息


	CACHE_IM_GET_OFFLINEMSG			= 0x0350,
	CACHE_IM_GETBCMSG,
    CACHE_IM_GETOFFLINE_BCMSG,
	CACHE_IM_GET_OFFLINEPOPUPMSG,
	CACHE_IM_INS_OFFLINEMSG,
	CACHE_IM_INSERT_POPUPMSG,



	CACHE_IM_GET_ROOM_ADDR			= 0x0400,
	CACHE_IM_ADDFAVROOM,										//收藏群
	CACHE_IM_DELFAVROOM,										//取消收藏
	CACHE_IM_GET_FAVROOM,										//获取我的收藏房间

	CACHE_IM_PRESENT_MONEY					= 0x0450,
	CACHE_IM_MONEY_TRANSFER,
	
	CACHE_ROOM_GET_SERVERINFO		= 0x0500,					//获取服务信息
	CACHE_ROOM_GET_SUPPERMANAGER,								//获取所有超管列表
	CACHE_ROOM_ROOMINFO,
	CACHE_ROOM_MODIFYINFO,										//修改房间
	CACHE_ROOM_MODIFYPASS,										//修改密码
	CACHE_ROOM_CHANGE_STATUS,									//设置开关
	CACHE_ROOM_CHG_USER_NUM,									//修改
	CACHE_ROOM_UPDATE_ONLINETIME,								//更新用户在房间时间
	CACHE_ROOM_USER_AUTH,										//用户进入认证
	CACHE_ROOM_ADDBLACK,										//添加黑名单
	CACHE_ROOM_USEGIFT,
	CACHE_ROOM_LOAD_PRIZE_INFO,									//获取税收、中奖总额
	CACHE_ROOM_BUY_GLOBLE_MSG,									//购买小嗽叭服务
	CACHE_ROOM_LOAD_RICH_INFO,									//获取富翁排名
	CACHE_ROOM_FORBID_CHAT,										//禁言用户
	CACHE_ROOM_LOG_ONMIC,										//记录用户上麦情况
	CACEH_ROOM_GET_ENTERINFO,									//读取进入房间
	CACEH_ROOM_GET_ACL,											//读取权限列表
	CACEH_ROOM_MODIFY_MGR,										//修改管理员
	CACEH_ROOM_LOAD_ANDROID,									//读取机器人
	CACHE_ROOM_ROOMINFO_XML,									//按xml返回房间信息
	CACHE_ROOM_GIFT_INFO,										//读取礼物详细信息
	CACHE_ROOM_USER_AUTH_XML,									//房间登陆，ＸＭＬ返回
	CACHE_ZHUANZHUAN_USER_AUTH,									//转转房间登陆信息
	CACHE_ROOM_SAVE_BROADCAST,									//保存全站广播或房间广播
	CACHE_ROOM_MIC_PRESENT,										//房间上麦赠送
	CACHE_ROOM_STAMP_INFO,										//取印章信息
	CACHE_ROOM_USEGIFT_LIST,									//批量刷礼
	CACHE_ROOM_USE_STAMP,										//用户之间盖章
	CACHE_ROOM_ERASE_STAMP,										//用户之间盖章


	CACHE_ROOM_ZZ_BET				= 0x550,					//转转押注	
	CACHE_ROOM_ZZ_AWARD,										//转转开奖
	CACHE_ROOM_ZZ_SETTING,										//押注开奖信息
	CACHE_ROOM_ZZ_HISTORY,										//开奖历史
	CACHE_ROOM_ZZ_ITEMS_NAME,									//各开奖项名称
	CACHE_ROOM_ZZ_SETTING2,										//新设置
	CACHE_ROOM_ZZ_BET_TAX,										//税收押注
	CACHE_ROOM_ZZ_POOL,											//转转奖池l
	
	CACHE_IM_PARTNER_INFO			= 0x600,					//合作商配置信息										
	CACHE_IM_PARTNER_LIST,										//合作商配置信息
	CACHE_IM_PARTNER_INFO_XML,									//
	CACHE_IM_PARTNER_LIST2,										//获取合作商列表
	CACHE_IM_PARTNER_INFO_XML_FORIM,							//获取合作商详细信息

	CACHE_NOTIFY_GET_NEW_ITEM		= 0x700,					//webnotify获取最新的消息
	CACHE_NOTIFY_DONE_ITEM,										//webnotify处理完一条
	CACHE_NOTIFY_OTHER,											//通知其他服务
	CACHE_NOTIFY_OTHER2,											//通知其他服务
	CACHE_DEF_END,
};


enum
{
	HDL_SUCCESS = 0x01,
	HDL_FAILED,
	HDL_WRONG_PASSWD,
	HDL_DB_ERROR,
	HDL_NO_FIND_FLOCK,


	HDL_QUITFLOCK_HASOUT,
	HDL_QUITFLOCK_ISOWNER,

	HDL_DRAGFLOCK_NORIGHT,
	HDL_DRAGFLOCK_HASMEMBER, 
	HDL_DRAGFLOCK_FLOCKISFULL,
	HDL_DRAGFLOCK_TOOMANYFLOCK,

	HDL_PUSHFLOCK_OWNNOTIN,
	HDL_PUSHFLOCK_OPPNOTIN,
	HDL_PUSHFLOCK_NORIGHT,
	
	HDL_ACCEPTFLOCK_NORIGHT,
	HDL_ACCEPTFLOCK_OWNNOTIN,
	HDL_ACCEPTFLOCK_TOOMANYMEMBER,
	HDL_ACCEPTFLOCK_TOOMANYFLOCK,

	HDL_INVALID_UIN,
	HDL_LOGIN_LOCKED,

	HDL_HUAZHANG_IN_GAME,
	HDL_HUAZHANG_OPP_IN_GAME,

	HDL_LOGIN_NEEDNEWVCODE,
	HDL_LOGIN_NEEDOLDVCODE,
	HDL_LOGIN_INVALIDVCODE,
	HDL_WRONG_VCODE,
	HDL_WRONG_VCODE_OVERTIME,

	HDL_USEGIFT_INGAME,
	HDL_USEGIFT_OPPINGAME,
	HDL_USEGIFT_NOENOUGHMONEY,													//钱不够

	HDL_JOINFLOCK2_HASIN,		
	HDL_JOINFLOCK2_TOOMANYFLOCK,
	HDL_JOINFLOCK2_TOOMANYMEMBER,
	HDL_JOINFLOCK2_REQAUTH,
	HDL_JOINFLOCK2_REFUSE,
	HDL_JOINFLOCK2_NEEDPAY,
	HDL_JOINFLOCK2_INGAME,
	HDL_JOINFLOCK2_NOENOUGHMONEY,

	HDL_QUITFLOCK2_HASOUT,
	HDL_QUITFLOCK2_ISOWNER,

	HDL_PUSHFLOCK2_OPPISSUPERMGR,								//对方是超管
	HDL_PUSHFLOCK2_ISNOTOWNER,									//非室主	
	HDL_PUSHFLOCK2_OPPISOWNER,									//对方是室主	
	HDL_PUSHFLOCK2_OPPHASOUT,									//对方已经不在群
	HDL_PUSHFLOCK2_NORIGHT,										//无权
	HDL_PUSHFLOCK2_INCHARGEROOM,								//收费房间不能踢人

	HDL_HUAZHANG_NOTENOUTHMONEY,								//划账余额不足

	HDL_ADDFRIEND_HASADD,										//加好友-已加
	HDL_ADDFRIEND_TOOMANYFRIEND,								//加好友-我的好友太多
	HDL_ADDFRIEND_OPP_TOOADDMYFRIEND,							//加好友-太多加我好友
	HDL_ADDFRIEND_REFUSE,										//加好友-拒绝加为好友
	HDL_ADDFRIEND_NEEDAUTH,										//加好友-需要认证	
	
	HDL_ACCEPTADDFRIEND_OPP_HASADD,								//允许加好友-已经是对方好友了
	HDL_ACCEPTADDFRIEND_OPP_TOOMANYFRIEND,						//允许加好友-对方有太多好友了
	HDL_ACCEPTADDFRIEND_TOOADDMYFRIEND,							//允许加好友-我已经被太多好友加过了
	HDL_ACCEPTADDFRIEND_OPP_INVALIDREQ,							//允许加好友-对方的请求已经过期或不存在

	HDL_ADDGROUP_TOOGROUP,										//加了太多分组
	HDL_UPDATECONTACT_NONEW,									//更新联系人,没有更新的消息
	HDL_OTHER_DEVICE_LOGIN,						//在其他设备登录（针对移动端）
	HDL_ERROR_USER_LAST_SCAN,					//最后一次是扫描登录
	HDL_ERROR_USER_LAST_ACCREDIT,						//最后一次是授权登录
};

class DBCacheInfo {
public:
	uint32			commtimeout;
	uint32			kpalivetimeout;
	string			host;
	uint16			port;
	uint32			connid;
	string			passwd;
	uint16			connnum;	

	bool operator == (const DBCacheInfo &u)
	{
		return (commtimeout == u.commtimeout && kpalivetimeout == u.kpalivetimeout && 
			host == u.host && port == u.port && connid == u.connid && passwd == u.passwd &&
			connnum == u.connnum);
	}

	bool operator != (const DBCacheInfo &u)
	{
		return (commtimeout != u.commtimeout || kpalivetimeout != u.kpalivetimeout || 
			host != u.host || port != u.port || connid != u.connid || passwd != u.passwd ||
			connnum != u.connnum);
	}
	void operator = (const DBCacheInfo &u)
	{
		commtimeout = u.commtimeout;
		kpalivetimeout = u.kpalivetimeout ; 
		host = u.host;
		port = u.port;
		connid = u.connid;
		passwd = u.passwd;
		connnum = u.connnum;
	}

	void LoadSetting(WingUtil::CXmlConfig &xml)
	{
		xml.ResetPos();

		if (!xml.FindElem("cache"))
			return;

		host = xml.ReadString( "host" );
		port = xml.Readuint16( "port" );
		connnum = xml.Readuint16( "connnum", 10 );

		connid = xml.ReadInt( "connid", 10000);
		passwd = xml.ReadString( "passwd", "123456" );
		commtimeout = xml.ReadInt( "commtimeout", 120 );
		kpalivetimeout = xml.ReadInt( "kpalivetimeout", 20 );
	}

	void DisplaySetting(void)
	{
		LOG(4)("\n");
		LOG(4)("Cache server = %s:%d\n", host.c_str(), port);
		LOG(4)("Cache connect id = %d, password = %s\n", connid, passwd.c_str());
		LOG(4)("Cache connections num = %d\n", connnum);
		LOG(4)("Cache connect timeout = %d\n", commtimeout);
		LOG(4)("Cache keepalive timeout = %d\n", kpalivetimeout);
	}
};


#endif
