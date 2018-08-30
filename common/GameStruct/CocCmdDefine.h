#ifndef _COC_CMD_DEFINE_H
#define _COC_CMD_DEFINE_H

#ifndef GAME_COMMON
#define GAME_COMMON
#endif

//�ƶ���chatЭ��汾��
enum MB_VER
{
	MB_CHAT_VER1		=	0x016,
	MB_CHAT_VER2,
	MB_CHAT_VER3,
	MB_CHAT_VER4,
	MB_CHAT_VER5,
	MB_CHAT_VER6,
	MB_CHAT_VER7,
	MB_CHAT_VER8,
	MB_CHAT_VER_CURR	=	MB_CHAT_VER8,			
};

class CocCmdType
{
public:
	enum
	{
		//��room�̳�cmd
		COC_KEEP_ALIVE = 1,
		COC_ACK = 2,	
		COC_FORCE_OFFLINE  = 0x0403,		//��ص�¼ǿ������
		//cocר��cmd
		COC_USER_LOGIN = 3000,				//����ǧ��ʼ��Ϊ�˷�ֹ��room cmd�ظ�
		COC_USER_LOGOUT,
		COC_T_CMD_SENDTIMEOUT,				//���ͽ���ص�
		COC_KEEP_ALIVE_GAME,
		COC_ACK_INVOLID,
		COC_SCENE_BUILD,					//����
		COC_SCENE_UPDATE_LEVEL,				//����
		COC_SCENE_MOVE,						//�ƶ�
		COC_SCENE_REMOVE,					//���
		COC_SCENE_RESOURCE_COLLECT,			//�ռ�����Դ��
		COC_SCENE_INFO,						//��ȡ�������������Ϣ��λ�ã��ȼ��ȣ�
		COC_SCENE_CHECK_UPDATE,				//����������
		COC_TRAIN_SOLDIER,					//ѵ��ʿ��
		COC_CANCEL_TRAIN_SOLDIER,			//ȡ������ѵ����ʿ��
		COC_UPDATE_SOLDIER_LEVEL,			//����ʿ��
		COC_FIND_USER_MAP,					//�鿴�����û��ĵ�ͼ
		COC_PUSH_SOLDIER_LIST,				//�·����Գ���ʿ��
		COC_COMPLETEDIMMEDIATELY,			//������ɣ�ʹ�ñ�ʯ��
		COC_ACHIEVEMENT_APPLY,				//�ͻ�����ȡ�ɾͽ���
		COC_PRODUCE_MAGIC,					//��������
		COC_SPEED_UP,						//����
		COC_PICKET_SOLDIERS,				//�ɱ�
		COC_WALL_MUTI_MOVE,					//��ǽ�����ƶ�
		COC_WALL_MUTI_UPDATE,				//��ǽ��������
		COC_BUY_SHILED,						//���򻤶�
		COC_BUY_ORNAMENT,					//����װ��
		COC_SELL_ORNAMENT,					//����װ��
		COC_MAP_COPY,						//��ͼ����
		COC_MAP_EDITE,						//��ͼ�༭
		COC_REPORT_BUILD,					//����ս��
		COC_REPORT_RESOURCE,				//��Դս��
		COC_TERMINAT_ATTACK,				//����ս��
		COC_GET_SOLDIER_RECORD,				//��ȡ�ɱ���¼
		COC_RECOVER_TRAP,					//�޸�����
		COC_CANCEL_BUILD,					//ȡ������ ���� ������
		COC_MACHING_USER,					//��ȡƥ����Ϣ
		COC_SVR_USER_INFO,					//�յ��û���Ϣ
		COC_CANCEL_MACHING,					//ȡ��ƥ����Ϣ
		COC_GET_ATTACK_HISTORY_MAP,			//��ȡ��ʷս����ͼ���طţ�
		COC_CANCEL_MAGIC_PRODUCT,			//ȡ����������
		COC_GEMSTONE_BUY_RESOURCE,			//������Դ

		COC_TERMINAT_TOLLGATE,				//��������

		COC_SET_NEW_USER_STEP,				//���ֽ̳̽��в���
		COC_SET_USER_NAME,					//��������

		//������ýӿ�
		COC_GET_USER_MAP_DATA,				//��ȡ�û���ͼ������Ϣ
		COC_GET_USER_UPDATE_SOLDIER,		//��ȡ�û������� ��ʿ��
		COC_GET_USER_WORKER_LIST,			//��ȡ�û�worker����������Ϣ
		COC_GET_USER_SOLDIER_LEVEL,			//��ȡ�û�ʿ���ȼ���Ϣ
		COC_GET_USER_PRODUCE_LIST,			//��ȡ�û�ʿ����������������Ϣ
		COC_GET_USER_OWN_SOLDIER_LIST,		//��ȡ�û�ӵ�е�ʿ����Ϣ
		COC_GET_USER_ACHIEVEMEN,			//��ȡ�û��ɾ���Ϣ
		COC_GET_USER_SPPEDUP_INFO,			//��ȡ�û�ʹ�ü��ٹ�����Ϣ
		COC_GET_USER_ATTACK_HISTORY_LIST,	//��ȡ�û�ս����ʷ��¼��Ϣ
		COC_GET_USER_DEFEND_ONATTACK_INFO,	//���ط� ��������Ϣ
		COC_GET_USER_TOLLGATE_lIST,			//��ȡ�ؿ���Ϣ��¼
		COC_GET_USER_TOLLGATE_MAP,			//��ȡ�ؿ���ͼ
		COC_GET_USER_INFO_DATA,				//��ȡ�û�������Ϣ
		//�ι�
		COC_GET_USER_MAP_DATA_VISIT,			//��ȡ�û���ͼ������Ϣ
		COC_GET_USER_UPDATE_SOLDIER_VISIT,		//��ȡ�û������� ��ʿ��
		COC_GET_USER_WORKER_LIST_VISIT,			//��ȡ�û�worker����������Ϣ
		COC_GET_USER_SOLDIER_LEVEL_VISIT,		//��ȡ�û�ʿ���ȼ���Ϣ
		COC_GET_USER_PRODUCE_LIST_VISIT,		//��ȡ�û�ʿ����������������Ϣ
		COC_GET_USER_OWN_SOLDIER_LIST_VISIT,	//��ȡ�û�ӵ�е�ʿ����Ϣ
		COC_USER_REVENGE,						//����
		COC_GET_OFFEND_SOLDIER_INFO,			//���ط� ��������Ϣ
		COC_ADD_WINNER_MSG,						//����ʤ������
		COC_BUY_GEMSTONE_INFO,					//�ɹ���ʯ��Ϣ�б�
		COC_CHARE_GEMSTONE,						//��ֵ��ʯ
		COC_FIRST_CHARGE_GEMSTONE,				//�û��׳��������֪ͨ
		COC_FINISH_FIRST_CHARGE,				//��ȡ�׳佱��
		COC_BROTHERHOOD_INFO,					//�ֵܹ�ϵ����
		COC_BROTHERLSIT_INFO,					//�ֵܹ�ϵ�б�
		COC_BROTHER_TASK_REWARD,				//��ȡ�ֵ�������
		COC_BIND_BROTHER,						//���ֵܹ�ϵ
		COC_CLANLIST_INFO,						//��������Ϣ�б�
		COC_CLANINFO,							//�����ҵĲ�����Ϣ
		COC_CLAN_ASKFOR_LIST,					//���������б�
		COC_CLAN_OPERATE,						//������벿�䣬ȡ������
		COC_CLAN_KICK_USER,						//�߳�����
		COC_CLAN_CREATE,						//��������,ɾ������
		COC_CLAN_DELETE,						//ɾ������
		COC_CLAN_MODIFY,						//�޸Ĳ�����Ϣ
		COC_CLAN_SEARCH,						//��������
		COC_CLAN_CHANGE_RANK,					//��������
		COC_CLAN_CONFIRM_REQ,					//��������������
		COC_CLAN_PID_ORDER,						//ȫվ��������
		COC_CLAN_DONATE,						//�������
		COC_CLAN_RECRUIT,						//������ļʿ��
		COC_CLAN_DONATE_INFO,					//�������ʱ�����Ϣ

