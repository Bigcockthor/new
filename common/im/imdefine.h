#ifndef IM_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF
#define IM_DEFINE_KSDJJFSDFKSDJLDSFLSJDFLJSDF

#include "include/icqtypes.h"
#include <string>
#include <map>
#include "include/TinyMarkup.h"
#include "include/base64.h"
#define BASE_ROOM_BINDSOCKET 64000
using namespace std;

#define MAX_SEARCH					10
#define PARTNER_DEFAULT				1							//ϵͳĬ�ϵĺϻ���,���Լ�
#define MAX_NICK_LEN				36


enum
{
	NEW_UIN_SUCCESS,
	NEW_UIN_LOWER_VER,
	NEW_UIN_FAILED,
	NEW_UIN_BLOCKED,											//������
};
class ImGiveGiftErr
{
public:
	enum
	{
		IM_GIFT_GIVE_SUCCESS,
		IM_GIFT_GIVE_FAILD,
		IM_GIFT_NOT_THIS_GIFT,					//�Ӻ����ż������������
		IM_GIFT_IS_NOT_CHARM_GIFT,				//������������
		IM_GIFT_NOT_HAVE_ENOUGH_MONEY,			//Ǯ����
		IM_GIFT_GIVE_GIFT_IN_GAME,				//��Ϸ�в���������
		IM_GIFT_NO_HAVE_THIS_GIFT,				//û���������
		IM_GIFT_WITHOUT_ADDFRIEND,				//����Ҫ��Ҫ��Ӻ���
		IM_GIFT_WITH_ADDFRIEND,					//��Ҫ��Ӻ���
		IM_GIFT_IN_BLACKLIST,					//�ں�������
		IM_GIFT_IS_NOT_FRIEND,					//���Ǻ��ѹ�ϵ
		IM_GIFT_IS_REPORTED,					//���ٱ�
	};
};

class ImDeleteFriendErr
{
public:
	enum
	{
		IM_DELETE_SUCCESS,				//ɾ�����ѳɹ�
		IM_DELETE_FAIL,					//ɾ������ʧ��
		IM_DELETE_FRIEND,				//����ɾ������
		IM_FRIEND_DELETE_ME,			//������ɾ��
		IM_IS_NOT_FRINED,				//���ں����б���
	};
};

class ImBlackListHandleErr
{
public:
	enum
	{
		IM_BLACKLIST_HANDLE_SUCCESS,		//��ӻ�ɾ���������ɹ�
		IM_BLACKLIST_HANDLE_IN_BLACKLIST,	//�Է����ں�������
		IM_BLACKLIST_HANDLE_NOT_IN_BLACKLIST,	//�Է�������ĺ�������
	};
};
class ImMsgErr
{
public:
	enum
	{
		IM_SEND_MSG,					//����Ϣ
		IM_PRESENT_GIFT,				//������
		IM_IS_NOT_FRIEND,				//���Ǻ��ѹ�ϵ
		IM_IN_BLACKLIST,				//�ں�������		
	};
};
class ImNotifyInfo
{
public:
	enum
	{
		IM_NOTIFY_SYNC_MONEY,			//�ʽ��˻�ͬ��
		IM_NOTIFY_SYS_MSG,				//�µ�ϵͳ֪ͨ
	};
};

enum 
{
	POPUPMSG_TYPE_PRESENTMONEY = 0x0002,						//�����ʽ�����
};

class ForceOffline
{
public:
	enum 
	{
		FORCEOFF_ANOTHER = 0x10,		//��������
		FORCEOFF_BLOCKED,				//�˺ŷ���
		FORCEOFF_MODIFY_PASSWORD,		//�޸�����
	};
};

class CTinyLordLevel
{
public:
	enum
	{
		LORD_LEVEL_NONE,										//�޾�λ
		LORD_LEVEL_BARON,										//�о�
		LORD_LEVEL_VISCOUNT,									//�Ӿ�
		LORD_LEVEL_EARL,										//����
		LORD_LEVEL_MARQUESS,									//���
		LORD_LEVEL_DUKE,										//����
		LORD_LEVEL_KING,										//����
		LORD_LEVEL_LIMIT,										//��λ����
	};
	static std::string LordLevelName[LORD_LEVEL_LIMIT];
	static string GetLordLevelName(uint8 lordLevel)
	{
		string lordstr = "��λ";
		switch (lordLevel)
		{
		case CTinyLordLevel::LORD_LEVEL_NONE:		
			lordstr="�Ǿ�λ";
			break;
		case CTinyLordLevel::LORD_LEVEL_BARON:		
			lordstr="�о�";
			break;
		case CTinyLordLevel::LORD_LEVEL_VISCOUNT:	
			lordstr="�Ӿ�";
			break;
		case CTinyLordLevel::LORD_LEVEL_EARL:		
			lordstr="����";
			break;
		case CTinyLordLevel::LORD_LEVEL_MARQUESS:	
			lordstr="���";
			break;
		case CTinyLordLevel::LORD_LEVEL_DUKE:	
			lordstr="����";
			break;
		case CTinyLordLevel::LORD_LEVEL_KING:	
			lordstr="����";
			break;
		}
		return lordstr;
	}
};




class CTaoleGlobleUserType
{
public:
	enum
	{
		USER_GLOBLE_TYPE_NONE			= 0,					//�����
		USER_GLOBLE_TYPE_SINGER			= 1,					//��˾ǩԼ����
		USER_GLOBLE_TYPE_AGENT			= 2,					//��˾ǩԼ����
		USER_GLOBLE_TYPE_CONTACT_STAFF	= 4,					//��˾�ͷ�
		USER_GLOBLE_TYPE_SALES			= 8,					//��˾����
		USER_GLOBLE_TYPE_PRIVILEGES		= 16,					//��Ȩ��־
		USER_GLOBLE_TYPE_COO_ASSISTANT	= 20,					//��վ����־
		USER_GLOBLE_TYPE_COO			= 22,					//վ����־
		USER_GLOBLE_TYPE_MUSIC_SOCIETY  = 24,					//���ű�־
		USER_GLOBLE_TYPE_DANCER			= 26,					//�赸��Ա��־
		USER_GLOBLE_TYPE_FUHAO			= 28,					//������־
		USER_GLOBLE_TYPE_STAR			= 30,					//��������
		USER_GLOBLE_TYPE_COMPERE		= 32,					//��������
		USER_GLOBLE_TYPE_COMPEREMAN		= 34,					//MC������
		USER_GLOBLE_TYPE_PATROL			= 36,					//Ѳ��
		USER_GLOBLE_TYPE_OPERATION		= 38,					//��Ӫ
		USER_GLOBLE_TYPE_BABY1			= 40,					//����1
		USER_GLOBLE_TYPE_BABY2			= 42,					//����2
		USER_GLOBLE_TYPE_BABY3			= 44,					//����3
		USER_GLOBLE_TYPE_BABY4			= 46,					//����4
		USER_GLOBLE_TYPE_BABY5			= 48,					//����5
		USER_GLOBLE_TYPE_BABY6			= 50,					//����6
	};
	static bool IsActor(uint8 usertype)
	{
		return (usertype == USER_GLOBLE_TYPE_SINGER 
			 || usertype == USER_GLOBLE_TYPE_MUSIC_SOCIETY 
			 || usertype == USER_GLOBLE_TYPE_DANCER 
			 || usertype == USER_GLOBLE_TYPE_STAR) ;
	}

