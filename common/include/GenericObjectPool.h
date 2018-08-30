// GenericObjectPool.h: interface for the GenericObjectPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined UTILITY_POOL_GENERICOBJECTPOOL_H
#define UTILITY_POOL_GENERICOBJECTPOOL_H

#include "ace/pre.h"
#include "ace/Task.h"
#include "ace/SString.h"
#include "ObjectPool.h"
#include "deque"

namespace utility
{
namespace pool
{

    //--- public constants -------------------------------------------

    /**
     * A "when exhausted action" type indicating that when the pool is
     * exhausted (i.e., the maximum number of active objects has
     * been reached), the {@link #borrowObject}
     * method should fail, throwing a {@link NoSuchElementException}.
     * @see #WHEN_EXHAUSTED_BLOCK
     * @see #WHEN_EXHAUSTED_GROW
     * @see #setWhenExhaustedAction
     */
	#define  WHEN_EXHAUSTED_FAIL    0

    /**
     * A "when exhausted action" type indicating that when the pool
     * is exhausted (i.e., the maximum number
     * of active objects has been reached), the {@link #borrowObject}
     * method should block until a new object is available, or the
     * {@link #getMaxWait maximum wait time} has been reached.
     * @see #WHEN_EXHAUSTED_FAIL
     * @see #WHEN_EXHAUSTED_GROW
     * @see #setMaxWait
     * @see #getMaxWait
     * @see #setWhenExhaustedAction
     */
    #define WHEN_EXHAUSTED_BLOCK   1

    /**
     * A "when exhausted action" type indicating that when the pool is
     * exhausted (i.e., the maximum number
     * of active objects has been reached), the {@link #borrowObject}
     * method should simply create a new object anyway.
     * @see #WHEN_EXHAUSTED_FAIL
     * @see #WHEN_EXHAUSTED_GROW
     * @see #setWhenExhaustedAction
     */
    #define WHEN_EXHAUSTED_GROW    2

    /**
     * The default cap on the number of "sleeping" instances in the pool.
     * @see #getMaxIdle
     * @see #setMaxIdle
     */
    #define DEFAULT_MAX_IDLE   10

    /**
     * The default minimum number of "sleeping" instances in the pool
     * before before the evictor thread (if active) spawns new objects.
     * @see #getMinIdle
     * @see #setMinIdle
     */
    #define DEFAULT_MIN_IDLE  5

    /**
     * The default cap on the total number of active instances from the pool.
     * @see #getMaxActive
     */
    #define DEFAULT_MAX_ACTIVE   10

    /**
     * The default "when exhausted action" for the pool.
     * @see #WHEN_EXHAUSTED_BLOCK
     * @see #WHEN_EXHAUSTED_FAIL
     * @see #WHEN_EXHAUSTED_GROW
     * @see #setWhenExhaustedAction
     */
    #define DEFAULT_WHEN_EXHAUSTED_ACTION  WHEN_EXHAUSTED_BLOCK

    /**
     * The default maximum amount of time (in millis) the
     * {@link #borrowObject} method should block before throwing
     * an exception when the pool is exhausted and the
     * {@link #getWhenExhaustedAction "when exhausted" action} is
     * {@link #WHEN_EXHAUSTED_BLOCK}.
     * @see #getMaxWait
     * @see #setMaxWait
     */
    #define DEFAULT_MAX_WAIT  -1

    /**
     * The default "test on borrow" value.
     * @see #getTestOnBorrow
     * @see #setTestOnBorrow
     */
    #define DEFAULT_TEST_ON_BORROW  false

    /**
     * The default "test on return" value.
     * @see #getTestOnReturn
     * @see #setTestOnReturn
     */
    #define DEFAULT_TEST_ON_RETURN  false

