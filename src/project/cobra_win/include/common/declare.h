#ifndef  _LC_COBRA_WIN_DECLARE_H
#define  _LC_COBRA_WIN_DECLARE_H


#include <stdio.h>

namespace  cobra_win
{


#define COBRA_PLATFORM_UNKNOWN        0
#define COBRA_PLATFORM_IOS            1
#define COBRA_PLATFORM_ANDROID        2
#define COBRA_PLATFORM_WIN32          3

#define COBRA_TARGET_PLATFORM         COBRA_PLATFORM_UNKNOWN

#if defined(ANDROID)
#undef  COBRA_TARGET_PLATFORM
#define COBRA_TARGET_PLATFORM         COBRA_PLATFORM_ANDROID
#elif defined(WIN32)
#undef  COBRA_TARGET_PLATFORM
#define COBRA_TARGET_PLATFORM         COBRA_PLATFORM_WIN32
#else
#undef  COBRA_TARGET_PLATFORM
#define COBRA_TARGET_PLATFORM         COBRA_PLATFORM_IOS
#endif

// 定义SOCKET
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
#define   SOCKET   int
#endif


// 得到一个field在结构体中的偏移量
#define   FIELD_POS(type, field) \
((unsigned long)&((type*)0)->field)


// 得到一个结构体中field所占用的字节数
#define   FIELD_SIZE(type, field) \
sizeof(((type*)0)->field)


// 防止溢出方法
#define   INC_SIZE(val)    (val=((val)+1)>(val))?(val)+1:(val))


// 返回数组元素的个数
#define   COBRA_ARRAY_SIZE(a)  (sizeof(a))/sizeof((a[0]))


// 把value转换成字符串
#define   TO_STRING(value)  #value


}


#endif
