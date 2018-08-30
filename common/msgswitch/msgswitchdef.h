#pragma once

#include <string>
#include "include/icqtypes.h"
#include "include/Markup.h"
#include "include/xmlconfig.h"
#include "include/log.h"

using namespace std;

enum
{
	MSGSWITCH_CLI_VER = 1
};

enum
{
	MSGSWITCH_CMD_KEEPALIVE = 0x0001,
	MSGSWITCH_CMD_ACK = 0x0002,

	MSGSWITCH_CMD_LOGIN = 0x0003,
	MSGSWITCH_CMD_LOGOUT = 0x0004,

	MSGSWITCH_CMD_SENDMESSAGE = 0x0005,
	MSGSWITCH_CMD_IMCMSG	 = 0x0006,
};

/*请求方发送进来的Type值*/
enum
{
	MSGSWITCH_TYPE_REQ = 0x0001,
	MSGSWITCH_TYPE_RES = 0x0002,
};

enum
{
	MSGSWITCH_HDL_SUCCESS = 0x0001,					//操作成功
	MSGSWITCH_HDL_FAILED,							//操作失败
	MSGSWITCH_HDL_WRONG_PASSWD,
};

enum
{
	MSGSWITCH_LOGON_SUCCESS		= 0x0001,
	MSGSWITCH_LOGON_WRONGPASS = 0x0002,
	MSGSWITCH_LOGON_NOID			= 0x0003,
	MSGSWITCH_LOGON_FAILED			= 0x0004,
};


enum {
	UDP_MAN_ACK					= 0x0000,
	UDP_MAN_CHANGE_PASS			= 0x0001,
	UDP_MAN_CREATE_FLOCK		= 0x0002,
	UDP_MAN_DISBAND_FLOCK		= 0x0003,
	UDP_MAN_ADD_MEMBER			= 0x0004,
	UDP_MAN_DEL_MEMBER			= 0x0005,
	UDP_MAN_NEW_BCMSG			= 0x0006,
	UDP_MAN_FLOCK_LIST			= 0x0007,

	UDP_MAN_TENROOM_KICKOUT		= 0x0019,						//十人房间踢人
	UDP_MAN_NEW_IMBCMSG			= 0x001A,						//IM广播

	UDP_MAN_HDR_ADDMGR          = 0x0020,   					//添加管理员
	UDP_MAN_HDR_DELMGR          = 0x0021,   					//删除管理员
	UDP_MAN_HDR_MODIFYINFO      = 0x0022,   					//修改房间资料
	UDP_MAN_HDR_BLACKLIST       = 0x0023,   					//黑名单
	UDP_MAN_DESTORYROOM			= 0x0024,						//重启房间

	UDP_MAN_ADDBLACKITEM		= 0x0029,						//IM添加黑名单
	UDP_MAN_DELBLACKITEM		= 0x002C,						//IM删除黑名单
	UDP_MAN_FORCEOFFLINE		= 0x0030,

	UDP_MAN_UPDMONEY			= 0x0032,						//重新通知资金
	UDP_MAN_UPDFLOCK			= 0x0033,						//更新房间

	UDP_MAN_ADDSUPERMAN			= 0x0035,						//添加超管
	UDP_MAN_DELSUPERMAN			= 0x0036,						//删除超管

	UDP_MAN_NOTIFYNEWMONEY		= 0x003D,						//通知最新的资金
	UDP_MAN_POPUPMSG			= 0x003E,						//通知最新的弹出消息
	UDP_MAN_USER_CLEAR_CACHE	= 0x003F,						//通知最新用户后台管理权限