    /**
     * The default "test while idle" value.
     * @see #getTestWhileIdle
     * @see #setTestWhileIdle
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    #define DEFAULT_TEST_WHILE_IDLE  false

    /**
     * The default "time between eviction runs" value.
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    #define DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS  50

    /**
     * The default number of objects to examine per run in the
     * idle object evictor.
     * @see #getNumTestsPerEvictionRun
     * @see #setNumTestsPerEvictionRun
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    #define DEFAULT_NUM_TESTS_PER_EVICTION_RUN  3

    /**
     * The default value for {@link #getMinEvictableIdleTimeMillis}.
     * @see #getMinEvictableIdleTimeMillis
     * @see #setMinEvictableIdleTimeMillis
     */
    #define DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS  1000L*60L*30L

/**
* A simple "struct" encapsulating the
* configuration information for a {@link GenericObjectPool}.
* @see GenericObjectPool#GenericObjectPool(org.apache.commons.pool.PoolableObjectFactory,org.apache.commons.pool.impl.GenericObjectPool.Config)
* @see GenericObjectPool#setConfig
*/
struct GenericObjectPoolConfig
{
public:
	int maxIdle ;//= DEFAULT_MAX_IDLE;
	int minIdle ;//= DEFAULT_MIN_IDLE;
	int maxActive ;//= DEFAULT_MAX_ACTIVE;
	long maxWait ;//= DEFAULT_MAX_WAIT;
	unsigned char whenExhaustedAction ;//= DEFAULT_WHEN_EXHAUSTED_ACTION;
	bool testOnBorrow ;//= DEFAULT_TEST_ON_BORROW;
	bool testOnReturn ;//= DEFAULT_TEST_ON_RETURN;
	bool testWhileIdle ;//= DEFAULT_TEST_WHILE_IDLE;
	long timeBetweenEvictionRunsMillis ;//= DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS;
	int numTestsPerEvictionRun ;//=  DEFAULT_NUM_TESTS_PER_EVICTION_RUN;
	long minEvictableIdleTimeMillis ;//= DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS;
	
	GenericObjectPoolConfig()
	{
		maxIdle = DEFAULT_MAX_IDLE;
		minIdle = DEFAULT_MIN_IDLE;
		maxActive = DEFAULT_MAX_ACTIVE;
		maxWait = DEFAULT_MAX_WAIT;
		whenExhaustedAction = DEFAULT_WHEN_EXHAUSTED_ACTION;
		testOnBorrow = DEFAULT_TEST_ON_BORROW;
		testOnReturn = DEFAULT_TEST_ON_RETURN;
		testWhileIdle = DEFAULT_TEST_WHILE_IDLE;
		timeBetweenEvictionRunsMillis = DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS;
		numTestsPerEvictionRun =  DEFAULT_NUM_TESTS_PER_EVICTION_RUN;
		minEvictableIdleTimeMillis = DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS;
		
	}
	
};

/**
* A simple "struct" encapsulating an object instance and a timestamp.
*/
class ObjectTimestampPair 
{
public :
	void* value;
	ACE_Time_Value tstamp;
	
	ObjectTimestampPair(void* val)
	{
		value = val;
		tstamp = ACE_OS::gettimeofday();
	}
	
