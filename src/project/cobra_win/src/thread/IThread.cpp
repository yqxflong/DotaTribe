#include "../../include/thread/IThread.h"
#include "../../include/common/Declare.h"
#include <assert.h>
using  namespace  cobra_win;


#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
DWORD WINAPI IThread::thread_function( LPVOID lpParam )
{
	IThread* pThread = (IThread*)lpParam;

	pThread->run();
	return 0;
}

IThread::IThread() : m_hHandle(INVALID_HANDLE_VALUE)
{

}

IThread::~IThread()
{
	if (m_hHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}
}

HANDLE  IThread::get_thread_handle()
{
	return m_hHandle;
}

bool    IThread::create_thread()
{
	DWORD threadId = 0;
	m_hHandle = ::CreateThread(NULL, 0, thread_function, this, 0, (DWORD*)&threadId);
	if (m_hHandle == NULL)
		return false;

	return true;
}

void    IThread::close_thread_handle()
{
	if (m_hHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}
}

void    IThread::wait_thread_close()
{
	assert(m_hHandle != NULL);

	WaitForSingleObject(m_hHandle, INFINITE);
}
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
void* IThread::thread_function(void* pParam)
{
	IThread* pThread = (IThread*)pParam;

	return pThread->run();
}

IThread::IThread()
{

}

IThread::~IThread()
{

}

pthread_t  IThread::get_thread_handle()
{
	return m_hHandle;
}

bool    IThread::create_thread()
{
	int ret = pthread_create(&m_hHandle, NULL, thread_function, this);
	if (ret != 0)
		return false;

	return true;
}

void    IThread::close_thread_handle()
{
	pthread_exit(NULL);
}

void    IThread::wait_thread_close()
{
	assert(m_hHandle != NULL);

	pthread_join(m_hHandle, NULL);
}
#endif




