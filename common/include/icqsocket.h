#ifndef _ICQ_SOCKET_H_SFLKSJDFS
#define _ICQ_SOCKET_H_SFLKSJDFS

#include <string.h>
#include <stdio.h>

#ifdef _WIN32

#	ifndef __func__ 
#		define __func__ __FUNCDNAME__
#	endif 
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif

#	pragma comment(lib, "ws2_32")
#	include <winsock2.h>
#	include <WS2tcpip.h>
#	include <io.h>
#	include <errno.h>
#	include <MSWSock.h>

#	ifndef myclose
#		define myclose		closesocket
#	endif

#	if _MSC_VER >= 1600
#		define snprintf(dst, size, format, ...) _snprintf_s((dst), (size), (size), (format), ## __VA_ARGS__)
#	else
#		define snprintf _snprintf
#	endif

typedef int socklen_t;

#	define mysleep(x) Sleep(x)
#	define STR_CASE_CMP _stricmp

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#define mysleep(x) usleep(x*1000)

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif



#ifndef myclose
#define myclose close
#endif

#define STR_CASE_CMP strcasecmp
#endif



#define datarecv recv;
#define datasend send;


#include <string>
#include "icqtypes.h"
using namespace  std;


#define IPPORTKEY(ip, port) CoreSocket::IpPortKey((ip), (port))


class  CoreSocket
{
public:
	static bool SocketStartUp(void)
	{
#ifdef _WIN32
		static int wsaStartup = INVALID_SOCKET;
		WSADATA wsaData;
		WORD version = MAKEWORD(2, 2);
		if (wsaStartup != 0)
			wsaStartup = WSAStartup(version, &wsaData);
		
		return wsaStartup == 0;
#endif
		return true;
	}
	static string TransMacAddr(uint64 macAddr) 
	{
		char strMac[33] = {0};
		unsigned char *mac = (unsigned char *)&macAddr; 
		snprintf(strMac, 33, "%02X%02X%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], mac[6], mac[7]);
		return strMac;
	}
	static uint64 IpPortKey(uint32 ip, uint32 port)
	{
		uint64 ret = 0;
		ret = ((uint64)ip << 32);
		ret = (ret | port);
		return ret;
	}
	static uint64 StrMacToAddr(string macAddr) 
	{
		uint64 macValue = 0;

		if (macAddr.length() != 16)
			return 0;

		uint8 *p = (uint8 *)&macValue;

		for (uint8 i=0; i<8; i++)
		{
			const char buf[3] = {*(macAddr.c_str()+i*2), *(macAddr.c_str()+i*2+1), 0};

			int v = 0;
			sscanf(buf, "%x", &v);
			*(p+i) = uint8(v);
		}
		
		return macValue;;
	}

	static bool GetLocalIPPort(int sock, uint32 &ip, uint16 &port)
	{
		sockaddr_in addrMy = {0};
		int len = sizeof(addrMy);

		int ret = getsockname(sock, ( struct sockaddr *)&addrMy, (socklen_t *)&len);
		if (ret != 0)
		{
			return false;
		}

		ip = addrMy.sin_addr.s_addr;
		port = addrMy.sin_port;

		return true;
	}

	static void SocketCleanUp(void)
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}

	static int	evutil_make_socket_nonblocking(int fd)
	{
#ifdef WIN32
		{
			unsigned long nonblocking = 1;
			ioctlsocket(fd, FIONBIO, (unsigned long*) &nonblocking);
		}
#else
		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
			return -1;
#endif
		return 0;
	}
	
	static uint32 GetPassMinutesOfToday()
	{
#ifdef _WIN32
		SYSTEMTIME wtm;
		
		GetLocalTime(&wtm);

		return wtm.wHour * 60 + wtm.wMinute;
#else
		time_t t = time(NULL);
		struct tm *p = localtime(&t);

		return p->tm_hour * 60 + p->tm_min;
#endif
	}


	//************************************
	// Method:    TcpConnect
	// FullName:  CoreSocket::TcpConnect
	// Access:    public static 
	// Returns:   int 返回建立成功的连接，　错误返回INVALID_SOCKET
	// Qualifier:
	// Parameter: uint32 ip		网络字节序转换后的服务器地址
	// Parameter: uint16 port	网络字节序转换后的服务器端口
	//************************************
	static int TcpConnect(unsigned int ip, unsigned short port)
	{
		struct sockaddr_in server_addr = {0};
		server_addr.sin_family  = AF_INET;
		server_addr.sin_port = port;
		server_addr.sin_addr.s_addr = ip;

		int sock = INVALID_SOCKET;

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			return INVALID_SOCKET;
		}
		
		if (connect(sock, (sockaddr *)&server_addr, sizeof(sockaddr_in)) != 0)
		{
			myclose(sock);
			return INVALID_SOCKET;
		}

		return sock;
	}

	//************************************
	// Method:    UDPBind
	// FullName:  CoreSocket::UDPBind
	// Access:    public static 
	// Returns:   int
	// Qualifier:
	// Parameter: const char * address
	// Parameter: const unsigned short port　和地址一下，没有进行网络字节序转换
	//************************************
	static int UDPBind(const char *address, const unsigned short port)
	{
		return UDPBind(address ? inet_addr(address) : 0, htons(port));
	}

	//************************************
	// Method:    UDPBind
	// FullName:  CoreSocket::UDPBind
	// Access:    public static 
	// Returns:   int
	// Qualifier:
	// Parameter: const unsigned int ip 
	// Parameter: const unsigned short port 必须是网络字节序转换过后的
	//************************************
	static int UDPBind(const unsigned int ip, const unsigned short port)
	{
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0) {
			myclose(sock);
			return INVALID_SOCKET;
		}

		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = ip;
		addr.sin_port = port;
		if (::bind(sock, (sockaddr *) &addr, sizeof(addr)) < 0)
		{
			myclose(sock);
			return INVALID_SOCKET;
		}
		else
			return sock;
	}

	static int UdpConnect(const char *address, const unsigned short port)
	{
		return UdpConnect(inet_addr(address), htons(port));
	}

	static int UdpConnect(unsigned int ip, const unsigned short port)
	{
		int sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock == INVALID_SOCKET) 
		{
			return INVALID_SOCKET;
		}

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = port;
		addr.sin_addr.s_addr = ip;

		if (connect(sock, (sockaddr *)&addr, sizeof(addr)) != 0)
		{
			myclose(sock);
			return INVALID_SOCKET;
		}

#ifdef  _WIN32
		DWORD dwBytesReturned = 0;   
		BOOL  bNewBehavior = FALSE;   
		DWORD status = WSAIoctl(sock, SIO_UDP_CONNRESET, &bNewBehavior,   
			sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);   

		if(status != 0)
		{	
			myclose(sock);
			return 0;
		} 
#endif

		return sock;
	}

	static int UdpRecvFrom(const int sock, char *buf, int bufsize, int waittime, sockaddr_in &saddr)
	{
		fd_set readfds;
		int maxfd = sock + 1;
		struct  timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = waittime;
		socklen_t cbAddr = sizeof(saddr);


		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		int n = select(maxfd, &readfds, NULL, NULL, waittime==0 ? NULL : &timeout);

		if (n < 0)
		{
			return 0;
		}
		else if (n > 0)
		{
			int len = recvfrom(sock, buf, bufsize, 0, (sockaddr*)&saddr, &cbAddr);

			return len;
		}
		else
			return -1;

	}

	
};


#endif
