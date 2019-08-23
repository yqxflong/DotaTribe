#include "../include/PESoulEquipSubView.h"
#include "../include/NFControlsManager.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IWindow.h"
  
#include "../include/RoleEquipDataHandler.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"

#include "../include/HERoleInfoNode.h"
#include "../include/HEHeroPropertyNode.h"
 
#include "../include/IDStringDataManager.h"
#include "../include/CMenuItemSprite.h"
//
#include "../include/PESWindow.h" 
#include "../include/WindowManager.h"

#include "../include/DTHeroIcon.h"
#include "../include/SoulEquipPacket.h"
#include "../include/SoulTipsWindow.h"
#include "../include/HeroSoulPacket.h"
#include "../include/HeroSoulDataHandler.h"



USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
 
 

PESoulEquipSubView::PESoulEquipSubView()
{
	m_pTable = NULL;
	m_pSkeletonNode = NULL;
	m_pBottomNode = NULL;
	m_szCELL_ITEM = cocos2d::CCSizeZero; 

	m_RoleSoulsEquipInfo = NULL;
	m_vAllUnESoulBufferVector.clear();
	m_vPowerUnESoulBufferVector.clear();
	m_vQuickUnESoulBufferVector.clear();
	m_vInteligenceUnESoulBufferVector.clear();
	m_vEquipSoulBufferVector.clear();
	m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_ALL_Type_;

	m_bPowerSwitchOn = false;
	m_bQucikSwitchOn = false;
	m_bInteligenceSwitchOn = false; 
	m_nPlayerLevel = 0;
	m_nCurHeroIdx = -1;
	memset(m_ArraySoulType, 0, sizeof(m_ArraySoulType));
}

bool PESoulEquipSubView::onLoad(){
	if(CCNode::init()){
		this->autorelease();
		setPosition(CCPointZero);
		_initLayout();
		return true;
	}
	return false;
}

/*
刷新数据
*/
void PESoulEquipSubView::_refreshData(int idx)
{
	 //todo 
	IHeroSkinItem* pHeroSkin = NFC_GetTeamHero(idx);
	if (pHeroSkin == NULL)
		return;
	
	m_RoleSoulsEquipInfo = pHeroSkin->getSoulsEquipManager();
	m_vAllUnESoulBufferVector = RoleSoulsDataHandler::get_instance2()->getHeroSoulDataManger()->getRoleAllSoulsVector();
	m_vPowerUnESoulBufferVector = RoleSoulsDataHandler::get_instance2()->getHeroSoulDataManger()->getRolePowerSoulsVector();
	m_vQuickUnESoulBufferVector = RoleSoulsDataHandler::get_instance2()->getHeroSoulDataManger()->getRoleQuickSoulsVector();
	m_vInteligenceUnESoulBufferVector = RoleSoulsDataHandler::get_instance2()->getHeroSoulDataManger()->getRoleInteligenceSoulsVector();
	m_vEquipSoulBufferVector = pHeroSkin->getSoulsEquipManager()->getHeroSoulEquipList();
	m_ArraySoulType[IHeroSoulItem::_HeroSoul_Power_Type_] = RoleSoulsDataHandler::get_instance2()->SoulUnActivIndex(m_vPowerUnESoulBufferVector);
	m_ArraySoulType[IHeroSoulItem::_HeroSoul_Quick_Type_] = RoleSoulsDataHandler::get_instance2()->SoulUnActivIndex(m_vQuickUnESoulBufferVector);
	m_ArraySoulType[IHeroSoulItem::_HeroSoul_Inteligence_Type_] = RoleSoulsDataHandler::get_instance2()->SoulUnActivIndex(m_vInteligenceUnESoulBufferVector);
	m_ArraySoulType[IHeroSoulItem::_HeroSoul_ALL_Type_] = RoleSoulsDataHandler::get_instance2()->SoulUnActivIndex(m_vAllUnESoulBufferVector);
}

void PESoulEquipSubView::_initLayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSOULEQUIPVIEW,this);
	_mapBtn();  
	_createTableView();
	NFC_setNodeVisable(kBG,this,true);
	//_showHeroDetailNode();
}


