#ifndef  _LC_COBRA_WIN_SINGLETON_H
#define  _LC_COBRA_WIN_SINGLETON_H


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

namespace  cobra_win
{


template <typename TYPE>
class  Singleton
{
protected:
	static  TYPE   m_Instance;

public:
	static  TYPE*  get_instance()
	{
		return &m_Instance;
	}
};

template <typename TYPE> TYPE Singleton<TYPE>::m_Instance;


template <typename TYPE>
class  Singleton2
{
protected:
	static  TYPE*  m_pMySelf;

public:
	Singleton2()
	{
		assert(m_pMySelf == NULL);

		m_pMySelf = (TYPE*)this;
	}
	virtual ~Singleton2()
	{
		m_pMySelf = NULL;
	}

public:
	static  TYPE*  get_instance2()
	{
		return m_pMySelf;
	}
};
template<typename TYPE> TYPE* Singleton2<TYPE>::m_pMySelf = NULL;


}


#endif
