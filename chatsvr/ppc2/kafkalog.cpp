#include "kafkalog.h"
#include <string.h>
#include <sstream>
#define JSVAL(val, data)  (val)[#data]=Json::Value(data)	


CTLKafkalog::CTLKafkalog( CTLKafaProducter* producer, uint32 _pid, uint32 _serverid)
	:CTLKafkaClient(producer)
{
	pid = _pid;
	serverid = _serverid;
}

CTLKafkalog::~CTLKafkalog()
{

}

Json::Value* CTLKafkalog::BuildServerInfo(const char* moudle,uint32 aRound )
{
	Json::Value *val = new Json::Value;
	JSVAL(*val, pid);
	JSVAL(*val, serverid);
	JSVAL(*val, moudle);
	JSVAL(*val,aRound);
	return val;
}

void CTLKafkalog::AddChatText( uint32 roomid, uint32 srcuin, uint32 dstuin, uint32 msgType, const char* msg,uint32 aRound )
{
	if(!msg)
	{
		return;
	}
	Json::Value *val = BuildServerInfo(TOP_TEXT_CHAT,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, srcuin);
	JSVAL(*val, dstuin);
	JSVAL(*val, msg);
	JSVAL(*val, msgType);
	ProducterMsg(TOP_TEXT_CHAT, val);
}

void CTLKafkalog::AddLogin( uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound )
{
	
	if(!ip || !proxyIp || !mac)
	{
		return;
	}
	Json::Value *val = BuildServerInfo(TOP_LOGIN,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val, ver);
	JSVAL(*val, ip);
	JSVAL(*val, port);
	JSVAL(*val, proxyIp);
	JSVAL(*val, proxyPort);
	JSVAL(*val, mac);
	JSVAL(*val, startTime);
	JSVAL(*val, endTime);
	ProducterMsg(TOP_LOGIN, val);
}

//µÇ³öÊý¾Ý
void CTLKafkalog::AddLoginOut(uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound)
{
	if(!ip || !proxyIp || !mac)
	{
		return;
	}
	Json::Value *val = BuildServerInfo(TOP_LOGOUT,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val, ver);
	JSVAL(*val, ip);
	JSVAL(*val, port);
	JSVAL(*val, proxyIp);
	JSVAL(*val, proxyPort);
	JSVAL(*val, mac);
	JSVAL(*val, startTime);
	JSVAL(*val, endTime);
	ProducterMsg(TOP_LOGOUT, val);
}

void CTLKafkalog::AddPPCBet( uint32 roomid, uint32 uin,const char* nick,uint32 aRound, uint32 betMoney,uint8 areaIndex,int errorCode )
{
	if (!nick)
	{
		return ;
	}
	Json::Value *val = BuildServerInfo(TOP_PPCBET,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val, nick);
	JSVAL(*val, betMoney);
	JSVAL(*val, areaIndex);
	JSVAL(*val,errorCode);
	ProducterMsg(TOP_PPCBET, val);
}

void CTLKafkalog::AddPPCBankerAction( uint32 roomid, uint32 uin,const char* nick,uint8 action,uint32 aRound,uint8 result )
{
	if (!nick)
	{
		return ;
	}
	Json::Value *val = BuildServerInfo(TOP_PPCBANKERREQ,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val, nick);
	JSVAL(*val, action);
	JSVAL(*val, result);
	ProducterMsg(TOP_PPCBANKERREQ, val);
}

