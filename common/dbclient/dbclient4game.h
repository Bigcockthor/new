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




namespace dataport4game {

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

    CLT_ERROR_FAIL = 200,						       //返回结果失败
    CLT_ERROR_PARAM_PARSE,						       //json解析失败  新的接口不再使用
	CLT_ERROR_UNKNOW_ERROR,							   //未知异常
	CLT_ERROR_DATA_INVALID,                             //错误的数据
	CLT_ERROR_DEST_IS_EXIT_BLACKLIST,					//对方已存在
	CLT_ERROR_USER_IS_NOT_ONLINE,						//用户不在线
	CLT_ERROR_OTHER_DEVICE_LOGIN,						//移动用户提示在其他设备登陆
	CTL_ERROR_USER_LAST_SCAN,							// 上次扫描登录
	CTL_ERROR_USER_LAST_ACCREDIT,						// 上次授权登录
	CTL_ERROR_THIRDPARTY_REAUTH,						// 需要重新授权

};

//返回结果类型(resultType)
enum {
	DB_LOGIN = 0x0001,
	DB_QUERY_MONEY,

};

enum DbTimeCount
{
	DB_COUNT_TIME_STAMP = 0,		//!< 时间戳
	DB_COUNT_THREAD,				//!< 线程池队列等待时间
	DB_COUNT_DB_CONNECT,				//!< DB连接时间
	DB_COUNT_DB_PROCESS,			//!< DB处理的时间
	DB_COUNT_GET_RESULT,			//!< 取到处理结果的延时
	DB_COUNT_PROCESS_RESULT,		//处理结果耗时
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
		snprintf(pBuf,  len, "message:%u connSize:%u DbTotal:%u threadQueue:%u DbConnect:%u inDbProcess:%u getDbResult:%u resultProcess:%u All:%u result:%d\n",
			resultType,
			dbStamp[DB_COUNT_CONNECT_SIZE],
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_GET_RESULT], dbStamp[dataport4game::DB_COUNT_TIME_STAMP]), 
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_THREAD], dbStamp[dataport4game::DB_COUNT_TIME_STAMP]), 
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_DB_CONNECT], dbStamp[dataport4game::DB_COUNT_THREAD]) ,
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_DB_PROCESS], dbStamp[dataport4game::DB_COUNT_DB_CONNECT]) ,
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_GET_RESULT], dbStamp[dataport4game::DB_COUNT_DB_PROCESS]),
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_PROCESS_RESULT], dbStamp[dataport4game::DB_COUNT_GET_RESULT]),
			TIME_DIFF_U(dbStamp[dataport4game::DB_COUNT_PROCESS_RESULT], dbStamp[dataport4game::DB_COUNT_TIME_STAMP]),
			errorCode
			);
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
	char nickname[DATAPORT_NICK_LEN+1];
	char onlyNick[DATAPORT_NICK_LEN+1];
	char enter_title[DATAPORT_TITLE_LEN+1];
	char enter_pic[DATAPORT_PIC_LEN+1];
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

class CDBRoomLoginResult:
	public CDBClientResult
{
public:
	RoomUserInfo roomUserInfo;
	CDBRoomBlockCheckNew blockInfo;
	unsigned int forbidStatus;
	unsigned int notalk_time;
	CDBRoomLoginResult()
	{
		memset(&roomUserInfo, 0, sizeof(roomUserInfo));
		forbidStatus = 0;
		notalk_time = 0;
	}
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

   
  
	
//==============coc=====end================//
    
public:
	void HotUpdate(uint8 bKeepConnected);
	 /*
        异步调用返回接口
        result->errorCode结果为0 时成功
    */
    virtual void OnResult (CDBClientResult *result) = 0;
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
