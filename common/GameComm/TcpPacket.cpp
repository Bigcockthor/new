#include "TcpPacket.h"


#include <string.h>

void OutPacketEx::write8(uint8 b)
{
	if(data + currentBuffSize >= cursor + sizeof(uint8))
	{
		memcpy(cursor, &b, sizeof(uint8));
		cursor += sizeof(uint8);
	}
}
void OutPacketEx::write16(uint16 w)
{
	if(data + currentBuffSize >= cursor + sizeof(uint16))
	{
		memcpy(cursor, &w, sizeof(uint16));
		cursor += sizeof(uint16);
	}
}
void OutPacketEx::write32(uint32 dw)
{
	if(data + currentBuffSize >= cursor + sizeof(uint32))
	{
		memcpy(cursor, &dw, sizeof(uint32));
		cursor += sizeof(uint32);
	}
}

void OutPacketEx::writeString(const char *str, int n)
{
	if(str && data + currentBuffSize >= cursor + sizeof(int) + n)
	{
		uint16 len = n + 1;
		*this << len;
		memcpy(cursor, str, len);
		cursor += len;
	}
}
void OutPacketEx::writeLVSString(const char *str, int n)
{
	if(data + currentBuffSize >= cursor + n)
	{
		memcpy(cursor, str, n);
		cursor += n;
	}
}
void OutPacketEx::writeBinary(const char *str, int n)
{
	if (data + currentBuffSize >= cursor +n)
	{
		memcpy(cursor, str, n);
		cursor += n;
	}
}

uint32 InPacketEx::read32(void)

{
	uint32 ret = 0;
	if (data + datalen >= cursor + sizeof(uint32))
	{
		memcpy(&ret, cursor, sizeof(uint32));
		cursor += sizeof(uint32);
	}
	return ret;
}
uint16 InPacketEx::read16(void)
{
	uint16 ret = 0;
	if (data + datalen >= cursor + sizeof(uint16))
	{
		memcpy(&ret, cursor, sizeof(uint16));
		cursor += sizeof(uint16);
	}

	return ret;
}

uint8 InPacketEx::read8(void)
{
	uint8 b = 0 ;
	if (data + datalen >= cursor + sizeof(uint8))
	{
		memcpy(&b, cursor, sizeof(uint8));
		cursor += sizeof(uint8);
	}
	return b;
}
uint16 InPacketEx::readLVSString(ICQ_STR &str)
{
	uint16 ret = 0;
	if (data + datalen >= cursor + str.len)
	{
		memcpy(&str.text, cursor, str.len);
		cursor += str.len;
	}
	return ret;
}

void InPacketEx::ReadData(char *buf, uint16 n)
{
	if (data + datalen >= cursor + n)
	{
		memcpy(buf, cursor, n);
		cursor += n;
	}
}
void InPacketEx::ReadString(string &str)
{
	if(data + datalen >= cursor + sizeof(int))
	{
		uint16 i = 0;
		*this >> i;
		if(i >= 0 && data + datalen >= cursor + i)
		{
			char *buf = new char[i +1];
			memcpy(buf, cursor, i);
			str.append(buf, i);
			delete buf;

		}
		cursor += i;
	}
	return;
}

void InPacketEx::ResolvHead()
{
	*this >> m_head.ver >> m_head.reserved >> m_head.uin >> m_head.sid >> m_head.cmd >> m_head.seq >> m_head.cc;
	if (m_head.cmd == 6)
	{
		return;
	}

}

//UniOutPacketEx::UniOutPacketEx()
//{
//
//}
//
//UniOutPacketEx::~UniOutPacketEx()
//{
//
//};
//
//void UniOutPacketEx::writeString(const char *str, int n)
//{
//// 	string temp;
//// #ifdef MARKUP_STL
//// 	temp = CMarkup::AToUTF8(str);
//// #else
//// 	temp = CMarkup::AToUTF8(str).GetBuffer();
//// #endif
//// 	OutPacket::writeString(temp.c_str(), temp.length());
//}
//
//UniInPacketEx::UniInPacketEx()
//{
//
//}
//
//UniInPacketEx::~UniInPacketEx()
//{
//
//}
//
//void UniInPacketEx::ReadString(string &str)
//{
//// 	string temp;
//// 	InPacket::ReadString(temp);
//// #ifdef MARKUP_STL
//// 	str = CMarkup::UTF8ToA(temp);
//// #else
//// 	str = CMarkup::UTF8ToA(temp.c_str()).GetBuffer();
//// #endif
//
//}