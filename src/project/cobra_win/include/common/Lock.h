#ifndef  _LC_COBRA_WIN_LOCK_H
#define  _LC_COBRA_WIN_LOCK_H


#include "Declare.h"
#include "NonCopyable.h"

#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
#include <pthread.h>
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <WinSock2.h>
#endif

namespace  cobra_win
{


class  EmptyLock : public NonCopyable
{
public:
	/*
		加锁
	*/
	inline   void   lock()
	{

	}
	/*
		解锁
	*/
	inline   void   unlock()
	{

	}
};


#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
class  ThreadLock : public NonCopyable
{
private:
	CRITICAL_SECTION  m_CS;

public:
	ThreadLock()
	{
		InitializeCriticalSectionAndSpinCount(&m_CS, 4000);
	}
	~ThreadLock()
	{
		::DeleteCriticalSection(&m_CS);
	}

public:
	/*
		加锁
	*/
	inline   void   lock()
	{
		::EnterCriticalSection(&m_CS);
	}
	/*
		解锁
	*/
	inline   void   unlock()
	{
		::LeaveCriticalSection(&m_CS);
	}
};
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
class  ThreadLock : public NonCopyable
{
private:
    pthread_mutex_t m_lock;
    
public:
	ThreadLock()
	{
		pthread_mutex_init(&m_lock, NULL);
	}
	~ThreadLock()
	{
		pthread_mutex_destroy(&m_lock);
	}

public:
	/*
		加锁
	*/
	inline   void   lock()
	{
		pthread_mutex_lock(&m_lock);
	}
	/*
		解锁
	*/
	inline   void   unlock()
	{
		pthread_mutex_unlock(&m_lock);
	}
};
#endif


}


#endif
