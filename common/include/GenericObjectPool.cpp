// GenericObjectPool.cpp: implementation of the GenericObjectPool class.
//
//////////////////////////////////////////////////////////////////////
#if !defined UTILITY_POOL_GENERICOBJECTPOOL_CPP
#define UTILITY_POOL_GENERICOBJECTPOOL_CPP

#include "include/GenericObjectPool.h"


namespace utility
{
namespace pool
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template <class T,class FACTORY,ACE_SYNCH_DECL>
GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::GenericObjectPool(
		const char* name,
		FACTORY* factory, 
		int maxActive, 
		unsigned char whenExhaustedAction, 
		long maxWait, 
		int maxIdle, 
		int minIdle, 
		bool testOnBorrow, 
		bool testOnReturn, 
		long timeBetweenEvictionRunsMillis, 
		int numTestsPerEvictionRun, 
		long minEvictableIdleTimeMillis, 
		bool testWhileIdle)
	: no_available_cond_ (this->lock_)
{
	init_i(name,factory,maxActive,whenExhaustedAction,maxWait,maxIdle, minIdle, testOnBorrow, testOnReturn, timeBetweenEvictionRunsMillis, numTestsPerEvictionRun, minEvictableIdleTimeMillis, testWhileIdle);
}

template <class T,class FACTORY,ACE_SYNCH_DECL>
void GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::init_i(const char* name,FACTORY* factory, int maxActive, unsigned char whenExhaustedAction, long maxWait, int maxIdle, int minIdle, bool testOnBorrow, bool testOnReturn, long timeBetweenEvictionRunsMillis, int numTestsPerEvictionRun, long minEvictableIdleTimeMillis, bool testWhileIdle)
{
	_name = name;
    _factory = factory;
    _maxActive = maxActive;
    switch(whenExhaustedAction) {
        case WHEN_EXHAUSTED_BLOCK:
        case WHEN_EXHAUSTED_FAIL:
        case WHEN_EXHAUSTED_GROW:
            _whenExhaustedAction = whenExhaustedAction;
            break;
        //default:
           // throw new IllegalArgumentException("whenExhaustedAction " + whenExhaustedAction + " not recognized.");
    }
    _maxWait = maxWait;
    _maxIdle = maxIdle;
    _minIdle = minIdle;
    _testOnBorrow = testOnBorrow;
    _testOnReturn = testOnReturn;
    _timeBetweenEvictionRunsMillis = timeBetweenEvictionRunsMillis;
    _numTestsPerEvictionRun = numTestsPerEvictionRun;
    _minEvictableIdleTimeMillis = minEvictableIdleTimeMillis;
    _testWhileIdle = testWhileIdle;

	_numActive = 0;


}


template <class T,class FACTORY,ACE_SYNCH_DECL>
GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::~GenericObjectPool()
{

}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::openPool()
{

	ACE_ASSERT(this->isClosed());
	
	ensureMinIdle();
	_cancelled = true;// Evict 线程没有运行  [11/14/2003 15:24 肖猛]
	_iterator_valid = false;
	
	open();
	
	ObjectPool<T,FACTORY>::openPool();
	return _pool.size();
}

template <class T,class FACTORY,ACE_SYNCH_DECL>
void GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::addObject()
{
	T* obj = (T*)_factory->makeObject();
	if(obj)
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, ;);
		
		_pool.push_front(new ObjectTimestampPair(obj));
		_iterator_valid = false;
#ifdef _UTILITY_POOL_DEBUG_
		ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] add object sccuess! set _iterator_valid false \n",_name.c_str()));
#endif
		this->no_available_cond_.broadcast (); 
	}
	else
	{
#ifdef _UTILITY_POOL_DEBUG_
		ACE_DEBUG((LM_ERROR,"%s:(T%t)[%D] add object failed!\n",_name.c_str()));
#endif
	}
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::getNumIdle() 
{
	ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
	ACE_ASSERT(!this->isClosed());
	int count = _pool.size();
	return count;
}
template <class T,class FACTORY,ACE_SYNCH_DECL>	
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::closePool()
{
	
	ACE_ASSERT(!this->isClosed());
	_cancelled = true;
	
//	wait();
//	modify by weilb
	ACE_Task_Base::wait();
	ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
	INNER_POOL::iterator it;
	for(it=_pool.begin();it!=_pool.end();++it)
	{
		ObjectTimestampPair* pair = *it;
		_factory->destroyObject(ACE_static_cast(T*,pair->value));
		delete pair;
	}
	_pool.clear();
	this->no_available_cond_.broadcast (); // num sleeping has changed
	_factory = NULL;
#ifdef _UTILITY_POOL_DEBUG_
	ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] pool closed,pool size = %d\n",_name.c_str(),_pool.size()));
