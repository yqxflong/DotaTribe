#include <cocos2d.h>
#include "../include/NotifySystem.h"
#include "../include/LoggerSystem.h"
#include "../include/LocalNotificationDataManager.h"



#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


void NotifySystem::ClearAllNotification()
{

}

void NotifySystem::RegisterAllNotification()
{
	if (LocalNotificationDataManager::get_instance2() == NULL)
		return;

	unsigned int number = LocalNotificationDataManager::get_instance2()->GetLocalNotifyNumber();
	for (unsigned int i=0; i<number; i++)
	{
		LocalNotificationItemData* pNotifyInfo = LocalNotificationDataManager::get_instance2()->GetLocalNotifyByPos(i);
		assert(pNotifyInfo != NULL);

		if (pNotifyInfo->mNotifyType == _TYPED_NOTIFY_DAILY_)
		{
			;
		}
		else if (pNotifyInfo->mNotifyType == _TYPED_NOTIFY_TIME_)
		{
			;
		}
	}
}


#endif