		COC_CLAN_WARBASTION_INFO,				//��ȡս��������Ϣ
		COC_CLAN_ALLOT,							//����ս��Ʒ
		COC_GET_CLAN_CHALLENGE_ATTACK_INFO,		//����ս���ط�ս����Ϣ







		//�������·���Ϣ
		COC_SERVER_ACHIEVEMENT_COMPLETE = 4000,		//�������·��ɾ����֪ͨ
		COC_SERVER_NOTIFY_MSG,						//�������·�֪ͨ��Ϣ
		COC_SERVER_PUSH_LAST_TOLLGATE,				//�������·��ؿ���Ϣ��¼
		COC_SERVER_USER_ATTACK_HISTORY_LIST,		//�������·��û�ս����ʷ��¼��Ϣ

		//
		COC_CANCEL_REMOVE,					//ȡ���Ƴ�
		COC_REMOVE_SOLDIER,					//ɾ��ʿ��
		COC_GET_SERVER_PUSH_LIST,			//��ȡ����������������
		COC_SEND_MAGIC,						//�ͷŷ���
		COC_GET_RANKING_LIST,				//���а�
		COC_CHECK_VER,						//�汾��У��
		//��ѯ�һ�����
		COC_SELECT_PLATFORM_MONEY,			//��ѯƽ̨��
		COC_SELECT_STATION_MONEY,			//��ѯվ���
		COC_PLATFORM_MONEY_BUY_GEMSTONE,	//ƽ̨����ʯ
		COC_STATION_MONEY_BUY_RESOURCE,		//վ�������Դ
		COC_GET_SHIELD_LIST,				//��ȡ�����б�
		COC_SERVER_MAIL_MSG,				//�����ʼ���Ϣ
		COC_SERVER_SYS_MSG,					//����ϵͳ��Ϣ
		COC_CHANGE_USER_NAME,				//�����û�����
		COC_MAIL_PRIZE_APPLY,				//�ͻ�����ȡϵͳ����
		COC_GET_MAILMSG_LIST,				//��ȡϵͳ�ʼ���Ϣ
		COC_DELETE_MAILMSG_LIST,			//ɾ���ʼ���Ϣ
		COC_GET_ONLINEPRIZE_INFO,			//��ȡ���߽���������Ϣ�Լ���ǰ��ȡ�Ľ���id���µ�����ʱ��
		COC_GET_CURR_ONLINEPRIZE,			//��ȡ��ǰ�����߽���
		COC_MACHING_USER_WITH_ID,			//ָ��ƥ��id
		COC_GET_DAY_ACTIVE_TASK_PRIZE_INFO,	//�ջ����Ϣ����
		COC_GET_DAY_ACTIVE_TASK_lIST,		//��ȡ�ջ���ɶ���Ϣ
		COC_GET_CURR_DAY_ACTIVE_PRIZE,		//��ȡ�ջ��
		COC_PUSH_ORNAMENT_UP_PERCENT,		//����װ��Ʒ���ٱ���
		COC_GAME_CHALLENGE,					//վ����ս��
		COC_REPORT_BUILD_CHALLENGE,			//����ս��
		COC_TERMINAT_CHALLENGE,				//��������
		COC_GET_CHALLENGE_RANKING_LIST,		//վ����ս��
		COC_SERVER_CHALLENGE_DESCRIBE,		//վ����ս��������Ϣ�� ����������ȡ�б�ʱ����
		COC_GET_CHALLENGE_ATTACK_INFO,		//վ����ս��ս����Ϣ
		COC_SVR_CLAN_CHANGED,				//���²�����Ϣ
		COC_SVR_CLAN_JOIN,					//���벿��
		COC_SVR_CLAN_LEAVE,					//�뿪����
		COC_SVR_CLAN_STATEACHE,				//���仺����Ϣ
		COC_SVR_CLANREQ_ADD,				//������벿���б���������
		COC_SVR_CLANREQ_DEL,				//������벿���б�����ɾ��
		COC_SVR_CLAN_UPDATELEVEL,			//����ȼ�����֪ͨ
		COC_SVR_CLAN_MEMLIST,				//���Ͳ����Ա��Ϣ
		COC_SVR_CLAN_CHANGERANK,			//����֪ͨ
		COC_SVR_CLAN_DONATE,				//�������֪ͨ
		COC_SVR_CLAN_DONATE_INFO,			//���������Ϣ����
		COC_SVR_LAST_WINPOINT_RANK,			//������ʤ������
		COC_SVR_CUR_WINPOINT_RANK,			//������ʤ������
		COC_SVR_CLAN_WINPIONT,				//����ʤ������(��Ԥ������)
		COC_SVR_CLAN_AWARD_LIST,			//ս��Ʒ��������
		COC_SVR_CLAN_AWARD_ALLOT,			//ս��Ʒ�ַ���������
		COC_SVR_CLAN_RANKAWARD_MAIL,		//�������������ʼ�
		COC_SVR_CLAN_ATTACK_HISTORY_LIST,	//����ս��ս����ʷ��¼��Ϣ
	};
};

