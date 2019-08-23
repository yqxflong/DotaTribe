// Name : HeroIllustratedWindow
// Function:英雄图鉴窗口
// Author : Johny


#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/HeroIllustratedWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CSHeroExpandInfoPacket.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/CProgressInnerBar.h"
#include "../include/PESWindow.h"
#include "../include/HeroAdvancedDataHandler.h"
#include "../include/MessageBoxWindow.h"
#include "../include/MiningDataHandler.h"
#include "../include/HeroSoulPacket.h"
#include "../include/HeroSoulDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
 
#include <string>


  
using  namespace  cocos2d;
using namespace cocos2d::extension;
 
 

#define  _DEFAULT_CELL_NUM_				4
#define  _HERO_QUALIY_TXT_ID_			961
#define  _HERO_BUFFER_NAME_FORMAT_		374
#define  _DEFAULT_GROW_VALUE_			12.0f
#define  _ATTACK_GROW_DESC_ID_			969
#define  _HP_GROW_DESC_ID_				970
#define  _SPEED_GROW_DESC_ID_			971 
#define  _MP_GROW_DESC_ID_				972

#define  _START_OFFSET_COUNT_			5

#define  _HERO_ADVANCE_LEVEL_LESS_TIPS_  7000
#define  _HERO_SOUL_CHALLENEGT_LESS_TIPS_ 7022

 
#define  CELLLISTFACTORY_ALL(type)		HEROILLUSTRATEDDATAHANDLER->getHeroCellListFactory()->GetHeroIllustratedByType(type)->getAllRecordCellList()

#define  CELLLISTFACTORY_SELF(type)		HEROILLUSTRATEDDATAHANDLER->getHeroCellListFactory()->GetHeroIllustratedByType(type)->getPlayerSelfCellList()
 
 
HeroIllustratedWindow::HeroIllustratedWindow()
{
	m_WindowType   = _TYPEF_WINDOW_HeroIllustratedWindow_;
	m_bModelWindow = false;
	m_nBackType      = 0;
	m_nHeroPos	     = 0;
	m_pTable=NULL;
	m_StarCellSize=CCSizeZero;
	m_HeroCellSize=CCSizeZero;
	m_bCurIllustatedType=_ALL_HERO_BTN_;
	m_bIsShowAllDB=false;
	m_nActiveCellIndex=-1;
	m_nActiveCellItemIndex=-1;
	m_nActiveHeroID=-1;
	m_nHeroCellOffSetCount=0;
	m_nStarCellOffSetCount=0; 
}
HeroIllustratedWindow::~HeroIllustratedWindow()
{
}
bool    HeroIllustratedWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HeroIllustratedWindow_);
	RegisterEvent(_TYPED_EVNET_HIDE_HeroIllustratedWindow_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_, true);
	RegisterEvent(_TYPED_EVENT_START_HERO_INFO_SYNC_, true);
	RegisterEvent(_TYPED_EVENT_END_HERO_INFO_SYNC_, true);
	 
	return IWindow::Init();
}
bool   HeroIllustratedWindow::Load()
{
	do
	{
		if (!IWindow::Load())
			break;
		
	} 
	while (false);
	return false;
}
void    HeroIllustratedWindow::Tick()
{
	IWindow::Tick();
}

void   HeroIllustratedWindow::Destroy()
{  
	m_nActiveCellIndex = -1;
	m_nActiveCellItemIndex = -1;
	m_nActiveHeroID = -1;
	m_nHeroCellOffSetCount = 0;
	m_nStarCellOffSetCount = 0;
	m_bIsShowAllDB = false;
	m_pTable = NULL;
	m_bCurIllustatedType = _ALL_HERO_BTN_; 

	RoleHeroSkinsDataHandler::get_instance2()->ResetHeroExpandInfo();
    IWindow::Destroy();
}

void   HeroIllustratedWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_HeroIllustratedWindow_ )
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVNET_HIDE_HeroIllustratedWindow_ )
	{ 
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_HeroIllustratedWindow_ )
	{
		if(!paramList.empty())
		{
			DispatchUpdateEventHandler(atoi((*paramList.begin()).c_str()));
		}
	} 
	else if(iEventType == _TYPED_EVENT_START_HERO_INFO_SYNC_)
	{
		NFC_showCommunicationWating(true);
	}
	else if(iEventType==_TYPED_EVENT_END_HERO_INFO_SYNC_)
	{
		NFC_showCommunicationWating(false);
		UpdateHeroCellListWithType();
	} 
}

