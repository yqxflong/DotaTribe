#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/HeroAdvancedWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/HeroIllustratedDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include <string>
 
using  namespace  cocos2d;
using  namespace  cocos2d::extension;

#define  _HERO_QUALIY_TXT_ID_			961
#define  _CANNOT_ENGOUGH_ID_			105

#define  _TWO_SHAPE_GROUP_NUM_			2

const int maxShowAdvancenum = 4;

HeroAdvancedWindow::HeroAdvancedWindow()
{
	m_WindowType   = _TYPEF_WINDOW_HeroAdvancedWindow_;
	m_bModelWindow = false;
	m_SubType      = 0;
	m_pHeroAdvanceData=NULL;
	m_pActiveHeroAdvanceItem=NULL;
	m_vShowHeroVector.clear();
	m_bOnlyTwoShape=false;
	m_nAdvanceHeroIndex=0;
}


HeroAdvancedWindow::~HeroAdvancedWindow()
{
}


bool    HeroAdvancedWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HeroAdvancedWindow_);
	RegisterEvent(_TYPED_EVNET_HIDE_HeroAdvancedWindow_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_HeroAdvancedWindow_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_END_HERO_INFO_SYNC_, true);
	
	return IWindow::Init();
}


bool   HeroAdvancedWindow::Load()
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


void    HeroAdvancedWindow::Tick()
{
		IWindow::Tick();
}


void   HeroAdvancedWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_HeroAdvancedWindow_ )
	{
		if(!paramList.empty())
		{
			m_SubType=atoi((*paramList.begin()).c_str());
		} 
		NFC_showCommunicationWating(false);
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVNET_HIDE_HeroAdvancedWindow_ )
	{
		Destroy();
		/*	if(m_SubType)
		PushEvent(m_SubType);
		else*/
		EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_,_to_event_param_(m_SubType));
		m_SubType = 0;
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_HeroAdvancedWindow_ )
	{ 
		if(!paramList.empty())
		{
			//NFC_showCommunicationWating(false);
			DispatchUpdateEventHandle(atoi((*paramList.begin()).c_str()));
		}
	}
	else if(iEventType==_TYPED_EVENT_END_HERO_INFO_SYNC_)
	{
		 NFC_showCommunicationWating(false);
		 AnalyseCurAdvanceData();
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		UpdatePlayerDiamonAndGold();
	}
}


cocos2d::CCNode *   HeroAdvancedWindow::GetRootNode()
{
	return m_pRootNode;
}

void    HeroAdvancedWindow::Destroy()
{ 
	m_nAdvanceHeroIndex=0;
	DetachMemData();
	IWindow::Destroy();
}


void    HeroAdvancedWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	 Show(true);
}
 
void   HeroAdvancedWindow::CommonBtnSelectorHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite * pMenuItemSprite=(CMenuItemSprite *)pSender;
	switch(pMenuItemSprite->getIDX())
	{
		case _CLOSE_BTN_:
		{
			PushEvent(_TYPED_EVNET_HIDE_HeroAdvancedWindow_);
			CCLOG(" _CLOSE_BTN_  Click Handler!");
			break;
		}
		case _ADVANCED_BTN_:
		{  
			//Send Advance
			if(!m_vShowHeroVector.empty())
			HeroAdvancedDataHandler::get_instance2()->sendHeroAdvancedVerify(m_vShowHeroVector.at(0)->getHeroGroupID());
			if(m_nAdvanceHeroIndex==1)
			{ 
				CAnimationSprite * pAnimationSprite=(CAnimationSprite *)m_pRootNode->getChildByTag(_HERO_EFFECT_2_);
				pAnimationSprite->PlayEffect();
			}
			else if(m_nAdvanceHeroIndex==2)
			{  
				CAnimationSprite * pAnimationSprite=(CAnimationSprite *)m_pRootNode->getChildByTag(_HERO_EFFECT_3_);
				pAnimationSprite->PlayEffect();
			} 
			CCLOG(" _ADVANCED_BTN_  Click Handler!");
			break;
		}
		case  _ITEM_OBJ_1_:
		{
			NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pActiveHeroAdvanceItem->getItemsVector().at(0)->getTemplateID(), _TYPEF_WINDOW_HeroAdvancedWindow_);
			CCLOG(" _ITEM_BG_1_  Click Handler!");
			break;
		}
		case _ITEM_OBJ_2_:
		{

			NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pActiveHeroAdvanceItem->getItemsVector().at(1)->getTemplateID(), _TYPEF_WINDOW_HeroAdvancedWindow_);
			CCLOG(" _ITEM_BG_2_  Click Handler!");
			break;
		}
		case _ITEM_OBJ_3_:
			{

				NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pActiveHeroAdvanceItem->getItemsVector().at(2)->getTemplateID(), _TYPEF_WINDOW_HeroAdvancedWindow_);
				CCLOG(" _ITEM_BG_3_  Click Handler!");
			}
			break;
		case _ITEM_OBJ_4_:
			{

				NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pActiveHeroAdvanceItem->getItemsVector().at(3)->getTemplateID(), _TYPEF_WINDOW_HeroAdvancedWindow_);
				CCLOG(" _ITEM_BG_4_  Click Handler!");
			}
			break;
		default: 
		break;
	}
}

