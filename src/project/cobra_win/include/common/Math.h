#ifndef  _LC_COBRA_WIN_MATH_H
#define  _LC_COBRA_WIN_MATH_H


#include <assert.h>
#include <stdio.h>

namespace  cobra_win
{


/*
	快速判断一个整数是不是二的整数次幂
*/
static   inline   bool     is_2n(size_t iNum)
{
	return (iNum&(iNum-1)) == 0;
}

/*
	快速调整到2的倍数
*/
static   inline   size_t   up_to_2n(size_t iNum)
{
	return (((iNum)+1) &~ 1);
}

/*
	快速调整到4的倍数
*/
static   inline   size_t   up_to_4n(size_t iNum)
{
	return (((iNum)+3) &~ 3);
}

/*
	快速调整到8的倍数
*/
static   inline   size_t   up_to_8n(size_t iNum)
{
	return (((iNum)+7) &~ 7);
}

/*
	快速调整到16的倍数
*/
static   inline   size_t   up_to_16n(size_t iNum)
{
	return (((iNum)+15) &~ 15);
}

/*
	快速调整到32的倍数
*/
static   inline   size_t   up_to_32n(size_t iNum)
{
	return (((iNum)+31) &~ 31);
}

/*
	快速调整到64的倍数
*/
static   inline   size_t   up_to_64n(size_t iNum)
{
	return (((iNum)+63) &~ 63);
}

/*
	快速调整到128的倍数
*/
static   inline   size_t   up_to_128n(size_t iNum)
{
	return (((iNum)+127) &~ 127);
}

/*
	快速调整到256的倍数
*/
static   inline   size_t   up_to_256n(size_t iNum)
{
	return (((iNum)+255) &~ 255);
}

/*
	快速调整到512的倍数
*/
static   inline   size_t   up_to_512n(size_t iNum)
{
	return (((iNum)+511) &~ 511);
}

/*
	快速调整到1024的倍数
*/
static   inline   size_t   up_to_1024n(size_t iNum)
{
	return (((iNum)+1023) &~ 1023);
}

/*
	快速调整到2048的倍数
*/
static   inline   size_t   up_to_2048n(size_t iNum)
{
	return (((iNum)+2047) &~ 2047);
}

/*
	快速调整到4096的倍数
*/
static   inline   size_t   up_to_4096n(size_t iNum)
{
	return (((iNum)+4095) &~ 4095);
}

/*
	快速调整到2^X的倍数
*/
static   inline   size_t   up_to_xn(size_t iNum)
{
	assert(is_2n(iNum));

	return (((iNum)+iNum-1) &~ (iNum-1));
}

/*
	快速换算到2的倍数的索引
*/
static   inline   size_t    query_2n_index(size_t iNum)
{
	return ((iNum+1)/2-1);
}

/*
	快速换算到4的倍数的索引
*/
static   inline   size_t    query_4n_index(size_t iNum)
{
	return ((iNum+3)/4-1);
}

/*
	快速换算到8的倍数的索引
*/
static   inline   size_t    query_8n_index(size_t iNum)
{
	return ((iNum+7)/8-1);
}

/*
	快速换算到16的倍数的索引
*/
static   inline   size_t    query_16n_index(size_t iNum)
{
	return ((iNum+15)/16-1);
}

/*
	快速换算到32的倍数的索引
*/
static   inline   size_t    query_32n_index(size_t iNum)
{
	return ((iNum+31)/32-1);
}

/*
	快速换算到64的倍数的索引
*/
static   inline   size_t    query_64n_index(size_t iNum)
{
	return ((iNum+63)/64-1);
}

/*
	快速换算到128的倍数的索引
*/
static   inline   size_t    query_128n_index(size_t iNum)
{
	return ((iNum+127)/128-1);
}

/*
	快速换算到256的倍数的索引
*/
static   inline   size_t    query_256n_index(size_t iNum)
{
	return ((iNum+255)/256-1);
}

/*
	快速换算到512的倍数的索引
*/
static   inline   size_t    query_512n_index(size_t iNum)
{
	return ((iNum+511)/512-1);
}

/*
	快速换算到1024的倍数的索引
*/
static   inline   size_t    query_1024n_index(size_t iNum)
{
	return ((iNum+1023)/1024-1);
}

/*
	快速换算到2048的倍数的索引
*/
static   inline   size_t    query_2048n_index(size_t iNum)
{
	return ((iNum+2047)/2048-1);
}

/*
	快速换算到4096的倍数的索引
*/
static   inline   size_t    query_4096n_index(size_t iNum)
{
	return ((iNum+4095)/4096-1);
}

/*
	快速换算到2^X的倍数的索引
*/
static   inline   size_t    query_xn_index(size_t x, size_t iNum)
{
	assert(is_2n(x));

	return ((iNum+x-1)/x-1);
}


}


#endif
