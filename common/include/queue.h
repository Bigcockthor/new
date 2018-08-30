/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by tiny                         *
 ***************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

#include <vector>
#include "list.h"
#include "sync.h"


class  Queue {
public:
	Queue(bool mSem = true) : bSem(mSem) { len=0;};
	bool isEmpty();
	ListHead *get();
    int put(ListHead *item);
	int  length();
private:
	int len;
	ListHead list;
	Mutex mutex;
	Semaphore sem;
	const bool bSem;
};


template <typename T>
class SyncList
{
public:
	SyncList(bool mWithSem = false) : withSem(mWithSem)
	{
	}
	~SyncList()
	{
		ClearSTLArray(taskL);
	}

	int push_back(T t)
	{
		MutexObject lock(&taskLock);

		if (t)
			taskL.push_back(t);

		if (withSem) sem.up();

		return taskL.size();
	}
	T pop_front()
	{
		if (withSem) sem.down();

		MutexObject lock(&taskLock);

		T t = NULL;
		if (taskL.begin() != taskL.end())
		{
			t = *taskL.begin();
			taskL.erase(taskL.begin());
		}

		return t;
	}

	int size()
	{
		MutexObject lock(&taskLock);

		return taskL.size();
	}

private:
	typedef std::vector<T> TaskList;

	TaskList taskL;
	Mutex taskLock;
	bool withSem;
	Semaphore sem;
};


#endif