void   HeroAdvancedWindow::InitUILayOut()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHeroAdvancedWindow,m_pRootNode);
    BindSelectorForBtn();
	AttachMemData();
}


void   HeroAdvancedWindow::BindSelectorForBtn()
{ 
	NFC_bindSelectorForBtn(_CLOSE_BTN_,GetRootNode(),this,menu_selector(HeroAdvancedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_ADVANCED_BTN_,GetRootNode(),this,menu_selector(HeroAdvancedWindow::CommonBtnSelectorHandler));

	int TypeObjArr[]={_ITEM_OBJ_1_,_ITEM_OBJ_2_,_ITEM_OBJ_3_,_ITEM_OBJ_4_};
	COMMON_BEIGIN_ARRAY(int,maxShowAdvancenum)
		DTAwardBoard* dd=(DTAwardBoard*)GetRootNode()->getChildByTag(TypeObjArr[index]);
		dd->setIDX(TypeObjArr[index]);
		dd->setTarget(this,menu_selector(HeroAdvancedWindow::CommonBtnSelectorHandler));
	COMMON_END_ARRAY
}


void   HeroAdvancedWindow::AttachMemData()
{ 
	 m_bOnlyTwoShape=false;
	 m_pHeroAdvanceData=HeroAdvancedDataHandler::get_instance2()->getHeroAdvancedData();
	 m_vShowHeroVector.clear();
     std::map<int,IHeroSkinItem *>::iterator  hero_iter=HeroIllustratedDataHandler::get_instance2()->GetAdvancedGropHeroSkins().begin();
	 while(hero_iter!=HeroIllustratedDataHandler::get_instance2()->GetAdvancedGropHeroSkins().end())
	 { 
		 m_vShowHeroVector.push_back(hero_iter->second);
		 ++hero_iter;
	 } 
	 if(m_vShowHeroVector.size()<=_TWO_SHAPE_GROUP_NUM_)
	 m_bOnlyTwoShape=true;
	 
	 UpdatePlayerDiamonAndGold();
	 AnalyseCurAdvanceData();
	 ShowAllHeroAnimation();
}
void   HeroAdvancedWindow::DetachMemData()
{	
	HeroAdvancedDataHandler::get_instance2()->destroyMemData();
	m_vShowHeroVector.clear();
	m_pHeroAdvanceData=NULL;
}

 void   HeroAdvancedWindow::ShowAllHeroAnimation()
 {  
	 DOTATribeApp::get_instance2()->ForceFreeMemory();
 
	 NFC_setCardsStarLevel(_HERO_STAR_LABEL_1_,GetRootNode(),m_vShowHeroVector.at(0)->getHeroQualiy()+1);
	 NFC_setCardsStarLevel(_HERO_STAR_LABEL_2_,GetRootNode(),m_vShowHeroVector.at(1)->getHeroQualiy()+1);  
	 ShowHeroAniamtionWithData(_HERO_NODE_1_,_HERO_ANIMATION_1_,GetRootNode(),m_vShowHeroVector.at(0)->getHeroShapeID());
	 ShowHeroAniamtionWithData(_HERO_NODE_2_,_HERO_ANIMATION_2_,GetRootNode(),m_vShowHeroVector.at(1)->getHeroShapeID());
	  
	 if(!m_bOnlyTwoShape)
	 {  
		 NFC_setCardsStarLevel(_HERO_STAR_LABEL_3_,GetRootNode(),m_vShowHeroVector.at(2)->getHeroQualiy()+1);
		  
		 ShowHeroAniamtionWithData(_HERO_NODE_3_,_HERO_ANIMATIOn_3_,GetRootNode(),m_vShowHeroVector.at(2)->getHeroShapeID());
	 } 
 }
  
void   HeroAdvancedWindow::AnalyseCurAdvanceData()
{   
	if(m_bOnlyTwoShape)
	{
		NFC_setNodeVisable(_Derection_BG_2_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_BG_3_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_STAR_LABEL_3_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_UnLight_BG_3_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_BG_3_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_EFFECT_3_,GetRootNode(),false);
		NFC_setGrapSprite(_Derection_BG_1_,GetRootNode(),false);

		if(RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(m_vShowHeroVector.at(1)->getHeroUniqueID())->getIsActived())
		{
			m_nAdvanceHeroIndex=-1;
			NFC_setNodeVisable(_HERO_BG_2_,GetRootNode(),true);
			NFC_setNodeVisable(_HERO_UnLight_BG_2_,GetRootNode(),false);
			ShowAdvancedInfoByItem(NULL);
		}
		else
		{ 
			m_nAdvanceHeroIndex=1;
			NFC_setNodeVisable(_HERO_UnLight_BG_2_,GetRootNode(),true);
			NFC_setNodeVisable(_HERO_BG_2_,GetRootNode(),false);
			AnalyseAdvanceNeedInfoByHeroID(m_vShowHeroVector.at(0)->getHeroUniqueID());	  
		}
	} 
	else
	{
		if(RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(m_vShowHeroVector.at(1)->getHeroUniqueID())->getIsActived())
		{ 
			NFC_setGrapSprite(_Derection_BG_1_,GetRootNode(),false);
			NFC_setGrapSprite(_Derection_BG_2_,GetRootNode(),false);

			NFC_setNodeVisable(_HERO_BG_2_,GetRootNode(),true);
			NFC_setNodeVisable(_HERO_UnLight_BG_2_,GetRootNode(),false);
			if(RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(m_vShowHeroVector.at(2)->getHeroUniqueID())->getIsActived())
			{
				m_nAdvanceHeroIndex=-1;
				NFC_setNodeVisable(_HERO_BG_3_,GetRootNode(),true);
				NFC_setNodeVisable(_HERO_UnLight_BG_3_,GetRootNode(),false);
				ShowAdvancedInfoByItem(NULL);
			} 
			else
			{
				m_nAdvanceHeroIndex=2;
				NFC_setNodeVisable(_HERO_BG_3_,GetRootNode(),false);
				NFC_setNodeVisable(_HERO_UnLight_BG_3_,GetRootNode(),true);
				AnalyseAdvanceNeedInfoByHeroID(m_vShowHeroVector.at(1)->getHeroUniqueID());  //显示第二位进阶
			}
		} 
		else
		{  
			m_nAdvanceHeroIndex=1;
			NFC_setGrapSprite(_Derection_BG_1_,GetRootNode(),false);
			NFC_setGrapSprite(_Derection_BG_2_,GetRootNode(),true);
			NFC_setNodeVisable(_HERO_BG_2_,GetRootNode(),false);
			NFC_setNodeVisable(_HERO_UnLight_BG_2_,GetRootNode(),true);
			NFC_setNodeVisable(_HERO_BG_3_,GetRootNode(),false);
			NFC_setNodeVisable(_HERO_UnLight_BG_3_,GetRootNode(),true);

			//显示第一位进阶
			AnalyseAdvanceNeedInfoByHeroID(m_vShowHeroVector.at(0)->getHeroUniqueID());
		}
	} 
}


void   HeroAdvancedWindow::AnalyseAdvanceNeedInfoByHeroID(int heroID)
{
	if(m_pHeroAdvanceData)
	{
		size_t advanceCount=m_pHeroAdvanceData->getAdvancedVector().size();
		COMMON_BEIGIN_ARRAY(size_t,advanceCount)
			if(m_pHeroAdvanceData->getAdvancedVector().at(index)->getHeroUniqueID()==heroID)
			{    
				ShowAdvancedInfoByItem(m_pHeroAdvanceData->getAdvancedVector().at(index));
				return ;
			}
		COMMON_END_ARRAY 
	}
}


void  HeroAdvancedWindow::ShowAdvancedInfoByItem(HeroAdvanceSingleItem * pHeroAdvancedSingleItem)
{  
	m_pActiveHeroAdvanceItem=pHeroAdvancedSingleItem;
	if(pHeroAdvancedSingleItem)
	{  
		char  commonStr[64]={0};
		bool  isCanAdvanced=true;
		bool  isEngoughNum=true;
		if(pHeroAdvancedSingleItem->getNeedMoneyNum()>RoleInfoDataHandler::get_instance2()->m_pRIData->money_)
		{ 
			isEngoughNum=false;
			isCanAdvanced&=isEngoughNum;
		}
		if(!isEngoughNum)
		{
			NFC_setLabelByFontID(_GOLD_NUM_,GetRootNode(),_CANNOT_ENGOUGH_ID_);
		}
		NFC_setLabelStringInt(_GOLD_NUM_,GetRootNode(),pHeroAdvancedSingleItem->getNeedMoneyNum());
		int TypeObjArr[]={_ITEM_OBJ_1_,_ITEM_OBJ_2_,_ITEM_OBJ_3_,_ITEM_OBJ_4_};
		int TypeNumArr[]={_ITEM_NUM_1_,_ITEM_NUM_2_,_ITEM_NUM_3_,_ITEM_NUM_4_};
		unsigned int itemsize = pHeroAdvancedSingleItem->getItemsVector().size();
		COMMON_BEIGIN_ARRAY(int,maxShowAdvancenum)
			if(index<itemsize)
			{
				IItem * pItem = pHeroAdvancedSingleItem->getItemsVector().at(index);
				if(pItem)
				{    
					DTAwardBoard* dd=(DTAwardBoard*)GetRootNode()->getChildByTag(TypeObjArr[index]);
					dd->ChangeObject(pItem->getQualiy(),pItem->getIconID());
					//
					sprintf(commonStr,SysLangDataManager::get_instance2()->GetSysLangById(134).c_str(),
						BagOtherObjectHandler::get_instance2()->getObjectCountByTemplateId(pItem->getTemplateID()),pItem->getNum());
					isEngoughNum=BagOtherObjectHandler::get_instance2()->getObjectCountByTemplateId(pItem->getTemplateID())>=pItem->getNum() ?true:false;
					if(!isEngoughNum)
					{
						NFC_setLabelByFontID(TypeNumArr[index],GetRootNode(),_CANNOT_ENGOUGH_ID_);
					}
					isCanAdvanced&=isEngoughNum;
					NFC_setLabelString(TypeNumArr[index],GetRootNode(),commonStr);
				}
			}
			else
			{
				NFC_showNode(TypeObjArr[index],GetRootNode(),false);
				NFC_showNode(TypeNumArr[index],GetRootNode(),false);
			}
		COMMON_END_ARRAY
		NFC_setNodeVisable(_ADVANCED_BTN_,GetRootNode(),true);
		NFC_setNodeVisable(_ADVANCED_LABEL_BNT_,GetRootNode(),true);
		NFC_setEnabledForMenuItem(_ADVANCED_BTN_,GetRootNode(),isCanAdvanced);
		NFC_setNodeVisable(_ADVANCE_COMPLETE_LABEL_,GetRootNode(),false);
	}
	else
	{
		NFC_setNodeVisable(_ITEM_OBJ_1_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_NUM_1_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_OBJ_2_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_NUM_2_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_OBJ_3_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_NUM_3_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_OBJ_4_,GetRootNode(),false);
		NFC_setNodeVisable(_ITEM_NUM_4_,GetRootNode(),false);
		NFC_setNodeVisable(_GOLD_NUM_,GetRootNode(),false);
		NFC_setNodeVisable(_GOLH_ICON_,GetRootNode(),false);
		NFC_setNodeVisable(_ADVANCED_BTN_,GetRootNode(),false);
		NFC_setNodeVisable(_ADVANCED_LABEL_BNT_,GetRootNode(),false);
		NFC_setNodeVisable(_ADVANCE_COMPLETE_LABEL_,GetRootNode(),true);
		 
	}
}

void  HeroAdvancedWindow::ShowHeroAniamtionWithData(int configUIIndex,int animationIndex,cocos2d::CCNode * pParent,int shapeID)
{
	CCSkeletonAnimation * pRoleSkeleton=(CCSkeletonAnimation *)GetRootNode()->getChildByTag(animationIndex);
	if(pRoleSkeleton!=NULL)
	{
		pRoleSkeleton->removeFromParentAndCleanup(true); 
	}
	cocos2d::CCNode * pRoleConfig=(cocos2d::CCNode *)pParent->getChildByTag(configUIIndex);
	if(pRoleConfig!=NULL)
	{ 
		RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
		if(pData)
		{
			CCSkeletonAnimation * pRoleSkeleton=CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage);
			if(pRoleSkeleton!=NULL)
			{
				pRoleSkeleton->setAnimation("DaiJi",true);
				pRoleSkeleton->setAnchorPoint(pRoleConfig->getAnchorPoint());
				pRoleSkeleton->setPosition(pRoleConfig->getPosition());
				pParent->addChild(pRoleSkeleton,pRoleConfig->getZOrder(),animationIndex);
			} 
		} 
	}
}


void   HeroAdvancedWindow::UpdatePlayerDiamonAndGold()
{
	/*
	 更新人物的金钱和钻石
	*/
	NFC_setLabelStringInt(_DIAMON_NUM_LABEL_,GetRootNode(),RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_);
	NFC_setLabelStringInt(_GOLD_BG_LABEL_,GetRootNode(),RoleInfoDataHandler::get_instance2()->m_pRIData->money_);
}

void   HeroAdvancedWindow::DispatchUpdateEventHandle(int eventType)
{
   switch(eventType)
   {
   case _UPDATE_FOR_ADVANCE_SUCCESS_TYPE_:
	   {
		   AnalyseCurAdvanceData();
		   break;
	   }
   default:
	   break;
   }
}