	ObjectTimestampPair(void* val, ACE_Time_Value& time) 
	{
		value = val;
		tstamp = time;
	}
};	
/**
* A configurable {@link ObjectPool} implementation.
* <p>
* When coupled with the appropriate {@link PoolableObjectFactory},
* <tt>GenericObjectPool</tt> provides robust pooling functionality for
* arbitrary objects.
* <p>
* A <tt>GenericObjectPool</tt> provides a number of configurable parameters:
* <ul>
*  <li>
*    {@link #setMaxActive <i>maxActive</i>} controls the maximum number of objects that can
*    be borrowed from the pool at one time.  When non-positive, there
*    is no limit to the number of objects that may be active at one time.
*    When {@link #setMaxActive <i>maxActive</i>} is exceeded, the pool is said to be exhausted.
*  </li>
*  <li>
*    {@link #setMaxIdle <i>maxIdle</i>} controls the maximum number of objects that can
*    sit idle in the pool at any time.  When negative, there
*    is no limit to the number of objects that may be idle at one time.
*  </li>
*  <li>
*    {@link #setWhenExhaustedAction <i>whenExhaustedAction</i>} specifies the
*    behaviour of the {@link #borrowObject} method when the pool is exhausted:
*    <ul>
*    <li>
*      When {@link #setWhenExhaustedAction <i>whenExhaustedAction</i>} is
*      {@link #WHEN_EXHAUSTED_FAIL}, {@link #borrowObject} will throw
*      a {@link NoSuchElementException}
*    </li>
*    <li>
*      When {@link #setWhenExhaustedAction <i>whenExhaustedAction</i>} is
*      {@link #WHEN_EXHAUSTED_GROW}, {@link #borrowObject} will create a new
*      object and return it(essentially making {@link #setMaxActive <i>maxActive</i>}
*      meaningless.)
*    </li>
*    <li>
*      When {@link #setWhenExhaustedAction <i>whenExhaustedAction</i>}
*      is {@link #WHEN_EXHAUSTED_BLOCK}, {@link #borrowObject} will block
*      (invoke {@link Object#wait} until a new or idle object is available.
*      If a positive {@link #setMaxWait <i>maxWait</i>}
*      value is supplied, the {@link #borrowObject} will block for at
*      most that many milliseconds, after which a {@link NoSuchElementException}
*      will be thrown.  If {@link #setMaxWait <i>maxWait</i>} is non-positive,
*      the {@link #borrowObject} method will block indefinitely.
*    </li>
*    </ul>
*  </li>
*  <li>
*    When {@link #setTestOnBorrow <i>testOnBorrow</i>} is set, the pool will
*    attempt to validate each object before it is returned from the
*    {@link #borrowObject} method. (Using the provided factory's
*    {@link PoolableObjectFactory#validateObject} method.)  Objects that fail
*    to validate will be dropped from the pool, and a different object will
*    be borrowed.
*  </li>
*  <li>
*    When {@link #setTestOnReturn <i>testOnReturn</i>} is set, the pool will
*    attempt to validate each object before it is returned to the pool in the
*    {@link #returnObject} method. (Using the provided factory's
*    {@link PoolableObjectFactory#validateObject}
*    method.)  Objects that fail to validate will be dropped from the pool.
*  </li>
* </ul>
* <p>
* Optionally, one may configure the pool to examine and possibly evict objects as they
* sit idle in the pool.  This is performed by an "idle object eviction" thread, which
* runs asychronously.  The idle object eviction thread may be configured using the
* following attributes:
* <ul>
*  <li>
*   {@link #setTimeBetweenEvictionRunsMillis <i>timeBetweenEvictionRunsMillis</i>}
*   indicates how long the eviction thread should sleep before "runs" of examining
*   idle objects.  When non-positive, no eviction thread will be launched.
*  </li>
*  <li>
*   {@link #setMinEvictableIdleTimeMillis <i>minEvictableIdleTimeMillis</i>}
*   specifies the minimum amount of time that an object may sit idle in the pool
*   before it is eligable for eviction due to idle time.  When non-positive, no object
*   will be dropped from the pool due to idle time alone.
*  </li>
*  <li>
*   {@link #setTestWhileIdle <i>testWhileIdle</i>} indicates whether or not idle
*   objects should be validated using the factory's
*   {@link PoolableObjectFactory#validateObject} method.  Objects
*   that fail to validate will be dropped from the pool.
*  </li>
* </ul>
* <p>
* GenericObjectPool is not usable without a {@link PoolableObjectFactory}.  A
* non-<code>null</code> factory must be provided either as a constructor argument
* or via a call to {@link #setFactory} before the pool is used.
*
* @author 肖猛 (移植自Jakarta)
* @version $Revision: 1.1.1.1 $ $Date: 2005/08/11 14:39:52 $
*/
template <class T,class FACTORY,ACE_SYNCH_DECL>
class GenericObjectPool : public ObjectPool<T,FACTORY>, public ACE_Task<ACE_SYNCH_USE>
{

    //--- private attributes ---------------------------------------
private:
    /**
     * The cap on the number of idle instances in the pool.
     * @see #setMaxIdle
     * @see #getMaxIdle
     */
    int _maxIdle ;//= DEFAULT_MAX_IDLE;

    /**
    * The cap on the minimum number of idle instances in the pool.
    * @see #setMinIdle
    * @see #getMinIdle
    */
   int _minIdle ;//= DEFAULT_MIN_IDLE;

