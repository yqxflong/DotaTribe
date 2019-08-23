#ifndef  _LC_COBRA_WIN_ARRAY_H
#define  _LC_COBRA_WIN_ARRAY_H


/*
* Copyright(c)2008
*
* 文件名称: Array
* 文件标识:
* 摘    要: 数组容器
*
* 当前版本: cobra_win
* 作    者: 关中刀客
* E-Mail  : guanzhongdaoke@gmail.com
* Blog    : http://guan-zhong-dao-ke.blog.163.com/
* 完成时间: 2009年05月23日
*/

#include "../common/NonCopyable.h"
#include "Malloc.h"

namespace  cobra_win
{


/*
	数组
	LOCK : 锁类型，可以选择空锁(单线程环境中使用)，线程锁(多线程环境中使用)
	TYPE : 真实元素的类型
	SIZE : 数组大小
*/
template <typename LOCK, typename TYPE, size_t SIZE>
class  Array : public NonCopyable
{
public:
	TYPE*   m_Array[SIZE];  // 数组
	size_t  m_iArrayLen;    // 数组的长度  
	LOCK    m_myLock;       // 串行化锁

public:
	Array() : m_iArrayLen(SIZE)
	{
		assert(SIZE != 0);
		for (size_t i=0; i<SIZE; i++)
		{
			m_Array[i] = NULL;
		}
	}
	~Array()
	{	
		destroy();	
	}

public:
	/*
		为保证在多线程中正确的操作，
		对外留出线程加锁的操作
	*/
	inline   void   lock()
	{
		m_myLock.lock();
	}
	/*
		为保证在多线程中正确的操作，
		对外留出线程解锁的操作
	*/
	inline   void   unlock()
	{
		m_myLock.unlock();
	}
	/*
		得到数组的长度(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t get_array_length()
	{
		return m_iArrayLen;
	}
	/*
		得到有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t get_element_number()
	{
		size_t iNum = 0;
		for (size_t i=0; i<m_iArrayLen; i++)
		{
			if (m_Array[i] != NULL)
			{
				iNum++;
			}
		}

		return  iNum;
	}
	/*
		得到指定位置的元素(外部调用的时候，需要手动加锁解锁)
	*/
	inline   TYPE*  at(size_t iPos)
	{
		assert(iPos < m_iArrayLen);

		return m_Array[iPos];
	}
	/*
		得到指定位置的元素(外部调用的时候，需要手动加锁解锁)
	*/
	inline   TYPE* operator [](size_t iPos)
	{
		assert(iPos < m_iArrayLen);

		return m_Array[iPos];
	}
	/*
		设置制定位置的元素(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void  set(size_t iPos, TYPE* pData)
	{
		assert(iPos < m_iArrayLen);

		if (m_Array[iPos] == NULL)
		{
			m_Array[iPos] = pData;
		}
		else
		{
			Malloc::delete_object<TYPE>(m_Array[iPos]);
			m_Array[iPos] = pData;
		}
	}
	/*
		设置指定位置的元素(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void   set2(size_t iPos, TYPE* pData)
	{
		assert(iPos < m_iArrayLen);

		m_Array[iPos] = pData;
	}
	/*
		销毁数组(外部调用的时候，且不可加锁解锁)
	*/
	inline   void   destroy()
	{
		m_myLock.lock();

		for (size_t i=0; i<m_iArrayLen; i++)
		{
			if (m_Array[i] != NULL)
			{
				Malloc::delete_object<TYPE>(m_Array[i]);
				m_Array[i] = NULL;
			}
		}

		m_myLock.unlock();
	}
};


}


#endif
