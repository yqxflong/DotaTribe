#ifndef  _LC_COBRA_WIN_DLIST_H
#define  _LC_COBRA_WIN_DLIST_H


#include "../common/NonCopyable.h"
#include "Malloc.h"

namespace  cobra_win
{


/*
	双向循环链表节点
	TYPE : 数据元素的类型
*/
template <typename TYPE>
struct  DListNode
{
	struct  DListNode<TYPE>*  pNext;  // 指向下一个元素节点的指针
	struct  DListNode<TYPE>*  pPre;   // 指向上一个元素节点的指针
	TYPE*                     pData;  // 真实的数据指针
	DListNode() : pNext(NULL), pPre(NULL), pData(NULL)
	{

	}
};

/*
	双向循环链表
	LOCK : 锁类型，可以选择空锁(单线程环境中使用)，线程锁(多线程环境中使用)
	TYPE : 真实元素的类型
*/
template <typename LOCK, typename TYPE>
class  DList : public NonCopyable
{
private:
	DListNode<TYPE>*   m_pStart;  // 保留的第一个空元素节点指针
	DListNode<TYPE>*   m_pEnd;    // 指向最末端的数据元素节点指针
	size_t             m_size;    // 节点的个数
	LOCK               m_myLock;  // 串行化锁 

public:
	DList() : m_size(0)
	{
		m_pStart = m_pEnd = Malloc::new_object< DListNode<TYPE> >();
		m_pStart->pNext = m_pStart;
		m_pStart->pPre  = m_pStart;
	}
	~DList()
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
		得到第一个有效元素的节点指针(外部调用的时候，需要手动加锁解锁)
	*/
	inline   DListNode<TYPE>*   begin()
	{
		return m_pStart->pNext;
	}
	/*
		得到最后一个有效元素的节点指针(外部调用的时候，需要手动加锁解锁)
	*/
	inline   DListNode<TYPE>*   end()
	{
		return m_pEnd;
	}
	/*
		得到有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t    size()
	{
		return m_size;
	}
	/*
		添加新的元素节点(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void    resize(size_t num)
	{
		lock();

		for (size_t i=0; i<num; i++)
		{
			alloc_node_from_system();
		}

		unlock();
	}
	/*
		插入元素到末尾(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void    push_back(TYPE* pData)
	{
		assert(pData != NULL);

		lock();

		if (m_pEnd == m_pStart)
		{
			alloc_node_from_system();
		}
		m_pEnd->pData  =  pData;
		m_pEnd         =  m_pEnd->pNext;

		unlock();
	}
	/*
		插入包含有效元素的节点到末尾(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   push_back(DListNode<TYPE>* pNode)
	{
		assert(pNode != NULL);

		lock();

		m_pEnd->pPre->pNext = pNode;
		pNode->pPre         = m_pEnd->pPre;
		pNode->pNext        = m_pEnd;
		m_pEnd->pPre        = pNode;

		unlock();
	}
	/*
		插入一个空的元素节点到末尾(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   push_node(DListNode<TYPE>* pNode)
	{
		assert(pNode != NULL);

		// 清空传进来的pNode节点各个成员
		pNode->pNext = pNode->pPre = NULL;
		pNode->pData = NULL;


		lock();

		// 插入到m_pEnd前面，并重新的调整m_pEnd指针，使其指向pNode
		m_pEnd->pPre->pNext = pNode;
		pNode->pPre         = m_pEnd->pPre;
		pNode->pNext        = m_pEnd;
		m_pEnd->pPre        = pNode;
		m_pEnd              = pNode;

		unlock();
	}
	/*
		在制定的元素节点前面插入数据元素节点(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   insert(DListNode<TYPE>* pPos, DListNode<TYPE>* pNode)
	{
		assert( (pPos!=NULL) && (pNode!=NULL) );

		lock();

		pPos->pPre->pNext = pNode;
		pNode->pPre       = pPos->pPre;
		pNode->pNext      = pPos;
		pPos->pPre        = pNode;

		unlock();
	}
	/*
		在制定的元素节点前面插入一个双向循环链表(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   insert(DListNode<TYPE>* pPos, DList<LOCK, TYPE>* pDList)
	{
		assert( (pPos!=NULL) && (pDList!=NULL) );

		lock();

		pDList->lock();

		DListNode<TYPE>*  pBegin = pDList->begin();
		DListNode<TYPE>*  pEnd   = pDList->end();
		if (pBegin != pEnd)
		{ // 确保她里面有真实的元素
			DListNode<TYPE>*  _pTemp = pBegin->pPre;

			pPos->pPre->pNext = pBegin;
			pBegin->pPre      = pPos->pPre;
			pEnd->pPre->pNext = pPos;
			pPos->pPre        = pEnd->pPre;

			// 把原来的pDList里面的元素清空，只保留最原始的m_pStart
			pEnd->pPre        = _pTemp;
			_pTemp->pNext     = pEnd;
		}

		pDList->unlock();

		unlock();
	}
	/*
		删除制定元素节点,不能删除双向链表中最原始保留的节点m_pStart(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void   erase(DListNode<TYPE>* pPos)
	{
		assert( (pPos!=m_pStart) && (pPos!=NULL) );

		pPos->pPre->pNext = pPos->pNext;
		pPos->pNext->pPre = pPos->pPre;
	}
	/*
		销毁双向循环链表(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void   destroy()
	{
		lock();

		// 必须放进来，不然存在潜在的致命bug
		if (m_pStart == NULL)
		{
			unlock();
			return ;
		}

		DListNode<TYPE>* pBegin = m_pStart->pNext;
		while (pBegin != m_pEnd)
		{
			DListNode<TYPE>* _pTemp = pBegin;
			pBegin                  = pBegin->pNext;
			Malloc::delete_object<TYPE>(_pTemp->pData);
			Malloc::delete_object< DListNode<TYPE> >(_pTemp);
		}
		while (m_pEnd != m_pStart)
		{
			DListNode<TYPE>* _pTemp = m_pEnd;
			m_pEnd                  = m_pEnd->pNext;
			Malloc::delete_object< DListNode<TYPE> >(_pTemp);
		}
		Malloc::delete_object< DListNode<TYPE> >(m_pStart);
		m_pStart = m_pEnd = NULL;

		unlock();
	}

private:
	/*
		从系统中分配新的元素节点，插入到结尾
	*/
	inline   void   alloc_node_from_system()
	{
		DListNode<TYPE>* pNode = Malloc::new_object< DListNode<TYPE> >();
		m_pEnd->pPre->pNext    = pNode;
		pNode->pPre            = m_pEnd->pPre;
		pNode->pNext           = m_pEnd;
		m_pEnd->pPre           = pNode;
		m_pEnd                 = pNode;
	}
};


}



#endif
