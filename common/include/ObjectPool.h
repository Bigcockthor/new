		// ObjectPool.h: interface for the ObjectPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined UTILITY_POOL_OBJECTPOOL_H
#define UTILITY_POOL_OBJECTPOOL_H

#include "ace/pre.h"
#include "ace/OS.h"
#include "PoolableObjectFactory.h"

namespace utility
{
namespace pool
{

/**
 *  @class classname
 *
 *  2003-11-13 9:00:08
 *
 *  @brief A pooling interface.
 *
 *  ObjectPool defines a trivially simple pooling interface. The only 
 *  required methods are borrowObject and returnObject. 
 *	
 *
 *  @author 肖猛 <xiaomeng@et66.com>
 */
template <class T,class FACTORY>
class ObjectPool  
{
public:
	ObjectPool();
	virtual ~ObjectPool();
    /**
	* Obtain an instance from my pool.
	* By contract, clients MUST return
	* the borrowed instance using
	* {@link #returnObject(java.lang.Object) returnObject}
	* or a related method as defined in an implementation
	* or sub-interface.
	* <p>
	* The behaviour of this method when the pool has been exhausted
	* is not specified (although it may be specified by implementations).
	*
	* @return an instance from my pool.
	*/
    virtual T* borrowObject() = 0;
	
    /**
	* Return an instance to my pool.
	* By contract, <i>obj</i> MUST have been obtained
	* using {@link #borrowObject() borrowObject}
	* or a related method as defined in an implementation
	* or sub-interface.
	*
	* @param obj a {@link #borrowObject borrowed} instance to be returned.
	*/
    virtual int returnObject(T* obj) = 0;
	
    /**
	* Invalidates an object from the pool
	* By contract, <i>obj</i> MUST have been obtained
	* using {@link #borrowObject() borrowObject}
	* or a related method as defined in an implementation
	* or sub-interface.
	* <p>
	* This method should be used when an object that has been borrowed
	* is determined (due to an exception or other problem) to be invalid.
	* If the connection should be validated before or after borrowing,
	* then the {@link PoolableObjectFactory#validateObject} method should be
	* used instead.
	*
	* @param obj a {@link #borrowObject borrowed} instance to be returned.
	*/
    virtual int invalidateObject(T* obj)=0;
	
    /**
	* Create an object using my {@link #setFactory factory} or other
	* implementation dependent mechanism, and place it into the pool.
	* addObject() is useful for "pre-loading" a pool with idle objects.
	* (Optional operation).
	*/
    virtual void addObject() = 0;
	
    /**
	* Return the number of instances
	* currently idle in my pool (optional operation).  
	* This may be considered an approximation of the number
	* of objects that can be {@link #borrowObject borrowed}
	* without creating any new instances.
	*
	* @return the number of instances currently idle in my pool
	* @throws UnsupportedOperationException if this implementation does not support the operation
	*/
    virtual int getNumIdle() = 0;
	
    /**
	* Return the number of instances
	* currently borrowed from my pool 
	* (optional operation).
	*
	* @return the number of instances currently borrowed in my pool
	* @throws UnsupportedOperationException if this implementation does not support the operation
	*/
    virtual int getNumActive() =0;
	
    /**
	* Clears any objects sitting idle in the pool, releasing any
	* associated resources (optional operation).
	*
	* @throws UnsupportedOperationException if this implementation does not support the operation
	*/
    virtual int clear() = 0;
	
    /**
	* Close this pool, and free any resources associated with it.
	*/
    virtual int closePool()
	{
		closed = true;
		return 0;
	};
	
    /**
	* Sets the {@link PoolableObjectFactory factory} I use
	* to create new instances (optional operation).
	* @param factory the {@link PoolableObjectFactory} I use to create new instances.
	*
	* @throws IllegalStateException when the factory cannot be set at this time
	* @throws UnsupportedOperationException if this implementation does not support the operation
	*/
    virtual void setFactory(FACTORY* factory) =0;

	/*
	 *	Jakarta 原来没有这个方法，它的设计中对象池一创建就是open的。
	 *  在C++版本中我添加了这个方法，对象池创建后调用这个方法，在这里
	 *  完成相关线程的创建。并保证方法返回时池中已经有了最小数量的对象
	 *  以备使用。 [11/19/2003 12:24 肖猛]
	 * @return 池中已有的对象个数
	 */
	virtual int openPool()
	{
		closed = false;
		return 0;
	}
	
protected:
	bool isClosed() 
	{
        return closed;
    }
	
protected:
	bool closed;

};

}
}

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#if !defined (ACE_HAS_BROKEN_HPUX_TEMPLATES)
#include "ObjectPool.cpp"
#endif /* !ACE_HAS_BROKEN_HPUX_TEMPLATES */
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("ObjectPool.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include "ace/post.h"

#endif // !defined(UTILITY_POOL_OBJECTPOOL_H)
