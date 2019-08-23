#include "../../include/mem/Allocator2.h"
#include <assert.h>
using  namespace  cobra_win;


#if  0
Allocator2::Allocator2()
{
	m_iMinNodeSize  = 128;
	m_iIntervalSize = 256;
}

Allocator2::~Allocator2()
{
	destroy_allocator();
}

bool       Allocator2::init_allocator(size_t iInitNum)
{
	for (size_t i=0; i<m_Array.get_array_length(); i++)
	{
		_MY_QUEUE_* pQueue = Malloc::new_object<_MY_QUEUE_>();
		for (size_t j=0; j<iInitNum; j++)
		{
			MemNode* pNode = Malloc::new_object<MemNode>();
			pNode->init(m_iMinNodeSize+i*m_iIntervalSize);
			pQueue->push_back(pNode);
		}
		m_Array.set(i, pQueue);
	}

	return true;
}

void       Allocator2::destroy_allocator()
{
	for (size_t i=0; i<m_Array.get_array_length(); i++)
	{
		_MY_QUEUE_* pQueue = m_Array[i];
		if (pQueue != NULL)
		{
			pQueue->destroy();
			Malloc::delete_object<_MY_QUEUE_>(pQueue);

			m_Array.set(i, NULL);
		}
	}
}

MemNode*   Allocator2::query_mem_node(size_t iSize)
{
	size_t iPos = iSize%m_iMinNodeSize;

	if (iPos >= m_Array.get_array_length())
	{
		MemNode* pNode = Malloc::new_object<MemNode>();
		pNode->init(iSize);

		return pNode;
	}

	_MY_QUEUE_* pQueue = m_Array[iPos];
	MemNode* pNode  = pQueue->pop_front();
	if (pNode->get_buff() == NULL)
	{
		pNode->init(m_iMinNodeSize+iPos*m_iIntervalSize);
	}
	else
	{
		pNode->clear();
	}

	return pNode;
}

void       Allocator2::insert_mem_node(MemNode* pNode)
{
	assert(pNode != NULL);

	size_t iPos = (pNode->size()-MemNode::MEM_ADD_SIZE)%m_iMinNodeSize;
	if (iPos >= m_Array.get_array_length())
	{
		Malloc::delete_object<MemNode>(pNode);
		return ;
	}

	_MY_QUEUE_* pQueue = m_Array[iPos];
	pQueue->push_back(pNode);
}

#endif
