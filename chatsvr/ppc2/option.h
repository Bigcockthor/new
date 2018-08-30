/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2010                         *
 ***************************************************************************/

#ifndef _OPTION_H
#define _OPTION_H

#include "include/icqtypes.h"
#include "ace/SString.h"
#include "ace/Singleton.h"
#include <string>
#include "bigroomdef.h"
#include "msgswitch/msgswitchdef.h"
#include "cache/cachedefine.h"
#include "room/RoomCommon.h"
#include "ppcAward.h"
#include "beanstalkdef.h"

using namespace std;
#define DEFAULT_MAX_MANAGER					10



class Options;

typedef ACE_Singleton<Options,ACE_Null_Mutex> BigRoomOption; 

typedef ACE_Hash_Map_Manager<ACE_UINT32,uint32,ACE_SYNCH_NULL_MUTEX> UINMap;

typedef struct ServerInfo
{
	uint32 serverid;
	uint16 kind;
	enum
	{
		KIND_NORMAL=1,
		KIND_VIP=3,
	};
	ServerInfo()
	{
		serverid = kind = 0;
	}
}ServerInfo;

typedef std::vector<ServerInfo> SvridList;

class Options {
public:
	Options();
	bool ReadConfig(const char *cfgFile);
	bool ReadPPCConfig();
	bool ReadViewConfig(WingUtil::CXmlConfig& xml);

	uint32 servid;												//服务器编号
	uint32 partnerid;											//商家ＩＤ号
	uint32 startTime;											//服务启动时间

	uint8		m_bMonitor;										//监控开关
	uint16		m_monitoryInterval;								//采集时间间隔 秒
	// network
	string		bindIP;
	uint16		bindPort;
	uint16		freePort1;
	uint16		freePort2;
	uint16		m_packetTimeout;
	uint16		m_packetTimes;
	uint8		m_nolock;
	uint64		m_moneyLimit;
	uint8		m_bSyncHist;
	uint16		m_bSyncBet;										//清理押注报文同步押注总金额
	uint8		pauseGame;										//暂停游戏
	uint8		m_pPromotedMobile;
	uint8		m_pPromotedPc;
	uint8		m_blink;										//中奖消息是否带链接

	//<!--车行房间押注-->
	uint16		m_roomBet;

	uint16		m_bankerRoomBet;
		
	//<!--车行房间中奖-->
	uint16		m_roomAward;

	uint16		m_bankerRoomAward;
		
	//<!--车行坐庄盈亏-->
	uint16		m_bankerAward;
		
	//<!--车行站点税收-->
	uint16		m_siteTax;


	//<!--车行室主税收-->
	uint16		m_ownerTax;
	
	//<!--车行用户押注-->
	uint16		m_userBet;
		
	//<!--车行用户中奖-->
	uint16		m_userAward;

	//  <!--车行游戏劵流水-->
	uint16		m_ticketBet;

	//<!--车行mac押注统计-->
	uint16		m_macBet;
	
	//<!--车行mac中奖统计-->
	uint16		m_macAward;

	//<!--车行用户上庄押注-->
	uint16		m_bankerUserBet;

	//<!--车行用户上庄开奖-->
	uint16		m_bankerUserAward;

	uint16		m_bBetNeedTax;

	PPCOption	m_ppcOption;

	////////////////////////////////////////////////////////////////////////
	std::string m_db_ip; //数据服务IP地址
	std::string m_db_port; //数据服务端口号
	std::string m_db_passwd; //数据服务密码
	uint32 m_db_thread_num; //数据服务线程数
	std::string m_db_appkey;	//判断用户的权限一个用户对应一个secret
	//////////////////////////////////////////////////////////////////////////
	uint32		m_maxSendQueue;
	uint32		m_forcectrl;


	MediaServerItem			mSwitcher;		

	MediaSvrList		mediaSvrItems;
	uint16				dxCount;
	uint16				wtCount;
	PpcViewInfo			m_ppcViewInfo;
	uint32		logLevel;
	string		logFile;
	string awardName[22];

	ACE_UINT32 put_queue_time_out;								// 将数据放入队列的超时时间(毫秒)
	ACE_UINT32 roommanager_high_water_mark;						// 认证查询队列的缓冲区大小(KB)
	ACE_UINT32 roommanager_low_water_mark;						// 认证查询队列的缓冲区大小(KB)

	ACE_UINT32 login_span;										//登陆时间间隔
	ACE_UINT32 login_limit;										//每秒登陆次数限制



	ACE_UINT32 login_timelimit;									//频繁登陆后限和盘托出制其再次登陆的最大时间间隔

	DBCacheInfo  dbhCache;
	MsgSwitchInfo switchInfo;
	BeanstalkInfo beanstalkInfo;	
	std::string m_kafkaBroker;		//kafka日志服务配置
	uint8		m_bkafkaLog;									//是否开启kafkalog
	uint32		m_ppcNewAward;									//新碰碰车中奖消息广播发送到哪些站配置
	uint8		m_notifyMsgType;								//奖励消息通知类型

	uint32		m_confusionOpen;								//混淆开关，0表示关闭，1表示开启
	uint32		m_confusionOpenMacLimit;						//混淆开始mac数
	uint32		m_confusionMinRate;								//混淆波动最小倍率
	uint32		m_confusionMaxRate;								//混淆波动最大倍率
	uint32		m_confusionCheckTime;							//混淆检查时间间隔
	uint32		m_repeatTimesRate;								//车行禁止几连开概率（如：禁止5连开设置为20）
	uint32		m_repeatMinTimes;								//车行随机最小连开次数
	uint32		m_repeatMaxTimes;								//车行随机最大连开次数
	uint32		m_kickLimitTimes;								//被限制用户当天最多被踢次数
	uint32		m_nobetMaxTimes;								//被限制用户连续最大局数没下注踢出

protected:
	UINMap				m_mapGift;

	void ReadMediaSwitch(WingUtil::CXmlConfig *xml);
	void ReadMediaServer(WingUtil::CXmlConfig *xml);

	void ReadMsg();


private:
	string xmlFile;
};

#endif
