/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by eph                         *
 ***************************************************************************/

#ifndef _PACKET_H
#define _PACKET_H

#include "icqtypes.h"
#include "icqsocket.h"
#include <string.h>
#include <string>
#include "list.h"




using namespace std;

#define _MAX_PACKET_SIZE	1536
#define _MAX_PACKET_SIZE2	768





class  SetWindowBit32
{
public:
	SetWindowBit32();
	bool SetWindow(uint16 seq);
	void SetInitSeq(uint16 seq);
	void InitWindow();
private:
	uint32 window;
	uint32 lastSeq;
};

class  SetWindowByte
{
public:
	SetWindowByte();
	bool SetWindow(uint16 seq);
	void InitWindow();
	bool CheckWindow(uint16 seq);
private:
	uint8 seqwindow[1 << 16];
};


class  Packet {
public:
	Packet() : data(cacheBuffer), cursor(cacheBuffer), currentBuffSize(_MAX_PACKET_SIZE2),
		ip(0), port(0)
	{
		memset(data, 0, sizeof(data));
		newBuffer = NULL;
	}
	virtual ~Packet()
	{
		if (data != cacheBuffer && newBuffer == data)
		{
			delete data;
		}
	}
	const char *getcursor(void) const {return (const char *)cursor;}

	//do not free buf while destory
	const void SetBuffer(char *buf, int bufSize)
	{
		if (!buf && !bufSize)
			return;

		data = cursor = (uint8 *)buf;
		currentBuffSize = bufSize;
	}

	//can not use with SetBuffer, free newbuff while destory
	bool ReSizeBuf(int newSize);
protected:
	uint8 *data;
	uint8 *cursor;
	int currentBuffSize;
private:
	uint8 cacheBuffer[_MAX_PACKET_SIZE2]; 
	uint8 *newBuffer;
public:
	uint32 ip;
	uint16 port;

	const char * GetData(void) const { return (const char *)data; };
	int reinit(void);
	int GetBufferSize() const { return currentBuffSize; }
};





class  OutPacket : public Packet {
public:
	OutPacket(	) : Packet()
	{
		
	}
	virtual void write8(uint8 b);
	virtual void write16(uint16 w);
	virtual void write32(uint32 dw);

	OutPacket &operator <<(uint8 b)
	{
		write8(b);
		return *this;
	}
	OutPacket &operator <<(bool b)
	{
		*this << (uint8)b;
		return *this;
	}
	OutPacket &operator <<(uint16 w) {
		write16(htons(w));
		return *this;
	}
	OutPacket &operator <<(uint32 dw) {
		write32(htonl(dw));
		return *this;
	}
	OutPacket &operator <<(uint64 u64) 
	{
		writeBinary((char *)&u64, sizeof(uint64));
		return *this;
	}
	OutPacket &operator <<(float df) {
		writeBinary((const char *)&df, sizeof(df));
		return *this;
	}
	OutPacket &operator <<(double dd) {
		writeBinary((const char *)&dd, sizeof(dd));
		return *this;
	}
	OutPacket &operator <<(ICQ_STR &str) {
		writeString(str.text, str.len);
		return *this;
	}
	OutPacket &operator <<(const char *str) {
		writeString(str, (int)strlen(str));
		return *this;
	}
	OutPacket &operator <<(const string str) {
		writeString(str.c_str(), (int)str.length());
		return *this;
	}

	//先写入word表示长度，然后复制字符串本身,不带\0
	virtual void writeString(const char *str, int n);
	//复制字符串，没有前置长度，并以\0结束
	virtual void writeLVSString(const char *str, int n);
	//复制内存块，类似memcpy
	virtual void writeBinary(const char *str, int n);

	virtual uint16 GetPosition(uint16 delta);

	virtual uint16 SetPosition(uint16 newPosition);

	int udpsend(int sock, uint32 ip, uint16 port);
	static int sendbuf(int sock, uint32 ip, uint16 port, const char *buf, int len);
	int tcpsend(int _sock);

