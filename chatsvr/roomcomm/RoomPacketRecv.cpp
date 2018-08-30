 #include "include/debug_new.h"

#ifdef _ACE_SOCK
#undef _ACE_SOCK
#include "RoomPacketRecv.h"
#endif
#include "include/icqsocket.h"
#include "include/packet.h"
#include "include/log.h"
#include "include/socketaddress.h"

#include "room/RoomCmdDef.h"
#include "../tools/common.h"

//IMPLEMENT_SLAB(TransportPacket, 128)
const int nPacketMinLen	= sizeof(UDP_CLI_HDR);

RecvPacketHandle *gHandle = NULL;
#define USER_EVENT_BROADCAST	1000

RecvPacketRecv::RecvPacketRecv() : sock(INVALID_SOCKET)
{
}

RecvPacketRecv::~RecvPacketRecv(void)
{
}




void RecvPacketRecv::run( void *mParameter )
{
	while(!GetWillStop())
	{
		if (sock == INVALID_SOCKET)				//bind没有成功，sleep 500ms
		{
			mysleep(500);					
			continue;
		}

		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);

		timeval to;
		to.tv_sec = 2;
		to.tv_usec = 0;
		
		int n = select(sock+1, &readfds, NULL, NULL, &to);
		if (n > 0 && handle) 
		{
			
			UdpInPacket *in = new UdpInPacket(this==&handle->GetDirectRecv());

			if (in)
			{
				int n = in->udprecv(sock);
				in->channel = ROOM_UDPSERVER;
				if (n < (int)sizeof(UDP_CLI_HDR) || !handle->OnData(in))
				{
					delete in;
					continue;
				}
			}
		}

	}
}

bool RecvPacketRecv::Init(uint32 bindIP, uint16 bindPort, RecvPacketHandle *mHandle)
{
	if (sock != INVALID_SOCKET)
		myclose(sock);

	sock = CoreSocket::UDPBind(bindIP, bindPort);
	if (sock == INVALID_SOCKET)
		return false;

	handle = mHandle;

	LOG(1)("RecvPacketRecv::Init\n");
	CoreThread::CreateNewThread(this, NULL);


	return true;
}

int RecvPacketHandle::SendData(OutPacket *out, uint32 ip, uint16 port, uint32 proxyIP, uint16 proxyPort)
{
	if (!proxyIP)
		return out->udpsend(gHandle->GetDirectRecv().GetSock(), ip, port);
	else
	{
		return out->udpsend(gHandle->GetProxyRecv().GetSock(), proxyIP, proxyPort);
	}

}

RecvPacketHandle::RecvPacketHandle()
{
	gHandle = this;
}

RecvPacketHandle::~RecvPacketHandle()
{
	gHandle = NULL;
}


TcpRecvPacketHandle::TcpRecvPacketHandle()
{
	memset(m_servers, 0, sizeof(m_servers));
}

TcpRecvPacketHandle::~TcpRecvPacketHandle()
{
	if(m_servers[ROOM_TCPSERVER])
	{
		m_servers[ROOM_TCPSERVER]->ShutDown();
		delete m_servers[ROOM_TCPSERVER];
		m_servers[ROOM_TCPSERVER] = NULL;
	}

	if(m_servers[ROOM_TCPPROXY])
	{
		m_servers[ROOM_TCPPROXY]->ShutDown();
		delete m_servers[ROOM_TCPPROXY];
		m_servers[ROOM_TCPPROXY] = NULL;
	}
	
}

bool TcpRecvPacketHandle::InitTcpServer(uint32 ip, uint16 port, uint32 proxyIp, uint16 proxyPort, uint32 webIp, uint16 webPort)
{
	
	m_servers[ROOM_TCPSERVER] = new TcpServer(ROOM_TCPSERVER, ip, port);
	if(!m_servers[ROOM_TCPSERVER]->Start((CTLTcpEventCustomer*)this))
	{
		return false;
	}
	m_servers[ROOM_TCPPROXY] = new TcpServer(ROOM_TCPPROXY, proxyIp, proxyPort);
	if(!m_servers[ROOM_TCPPROXY]->Start((CTLTcpEventCustomer*)this))
	{
		return false;
	}

	if(webPort)
	{
		m_servers[ROOM_TCPWEB] = new TcpServer(ROOM_TCPWEB, webIp, webPort);
		if(!m_servers[ROOM_TCPWEB]->Start((CTLTcpEventCustomer*)this))
		{
			return false;
		}
	}

	return m_servers[ROOM_TCPSERVER] && m_servers[ROOM_TCPSERVER]->NetWorkReady() && m_servers[ROOM_TCPPROXY] && m_servers[ROOM_TCPPROXY]->NetWorkReady();


}

