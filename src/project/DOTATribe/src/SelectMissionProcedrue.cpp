// Name :		SelectMissionProcedure.h
// Function:	关卡选择流程
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/SelectMissionProcedure.h"
#include "../include/DOTATribeApp.h"
#include "../include/ProfSystem.h"
#include "../include/SoundSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/AthleticsProcedure.h"
#include "../include/LoginProcedure.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/MissionDataHandler.h"
#include "../include/HomeProcedure.h"
#include <list>
#include "../include/GuideSystem.h"

#include "../include/ServerInfoDataHandler.h"


SelectMissionProcedure::SelectMissionProcedure()
{
	m_Type = _TYPED_SELECTMISSION_PROCEDURE_;
	m_showWindow = 0;
	m_skipWindow = 0;
	m_skipTabNum = 0;
}

SelectMissionProcedure::~SelectMissionProcedure()
{

}

void SelectMissionProcedure::ChangeProcedureTo(IProcedure* procedure)
{
	// 切换流程
	char type[128] = "";
	sprintf(type,"%d",procedure->GetType());
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,type);
}
void SelectMissionProcedure::ChangeToSelectSonMissionProcedure()
{
}

bool  SelectMissionProcedure::Init()
{
	do 
	{  

		GUIDESYSTEM->NextDone();
			// 显示UI
			if (m_showWindow!=0)
			{
				if (m_skipWindow!=0)
				{
					char param1[128];
					sprintf(param1,"%d",m_skipTabNum);
					char param2[128];
					sprintf(param2,"%d",m_showWindow);
					if (m_skipWindow == _TYPED_EVENT_FADEIN_PESWINDOW_ || m_skipWindow == _TYPED_EVENT_SHOW_STRENTHENWINDOW_ || m_skipWindow == _TYPED_EVENT_SHOW_PESWINDOW_)
					EVENTSYSTEM->PushEvent(m_skipWindow,param1,param2);
					else
					EVENTSYSTEM->PushEvent(m_skipWindow,param2);
				}
				else
				{
					StatesInfoData * pStatesData = MissionDataHandler::get_instance2()->GetStatesInfoInfo(1,1);
					if (pStatesData&&!pStatesData->getIsClear())
						EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTMISSIONWINDOW_);
					else
						EVENTSYSTEM->PushEvent(m_showWindow);
				}
				m_showWindow = 0;
				m_skipWindow = 0;
				m_skipTabNum = 0;
			}
			else
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTMISSIONWINDOW_);
		PlayBGSound();



		//注册断网通知
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);
		return true;
	} 
	while (false);

	return false;
}

void  SelectMissionProcedure::Tick()
{
	// 执行输入处理
	OnInputEventHandler();
}

void  SelectMissionProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("SelectMissionProcedure::Destroy()")
	// 隐藏UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTMISSIONWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MASSACREWINDOW_);
	DOTATribeApp::get_instance2()->ForceFreeMemory();
	//StopAllSound();
	_END_PROF_CHUNK_()



	//取消注册断网通知
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
	LOGGERSYSTEM->LogInfo("SelectMissionProcedure: Leave\n");
}

void  SelectMissionProcedure::OnInputEventHandler()
{

}

void  SelectMissionProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  SelectMissionProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  SelectMissionProcedure::OnSystemPauseEventHandler()
{

}

void  SelectMissionProcedure::OnSystemResumeEventHandler()
{

}


void SelectMissionProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
	}
}