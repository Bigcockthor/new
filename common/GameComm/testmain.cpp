// mobileChatComm.cpp : 定义控制台应用程序的入口点。
//

#include "CocGameComm.h"
#include <stdlib.h>
#include "include/socketaddress.h"
#include "include/Markup.h"
// 
//#define IP		"192.168.20.221"
//#define IP		"192.168.20.77"
#define IP		"122.225.102.28"
//#define IP		"122.225.102.28"
#define PORT	8800
#define ROOMID	8800
#define UIN		80088


#define MACADR	"14496051001816968839"

#define PASS	"123456"
//#define PASS	"66994853"
#include "include/icqsocket.h"
#include "room/RoomCmdDef.h"
#include "include/md5class.h"

CTLMoblieSocket* g_client =NULL;
void TestLogin(CTLMoblieSocket* moblieSocket)
{
	
	string str = CMD5::MD5(PASS);
	//string mac = CMD5::MD5(MACADR);
	//moblieSocket.SendLogonRoom(100000, ROOMID, str.c_str(), "", 56456474 );


	Json::Value jsval;

	jsval[JSKEY_CMD] = Json::Value(CocCmdType::COC_USER_LOGIN);
	jsval[JSKEY_UIN] = Json::Value(UIN);
	jsval[JSKEY_ROOMID] = Json::Value(ROOMID);
	jsval[JSKEY_PASS] = Json::Value(str);
	jsval[JSKEY_MACADDR] = Json::Value(MACADR);//为uin64为的数据 用字符形式传入
	jsval[JSKEY_DEVTYPE] = Json::Value(chat_user_ios);
	jsval[JSKEY_DEVNUM] = Json::Value("0e68b175280869028083c32df238e18bf06d4f66");
	jsval[JSKEY_PACKETID] = Json::Value("1000");
	jsval[JSKEY_BINDLOGIN] = Json::Value(0);
	jsval[JSKEY_PASSTYPE] = Json::Value(0);	
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());

	///////////////////////ok
}
void testLogOut(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsval;
	jsval[JSKEY_CMD] = Json::Value(CocCmdType::COC_USER_LOGOUT);
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());

	///////////////////////ok
}


void testLoginOut(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsval;
	jsval[JSKEY_CMD] = Json::Value(IM_CHAT_LOGOUT_ROOM);
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());

	///////////////////////ok
}

void testSendGetUserMap(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsValue;
	Json::FastWriter testwirter;
	uint16 cmd = CocCmdType::COC_GET_USER_MAP_DATA;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PID] = Json::Value(17);
	jsValue[JSKEY_UIN] = Json::Value(UIN);
	//jsValue[JSKEY_MAP_INDEX]	= Json::Value(0);
	std::string strRet = testwirter.write(jsValue);
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetUserCmd(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsValue;
	Json::FastWriter testwirter;
	char buf[8] = {0};
	gets(buf);
	static uint16 cmd = CocCmdType::COC_GET_USER_MAP_DATA;
	uint16 num = atoi(buf);
	if (num > 0)
	{
		cmd = num;
	}
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_PID] = Json::Value(13);
	jsValue[JSKEY_UIN] = Json::Value(UIN);
	//jsValue[JSKEY_MAP_INDEX]	= Json::Value(0);
	std::string strRet = testwirter.write(jsValue);
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}

void testSendCreateBuilding(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	static uint8 i = 0;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_BUILD);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(num);
// 	jsValue[JSKEY_X_POS] = Json::Value(17);
// 	jsValue[JSKEY_Y_POS] = Json::Value(17);
	jsValue[JSKEY_X_POS] = Json::Value(30 + i*4);
	jsValue[JSKEY_Y_POS] = Json::Value(30);
	jsValue[JSKEY_USE_RES_TYPE] = Json::Value(1);
	i ++;
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendUpDateBuilding(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_UPDATE_LEVEL);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(19);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(1);
	jsValue[JSKEY_CHECK_SUCC] = Json::Value(0);
	jsValue[JSKEY_USE_RES_TYPE] = Json::Value(0);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCollect(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_RESOURCE_COLLECT);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(23);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(0);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCompletedImmediately(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_COMPLETEDIMMEDIATELY);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(num);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(0);
	jsValue[JSKEY_COMPLETE_TYPE] = Json::Value(Immediately::COC_LAB);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendMoveBuilding(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	static uint8 xpos = 15;
	static uint8 ypos = 19;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_MOVE);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(10);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(0);
	jsValue[JSKEY_X_POS] = Json::Value(xpos);
	jsValue[JSKEY_Y_POS] = Json::Value(ypos);
	jsValue[JSKEY_MODEL] = Json::Value(0);
	jsValue[JSKEY_MAP_INDEX] = Json::Value(0);
	//jsValue[JSKEY_PACKETID] = Json::Value("10000");
	std::string strRet = testWriter.write(jsValue);
	xpos ++;
	ypos ++;
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}