	const int getdatalen(void) const { return (const int)(cursor - data); };
};



class  InPacket : public Packet {
public:
	InPacket() {
		datalen = 0;
	}

	uint32 read32(void);
	uint16 read16(void);
	uint16 readLVSString(ICQ_STR &str);

	InPacket &operator >>(uint8 &b);
	InPacket &operator >>(bool &b)
	{
		uint8 ret;
		*this >> ret;

		b = ret ? true : false;

		return *this;
	}
	InPacket &operator >>(uint16 &w) {
		w = ntohs(read16());
		return *this;
	}
	InPacket &operator >>(uint32 &dw) {
		dw = ntohl(read32());
		return *this;
	}
	InPacket &operator >>(uint64 &u64){
		char *u = (char *)&u64;
		ReadData(u, sizeof(uint64));
		return *this;
	}
	InPacket &operator >>(float &df) {
		ICQ_STR temp;
		temp.len = sizeof(float);
		readLVSString(temp);
		df = *(float *)temp.text;
		return *this;
	}
	InPacket &operator >>(double &dd) {
		ICQ_STR temp;
		temp.len = sizeof(double);
		readLVSString(temp);
		dd = *(double *)temp.text;
		return *this;
	}
	InPacket &operator >>(ICQ_STR &str);
	InPacket &operator >>(string &str)
	{
		ReadString(str);

		return *this;
	}

	void ReadData(char *buf, uint16 n);
	virtual void ReadString(string &str);

	virtual int udprecv(int sock);

	int tcprecv(int sock);

	ListHead Q_Item;

protected:
	uint16 datalen;
public:
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
		if (ReSizeBuf(buflen))
		{
			datalen = buflen;
			memcpy(data, buf, datalen);
		}
	}
	
	const int getRemain(void){const int remain=datalen-(int)(cursor-data); return remain;};
};


// Large Packet

class  LargePacket
{
protected:
	enum
	{
		LP_MAX_PACKET_SIZE = 1024 * 10,
	};
	char *data;
	/// Pointer to beginning of next read.
	size_t rd_ptr_;

	/// Pointer to beginning of next write.
	size_t wr_ptr_;

	size_t recvLength;
	size_t Size;
private:
	char basedata[LP_MAX_PACKET_SIZE];
public:
	LargePacket(char* p, int sizeStr);
	LargePacket(int sizeStr = LP_MAX_PACKET_SIZE);
	virtual ~LargePacket();
	/// Get message data.
	char *base (void) const
	{
		return (char*)data;
	}

	void reset (void)
	{
		this->rd_ptr_ = 0;
		this->wr_ptr_ = 0;
	}

	size_t size (void) const
	{
		return Size;
	}

	size_t Segmentsize(void) const
	{
		return LP_MAX_PACKET_SIZE;
	}

	/// Get the read pointer.
	char *rd_ptr (void) const
	{
		return base() + rd_ptr_;
	}

	/// Set the read pointer to <ptr>.
	void rd_ptr (char *new_ptr)
	{
		rd_ptr_ = new_ptr - data;
	}

	/// Set the read pointer ahead <n> bytes.
	void rd_ptr (size_t n)
	{
		rd_ptr_ += n;
	}

	/// Get the write pointer.
	char *wr_ptr (void) const
	{
		return base() +wr_ptr_;
	}

	/// Set the write pointer to <ptr>.
	void wr_ptr (char *new_ptr)
	{
		wr_ptr_ = new_ptr - data;
	}

	/// Set the write pointer ahead <n> bytes.  This is used to compute
	/// the <length> of a message.
	void wr_ptr (size_t n)
	{
		wr_ptr_ += n;
	}

	/** @name Message length and size operations
	*
	* Message length is (wr_ptr - rd_ptr).
	*
	* Message size is capacity of the message, including data outside
	* the [rd_ptr,wr_ptr] range.
	*/
	//@{
	/// Get the length of the message
	size_t length (void) const
	{
		 return wr_ptr_ - rd_ptr_;
	}

