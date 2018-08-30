#ifndef CACHEDEFINE_SLDKFJSLDFJSLDKFLSDFJSD
#define CACHEDEFINE_SLDKFJSLDFJSLDKFLSDFJSD
#include "include/xmlconfig.h"
#include <string>
#include "include/icqtypes.h"
#include "include/log.h"

using namespace std;

enum
{
	CACHE_TCP_VER = 1
};

enum
{
	DBHANDLE_SUCCESS = 0x0001,									//�����ɹ�
	DBHANDLE_FAILED,											//����ʧ��
	DBHANDLE_WRONG_PASSWD,
	DBHANDLE_NOT_FIND_ROOM,

	DBH_INVALID_UIN,
};

enum 
{
	CHECKUSER_SUCCESS = 0x0001,
	CHECKUSER_FAILED,
	CHECKUSER_INVALID_UIN,
	CHECKUSER_WRONG_PASSWD,
	CHECKUSER_NO_MEMBER,
	CHECKUSER_BLOCKED,											//������������
	CHECKUSER_NEEDPAY,											//��Ҫ֧��
	CHECKUSER_PAYFAILED_INGAME,									//����ʧ��,��ǰ����Ϸ��
	CHECKUSER_PAYFAILED_NOENOUGH,								//����ʧ��,����
	CHECKUSER_NEEDPAYBUTFAILED,									//����ʧ��
	CHECKUSER_NOTCLASSMEMBER,									//�ǰ༶��Ա,�����԰༶��Ա��ݽ���
	CHECKUSER_NOT_SUBSCRIBER,									//�Ƿ��������û�
	CHECKUSER_INGAME,											//��ǰ����Ϸ����
	CHECKUSER_BLOCK_IP,											//�ɣб�����
	CHECKUSER_BLOCK_MAC,										//MAC������
	CHECKUSER_BLOCK_UIN,										//UIN������

	CHECKROOM_SUCCESS = 0x0100,
	CHECKROOM_INVAILD_ROOM,  	
	CHECKROOM_WRONG_PASSWD,	
};

enum {
	CACHE_TCPSRV_LOGIN = 0x0001,
	CACHE_TCPSRV_LOGOUT,
	CACHE_TCPSRV_KEEPALIVE,

	CACHE_IM_GET_BLACKLIST			= 0x0100,					//��ȡ��վ������


	CACHE_IM_NEWUIN = 0x0150,									//�����û�
	CACHE_IM_USER_LOGIN,
	CACHE_IM_OFFLINE,
	CACHE_IM_INSERT_ONLINE,
	CACHE_IM_CLEAR_MEM_CACHE,									//�����û�����



	CACHE_IM_SEARCHSERVICE			= 0x0200,
	CACHE_IM_SEARCHSECTION,
	CACHE_IM_SEARCHUIN,
	CACHE_IM_SEARCHCUSTOM,
	CACHE_IM_QUERYAUTH,

	CACHE_IM_CONTACTLIST			= 0x250,
	CACHE_IM_ADDFRIEND,
	CACHE_IM_DELFRIEND,
	CACHE_IM_DELADDFRIEND,
	CACHE_IM_GET_MYFRIEND,
	CACHE_IM_GET_ADDFRIEND,
	CACHE_IM_DELFRIENDMYANDADD,



	CACHE_IM_MODIFY_USERINFO		= 0x300 ,
	CACHE_IM_GET_MONEY,
	CACHE_IM_UPDATEPASSWD,
	CACHE_IM_UPDATE_ONLINETIME,
	CACHE_IM_GET_CONTACT,
	CACHE_IM_UPDATE_BLOCK,										//���·���������Ϣ


	CACHE_IM_GET_OFFLINEMSG			= 0x0350,
	CACHE_IM_GETBCMSG,
    CACHE_IM_GETOFFLINE_BCMSG,
	CACHE_IM_GET_OFFLINEPOPUPMSG,
	CACHE_IM_INS_OFFLINEMSG,
	CACHE_IM_INSERT_POPUPMSG,



	CACHE_IM_GET_ROOM_ADDR			= 0x0400,
	CACHE_IM_ADDFAVROOM,										//�ղ�Ⱥ
	CACHE_IM_DELFAVROOM,										//ȡ���ղ�
	CACHE_IM_GET_FAVROOM,										//��ȡ�ҵ��ղط���

	CACHE_IM_PRESENT_MONEY					= 0x0450,
	CACHE_IM_MONEY_TRANSFER,
	