void testSendRemoveBuilding(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_SCENE_REMOVE);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(num);
	jsValue[JSKEY_BUILD_NUM] = Json::Value(0);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}

void testSendTrainSoldier(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_TRAIN_SOLDIER);
	jsValue[JSKEY_TRAINING_CAMP_INDEX] = Json::Value(0);
	jsValue[JSKEY_SOLDIER_TYPE] = Json::Value(101);
	jsValue[JSKEY_SOLDIER_NUM]	= Json::Value(10);
	jsValue[JSKEY_USE_RES_TYPE]	= Json::Value(0);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendUpdateTrainSoldier(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_UPDATE_SOLDIER_LEVEL);
	jsValue[JSKEY_SOLDIER_TYPE] = Json::Value(101);
	jsValue[JSKEY_TRAINING_CAMP_INDEX] = Json::Value(0);
	jsValue[JSKEY_USE_RES_TYPE] = Json::Value(1);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCancelTrainSoldier(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_CANCEL_TRAIN_SOLDIER);
	jsValue[JSKEY_TRAINING_CAMP_INDEX] = Json::Value(num);
	jsValue[JSKEY_SOLDIER_TYPE] = Json::Value(101);
	jsValue[JSKEY_SOLDIER_NUM]	= Json::Value(5);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendApplyToGetAchievement(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_ACHIEVEMENT_APPLY);
	jsValue[JSKEY_ACHIEVEMENT_ID] = Json::Value(101);
	jsValue[JSKEY_ACHIEVEMENT_LEVEL] = Json::Value(1);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendApplyToGetMailPrize(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_MAIL_PRIZE_APPLY);
	jsValue[JSKEY_MAIL_ID] = Json::Value(14);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendDeleteMailMsg(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_DELETE_MAILMSG_LIST);
	jsValue[JSKEY_MAIL_ID] = Json::Value(9527);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetTollGateMap(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_TOLLGATE_MAP);
	jsValue[JSKEY_GATE_INDEX] = Json::Value(1);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetTollGateHistory(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_TOLLGATE_lIST);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendMachingUser(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_MACHING_USER);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//指定账号匹配