	static bool IsGlobalMsgFree(uint8 usertype)
	{
		
		return (usertype == USER_GLOBLE_TYPE_CONTACT_STAFF 
			 || usertype == USER_GLOBLE_TYPE_SALES 
			 || usertype == USER_GLOBLE_TYPE_COO 
			 || usertype == USER_GLOBLE_TYPE_COO_ASSISTANT);
	}

	static string GetLordLevelName(uint8 usertype)
	{
		string userTypeStr = "";
		switch (usertype)
		{
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_NONE:		
			userTypeStr="���������";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SINGER:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_AGENT:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_CONTACT_STAFF:		
			userTypeStr="�ͷ�";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_SALES:		
			userTypeStr="�������";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PRIVILEGES:		
			userTypeStr="��Ȩ";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO:		
			userTypeStr="վ��";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COO_ASSISTANT:		
			userTypeStr="��վ��";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_MUSIC_SOCIETY:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_DANCER:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_FUHAO:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_STAR:		
			userTypeStr="����";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPERE:		
			userTypeStr="��������";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_COMPEREMAN:		
			userTypeStr="MC������";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_PATROL:		
			userTypeStr="Ѳ��";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_OPERATION:		
			userTypeStr="��Ӫ";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY1:		
			userTypeStr="����1";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY2:		
			userTypeStr="����2";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY3:		
			userTypeStr="����3";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY4:		
			userTypeStr="����4";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY5:		
			userTypeStr="����5";
			break;
		case CTaoleGlobleUserType::USER_GLOBLE_TYPE_BABY6:		
			userTypeStr="����6";
			break;
		

		}
		return userTypeStr;
	}
	
	static uint8 GetLordLevelType(string typeName)
	{
		uint8 userType = USER_GLOBLE_TYPE_NONE;
		if (typeName == "���������")
		{
			userType = USER_GLOBLE_TYPE_NONE;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_SINGER;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_AGENT;
		}
		else if (typeName == "�ͷ�")
		{
			userType = USER_GLOBLE_TYPE_CONTACT_STAFF;
		}
		else if (typeName == "�������")
		{
			userType = USER_GLOBLE_TYPE_SALES;
		}
		else if (typeName == "��Ȩ")
		{
			userType = USER_GLOBLE_TYPE_PRIVILEGES;
		}
		else if (typeName == "վ��")
		{
			userType = USER_GLOBLE_TYPE_COO;
		}
		else if (typeName == "��վ��")
		{
			userType = USER_GLOBLE_TYPE_COO_ASSISTANT;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_MUSIC_SOCIETY;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_DANCER;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_FUHAO;
		}
		else if (typeName == "����")
		{
			userType = USER_GLOBLE_TYPE_STAR;
		}
		else if (typeName == "��������")
		{
			userType = USER_GLOBLE_TYPE_COMPERE;
		}
		else if (typeName == "MC������")
		{
			userType = USER_GLOBLE_TYPE_COMPEREMAN;
		}
		else if (typeName == "Ѳ��")
		{
			userType = USER_GLOBLE_TYPE_PATROL;
		}
		else if (typeName == "��Ӫ")
		{
			userType = USER_GLOBLE_TYPE_OPERATION;
		}
		else if (typeName == "����1")
		{
			userType = USER_GLOBLE_TYPE_BABY1;
		}
		else if (typeName == "����2")
		{
			userType = USER_GLOBLE_TYPE_BABY2;
		}
		else if (typeName == "����3")
		{
			userType = USER_GLOBLE_TYPE_BABY3;
		}
		else if (typeName == "����4")
		{
			userType = USER_GLOBLE_TYPE_BABY4;
		}
		else if (typeName == "����5")
		{
			userType = USER_GLOBLE_TYPE_BABY5;
		}
		else if (typeName == "����6")
		{
			userType = USER_GLOBLE_TYPE_BABY6;
		}

		return userType;
	}
};


enum {
	CHANGE_MONEY_SUCCESS,										//���˳ɹ�
	CHANGE_MONEY_FAILED,										//����ʧ��
};  


enum
{
	UDP_VER_01				=		0x001,
	UDP_VER_02				=       0x002,
	UDP_VER_03				=		0x003,
	UDP_VER_04				=		0x004,						//������վ��̨����.
	UDP_VER_05				=		0x005,						//������վ��̨����.
	UDP_VER_O6				=		0x006,						//����Ӻ�������		2013/7/22
	UDP_VER_07				=		0x007,						//��Ϣ�Ѷ�
	UDP_VER_08				=		0x008,						//���Ӳ����û���������Ŀ����
	UDP_VER_09				=		0x009,						//�ƶ�IM
	UDP_VER_10				=		0x010,						//�ͷ���������subUin
	UDP_VER_11				=		0x011,						//�ղط��䣬��������uin �ҵĴ����ķ��� ��������ʾ
	UDP_VER_12				=		0x012,						//�ղط��䷵�ط�����Ϣ�汾��
	UDP_VER_13				=		0x013,
	UDP_VER_14				=		0x014,
	UDP_VER_15				=		0x015,						//ȡ����֪ͨ
	UDP_VER_16				=		0X016,						//���Ϸ���
	UDP_VER_CURRENT			=       UDP_VER_16,
};

enum
{
	TCP_VER_01				=		0x002,
	TCP_VER_CURRENT			=       TCP_VER_01,
};

enum
{
	//MSG_STATUS_DEFAULT = 0,			
	MSG_STATUS_SENDED = 0,											//���ʹ�
	MSG_STATUS_READED,											//�Ѷ�
};

typedef enum
{
	NET_TYPE_DX,												//����
	NET_TYPE_WT,												//����
}NetTypeDefine;

enum
{
	UDP_SEND_TIMEOUT		=		3000,			//3 secs
	UDP_KEEPALIVE_INTERVAL	=		20*1000,		//20 secs
	UDP_MAX_SEND_ATTEMPTS	=		5,				//5 times
};

enum {
	UDP_ACK = 1,
	UDP_NEW_UIN,
	UDP_GET_CONTACTLIST,
	UDP_LOGIN,
	UDP_LOGOUT,
	UDP_KEEPALIVE,
	UDP_CHANGE_STATUS,
	UDP_UPDATE_CONTACT,
	UDP_MODIFY_USER,
	UDP_UPDATE_USER,
	UDP_SEND_MSG,
	UDP_SEARCH_RANDOM,
	UDP_SEARCH_CUSTOM,
	UDP_ADD_FRIEND,
	UDP_DEL_FRIEND,
	UDP_SEARCH_CUSTOM_ONLINE,
	UDP_SEARCH_SERVICE,

