#include "../include/ArenaProcedure.h"
#include "../include/DOTATribeApp.h"
#include "../include/ProfSystem.h"
#include "../include/SoundSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/LoginProcedure.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/AthleticsSceneManager.h"
#include "../include/SelectMissionProcedure.h"
#include  "../include/LoginProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/ArenaInfoDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/NFControlsManager.h"


#include <vector>
#include <cocos2d.h>
#include <include/common/String.h>




ArenaProcedure::ArenaProcedure()
{
	m_Type    = _TYPED_ARENA_PROCEDURE_;
	m_LogicTickCounter=0;
}

ArenaProcedure::~ArenaProcedure()
{

}


int   ArenaProcedure::GetSubType()
{	
	return  m_SubType;
}
 
bool  ArenaProcedure::Init()
{ 
	CCLOG("ArenaProcedure  Init ");
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);
    NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_SHOW_ARENAWINDOW_);
	PlayBGSound();

	//注册断网通知
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
	 return  true;
} 

void  ArenaProcedure::Tick()
{
	m_LogicTickCounter++; 
}

void   ArenaProcedure::Destroy()
{
	CCLOG("Athletics Procedure Destroy :");
    NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HEROSOULWINDOW_);
	//释放内存数据 

	_BEGIN_PROF_CHUNK_("ArenaProcedure::ForceFreeMomery")
		// 释放无用资源
	DOTATribeApp::get_instance2()->ForceFreeMemory();
	//StopAllSound();
	_END_PROF_CHUNK_()


	//取消注册断网通知
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
}

//输入事件 暂时不予适用
void  ArenaProcedure::OnInputEventHandler()
{
	//do nothing 
}

 
void ArenaProcedure::OnChangeProcedureToHome()
{
	CCLOG("ArenaProcedure OnChangeProcedureToHomeProcure ");
	DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
}
 

void  ArenaProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}


void  ArenaProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  ArenaProcedure::OnSystemPauseEventHandler()
{

}

void   ArenaProcedure::OnSystemResumeEventHandler()
{

}

void ArenaProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
	}
}
