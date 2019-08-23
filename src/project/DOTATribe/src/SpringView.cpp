#include "../include/SpringView.h"
#include "../include/UIViewDataManger.h"
#include "../include/IDStringDataManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NetSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/ActivityPacket.h"
#include "../include/ActivityDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"
using namespace std;


SpringView::SpringView()
{
	m_WindowType = _TYPED_WINDOW_ACTIVITY_SPRING;
	m_CurWindowActiviId = 0;
}

SpringView::~SpringView()
{
}

bool SpringView::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_SPEING_);
	RegisterEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_SPEING_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ACTIVITYWINDOW_SPEING_,true);
	return IWindow::Init();
}

bool SpringView::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		initLayer();
		
		return true;
	} 
	while (false);

	return false;
	
}
void SpringView::Tick()
{
	IWindow::Tick();
}
void SpringView::Destroy()
{
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}
	
	IWindow::Destroy();
}
void SpringView::initLayer()
{

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSPRINGVIEW,m_pRootNode);
	UpdataButton();

}
void SpringView::OnClick(cocos2d::CCObject* pSender)
{
	NFC_showCommunicationWating(true);
	C2SInSpringPacket packet;
	packet.Send();
}
void SpringView::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ACTIVITYWINDOW_SPEING_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ACTIVITYWINDOW_SPEING_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_ACTIVITYWINDOW_SPEING_)
	{
		OnUpdateUITextEventHandler(paramList);
	}

}

void SpringView::OnUpdateTempleUI(std::list<std::string>& paramList)
{

}
void SpringView::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (WindowManager::get_instance2()->IsWindowVisible(_TYPED_WINDOW_ACTIVITY_))
	{
		if (paramList.size()>0)
		{
			m_CurWindowActiviId = atoi(paramList.begin()->c_str());
			SpringActivityDataHandler::get_instance2()->setSpringActiviId(m_CurWindowActiviId);
		}
		if (m_pRootNode->isVisible())
		{
			UpdataButton();
		}
		Show(true);
	}
}
void SpringView::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{
	UpdataButton();
}
void SpringView::UpdataButton()
{
	CCMenu* ptemp = (CCMenu*)m_pRootNode->getChildByTag(_Spring_Enter_Button_);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(SpringView::OnClick)); 
	if (SpringActivityDataHandler::get_instance2()->getSpringIsOpen()== 0)
	{
		ptempItem->setEnabled(true);
		CCLOG("IsOpen!");
	}
	else
	{
		ptempItem->setEnabled(false);
		CCLOG("IsClose!");
	}
}
