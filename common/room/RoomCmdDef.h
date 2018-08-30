#ifndef ROOM_CMD_DEF_KDLFJSDLFJSDLFJDSF
#define ROOM_CMD_DEF_KDLFJSDLFJSDLFJDSF

enum 
{
	IM_CHAT_VER1		=	0,
	IM_CHAT_VER2		=	1,
	IM_CHAT_VER3		=	2,
	IM_CHAT_VER4		=	3,
	IM_CHAT_VER5		=   4,
	IM_CHAT_VER6		=	6,
	IM_CHAT_VER7		=   7,
	IM_CHAT_VER8		=   8,
	IM_CHAT_VER9		=   9,
	IM_CHAT_VER10		=   10,
	IM_CHAT_VER11		=   11,
	IM_CHAT_VER12		=   12,						//Э�������˾�λ��,
	IM_CHAT_VER13		=	13,						//������������˲�����,�Ľ��н���ʾ
	IM_CHAT_VER14		=	14,						//������ý���������ֻ�·�ý���������
	IM_CHAT_VER15		=	15,						//�������·�������Ϣʱ������ʱ,�û��б��ٴ��û�����Ϣ
	IM_CHAT_VER16		=	16,						//������������
	IM_CHAT_VER17		=   17,						//����ӡ�¹���
	IM_CHAT_VER18		=   18,						//������ѿ������
	IM_CHAT_VER19		=	19,						//������ʯ��Ա���µ����  2013-09-28
	IM_CHAT_VER20		=   20,						//����������Ϸ
	IM_CHAT_VER21		=   21,						//���ӵ�¼����desУ��
	IM_CHAT_VER22		=   22,						//����������
	IM_CHAT_VER23		=   23,						//�û��б������豸�����ֶΣ�����ʣ��ʱ���ֶ�
	IM_CHAT_VER24		=   24,						//���������շѱ���
	IM_CHAT_VER25		=	25,                     //�·�������汾�ţ����ϵ�����
	IM_CHAT_VER26		=   26,						//�޸�ȫ������Э���Լ��� ���ϵ�����������е���ʾ
	IM_CHAT_VER27		=	27,						//������Ϣ����nick
	IM_CHAT_VER28		=	28,						//������Ϣ���������ʱ
	IM_CHAT_VER30		=	30,						//��¼��������mic�����ֶ�
	IM_CHAT_VER31		=	31,						//��¼��������˽�󿪹�
	IM_CHAT_VER32		=	32,						//������ؽӿڵ���Ϊuint64
	IM_CHAT_VER33		=	33,
	IM_CHAT_VER34		=	34,						//���ӻ���
	IM_CHAT_VER35		=	35,						//�޸�rankΪuint16�ֶ�
	IM_CHAT_VER36		=	36,						//��ݼ���
	IM_CHAT_VER37		=   37,						//����б����
	IM_CHAT_VER38		=   38,						//rank uint32
	IM_CHAT_VER40		=	40,						//Ƥ����Ϣ �ͻ��˰汾
	IM_CHAT_VER41		=	41,						//������˽�������ID�������Ϊuint64����������·�����䳵������
	IM_CHAT_VER_CURR	=	IM_CHAT_VER38,			
	
	IM_CHAT_VERPROT		=	100,
	//IM_CHAT_VER_CURR	=	IM_CHAT_VER16, 
	IM_PPC_PROTO		=	200,					//ppcʹ��proto�汾��
};

class CChatMsgType
{
public:
	 enum ChatMsgType
	{
		ChatUinMsg,
		SystemMsg,
		ImportMsg,
		SystemUinMsg,
		UnitMsg,
		GiftChatUinMsg,
		ShowGiftName,
		ShowGift,
		PromptMsg ,
		BroadMsg,
		VipEnterMsg,
		WinPrizeMsg,
		ShowReceviedGift,
		ShowColorTip,
		ColorTip,
		Msg_Auto_Reply,//�Զ��ظ�����Ϣ
		ShowHtmlMsg,
		GneralMsg, //
		SystemWarmPromptMsg,
		ExpressionMsg,
	};
};


//������Ϸ
class CChatGameType
{
public:
	enum ChatMsgType
	{
		ChatDicing,		//������
	};
};


class RoomInfoItemStr
{
public:
	static std::string CHAT_PRIVATE_ACCESS;							//˽�������޸�
	static std::string CHAT_PUBLIC_ACCESS;							//���������޸�
};



typedef enum RoomType
{
	IMROOM_TYPE_SMALL			= 1,							//�У�����תС����
	IMROOM_TYPE_BIG				= 2,							//����Ƶ��ת�󷿼�
	IMROOM_TYPE_GAME_STAR		= 3,							//תת
	IMROOM_TYPE_GAME_POKER		= 4,							//
	IMROOM_TYPE_GAME_POKER_100	= 5,
	IMROOM_TYPE_BIG_3			= 6,                            //1��2С��Ƶ
	IMROOM_TYPE_BIG_3_SH		= 7,                            //3С����Ƶ
	IMROOM_TYPE_BIG_3_SV		= 8,							//3С����Ƶ
	IMROOM_TYPE_BIG_3_F			= 9,							//2��һ������Ƶ
	IMROOM_TYPE_BIG_3_NEW		= 10,                           //�¿���Ƶ����
	IMROOM_TYPE_GAME_BOX		= 11,							//��������Ϸ
	IMROOM_TYPE_GAME_RICHMAN	= 12,							//����
	IMROOM_TYPE_BIG_UC			= 13,
	IMROOM_TYPE_BIG_BIGONE		= 21,							//������
	IMROOM_TYPE_ANCHOR			= 22,							//��������
	IMROOM_TYPE_GUAGUA			= 23,							//���ɷ�������
	IMROOM_TYPE_GAME_COC        = 26,                           // COC��Ϸ
	IMROOM_TYPE_GAME_NEW_POKER  = 27,                           // �°泵��
	IMROOM_TYPE_GAME_REDPACKETS = 28,							//�����Ϸ
	IMROOM_TYPE_DIAMOND			= 29,							//��ʯ�ػ���������

	//�¼���Ϸroomtype��Χ����Ϊ100-200
	IMROOM_TYPE_GAME_BASE       = 100,
	IMROOM_TYPE_GAME_MAX        = 200,
}RoomType;

//��־�ɼ�
typedef enum EventID 
{
	//�����ڲ��¼�
	EV_LOGIN_ROOM = 0x100, //��¼����
	EV_LOGOUT_ROOM,      //�˳�����
	EV_BIND_MIC,		 //����
	EV_UNBIND_MIC,       //����
	EV_BIND_PRIVATE_MIC,//��˽��
	EV_UNBIND_PRIVATE_MIC,//��˽��
	EV_MIC_PRSENTR,       //��������
	EV_SENDGIT,          // ˢ������
	EV_DIG_GEM,          //�ڱ�
	EV_PRINT_GIFT_PRIZE_POOL,//ˢ������
	EV_PRINT_GEM_POOL,//�ڱ�����
	//DB�����¼�
	EV_LOGIN_ROOM_DB_RES = 0x200,
}EventID;
typedef enum KickOutType
{
	ROOM_KICKTYPE_KICKOUT		= 0,							//�߳�ȥ
	ROOM_KICKTYPE_PUSHOUT,										//����ȥ��
	ROOM_KICKTYPE_SVR_RELOGIN,									//������Ϣ�����仯���ͻ�����Ҫ�˳��ؽ���
	ROOM_KICKTYPE_ONLY_ALLOW_VIP,								//�������ѹ���ֻ����VIP�û�����ʹ��
	ROOM_KICKTYPE_ADDPID_BLACK,									//����վ�������	
	ROOM_KICKTYPE_FORCE_VIEWEND,								//ǿ�ƽ���ֱ��
	ROOM_KICKTYPE_KICKOUT_TABLE,								//�߳���ǰ��
	ROOM_KICKTYPE_NOENOUGH_MONEY,								//����
	ROOM_KICKTYPE_UPPER_TODAYLIMIT,								//�ﵽ���е��챻�߳�����
	ROOM_KICKTYPE_NOBET_TIMES,									//���û������ƣ��ﵽ����û��ע����

}KickOutType;

typedef enum RoomAuth
{
	ROOM_AUTH_ALLOW_ALL = 0,									//���������˽���
	ROOM_AUTH_ALLOW_AUTH,										//�������
}RoomAuth;

enum
{
	AWARD_STATUS_STOP,
	AWARD_STATUS_BETTING,										//��עʱ��
	AWARD_STATUS_WAITING,										//ȷ����ע��
	AWARD_STATUS_AWARDING,										//�ȴ�����ʱ��
	AWARD_STATUS_AWARDED,										//����
	AWARD_STATUS_AWARD_WAIT,									//�ٻ�����
};



