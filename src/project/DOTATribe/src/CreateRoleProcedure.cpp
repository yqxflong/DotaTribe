// Name :		CreateRoleProcedure.h
// Function:	��ɫ��������
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#include "../include/CreateRoleProcedure.h"
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
#include "../include/MessagePacket.h"
#include "../include/MessagePacketManager.h"
#include "../include/ServerInfoDataHandler.h"
#include <list>


CreateRoleProcedure::CreateRoleProcedure()
{
	m_Type = _TYPED_CREATEROLEPROCEDURE_PROCEDURE_;
}

CreateRoleProcedure::~CreateRoleProcedure()
{

}

void CreateRoleProcedure::ChangeProcedureTo(IProcedure* procedure)
{
	// �л�����
	char type[128] = "";
	sprintf(type,"%d",procedure->GetType());
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,type);

}

bool  CreateRoleProcedure::Init()
{
	do 
	{
		_BEGIN_PROF_CHUNK_("CreateRoleProcedure::Init()")
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTROLEWINDOW_);	
		PlayBGSound();
		_END_PROF_CHUNK_()



		//ע�����֪ͨ
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
		return true;
	} 
	while (false);

	return false;
}

void  CreateRoleProcedure::Tick()
{
	// ִ�����봦��
	OnInputEventHandler();
}

void  CreateRoleProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("CreateRoleProcedure::Destroy()")

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTROLEWINDOW_);


		_BEGIN_PROF_CHUNK_("CreateRoleProcedure::ForceFreeMomery")
		// �ͷ�������Դ
		DOTATribeApp::get_instance2()->ForceFreeMemory();
		_END_PROF_CHUNK_()
		//StopAllSound();
	_END_PROF_CHUNK_()

	//ȡ��ע�����֪ͨ
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
	LOGGERSYSTEM->LogInfo("CreateRoleProcedure: Leave\n");
}

void  CreateRoleProcedure::OnInputEventHandler()
{

}

void  CreateRoleProcedure::OnSystemEnterBackEventHandler()
{

}

void  CreateRoleProcedure::OnSystemEnterFrontEventHandler()
{

}

void  CreateRoleProcedure::OnSystemPauseEventHandler()
{

}

void  CreateRoleProcedure::OnSystemResumeEventHandler()
{

}

void CreateRoleProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
	}
}