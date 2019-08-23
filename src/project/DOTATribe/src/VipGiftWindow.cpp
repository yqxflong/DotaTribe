//Name:VipGiftWindow
//Author: lvyunlong
//Func: Activity of vip gift
//Maintainer:lvyunlong


#include "../include/VipGiftWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/EffectDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/ActivityDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

VipGiftWindow::VipGiftWindow()
	:m_pTable(NULL),
	m_CurWindowActiviId(0),
	m_CurBuyVipLevel(0)
{
	m_WindowType   = _TYPED_WINDOW_VIPGIFTWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

VipGiftWindow::~VipGiftWindow()
{

}


void VipGiftWindow::_initLayout()
{
	_initControl();
	_initCell();
}

void VipGiftWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kVIPGIFTWINDOW,m_pRootNode);
}

void VipGiftWindow::_initCell()
{
	CCNode* cell = NFC_getNode(udTABLECELL,m_pRootNode);
	m_szCellGift = cell->getContentSize();
}

void VipGiftWindow::_mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	//绑定预览
	NFC_bindSelectotForCellBtn(CELL_GIFTBOXBTN,idx,cell,this,menu_selector(VipGiftWindow::On_CheckItem_Click));
	//绑定购买
	NFC_bindSelectotForCellBtn(CELL_BUYBTN,idx,cell,this,menu_selector(VipGiftWindow::On_Click_Buy_Enevnt));
}

bool  VipGiftWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_VIPGIFTWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_VIPGIFTWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_VIPGIFTWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_BACKQA_VIPGIFTWINDOW_, true);
	return IWindow::Init();
}

bool  VipGiftWindow::Load()
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

void  VipGiftWindow::Tick()
{
	IWindow::Tick();
}

void  VipGiftWindow::Destroy()
{
	m_pTable = NULL;
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}

	IWindow::Destroy();
}

void  VipGiftWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_VIPGIFTWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_VIPGIFTWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_VIPGIFTWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_BACKQA_VIPGIFTWINDOW_)
	{
		OnBackQAWindowEventHandler(paramList);
	}
}

void   VipGiftWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		m_CurWindowActiviId = atoi(paramList.begin()->c_str());
		//FIRSTRECHDATAHANDLER->setFirstRechActiviId(m_CurWindowActiviId);
	}
	Show(true);
}

void  VipGiftWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void  VipGiftWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_refreshTableView(m_pTable);
	NFC_showCommunicationWating(false);
}

/*
	返回VIP礼包事件处理
*/
void  VipGiftWindow::OnBackQAWindowEventHandler(std::list<std::string>& paramList)
{
	VIPGIFTACTIVITYHANDLER->BuyGift(m_CurBuyVipLevel);
}

void VipGiftWindow::_setTableView()
{
	if (m_pTable)
		m_pTable->removeAllChildrenWithCleanup(true);

	m_pTable = (CCTableView*)m_pRootNode->getChildByTag(udTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

cocos2d::CCSize VipGiftWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCellGift;
}

cocos2d::extension::CCTableViewCell* VipGiftWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){

	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}

void VipGiftWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	if(m_pTable)
	{ 
		unsigned int  cellArraySize = numberOfCellsInTableView(NULL);
		cocos2d::extension::CCTableViewCell * pTableViewCell = m_pTable->cellAtIndex(0); 
		NFC_setNodeVisable(udARROWLEFTMOVE,m_pRootNode,pTableViewCell!=NULL? false:true); 
		pTableViewCell = m_pTable->cellAtIndex(cellArraySize-1); 
		NFC_setNodeVisable(udARROWRIGHTMOVE,m_pRootNode,pTableViewCell!=NULL? false:true); 
	}
}

void VipGiftWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kVIPGIFTCELL,cell);
}

void VipGiftWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	VipGiftItem *data = VIPGIFTACTIVITYHANDLER->m_ActiviVipShowList[idx];
	if (data == NULL)
		return;

	//设置名字
	std::string name = data->getVipName();
	NFC_setLabelString(CELL_NAMETTF,cell,name);
	//设置原价
	NFC_setLabelStringInt(CELL_COSTMONEY,cell,data->getOriginalPrice());
	//设置特价
	NFC_setLabelStringInt(CELL_OFFERMONEY,cell,data->getDiscountPrice());

	_mapCellItemBtn(idx,cell);
	//设置当前附件图标
	_setVipBox(data,cell);
}

void VipGiftWindow::_setVipBox(VipGiftItem *data,cocos2d::extension::CCTableViewCell* cell)
{
	std::string file=NFC_getFileFromResourceID(data->getIconId());
	assert(file.length()>0);
	NFC_setPicForCCSprite(CELL_GIFTBOXICON,cell,file.c_str());
}

unsigned int VipGiftWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return VIPGIFTACTIVITYHANDLER->m_ActiviVipShowList.size();
}

void VipGiftWindow::On_CheckItem_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;	
	int index = cc->getIDX();
	VipGiftItem* data = VIPGIFTACTIVITYHANDLER->m_ActiviVipShowList[index];
	if (data == NULL)
		return;
	//点击预览礼包
	VIPGIFTACTIVITYHANDLER->PreviewGift(data->getPreviewId());
}

void VipGiftWindow::On_Click_Buy_Enevnt(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;	
	int index = cc->getIDX();
	VipGiftItem* data = VIPGIFTACTIVITYHANDLER->m_ActiviVipShowList[index];
	if (data == NULL)
		return;
	m_CurBuyVipLevel = data->getVipLevel();
	//点击预览礼包
	if (ROLEINFODATAHANDLER->m_pRIData->vipLevel_ < data->getVipLevel())
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6077));
		return;
	}
	if (ROLEINFODATAHANDLER->m_pRIData->jewels_ < data->getDiscountPrice())
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6078));
		return;
	}
	char buff[1024] = {0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6080).c_str(),data->getDiscountPrice());
	NFC_showMessageBox(kMISSION_VIPGIFTBOX,buff);
}