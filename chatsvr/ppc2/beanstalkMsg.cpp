#include "beanstalkMsg.h"
#include "include/log.h"
#include "include/debug_new.h"
#include "msgswitch/msgswitchdef.h"
#include "include/base64.h"

#ifdef WIN32
#define atoll _atoi64
#endif


BeanstalkMsg::BeanstalkMsg(RoomManager* pMgr)
{
	m_pRoomManager = pMgr;		
}

BeanstalkMsg::~BeanstalkMsg()
{

}

bool BeanstalkMsg::Init(BeanstalkInfo& initinfo)
{
	if(OpenClient(initinfo.host, initinfo.port, initinfo.conn_timeout,&(initinfo.swatchList)))
	{
		LOG(1)("beanstalkMsg connect failed, host = %s port = %d", initinfo.host.c_str(), initinfo.port);
		return false;
	}
	LOG(4)("beanstalkMsg client start success!");
	
	return true;
}


bool BeanstalkMsg::BuildOfflineMsg(std::string& strData, ForceOfflineMsg& offlineMsg)
{
	std::string strTemp;

	int nRet = -1;
	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_roomid = atoi(strTemp.c_str());

	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_uin = atoi(strTemp.c_str());

	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_newRoomid = atoi(strTemp.c_str());


	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_newip = atoi(strTemp.c_str());


	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_newport = atoi(strTemp.c_str());


	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_devType = atoi(strTemp.c_str());

	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	offlineMsg.m_newMac = atoll(strTemp.c_str());
	

	return true;

}
bool BeanstalkMsg::BuildNewMoneyMsg(std::string& strData, NewMoneyMsg& newMoneyMsg)
{
	std::string strTemp;
	std::string strUin;
	int nRet = -1;
	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}

	nRet = SplitMsg(strTemp,":", strUin);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.srcuin = atoll(strUin.c_str());
	newMoneyMsg.srcMoney = atoll(strTemp.c_str());


	nRet = SplitMsg(strData,":", strUin);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.dstuin = atoll(strUin.c_str());
	newMoneyMsg.dstMoney = atoll(strData.c_str());
	return true;
}


bool BeanstalkMsg::BuildModifyMgrMsg(std::string& strData, ModifyMgrMsg& newMoneyMsg)
{
	std::string strTemp;

	int nRet = -1;
	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.m_roomid = atoi(strTemp.c_str());

	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.m_src = atoi(strTemp.c_str());

	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.m_dst = atoi(strTemp.c_str());


	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		return false;
	}
	newMoneyMsg.m_action = atoi(strTemp.c_str());

	return true;
}

