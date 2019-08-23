// Name :		HelpWindow.h
// Function:	°ïÖú´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/HelpWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/UIViewDataManger.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>

using  namespace  cocos2d;


HelpWindow::HelpWindow()
{
	m_WindowType = _TYPED_WINDOW_HELPWINDOW_;
	m_WindowLabel = 0;
}

HelpWindow::~HelpWindow()
{
}

bool HelpWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HELPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_HELPWINDOW_, true);

	return IWindow::Init();
}

bool HelpWindow::Load()
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

void HelpWindow::Tick()
{
	IWindow::Tick();
}

void HelpWindow::Destroy()
{
	IWindow::Destroy();
}
void HelpWindow::InitLayer()
{
	CCNode *pNode = m_pRootNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(m_WindowLabel,pNode);

	CPriorityLayerColor* pBGLayer = (CPriorityLayerColor*)pNode->getChildByTag(Help_MarkLayer);
	pBGLayer->setDelegate(this);
	


}
void HelpWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_HELPWINDOW_);
	
}
void HelpWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_HELPWINDOW_)
	{
		std::list<std::string>::iterator iter_param=paramList.begin();
		if(iter_param!=paramList.end())
		{ 
			m_WindowLabel =atoi(iter_param->c_str());
		}
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_HELPWINDOW_)
	{
		Destroy();
	}
}
void HelpWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	InitLayer();
	Show(true);
}

void HelpWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	PushEvent(_TYPED_EVENT_HIDE_HELPWINDOW_);
}