enum
{
	REDPACKETS_STOP,		//ֹͣ״̬
	REDPACKETS_WAIT,		//�ȴ�״̬
	REDPACKETS_RUN,			//��Ϸ״̬
	REDPACKETS_END,			//���ֽ������ֿ�ʼ״̬
};

enum
{
	REDPACKETS_SUCCESS,			//����������ɹ�
	ROB_REDPACKETS_REPEAT,		//�Ѿ��������
	ROB_REDPACKETS_NOTENOUGH,	//����Ѿ�����
	ROB_REDPACKETS_EXPIRE,		//����Ѿ�����
	ROB_REDPACKETS_FAILED,		//�����ʧ��
	SEND_REDPACKETS_FILED,		//���ͺ��ʧ��
	SEND_NOTENOUGH_UIN,			//û���㹻����
	SEND_STATE_ERR,				//û�е����ͺ����״̬
	SEND_UIN_ERR,				//���ֲ����ڵ�ǰ�û����ͺ��
	MONEY_LOCKED,				//��ұ���Ϸ����
	RED_CLOSED,					//��Ϸ�ر�
};

enum
{
	PPC_STOP,												//ֹͣ״̬
	PPC_FREE,												//����ʱ��
	PPC_BETTING,											//��������עʱ��
	PPC_WAIT,												//�ȴ�ʱ��
	PPC_CARRUN,												//��������ת
	PPC_END,												//�˾ֽ���

};
class LimitEnterRoom
{
public:
	enum LimitList
	{
		LIMIT_ROOM_VISISTOR,									//��ͨ�ο�
		LIMIT_ROOM_JUNION_VIP,									//����
		LIMIT_ROOM_MIDDLE_VIP,									//�л�
		LIMIT_ROOM_HIGHER_VIP,									//�߻�
		LIMIT_ROOM_GOLD_VIP,									//�׽��Ա
		LIMIT_ROOM_LORD,										//��λ
		LIMIT_ROOM_RICHER,										//���
		LIMIT_ROOM_SINGER,										//����
		LIMIT_ROOM_AGENT,										//����
		LIMIT_ROOM_SALES,										//����
		LIMTI_ROOM_STAFF,										//�ͷ�
		LIMIT_ROOM_PRIVILEGES,									//��Ȩ
		LIMIT_ROOM_COO,											//վ��
		LIMIT_ROOM_COO_ASSISTANT,								//��վ��
		LIMIT_ROOM_MUSIC_SOCIETY,								//����
		LIMIT_ROOM_DANCER,										//����
		LIMIT_ROOM_FUHAO,										//����
		LIMIT_ROOM_STAR,										//����
		LIMIT_ROOM_DIAMOND_BLACK_VIP,							//����VIP
		LIMIT_ROOM_DIAMOND_RED_VIP,								//����VIP
		LIMIT_ROOM_DIAMOND_YELLOW_VIP,							//����VIP
		LIMIT_ROOM_DIAMOND_GREEN_VIP,							//����VIP
		LIMIT_ROOM_DIAMOND_BLUE_VIP,							//����VIP
		LIMIT_ROOM_DIAMOND_PINK_VIP,							//����VIP
		LIMIT_ROOM_DIAMOND_PURPLE_VIP,							//����VIP 
		LIMIT_ROOM_DIAMOND_COLOUR_VIP,							//����VIP
		LIMIT_ROOM_LIMIT,
	};
};




class CChatRankList
{
public:
	enum RankList
	{
		RANK_GENERAL,											//��ͨ�û�
		RANK_ROOM_JUNION_VIP,									//�ͻ�	
		RANK_ROOM_MIDDLE_VIP,									//�л�
		RANK_ROOM_HIGHER_VIP,									//�߻�
		RANK_ROOM_GOLD_VIP,										//���
		RANK_ROOM_LORD_BARON,									//�о�
		RANK_ROOM_LORD_VISCOUNT,								//�Ӿ�
		RANK_ROOM_LORD_EARL,									//����
		RANK_ROOM_LORD_MARQUESS,								//���
		RANK_ROOM_LORD_DUKE,									//����
		RANK_ROOM_LORD_KING,									//����
		RANK_ROOM_MANAGER,										//�������
		RANK_ROOM_ASSISTANT,									//����
		RANK_ROOM_OWNER,										//����
		RANK_ROOM_SUPPER,										//����
		RANK_ROOM_SINGER,										//����
		RANK_ROOM_AGENT,										//����
		RANK_ROOM_CONTACT_STAFF,								//�ͷ�
		RANK_ROOM_SALES,										//����
		RANK_ROOM_PRIVILEGES,									//��Ȩ
		RANK_ROOM_COO,											//վ��
		RANK_ROOM_RICHER1,										//����֮�ǵ�1��
		RANK_ROOM_RICHER2,										//����֮�ǵ�2��
		RANK_ROOM_RICHER3,										//����֮�ǵ�3��
		RANK_ROOM_RICHER4,										//����֮�ǵ�4��
		RANK_ROOM_RICHER5,										//����֮�ǵ�5��
		RANK_ROOM_RICHER6,										//����֮�ǵ�6��
		RANK_ROOM_RICHER7,										//����֮�ǵ�7��
		RANK_ROOM_RICHER8,										//����֮�ǵ�8��
		RANK_ROOM_RICHER9,										//����֮�ǵ�9��
		RANK_ROOM_RICHER10,										//����֮�ǵ�10��
		RANK_ROOM_AREA_MASTER,									//����
		RANK_ROOM_AREA_ASSISTANT,								//������������
		RANK_ROOM_COO_ASSISTANT,								//����վ��
		RANK_ROOM_MUSIC_SOCIETY,								//����
		RANK_ROOM_DANCER,										//�赸��Ա
		RANK_ROOM_FUHAO,										//���ֱ�־
		RANK_ROOM_STAR,											//�Ǽ�����
		RANK_ROOM_DIAMOND_BLACK_VIP,							//����VIP
		RANK_ROOM_DIAMOND_RED_VIP,								//����VIP
		RANK_ROOM_DIAMOND_YELLOW_VIP,							//����VIP
		RANK_ROOM_DIAMOND_GREEN_VIP,							//����VIP
		RANK_ROOM_DIAMOND_BLUE_VIP,								//����VIP
		RANK_ROOM_DIAMOND_PINK_VIP,								//����VIP
		RANK_ROOM_DIAMOND_PURPLE_VIP,							//����VIP
		RANK_ROOM_DIAMOND_COLOUR_VIP,							//����VIP
		RANK_ROOM_GUARD,										//�ػ�
		RANK_ROOM_CARETAKER,									//�ٹ�
		RANK_ROOM_LIMIT,
	};

	static std::string GetRankName(uint8 usertype)
	{
		std::string rankStr = "";
		switch (usertype)
		{
		case CChatRankList::RANK_GENERAL:		
			rankStr="��ͨ�û�";
			break;
		case CChatRankList::RANK_ROOM_JUNION_VIP:				//�ͻ�	
			rankStr="������Ա";
			break;
		case CChatRankList::RANK_ROOM_MIDDLE_VIP:				//�л�
			rankStr="�м���Ա";
			break;
		case CChatRankList::RANK_ROOM_HIGHER_VIP:				//�߻�
			rankStr="�߼���Ա";
			break;
		case CChatRankList::RANK_ROOM_GOLD_VIP:					//���
			rankStr="�׽��Ա";
			break;
		case CChatRankList::RANK_ROOM_LORD_BARON:				//�о�
			rankStr="�о�";
			break;
		case CChatRankList::RANK_ROOM_LORD_VISCOUNT:			//�Ӿ�
			rankStr="�Ӿ�";
			break;
		case CChatRankList::RANK_ROOM_LORD_EARL:				//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_LORD_MARQUESS:			//���
			rankStr="���";
			break;
		case CChatRankList::RANK_ROOM_LORD_DUKE:				//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_LORD_KING:				//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_MANAGER:					//�������
			rankStr="�������";
			break;
		case CChatRankList::RANK_ROOM_ASSISTANT:				//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_OWNER:					//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_SUPPER:					//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_SINGER:					//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_AGENT:					//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_CONTACT_STAFF:			//�ͷ�
			rankStr="�ͷ�";
			break;
		case CChatRankList::RANK_ROOM_SALES:					//����
			rankStr="�������";
			break;
		case CChatRankList::RANK_ROOM_PRIVILEGES:				//��Ȩ
			rankStr="��Ȩ";
			break;
		case CChatRankList::RANK_ROOM_COO:						//վ��
			rankStr="վ��";
			break;
		case CChatRankList::RANK_ROOM_RICHER1:					//����֮�ǵ�1��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER2:					//����֮�ǵ�2��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER3:					//����֮�ǵ�3��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER4:					//����֮�ǵ�4��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER5:					//����֮�ǵ�5��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER6:					//����֮�ǵ�6��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER7:					//����֮�ǵ�7��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER8:					//����֮�ǵ�8��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER9:					//����֮�ǵ�9��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_RICHER10:					//����֮�ǵ�10��
			rankStr="����֮��";
			break;
		case CChatRankList::RANK_ROOM_AREA_MASTER:				//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_AREA_ASSISTANT:			//������������
			rankStr="������";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_BLACK_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_RED_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_YELLOW_VIP:		//����VIP
			rankStr="�����Ա";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_GREEN_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_BLUE_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_PINK_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_PURPLE_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_DIAMOND_COLOUR_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankList::RANK_ROOM_COO_ASSISTANT:			//����վ��
			rankStr="��վ��";
			break;
		case CChatRankList::RANK_ROOM_MUSIC_SOCIETY:			//����
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_DANCER:					//�赸��Ա
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_FUHAO:					//���ֱ�־
			rankStr="����";
			break;
		case CChatRankList::RANK_ROOM_STAR:						//�Ǽ�����
			rankStr = "����";
			break;

		case CChatRankList::RANK_ROOM_GUARD:					//�ػ�
			rankStr = "�ػ�";
			break;
		case CChatRankList::RANK_ROOM_CARETAKER:					//�ٹ�
			rankStr = "�ٹ�";
			break;
		}
		return rankStr;
	}


};