BCMessageBase* BeanstalkMsg::ResolvData(std::string &strData)//解析job，把job转换成message,然后放进消息队列中
{

	std::string strTemp;
	std::string strMsg = strData;
	int nRet = -1;
	nRet = SplitMsg(strData,"#", strTemp);
	if(nRet)
	{
		LOG(4)( "BeanstalkMsg::ResolvData SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
		return NULL;
	}

	if (strData.empty())//无效数据
	{
		LOG(4)( "BeanstalkMsg::ResolvData inval data is empty\n");
		return NULL;
	}
	uint32 nMsgType = atoi(strTemp.c_str());
	BCMessageBase* bcMessage = NULL;
	switch(nMsgType)
	{
	case UDP_MAN_GLOBLE_MSG:
			{
				GlobalMsg* pGlobaltMsg = new GlobalMsg(nMsgType);

				string decodedMsg = talk_base::Base64::decode(strData);

				pGlobaltMsg->m_in.setdata(decodedMsg.c_str(), decodedMsg.length());


				bcMessage = pGlobaltMsg;

				break;
			}
		case UDP_MAN_GLOBLE_MSG2:
			{
				GreatGiftMsg* pCreatGiftMsg = new GreatGiftMsg(nMsgType);

				string decodedMsg = talk_base::Base64::decode(strData);


				pCreatGiftMsg->m_out.writeBinary(decodedMsg.c_str(), decodedMsg.length());

				bcMessage = pCreatGiftMsg;

				break;
			}
		case UDP_MAN_GLOBLE_MSG3:
			{
				GlobalMsgXML* pGlobalMsgXML = new GlobalMsgXML(nMsgType);

				pGlobalMsgXML->m_msgTemp.ParseXML(strData);


				bcMessage = pGlobalMsgXML;
				break;
			}
		case UDP_MAN_DESTORYROOM: //重启房间 no need break;
		case UDP_MAN_HDR_MODIFYINFO:
			{
				RoomInfoMsg* pUpdateRoomInfoMsg = new RoomInfoMsg(nMsgType);

				nRet = SplitMsg(strData,"#", strTemp);

				if(nRet)
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_HDR_MODIFYINFO SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pUpdateRoomInfoMsg;
					pUpdateRoomInfoMsg = NULL;
					return NULL;
				}

				pUpdateRoomInfoMsg->m_nFid = atoi(strTemp.c_str());

				bcMessage = pUpdateRoomInfoMsg;

				break;
			}
		case UDP_MAN_NOTIFYNEWMONEY://web转账
			{
				NewMoneyMsg* pNewMoneyMsg = new NewMoneyMsg(nMsgType);
				if(!BuildNewMoneyMsg(strData, *pNewMoneyMsg))
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_NOTIFYNEWMONEY SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pNewMoneyMsg;
					pNewMoneyMsg = NULL;
					return NULL;
				}


				bcMessage = pNewMoneyMsg;
				break;
			} 
		case UDP_MAN_GENERAL_MSG:
			{
				GameMsg* pGameMsg = new GameMsg(nMsgType);

				nRet = SplitMsg(strData,"#", strTemp);
				if(nRet)
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_GENERAL_MSG SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pGameMsg;
					pGameMsg = NULL;
					return NULL;

				}
				pGameMsg->m_nDestRoom = atoi(strTemp.c_str());
				pGameMsg->m_strData = strData;

				LOG(4)( "BeanstalkMsg::get a  UDP_MAN_GENERAL_MSG job destroom=%d msg=%s\n",pGameMsg->m_nDestRoom, pGameMsg->m_strData.c_str());
				bcMessage = pGameMsg;
				break;
			}
		case UDP_MAN_NOTIFYFORCEOFFLINE:
			{
				ForceOfflineMsg* pOfflineMsg = new ForceOfflineMsg(nMsgType);
				if(!BuildOfflineMsg(strData, *pOfflineMsg))
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_NOTIFYFORCEOFFLINE SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pOfflineMsg;
					pOfflineMsg = NULL;
					return NULL;

				}

				//LOG(4)( "BeanstalkMsg::get a  UDP_MAN_NOTIFYFORCEOFFLINE job roomid=%u uin=%u devType=%d\n",pOfflineMsg->m_roomid, pOfflineMsg->m_devType);
				bcMessage = pOfflineMsg;

				break;
			}
		case UDP_MAN_MODIFYMGRINFO:
			{
				ModifyMgrMsg* pModifyMgrMsg = new ModifyMgrMsg(nMsgType);
				if(!BuildModifyMgrMsg(strData, *pModifyMgrMsg))
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_MODIFYMGRINFO SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pModifyMgrMsg;
					pModifyMgrMsg = NULL;
					return NULL;

				}

				bcMessage = pModifyMgrMsg;
				break;
			}
		case UDP_MAN_FORMAL_OPERATION:
			{
				BCMessageBase* pMsg = new BCMessageBase(nMsgType);
				bcMessage = pMsg;
				break;
			}
		case UDP_MAN_NOTIFY_MSG:
			{
				GameMsg* pGameMsg = new GameMsg(nMsgType);

				nRet = SplitMsg(strData,"#", strTemp);
				if(nRet)
				{
					LOG(4)( "BeanstalkMsg::ResolvData UDP_MAN_NOTIFY_MSG SplitMsg failed %s   strTemp = %s\n", strMsg.c_str(),  strTemp.c_str());
					delete pGameMsg;
					pGameMsg = NULL;
					return NULL;

				}
				pGameMsg->m_nDestRoom = atoi(strTemp.c_str());
				pGameMsg->m_strData = strData;

				LOG(4)( "BeanstalkMsg::get a  UDP_MAN_GENERAL_MSG job destroom=%d msg=%s\n",pGameMsg->m_nDestRoom, pGameMsg->m_strData.c_str());
				bcMessage = pGameMsg;
				break;
			}
		default:
			{
				LOG(4)("beanstalk unknow msgType=%d!\n", nMsgType);
				break;
			}

	}
	
	


	if(bcMessage)
	{
		ACE_Message_Block* mb = NULL;
		ACE_NEW_MALLOC_NORETURN (mb,
			ACE_static_cast
			(	ACE_Message_Block*,
			RoomManager::_buf_allocator->malloc (sizeof (ACE_Message_Block))
			),
			ACE_Message_Block
			(sizeof(dataport::CDBClientResult*), // size
			MB_BEANSTALK, // type
			0,
			0,
			RoomManager::_buf_allocator, // allocator_strategy
			0, // locking strategy
			ACE_DEFAULT_MESSAGE_BLOCK_PRIORITY, // priority
			ACE_Time_Value::zero,
			ACE_Time_Value::max_time,
			RoomManager::_buf_allocator,
			RoomManager::_buf_allocator
			)
			);	

		if(!mb)
			return bcMessage;


		BCMessageBase** loadin = (BCMessageBase**)mb->base();
		*loadin = bcMessage;
		ACE_Time_Value xtime(ACE_OS::gettimeofday()+g_puttimeout);
		if(RoomManager::gRoot->putq(mb, &xtime) == -1)
		{
			LOG(1)("put BeanstalkMsg failed\n");
			mb->release();
			return bcMessage;
		}
	}
	return NULL;
}

uint32 BeanstalkMsg::HandleBCMsg()				//从消息队列中去数据,然后处理
{
	BCMessageBase* pMsg = NULL;
	while((pMsg = GetOneMsg()))
	{
		ProcessBcMsg(pMsg);
		if(pMsg)
		{
			delete pMsg;
			pMsg = NULL;
		}
		
	}
	
	return 0;
}




void BeanstalkMsg::ProcessBcMsg(BCMessageBase* pMsg)
{
	if(!pMsg)
	{
		return;
	}
	switch(pMsg->m_msgType)
	{
	case UDP_MAN_HDR_MODIFYINFO:
		{
			RoomInfoMsg* pUpdateRoomInfoMsg = (RoomInfoMsg*)pMsg;

			m_pRoomManager->UpdateRoomInfo(pUpdateRoomInfoMsg->m_nFid);

			LOG(4)( "BeanstalkMsg::get a  UDP_MAN_HDR_MODIFYINFO job fid=%d\n", pUpdateRoomInfoMsg->m_nFid);
			break;
		}
	
	default:
		{
			LOG(4)( "BeanstalkMsg::get a  unknow job  msgType=%d\n", pMsg->m_msgType);
			break;
		}
	}

}