void   HeroIllustratedWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(m_pRootNode->isVisible())
		return ;

	if(!paramList.empty())
	{ 
		std::list<std::string>::iterator param_iter=paramList.begin();
		m_nBackType=atoi((*param_iter++).c_str()); 
		//#back type
		if(m_nBackType==IWindow::_TYPED_WINDOW_HEROBAR_)
		{
			m_bIsShowAllDB=true;
			HeroSoulDataHandler::get_instance2()->setBackWindowType(m_nBackType);
		}
		else if (m_nBackType == IWindow::_TYPED_WINDOW_PESWINDOW_)
		{
			m_bIsShowAllDB = true;
			HeroSoulDataHandler::get_instance2()->setBackWindowType(m_nBackType);
		}
		else if (m_nBackType == IWindow::_TYPED_WINDOW_TEAMINFOWINDOW_)
		{
			HeroSoulDataHandler::get_instance2()->setBackWindowType(m_nBackType);
		}
		else
			HeroSoulDataHandler::get_instance2()->setBackWindowType(0);

		//#heroPos
		if(param_iter != paramList.end())
			m_nHeroPos = atoi((*param_iter++).c_str());
		else
			m_nHeroPos = 0;
	} 
	else{
		m_nBackType=0;
		m_nHeroPos = 0;
	}

	InitUILayOut();
	InitDefaultSetting();

	Show(true);
}

cocos2d::CCNode *   HeroIllustratedWindow::GetRootNode()
{
	return m_pRootNode;
}

void   HeroIllustratedWindow::CommonBtnSelectorHandler(cocos2d::CCObject * pSender)
{   
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case _CLOSE_BTN_:
			{ 
				int preWindowType = m_nBackType;
				Destroy();
				if(preWindowType == 0)
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_); 
				}
				else if(preWindowType==_TYPED_WINDOW_TEAMINFOWINDOW_)
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
				}
				else if (preWindowType == IWindow::_TYPED_WINDOW_PESWINDOW_)
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(PESWindow::kTAB_1+m_nHeroPos*2), _to_event_param_(PESWindow::LOAD_SOUL_VIEW));
				}
				else if(preWindowType==IWindow::_TYPED_WINDOW_GAINHEROWINDOW_)
				{
					if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_HOME_PROCEDURE_)
					{
						DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_HOMEWINDOW_);
						DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
					} 
					else
					{
						EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_); 
					} 
				}
				else if(preWindowType==IWindow::_TYPED_WINDOW_HEROBAR_)
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_); 
				} 
				else if(preWindowType == _TYPED_EVENT_SHOW_MINEAREAWINDOW_)
				{
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MININGDATAHANDLER->m_iBackArea));
				}
				else
				{
					EVENTSYSTEM->PushEvent(preWindowType); 
				}
				CCLOG("  _CLOSE_BTN_ Click Handler!");
				break;
			}
		case  _SWITCH_BTN_:
			{ 
				ChangeSwitchBtn();
				break;
			}
		case _ALL_HERO_BTN_:
		case _POWER_HERO_BTN_:
		case _QUICK_HERO_BTN_:
		case _INTELIGENCE_HERO_BTN_:
		    {
				ChangeIllustatedTabType(pMenuItem->getIDX());
			   break;
			}	 
		case _HERO_CHANGE_BTN_:
			{   
				HeroIllustratedDataHandler::get_instance2()->SendReplaceHeroRequest(m_nActiveHeroID, m_nHeroPos);
				//to do 
				CCLOG(" _HERO_CHANGE_BTN_ Click Handler!");
				break;
			}
		case _HERO_ADVANCE_BTN_:
			{ 
				if(ClientConstDataManager::get_instance2()->getValueByKey(HERO_ADVANCE_LEVEL)>RoleInfoDataHandler::get_instance2()->m_pRIData->level_)
				{  
					char commonStr[128]={0};
					std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_HERO_ADVANCE_LEVEL_LESS_TIPS_);
					sprintf(commonStr,advanceTips.c_str(),ClientConstDataManager::get_instance2()->getValueByKey(HERO_ADVANCE_LEVEL));
					NFC_showMessageBoxSingle(kDEFAULT,commonStr);
					return ;
				}
				IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
				if(pHeroSkinItem)
				HeroAdvancedDataHandler::get_instance2()->sendHeroAdvancedNeedRequest(pHeroSkinItem->getHeroGroupID());
				CCLOG(" _HERO_ADVANCE_BTN_ Click Handler!");
				break;
			}
		case _HERO_DESC_BTN_:
			{ 
				ShowDetailedHeroInfo();
				CCLOG(" _HERO_DESC_BTN_ Click Handler!");
				break;
			}
		case _HERO_EXPAND_BTN_:
			{
				CallInDetailedHeroInfo();
				CCLOG(" _HERO_EXPAND_BTN_ Click Handler!");
				break;
			}
		case _HERO_HERO_SOUL_BTN_:
			{ 
				//英雄战魂
				//检测当前选中英雄的战魂等级 
				if(m_nActiveHeroID!=-1)
				{
					IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
					if(RoleInfoDataHandler::get_instance2()->m_pRIData->level_>=pHeroSkinItem->getHeroSoulChallenegeLevel())
					{
						HeroSoulDataHandler::get_instance2()->setRequestHeroID(m_nActiveHeroID);
						C2SHeroSoulPacket heroSoulPacket(m_nActiveHeroID);
						heroSoulPacket.Send();
					} 
					else
					{
						char commonStr[128]={0};
						std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_HERO_SOUL_CHALLENEGT_LESS_TIPS_);
						sprintf(commonStr,advanceTips.c_str(),pHeroSkinItem->getHeroSoulChallenegeLevel());
						NFC_showMessageBoxSingle(kDEFAULT,commonStr);
						return ;
					}
				}				  
				break;
			}
		default:
			break;
		}
	}
}

