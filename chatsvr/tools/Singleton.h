//---------------------------------------------------------------------------

#ifndef SingletonH
#define SingletonH
//---------------------------------------------------------------------------

#include "include/sync.h"


//����ģ���� �÷� CTLSingleton<��Ҫ���ɵ���������>::GetInstance() ���ɻ����Ӧ�ĵ������󣬲���Ҫ�����ͷ�
static Mutex g_singletonMetux;
template <class T>
class CTLSingleton
{
public:
	static T * GetInstance()
	{
		if(NULL == m_pInstance)
		{
			//�ӻ���������ֹ��δ�������ڴ�й©
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
