//Name：SelectServerWindow
//Function：服务器选择界面
//Written By：吕云龙
//Edit:Johny
#include "../include/SelectServerWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/MessageBoxWindow.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/MaskNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

SelectServerWindow::SelectServerWindow()
:m_pRoot(0)
,m_pRoot_Server(0)
,m_pTable(0)
,m_curServerInfostate(0)
,m_SoonTitleIndex(-1)
,m_AllTitleIndex(-1)
{
	m_WindowType = _TYPED_WINDOW_SELECTSERVER_;
}

SelectServerWindow::~SelectServerWindow()
{

}

bool SelectServerWindow::Init()
{

	RegisterEvent(_TYPED_EVENT_SHOW_SELECTSERVERWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SELECTSERVERWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SELECTSERVERWINDOW_);

	return IWindow::Init();
}

bool SelectServerWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		//初始化界面
		_initLayout();
		//刷新服务器列表
		SERVERINFODATAINFO->QueryServerListData_selServerWindow();
		return true;
	} 
	while (false);

	return false;
}

void SelectServerWindow::Tick()
{
	IWindow::Tick();
}

void SelectServerWindow::Destroy()
{
	IWindow::Destroy();
}

void SelectServerWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_SELECTSERVERWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SELECTSERVERWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_SELECTSERVERWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void SelectServerWindow::OnShowWindowEventHandler(std::list<std::string>& paramList){
	Show(true);
}

void SelectServerWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList){
	
	m_SoonTitleIndex = SERVERINFODATAINFO->GetSoonServerIndex();
	m_AllTitleIndex = SERVERINFODATAINFO->GetAllServerIndex();
	NFC_refreshTableView(m_pTable);
}

void SelectServerWindow::_initLayout()
{
	m_pRoot_Server=m_pRootNode;
	//UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSELECTSERVERWINDOW,m_pRoot);
	//m_pRoot_Server =(CCNode*)m_pRoot->getChildByTag(pRoot);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSELECTSERVERWINDOW,m_pRoot_Server);
	_mapGrayLayer();
	_setTableView();
}	

void SelectServerWindow::_mapGrayLayer(){
	CPriorityLayerColor* color = (CPriorityLayerColor*)NFC_getNode(SERVERPRIORCOLOR,m_pRoot_Server);
	color->setDelegate(this);
	CTouchSprite* cc2=(CTouchSprite*)NFC_getNode(SERVERBG,m_pRoot_Server);
	cc2->setDelegate(this);
}

void SelectServerWindow::_setTableView(){
	CCNode* node=(CCNode*)m_pRoot_Server->getChildByTag(TABLEVIEWCELL);
	m_szCell = node->getContentSize();


	m_pTable = (CCTableView*)m_pRootNode->getChildByTag(TABLEVIEW);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

cocos2d::CCSize SelectServerWindow::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	int index = m_AllTitleIndex/2;
	if (m_SoonTitleIndex != -1 && m_SoonTitleIndex == idx)
	{
		return CCSizeMake(m_szCell.width,m_szCell.height+40.0f);
	}
	else if (m_AllTitleIndex != -1 && index == idx)
	{
		return CCSizeMake(m_szCell.width,m_szCell.height+40.0f);
	}
	return m_szCell;
}

CCTableViewCell* SelectServerWindow::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);	
	}
	_setTableCell(cell,idx);
	return cell;
};


unsigned int SelectServerWindow::numberOfCellsInTableView(CCTableView *table){
	unsigned short icount = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.size()/ 2;
	unsigned short rest = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.size() % 2;
	return icount + rest;
};


void SelectServerWindow::_createTableCell(cocos2d::extension::CCTableViewCell * cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVERROOTCELL,cell);
} 


void SelectServerWindow::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
{
	int index = m_AllTitleIndex/2;
	if (m_SoonTitleIndex == idx || index == idx)
	{
		std::string str = "";
		if (m_SoonTitleIndex == idx)
			str = SysLangDataManager::get_instance2()->GetSysLangById(6073);
		else
			str = SysLangDataManager::get_instance2()->GetSysLangById(6074);
		_showTitle(cell,true,str);
	}	
	else
	{
		_showTitle(cell,false);
	}
	idx*=2;
	_setCellBlockInfo(cell,idx);
	_mapCellBtn(cell,idx);
	idx++;
	if (idx==SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.size()){
		_showBlock2(cell,false);
		return;
	}else{
		const GameServerdata& data = SERVERINFODATAINFO->ByIndexServerInfo(idx);
		if (data.isshow_)
		{
			_showBlock2(cell,true);
			_setCellBlockInfo(cell,idx);
			_mapCellBtn(cell,idx);
		}
		else
		{
			_showBlock2(cell,false);
		}
	}
}

void SelectServerWindow::_setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	const GameServerdata& theServer = SERVERINFODATAINFO->ByIndexServerInfo(blockIdx);
	if (!theServer.isshow_)
		return;
	MaskNode* node = NULL;
	if (theServer.state_==0)//维护中
	{
		node=(MaskNode*)m_pRoot_Server->getChildByTag(PNODE1);
	}
	else
	{
		if (theServer.level_==0)
		{
			node=(MaskNode*)m_pRoot_Server->getChildByTag(PNODE2);
		}else{
			node=(MaskNode*)m_pRoot_Server->getChildByTag(PNODE3);
		}
	}
	NFC_setPicForCCSprite(CELL_NEWSER1+blockIdx%2,cell,node->GetViewData().filepath_);
	NFC_setLabelString(CELL_SERVERNAME1+blockIdx%2,cell,theServer.name_);
}

void SelectServerWindow::_mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	NFC_bindSelectotForCellBtn(CELL_SERVERBTN1+blockIdx%2,blockIdx,cell,this,menu_selector(SelectServerWindow::On_Click_Table_Block));
}

void SelectServerWindow::_showBlock2(cocos2d::CCNode* cell,bool isShow)
{
	NFC_setNodeVisable(CELL_SERVERBTN2,cell,isShow);
	NFC_setNodeVisable(CELL_NEWSER2,cell,isShow);
	NFC_setNodeVisable(CELL_SERVERNAME2,cell,isShow);
	NFC_setNodeVisable(CELL_SERVERBG2,cell,isShow);
}

void SelectServerWindow::_showTitle(cocos2d::CCNode* cell,bool isShow,std::string str)
{
	if (isShow)
	{
		NFC_setNodeVisable(CELL_TITLEBG,cell,isShow);
		NFC_setLabelString(CELL_TILENAME,cell,str,isShow);
	}
	else
	{
		NFC_setNodeVisable(CELL_TILENAME,cell,isShow);
		NFC_setNodeVisable(CELL_TITLEBG,cell,isShow);
	}
}

void SelectServerWindow::On_Click_Table_Block(cocos2d::CCObject * pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	std::list<GameServerdata>::iterator it=SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
	for (int i=0;i<idx;i++)
		it++;
	GameServerdata& theServer=*it;
	SERVERINFODATAINFO->RecordTheGameServerInfo(theServer);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSERVERWINDOW_);
}

	/*
		CPriorityLayerColor CallBack
	*/
void SelectServerWindow::touchEvent(CPriorityLayerColor* pLayerColor){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSERVERWINDOW_);
}

/*
	CTouchSprite CallBack
*/
void SelectServerWindow::rangeTouched(cocos2d::CCObject* pSender){
	;
}