class CChatRankListVip
{
public:
	enum RankListVip
	{
		RANK_GENERAL,											//��ͨ�û�
		RANK_ROOM_JUNION_VIP,									//�ͻ�	
		RANK_ROOM_MIDDLE_VIP,									//�л�
		RANK_ROOM_HIGHER_VIP,									//�߻�
		RANK_ROOM_GOLD_VIP,										//�׽��
		RANK_ROOM_LORD_BARON,									//�о�
		RANK_ROOM_LORD_VISCOUNT,								//�Ӿ�
		RANK_ROOM_LORD_EARL,									//����
		RANK_ROOM_LORD_MARQUESS,								//���
		RANK_ROOM_LORD_DUKE,									//����
		RANK_ROOM_LORD_KING,									//����
		RANK_ROOM_MANAGER,										//�������
		RANK_ROOM_ASSISTANT,									//����
		RANK_ROOM_OWNER,										//����
		RANK_ROOM_SUPPER,										//����
		RANK_ROOM_CONTACT_STAFF,								//�ͷ�
		RANK_ROOM_PRIVILEGES,									//��Ȩ
		RANK_ROOM_COO,											//վ��
		RANK_ROOM_COO_ASSISTANT,								//��վ��
		RANK_ROOM_CASTEALLAN,									//����
		RANK_ROOM_CASTEALLAN_MRS,								//��������
		RANK_ROOM_COMPERE,										//��������
		RANK_ROOM_COMPEREMAN,									//MC������
		RANK_ROOM_BABY1,										//����1
		RANK_ROOM_BABY2,										//����2
		RANK_ROOM_BABY3,										//����3
		RANK_ROOM_BABY4,										//����4
		RANK_ROOM_BABY5,										//����5
		RANK_ROOM_BABY6,										//����6
		RANK_ROOM_PATROL,										//Ѳ��
		RANK_ROOM_OPERATION,									//��Ӫ
		RANK_ROOM_DIAMOND_BLACK_VIP,							//����VIP
		RANK_ROOM_DIAMOND_RED_VIP,								//����VIP
		RANK_ROOM_DIAMOND_YELLOW_VIP,							//����VIP
		RANK_ROOM_DIAMOND_GREEN_VIP,							//����VIP
		RANK_ROOM_DIAMOND_BLUE_VIP,								//����VIP
		RANK_ROOM_DIAMOND_PINK_VIP,								//����VIP
		RANK_ROOM_DIAMOND_PURPLE_VIP,							//����VIP
		RANK_ROOM_DIAMOND_COLOUR_VIP,							//����VIP
		RANK_ROOM_CARETAKER,									//�ٹ�
		RANK_ROOM_LIMIT,
	};

	static std::string GetRankName(uint8 usertype)
	{
		std::string rankStr = "";
		switch (usertype)
		{
		case CChatRankListVip::RANK_GENERAL:		
			rankStr="��ͨ�û�";
			break;
		case CChatRankListVip::RANK_ROOM_JUNION_VIP:				//�ͻ�	
			rankStr="������Ա";
			break;
		case CChatRankListVip::RANK_ROOM_MIDDLE_VIP:				//�л�
			rankStr="�м���Ա";
			break;
		case CChatRankListVip::RANK_ROOM_HIGHER_VIP:				//�߻�
			rankStr="�߼���Ա";
			break;
		case CChatRankListVip::RANK_ROOM_GOLD_VIP:					//���
			rankStr="�׽��Ա";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_BARON:				//�о�
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_VISCOUNT:			//�Ӿ�
			rankStr="��������";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_EARL:				//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_MARQUESS:			//���
			rankStr="�ʵ�";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_DUKE:				//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_LORD_KING:				//����
			rankStr="���";
			break;
		case CChatRankListVip::RANK_ROOM_MANAGER:					//�������
			rankStr="�������";
			break;
		case CChatRankListVip::RANK_ROOM_ASSISTANT:				//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_OWNER:					//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_SUPPER:					//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_CONTACT_STAFF:			//�ͷ�
			rankStr="�ͷ�";
			break;
		case CChatRankListVip::RANK_ROOM_PRIVILEGES:				//��Ȩ
			rankStr="��Ȩ";
			break;
		case CChatRankListVip::RANK_ROOM_COO:						//վ��
			rankStr="վ��";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_BLACK_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_RED_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_YELLOW_VIP:		//����VIP
			rankStr="�����Ա";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_GREEN_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_BLUE_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_PINK_VIP:			//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_PURPLE_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_DIAMOND_COLOUR_VIP:		//����VIP
			rankStr="����VIP";
			break;
		case CChatRankListVip::RANK_ROOM_COO_ASSISTANT:			//����վ��
			rankStr="��վ��";
			break;
		case CChatRankListVip::RANK_ROOM_CASTEALLAN:				//����
			rankStr="����";
			break;
		case CChatRankListVip::RANK_ROOM_CASTEALLAN_MRS:			//��������
			rankStr="��������";
			break;

		case CChatRankListVip::RANK_ROOM_COMPEREMAN:			////MC������
			rankStr="MC������";
			break;
		case CChatRankListVip::RANK_ROOM_COMPERE:			//��������
			rankStr="��������";
			break;
		case CChatRankListVip::RANK_ROOM_BABY1:			//����1
			rankStr="����1";
			break;
		case CChatRankListVip::RANK_ROOM_BABY2:			//����2
			rankStr="����2";
			break;
		case CChatRankListVip::RANK_ROOM_BABY3:			//����3
			rankStr="����3";
			break;
		case CChatRankListVip::RANK_ROOM_BABY4:			//����4
			rankStr="����4";
			break;
		case CChatRankListVip::RANK_ROOM_BABY5:			//����5
			rankStr="����5";
			break;
		case CChatRankListVip::RANK_ROOM_BABY6:			//����6
			rankStr="����6";
			break;
		case CChatRankListVip::RANK_ROOM_PATROL:			//Ѳ��
			rankStr="Ѳ��";
			break;
		case CChatRankListVip::RANK_ROOM_OPERATION:			//��Ӫ
			rankStr="��Ӫ";
			break;
		case CChatRankListVip::RANK_ROOM_CARETAKER:			//�ٹ�
			rankStr="�ٹ�";
			break;
			
		}
		return rankStr;
	}


};



class ChatAct
{
public:
	enum Act
	{
		ActKickOut = 1,											//����
		ActBlock,												//���ڹ���
		ActMic,													//����
		ActForbidChat,											//�������˹���
		ActModifyRoomInfo,										//�޸ķ�����Ϣ
		ActGetUserIP,											//�鿴�û�IPȨ��
		ActShake,												//��������
		ActPublicChat,											//�ڹرպ�,�Ƿ��й��Ĺ���
		ActPrivateChat,											//�ڹرպ�,�Ƿ���˽�Ĺ���,
		ActRoomBroadcast,										//����㲥����
		ActRoomGlobalMsg,										//ȫվ����
		ActVipRoom,												//����vip����Ȩ��
		ActVipRoomFull,											//����vip��Ա����Ȩ��
		ActRoomBlock,											//���뷿�������Ȩ��
		ActPidBlock,											//����վ�������Ȩ��
		ActModifyMgr,											//���ù���ԱȨ��
		ActModifyOwner,											//���ø�����Ȩ��
		ActChatLenLimit,										//������������
		ActChatDiy,												//�����Զ�������
		ActChatFace,											//����Ȩ��
		ActChatPicture,											//ͼƬȨ��
		ActChatColor,											//����Ȩ��
		ActModifyCaretaker,										//�޸��ٹ�	
		ActTakeMic,												//����
		ActGreeter,												//ӭ����
		ActOtherPrivateChat,									//���������Ļ�Ȩ��
		ActTransfer,											//ת��
		ActPrivateMic,											//��˽��Ȩ��
		ActPrivateWatch,										//��˽��ָ��Ȩ��
		ActSpecialWatch,										//�������Ƶ�˽��ۿ�Ȩ��
		ActGetRed,												//�����
		ActSendRed,												//�����

		ActLimit,

		ActGameStart = 100,
		ActChat,												//��Ϸ����
		ActKick,												//��������
		ActGameLimit,											//�������Ȩ��(���һ�)
	};
	static std::string GetActionName(uint8 actid)
	{
		std::string actNameStr = "";
		switch (actid)
		{
		case ActKickOut:										//����
			actNameStr = "kickout";
			break;
		case ActBlock:											//���ڹ���
			actNameStr = "block";
			break;
		case ActMic:											//����
			actNameStr = "mic";
			break;
		case ActForbidChat: 									//�������˹���
			actNameStr = "forbidchat";
			break;
		case ActModifyRoomInfo: 								//�޸ķ�����Ϣ
			actNameStr = "modifyinfo";
			break;
		case ActGetUserIP: 										//�鿴�û�IPȨ��
			actNameStr = "getuserip";
			break;
		case ActShake:											//��������
			actNameStr = "shark";
			break;
		case ActPublicChat: 									//�ڹرպ�:�Ƿ��й��Ĺ���
			actNameStr = "publicchat";
			break;
		case ActPrivateChat:									//�ڹرպ�:�Ƿ���˽�Ĺ���:
			actNameStr = "privatechat";
			break;
		case ActRoomBroadcast: 									//����㲥����
			actNameStr = "broadcast";
			break;
		case ActRoomGlobalMsg: 									//ȫվ����
			actNameStr = "ActRoomGlobalMsg";
			break;

		case ActVipRoom:										//����vip����Ȩ��
			actNameStr = "ActVipRoom";
			break;

		case ActVipRoomFull:									//����vip��Ա����Ȩ��
			actNameStr = "ActVipRoomFull";
			break;

		case ActRoomBlock:										//���뷿�������Ȩ��
			actNameStr = "ActRoomBlock";
			break;

		case ActPidBlock:										//����վ�������Ȩ��
			actNameStr = "ActPidBlock";						
			break;
			
		case ActModifyMgr:										//���ù���ԱȨ��
			actNameStr = "ActModifyMgr";						
			break;
		
		case ActModifyOwner:									//���ø�����Ȩ��
			actNameStr = "ActModifyOwner";						
			break;
		
		case ActChatLenLimit:									//������������
			actNameStr = "ActChatLenLimit";						
			break;

		case ActChatDiy:										//�����Զ�������
			actNameStr = "ActChatDiy";						
			break;
		
		case ActChatFace:										//����Ȩ��
			actNameStr = "ActChatFace";						
			break;
				
		case ActChatPicture:									//ͼƬȨ��
			actNameStr = "ActChatPicture";						
			break;	

		case ActChatColor:										//����Ȩ��
			actNameStr = "ActChatColor";						
			break;	
				
		case ActModifyCaretaker:								//�޸��ٹ�
			actNameStr = "ActModifyCaretaker";						
			break;	

		case ActTakeMic:										//����
			actNameStr = "ActTakeMic";						
			break;	

		case ActGreeter:										//ӭ����
			actNameStr = "ActGreeter";						
			break;	
		case ActOtherPrivateChat:								//���������Ļ�Ȩ��
			actNameStr = "ActOtherPrivateChat";						
			break;	
		case ActTransfer:										//ת��
			actNameStr = "ActTransfer";						
			break;	
		case ActPrivateMic:										//��˽��Ȩ��
			actNameStr = "ActPrivateMic";						
			break;	
		case ActPrivateWatch:										//��˽��ָ��Ȩ��
			actNameStr = "ActPrivateWatch";						
			break;	
		case ActSpecialWatch:										//�������Ƶ�˽��ۿ�Ȩ��
			actNameStr = "ActSpecialWatch";						
			break;	
		case ActGetRed:												//�����
			actNameStr = "ActGetRed";
			break;
		case ActSendRed:											//�����
			actNameStr = "ActSendRed";
			break;


		//��Ϸ100�Ժ��
		case ActChat:
			actNameStr = "ActGameChat";						
			break;
		case ActKick:
			actNameStr = "ActGameKick";
			break;
		case ActGameLimit:
			actNameStr = "ActGameLimit";
			break;
		}
		return actNameStr;
	};

};

#pragma pack(push, 1)


class ChatAclCtrl
{
public:
	ChatAclCtrl()
	{
		actKickOut = actMic = actForbidChat = actModifyRoomInfo \
			= actGetUserIP = actShake = actPublicChat = actPrivateChat = actRoomBroadcast = 0;
		actRoomGlobalMsg = 0;
		actVipRoom		 = 0;											//����vip����Ȩ��										
		actVipRoomFull	 = 0;;										//����vip��Ա����Ȩ��
		actRoomBlock	 = 0;										//���뷿�������Ȩ��
		actPidBlock      = 0;											//����վ�������Ȩ��
		actModifyMgr     = 0;										//���ù���ԱȨ��(����)
		actModifyOwner   = 0;										//���ø�����Ȩ��(����)
		actChatLenLimit  = 0;										//������������
		actChatDiy       = 0;										//�����Զ�������
		actChatFace		 = 0;											//����Ȩ��
		actChatPicture	 = 0;										//ͼƬȨ��
		actChatColor	 = 0;								
		actModifyCaretaker= 0;
		actTakeMic		 = 0;											
		actGreeter		 = 0;;											
		actOtherPrivateChat = 0;								
		actTransfer = 0;	
		actPrivateMic = 0;										
		actPrivateWatch = 0;									
		actSpecialWatch = 0;
		actGetRed = 0;
		actSendRed = 0;
	}
	uint8 actKickOut:1;											//����
	uint8 actMic:1;												//����
	uint8 actForbidChat:1;										//����
	uint8 actModifyRoomInfo:1;									//�޸ķ�����Ϣ
	uint8 actGetUserIP:1;										//�鿴�û�IPȨ��
	uint8 actShake:1;											//��������
	uint8 actPublicChat:1;										//���Ĺ���
	uint8 actPrivateChat:1;										//˽�Ĺ���
	uint8 actRoomBroadcast:1;									//����㲥����
	uint8 actRoomGlobalMsg:1;									//ȫվ����
	uint8 actVipRoom:1;											//����vip����Ȩ��										
	uint8 actVipRoomFull:1;										//����vip��Ա����Ȩ��
	uint8 actRoomBlock:1;										//���뷿�������Ȩ��
	uint8 actPidBlock:1;										//����վ�������Ȩ��
	uint8 actModifyMgr:1;										//���ù���ԱȨ��(����)
	uint8 actModifyOwner:1;										//���ø�����Ȩ��(����)
	uint8 actChatLenLimit:1;									//������������
	uint8 actChatDiy:1;											//�����Զ�������
	uint8 actChatFace:1;										//����Ȩ��
	uint8 actChatPicture:1;										//ͼƬȨ��
	uint8 actChatColor:1;										//����Ȩ��
	uint8 actModifyCaretaker:1;									//�޸��ٹ�
	uint8 actTakeMic:1;											//����Ȩ��
	uint8 actGreeter:1;											//ӭ����Ȩ��
	uint8 actOtherPrivateChat:1;								//���������Ļ�
	uint8 actTransfer:1;										//ת��
	uint8 actPrivateMic:1;										//��˽��
	uint8 actPrivateWatch:1;									//˽���ָ��Ȩ�޹ۿ�
	uint8 actSpecialWatch:1;									//�����κ����ƹۿ�˽��Ȩ��
	uint8 actGetRed:1;											//�����Ȩ��
	uint8 actSendRed:1;											//�����Ȩ��

	
	std::string GetAclStr()
	{
		std::string aclStr;
		
		aclStr += actKickOut?"1":"0";
		aclStr += actMic?"1":"0";
		aclStr += actForbidChat?"1":"0";
		aclStr += actModifyRoomInfo?"1":"0";
		aclStr += actGetUserIP?"1":"0";
		aclStr += actShake?"1":"0";
		aclStr += actPublicChat?"1":"0";
		aclStr += actPrivateChat?"1":"0";
		aclStr += actRoomBroadcast? "1":"0";
		aclStr += actRoomGlobalMsg? "1":"0";
		aclStr += actVipRoom? "1":"0";
		aclStr += actVipRoomFull? "1":"0";
		aclStr += actRoomBlock? "1":"0";
		aclStr += actPidBlock? "1":"0";
		aclStr += actModifyMgr? "1":"0";
		aclStr += actModifyOwner? "1":"0";
		aclStr += actChatLenLimit? "1":"0";
		aclStr += actChatDiy? "1":"0";
		aclStr += actChatFace? "1":"0";
		aclStr += actChatPicture? "1":"0";
		aclStr += actChatColor? "1":"0";
		aclStr += actModifyCaretaker?"1":"0";
		aclStr += actTakeMic?"1":"0";
		aclStr += actGreeter?"1":"0";
		aclStr += actOtherPrivateChat?"1":"0";
		aclStr += actTransfer?"1":"0";
		aclStr += actPrivateMic?"1":"0";
		aclStr += actPrivateWatch?"1":"0";
		aclStr += actSpecialWatch?"1":"0";
		aclStr += actGetRed?"1":"0";
		aclStr += actSendRed?"1":"0";

		return aclStr;
	}
	void SetAcl(std::string aclStr)
	{
		uint8 i=0;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actKickOut = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actMic = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actForbidChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyRoomInfo = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGetUserIP = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actShake = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPublicChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateChat = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomBroadcast = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomGlobalMsg = 1;


		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actVipRoom = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actVipRoomFull = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actRoomBlock = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPidBlock = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyMgr = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyOwner = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatLenLimit = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatDiy = 1;	

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatFace = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatPicture = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actChatColor = 1;
		
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actModifyCaretaker = 1;
	
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actTakeMic = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGreeter = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actOtherPrivateChat = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actTransfer = 1;

		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateMic = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actPrivateWatch = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actSpecialWatch = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actGetRed = 1;
		i++;
		if (i < aclStr.length() && *(i + aclStr.c_str()) == '1')
			actSendRed = 1;

	}
	bool ISManager()
	{
		return (actKickOut || actMic);
	}
} ;

