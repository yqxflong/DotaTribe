#include "../include/EquipsRecastSubView.h" 
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/IDStringDataManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/TimeSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/IWindow.h"
#include "../include/DTAwardBoard.h"
#include "../include/EquipCastPacket.h"
#include "../include/EquipRecastDataHandler.h"
#include "../include/EquipStrengthenDataHandler.h"
#include "../include/DTEquipBoard.h"


const  int  rewardNumTID = 7037;
const  int  equipAdvanceTID = 606;

EquipsRecastSubView::EquipsRecastSubView()
{
	m_pEquipRecastDataInfo = NULL;
	m_nActiveEquipID = -1;
	m_bEquipEffectFinish = true;
	m_bEquipBreakDownSuccess = false;
}
EquipsRecastSubView::~EquipsRecastSubView()
{

}
bool EquipsRecastSubView::onLoad()
{
	if(CCNode::init())
	{
		this->autorelease();
		setPosition(CCPointZero);
		_initLayout(); 
		return true;
	}
	return false;
}
bool EquipsRecastSubView::onTick()
{ 
	return true;
}

 
bool EquipsRecastSubView::onDestroy()
{ 
	m_bEquipBreakDownSuccess=false;
	m_bEquipEffectFinish=true;
	m_nActiveEquipID = 0;
	//EquipRecastDataHandler::get_instance2()->destroyData();
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}
 
void  EquipsRecastSubView::_initLayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPRECASTVIEW,this);
	UIViewDataManager::get_instance2()->loadData(UIViewDataManager::kEQUIPRECASTVIEW);
	 
	_bindMenuSelector();
	_initToDefualtUI();

	CAnimationSprite * pEffectAnimation= (CAnimationSprite *)NFC_getNode(_EQUIP_CAST_EFFECT_,this);
	pEffectAnimation->RegisterEventHandler(this);

}

void  EquipsRecastSubView::_bindMenuSelector()
{
	NFC_bindSelectorForBtn(_EQUIP_CAST_CAST_BTN_,this,this,menu_selector(EquipsRecastSubView::CommonMenuSelectorHandler));

}

void   EquipsRecastSubView::CommonMenuSelectorHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite =(CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{ 
		switch(pMenuItemSprite->getIDX())
		{
		case _EQUIP_CAST_CAST_BTN_:
			{ 
				if(m_nActiveEquipID != -1)
				{
					BTN_INTERVAL("EQUIPRECASTBTN",_COMMON_BTN_CLICK_INTERVAL_SMALL)
					CCLOG("m_nActiveEquipID : %d",m_nActiveEquipID);
					NFC_setNodeVisable(_EQUIP_CAST_MASK_,this,true);
					CSEquipRecastDoPacket  recastPacket(m_nActiveEquipID);
					recastPacket.Send();
					NFC_setAnimationSpriteEnable(_EQUIP_CAST_EFFECT_,this,true); 
					m_bEquipEffectFinish = false;
				} 
				break;
			}
		default:
			break;
		}
	}
}


void EquipsRecastSubView::EquipHasBeenSeleted(int equipID)
{
	if(m_nActiveEquipID == equipID||equipID == -1)
	return ; 
	m_nActiveEquipID = equipID;
	CCLOG("EquipsRecastSubView equipID Selected: %d",m_nActiveEquipID);
	CSEquipRecastInfoPacket  recastInfoPacket(m_nActiveEquipID);
	recastInfoPacket.Send(); 
	
}
 
void  EquipsRecastSubView::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	//to do 
	m_bEquipEffectFinish = true;
	NFC_setAnimationSpriteEnable(_EQUIP_CAST_EFFECT_,this,false);
	if(m_bEquipBreakDownSuccess)
	{
		NFC_setNodeVisable(_EQUIP_CAST_MASK_,this,false);
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_EQUPERECAST_REFRESH_LIST_);
		m_bEquipBreakDownSuccess = false;
	} 
	NFC_setNodeVisable(_EQUIP_CAST_MASK_,this,false);
}

  
void  EquipsRecastSubView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_EQUIPRECAST_UPDATE_)
	{ 
		int receiptCode = atoi(paramList.begin()->c_str());
		DispatchEventHandler(receiptCode);
	}	 
	else if(iEventType == _TYPED_EVENT_EQUPERECAST_REFRESH_LIST_)
	{
		_initToDefualtUI();
	} 
}