void   HeroIllustratedWindow::CellBtnSelectorHandler(cocos2d::CCObject * pSender)
{ 
	//Cell按钮点击事件
	CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem)
	{  
		ChangeCellItemState(pMenuItem->getIDX(),pMenuItem->getAttachData1(),pMenuItem->getAttachData2());
	} 
}



void   HeroIllustratedWindow::InitUILayOut()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHeroIllustratedWindow,m_pRootNode);
    BindSelectorForBtn();
	setTableView();

	if(m_nActiveHeroID==-1)
		m_nActiveHeroID=HeroIllustratedDataHandler::get_instance2()->GetFirstHightestActiveSkinUID();

	CSHeroExpandInfoPacket  heroInfoRequest(m_nActiveHeroID);
	heroInfoRequest.Send();
}

void   HeroIllustratedWindow::BindSelectorForBtn()
{  
	NFC_bindSelectorForBtn(_CLOSE_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));

	NFC_bindSelectorForBtn(_SWITCH_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));

	NFC_bindSelectorForBtn(_ALL_HERO_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_POWER_HERO_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_QUICK_HERO_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_INTELIGENCE_HERO_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));

 
	NFC_bindSelectorForBtn(_HERO_CHANGE_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_HERO_ADVANCE_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	 
	NFC_bindSelectorForBtn(_HERO_DESC_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
	NFC_bindSelectorForBtn(_HERO_EXPAND_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler)); 
	 
	NFC_bindSelectorForBtn(_HERO_HERO_SOUL_BTN_,GetRootNode(),this,menu_selector(HeroIllustratedWindow::CommonBtnSelectorHandler));
}

void   HeroIllustratedWindow::AttachMemData()
{ 
	//关联内存数据
}

void   HeroIllustratedWindow::DetachMemData()
{
	//脱离内存数据
}
  

void  HeroIllustratedWindow::setTableView()
{
	CCNode* cc=m_pRootNode->getChildByTag(_STAR_CELL_NODE_);
	m_StarCellSize=cc->getContentSize();
	cc=m_pRootNode->getChildByTag(_HERO_CELL_NODE_);
	m_HeroCellSize=cc->getContentSize();
 
	m_pTable =(cocos2d::extension::CCTableView *)m_pRootNode->getChildByTag(_HERO_TABLE_VIEW_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	
	
}
  

cocos2d::extension::CCTableViewCell*   HeroIllustratedWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	cocos2d::extension::CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new cocos2d::extension::CCTableViewCell();
		cell->autorelease();
		createTableCell(cell,idx);
		setTableCell(cell,idx);
		return cell;
	}
	setTableCell(cell,idx,true);
	return cell;
} 

cocos2d::CCSize HeroIllustratedWindow::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	cocos2d::CCSize tmpSize=CCSizeZero;
	GetCellTypeFromConfig(idx,tmpSize);
	return tmpSize;
}

unsigned int HeroIllustratedWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return GetNumberCellsList();
}

void   HeroIllustratedWindow::createTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{    
	cocos2d::CCSize tmpSize=CCSizeZero;
	IHeroCellItem *	pTempItem=HeroIllustratedWindow::GetCellTypeFromConfig(cellIndex,tmpSize);
	if(pTempItem&&pTempItem->getIsStarCellType())
	{  
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHerolllustratedStarCell,pTableCell);
	}
	else
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHeroIllustratedHeroCell,pTableCell);
		if(pTempItem->getHeroVector().size()<_DEFAULT_CELL_NUM_)
		{   
			RemoveHeroCellFromTableCell(pTableCell,pTempItem->getHeroVector().size());
		}
	}
}

void    HeroIllustratedWindow::RemoveHeroCellFromTableCell(cocos2d::extension::CCTableViewCell* cell,int exsitNum)
{    
	for(int startIndex=exsitNum*_HERO_CELL_NUN_;startIndex<=_HERO_CELL_END_;startIndex++)
	{   
		cocos2d::CCNode * pSubNode=cell->getChildByTag(startIndex);
		if(pSubNode!=NULL)
		pSubNode->removeFromParentAndCleanup(true);
	}
}
 
 
void   HeroIllustratedWindow::setTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex,bool isNeedCear)
{  
	if(isNeedCear)
	{
		pTableCell->removeAllChildrenWithCleanup(true);
		createTableCell(pTableCell,cellIndex);
	}
	//to do
	cocos2d::CCSize  tempSize=CCSizeZero;
	IHeroCellItem * pHeroCellItem=GetCellTypeFromConfig(cellIndex,tempSize);
	if(pHeroCellItem->getIsStarCellType())
	{ 
		CCardsStarProgress * pStar=(CCardsStarProgress *)pTableCell->getChildByTag(_STAT_PROGRESS_);
		pStar->SetCurcount(pHeroCellItem->getStarsNum()+1);
	}
	else
	{   
		size_t heroCellCount=pHeroCellItem->getHeroVector().size();
		COMMON_BEIGIN_ARRAY(size_t,heroCellCount)
			 SetHeroCellItem(cellIndex,pTableCell,(int)index,pHeroCellItem->getHeroVector().at(index));
		COMMON_END_ARRAY
	}
}

