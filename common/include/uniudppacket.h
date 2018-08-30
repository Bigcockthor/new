#pragma once
#include "udppacket.h"

#define MAX_TIME_ARRAY_SIZE     5  //packet时间统计数组大小

class TimeArrayIndex
{
public:
	enum
	{
		PACKET_CREATTIME = 0,
		PACKET_ONACK_TIME,
		PACKET_PROCCESS_TIME,
	};
};

class  UniUdpInPacket :	public UdpInPacket
{
public:
	UniUdpInPacket(void);
	~UniUdpInPacket(void);

	virtual void ReadString(string &str);
};

class  UniUdpOutPacket : public UdpOutPacket
{
public:
	UniUdpOutPacket(void);
	~UniUdpOutPacket(void);

	virtual void writeString(const char *str, int n);
};



class NewUniUdpOutPacket : public UniUdpOutPacket
{
public:
	virtual ~NewUniUdpOutPacket(){}
	NewUniUdpOutPacket()
	{
		memset(m_timeArray, 0, sizeof(m_timeArray));
	}
public:
	uint32 m_timeArray[MAX_TIME_ARRAY_SIZE];
};

class NewUniUdpInPacket : public UniUdpInPacket
{
public:
	NewUniUdpInPacket()
	{
		memset(m_timeArray, 0, sizeof(m_timeArray));
		m_reqAttempts = 0;
		m_reqCmd = 0;
	}
	virtual ~NewUniUdpInPacket(){}
	uint32 m_timeArray[MAX_TIME_ARRAY_SIZE];
	uint32 m_reqAttempts;
	uint16 m_reqCmd;
};

