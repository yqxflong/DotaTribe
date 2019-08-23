#include "../include/IProcedure.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/config_SoundSystem.h"


IProcedure::IProcedure()
{
	m_Type = _TYPED_UNKOWN_PROCEDURE_;
}

IProcedure::~IProcedure()
{

}

void IProcedure::PlayBGSound()
{
	LoadingAnimationData* pData= LoadingAnimationManager::get_instance2()->GeLoadingAnimationDataByID(GetType());
	if (pData->mBackgroundSuondID == -1)
		return;
	char _soundID[64]="";
	sprintf(_soundID,"%d",pData->mBackgroundSuondID);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
}

void IProcedure::StopAllSound()
{
	char _typeID[64]="";
	sprintf(_typeID,"%d",kSOUND_STOP_TYPE_EFFECT_AND_BACKGROUND);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_,_typeID);
}

int IProcedure::GetType()
{
	return m_Type;
}