void    HeroIllustratedWindow::SetHeroCellItem(int cellIndex,cocos2d::extension::CCTableViewCell* cell ,int cellItemIndex,IHeroSkinItem * pHeroSkinItem)
{   
	if(m_nActiveCellIndex==cellIndex&&m_nActiveCellItemIndex==cellItemIndex)
	{
		NFC_setNodeVisable(cellItemIndex*_HERO_CELL_NUN_+_HIGHT_LIGHT_BG_,cell,true);
	} 
	
	NFC_bindDTHeroCellSelectorAndAttahParam(cellItemIndex*_HERO_CELL_NUN_+_HERO_ICON_,cellIndex,cell,this,menu_selector(HeroIllustratedWindow::CellBtnSelectorHandler),cellItemIndex,pHeroSkinItem->getHeroUniqueID());

	NFC_setDTHeroQualiy(cellItemIndex*_HERO_CELL_NUN_+_HERO_ICON_,cell,(int)pHeroSkinItem->getHeroQualiy());

	if(!pHeroSkinItem->getIsActived())
	{
		NFC_setDTHeroColor(cellItemIndex*_HERO_CELL_NUN_+_HERO_ICON_,cell,color_BagGrap);
	}

	NFC_setDTHeroIcon(cellItemIndex*_HERO_CELL_NUN_+_HERO_ICON_,cell,pHeroSkinItem->getHeroIconID(),true);
	 
	cocos2d::CCSprite *pSItem=(cocos2d::CCSprite *)cell->getChildByTag(cellItemIndex*_HERO_CELL_NUN_+_HERO_TYPE_);
	if(pSItem)
	{
		int  typeResouleID=0;
		if(pHeroSkinItem->getHeroType()==IHeroillustated_Base_Tag::_Illustrated_Power_Type_)
		{  
			typeResouleID=ClientConstDataManager::get_instance2()->getValueByKey(POWER_ICON);
		}
		else if(pHeroSkinItem->getHeroType()==IHeroillustated_Base_Tag::_Illustrated_Quick_Type_)
		{ 
			typeResouleID=ClientConstDataManager::get_instance2()->getValueByKey(QUICK_ICON);
		}
		else if(pHeroSkinItem->getHeroType()==IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_)
		{ 
			typeResouleID=ClientConstDataManager::get_instance2()->getValueByKey(INTELIGENCE_ICON);
		}
		pSItem->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(typeResouleID).c_str());
		pSItem->setVisible(true);
	} 
	NFC_setNodeVisable(cellItemIndex*_HERO_CELL_NUN_+_HERO_NAME_BG_,cell,true);
	cocos2d::CCLabelTTF * pNameLabel=(cocos2d::CCLabelTTF *)cell->getChildByTag(cellItemIndex*_HERO_CELL_NUN_+_HERO_NAME_CELL_LABEL_);
	if(pNameLabel)
	{
		pNameLabel->setString(pHeroSkinItem->getHeroName().c_str());
		pNameLabel->setVisible(true);
	}
}
	 
	 

void   HeroIllustratedWindow::ChangeIllustatedTabType(int illustratedType)
{
	if(m_bCurIllustatedType!=illustratedType)
	{ 
		NFC_setTabMenuState(illustratedType,GetRootNode(),true);
		NFC_setTabMenuState(m_bCurIllustatedType,GetRootNode(),false);
		m_bCurIllustatedType=illustratedType;
	    UpdateHeroCellListWithType();
	} 
}



void  HeroIllustratedWindow::UpdateHeroCellListWithType()
{    
	 if(m_bCurIllustatedType==_ALL_HERO_BTN_)
	 {
		 CalActiveHeroCelllConfig(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_);
	 }
	 else if(m_bCurIllustatedType==_POWER_HERO_BTN_)
	 { 
		 CalActiveHeroCelllConfig(IHeroillustated_Base_Tag::_Illustrated_Power_Type_);
	 }
	 else if(m_bCurIllustatedType==_QUICK_HERO_BTN_)
	 {
		 CalActiveHeroCelllConfig(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_);
	 }
	 else if(m_bCurIllustatedType==_INTELIGENCE_HERO_BTN_)
	 {
		 CalActiveHeroCelllConfig(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_);
	 } 
	 refreshTableView(m_pTable);
}


void    HeroIllustratedWindow::ChangeSwitchBtn()
{    
   m_bIsShowAllDB=!m_bIsShowAllDB;
   if(m_bIsShowAllDB)
   {
	   NFC_setTabMenuState(_SWITCH_BTN_,GetRootNode(),m_bIsShowAllDB);
   }
   CCLOG("ChangeSwitchBtn  Handler!");
   //to do
   UpdateHeroCellListWithType();

}