#pragma pack(pop)




class CGiftKind
{
public:
	enum
	{
		MAX_SINGER_GIFT_NUM = 2,								//���������Ч�������
	};

	enum
	{
		SINGER_GIFT_FOR_SINGER = 0,								//�������ֻ�Ը�����Ч
		SINGER_GIFT_FOR_ALL,									//����������������Ч
	};

	enum Giftkind
	{
		GENERAL_GIFT = 0,										//��ͨ����
		LUCKY_GIFT,												//��������
		SINGER_GIFT,											//��������
		WELFARE_GIFT,											//Ⱥˢ������䷢����
        TRANSFER_GIFT = 5,                                      //ת������ [JWJ]
		VOD_GIFT,												//���
		SMALL_FIREWORKS,										//С�̻�
		BIG_FIREWORKS,											//���̻�
		DIAMOND_GIFT,											//��ʯ����
		WEEKSTAR_GFIT,											//������ʯ����
		SIEGE_GIFT_KIND,										//��������	
		DIAMOND_TRANSFER,										//��ʯת������		
	};
};

class CRebateKind
{
public:
	enum
	{
		NORMAL_USER = 1,	//��ͨ�û�
		SINGER_USER,		//����
	};
};

class CRoomMicMode
{
public:
	enum MicMode
	{
		GENERAL_MODE = 0,										//��ͨģʽ
		SINGER_MODE,											//����ģʽ
	};
};

enum PrivateMicType
{
	NONEED_AUTH,				//����Ҫ��֤��������֤ͨ��
	ONLY_VIP_AUTH,				//��Ա�û��ɹۿ�
	USER_AGREE_AUTH,			//��Ҫ�û�ȷ��������
	GIFT_AUTH,					//���������

	AUTH_LIMIT,					//˽����������
};

enum PrivateMicConfirmAction
{
	CONFIRM_ANSWER_AGREE,			//˽���û�ͬ������
	CONFIRM_ANSWER_REFUSE,			//˽���û��ܾ�����
};


enum ChatUserType
{
	chat_user_general,									//��ͨ�û�
	chat_user_virtual,									//�����û�������ϣ���ܹ���չ�ɻ�����
	chat_user_ios,										//�ƶ�ios�û�
	chat_user_android,									//�ƶ�andorid�û�
	chat_user_web,										//web�û�
	chat_user_letao,									//pc���԰汾		
	chat_user_iospad,									//ios pad�汾	
	chat_user_androidpad,								//��׿pad
};


enum BeanstalkNotifyType
{
	//��Ϸ
	BNT_PPC_NEW				= 1,					//���������н���Ϣ�㲥
	BNT_PPC_FKCH,									//������н���Ϣ�㲥
	BNT_PPC_FRUIT,									//����ˮ�����н���Ϣ�㲥
	BNT_PPC_DIAMOND,								//שʯ�����н���Ϣ�㲥
	BNT_ZZ_LE,										//תת���н���Ϣ�㲥
	BNT_OPEN_BOX,									//���俪�����н���Ϣ�㲥
	BNT_DUG_TREASURE,								//�����ڱ��н���Ϣ�㲥
	BNT_NN_CARD,									//ţţ�н���Ϣ�㲥

	//����
	BNT_LUCKY_GIFT			= 101,					//���������н��н���Ϣ
	BNT_DUOBAO_WIN,									//һԪ�ᱦ�н���Ϣ
	BNT_ACTIVIT_PROMOTE,							//�����ƹ���Ϣ
	//��ҹ㲥��Ϣ
	BNT_NORMAL_USER_MSG			= 201,				//��ͨ������ҷ��͹㲥��Ϣ
	BNT_VIP_USRE_MSG,								//VIP������ҷ��͹㲥��Ϣ
};

enum GiftDayRankFirstType
{
	GDRFT_SSEND_GIFT = 1,				//�����һ��
	GDRFT_RECIVE_GIFT = 2,				//�����һ��

	GDRFT_LIMIT,
};