void    PESoulEquipSubView::_refreshUIWithData()
{ 
	NFC_showCommunicationWating(false);
	//刷新战魂装备槽 
	size_t soulEquipSize = m_RoleSoulsEquipInfo->getHeroSoulEuipMaxCount();
	int  labelArray[] ={-1,kLEVEL_VALUE_2,kLEVEL_VALUE_3,kLEVEL_VALUE_4};
	int  lockBgArray[] ={-1,kLEVEL_BG_2,kLEVEL_BG_3,kLEVEL_BG_4};
	int  iconArray[]={kBOARD_1,kBOARD_2,kBOARD_3,kBOARD_4};
	COMMON_BEIGIN_ARRAY(size_t,soulEquipSize)
		DTHeroIcon * pDTHeroIcon = (DTHeroIcon *)this->getChildByTag(iconArray[index]);
		pDTHeroIcon->setHeroIconVisable(false);
		SoulEquipItem equipItem = m_RoleSoulsEquipInfo->getHeroSoulPosVector().at(index);
		if(!equipItem.m_uHeroSoulEquipIsOpen)
		{  
			if (RoleInfoDataHandler::get_instance2()->m_pRIData->level_ >= equipItem.m_uHeroSoulEquipOpenLevel)
			{
				NFC_setNodeVisable(labelArray[index],this,false);
				NFC_setNodeVisable(lockBgArray[index],this,true);
			}
			else
			{ 
				NFC_setLabelStringInt(labelArray[index],this,equipItem.m_uHeroSoulEquipOpenLevel,612,true);
				NFC_setNodeVisable(lockBgArray[index],this,true);
			}
		} 
		else
		{  
			NFC_setNodeVisable(labelArray[index],this,false);
			NFC_setNodeVisable(lockBgArray[index],this,false);
			char equipIndex=(char)index;
			_showEquipBuffer(equipIndex,iconArray[index]);
		}
	COMMON_END_ARRAY
		 
	_refreshSwithState();
	NFC_setNodeVisable(kBG,this,true);
}


void    PESoulEquipSubView::_showEquipBuffer(char  equipIndex,int uiIndex)
{
	size_t equipVectorSize = m_vEquipSoulBufferVector.size();
	COMMON_BEIGIN_ARRAY(size_t,equipVectorSize)
		if(m_vEquipSoulBufferVector.at(index)->getHeroSoulEquipIndex() == equipIndex)
		{
			DTHeroIcon * pDTHeroIcon =(DTHeroIcon *)this->getChildByTag(uiIndex);
			if(pDTHeroIcon)
			{
				pDTHeroIcon->setHeroIconID(m_vEquipSoulBufferVector.at(index)->getHeroSoulBufferIconID());
				return ;
			}
		}
	COMMON_END_ARRAY  
	NFC_setDTHeroIconVisiable(uiIndex,this,false);
}

void   PESoulEquipSubView::_refreshSwithState()
{ 
	NFC_setTabMenuState(kPOWERBTN,this,m_bPowerSwitchOn);
	NFC_setTabMenuState(kQUCIKBTN,this,m_bQucikSwitchOn);
	NFC_setTabMenuState(kINTELIGENBTN,this,m_bInteligenceSwitchOn); 

	unsigned int cellItemsCount = numberOfCellsInTableView(NULL);
	_refreshEmptySoulTips(cellItemsCount > 0 ? true:false);
	_refreshTableView(m_pTable);
}



void  PESoulEquipSubView::_refreshEmptySoulTips(bool isSoulEmpty)
{
	if(!isSoulEmpty)
	{ 
		NFC_setNodeVisable(kSoulEmptyTips,this,true);
		NFC_setNodeVisable(kSoulChallengeImage,this,true);
		NFC_setNodeVisable(kSoulChallengeLabel,this,true);
		NFC_setNodeVisable(kSoulChallengeBtn,this,true);
	}
	else
	{  
		NFC_setNodeVisable(kSoulEmptyTips,this,false);
		NFC_setNodeVisable(kSoulChallengeImage,this,false);
		NFC_setNodeVisable(kSoulChallengeLabel,this,false);
		NFC_setNodeVisable(kSoulChallengeBtn,this,false);
	} 
}  