void    HeroIllustratedWindow::InitDefaultSetting()
{
	//to do
   NFC_setTabMenuState(_SWITCH_BTN_,GetRootNode(),m_bIsShowAllDB);
   NFC_setTabMenuState(m_bCurIllustatedType,GetRootNode(),true); 
   //计算当前英雄的CellIndex和CellItemIndex
   CalActiveHeroCelllConfig(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_);	
   refreshTableView(m_pTable);
   UpdateHeroSoulBtnState();

   if(m_nActiveCellIndex>=_START_OFFSET_COUNT_)
   {  
	   refreshTableViewOffCount(m_pTable,m_nHeroCellOffSetCount,m_nStarCellOffSetCount);
   }
}

IHeroCellItem *	HeroIllustratedWindow::GetCellTypeFromConfig(int cellIndex,cocos2d::CCSize & cellSize)
{ 
	IHeroCellItem * pHeroCellItem=NULL;
	bool isStarItem=false;
	switch(m_bCurIllustatedType)
	{
	case _ALL_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_),cellIndex);
			else
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_),cellIndex);
			break;
		}
	case _POWER_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Power_Type_),cellIndex);
			else
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Power_Type_),cellIndex);
			break;
		}
	case _QUICK_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_),cellIndex);
			else
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_),cellIndex);
			break;
		}
	case _INTELIGENCE_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_),cellIndex);
			else
			pHeroCellItem=GetCellTypeFromCellIndex(CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_),cellIndex);
			break;
		}
	default:
		break;
	} 
	if(pHeroCellItem!=NULL)
	{
		if(pHeroCellItem->getIsStarCellType())
		{
			cellSize=m_StarCellSize;
		}
		else
		{
			cellSize=m_HeroCellSize;
		}
	}
	return  pHeroCellItem;
}





IHeroCellItem *  HeroIllustratedWindow::GetCellTypeFromCellIndex(std::vector<IHeroCellItem *> & cellItem,int cellIndex)
{
	if(cellIndex<(int)cellItem.size())
	{  
		return cellItem.at(cellIndex);
	} 
	return NULL;
}


unsigned int     HeroIllustratedWindow::GetNumberCellsList()
{ 
	switch(m_bCurIllustatedType)
	{
	case _ALL_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
				return CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_).size();
			else
				return CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_).size();
			break;
		}
	case _POWER_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
				return CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Power_Type_).size();
			else
				return CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Power_Type_).size();
			break;
		}
	case _QUICK_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
				return CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_).size();
			else
				return CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_).size();
			break;
		}
	case _INTELIGENCE_HERO_BTN_:
		{
			if(m_bIsShowAllDB)
				return CELLLISTFACTORY_ALL(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_).size();
			else
				return CELLLISTFACTORY_SELF(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_).size();
			break;
		}
	default:
		break;
	} 
	return  0;
}


void     HeroIllustratedWindow::ChangeCellItemState(int cellIndex,int cellItemIndex,int heroID)
{ 
	if(m_nActiveCellIndex!=cellIndex||m_nActiveCellItemIndex!=cellItemIndex)
	{
		//找到之前的Cell
		cocos2d::extension::CCTableViewCell * cell= m_pTable->cellAtIndex(m_nActiveCellIndex);
		int  activeUITag=0;
		if(cell)
		{  
			activeUITag=m_nActiveCellItemIndex*_HERO_CELL_NUN_+_HIGHT_LIGHT_BG_;
			cell->getChildByTag(activeUITag)->setVisible(false);
		}
		cell= m_pTable->cellAtIndex(cellIndex);
		if(cell)
		{
			activeUITag=cellItemIndex*_HERO_CELL_NUN_+_HIGHT_LIGHT_BG_;
			cell->getChildByTag(activeUITag)->setVisible(true);
		}
		m_nActiveCellIndex=cellIndex;
		m_nActiveCellItemIndex=cellItemIndex;
		if(m_nActiveHeroID!=heroID)
		{ 
		    //to do
		    CCLOG("Hero Change Item : %d",heroID);
			m_nActiveHeroID=heroID;
			UpdateHeroSoulBtnState();
			IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
			bool isNeedUpdate = pHeroSkinItem->getIsNeedUpdate();
			if(pHeroSkinItem)
			{  
				//to do
				CSHeroExpandInfoPacket  heroInfoRequest(m_nActiveHeroID);
				heroInfoRequest.Send();
			}
			else
			{
				ShowHeroExpandInfoLayer();
			}
		}
	}
}