void testSendMachingUserWithId(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_MACHING_USER_WITH_ID);
	jsVal[JSKEY_DEFEND_UIN] = Json::Value(88888);
	jsVal[JSKEY_DEFEND_PID] = Json::Value(17);
	jsVal[JSKEY_DEFEND_GAMEID] = Json::Value(0);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGameChallenge(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GAME_CHALLENGE);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCancelMaching(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_CANCEL_MACHING);
	jsValue[JSKEY_DSTPID] = Json::Value(13);
	jsValue[JSKEY_DSTUIN] = Json::Value(30009079);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendProduceMagic(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsval;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	static uint8 i = 0;
	jsval[JSKEY_CMD] = Json::Value(CocCmdType::COC_PRODUCE_MAGIC);
	jsval[JSKEY_SOLDIER_TYPE] = Json::Value(num);
	jsval[JSKEY_SOLDIER_NUM]	= Json::Value(1);
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendSpeedUp(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsval;
	jsval[JSKEY_CMD] = Json::Value(CocCmdType::COC_SPEED_UP);
	jsval[JSKEY_NUM] = Json::Value(2);
	Json::Value jsSpeed;
	jsSpeed[JSKEY_BUILD_TYPE] = Json::Value(23);
	jsSpeed[JSKEY_BUILD_NUM] = Json::Value(0);
	jsval[JSKEY_SPEED_UP_KEY].append(jsSpeed);
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCanUseSoldierList(CTLMoblieSocket* moblieSocket)
{
	Json::Value jsval;
	jsval[JSKEY_CMD] = Json::Value(CocCmdType::COC_PUSH_SOLDIER_LIST);
	std::string strRet = jsval.toStyledString();
	moblieSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}

void testSendPicketSoldiers(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_PICKET_SOLDIERS);
	jsVal[JSKEY_SOLDIER_ID] = Json::Value(10101);
	jsVal[JSKEY_SOLDIER_GROUP] = Json::Value(SoldierGroup::GROUP_BARRACK);
	jsVal[JSKEY_SOLDIER_NUM] = Json::Value(1);
	jsVal[JSKEY_TIME_OFFSET] = Json::Value(1);
	jsVal[JSKEY_X_POS] = Json::Value(20);
	jsVal[JSKEY_Y_POS] = Json::Value(20);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendWallMutiMove(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	Json::Value jsWall;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_WALL_MUTI_MOVE);
	jsVal[JSKEY_MODEL]= Json::Value(1);
	jsVal[JSKEY_MAP_INDEX] = Json::Value(2);
	for (int i = 0; i < 1; ++i)
	{
		jsWall[JSKEY_BUILD_NUM] = Json::Value(uint8(1));
		jsWall[JSKEY_X_POS] = Json::Value(18);
		jsWall[JSKEY_Y_POS] = Json::Value(18);
		jsVal[JSKEY_BUILD_ARRAY].append(jsWall);
	}	
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
	
}
void testSendWallMutiUpdate(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_WALL_MUTI_UPDATE);
	jsVal[JSKEY_USE_RES_TYPE] = Json::Value(1);
	for (int i = 0; i < 3; ++i)
	{
		jsVal[JSKEY_BUILD_ARRAY].append(uint8(i));
	}	
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendBuyShield(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	Json::Value jsbuild;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_BUY_SHILED);
	jsVal[JSKEY_SHIELD_ID]= Json::Value(2);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendBuyOrnament(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	Json::Value jsbuild;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_BUY_ORNAMENT);
	jsVal[JSKEY_BUILD_TYPE]= Json::Value(41);
	jsVal[JSKEY_USE_RES_TYPE]= Json::Value(0);
	jsVal[JSKEY_X_POS]= Json::Value(30);
	jsVal[JSKEY_Y_POS]= Json::Value(30);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendSellOrnamentd(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_SELL_ORNAMENT);
	jsVal[JSKEY_BUILD_TYPE]= Json::Value(100);
	jsVal[JSKEY_BUILD_NUM]= Json::Value(100);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendMapEdite(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	Json::Value jsbuild;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_MAP_EDITE);
	jsVal[JSKEY_MODEL]= Json::Value(1);
	jsVal[JSKEY_MAP_INDEX] = Json::Value(2);
	for (int i = 0; i < 1; ++i)
	{
		jsbuild[JSKEY_BUILD_TYPE] = Json::Value(uint8(100));
		jsbuild[JSKEY_BUILD_NUM] = Json::Value(uint8(9));
		jsbuild[JSKEY_X_POS] = Json::Value(18);
		jsbuild[JSKEY_Y_POS] = Json::Value(18);
		jsVal[JSKEY_BUILD_ARRAY].append(jsbuild);
	}	
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendMapCopy(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_MAP_COPY);
	jsVal[JSKEY_SRC_MODEL]= Json::Value(0);
	jsVal[JSKEY_SRC_MAP_INDEX] = Json::Value(2);
	jsVal[JSKEY_DST_MODEL]= Json::Value(1);
	jsVal[JSKEY_DST_MAP_INDEX] = Json::Value(0);
	//jsValue[JSKEY_PACKETID] = Json::Value("10000");
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendReportBuild(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_REPORT_BUILD);
	jsVal[JSKEY_BUILD_TYPE] = Json::Value(22);
	jsVal[JSKEY_BUILD_NUM] = Json::Value(0);
	jsVal[JSKEY_TIME_OFFSET] = Json::Value(5);
	//jsVal[JSKEY_PACKETID] = Json::Value(10);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendReportResource(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_REPORT_RESOURCE);
	jsVal[JSKEY_RES_GOLD] = Json::Value(20);
	jsVal[JSKEY_RES_HOLYWARTER] = Json::Value(21);
	jsVal[JSKEY_RES_BLACKWATER] = Json::Value(22);
	jsVal[JSKEY_RES_GOLD_STORE] = Json::Value(23);
	jsVal[JSKEY_RES_HOLYWARTER_STORE] = Json::Value(24);
	jsVal[JSKEY_RES_BLACKWATER_STORE] = Json::Value(25);
	jsVal[JSKEY_TIME_OFFSET] = Json::Value(110);
	//jsVal[JSKEY_PACKETID] = Json::Value(10);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendTerminatAttack(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_TERMINAT_ATTACK);
	jsVal[JSKEY_TIME_OFFSET] = Json::Value(200);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendTerminatTollGate(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_TERMINAT_TOLLGATE);
	jsVal[JSKEY_TIME_OFFSET] = Json::Value(200);
	jsVal[JSKEY_GATE_INDEX] = Json::Value(1);
	jsVal[JSKEY_RES_GOLD] = Json::Value(100);
	jsVal[JSKEY_RES_HOLYWARTER] = Json::Value(100);
	jsVal[JSKEY_RES_BLACKWATER] = Json::Value(0);
	jsVal[JSKEY_WAR_STAR_NUM] = Json::Value(2);
	for (int i = 0; i < 1; ++i)
	{
		uint16 soldierType = 101;
		Json::Value jSoldier;
		jSoldier[JSKEY_SOLDIER_TYPE] = Json::Value(soldierType);
		jSoldier[JSKEY_SOLDIER_NUM] = Json::Value(1);
		jsVal[JSKEY_SOLDIER_LIST].append(jSoldier);
		soldierType ++;
	}
	
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetSoldierRecord(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_SOLDIER_RECORD);
	jsVal[JSKEY_SRCPID] = Json::Value(13);
	jsVal[JSKEY_SRCUIN] = Json::Value(300009070);
	jsVal[JSKEY_DSTPID] = Json::Value(13);
	jsVal[JSKEY_DSTUIN] = Json::Value(10007);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendRecoverTrap(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	Json::Value jsTrap;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_RECOVER_TRAP);
	for (int i = 0; i < 1; ++i)
	{
		jsTrap[JSKEY_BUILD_TYPE] = Json::Value(uint8(100));
		jsTrap[JSKEY_BUILD_NUM] = Json::Value(uint8(9));
		jsVal[JSKEY_BUILD_ARRAY].append(jsTrap);
	}	
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCancelBuilding(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_CANCEL_BUILD);
	jsValue[JSKEY_BUILD_TYPE] = Json::Value(num);
	jsValue[JSKEY_BUILD_NUM]	= Json::Value(0);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGemstonBuyResource(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	char buf[8] = {0};
	gets(buf);
	uint16 num = atoi(buf);
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GEMSTONE_BUY_RESOURCE);
	jsValue[JSKEY_RES_ID] = Json::Value(num);
	jsValue[JSKEY_RES_NUM]	= Json::Value(1000000);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendAttackHistoryMap(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_ATTACK_HISTORY_MAP);
	jsValue[JSKEY_FLAG] = Json::Value(0);
	jsValue[JSKEY_OFFENSE_PID] = Json::Value(13);
	jsValue[JSKEY_OFFENSE_UIN] = Json::Value(1000130);
	jsValue[JSKEY_DEFEND_PID] = Json::Value(0);
	jsValue[JSKEY_DEFEND_UIN] = Json::Value(30000007);
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(1450866985);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
	
}
void testSendChallengeHistoryMap(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_CHALLENGE_ATTACK_INFO);
	jsValue[JSKEY_PID] = Json::Value(17);
	jsValue[JSKEY_UIN] = Json::Value(56789);
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(1450866985);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendCmd(CTLMoblieSocket *mobileSocket, uint16 cmd, uint32 timeInfo)
{
	Json::Value jsValue;
	Json::FastWriter testWriter;
	jsValue[JSKEY_CMD] = Json::Value(cmd);
	jsValue[JSKEY_DEFEND_PID] = Json::Value(17);
	jsValue[JSKEY_DEFEND_UIN] = Json::Value(UIN);
	jsValue[JSKEY_ATTACK_TIME] = Json::Value(timeInfo);
	std::string strRet = testWriter.write(jsValue);
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
	
}
void testSendSetNewUserStep(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_SET_NEW_USER_STEP);
	jsVal[JSKEY_NEW_USER_STEP] = Json::Value(1);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendSetUserName(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_SET_USER_NAME);
	jsVal[JSKEY_USERNICK] = Json::Value("123456");
	//jsVal[JSKEY_PACKETID] = Json::Value(10);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendChangeUserName(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_CHANGE_USER_NAME);
	jsVal[JSKEY_USERNICK] = Json::Value("ABCDEFA");
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetSoldierLevel(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_SOLDIER_LEVEL);
	jsVal[JSKEY_PID] = Json::Value(17);
	jsVal[JSKEY_UIN] = Json::Value(30000682);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//复仇
