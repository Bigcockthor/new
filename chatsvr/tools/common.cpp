#include "common.h"
#include "include/icqsocket.h"
#include "time.h"

#define MAX_IPVALUE	0xFFFFFFFF
#define DATE_MASK	100

std::string mac_to_string(unsigned long long * pMac,const char chKen)
{
	//char szFormat[] = "%02X:%02X:%02X:%02X:%02X:%02X";
	//int nLen = strlen(szFormat);
	//if (chKen != ':')
	//{
	//	for (int i = 2;i < nLen;i += 3)
	//	{
	//		szFormat[i] = chKen;
	//	}
	//}

	char szMac[16] = {0};
	sprintf(szMac,"%llu", *pMac);
	std::string strRet(szMac);
	return strRet;
}

//判断给定IP字符串是否是合法的ip地址  
bool IsRightIpString(const char* pszIp)  
{  
	if (!pszIp) 
	{  
		return false;  
	}  

	int nLen = strlen(pszIp);  
	if (nLen < 7) 
	{  

		// 至少包含7个字符"0.0.0.0"  
		return false;  
	}  

	for (int i = 0; i < nLen; ++i) 
	{  
		if (!isdigit(pszIp[i]) && pszIp[i] != '.') 
		{  
			return false;  
		}  

		if (pszIp[i] == '.') 
		{  
			if (0 == i) 
			{  
				if (!isdigit(pszIp[i + 1])) 
				{  
					return false;  
				}  
			} else if (nLen - 1 == i) {  
				if (!isdigit(pszIp[i - 1])) 
				{  
					return false;  
				}  
			} else {  
				if (!isdigit(pszIp[i - 1]) || !isdigit(pszIp[i + 1])) 
				{  
					return false;  
				}  
			}  
		}  
	}  
	return true;  
}  

uint32 IpString2IpValue(std::string strIp)
{
	return IpString2IpValue(strIp.c_str());
}

uint32 IpString2IpValue(const char *pszIp)  
{  
	if (!IsRightIpString(pszIp)) 
	{  
		return 0;  
	}  

	int nNum = 0;           // 每个段数值  
	const char *pBeg = pszIp;  
	const char *pPos = NULL;  
	uint32 ulIp = 0; // 整个IP数值  

	pPos = strchr(pszIp, '.');  
	while (pPos != NULL) 
	{  
		nNum = atoi(pBeg);  
		if(nNum > 255)
		{
			return 0;
		}
		ulIp += nNum;  
		ulIp *= 0x100;  
		pBeg = pPos + 1;  
		pPos = strchr(pBeg, '.');  
	}  

	nNum = atoi(pBeg);  
	ulIp += nNum;  
	return ulIp;  
} 

std::string  IpValue2IpString(uint32 ipValue)
{
	char buf[32] = {0};
	IpValue2IpString(ipValue, buf, sizeof(buf));
	return std::string(buf);
}

void IpValue2IpString(uint32 ipValue,   char *pszIpAddressBuf,  int nBufLen)  
{  
	if (!pszIpAddressBuf) 
	{  
		return;  
	}
	
	if(nBufLen < 7)
	{
		return;
	}

	if(ipValue > MAX_IPVALUE)
	{
		return;
	}
	char buf[32]={0};
	snprintf(buf, sizeof(buf), "%u.%u.%u.%u", (ipValue & 0xFF000000) >> 24,  
		(ipValue & 0x00FF0000) >> 16, (ipValue & 0x0000FF00) >> 8,ipValue & 0x000000FF);  
	int nNewLen = strlen(buf);
	if(nNewLen >= nBufLen)//缓冲区不够大
	{
		return;
	}
	memcpy(pszIpAddressBuf, buf, nNewLen);
	pszIpAddressBuf[nNewLen] = 0;  
}
void FromInt2String(string & strValue, const uint32 nValue)
{
	char buf[64];
	snprintf(buf, sizeof(buf)-1, "%u", nValue);
	strValue = buf;
}

long GetCurDateNumber()
{
	char tmp[64] = {0}; 
	time_t t = time(NULL);
	strftime( tmp, sizeof(tmp), "%Y%m%d",localtime(&t)); 

	return atol(tmp);
}

std::string GetDateOfString(time_t t)
{
	char tmp[64] = {0}; 
	strftime( tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&t)); 
	return std::string(tmp);
}
uint32 GetCurYearWeekNum(time_t timeNow,int64 dstTime)
{
	uint32 weekNum = 0;
	time_t newTime = timeNow+dstTime;
	char week[32]; 
	strftime( week, sizeof(week), "%W",localtime(&newTime));
	weekNum = (uint32)atoi(week);

	char yearNum[32];
	strftime( yearNum, sizeof(yearNum), "%Y",localtime(&newTime));
	weekNum += (uint32)atoi(yearNum)*100;
	return weekNum;
}

bool CheckIsSameWeek(time_t curTime, int64 dstTime)
{
	uint32 yearWeekNum = GetCurYearWeekNum(curTime,0);
	uint32 realYearWeekNum = GetCurYearWeekNum(curTime,dstTime);
	if (yearWeekNum != realYearWeekNum)
		return false;
	return true;
}

bool CheckIsSameYearWeek(time_t curTime, time_t dstTime,uint64 checkTime)
{
	uint32 yearWeekNum = GetCurYearWeekNum(curTime,checkTime);
	uint32 realYearWeekNum = GetCurYearWeekNum(dstTime,checkTime);
	if (yearWeekNum != realYearWeekNum)
		return false;
	return true;
}





