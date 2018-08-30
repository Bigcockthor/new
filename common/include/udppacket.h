/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by eph                         *
 ***************************************************************************/

#ifndef _UDP_PACKET_H
#define _UDP_PACKET_H

#include "packet.h"
#include "list.h"
#ifndef _XCODE_
#   include "slab.h"
#endif
#include <time.h>

// 点对点穿透服务
#define NAT_CALL           1
// 请求中转服务器地址
#define NAT_STAT           5

#define T_CALL		100			//call命令 id
#define T_ACCEPT	201			//accept命令 id
#define T_ACCEPTRET	202			//acceptret命令 id
#define T_CALLRET	203			//callret命令 id
#define T_REPLAY	210			//replay命令 id
#define T_END		211			//end结束

#pragma pack(1)

typedef struct
{
	short flag;							//报文类型
	uint8 cmd;
	uint8 id;
	unsigned int srcuid;				//src uin
	unsigned int dstuid;				//dst uin
	uint8 srcsession;
	uint8 dstsession;
	uint8 type;
	uint8 ext;
	uint32 srcPid;
}PACK_CMD;

struct UDP_CLI_HDR {
	uint16 ver;
	uint32 reserved;
	uint32 uin;
	uint32 sid;
	uint16 cmd;
	uint16 seq;
	uint16 cc;		// check code
};

struct UDP_SRV_HDR {
	uint16 ver;
	uint32 reserved;
	uint32 uin;
	uint32 sid;
	uint16 cmd;
	uint16 seq;
	uint16 ackseq;
};

#pragma pack()



class  UdpOutPacket : public OutPacket {
public:
	UdpOutPacket(void *s = NULL);

	ListHead sendItem;
	ListHead globalSendItem;

	int attempts;
	uint32 expire;
	uint16 seq;
	uint16 cmd;
	uint32 destsid;
	void *session;

	void encrypt(const char *subkey);

#ifndef _AFXDLL
#   ifndef _XCODE_
	DECLARE_SLAB(UdpOutPacket)
#   endif
#endif
	
};

class  UdpInPacket : public InPacket {
public:
	UdpInPacket(bool generalPacket = true);
	UdpInPacket(UdpInPacket& p);
	ListHead waitItem;

	bool decrypt(char *subkey);
	virtual int udprecv(int sock);
	UDP_CLI_HDR header;

	virtual void setdata(const char *buf, const uint16 buflen);

	virtual void SetDatalen(int len);

#ifndef _AFXDLL
#   ifndef _XCODE_
	DECLARE_SLAB(UdpInPacket)
#   endif
#endif

	void *session;												//临时的session等
	uint32 proxyIP;												//代理服务器ＩＰ
	uint16 proxyPort;											//代理服务器端口
	uint8 channel;												//通道ＩＤ
	bool general;												//普通报文（相对代理报文）
protected:
	void OnRecv(int n);
};

class  UdpNatPacket : public InPacket {
public:
	UdpNatPacket();
	virtual int udprecv(int sock);

	virtual void setdata(const char *buf, const uint16 buflen);
	uint32 proxyIP;												//代理服务器ＩＰ
	uint16 proxyPort;											//代理服务器端口

	bool ipcmd;
	PACK_CMD* ipcmdbuf;
};

#endif
