#include <cocos2d.h>
#include "../include/TCPConnectorThread.h"
#include "../include/VariableSystem.h"
#include "../include/NetSystem.h"


TCPConnectorThread::TCPConnectorThread()
{
	m_ThreadState = _TYPED_THREAD_RUNING_;
}

TCPConnectorThread::~TCPConnectorThread()
{

}

int TCPConnectorThread::GetThreadState()
{
	int ret = _TYPED_THREAD_RUNING_;

	m_ThreadLock.lock();
	ret = m_ThreadState;
	m_ThreadLock.unlock();

	return ret;
}

void TCPConnectorThread::SetThreadState(int IThreadState)
{
	m_ThreadLock.lock();
	m_ThreadState = IThreadState;
	m_ThreadLock.unlock();
}

void TCPConnectorThread::post_close_message()
{

}
