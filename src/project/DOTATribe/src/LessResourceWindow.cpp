// Name :		LessResourceWindow.h
// Function:	资源不足窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/LessResourceWindow.h"
#include "../include/EngineSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/LessResourceDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/AthleticsProcedure.h"
#include "../include/CPublicVarReader.h"
#include "../include/C2SArenaInfoPacket.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/LessResourcePacket.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>

using  namespace  cocos2d;

#define  Less_Energy_Image		682
#define  Less_Town_Image		685
#define  Less_Athletic_Image	688
#define  Less_Hunt_Image		691
#define  Less_Relic_Image		694
LessResourceWindow::LessResourceWindow()
{
	m_WindowType = _TYPEF_WINDOW_LessResourceWindow_;

}

LessResourceWindow::~LessResourceWindow()
{
}

bool LessResourceWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LESSRESOURCEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LESSRESOURCEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LESSRESOURCEWINDOW_,true);

	return IWindow::Init();
}

bool LessResourceWindow::Load()
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

void LessResourceWindow::Tick()
{
	IWindow::Tick();
}

void LessResourceWindow::Destroy()
{
	IWindow::Destroy();
}
void LessResourceWindow::InitLayer()
{

	
	m_pRoot  = CCLayer::create();
	m_pRootNode->addChild(m_pRoot,1);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLESSRESOURCEWINDOW,m_pRoot);
	CPriorityLayerColor* pTempNode = (CPriorityLayerColor*)m_pRoot->getChildByTag(LessResource_Mark_Layer);
	pTempNode->removeFromParent();
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate((cocos2d::CCTouchDelegate *)pTempNode);
	m_pRootNode->addChild(pTempNode);


	CCMenu* ptemp = (CCMenu*)m_pRoot->getChildByTag(LessResource_Close_Button);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(LessResourceWindow::On_Close));

	ptemp = (CCMenu*)m_pRoot->getChildByTag(LessResource_Other_Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(LessResourceWindow::On_SingleClick));

	ptemp = (CCMenu*)m_pRoot->getChildByTag(LessResource_Sure_Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(LessResourceWindow::On_SureClick));

	for (int i=LessResource_Small_Button_Up; i<=LessResource_Small_Button_Right;i++)
	{
		ptemp = (CCMenu*)m_pRoot->getChildByTag(i);
		ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		ptempItem->setTarget(this,menu_selector(LessResourceWindow::On_ItemClick));
	}

	pBigLayer = (CPriorityLayerColor*)m_pRoot->getChildByTag(LessResource_Mark_Layer2);
	pBigLayer->setDelegate(this);
	pSmallLayer =(CPriorityLayerColor*)m_pRoot->getChildByTag(LessResource_Mark_Layer2_Smale);
	for (int i=LessResource_BG_Small;i<=LessResource_Small_Button_Right;i++)
	{
		CCNode* pTempNode = m_pRoot->getChildByTag(i);
		pTempNode->removeFromParent();
		pTempNode->setParent(NULL);
		pSmallLayer->addChild(pTempNode,0,i);
	}
	pBigLayer->setVisible(false);
	pSmallLayer->setVisible(false);
	OnUpdateInfo();
}
void LessResourceWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_LESSRESOURCEWINDOW_);	
}
void LessResourceWindow::On_SingleClick(cocos2d::CCObject* pSender)
{
	if (pBigLayer->isVisible())
	{
		pBigLayer->setVisible(false);
		pSmallLayer->setVisible(false);
	}
	else
	{
		pBigLayer->setVisible(true);
		pSmallLayer->setVisible(true);
		NFC_Action_scaleIn(pSmallLayer);
	}
	CCLOG("On_SingleClick");
}
void LessResourceWindow::On_SureClick(cocos2d::CCObject* pSender)
{
	NFC_showCommunicationWating(true);
	C2SChioseLessResourcePacket pack;
	pack.Send();
	CCLOG("On_SureClick");

}

