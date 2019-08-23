#ifndef  _LC_COBRA_WIN_STRING_H
#define  _LC_COBRA_WIN_STRING_H


#include <stdio.h>

namespace  cobra_win
{


class  String
{
public:
	/*
		字符串拷贝
	*/
	static   int     copy(char* pDes, char* pSrc, size_t iLen);
	/*
		字符查找
	*/
	static   int     find(char* pBuffer, char finder);
	/*
		字符串查找	
	*/
	static   int     find(char* pBuffer, char* pFinderStr);
	/*
		字符串比较(bCare代表是否对大小写敏感)
	*/
	static   bool    compare(char* pBuffer1, char* pBuffer2, bool bCare);
};


}


#endif