class Immediately
{
public:
	enum
	{
		COC_BUID,
		COC_REMOVE,
		COC_LAB,
		COC_TRAINS,
		COC_MAGIC,
		COC_UPDATE,
	};
};
class ChangeName
{
public:
	enum
	{
		CHANGE_SUCESS,		//�����ɹ�
		CHANGE_MONEY,		//����
		CHANGE_IN_USE,		//�����Ѿ���ʹ��
		CHANGE_EMPTY,		//�յ�����
	};
};
class SoldierGroup
{
public:
	enum
	{
		GROUP_BARRACK,
		GROUP_CASTLE,
	};
};
class GameNotifyCmd
{
public:
	enum
	{
		SUCCESS,							//û�д���
		KICK_OUT,							//��������
		NEED_WAIT,							//��¼δ��ɣ� ��Ҫ�ȴ�
		REVENGE_REPEAT,						//�ظ�����
		REVENGE_ONLINE,						//���߻��߻���״̬
		REVENGE_ONATTACK,					//������״̬
		COCVER_ERRO,						//�汾�Ŵ���
		USER_LOGOUT,						//�˳���¼ 
		EXCHANGE_MONEY_NOT_ENOUGH,			//�һ��ʽ���
		EXCHANGE_DB_ERRO,					//DB���ϣ�������
		SERVER_WAIT,						//����ά����
		NITIFY,								//֪ͨ
		RESOURCE_IS_FULL,					//��Դ�洢����
		STATTION_GOLD_SUCESS,				//վ��Ҳ����ɹ�
		STATTION_GOLD_FAIL,					//վ��Ҳ���ʧ��
		STATTION_GOLD_FAIL_DB,				//վ��Ҳ���ʧ��
		GEMSTONE_NOT_ENOUGH,				//��ʯ����
		MONEY_LOCKED_BYGAME,				//����ұ�����
	};
};



//֪ͨ��
class CocCmdStateType
{
public:
	enum
	{
		COC_HANDLE_SUCCESS = 0x0001,								//��½�ɹ�
		COC_HANDLE_FAILED,											//���ڲ���ȷ����,ͳһ�Դ˷���
		COC_INVALID_UIN,											//uin������
		COC_WRONG_PASSWD,											//�������
		COC_USER_IS_ONLINE,											//�Է�������״̬
		COC_REQUEST_SUCCESS,										//����Ĳ���������
		COC_REQUEST_ERRO,											//����û�б�����
		// 	LOGIN_NO_ROOM_MEMBER,										//���Ƿ����Ա
		// 	LOGON_ROOM_IS_BUSY,											//��������æ,��ʾ�ͻ����Ժ�����
		// 	LOGON_NO_THIS_ROOM,  										//�÷��䲻����(�����ѽ�ɢ,����ʱ����)
		// 	LOGON_REJECT,												//���ܾ���¼
		// 	LOGON_REQ,													//���������½��
		// 	LOGON_VISITOR_ISFULL,										//��������
		// 	LOGON_ROOM_CLOSE,											//�����ǹرյ�
		// 	LOGON_WRONG_ROOM_PASSWD,									//�����������
		// 	LOGON_ROOM_ISFULL,											//�ο�����
		// 	LOGON_BLACKLIST_UIN,										//�û��ں�������
		// 	LOGON_BLACKLIST_IP,											//IP�ں�������
		// 	LOGON_FORBID_JOIN,											//�÷��䲻����������
		// 	LOGON_REQUEST_DATA,											//��¼�ɹ������������й�//������ whg 20090604
		// 	LOGON_REQUEST_SUCESS,										//��¼�ɹ�������������ȫ������//������ whg 20090604
		// 	LOGON_ROOM_ONLY_SUBSCRIBER,									//ֻ�������߽���
		// 	LOGON_ROOM_ONLY_VIP,										//�շѷ��䣬ֻ����ɷ��û����루�����Ѿ������ߣ�
		// 	LOGON_ROOM_PAY_ERROR,										//�۷Ѳ�ʧ�ܣ�ϵͳ���������)
		// 	LOGON_ROOM_INGAME,											//������Ϸ����
		// 	LOGON_BLACKLIST_MAC,										//�������ں�������
		// 	LOGON_MAX_LIMIT,											//����mac��¼�����������
	};
};


