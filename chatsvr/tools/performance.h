#ifndef INC_PERFORMANCE_H
#define INC_PERFORMANCE_H

#include "include/corethread.h"
#include "Singleton.h"
#include "include/sync.h"
#include "include/coretime.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#include <time.h>
int gettimeofday(struct timeval *tp, void *tzp);
#else
#   include <sys/time.h>

#endif



#define AUTO_PERF() CTLPerformance::CTLPerftool __tmp__(__FUNCTION__)
#define AUTO_PERF_NAME(x, y) CTLPerformance::CTLPerftool(x, y)
#define PERF(m)     CTLPerformance::CTLPerftool __tmp__(m)

//! 性能监控
class CTLPerformance:public CoreThreadHandle
{
public:
	struct CTLPerftool
	{
		CTLPerftool(const char* mod_, uint32 id_):
	mod(mod_),cmd(id_)
	{
		gettimeofday(&tm, NULL);
	}
	~CTLPerftool()
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		long cost = (now.tv_sec - tm.tv_sec)*1000000 + (now.tv_usec - tm.tv_usec);
		CTLSingleton<CTLPerformance>::GetInstance()->addData(mod, cost, cmd);
	}
	const char*    mod;
	uint32		   cmd;
	struct timeval tm;
	};


	struct CTLPerfInfo
	{
		CTLPerfInfo():
		m_max(0),
		m_min(2147483647),
		m_total(0),
		m_times(0),
		m_cmd(0)
	{}
	volatile long m_max;
	volatile long m_min;
	volatile long m_total;
	volatile long m_times;
	volatile uint32 m_cmd;
	};

	struct CTLAutoAddPerfData
	{
		static void add_perf_data(void* p_)
		{
			CTLAutoAddPerfData* pd_ptr = (CTLAutoAddPerfData*)p_;
			pd_ptr->pd->add_perf_data(pd_ptr->mod, pd_ptr->cost, pd_ptr->cmd);

			delete pd_ptr;
		}
		CTLAutoAddPerfData(CTLPerformance* p_, const string& mod_, long cost_, uint32 cmd_):
		pd(p_),
			mod(mod_),
			cost(cost_),
			cmd(cmd_)
		{
		}
		CTLPerformance* pd;
		string                mod;
		long                  cost;
		uint32				  cmd;
	};
	typedef SyncList<CTLAutoAddPerfData *> autoData;
	
public:
	CTLPerformance();
	~CTLPerformance();

	//! 启动线程，创建文件
	int Init(const string& path_, const string& serverName, uint32 servid, int intervalSec, uint8 nState);


	void addData(const string& mod_, long us_, uint32 cmd);

	
	void UpdateState(uint8 nState, int intervalSec);


public:
	void add_perf_data(const string& mod_, long us, uint32 cmd);

	void ProcessData();

	//! 更新性能日志
	void flush();

protected:
	virtual void run(void *mParameter);

private:
	volatile bool               m_started;
	int                         m_timeout_sec;
	map<string, CTLPerfInfo>    m_perf_info;
	autoData					m_listData;
	ofstream                    m_fstream;
	string						m_path;
	string						m_logserverName;
	uint32						m_servid;
	uint8						m_nState;
};



#endif

