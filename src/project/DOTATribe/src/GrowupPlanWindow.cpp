//Name: GrowupPlanWindow
//Author: lvyunlong
//Func: Activity of growup plan window
//Maintainer:lvyunlong


#include "../include/GrowupPlanWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/EffectDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/ActivityDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/TimeSystem.h"

GrowupPlanWindow::GrowupPlanWindow()
	:m_pTableAttachment(NULL),
	m_CurWindowActiviId(0)
{
	m_WindowType   = _TYPED_WINDOW_ACTIVITYGROWUPPLAN_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

GrowupPlanWindow::~GrowupPlanWindow()
{

}


void GrowupPlanWindow::_initLayout()
{
	_initStr();
	_initControl();
	_initCell();
	_mapBtn();
}

void GrowupPlanWindow::_initStr()
{
	strGrowlevel = SysLangDataManager::get_instance2()->GetSysLangById(6065);
	strReachlevel = SysLangDataManager::get_instance2()->GetSysLangById(6066);
	strMoneynum = SysLangDataManager::get_instance2()->GetSysLangById(6067);
}

void GrowupPlanWindow::_initControl()
{	
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGROWUPPLANACTIVITYWINDOW,m_pRootNode);
}

void GrowupPlanWindow::_mapBtn()
{
	NFC_bindSelectorForBtn(udRECHGEBTN,m_pRootNode,this,menu_selector(GrowupPlanWindow::On_Click_RechgeBtn_Event));
	NFC_bindSelectorForBtn(udBUYBTN,m_pRootNode,this,menu_selector(GrowupPlanWindow::On_Click_BuyPlan_Event));
}

void GrowupPlanWindow::_initCell()
{
	CCNode* cell = NFC_getNode(udTABLECELL,m_pRootNode);
	m_szCellGift = cell->getContentSize();
}


bool  GrowupPlanWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_GROWUPPLANACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_GROWUPPLANACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_GROWUPPLANACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_BTNTEXT_GROWUPPLANACTIVITYWINDOW_, true);
	
	return IWindow::Init();
}

bool  GrowupPlanWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		_setTableView(); //设置TableView

		return true;
	} 
	while (false);

	return false;
}

void  GrowupPlanWindow::Tick()
{
	IWindow::Tick();
}

void  GrowupPlanWindow::Destroy()
{
	m_pTableAttachment = NULL;
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}

	IWindow::Destroy();
}

void  GrowupPlanWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_GROWUPPLANACTIVITYWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_GROWUPPLANACTIVITYWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_GROWUPPLANACTIVITYWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_BTNTEXT_GROWUPPLANACTIVITYWINDOW_)
	{
		OnUpdateBtnWindowEventHandler(paramList);
	}
}

void   GrowupPlanWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		m_CurWindowActiviId = atoi(paramList.begin()->c_str());
		GROWUPPLANDATAHANDLER->setGrowupPlanActiviId(m_CurWindowActiviId);
	}
	Show(true);
}

void  GrowupPlanWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void  GrowupPlanWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_refreshTableView(m_pTableAttachment);
	NFC_showCommunicationWating(false);

	if (GROWUPPLANDATAHANDLER->m_isBuyPlan == 0)
	{
		NFC_setEnabledForMenuItem(udBUYBTN,m_pRootNode,true);
	}
	else
	{
		NFC_setEnabledForMenuItem(udBUYBTN,m_pRootNode,false);
		NFC_setLabelString(udBUYTTF,m_pRootNode,SysLangDataManager::get_instance2()->GetSysLangById(6070).c_str());
	}
}

void  GrowupPlanWindow::OnUpdateBtnWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		std::list<std::string>::iterator it = paramList.begin();
		std::string strtemp = *it;
		int level = atoi(strtemp.c_str());
		int index = GROWUPPLANDATAHANDLER->ByLevelPlanRewardListIndex(level);
		if (index == -1)
		{
			return;
		}
		cocos2d::extension::CCTableViewCell* pNode = m_pTableAttachment->cellAtIndex(index);
		if (pNode)
		{
			//设置按钮不可按
			NFC_setEnabledForMenuItem(_PLAN_GETBTN,pNode,false);
			//隐藏特效
			NFC_setNodeVisable(_PLAN_EFFECTBTN,pNode,false);
			//改文字
			NFC_setLabelString(_PLAN_GETTFF,pNode,SysLangDataManager::get_instance2()->GetSysLangById(6060).c_str());
		}
	}
}

void GrowupPlanWindow::_setTableView()
{
	if (m_pTableAttachment)
		m_pTableAttachment->removeAllChildrenWithCleanup(true);

	m_pTableAttachment = (CCTableView*)m_pRootNode->getChildByTag(udTABLE);
	m_pTableAttachment->setDataSource(this);
	m_pTableAttachment->setDelegate(this);
	m_pTableAttachment->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTableAttachment->setTouchEnabled(true);
	m_pTableAttachment->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

cocos2d::CCSize GrowupPlanWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCellGift;
}

cocos2d::extension::CCTableViewCell* GrowupPlanWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){

	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}

void GrowupPlanWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGROWUPPLANAREWARDCELL,cell);
}

void GrowupPlanWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	GrowupRewardData* data = GROWUPPLANDATAHANDLER->m_GrowupRewardVector.at(idx);
	if (data == NULL)
		return;
	//按钮特效隐藏
	NFC_setNodeVisable(_PLAN_EFFECTBTN,cell,false);
	char buff[1024] = {0};
	//级成长基金
	CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(_PLAN_LEVELGROWTTF,cell);
	sprintf(buff,strGrowlevel.c_str(),data->getRewardLevel());
	ttf->setString(buff);
	//达到级可领取
	ttf = (CCLabelTTF*)NFC_getNode(_PLAN_REACHLEVELTTF,cell);
	memset(buff,0,sizeof(buff));
	sprintf(buff,strReachlevel.c_str(),data->getRewardLevel());
	ttf->setString(buff);
	//奖励设置
	PRewardItemNode pRewardItemNode = data->getRewardVector().at(0);
	if(pRewardItemNode)
	{
		//多少钱
		ttf = (CCLabelTTF*)NFC_getNode(_PLAN_GETMONEYTTF,cell);
		memset(buff,0,sizeof(buff));
		sprintf(buff,strMoneynum.c_str(),pRewardItemNode->rewardItemCount);
		ttf->setString(buff);

		//绑定事件 
		DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(_PLAN_DTREWARD);
		dd->setIDX(idx);
		dd->setTarget(this,menu_selector(GrowupPlanWindow::On_Click_Reward_Tips_Event));

		switch (pRewardItemNode->rewardItemType)
		{
		case  kDT_AWARD_OBJECT:
			{     
				dd->ChangeObject(pRewardItemNode->rewardQuality,pRewardItemNode->rewardIconID,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);
				if(pRewardItemNode->rewardCatagory == kBAGSKIN)
				{
					dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
				}
				else
				{
					dd->setContentScale(1);
				}
				break;
			}
		case   kDT_AWARD_MONEY:
			{    
				int quality=_GOLD_QUALITY_RESID_;
				dd->ChangeObject(quality,_GOLD_ICON_RESID_,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);

			}
			break;
		case  kDT_AWARD_EXP:
			{
				int quality=_EXP_QUALITY_RESID_;
				dd->ChangeObject(quality,_EXP_ICON_RESID_,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);

			}
			break;
		case  kDT_AWARD_DIAMOND:
			{
				int quality=_DIAMOND_QUALITY_RESID_;
				dd->ChangeObject(quality,_DIAMOND_ICON_RESID_,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);

			}
			break;
		case kDT_AWARD_PRESTIGE:
			{
				int quality=_PREGIST_QUALITY_RESID_;
				dd->ChangeObject(quality,_PREGIST_ICON_RESID_,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);	
			}
			break;
		case kDT_AWARD_POWER:
			{
				int quality=_POWER_QUALITY_RESID_;
				dd->ChangeObject(quality,_POWER_ICON_RESID_,pRewardItemNode->rewardItemCount);
				dd->setEnabled(true);
			}
			break;
		default:
			break;
		}
	}
	//绑定按钮
	NFC_bindSelectotForCellBtn(_PLAN_GETBTN,idx,cell,this,menu_selector(GrowupPlanWindow::On_Click_GetReward_Event));
	if (data->getHasReward())
	{
		NFC_setEnabledForMenuItem(_PLAN_GETBTN,cell,false);
		NFC_setLabelString(_PLAN_GETTFF,cell,SysLangDataManager::get_instance2()->GetSysLangById(6060).c_str());
	}
	else
	{
		NFC_setLabelString(_PLAN_GETTFF,cell,SysLangDataManager::get_instance2()->GetSysLangById(6047).c_str());
		if (ROLEINFODATAHANDLER->m_pRIData->level_>=data->getRewardLevel())
		{
			NFC_setNodeVisable(_PLAN_EFFECTBTN,cell,true);
			NFC_resumeActionsForSceneSprite(_PLAN_EFFECTBTN,cell);
			NFC_setEnabledForMenuItem(_PLAN_GETBTN,cell,true);
		}
		else
		{
			NFC_setEnabledForMenuItem(_PLAN_GETBTN,cell,false);
		}
	}
}


unsigned int GrowupPlanWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return GROWUPPLANDATAHANDLER->m_GrowupRewardVector.size();
}

void GrowupPlanWindow::On_Click_RechgeBtn_Event(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_ACTIVITYWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
}

void GrowupPlanWindow::On_Click_BuyPlan_Event(cocos2d::CCObject* pSender)
{
	GROWUPPLANDATAHANDLER->ToServerBuyGrowPlan();
}

void GrowupPlanWindow::On_Click_GetReward_Event(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("Growup_Reward",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if (pMenuItemSprite)
	{
		int cellIndex = pMenuItemSprite->getIDX();
		GrowupRewardData* data = GROWUPPLANDATAHANDLER->m_GrowupRewardVector.at(cellIndex);
		if (data == NULL)
			return;
		GROWUPPLANDATAHANDLER->ToServerGetPlanReward(data->getRewardLevel());
	}
}

void GrowupPlanWindow::On_Click_Reward_Tips_Event(cocos2d::CCObject* pSender)
{
	
}