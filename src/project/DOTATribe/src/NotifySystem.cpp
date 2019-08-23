#include "../include/NotifySystem.h"
#include "../include/LoggerSystem.h"


template<> NotifySystem* cobra_win::Singleton2<NotifySystem>::m_pMySelf = NULL;

NotifySystem::NotifySystem()
{

}

NotifySystem::~NotifySystem()
{

}

void NotifySystem::OnSystemEnterBackEventHandler()
{
	RegisterAllNotification();
}

void NotifySystem::OnSystemEnterFrontEventHandler()
{
	ClearAllNotification();
}

bool NotifySystem::Init()
{
	do 
	{
		ClearAllNotification();
		LOGGERSYSTEM->LogInfo("Init NotifySystem Success\n");
		return true;
	} 
	while (false);

	LOGGERSYSTEM->LogInfo("Init NotifySystem Failed\n");
	return false;
}

void NotifySystem::Tick()
{

}

void NotifySystem::Destroy()
{
	ClearAllNotification();
	RegisterAllNotification();
	LOGGERSYSTEM->LogInfo("Destroy NotifySystem Success\n");
}
