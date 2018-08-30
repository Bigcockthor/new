#pragma once

#include <string>
#include "include/icqtypes.h"
#include "include/Markup.h"
#include "include/xmlconfig.h"
#include "include/log.h"

using namespace std;

enum
{
	MSGSWITCH_CLI_VER = 1
};

enum
{
	MSGSWITCH_CMD_KEEPALIVE = 0x0001,
	MSGSWITCH_CMD_ACK = 0x0002,

	MSGSWITCH_CMD_LOGIN = 0x0003,
	MSGSWITCH_CMD_LOGOUT = 0x0004,

	MSGSWITCH_CMD_SENDMESSAGE = 0x0005,
	MSGSWITCH_CMD_IMCMSG	 = 0x0006,
};

/*���󷽷��ͽ�����Typeֵ*/
enum
{
	MSGSWITCH_TYPE_REQ = 0x0001,
	MSGSWITCH_TYPE_RES = 0x0002,
};

enum
{
	MSGSWITCH_HDL_SUCCESS = 0x0001,					//�����ɹ�
	MSGSWITCH_HDL_FAILED,							//����ʧ��
	MSGSWITCH_HDL_WRONG_PASSWD,
};

enum
{
	MSGSWITCH_LOGON_SUCCESS		= 0x0001,
	MSGSWITCH_LOGON_WRONGPASS = 0x0002,
	MSGSWITCH_LOGON_NOID			= 0x0003,
	MSGSWITCH_LOGON_FAILED			= 0x0004,
};


enum {
	UDP_MAN_ACK					= 0x0000,
	UDP_MAN_CHANGE_PASS			= 0x0001,
	UDP_MAN_CREATE_FLOCK		= 0x0002,
	UDP_MAN_DISBAND_FLOCK		= 0x0003,
	UDP_MAN_ADD_MEMBER			= 0x0004,
	UDP_MAN_DEL_MEMBER			= 0x0005,
	UDP_MAN_NEW_BCMSG			= 0x0006,
	UDP_MAN_FLOCK_LIST			= 0x0007,

	UDP_MAN_TENROOM_KICKOUT		= 0x0019,						//ʮ�˷�������
	UDP_MAN_NEW_IMBCMSG			= 0x001A,						//IM�㲥

	UDP_MAN_HDR_ADDMGR          = 0x0020,   					//��ӹ���Ա
	UDP_MAN_HDR_DELMGR          = 0x0021,   					//ɾ������Ա
	UDP_MAN_HDR_MODIFYINFO      = 0x0022,   					//�޸ķ�������
	UDP_MAN_HDR_BLACKLIST       = 0x0023,   					//������
	UDP_MAN_DESTORYROOM			= 0x0024,						//��������

	UDP_MAN_ADDBLACKITEM		= 0x0029,						//IM��Ӻ�����
	UDP_MAN_DELBLACKITEM		= 0x002C,						//IMɾ��������
	UDP_MAN_FORCEOFFLINE		= 0x0030,

	UDP_MAN_UPDMONEY			= 0x0032,						//����֪ͨ�ʽ�
	UDP_MAN_UPDFLOCK			= 0x0033,						//���·���

	UDP_MAN_ADDSUPERMAN			= 0x0035,						//��ӳ���
	UDP_MAN_DELSUPERMAN			= 0x0036,						//ɾ������

	UDP_MAN_NOTIFYNEWMONEY		= 0x003D,						//֪ͨ���µ��ʽ�
	UDP_MAN_POPUPMSG			= 0x003E,						//֪ͨ���µĵ�����Ϣ
	UDP_MAN_USER_CLEAR_CACHE	= 0x003F,						//֪ͨ�����û���̨����Ȩ��



	UDP_MAN_IMMESSAGE			= 0x0040,						//Im��Ϣ
	UDP_MAN_PARTNER_UPDATE		= 0x0041,						//����������ø���
	UDP_MAN_GLOBLE_MSG,											//ȫ������
	UDP_MAN_GLOBLE_MSG2,										//��������
	UDP_MAN_GLOBLE_MSG3,										//ȫ��ϵͳ�԰�
	UDP_MAN_GENERAL_MSG,										//ȫ��ϵͳ�԰�
	UDP_MAN_DISTRIBUTE_REDPAPER,								//�ַ������Ϣ
	UDP_MAN_ACQUIRE_REDPAPER,									//��ú����Ϣ
	UDP_MAN_NOTIFY_REDPAPER,									//֪ͨ�������Ϣ
	UDP_MAN_OUTOFDATE_REDPAPER,									//���ں����Ϣ
	UDP_MAN_NOTIFYFORCEOFFLINE,									//ǿ������֪ͨ
	UDP_MAN_MODIFYMGRINFO,										//�޸Ĺ���
	UDP_MAN_FORMAL_OPERATION,									//��ʽ��Ӫ֪ͨ
	UDP_MAN_SUIBO_FORCE_END,									//�沥ǿ�ƹر�
	UDP_MAN_SUIBO_MSG,											//�沥�ƹ���Ϣ //����
	UDP_MAN_SUIBO_OWN_MSG,										//�沥����֪ͨ������Ϣ
	UDP_MAN_NOTIFY_MSG,											//�ƹ���Ϣ���
	UDP_MAN_NOTIFY_BLOCK,										//�沥����֪ͨ
	UDP_MAN_PPC_AWARD_MSG,										//�����н���Ϣ
	UDP_MAN_SUIBO_ROOM_BROADCAST2,                              //�沥����㲥��1������2��������web��̨
	UDP_MAN_WEEKSTAR_CHANGE,									//���Ǳ��֪ͨ//����
	UDP_MAN_DIAMON_UPDATE,										//��ʯ����
	UDP_MAN_DIAMONRECV_UPDATE,									//��ʯ������
	UDP_MAN_ANYCAST_NEW_BROADCAST,								//�沥�¹㲥��Ϣ
	UDP_MAN_SUIBO_MSG_NEW,										//�沥�ƹ���Ϣ ����
	UDP_MAN_SUIBO_OWN_MSG_NEW,									//�沥����֪ͨ������Ϣ
	UDP_MAN_ANYCAST_ACTIVE_UPDATE,								//�����
	UDP_MAN_ANYCAST_LEVEL_CHANGE,								//�ȼ�����֪ͨ
	UDP_MAN_ANYCAST_ONFOCUS,									//ֱ�����й�ע֪ͨ
	UDP_MAN_ANYCAST_ONFOCUS_SHARE,								//�����д����Ĺ�ע
	UDP_MAN_ANYCAST_SHARE_VIEWER,								//���ڷ�������
	UDP_MAN_ANYCAST_UPDATEVER,									//�޸İ汾��
	UDP_MAN_ANYCAST_SHAREEXP,									//���������
	


	UDP_MAN_MEDIA_CREATEROOM	= 0x0100,						//GTS��������
	UDP_MAN_MEDIA_DESTROYROOM	= 0x0101,						//GTS���ٷ���
	UDP_MAN_MEDIA_MICLIST		= 0x0102,						//GTS����б�
	UDP_MAN_MEDIA_CHECKROOM		= 0x0103,						//GTS��鷿��
	UDP_MAN_MEDIA_LOGOUTUSER	= 0x0104,						//Gts�û��˳�
	UDP_MAN_MEDIA_CHECKROOM2	= 0x0105,						//GTS��鷿��

	UDP_MAN_WEB_USER			= 0x0200,						//web�û���������Ϣ
	UDP_MAN_WEB_CHATTEXT,										//web������Ϣ
	UDP_MAN_WEB_VIEWSTATE,										//ֱ��״̬


	//cocר�÷��䲻���ظ�
	UDP_MAN_COC_SYS_MSG = 200,									//��Ϸϵͳ��Ϣ
	UDP_MAN_COC_MAIL_MSG,										//��Ϸ�ʼ���Ϣ
	UDP_MAN_COC_CHALLENG_NOTIFY,								//��ս��֪ͨ
	UDP_MAN_COC_DISCOUNT,										//����֪ͨ
	UDP_MAN_COC_BUY_GEMSTONE,									//����ʯ֪ͨ

	UDP_MAN_BIGROOM_UPDATE_ACT		= 0x300,					//Ȩ�ޱ��
	UDP_MAN_BIGROOM_UPDATE_PARTNER,								//��������Ϣ���
	UDP_MAN_BIGROOM_UPDATE_GIFT,								//������Ϣ�䶯
	UDP_MAN_BIGROOM_UPDATE_DIAMON,								//��ʯ��������
	UDP_MAN_BIGROOM_UPDATE_BOX,									//����������
	UDP_MAN_BIGROOM_UPDATE_REDCONF,								//�������
	UDP_MAN_BIGROOM_UPDATE_REDSTATE,							//���������
	UDP_MAN_BIGROOM_UPDATE_SIEGEGIFT,							//���¹���������Ϣ
	UDP_MAN_BIGROOM_WEEKSTAR_CHANGE,							//���Ǳ䶯֪ͨ
	UDP_MAN_BIGROOM_DAYRANK_UPDATE,								//�����е�һ���䶯֪ͨ

