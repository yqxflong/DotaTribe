#ifndef  _LC_COBRA_WIN_ITHREAD_H
#define  _LC_COBRA_WIN_ITHREAD_H


#include "../common/Declare.h"
#include "../common/NonCopyable.h"
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <Windows.h>
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
#include <pthread.h>
#endif

namespace  cobra_win
{


class  IThread : public NonCopyable
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
protected:
	HANDLE   m_hHandle;        // 线程句柄
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
protected:
	pthread_t   m_hHandle;     // 线程句柄
#endif

public:
	IThread();
	virtual  ~IThread();

public:
	/*
		得到线程句柄
	*/
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	HANDLE  get_thread_handle();
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	pthread_t  get_thread_handle();
#endif

public:
	/*
		创建线程
	*/
	bool    create_thread();
	/*
		等待线程结束
	*/
	void    wait_thread_close();
	/*
		关闭线程句柄
	*/
	void    close_thread_handle();

public:
	/*
		线程处理函数
	*/
	virtual   void*  run()                 =  0;
	/*
		发起关闭消息
	*/
	virtual   void   post_close_message()  =  0;

private:
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	static    DWORD    WINAPI    thread_function(LPVOID lpParam);
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	static    void*   thread_function(void* pParam);
#endif
};


}

#endif
