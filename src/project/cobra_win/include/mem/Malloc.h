#ifndef  _LC_COBRA_WIN_MALLOC_H
#define  _LC_COBRA_WIN_MALLOC_H


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

namespace  cobra_win
{


#define  MALLOC_BUFFER_FAILED(p) { \
	if (p == NULL) \
		{ \
			assert(0); \
			exit(0); \
		} \
	} 

class  Malloc
{
public:
	/*
		分配空间malloc版本
	*/
	static  char*  malloc_buff(size_t size)
	{
		char* p = (char*)malloc(size);
		MALLOC_BUFFER_FAILED(p);
		return p;
	}
	/*
		释放空间free版本
	*/
	static  void   free_buff(char* pBuff)
	{
		free(pBuff);
	}
	/*
		分配空间new版本
	*/
	static  char*  new_buff(size_t size)
	{
		char* p = new char[size];
		MALLOC_BUFFER_FAILED(p);
		return p;
	}
	/*
		释放空间delete版本
	*/
	static  void   delete_buff(char* pBuff)
	{
		delete []pBuff;
	}
	/*
		创建一个对象
	*/
	template <typename TYPE>
	static  TYPE*  new_object()
	{
		TYPE* p = new TYPE;
		MALLOC_BUFFER_FAILED(p);
		return p;
	}
	/*
		创建一个对象的数组指针
	*/
	template <typename TYPE>
	static  TYPE*  new_object_array(size_t num)
	{
		TYPE* p = new TYPE[num];
		MALLOC_BUFFER_FAILED(p);
		return p;
	}
	/*
		删除一个给定的对象
	*/
	template <typename TYPE>
	static  void   delete_object(TYPE* pObj)
	{
		delete pObj;
	}
	/*
		删除一个给定对象的数组
	*/
	template <typename TYPE>
	static  void   delete_object_array(TYPE* pObjArray)
	{
		delete []pObjArray;
	}
	/*
		从给定的地址上，创建一个给定的对象指针
	*/
	template <typename TYPE>
	static  TYPE*  new_object(char* pBuff)
	{
		return new(pBuff)TYPE;
	}
};


}


#endif
