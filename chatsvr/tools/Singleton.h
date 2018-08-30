//---------------------------------------------------------------------------

#ifndef SingletonH
#define SingletonH
//---------------------------------------------------------------------------

#include "include/sync.h"


//单例模版类 用法 CTLSingleton<需要做成单例的类名>::GetInstance() 即可获得相应的单例对象，不需要考虑释放
static Mutex g_singletonMetux;
template <class T>
class CTLSingleton
{
public:
	static T * GetInstance()
	{
		if(NULL == m_pInstance)
		{
			//加互斥锁，防止多次创建造成内存泄漏
			MutexObject lock(&g_singletonMetux);
			if(NULL == m_pInstance)
			{
				m_pInstance = new T;
			}
			
		}
		return m_pInstance;
	}
	static void Distroy()
	{
		if(NULL != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
private:
	CTLSingleton()
	{
	}

	virtual ~CTLSingleton()
	{
	}

private:
	static T* m_pInstance;

};

template<class T> T * CTLSingleton<T>::m_pInstance = NULL;


#endif
