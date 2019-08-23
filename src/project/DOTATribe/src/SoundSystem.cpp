#include <cocos2d.h>
#include "../include/SoundSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/CommonButtonDataManager.h"
#include <SimpleAudioEngine.h>
#include <include/Common/String.h>
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/SoundDataManager.h"
#include "../include/VariableSystem.h"

using namespace  cobra_win;
using namespace std;


template<> SoundSystem* cobra_win::Singleton2<SoundSystem>::m_pMySelf = NULL;

SoundSystem::SoundSystem()
{
	m_MyTimer = 0;
	m_BackSoundName  = "";
	m_isBackgroundSound = false;		//背景音乐是否关闭
	m_isEffectSound = false;			//音效是否关闭
	m_preLoadSoundEffectList.clear();	
	_registerEvent();
}

SoundSystem::~SoundSystem()
{
	_unRegisterEvent();
}

void SoundSystem::MuteBackgroundMusic(bool bMute)
{
	if (bMute)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	m_isBackgroundSound = bMute;
	VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SOUND", "BackgroundMusicMute", bMute);
}

void SoundSystem::MuteEffectSound(bool bMute)
{
	if (bMute)
	{
		PauseAllEffectSound();
	}
	else
	{
		ResumeAllEffectSound();
	}
	m_isEffectSound = bMute;
	VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SOUND", "EffectSoundMute", bMute);
}

bool SoundSystem::IsBackgroundMusicMute()
{
	return m_isBackgroundSound;
}

bool SoundSystem::IsEffectSoundMute()
{
	return m_isEffectSound;
}

void SoundSystem::PlayEffect(int effectID, std::string soundName, bool bLoop, float fPitch)
{
	if (soundName.length() == 0||effectID==-1)
		return;

	if (!IsCanPlay(effectID))
		return ;

	int soundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundName.c_str(), bLoop, fPitch);
	InsertEffectInfo(effectID, soundName, soundId, bLoop);
}

	/*
		停止所有音效
	*/
void SoundSystem::StopAllEffect(){
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*temp).mSoundId);
	}
	m_EffectList.clear();
}
	/*
		停止音效
	*/
void SoundSystem::StopEffect(int effectID)
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if ((*temp).mEffectType == effectID)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*temp).mSoundId);
			m_EffectList.erase(temp);
		}
	}
}

void SoundSystem::PlayBackgroundMusic(std::string soundName,int soundVolume/* =10 */)
{
	if (m_BackSoundName.compare(soundName) == 0)
		return;

	m_BackSoundName = soundName;
	if(soundVolume!=-1)
    SetBackgroundMusicVolume(((float)soundVolume)/10.0f);
	else
    SetBackgroundMusicVolume(1.0f);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_BackSoundName.c_str(), 1);
	if (IsBackgroundMusicMute())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void SoundSystem::StopBackgroundMusic()
{
	m_BackSoundName  = "";
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

/*
预加载音效队列
*/
void   SoundSystem::PreLoadSoundEffectQueue(std::set<int> & soundEffectVec)
{ 
	UnLoadSoundEffectQueue();
	if(!soundEffectVec.empty()&&!IsEffectSoundMute())
	{ 
		std::set<int>::iterator sound_iter=soundEffectVec.begin();
		while(sound_iter!=soundEffectVec.end())
		{ 
			SoundData * pSoundData=SoundDataManager::get_instance2()->GetSoundData(*sound_iter);
			if(pSoundData!=NULL)
			{    
				m_preLoadSoundEffectList.push_back(pSoundData->soundName);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(pSoundData->soundName);
			}
			++sound_iter;
		}
	}
}

/*
卸载预加载音效队列
*/
void  SoundSystem::UnLoadSoundEffectQueue()
{   
	if(!m_preLoadSoundEffectList.empty())
	{
		std::list<std::string>::iterator sound_iter=m_preLoadSoundEffectList.begin();
		while(sound_iter!=m_preLoadSoundEffectList.end())
		{ 
			CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect((*sound_iter).c_str());
			++sound_iter;
		}
		m_preLoadSoundEffectList.clear();
	}
}
 

void SoundSystem::SetBackgroundMusicVolume(float volume)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

float SoundSystem::GetBackgroundMusicVolume()
{
	return CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void SoundSystem::_registerEvent(){
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOUND_PLAY_,On_SoundEvent_Handle_Play);
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOUND_STOP_,On_SoundEvent_Handle_Stop);
}
void SoundSystem::_unRegisterEvent(){
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOUND_PLAY_,On_SoundEvent_Handle_Play);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOUND_STOP_,On_SoundEvent_Handle_Stop);
}

