/***************************************************************************
 *                                                                         *
 *   copyright            : (C) 2002 by tiny                         *
 ***************************************************************************/

#ifndef _SLAB_H
#define _SLAB_H
#include "list.h"
#include <stdio.h>

#include "sync.h"


struct SLAB;

struct OBJ {
	OBJ *next;
	SLAB *slab;
};

struct SLAB {
	ListHead item;
	int inuse;
	OBJ *free;
};

class  Cache {
public:
	Cache(int size, int n);
	~Cache();

	void *allocObj();
	void freeObj(void *p);

	static int reclaimAll();

private:
	SLAB *newSlab();


	Mutex mutex;

	int reclaim();

	Cache *nextCache;
	ListHead slabList;
	ListHead *firstNotFull;

	int objSize;
	int numObjs;
	int slabSize;

	static Cache *cacheList;
};


#define DECLARE_SLAB(type)		\
private:	\
	static Cache type##_cache;	\
public:	\
	void *operator new(size_t) {	\
		return type##_cache.allocObj();	\
	}	\
	void operator delete(void *p) {	\
		type##_cache.freeObj(p);	\
	}

#define IMPLEMENT_SLAB(type, num)	\
	Cache type::type##_cache(sizeof(type), num);


#endif