	UDP_CHANGE_PASSWD,		
	UDP_SEARCH_SECTION,
	UDP_CHANGE_MONEY,											//����
	UDP_GET_ROOM_ADDR,											//��õ�ַ

	UDP_ADD_FAV_ROOM,											//���ӷ����ղ�
	UDP_DEL_FAV_ROOM,											//ɾ�������ղ�

	UDP_DEL_ADDFRIEND,
	UDP_DEL_FREIND_MYANDADD,

	UDP_HUAJB,													//�����
	UDP_ZHUANYXB,												//���ת��Ϸ��
	UDP_ANDROID_LOGIN,											//�����˵�½
	UDP_SEND_MSG_2,												//�µ�������Ϣ�ӿ�
	UDP_MODIFY_PASS,											//�����ƶ����޸�����ӿ�

	UDP_SRV_USER_ONLINE = 0x0100,
	UDP_SRV_USER_OFFLINE,
	UDP_SRV_MULTI_ONLINE,
	UDP_SRV_STATUS_CHANGED,
	UDP_SRV_MESSAGE,
	UDP_SRV_SEARCH,
	UDP_SRV_IPCMD,
	UDP_SRV_IPCMD_RESPOND,

	//account
	UDP_SRV_ACCOUNT,

	UDP_SRV_NEW_VER,
	UDP_SRV_FORCE_OFFLINE,										//ǿ���û�����
	UDP_SRV_CHANGE_MONEY,										//֪ͨ����

	UDP_SRV_WEB_NOTIFY,											//ͨ��web�򿪵�֪ͨ
	UDP_SRV_ALBUM,												//�������
	UDP_SRV_FAVBLOG,											//����Blog�ղ��б�
	UDP_SRV_POPUP_MSG,											//���Ƶ�����Ϣ

	UDP_SRV_FAVROOM,
	UDP_SRV_MINIMSG,											//֪ͨ������Ϣ
	UDP_SRV_CUSTOM_SYSMSG,										//�û����Ƶ�ϵͳ��Ϣ
	UDP_SRV_LJXF,												//������ѽ��

	UDP_MANCMD = 0x0400,										//����ָ��

	UDP_SIG_START  = 0x0500,

	UDP_SIG_REQRES,												//����ͨѶ��Դ
	UDP_SIG_INVITE,
	UDP_SIG_NOTIFY,
	UDP_SIG_ACCEPT,
	UDP_SIG_REFUSE,
	UDP_SIG_ACK,
	UDP_SIG_BYE,
	UDP_SIG_CANCELINVITE,

	UDP_REQ_RES = 0x0600,										//������Դ
	UDP_GET_VCODE,												//������֤��

	UDP_SIG_END  = 0x0700,
	UDP_SEND_ISINPUT,											//��������
	UDP_USER_INFO_UPDATE,										//��̨�޸��û���Ϣ
	UDP_MESSAGE_IS_READED,										//��Ϣ�Ѷ�
	UDP_GIVE_GIFT,												//������
	UDP_ADD_BLACKLIST,											//��Ӻ�����
	UDP_GET_BLACKLIST,
	UDP_DELETE_BLACKLIST,
	UDP_UPDATE_REMARK,											//�޸ı�ע
	UDP_UPDATE_COORDINATE,										//��������
	UDP_USER_DETAIL_INFO_GET,									//��ȡ�û�����
	UDP_USER_DETAIL_INFO_UPDATE,								//�޸��û�����
	UDP_S2C_RELOGIN,											//�û�������֤
	UDP_C2S_RELOGIN,											//�ͻ�����֤����
	UDP_S2C_RELOGIN_REPLY,										//��֤���0 �ɹ��� 1 ʧ��
	UDP_C2S_RELOGIN_REPLY,										//��֤�ɹ�֮�󣬿ͻ����ϴ�״̬
	UDP_ISNOT_FRIEND,											//���Ǻ��ѹ�ϵ
	UDP_C2S_UPLOAD_DEVICE_INFO,									//�ϴ��豸Ψһʶ���룬���豸����
	UDP_S2C_UPLOAD_DEVICE_INFO,									//�·��û�Ψһʶ����
	UDP_C2S_UPLOAD_PUSH_TOKEN,									//�ϴ���Ϣ����ID
	UDP_S2C_UPLOAD_PUSH_TOKEN,									//�·���Ϣ����ID
	UDP_S2C_GIVE_GIFT,											//�������·��������Ƿ�ɹ�
	UDP_S2C_NEW_GIFT,											//�յ�������
	UDP_S2C_MISSION_COMPLETED_NOTICE,							//�������֪ͨ
	UDP_C2S_GET_SERVICE_LIST,									//��ȡ�ͷ��б�
	UDP_S2C_GET_SERVICE_LIST,									//���ؿͷ��б�
	UDP_C2S_GET_PREROGATIVE_ICON,								//��Ȩͼ��
	UDP_S2C_GET_PREROGATIVE_ICON,								//�·���Ȩͼ��
	UDP_C2S_MOBILE_NUMBER_LOGIN,								//�ֻ��ŵ�½
	UDP_C2S_GET_URL,											//��̬�·�url
	UDP_S2C_GET_URL,
	UDP_S2C_WEATH_AND_CHARM_VALUE,								//�·�����ֵ�ͲƸ�ֵ�����Ϣ
	UDP_C2S_UPDATE_PUSH_TIMES,									//������Ϣ���ͼ�����
	UD_S2C_NEW_SITUATION_NOTIFY_USER,							//�¶�̬֪ͨ����
	UDP_S2C_NEW_REVIEW_NOTIFY_USER,								//������֪ͨ
	UDP_S2C_NOTICE_NEW,											//֪ͨ
	UDP_C2S_BINGDING_NOTIFY,									//��֪ͨ
	UDP_S2C_BINGDING_NOTIFY,	
	UDP_S2C_ROOM_PORT_LIST,											//������ɫͨ���˿ں�
	UDP_C2S_ADD_NEW_CONN,										//��Ȩ��¼ǰ��session������connection
	UDP_S2C_ATTPARTNER_LIST,									//��ע�б�
	UDP_C2S_GET_URL_IP,											//��ȡurl��ӦiP
	UDP_S2C_CANCEL_BINGDING_NOTIFY,								//ȡ����֪ͨ
};

enum
{
	UDP_UPDATE_CUSTOMFACE,										//�޸��Զ���ͷ��
	UDP_UPDATE_LORDLEVEL,										//�޸ľ�λ
	UDP_UPDATE_LEVEL,											//�޸Ļ�Ա
};

