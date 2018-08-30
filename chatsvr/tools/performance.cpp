#include "performance.h"
#include "include/icqsocket.h"
#include "common.h"

#define LOGVER		"version:1.0.0.1"
#ifdef WIN32

int gettimeofday(struct timeval *tp, void *tzp)
{
	
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year     = wtm.wYear - 1900;
	tm.tm_mon     = wtm.wMonth - 1;
	tm.tm_mday     = wtm.wDay;
	tm.tm_hour     = wtm.wHour;
	tm.tm_min     = wtm.wMinute;
	tm.tm_sec     = wtm.wSecond;
	tm. tm_isdst    = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

CTLPerformance::CTLPerformance():
m_started(false),
	m_timeout_sec(3600)
{
	m_nState = 1;
}

CTLPerformance::~CTLPerformance()
{
	flush();
	Stop();
}


int CTLPerformance::Init(const string& path_, const string& serverName, uint32 servid, int intervalSec, uint8 nState)
{
	if (true == m_started) return -1;

	m_timeout_sec = intervalSec;
	m_servid = servid;
	
	char buf[64]={0};
	sprintf(buf, "%s%u", path_.c_str(), servid);
	m_path = buf;
	m_nState = nState;
	m_logserverName = serverName;
	CoreThread::CreateNewThread(this, NULL);
	return 0;
}



void CTLPerformance::addData(const string& mod_, long us_, uint32 cmd_)
{
	m_listData.push_back(new CTLAutoAddPerfData(this, mod_, us_, cmd_));
}


void CTLPerformance::UpdateState(uint8 nState, int intervalSec)
{
	m_nState = nState;
	m_timeout_sec = intervalSec;
}

void CTLPerformance::flush()
{
	if(!m_nState)
	{
		m_perf_info.clear();
		return;
	}
	std::string strFileName = "./logs/" + m_path;
	strFileName += "_";
	char tmpbuf[64] = {0}; 
	time_t timep   = time(NULL);
	struct tm *tmp = localtime(&timep);
	strftime( tmpbuf, sizeof(tmpbuf), "%m%d",tmp);
	strFileName += tmpbuf;
	strFileName += ".txt";
		 
	m_fstream.open(strFileName.c_str(), ios::app);
	map<string, CTLPerfInfo>::iterator it = m_perf_info.begin();

	

	char tmp_buff[256];
	sprintf(tmp_buff, "%04d/%02d/%02d %02d:%02d:%02d type:%s %s",
		tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
		m_logserverName.c_str(), LOGVER);
	


	
	for (; it != m_perf_info.end(); ++it)
	{
		CTLPerfInfo& pinfo = it->second;
		if(pinfo.m_min == 2147483647)
		{
			continue;
		}
		long per = pinfo.m_total / pinfo.m_times;
		long rps = pinfo.m_total / m_timeout_sec;

		char buff[1024] = {0};

		sprintf(buff, "%s module:%s eventid:%d servid:%u max_cost[us]:%ld min_cost[us]:%ld per_cost[us]:%ld request_per_second:%ld exe_times:%ld\n",
						tmp_buff, it->first.c_str(), pinfo.m_cmd, m_servid, pinfo.m_max, pinfo.m_min, per, rps, pinfo.m_times);
		m_fstream << buff;
		
	}
	m_fstream.flush();
	m_fstream.close();
	m_perf_info.clear();
}

void CTLPerformance::ProcessData()
{
	while(m_listData.size())
	{
		CTLAutoAddPerfData* pData = m_listData.pop_front();

		if(!pData)
		{
			continue;
		}
		CTLAutoAddPerfData::add_perf_data(pData);
	}
}

void CTLPerformance::run(void *mParameter)
{
	uint64 nCount = 0;
	while(!GetWillStop())
	{
		nCount++;
		ProcessData();


		if(nCount%m_timeout_sec==0)
		{
			flush();
		}
		mysleep(1000);					

	}

}



void CTLPerformance::add_perf_data(const string& mod_, long us_, uint32 cmd)
{
	CTLPerfInfo& pinfo = m_perf_info[mod_];
	pinfo.m_cmd = cmd;

	pinfo.m_total += us_;
	pinfo.m_times += 1;

	if (us_ > pinfo.m_max)
	{
		pinfo.m_max = us_;
	}
	else if (us_ < pinfo.m_min)
	{
		pinfo.m_min = us_;
	}
}