bool   SoundSystem::Init()
{
	m_MyTimer = 0;
	CocosDenshion::SimpleAudioEngine::sharedEngine();

	//初始设置当前背景音乐是否关闭
	bool bMute;
	if (!VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SOUND", "BackgroundMusicMute", bMute))
	{
		m_isBackgroundSound = false;
	}
	else
	{
		m_isBackgroundSound = bMute;
	}
	//初始设置当前音效是否关闭
	if (!VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SOUND", "EffectSoundMute", bMute))
	{
		m_isEffectSound = false;
	}
	else
	{
		m_isEffectSound = bMute;
	}

	// 继续播放背景音效
	if (m_BackSoundName.length() != 0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_BackSoundName.c_str(), 1);
		if (IsBackgroundMusicMute())
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

	// 播放循环的特效音效
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if ((*temp).mLoop)
		{
			(*temp).mSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect((*temp).mSoundName);
			if (IsEffectSoundMute())
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect((*temp).mSoundId);
		}
	}
	LOGGERSYSTEM->LogInfo("Init SoundSystem Success\n");
	return true;
}

void   SoundSystem::Tick()
{
	m_MyTimer++;

	float effectReleaseInterval = 5.0f;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "EffectReleaseInterval", effectReleaseInterval);
	int interval = (int)(effectReleaseInterval*DOTATribeApp::get_instance2()->GetFPS());

	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if (!(*temp).mLoop)
		{
			if (m_MyTimer-(*temp).mStartTime>=interval)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*temp).mSoundId);
				m_EffectList.erase(temp);
			}
		}
	}
}

void   SoundSystem::Destroy()
{
	// 删除所有的非循环特效音效
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if (!(*temp).mLoop)
		{
			m_EffectList.erase(temp);
		}
	}

	// 销毁音效系统
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::end();

	LOGGERSYSTEM->LogInfo("Destroy SoundSystem Success\n");
}

bool   SoundSystem::IsCanPlay(int effectID)
{
	if (IsEffectSoundMute())
		return false;

	int len = m_EffectList.size();
	int maxSound = 20;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "MaxEffectSound", maxSound);
	if (len > maxSound)
	{
		for (int i=0; i<len-maxSound; i++)
		{
			std::list<_EFFECT_INFO_>::iterator iter = m_EffectList.begin();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*iter).mSoundId);
			m_EffectList.erase(iter);
		}
	}

	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if ((*iter).mLoop)
		{
			if ((*iter).mEffectType == effectID)
			{
				return false;
			}
		}
	}

	return true;
}

void   SoundSystem::InsertEffectInfo(int effectID, std::string soundName, int soundId, bool bLoop)
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if ((*iter).mSoundId == soundId)
		{
			(*iter).mStartTime = m_MyTimer;
			return;
		}
	}

	_EFFECT_INFO_ info;
	info.mEffectType= effectID;
	info.mSoundId   = soundId;
	info.mStartTime = m_MyTimer;
	info.mLoop      = bLoop;
	String::copy(info.mSoundName, (char*)soundName.c_str(), sizeof(info.mSoundName));
	m_EffectList.push_back(info);
}

void SoundSystem::PauseAllEffectSound()
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if (!(*temp).mLoop)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*temp).mSoundId);
			m_EffectList.erase(temp);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect((*temp).mSoundId);
		}
	}
}