    /**
     * The cap on the total number of active instances from the pool.
     * @see #setMaxActive
     * @see #getMaxActive
     */
    int _maxActive ;//= DEFAULT_MAX_ACTIVE;

    /**
     * The maximum amount of time (in millis) the
     * {@link #borrowObject} method should block before throwing
     * an exception when the pool is exhausted and the
     * {@link #getWhenExhaustedAction "when exhausted" action} is
     * {@link #WHEN_EXHAUSTED_BLOCK}.
     *
     * When less than 0, the {@link #borrowObject} method
     * may block indefinitely.
     *
     * @see #setMaxWait
     * @see #getMaxWait
     * @see #WHEN_EXHAUSTED_BLOCK
     * @see #setWhenExhaustedAction
     * @see #getWhenExhaustedAction
     */
    long _maxWait ;//= DEFAULT_MAX_WAIT;

    /**
     * The action to take when the {@link #borrowObject} method
     * is invoked when the pool is exhausted (the maximum number
     * of "active" objects has been reached).
     *
     * @see #WHEN_EXHAUSTED_BLOCK
     * @see #WHEN_EXHAUSTED_FAIL
     * @see #WHEN_EXHAUSTED_GROW
     * @see #DEFAULT_WHEN_EXHAUSTED_ACTION
     * @see #setWhenExhaustedAction
     * @see #getWhenExhaustedAction
     */
    unsigned char _whenExhaustedAction ;//= DEFAULT_WHEN_EXHAUSTED_ACTION;

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned by the {@link #borrowObject}
     * method.  If the object fails to validate,
     * it will be dropped from the pool, and we will attempt
     * to borrow another.
     *
     * @see #setTestOnBorrow
     * @see #getTestOnBorrow
     */
    bool _testOnBorrow ;//= DEFAULT_TEST_ON_BORROW;

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned to the pool within the
     * {@link #returnObject}.
     *
     * @see #getTestOnReturn
     * @see #setTestOnReturn
     */
    bool _testOnReturn ;//= DEFAULT_TEST_ON_RETURN;

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * by the idle object evictor (if any).  If an object
     * fails to validate, it will be dropped from the pool.
     *
     * @see #setTestWhileIdle
     * @see #getTestWhileIdle
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    bool _testWhileIdle ;//= DEFAULT_TEST_WHILE_IDLE;

    /**
     * The number of milliseconds to sleep between runs of the
     * idle object evictor thread.
     * When non-positive, no idle object evictor thread will be
     * run.
     *
     * @see #setTimeBetweenEvictionRunsMillis
     * @see #getTimeBetweenEvictionRunsMillis
     */
    long _timeBetweenEvictionRunsMillis ;//= DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS;

    /**
     * The number of objects to examine during each run of the
     * idle object evictor thread (if any).
     * <p>
     * When a negative value is supplied, <tt>ceil({@link #getNumIdle})/abs({@link #getNumTestsPerEvictionRun})</tt>
     * tests will be run.  I.e., when the value is <i>-n</i>, roughly one <i>n</i>th of the
     * idle objects will be tested per run.
     *
     * @see #setNumTestsPerEvictionRun
     * @see #getNumTestsPerEvictionRun
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int _numTestsPerEvictionRun ;//=  DEFAULT_NUM_TESTS_PER_EVICTION_RUN;

    /**
     * The minimum amount of time an object may sit idle in the pool
     * before it is eligable for eviction by the idle object evictor
     * (if any).
     * When non-positive, no objects will be evicted from the pool
     * due to idle time alone.
     *
     * @see #setMinEvictableIdleTimeMillis
     * @see #getMinEvictableIdleTimeMillis
     * @see #getTimeBetweenEvictionRunsMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    long _minEvictableIdleTimeMillis ;//= DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS;

    /** My pool. */
    //private CursorableLinkedList _pool = null;

    /** My {@link PoolableObjectFactory}. */
    FACTORY* _factory ;// = null;

    /**
     * The number of objects {@link #borrowObject} borrowed
     * from the pool, but not yet returned.
     */
    int _numActive ;//= 0;

    /**
     * My idle object eviction thread, if any.
     */
    //private Evictor _evictor = null;

    //private CursorableLinkedList.Cursor _evictionCursor = null;
private:
    //--- inner classes ----------------------------------------------
	


typedef std::deque<ObjectTimestampPair*> INNER_POOL;

private:
	INNER_POOL _pool;
	

public:
	virtual ~GenericObjectPool();
    //--- constructors -----------------------------------------------

 
    /**
     * Create a new <tt>GenericObjectPool</tt> using the specified values.
     * @param factory the (possibly <tt>null</tt>)PoolableObjectFactory to use to create, validate and destroy objects
     * @param maxActive the maximum number of objects that can be borrowed from me at one time (see {@link #setMaxActive})
     * @param whenExhaustedAction the action to take when the pool is exhausted (see {@link #setWhenExhaustedAction})
     * @param maxWait the maximum amount of time to wait for an idle object when the pool is exhausted an and <i>whenExhaustedAction</i> is {@link #WHEN_EXHAUSTED_BLOCK} (otherwise ignored) (see {@link #setMaxWait})
     * @param maxIdle the maximum number of idle objects in my pool (see {@link #setMaxIdle})
     * @param minIdle the minimum number of idle objects in my pool (see {@link #setMinIdle})
     * @param testOnBorrow whether or not to validate objects before they are returned by the {@link #borrowObject} method (see {@link #setTestOnBorrow})
     * @param testOnReturn whether or not to validate objects after they are returned to the {@link #returnObject} method (see {@link #setTestOnReturn})
     * @param timeBetweenEvictionRunsMillis the amount of time (in milliseconds) to sleep between examining idle objects for eviction (see {@link #setTimeBetweenEvictionRunsMillis})
     * @param numTestsPerEvictionRun the number of idle objects to examine per run within the idle object eviction thread (if any) (see {@link #setNumTestsPerEvictionRun})
     * @param minEvictableIdleTimeMillis the minimum number of milliseconds an object can sit idle in the pool before it is eligable for evcition (see {@link #setMinEvictableIdleTimeMillis})
     * @param testWhileIdle whether or not to validate objects in the idle object eviction thread, if any (see {@link #setTestWhileIdle})
     */
    GenericObjectPool(
		const char* name,
		FACTORY* factory = NULL,
		int maxActive = DEFAULT_MAX_ACTIVE, 
		unsigned char whenExhaustedAction = DEFAULT_WHEN_EXHAUSTED_ACTION,
		long maxWait = DEFAULT_MAX_WAIT,
		int maxIdle = DEFAULT_MAX_IDLE, 
		int minIdle = DEFAULT_MIN_IDLE,
		bool testOnBorrow = DEFAULT_TEST_ON_BORROW,
		bool testOnReturn = DEFAULT_TEST_ON_RETURN,
		long timeBetweenEvictionRunsMillis = DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS,
		int numTestsPerEvictionRun = DEFAULT_NUM_TESTS_PER_EVICTION_RUN,
		long minEvictableIdleTimeMillis = DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS,
		bool testWhileIdle = DEFAULT_TEST_WHILE_IDLE);
	
private:
	void init_i(const char* name,FACTORY* factory, int maxActive, unsigned char whenExhaustedAction, long maxWait, int maxIdle, int minIdle, bool testOnBorrow, bool testOnReturn, long timeBetweenEvictionRunsMillis, int numTestsPerEvictionRun, long minEvictableIdleTimeMillis, bool testWhileIdle);

protected:
	// = Synchronization primitives for controlling concurrent access.
	/// Protect queue from concurrent access.
	ACE_SYNCH_MUTEX_T lock_;
	
	/// 当没有可用对象时,此变量用来让发出请求的线程等待
	ACE_SYNCH_CONDITION_T no_available_cond_;

public:
    //--- configuration methods --------------------------------------

    /**
     * Returns the cap on the total number of active instances from my pool.
     * @return the cap on the total number of active instances from my pool.返回-1表示操作失败
     * @see #setMaxActive
     */
    int getMaxActive()
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
        return _maxActive;
    }

    /**
     * Sets the cap on the total number of active instances from my pool.
     * @param maxActive The cap on the total number of active instances from my pool.
     *                  Use a negative value for an infinite number of instances.
	 * @return 返回-1表示操作失败
     * @see #getMaxActive
     */
     int setMaxActive(int maxActive)
	 {
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_maxActive = maxActive;
		this->no_available_cond_.broadcast ();
		return 0;
	 }

    /**
     * Returns the action to take when the {@link #borrowObject} method
     * is invoked when the pool is exhausted (the maximum number
     * of "active" objects has been reached).
     *
     * @return one of {@link #WHEN_EXHAUSTED_BLOCK}, {@link #WHEN_EXHAUSTED_FAIL} or {@link #WHEN_EXHAUSTED_GROW}
     * @see #setWhenExhaustedAction
     */
    unsigned char getWhenExhaustedAction()
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
        return _whenExhaustedAction;
    }

