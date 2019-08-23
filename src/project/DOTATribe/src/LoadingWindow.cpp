// Name :		LoadingWindow.h
// Function:	Loading窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/LoadingWindow.h"
#include "../include/IWindow.h"
#include "../include/WindowManager.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/EventSystem.h"
#include "../include/LoginProcedure.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/AthleticsProcedure.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/EngineSystem.h"
#include "../include/ClientConstDataManager.h"
#include "../include/SysLangDataManager.h"
#include  "../include/NFControlsManager.h"
#include  "spine/SpineCallBackEvent.h"
#include <include/common/Random.h>
#include <cocos2d.h>
#include <cocos-ext.h>


using namespace cocos2d;
using namespace cocos2d::extension; 
using namespace  cobra_win;

#define  MaxRandom 30
#define  Tip_FontStyle 23
#define  START_TIPS_TID 800
LoadingWindow::LoadingWindow()
{
	m_WindowType = _TYPED_WINDOW_LOADING_;
	m_NextProcedure = 0;
	m_count = 0;
	m_maxCount = 0;

}

LoadingWindow::~LoadingWindow()
{

}

bool LoadingWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_UI_TEXT_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LOADINGWINDOW_BAR_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LOADINGWINDOW_TEXT_, true);
	return IWindow::Init();
}

bool LoadingWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		return true;
	} 
	while (false);

	return false;
}

void LoadingWindow::SkipToNextProcedure(){
	if (m_NextProcedure!=0)
	{
		if(m_NextProcedure==_RESTART_ATHLETICS_PROCEDURE_)
		{
			//在此进行战斗流程重启
			DOTATribeApp::get_instance2()->m_pAthleticsProcudure->DestroyWithOutAthleticsData();
			DOTATribeApp::get_instance2()->m_pAthleticsProcudure->Init();
		}
		else if(m_NextProcedure==_RESTART_MISSION_PROCEDURE_)
		{
			DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->Destroy();
			DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->Init();
		}
		else
			DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->GetProcedure(m_NextProcedure));

		m_NextProcedure = 0;
	}
}

void LoadingWindow::Tick()
{
	m_count++;
	if(m_count > m_maxCount&&m_NextProcedure!=0)
	{
		m_count = 0;
		SkipToNextProcedure();
	}

	IWindow::Tick();
}

void LoadingWindow::Destroy()
{
	m_count = 0;
	IWindow::Destroy();
}

void LoadingWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LOADINGWINDOW_)
	{ 
		std::list<std::string>::iterator iter_param=paramList.begin();
		if(iter_param!=paramList.end())
		{ 
			m_NextProcedure=atoi(iter_param->c_str());
		}
		OnShowWindowEventHandler(paramList);
		NFC_showCommunicationWating(false);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LOADINGWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_UI_TEXT_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LOADINGWINDOW_BAR_)
	{
		OnUpdateLoadingBarEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LOADINGWINDOW_TEXT_)
	{
		OnUpdateLoadingTextEventHandler(paramList);
	}
}

void LoadingWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	std::list<std::string>::iterator iter_param=paramList.begin();
	if(iter_param!=paramList.end())
	{ 
		m_NextProcedure=atoi(iter_param->c_str());
	}
	if (!m_pRootNode->isVisible())
	{
		InitLayer();
		randomMaxCount();
		Show(true);
	}
 }

void LoadingWindow::InitLayer()
{
	CCNode* baseNode = CCNode::create();
	baseNode->setAnchorPoint(ccp(0,0));
	baseNode->setPosition(ccp(0,0));
	m_pRootNode->addChild(baseNode);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLOADINGWINDOW, baseNode);
	 
	CCLabelTTF* text = (CCLabelTTF*)baseNode->getChildByTag(3);
	int  maxRankLimit = ClientConstDataManager::get_instance2()->getValueByKey(Loading_Tip_Total_Num);
	text->setString(SysLangDataManager::get_instance2()->GetSysLangById(Random::rand()%maxRankLimit + START_TIPS_TID).c_str());
}

void LoadingWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{

}

void LoadingWindow::OnUpdateLoadingBarEventHandler(std::list<std::string>& paramList)
{

}

void LoadingWindow::OnUpdateLoadingTextEventHandler(std::list<std::string>& paramList)
{
}
void LoadingWindow::randomMaxCount()
{
	m_maxCount = Random::rand()%MaxRandom + 10;
	CCLOG("Time : %d",m_maxCount);
}