#endif
	ObjectPool<T,FACTORY>::closePool();
	return 0;
	
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
void GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::setFactory(FACTORY* factory)
{
	
	ACE_ASSERT(!this->isClosed());
	if(0 < getNumActive()) 
	{
		return;// Objects are already active [11/14/2003 14:55 肖猛]
	}
	else 
	{
		clear();
		_factory = factory;
	}
}



template <class T,class FACTORY,ACE_SYNCH_DECL>
T* GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::borrowObject()
{
#ifdef _UTILITY_POOL_DEBUG_
	ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] In borrowObject. current active = %d, idle = %d\n",_name.c_str(),_numActive,_pool.size()));
#endif
	ACE_Time_Value starttime = ACE_OS::gettimeofday();
	bool newlyCreated = false;
	for(;;) {
		ObjectTimestampPair* pair = NULL;
		
		{	// ACE_GUARD_RETURN 宏在这个作用域内取得同步锁，离开此作用域后释放同步锁 [11/14/2003 9:45 肖猛]
			ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, NULL);
			ACE_ASSERT(!this->isClosed());
			// if there are any sleeping, just grab one of those
			if(!_pool.empty())
			{
				pair = _pool.front();
				_pool.pop_front();
#ifdef _UTILITY_POOL_DEBUG_
				ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] get object from idle list,set _iterator_valid false\n",_name.c_str()));
#endif
				_iterator_valid = false;
			}
			
			// otherwise
			if(NULL == pair) {
				// check if we can create one
				// (note we know that the num sleeping is 0, else we wouldn't be here)
				if(_maxActive <= 0 || _numActive < _maxActive) {
					// allow new object to be created
#ifdef _UTILITY_POOL_DEBUG_
					ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] no object in idle list,but _numActive < _maxActive ,will creat new\n",_name.c_str()));
#endif
				} else {
#ifdef _UTILITY_POOL_DEBUG_
					ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] no object in idle list,and _numActive >= _maxActive \n",_name.c_str()));
#endif
					
					// the pool is exhausted
					switch(_whenExhaustedAction) {
					case WHEN_EXHAUSTED_GROW:
						// allow new object to be created
#ifdef _UTILITY_POOL_DEBUG_
						ACE_DEBUG((LM_INFO,"%s:(T%t)[%D] _whenExhaustedAction = WHEN_EXHAUSTED_GROW,will creat new",_name.c_str()));
#endif
						break;
					case WHEN_EXHAUSTED_FAIL:
						//throw new NoSuchElementException();
#ifdef _UTILITY_POOL_DEBUG_
						ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]_whenExhaustedAction = WHEN_EXHAUSTED_FAIL,borrow object failed!",_name.c_str()));
#endif
						
						return NULL;
						break;
					case WHEN_EXHAUSTED_BLOCK:
#ifdef _UTILITY_POOL_DEBUG_
						ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]_whenExhaustedAction = WHEN_EXHAUSTED_BLOCK,wait for object!\n",_name.c_str()));
#endif						
						if(_maxWait <= 0) 
						{
#ifdef _UTILITY_POOL_DEBUG_
							ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]wait for object forever\n",_name.c_str()));
#endif
							no_available_cond_.wait();
						} 
						else 
						{
#ifdef _UTILITY_POOL_DEBUG_
							ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]wait for object %d seconds\n",_name.c_str(),_maxWait));
#endif
							ACE_Time_Value time(0,_maxWait*1000);
							no_available_cond_.wait(&time);// ACE_Time_Value 第二个参数是微秒 [11/14/2003 10:55 肖猛]
						}
							
						if(_maxWait > 0 && ((ACE_OS::gettimeofday().msec() - starttime.msec()) >= _maxWait))
						{
#ifdef _UTILITY_POOL_DEBUG_
							ACE_DEBUG((LM_ERROR,"%s:(T%t)[%D]Timeout waiting for idle object\n",_name.c_str()));
#endif
							return NULL;
						} else {
							continue; // keep looping
						}
					}
				}
			}
			_numActive++;
		} // end synchronized
		
		// create new object when needed
		if(NULL == pair) 
		{
#ifdef _UTILITY_POOL_DEBUG_
			ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]now creat new object\n",_name.c_str()));
