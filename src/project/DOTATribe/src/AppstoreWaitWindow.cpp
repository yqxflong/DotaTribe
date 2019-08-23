//Name£ºAppstoreWaitWindow
//Function£ºAppstoreµÈ´ýÖ§¸¶¿ò
//Written By£ºlvyunlong

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/AppstoreWaitWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/NetSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"


using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


AppstoreWaitWindow::AppstoreWaitWindow()
:m_pRoot(0)
{
	m_WindowType   = _TYPED_WINDOW_APPSTOREWAITWINDOW_;
	m_bModelWindow = true;
}

AppstoreWaitWindow::~AppstoreWaitWindow()
{

}

bool AppstoreWaitWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_APPSTOREWAITWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_APPSTOREWAITWINDOW_, true);

	return IWindow::Init();
}

void AppstoreWaitWindow::_initLayout(){
	m_pRoot= m_pRootNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kAPPSTOREWAITWINDOW,m_pRoot);
}

bool AppstoreWaitWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();

		return true;
	} 
	while (false);

	return false;
}

void AppstoreWaitWindow::Tick()
{
	IWindow::Tick();
}

void AppstoreWaitWindow::Destroy()
{
	IWindow::Destroy();
}

void AppstoreWaitWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_APPSTOREWAITWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_APPSTOREWAITWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}
/*
	paramList: 0:Title  1:Text
*/
void AppstoreWaitWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}


void   AppstoreWaitWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}