void CTLKafkalog::AddUserBetList( uint32 roomid, uint32 uin,uint32 aRound,int64 ferrari/*=0*/, int64 benz/*=0*/, int64 lamborghini/*=0*/,int64 bwm/*=0 */,int64 maserati/*=0*/,int64 audi/*=0*/,int64 porsche/*=0*/,int64 daz/*=0*/ )
{
	Json::Value *val = BuildServerInfo(TOP_PPCBETLIST,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val,aRound);

	char index0[32],index1[32],index2[32],index3[32],index4[32],index5[32],index6[32],index7[32];
#ifdef WIN32	
	sprintf(index0, "%I64d", ferrari);
	sprintf(index1, "%I64d", benz);
	sprintf(index2, "%I64d", lamborghini);
	sprintf(index3, "%I64d", bwm);
	sprintf(index4, "%I64d", maserati);
	sprintf(index5, "%I64d", audi);
	sprintf(index6, "%I64d", porsche);
	sprintf(index7, "%I64d", daz);
#else
	sprintf(index0, "%llu", ferrari);
	sprintf(index1, "%llu", benz);
	sprintf(index2, "%llu", lamborghini);
	sprintf(index3, "%llu", bwm);
	sprintf(index4, "%llu", maserati);
	sprintf(index5, "%llu", audi);
	sprintf(index6, "%llu", porsche);
	sprintf(index7, "%llu", daz);
#endif

	JSVAL(*val, index0);
	JSVAL(*val, index1);
	JSVAL(*val, index2);
	JSVAL(*val, index3);
	JSVAL(*val, index4);
	JSVAL(*val, index5);
	JSVAL(*val, index6);
	JSVAL(*val, index7);
	ProducterMsg(TOP_PPCBETLIST, val);
}

void CTLKafkalog::AddOpenItemCalculate( uint32 roomid,uint32 aRound,uint32 winItem,const char* openType,uint32 maxUin,int64 sysbalance,int64 betCount,int64 wantprofit, int64 jetCount,int64 currRoundBalance )
{
	if (!openType)
	{
		return;
	}
	Json::Value *val = BuildServerInfo(TOP_PPC_OPENITEM,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, winItem);
	JSVAL(*val, openType);
	JSVAL(*val, maxUin);
	std::string sysbalanceStr,betCountStr,wantprofitStr,jetCountStr,currRoundBalanceStr;
	std::stringstream str;
	str << sysbalance;
	str >> sysbalanceStr;
	str.clear();
	str << betCount;
	str >> betCountStr;
	str.clear();
	str << wantprofit;
	str >> wantprofitStr;
	str.clear();
	str << jetCount;
	str >> jetCountStr;
	str.clear();
	str << currRoundBalance;
	str >> currRoundBalanceStr;
 	//_ui64toa_s(sysbalance,sysbalanceStr,);
	JSVAL(*val, sysbalanceStr.c_str());
	JSVAL(*val, betCountStr.c_str());
	JSVAL(*val, wantprofitStr.c_str());
	JSVAL(*val, jetCountStr.c_str());
	JSVAL(*val, currRoundBalanceStr.c_str());
	ProducterMsg(TOP_PPC_OPENITEM, val);
}

void CTLKafkalog::AddWinLimit( uint32 roomid,uint32 aRound,uint32 uin,const char* mac,const int64 win )
{
	if (!mac)
	{
		return;
	}
	Json::Value *val = BuildServerInfo(TOP_PPC_WINLIMIT,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, uin);
	JSVAL(*val, mac);
	std::stringstream str;
	str << win;
	std::string winNum;
	str >> winNum;
	JSVAL(*val, winNum.c_str());
	
	ProducterMsg(TOP_PPC_WINLIMIT, val);
}

void CTLKafkalog::AddGameEndInfo( uint32 roomid,uint32 aRound,uint32 winItem,int64 bankerWin, uint32 userUin, int64 userWin )
{
	Json::Value *val = BuildServerInfo(TOP_PPC_WINLIMIT,aRound);
	JSVAL(*val, roomid);
	JSVAL(*val, winItem);
	//JSVAL(*val, bankUin);
	JSVAL(*val, userUin);
	std::stringstream str;
	std::string bankerWinStr,userWinStr;
	str << bankerWin;
	str >> bankerWinStr;
	str.clear();
	str >> userWin;
	str >> userWinStr;
	JSVAL(*val, bankerWinStr.c_str());
	JSVAL(*val, userWinStr.c_str());

	ProducterMsg(TOP_PPC_WINLIMIT, val);
}


