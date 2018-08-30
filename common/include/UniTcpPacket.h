#pragma once
#include "tcppacket.h"
class  UniTcpOutPacket:public TcpLargeOutPacket
{
public:
	UniTcpOutPacket(bool bU=true);
	~UniTcpOutPacket(void);
	virtual void writeString(const char *str, int n);
private:
	bool m_bUtf;
public:
	bool IsUTF(){return m_bUtf;}
	void SeteUTF(bool butf){m_bUtf = butf;}
};


class  UniTcpInPacket:public TcpLargeInPacket
{
public:
	UniTcpInPacket(char* p, int len,bool bU=true);
	~UniTcpInPacket(void);
	virtual		void ReadString(string &str);
private:
	bool m_bUtf;
public:
	bool IsUTF(){return m_bUtf;}
	void SeteUTF(bool butf){m_bUtf = butf;}
};

