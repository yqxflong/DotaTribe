#ifndef  _LC_COBRA_WIN_EVENT_H
#define  _LC_COBRA_WIN_EVENT_H


#include "Declare.h"
#include "NonCopyable.h"

#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
#include "Lock.h"
#include <pthread.h>
#endif

namespace  cobra_win
{


class  Event : public NonCopyable
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
private:
	ThreadLock     m_lock;
	pthread_cond_t m_event;
#endif

public:
	Event();
	~Event();

public:
	/*
		设置事件为有信号状态
	*/
	void    set_event_signal();
	/*
		等待事件信号
		timeout : 如果为正数的话，表示等待对应长度的事件
		如果为负数的话，永远等待
		返回值：
		true  : 表示有信号了返回
		false : 表示超时
	*/
	bool    wait_for_event_signal(int timeout);
};


}


#endif