#endif
			T* obj = _factory->makeObject();
			if(obj)
			{
				pair = new ObjectTimestampPair(obj);
#ifdef _UTILITY_POOL_DEBUG_
				ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]creat new object sccuess\n",_name.c_str()));
#endif
				newlyCreated = true;
			}
			else
			{
				// object cannot be created
#ifdef _UTILITY_POOL_DEBUG_
				ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]creat new object failed\n",_name.c_str()));
#endif
				
				ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, NULL);
				_numActive--;
				this->no_available_cond_.broadcast ();
				return NULL;
				
			}
		}
		
		// activate & validate the object
		if(_factory->activateObject(ACE_static_cast(T*,pair->value))==0)
		{	// 激活对象成功 [11/14/2003 11:29 肖猛]
			if(!_testOnBorrow)// 不需要测试 [11/14/2003 11:29 肖猛]
			{
				T* tmpObj = ACE_static_cast(T*,pair->value);
				delete pair;
				return tmpObj;

			}
			else if(_factory->validateObject(ACE_static_cast(T*,pair->value))) // 测试成功 [11/14/2003 11:29 肖猛]
			{
#ifdef _UTILITY_POOL_DEBUG_
				ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]test new object sccuess\n",_name.c_str()));
#endif
				T* tmpObj = ACE_static_cast(T*,pair->value);
				delete pair;
				return tmpObj;
				
			}
		}
		// 以下是失败后的处理 [11/14/2003 11:30 肖猛]
		// object cannot be activated or is invalid
			{
				ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, NULL);
				_numActive--;
				this->no_available_cond_.broadcast ();
			}
			_factory->destroyObject(ACE_static_cast(T*,pair->value));
			delete pair;
			if(newlyCreated) {
				return NULL;
			} 
			else {
				continue; // keep looping
			}
		}
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::invalidateObject(T* obj)
{
	ACE_ASSERT(!this->isClosed());
	
	int result = _factory->destroyObject(obj);
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_numActive--;
		this->no_available_cond_.broadcast ();// _numActive has changed
		
	}
	return result;
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::clear() 
{
	ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
	ACE_ASSERT(!this->isClosed());
	INNER_POOL::iterator it;
	for(it=_pool.begin();it!=_pool.end();++it)
	{
		ObjectTimestampPair* pair = *it;
		_factory->destroyObject(ACE_static_cast(T*,pair->value));
		delete pair;
	}
	_pool.clear();
	this->no_available_cond_.broadcast (); // num sleeping has changed

	return 0;
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::returnObject(T* obj)
{
#ifdef _UTILITY_POOL_DEBUG_
	ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]In returnObject! current active = %d, idle = %d\n",_name.c_str(),_numActive,_pool.size()));
#endif
	
	ACE_ASSERT(!this->isClosed());
	bool success = true;
	if(_testOnReturn && !(_factory->validateObject(obj))) {
#ifdef _UTILITY_POOL_DEBUG_
		ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]test object failed when return\n",_name.c_str()));
#endif
		success = false;
	} 
	else if(_factory->passivateObject(obj)==-1)
	{
#ifdef _UTILITY_POOL_DEBUG_
		ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]passivate object failed when return\n",_name.c_str()));
#endif
		
		success = false;
	}
	
	bool shouldDestroy = !success;
	
	{
		ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1);
		_numActive--;
		if((_maxIdle >= 0) && (_pool.size() >= (unsigned int)_maxIdle)) {
#ifdef _UTILITY_POOL_DEBUG_
			ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]there are too much idle object,this return object will be destory\n",_name.c_str()));
#endif
			shouldDestroy = true;
		} else if(success) {
			_pool.push_front(new ObjectTimestampPair(obj));
#ifdef _UTILITY_POOL_DEBUG_
			ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]return object to idle list,set _iterator_valid false\n",_name.c_str()));
#endif
			_iterator_valid = false;
		}
		this->no_available_cond_.broadcast (); // _numActive has changed
	}
	
	if(shouldDestroy) 
	{
#ifdef _UTILITY_POOL_DEBUG_
		ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]start destory object\n",_name.c_str()));
