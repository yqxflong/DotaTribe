#ifndef  _LC_COBRA_WIN_ALLOCATOR_H
#define  _LC_COBRA_WIN_ALLOCATOR_H


#include "../common/NonCopyable.h"
#include "../common/Declare.h"
#include "../common/Lock.h"
#include "../common/Math.h"
#include "MemNode.h"
#include "Queue.h"
#include "Array.h"

namespace  cobra_win
{


template  <size_t iBlockSize, size_t iArraySize> 
class  Allocator : public  NonCopyable
{
public:
	typedef  Queue<EmptyLock, MemNode>  _MY_QUEUE_;

private:
	Array<EmptyLock, _MY_QUEUE_, iArraySize>  m_Array; // 内存节点分配器数组

public:
	Allocator()
	{
		for (size_t i=0; i<iArraySize; i++)
		{
			m_Array.set2(i, NULL);
		}
	}
	~Allocator()
	{
		destroy_allocator();
	}

public:
	/*
		初始化内存节点分配器
	*/
	inline    bool    init_allocator(size_t iInitNum)
	{
		for (size_t i=0; i<iArraySize; i++)
		{
			_MY_QUEUE_* pQueue = Malloc::new_object<_MY_QUEUE_>();
			for (size_t j=0; j<iInitNum; j++)
			{
				MemNode* pNode = Malloc::new_object<MemNode>();
				pNode->init((i+1)*iBlockSize);
				pQueue->push_back(pNode);
			}
			m_Array.set(i, pQueue);
		}

		return true;
	}
	/*
		销毁内存节点分配器
	*/
	inline    void    destroy_allocator()
	{
		for (size_t i=0; i<iArraySize; i++)
		{
			_MY_QUEUE_* pQueue = m_Array[i];
			if (pQueue != NULL)
			{
				pQueue->destroy();
				Malloc::delete_object<_MY_QUEUE_>(pQueue);

				m_Array.set2(i, NULL);
			}
		}
	}

public:
	/*
		得到一个MemNode指针
	*/
	inline    MemNode*   query_mem_node(size_t iSize)
	{
		size_t iPos = query_xn_index(iBlockSize, iSize);
		if (iPos >= iArraySize)
		{
			MemNode* pNode = Malloc::new_object<MemNode>();
			pNode->init(iSize);

			return pNode;
		}

		_MY_QUEUE_* pQueue = m_Array[iPos];
		MemNode* pNode  = pQueue->pop_front();
		if (pNode->get_buff() == NULL)
		{
			pNode->init((iPos+1)*iBlockSize);
		}
		else
		{
			pNode->clear();
		}

		return pNode;
	}
	/*
		插入一个MemNode指针
	*/
	inline    void       insert_mem_node(MemNode* pNode)
	{
		assert(pNode != NULL);

		size_t iPos = query_xn_index(iBlockSize, pNode->size());
		if (iPos >= iArraySize)
		{
			Malloc::delete_object<MemNode>(pNode);
			return ;
		}

		_MY_QUEUE_* pQueue = m_Array[iPos];
		pQueue->push_back(pNode);
	}
};


}


#endif