enum {
	MSG_TEXT,
	MSG_AUTO_REPLY,
	MSG_AUTH_ACCEPTED,
	MSG_AUTH_REQ,
	MSG_AUTH_REJECTED,
	MSG_ADDED,
	MSG_TCP_REQUEST,
	MSG_TCP_ACCEPTED,
	MSG_TCP_REJECTED,
	MSG_XML,
	MSG_UPGRADE,
	MSG_FILTER,
	MSG_FILTER_ONLINE,
	MSG_XML_AUTH,												//xmlȨ����Ϣ�����ڻ�Ա����
	MSG_NOTIFY,													//ϵͳ֪ͨ��Ϣ,��������notify wnd
	MSG_PLUGIN,													// ���֮��ͨ�ŵ���Ϣ [8/5/2003 9:49 why]
	MSG_NEW_SYSMSG,
	MSG_PLUGIN_NEW,												//���֮��ͨ�ŵ���Ϣ����Ҫ�������ƣ���Ƶ�����Ƶȡ�
	MSG_POPMSG, //

	MSG_IMAGE,											//ͼƬ
	MSG_VOICE,											//��Ƶ
	MSG_VIDEO,											//����
	MSG_LOCATION,										//λ��
	MSG_CONTACT,										//��Ƭ
	MSG_GIFT,											//����
	MSG_SNAP_PICTURE,									//�ĺ󼴷�
	MSG_IMAGE_TEXT,										//���ֺ�ͼƬ�����Ϣ
	MSG_NEED_TRANS_SRCUIN,								//��Ҫ��srcuin�滻��10000
	MSG_NOT_NEED_TRANS_SRCUIN,							//����Ҫ��srcuin�滻��10000
	MSG_NEWS,											//�����˺���Ϣ
	MSG_ROOM,											//�ƽ�������Ϣ
	MSG_EXPRESSION,										//������Ϣ
	MSG_TUIBO,

	MSG_COMPLEX = 249,										//�������ͣ�����ʱû�г�������ɲ�ҪԽ�����ֶ�
};

enum
{
	VCODE_ACTION_TYPE_ADDFRIEND,								//��Ӻ���
	VCODE_ACTION_TYPE_INVITE,									//����

	VCODE_ACTION_TYPE_MAX = VCODE_ACTION_TYPE_INVITE,
};

enum {
	ADD_FRIEND_ACCEPTED,
	ADD_FRIEND_AUTH_REQ,
	ADD_FRIEND_REJECTED,
	ADD_FRIEND_TOO_FAST,
	ADD_FRIEND_VCODE_NOT_MATCH,
	ADD_FRIEND_VCODE_OUT_TIME,
	ADD_FRIEND_IS_REPORTED,			//���ٱ�
};

enum {
	LOGIN_SUCCESS,
	LOGIN_INVALID_UIN,
	LOGIN_WRONG_PASSWD,
	LOGIN_LOCKED,
	LOGIN_FAILED,
	LOGIN_LOW_VER,
	LOGIN_OTHER_DEVICE_LOGIN,
	LOGIN_USER_LAST_SCAN,					//���һ����ɨ���¼
	LOGIN_USER_LAST_ACCREDIT,						//���һ������Ȩ��¼
	LOGIN_THIRDPARTY_REAUTH,				//��Ҫ������Ȩ
};



enum {
	STATUS_ONLINE,
	STATUS_OFFLINE,
	STATUS_AWAY,
	STATUS_INVIS,
	NR_STATUS
};

enum
{
	LOGIN_DEVICE_PC = 1<<1,
	LOGIN_DEVICE_IOS = 1<<2,
	LOGIN_DEVICE_ANDROID = 1<<3,
};

union TransTaxRate
{
	struct
	{
		uint8 generalTrans:1;								//��ͨ�û��Ƿ�������
		uint8 generalTax:7;									//��ͨ�û�������˰��%
		uint8 lowVipTrans:1;								//�ͻ��û��Ƿ�������
		uint8 lowVipTax:7;									//�ͻ��û�������˰��%
		uint8 midVipTrans:1;								//�л��û��Ƿ�������
		uint8 midVipTax:7;									//�л��û�������˰��%
		uint8 higherVipTrans:1;								//�߻��û��Ƿ�������			
		uint8 higherVipTax:7;								//�߻��û�������˰��%		
	};
	uint32 transTax;										//��Ա����˰��
};


class PassWdType
{
public:
	enum
	{
		IM_UIN_PASSWD,		//�û�ID��¼
		IM_PHONE_NUMBER_PASSWD,		//ģ����¼(uin/phonenum��¼)
	};
};
enum
{
	//���Ӳ�����ö��ֵ
	IM_USER_LOGIN,			 //�ͻ��˵�½(��ȡ�����б�/PC��½/�ֻ��û��ӵ�½�����½/)
	IM_USER_RELOGIN,		 //�û�������֤
	IM_USER_GET_CONTACT,	 //�ͻ���������ȡ�����б�
	IM_USER_NOT_FIRST_LOGIN, //�ֻ��û�����Ļ֮��ֱ��login
};

class AuthorizationLogin
{
public:
	enum
	{
		AUTHORIZATION_LOGIN,	//��Ȩ��¼
		BINGDING_UIN,			//���ʺ�
		CANCEL_BINGING,			//�����
		MANUAL_BINDING,			//�ֶ��޸İ�
	};
};


#pragma pack(1)
union	Customface						
{
	unsigned short customFace;
	struct {
		unsigned short userNew:1;								//�Ƿ��������Զ���ͷ��			
		unsigned short newFace:15;								//ͷ��汾��
	};
};
#pragma pack()

class LoginResult {
public:
	uint16		state;											//����״̬
	uint32		ip;												//����IP
	uint8		level;											//�û�����
	uint16		levelEndDays;									//��Ա���ж೤ʱ�����,���������û�����
	uint8		lordLevel;										//��λ����
	uint32		right;											//Ȩ��
	uint32		onlinetime;										//������ʱ��
	uint64		cash;											//�ֽ�
	uint32		infoVer;										//�û����ϰ汾
	uint32		friendVer;										//������Ϣ�汾	
	uint32		friendListVer;									//�����б�汾��
	Customface  customFace;
	string		sessionKey;										
	uint16		usertype;										//�û����ͣ��ͷ�������֮��
	uint8		richerOrder;									//��������
	uint32		m_urlVer;										//url�汾��
	
	LoginResult()
	{
		init();
	}
	void init()
	{
		state = 0;
		ip = 0;
		right = level = 0;
		onlinetime = 0;
		cash = 0;
		infoVer = 0;
		friendVer = 0;
		friendListVer = 0;
		sessionKey = "";
		usertype = 0;
		richerOrder = 0;
		m_urlVer = 0;
	}
};



#pragma pack(1)

class ParterInfo
{
	
public:

	ParterInfo(uint32 pid = 0) : partnerID(pid)
	{
		newUserPresent		= 500;
		receiverRatio		= 50;
		companyTaxRatio		= 20;
		roomHostTaxRatio	= 5;
		prizePoolRatio		= 100 - receiverRatio - companyTaxRatio - roomHostTaxRatio;

		prize_recv_ratio	= 40;
		prize_comp_ratio	= 15;
		prize_host_ratio	= 20;
		prize_pool_ratio	= 100 - prize_recv_ratio - prize_comp_ratio - prize_host_ratio;

		diamon_receiver		= 70;									//�����������
		diamon_host			= 1;										//��������
		diamon_pid			= 15;											//վ�����
		diamon_company		= 100 - diamon_receiver - diamon_host -diamon_pid;										//��˾�������
		present_radioType	= 0;
		greate_giftprice	= 1000000;
		greate_present		= 1000000;
		globle_redpaper		= 5000000;
		greate_disp_times	= 2;
		bRedpaperOff		= false;		
		currPrizedRatio		= 800;
		prizeIncoming		= 0;
		prizeOutgoing		= 0;

		automic				= true;
		automic_start		= 660;
		automic_end			= 1020;

		generalAccessMultiRoom=0;
		lowVipAccessMultiRoom=0;
		midVipAccessMultiRoom=0;
		hightVipAccessMultiRoom=1;
		richerAccessMultiRoom=1;
		agentAccessMultiRoom=1;
		supperAccessMultiRoom=1;

		generalTrans		= 0;								//��ͨ�û��Ƿ�������
		generalTax			= 0;								//��ͨ�û�������˰��%
		lowVipTrans			= 1;								//�ͻ��û��Ƿ�������
		lowVipTax			= 8;								//�ͻ��û�������˰��%
		midVipTrans			= 1;								//�л��û��Ƿ�������
		midVipTax			= 5;								//�л��û�������˰��%
		higherVipTrans		= 1;								//�߻��û��Ƿ�������			
		higherVipTax		= 0;								//�߻��û�������˰��%		


		lastMonthTax		= 0;
		currMonthTax		= 0;
		broadCasePrice		= 100000;
		lastUpdate			= 0;

		presentOnMicTimelimit= 0;
		presentOnMicPerMin	= 0;

		status				= 2;
		micPresentTimeout   = 0;
		sRoomAccess			= "";

		diamon_gift_flag	= 0;									//��ʯ���￪��
		diamon_action_flag	= 0;									//��ʯ������Ч����
		diamon_action_limit	= 0;									//��ʯ����
		duobao_treasure_open= 0;
	}
	virtual ~ParterInfo(){}
	uint32	partnerID;											//������ID
	string	username;											//�����̵�½�û�����ע���Ĭ��ָ��username.XXXXXX.com�������̼�
	string	partnerName;										//������ȫ��
	string	domainName;											//��������������
	string	domainNameEx;										//��������
	string	moneyName;											//���������
	uint32 lastUpdate;

	uint16	newUserPresent;										//��ע���û���������ҽ��
	uint8	receiverRatio;										//�������������
	uint8	companyTaxRatio;									//��˾˰������
	uint8	roomHostTaxRatio;									//������������
	uint8	prizePoolRatio;										//���ر���

	uint8	diamon_receiver;									//�����������
	uint8	diamon_company;										//��˾�������
	uint8	diamon_host;										//��������
	uint8	diamon_pid;											//վ�����

	uint8   prize_recv_ratio;									//�������������˱���
	uint8	prize_comp_ratio;									//�������﹫˾����
	uint8	prize_host_ratio;									//����������������
	uint8	prize_pool_ratio;									//�������ｱ�ر���

	uint8	present_radioType;									//�󽱹㲥����,0Ĭ���Ǹ���ˢ���ܶ����greate_present, 1�Ǹ������ﵥ�۴���
	uint32	greate_giftprice;									//�󽱹㲥����Ϊ1ʱ,�����ﵥ�۴��ڸ�ֵ���͹㲥
	uint32	greate_present;										//�㲥��ֵĬ�ϣ�������
	uint32	greate_disp_times;									//�󽱲��Ž���
	uint32  globle_redpaper;									//ȫվƮ����
	bool	bRedpaperOff;										//�������

	uint8	automic;											//�Զ�����
	uint16	automic_start;										//�Զ�����ʼʱ�䣨����ĵڣη��ӣ�
	uint16	automic_end;										//�Զ��������ʱ�䣨����ĵڣη���)

	uint16	currPrizedRatio;									//�н�����
	uint16	prize_rate2;										//���������н�����
	uint64	prizeIncoming;										//��������
	uint64	prizeOutgoing;										//����֧��


	uint64	lastMonthTax;										//�ϸ���˰��
	uint64	currMonthTax;										//����˰��	
	uint32  broadCasePrice;										//С���ȼ۸�

	uint8	presentOnMicTimelimit;								//�������������ʼʱ�䣬0Ϊ���ͣ�С�ڴ�ֵ���ͣ�ʱ�����
	uint32	presentOnMicPerMin;									//�ﵽ�򳬹�presentOnMicTimeʱ��ÿ���������������

	string  sRoomAccess;											//�ַ�����̬����������
	string	giftVer;											//��������汾��
	string  stampVer;											//ӡ�°汾��
	string  sortVer;											//��������汾��
	string	giftVerNew;											//������汾��
	uint8	gift_vod;											//����������÷�Χ

	uint8  status;												//0:�ر�״̬ 1:����Ӫ�� 2:��ʽ��Ӫ

	uint32	host_type;											//����˰���Ƿ��������˻��ܿ���
	uint32  micPresentTimeout;									//��������ȡ��ʱʱ��

	uint8  diamon_gift_flag;									//��ʯ���￪��
	uint8  diamon_action_flag;									//��ʯ������Ч����
	uint32 diamon_action_limit;									//��ʯ����
	uint8  duobao_treasure_open;								//�ᱦ�����

	union
	{
		struct
		{
			uint8 generalAccessMultiRoom:1;						//��ͨ�û��������������
			uint8 lowVipAccessMultiRoom:1;						//�ͻ�������������
			uint8 midVipAccessMultiRoom:1;						//�л�������������
			uint8 hightVipAccessMultiRoom:1;					//�߻�������������
			uint8 richerAccessMultiRoom:1;						//���̽������������
			uint8 agentAccessMultiRoom:1;						//����������������
			uint8 supperAccessMultiRoom:1;						//���ܽ������������
			uint8 reserved:1;					
		};
		uint8	roomAccess;										//ͬһ�����������������
	};
	union 
	{
		struct
		{
			uint8 generalTrans:1;								//��ͨ�û��Ƿ�������
			uint8 generalTax:7;									//��ͨ�û�������˰��%
			uint8 lowVipTrans:1;								//�ͻ��û��Ƿ�������
			uint8 lowVipTax:7;									//�ͻ��û�������˰��%
			uint8 midVipTrans:1;								//�л��û��Ƿ�������
			uint8 midVipTax:7;									//�л��û�������˰��%
			uint8 higherVipTrans:1;								//�߻��û��Ƿ�������			
			uint8 higherVipTax:7;								//�߻��û�������˰��%		
		};
		uint32 transTax;										//��Ա����˰��
	};

