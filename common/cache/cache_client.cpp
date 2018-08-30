#include "cache_client.h"
#include "cachedefine.h"

CacheClient::CacheClient(void)
{
}

CacheClient::~CacheClient(void)
{
}

void CacheClient::DBhLoadPartnerInfo(TCPSRV_CALLBACK callback, uint32 pid)
{
	TcpSrvReq* req = m_dbhCache->BuildTcpSrvReq(1, callback, CACHE_IM_PARTNER_INFO_XML, 
		"d", pid);
	if (req)
	{
		req->setparam(0, (uint32)this);
		int nret = m_dbhCache->PostTcpSrvReq(req);
		if(nret != 0)
			req->release();
	}
}