void	HeroIllustratedWindow::ShowHeroExpandInfoLayer()
{  
	UpdateAdvanceHeroBtnState();
	UpdateChangeHeroBtnState();
	IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
	bool isNeedUpdate = pHeroSkinItem->getIsNeedUpdate();
	if(pHeroSkinItem)
	{    
		 NFC_setLabelString(_HERO_NAME_LABEL_,GetRootNode(),pHeroSkinItem->getHeroName());
		 UpdateHeroAnimation(pHeroSkinItem->getHeroShapeID());
		 char  commonStr[128]={0}; 
		 NFC_setLabelStringInt(_HERO_LEVEL_NUM_,GetRootNode(),RoleInfoDataHandler::get_instance2()->m_pRIData->heroLevel_);
  
		 NFC_setNodeVisable(_HERO_STAR_LABEL_,GetRootNode(),false);
		  
		 NFC_setLabelStringInt(_HERO_POWER_NUM_,GetRootNode(),pHeroSkinItem->getHeroPower());
		 NFC_setLabelStringInt(_HERO_QUICK_NUM_,GetRootNode(),pHeroSkinItem->getHeroQuick());
		 NFC_setLabelStringInt(_HERO_INTELIGENCE_NUM_,GetRootNode(),pHeroSkinItem->getHeroIntligence());
		 
		 float   maxHeroProgress=(float)NFC_getValueFromClientConst(MAX_HERO_PROGRESS);

		 if(pHeroSkinItem->getHeroAttackGrow()<maxHeroProgress)
		 NFC_setCProgressInnerBar(_HERO_ATTACK_INTERPASS_BG_,GetRootNode(),1.0f);
		 else
		 NFC_setCProgressInnerBar(_HERO_ATTACK_INTERPASS_BG_,GetRootNode(),maxHeroProgress/pHeroSkinItem->getHeroAttackGrow());
		 
		 if(pHeroSkinItem->getHeroHpGrow()<maxHeroProgress)
		 NFC_setCProgressInnerBar(_HERO_HP_INTERPASS_BG_,GetRootNode(),1.0f);
		 else
		 NFC_setCProgressInnerBar(_HERO_HP_INTERPASS_BG_,GetRootNode(),maxHeroProgress/pHeroSkinItem->getHeroHpGrow());
 
		 if(pHeroSkinItem->getHeroSpeedGrow()<maxHeroProgress)
		 NFC_setCProgressInnerBar(_HERO_SPEDDGROW_INTERPASS_BG_,GetRootNode(),1.0f);
		 else
		 NFC_setCProgressInnerBar(_HERO_SPEDDGROW_INTERPASS_BG_,GetRootNode(),maxHeroProgress/pHeroSkinItem->getHeroSpeedGrow());
		  
		 if(pHeroSkinItem->getHeroMpGrow()<maxHeroProgress)
		 NFC_setCProgressInnerBar(_HERO_MPGROW_INTERPASS_BG_,GetRootNode(),1.0f);
		 else
		 NFC_setCProgressInnerBar(_HERO_MPGROW_INTERPASS_BG_,GetRootNode(),maxHeroProgress/pHeroSkinItem->getHeroMpGrow());
	  
		 if(pHeroSkinItem->getHeroBufferID()>0)
		 {  
		 	 std::string buffer=pHeroSkinItem->getHeroBufferName();
			 sprintf(commonStr,SysLangDataManager::get_instance2()->GetSysLangById(_HERO_BUFFER_NAME_FORMAT_).c_str(),pHeroSkinItem->getHeroBufferLevel()); 
			 buffer+=" ";
			 buffer+=commonStr;
			 NFC_setLabelString(_HERO_BUFFER_NAME_,GetRootNode(),buffer,true); 
		 }
		 else
		 { 
			 NFC_setNodeVisable(_HERO_BUFFER_NAME_,GetRootNode(),false); 
		 } 
		//todo  
		 CallInDetailedHeroInfo();
	}
	NFC_showCommunicationWating(false);
}


void	 HeroIllustratedWindow::UpdateHeroAnimation(int heroShapeID)
{
	CCSkeletonAnimation * pRoleSkeleton=(CCSkeletonAnimation *)GetRootNode()->getChildByTag(_HERO_ANIMATION_NODE_);
	if(pRoleSkeleton!=NULL)
	{
		pRoleSkeleton->removeFromParentAndCleanup(true); 
	}
	cocos2d::CCNode * pRoleConfig=(cocos2d::CCNode *)GetRootNode()->getChildByTag(_HERO_ANIMATION_CONFIG_);
	if(pRoleConfig!=NULL)
	{ 
		RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(heroShapeID);
		if(pData)
		{
			CCSkeletonAnimation * pRoleSkeleton=CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage);
			if(pRoleSkeleton!=NULL)
			{
				pRoleSkeleton->setAnimation("DaiJi",true);
				pRoleSkeleton->setAnchorPoint(pRoleConfig->getAnchorPoint());
				pRoleSkeleton->setPosition(pRoleConfig->getPosition());
				GetRootNode()->addChild(pRoleSkeleton,pRoleConfig->getZOrder(),_HERO_ANIMATION_NODE_);
			} 
		} 
	}
}