	UDP_MAN_IMMESSAGE			= 0x0040,						//Im消息
	UDP_MAN_PARTNER_UPDATE		= 0x0041,						//合作伙伴设置更新
	UDP_MAN_GLOBLE_MSG,											//全局喇叭
	UDP_MAN_GLOBLE_MSG2,										//大礼喇叭
	UDP_MAN_GLOBLE_MSG3,										//全局系统嗽叭
	UDP_MAN_GENERAL_MSG,										//全局系统嗽叭
	UDP_MAN_DISTRIBUTE_REDPAPER,								//分发红包消息
	UDP_MAN_ACQUIRE_REDPAPER,									//获得红包消息
	UDP_MAN_NOTIFY_REDPAPER,									//通知抢红包消息
	UDP_MAN_OUTOFDATE_REDPAPER,									//过期红包消息
	UDP_MAN_NOTIFYFORCEOFFLINE,									//强制下线通知
	UDP_MAN_MODIFYMGRINFO,										//修改管理
	UDP_MAN_FORMAL_OPERATION,									//正式运营通知
	UDP_MAN_SUIBO_FORCE_END,									//随播强制关闭
	UDP_MAN_SUIBO_MSG,											//随播推广消息 //废弃
	UDP_MAN_SUIBO_OWN_MSG,										//随播分享通知主播消息
	UDP_MAN_NOTIFY_MSG,											//推广消息入口
	UDP_MAN_NOTIFY_BLOCK,										//随播封锁通知
	UDP_MAN_PPC_AWARD_MSG,										//车行中奖消息
	UDP_MAN_SUIBO_ROOM_BROADCAST2,                              //随播房间广播，1条或者2条，来自web后台
	UDP_MAN_WEEKSTAR_CHANGE,									//周星变更通知//废弃
	UDP_MAN_DIAMON_UPDATE,										//钻石更新
	UDP_MAN_DIAMONRECV_UPDATE,									//钻石劵更新
	UDP_MAN_ANYCAST_NEW_BROADCAST,								//随播新广播消息
	UDP_MAN_SUIBO_MSG_NEW,										//随播推广消息 废弃
	UDP_MAN_SUIBO_OWN_MSG_NEW,									//随播分享通知主播消息
	UDP_MAN_ANYCAST_ACTIVE_UPDATE,								//活动更新
	UDP_MAN_ANYCAST_LEVEL_CHANGE,								//等级更新通知
	UDP_MAN_ANYCAST_ONFOCUS,									//直播间中关注通知
	UDP_MAN_ANYCAST_ONFOCUS_SHARE,								//分享中带来的关注
	UDP_MAN_ANYCAST_SHARE_VIEWER,								//观众分享推送
	UDP_MAN_ANYCAST_UPDATEVER,									//修改版本号
	UDP_MAN_ANYCAST_SHAREEXP,									//带经验分享
	


	UDP_MAN_MEDIA_CREATEROOM	= 0x0100,						//GTS创建房间
	UDP_MAN_MEDIA_DESTROYROOM	= 0x0101,						//GTS销毁房间
	UDP_MAN_MEDIA_MICLIST		= 0x0102,						//GTS麦克列表
	UDP_MAN_MEDIA_CHECKROOM		= 0x0103,						//GTS检查房间
	UDP_MAN_MEDIA_LOGOUTUSER	= 0x0104,						//Gts用户退出
	UDP_MAN_MEDIA_CHECKROOM2	= 0x0105,						//GTS检查房间

	UDP_MAN_WEB_USER			= 0x0200,						//web用户上下线消息
	UDP_MAN_WEB_CHATTEXT,										//web聊天消息
	UDP_MAN_WEB_VIEWSTATE,										//直播状态


	//coc专用房间不可重复
	UDP_MAN_COC_SYS_MSG = 200,									//游戏系统消息
	UDP_MAN_COC_MAIL_MSG,										//游戏邮件消息
	UDP_MAN_COC_CHALLENG_NOTIFY,								//挑战赛通知
	UDP_MAN_COC_DISCOUNT,										//打折通知
	UDP_MAN_COC_BUY_GEMSTONE,									//购买宝石通知

	UDP_MAN_BIGROOM_UPDATE_ACT		= 0x300,					//权限变更
	UDP_MAN_BIGROOM_UPDATE_PARTNER,								//服务商信息变更
	UDP_MAN_BIGROOM_UPDATE_GIFT,								//礼物信息变动
	UDP_MAN_BIGROOM_UPDATE_DIAMON,								//钻石礼物配置
	UDP_MAN_BIGROOM_UPDATE_BOX,									//开宝箱配置
	UDP_MAN_BIGROOM_UPDATE_REDCONF,								//红包配置
	UDP_MAN_BIGROOM_UPDATE_REDSTATE,							//红包已抢完
	UDP_MAN_BIGROOM_UPDATE_SIEGEGIFT,							//更新攻城礼物信息
	UDP_MAN_BIGROOM_WEEKSTAR_CHANGE,							//周星变动通知
	UDP_MAN_BIGROOM_DAYRANK_UPDATE,								//日排行第一名变动通知

