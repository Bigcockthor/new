// PoolableObjectFactory.h: interface for the PoolableObjectFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined UTILITY_POOL_POOLABLEOBJECTFACTORY_H
#define UTILITY_POOL_POOLABLEOBJECTFACTORY_H


namespace utility
{
namespace pool
{
/**
* An interface defining life-cycle methods for
* instances to be used in an
* {@link ObjectPool ObjectPool}.
* <p>
* By contract, when an {@link ObjectPool ObjectPool}
* delegates to a <tt>PoolableObjectFactory</tt>,
* <ol>
*  <li>
*   {@link #makeObject makeObject} 
*   is called  whenever a new instance is needed.
*  </li>
*  <li>
*   {@link #activateObject activateObject} 
*   is invoked on every instance before it is returned from the
*   pool.
*  </li>
*  <li>
*   {@link #passivateObject passivateObject} 
*   is invoked on every instance when it is returned to the
*   pool.
*  </li>
*  <li>
*   {@link #destroyObject destroyObject} 
*   is invoked on every instance when it is being "dropped" from the
*   pool (whether due to the response from
*   {@link #validateObject validateObject}, or
*   for reasons specific to the pool implementation.)
*  </li>
*  <li>
*   {@link #validateObject validateObject} 
*   is invoked in an implementation-specific fashion to determine if an instance
*   is still valid to be returned by the pool.
*   It will only be invoked on an {@link #activateObject "activated"}
*   instance.
*  </li>
* </ol>
*
* java �汾������ӿ������ж��󹤳�����ʵ�ֵġ�C++�汾�������ʵ���Ǳ���
* �ģ���Ϊ����ģ��ʵ�ֶ���أ���ObjectPoolģ����ʵ����ʱָ�����󹤳�����
* �͡�ֻҪ�ö��󹤳�����ӵ��PoolableObjectFactoryͨ���ĵ���Ӧ��������Ȼ��
* �������ݵĶ�����������Ƕ���ع���Ķ������ͣ�������void* ��ʵ������Ҳ
* �����˶��󹤳��Ľӿڣ�ֻ�������ڱ����ڼ���ɼ����ѡ���Ҳ��C++ģ�����
* �����ڡ��Һó���ϡ�
*
* ��������ȫ���ԴӴ�����ɾ������������Ϊ��һ���ο���
*
* @author Ф�� (��ֲ��Jakarta)
*
* @see ObjectPool
*/
class PoolableObjectFactory  
{
public:
	PoolableObjectFactory();
	virtual ~PoolableObjectFactory();
	/**
	* Creates an instance that can be returned by the pool.
	* @return an instance that can be returned by the pool.
	*/
	virtual void* makeObject() = 0;
	
	/**
	* Destroys an instance no longer needed by the pool.
	* @param obj the instance to be destroyed
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	virtual int destroyObject(void* obj) = 0;
	
	/**
	* Ensures that the instance is safe to be returned by the pool.
	* Returns <tt>false</tt> if this object should be destroyed.
	* @param obj the instance to be validated
	* @return <tt>false</tt> if this <i>obj</i> is not valid and should
	*         be dropped from the pool, <tt>true</tt> otherwise.
	*/
	virtual bool validateObject(void* obj) = 0;
	
	/**
	* Reinitialize an instance to be returned by the pool.
	* @param obj the instance to be activated
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	virtual int activateObject(void* obj) = 0;
	
	/**
	* Uninitialize an instance to be returned to the pool.
	* @param obj the instance to be passivated
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	virtual int passivateObject(void* obj) = 0;
};


}
}


#endif // !defined(UTILITY_POOL_POOLABLEOBJECTFACTORY_H)
