#ifndef COMMON_H
#define COMMON_H

#pragma once

#include <string>
#include <string.h>
#include "include/icqtypes.h"

std::string mac_to_string(unsigned long long * pMac,const char chKen=':');

//ip����ʽУ��
bool IsRightIpString(const char* pszIp);

//ip�ַ���ת����ip
inline uint32 IpString2IpValue(std::string strIp);

//ip�ַ���ת����ip
uint32 IpString2IpValue(const char *pszIp);

//����ipת�ַ���ip
std::string  IpValue2IpString(uint32 ipValue);


//����ipת�ַ���ip
void IpValue2IpString(uint32 ipValue,  char *pszIpAddressBuf,  int nBufLen);
void FromInt2String(std::string & strValue, const uint32 nValue);


long GetCurDateNumber();
std::string GetDateOfString(time_t t);
//��ȡ��ǰʱ���Ǳ���ĵڼ���
uint32 GetCurYearWeekNum(time_t timeNow,int64 dstTime=0);
bool CheckIsSameWeek(time_t curTime, int64 dstTime);
bool CheckIsSameYearWeek(time_t curTime, time_t dstTime,uint64 checkTime);



#define NIP2CHAREX(ip)	IpValue2IpString(htonl(ip)).c_str()
#endif