void PESoulEquipSubView::_refreshHeroNameAndStarLv(int index)
{
	int quality=NFC_GetTeamHero(index)->getHeroQualiy();
	string name=NFC_GetTeamHero(index)->getHeroName();
	//star
	CCardsStarProgress* cc=(CCardsStarProgress*)NFC_getNode(kSTAR,this);
	cc->SetCurcount(quality+1);
	//name
	NFC_setLabelString(kNAME,this,name);
}

void PESoulEquipSubView::_refreshHeroByIdx(int idx)
{
	_refreshData(idx);
	_refreshUIWithData();
	_refreshHeroNameAndStarLv(idx);
	_refreshHeroShape(idx);
}

void PESoulEquipSubView::_mapBtn(){
	NFC_bindSelectorForDTHeroIcon(kBOARD_1,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));
	NFC_bindSelectorForDTHeroIcon(kBOARD_2,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));
	NFC_bindSelectorForDTHeroIcon(kBOARD_3,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));
	NFC_bindSelectorForDTHeroIcon(kBOARD_4,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));

	NFC_bindSelectorForBtn(kPOWERBTN,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));
	NFC_bindSelectorForBtn(kQUCIKBTN,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));
	NFC_bindSelectorForBtn(kINTELIGENBTN,this,this,menu_selector(PESoulEquipSubView::On_Click_Event)); 
	NFC_bindSelectorForBtn(kSoulChallengeBtn,this,this,menu_selector(PESoulEquipSubView::On_Click_Event));  
	 
}

bool PESoulEquipSubView::onDestroy(){
	memset(m_ArraySoulType, 0, sizeof(m_ArraySoulType));
	m_nPlayerLevel = 0; 
	UIVIEWDATAMANAGER->clearData();
	m_pSkeletonNode->removeFromParentAndCleanup(true);
	m_pSkeletonNode=0;
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}

bool PESoulEquipSubView::onTick(){
	return true;
}

void PESoulEquipSubView::onChangeTabIndex(int idx){
	if (m_nCurHeroIdx==idx||!NFC_HasTeamHero(idx))
		return;
	m_nCurHeroIdx=idx;
	_refreshHeroByIdx(idx);
}

void PESoulEquipSubView::_refreshHeroShape(int idx){
	m_nPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
	CCNode* node=this->getChildByTag(kHERO);
	if(m_pSkeletonNode) 
		m_pSkeletonNode->removeFromParentAndCleanup(true); 
	int shapeID=NFC_GetTeamHero(idx)->getHeroShapeID();
	assert(shapeID>=0);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	if(m_pSkeletonNode) 
		m_pSkeletonNode->setAnimation("DaiJi", true); 
	m_pSkeletonNode->setAnchorPoint(node->getAnchorPoint());
	m_pSkeletonNode->setPosition(node->getPosition());
	this->addChild(m_pSkeletonNode,node->getZOrder()); 	
}
  

//////////////////////////////////////////////////////////////////////////
void    PESoulEquipSubView::createTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSOULEQUIPCELL,pTableCell);
}

