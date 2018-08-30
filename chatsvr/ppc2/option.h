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

	uint32 servid;												//���������
	uint32 partnerid;											//�̼ңɣĺ�
	uint32 startTime;											//��������ʱ��

	uint8		m_bMonitor;										//��ؿ���
	uint16		m_monitoryInterval;								//�ɼ�ʱ���� ��
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
	uint16		m_bSyncBet;										//����Ѻע����ͬ��Ѻע�ܽ��
	uint8		pauseGame;										//��ͣ��Ϸ
	uint8		m_pPromotedMobile;
	uint8		m_pPromotedPc;
	uint8		m_blink;										//�н���Ϣ�Ƿ������

	//<!--���з���Ѻע-->
	uint16		m_roomBet;

	uint16		m_bankerRoomBet;
		
	//<!--���з����н�-->
	uint16		m_roomAward;

	uint16		m_bankerRoomAward;
		
	//<!--������ׯӯ��-->
	uint16		m_bankerAward;
		
	//<!--����վ��˰��-->
	uint16		m_siteTax;


	//<!--��������˰��-->
	uint16		m_ownerTax;
	
	//<!--�����û�Ѻע-->
	uint16		m_userBet;
		
	//<!--�����û��н�-->
	uint16		m_userAward;

	//  <!--������Ϸ����ˮ-->
	uint16		m_ticketBet;

	//<!--����macѺעͳ��-->
	uint16		m_macBet;
	
	//<!--����mac�н�ͳ��-->
	uint16		m_macAward;

	//<!--�����û���ׯѺע-->
	uint16		m_bankerUserBet;

	//<!--�����û���ׯ����-->
	uint16		m_bankerUserAward;

	uint16		m_bBetNeedTax;

	PPCOption	m_ppcOption;

	////////////////////////////////////////////////////////////////////////
	std::string m_db_ip; //���ݷ���IP��ַ
	std::string m_db_port; //���ݷ���˿ں�
	std::string m_db_passwd; //���ݷ�������
	uint32 m_db_thread_num; //���ݷ����߳���
	std::string m_db_appkey;	//�ж��û���Ȩ��һ���û���Ӧһ��secret
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

	ACE_UINT32 put_queue_time_out;								// �����ݷ�����еĳ�ʱʱ��(����)
	ACE_UINT32 roommanager_high_water_mark;						// ��֤��ѯ���еĻ�������С(KB)
	ACE_UINT32 roommanager_low_water_mark;						// ��֤��ѯ���еĻ�������С(KB)

	ACE_UINT32 login_span;										//��½ʱ����
	ACE_UINT32 login_limit;										//ÿ���½��������



	ACE_UINT32 login_timelimit;									//Ƶ����½���޺����г������ٴε�½�����ʱ����

	DBCacheInfo  dbhCache;
	MsgSwitchInfo switchInfo;
	BeanstalkInfo beanstalkInfo;	
	std::string m_kafkaBroker;		//kafka��־��������
	uint8		m_bkafkaLog;									//�Ƿ���kafkalog
	uint32		m_ppcNewAward;									//���������н���Ϣ�㲥���͵���Щվ����
	uint8		m_notifyMsgType;								//������Ϣ֪ͨ����

	uint32		m_confusionOpen;								//�������أ�0��ʾ�رգ�1��ʾ����
	uint32		m_confusionOpenMacLimit;						//������ʼmac��
	uint32		m_confusionMinRate;								//����������С����
	uint32		m_confusionMaxRate;								//�������������
	uint32		m_confusionCheckTime;							//�������ʱ����
	uint32		m_repeatTimesRate;								//���н�ֹ���������ʣ��磺��ֹ5��������Ϊ20��
	uint32		m_repeatMinTimes;								//���������С��������
	uint32		m_repeatMaxTimes;								//������������������
	uint32		m_kickLimitTimes;								//�������û�������౻�ߴ���
	uint32		m_nobetMaxTimes;								//�������û�����������û��ע�߳�

protected:
	UINMap				m_mapGift;

	void ReadMediaSwitch(WingUtil::CXmlConfig *xml);
	void ReadMediaServer(WingUtil::CXmlConfig *xml);

	void ReadMsg();


private:
	string xmlFile;
};

#endif
