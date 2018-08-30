#ifndef INC_KAFKALOG_H
#define INC_KAFKALOG_H
#include "../tools/kafkaProducter.h"
#include "include/icqtypes.h"
#include "room/RoomCmdDef.h"


#define TOP_TEXT_CHAT		"TEXT"
#define TOP_LOGIN			"LOGIN"
#define TOP_LOGOUT			"LOGOUT"
#define TOP_PPCBET			"PPCBET"		//ppc下注
#define TOP_PPCBANKERREQ	"BANKER_REQ"	//ppc庄家操作
#define TOP_PPCBETLIST		"PPC_BETLIST"	//ppc单个玩家下注列表
#define TOP_PPC_OPENITEM	"PPC_OPENITEM"	//ppc开奖结果
#define TOP_PPC_WINLIMIT	"PPC_WINLIMIT"	//ppc输赢控制

class CTLKafkalog:public CTLKafkaClient
{
public:
	CTLKafkalog(CTLKafaProducter* producer, uint32 _pid, uint32 _serverid);
	~CTLKafkalog();

	//聊天数据
	void AddChatText(uint32 roomid, uint32 srcuin, uint32 dstuin, uint32 msgType, const char* msg,uint32 aRound);
	
	//登录数据
	void AddLogin(uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound);

	//登出数据
	void AddLoginOut(uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound);

	//玩家下注操作(只记录押注失败)
	void AddPPCBet(uint32 roomid, uint32 uin,const char* nick,uint32 aRound, uint32 betMoney,uint8 areaIndex,int errorCode = 0);
	
	//玩家庄家操作
	void AddPPCBankerAction(uint32 roomid, uint32 uin,const char* nick,uint8 action,uint32 aRound,uint8 result = 0);

	//玩家下注列表(总下注uin=10000)
	void AddUserBetList(uint32 roomid, uint32 uin,uint32 aRound,int64 ferrari=0, int64 benz=0, int64 lamborghini=0,int64 bwm=0
		,int64 maserati=0,int64 audi=0,int64 porsche=0,int64 daz=0);

	//系统庄家开奖结果计算@openType:开奖计算方式函数
	void AddOpenItemCalculate(uint32 roomid,uint32 aRound,uint32 winItem,const char* openType,uint32 maxUin,int64 sysbalance,int64 betCount,int64 wantprofit,
		int64 jetCount,int64 currRoundBalance);

	//mac输赢限制记录
	void AddWinLimit(uint32 roomid,uint32 aRound,uint32 uin,const char* mac,int64 win);
	//游戏结束记录
	void AddGameEndInfo(uint32 roomid,uint32 aRound,uint32 winItem,int64 bankerWin, uint32 userUin, int64 userWin);

private:
	inline Json::Value* BuildServerInfo(const char* moudle,uint32 aRound);

private:
	uint32				pid;
	uint32				serverid;
	
};



#endif