void    PESoulEquipSubView::setTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{      
	switch(m_nCurSoulBufferType)
	{
	case IHeroSoulItem::_HeroSoul_Power_Type_:
		{    
		setCellWithData(m_vPowerUnESoulBufferVector.at(cellIndex), pTableCell, cellIndex, IHeroSoulItem::_HeroSoul_Power_Type_);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Quick_Type_:
		{  
		setCellWithData(m_vQuickUnESoulBufferVector.at(cellIndex), pTableCell, cellIndex, IHeroSoulItem::_HeroSoul_Quick_Type_);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Inteligence_Type_:
		{
		setCellWithData(m_vInteligenceUnESoulBufferVector.at(cellIndex), pTableCell, cellIndex, IHeroSoulItem::_HeroSoul_Inteligence_Type_);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_ALL_Type_:
		{
		setCellWithData(m_vAllUnESoulBufferVector.at(cellIndex), pTableCell, cellIndex, IHeroSoulItem::_HeroSoul_ALL_Type_);
			break;
		}
	default: 
		break;
	}
} 
  
void  PESoulEquipSubView::On_Cell_Click_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{   
		CCLOG("CELL BTN Handler : %d",pMenuItemSprite->getIDX());  
		_handlerUnEquipSoulWithCellIndex(pMenuItemSprite->getIDX());
	}
}
 
void  PESoulEquipSubView::On_Cell_Tips_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{     
		_handlerUnEquipBufferTips(pMenuItemSprite->getIDX());
	}
}

void  PESoulEquipSubView::On_Cell_UpSoulLevel_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)pSender;
	if (pMenuItemSprite)
	{
		_handlerUpSoulLevel(pMenuItemSprite->getIDX());
	}
}

void    PESoulEquipSubView::setCellWithData(IHeroSoulItem * pSoulItem, cocos2d::extension::CCTableViewCell * pTableCell, int cellIndex, int type)
{
	if(pTableCell&&pSoulItem)
	{ 
		NFC_setNodeVisable(kCELLUPSOULLEVELBTN, pTableCell,true);
		NFC_setNodeVisable(kCELLUNACTIVITTF, pTableCell, true);
		NFC_setNodeVisable(kCELLUNACTIVITITLE, pTableCell, true);
		NFC_bindSelectorForCellDTHeroIcon(kCELLBOARD,cellIndex,pTableCell,this,menu_selector(PESoulEquipSubView::On_Cell_Tips_Event));
		NFC_setDTHeroIcon(kCELLBOARD,pTableCell,pSoulItem->getHeroSoulBufferIconID(),true);
		NFC_setLabelString(kCELLTALENTNAME,pTableCell,pSoulItem->getHeroSoulBufferName(),true);
		NFC_bindSelectotForCellBtn(kCELLUPSOULLEVELBTN, cellIndex, pTableCell, this, menu_selector(PESoulEquipSubView::On_Cell_UpSoulLevel_Event));//等级提升按钮
		NFC_bindSelectotForCellBtn(kCELLEQUIPBTN,cellIndex,pTableCell,this,menu_selector(PESoulEquipSubView::On_Cell_Click_Event));
		if (pSoulItem->getHeroSoulCurLevel() == 0)
		{
			NFC_setNodeVisable(kCELLUPSOULLEVELBTN, pTableCell, false);
		}
		else if (pSoulItem->getHeroSoulCurLevel() == pSoulItem->getHeroSoulMaxLevel())
		{
			NFC_setNodeVisable(kCELLUPSOULLEVELBTN, pTableCell, false);
		}
		else
		{
			NFC_setNodeVisable(kCELLUPSOULLEVELBTN, pTableCell, true);
		}
		char buff[1024] = { 0 };
		char buff1[1024] = { 0 };
		if (pSoulItem->getHeroSoulCurLevel() == 0)
		{
			sprintf(buff, SysLangDataManager::get_instance2()->GetSysLangById(6091).c_str());
			sprintf(buff1, SysLangDataManager::get_instance2()->GetSysLangById(6092).c_str());
		}
		else
		{
			sprintf(buff, "LV.%d", pSoulItem->getHeroSoulCurLevel());
			sprintf(buff1, SysLangDataManager::get_instance2()->GetSysLangById(6094).c_str());
		}
		NFC_setLabelString(kCELLATRIBUTENAME, pTableCell, buff, true);
		NFC_setLabelString(kCELLEQUIPLABEL, pTableCell, buff1);
		if (m_ArraySoulType[type] != cellIndex)
		{
			NFC_setNodeVisable(kCELLUNACTIVITTF, pTableCell, false);
			NFC_setNodeVisable(kCELLUNACTIVITITLE, pTableCell, false);
		}
	}
}

cocos2d::CCSize PESoulEquipSubView::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	if (m_ArraySoulType[m_nCurSoulBufferType] == idx)
	{
		return  CCSizeMake(m_szCELL_ITEM.width, m_szCELL_ITEM.height + 60.0f);
	}
	else
	{
		return m_szCELL_ITEM;
	}
	
}

