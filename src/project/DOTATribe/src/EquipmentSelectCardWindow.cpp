//Name：EquipMentSelectWindow
//Function：选择装备素材
//Written By：尹强

#include "../include/EquipmentSelectCardWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/IDStringDataManager.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/CSMapTable.h"
#include "../include/GuideSystem.h"
#include "../include/DTEquipBoard.h"

using namespace std;

USING_NS_CC;                                                                                  
USING_NS_CC_EXT;

EquipmentSelectCardWindow::EquipmentSelectCardWindow()
:m_pWRootNode(0)
,m_nShowWindow(0)
,m_nCurCount(0)
,m_nTotalCount(0)
{
	m_WindowType   = _TYPED_WINDOW_EQUIPMENTSELECTCARD_;
}

bool EquipmentSelectCardWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_EQUIPSELECTCARDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_EQUIPSELECTCARDWINDOW_, true);

	return IWindow::Init();
}

bool EquipmentSelectCardWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;



		_initData();
		_initLayout();
		_mapTable();
		_mapBtn();
		_checkTickAll();
		_showCurTickCount();
		return true;
	} 
	while (false);

	return false;
}

void EquipmentSelectCardWindow::Tick()
{
	IWindow::Tick();
}

void EquipmentSelectCardWindow::Destroy()
{
	IWindow::Destroy();
}

void EquipmentSelectCardWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_EQUIPSELECTCARDWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_EQUIPSELECTCARDWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void EquipmentSelectCardWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void EquipmentSelectCardWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	Destroy();
}

void EquipmentSelectCardWindow::_initLayout(){
	m_pWRootNode = CCNode::create();
	m_pRootNode->addChild(m_pWRootNode, 10);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPMENTSELECTCARDWINDOW, m_pWRootNode);
}

void EquipmentSelectCardWindow::_mapBtn()
{
	//okbtn
	CMenuItemSprite* cc= (CMenuItemSprite*)NFC_getMenuItem(udCONFIRMBTN,m_pWRootNode);
	cc->setIDX(udCONFIRMBTN);
	cc->setTarget(this,menu_selector(EquipmentSelectCardWindow::On_Click_Event));
	//close
	cc= (CMenuItemSprite*)(CMenuItemSprite*)NFC_getMenuItem(udCLOSEBTN,m_pWRootNode);
	cc->setIDX(udCLOSEBTN);
	cc->setTarget(this,menu_selector(EquipmentSelectCardWindow::On_Click_Event));
	//Toggle
	for (int i=udTOGGLE1;i<=udTOGGLE3;i++)
	{
		cc= (CMenuItemSprite*)NFC_getMenuItem(i,m_pWRootNode);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(EquipmentSelectCardWindow::On_Toggle_Click_Event));
	}
}

void EquipmentSelectCardWindow::_initData()
{
	BAGEQUIPDATAHANDLER->reorderBagEquips_equiplvup_costcards();
	m_vecCardList=EQUIPMENTLVUPDATAHANDLER->GetEquipCostCardList();
	m_nTotalCount = (int)m_vecCardList.size();
}

cocos2d::CCSize EquipmentSelectCardWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_nCellSize;
}

void EquipmentSelectCardWindow::_createTableCell(cocos2d::extension::CCTableViewCell * cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPMENTSELECTCARDWINDOWCELL, cell);
}

void EquipmentSelectCardWindow::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
{
	int index = idx * 3;
	CMenuItemSprite* item=NULL;
	//列1
	if(index >= (int)m_vecCardList.size())
	{
		_setBlockVisiable(cell, index++, false);
	}
	else
	{
		_setBlockVisiable(cell, index, true);
		item = (CMenuItemSprite *)NFC_getMenuItem(cellBG1,cell);
		item->setIDX(index);
		_setBlockInfo(cell, index++);
		item->setTarget(this, menu_selector(EquipmentSelectCardWindow::On_Click_Block));
	}
	
	//列2
	if(index >= (int)m_vecCardList.size())
	{
		_setBlockVisiable(cell, index++, false);
	}
	else
	{
		_setBlockVisiable(cell, index, true);
		item = (CMenuItemSprite *)NFC_getMenuItem(cellBG2,cell);
		item->setIDX(index);
		_setBlockInfo(cell, index++);
		item->setTarget(this, menu_selector(EquipmentSelectCardWindow::On_Click_Block));
	}
	
	//列3
	if(index >= (int)m_vecCardList.size())
	{
		_setBlockVisiable(cell, index++, false);
	}
	else
	{
		_setBlockVisiable(cell, index, true);
		item = (CMenuItemSprite *)NFC_getMenuItem(cellBG3,cell);
		item->setIDX(index);
		_setBlockInfo(cell, index++);
		item->setTarget(this, menu_selector(EquipmentSelectCardWindow::On_Click_Block));
	}

}

