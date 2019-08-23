#include <cocos2d.h>
#include "../include/ProfSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/TimeSystem.h"


template<> ProfSystem* cobra_win::Singleton2<ProfSystem>::m_pMySelf = NULL;

ProfSystem::ProfSystem()
{
	
}

ProfSystem::~ProfSystem()
{

}

void ProfSystem::Start(const char* pChunkName)
{
	_PROF_INFO_ info;
	info.mChunkName = pChunkName;
	info.mStartTime = TimeSystem::GetCurrentMicroSecond();
	m_ProfList.push(info);
}

void ProfSystem::End()
{
	if (m_ProfList.empty())
	return ;

	_PROF_INFO_& info = m_ProfList.top();
	m_ProfList.pop();

	long long diffTime = TimeSystem::GetCurrentMicroSecond()-info.mStartTime;
	float second = (float(diffTime)/1000000.0f);
	LOGGERSYSTEM->LogProf("chunk name=【%s】, cost time=【%f】\n", info.mChunkName, second);
}

bool ProfSystem::Init()
{
	do 
	{
		LOGGERSYSTEM->LogInfo("Init ProfSystem Success\n");
		return true;
	} 
	while(false);

	LOGGERSYSTEM->LogFatal("Init ProfSystem Failed\n");
	return false;
}

void ProfSystem::Tick()
{

}

void ProfSystem::Destroy()
{
	LOGGERSYSTEM->LogInfo("Destroy ProfSystem Success\n");
}