void    EquipsRecastSubView::DispatchEventHandler(int receiptCode)
{
	switch(receiptCode)
	{
	case _EQUIP_CAST_UPDATE_EQUIP_INFO_:
		{
			UpdateUIWithData();
			break;
		}
	case _RQUIP_CAST_UPDATE_EQUIP_SUCCESS_DO_:
		{
			m_bEquipBreakDownSuccess = true;
			if(m_bEquipEffectFinish)
			{
				NFC_setNodeVisable(_EQUIP_CAST_MASK_,this,false);
				EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_EQUPERECAST_REFRESH_LIST_);
				m_bEquipBreakDownSuccess = false;
			}
			break;
		}
	default:
		break;
	}
}


BagEquipData *  EquipsRecastSubView::GetActiveEquipData(int equipID)
{
	size_t equipSize = EquipStrengthenDataHandler::get_instance2()->EquipList_.size();
	for(size_t equipIndex = 0;equipIndex < equipSize ;equipIndex++)
	{ 
		BagEquipData * pBagEquipData = EquipStrengthenDataHandler::get_instance2()->EquipList_.at(equipIndex);
		if(pBagEquipData&&pBagEquipData->id_ == equipID)
		{
			return pBagEquipData;
		}
	} 
	return NULL;
}


void    EquipsRecastSubView::ShowFunctionDescription(bool visiable)
{
   NFC_setNodeVisable(_EQUIP_CAST_DESC_1_LABEL,this,visiable); 
   NFC_setNodeVisable(_EQUIP_CAST_REWARD_LABEL_,this,!visiable);
   NFC_setNodeVisable(_EQUIP_CAST_REWARD_BG_,this,!visiable);  
}