cocos2d::extension::CCTableViewCell*  PESoulEquipSubView::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	cocos2d::extension::CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new cocos2d::extension::CCTableViewCell();
		cell->autorelease();
		createTableCell(cell);
	}
	setTableCell(cell,idx);
	return cell;
}

unsigned int PESoulEquipSubView::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{ 
	switch(m_nCurSoulBufferType)
	{
	case IHeroSoulItem::_HeroSoul_Power_Type_:
		{ 
			return m_vPowerUnESoulBufferVector.size();
		}
	case  IHeroSoulItem::_HeroSoul_Quick_Type_:
		{ 
			return m_vQuickUnESoulBufferVector.size();
		}
	case  IHeroSoulItem::_HeroSoul_Inteligence_Type_:
		{
			return m_vInteligenceUnESoulBufferVector.size();
		}
	case  IHeroSoulItem::_HeroSoul_ALL_Type_:
		{
			return m_vAllUnESoulBufferVector.size();
		}
	default:
		return 0;
	}
} 

//////////////////////////////////////////////////////////////////////////
/*
设置TableView
*/
void PESoulEquipSubView::_createTableView(){
	//准备cell大小
	CCNode* node=this->getChildByTag(kTABLECELL);
	m_szCELL_ITEM=node->getContentSize(); 
	//设置table
	m_pTable=(CCTableView*)this->getChildByTag(kTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}
 

//显示英雄信息
void PESoulEquipSubView::_showHeroInfoNode(){
	if (m_pBottomNode)
	{
		m_pBottomNode->removeFromParent();
		m_pBottomNode=NULL;
	}
	CCNode* bottomNode=NFC_getNode(kBOTTOM_NODE,this);
	m_pBottomNode=HERoleInfoNode::create();
	m_pBottomNode->setZOrder(bottomNode->getZOrder());
	m_pBottomNode->setPosition(bottomNode->getPosition());
	this->addChild(m_pBottomNode);
}

//显示英雄详细信息
void PESoulEquipSubView::_showHeroDetailNode(){
	if (m_pBottomNode)
	{
		m_pBottomNode->removeFromParent();
		m_pBottomNode=NULL;
	}
	CCNode* bottomNode=NFC_getNode(kBOTTOM_NODE,this);
	m_pBottomNode=HEHeroPropertyNode::create();
	m_pBottomNode->setZOrder(bottomNode->getZOrder());
	m_pBottomNode->setPosition(bottomNode->getPosition());
	this->addChild(m_pBottomNode);
}
 
/*
主窗口的通知
*/
void PESoulEquipSubView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList){
	if(iEventType == _TYPED_EVENT_UPDATE_HEROSOUL_VIEW_)
	{ 
		int receiptCode = atoi(paramList.begin()->c_str());
		_dispatchEventHandler(receiptCode);
		return ;
	}
	if (m_pBottomNode){
		m_pBottomNode->EventWindowCallBack(iEventType,paramList);
	}
}


void  PESoulEquipSubView::On_Click_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItemSprite =(CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{
		switch(pMenuItemSprite->getIDX())
		{
		case kBOARD_1: 
			{ 
				_handlerEquipClick(0);
				break;
			}
		case kBOARD_2:
			{
				_handlerEquipClick(1);
				break;
			}
		case kBOARD_3:
			{
				_handlerEquipClick(2);
				break;
			}
		case kBOARD_4:
			{
				_handlerEquipClick(3);
				break;
			} 
		case kPOWERBTN:
			{ 
				m_bPowerSwitchOn = ! m_bPowerSwitchOn;
				m_bQucikSwitchOn = false;
				m_bInteligenceSwitchOn = false;
				if(m_bPowerSwitchOn)
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_Power_Type_;
				}
				else
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_ALL_Type_;
				}
				_refreshSwithState();
				break;
			}
		case kQUCIKBTN:
			{
				m_bQucikSwitchOn = ! m_bQucikSwitchOn;
				m_bPowerSwitchOn = false;
				m_bInteligenceSwitchOn = false;
				if(m_bQucikSwitchOn)
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_Quick_Type_;
				}
				else
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_ALL_Type_;
				} 
				_refreshSwithState();
				break;
			}
		case kINTELIGENBTN:
			{
				m_bInteligenceSwitchOn = ! m_bInteligenceSwitchOn;
				m_bPowerSwitchOn = false;
				m_bQucikSwitchOn = false;
				if(m_bInteligenceSwitchOn)
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_Inteligence_Type_;
				}
				else
				{
					m_nCurSoulBufferType = IHeroSoulItem::_HeroSoul_ALL_Type_;
				} 
				_refreshSwithState();
				break;
			}
		case kSoulChallengeBtn:
			{ 
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_, _to_event_param_(IWindow::_TYPED_WINDOW_PESWINDOW_), _to_event_param_(m_nCurHeroIdx));
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
				break;
			}
		default:
			break;
		}
	} 
}


