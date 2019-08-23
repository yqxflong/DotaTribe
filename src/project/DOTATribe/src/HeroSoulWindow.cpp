#include  "../include/HeroSoulWindow.h"
#include  <cocos2d.h>
#include  "cocos-ext.h" 
#include  "../include/EventTyper.h"
#include  "../include/TimeSystem.h"
#include  "../include/EventSystem.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/VariableSystem.h"
#include  "../include/SysLangDataManager.h"
#include  "../include/UIViewDataManger.h"
#include  "../include/CPublicVarReader.h"
#include  "../include/NFControlsManager.h"
#include  "../include/NFAnimationController.h"
#include  "../include/CMenuItemSprite.h"
#include  "../include/HeroIllustratedDataHandler.h"
#include  "../include/RoleHeroSkinsDataHandler.h"
#include  "../include/RoleShapeDataManager.h"
#include  "../include/BagOtherObjectHandler.h"
#include  "../include/NetObjectTipsDataHandler.h"
#include  "../include/HeroSoulPacket.h"
#include  "../include/DTHeroIcon.h"
#include  "../include/DTAwardBoard.h"
#include  "../include/GrapStarsProgress.h"
#include  "../include/PESWindow.h"
#include "../include/RoleInfoDataHandler.h"
 

#define   ALREADY_MAX_SHAPLE_LEVEL_TID	  7033	
#define   NEED_HIGHT_SHAPLE_HERO_TID	  7034	
#define   ITEM_LESS_TIPS_TID			  7032		
#define   ADVISE_CHALLENEGE_LEVEL_TID	  7039
#define   NEED_ITEMS_NUMBER_FORMAT_TID	  134

#define   OBJECT_TIPS_(index)     if(m_pHeroSoulInfoData&&index<m_pHeroSoulInfoData->getNeetItemVector().size()) \
	{ \
	NeedItemNode * pNeedItemNode = m_pHeroSoulInfoData->getNeetItemVector().at(index); \
	if(pNeedItemNode&&pNeedItemNode->getItemType()==0) \
		{  \
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pNeedItemNode->getItemTemplateID(), _TYPED_WINDOW_HEROSOULWINDOW_);\
		} \
	}
 

 
 
HeroSoulWindow::HeroSoulWindow()
{
	m_SubType = -1;
	m_WindowType = _TYPED_WINDOW_HEROSOULWINDOW_;
	m_bModelWindow = false;
	m_bIsActiveHeroSoulType = false;
	m_pHeroSoulInfoData = NULL;
	m_isNeedShowActivieEffect = false; 
	m_BackWindow = -1;
	m_BackTab = - 1;
	m_BackView = -1;
}

HeroSoulWindow::~HeroSoulWindow()
{ 

}


bool HeroSoulWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HEROSOULWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_HEROSOULWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_HEROSOULWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	return true;
}

bool  HeroSoulWindow::Load()
{
	do
	{
		if (!IWindow::Load())
			break;
		InitUILayOut();
	} 
	while (false);
	return false;
}

void   HeroSoulWindow::Tick()
{
	IWindow::Tick();
}

 void    HeroSoulWindow::Destroy()
 {
	 m_isNeedShowActivieEffect = false;
	 DetachMemData();
	 IWindow::Destroy();
 }

void    HeroSoulWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_HEROSOULWINDOW_ )
	{ 
		NFC_showCommunicationWating(false);
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_HEROSOULWINDOW_ )
	{ 
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_HEROSOULWINDOW_)
	{ 
		m_isNeedShowActivieEffect = true;
		NFC_showCommunicationWating(false);
		ShowWindowWithType();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		UpdateDiamondAndGold();
	}
}

void    HeroSoulWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{  
	list<string>::iterator it = paramList.begin();
	string tmp;
	//第一个参数为子界面
	if (paramList.size() > 0){
		tmp = *it++;
		m_BackTab = atoi(tmp.c_str());
		if (paramList.size() > 1){
			tmp = *it++;
			m_BackView = atoi(tmp.c_str());
		}
		if (paramList.size() > 2){
			tmp = *it++;
			m_BackWindow = atoi(tmp.c_str());
		}
	}
	//绑定内存数据 初始化
	AttachMemData();
	ShowWindowWithType();
	Show(true);
}