	/// Set the length of the message
	void length (size_t n)
	{
		wr_ptr_ = rd_ptr_ + n;
	}

protected:
	void relloc_ptr(uint32 nsize = LP_MAX_PACKET_SIZE);

//    static LargePacket_Allocator *m_pAllocator;

};

class  LargeOutPacket : public LargePacket 
{
public:
	LargeOutPacket(int sizeStr = LP_MAX_PACKET_SIZE);

	virtual ~LargeOutPacket();
	
	void write8(uint8 b);
	void write16(uint16 w);
	void write32(uint32 dw);

	LargeOutPacket &operator <<(uint8 b);
	LargeOutPacket &operator <<(uint16 w) {
		write16(htons(w));
		return *this;
	}
	LargeOutPacket &operator <<(uint32 dw) {
		write32(htonl(dw));
		return *this;
	}
#ifdef _WIN32
	LargeOutPacket &operator <<(DWORD dw) {
		write32(htonl(dw));
		return *this;
	}
#endif
	LargeOutPacket &operator <<(uint64 u64)
	{
		memcpy(wr_ptr(), &u64, sizeof(uint64));
		wr_ptr(sizeof(uint64));
		return *this;
	}

	LargeOutPacket &operator <<(int64 i64)
	{
		memcpy(wr_ptr(), &i64, sizeof(uint64));
		wr_ptr(sizeof(int64));
		return *this;
	}

	LargeOutPacket &operator <<(ICQ_STR &str) {
		writeString(str.text, str.len);
		return *this;
	}
	LargeOutPacket &operator <<(const char *str) {
		writeString(str, strlen(str));
		return *this;
	}
	LargeOutPacket &operator <<(const string &str) 
	{
		writeString(str.c_str(), str.length());
		return *this;
	}
	virtual void writeString(const char *str, int n);
	void directwr16(char* p, uint16 w);
	void directwr32(char* p, uint32 w);
	
	uint8 *skip(int delta) {
		//		cursor += delta;
		//		return (cursor - delta);
		wr_ptr(delta);
		return (uint8*)(wr_ptr()- delta);
	}
	uint8 *setCursor(uint8 *cur) {
		//		uint8 *old = cursor;
		//		cursor = cur;
		uint8 *old = (uint8*)wr_ptr();
		wr_ptr((char*)cur);
		return old;
	}
};

class  LargeInPacket : public LargePacket 
{
public:
	LargeInPacket();
	LargeInPacket(char* p, int sizeStr);
	LargeInPacket(int sizeStr);
	virtual ~LargeInPacket();

	
	uint32 read32();
	uint16 read16();
	
	LargeInPacket &operator >>(uint8 &b);
	LargeInPacket &operator >>(uint16 &w) {
		w = ntohs(read16());
		return *this;
	}
#ifdef _WIN32
	LargeInPacket &operator >>(DWORD &dw) {
		dw = ntohl(read32());
		return *this;
	}
#endif
	LargeInPacket &operator >>(uint32 &dw) {
		dw = ntohl(read32());
		return *this;
	}
	LargeInPacket &operator >>(uint64 &u64)
	{
		memcpy(&u64, rd_ptr(), sizeof(uint64));
		rd_ptr(sizeof(uint64));
		return *this;
	}
	LargeInPacket &operator >>(int64 &i64)
	{
		memcpy(&i64, rd_ptr(), sizeof(int64));
		rd_ptr(sizeof(int64));
		return *this;
	}
	LargeInPacket &operator >>(ICQ_STR &str);
	LargeInPacket &operator >>(string &str);
	virtual void ReadString(string& str);
	const char *readData(int &n);

	uint32 getSize()
	{
		return datalen;
	}
	
	
protected:
	int  datalen;
};


#endif