void EquipmentSelectCardWindow::_setBlockInfo(cocos2d::CCNode * block, int idx)
{
	EquipCardsStructure & ecs = m_vecCardList[idx];
 	BagEquipData * bed = ecs.data;
 	char temp[128];
 	//Item
 	DTEquipBoard * board = (DTEquipBoard *)block->getChildByTag(cellITEMBOARD1 + idx % 3);
	board->SetEquip(kHETYPE_ELIST,bed,NULL);

	//设置装备名字+进阶级别
	if(bed->advanceLevel_>0){
		char tmp[128]="";
		string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
		sprintf(tmp,sys.c_str(),bed->template_->name_.c_str(),bed->advanceLevel_);
		NFC_setLabelString(cellNAME1+idx%3,block,tmp);
	}else{
		NFC_setLabelString(cellNAME1+idx%3,block,bed->template_->name_);
	}
 
 	//类型
 	CCLabelTTF* ttf = (CCLabelTTF *)block->getChildByTag(cellTYPE1+idx%3);
 	std::string ss = IDStringDataManager::get_instance2()->GetIDStringByID(1, bed->template_->type_);
 	sprintf(temp, "%s", ss.c_str());
 	ttf->setString(temp);
 
	//选中勾号
	NFC_showNode(cellSELECT1 + idx % 3,block,ecs.isSelected);

	//当前背景框是否被选中
	CCMenu* menu=(CCMenu*)block->getChildByTag(cellBG1 + idx % 3);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	if (ecs.isSelected)
		cc->selected(true);
	else
		cc->unselected();
	
	//设置选中勾号是否显示
	_setSelectPicVisible(block, idx, ecs.isSelected);

	//设置星级
	_setBlockStar(cellSTAR1+idx%3,block,bed);
}

void EquipmentSelectCardWindow::_setBlockStar( int key,cocos2d::CCNode * block,BagEquipData* bb){
	NFC_setCardsStarLevel(key,block,bb->template_->quality_+1);
}

void EquipmentSelectCardWindow::_setSelectPicVisible(cocos2d::CCNode * cell, int idx, bool visible)
{
	NFC_showNode(cellSELECT1 + idx % 3,cell,visible);
}


void EquipmentSelectCardWindow::_mapTable(){
	CCNode* cc=m_pWRootNode->getChildByTag(hTABLECELL);
	m_nCellSize=cc->getContentSize();
	//
	m_pTable =(CCTableView*)m_pWRootNode->getChildByTag(hTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);

}

void EquipmentSelectCardWindow::_setBlockVisiable(cocos2d::CCNode * block, int blockidx, bool visable)
{
	blockidx%=3;
	NFC_showNode(cellBG1 +blockidx,block,visable);
	NFC_showNode(cellITEMBOARD1 + blockidx,block,visable);
	NFC_showNode(cellNAME1 + blockidx,block,visable);
	NFC_showNode(cellTYPE1 + blockidx,block,visable);
	NFC_showNode(cellSELECT1_BG + blockidx,block,visable);
	NFC_showNode(cellSELECT1 + blockidx,block,false);
	NFC_showNode(cellSTAR1+blockidx,block,visable);
}

void EquipmentSelectCardWindow::On_Click_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (cc->getIDX()==udCONFIRMBTN)
	{
		//清空选择的卡片
		EQUIPMENTLVUPDATAHANDLER->needMoneyAll=0;
		EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.clear();
		//
		for(int i = 0; i < (int)m_vecCardList.size(); ++i)
		{
			int ecs = m_vecCardList[i].data->id_;
			if( m_vecCardList[i].isSelected)
			{
				EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.push_back(ecs);
			}
		}
		//此处需要和服务器通讯计算金钱等
		EQUIPMENTLVUPDATAHANDLER->toServerSelectCard();	
		//==============新手引导================
		GUIDESYSTEM->Next();
	}else if(cc->getIDX()==udCLOSEBTN){
	
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPSELECTCARDWINDOW_);
	EVENTSYSTEM->PushEvent(_TEPED_EVENT_EQUIPLVUP_AFTER_CHOOSECOST_);
}