void   HeroSoulWindow::CommonBtnSelectorHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{ 
		switch (pMenuItemSprite->getIDX())
		{
		case _UI_HELP_BTN_:
			{  
				break;
			}
		case _UI_CLOSE_BTN_:
			{
				PushEvent(_TYPED_EVENT_HIDE_HEROSOULWINDOW_);
				if(HeroSoulDataHandler::get_instance2()->getBackWindowType() == IWindow::_TYPED_WINDOW_HEROBAR_)
				{ 
					EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_,_to_event_param_(IWindow::_TYPED_WINDOW_HEROBAR_));	
					//break;
				}
				else if (m_BackWindow != -1)
				{
					EventSystem::get_instance2()->PushEvent(m_BackWindow, _to_event_param_(m_BackTab), _to_event_param_(m_BackView));
					m_BackWindow = -1;
					break;
				}
				else
				{
					EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_, _to_event_param_(IWindow::_TYPED_WINDOW_TEAMINFOWINDOW_));
					break;
				}
				break;
			}
		case  _UI_CHALLENGE_BTN_:
			{
				C2SChallengeHeroSoul challengeHeroSoul(m_pHeroSoulInfoData->getRoBotHeroID());
				challengeHeroSoul.Send();
				break;
			}
		case _UI_ACTIVE_ITEM_1_:
			{
				OBJECT_TIPS_(0)
				break;
			}
		case _UI_ACTIVE_ITEM_2_:
			{
				OBJECT_TIPS_(1)
				break;
			}
		case _UI_ACTIVE_ITEM_3_:
			{
				OBJECT_TIPS_(2)
				break;
			}
		case _UI_ACTIVE_ITEM_4_:
			{
				OBJECT_TIPS_(3)
				break;
			}
		case _UI_ACTIVE_ACTIVE_BTN_:
			{ 
				BTN_INTERVAL("BTN_CHALLENGE_HEROSOUL",_COMMON_BTN_CLICK_INTERVAL_SMALL)
				IByte  canActivityHeroSoulValue = m_pHeroSoulInfoData->getCanActiveHeroSoul();
				if(canActivityHeroSoulValue == 0)
				{
					SendActiveHeroSoul();
				}
				else if (canActivityHeroSoulValue == 1)
				{ 
					//满级提示 
					NFC_showMessageBoxSingle(kDEFAULT,SysLangDataManager::get_instance2()->GetSysLangById(ALREADY_MAX_SHAPLE_LEVEL_TID));
				}
				else if (canActivityHeroSoulValue == 2)
				{  
					//需要进阶
					NFC_showMessageBoxSingle(kDEFAULT,SysLangDataManager::get_instance2()->GetSysLangById(NEED_HIGHT_SHAPLE_HERO_TID));
				}
				else if(canActivityHeroSoulValue == 3)
				{ 
					//道具不足
					NFC_showMessageBoxSingle(kDEFAULT,SysLangDataManager::get_instance2()->GetSysLangById(ITEM_LESS_TIPS_TID));
				}
				break;
			}
		case  _UI_ACTIVE_RIGHTNOW_USE_BTN_:
			{ 
				PushEvent(_TYPED_EVENT_HIDE_HEROSOULWINDOW_);
				if (m_BackWindow != -1)
				{
					EventSystem::get_instance2()->PushEvent(m_BackWindow, _to_event_param_(m_BackTab), _to_event_param_(m_BackView));
					m_BackWindow = -1;
				}
				else
				{
					EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1),_to_event_param_(PESWindow::LOAD_SOUL_VIEW));
				}
				break;
			}
		default:
			break;
		}
	}
}
 
