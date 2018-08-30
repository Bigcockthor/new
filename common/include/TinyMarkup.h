#ifndef  _TINY_MARKUP_KJHIOWEIOJKDMSSSIDIDIDISOSOSOSKKKD__
#define _TINY_MARKUP_KJHIOWEIOJKDMSSSIDIDIDISOSOSOSKKKD__
#include "Markup.h"
#include <stdio.h>

class  TinyMarkup : public CMarkup
{
public:


	int GetChildValue(std::string key, std::string &v)
	{
		if (FindElem( key.c_str()))
		{
			v = GetData();
			return 0;
		}
		else
			return -1;
	}

	bool GetChildValue(std::string key, uint32 &v)
	{
		v =  (uint32)GetChildValue(key);
		return true;
	}
	bool GetChildValue(std::string key, uint16 &v)
	{
		v = (uint16)GetChildValue(key);

		return true;
	}
	bool GetChildValue(std::string key, uint8 &v)
	{
		v = (uint8)GetChildValue(key);

		return true;
	}
	void GetChildValue(std::string key, uint64 &v)
	{
		v = (uint64)GetChildValueInt64(key);


	}
	void GetChildValue(std::string key, int64 &v)
	{
		v = GetChildValueInt64(key);

	}



	bool AddElemInt64( std::string szName, int64 nValue, int nFlags=0 )
	{
		char buf[128] = {0};

#ifdef _WIN32
		_snprintf(buf, sizeof(buf)-1, "%I64d", nValue);
#else
		snprintf(buf, sizeof(buf)-1, "%lld", nValue);
#endif
		return CMarkup::AddElem(szName.c_str(), buf, nFlags);
	}

public:

	int GetChildValue(std::string key)
	{
		if (FindElem( key.c_str()))
		{
#if defined(MARKUP_STL)
			return (int)atol(GetData().c_str());
#else
			return (int)atol(GetData());
#endif

		}
		else
			return 0;
	}
	int64 GetChildValueInt64(std::string key)
	{
		std::string vStr;

		GetChildValue(key, vStr);

#ifdef _WIN32
		return  _atoi64(vStr.c_str());
#else
		return atoll(vStr.c_str());
#endif
	}
};


#endif