    /**
     * Sets the action to take when the {@link #borrowObject} method
     * is invoked when the pool is exhausted (the maximum number
     * of "active" objects has been reached).
     *
     * @param whenExhaustedAction the action code, which must be one of
     *        {@link #WHEN_EXHAUSTED_BLOCK}, {@link #WHEN_EXHAUSTED_FAIL},
     *        or {@link #WHEN_EXHAUSTED_GROW}
     * @see #getWhenExhaustedAction
     */
    int setWhenExhaustedAction(unsigned char whenExhaustedAction)
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        switch(whenExhaustedAction) {
            case WHEN_EXHAUSTED_BLOCK:
            case WHEN_EXHAUSTED_FAIL:
            case WHEN_EXHAUSTED_GROW:
                _whenExhaustedAction = whenExhaustedAction;
				this->no_available_cond_.broadcast ();
                break;
            //default:
              //  throw new IllegalArgumentException("whenExhaustedAction " + whenExhaustedAction + " not recognized.");
        }
		return 0;
    }


    /**
     * Returns the maximum amount of time (in milliseconds) the
     * {@link #borrowObject} method should block before throwing
     * an exception when the pool is exhausted and the
     * {@link #setWhenExhaustedAction "when exhausted" action} is
     * {@link #WHEN_EXHAUSTED_BLOCK}.
     *
     * When less than 0, the {@link #borrowObject} method
     * may block indefinitely.
     *
     * @see #setMaxWait
     * @see #setWhenExhaustedAction
     * @see #WHEN_EXHAUSTED_BLOCK
     */
    long getMaxWait() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        return _maxWait;
    }