class CocBindBrother
{
public:
	enum
	{
		COC_BIND_SUCCESS,											//�ɹ�				
		COC_BIND_FAILED,											//���ڲ���ȷ����,ͳһ�Դ˷���
		COC_INVALID_GAMEID,											//��Ϸid������
		COC_ALREADY_BIND,											//�Ѿ��󶨹���
		COC_MAC_REPEAT,												//mac�Ѿ�����
		COC_LEVEL_LIMIT,											//��Ӫ�ȼ������
		COC_BIND_SELF,												//�Լ����Լ�
	};

};

class COCClanState
{
public:
	enum
	{
		CLAN_NORMAL_STATE,				//��״̬
		CLAN_REQ_STATE,					//����״̬
		CLAN_IN_STATE,					//�ڲ�����
	};
};

//coc���в���״̬�룬ͳһ�ڴ˶���
class CocNewState
{
public:
	enum
	{
		COC_SUCCESS,											//�ɹ�		
		COC_CLAN_BASECAMP_ERROR,								//��Ӫ�ȼ������
		COC_CLAN_GEMSTONE_NOTENOUGH,							//��ʯ����
		COC_CLAN_NAME_REPEAT,									//�����ظ�
		COC_ALREADY_IN_CLAN,									//�Ѿ��ڲ�����
		COC_CLAN_TOMANY_MEMBER,									//������Ա��������
		COC_CLANID_NOT_EXIST,									//���䲻����
		COC_NOT_CLAN_MEMBER,									//���ǲ����Ա
		COC_CLAN_ACL_NOTENOUGH,									//Ȩ�޲���
		COC_CLAN_CDTIME,										//��ȴ��
		COC_CLAN_LEAVE_ERR,										//���첻���뿪
		COC_CLAN_ALREADY_REQ,									//�����ظ�����
		COC_CLAN_CLANID_EXIST,									//����id����
		COC_CLAN_NAME_ERR,										//�������ֲ���Ϊ��
		COC_CLAN_NAME_LEN_ERR,									//�������ֳ�������
		COC_CLAN_CUP_NOTENOUGH,									//������̫С
		COC_CLAN_RANK_NUM_LIMIT,								//�������������������
		COC_CLAN_FAILD,											//δ֪����
		COC_CLAN_NOT_INCLA,										//���ٲ�����
		COC_CLAN_TIMES_NOTENOUGH,								//��������
		COC_CLAN_REQ_TIMEOUT,									//�������

		COC_CLAN_CONFIG_EXCEPTION,								//�����쳣
		COC_CLAN_COLDTIME,										//��ȴʱ����
		COC_CLAN_CONTRIBUTION_ONTENOUGH,						//���乱�ײ���
	};
};

class ResourceErrorCode
{
public:
	enum
	{
		RESOURCE_GOLD_NOTENOUGH = 101,							//��Ҳ���
		RESOURCE_HOLYWARTER_NOTENOUGH,							//ʥˮ����
		RESOURCE_BLACKWATER_NOTENOUGH,							//��ˮ����
		RESOURCE_GEMSTONE_NOTENOUGH,							//��ʯ����
		RESOURCE_NOTDEFINE,										//δ��������
	};
};

#endif
