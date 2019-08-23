// Name :		ActivityWindow.h
// Function:	活动窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/ActivityWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/WindowManager.h"
#include "../include/SpringView.h"
#include "../include/ActivityDataHandler.h"
#include "../include/ActivityPacket.h"
#include "../include/NFAnimationController.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>
#include "../include/CSMapTable.h"
using  namespace  cocos2d;

#define Interval	75
#define Interval_NULL	10
#define FontName	"ArialRoundedMTBold" //默认字体

#define Top_Boundary 500.0f
#define Down_Boundary -60.0f
#define JUMP_Boundary 125.0f
#define JUMP_Top_Boundary 375.0f
#define JUMP_Down_Boundary 70.0f
ActivityWindow::ActivityWindow()
{
	m_WindowType = _TYPED_WINDOW_ACTIVITY_;
	m_Tab_One = NULL;
	m_Tab_Two = NULL;
	m_showWindow = NULL;
	m_nHideLastWindowEventId = -1;
	m_tabNum = 1;
	m_scrollView = NULL;
	m_scrollLayer = NULL;
	m_Frame= NULL;
	m_RecharMenu = NULL;
	m_Reroad = false;
	m_CurActivityType = _ACTIVITY_UNKONW_TYPE_;
	m_scrollflag = false;
	m_isFirstIn = false;
}

ActivityWindow::~ActivityWindow()
{

}

bool ActivityWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ACTIVITYWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	RegisterEvent(_TYPED_EVENT_DELETE_ACTIVITY_,true);
	RegisterEvent(_TYPED_EVENT_UPDATEEFFECT_ACTIVITY_,true);
	
	
	return IWindow::Init();
}

bool ActivityWindow::Load()
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

void ActivityWindow::Tick()
{
	IWindow::Tick();
}

void ActivityWindow::Destroy()
{
	m_Tab_One = NULL;
	m_Tab_Two = NULL;
	m_tabNum = 1;
	m_Reroad = false;
	if (m_showWindow)
	{
		m_showWindow->Destroy();
		m_showWindow = NULL;
	}
	if(m_nHideLastWindowEventId > 0)
	{
		EVENTSYSTEM->PushEvent(m_nHideLastWindowEventId);
		m_nHideLastWindowEventId = -1;
	}
	m_scrollView->removeFromParentAndCleanup(true);
	m_scrollView = NULL;
	m_scrollLayer = NULL;
	m_Frame= NULL;
	m_LayerList.clear();
	m_MapCSpriteEffEct.clear();
	ExchangeActivityDataHandler::get_instance2()->destroyData();
	IWindow::Destroy();
}

void ActivityWindow::InitLayer()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kACTIVITYWINDOW,m_pRootNode);
	CCMenu* ptemp = (CCMenu*)m_pRootNode->getChildByTag(Activity_CLOSE);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(ActivityWindow::On_Close));
	m_scrollView =(CScrollView*)m_pRootNode->getChildByTag(Activity_View);
	m_scrollView->setDelegate(this);
	m_scrollLayer = (CCLayerColor*)m_scrollView->getContainer();
}

void ActivityWindow::DeleteCurActivity()
{
	PushEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_);
	C2SActivityPacket packet;
	packet.Send();
}

void ActivityWindow::InitTab()
{
	//初始化默认活动 
	ActivityInfoItem  * pAcitivityInfoItem  = ActivityDataHandler::get_instance2()->getActivityServerMap()->getDefaulActivityItem(); 
	short  activityType = pAcitivityInfoItem->getActivityItemType(); 
	m_CurActivityType = activityType;
	if(pAcitivityInfoItem->getActivityConfig()->m_nShowActivityBg > 0)
	{
		NFC_showNode(ActivityBG,m_pRootNode,true);
	}
	else
	{
		NFC_showNode(ActivityBG,m_pRootNode,false);
	}
	if (_ACTIVITY_FIRSTRECHGIFT_TYPE_ == activityType)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_FIRSTRECHGIFTWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));		
		FIRSTRECHDATAHANDLER->ToServerInfoFirstRech();
	}
	else if (_ACTIVITY_VIPBAGREWARD_TYPE_ == activityType)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_VIPGIFTWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));		
		VIPGIFTACTIVITYHANDLER->ToServerInfoVipGift();
	}
	else
	{
		if(_ACTIVITY_LEVELUPREWARD_TYPE_ == activityType)
		{  
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPREWARDACTIVITYWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));
		} 
		else if(_ACTIVITY_SPRING_TYPE_ == activityType)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_SPEING_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));
		}
		else if(_ACTIVITY_GROWUPPLAN_TYPE_ == activityType)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_GROWUPPLANACTIVITYWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));
		}
		else if(_ACTIVITY_LOGINREWARD_TYPE_ == activityType)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOGINACTIVITYWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));
		}
		else if(_ACTIVITY_EXCHANGEREWARD_TYPE_ == activityType)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EXCHANGEACTIVITYWINDOW_,_to_event_param_(pAcitivityInfoItem->getActivityItemID()));
		}
		NFC_showCommunicationWating(true);
		C2SChioseActivityPacket packet(pAcitivityInfoItem->getActivityItemID());
		packet.Send();
	}
	if(pAcitivityInfoItem->getActivityConfig()->m_nUseLua > 0)
	{
		m_nHideLastWindowEventId = pAcitivityInfoItem->getActivityConfig()->m_nHideEventId;
		m_showWindow = NULL;
	}
	else
	{
		m_nHideLastWindowEventId = -1;
		m_showWindow = WINDOWMANAGER->GetWindowByType(pAcitivityInfoItem->getActivityConfig()->m_nActivityWindowID);
	}
}

void ActivityWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_);	
	if (DOTATribeApp::get_instance2()->IsHomeProcedureAsActiveProcedure())
	{
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else
	{
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
	}
}

void ActivityWindow::On_Chiose_Activity(cocos2d::CCObject* pSender)
{

}

void ActivityWindow::On_SelectTab(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* pItem = (CMenuItemSprite*)pSender;
	CCLOG("%f",pItem->getParent()->getParent()->getPositionY()+m_scrollView->getContainer()->getPositionY());
	int posY =(int)(pItem->getParent()->getParent()->getPositionY()+m_scrollView->getContainer()->getPositionY());
	if (posY > Top_Boundary || posY < Down_Boundary)
		return;

	float _len1;
	posY > Top_Boundary ? _len1 = (posY-Top_Boundary) :  _len1 = (Top_Boundary-posY); 
	float _len2;
	posY > Down_Boundary ? _len2 = (posY-Down_Boundary) :  _len2 = (Down_Boundary-posY); 
	if (_len1 < _len2)
	{
		if (_len1<JUMP_Boundary)
		{
			int _len = (int)(JUMP_Boundary - _len1);
			m_scrollView->getContainer()->setPosition(ccp(m_scrollView->getContainer()->getPositionX(),m_scrollView->getContainer()->getPositionY()-_len));
		}
	}
	else
	{
		if (_len2<JUMP_Boundary+5)
		{
			int _len = (int)(JUMP_Boundary+5 - _len2);
			m_scrollView->getContainer()->setPosition(ccp(m_scrollView->getContainer()->getPositionX(),m_scrollView->getContainer()->getPositionY()+_len));
		}
	}
	if (pItem->getParent()->getTag() != m_tabNum)
	{
		m_tabNum = pItem->getParent()->getTag();
		if (m_Frame)
		{
			m_Frame->setVisible(false);
			m_Frame = (CCSprite*)pItem->getParent()->getParent()->getChildByTag(0);
			m_Frame->setVisible(true);
		} 
		else
		{
			m_Frame = (CCSprite*)pItem->getParent()->getParent()->getChildByTag(0);
			m_Frame->setVisible(true);
		}
		ActivityInfoItem * pActivityInfoItem = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByIndex(m_tabNum-1); 
		short activityType = pActivityInfoItem->getActivityItemType(); 
		m_CurActivityType = activityType;
		//占时先这么做下 
		if(pActivityInfoItem->getActivityConfig()->m_nShowActivityBg > 0)
		{
			NFC_showNode(ActivityBG,m_pRootNode,true);
		}
		else
		{
			NFC_showNode(ActivityBG,m_pRootNode,false);
		}
		if (_ACTIVITY_FIRSTRECHGIFT_TYPE_ == activityType)
		{
			if (m_showWindow)
			{
				m_showWindow->Destroy();
			}
			if(m_nHideLastWindowEventId > 0)
			{
				EVENTSYSTEM->PushEvent(m_nHideLastWindowEventId);
			}
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_FIRSTRECHGIFTWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));		
			FIRSTRECHDATAHANDLER->ToServerInfoFirstRech();

		}
		else if (_ACTIVITY_VIPBAGREWARD_TYPE_ == activityType)
		{
			if (m_showWindow)
			{
				m_showWindow->Destroy();
			}
			if(m_nHideLastWindowEventId > 0)
			{
				EVENTSYSTEM->PushEvent(m_nHideLastWindowEventId);
			}

			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_VIPGIFTWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));		
			VIPGIFTACTIVITYHANDLER->ToServerInfoVipGift();
		}
		else
		{
			if (m_showWindow)
			{
				m_showWindow->Destroy();
			}
			if(m_nHideLastWindowEventId > 0)
			{
				EVENTSYSTEM->PushEvent(m_nHideLastWindowEventId);
			}
			if(_ACTIVITY_LEVELUPREWARD_TYPE_ == activityType)
			{  
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPREWARDACTIVITYWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
			   
			} 
			else if(_ACTIVITY_SPRING_TYPE_ == activityType)
			{
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{
			   	    EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_SPEING_,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}

			}
			else if(_ACTIVITY_GROWUPPLAN_TYPE_ == activityType)
			{
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_GROWUPPLANACTIVITYWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				
			}
			else if(_ACTIVITY_LOGINREWARD_TYPE_ == activityType)
			{
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOGINACTIVITYWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
			}
			else if(_ACTIVITY_EXCHANGEREWARD_TYPE_ == activityType)
			{ 	
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EXCHANGEACTIVITYWINDOW_,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				
			}
			else if(_ACTIVITY_LIANJIN_TYPE_ == activityType)
			{
				if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
				{
					EVENTSYSTEM->PushEvent(pActivityInfoItem->getActivityConfig()->m_nShowEventId,_to_event_param_(pActivityInfoItem->getActivityItemID()));
				}
				else
				{

				}
			}

			NFC_showCommunicationWating(true);
			C2SChioseActivityPacket packet(pActivityInfoItem->getActivityItemID());
			packet.Send();
		}
		if(pActivityInfoItem->getActivityConfig()->m_nUseLua > 0)
		{
			m_nHideLastWindowEventId = pActivityInfoItem->getActivityConfig()->m_nHideEventId;
			m_showWindow = NULL;
		}
		else
		{
			m_nHideLastWindowEventId = -1;
			m_showWindow = WINDOWMANAGER->GetWindowByType(pActivityInfoItem->getActivityConfig()->m_nActivityWindowID);
		}
		
	} 
}