void     HeroIllustratedWindow::ShowDetailedHeroInfo()
{ 
	//to do 
	IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
	bool isNeedUpdate = pHeroSkinItem->getIsNeedUpdate();
	if(pHeroSkinItem)
	{ 
		NFC_setNodeVisable(_HERO_DESC_BTN_,GetRootNode(),false);
		NFC_setNodeVisable(_HERO_DESC_LABEL_,GetRootNode(),false);

		NFC_setNodeVisable(_HERO_TIPS_MARK_BG_,GetRootNode(),true);

		NFC_setNodeVisable(_HERO_EXPAND_BTN_,GetRootNode(),true);
		NFC_setNodeVisable(_HERO_EXPAND_LABEL_,GetRootNode(),true);

		char commonBtn[128]={0};
		sprintf(commonBtn,SysLangDataManager::get_instance2()->GetSysLangById(_ATTACK_GROW_DESC_ID_).c_str(),pHeroSkinItem->getHeroAttackGrow(),getHeroTypeStr(pHeroSkinItem->getHeroType()).c_str());
		NFC_setLabelString(_HERO_TIPS1_LABEL_,GetRootNode(),commonBtn,true);
		 
	    sprintf(commonBtn,SysLangDataManager::get_instance2()->GetSysLangById(_HP_GROW_DESC_ID_).c_str(),pHeroSkinItem->getHeroHpGrow());
	    NFC_setLabelString(_HERO_TIPS2_LABEL_,GetRootNode(),commonBtn,true);

	    sprintf(commonBtn,SysLangDataManager::get_instance2()->GetSysLangById(_SPEED_GROW_DESC_ID_).c_str(),pHeroSkinItem->getHeroSpeedGrow());
		NFC_setLabelString(_HERO_TIPS3_LABEL_,GetRootNode(),commonBtn,true);

	    sprintf(commonBtn,SysLangDataManager::get_instance2()->GetSysLangById(_MP_GROW_DESC_ID_).c_str(),pHeroSkinItem->getHeroMpGrow());
		NFC_setLabelString(_HERO_TIPS4_LABEL_,GetRootNode(),commonBtn,true); 

		if(pHeroSkinItem->getHeroBufferID()>0)
		{
			 NFC_setLabelString(_HERO_BUFFER_DESC_NAME_,GetRootNode(),pHeroSkinItem->getHeroBufferDesc(),true);
		}
		else
		{
			 NFC_setNodeVisable(_HERO_BUFFER_DESC_NAME_,GetRootNode(),false);
		} 
	}
	 
}
void     HeroIllustratedWindow::CallInDetailedHeroInfo()
{
	//to do
	NFC_setNodeVisable(_HERO_BUFFER_DESC_NAME_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_EXPAND_BTN_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_EXPAND_LABEL_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_TIPS_MARK_BG_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_TIPS1_LABEL_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_TIPS2_LABEL_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_TIPS3_LABEL_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_TIPS4_LABEL_,GetRootNode(),false);
	NFC_setNodeVisable(_HERO_DESC_BTN_,GetRootNode(),true);
	NFC_setNodeVisable(_HERO_DESC_LABEL_,GetRootNode(),true); 
}

 
void	 HeroIllustratedWindow::UpdateChangeHeroBtnState()
{ 
	//to do
	IHeroSkinItem * pHeroSkinItem=NFC_GetHeroFromLib(m_nActiveHeroID);
	if (pHeroSkinItem&&pHeroSkinItem->getIsActived() && !NFC_IsHeroInTeam(pHeroSkinItem->getHeroUniqueID()) && HEROILLUSTRATEDDATAHANDLER->IsTeamHeroSame(m_nHeroPos, pHeroSkinItem))
	{  
		NFC_setEnabledForMenuItem(_HERO_CHANGE_BTN_,GetRootNode(),true);
	}
	else
	{
		NFC_setEnabledForMenuItem(_HERO_CHANGE_BTN_,GetRootNode(),false);
	}
}


void	 HeroIllustratedWindow::UpdateAdvanceHeroBtnState()
{ 
	//to do
	IHeroSkinItem * pHeroSkinItem=NFC_GetHeroFromLib(m_nActiveHeroID);
	if(pHeroSkinItem&&pHeroSkinItem->getIsActived())
	{  
	    if(HeroIllustratedDataHandler::get_instance2()->JudgeHeroAdvancedEnable(pHeroSkinItem))
		{
			NFC_setEnabledForMenuItem(_HERO_ADVANCE_BTN_,GetRootNode(),true);
			return ;
		}
	}
	NFC_setEnabledForMenuItem(_HERO_ADVANCE_BTN_,GetRootNode(),false);
}


void    HeroIllustratedWindow::DispatchUpdateEventHandler(int eventType)
{
	switch(eventType)
	{
	case  _UPDATE_FOR_HERO_EXPAND_TYPE_:
		{
			ShowHeroExpandInfoLayer();
			break;
		}
	case _UPDATE_FOR_SUCCESS_REPLACE_HERO_TYPE_:
		{
			PushEvent(_TYPED_EVNET_HIDE_HeroIllustratedWindow_);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		}
	case _UPDATE_FOR_ERROR_TYPE_:
		{
			//to do 暂无处理
			break;
		}
	case _UPDATE_FOR_ENTER_ADVANCE_TYPE_:
		{  
		    PushEvent(_TYPED_EVNET_HIDE_HeroIllustratedWindow_);
			EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_HeroAdvancedWindow_,_to_event_param_(m_nBackType));
			break;
		}
	case _UPDATE_FOR_HERO_SOUL_TYPE_:
		{
			PushEvent(_TYPED_EVNET_HIDE_HeroIllustratedWindow_);
			EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_HEROSOULWINDOW_);
			break;
		}
	default:
		break;
	}
}

