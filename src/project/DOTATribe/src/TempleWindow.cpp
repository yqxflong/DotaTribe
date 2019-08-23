#include "../include/TempleWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/WindowManager.h"
#include "../include/SpringView.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>
using  namespace  cocos2d;


TempleWindow::TempleWindow()
{
	m_WindowType = _TYPED_WINDOW_TEMPLE_;
	m_Tab_One = NULL;
	m_Tab_Two = NULL;
	m_showWindow = NULL;
	m_tabNum = 0;
	m_return = 0;
}

TempleWindow::~TempleWindow()
{

}

bool TempleWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TEMPLEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_TEMPLEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	return IWindow::Init();
}

bool TempleWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		InitLayer();
		return true;
	} 
	while (false);

	return false;
}

void TempleWindow::Tick()
{
	IWindow::Tick();
}

void TempleWindow::Destroy()
{
	m_Tab_One = NULL;
	m_Tab_Two = NULL;
	m_tabNum = 0;
	m_return = 0;
	if (m_showWindow)
	{
		m_showWindow->Destroy();
		m_showWindow = NULL;
	}	
		IWindow::Destroy();
}

void TempleWindow::InitLayer()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEMPLEWINDOW,m_pRootNode);
	_uckInitButton();
	_uckUpdateDiamondAndMoney();
}

void TempleWindow::InitTab()
{
	_uckInitTab(m_tabNum);
}

void TempleWindow::On_Close( cocos2d::CCObject* pSender )
{
	PushEvent(_TYPED_EVENT_HIDE_TEMPLEWINDOW_);	
}

void TempleWindow::On_Help( cocos2d::CCObject* pSender )
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kHEROTECHNOLOGY_HELP_));
}

void TempleWindow::On_SelectTab( cocos2d::CCObject* pSender )
{
	_uckSelectTab((CMenuItemSprite*)pSender);
}

void TempleWindow::OnEventHandler( int iEventType, std::list<std::string>& paramList )
{
	if (iEventType == _TYPED_EVENT_SHOW_TEMPLEWINDOW_)
	{
		_uckSetTabAndReturnWindow(paramList);
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_TEMPLEWINDOW_)
	{
		_uckReturnWindow();
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		OnUpdateTempleUI(paramList);
	}
}

void TempleWindow::OnUpdateTempleUI( std::list<std::string>& paramList )
{
	_uckUpdateDiamondAndMoney();
}

void TempleWindow::OnShowWindowEventHandler( std::list<std::string>& paramList )
{
	Show(true);
	InitTab();
}

void TempleWindow::_uckSetTabAndReturnWindow( std::list<std::string>& paramList )
{
	std::list<std::string>::iterator iter_b = paramList.begin();
	if (iter_b != paramList.end())
	{
		m_tabNum = atoi((*iter_b).c_str());
		iter_b++;
	}
	if (iter_b != paramList.end())
	{
		m_return = atoi((*iter_b).c_str());
		iter_b++;
	}
}

void TempleWindow::_uckUpdateDiamondAndMoney()
{
	CCLabelTTF* pDiamond = (CCLabelTTF*)m_pRootNode->getChildByTag(Temple_DIAMONDNUM);
	char _diamond[64] = "";
	sprintf(_diamond,"%d",RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_);
	pDiamond->setString(_diamond);
	CCLabelTTF* pMoney = (CCLabelTTF*)m_pRootNode->getChildByTag(Temple_MONEYDNUM);
	char _money[64] = "";
	sprintf(_money,"%d",RoleInfoDataHandler::get_instance2()->m_pRIData->money_);
	pMoney->setString(_money);
}

void TempleWindow::_uckInitButton()
{
	CCMenu* ptemp = (CCMenu*)m_pRootNode->getChildByTag(Temple_HELP);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(TempleWindow::On_Help));

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Temple_CLOSE);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(TempleWindow::On_Close));

	ptemp = (CCMenu*)m_pRootNode->getChildByTag(Temple_TAB_ONE_BUTTON);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(TempleWindow::On_SelectTab));
	m_Tab_One = ptempItem;
}

void TempleWindow::_uckInitTab( int tabNum )
{
	switch(tabNum)
	{
	case Temple_FIRST_TAB_:
		{
			m_Tab_One->selected(true);
			C2SHeroTechnologyPacket crpacket;
			crpacket.Send();
			m_showWindow = WINDOWMANAGER->GetWindowByType(_TYPED_WINDOW_CONVICTION_);
		}

		break;
	case Temple_SECOND_TAB_:
		/*m_Tab_Two->selected(true);*/
		break;
	default:
		break;
	}
}

void TempleWindow::_uckSelectTab( CMenuItemSprite* pItem )
{
	if (pItem->getParent()->getTag() == Temple_TAB_ONE_BUTTON)
	{
		if (m_Tab_One != pItem)
		{
			m_Tab_One->selected(true);
			//显示界面
			//关闭之前界面
		}
	}
}

void TempleWindow::_uckReturnWindow()
{
	if (m_return!=0)
		PushEvent(m_return);
	else
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
}