void    HeroSoulWindow::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	switch(eventType)
	{
	case _Animation_Timer_Triger_Event_:
		{
			//播放特效2
			cocos2d::CCSprite * pStartEffect = NFC_getUnLoopFrameEffect(2065);
			GrapStarsProgress * pGrapStarsProgress = (GrapStarsProgress *)(m_pRootNode->getChildByTag(_UI_ACTIVE_STATS_));
			IByte curLevel = m_pHeroSoulInfoData->getHeroSoulLevel();   
			pStartEffect->setPosition(ccp(pGrapStarsProgress->getPositionX()+22+(curLevel-1)*40,pGrapStarsProgress->getPositionY()+22));
			m_pRootNode->addChild(pStartEffect,100);
			break;
		}
	case _Animation_Timer_Triger_Event_02_:
		{
			//更新星星
			GrapStarsProgress * pGrapStarProgress = (GrapStarsProgress *)m_pRootNode->getChildByTag(_UI_ACTIVE_STATS_);
			pGrapStarProgress->setStars(m_pHeroSoulInfoData->getHeroSoulMaxLevel(),m_pHeroSoulInfoData->getHeroSoulLevel());
			break;
		} 
	case _Animation_Effect_Finish_Event_:
		{
			animationNode->removeFromParentAndCleanup(true);
			break;
		}
	default: 
		break;
	} 
}

//////////////////////////////////////////////////////////////////////////
  
void    HeroSoulWindow::InitUILayOut()
{ 
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROSOULWINDOW,m_pRootNode);
	BindSelectorForBtn();

}
void    HeroSoulWindow::BindSelectorForBtn()
{ 
	NFC_bindSelectorForBtn(_UI_CLOSE_BTN_,m_pRootNode,this,menu_selector(HeroSoulWindow::CommonBtnSelectorHandler));

}
void    HeroSoulWindow::AttachMemData()
{
	 m_pHeroSoulInfoData = HeroSoulDataHandler::get_instance2()->getHeroSoleInfoData();
	 m_bIsActiveHeroSoulType = m_pHeroSoulInfoData->getIsWinHeroSoul();
	   
}
void    HeroSoulWindow::DetachMemData()
{ 
} 

void   HeroSoulWindow::DispatchUpdateEventHandle(int eventType)
{  
}
  

void    HeroSoulWindow::ShowWindowWithType()
{
	//显示激活战魂窗口
	NFC_setNodeVisable(_UI_TITLE_BG_,m_pRootNode,true);
	NFC_setNodeVisable(_UI_TITLE_LABEL_,m_pRootNode,true); 

	for(int uiIndex = _UI_CHALLENEGE_LABEL_;uiIndex <= _UI_CHALLENGE_NEED_IMAGE_; uiIndex++)
	{
		//to do
		NFC_setNodeVisable(uiIndex,m_pRootNode,!m_bIsActiveHeroSoulType);
		//to do 
	} 
	for(int uiIndex = _UI_ACTIVE_UP_BG_ ; uiIndex <= _UI_ACTIVE_ACTIVE_LABEL_; uiIndex++)
	{
		NFC_setNodeVisable(uiIndex,m_pRootNode,m_bIsActiveHeroSoulType);
		//to do 
	}
	if(m_bIsActiveHeroSoulType)
	{
		InitHeroSoulActiveView();
	}
	else
	{
		InitHeroSoulChallengeView();
	}

}

