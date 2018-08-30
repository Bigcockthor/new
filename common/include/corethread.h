// ***************************************************************
//  CoreThread   version:  1.0   ·  date: 09/16/2007
//  -------------------------------------------------------------
//  Author: Seoul.Tsai
//  Email: Seoul.Tsai@gmail.com
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
//
/*
sample:

class TestServer : public CoreThreadHandle
{
public:
	void run(void *mParameter)
{
	printf("Thread test\n");
}
};

void testProc1(void)
{
	printf ("test 1\n");
}

void testProc2(void *pm)
{
	if (pm)
		printf("test 2 ....\n");
	else
		printf("test 2\n");
}



int main(int argc, char* argv[])
{

	CoreThread::CreateNewThread(new TestServer, NULL);

	int a;
	CoreThread::CreateNewThread(testProc1);
	CoreThread::CreateNewThread(testProc2,&a);
	CoreThread::CreateNewThread(testProc2,NULL);

	return 0;
}
 ***************************************************************/

#ifndef  THREAD_CROSS_PLATFORM_DEFINEKJDK
#define THREAD_CROSS_PLATFORM_DEFINEKJDK

#define CORE_DEFAULT_STACK_SIZE 512

#include "queue.h"
#include "include/log.h"
#include <vector>

#ifdef _WIN32
#include <WinSock2.h>



typedef HANDLE ThreadHandle;

#else

#include <pthread.h>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (~0)
#endif


typedef pthread_t ThreadHandle;

#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((ThreadHandle)(~0))
#endif

class CoreThread;

class CoreThreadHandle
{
public:
	CoreThreadHandle() : willStop(false) {}
	virtual ~CoreThreadHandle(){}
	virtual void run(void *mParameter) = 0;


	bool GetWillStop(void) const {return willStop;}
	virtual void Stop(bool bWait = true) 
	{
		willStop = true;

		if (bWait)
		{
#ifdef _WIN32
#ifndef THREAD_NOTINFINITE_STOP
			WaitForSingleObject(handle, 1000);
#endif
#else
			void *temp = NULL;
			pthread_join(handle, &temp);
#endif
		}

	}
	void SetThreadHandle(ThreadHandle hdl)
	{
		handle = hdl;
	}
	ThreadHandle GetThreadHandle(void) const { return handle; }
private:
	bool willStop;

	ThreadHandle handle;

	//friend CoreThread;
};


typedef void (*ThreadSimpleProc)(void);
typedef void (*ThreadProc)(void *Parameter);

class ParameterStruct
{
public:
	ParameterStruct(CoreThreadHandle *mCth = NULL, ThreadSimpleProc mSimpleProc = NULL, 
		ThreadProc mProc = NULL, void *mParameter = NULL) : cth(mCth), SimpleProc(mSimpleProc),
		Proc(mProc), parameter(mParameter)
	{
	}
	ParameterStruct(ParameterStruct &PS)
	{
		cth = PS.cth;
		SimpleProc = PS.SimpleProc;
		Proc = PS.Proc;
		parameter = PS.parameter;
	}
	CoreThreadHandle *cth;
	ThreadSimpleProc SimpleProc;
	ThreadProc Proc;
	void *parameter;
};

class CoreThread
{
public:
	static ThreadHandle CreateNewThread(ThreadSimpleProc mProc, int stackSize = CORE_DEFAULT_STACK_SIZE)
	{
		ParameterStruct *pm = new ParameterStruct;
		if (pm)
		{
			pm->SimpleProc = mProc;

			return CreateNewThread(pm, stackSize);
		}
		else
			return 0;
	}

	static ThreadHandle CreateNewThread(ThreadProc mProc, void *mParameter, int stackSize = CORE_DEFAULT_STACK_SIZE)
	{
		ParameterStruct *pm = new ParameterStruct;
		if (pm)
		{
			pm->Proc = mProc;
			pm->parameter = mParameter;

			return CreateNewThread(pm, stackSize);
		}
		else 
			return 0;
	}