	UDP_MAN_YIYUAN_DUOBAO			= 0x400,					//一元夺宝全站中奖消息
};

struct MsgSwitchInfo
{
public:
	MsgSwitchInfo()
	{
		port = 0;
		conn_id = 0;
		clientSvrID = 0;
		clientpid = 0;
		clientport = 0;
		conn_num = 0;
		keepalive_timeout = 0;
		waitkeepalive_timeout = 0;
		comm_timeout = 0;
		send_timeout = 0;
	}
	string				host;
	uint16				port;
	uint32				conn_id;
	string				conn_passwd;
	uint32				clientSvrID;
	uint16				clientpid;
	string				clienthost;
	uint16				clientport;
	uint32				conn_num;
	uint32				keepalive_timeout;
	uint32				waitkeepalive_timeout;
	uint32				comm_timeout;
	uint32				send_timeout;

	bool operator != (const MsgSwitchInfo &u)
	{
		return (host != u.host || port != u.port || 
			conn_id != u.conn_id || conn_passwd != u.conn_passwd || 
			clientSvrID != u.clientSvrID || clientpid != u.clientpid ||
			clienthost != u.clienthost || clientport != u.clientport ||
			conn_num != u.conn_num || keepalive_timeout != u.keepalive_timeout ||
			waitkeepalive_timeout != u.waitkeepalive_timeout || comm_timeout != u.comm_timeout||
			send_timeout != u.send_timeout);
	}

	void operator = (const MsgSwitchInfo &u)
	{
		host = u.host; port = u.port; 
		conn_id = u.conn_id; conn_passwd = u.conn_passwd; 
		clientSvrID = u.clientSvrID; clientpid = u.clientpid;
		clienthost = u.clienthost; clientport = u.clientport;
		conn_num = u.conn_num; keepalive_timeout = u.keepalive_timeout;
		waitkeepalive_timeout = u.waitkeepalive_timeout; comm_timeout = u.comm_timeout;
		send_timeout = u.send_timeout;
	}

	void LoadSetting(WingUtil::CXmlConfig &xml)
	{
		xml.ResetPos();

		if (!xml.FindElem("msgswitch"))
			return;

		host = xml.ReadString("host");
		port = xml.Readuint16("port", 7000);
		conn_id = xml.ReadInt("connid", 10000);
		conn_passwd = xml.ReadString("passwd", "123456");
		conn_num = xml.ReadInt("connnum", 1);
		clientSvrID = xml.ReadInt("clientsvrid", 0);
		clientpid = xml.Readuint16("clientpid", 400);
		clienthost = xml.ReadString("clienthost", "127.0.0.1");
		clientport = xml.Readuint16("clientport", 9000);
		comm_timeout = xml.ReadInt("commtimeout", 30);
		keepalive_timeout = xml.ReadInt("keepalivetimeout", 15);
		waitkeepalive_timeout = xml.ReadInt("waittimeout", 60);
		
		send_timeout = xml.ReadInt("sendtimeout", 2);
	}

	void DisplaySetting(void)
	{
		LOG(4)("\n");
		LOG(4)("Msg switch server = %s:%d\n", host.c_str(), port);
		LOG(4)("Msg switch connect id = %d, password = %s\n", conn_id, conn_passwd.c_str());
		LOG(4)("Msg switch connections num = %d\n", conn_num);
		LOG(4)("Msg switch connect clientSvrID = %d\n", clientSvrID);
		LOG(4)("Msg switch connect clientpid = %d\n", clientpid);
		LOG(4)("Msg switch client = %s:%d\n", clienthost.c_str(), clientport);
		LOG(4)("Msg switch connect conn_num = %d\n", conn_num);
		LOG(4)("Msg switch connect keepalive_timeout = %d\n", keepalive_timeout);
		LOG(4)("Msg switch connect waitkeepalive_timeout = %d\n", waitkeepalive_timeout);
		LOG(4)("Msg switch connect comm_timeout = %d\n", comm_timeout);
		LOG(4)("Msg switch connect send_timeout = %d\n", send_timeout);



	}

};
