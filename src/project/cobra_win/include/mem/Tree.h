#ifndef  _LC_COBRA_WIN_TREE_H
#define  _LC_COBRA_WIN_TREE_H


#include "../common/NonCopyable.h"
#include "Malloc.h"

namespace  cobra_win
{


/*
	二叉树节点
*/
template <typename TYPE>
struct  TreeNode
{
	struct  TreeNode<TYPE>*  pParent;
	struct  TreeNode<TYPE>*  pLeftChild;
	struct  TreeNode<TYPE>*  pRightChild;
	TYPE*                    pData;  // 真实的数据元素 
	TreeNode() : pParent(NULL), pLeftChild(NULL), pRightChild(NULL), pData(NULL)
	{

	}
};

/*
	二叉树
	LOCK : 锁的类型，可选择空锁(单线程下使用)，或者线程锁(多线程下使用) 
	TYPE : 真实的元素类型
*/
template <typename LOCK, typename TYPE>
class  Tree : public NonCopyable
{
private:
	TreeNode<TYPE>*  m_pRoot;  // 根节点
	size_t           m_size;   // 元素个数
	LOCK             m_myLock; // 串行化锁

public:
	Tree() : m_pRoot(NULL), m_size(0)
	{

	}
	~Tree()
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
		得到当前二叉树中真实有效元素的个数(外部调用的时候，需要手动加锁解锁)
	*/
	inline   size_t  size() 
	{
		return m_size;
	}
	/*
		得到二叉树根节点
	*/
	inline   TreeNode<TYPE>*  root()
	{
		return m_pRoot;
	}
	/*
		销毁二叉树
	*/
	inline   void   destroy()
	{

	}
};


}


#endif
