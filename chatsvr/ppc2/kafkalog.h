#ifndef INC_KAFKALOG_H
#define INC_KAFKALOG_H
#include "../tools/kafkaProducter.h"
#include "include/icqtypes.h"
#include "room/RoomCmdDef.h"


#define TOP_TEXT_CHAT		"TEXT"
#define TOP_LOGIN			"LOGIN"
#define TOP_LOGOUT			"LOGOUT"
#define TOP_PPCBET			"PPCBET"		//ppc��ע
#define TOP_PPCBANKERREQ	"BANKER_REQ"	//ppcׯ�Ҳ���
#define TOP_PPCBETLIST		"PPC_BETLIST"	//ppc���������ע�б�
#define TOP_PPC_OPENITEM	"PPC_OPENITEM"	//ppc�������
#define TOP_PPC_WINLIMIT	"PPC_WINLIMIT"	//ppc��Ӯ����

class CTLKafkalog:public CTLKafkaClient
{
public:
	CTLKafkalog(CTLKafaProducter* producer, uint32 _pid, uint32 _serverid);
	~CTLKafkalog();

	//��������
	void AddChatText(uint32 roomid, uint32 srcuin, uint32 dstuin, uint32 msgType, const char* msg,uint32 aRound);
	
	//��¼����
	void AddLogin(uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound);

	//�ǳ�����
	void AddLoginOut(uint32 roomid, uint32 uin, uint16 ver, const char* ip, uint32 port, const char* proxyIp, uint32 proxyPort, const char* mac, uint32 startTime, uint32 endTime,uint32 aRound);

	//�����ע����(ֻ��¼Ѻעʧ��)
	void AddPPCBet(uint32 roomid, uint32 uin,const char* nick,uint32 aRound, uint32 betMoney,uint8 areaIndex,int errorCode = 0);
	
	//���ׯ�Ҳ���
	void AddPPCBankerAction(uint32 roomid, uint32 uin,const char* nick,uint8 action,uint32 aRound,uint8 result = 0);

	//�����ע�б�(����עuin=10000)
	void AddUserBetList(uint32 roomid, uint32 uin,uint32 aRound,int64 ferrari=0, int64 benz=0, int64 lamborghini=0,int64 bwm=0
		,int64 maserati=0,int64 audi=0,int64 porsche=0,int64 daz=0);

	//ϵͳׯ�ҿ����������@openType:�������㷽ʽ����
	void AddOpenItemCalculate(uint32 roomid,uint32 aRound,uint32 winItem,const char* openType,uint32 maxUin,int64 sysbalance,int64 betCount,int64 wantprofit,
		int64 jetCount,int64 currRoundBalance);

	//mac��Ӯ���Ƽ�¼
	void AddWinLimit(uint32 roomid,uint32 aRound,uint32 uin,const char* mac,int64 win);
	//��Ϸ������¼
	void AddGameEndInfo(uint32 roomid,uint32 aRound,uint32 winItem,int64 bankerWin, uint32 userUin, int64 userWin);

private:
	inline Json::Value* BuildServerInfo(const char* moudle,uint32 aRound);

private:
	uint32				pid;
	uint32				serverid;
	
};



#endif