void TcpRecvPacketHandle::OnClose(int serverIndex, const CTLConnection *cn)
{
	LOG(1)("serverIndex %d %s:%d closed\n", serverIndex, NIP2CHAREX(cn->ip), ntohs(cn->port));
	if(serverIndex == ROOM_TCPWEB)
	{
		MutexObject lock(&m_lock);
		IpPort ipInfo;
		ipInfo.ip = cn->ip;
		ipInfo.port = cn->port;
		m_connectList.erase(ipInfo.data);
	}
}
void TcpRecvPacketHandle::OnNewConnection(int serverIndex, const CTLConnection *cn)
{
	LOG(1)("serverIndex %d %s:%d connected\n", serverIndex, NIP2CHAREX(cn->ip), ntohs(cn->port));
	if(serverIndex == ROOM_TCPWEB)
	{
		MutexObject lock(&m_lock);
		IpPort ipInfo;
		ipInfo.ip = cn->ip;
		ipInfo.port = cn->port;
		m_connectList[ipInfo.data] = ipInfo;
#ifdef WIN32
		ipInfo.verify = 1;//直接验证通过
#endif

	}
}
void TcpRecvPacketHandle::OnTcpDataReceived(int serverIndex, const CTLConnection *cn, const char *buf, int len)
 {
	if(len < nPacketMinLen)
	{
		return;
	}
	UdpInPacket* in = new UdpInPacket(ROOM_TCPPROXY != serverIndex);
	in->setdata(buf, len);
	in->channel = serverIndex;
	if(ROOM_TCPPROXY == serverIndex)
	{
		in->proxyIP = cn->ip;
		in->proxyPort = cn->port;
		LOG(6)("recv from %s:%d real from  %s:%d\n", NIP2CHAREX(in->proxyIP), htons(in->proxyPort),  NIP2CHAREX(in->ip), htons(in->port));
	}
	else if(ROOM_TCPSERVER == serverIndex)
	{
		in->port = cn->port;
		in->ip = cn->ip;

	}
	else if(ROOM_TCPWEB == serverIndex)
	{
		LOG(6)("ROOM_TCPWEB recv from %s:%d real from  %s:%d\n", NIP2CHAREX(in->proxyIP), htons(in->proxyPort),  NIP2CHAREX(in->ip), htons(in->port));
	}
	else
	{
		LOG(1)("OnTcpDataReceived: error serverIndex %d\n", serverIndex);
		return ;
	}
	if(!OnData(in, serverIndex))
	{
		delete in;
	}
}

void TcpRecvPacketHandle::OnSendError(int err_no, void *param)
{
	//if(NULL == param)
	//{
	//	LOG(1)("OnSendError:: NULL param errno %d", err_no);
	//	return;
	//}
	
	LOG(1)("OnSendError:: errno %d  \n", err_no);
	
}

int TcpRecvPacketHandle::SendTcpData(int serverIndex, OutPacket *out, uint32 ip, uint16 port, uint32 proxyIP, uint16 proxyPort)
{
		if(ROOM_TCPPROXY == serverIndex)
		{
			 m_servers[ROOM_TCPPROXY]->PushData(proxyIP, proxyPort, out->GetData(), out->getdatalen());
			 LOG(6)("ROOM_TCPPROXY sendto %s %d  len %d\n",  NIP2CHAREX(proxyIP), ntohs(proxyPort), out->getdatalen());
		}
		else if(ROOM_TCPSERVER == serverIndex)
		{
			m_servers[ROOM_TCPSERVER]->PushData(ip, port, out->GetData(), out->getdatalen());
			LOG(6)("ROOM_TCPSERVER sendto %s %d  len %d\n",  NIP2CHAREX(ip), ntohs(port), out->getdatalen());
		}
		else if(ROOM_TCPWEB == serverIndex)
		{
			MutexObject lock(&m_lock);
			ConnectIpInfoList::iterator iter = m_connectList.begin();
			for(; iter != m_connectList.end(); iter++)
			{
				m_servers[ROOM_TCPWEB]->PushData(iter->second.ip, iter->second.port, out->GetData(), out->getdatalen());
				LOG(6)("ROOM_TCPSERVER sendto %s %d  len %d\n",  NIP2CHAREX(iter->second.ip), ntohs(iter->second.port), out->getdatalen());
			}

		}
		
		
	return 0;

}


int TcpRecvPacketHandle::SendTcpDataAll(int serverIndex, OutPacket *out)
{
	EvBufferEx  * evb = new EvBufferEx(serverIndex, 0);
	evb->AddBuffer(out->GetData(), out->getdatalen());
	m_servers[serverIndex]->NotifyUserEvent(USER_EVENT_BROADCAST, evb);
	return 0;

}

void TcpRecvPacketHandle::OnUserEvent( uint32 eventid, void* para )
{
	EvBufferEx  * evb = (EvBufferEx*) para;
	if(!evb)
	{
		return;
	}
	if(evb->dstIP < ROOM_MAXSERVER)
	{
		m_servers[evb->dstIP]->SendBroadcast(evb->GetData(), evb->Getdatalen(), NULL);
	}
	
	delete evb;
}





TcpServer::TcpServer( int idx, uint32 bindIP, uint16 bindPort )
	:CTLEventTcpServer(idx, bindIP, bindPort)
{

}

int TcpServer::SendBroadcast( const char *buf, int len, void *param )
{
	ConnectionMap* connMap =  sessionMgr.GetConnMap();
	ConnectionMap::iterator iter = connMap->begin();
	for( ; iter != connMap->end(); iter ++)
	{
		if(iter->second != param)
		{
			SendData(iter->second, buf, len, param);
		}
		
	}
	return 0;
}

TcpServer::~TcpServer()
{

}