    /**
     * Sets the maximum amount of time (in milliseconds) the
     * {@link #borrowObject} method should block before throwing
     * an exception when the pool is exhausted and the
     * {@link #setWhenExhaustedAction "when exhausted" action} is
     * {@link #WHEN_EXHAUSTED_BLOCK}.
     *
     * When less than 0, the {@link #borrowObject} method
     * may block indefinitely.
     *
     * @see #getMaxWait
     * @see #setWhenExhaustedAction
     * @see #WHEN_EXHAUSTED_BLOCK
     */
    int setMaxWait(long maxWait) {
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_maxWait = maxWait;
		this->no_available_cond_.broadcast ();
        return 0;
    }

    /**
     * Returns the cap on the number of "idle" instances in the pool.
     * @return the cap on the number of "idle" instances in the pool.
     * @see #setMaxIdle
     */
    int getMaxIdle() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		return _maxIdle;
    }

    /**
     * Sets the cap on the number of "idle" instances in the pool.
     * @param maxIdle The cap on the number of "idle" instances in the pool.
     *                Use a negative value to indicate an unlimited number
     *                of idle instances.
     * @see #getMaxIdle
     */
    int setMaxIdle(int maxIdle) {
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_maxIdle = maxIdle;
		this->no_available_cond_.broadcast ();
        return 0;
    }

    /**
     * Sets the minimum number of objects allowed in the pool
     * before the evictor thread (if active) spawns new objects.
     * (Note no objects are created when: numActive + numIdle >= maxActive)
     * 
     * @param minIdle The minimum number of objects. 
     * @see #getMinIdle
     */
    int setMinIdle(int minIdle) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_minIdle = minIdle;
		this->no_available_cond_.broadcast ();
        return 0;
    }

    /**
     * Returns the minimum number of objects allowed in the pool
     * before the evictor thread (if active) spawns new objects.
     * (Note no objects are created when: numActive + numIdle >= maxActive)
     *
     * @return The minimum number of objects.
     * @see #setMinIdle
     */
    int getMinIdle() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        return _minIdle;
    }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned by the {@link #borrowObject}
     * method.  If the object fails to validate,
     * it will be dropped from the pool, and we will attempt
     * to borrow another.
     *
     * @see #setTestOnBorrow
     */
     int getTestOnBorrow(bool& istest) 
	 {
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		istest = _testOnBorrow;
		 
        return 0;
	 }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned by the {@link #borrowObject}
     * method.  If the object fails to validate,
     * it will be dropped from the pool, and we will attempt
     * to borrow another.
     *
     * @see #getTestOnBorrow
     */
    int setTestOnBorrow(bool testOnBorrow) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        _testOnBorrow = testOnBorrow;
		return 0;
    }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned to the pool within the
     * {@link #returnObject}.
     *
     * @see #setTestOnReturn
     */
    int getTestOnReturn(bool& istest) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		istest = _testOnReturn;
        return 0;
    }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * before being returned to the pool within the
     * {@link #returnObject}.
     *
     * @see #getTestOnReturn
     */
    int setTestOnReturn(bool testOnReturn) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
        _testOnReturn = testOnReturn;
		return 0;
    }

    /**
     * Returns the number of milliseconds to sleep between runs of the
     * idle object evictor thread.
     * When non-positive, no idle object evictor thread will be
     * run.
     *
     * @see #setTimeBetweenEvictionRunsMillis
     */
    long getTimeBetweenEvictionRunsMillis() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        return _timeBetweenEvictionRunsMillis;
    }

    /**
     * Sets the number of milliseconds to sleep between runs of the
     * idle object evictor thread.
     * When non-positive, no idle object evictor thread will be
     * run.
     *
     * @see #getTimeBetweenEvictionRunsMillis
     */
    int setTimeBetweenEvictionRunsMillis(long timeBetweenEvictionRunsMillis) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        _timeBetweenEvictionRunsMillis = timeBetweenEvictionRunsMillis;
		return 0;
    }

    /**
     * Returns the number of objects to examine during each run of the
     * idle object evictor thread (if any).
     *
     * @see #setNumTestsPerEvictionRun
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int getNumTestsPerEvictionRun() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
        return _numTestsPerEvictionRun;
    }

    /**
     * Sets the number of objects to examine during each run of the
     * idle object evictor thread (if any).
     * <p>
     * When a negative value is supplied, <tt>ceil({@link #getNumIdle})/abs({@link #getNumTestsPerEvictionRun})</tt>
     * tests will be run.  I.e., when the value is <i>-n</i>, roughly one <i>n</i>th of the
     * idle objects will be tested per run.
     *
     * @see #getNumTestsPerEvictionRun
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int setNumTestsPerEvictionRun(int numTestsPerEvictionRun) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_numTestsPerEvictionRun = numTestsPerEvictionRun;
    }

    /**
     * Returns the minimum amount of time an object may sit idle in the pool
     * before it is eligable for eviction by the idle object evictor
     * (if any).
     *
     * @see #setMinEvictableIdleTimeMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    long getMinEvictableIdleTimeMillis() 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
        return _minEvictableIdleTimeMillis;
    }

    /**
     * Sets the minimum amount of time an object may sit idle in the pool
     * before it is eligable for eviction by the idle object evictor
     * (if any).
     * When non-positive, no objects will be evicted from the pool
     * due to idle time alone.
     *
     * @see #getMinEvictableIdleTimeMillis
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int setMinEvictableIdleTimeMillis(long minEvictableIdleTimeMillis) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_minEvictableIdleTimeMillis = minEvictableIdleTimeMillis;
		return 0;
    }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * by the idle object evictor (if any).  If an object
     * fails to validate, it will be dropped from the pool.
     *
     * @see #setTestWhileIdle
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int getTestWhileIdle(bool& istest ) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		istest = _testWhileIdle;
        return 0;
    }

    /**
     * When <tt>true</tt>, objects will be
     * {@link PoolableObjectFactory#validateObject validated}
     * by the idle object evictor (if any).  If an object
     * fails to validate, it will be dropped from the pool.
     *
     * @see #getTestWhileIdle
     * @see #setTimeBetweenEvictionRunsMillis
     */
    int setTestWhileIdle(bool testWhileIdle) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		
        _testWhileIdle = testWhileIdle;
		return 0;
    }

    /**
     * Sets my configuration.
     * @see GenericObjectPool.Config
     */
    int setConfig(GenericObjectPoolConfig* conf) 
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_maxIdle = conf->maxIdle;
		_minIdle = conf->minIdle;
        _maxActive = conf->maxActive;
        _maxWait = conf->maxWait;
        switch(conf->whenExhaustedAction) {
			case WHEN_EXHAUSTED_BLOCK:
			case WHEN_EXHAUSTED_FAIL:
			case WHEN_EXHAUSTED_GROW:
				_whenExhaustedAction = conf->whenExhaustedAction;
				break;
		//	default:
		}
		_testOnBorrow = conf->testOnBorrow;			
        _testOnReturn = conf->testOnReturn;
        _testWhileIdle = conf->testWhileIdle;
        _numTestsPerEvictionRun = conf->numTestsPerEvictionRun;
        _minEvictableIdleTimeMillis = conf->minEvictableIdleTimeMillis;
        _timeBetweenEvictionRunsMillis = conf->timeBetweenEvictionRunsMillis;
		this->no_available_cond_.broadcast ();

		return 0;
    }
    //-- ObjectPool methods ------------------------------------------
	
    virtual T* borrowObject();
	virtual int returnObject(T* obj);
	virtual int invalidateObject(T* obj);
    /**
	* Create an object, and place it into the pool.
	* addObject() is useful for "pre-loading" a pool with idle objects.
	*/
    virtual void addObject();

    virtual int getNumActive() {
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		ACE_ASSERT(!this->isClosed());
        return _numActive;
    }
	virtual int clear();

    virtual int getNumIdle();
	virtual int openPool();	
	virtual int closePool();
	virtual void setFactory(FACTORY* factory);