	std::string BuildXMLInfoForClient(uint16 udpver)
	{
		CMarkup xmldoc;
		xmldoc.AddElem("pid", partnerID);
		xmldoc.AddElem("dm", domainName.length() ? domainName.c_str() : domainNameEx.c_str());
		xmldoc.AddElem("gdt", greate_disp_times);
		xmldoc.AddElem("bpc", broadCasePrice);
		string strAccess;
		if (udpver < UDP_VER_08)
		{
			if(sRoomAccess.length() > 13)
			{
				strAccess = sRoomAccess.substr(0, 13);
			}
			else
			{
				strAccess = sRoomAccess;
			}	
		}
		else
		{
			strAccess = sRoomAccess;
		}
		xmldoc.AddElem("rAc", strAccess.c_str());
		xmldoc.AddElem("tax", transTax);
		xmldoc.AddElem("pot", presentOnMicTimelimit);
		xmldoc.AddElem("ppm", presentOnMicPerMin);
		xmldoc.AddElem("mnn", moneyName.c_str());
		xmldoc.AddElem("giftv", giftVer.c_str());
		xmldoc.AddElem("dmex", domainNameEx.c_str());

#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}

	void ClientParseXML(std::string infoXml)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(infoXml.c_str());
		xmldoc.GetChildValue("pid", partnerID);
		xmldoc.GetChildValue("dm", domainName);
		xmldoc.GetChildValue("gdt", greate_disp_times);
		xmldoc.GetChildValue("bpc", broadCasePrice);
		xmldoc.GetChildValue("rAc", sRoomAccess);
		xmldoc.GetChildValue("tax", transTax);
		xmldoc.GetChildValue("pot", presentOnMicTimelimit);
		xmldoc.GetChildValue("ppm", presentOnMicPerMin);
		xmldoc.GetChildValue("mnn", moneyName);
		xmldoc.GetChildValue("giftv", giftVer);
		xmldoc.GetChildValue("dmex", domainNameEx);
	}


	std::string BuildXMLInfo()
	{
		TinyMarkup xmldoc;

		xmldoc.AddElem("pid", partnerID);			 
		xmldoc.AddElem("pname", talk_base::Base64::encode(partnerName).c_str());		
		xmldoc.AddElem("domain", domainName.c_str());			
		xmldoc.AddElem("money", talk_base::Base64::encode(moneyName).c_str());			
		xmldoc.AddElem("lastup", lastUpdate);

		xmldoc.AddElem("present", newUserPresent);		
		xmldoc.AddElem("recvRatio", receiverRatio);		
		xmldoc.AddElem("comRatio", companyTaxRatio);	
		xmldoc.AddElem("hostRatio", roomHostTaxRatio);	
		xmldoc.AddElem("poolRatio", prizePoolRatio);		
		xmldoc.AddElem("broadprice", broadCasePrice);
										
		xmldoc.AddElem("greategift", greate_present);		
		xmldoc.AddElem("greatedisp", greate_disp_times);	
										
		xmldoc.AddElem("automic", automic);			
		xmldoc.AddElem("automic_start", automic_start);		
		xmldoc.AddElem("automic_end", automic_end);		
										
		xmldoc.AddElem("currPrizedRatio", currPrizedRatio);
		xmldoc.AddElemInt64("prizeIncoming", prizeIncoming);
		xmldoc.AddElemInt64("prizeOutgoing", prizeOutgoing);
										
		xmldoc.AddElem("roomAccess", roomAccess);
		xmldoc.AddElem("transTax", transTax);
										
		xmldoc.AddElemInt64("lastMonthTax", lastMonthTax);
		xmldoc.AddElemInt64("currMonthTax", currMonthTax);
										
		xmldoc.AddElem("presentOnMicTimelimit", presentOnMicTimelimit);
		xmldoc.AddElem("presentOnMicPerMin", presentOnMicPerMin);
										
		xmldoc.AddElem("recv_ratio", prize_recv_ratio);
		xmldoc.AddElem("comp_ratio", prize_comp_ratio);
		xmldoc.AddElem("host_ratio", prize_host_ratio);
		xmldoc.AddElem("pool_ratio", prize_pool_ratio);
										
		xmldoc.AddElem("prize_rate2", prize_rate2);
										
		xmldoc.AddElem("domainNameEx", domainNameEx.c_str());

		xmldoc.AddElem("giftVer", giftVer.c_str());
		xmldoc.AddElem("gift_vod", gift_vod);
		xmldoc.AddElem("sRoomAccess", sRoomAccess.c_str());

#if defined(MARKUP_STL)
		return xmldoc.GetDoc();
#else
		return (LPCTSTR)xmldoc.GetDoc();
#endif
	}

	void ParseXML(std::string &infoXml)
	{
		TinyMarkup xmldoc;
		xmldoc.SetDoc(infoXml.c_str());

		xmldoc.GetChildValue("pid", partnerID);			 
		xmldoc.GetChildValue("pname", partnerName);	
		partnerName = talk_base::Base64::decode(partnerName);
		xmldoc.GetChildValue("domain", domainName);	
		xmldoc.GetChildValue("money", moneyName);
		moneyName = talk_base::Base64::decode(moneyName);
		xmldoc.GetChildValue("lastup", lastUpdate);

		xmldoc.GetChildValue("present", newUserPresent);		
		xmldoc.GetChildValue("recvRatio", receiverRatio);		
		xmldoc.GetChildValue("comRatio", companyTaxRatio);	
		xmldoc.GetChildValue("hostRatio", roomHostTaxRatio);	
		xmldoc.GetChildValue("poolRatio", prizePoolRatio);		
		xmldoc.GetChildValue("broadprice", broadCasePrice);

		xmldoc.GetChildValue("greategift", greate_present);		
		xmldoc.GetChildValue("greatedisp", greate_disp_times);	

		xmldoc.GetChildValue("automic", automic);			
		xmldoc.GetChildValue("automic_start", automic_start);		
		xmldoc.GetChildValue("automic_end", automic_end);		

		xmldoc.GetChildValue("currPrizedRatio", currPrizedRatio);
		xmldoc.GetChildValue("prizeIncoming", prizeIncoming);
		xmldoc.GetChildValue("prizeOutgoing", prizeOutgoing);

		xmldoc.GetChildValue("roomAccess", roomAccess);
		xmldoc.GetChildValue("transTax", transTax);

		xmldoc.GetChildValue("lastMonthTax", lastMonthTax);
		xmldoc.GetChildValue("currMonthTax", currMonthTax);

		xmldoc.GetChildValue("presentOnMicTimelimit", presentOnMicTimelimit);
		xmldoc.GetChildValue("presentOnMicPerMin", presentOnMicPerMin);

		xmldoc.GetChildValue("recv_ratio", prize_recv_ratio);
		xmldoc.GetChildValue("comp_ratio", prize_comp_ratio);
		xmldoc.GetChildValue("host_ratio", prize_host_ratio);
		xmldoc.GetChildValue("pool_ratio", prize_pool_ratio);

		xmldoc.GetChildValue("prize_rate2", prize_rate2);

		xmldoc.GetChildValue("domainNameEx", domainNameEx);

		xmldoc.GetChildValue("giftVer", giftVer);
		xmldoc.GetChildValue("gift_vod", gift_vod);
		xmldoc.GetChildValue("sRoomAccess", sRoomAccess);



	}