void EquipmentSelectCardWindow::On_Toggle_Click_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * cis = (CMenuItemSprite *)pSender;

	bool haveThoseCard = false;

	if(udTOGGLE1 == cis->getIDX())
	{	
		if(false == cis->getIsSeleted())
		{
			//全选1星卡牌
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(ecs.data->template_->quality_ ==kCARD_1_STAR)
				{
					ecs.isSelected = true;
					haveThoseCard = true;
				}
			}
		}
		else{//取消
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(ecs.data->template_->quality_ ==kCARD_1_STAR)
				{
					ecs.isSelected = false;
					haveThoseCard = true;
				}
			}
		}
	}
	else if(udTOGGLE2 == cis->getIDX()){
		if(false == cis->getIsSeleted())
		{
			//全选2星
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(kCARD_2_STAR == ecs.data->template_->quality_)
				{
					ecs.isSelected = true;
					haveThoseCard = true;
				}
			}
		}
		else{	//取消
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(kCARD_2_STAR == ecs.data->template_->quality_)
				{
					ecs.isSelected = false;
					haveThoseCard = true;
				}
			}
		}
	}else if(udTOGGLE3 == cis->getIDX()){	
		if(false == cis->getIsSeleted())
		{
			//全选3星卡牌
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(ecs.data->template_->quality_ ==kCARD_3_STAR)
				{
					ecs.isSelected = true;
					haveThoseCard = true;
				}
			}
		}
		else{//取消
			for(int i = 0; i < (int)m_vecCardList.size(); ++i)
			{
				EquipCardsStructure & ecs = m_vecCardList[i];
				if(ecs.data->template_->quality_ ==kCARD_3_STAR)
				{
					ecs.isSelected = false;
					haveThoseCard = true;
				}
			}
		}
	}

	//设置选中
	if(cis->getIsSeleted())
	{
		cis->unselected();
		cis->setIsSelected(false);
	}
	else 
	{
		if(haveThoseCard)
		{
			cis->selected(true);
			cis->setIsSelected(true);
		}
	}


	NFC_refreshTableView(m_pTable);
	_showCurTickCount();
}

void EquipmentSelectCardWindow::On_Click_Block(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int idx = item->getIDX();
	EquipCardsStructure & ecs = m_vecCardList[idx];
	if(ecs.isSelected == true)
	{
		ecs.isSelected = false;
		item->setIsSelected(false);
		item->unselected();
		cocos2d::extension::CCTableViewCell * cell = m_pTable->cellAtIndex(idx / 3);
		if(cell)
		{
			_setSelectPicVisible(cell, idx, false);
		}
	}
	else
	{
		ecs.isSelected = true;
		item->setIsSelected(true);
		item->selected(true);
		cocos2d::extension::CCTableViewCell * cell = m_pTable->cellAtIndex(idx / 3);
		if(cell)
		{
			_setSelectPicVisible(cell, idx, true);
		}
	}
	_checkTickAll();
//=====新手引导======
	GUIDESYSTEM->Next();

	_showCurTickCount();
}

	/*
		检查全选状态
	*/
void EquipmentSelectCardWindow::_checkTickAll(){
	//判断是否某种颜色全部选择
	bool all_1_star= true;
	bool all_2_star = true;
	bool all_3_star = true;
	bool have_1_star= false;
	bool have_2_star= false;
	bool have_3_star= false;
	for(int i = 0; i < (int)m_vecCardList.size(); ++i)
	{
		EquipCardsStructure & ecs = m_vecCardList[i];
		if(ecs.data->template_->quality_ ==kCARD_1_STAR)
		{
			have_1_star = true;
			if(false == ecs.isSelected)
				all_1_star = false;
		}else if(ecs.data->template_->quality_ ==kCARD_2_STAR){
			have_2_star = true;
			if(false == ecs.isSelected)
				all_2_star = false;
		}else if(ecs.data->template_->quality_ == kCARD_3_STAR){
			have_3_star = true;
			if(false == ecs.isSelected)
				all_3_star = false;
		}
	}
	_setToggleSelect(udTOGGLE1, all_1_star&&have_1_star);
	_setToggleSelect(udTOGGLE2, all_2_star&&have_2_star);
	_setToggleSelect(udTOGGLE3, all_3_star&&have_3_star);
}

void EquipmentSelectCardWindow::_setToggleSelect(int key, bool selected)
{
	CMenuItemSprite * cc= (CMenuItemSprite*)NFC_getMenuItem(key,m_pWRootNode);
	if(selected)
	{
		cc->selected(true);
		cc->setIsSelected(true);
	}
	else
	{
		cc->unselected();
		cc->setIsSelected(false);
	}
}

cocos2d::extension::CCTableViewCell* EquipmentSelectCardWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(cell,idx);

	return cell;

}

unsigned int EquipmentSelectCardWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	int num = m_vecCardList.size();
	int count = num / 3;
	int rest = num % 3;
	if(rest > 0)
		++count;

	return count;
}

	/*
		获取当前选中的数量
	*/
void EquipmentSelectCardWindow::_checkCurTickCount(){
	m_nCurCount=0;
	for (int i=0;i<(int)m_vecCardList.size();i++)
	{
		EquipCardsStructure &cs=m_vecCardList[i];
		if (cs.isSelected)
			m_nCurCount++;
	}
}

	/*
		显示当前选中数量
	*/
void EquipmentSelectCardWindow::_showCurTickCount(){
	_checkCurTickCount();
	char tmp[128];
	sprintf(tmp,"%d/%d",m_nCurCount,m_nTotalCount);
	NFC_setLabelString(hCOUNTER,m_pWRootNode,tmp);
}