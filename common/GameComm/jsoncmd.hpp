#ifndef INC_JSONCMD_H
#define INC_JSONCMD_H

#include "json/json.h"
#include <string>
#include "include/uniudppacket.h"
#include "mobiledef.h"


void GetStringValue(string & strValue, const unsigned int nValue);
void GetStringValue(string & strValue, const unsigned long long llValue);
void GetStringValue(string & strValue, const unsigned long lValue);
void GetStringValue(string & strValue, const int iValue);
unsigned long long StringToUll(const char *strValue, short flag);


class CTLCmdReply
{
public:
	std::string operator()(InPacketEx &in, uint32 cmd)  
	{  
		uint16 result;

		in >> result;

		Json::Value jsValue;
		jsValue[JSKEY_CMD] = Json::Value(cmd);
		jsValue[JSKEY_RESULT] = Json::Value(result);

		return jsValue.toStyledString();
	} 
	
};



//发送命令结果回调
class CTLSendResult
{
public:
	std::string operator()(OutPacketEx &out, MB_CHAT_ERROR_CODE result)  
	{  
		Json::Value jsValue;
		jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_T_CMD_SENDTIMEOUT);
		jsValue[JSKEY_SUBCMD] = Json::Value(out.cmd);
		jsValue[JSKEY_PACKETID] = Json::Value(out.packetid);
		jsValue[JSKEY_RESULT] = Json::Value(result);
		jsValue[JSKEY_SEQ] = Json::Value(out.seq);
		jsValue[JSKEY_TIMES] = Json::Value(out.attempts);
		std::string str = jsValue.toStyledString();
		if (0 == result)
		{
			LOG(2)("%s : %s\n", __FUNCTION__, str.c_str());
		}
		else
		{
			LOG(0)("%s : %s ERRO\n", __FUNCTION__, str.c_str());
		}
		return str;
	}  
};




// /class CTLUserClearStamp
// {
// public:
// 	std::string operator()(InPacketEx &in, uint32 uin)  
// 	{  
// 		Json::Value jsValue;
// 		Json::Value	jsList;
// 		jsValue[JSKEY_CMD] = Json::Value(IM_CHAT_SRV_ERASESTAMP);
// 
// 		uint32 srcuin = 0;
// 		in >> srcuin;
// 		
// 		
// 		if (srcuin == uin)
// 		{
// 			uint64 money = 0;
// 			string strTemp;
// 			in >> money;
// 			GetStringValue(strTemp, money);
// 			jsValue[JSKEY_MONEY] = Json::Value(strTemp);
// 		}
// 		jsValue[JSKEY_SRCUIN] = Json::Value(srcuin);
// 
// 
// 		return jsValue.toStyledString();
// 	}  
// };



// class CTLForceOffLine
// {
// public:
// 	std::string operator()(InPacketEx &in)  
// 	{  
// 		Json::Value jsValue;
// 		uint32 newip;
// 		uint16 port;
// 		uint8 nState;
// 		uint8 devType;
// 		uint32 roomid;
// 		in >> newip >> port >>nState >> devType >> roomid;
// 		jsValue[JSKEY_CMD] = Json::Value(IM_CHAT_SRV_FORCE_OFFLINE);
// 		jsValue[JSKEY_IP] = Json::Value(newip);
// 		jsValue[JSKEY_PORT] = Json::Value(port);
// 		jsValue[JSKEY_DEVTYPE] = Json::Value(devType);
// 		jsValue[JSKEY_ROOMID]	= Json::Value(roomid);
// 		
// 		return jsValue.toStyledString();
// 	}  
// 
// };

// class CTLOffLine
// {
// public:
// 	std::string operator()(InPacketEx &in)  
// 	{  
// 		Json::Value jsValue;
// 		uint32 uin;
// 
// 		in >> uin;
// 		jsValue[JSKEY_CMD] = Json::Value(IM_CHAT_SRV_USER_OFFLINE);
// 		jsValue[JSKEY_UIN] = Json::Value(uin);
// 
// 
// 		return jsValue.toStyledString();
// 	}  
// 
// };




// class CTLKeepAlive
// {
// public:
// 	std::string operator()(InPacketEx &in)  
// 	{  
// 		Json::Value jsValue;
// 
// 		uint16 currUserInRoom;				//当前房间在线
// 		uint8	micCount;						//当前麦数
// 		in >> currUserInRoom >> micCount;
// 
// 		MicAVStatus avStatus[MAX_MIC_USER_NUM] = {0};
// 
// 		for (uint8 i=0; i<micCount; i++)
// 		{
// 			in >> avStatus[i].value;
// 
// 		}
// 
// 		uint32 giftver = 0;
// 		uint32 stampver = 0;
// 		uint32 sortVer = 0;
// 		uint32 broadCasePrice = 0;
// 		uint16 discount = 100;
// 		in >> giftver >> stampver >> sortVer >> broadCasePrice >> discount;
// 
// 		jsValue[JSKEY_CMD] = Json::Value(IM_CHAT_KEEP_ALIVE);
// 		jsValue[JSKEY_GIFTVER] = Json::Value(giftver);
// 		jsValue[JSKEY_STAMPVER] = Json::Value(stampver);
// 		jsValue[JSKEY_SORTVER] = Json::Value(sortVer);
// 		jsValue[JSKEY_BROADCASEPRICE] = Json::Value(broadCasePrice);
// 		jsValue[JSKEY_DISCOUNT] = Json::Value(discount);
// 		
// 
// 		return jsValue.toStyledString();
// 	} 
// };








void GetStringValue(string & strValue, const unsigned int nValue)
{
	char buf[64];
	snprintf(buf, sizeof(buf)-1, "%u", nValue);
	strValue = buf;
}

void GetStringValue(string & strValue, const unsigned long long llValue)
{
	char buf[64];
	snprintf(buf, sizeof(buf)-1, "%llu", llValue);
	strValue = buf;
}

void GetStringValue(string & strValue, const unsigned long lValue)
{
	char buf[64];
	snprintf(buf, sizeof(buf)-1, "%lu", lValue);
	strValue = buf;
}

void GetStringValue(string & strValue, const int iValue)
{
	char buf[64];
	snprintf(buf, sizeof(buf)-1, "%u", iValue);
	strValue = buf;
}

unsigned long long StringToUll(const char *strValue, short flag)
{
#ifdef WIN32
	return std::stoull(strValue, NULL, flag);
#else
	return strtoull(strValue, NULL, flag);
#endif
}



#endif