void    PESoulEquipSubView::_handlerEquipClick(char equipIndex)
{
	//首先判断是否开启 
	size_t soulEquipSize = m_RoleSoulsEquipInfo->getHeroSoulEuipMaxCount();
	COMMON_BEIGIN_ARRAY(size_t,soulEquipSize)
		SoulEquipItem equipItem = m_RoleSoulsEquipInfo->getHeroSoulPosVector().at(index);
		if(equipItem.m_uHeroSoulEquipIndex == equipIndex)
		{
			if(equipItem.m_uHeroSoulEquipIsOpen)
			{
				//搜索是否安装 
				_handlerEquipSoulWithIndex(equipIndex);
			}
			else if (RoleInfoDataHandler::get_instance2()->m_pRIData->level_ >= equipItem.m_uHeroSoulEquipOpenLevel)
			{
				//请求开锁
				C2SUnLockHeroSoulPacket unLockHeroSoul(equipIndex, m_nCurHeroIdx);
				unLockHeroSoul.Send();
			}
			else
			{
				//提示等级不够  
				char commonStr[128]={0};
				std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_COMMON_LESS_LEVEL_TIPS_);
				sprintf(commonStr,advanceTips.c_str(),equipItem.m_uHeroSoulEquipOpenLevel);
				NFC_showMessageBoxSingle(kDEFAULT,commonStr);
				return ;
			}
			return ;
		}
	COMMON_END_ARRAY 
}

void   PESoulEquipSubView::_handlerEquipSoulWithIndex(char equipIndex)
{
	size_t equipBufferSize = m_vEquipSoulBufferVector.size();
	COMMON_BEIGIN_ARRAY(size_t,equipBufferSize)
		if(m_vEquipSoulBufferVector.at(index)->getHeroSoulEquipIndex() == equipIndex)
		{
			 //显示Tips 
			_handlerEquipBufferTips(m_vEquipSoulBufferVector.at(index)->getHeroSoulBufferID(),_SOUL_HERO_TYPE_);
			return ;
		}
	COMMON_END_ARRAY
	  
}