protected:
   /**
	* Start the eviction thread or service
	*/
	void evict();
    /**
	* Check to see if we are below our minimum number of objects
	* if so enough to bring us back to our minimum.
	*/
    void ensureMinIdle();
	
    int calculateDeficit();
	
    int getNumTests() 
	{
        if(_numTestsPerEvictionRun >= 0) 
            return _numTestsPerEvictionRun;
		else 
            return 5;
	}
		
	
	
public:
    //-- Task methods ------------------------------------------
	
	virtual int svc();
    virtual int open(void * = 0);

private:
	bool _cancelled ; // 用于线程退出控制 [11/14/2003 15:11 肖猛]
	/*
	 *	evict 方法会对所有idle的对象进行检查，删除无效的对象。检查过程中
	 *  为了遍历队列中的所有对象，会使用一个迭代器。每次调用evict方法时只
	 *  检查一定数量的对象，下次调用时从下一个对象开始检查。因此这个迭代器
	 *  要保存以备下次使用。如果其他方法对队列有添加或删除动作，此迭代器很
	 *  不再有效。因此要重新开始遍历。这个变量用来标志当前的迭代器是否有效。
	 *  evict 中发现此变量为false则对迭代器赋新值然后后将此变量设为true。
	 *  其它方法增删队列后将此变量设为false
	 */
	bool _iterator_valid;
	ACE_CString _name;

	/*
	 *	用于遍历idle对象的迭代器
	 */
	INNER_POOL::iterator _evictionCursor;
	
	
};

}
}

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#if !defined (ACE_HAS_BROKEN_HPUX_TEMPLATES)
#include "GenericObjectPool.cpp"
#endif /* !ACE_HAS_BROKEN_HPUX_TEMPLATES */
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("GenericObjectPool.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */


#include "ace/post.h"


#endif // !defined(UTILITY_POOL_GENERICOBJECTPOOL_H)
