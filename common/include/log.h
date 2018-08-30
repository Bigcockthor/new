/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by eph                         *
 ***************************************************************************/
#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <string>
using namespace std;
#define LOG(level)	if (level <= Log::logLevel) Log::print
#define LOG2(level)	if (level <= Log::logLevel) Log::print2

#ifdef _DEBUG
#define DLOG(level) if (level <= Log::logLevel) Log::print
#define DLOG2(level) if (level <= Log::logLevel) Log::print2
#else
#define DLOG(level) ;//
#endif



class  Log {
public:
	enum
	{
		LOG_LEVEL_ERROR = 1,			
		LOG_LEVEL_WARNING,
		LOG_LEVEL_NOTIFY,
		LOG_LEVEL_PRINT,
	};
	static void open(const char *file, int level, bool printfInconsole = false);
	static void open(const char *file,  char* type,char* ver,int level, bool printfInconsole = false);//适用于日志采集的规范
	static void ChangeLevel(int level);
	static void closeLog();
	static void print(const char *fmt, ...);
	static void print2(const char *fmt, ...);//日志采集的规范的打印
	static int logLevel;
	static bool logPrintfInconsole;

private:
	static FILE *logFile;
	static string m_type;
	static string  m_ver;
};

#endif