void testSendUserRevenge(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_USER_REVENGE);
	jsVal[JSKEY_DEFEND_UIN] = Json::Value(1000130);
	jsVal[JSKEY_ATTACK_TIME]= Json::Value(1438248832);
	jsVal[JSKEY_DEFEND_PID] = Json::Value(13);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//获取主动推送数
void testSendGetServerPushList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_SERVER_PUSH_LIST);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//排行榜
void testSendGetRankList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_RANKING_LIST);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//获取用户信息
void testSendGetUserInfo(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_INFO_DATA);
	jsVal[JSKEY_UIN] = Json::Value(1000130);
	jsVal[JSKEY_PID] = Json::Value(13);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetAchivement(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_ACHIEVEMEN);
	jsVal[JSKEY_UIN] = Json::Value(1000130);
	jsVal[JSKEY_PID] = Json::Value(13);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
//查询兑换功能
void testSendSelectPlatformMoney(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_SELECT_PLATFORM_MONEY);
	jsVal[JSKEY_UIN] = Json::Value(UIN);
	jsVal[JSKEY_PID] = Json::Value(17);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendSelectStationMoney(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_SELECT_STATION_MONEY);
	jsVal[JSKEY_UIN] = Json::Value(UIN);
	jsVal[JSKEY_PID] = Json::Value(17);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendPlatformMoneyBuyGemston(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_PLATFORM_MONEY_BUY_GEMSTONE);
	jsVal[JSKEY_UIN] = Json::Value(1000130);
	jsVal[JSKEY_PID] = Json::Value(13);
	jsVal[JSKEY_RES_NUM] = Json::Value(100);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendStationMoneyBuyResource(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_STATION_MONEY_BUY_RESOURCE);
	jsVal[JSKEY_UIN] = Json::Value(1000130);
	jsVal[JSKEY_PID] = Json::Value(13);
	jsVal[JSKEY_RES_ID] = Json::Value(1);
	jsVal[JSKEY_RES_NUM] = Json::Value(1000000);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetShieldCooltimeEndList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_SHIELD_LIST);
	jsVal[JSKEY_UIN] = Json::Value(101900);
	jsVal[JSKEY_PID] = Json::Value(13);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetAttackHistoryist(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_ATTACK_HISTORY_LIST);
	jsVal[JSKEY_UIN] = Json::Value(88888);
	jsVal[JSKEY_PID] = Json::Value(17);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetMailMsgList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_MAILMSG_LIST);