void SoundSystem::ResumeAllEffectSound()
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if ((*temp).mLoop)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeEffect((*temp).mSoundId);
		}
	}
}

void SoundSystem::OnPauseEventHandler()
{
	if (m_BackSoundName.length() != 0)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void SoundSystem::OnResumeEventHandler()
{
	if (!IsBackgroundMusicMute())
	{
		if (m_BackSoundName.length() != 0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
	}
}

void SoundSystem::OnEnterBackgroundEventHandler()
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect((*temp).mSoundId);
		if (!(*temp).mLoop)
			m_EffectList.erase(temp);
	}

	if (!IsBackgroundMusicMute())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void SoundSystem::OnEnterForegroundEventHandler()
{
	std::list<_EFFECT_INFO_>::iterator iter   = m_EffectList.begin();
	std::list<_EFFECT_INFO_>::iterator iter_e = m_EffectList.end();
	for ( ; iter!=iter_e; )
	{
		std::list<_EFFECT_INFO_>::iterator temp = iter;
		++iter;

		if ((*temp).mLoop)
		{
			(*temp).mSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect((*temp).mSoundName);
			if (IsEffectSoundMute())
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect((*temp).mSoundId);
			}
		}
	}

	if (!IsBackgroundMusicMute())
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
	/*
		处理声音播放事件
		0:id
	*/
void SoundSystem::On_SoundEvent_Handle_Play(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (paramList.size()<1)return;
	std::list<std::string>::iterator it=paramList.begin();
	int id_=atoi((*it++).c_str());
	if(id_ < 0)
		return;

	SoundData* dd=SoundDataManager::get_instance2()->GetSoundData(id_);
	assert(dd!=NULL);
	if(dd->soundType==kSOUND_PLAY_TYPE_BACKGROUND){
		SOUNDSYSTEM->PlayBackgroundMusic(dd->soundName,dd->soundVolume);
	}else{
		float playSpeed=1.0f;
		bool isInAthletics=false;
		VariableSystem::get_instance2()->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"DotaAthletics","isInAthletics",isInAthletics);
		if(isInAthletics)
		{   
			VariableSystem::get_instance2()->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"DotaAthletics","AthleticsSpeed",playSpeed);
		} 
		SOUNDSYSTEM->PlayEffect(dd->soundID,dd->soundName,dd->soundIsCycle,playSpeed);
	}
}

	/*
		处理声音停止事件
		0:StopType
		1:EffectID		(just used by Effect)
	*/
void SoundSystem::On_SoundEvent_Handle_Stop(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (paramList.size()<1)return;
	std::list<std::string>::iterator it=paramList.begin();
	int param1_=atoi((*it++).c_str());
	if(kSOUND_STOP_TYPE_BACKGROUND==param1_){
		SOUNDSYSTEM->StopBackgroundMusic();
	}else if(kSOUND_STOP_TYPE_EFFECT==param1_){
		if (paramList.size()<2)return;
		int param2_=atoi((*it++).c_str());
		SOUNDSYSTEM->StopEffect(param2_);
	}else if(kSOUND_STOP_TYPE_EFFECT_ALL==param1_){
		SOUNDSYSTEM->StopAllEffect();
	}
	else if(kSOUND_STOP_TYPE_EFFECT_AND_BACKGROUND==param1_){
		SOUNDSYSTEM->StopBackgroundMusic();
		SOUNDSYSTEM->StopAllEffect();
	}
}

/*~~~~
void SoundSystem::OnMenuItemCallbackEventHandler(std::string eventName, std::string menuItemName)
{
	if (SOUNDSYSTEM == NULL)
		return;

	CommonButtonItemData* pButtonItem = CommonButtonDataManager::get_instance2()->GetCommonButtonByName(menuItemName);
	if (pButtonItem==NULL || pButtonItem->mSoundName[0]=='\0')
		return;

	// 播放音效
	SOUNDSYSTEM->PlayEffect(SoundSystem::_TYPED_EFFECTSOUND_COMMONBUTTON_, pButtonItem->mSoundName, false);
}
*/
