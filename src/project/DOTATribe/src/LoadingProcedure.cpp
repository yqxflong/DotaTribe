// Name :		LoadingProcedure.h
// Function:	Loading流程
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/LoadingProcedure.h"
#include "../include/DOTATribeApp.h"
#include "../include/ProfSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"

LoadingProcedure::LoadingProcedure()
{
	m_Type = _TYPED_LOADING_PROCEDURE_;
}

LoadingProcedure::~LoadingProcedure()
{

}

bool  LoadingProcedure::Init()
{
	do 
	{
		_BEGIN_PROF_CHUNK_("LoadingProcedure::Init()");

		_END_PROF_CHUNK_()
		LOGGERSYSTEM->LogInfo("LoadingProcedure: Enter\n");
		return true;
	} 
	while (false);

	return false;
}

void  LoadingProcedure::Tick()
{
	// 执行输入处理
	OnInputEventHandler();
}

void  LoadingProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("LoadingProcedure::Destroy()");

	_END_PROF_CHUNK_()
	LOGGERSYSTEM->LogInfo("LoadingProcedure: Leave\n");
}

void  LoadingProcedure::OnInputEventHandler()
{

}

void  LoadingProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  LoadingProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  LoadingProcedure::OnSystemPauseEventHandler()
{

}

void  LoadingProcedure::OnSystemResumeEventHandler()
{

}