void    HeroIllustratedWindow::CalActiveHeroCelllConfig(int illustrateType)
{  
	CheckCellListEmptyEvent(illustrateType);
	IHeroSkinItem * pHeroSkinItem= NFC_GetHeroFromLib(m_nActiveHeroID);
	if(pHeroSkinItem&&pHeroSkinItem->getHeroType()!=illustrateType&&illustrateType!=IHeroillustated_Base_Tag::_Illustrated_ALL_Type_)
	{	 
		m_nActiveCellIndex=-1;
		m_nActiveCellItemIndex= -1;
		return ;
	}
	bool isFindCellList=false;
	if(m_bIsShowAllDB)
	{
		size_t cellCount=CELLLISTFACTORY_ALL(illustrateType).size();
		for(size_t cellIndex=0;cellIndex<cellCount;cellIndex++)
		{ 
			if(!CELLLISTFACTORY_ALL(illustrateType).at(cellIndex)->getIsStarCellType())
			{  
				m_nHeroCellOffSetCount++;
				size_t cellItemCount=CELLLISTFACTORY_ALL(illustrateType).at(cellIndex)->getHeroVector().size();
				for(size_t cellItemIndex=0;cellItemIndex<cellItemCount;cellItemIndex++)
				{
					if(CELLLISTFACTORY_ALL(illustrateType).at(cellIndex)->getHeroVector().at(cellItemIndex)->getHeroUniqueID()==m_nActiveHeroID)
					{
						m_nActiveCellIndex=cellIndex;
						m_nActiveCellItemIndex= cellItemIndex;
						return ;
					}	
				}
			} 
			else
			{
				m_nStarCellOffSetCount++;
			}
		}
	}
	else
	{  
		size_t cellCount=CELLLISTFACTORY_SELF(illustrateType).size();
		for(size_t cellIndex=0;cellIndex<cellCount;cellIndex++)
		{ 
			if(!CELLLISTFACTORY_SELF(illustrateType).at(cellIndex)->getIsStarCellType())
			{ 
				m_nHeroCellOffSetCount++;
				size_t cellItemCount=CELLLISTFACTORY_SELF(illustrateType).at(cellIndex)->getHeroVector().size();
				for(size_t cellItemIndex=0;cellItemIndex<cellItemCount;cellItemIndex++)
				{
					if(CELLLISTFACTORY_SELF(illustrateType).at(cellIndex)->getHeroVector().at(cellItemIndex)->getHeroUniqueID()==m_nActiveHeroID)
					{
						m_nActiveCellIndex=cellIndex;
						m_nActiveCellItemIndex= cellItemIndex;
						return ;
					}	
				}
			} 
			else
			{ 
		    	m_nStarCellOffSetCount++;
			}
		}
	}
	if(!isFindCellList)
	{
		m_nActiveCellIndex=-1;
		m_nActiveCellItemIndex= -1;
	}
}

 
void    HeroIllustratedWindow::CheckCellListEmptyEvent(int illustrateType)
{  
	if(m_bIsShowAllDB)
	{
		SetCallNewHeroLayerVisiable(CELLLISTFACTORY_ALL(illustrateType).empty());
	}
	else
	{
		SetCallNewHeroLayerVisiable(CELLLISTFACTORY_SELF(illustrateType).empty());
	}
}

void    HeroIllustratedWindow::SetCallNewHeroLayerVisiable(bool isVisiable)
{ 
	NFC_setNodeVisable(_HERO_CALL_HERO_LABEL_,GetRootNode(),isVisiable);
}

void     HeroIllustratedWindow::UpdateHeroSoulBtnState()
{
	//更新战魂按钮的状态 
	IHeroSkinItem * pHeroSkinItem = NFC_GetHeroFromLib(m_nActiveHeroID);
	bool isExistHeroSoul = pHeroSkinItem->getIsExistHeroSoul();
	if(pHeroSkinItem&&pHeroSkinItem->getIsActived())
	{ 
		NFC_setMenuEnable(_HERO_HERO_SOUL_BTN_,GetRootNode(),true);
	}
	else
	{
		NFC_setMenuEnable(_HERO_HERO_SOUL_BTN_,GetRootNode(),false);
	} 
	/*if(RoleInfoDataHandler::get_instance2()->m_pRIData->level_ < pHeroSkinItem->getHeroSoulChallenegeLevel())
	{
	NFC_setMenuEnable(_HERO_HERO_SOUL_BTN_,GetRootNode(),false);
	} */
	NFC_setNodeVisable(_HERO_HERO_SOUL_BTN_,GetRootNode(),isExistHeroSoul); 
}



 