	UDP_MAN_YIYUAN_DUOBAO			= 0x400,					//һԪ�ᱦȫվ�н���Ϣ
};

struct MsgSwitchInfo
{
public:
	MsgSwitchInfo()
	{
		port = 0;
		conn_id = 0;
		clientSvrID = 0;
		clientpid = 0;
		clientport = 0;
		conn_num = 0;
		keepalive_timeout = 0;
		waitkeepalive_timeout = 0;
		comm_timeout = 0;
		send_timeout = 0;
	}
	string				host;
	uint16				port;
	uint32				conn_id;
	string				conn_passwd;
	uint32				clientSvrID;
	uint16				clientpid;
	string				clienthost;
	uint16				clientport;
	uint32				conn_num;
	uint32				keepalive_timeout;
	uint32				waitkeepalive_timeout;
	uint32				comm_timeout;
	uint32				send_timeout;

	bool operator != (const MsgSwitchInfo &u)
	{
		return (host != u.host || port != u.port || 
			conn_id != u.conn_id || conn_passwd != u.conn_passwd || 
			clientSvrID != u.clientSvrID || clientpid != u.clientpid ||
			clienthost != u.clienthost || clientport != u.clientport ||
			conn_num != u.conn_num || keepalive_timeout != u.keepalive_timeout ||
			waitkeepalive_timeout != u.waitkeepalive_timeout || comm_timeout != u.comm_timeout||
			send_timeout != u.send_timeout);
	}

	void operator = (const MsgSwitchInfo &u)
	{
		host = u.host; port = u.port; 
		conn_id = u.conn_id; conn_passwd = u.conn_passwd; 
		clientSvrID = u.clientSvrID; clientpid = u.clientpid;
		clienthost = u.clienthost; clientport = u.clientport;
		conn_num = u.conn_num; keepalive_timeout = u.keepalive_timeout;
		waitkeepalive_timeout = u.waitkeepalive_timeout; comm_timeout = u.comm_timeout;
		send_timeout = u.send_timeout;
	}

	void LoadSetting(WingUtil::CXmlConfig &xml)
	{
		xml.ResetPos();

		if (!xml.FindElem("msgswitch"))
			return;

		host = xml.ReadString("host");
		port = xml.Readuint16("port", 7000);
		conn_id = xml.ReadInt("connid", 10000);
		conn_passwd = xml.ReadString("passwd", "123456");
		conn_num = xml.ReadInt("connnum", 1);
		clientSvrID = xml.ReadInt("clientsvrid", 0);
		clientpid = xml.Readuint16("clientpid", 400);
		clienthost = xml.ReadString("clienthost", "127.0.0.1");
		clientport = xml.Readuint16("clientport", 9000);
		comm_timeout = xml.ReadInt("commtimeout", 30);
		keepalive_timeout = xml.ReadInt("keepalivetimeout", 15);
		waitkeepalive_timeout = xml.ReadInt("waittimeout", 60);
		
		send_timeout = xml.ReadInt("sendtimeout", 2);
	}

	void DisplaySetting(void)
	{
		LOG(4)("\n");
		LOG(4)("Msg switch server = %s:%d\n", host.c_str(), port);
		LOG(4)("Msg switch connect id = %d, password = %s\n", conn_id, conn_passwd.c_str());
		LOG(4)("Msg switch connections num = %d\n", conn_num);
		LOG(4)("Msg switch connect clientSvrID = %d\n", clientSvrID);
		LOG(4)("Msg switch connect clientpid = %d\n", clientpid);
		LOG(4)("Msg switch client = %s:%d\n", clienthost.c_str(), clientport);
		LOG(4)("Msg switch connect conn_num = %d\n", conn_num);
		LOG(4)("Msg switch connect keepalive_timeout = %d\n", keepalive_timeout);
		LOG(4)("Msg switch connect waitkeepalive_timeout = %d\n", waitkeepalive_timeout);
		LOG(4)("Msg switch connect comm_timeout = %d\n", comm_timeout);
		LOG(4)("Msg switch connect send_timeout = %d\n", send_timeout);



	}

};