void ActivityWindow::scrollViewDidScroll(CCScrollView* view)
{
	SetArrowState(view);
}

void ActivityWindow::SetArrowState(CCScrollView* view)
{
	if (view->getContentOffset().y >= 0)
	{
		if (!m_scrollflag || m_isFirstIn)
		{
			NFC_setNodeVisable(uiArrowMoveDown,m_pRootNode,false);
			m_scrollflag = true;
			m_isFirstIn = false;
			
		}
	}
	else if (view->getContentOffset().y <= (view->getContentSize().height-view->getViewSize().height)*-1)
	{
		if (!m_scrollflag || m_isFirstIn)
		{
			NFC_setNodeVisable(uiArrowMoveUp,m_pRootNode,false);
			m_scrollflag = true;
			m_isFirstIn = false;
		}
	}
	else
	{
		if (m_scrollflag || m_isFirstIn)
		{
			NFC_setNodeVisable(uiArrowMoveUp,m_pRootNode,true);
			NFC_setNodeVisable(uiArrowMoveDown,m_pRootNode,true);
			m_scrollflag = false;
			m_isFirstIn = false;
		}
	}
	std::map<short,ActivityInfoItem *> &  activityServerMap = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityRefMap();
	if (activityServerMap.size() == 3)
	{
		NFC_setNodeVisable(uiArrowMoveUp,m_pRootNode,false);
		NFC_setNodeVisable(uiArrowMoveDown,m_pRootNode,false);
	}
}

void ActivityWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ACTIVITYWINDOW_)
	{ 
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ACTIVITYWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_ACTIVITYWINDOW_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		OnUpdateTempleUI(paramList);
	}
	else if (iEventType == _TYPED_EVENT_DELETE_ACTIVITY_)
	{
		DeleteCurActivity();
	}
	else if (iEventType == _TYPED_EVENT_UPDATEEFFECT_ACTIVITY_)
	{
		OnUpdateEffectUI(paramList);
	}
}

void   ActivityWindow::OnUpdateEffectUI(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		int id = atoi(paramList.begin()->c_str());
		if (ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(id)->getActivityItemType() == m_CurActivityType)
		{
			std::map<int,CCSprite*>::iterator itbegin = m_MapCSpriteEffEct.find(id);
			if (itbegin != m_MapCSpriteEffEct.end())
			{
				if (itbegin->second)
				{
					itbegin->second->setVisible(false);
				}
			}
		}
	}
}

void ActivityWindow::OnUpdateTempleUI(std::list<std::string>& paramList)
{

}

void ActivityWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	//PushEvent(_TYPED_EVENT_UPDATE_ACTIVITYWINDOW_);
}

void ActivityWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{

	float tempHeight =m_scrollLayer->getContentSize().height- Interval;

	if (m_LayerList.empty() || m_Reroad)
	{
		m_Reroad = false;
		std::map<short,ActivityInfoItem *> &  activityServerMap = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityRefMap();
		std::map<short,ActivityInfoItem *>::iterator activity_iter = activityServerMap.begin();
		int  index = 0;
		while(activity_iter != activityServerMap.end())
		{  
			CCLayerColor* bg =CCLayerColor::create();
			//图标按钮
			CImmovableMenu* IconMenu = CImmovableMenu::create(kPRIORITYLOW3);
			std::string  iconFileName =  ResourceIDDataManager::get_instance2()->getDataByID(activity_iter->second->getActivityItemIconID());       
			CMenuItemSprite* pIcon = CMenuItemSprite::create(iconFileName.c_str(),iconFileName.c_str(),this, menu_selector(ActivityWindow::On_Chiose_Activity));
			pIcon->setAnchorPoint(ccp(0.5,0.5));
			pIcon->setTarget(this,menu_selector(ActivityWindow::On_SelectTab));
			IconMenu->setPosition(CCPointZero);
			IconMenu->addChild(pIcon);
			bg->addChild(IconMenu,0,index+1); 
			MaskNode* node=(MaskNode*)m_pRootNode->getChildByTag(Activity_Frame);
			const UIViewData & dd=node->GetViewData();
			CCSprite* pFrame = CCSprite::create();
			pFrame->setProperty("File",dd.filepath_);
			pFrame->setAnchorPoint(ccp(0.5,0.5));
			pFrame->setPosition(pIcon->getPosition());
			bg->addChild(pFrame,1,0);
			MaskNode *ttfnode = (MaskNode*)m_pRootNode->getChildByTag(Activity_NAMETTF);
			CCLabelTTF* pTtf = NFC_createLabelByViewData(bg,ttfnode->GetViewData());
			pTtf->setString(activity_iter->second->getActivityStrName().c_str());
			//首充领取特效
			if (activity_iter->second->getActivityItemType() == _ACTIVITY_FIRSTRECHGIFT_TYPE_)
			{
				//记录按钮信息
				m_RecharMenu = pIcon;
			} 
			if (activity_iter->second->getActivityOpen() != 0)
			{
				CCSprite* pEffect = NFC_getLoopFrameEffect(2061);
				bg->addChild(pEffect,1);
				int id = activity_iter->second->getActivityItemID();
				m_MapCSpriteEffEct.insert(std::map<int,CCSprite*>::value_type(activity_iter->second->getActivityItemID(),pEffect));

			}
			if (index!=0)
			{
				pFrame->setVisible(false);
			}
			else
			{
				m_Frame = pFrame;
			}
			bg->setContentSize(pIcon->getContentSize()); 
			m_LayerList.push_back(bg);
			tempHeight = tempHeight - pIcon->getContentSize().height - Interval_NULL; 
			index++;
			++activity_iter;
		}  

		float _hight = m_scrollLayer->getContentSize().height - tempHeight;
		if (!(_hight >m_scrollView->getViewSize().height))
		{
			_hight = m_scrollView->getViewSize().height;
		}
		m_scrollLayer->setContentSize(CCSizeMake(m_scrollView->getViewSize().width,_hight - Interval));
		m_scrollView->setContentSize(CCSizeMake(m_scrollView->getViewSize().width,_hight - Interval));
		m_scrollLayer->setPosition(ccp(0,m_scrollView->getViewSize().height-m_scrollLayer->getContentSize().height));

		std::vector<CCLayerColor*>::iterator itar = m_LayerList.begin();
		std::vector<CCLayerColor*>::iterator itar_end = m_LayerList.end();
		float _scrollTotalHight = m_scrollLayer->getContentSize().height - Interval;
		for (;itar!=itar_end;++itar)
		{
			(*itar)->setPosition(ccp(m_scrollView->getViewSize().width/2,_scrollTotalHight));
			m_scrollLayer->addChild((*itar),0);
			_scrollTotalHight = _scrollTotalHight - (*itar)->getContentSize().height - Interval_NULL;


		}
	}
	if (ActivityDataHandler::get_instance2()->getServerActivitysCount() >0)
		InitTab();
	//确保更新完事
	if (paramList.size() > 0)
	{
		//这是从VIP跳转到活动
		if (FIRSTRECHDATAHANDLER->m_isRechGift)
		{
			On_SelectTab(m_RecharMenu);
			FIRSTRECHDATAHANDLER->m_isRechGift = false;
		}
	}
	SetArrowState(m_scrollView);
}