void    HeroSoulWindow::InitHeroSoulChallengeView()
{
	NFC_bindSelectorForBtn(_UI_CHALLENGE_BTN_,m_pRootNode,this,menu_selector(HeroSoulWindow::CommonBtnSelectorHandler)); 
	 
	cocos2d::extension::CCSkeletonAnimation * pCCSkeletonAnimation =(cocos2d::extension::CCSkeletonAnimation *)m_pRootNode->getChildByTag(_UI_ROLE_NODE_);
	if(pCCSkeletonAnimation)
	{
		pCCSkeletonAnimation->removeFromParentAndCleanup(true); 
	}
	int challengeRoleShapeID = RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(m_pHeroSoulInfoData->getRoBotHeroID())->getHeroShapeID();
	RoleShapeData * pRoleShapeData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(challengeRoleShapeID);
	pCCSkeletonAnimation = cocos2d::extension::CCSkeletonAnimation::createWithFile(pRoleShapeData->mShapeAnimationFileDaiJi,pRoleShapeData->mShapeAnimationImage);
	cocos2d::CCNode * pConfigNode = m_pRootNode->getChildByTag(_UI_ROLE_CONFIG_NODE_);
	pCCSkeletonAnimation->setAnchorPoint(pConfigNode->getAnchorPoint());
	pCCSkeletonAnimation->setPosition(pConfigNode->getPosition());	 
	m_pRootNode->addChild(pCCSkeletonAnimation,pConfigNode->getZOrder(),_UI_ROLE_NODE_);
	pCCSkeletonAnimation->setAnimation("DaiJi",true);
	NFC_setLabelStringInt(_UI_CHALLENGE_COUNT_VALUE_,m_pRootNode,m_pHeroSoulInfoData->getLeftChallenegtCount(),413,true);
	NFC_setLabelStringInt(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,m_pHeroSoulInfoData->getConsumeCost(),true); 

	//设置建议挑战等级
	NFC_setLabelStringInt(_UI_ADVISE_CHALLENGE_LEVEL_,m_pRootNode,m_pHeroSoulInfoData->getAdviseChallenegeLevel(),ADVISE_CHALLENEGE_LEVEL_TID,true);
 	 
	if(m_pHeroSoulInfoData->getLeftChallenegtCount()==0)
	{
		NFC_setNodeVisable(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,false); 
		NFC_setNodeVisable(_UI_CHALLENGE_NEED_IMAGE_,m_pRootNode,false);
		NFC_setMenuEnable(_UI_CHALLENGE_BTN_,m_pRootNode,false);
	}
	else
	{
		UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kHEROSOULWINDOW);
		if(m_pHeroSoulInfoData->getConsumeType() == 1)
		{ 
			if(RoleInfoDataHandler::get_instance2()->m_pRIData->money_>=m_pHeroSoulInfoData->getConsumeCost())
			{
				NFC_setMenuEnable(_UI_CHALLENGE_BTN_,m_pRootNode,true);
				//显示普通文字
				NFC_setLabelByFontID(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,UIViewDataManager::get_instance2()->getControlDataByID(_UI_CHALLENGE_NEED_COUNT_)->m_nFontStyleID);
			}
			else
			{
				NFC_setMenuEnable(_UI_CHALLENGE_BTN_,m_pRootNode,false);
				//显示特殊红色文字
			   NFC_setLabelByFontID(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,(int)UIViewDataManager::get_instance2()->getControlDataByID(_UI_CHALLENGE_NEED_COUNT_)->width_); 
			} 
			NFC_setPicForCCSprite(_UI_CHALLENGE_NEED_IMAGE_,m_pRootNode,ResourceIDDataManager::get_instance2()->getDataByID(_GOLD_ICON_RESID_),true);
		}
		else if(m_pHeroSoulInfoData->getConsumeType() == 3)
		{
			if(RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_>=m_pHeroSoulInfoData->getConsumeCost())
			{
				NFC_setMenuEnable(_UI_CHALLENGE_BTN_,m_pRootNode,true);
				NFC_setLabelByFontID(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,UIViewDataManager::get_instance2()->getControlDataByID(_UI_CHALLENGE_NEED_COUNT_)->m_nFontStyleID);
			}
			else
			{
				NFC_setMenuEnable(_UI_CHALLENGE_BTN_,m_pRootNode,false);
				NFC_setLabelByFontID(_UI_CHALLENGE_NEED_COUNT_,m_pRootNode,(int)UIViewDataManager::get_instance2()->getControlDataByID(_UI_CHALLENGE_NEED_COUNT_)->width_); 
			} 
			NFC_setPicForCCSprite(_UI_CHALLENGE_NEED_IMAGE_,m_pRootNode,ResourceIDDataManager::get_instance2()->getDataByID(_DIAMOND_ICON_RESID_),true);
		} 
	}
	UpdateDiamondAndGold();
}