// 	jsVal[JSKEY_UIN] = Json::Value(88888);
// 	jsVal[JSKEY_PID] = Json::Value(17);
	//这里传的时间值是本地保存的邮件列表最近一条的起始时间
	uint32 curr = 0;
	jsVal[JSKEY_START_TIME] = Json::Value(curr);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetSpeedList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_USER_SPPEDUP_INFO);
	// 	jsVal[JSKEY_UIN] = Json::Value(88888);
	// 	jsVal[JSKEY_PID] = Json::Value(17);
	//这里传的时间值是本地保存的邮件列表最近一条的起始时间
	jsVal[JSKEY_PID] = Json::Value(17);
	jsVal[JSKEY_UIN] = Json::Value(UIN);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetOnlinePrizeList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_ONLINEPRIZE_INFO);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetCurrOnlinePrize(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_CURR_ONLINEPRIZE);
	jsVal[JSKEY_PRIZE_ID] = Json::Value(1);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetDayActivityTaskList(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_DAY_ACTIVE_TASK_lIST);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetDayActivityPrize(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_CURR_DAY_ACTIVE_PRIZE);
	jsVal[JSKEY_PRIZE_ID] = Json::Value(1);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}
void testSendGetDayActivityPrizeInfo(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_GET_DAY_ACTIVE_TASK_PRIZE_INFO);
	jsVal[JSKEY_PRIZE_ID] = Json::Value(1);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}


