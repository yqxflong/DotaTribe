//Name：LogoWindow
//Function：展示Logo，只有安卓用
//Author：尹强

#include <cocos2d.h>
#include "../include/LogoWindow.h"
#include "../include/UIViewDataManger.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LogoProcedure.h"


LogoWindow::LogoWindow()
	:m_LogicTickCounter(0)
	,m_bChangeLogo(false)
	,m_pLogo(NULL)
{
	m_WindowType   = _TYPED_WINDOW_LOGO_;
	m_bModelWindow = false;

}

LogoWindow::~LogoWindow()
{

}

bool LogoWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LOGOWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LOGOWINDOW_, true);

	return IWindow::Init();
}

bool LogoWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kANDROID_LOGOWINDOW,m_pRootNode);

		m_pLogo = (CSprite *)m_pRootNode->getChildByTag(tLogo);

		if(m_pLogo)
			m_pLogo->changeToImage1();

		return true;
	} 
	while (false);

	return false;
}

void LogoWindow::Tick()
{
	m_LogicTickCounter++;

	float idleTime = 0.5f;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "LogoProcedureIdleTime", idleTime);

	if(m_LogicTickCounter >= int(idleTime*DOTATribeApp::get_instance2()->GetFPS()) && m_bChangeLogo == false)
	{
		m_bChangeLogo = true;

		//判断logo是否包含第二张logo，有的话，需要显示第二张,否则显示切换流程
		if(m_pLogo && m_pLogo->hasImage2())
		{
			m_pLogo->changeToImage2();
		}
		else
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			//通知sdk已经完成显示公司LOGO了
			CCDirector::sharedDirector()->getPlatform()->companyLogoFinished();
#endif
			DOTATribeApp::get_instance2()->m_pLogoProcedure->ChangeToNextProcedure();
		}
	}

	if (m_LogicTickCounter >= 2 * (int)(idleTime*DOTATribeApp::get_instance2()->GetFPS()))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//通知sdk已经完成显示公司LOGO了
		CCDirector::sharedDirector()->getPlatform()->companyLogoFinished();
#endif
		DOTATribeApp::get_instance2()->m_pLogoProcedure->ChangeToNextProcedure();
	}

	IWindow::Tick();
}

void LogoWindow::Destroy()
{
	m_LogicTickCounter = 0;
	m_bChangeLogo = false;
	m_pLogo = NULL;

	IWindow::Destroy();
}

void LogoWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LOGOWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LOGOWINDOW_)
	{
		Destroy();
	}
}

void LogoWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}
