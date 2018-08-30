/***********************************************************************************************
// 文件名:     beanstalkMsg.h
// 创建者:     徐运杰
// Email:      linux_xuyunjie@163.com
// 创建时间:   2014/1/14 16:20:20
// 内容描述:   msgswitch改beanstalk
// 版本信息:   1.0V
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
*\brief BeanstalkMsg接口类
*/
class BeanstalkMsg: public BeanstanlkdClient
{

public:
	BeanstalkMsg(RoomManager* pMgr);
	~BeanstalkMsg();


public:
	/** 
	*\brief ResolvData 
	* 解析job，把job转换成message,返回消息对象的指针
	*\param strData 
	*\return  
	*/
	virtual BCMessageBase * ResolvData(std::string &strData);
	
	/** 
	*\brief HandleBCMsg 
	*\从消息队列中去数据然后处理 
	*\return  
	*/
	virtual uint32 HandleBCMsg();
	void ProcessBcMsg(BCMessageBase* pMsg);

public:
	/** 
	*\brief Init 
	* beanstalk 初始化函数
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

