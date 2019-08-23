//Name：GuideSystem
//Function：新手引导系统
//Written By：尹强

#include "../include/GuideSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/GuideDataManager.h"
#include "../include/SoundSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/HomeProcedure.h"
#include "../include/GuidePacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/NFControlsManager.h"
#include "../include/DotaGameConfig.h"
#include "../include/SysLangDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

template<> GuideSystem* cobra_win::Singleton2<GuideSystem>::m_pMySelf = NULL;

GuideSystem::GuideSystem()
{
	_resetVariable();
}


/*
	检查是否有新手引导
*/
bool GuideSystem::IsNeedGuide()
{
	return m_bIsNeedGuide;
}
/*
	获得当前模块ID
*/
int GuideSystem::GetModuleID()
{
	return m_GuideModuleID;
}
/*
	获得当前步骤ID
*/
int GuideSystem::GetStepID()
{
	return m_GuideStepID;
}

	/*
		开启一个新功能的引导
	*/
void GuideSystem::StartGuide4NewFunc(int moduleID){
	m_bIsNeedGuide=true;
	m_GuideModuleID=moduleID;
	GuideItemData* pStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(m_GuideModuleID, 0);
	if (pStep == NULL){//没有该模块
		Finish();
		return;
	}
	m_isRunning=true;
	m_GuideStepID= 0;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_GUIDEWINDOW_);
}

/*
	开始新手引导
*/
void GuideSystem::StartGuide(){
	if (RoleInfoDataHandler::get_instance2()->CheckNewFuncOPenGuide(_TYPED_GUIDE_1_))
	{
		StartGuide4NewFunc(_TYPED_GUIDE_1_);
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(_TYPED_GUIDE_1_);
	}
}

	/*
		下一个模块
	*/
void GuideSystem::NextModule(){
	if (m_GuideModuleID==_TYPED_GUIDE_1_)
	{
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(_TYPED_GUIDE_1_);
	}else if(m_GuideModuleID==_TYPED_GUIDE_2_){
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(_TYPED_GUIDE_2_);
	}
	m_GuideModuleID++;
	m_GuideStepID= 0;
	Finish();
}

void GuideSystem::NextBegin(){
	m_isGuideTriggered = true;
}
void GuideSystem::NextDone(){
	if (m_isGuideTriggered == false) return;
	Next();
	m_isGuideTriggered = false;
}
/*
	下一步，会检测下一个模块，及结束
*/
void GuideSystem::Next()
{
	if (!IsNeedGuide())return;
	if (m_GuideModuleID == _TYPED_GUIDE_NONE_)return;

	//告诉服务器做完哪一步引导
	sendToServerFinishOneStep(m_GuideModuleID,m_GuideStepID);
	//检查完成的这步需要做什么？
	_checkSpecialStep();
	//准备下一步得数据
	m_GuideStepID++;
	GuideItemData* pStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(m_GuideModuleID, m_GuideStepID);
	if (pStep == NULL)
	{
		NextModule();
		return;
	}

	//是否播放音效
	if (pStep->mSoundName[0] != '\0')
		SOUNDSYSTEM->PlayEffect(SoundSystem::_TYPED_EFFECTSOUND_OTHER_, pStep->mSoundName, false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_NEXT_GUIDESTEP_);
}

	/*
		暂停引导
		停留在原步骤上，等待恢复，恢复时会继续增加步骤ID
	*/
void GuideSystem::PauseGuide(){
	if (!IsNeedGuide())return;
	m_bIsPaused=true;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_GUIDEWINDOW_);
}

	/*
		恢复引导
	*/
void GuideSystem::RestoreGuide(){
	if (!IsNeedGuide())return;
	m_bIsPaused=false;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_GUIDEWINDOW_);
	Next();
}

	/*
		停止引导
	*/
void GuideSystem::StopGuide(){
	if (!IsNeedGuide())return;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_GUIDEWINDOW_);
	_resetVariable();
}

	/*
		告诉服务器完成了哪一步引导
	*/
void GuideSystem::sendToServerFinishOneStep(int moduleID,int stepID,unsigned char isSkip){
	CSGuideStepPacket packet((short)moduleID,(short)stepID,isSkip);
	packet.Send();
}

/*
	告诉服务器跳过新手引导
*/
void GuideSystem::ToServerSkipGuide(){
	sendToServerFinishOneStep(m_GuideModuleID,m_GuideStepID,1);
}

/*
	引导结束
*/
void GuideSystem::Finish()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_GUIDEWINDOW_);
	_resetVariable();
}

bool  GuideSystem::Init()
{
	_resetVariable();
	LOGGERSYSTEM->LogInfo("Init GuideSystem Success\n");
	return true;
}

void  GuideSystem::Tick()
{
	;
}

void  GuideSystem::Destroy()
{
	LOGGERSYSTEM->LogInfo("Destroy GuideSystem Success\n");
}

 	/*
		检查特殊步骤
	*/
void GuideSystem::_checkSpecialStep(){
	if (m_GuideModuleID>=_TYPED_NEWFUNC_1_HEROBAR)//开启新功能
	{
		if(m_GuideStepID==0){
			LevelUpDataHandler::get_instance2()->LevelUpDataList.clear();	//清空升级容器
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_);//如果有升级窗口，干掉！~
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MAINTASKWINDOW_);//如果有主线任务窗口，干掉！
			//
			//通知homewindow展示new字样
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_NEWFUNCOPEN_HOMESHOWNEW_,_to_event_param_(m_GuideModuleID));
		}
	}else if(m_GuideModuleID==_TYPED_GUIDE_1_){
		if(m_GuideStepID==2){
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SELECTSONMISSIONWINDOW_HIDE_ARROWHINT);
		}else if (m_GuideStepID==6){
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SELECTSONMISSIONWINDOW_SHOW_ARROWHINT);
		}
	}
}

 	/*
		reset Var
	*/
void GuideSystem::_resetVariable(){
	m_isRunning=false;
	m_bIsPaused=false;
	m_bIsNeedGuide=false;
	m_GuideModuleID = _TYPED_GUIDE_NONE_;
	m_GuideStepID= -1;
	m_isGuideTriggered=false;
}


void GuideSystem::CheckAndStartGuide(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(_TYPED_GUIDE_1_)){
		GUIDESYSTEM->StartGuide();
	}
}