/************************************************************************/
/* �������Ϳͻ��˹��������ּ��ϣ������ط������ٶ���������,�����Դ�Ϊ׼*/
/************************************************************************/
typedef enum RoomCmdType
{	
	IM_CHAT_KEEP_ALIVE = 0x0001,
	IM_CHAT_ACK,
	IM_CHAT_PING,												//���ټ�ⱨ��
	IM_CHAT_OBTAIN_IP,											//����û��ɣ�
	IM_CHAT_ANDROID_LOGON,										//�����˵�½
	IM_CHAT_ANDROID_LOGON2,

	IM_CHAT_LOGON_ROOM			= 0x0100,						//��½����
	IM_CHAT_LOGOUT_ROOM,										//�˳�����
	IM_CHAT_KICKOUT,											//�߳�
	IM_CHAT_VISITOR,											//��ȡ���䵱ǰ�û��б�
	IM_CHAT_FORBID_CHAT,                                        //����ĳ�û� 
	IM_CHAT_EXTRA_MICTIME,										//�ӳ���ʱ
	IM_CHAT_MAC_PRESENTLIST,									//�ͻ������������ȡ���������б�
	IM_CHAT_PRIVATE_BIND,										//��˽��
	IM_CHAT_PRIVATE_UNBIND,										//��˽��
	IM_CHAT_PRIVATE_WATCH,										//�ۿ�˽��
	IM_CHAT_PRIVATE_UNWATCH,									//�˳��ۿ�˽��
	IM_CHAT_PRIVATE_WATCHLIST,									//����˽��ۿ��б�
	IM_CHAT_PRIVATE_LIST_REQ,									//����˽���б�
	IM_CHAT_KICKOUT_PRIVATE,									//����˽��	
	IM_CHAT_PRIVATE_AVSTATE,									//˽������Ƶ״̬�޸�
	IM_CHAT_FORBID_CHAT_BY_ANCHOR,                               //�������Բ���
	
	IM_CHAT_MODIFY_INFO			= 0x0200,						//�޸ķ�����Ϣ
	IM_CHAT_GET_ROOMINFO,										//��ȡ������Ϣ
	IM_CHAT_MODIFYPASS,											//�޸ķ�������
	IM_CHAT_ROOM_OPEN,											//�򿪷���
	IM_CHAT_ROOM_CLOSE,											//�رշ���

	IM_CHAT_MODIFY_MANGER,										//�޸Ĺ���ԱȨ��
	IM_CHAT_ROOM_MSG,											//���ͷ����ڲ��㲥
	IM_CHAT_MODIFY_ROOM_INFO_ITEM,								//�����޸ķ�����Ϣ
	IM_CHAT_SUIBO_PAUSE,										//�����л�����̨
	IM_CHAT_MGRLIMIT_CONFIRM,									//���ܳ�������ȷ�Ͽ�����

	IM_CHAT_CONF_JOIN			= 0x0250,						//����
	IM_CHAT_CONF_EXIT,											//��������
	IM_CHAT_CONF_KICKOUT,										//������			
	IM_CHAT_CONF_DRAGIN,										//������������
	IM_CHAT_CANCEL_CFWAIT,										//ȡ���ȴ�����
	IM_CHAT_GET_MIC_LIST,										//��ȡ��ǰ�����б�
	IM_CHAT_CFWAITLIST,											//��ȡ�����б�
	IM_CHAT_CHANGE_AUTOMIC,										//����Զ�����״̬
	IM_CHAT_ADJUST_MIC_QUEUE,									//��������Ķ���
	IM_CHAT_DRAG_SETTING,										//���÷�����ѡ��
	IM_CHAT_SHAKE,												//�ζ��Է�
	IM_CHAT_STAMP,												//ӡ��
	IM_CHAT_GET_USER_STAMP_INFO,								//��ȡ�����б�
	IM_CHAT_ERASESTAMP,											//��������
	IM_CHAT_REQUEST_OPENBOX,									//������ѿ���������
	IM_CHAT_VIEWSTATE,											//ֱ��״̬���
	IM_CHAT_LAUDCOUNT,											//����
	IM_CHAT_TAKEMIC,											//����
	IM_CHAT_MODIFYCARETAKER,									//�޸���ʱ����
	IM_CHAT_FILLUPMICQUEUE,										//������
	IM_CHAT_MODIFYMICTIME,										//�޸������ʱ
	IM_CHAT_CHANGE_MACLIMIT,									//��������
	IM_CHAT_GET_VID,											//��ȡvid
	IM_CHAT_OPEN_BOX,											//�ڱ�����
	IM_CHAT_MICINFO_REQ,										//���������û���Ϣ
	IM_CHAT_INVITE_FRIENDS,                                     //����QQ����
	IM_CHAT_REQ_REDLIST,										//�������б�


	IM_CHAT_TEXT				= 0x0300,						//������Ϣ
	IM_CHAT_USEGIFT,											//����
	IM_CHAT_AUDIO,												//��Ƶ
	IM_CHAT_VIDEO,												//��Ƶ
	IM_CHAT_GLOBLE_MSG,											//����С������Ϣ
	IM_CHAT_RTP,												//RTP����
	IM_CHAT_RTP_ACK,											//RTP����ACK
	IM_CHAT_RTP_REQ,											//RTP��������ʧ����
	IM_CHAT_RTP_REQ_DIRECT,										//ֱ������ĳ����
	IM_CHAT_USEGIFT_LIST,										//Ⱥˢ���ܣ�
	IM_CHAT_GAME,												//������Ϸ
	IM_CHAT_GETPRESENT_MONEY,									//��ȡ������
    IM_CHAT_TRANS_TAX_RATE,                                     //��ȡת��˰�ʺ�Ȩ�� // [JWJ]
	IM_CHAT_ADDBLOCK,											//����ȫվ����
	IM_CHAT_MODIFYOWNER,										//�޸ĸ�����
	IM_CHAT_GUARD_LIST,											//�ػ��б�
	IM_CHAT_GUARD_ACL,											//�ػ�Ȩ�޽ӿ�
	IM_CHAT_FANS_LIST,											//��˿�б�
	IM_CHAT_SINGE_ORDER,										//����б�
	IM_CHAT_VOD,												//���
	IM_CHAT_VID_GIFTORDER,										//ֱ����
	IM_CHAT_MONTH_GIFTORDER,									//�°�
	IM_CHAT_SUIBO_REDUCEMONEY,									//�沥��Ǯ����ͨ�ýӿ�
	IM_CHAT_ANYCAST_INFO,										//�沥���뷿�����ݻ�ȡ�ӿ�
	IM_CHAT_REQ_MGRLIST,										//���󷿼�����б�
	IM_CHAT_ANYCAST_BLOCK,										//�沥����
	IM_CHAT_ANYCAST_REDLIST,									//�沥����б�


	IM_CHAT_ZZ_BET					= 0x350,					//תת��ע
	IM_CHAT_RELAY_MSG,											//ת����Ϣ


	IM_CHAT_SRV_USER_ONLINE		= 0x0400,						//�û����뷿��
	IM_CHAT_SRV_USER_OFFLINE,									//����
	IM_CHAT_SRV_KICKOUT,										//ǿ������
	IM_CHAT_SRV_FORCE_OFFLINE,									//��ص�¼ǿ������

	IM_CHAT_SRV_MODIFY_MANGER,
	IM_CHAT_SRV_FORBIDCHAT_NTY,									//����֪ͨ�ӿ�
	IM_CHAT_SRV_MODIFYCARETAKER,								//�޸��ٹ�
	IM_CHAT_SRV_PRIVATE_LIST,									//�·�˽���б�
	IM_CHAT_SRV_CONFIRM_ASK,									//˽����������֪ͨ
	IM_CHAT_SRV_CONFIRM_ANSWER,									//˽ȷ������
	IM_CHAT_SRV_WATCHLIST,										//�·�˽��ۿ��б�
	IM_CHAT_SRV_PRIVATEJOIN,									//��˽��֪ͨ
	IM_CHAT_SRV_PRIVATEEXIT,									//��˽��֪ͨ
	IM_CHAT_SRV_GUARDWEEKLIST,									//���ػ��б�
	


	IM_CHAT_SRV_CONF_JOIN		= 0x0500,						//����
	IM_CHAT_SRV_CONF_EXIT,										//����
	IM_CHAT_SRV_CONF_KICKOUT,									//������
	IM_CHAT_SRV_ADDCFWAIT,										//���������ȴ�
	IM_CHAT_SRV_REMOVECFWAIT,									//���ӻ���ȴ������
	IM_CHAT_SRV_AUTOMIC_STATUS_CHANGE,							//�Զ�����״̬�仯
	IM_CHAT_SRV_MICTIME_CHANGE,									//֪ͨʣ������ʱ
	IM_CHAT_SRV_MICPRESENT,										//֪ͨ��ȡ������
	IM_CHAT_SRV_LAUDCOUNT,										//���µ���
	IM_CHAT_SRV_SHARE,											//����
	IM_CHAT_SVR_FIREWORKS,										//��֪ͨ
	IM_CHAT_SVR_TOTALRECV,										//�沥����������㲥



	IM_CHAT_SRV_ROOMINFO		= 0x0600,						//���·�����Ϣ, ���ڹ���Ա�޸ķ�����Ϣ��
	IM_CHAT_SRV_ROOM_BROADCAST,									//���ͷ���㲥
	IM_CHAT_SRV_ROOM_OPEN,										//���䱻��
	IM_CHAT_SRV_ROOM_CLOSE,										//���䱻�ر�

	IM_CHAT_SRV_USEGIFT			= 0x0700,						//����
	IM_CHAT_SRV_NTY_MSG,										//֪ͨ��Ϣ
	IM_CHAT_SRV_GLOBLE_MSG,										//С�԰���Ϣ
	IM_CHAT_SRV_PRIZE,											//�н���Ϣ
	IM_CHAT_SRV_GREAT_GIFT,										//������Ϣ
	IM_CHAT_SRV_IP_INFO,										//�û���IP��Ϣ
	IM_CHAT_SRV_MARQUEE_MSG,									//����Ʈ������Ϣ,ֻ�·�����
	IM_CHAT_SRV_GENERAL_MSG,									//�������Ϣ�㲥��Ϣ
	IM_CHAT_SRV_STAMP,											//ӡ��
	IM_CHAT_SRV_ERASESTAMP,										//����ӡ��
	IM_CHAT_SRV_GET_USER_STAMP_INFO,							//��ȡ�������û������б�
	IM_CHAT_SRV_REQUEST_OPENBOX,								//��������ѿ���
	IM_CHAT_SRV_ROOMINFO_CHANGE,								//֪ͨ�������Ա��޸�
	IM_CHAT_SRV_GET_REDPAPER,									//�������֪ͨ��Ϣ	//---sqh
	IM_CHAT_SRV_SEND_REDPAPER,									//���ź��֪ͨ��Ϣ	//---sqh
    IM_CHAT_SRV_TRANS_TAX_RATE,                                 //ת��˰�� // [JWJ]
	IM_CHAT_SRV_USEGIFTNEW,										//������н���Ϣ
	IM_CHAT_SRV_NTY_MSGEX,										//��չ֪ͨ��Ϣ
	IM_CHAT_SRV_BOX_NOTIFY,										//����֪ͨ��Ϣ
	IM_CHAT_SRV_OPENBOX_NOTIFY,									//�ڱ�֪ͨ
	IM_CHAT_SRV_ONMIC_INFO,										//֪ͨ�����û���Ϣ
	IM_CHAT_SRV_ROOM_INVITE,                                     //����������Ϣ
	IM_CHAT_SRV_WEEKSTAR_CHANGE,								//���Ǳ��֪ͨ��Ϣ
	IM_CHAT_SRV_DIAMOND_GIFT,									//��ʯ����֪ͨ
	IM_CHAT_SRV_WEEKSTAR_LIST,									//ȫ�������б�
	IM_CHAT_SRV_REDLIST,										//���ͺ���б�
	IM_CHAT_SRV_SIEGEGIFT,										//���¹�������
	IM_CHAT_SRV_UPDATEDAY_GIFTRANK,								//�����������������һ��

	IM_CHAT_SRV_ZZ_BET_START	= 0x0750,						//תת��һ�ֿ�ʼͶע���·�Ͷעʱ��
	IM_CHAT_SRV_ZZ_BETMSG,										//תתĳ����ע��Ϣ
	IM_CHAT_SRV_ZZ_WAITING,										//ȷ����ע���ȴ���������
	IM_CHAT_SRV_ZZ_AWARDING,									//תת��ʼ����
	IM_CHAT_SRV_ZZ_AWARDED,										//תת������Ϣ����ʼ�·���һ��Ͷע��ʼ
	IM_CHAT_SRV_ZZ_AWARDMSG,									//ת��ĳ���н���Ϣ
	IM_CHAT_SRV_ZZ_STOP,										//ֹͣ����
	IM_CHAT_SRV_ZZ_AWARD_TODAY,									//���쿪����Ϣ


	IM_CHAT_SRV2SRV_RTP			= 0x800,						//������֮�䴫��RTP����
	IM_CHAT_SRV2SRV_RTP_REQ,									//������֮�䶪���ط�����

	IM_CHAT_PPC_BET				= 0x900,						//�û�PPCѺע
	IM_CHAT_PPC_BANKER_REQ,										//�û�ׯ�Ҳ���
	IM_CHAT_SVR_PPC_HISTORY,									//������ʷ�·�
	IM_CHAT_SVR_PPC_BETSTART,									//��һ�ֿ�ʼ
	IM_CHAT_SVR_PPC_SCENE,										//��ǰ�����·�
	IM_CHAT_SVR_PPC_AWARD_ITEM,									//�������
	IM_CHAT_SVR_PPC_BET_ACTION,									//��ע����֪ͨ
	IM_CHAT_SVR_PPC_BET_RESULT,									//�û���ע�������,��֪ͨ�µĽ������
	IM_CHAT_SVR_PPC_AWARD_RESULT,								//�û��н�����֪ͨ.
	IM_CHAT_SVR_PPC_BANKER_CHANGE,								//PPCׯ����Ϣ���
	IM_CAHT_SVR_PPC_STOP,										//ֹͣ����
	IM_CAHT_SVR_PPC_FREE,										//�ȴ�������
	IM_CHAT_SVR_PPC_GAMEEND,									//��Ϸ����֪ͨ
	IM_CHAT_PPC_SYNC_SCENE,										//ͬ����������
	IM_CHAT_PPC_SYNC_USERINFO,									//�����û��б�����
	IM_CHAT_PPC_GAMELIMIT,										//��ӳ�������(���һ�)


	REDPACKETS_GAME_START		= 0x1000,						//��һ����Ϸ��ʼ									
	REDPACKETS_SEND_REDPACKETS,									//���ͺ��
	REDPACKETS_SEND_REDPACKETS_NTY,								//�����֪ͨ
	REDPACKETS_ROB_REDPACKETS,									//�����
	REDPACKETS_ROB_REDPACKETS_NTY,								//�����֪ͨ
	REDPACKETS_SENCE_STATE,										//��Ϸ����״̬��������Ϸ�� ���û��������ʹ���Ϣ��
	REDPACKETS_GAME_END,										//��Ϸ�����·������������ٵ��û�
								


	
	IM_CHAT_WEB_USERINFO	= 0x2000,							//web�û���������Ϣ
	IM_CHAT_WEB_CHATTEXT,										//������Ϣ
	IM_CHAT_WEB_VIEWSTATE,										//ֱ��״̬

	DIS_SERVER_REGIST			= 0x3000,						//��ӷ���
	DIS_SERVER_ADD_DELETE_ROOM,									//��ӻ�ɾ������
	DIS_SERVERINFO				,						//���������ϱ�
	DIS_SERVER_ROOMINFO			,						//�ϱ���������

	//�ͻ�������ȷ���
	DIS_CLIENT_GETSERVER,										//�ͻ��˻�ȡ��Ҫ��¼�ķ�����Ϣ

	IM_CHAT_CMD_LIMIT

}RoomCmdType;