void  EquipsRecastSubView::UpdateUIWithData()
{ 
	ShowFunctionDescription(false); 
	
	m_pEquipRecastDataInfo = EquipRecastDataHandler::get_instance2()->getEquipRecastDataInfos();
	//装备Icon
	BagEquipData* equipData = GetActiveEquipData(m_pEquipRecastDataInfo->getEquipID());
	if(equipData)
	{ 
		DTAwardBoard* award = (DTAwardBoard*)NFC_getNode(_EQUIP_CAST_EQUIP_ICON_,this);
		award->ChangeObject(equipData->template_->quality_,equipData->template_->iconId_);
		NFC_setNodeVisable(_EQUIP_CAST_EQUIP_ICON_,this,true); 
		NFC_setLabelString(_EQUIP_CAST_EQUIP_NAME_,this,equipData->template_->name_,true);
		if(0 < equipData->advanceLevel_)
		{
			NFC_setLabelStringInt(_EQUIP_CAST_EQUIP_LEVEL_,this,equipData->advanceLevel_,equipAdvanceTID,true);
			cocos2d::CCLabelTTF * pNameLabel = (cocos2d::CCLabelTTF *)NFC_getNode(_EQUIP_CAST_EQUIP_NAME_,this);
			cocos2d::CCLabelTTF * pLevelLabel =(cocos2d::CCLabelTTF *)NFC_getNode(_EQUIP_CAST_EQUIP_LEVEL_,this);
			pLevelLabel->setPositionX(pNameLabel->getPositionX()+pNameLabel->getContentSize().width+12);
		} 
		else
		{
			NFC_setNodeVisable(_EQUIP_CAST_EQUIP_LEVEL_,this,false);
		}
		 
		//显示装备奖励物品
		DTEquipBoard * pDefaultEquip = (DTEquipBoard *)NFC_getNode(_EQUIP_CAST_REWARD1_ICON_,this);
		pDefaultEquip->SetEquip(m_pEquipRecastDataInfo->getDefaultIconID(),m_pEquipRecastDataInfo->getDefaultQuality(),m_pEquipRecastDataInfo->getDefaultLevel());
		pDefaultEquip->setVisible(true);

		NFC_setNodeVisable(_EQUIP_CAST_REWARD1_BG_,this,true);
		NFC_setLabelString(_EQUIP_CAST_REWARD1_NAME_,this,m_pEquipRecastDataInfo->getDefaultName().c_str(),true);
		NFC_setLabelStringInt(_EQUIP_CAST_REWARD1_COUNT_,this,1,true);
		
		//显示其他奖励
		int rewardSize = m_pEquipRecastDataInfo->getRewardDataList().size();
		int rewardBGArray[] ={_EQUIP_CAST_REWARD2_BG_,_EQUIP_CAST_REWARD3_BG_};
		int rewardIconArray[] ={_EQUIP_CAST_REWARD2_ICON_,_EQUIP_CAST_REWARD3_ICON_};
		int rewardNameArray[] = {_EQUIP_CAST_REWARD2_NAME_,_EQUIP_CAST_REWARD3_NAME_};
		int rewardCountArray[] = {_EQUIP_CAST_REWARD2_COUNT_,_EQUIP_CAST_REWARD3_COUNT_}; 
		COMMON_BEIGIN_ARRAY(int,2)
		   DTAwardBoard * award=(DTAwardBoard*)NFC_getNode(rewardIconArray[index],this);
		   if(index < rewardSize)
		   {
			   NFC_setNodeVisable(rewardBGArray[index],this,true);
			   PRewardItemNode pRewardItemNode = m_pEquipRecastDataInfo->getRewardDataList().at(index);
			   award->setVisible(true);
			   int quality=-1;
			   int iconid=-1; 
			   switch (pRewardItemNode->rewardItemType)
			   {
			   case  kDT_AWARD_OBJECT:
				   {     
					   quality=pRewardItemNode->rewardQuality;
					   iconid=pRewardItemNode->rewardIconID;
					   NFC_setLabelString(rewardNameArray[index],this,pRewardItemNode->rewardRewardName.c_str(),true);
					   break;
				   }
			   case   kDT_AWARD_MONEY:
				   {   
					   quality=_GOLD_QUALITY_RESID_;
					   iconid=_GOLD_ICON_RESID_;
					   NFC_setLabelString(rewardNameArray[index],this,kDT_MONEY_TID,true);
					   break;
				   }
			   case  kDT_AWARD_EXP:
				   {
					   quality=_EXP_QUALITY_RESID_;
					   iconid=_EXP_ICON_RESID_;
					   NFC_setLabelString(rewardNameArray[index],this,kDT_EXP_TID,true);
					   break;
				   }
			   case  kDT_AWARD_DIAMOND:
				   {
					   quality=_DIAMOND_QUALITY_RESID_;
					   iconid=_DIAMOND_ICON_RESID_;
					   NFC_setLabelString(rewardNameArray[index],this,kDT_DIAMOND_TID,true);
					   break;
				   }
			   case kDT_AWARD_PRESTIGE:
				   {
					   quality=_PREGIST_QUALITY_RESID_;
					   iconid=_PREGIST_ICON_RESID_;
					   NFC_setLabelString(rewardNameArray[index],this,kDT_PRESTIGE_TID,true);
					   break;
				   }
			   case kDT_AWARD_POWER:
				   {
					   quality=_POWER_QUALITY_RESID_;
					   iconid=_POWER_ICON_RESID_;
					   NFC_setLabelString(rewardNameArray[index],this,kDT_POWER_TID,true);
					   break;
				   }
			   default:
				   break;
			   }
			   award->ChangeObject(quality,iconid);  
			   NFC_setLabelStringInt(rewardCountArray[index],this,pRewardItemNode->rewardItemCount,true);
		   }
		   else
		   {
			   award->ChangeObject();
			   award->setVisible(false);
			   NFC_setNodeVisable(rewardNameArray[index],this,false);
			   NFC_setNodeVisable(rewardCountArray[index],this,false); 
			   NFC_setNodeVisable(rewardBGArray[index],this,false); 
		   }  
		COMMON_END_ARRAY 
		 NFC_bindSelectorForBtn(_EQUIP_CAST_CAST_BTN_,this,this,menu_selector(EquipsRecastSubView::CommonMenuSelectorHandler));
		 NFC_setMenuEnable(_EQUIP_CAST_CAST_BTN_,this,true);
		 NFC_setNodeVisable(_EQUIP_CAST_CAST_BTN_,this,true);
		 NFC_setNodeVisable(_EQUIP_CAST_CAST_LABEL_,this,true);   
	}
	NFC_showCommunicationWating_2(false);

}


void    EquipsRecastSubView::_initToDefualtUI()
{
	DTAwardBoard* award = (DTAwardBoard*)NFC_getNode(_EQUIP_CAST_EQUIP_ICON_,this);
	award->ChangeObject();
	award->setVisible(true);
	 
	COMMON_BEIGIN_ARRAY(int,17)
		NFC_setNodeVisable(_EQUIP_CAST_REWARD_LABEL_+index,this,false);
	COMMON_END_ARRAY

	NFC_setNodeVisable(_EQUIP_CAST_CAST_BTN_,this,true);
	NFC_setNodeVisable(_EQUIP_CAST_CAST_LABEL_,this,true);
	NFC_setMenuEnable(_EQUIP_CAST_CAST_BTN_,this,false); 

    ShowFunctionDescription(true);
}