#include "../../include/common/Event.h"
#include "../../include/common/Declare.h"
#include <assert.h>
#include <time.h>
#include <memory.h>
#include <string.h>
using  namespace  cobra_win;


Event::Event()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	pthread_cond_init(&m_event, NULL);
#endif
}

Event::~Event()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	pthread_cond_destroy(&m_event);
#endif
}

void    Event::set_event_signal()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	pthread_cond_signal(&m_event);
#endif
}

bool    Event::wait_for_event_signal(int timeout)
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
	struct timespec temp;
	memset(&temp, 0, sizeof(timespec));
	temp.tv_sec  = time(NULL);
	temp.tv_nsec = timeout*1000;

	m_lock.lock();
	do 
	{
		int ret = pthread_cond_timedwait(&m_event, NULL, &temp);
		if (ret != 0)
			break;

		m_lock.unlock();
		return true;
	}
	while (false);
	m_lock.unlock();
#endif

	return false;
}