typedef enum Language
{
	TL_ZH_CN,	//��������
	TL_ZH_TW,	//��������̨��
	TL_ZH_HK,	//�����������
	TL_EN,		//Ӣ��

	TL_LANGUAGE_LIMIT	//��������
}Language;

//ϵͳ��Ϣ����
typedef enum SystemMsgType
{
	TL_CHAT_MSG,	//��������ʾ����Ϣ
	TL_BOX_MSG,		//������Ϣ
};

typedef enum RoomMsgType
{
	IM_SVR_MSG_SUCCESS = 0x0001,

	IM_SVR_MSG_NO_PRIVILEGE = 0x1000,

	IM_SVR_MSG_CONF_IS_FULL,									//��������Ա
	IM_SVR_MSG_CONF_NOT_IN,										//�㲻�ڻ�����
	IM_SVR_MSG_CONF_HAS_IN,										//�����ڻ�����	
	IM_SVR_MSG_CONF_HAS_MIC,									//���������
	IM_SVR_MSG_CONF_NO_MIC,										//��û�����
	IM_SVR_MSG_CONF_NO_MIC_REMAIN,								//û�ж������
	IM_SVR_MSG_CONF_BE_CLOSE,									//�������ǹرյ�
	IM_SVR_MSG_CONF_NEED_PASS,									//��Ҫ����
	IM_SVR_MSG_CONF_ERR_PASS,									//��������
	IM_SVR_MSG_CONF_ERR_OLDPASS,								//���������
	IM_SVR_MSG_MEMBER_HAS_IN,									//�����ǳ�Ա
	IM_SVR_MSG_MEMBER_NOT_IN,									//�㲻�ǳ�Ա
	IM_SVR_MSG_CONF_HAS_OPEN,									//�����Ѿ��Ǵ򿪵�
	IM_SVR_MSG_CONF_HAS_CLOSE,									//�����Ѿ��ǹرյ�
	IM_SVR_MSG_CONF_HAS_FROZEN,									//�����Ѿ��Ƕ����
	IM_SVR_MSG_CONF_HAS_UNFROZEN,								//�����Ѿ��ǷǶ����
	IM_SVR_MSG_NOT_ONLINE,										//�㲻�����ߣ��޷����б�����
	IM_SVR_MSG_HAS_OPEN,										//�����Ѿ��Ǵ򿪵�
	IM_SVR_MSG_HAS_CLOSE,										//�����Ѿ��ǹرյ�
	IM_SVR_MSG_ERR_OLDPASS,										//���������
	IM_SVR_MSG_CFWAIT_HAS_IN,									//������������
	IM_SVR_MSG_CFWAIT_IS_FULL,									//��������
	IM_SVR_MSG_CFWAIT_NOT_IN,									//�Է���������

	IM_SVR_MSG_OPP_CONF_NOT_IN = 0x1100,						//�Է����ڻ���
	IM_SVR_MSG_OPP_CONF_HAS_IN,									//�Է����ڻ���
	IM_SVR_MSG_OPP_CONF_HAS_MIC,								//�Է��������
	IM_SVR_MSG_OPP_CONF_NO_MIC,									//�Է�û�����
	IM_SVR_MSG_OPP_HAS_BE_MEMBER,								//�Է����ǳ�Ա
	IM_SVR_MSG_OPP_NOT_BE_MEMBER,								//�Է����ǳ�Ա
	IM_SVR_MSG_OPP_HAS_BE_MANAGER,								//�Է����ǹ���Ա			
	IM_SVR_MSG_OPP_NOT_BE_MANAGER,								//�Է����ǹ���Ա
	IM_SVR_MSG_OPP_NOT_ONLINE,									//�Է�������
	IM_SVR_MSG_OPP_HAS_INBLACKLIST,								//�Է����ں�������
	IM_SVR_MSG_OPP_NOT_INBLACKLIST,								//�Է����ں�������
	IM_SVR_MSG_OPP_CFWAIT_NOT_IN,								//�Է�����������

	IM_SVR_MSG_NOT_IN,											//�㲻��Ȧ��
	IM_SVR_MSG_OPP_NOT_IN,										//�Է�����Ȧ��
	IM_SVR_MSG_CANNOT_KICKOUT_NOVISITOR,						//���ܽ���Ա�߳�Ȧ

	IM_SVR_MSG_GIFT_NOMONEY,									//�ʽ�����
	IM_SVR_MSG_GIFT_FAILED,										//����ʧ��

	IM_SVR_MSG_OVER_MEMBER_LIMIT = 0x1200,						//������Ա�������ƣ��޷���ӳ�Ա
	IM_SVR_MSG_OVER_MANAGER_LIMIT,								//��������Ա�������ƣ��޷��ټӹ���Ա
	IM_SVR_MSG_OVER_IMPMES_LIMIT,								//���������ش���Ϣ�����������
	IM_SVR_MSG_OVER_PIC_LIMIT,									//��������ͼƬ�����������
	IM_SVR_MSG_OVER_BLACKLIST_LIMIT,							//�������ѳ����������
	
	IM_SVR_MSG_NOT_IN_SYS_ALLOW_TIME,							//����ϵͳ��������ʱ�䷶Χ��



	ANYCAST_ACL_NOT_ENOUGH	 = 0x1300,							//Ȩ�޲���
	ANYCAST_USER_NUM_LIMIT,										//������������
	ANYCAST_DB_ERROR,											//db�ӿڴ���

}RoomMsgType;



