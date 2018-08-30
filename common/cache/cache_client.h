#pragma once
#ifndef _CacheClient_DFKSDFLSDJKFKJSKSKFKNMVNMVJDSKS
#define _CacheClient_DFKSDFLSDJKFKJSKSKFKNMVNMVJDSKS
#include "cachesrvman.h"

class CacheClient
{
public:
	CacheClient(void);
	virtual ~CacheClient(void);

	void DBhLoadPartnerInfo(TCPSRV_CALLBACK callback, uint32 pid);
};


#endif