	void equal(ParterInfo &info)
	{
		partnerID			= info.partnerID;
		username			= info.username;
		partnerName			= info.partnerName;
		domainName			= info.domainName;		
		domainNameEx		= info.domainNameEx;
		moneyName			= info.moneyName;			
		lastUpdate			= info.lastUpdate;

		newUserPresent		= info.newUserPresent;		
		receiverRatio		= info.receiverRatio;		
		companyTaxRatio		= info.companyTaxRatio;	
		roomHostTaxRatio	= info.roomHostTaxRatio;	
		prizePoolRatio		= info.prizePoolRatio;		
		broadCasePrice		= info.broadCasePrice;

		prize_recv_ratio	= info.prize_recv_ratio;
		prize_comp_ratio	= info.prize_comp_ratio;
		prize_host_ratio	= info.prize_host_ratio;
		prize_pool_ratio	= info.prize_pool_ratio;

		prize_rate2			= info.prize_rate2;

		greate_present		= info.greate_present;		
		greate_disp_times	= info.greate_disp_times;
		globle_redpaper		= info.globle_redpaper;

		automic				= info.automic;					
		automic_start		= info.automic_start;		
		automic_end			= info.automic_end;		

		currPrizedRatio		= info.currPrizedRatio;
		prizeIncoming		= info.prizeIncoming;
		prizeOutgoing		= info.prizeOutgoing;
		roomAccess			= info.roomAccess;
		transTax			= info.transTax;


		lastMonthTax		= info.lastMonthTax;
		currMonthTax		= info.currMonthTax;
		presentOnMicTimelimit	= info.presentOnMicTimelimit;
		presentOnMicPerMin	= info.presentOnMicPerMin;

		giftVer				= info.giftVer;
		gift_vod			= info.gift_vod;
		sRoomAccess			= info.sRoomAccess;
	}
	template <class T>
	void BuildPacketForClient(T &out)
	{
		out <<	partnerID;
		if (domainName.length())
			out << domainName;
		else
			out << domainNameEx;
		out << 	greate_disp_times;
		out <<  broadCasePrice;
		out <<	roomAccess;
		out <<	transTax;
		out <<	presentOnMicTimelimit;
		out <<	presentOnMicPerMin;
		out <<	moneyName;
	}
	template <class T>
	void BuildPacket(T &out)
	{
		out << 	partnerID;			
		out << 	username;			
		out << 	partnerName;		
		out <<	domainName;			
		out << 	moneyName;			
		out <<	lastUpdate;

		out << 	newUserPresent;		
		out << 	receiverRatio;		
		out << 	companyTaxRatio;	
		out << 	roomHostTaxRatio;	
		out << 	prizePoolRatio;		
		out <<  broadCasePrice;

		out << 	greate_present;	
		out << 	greate_disp_times;	

		out << 	automic;				
		out << 	automic_start;		
		out << 	automic_end;		

		out << 	currPrizedRatio;
		out <<	prizeIncoming;
		out	<<	prizeOutgoing;

		out <<	roomAccess;
		out <<	transTax;

		out << lastMonthTax;
		out << currMonthTax;

		out << presentOnMicTimelimit;
		out << presentOnMicPerMin;

		out << prize_recv_ratio;
		out << prize_comp_ratio;
		out << prize_host_ratio;
		out << prize_pool_ratio;

		out << prize_rate2;

		out << domainNameEx;
		
		out << giftVer;
		out << gift_vod;
		out << sRoomAccess;
		out << status;
	}

	template <class T>
	void ClientParsePacket(T &in)
	{
		in >>	partnerID;
		in >> 	domainName;
		in >> 	greate_disp_times;
		in >>	broadCasePrice;
		in >>	roomAccess;
		in >>	transTax;
		in >>	presentOnMicTimelimit;
		in >>	presentOnMicPerMin;
		in >>   moneyName;

	}


	template <class T>
		void ParsePacket(T &in)
	{
		in >> partnerID;			
		in >> username;			
		in >> partnerName;		
		in >> domainName;			
		in >> moneyName;
		in >> lastUpdate;


		in >> newUserPresent;		
		in >> receiverRatio;		
		in >> companyTaxRatio;	
		in >> roomHostTaxRatio;	
		in >> prizePoolRatio;
		in >> broadCasePrice;

		in >> greate_present;		
		in >> greate_disp_times;	

		in >> automic;				
		in >> automic_start;		
		in >> automic_end;		

		in >> currPrizedRatio;		
		in >> prizeIncoming;
		in >> prizeOutgoing;

		in >> roomAccess;
		in >> transTax;

		in >> lastMonthTax;
		in >> currMonthTax;

		in >> presentOnMicTimelimit;
		in >> presentOnMicPerMin;

		in >> prize_recv_ratio;
		in >> prize_comp_ratio;
		in >> prize_host_ratio;
		in >> prize_pool_ratio;

		in >> prize_rate2;
		 
		in >> domainNameEx;

		in >> giftVer;
		in >> gift_vod;
		in >> sRoomAccess;
		in >> status;
	}

};



class TinyUserInfo
{
	typedef union TinyUserKey
	{
		uint32 pid;												//�̼�id
		uint32 uin;												//�û�id
		uint64 userKey;											//����key
	}TinyUserKey;
public:
	TinyUserKey uid;											//�û��ɣ�
	string passwd;												//password
	uint8 face;													//ͷ��
	string nickname;											//�ǳ�
	string province;											//ʡ��
	uint8 auth;													//���������֤��ʽ 0, ����Ҫ��֤; 1��Ҫ��֤;2�������κ������
	uint32 oldMsgID;											//��ȡ��ϢID											
	uint8 gender;												//�Ա�
	uint8 age;													//����
	string city;												//����
	string country;												//����
	string email;												//�����ַ
	uint32 onlinetimes;											//������ʱ��
	uint8 locked;												//�ʺ��Ƿ�����
	uint8 hide;													//�Ƿ�����

	string address;												//��ַ
	string zipcode;												//�ʱ�
	string tel;													//�绰
	string name;												//����
	uint8 blood;												//Ѫ��
	string college;												//ѧУ
	string profession;											//ְҵ
	string homepage;											//������ҳ
	string intro;												//���˽���
	uint8 level;												//��Ա����0, ��ͨ�û� 1�ͻ�2�л�3�߻�4�׽��Ա
	uint16 LevelEndtime;										//��Ա����ʱ��
	uint8 lordLevel;											//�û���λ
	uint16 customFace;											//�Զ���ͼ��
	uint32 promoteid;											//�ƹ���ID

	uint64 money;												//�û��ʽ�
	uint64 received;											//�û������ʻ����
	uint8 accountStatus;										//�û��ʽ��ʻ�״̬
	uint8  flowinout;											//�ʽ��������



	template <class T>
		void BuildPacket(T &out)
	{
		out << uid.pid << uid.uin << passwd << face << nickname << province << auth << oldMsgID << gender << age << city << country;
		out << email <<  onlinetimes << locked << hide;
		out << address << zipcode << tel << name << blood << college << profession << homepage;
		out << intro << level << LevelEndtime << lordLevel << customFace;

		out << money << received << accountStatus << flowinout;
	}

	template <class T>
		void ParsePacket(T &in)
	{
		in >> uid.pid >> uid.uin >> passwd >> face >> nickname >> province >> auth >> oldMsgID >> gender >> age >> city >> country;
		in >> email >>  onlinetimes >> locked >> hide;
		in >> address >> zipcode >> tel >> name >> blood >> college >> profession >> homepage;
		in >> intro >> level >> LevelEndtime >> lordLevel >> customFace;

		in >> money >> received >> accountStatus >> flowinout;
	}
};



#pragma pack()

class VipLevel
{
private:
	VipLevel(){};
public:
	enum{
		NOT_VIP,
		JUNION_VIP,
		MIDDLE_VIP,
		HIGHER_VIP,
		GOLD_VIP,										//�׽�VIP
		DIAMOND_BLACK_VIP,								//����VIP
		DIAMOND_RED_VIP,								//����VIP
		DIAMOND_YELLOW_VIP,								//����VIP
		DIAMOND_GREEN_VIP,								//����VIP
		DIAMOND_BLUE_VIP,								//����VIP
		DIAMOND_PINK_VIP,								//����VIP
		DIAMOND_PURPLE_VIP,								//����VIP 
		DIAMOND_COLOUR_VIP,								//����VIP
		LIMIT_VIP
	};
	static string GetLevelName(uint8 nlevel)
	{
		string levelname = "��Ա";
		switch (nlevel)
		{
		case  VipLevel::NOT_VIP:
			levelname = "�ǻ�Ա";
			break;
		case VipLevel::JUNION_VIP:
			levelname="������Ա";
			break;
		case VipLevel::MIDDLE_VIP:
			levelname = "�м���Ա";
			break;
		case VipLevel::HIGHER_VIP:
			levelname = "�߼���Ա";
			break;
		case VipLevel::GOLD_VIP:
			levelname = "�׽��Ա";
			break;
		case VipLevel::DIAMOND_BLACK_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_RED_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_YELLOW_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_GREEN_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_BLUE_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_PINK_VIP:
			levelname = "�����Ա";
			break;
		case VipLevel::DIAMOND_PURPLE_VIP:
			levelname = "�����Ա";
			break;
		case  VipLevel::DIAMOND_COLOUR_VIP:
			levelname = "�����Ա";
			break;
		}
		return levelname;
	}
};


/************************************************************************/
/*                   ������վ�������ڵ�URL                         */
/************************************************************************/
enum REQ_URL_ROOMTYPE
{
	URL_VIDEOROOM,				//��Ƶ����Ĵ���
	URL_GAMEROOM,
	URL_SELF,
	URL_MANGER,					//��վ�����̨
};
class IM_UIN
{
private:
	IM_UIN();
public:
	enum RANGE
	{
		SYSTEM_UIN = 10000,			//ϵͳ����
		SERVICE_UIN = 10001,		//�ͷ���
	};
};


class BlockType
{
public:
	enum 
	{
		BLOCK_TYPE_UIN	= 0,										//���뱻����
		BLOCK_TYPE_IP,												//IP������
		BLOCK_TYPE_MAC,												//����������
	};
};

class CWingPCInfo
{
public:
	CWingPCInfo()
	{
		Reset();
	};
	void Reset()
	{
		m_sPCMacID = "";
		m_nWingMac = 0;
		m_diskSerNum = "";
		m_sBoardSerNum = "";
		m_sCpuID = "";
		m_sBiosSerNum = "";
	}
	string	m_sPCMacID;
	uint64	m_nWingMac;
	string  m_diskSerNum;
	string	m_sBoardSerNum;
	string  m_sCpuID;
	string	m_sBiosSerNum;

};


enum MAC_PRESENT_MONEY_STATE
{
	MAC_PRESENT_GET_OK,				//������ ��ȡ�ɹ�
	MAC_PRESENT_TIMEOUT,			//������ ����״̬
	MAC_PRESENT_GOT,				//������ �Ѿ���ȡ״̬
	MAC_PRESENT_FAILED,				//������ ��ȡʧ��
	MAC_PRESENT_READY,				//������ �ȴ���ȡ״̬
};


class MonitorServerType
{
public:
	enum 
	{
		SERVER_TYPE_IM,
		SERVER_TYPE_IM_PROXY,
		SERVER_TYPE_ROOM,
		SERVER_TYPE_ROOM_PROXY,
        SERVER_TYPE_MEDIA,
	};
};

class ServerMonitorCmd
{
public:
	enum
	{
		//IM���
		IM_SERVER_RUN_STATUS_MONITOR,
		IM_SERVER_USER_LOGIN_OR_LOGTOU,//ͳ���û���¼�����˳�
		IM_SERVER_USER_PRESENT_GIFT,		//ͳ���û�����Ϣ�����������
		IM_PROXY_CONNECT_STATUS,			//��ش����IM֮�������״̬
		//�������
		ROOM_SERVER_RUNSTATUS_MONITOR = 0x500,
	};
};

class MonitorVer
{
public:
	enum
	{
		MONITOR_VER_1 = 1,
	};
};

class UserLogoutType
{
public:
	enum
	{
		MONITOR_USER_REQ_LOGOUT = 1,//�û���������
		MONITOR_USER_FOURCE_OFFLINE,//�û���ǿ������
		MONITOR_USER_OTHRE_LOGIN_OFLINE,//�û��������ط�������
		MONITOR_USER_KPTO_OFFLINE,		//�û�����.

		MONITOR_USER_LOGOUT = 400,//���û��,�������Щ�����Ľӿ���

	};
};


class MD_cmd
{
public:
	enum
	{
		//Ҫͳ�ƺ�ʱ��api
		MD_IM_LOG_IN = 0,	// ��¼��ʱcmd
		MD_GET_URL,		//get url��ʱcmd
		MD_GET_CONTACTLIST,	//��ȡ�����б��ʱcmd 
		MD_GET_ROOM_ADDR,		//��ȡ����ip port��ʱcmd
		MD_NET_ERRO = 0x20,	//��·����cmd
		MD_KEEPALIVE_DELAY, //keepalive ��ʱ
		MD_DETECT_IP,		//̽���½���ʱ
		MD_MISS_PACKET,		//������
	};
};

class TuiboReviewType
{
public:
	enum
	{
		TUIBO_REVIEW_DING = 0,      //���Ʋ�
		TUIBO_REVIEW_PINGLUN,   //�����Ʋ�
		TUIBO_REVIEW_HUIFU,	    //�ظ�����
	};
};


#endif