	static ThreadHandle CreateNewThread(CoreThreadHandle *mCoreThreadHandle, void *lpParameter = NULL, int stackSize = CORE_DEFAULT_STACK_SIZE)
	{
		ParameterStruct *pm = new ParameterStruct;
		pm->cth = mCoreThreadHandle;
		pm->parameter = lpParameter;

		mCoreThreadHandle->SetThreadHandle(CreateNewThread(pm, stackSize));
		return mCoreThreadHandle->GetThreadHandle();
	}



#ifdef _WIN32
	static DWORD WINAPI ThreadFunction(LPVOID lpParameter)

#else
	static void *ThreadFunction(void *lpParameter) 
#endif
	{
		if (!lpParameter) return 0;

		ParameterStruct *pm = (ParameterStruct *)lpParameter;
		ParameterStruct newpm(*pm);
		delete pm;

		if (newpm.cth)
			((CoreThreadHandle *)newpm.cth)->run(newpm.parameter);
		else if (newpm.SimpleProc)
			newpm.SimpleProc();
		else
			newpm.Proc(newpm.parameter);

		return 0;
	}

private:
	static ThreadHandle CreateNewThread(ParameterStruct *pm, int stackSize)
	{
#ifdef _WIN32

		DWORD dwThreadId;

		//return   CreateThread(NULL, 0, CoreThread::ThreadFunction, (LPVOID)pm, 0, &dwThreadId);
        ThreadHandle hThread = CreateThread(NULL, 0, CoreThread::ThreadFunction, (LPVOID)pm, 0, &dwThreadId);
        if (NULL == hThread)
            return INVALID_HANDLE_VALUE;
        return hThread;
#else
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_attr_setstacksize(&attr, stackSize * 1024);
		//pthread_create(&thread,  &attr, CoreThread::ThreadFunction, pm);
		//return thread;
        if (0 != pthread_create(&thread,  &attr, CoreThread::ThreadFunction, pm))
            return INVALID_HANDLE_VALUE;
        return thread;
#endif
	}


};

typedef void (*CoreThreadPool_fn)(void *);

class CoreThreadPool;

class CoreThreadTask //: public ListHead
{
public:
	CoreThreadTask(CoreThreadPool_fn dispatchFunc, void *mArgv,
		bool quitTask = false) : quit(quitTask), fn(dispatchFunc), 
		argv(mArgv)
	{

	}

	inline void process(void)
	{
		if (fn)
			fn(argv);
	}

	const bool quit;
private:
	CoreThreadPool_fn fn;
	void *argv;
};

typedef std::vector<CoreThreadTask *> TaskList;

class CoreThreadPool : public CoreThreadHandle
{
public:
	enum
	{
		MESSAGE_QUIT = 1,		//线程退出命令
	};
	CoreThreadPool(int minT, int maxT) : minThread(minT), maxThread(maxT),
		current(0)
	{
		if (minThread < 1)
			minThread = 1;

		if (maxThread < minThread)
			maxThread = minThread * 2;

		for (int i=0; i<minThread; i++)
		{
			CreateNewThread();
		}
	}

	void ChangeNum(int minT, int maxT)
	{

		if (minT)
			minThread = minT;

		maxThread = maxT;
	}

	//暂时不作退出处理
	//~CoreThreadPool()
	//{
	//	Stop();

	//	for (int i = 0; i<current * 2; i++)
	//	{
	//		CoreThreadTask *task = new CoreThreadTask(NULL, NULL, true);
	//		if (task)
	//			taskQueue.put(task);
	//	}

	//	while(current > 0)
	//	{
	//		
	//		mysleep(10);
	//	}


	//}

	void PushTask(CoreThreadPool_fn fn, void *argv)
	{
		if (!fn) return;

		CoreThreadTask *task = new CoreThreadTask(fn, argv);
		if (task)
		{
			int len = 0;
			qLock.lock();
			q.push_back(task);
			len = q.size();
			qLock.unlock();
			sem.up();
//			int len = taskQueue.put(task);	
			if (len >= current && current < maxThread)
			{
				LOG(4)("task queue = %d, current = %d\n", len, current);
				CreateNewThread();
			}
		}
	}
protected:
	virtual void run(void *mParameter)
	{
		numLock.lock();
		current++;
		numLock.unlock();

		while(!GetWillStop())
		{
			CoreThreadTask *task = NULL;
			sem.down();
			qLock.lock();
			if (q.size())
			{
				task = q[0];
				q.erase(q.begin());
			}
			qLock.unlock();
			
//			(CoreThreadTask *)taskQueue.get();
			if (task)
			{
				if (task->quit)
				{	
					delete task;
					break;
				}

				task->process();

				delete task;
			}
		}

		numLock.lock();
		current--;
		numLock.unlock();
	}
private:
	int minThread;
	int maxThread;
	int current;
	Mutex numLock;


	Mutex qLock;
	Semaphore sem;
	TaskList q;

	Queue taskQueue;

	void CreateNewThread(void)
	{
		CoreThread::CreateNewThread(this, NULL);
	}
};




#endif
