//Name:TeamBattleProcedure
//Function:组队副本流程
//Author:fangjun
//Date:20130918

#include "../include/TeamBattleProcedure.h"
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
#include "../include/MessagePacket.h"
#include "../include/MessagePacketManager.h"
#include "../include/HomeProcedure.h"
#include <list>
#include "../include/TeamBattleDataHandler.h"
#include "../include/ServerInfoDataHandler.h"


TeamBattleProcedure::TeamBattleProcedure()
{
	m_Type = _TYPED_TEAMBATTLE_PROCEDURE_;

	m_nowState = _TEAMBATTLE_STATE_UNKNOW_;
}

TeamBattleProcedure::~TeamBattleProcedure()
{

}

bool  TeamBattleProcedure::Init()
{
	do
	{

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);

		if(this->m_nowState == _TEAMBATTLE_STATE_SELECTGATE_)
		{
			TEAMBATTLEDATAHANDLER->ToServerEnterTeamBattle();
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
		}
		else if(this->m_nowState == _TEAMBATTLE_STATE_WAITTEAMER_)
		{
			TEAMBATTLEDATAHANDLER->ToServerEnterTeamSelect();
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMSELECTWINDOW_);
		}
		else
		{//default
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
		}



		//注册断网通知
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY,Event_Procedure_Handler);

		LOGGERSYSTEM->LogInfo("TeamBattleProcedure: Enter\n");
		return true;
	} 
	while (false);

	return false;
}

void  TeamBattleProcedure::Tick()
{
	// 执行输入处理
	OnInputEventHandler();
}

void  TeamBattleProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("TeamBattleProcedure::Destroy()")

	_BEGIN_PROF_CHUNK_("TeamBattleProcedure::Hide Window")
	// 隐藏UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMSELECTWINDOW_);

	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_HIDE_PLAYERTIPSWINDOW_);

	_END_PROF_CHUNK_()

	_BEGIN_PROF_CHUNK_("TeamBattleProcedure::ForceFreeMomery")
		// 释放无用资源
		DOTATribeApp::get_instance2()->ForceFreeMemory();
	_END_PROF_CHUNK_()

	m_nowState = _TEAMBATTLE_STATE_UNKNOW_;




	//取消注册断网通知
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY,Event_Procedure_Handler);

	LOGGERSYSTEM->LogInfo("TeamBattleProcedure: Leave\n");
}

void  TeamBattleProcedure::OnInputEventHandler()
{

}

void  TeamBattleProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  TeamBattleProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  TeamBattleProcedure::OnSystemPauseEventHandler()
{

}

void  TeamBattleProcedure::OnSystemResumeEventHandler()
{

}

void TeamBattleProcedure::SetBackWindow(int backwindowId)
{
	this->m_backWindow = backwindowId;
}

void TeamBattleProcedure::GetProvideStateData(int stateEnumId)
{
	if(stateEnumId == _TEAMBATTLE_STATE_SELECTGATE_)
	{
		TEAMBATTLEDATAHANDLER->ToServerEnterTeamBattle();
		TEAMBATTLEDATAHANDLER->m_pTeamListData->destroyData();
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
	}
	else if(stateEnumId == _TEAMBATTLE_STATE_WAITTEAMER_)
	{
		TEAMBATTLEDATAHANDLER->ToServerEnterTeamSelect();
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
	}
}

void TeamBattleProcedure::ChangeNowState(int stateEnumId)
{
	this->m_nowState = stateEnumId;

	if(m_nowState == _TEAMBATTLE_STATE_SELECTGATE_)
	{
		TEAMBATTLEDATAHANDLER->ToServerEnterTeamBattle();
		TEAMBATTLEDATAHANDLER->m_pTeamListData->destroyData();
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
	}
	else if(m_nowState == _TEAMBATTLE_STATE_WAITTEAMER_)
	{
		TEAMBATTLEDATAHANDLER->ToServerEnterTeamSelect();
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
	}
}

int TeamBattleProcedure::GetNowState()
{
	return this->m_nowState;
}

void TeamBattleProcedure::ChangeProcedureToHomeWithLoading()
{
	//切换流程
	CCLOG("TeamBattleProcedure changeToProcedure HomeProcure");
	DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
}

void TeamBattleProcedure::ChangeProcedureToAthletic()
{
	//Post进入战斗流程通知
	char athleticsProcedure[8]={0};
	sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_ATHLETICS_PROCEDURE_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);
}

void TeamBattleProcedure::DisconnectNetworkHandler()
{
	if(GetNowState() == TeamBattleProcedure::_TEAMBATTLE_STATE_WAITTEAMER_)
	{
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
		{
			delete TEAMBATTLEDATAHANDLER->m_pMyTeamData;
			TEAMBATTLEDATAHANDLER->m_pMyTeamData = NULL;
		}
		ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMSELECTWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
	}

}

void TeamBattleProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
	}else if(iEventType==_TYPED_EVENT_RECONNECT_INGAME_NOTIFY){
		//断线重连后的通知
		//可以做相应的处理
		if(typeid(* DOTATribeApp::get_instance2()->GetActiveProcedure()) == typeid(TeamBattleProcedure))
		{
			((TeamBattleProcedure *)(DOTATribeApp::get_instance2()->GetActiveProcedure()))->DisconnectNetworkHandler();
		}
	}
}