void LessResourceWindow::On_ItemClick(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* pItem =(CMenuItemSprite*)pSender;

	GotoOther(LessResourceDataHandler::get_instance2()->DoingDataList[pItem->getParent()->getTag()-LessResource_Small_Button_Up]);


	CCLOG("On_ItemClick %d",pItem->getParent()->getTag());
}
void LessResourceWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LESSRESOURCEWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LESSRESOURCEWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LESSRESOURCEWINDOW_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
}
void LessResourceWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	if(m_pRootNode->isVisible())
		return;
	Show(true);
}
void LessResourceWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{

}
void LessResourceWindow::OnUpdateInfo()
{
	//标题
	CCLabelTTF* pTitle = (CCLabelTTF*)m_pRoot->getChildByTag(LessResource_Title);
	char _title[128]="";
	sprintf(_title,SysLangDataManager::get_instance2()->GetSysLangById(784).c_str(),GetTypeString(LessResourceDataHandler::get_instance2()->type).c_str());
	pTitle->setString(_title);

	//第一行文字
	CCLabelTTF* pDesc_UP = (CCLabelTTF*)m_pRoot->getChildByTag(LessResource_Desc_UP);
	pDesc_UP->setString(LessResourceDataHandler::get_instance2()->description.c_str());
	
	CCSprite* pItemBG = (CCSprite*)m_pRoot->getChildByTag(LessResource_Item_BG);
	if (!LessResourceDataHandler::get_instance2()->hasNext)
		pItemBG->setVisible(false);
	else
	{
		pItemBG->setProperty("File",varConfig::getCardBGFilePath(LessResourceDataHandler::get_instance2()->quality));
		pItemBG->setVisible(true);
	}
	
	CCSprite* pItem = (CCSprite*)m_pRoot->getChildByTag(LessResource_Item);
	if (!LessResourceDataHandler::get_instance2()->hasNext)
		pItem->setVisible(false);
	else
	{
		pItem->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(LessResourceDataHandler::get_instance2()->iconId).c_str());
		pItem->setVisible(true);
	}

	CCLabelTTF* pItem_num = (CCLabelTTF*)m_pRoot->getChildByTag(LessResource_Item_Num);
	if (LessResourceDataHandler::get_instance2()->leftCount == 0 || !LessResourceDataHandler::get_instance2()->hasNext)
		pItem_num->setVisible(false);
	else
	{
		char _itemnum[128]="";
		sprintf(_itemnum,"%d",LessResourceDataHandler::get_instance2()->leftCount);
		pItem_num->setString(_itemnum);
		pItem_num->setVisible(true);
	}

	//按钮
	for (int i=0;i<LessResourceDataHandler::get_instance2()->DoingDataList.size();i++)
	{
		DoingData* pData = LessResourceDataHandler::get_instance2()->DoingDataList[i];
		CCMenu* ptemp = (CCMenu*)pSmallLayer->getChildByTag(i+LessResource_Small_Button_Up);
		CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		NFC_setNormalImageForMenuItem(ptempItem,ResourceIDDataManager::get_instance2()->getDataByID(GetDoingIcon(pData->id)));
		NFC_setSelectedImageForMenuItem(ptempItem,ResourceIDDataManager::get_instance2()->getDataByID(GetDoingIcon(pData->id)+1));
		NFC_setDisabledImageForMenuItem(ptempItem,ResourceIDDataManager::get_instance2()->getDataByID(GetDoingIcon(pData->id)+2));
		if (pData->isOpen == 0)
			ptempItem->setEnabled(false);
	}
}
void LessResourceWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{

}

std::string LessResourceWindow::GetTypeString(int type)
{
	switch(type)
	{
	case LessResource_Less_Energy:
		return SysLangDataManager::get_instance2()->GetSysLangById(785);
	case LessResource_Less_Town:
		return SysLangDataManager::get_instance2()->GetSysLangById(786);
	case LessResource_Less_Athletic:
		return SysLangDataManager::get_instance2()->GetSysLangById(787);
	case LessResource_Less_Hunt:
		return SysLangDataManager::get_instance2()->GetSysLangById(788);
	case LessResource_Less_Relic:
		return SysLangDataManager::get_instance2()->GetSysLangById(789);
	default:
		return "";
	}
	
}

int  LessResourceWindow::GetDoingIcon(int type)
{
	switch(type)
	{
		case LessResource_Less_Energy:
			return Less_Energy_Image;
		case LessResource_Less_Town:
			return Less_Town_Image;
		case LessResource_Less_Athletic:
			return Less_Athletic_Image;
		case LessResource_Less_Hunt:
			return Less_Hunt_Image;
		case LessResource_Less_Relic:
			return Less_Relic_Image;
		default:
			return -1;
	}
}
void LessResourceWindow::GotoOther(DoingData* pData)
{
	HideCurWindow();
	switch(pData->id)
	{
		case	LessResource_Less_Energy:
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow();
				MissionDataHandler::get_instance2()->setCurMissionID(MissionDataHandler::get_instance2()->getWorldMapStateNum()); 
				DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
				DOTATribeApp::get_instance2()->m_pHomeProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
			}
			break;
		case	LessResource_Less_Town:
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow();
				if (DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType() == IProcedure::_TYPED_HOME_PROCEDURE_)
					PushEvent(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
				else
					DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);

				CLIMBTOWERDATAHANDLER->ToServerEnterTower();
			}
			break;
		case	LessResource_Less_Athletic:
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow();
				if (DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType() == IProcedure::_TYPED_ARENA_PROCEDURE_)
				{
					PushEvent(_TYPEF_EVENT_SHOW_ARENAWINDOW_);
				}
				else
				{
					C2SArenaInfoPacket  requestArenaInfo;
					requestArenaInfo.Send();	
				}

			}
			break;
		case	LessResource_Less_Hunt:
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow();
				if (DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType() == IProcedure::_TYPED_HOME_PROCEDURE_)
					PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
				else
					DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
			}
			break;
		case	LessResource_Less_Relic:
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow();
				if (DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType() == IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_)
				{
					PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
				}
				else
				{
					DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->SetBackWindow(_TYPED_EVENT_SHOW_HOMEWINDOW_);
					DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_));
				}
			}
			break;
		default:
			break;
	}
}
void LessResourceWindow::HideCurWindow()
{
	switch(LessResourceDataHandler::get_instance2()->type)
	{
		case LessResource_Less_Energy:
			break;
		case LessResource_Less_Town:
			PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
			break;
		case LessResource_Less_Athletic:
			break;
		case LessResource_Less_Hunt:
			PushEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_);
			break;
		case LessResource_Less_Relic:
			break;
		default:
			break;
	}
}