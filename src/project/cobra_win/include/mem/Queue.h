#ifndef  _LC_COBRA_WIN_QUEUE_H
#define  _LC_COBRA_WIN_QUEUE_H


#include "../common/NonCopyable.h"
#include "Malloc.h"

namespace  cobra_win
{


/*
	对列元素节点
	TYPE : 数据元素的类型
*/
template <typename TYPE>
struct  QueueNode
{
	struct  QueueNode<TYPE>*  pNext;  // 指向下一个元素节点的指针
	TYPE*                     pData;  // 真实的数据元素
	QueueNode() : pNext(NULL), pData(NULL)
	{

	}
};

/*
	对列
	LOCK : 锁的类型，可选择空锁(单线程下使用)，或者线程锁(多线程下使用) 
	TYPE : 真实的元素类型
*/
template <typename LOCK, typename TYPE>
class  Queue : public NonCopyable
{
private:
	QueueNode<TYPE>*   m_pBegin;   // 对列的开始位置
	QueueNode<TYPE>*   m_pEnd;     // 对列的结束位置
	QueueNode<TYPE>*   m_pFinish;  // 对列的末尾位置
	size_t             m_size;     // 对列中有效的数据元素个数
	LOCK               m_myLock;   // 串行化锁

public:
	Queue() : m_size(0)
	{
		m_pBegin = m_pEnd = m_pFinish = Malloc::new_object< QueueNode<TYPE> >();
	}
	~Queue()
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
		得到当前对列中真实有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t  size() 
	{
		return m_size;
	}
	/*
		得到对列中第一个有效元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   QueueNode<TYPE>*    begin()  
	{
		return m_pBegin;
	}
	/*
		得到对列中最后一个有效元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   QueueNode<TYPE>*    end() 
	{
		return m_pEnd;
	}
	/*
		增加元素的节点(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   resize(size_t num)
	{
		lock();

		for (size_t i=0; i<num; i++)
		{
			QueueNode<TYPE>* pNode =  Malloc::new_object< QueueNode<TYPE> >();
			m_pFinish->pNext       =  pNode;
			m_pFinish              =  pNode;
		}

		unlock();
	}
	/*
		从对列头中弹出一个元素(内部进行加锁解锁，外部且不可进行加锁解锁)
		如果当前对列为空的话，系统会自动地产生一个节点元素然后返回
	*/
	inline   TYPE*   pop_front()
	{
		TYPE*  pData = NULL;

		lock();

		if (m_pBegin == m_pEnd)
		{
			pData = Malloc::new_object<TYPE>();
		}
		else
		{
			pData                   = m_pBegin->pData;
			QueueNode<TYPE>* _pNode = m_pBegin;
			m_pBegin                = m_pBegin->pNext;
			_pNode->pData           = NULL;
			_pNode->pNext           = NULL;
			insert_node_to_end(_pNode);
			m_size--;
		}

		unlock();

		return pData;
	}
	/*
		从对列头中弹出一个元素(内部进行加锁解锁，外部且不可进行加锁解锁)
		如果当前对列为空的话，返回false,否则返回true
	*/
	inline   bool   pop_front(TYPE** pData)
	{
		bool bRet = false;

		lock();

		if (m_pBegin == m_pEnd)
		{
			*pData = NULL;
			bRet   = false;
		}
		else
		{
			*pData                   =  m_pBegin->pData;
			QueueNode<TYPE>* _pNode  =  m_pBegin;
			m_pBegin                 =  m_pBegin->pNext;
			_pNode->pData            =  NULL;
			_pNode->pNext            =  NULL;
			insert_node_to_end(_pNode);
			m_size--;
			bRet                     =  true;
		}	

		unlock();

		return bRet;
	}
	/*
		把元素压入对列到的末尾(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   push_back(TYPE* pData)
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
		清空对列(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   clear()
	{
		lock();

		m_pEnd  =  m_pBegin;
		m_size  =  0;

		unlock();
	}
	/*
		销毁对列(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   destroy()
	{
		lock();

		QueueNode<TYPE>* pNode = NULL;
		for ( ;m_pBegin!=m_pEnd; )
		{
			pNode    =  m_pBegin;
			m_pBegin =  m_pBegin->pNext;
			Malloc::delete_object<TYPE>(pNode->pData);
			Malloc::delete_object< QueueNode<TYPE> >(pNode);
			m_size--;
		}

		for ( ;m_pEnd!=m_pFinish; )
		{
			pNode  =  m_pEnd;
			m_pEnd =  m_pEnd->pNext;
			Malloc::delete_object< QueueNode<TYPE> >(pNode);
		}

		if (m_pFinish != NULL)
		{
			Malloc::delete_object< QueueNode<TYPE> >(m_pFinish);
		}

		m_pBegin = m_pEnd = m_pFinish = NULL;

		unlock();
	}

private:
	/*
		从系统中分配一个对列元素节点
	*/
	inline   void   alloc_node_from_system()
	{
		QueueNode<TYPE>* pNode = Malloc::new_object< QueueNode<TYPE> >();
		m_pFinish->pNext       = pNode;
		m_pFinish              = pNode;
	}
	/*
		把一个元素节点插入到对列末尾
	*/
	inline   void   insert_node_to_end(QueueNode<TYPE>* pNode)
	{
		m_pFinish->pNext = pNode;
		m_pFinish        = pNode;
	}
};


}


#endif
