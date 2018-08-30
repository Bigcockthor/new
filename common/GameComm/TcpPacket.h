#ifndef TCP_PACKET_H
#define TCP_PACKET_H

#ifdef WIN32
#include <WinSock2.h>
#else
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#endif
#include <string>
#include <string.h>
#include <stdio.h>
#include "include/icqtypes.h"
#include "include/base64.h"

using namespace std;

#define _MAX_PACKET_SIZE	2000


struct TCP_CLI_HDR 
{
	uint16 ver;
	uint32 reserved;
	uint32 uin;
	uint32 sid;
	uint16 cmd;
	uint16 seq;
	uint16 cc;		// check code
};

#ifndef ANDROID_COMM
typedef std::string NickString;
#else
class CNickString:public std::string
{
public:
	CNickString(){}
	CNickString(const CNickString &temp)
	{
		*this = temp;
	}
	CNickString &operator = (const CNickString & temp)
	{
		this->clear();
		this->append(temp.c_str(), temp.length());
		return *this;
	}
	CNickString &operator = (const std::string & temp)
	{
		this->clear();
		this->append(temp.c_str(), temp.length());
		return *this;
	}
};
typedef CNickString NickString;
#endif

class PacketEx{
public:
	PacketEx() : data(cacheBuffer), cursor(cacheBuffer), currentBuffSize(_MAX_PACKET_SIZE),
		ip(0), port(0)
	{
		memset(data, 0, sizeof(data));
	}
	virtual ~PacketEx(){}
	const char *getcursor(void) const {return (const char *)cursor;}
	const void SetBuffer(char *buf, int bufSize)
	{
		if (!buf && !bufSize)
			return;

		data = cursor = (uint8 *)buf;
		currentBuffSize = bufSize;
	}
protected:
	uint8 *data;
	uint8 *cursor;
	int currentBuffSize;
private:
	uint8 cacheBuffer[_MAX_PACKET_SIZE]; 
public:
	uint32 ip;
	uint16 port;

	const char * GetData(void) const { return (const char *)data; };
	//int reinit(void);
	int GetBufferSize() const { return currentBuffSize; }
};

class  OutPacketEx : public PacketEx {
public:
	OutPacketEx() : PacketEx()
	{
		expire = 0;
		attempts = 0;
		cmd = 0;
		seq = 0;
	}
	virtual void write8(uint8 b);
	virtual void write16(uint16 w);
	virtual void write32(uint32 dw);

	OutPacketEx &operator <<(uint8 b)
	{
		write8(b);
		return *this;
	}
	OutPacketEx &operator <<(bool b)
	{
		*this << (uint8)b;
		return *this;
	}
	OutPacketEx &operator <<(uint16 w) {
		write16(htons(w));
		return *this;
	}
	OutPacketEx &operator <<(uint32 dw) {
		write32(htonl(dw));
		return *this;
	}
	OutPacketEx &operator <<(uint64 u64) 
	{
		writeBinary((char *)&u64, sizeof(uint64));
		return *this;
	}
	OutPacketEx &operator <<(float df) {
		writeBinary((const char *)&df, sizeof(df));
		return *this;
	}
	OutPacketEx &operator <<(double dd) {
		writeBinary((const char *)&dd, sizeof(dd));
		return *this;
	}
	OutPacketEx &operator <<(ICQ_STR &str) {
		writeString(str.text, str.len);
		return *this;
	}
	OutPacketEx &operator <<(const char *str) {
		writeString(str, (int)strlen(str));
		return *this;
	}
	OutPacketEx &operator <<(const string str) {
		writeString(str.c_str(), (int)str.length());
		return *this;
	}

	virtual void writeString(const char *str, int n);
	virtual void writeLVSString(const char *str, int n);
	virtual void writeBinary(const char *str, int n);

	virtual uint8 *skip(int delta) {
		cursor += delta;
		return (cursor - delta);
	}

	virtual uint8 *setCursor(uint8 *cur) {
		uint8 *old = cursor;
		cursor = cur;
		return old;
	}
	const int getdatalen(void) const { return (const int)(cursor - data); };
public:
	uint32 expire;
	uint16 attempts;
	uint16 cmd;
	uint16 seq;
	string packetid;	//Ӧ�ò�id
};

class  InPacketEx : public PacketEx {
public:
	InPacketEx() {
		datalen = 0;
	}

	uint8 read8(void);
	uint32 read32(void);
	uint16 read16(void);
	uint16 readLVSString(ICQ_STR &str);

	InPacketEx &operator >>(uint8 &b)
	{
		b = read8();
		return *this;
	}
	InPacketEx &operator >>(bool &b)
	{
		uint8 ret;
		*this >> ret;

		b = ret ? true : false;

		return *this;
	}
	InPacketEx &operator >>(uint16 &w) {
		w = ntohs(read16());
		return *this;
	}
	InPacketEx &operator >>(uint32 &dw) {
		dw = ntohl(read32());
		return *this;
	}
	InPacketEx &operator >>(uint64 &u64){
		char *u = (char *)&u64;
		ReadData(u, sizeof(uint64));
		return *this;
	}
	InPacketEx &operator >>(float &df) {
		ICQ_STR temp;
		temp.len = sizeof(float);
		readLVSString(temp);
		df = *(float *)temp.text;
		return *this;
	}
	InPacketEx &operator >>(double &dd) {
		ICQ_STR temp;
		temp.len = sizeof(double);
		readLVSString(temp);
		dd = *(double *)temp.text;
		return *this;
	}
	InPacketEx &operator >>(ICQ_STR &str);
	InPacketEx &operator >>(string &str)
	{
		ReadString(str);
		return *this;
	}

#ifdef ANDROID_COMM	//andorid nickʹ��base64�����ֹ��emoji������ʧ��
	InPacketEx &operator >>(NickString &str)
	{
		ReadString(str);
		str = talk_base::Base64::encode(str);
		return *this;
	}
#endif
	void ReadData(char *buf, uint16 n);
	virtual void ReadString(string &str);
	void ResolvHead();
protected:
	uint16 datalen;
public:
	TCP_CLI_HDR m_head;
	const uint16 getdatalen(void) const 
	{
		return (const int)datalen; 
	}
	virtual void SetDatalen(int len)  
	{
		datalen += len; 
		if (datalen > currentBuffSize)
			datalen = currentBuffSize;
	}

	virtual void setdata(const char *buf, const uint16 buflen)
	{
		datalen = buflen>currentBuffSize?currentBuffSize:buflen;
		if ((uint8 *)buf != data)
			memcpy(data, buf, datalen);
	}

	const int getRemain(void){const int remain=datalen-(int)(cursor-data); return remain;};
};


//
//class UniOutPacketEx : public OutPacketEx
//{
//public:
//	UniOutPacketEx();
//	~UniOutPacketEx();
//	virtual void writeString(const char *str, int n);
//}; 
//
//class UniInPacketEx : public InPacketEx
//{
//public:
//	UniInPacketEx();
//	~UniInPacketEx();
//	virtual void ReadString(string &str);
//};
#endif