void testWinnerMsg(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_ADD_WINNER_MSG);
	jsVal[JSKEY_GAME_ID] = Json::Value(12345);
	jsVal[JSKEY_MSG] = Json::Value("弄死你不服你打回来啊，不在线一次弄你一次");
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}

//主动请求宝石信息列表
void testGemstoneInfoReq(CTLMoblieSocket *mobileSocket)
{
	Json::Value jsVal;
	jsVal[JSKEY_CMD] = Json::Value(CocCmdType::COC_BUY_GEMSTONE_INFO);
	std::string strRet = jsVal.toStyledString();
	mobileSocket->SendJsonData((void*)strRet.c_str(), strRet.length());
}




void _ONRECV(const char* pData, int nLen)
{
	string str = CMarkup::UTF8ToA(pData);
	Json::Reader read;
	Json::Value val;
	read.parse(pData, pData+nLen, val);
	int cmd = val[JSKEY_CMD].asInt();
	if(cmd == IM_CHAT_LOGON_ROOM)
	{
		
	}
	else if (CocCmdType::COC_GET_CHALLENGE_ATTACK_INFO == cmd)
	{
		g_client->ReConnect();
	}
//  	LOG(4)("ansii %s\n", str.c_str());
//  	LOG(4)("utf8 %s\n", pData);
}


