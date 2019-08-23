//Name：LoginProcedure
//Function：登录流程，游戏第一个流程
//Written By：尹强

#include <cocos2d.h>
#include "../include/LoginProcedure.h"
#include "../include/SoundSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/ProfSystem.h"
#include "../include/WindowManager.h"
#include "../include/InputEvent.h"
#include "../include/IWindow.h"
#include "../include/ServerInfoDataHandler.h"
#include <list>
#include "../include/NetSystem.h"
#include "../include/NFControlsManager.h"


using namespace cocos2d;

LoginProcedure::LoginProcedure()
{
	m_Type = _TYPED_LOGIN_PROCEDURE_;
}

LoginProcedure::~LoginProcedure()
{

}

void  LoginProcedure::ChangeProcedureTo(IProcedure* procedure){
	if (DOTATribeApp::get_instance2()->GetActiveProcedure()!=procedure){
		char type[128] = "";
		sprintf(type,"%d",procedure->GetType());
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,type);
	}else{
		NFC_showCommunicationWating(false);
	}
}

bool  LoginProcedure::Init()
{
	do 
	{
		LOGGERSYSTEM->LogInfo("======LoginProcedure::Init=======");
		//hide SDK ToolBar
		SERVERINFODATAINFO->ShowSuspendWindow(false);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_STARTWINDOW_);
		SERVERINFODATAINFO->LoginProcedureInit();
		//
		PlayBGSound();
		LOGGERSYSTEM->LogInfo("LoginProcedure: Enter\n");
		return true;
	} 
	while (false);

	return false;
}

void  LoginProcedure::Tick()
{
	// 执行输入处理
	OnInputEventHandler();
}

void  LoginProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("LoginProcedure::Destroy()==Unload Resource");
	// 隐藏UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_STARTWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSERVERWINDOW_);
	DOTATribeApp::get_instance2()->ForceFreeMemory();
	_END_PROF_CHUNK_()
	LOGGERSYSTEM->LogInfo("LoginProcedure: Leave\n");
}

/*
	仅处理该流程的输入相关事件
*/
void  LoginProcedure::OnInputEventHandler()
{ 
	
}

void  LoginProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  LoginProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  LoginProcedure::OnSystemPauseEventHandler()
{

}

void  LoginProcedure::OnSystemResumeEventHandler()
{

}
