/***********************************************************************************************
// 文件名:     beanstalkdef.h
// 创建者:     徐运杰
// Email:      linux_xuyunjie@163.com
// 创建时间:   2014/1/13 13:47:17
// 内容描述:   beanstalk相关数据类型定义
// 版本信息:   1.0V
************************************************************************************************/
#ifndef INC_BEANSTALKDEF_H
#define INC_BEANSTALKDEF_H



#include "msgswitch/beanstalkclient.h"
#include "include/udppacket.h"
#include "room/RoomCommon.h"
using namespace Beanstalk;

#define TUBENAME_FORMAT			"BigRoom%u_%u"

//beanstalk 配置
struct BeanstalkInfo
{
	typedef std::list<std::string> SwatchList;
	typedef SwatchList::iterator   SwatchListIter;
public:
	BeanstalkInfo()
	{
		port = 0;
		conn_timeout = 0;
	}
	string				host;
	uint16				port;
	int				conn_timeout;
	SwatchList			swatchList;
	string				swatchNames;


	bool operator != (const BeanstalkInfo &u)
	{
		return (host != u.host || port != u.port || conn_timeout != u.conn_timeout|| swatchNames != u.swatchNames);
	}

	void operator = (const BeanstalkInfo &u)
	{
		host = u.host; 
		port = u.port;
		conn_timeout = u.conn_timeout;
		swatchNames = swatchNames;
		swatchList.clear();
		swatchList.assign(u.swatchList.begin(), u.swatchList.end());
	}

	void LoadSetting(WingUtil::CXmlConfig &xml,uint32 partnerid, uint32 srvid)
	{
		xml.ResetPos();
		if (!xml.FindElem("beanstalk"))
			return;

		host = xml.ReadString("host");
		port = xml.Readuint16("port", 11300);
		conn_timeout = xml.ReadInt("conntimeout", 0);
		char chDefaultName[64]={0};
		snprintf(chDefaultName, sizeof(chDefaultName)-1, TUBENAME_FORMAT, partnerid, srvid);
		swatchNames = xml.ReadString("swatchlist", chDefaultName);
		string  strSwatchName;
		string  strTemp = swatchNames;
		while(!BeanstanlkdClient::SplitMsg(strTemp, ";", strSwatchName))//此字符串分割函数会改变
		{
			swatchList.push_back(strSwatchName);	
		}
	}

	void DisplaySetting(void)
	{
		LOG(4)("\n");
		LOG(4)("Msg beanstalk server = %s:%d\n", host.c_str(), port);
		LOG(4)("Msg beanstalk connect timeout = %d\n", conn_timeout);
		LOG(4)("Msg beanstalk swatchlist = %s\n", swatchNames.c_str());
	}

};

//beanstalk 全局大礼数据定义
class GreatGiftMsg :public BCMessageBase
{
public:
	GreatGiftMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~GreatGiftMsg(){}
public:
	OutPacket m_out;

};

class GlobalMsg :public BCMessageBase
{
public:
	GlobalMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~GlobalMsg(){}
public:
	UdpInPacket m_in;

};

class GlobalMsgXML :public BCMessageBase
{
	public:
		GlobalMsgXML(uint32 nMsgType):BCMessageBase(nMsgType){}
		virtual ~GlobalMsgXML(){}
	public:
		ChatRoomGlobalMsg m_msgTemp;
};

class RoomInfoMsg:public BCMessageBase
{
public:
	RoomInfoMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~RoomInfoMsg(){}
public:
	int m_nFid;

};

class GameMsg:public BCMessageBase
{
public:
	GameMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~GameMsg(){}
public:
	std::string m_strData;
	uint32	m_nDestRoom;

};


class ForceOfflineMsg:public BCMessageBase
{
public:
	ForceOfflineMsg(uint32 nMsgType):BCMessageBase(nMsgType)
	{
		m_roomid = 0;
		m_uin = 0;
		m_newRoomid = 0;
		m_newip = 0;
		m_newport = 0;
		m_devType = 0;
		m_newMac = 0;
	}
	virtual ~ForceOfflineMsg(){}
public:
	uint32 m_roomid;
	uint32 m_uin;
	uint32 m_newRoomid;
	uint32 m_newip;
	uint32 m_newport;
	uint64 m_newMac;
	uint8  m_devType;
	
};


class ModifyMgrMsg:public BCMessageBase
{
public:
	ModifyMgrMsg(uint32 nMsgType):BCMessageBase(nMsgType)
	{
		m_roomid = 0;
		m_src	 = 0;
		m_dst	 = 0;
		m_action = 0;
	
	}
	virtual ~ModifyMgrMsg(){}
public:
	uint32 m_roomid;
	uint32 m_src;
	uint32 m_dst;
	uint8  m_action;

	

};

class GneralMsg:public BCMessageBase
{
public:
	enum
	{
		MSG_PUBLIC = 0x0001,
		MSG_PRIVATE = 0x0002,
		MSG_SCROLLBROAD = 0x0004,
		MSG_SYSTEMBORAD = 0x0008,

	};
public:
	GneralMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~GneralMsg(){}
	void BuildGneralMsg(int type, const char* pMsg)
	{
		CMarkup xml;
		xml.AddElem("msg");
		xml.AddChildElem("flag", type);
		xml.AddChildElem("content", pMsg);
		xml.AddChildElem("swf");
		m_strMsg = xml.GetDoc();
	}
public:
	std::string m_strMsg;
	uint32	m_nDestRoom;

};


class NewMoneyMsg:public BCMessageBase
{
public:
	NewMoneyMsg(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~NewMoneyMsg(){}
public:
	uint32 srcuin;
	uint32 dstuin;
	uint64 srcMoney;
	uint64 dstMoney;
};
class DistributeRedPaperInfo:public BCMessageBase
{
public:
	DistributeRedPaperInfo(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~DistributeRedPaperInfo(){}
public:
	uint32 uin;
	uint32 money;
	uint32 roomId;
	uint32 redPaperId;
	time_t endTime;
	string msg;
	uint16 num;
};

class NotifyUser:public BCMessageBase
{
public:
	NotifyUser(uint32 nMsgType):BCMessageBase(nMsgType){}
	virtual ~NotifyUser(){}
public:
	uint32 roomId;
	uint32 uin;
};
class BeanstalkMsg;

#endif