#endif
		_factory->destroyObject(obj);
	}

	return 0;
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::open(void *)
{
	_cancelled = false;
	ACE_Task_Base::activate(THR_NEW_LWP);
	
	return 0;
	
}

template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::svc()
{
	//ACE_DEBUG((LM_INFO,"in svc\n"));
	ACE_Time_Value _delay(0,_timeBetweenEvictionRunsMillis*1000);
	while(!_cancelled)
	{
		ACE_OS::sleep(_delay);
		evict();
		ensureMinIdle();
	}
//	synchronized(GenericObjectPool.this) {
//		if(null != _evictionCursor) {
//			_evictionCursor.close();
//			_evictionCursor = null;
//		}
//	}

	return 0;
	
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
void GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::ensureMinIdle() 
{
	// this method isn't synchronized so the
	// calculateDeficit is done at the beginning
	// as a loop limit and a second time inside the loop
	// to stop when another thread already returned the
	// needed objects
	int objectDeficit = calculateDeficit();
	//ACE_DEBUG((LM_TRACE,"objectDeficit = %d \n",objectDeficit));
	for ( int j = 0 ; j < objectDeficit && calculateDeficit() > 0 ; j++ ) {
		addObject();
	}
}
template <class T,class FACTORY,ACE_SYNCH_DECL>
int GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::calculateDeficit() 
{
	ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, -1;);
	
	int objectDeficit = _minIdle - _pool.size();
	if (_maxActive > 0) 
	{
		int growLimit = _maxActive - _numActive - _pool.size();
		growLimit = growLimit>0 ? growLimit:0;
		objectDeficit = objectDeficit< growLimit ? objectDeficit :  growLimit;
	}
	return objectDeficit;
} 

template <class T,class FACTORY,ACE_SYNCH_DECL>
void GenericObjectPool<T,FACTORY,ACE_SYNCH_USE>::evict()
{
	ACE_GUARD_RETURN (ACE_SYNCH_MUTEX_T, ace_mon, this->lock_, ;);
	ACE_ASSERT(!this->isClosed());
	if(!_pool.empty()) 
	{
		if(!_iterator_valid) 
		{
			_evictionCursor = _pool.begin();
			_iterator_valid = true;
#ifdef _UTILITY_POOL_DEBUG_
			ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]reset evict iterator\n",_name.c_str()));
#endif
		} 
		else if(_evictionCursor == _pool.end()) 
		{
			_evictionCursor = _pool.begin();
		}
		for(int i=0,m=getNumTests();i<m;i++) 
		{
			if(_evictionCursor == _pool.end()) 
			{
				_evictionCursor = _pool.begin();
			} 
			else 
			{
				bool removeObject = false;
				ObjectTimestampPair* pair = *_evictionCursor;
				if(_minEvictableIdleTimeMillis > 0 &&
					ACE_OS::gettimeofday().msec() - pair->tstamp.msec() > _minEvictableIdleTimeMillis) 
				{
#ifdef _UTILITY_POOL_DEBUG_
					ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]idle object expile,will be destory!\n",_name.c_str()));
#endif
					removeObject = true;
				} 
				else if(_testWhileIdle) 
				{
					bool active = false;
					if(_factory->activateObject(ACE_static_cast(T*,pair->value))==0)
						active = true;
					else 
					{
						removeObject=true;
#ifdef _UTILITY_POOL_DEBUG_
						ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]idle object activate failed,will be destory!\n",_name.c_str()));
#endif
						
					}
					if(active) 
					{
						if(!_factory->validateObject(ACE_static_cast(T*,pair->value))) 
							removeObject=true;
						else if(_factory->passivateObject(ACE_static_cast(T*,pair->value))==-1)
							removeObject=true;
					}
				}
				if(removeObject) 
				{
					_pool.erase(_evictionCursor);
#ifdef _UTILITY_POOL_DEBUG_
					ACE_DEBUG((LM_INFO,"%s:(T%t)[%D]pool size = %d\n",_name.c_str(),_pool.size()));
#endif
					_factory->destroyObject(ACE_static_cast(T*,pair->value));
					_iterator_valid = false;
					delete pair;
					break;
				}
				_evictionCursor++;
			}
		}
	} // if !empty
}

}
}

#endif // !defined(UTILITY_POOL_GENERICOBJECTPOOL_CPP)