	CACHE_ROOM_GET_SERVERINFO		= 0x0500,					//��ȡ������Ϣ
	CACHE_ROOM_GET_SUPPERMANAGER,								//��ȡ���г����б�
	CACHE_ROOM_ROOMINFO,
	CACHE_ROOM_MODIFYINFO,										//�޸ķ���
	CACHE_ROOM_MODIFYPASS,										//�޸�����
	CACHE_ROOM_CHANGE_STATUS,									//���ÿ���
	CACHE_ROOM_CHG_USER_NUM,									//�޸�
	CACHE_ROOM_UPDATE_ONLINETIME,								//�����û��ڷ���ʱ��
	CACHE_ROOM_USER_AUTH,										//�û�������֤
	CACHE_ROOM_ADDBLACK,										//��Ӻ�����
	CACHE_ROOM_USEGIFT,
	CACHE_ROOM_LOAD_PRIZE_INFO,									//��ȡ˰�ա��н��ܶ�
	CACHE_ROOM_BUY_GLOBLE_MSG,									//����С�԰ȷ���
	CACHE_ROOM_LOAD_RICH_INFO,									//��ȡ��������
	CACHE_ROOM_FORBID_CHAT,										//�����û�
	CACHE_ROOM_LOG_ONMIC,										//��¼�û��������
	CACEH_ROOM_GET_ENTERINFO,									//��ȡ���뷿��
	CACEH_ROOM_GET_ACL,											//��ȡȨ���б�
	CACEH_ROOM_MODIFY_MGR,										//�޸Ĺ���Ա
	CACEH_ROOM_LOAD_ANDROID,									//��ȡ������
	CACHE_ROOM_ROOMINFO_XML,									//��xml���ط�����Ϣ
	CACHE_ROOM_GIFT_INFO,										//��ȡ������ϸ��Ϣ
	CACHE_ROOM_USER_AUTH_XML,									//�����½���أ̷ͣ���
	CACHE_ZHUANZHUAN_USER_AUTH,									//תת�����½��Ϣ
	CACHE_ROOM_SAVE_BROADCAST,									//����ȫվ�㲥�򷿼�㲥
	CACHE_ROOM_MIC_PRESENT,										//������������
	CACHE_ROOM_STAMP_INFO,										//ȡӡ����Ϣ
	CACHE_ROOM_USEGIFT_LIST,									//����ˢ��
	CACHE_ROOM_USE_STAMP,										//�û�֮�����
	CACHE_ROOM_ERASE_STAMP,										//�û�֮�����


	CACHE_ROOM_ZZ_BET				= 0x550,					//תתѺע	
	CACHE_ROOM_ZZ_AWARD,										//תת����
	CACHE_ROOM_ZZ_SETTING,										//Ѻע������Ϣ
	CACHE_ROOM_ZZ_HISTORY,										//������ʷ
	CACHE_ROOM_ZZ_ITEMS_NAME,									//������������
	CACHE_ROOM_ZZ_SETTING2,										//������
	CACHE_ROOM_ZZ_BET_TAX,										//˰��Ѻע
	CACHE_ROOM_ZZ_POOL,											//תת����l
	
	CACHE_IM_PARTNER_INFO			= 0x600,					//������������Ϣ										
	CACHE_IM_PARTNER_LIST,										//������������Ϣ
	CACHE_IM_PARTNER_INFO_XML,									//
	CACHE_IM_PARTNER_LIST2,										//��ȡ�������б�
	CACHE_IM_PARTNER_INFO_XML_FORIM,							//��ȡ��������ϸ��Ϣ

	CACHE_NOTIFY_GET_NEW_ITEM		= 0x700,					//webnotify��ȡ���µ���Ϣ
	CACHE_NOTIFY_DONE_ITEM,										//webnotify������һ��
	CACHE_NOTIFY_OTHER,											//֪ͨ��������
	CACHE_NOTIFY_OTHER2,											//֪ͨ��������
	CACHE_DEF_END,
};


enum
{
	HDL_SUCCESS = 0x01,
	HDL_FAILED,
	HDL_WRONG_PASSWD,
	HDL_DB_ERROR,
	HDL_NO_FIND_FLOCK,


	HDL_QUITFLOCK_HASOUT,
	HDL_QUITFLOCK_ISOWNER,

	HDL_DRAGFLOCK_NORIGHT,
	HDL_DRAGFLOCK_HASMEMBER, 
	HDL_DRAGFLOCK_FLOCKISFULL,
	HDL_DRAGFLOCK_TOOMANYFLOCK,

	HDL_PUSHFLOCK_OWNNOTIN,
	HDL_PUSHFLOCK_OPPNOTIN,
	HDL_PUSHFLOCK_NORIGHT,
	
	HDL_ACCEPTFLOCK_NORIGHT,
	HDL_ACCEPTFLOCK_OWNNOTIN,
	HDL_ACCEPTFLOCK_TOOMANYMEMBER,
	HDL_ACCEPTFLOCK_TOOMANYFLOCK,

	HDL_INVALID_UIN,
	HDL_LOGIN_LOCKED,

	HDL_HUAZHANG_IN_GAME,
	HDL_HUAZHANG_OPP_IN_GAME,

	HDL_LOGIN_NEEDNEWVCODE,
	HDL_LOGIN_NEEDOLDVCODE,
	HDL_LOGIN_INVALIDVCODE,
	HDL_WRONG_VCODE,
	HDL_WRONG_VCODE_OVERTIME,

	HDL_USEGIFT_INGAME,
	HDL_USEGIFT_OPPINGAME,
	HDL_USEGIFT_NOENOUGHMONEY,													//Ǯ����

	HDL_JOINFLOCK2_HASIN,		
	HDL_JOINFLOCK2_TOOMANYFLOCK,
	HDL_JOINFLOCK2_TOOMANYMEMBER,
	HDL_JOINFLOCK2_REQAUTH,
	HDL_JOINFLOCK2_REFUSE,
	HDL_JOINFLOCK2_NEEDPAY,
	HDL_JOINFLOCK2_INGAME,
	HDL_JOINFLOCK2_NOENOUGHMONEY,

	HDL_QUITFLOCK2_HASOUT,
	HDL_QUITFLOCK2_ISOWNER,

	HDL_PUSHFLOCK2_OPPISSUPERMGR,								//�Է��ǳ���
	HDL_PUSHFLOCK2_ISNOTOWNER,									//������	
	HDL_PUSHFLOCK2_OPPISOWNER,									//�Է�������	
	HDL_PUSHFLOCK2_OPPHASOUT,									//�Է��Ѿ�����Ⱥ
	HDL_PUSHFLOCK2_NORIGHT,										//��Ȩ
	HDL_PUSHFLOCK2_INCHARGEROOM,								//�շѷ��䲻������

	HDL_HUAZHANG_NOTENOUTHMONEY,								//��������

	HDL_ADDFRIEND_HASADD,										//�Ӻ���-�Ѽ�
	HDL_ADDFRIEND_TOOMANYFRIEND,								//�Ӻ���-�ҵĺ���̫��
	HDL_ADDFRIEND_OPP_TOOADDMYFRIEND,							//�Ӻ���-̫����Һ���
	HDL_ADDFRIEND_REFUSE,										//�Ӻ���-�ܾ���Ϊ����
	HDL_ADDFRIEND_NEEDAUTH,										//�Ӻ���-��Ҫ��֤	
	
	HDL_ACCEPTADDFRIEND_OPP_HASADD,								//����Ӻ���-�Ѿ��ǶԷ�������
	HDL_ACCEPTADDFRIEND_OPP_TOOMANYFRIEND,						//����Ӻ���-�Է���̫�������
	HDL_ACCEPTADDFRIEND_TOOADDMYFRIEND,							//����Ӻ���-���Ѿ���̫����Ѽӹ���
	HDL_ACCEPTADDFRIEND_OPP_INVALIDREQ,							//����Ӻ���-�Է��������Ѿ����ڻ򲻴���

	HDL_ADDGROUP_TOOGROUP,										//����̫�����
	HDL_UPDATECONTACT_NONEW,									//������ϵ��,û�и��µ���Ϣ
	HDL_OTHER_DEVICE_LOGIN,						//�������豸��¼������ƶ��ˣ�
	HDL_ERROR_USER_LAST_SCAN,					//���һ����ɨ���¼
	HDL_ERROR_USER_LAST_ACCREDIT,						//���һ������Ȩ��¼
};

class DBCacheInfo {
public:
	uint32			commtimeout;
	uint32			kpalivetimeout;
	string			host;
	uint16			port;
	uint32			connid;
	string			passwd;
	uint16			connnum;	

	bool operator == (const DBCacheInfo &u)
	{
		return (commtimeout == u.commtimeout && kpalivetimeout == u.kpalivetimeout && 
			host == u.host && port == u.port && connid == u.connid && passwd == u.passwd &&
			connnum == u.connnum);
	}

	bool operator != (const DBCacheInfo &u)
	{
		return (commtimeout != u.commtimeout || kpalivetimeout != u.kpalivetimeout || 
			host != u.host || port != u.port || connid != u.connid || passwd != u.passwd ||
			connnum != u.connnum);
	}
	void operator = (const DBCacheInfo &u)
	{
		commtimeout = u.commtimeout;
		kpalivetimeout = u.kpalivetimeout ; 
		host = u.host;
		port = u.port;
		connid = u.connid;
		passwd = u.passwd;
		connnum = u.connnum;
	}

	void LoadSetting(WingUtil::CXmlConfig &xml)
	{
		xml.ResetPos();

		if (!xml.FindElem("cache"))
			return;

		host = xml.ReadString( "host" );
		port = xml.Readuint16( "port" );
		connnum = xml.Readuint16( "connnum", 10 );

		connid = xml.ReadInt( "connid", 10000);
		passwd = xml.ReadString( "passwd", "123456" );
		commtimeout = xml.ReadInt( "commtimeout", 120 );
		kpalivetimeout = xml.ReadInt( "kpalivetimeout", 20 );
	}

	void DisplaySetting(void)
	{
		LOG(4)("\n");
		LOG(4)("Cache server = %s:%d\n", host.c_str(), port);
		LOG(4)("Cache connect id = %d, password = %s\n", connid, passwd.c_str());
		LOG(4)("Cache connections num = %d\n", connnum);
		LOG(4)("Cache connect timeout = %d\n", commtimeout);
		LOG(4)("Cache keepalive timeout = %d\n", kpalivetimeout);
	}
};


#endif