void    HeroSoulWindow::InitHeroSoulActiveView()
{
	if(m_pHeroSoulInfoData&&m_pHeroSoulInfoData->getHeroSoulLevel()>0)
	{ 
		NFC_setMenuEnable(_UI_ACTIVE_RIGHTNOW_USE_BTN_,m_pRootNode,true);
	}
	else
	{ 
		NFC_setMenuEnable(_UI_ACTIVE_RIGHTNOW_USE_BTN_,m_pRootNode,false);
	}

	cocos2d::extension::CCSkeletonAnimation * pCCSkeletonAnimation =(cocos2d::extension::CCSkeletonAnimation *)m_pRootNode->getChildByTag(_UI_ROLE_NODE_);
	if(pCCSkeletonAnimation)
	{
		pCCSkeletonAnimation->removeFromParentAndCleanup(true);
	}
	//设置头像
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *)m_pRootNode->getChildByTag(_UI_ACTIVE_HERO_ICON_);
	pDTHeroIcon->setHeroIconID(m_pHeroSoulInfoData->getHeroIconID());

	if(m_isNeedShowActivieEffect)
	{
		m_isNeedShowActivieEffect = false;
		OnPlayActiveEffect();
	}
	else
	{
		//设置等级
		GrapStarsProgress * pGrapStarProgress = (GrapStarsProgress *)m_pRootNode->getChildByTag(_UI_ACTIVE_STATS_);
		pGrapStarProgress->setStars(m_pHeroSoulInfoData->getHeroSoulMaxLevel(),m_pHeroSoulInfoData->getHeroSoulLevel());
	} 
	//设置天赋
	NFC_setLabelString(_UI_ACTIVE_TALENT_VALUE_,m_pRootNode,m_pHeroSoulInfoData->getHeroTalentName(),true);
	//设置属性
	NFC_setLabelString(_UI_ACTIVE_ATRIBUTE_VALUE_,m_pRootNode,m_pHeroSoulInfoData->getHeroAtributeName(),true);
	//绑定前往
	NFC_bindSelectorForBtn(_UI_ACTIVE_RIGHTNOW_USE_BTN_,m_pRootNode,this,menu_selector(HeroSoulWindow::CommonBtnSelectorHandler));
	//显示道具  

	if(m_pHeroSoulInfoData->getCanActiveHeroSoul()== _ACTIVE_MSG_FULL_LEVEL_)
	{
		//已经满级  
		for(int uiIndex = _UI_ACTIVE_ADVANCE_LABEL_;uiIndex<=_UI_ACTIVE_ACTIVE_LABEL_;uiIndex++)
		{
			NFC_setNodeVisable(uiIndex,m_pRootNode,false);
		} 
		NFC_setNodeVisable(_UI_ACTIVE_FULLLEVEL_LABEL_,m_pRootNode,true);
	}
	else
	{ 
		NFC_setNodeVisable(_UI_ACTIVE_FULLLEVEL_LABEL_,m_pRootNode,false);
		int  ItemIndexArray[] ={_UI_ACTIVE_ITEM_1_,_UI_ACTIVE_ITEM_2_,_UI_ACTIVE_ITEM_3_,_UI_ACTIVE_ITEM_4_};
		int  ItemValueArray[] ={_UI_ACTIVE_ITEM_1_VALUE_,_UI_ACTIVE_ITEM_2_VALUE_,_UI_ACTIVE_ITEM_3_VALUE_,_UI_ACTIVE_ITEM_4_VALUE_};
		size_t ItemsCount = m_pHeroSoulInfoData->getNeetItemVector().size();
		COMMON_BEIGIN_ARRAY(int,4)
			if(index<(int)ItemsCount)
			{
				ShowNeedItemICON(ItemIndexArray[index],m_pHeroSoulInfoData->getNeetItemVector().at(index));
				ShowNeedItemValue(ItemValueArray[index],m_pHeroSoulInfoData->getNeetItemVector().at(index));
			}
			else
			{
				NFC_setNodeVisable(ItemIndexArray[index],m_pRootNode,false);
				NFC_setNodeVisable(ItemValueArray[index],m_pRootNode,false);
			}
			COMMON_END_ARRAY
				 
			NFC_bindSelectorForBtn(_UI_ACTIVE_ACTIVE_BTN_,m_pRootNode,this,menu_selector(HeroSoulWindow::CommonBtnSelectorHandler));
			NFC_setNodeVisable(_UI_ACTIVE_ACTIVE_LABEL_,m_pRootNode,true); 

			if(m_pHeroSoulInfoData->getCanActiveHeroSoul() != _ACTIVE_MSG_CAN_ACTIVE_)
			{
				NFC_setMenuEnable(_UI_ACTIVE_ACTIVE_BTN_,m_pRootNode,false);
			}
			else
			{
				NFC_setMenuEnable(_UI_ACTIVE_ACTIVE_BTN_,m_pRootNode,true);
			}
	} 
	UpdateDiamondAndGold();
}

