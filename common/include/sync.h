/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by tiny                         *
 ***************************************************************************/

#ifndef _SYNC_H
#define _SYNC_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

class  Mutex {
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

private:

#ifdef _WIN32
	CRITICAL_SECTION cs;
#else
	pthread_mutex_t m;
#endif
};

class  MutexObject
{
public:
	MutexObject(Mutex *m) : mutex(m)
	{
		mutex->lock();
	}
	MutexObject(Mutex &m) : mutex(&m)
	{
		mutex->lock();
	}
	~MutexObject()
	{
		mutex->unlock();
	}
private:
	Mutex *mutex;
};

class  Semaphore {
public:
	Semaphore();
	~Semaphore();

	void down();
	void up();

private:

#ifdef _WIN32
	HANDLE sem;
#else
	sem_t sem;
#endif
};


#ifdef _WIN32	// Win32 implementation

inline Semaphore::Semaphore()
{
	sem = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
}

inline Semaphore::~Semaphore()
{
	if (sem)
		CloseHandle(sem);
}

inline void Semaphore::down()
{
	WaitForSingleObject(sem, INFINITE);
}

inline void Semaphore::up()
{
	ReleaseSemaphore(sem, 1, NULL);
}


inline Mutex::Mutex()
{
	InitializeCriticalSection(&cs);
}

inline Mutex::~Mutex()
{
	DeleteCriticalSection(&cs);
}

inline void Mutex::lock()
{
	EnterCriticalSection(&cs);
}

inline void Mutex::unlock()
{
	LeaveCriticalSection(&cs);
}

#else		// Linux implementation

inline Semaphore::Semaphore()
{
	sem_init(&sem, 0, 0);
}

inline Semaphore::~Semaphore()
{
	sem_destroy(&sem);
}

inline void Semaphore::down()
{
	sem_wait(&sem);
}

inline void Semaphore::up()
{
	sem_post(&sem);
}


inline Mutex::Mutex()
{
	pthread_mutex_init(&m, NULL);
}

inline Mutex::~Mutex()
{
	pthread_mutex_destroy(&m);
}

inline void Mutex::lock()
{
	pthread_mutex_lock(&m);
}

inline void Mutex::unlock()
{
	pthread_mutex_unlock(&m);
}

#endif		// _WIN32

#endif