void  PESoulEquipSubView::_handlerUnEquipSoulWithCellIndex(int cellIndex)
{
	IHeroSoulItem * pWillEquipSoulItem = NULL;
	switch(m_nCurSoulBufferType)
	{
	case IHeroSoulItem::_HeroSoul_Power_Type_:
		{ 
			pWillEquipSoulItem = m_vPowerUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Quick_Type_:
		{ 
			pWillEquipSoulItem = m_vQuickUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Inteligence_Type_:
		{
			pWillEquipSoulItem = m_vInteligenceUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_ALL_Type_:
		{
			pWillEquipSoulItem = m_vAllUnESoulBufferVector.at(cellIndex);
			break;
		}
	default:
		 break;
	}
	if(pWillEquipSoulItem)
	{
		if (pWillEquipSoulItem->getHeroSoulCurLevel() == 0)
		{
			C2SHeroSoulPacket heroSoulPacket(pWillEquipSoulItem->getHeroID());
			heroSoulPacket.Send();
			HeroSoulDataHandler::get_instance2()->setRequestHeroID(pWillEquipSoulItem->getHeroID());
			HeroSoulDataHandler::get_instance2()->setBackTab(m_nCurHeroIdx * 2 + PESWindow::kTAB_1);
		}
		else
		{
			//发送安装请求 
			_handlerEquipSoule(pWillEquipSoulItem->getHeroSoulBufferID());
		}
	}
}


void   PESoulEquipSubView::_handlerUnEquipBufferTips(int cellIndex)
{
	IHeroSoulItem * pWillEquipSoulItem = NULL;
	switch(m_nCurSoulBufferType)
	{
	case IHeroSoulItem::_HeroSoul_Power_Type_:
		{ 
			pWillEquipSoulItem = m_vPowerUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Quick_Type_:
		{ 
			pWillEquipSoulItem = m_vQuickUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_Inteligence_Type_:
		{
			pWillEquipSoulItem = m_vInteligenceUnESoulBufferVector.at(cellIndex);
			break;
		}
	case  IHeroSoulItem::_HeroSoul_ALL_Type_:
		{
			pWillEquipSoulItem = m_vAllUnESoulBufferVector.at(cellIndex);
			break;
		}
	default:
		break;
	}
	if(pWillEquipSoulItem)
	{
		 //to do
		//显示Tips
		_handlerEquipBufferTips(pWillEquipSoulItem->getHeroSoulBufferID(), _SOUL_DB_TYPE_);
	}
}



void   PESoulEquipSubView::_dispatchEventHandler(int receiptCode)
{
	switch(receiptCode)
	{
	case 0:
		{   
			//解锁
			_refreshUIWithData();
			break;
		}
	case 1:
		{ 
			//装备
			_refreshData(m_nCurHeroIdx);
			_refreshUIWithData();
			break;
		}
	case 2:
		{
			//卸载
			_refreshData(m_nCurHeroIdx);
			_refreshUIWithData();
			break;
		}
	default:
		break;
	}
}


void    PESoulEquipSubView::_handlerEquipBufferTips(int souleBufferID, int type)
{ 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SOULTIPSWINDOW_,_to_event_param_(souleBufferID),_to_event_param_(_SOULTIPS_OWNER_),_to_event_param_(m_nCurHeroIdx),_to_event_param_(type));
}
 
/*
装置战魂
*/
void    PESoulEquipSubView::_handlerEquipSoule(int soulBufferID)
{
	C2SEquipHeroSoulPacket   equipSoulPacket(m_nCurHeroIdx,soulBufferID);
	equipSoulPacket.Send();
}


void    PESoulEquipSubView::_handlerUpSoulLevel(int cellIndex)
{
	IHeroSoulItem * pWillEquipSoulItem = NULL;
	switch (m_nCurSoulBufferType)
	{
	case IHeroSoulItem::_HeroSoul_Power_Type_:
	{
		pWillEquipSoulItem = m_vPowerUnESoulBufferVector.at(cellIndex);
		break;
	}
	case  IHeroSoulItem::_HeroSoul_Quick_Type_:
	{
		pWillEquipSoulItem = m_vQuickUnESoulBufferVector.at(cellIndex);
		break;
	}
	case  IHeroSoulItem::_HeroSoul_Inteligence_Type_:
	{
		pWillEquipSoulItem = m_vInteligenceUnESoulBufferVector.at(cellIndex);
		break;
	}
	case  IHeroSoulItem::_HeroSoul_ALL_Type_:
	{
		pWillEquipSoulItem = m_vAllUnESoulBufferVector.at(cellIndex);
		break;
	}
	default:
		break;
	}
	if (pWillEquipSoulItem)
	{
		C2SHeroSoulPacket heroSoulPacket(pWillEquipSoulItem->getHeroID());
		heroSoulPacket.Send();
		HeroSoulDataHandler::get_instance2()->setRequestHeroID(pWillEquipSoulItem->getHeroID());
		HeroSoulDataHandler::get_instance2()->setBackTab(m_nCurHeroIdx * 2 + PESWindow::kTAB_1);
	}

}