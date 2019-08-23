#ifndef  _DOTATRIBE_WINMAIN_H_
#define  _DOTATRIBE_WINMAIN_H_


#include <cocos2d.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <CCStdC.h>

#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>

#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include <UIKit/UIKit.h>

#endif


#endif
