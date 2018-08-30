#pragma once
#include "include/icqtypes.h"
#include "include/sync.h"
#include <map>
#include <time.h>

using namespace std;

//
//*************单方需要的数据报结构  BEGIN*********************
//音频数据包（包含音频数据）
typedef struct
{
	short flag;
	uint8 session;
	uint8  id;
	unsigned short data_size;	
}AVIO_AUDIO;

class AudioPack
{
public:
	AudioPack() : hdr((AVIO_AUDIO *)m_AudioPack)
	{
		m_id = 0;
		iLen = 114;
		memset(m_AudioPack,0,114);
	}
	const AVIO_AUDIO *hdr;
	uint32    m_id;
	char	m_AudioPack[114];
	uint32	iLen;
//#ifndef _DEBUG
//	DECLARE_SLAB(AudioPack)
//#endif
	
};


#ifndef LoginProxyList
typedef std::map<uint32, uint8> LoginProxyList;
#endif

//埋点统计
#define MAX_RESEND_TIMES  8
#define MAX_TIME_RANGE	6
enum 
{
	NET_SUCESS,
	NET_ERR_CREAT_SOCKET
};
#define MD_API_MAX  4

typedef enum IMMediaType
{
	IM_MEDIATYPE_UNKNOW = 0,					//未知
	IM_MEDIATYPE_AUDIO,							//音频
	IM_MEDIATYPE_VEDIO,							//视频
	IM_MEDIATYPE_FILESTREAM,					//文件传送


    IM_MEDIATYPE_AUDIO_22KHZ,                 // PC default  audio config
    IM_MEDIATYPE_AUDIO_44KHZ,                 // mobile default audio config
    IM_MEDIATYPE_AUDIO_48KHZ,
    IM_MEDIATYPE_AUDIO_64KHZ,

    IM_MEDIATYPE_CMD,                    // mobile App cmd line
	IM_MEDIATYPE_MAX,							//最大类型值
}IMMediaType;




struct IMComputerInfo
{
public:
	IMComputerInfo()
	{
		m_nCurDiskTotal =0;
		m_nCurDiskFree = 0;
		m_nTotalMeory = 0;
		m_nFreeMemory = 0;
		m_nXScreen = 0;
		m_nYScreen = 0;
		m_nCPUCount = -1;
	}
	uint32 m_nCPUCount; //处理器个数
	unsigned long m_nCurDiskTotal; //单位MB
	unsigned long m_nCurDiskFree;	////单位MB
	unsigned long m_nTotalMeory;	//单位K
	unsigned long m_nFreeMemory;	//单位K
	uint16 m_nXScreen;		//像素点
	uint16 m_nYScreen;		//像素点
	string m_osVersion;		//操作系统
	string m_curDir;		//当前目录
};

struct USERSELFTYPE
{
	enum USER_SELF_TYPE
	{
		SELF_DEFUALT=0,											//默认
		SELF_ROOM,												//房间管理
		SELF_CHANG,												//用户礼金
		SELF_BUGMONEY,
		SELF_MYBANK,											//银行
		SELF_AREAMANAG,											//区长管理
		WEB_INDEX,												//首页
		SELF_SHOP,												//购买;
		SELF_RESETPWD											//修改密码
	};
};

class WebInfoType
{
public:
	enum TYPE
	{
		URL_BMPINFO=0,//等级图标
		URL_GIFTDETAIL=1, //用户收礼详细
		URL_INFORM, //举报时
	};
};

/*
 *	计数器, 用于防止快速刷屏用,加人用
 */
class counter
{
public:
	counter(uint16 intervalValue, uint32 maxValue) : interval(intervalValue), maxTimes(maxValue)
	{
		countTimes = lastTime = 0;
	}
	bool count()
	{
		uint32 now = (uint32)time(NULL);
		if (now < lastTime + interval )
		{
			countTimes++;
			if (countTimes >= maxTimes)
				return false;
		}
		else
		{
			countTimes  = 1;
			lastTime = now;
		}

		return true;
	}
	uint32 GetTimes()  const 
	{
		return countTimes;
	}
	void SetTimes(uint32 times){ maxTimes = times;}
private:
	const uint16 interval;									//控制间隔,秒为单位
	uint32 maxTimes;									//许可次数
	uint32 lastTime;										//最近的统计时间
	uint32 countTimes;										//已有次数
};

