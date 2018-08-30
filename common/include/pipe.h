
#ifndef INC_PIPE_H
#define INC_PIPE_H

enum
{
	PIPE_TCP,
	PIPE_UDP
};
class CTLPipe
{
public:
	CTLPipe(int nType = PIPE_UDP);
	~CTLPipe();
	int WriteData(const char* pData, int nDataLen);
	int ReadData(char* buf, int nBuferLen);
	int ReadFd(){return m_sock[0];}
	void ResetReadFd();
	int WriteFd(){return m_sock[1];}
    bool CheckValid() const {return m_bValid;}

    void Reset();
private:
#ifdef WIN32
	int __stream_socketpair(struct addrinfo* ai,int sock[2]);
	int __dgram_socketpair(struct addrinfo* ai,int sock[2]);
	int win32_socketpair(int family,int type,int protocol,int sock[2]);
#endif

	int socket_pair(int family,int type,int protocol,int sock[2]);
    void Close();
private:
	int m_sock[2];
	int m_nType;
    bool m_bValid;
};
#endif