//֪ͨ��
typedef enum RoomCmdStateType
{
	LOGON_SUCCESS = 0x0001,										//��½�ɹ�
	LOGON_ROOM_FAILED,											//���ڲ���ȷ����,ͳһ�Դ˷���
	LOGON_INVALID_UIN,											//uin������
	LOGON_WRONG_PASSWD,											//�������
	LOGIN_NO_ROOM_MEMBER,										//���Ƿ����Ա
	LOGON_ROOM_IS_BUSY,											//��������æ,��ʾ�ͻ����Ժ�����
	LOGON_NO_THIS_ROOM,  										//�÷��䲻����(�����ѽ�ɢ,����ʱ����)
	LOGON_REJECT,												//���ܾ���¼
	LOGON_REQ,													//���������½��
	LOGON_VISITOR_ISFULL,										//��������
	LOGON_ROOM_CLOSE,											//�����ǹرյ�
	LOGON_WRONG_ROOM_PASSWD,									//�����������
	LOGON_ROOM_ISFULL,											//�ο�����
	LOGON_BLACKLIST_UIN,										//�û��ں�������
	LOGON_BLACKLIST_IP,											//IP�ں�������
	LOGON_FORBID_JOIN,											//�÷��䲻����������
	LOGON_REQUEST_DATA,											//��¼�ɹ������������й�//������ whg 20090604
	LOGON_REQUEST_SUCESS,										//��¼�ɹ�������������ȫ������//������ whg 20090604
	LOGON_ROOM_ONLY_SUBSCRIBER,									//ֻ�������߽���
	LOGON_ROOM_ONLY_VIP,										//�շѷ��䣬ֻ����ɷ��û����루�����Ѿ������ߣ�
	LOGON_ROOM_PAY_ERROR,										//�۷Ѳ�ʧ�ܣ�ϵͳ���������)
	LOGON_ROOM_INGAME,											//������Ϸ����
	LOGON_BLACKLIST_MAC,										//�������ں�������
	LOGON_MAX_LIMIT,											//����mac��¼�����������
	LOGON_ENTIRY_LIMIT,											//������ݳ�������¼����
	LOGON_SUIBO_END,
	LOGIN_SUIBO_VIDERROR,
	LOGIN_TABLE_ERROR,											//���Ų�����
	LOGIN_TABLE_LOCKED,											//����������
	LOGIN_TABLE_MONEY_LOCKED,									//����ұ���Ϸ����
	LOGIN_NOENOUGH_MONEY,										//û���㹻�������
	LOGIN_KICK_LIMITTIMES,                                      //��������ûѺע����������
}RoomCmdStateType;


//֪ͨ��
typedef enum TableState
{
	TABLE_SUCCESS = 0x0001,										//�ɹ�
	TABLE_NOENOUTH_MONEY,										//����
	TABLE_API_ERROR,											//�ӿڴ���
	TABLE_ID_EXIST,												//��id���Ѿ�����
	TABLE_MONEY_LOCKED,											//����ұ���Ϸ����

}TableState;

typedef enum OpenBoxState
{
	OPENBOX_SUCCESS,			//�ڱ��ɹ�
	OPENBOX_NOT_FREETIME,		//�����ʱ��
	OPENBOX_NO_FREECOUNT,		//��Ѵ�������
	OPENBOX_FAILED,				//�ӿڴ���
	OPENBOX_NO_ENOUGHMONEY,		//û���㹻��Ǯ
	OPENBOX_MONEYLOCK			//��ұ���Ϸ����
};

typedef enum RoomUserRankType
{
	USER_RANK_GENERAL		= 0x0000,							//None
	USER_RANK_VISITOR		= 0x0001,							//�ο�
	USER_RANK_MEMBER		= 0x0002,							//��ͨ��Ա
	USER_RANK_ROOMMAN		= 0x0004,							//����Ա
	USER_RANK_ROOMOWNER		= 0x0008,							//�ҳ�
	USER_RANK_SUPERMAN		= 0x0010,							//һ������
	USER_RANK_AREA_MASTER	= 0x0020,							//����
	USER_RANK_AREA_ASSISTANT= 0x0040,							//��������
	USER_RANK_ANCHOR		= 0x0080,							//����
	USER_RANK_GUARD			= 0x0100,							//�ػ�
	USER_RANK_CARETAKER		= 0x0200,							//�ٹ�
	USER_RANK_CASTELLAN		= 0x0400,							//����
	USER_RANK_CASTELLAN_MRS = 0x0800,							//��������
	USER_RANK_LIMIT,
}RoomUserRankType;

typedef enum ViewRuningAction
{
	RUN_FRONT		= 0,							//ǰ����������
	RUN_BACK,										//��̨����																
}ViewRuningAction;
//typedef enum GlobleUserType
//{
//	USER_GLOBLE_TYPE_SINGER			= 1,					//��˾ǩԼ����
//	USER_GLOBLE_TYPE_AGENT			= 2,					//��˾ǩԼ����
//	USER_GLOBLE_TYPE_CONTACT_STAFF	= 4,					//��˾�ͷ�
//	USER_GLOBLE_TYPE_SALES			= 8,					//��˾����
//	USER_GLOBLE_TYPE_PRIVILEGES		= 16,					//��Ȩ��־
//	USER_GLOBLE_TYPE_COO			= 32,					//վ����־
//}GlobleUserType;



typedef enum USER_RIGHT_FLAG
{
	USER_FLAG_MIC		= 0x0001,								//�Ƿ����ˣ�ָ�û��ն˲�����ˣ�����˵��ӵ��˵��Ȩ��
	USER_FLAG_CAMERA	= 0x0002,								//�Ƿ�������ͷ��ָ�û��ն˲�������ͷ������˵��ӵ����ƵȨ��
	USER_FLAG_INCONF	= 0x0004,								//�Ƿ��ڻ�����
	USER_FLAG_ROOM_VIP	= 0x0008,								//�Ƿ��Ƿ������շ��û�
}USER_RIGHT_FLAG;



enum
{
	CONF_STATUS_CLOSE,
	CONF_STATUS_OPEN,
	CONF_STATUS_FROZEN,
};

enum
{
	RES_CONF_INVITE_ACCEPT,										//��������
	RES_CONF_INVITE_REFUSE,										//�ܾ�����
	RES_CONF_INVITE_CANT_ACCEPT,								//�޷���������,���е��޷���ȷ������޷���������
	RES_CONF_INVITE_BUSY,										//�û�æµ�޷���������
	RES_CONF_INVITE_AV_BUSY,									//����Ƶռ��,�޷���������
	RES_CONF_INVITE_A_BUSY,										//��Ƶռ��,�޷���������
	RES_CONF_INVITE_V_BUSY,										//��Ƶռ��,�޷���������
};

#ifndef MAX_MIC_USER_NUM
#	define MAX_MIC_USER_NUM				4						//�������
#endif

class StampUserItem           //�û����µ���Ϣ
{
public:
	enum
	{
		MAX_STAMP_TEXT = 12,									//������������Ϣ��		
	};
public:
	StampUserItem()
	{
		src = dst = stampTime = stampID = 0;
		memset(stampMsg, 0, sizeof(stampMsg));
	}

	StampUserItem& operator=(const StampUserItem& smpItem)
	{
		if(this == &smpItem)
			return *this;

		src = smpItem.src;
		dst = smpItem.dst;
		stampID = smpItem.stampID;
		stampTime = smpItem.stampTime;
		memcpy(stampMsg,smpItem.stampMsg,sizeof(stampMsg));
		return *this;
	}

	StampUserItem(const StampUserItem& smpItem)
	{
		*this = smpItem;
	}
public:
	uint32 src;				//��ʾ�ͳ������������
	uint32 dst;				//��ʾ�����µ���
	uint16 stampID;
	uint32 stampTime;
	char   stampMsg[MAX_STAMP_TEXT+1];
};

#endif
