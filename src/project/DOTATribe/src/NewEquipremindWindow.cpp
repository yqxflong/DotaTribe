//Name:NewEquipremindWindow
//Author: lvyunlong
//Func: 新装备提醒功能
//Maintainer:lvyunlong

#include "../include/NewEquipremindWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/WindowManager.h"
#include "../include/PESWindow.h"
#include "../include/HomeProcedure.h"

USING_NS_CC;


NewEquipremindWindow::NewEquipremindWindow()
{
	m_WindowType   = _TYPED_WINDOW_NEWEQUIPREMINDWINDOW_;
	m_bModelWindow = true;
	m_pEquip = NULL;
}

NewEquipremindWindow::~NewEquipremindWindow()
{
	m_pEquip = NULL;
}

bool NewEquipremindWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_NEWEQUIPREMINDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_, true);
	
	return IWindow::Init();
}
bool NewEquipremindWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		
		BagEquipData *bed =  BAGEQUIPDATAHANDLER->getEquipById(NEWEQUIPREMINDDATAHANDLER->id_);
		if (bed == NULL)
		{
			return false;
		}
		m_pEquip = bed;
		_initLayout();
		return true;
	} 
	while (false);

	return false;
}

void NewEquipremindWindow::Tick()
{
	IWindow::Tick();
}

void NewEquipremindWindow::Destroy()
{
	m_pRootNode->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void NewEquipremindWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_NEWEQUIPREMINDWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void NewEquipremindWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void  NewEquipremindWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void NewEquipremindWindow::_initLayout()
{
	_initControl();
	_mapBtn();
	_setEquipicon();
	_setQualityicon();
}

void NewEquipremindWindow::_setEquipicon()
{
	std::string filepath = RESOURCEDAIDMANAGER->getDataByID(m_pEquip->template_->iconId_);
	NFC_setPicForCCSprite(udEQUIPICON,m_pRootNode,filepath.c_str());
}

void NewEquipremindWindow::_setQualityicon()
{
	std::string qua = varConfig::getCardBGFilePath(m_pEquip->template_->quality_);
	NFC_setPicForCCSprite(udQUALITY,m_pRootNode,qua.c_str());
}

void NewEquipremindWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kNEWEQUIPREMINDWINDOW,m_pRootNode);
}

void NewEquipremindWindow::_mapBtn()
{
	CCMenu* menu=(CCMenu*)NFC_getNode(udCHECKBTN,m_pRootNode);
	CMenuItemSprite *item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(NewEquipremindWindow::On_Check_ClickBtn));


	menu=(CCMenu*)NFC_getNode(udCLOSEBTN,m_pRootNode);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(NewEquipremindWindow::On_Close_ClickBtn));
}

void NewEquipremindWindow::On_Check_ClickBtn(cocos2d::CCObject * pSender)
{
	if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_SELECTSONMISSION_))
	{
		int backwindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_CLIMBWINDOW_))
	{
		int backwindow = _TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_TEAMBATTLEWINDOW_))
	{
		int backwindow = _TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_ARENAWINDOW_))
	{
		int backwindow = _TYPEF_EVENT_SHOW_ARENAWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_MINEAREA_WINDOW_))
	{
		int backwindow = _TYPED_EVENT_SHOW_MINEAREAWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else if (WINDOWMANAGER->IsWindowVisible(_TYPED_WINDOW_BOSSSCORE_))
	{
		int backwindow = _TYPED_EVENT_SHOW_BOSSSCOREWINDOW_;
		NEWEQUIPREMINDDATAHANDLER->HideClearData();
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
	}
	else
	{
		if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
		{
			int backwindow = _TYPED_EVENT_SHOW_HOMEWINDOW_;
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
			NEWEQUIPREMINDDATAHANDLER->HideClearData();
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(backwindow));
		}
		else
		{
			int backwindow = _TYPED_EVENT_SHOW_HOMEWINDOW_;
			PESWindow* pWindow = (PESWindow*)WINDOWMANAGER->GetWindowByType(IWindow::_TYPED_WINDOW_PESWINDOW_);
			pWindow->m_nBackWindowType = backwindow;
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_GUIDE_);
			NEWEQUIPREMINDDATAHANDLER->HideClearData();
			DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_FADEIN_PESWINDOW_);
			DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(PESWindow::kTAB_1);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
		} 

	}
	//新手引导
	GuideSystem::get_instance2()->Next();
}

void NewEquipremindWindow::On_Close_ClickBtn(cocos2d::CCObject * pSender)
{
	NEWEQUIPREMINDDATAHANDLER->HideClearData();
}