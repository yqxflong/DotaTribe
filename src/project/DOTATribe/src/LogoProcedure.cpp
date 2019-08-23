#include <cocos2d.h>
#include "../include/LogoProcedure.h"
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ProfSystem.h"
#include "../include/LoginProcedure.h"
#include "../include/CreateRoleProcedure.h"
#include "../include/DOTATribeApp.h"
#include <list>


LogoProcedure::LogoProcedure()
{
	m_Type = _TYPED_LOGO_PROCEDURE_;
	
}

LogoProcedure::~LogoProcedure()
{

}

void  LogoProcedure::ChangeToNextProcedure()
{
	/*
		登陆流程包含：
		1.检查更新
		2.更新
		3.选服务器
		4.登陆
	*/
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pLoginProcedure);
}

bool  LogoProcedure::Init()
{
	do 
	{
		_BEGIN_PROF_CHUNK_("LogoProcedure::Init()")
		// 显示UI
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOGOWINDOW_);
		_END_PROF_CHUNK_()
		LOGGERSYSTEM->LogInfo("LogoProcedure: Enter\n");
		return true;
	} 
	while (false);

	return false;
}

void  LogoProcedure::Tick()
{
	// 执行输入处理
	OnInputEventHandler();

}

void  LogoProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("LogoProcedure::Destroy()")
	// 隐藏UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOGOWINDOW_);
	// 释放无用资源
	DOTATribeApp::get_instance2()->ForceFreeMemory();
	_END_PROF_CHUNK_()

	LOGGERSYSTEM->LogInfo("LogoProcedure: Leave\n");
}

void  LogoProcedure::OnInputEventHandler()
{
	
}

void  LogoProcedure::OnSystemEnterBackEventHandler()
{

}

void  LogoProcedure::OnSystemEnterFrontEventHandler()
{

}

void  LogoProcedure::OnSystemPauseEventHandler()
{

}

void  LogoProcedure::OnSystemResumeEventHandler()
{

}