void _ONDISCONNECT(int nState)
{
	g_client->ReConnect();
	Sleep(50000);
}
void _ONCONNECT(int nState)
{
	if(nState ==0)
	{
		TestLogin(g_client);
	}
	else
	{
		LOG(0)("%s erro state:%d\n",__FUNCTION__, nState);
	}
}
void _ONTIMER()
{

}
int main(int argc, char* argv[])
{
	Log::open("mobile", 4, true);
	CoreSocket::SocketStartUp();
	g_client = new CTLMoblieSocket;
	g_client->RegistCallBack(_ONRECV, NULL, _ONCONNECT, _ONDISCONNECT, _ONTIMER);
	if(!g_client->StartUp(IP, PORT))
	{
		return -1;
	}	
	char cmd;
	while(1)
	{
 		cmd = getchar();
// 		if('0' == cmd)
// 		{
// 			g_client->ReConnect(true);
// 			Sleep(10000);
// 		}
		switch(cmd)
		{
		case 'a':
			{
				g_client->StartUp(IP, PORT);
			}
			break;
		case 'b':
			{
				g_client->ShutDown();
			}
			break;
		case 'c':
			{
				g_client->ShutDown();
				g_client->StartUp(IP, PORT);
				//testSendSetUserName(pClient);
				//testSendSetNewUserStep(pClient);
			}
			break;
		case 'd':
			{
				testSendGetUserMap(g_client);
				//testSendBuyOrnament(pClient);
			}
			break;
		case 'e':
			{
				testSendMachingUser(g_client);
			}
			break;
		case 'f':
			{
				testSendMoveBuilding(g_client);
			}
			break;
		case 'g':
			{
				testSendRemoveBuilding(g_client);
			}
			break;
		case 'h':
			{
				testSendUpDateBuilding(g_client);
			}
			break;
		case 'i':
			{
				testSendCollect(g_client);
			}
			break;
		case 'j':
			{
				testSendTrainSoldier(g_client);
			}
			break;
		case 'k':
			{
				testSendCancelTrainSoldier(g_client);
			}
			break;
		case 'l':
			{
				testSendGetTollGateMap(g_client);
				testSendGetTollGateHistory(g_client);
			}
			break;
		case 'm':
			{
				testSendUpdateTrainSoldier(g_client);
			}
			break;
		case 'n':
			{
				testSendCompletedImmediately(g_client);
			}
			break;
		case 'o':
			{
				testSendApplyToGetAchievement(g_client);
			}
			break;
		case 'p':
			{
				testLogOut(g_client);
			}
			break;
		case 'r':
			{
				testSendProduceMagic(g_client);
			}
			break;
		case 's':
			{
				testSendSpeedUp(g_client);
			}
			break;
		case  't':
			{
				testSendCanUseSoldierList(g_client);
			}
			break;
		case 'u':
			{
				testSendWallMutiMove(g_client);
			}
			break;
		case 'v':
			{
				testSendWallMutiUpdate(g_client);
			}
			break;
		case 'w':
			{
				testSendMapEdite(g_client);
				testSendMapCopy(g_client);
			}
			break;
		case 'x':
			{
				testSendReportBuild(g_client);
				testSendReportResource(g_client);
			}
			break;
		case 'y':
			{
				testSendPicketSoldiers(g_client);
			}
			break;
		case 'z':
			{
				testSendGetSoldierRecord(g_client);
			}
			break;
		case 'A':
			{
				testSendRecoverTrap(g_client);
			}
			break;
		case 'B':
			{
				//testSendCancelBuilding(pClient);
				testSendApplyToGetAchievement(g_client);
			}
			break;
		case 'C':
			{
				testSendMachingUser(g_client);
			}
			break;
		case 'D':
			{
				testSendCancelMaching(g_client);
			}
			break;
		case 'E':
			{
				testSendGemstonBuyResource(g_client);
			}
			break;
		case 'F':
			{
				testSendAttackHistoryMap(g_client);
			}
			break;
		case 'G':
			{
				//testSendTerminatAttack(pClient);
				testSendTerminatTollGate(g_client);
			}
		case 'H':
			{
				//testSendTerminatAttack(pClient);
				testSendGetUserCmd(g_client);
			}
		case 'I':
			{
				testSendUserRevenge(g_client);
			}
		case 'J':
			{
				testWinnerMsg(g_client);
//  			testSendSelectPlatformMoney(pClient);
// 				testSendSelectStationMoney(g_client);
// 				testSendPlatformMoneyBuyGemston(pClient);
// 				testSendStationMoneyBuyResource(g_client);
//				testSendGetShieldCooltimeEndList(pClient);
//				testSendBuyShield(pClient);
//				testSendGetShieldCooltimeEndList(pClient);
//				testSendGetAttackHistoryist(g_client);
//				testSendChangeUserName(pClient);
//				testSendGetMailMsgList(pClient);
//				testSendApplyToGetMailPrize(pClient);
//				testSendDeleteMailMsg(pClient);
//				testSendGetSpeedList(pClient);
//				testSendChangeUserName(pClient);
//				LOG(4)("[%s millisecond:%u]\n", __FUNCTION__, talk_base::TimeStamp());
//				testSendGetUserMap(pClient);
//				testSendGetSoldierLevel(pClient);
//				testSendGetOnlinePrizeList(pClient);
//				testSendGetCurrOnlinePrize(pClient);
//				testSendMachingUserWithId(pClient);
//				testSendGameChallenge(pClient);
//				testSendGetDayActivityPrizeInfo(pClient);
//				testSendGetDayActivityTaskList(pClient);
//				testSendGetDayActivityPrize(pClient);
//				testSendChallengeHistoryMap(g_client);
//				testSendCmd(g_client, CocCmdType::COC_GET_ATTACK_HISTORY_MAP, 1452671734);
			}
			break;
		default:
			TestLogin(g_client);
		}
		fflush(stdin);
	}
	CoreSocket::SocketCleanUp();
	return 0;
}