void    HeroSoulWindow::UpdateDiamondAndGold()
{
	 NFC_setLabelStringInt(_UI_DIAMONDS_LABEL_,m_pRootNode,RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_,true);
	 NFC_setLabelStringInt(_UI_GOLD_LABEL_,m_pRootNode,RoleInfoDataHandler::get_instance2()->m_pRIData->money_,true);
}

void   HeroSoulWindow::ShowNeedItemICON(int uiIndex,NeedItemNode * pNeedItemNode)
{
	DTAwardBoard * pDTAwardBoard =(DTAwardBoard *)m_pRootNode->getChildByTag(uiIndex);
	if(pDTAwardBoard&&pNeedItemNode)
	{ 
		int iconID = 0;
		pDTAwardBoard->setTarget(this,menu_selector(HeroSoulWindow::CommonBtnSelectorHandler));
		switch(pNeedItemNode->getItemType())
		{
		case  kDT_AWARD_OBJECT:
			{ 
				pDTAwardBoard->setIDX(uiIndex);
				pDTAwardBoard->setEnabled(true);
				pDTAwardBoard->ChangeObject(pNeedItemNode->getItemQuality(),pNeedItemNode->getItemIcon());
				pDTAwardBoard->setVisible(true);
				break;
			}
		case kDT_AWARD_MONEY:
			{ 
				iconID=_GOLD_ICON_RESID_;
				pDTAwardBoard->ChangeObject(_GOLD_QUALITY_RESID_,iconID);
				break;
			}
		case kDT_AWARD_EXP:
			{
				iconID=_EXP_ICON_RESID_;
				pDTAwardBoard->ChangeObject(_EXP_QUALITY_RESID_,iconID);
				break;
			}
		case kDT_AWARD_DIAMOND:
			{
				iconID=_DIAMOND_ICON_RESID_;
				pDTAwardBoard->ChangeObject(_DIAMOND_QUALITY_RESID_,iconID);
				break;
			}
		case  kDT_AWARD_PRESTIGE:
			{
				iconID=_PREGIST_ICON_RESID_;
				pDTAwardBoard->ChangeObject(_PREGIST_QUALITY_RESID_,iconID);
				break;
			}
		case kDT_AWARD_POWER:
			{
				iconID=_POWER_ICON_RESID_;
				pDTAwardBoard->ChangeObject(_POWER_QUALITY_RESID_,iconID);
				break;
			}
		default: 
			break;
		}
	}
}


void   HeroSoulWindow::ShowNeedItemValue(int uiIndex,NeedItemNode * pNeedItemNode)
{
	char  labelValue[64] = {0};
	sprintf(labelValue,SysLangDataManager::get_instance2()->GetSysLangById(NEED_ITEMS_NUMBER_FORMAT_TID).c_str(),pNeedItemNode->getItemHadCount(),pNeedItemNode->getItemNeedCount());
	NFC_setLabelString(uiIndex,m_pRootNode,labelValue,true);
	UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kHEROSOULWINDOW);
	if(pNeedItemNode->getItemHadCount()>=pNeedItemNode->getItemNeedCount())
	{ 
		//to do   
		NFC_setLabelByFontID(uiIndex,m_pRootNode,(int)UIViewDataManager::get_instance2()->getControlDataByID(uiIndex)->width_); 
	}
	else
	{
		// to do 
		NFC_setLabelByFontID(uiIndex,m_pRootNode,UIViewDataManager::get_instance2()->getControlDataByID(uiIndex)->m_nFontStyleID);
	}
}

void   HeroSoulWindow::SendActiveHeroSoul()
{
	C2SActiveSoulePacket activeSoulPacket(HeroSoulDataHandler::get_instance2()->getRequestHeroID());
	activeSoulPacket.Send();
}
 
void  HeroSoulWindow::OnPlayActiveEffect()
{
	cocos2d::CCSprite *  pHeroIconEffect = NFC_getUnLoopFrameEffect(2064,this,0.33f,0.43f);
	DTHeroIcon * pHeroIcon = (DTHeroIcon *)m_pRootNode->getChildByTag(_UI_ACTIVE_HERO_ICON_);
	pHeroIconEffect->setPosition(pHeroIcon->getPosition());
	m_pRootNode->addChild(pHeroIconEffect,pHeroIcon->getZOrder()+1);
}



 