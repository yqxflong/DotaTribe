#ifndef  _LC_COBRA_WIN_HASH_H
#define  _LC_COBRA_WIN_HASH_H


#include "../common/NonCopyable.h"
#include "Malloc.h"
#include "Queue.h"

namespace  cobra_win
{


/*
	哈西表元素节点
	TYPE : 哈西表存贮的数据类型
*/
template <typename TYPE>
struct  HashNode
{
	struct  HashNode<TYPE>*  pNext;  // 指向下一个元素节点的指针
	struct  HashNode<TYPE>*  pPre;   // 指向前一个元素节点的指针
	size_t                   key;    // 主键值
	TYPE*                    pData;  // 对应的数据指针 
	HashNode() : pNext(NULL), pPre(NULL), key(0)
	{	
		pData = Malloc::new_object<TYPE>();
	}		
	~HashNode()
	{
		Malloc::delete_object<TYPE>(pData);
	}
};

/*
	链表式哈西表 
	LOCK : 串行化锁，可选择空锁(单线程下使用)，线程锁(多线程环境下使用)
	TYPE : 真实的数据类型
	NUM  : 哈西表缓冲数组的大小
*/
template <typename LOCK, typename TYPE, size_t NUM>
class  Hash : public NonCopyable
{
private:
	HashNode<TYPE>*                 m_Array[NUM];  // 哈西表双向缓冲链表数组
	size_t                          m_ArraySize;   // 数组的最大长度
	size_t                          m_size;        // 真实的元素个数
	Queue< LOCK, HashNode<TYPE> >   m_myQueue;     // 后备的哈西节点对列缓冲
	LOCK                            m_myLock;      // 串行化锁 

public:
	Hash() : m_ArraySize(NUM), m_size(0)
	{
		for (size_t i=0; i<NUM; i++)
		{
			m_Array[i] = NULL;
		}
	}
	~Hash()
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
		得到哈西表中有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t  size()
	{
		return  m_size;
	}
	/*
		得到链表式哈西表数组缓冲区的起始位置,主要留给使用者遍历==(外部调用的时候，需要手动加锁解锁)
	*/
	inline   HashNode<TYPE>**  get_hash_array_begin()
	{
		return m_Array;
	}
	/*
		得到链表是哈西表数组缓冲区的大小(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t   get_hash_array_size()
	{
		return m_ArraySize;
	}
	/*
		设置哈西表中有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void    set_size(size_t size)
	{
		m_size = size;
	}
	/*
		设置后备缓冲对列的大小(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void    set_hash_queue_size(size_t size)
	{
		for (size_t i=0; i<size; i++)
		{
			HashNode<TYPE>* pNode = Malloc::new_object< HashNode<TYPE> >();
			m_myQueue.push_back(pNode);
		}
	}
	/*
		从链表式哈西表的后备对列中取出一个哈西元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   HashNode<TYPE>*    get_hash_node_from_hashqueue()
	{
		return m_myQueue.pop_front();
	}
	/*
		把一个哈西元素节点插入到后备缓冲节点对列中(外部调用的时候，需要手动加锁解锁)
	*/
	inline   void     insert_hashnode_to_hashqueue(HashNode<TYPE>* pNode)
	{
		m_myQueue.push_back(pNode);
	}
	/*
		把健值为key的元素节点插入到哈西表中(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline    void    insert_hash_node(size_t key, HashNode<TYPE>* pNode)
	{
		pNode->key   = key;
		size_t index = key%m_ArraySize;

		lock();

		HashNode<TYPE>* _pTemp = m_Array[index];
		pNode->pNext          = _pTemp;
		if (_pTemp != NULL)
		{
			_pTemp->pPre = pNode;
		}
		m_Array[index] = pNode;
		m_size++;

		unlock();
	}
	/*
		从哈西表中删除健值为key的节点(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void    delete_hash_node(size_t key)
	{
		HashNode<TYPE>* pNode = NULL;
		size_t          index = key%m_ArraySize;

		lock();

		pNode = m_Array[index];
		while (pNode && pNode->key!=key)
		{
			pNode = pNode->pNext;
		}
		if (pNode == NULL)
		{// 没有找到这个元素，直接退出 
			unlock();
			return ;
		}
		else
		{
			if (pNode->pPre == NULL)
			{
				m_Array[index] = pNode->pNext;
			}
			else
			{
				pNode->pPre->pNext = pNode->pNext;
			}

			if (pNode->pNext != NULL)
			{
				pNode->pNext->pPre = pNode->pPre;
			}

			m_size--;
		}

		unlock();

		pNode->key   = 0;
		pNode->pNext = NULL;
		pNode->pPre  = NULL;

		m_myQueue.push_back(pNode);
	}
	/*
		得到key值在哈西表中对应的元素节点(外部调用的时候，需要手动加锁解锁)
	*/
	inline   HashNode<TYPE>*   get_hash_node_by_key(size_t key)
	{
		size_t index          = key%m_ArraySize;
		HashNode<TYPE>* pNode = NULL;

		if (m_Array[index] == NULL)
		{// 没有这个元素
			return NULL;
		}

		pNode = m_Array[index];
		while (pNode && pNode->key!=key)
		{
			pNode = pNode->pNext;
		}
		if (pNode == NULL)
		{ // 没有找到这个元素
			return NULL;
		}

		return pNode;
	}
	/*	
		销毁链表式哈西表(内部进行加锁解锁，外部且不可进行加锁解锁)
	*/
	inline   void    destroy()
	{
		lock();

		for (size_t i=0; i<m_ArraySize; i++)
		{
			while (m_Array[i] != NULL)
			{
				m_myQueue.push_back(m_Array[i]);
				m_Array[i] = m_Array[i]->pNext;
				m_size--;
			}
		}

		unlock();

		m_myQueue.destroy();
	}
};


}


#endif
