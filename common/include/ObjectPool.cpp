// ObjectPool.cpp: implementation of the ObjectPool class.
//
//////////////////////////////////////////////////////////////////////
#if !defined UTILITY_POOL_OBJECTPOOL_CPP
#define UTILITY_POOL_OBJECTPOOL_CPP

#include "include/ObjectPool.h"

namespace utility
{
namespace pool
{
		
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
template <class T,class FACTORY>
ObjectPool<T,FACTORY>::ObjectPool()
{
	closed = true;
}

template <class T,class FACTORY>
ObjectPool<T,FACTORY>::~ObjectPool()
{

}

}
}

#endif // !defined(UTILITY_POOL_OBJECTPOOL_CPP)
