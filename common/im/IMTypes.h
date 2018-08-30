#ifndef _IMTYPES_TYPES_H_
#define _IMTYPES_TYPES_H_

#include <string>
#include <list>
#include <vector>
#include <bitset>
#include "include/icqtypes.h"

using namespace std;

typedef struct ProxyServerItem
{
	uint32 ip;
	uint8 nettype;
}ProxyServerItem;


typedef list<string> 	StrList;
typedef list<void *>	PtrList;
typedef list<uint32>	UinList;
typedef list<uint32>	RoomList;
typedef list<ProxyServerItem>	ProxyList;

#ifdef _WIN32
#define strncasecmp		_strnicmp
#define strcasecmp		_stricmp
#endif

struct MQ_STR {
	const char *text;
	uint16 len;
};



#ifndef SAFE_CLEAR_PRTLIST
#define SAFE_CLEAR_PRTLIST(lst, type)   for (PtrList::iterator it = (lst).begin(); it!=(lst).end(); it++) \
{\
	if ((*it) != NULL) \
	delete (type *)(*it);\
}	\
	(lst).clear();
#endif

struct HtmlFontItem
{
public:
	string m_FontName;
	string m_FontSize;
	string m_FontColor;
	string m_ItmeName;
	HtmlFontItem()
	{
		m_FontName = "ËÎÌו";
		m_FontSize = "9.0pt";
		m_FontColor = "#0080FF";
	}
};

#endif
