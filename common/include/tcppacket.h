/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by eph                         *
 ***************************************************************************/
//#pragma once

#ifndef _TCP_PACKET_H
#define _TCP_PACKET_H

#ifdef _ACE_SOCK
#include "ace/SOCK_Connector.h" 
#endif
#include "packet.h"
#ifndef _XCODE_
#   include "slab.h"
#endif
#include "icqsocket.h"


#define PACKET_CC		0xFEDC
#define TCP_CLI_HDR_LARGE_SIZE	22		//sizeof(TCP_CLI_HDR_LARGE)
#define TCP_CLI_HDR_SIZE		22		//sizeof(TCP_CLI_HDR)
#define TCP_LEN_WRITE_PLACE				(TCP_CLI_HDR_SIZE - 4)
#define TCP_LARGE_LEN_WRITE_PLACE		(TCP_CLI_HDR_LARGE_SIZE - 4)
#define TCP_MAX_PACKET_SIZE				81920			//单个包不应该大于80K,防止数据错乱引发系统崩溃
#define MAX_MSG_SIZE					4096

#pragma pack(1)

struct TCP_CLI_HDR {
	uint16 ver;
	uint32 id;
	uint32 uin;
	uint32 sid;
	uint16 cmd;
	uint16 seq;
	uint16 len;
	uint16 cc;		// check code
};

struct TCP_CLI_HDR_LARGE {
	uint16 ver;
	uint32 id;
	uint32 uin;
	uint32 sid;
	uint16 cmd;
	uint16 seq;
	uint16 len;
	uint16 cc;		// check code
};

typedef TCP_CLI_HDR TCP_SRV_HDR;

#pragma pack()

class  TcpLargeInPacket  : public LargeInPacket
{
public:
	TcpLargeInPacket(char*p, int len);
	TcpLargeInPacket();
	virtual ~TcpLargeInPacket();
	

#ifdef _ACE_SOCK
	int recv(ACE_SOCK_Stream& sock, const ACE_Time_Value *timeout = NULL)
	{
		int n = 0;
		reset();
		n = sock.recv_n(wr_ptr(), TCP_CLI_HDR_LARGE_SIZE, timeout);
		if(n < TCP_CLI_HDR_LARGE_SIZE)
			return -1;
		datalen = n; 
		wr_ptr(datalen);
		*this >> header.ver >> header.id;
		*this >> header.uin >> header.sid >> header.cmd;
		*this >> header.seq >> header.len >> header.cc;
		if(header.cc != PACKET_CC/*0*/ || header.len <  TCP_CLI_HDR_LARGE_SIZE)
			return -1;
		if(header.len == TCP_CLI_HDR_LARGE_SIZE)
		{
			return datalen;
		}
		if(header.len > Size - TCP_CLI_HDR_LARGE_SIZE)
		{
			relloc_ptr(header.len);
		}

		//多次读取
		int lastlen = header.len - TCP_CLI_HDR_LARGE_SIZE;
		int hasrecv = 0;
		int perlen;
		int perrecv;
		while(lastlen > 0) {
			perlen = lastlen > MAX_MSG_SIZE ? MAX_MSG_SIZE : lastlen;
			perrecv = sock.recv_n(wr_ptr() + hasrecv, perlen, timeout);
			if(perrecv <= 0) break;
			hasrecv += perrecv;
			lastlen -= perrecv;
		}
		if(lastlen > 0)
			return -1;
		else {
			datalen = header.len;
			wr_ptr(header.len - TCP_CLI_HDR_LARGE_SIZE);
			return datalen;
		}
	}

#endif
	int recv(int sock, int timeout = 0);
	void release();
	
public:
	TCP_CLI_HDR_LARGE header;

#ifndef _XCODE_
	DECLARE_SLAB(TcpLargeInPacket)
#endif
private:
	void OnRecv();
};

class  TcpLargeOutPacket  : public LargeOutPacket
{
public:
	TcpLargeOutPacket();
	virtual ~TcpLargeOutPacket();
	//void release();

	int attempts;
	time_t expire;
	uint16 seq;
	uint32 cmd;

	ListHead qItem;
	
	
	
#ifdef _ACE_SOCK
	int send(ACE_SOCK_Stream& sock, const ACE_Time_Value *timeout = NULL)
	{
		//write len before send
		writelen();

		//判断包的大小,如果过大，分包发送，否则一次性发送
		//加入打包发送支持
		int lastlen = length();						
		if(lastlen > TCP_MAX_PACKET_SIZE)
			return -1;
		int hassend = 0;
		int perlen;
		int persend;
		while(lastlen > 0) {
			perlen = lastlen > MAX_MSG_SIZE ? MAX_MSG_SIZE : lastlen;
			persend = sock.send_n(rd_ptr() + hassend, perlen, timeout);
			if(persend <= 0) break;
			hassend += persend;
			lastlen -= persend;
		}
		return hassend;

	}

#endif
	void CreateTcpOutPacketHead(uint16 ver, uint16 cmd, uint32 uin);
	void writelen();

#ifndef _XCODE_
	DECLARE_SLAB(TcpLargeOutPacket)
#endif
private:

};

#endif
