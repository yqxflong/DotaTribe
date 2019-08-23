#ifndef  _LC_COBRA_WIN_MBUF_H
#define  _LC_COBRA_WIN_MBUF_H


#include "../common/NonCopyable.h"
#include "Malloc.h"
#include <string.h>

namespace  cobra_win
{


class  mbuf : public NonCopyable
{
public:
	class  mbuf*   pNext;          //  指向下一个指针
	class  mbuf*   pRef;           //  指向自己
	char*          pReader;        //  读指针
	char*          pWriter;        //  写指针
	size_t         iUsed;          //  当前含有的有效数据数量
	size_t         iUnused;        //  未被使用的字节数目
	size_t         iTotal;         //  申请的字符串总长度
	char*          pBuff;          //  数据缓冲区

public:
	mbuf(size_t iSize)
	{ // 申请指定大小的空间
		pBuff  = Malloc::new_buff(iSize);
		iTotal = iSize;
	}
	~mbuf()
	{ // 回收申请的空间
		Malloc::delete_buff(pBuff);
	}

public:
	/*
		初始化mbuf
	*/
	inline  void  init_mbuf()
	{
		pNext    =  NULL;
		pRef     =  this;
		pReader  =  pBuff;
		pWriter  =  pBuff;
		iUsed    =  0;
		iUnused  =  iTotal;

		memset(pBuff, 0, iTotal);
	}
};


}



#endif
