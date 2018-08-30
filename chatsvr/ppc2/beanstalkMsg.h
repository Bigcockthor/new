/***********************************************************************************************
// �ļ���:     beanstalkMsg.h
// ������:     ���˽�
// Email:      linux_xuyunjie@163.com
// ����ʱ��:   2014/1/14 16:20:20
// ��������:   msgswitch��beanstalk
// �汾��Ϣ:   1.0V
************************************************************************************************/
#ifndef INC_BEANSTALKMSG_H
#define INC_BEANSTALKMSG_H



#include <msgswitch/beanstalkclient.h>
#include "include/icqtypes.h"
#include "include/packet.h"
#include "include/tcppacket.h"
#include "bigroomdef.h"
#include "include/slab.h"
#include "include/xmlconfig.h"
#include "beanstalkdef.h"
#include "RoomManager.h"




using namespace BigRoom;



/** 
*\brief BeanstalkMsg�ӿ���
*/
class BeanstalkMsg: public BeanstanlkdClient
{

public:
	BeanstalkMsg(RoomManager* pMgr);
	~BeanstalkMsg();


public:
	/** 
	*\brief ResolvData 
	* ����job����jobת����message,������Ϣ�����ָ��
	*\param strData 
	*\return  
	*/
	virtual BCMessageBase * ResolvData(std::string &strData);
	
	/** 
	*\brief HandleBCMsg 
	*\����Ϣ������ȥ����Ȼ���� 
	*\return  
	*/
	virtual uint32 HandleBCMsg();
	void ProcessBcMsg(BCMessageBase* pMsg);

public:
	/** 
	*\brief Init 
	* beanstalk ��ʼ������
	*\param initinfo 
	*\return  
	*/
	bool Init(BeanstalkInfo& initinfo);


private:
	bool BuildModifyMgrMsg(std::string& strData, ModifyMgrMsg& newMoneyMsg);
	bool BuildNewMoneyMsg(std::string& strData, NewMoneyMsg& newMoneyMsg);
	bool BuildOfflineMsg(std::string& strData, ForceOfflineMsg& offlineMsg);
	RoomManager* m_pRoomManager;
	
};


#endif		

