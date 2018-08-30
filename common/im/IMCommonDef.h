#pragma once
#include "include/icqtypes.h"
#include "include/sync.h"
#include <map>
#include <time.h>

using namespace std;

//
//*************������Ҫ�����ݱ��ṹ  BEGIN*********************
//��Ƶ���ݰ���������Ƶ���ݣ�
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

//���ͳ��
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
	IM_MEDIATYPE_UNKNOW = 0,					//δ֪
	IM_MEDIATYPE_AUDIO,							//��Ƶ
	IM_MEDIATYPE_VEDIO,							//��Ƶ
	IM_MEDIATYPE_FILESTREAM,					//�ļ�����


    IM_MEDIATYPE_AUDIO_22KHZ,                 // PC default  audio config
    IM_MEDIATYPE_AUDIO_44KHZ,                 // mobile default audio config
    IM_MEDIATYPE_AUDIO_48KHZ,
    IM_MEDIATYPE_AUDIO_64KHZ,

    IM_MEDIATYPE_CMD,                    // mobile App cmd line
	IM_MEDIATYPE_MAX,							//�������ֵ
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
	uint32 m_nCPUCount; //����������
	unsigned long m_nCurDiskTotal; //��λMB
	unsigned long m_nCurDiskFree;	////��λMB
	unsigned long m_nTotalMeory;	//��λK
	unsigned long m_nFreeMemory;	//��λK
	uint16 m_nXScreen;		//���ص�
	uint16 m_nYScreen;		//���ص�
	string m_osVersion;		//����ϵͳ
	string m_curDir;		//��ǰĿ¼
};

struct USERSELFTYPE
{
	enum USER_SELF_TYPE
	{
		SELF_DEFUALT=0,											//Ĭ��
		SELF_ROOM,												//�������
		SELF_CHANG,												//�û����
		SELF_BUGMONEY,
		SELF_MYBANK,											//����
		SELF_AREAMANAG,											//��������
		WEB_INDEX,												//��ҳ
		SELF_SHOP,												//����;
		SELF_RESETPWD											//�޸�����
	};
};

class WebInfoType
{
public:
	enum TYPE
	{
		URL_BMPINFO=0,//�ȼ�ͼ��
		URL_GIFTDETAIL=1, //�û�������ϸ
		URL_INFORM, //�ٱ�ʱ
	};
};

/*
 *	������, ���ڷ�ֹ����ˢ����,������
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
	const uint16 interval;									//���Ƽ��,��Ϊ��λ
	uint32 maxTimes;									//��ɴ���
	uint32 lastTime;										//�����ͳ��ʱ��
	uint32 countTimes;										//���д���
};

