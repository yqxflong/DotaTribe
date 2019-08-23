#ifndef  _LC_COBRA_WIN_SLIST_H
#define  _LC_COBRA_WIN_SLIST_H


#include "../common/NonCopyable.h"
#include "Malloc.h"

namespace  cobra_win
{


/*
	单链表元素节点
	TYPE : 元素的类型
*/
template <typename TYPE>
struct  SListNode
{
	struct  SListNode<TYPE>*  pNext;  // 指向下一个元素的节点
	TYPE*                     pData;  // 真实的数据指针
	SListNode() : pNext(NULL), pData(NULL)
	{

	}
};

/*
	单链表容器
	LOCK : 锁的类型，可选择空锁(单线程下使用)，线程锁(多线程下使用)
	TYPE : 数据元素的类型
*/
template <typename LOCK, typename TYPE>
class  SList : public NonCopyable
{
private:
	SListNode<TYPE>*     m_pBegin;   // 单链表的开始位置
	SListNode<TYPE>*     m_pEnd;     // 单链表的结束位置
	SListNode<TYPE>*     m_pFinish;  // 单链表的末尾位置
	size_t               m_size;     // 单链表中真实的元素个数
	LOCK                 m_myLock;   // 串行化锁

public:
	SList() : m_size(0)
	{
		m_pBegin = m_pEnd = m_pFinish = Malloc::new_object< SListNode<TYPE> >();
	}
	~SList()
	{
		destroy();
	}

public:
	/*
		为保证在多线程中正确的操作，
		对外留出线程加锁的操作
	*/
	inline   void    lock()
	{
		m_myLock.lock();
	}
	/*
		为保证在多线程中正确的操作，
		对外留出线程解锁的操作
	*/
	inline   void    unlock()
	{
		m_myLock.unlock();
	}
	/*
		得到有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t  size()
	{
		return m_size;
	}
	/*
		得到第一个有效的元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   SListNode<TYPE>*   begin()  
	{
		return m_pBegin;
	}
	/*
		得到最后一个有效的元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   SListNode<TYPE>*   end() 
	{
		return m_pEnd;
	}
	/*
		得到单链表中第index个元素节点的数据(外部调用的时候，需要手动加锁解锁)
	*/
	inline   TYPE*              at(size_t index)
	{
		if (index > m_size)
			return NULL;

		SListNode<TYPE>* pNode = m_pBegin;
		for (size_t i=0; i<index; i++)
		{
			pNode = pNode->pNext;
		}

		return pNode->pData;
	}
	/*
		添加新的元素节点(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void               resize(size_t num)
	{
		lock();

		for (size_t i=0; i<num; i++)
		{
			SListNode<TYPE>* pNode = Malloc::new_object< SListNode<TYPE> >();
			m_pFinish->pNext = pNode;
			m_pFinish        = pNode;
		}

		unlock();
	}
	/*
		压入有效的元素到单链表末尾(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void               push_back(TYPE* pData)
	{
		assert(pData != NULL);

		lock();

		if (m_pEnd == m_pFinish)
		{
			alloc_node_from_system();
		}
		m_pEnd->pData = pData;
		m_pEnd        = m_pEnd->pNext;
		m_size++;

		unlock();
	}
	/*
		清空单链表(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void               clear()
	{
		lock();

		m_pEnd = m_pBegin;
		m_size = 0;

		unlock();
	}
	/*
		销毁单链表(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void               destroy()
	{
		lock();

		SListNode<TYPE>*  pNode = NULL;
		for ( ;m_pBegin!=m_pEnd; )
		{ // 链表中有真实的数据
			Malloc::delete_object<TYPE>(m_pBegin->pData);
			pNode    =  m_pBegin;
			m_pBegin =  m_pBegin->pNext;
			Malloc::delete_object< SListNode<TYPE> >(pNode);
			m_size--;
		}

		for ( ;m_pEnd!=m_pFinish; )
		{
			pNode  =  m_pEnd;
			m_pEnd =  m_pEnd->pNext;
			Malloc::delete_object< SListNode<TYPE> >(pNode);
		}

		if (m_pFinish != NULL)
			Malloc::delete_object< SListNode<TYPE> >(m_pFinish);

		m_pBegin = m_pEnd = m_pFinish = NULL;

		unlock();
	}

private:
	/*
		从系统中分配元素节点
	*/
	inline   void    alloc_node_from_system()
	{
		SListNode<TYPE>* pNode = Malloc::new_object< SListNode<TYPE> >();
		m_pFinish->pNext       = pNode;
		m_pFinish              = pNode;
	}
};


}


#endif
