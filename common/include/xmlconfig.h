#pragma once
#ifndef MARKUP_STL
#define MARKUP_STL
#endif
#include "Markup.h"
#include <string>
#include "icqtypes.h"

namespace WingUtil
{
	using namespace std;

	class  CXmlConfig :	public CMarkup
	{
	public:
		CXmlConfig(void);
		virtual ~CXmlConfig(void);

		uint32 ReadIp(string fieldName, uint32 defaultValue = 0);
		uint16 ReadPort(string fieldName, uint16 defaultValue = 0);
		uint32 ReadInt(string fieldName, uint32 defaultValue = 0);
		uint64 ReadInt64(string fieldName, uint32 defaultValue = 0);
		uint16 Readuint16(string fieldName, uint16 defaultValue = 0);
		string ReadString(string fieldName, string defaultValue = "");
	};

};

