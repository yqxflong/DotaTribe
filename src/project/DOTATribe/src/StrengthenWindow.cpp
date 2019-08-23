//Name : StrengthenWindow
//Function : װ����һϵ��ǿ��
//Author : ��ǿ

#include "../include/StrengthenWindow.h"
#include "../include/WindowManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/EquipLvUpView.h"
#include "../include/EquipTrainView.h"
#include "../include/EquipPromoteView.h"
#include "../include/EquipsRecastSubView.h"
#include "../include/CPublicVarReader.h"
//�ĸ������������
#include "../include/GuideSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/EquipStrengthenDataHandler.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/DTEquipBoard.h"
#include "../include/RoleEquipDataHandler.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

//���ܵȼ�δ������ʾ
#define  _LEVEL_LESS_TIPS_  7000
#define  _ESEQUIPLVUP_TEXT_ 4017
#define  _ESEQUIPMAKEPROGRESS_TEXT_ 4018
#define  _ESEQUIPTRAIN_TEXT_ 4019
#define  _ESEQUIPBEAKDOMN_TEXT 7038
#define  _EMPTYWIDTH 250
StrengthenWindow::StrengthenWindow()
:m_nSVZorder(10)
,m_pSubView(NULL)
,m_bScrollBegin(false)
,m_bScrollEnd(false)
,m_HeroIndex(0)
{
	m_offSetPoint = cocos2d::CCPointZero;
	m_nLastSelectEquipId4 = -1;
	m_nLastCellIDX_tab4 = -1;
	m_WindowType   = _TYPED_WINDOW_STRENGTHEN_;
	_resetWindowParams();
}

bool StrengthenWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_STRENTHENWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_STRENTHENWINDOW_GUIDE_,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH,true);
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH,true);


	//begin:װ������
	RegisterEvent(_TEPED_EVENT_EQUIPLVUP_GET_COSTMONEY_, true);
	RegisterEvent(_TEPED_EVENT_EQUIPLVUP_GET_LVUPRESULT_, true);
	RegisterEvent(_TEPED_EVENT_EQUIPLVUP_AFTER_CHOOSECOST_,true);	//���ѡ���زĿ�
	RegisterEvent(_TYPED_EVENT_CONFIRMUSE_CONTAINPURPLECARD_, true);//ѡ��ɫ������ʾ����
	//end
	//begim:װ������
	RegisterEvent(_TEPED_EVENT_UPDATRA_EQUIPPROMOTE_, true);
	RegisterEvent(_TYPED_EVENT_EQUIPPROMOTE_RESULT_, true);
	//end
	//begin:װ��ϴ��
	RegisterEvent(_TYPED_EVENT_LOCK_ATTRIBUTE_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_UNLOCK_ATTRIBUTE_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_EQUIPTRAIN_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_EQUIPTRAIN_GETLOCKSTATUS_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_CONFIRM_EQUIP_USEONEKEYTRAIN_, true);
	RegisterEvent(_TYPED_EVENT_UNLOCK_EQUIPATTRIBUTELOCK_, true);
	//end

	//װ�� ����
	RegisterEvent(_TYPED_EVENT_EQUIPRECAST_UPDATE_, true);
	RegisterEvent(_TYPED_EVENT_EQUPERECAST_REFRESH_LIST_, true);
	 
	//end
	return IWindow::Init();
}

bool StrengthenWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();
		_initEmptyLabel();
		_mapBtn();
		_mapTable();
		_mapMoneyAndDiamond();
		return true;
	} 
	while (false);

	return false;
}

void StrengthenWindow::Tick()
{
	IWindow::Tick();
	if(m_pSubView)
		m_pSubView->onTick();
}

void StrengthenWindow::Destroy()
{
	//1.�ɵ�����effect
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);
	if(m_pSubView){
		m_pSubView->onDestroy();
		m_pSubView=NULL;
	}
	m_offSetPoint = cocos2d::CCPointZero;
	m_nLastCellIDX_tab4 = -1;
	m_nLastSelectEquipId4 = -1;
	m_bScrollBegin = false;
	m_bScrollEnd = false;
	m_bShowIsEnd = false;
	m_HeroIndex = 0;
	IWindow::Destroy();
}

void StrengthenWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_STRENTHENWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_STRENTHENWINDOW_)
	{
		Destroy();
	}else if(iEventType==_TYPED_EVENT_HIDE_STRENTHENWINDOW_GUIDE_){
		_resetWindowParams();
		Destroy();
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_){
		_mapMoneyAndDiamond();
	}else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH){
		_reloadEquipListByTab();

	}else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH){
		_reloadEquipListByTab();
	}else if(iEventType==_TEPED_EVENT_EQUIPLVUP_AFTER_CHOOSECOST_){
		_reloadEquipListByTab();
	}else if(iEventType==_TYPED_EVENT_EQUPERECAST_REFRESH_LIST_){
		_reloadEquipListByTab();
	}

	if(m_pSubView)
		m_pSubView->EventWindowCallBack(iEventType, paramList);

}

//����tabNum����Ϊ��windowTab��ö��
void StrengthenWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	string tmp;
	if (paramList.size()>0){
		tmp=*it++;
		int ntabNum=atoi(tmp.c_str());
		//�ڲ���Ӧת��
		if (ntabNum==ESTREN_TAB1){
			ntabNum=kTAB_1;
		}else if(ntabNum==ESTREN_TAB2){
			ntabNum=kTAB_2;
		}else if(ntabNum==ESTREN_TAB3){
			ntabNum=kTAB_3;
		}else{
			ntabNum=kTAB_1;
		}
		_selectTabItem(ntabNum);
		if (paramList.size()>1){
			tmp=*it++;
			m_nBackWindow=atoi(tmp.c_str());
		}
		if (paramList.size()>2){
			m_strParam1=*it++;
		}
		//�˲���ΪĬ��ѡ�е�װ��(����װ������)
		if (paramList.size()>3){
			tmp=*it++;
			if (tmp.length()>0)
			{
				m_nLastSelectEquipId1=atoi(tmp.c_str());
				_refreshEquipListAndCheckEquipSelected_setOffSet();
			}
		}
	}else{
		_selectTabItem(kTAB_1);
	}
	m_bShowIsEnd = true;
}

void StrengthenWindow::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSTRENGTHENWINDOW,m_pRootNode);
}
void StrengthenWindow::_initEmptyLabel(){
	CCLabelTTF* pEmptyLabel = (CCLabelTTF*)m_pRootNode->getChildByTag(kEMPTY_LABEL);
	pEmptyLabel->setDimensions(ccp(_EMPTYWIDTH,0));
	pEmptyLabel->setVisible(false);
}
void StrengthenWindow::_mapBtn(){
	CMenuItemSprite* cc=NULL;
	//close
	cc=(CMenuItemSprite*)NFC_getMenuItem(kCLOSE,m_pRootNode);
	cc->setIDX(kCLOSE);
	cc->setTarget(this,menu_selector(StrengthenWindow::On_Click_Event));
	//help
	cc=(CMenuItemSprite*)NFC_getMenuItem(kHELP,m_pRootNode);
	cc->setIDX(kHELP);
	cc->setTarget(this,menu_selector(StrengthenWindow::On_Click_Event));
	//tab1-3
	for (int i=kTAB_1;i<=kTAB_4;i+=2)
	{
		cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(StrengthenWindow::On_Tab_Selected));
	}
	//toggle
	cc=(CMenuItemSprite*)NFC_getMenuItem(kTOGGLE,m_pRootNode);
	cc->setIDX(kTOGGLE);
	cc->setTarget(this,menu_selector(StrengthenWindow::On_Click_Event));
}

void StrengthenWindow::_mapTable(){
	//׼��cell��С
	CCNode* node=m_pRootNode->getChildByTag(kCELLNODE);
	m_szCell=node->getContentSize();
	//����table
	m_pTable=(CCTableView*)m_pRootNode->getChildByTag(kTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	//Ĭ�ϼ���װ��������װ���б�
	_reloadEquipList_lvup();
	//Ĭ��ѡ�н���ʾװ��
	_toggleSeleted(m_bIsOnlyShowEquiped);
}

/*
	ȡ������ҳǩѡ��
*/
void StrengthenWindow::_resetAllHighlight(){
	for (int i=kTAB_1;i<=kTAB_4;i+=2)
	{
		CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->unselected();
	}
}

//����ҳǩ
void StrengthenWindow::_highlightTabItem(unsigned int idx){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(idx,m_pRootNode);
	cc->selected(true);
}


void StrengthenWindow::_loadSubView(unsigned int idx){

	if(idx==kTAB_1){
		LOGGERSYSTEM->LogInfo("EQUIP_LVUP==begin");
 		if(m_pSubView)
 		{
 			if(typeid(*m_pSubView) == typeid(EquipLvUpView))
 				return;
 			else
 				m_pSubView->onDestroy();
 		}
 		m_pSubView=new EquipLvUpView();
 		m_pSubView->onLoad();
 		m_pRootNode->addChild(m_pSubView,m_nSVZorder);
		m_bIsForceNotifySubView=true;
		m_nCurTab=idx;
		_reloadEquipList_lvup();
		_notifySubViewDefault();
		LOGGERSYSTEM->LogInfo("EQUIP_LVUP==End");
	}else if(idx==kTAB_2){//װ������
		if(ClientConstDataManager::get_instance2()->getValueByKey(EQUIP_PROMOTE_LEVEL)>RoleInfoDataHandler::get_instance2()->m_pRIData->level_) 
		{  
			char commonStr[128]={0}; 
			std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_LEVEL_LESS_TIPS_);
			sprintf(commonStr,advanceTips.c_str(),ClientConstDataManager::get_instance2()->getValueByKey(EQUIP_PROMOTE_LEVEL));
			NFC_showMessageBoxSingle(kDEFAULT,commonStr); 
			return ; 
		}
		else
		{
			LOGGERSYSTEM->LogInfo("EQUIP_Progress==begin");
			if (m_pSubView){
				if(typeid(*m_pSubView)==typeid(EquipPromoteView))
					return;
				else
					m_pSubView->onDestroy();
			}
			m_pSubView=new EquipPromoteView();
			m_pRootNode->addChild(m_pSubView,m_nSVZorder);
			m_pSubView->onLoad();
			m_bIsForceNotifySubView=true;
			m_nCurTab=idx;
			_reloadEquipList_progress();
			_notifySubViewDefault();
			LOGGERSYSTEM->LogInfo("EQUIP_Progress==end");
		} 

	}else if(idx==kTAB_3){//װ��ϴ��
		if(ClientConstDataManager::get_instance2()->getValueByKey(EQUIP_TRAIN_LEVEL)>RoleInfoDataHandler::get_instance2()->m_pRIData->level_) 
		{  
			char commonStr[128]={0}; 
			std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_LEVEL_LESS_TIPS_);
			sprintf(commonStr,advanceTips.c_str(),ClientConstDataManager::get_instance2()->getValueByKey(EQUIP_TRAIN_LEVEL));
			NFC_showMessageBoxSingle(kDEFAULT,commonStr); 
			return ; 
		}
		else
		{
			LOGGERSYSTEM->LogInfo("EQUIP_Train==begin");
			if (m_pSubView){
				if(typeid(*m_pSubView)==typeid(EquipTrainView))
					return;
				else
					m_pSubView->onDestroy();
			}
			m_pSubView=new EquipTrainView();
			m_pRootNode->addChild(m_pSubView,m_nSVZorder);
			m_pSubView->onLoad();
			m_bIsForceNotifySubView=true;
			m_nCurTab=idx;
			_reloadEquipList_train();
			_notifySubViewDefault();
			LOGGERSYSTEM->LogInfo("EQUIP_Train==end");
		}
	}
	else if(idx==kTAB_4){ //װ���ֽ�
		if(ClientConstDataManager::get_instance2()->getValueByKey(EQUIPS_BEACKDOMN_LEVEL_LIMIT)>RoleInfoDataHandler::get_instance2()->m_pRIData->level_) 
		{  
			char commonStr[128]={0}; 
			std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_LEVEL_LESS_TIPS_);
			sprintf(commonStr,advanceTips.c_str(),ClientConstDataManager::get_instance2()->getValueByKey(EQUIPS_BEACKDOMN_LEVEL_LIMIT));
			NFC_showMessageBoxSingle(kDEFAULT,commonStr); 
			return ; 
		}
		else
		{ 
			LOGGERSYSTEM->LogInfo("EQUIP_RECAST==begin");
			if (m_pSubView){
				if(typeid(*m_pSubView)==typeid(EquipsRecastSubView))
					return;
				else
					m_pSubView->onDestroy();
			} 
			m_offSetPoint = cocos2d::CCPointZero;
			m_pSubView=new EquipsRecastSubView();
			m_pRootNode->addChild(m_pSubView,m_nSVZorder);
			m_pSubView->onLoad();
			m_bIsForceNotifySubView=true; 
			m_nCurTab=idx;
			_forceChancelEquipState();
			_reloadEquipList_Recast();
			_notifySubViewDefault();
			LOGGERSYSTEM->LogInfo("EQUIP_RECAST==end");  
		} 
	}
	_resetAllHighlight();
	_highlightTabItem(idx);
}

//ѡ��ĳ����ǩ
void StrengthenWindow::_selectTabItem(unsigned int idx){

	_loadSubView(idx);

}

	/*
		��ť�¼�
	*/
void StrengthenWindow::On_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (cc->getIDX()==kCLOSE)
	{
		LOGGERSYSTEM->LogInfo("On_Close_Window");
		if (m_nBackWindow>=0)
		{
			if (m_strParam1.length()>0)
			{
				EVENTSYSTEM->PushEvent(m_nBackWindow,m_strParam1);
			}else
				EVENTSYSTEM->PushEvent(m_nBackWindow);
			m_nBackWindow = -1;
		}else{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		}
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_STRENTHENWINDOW_);
		_resetWindowParams();

		//��������
		GUIDESYSTEM->Next();
	}else if(cc->getIDX()==kHELP){
		char type[128] = "";
		sprintf(type,"%d",UIViewDataManager::kSTRENGTHEN_HELP_);
		PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,type);
		LOGGERSYSTEM->LogInfo("On_Help");
	}else if(cc->getIDX()==kTOGGLE){
		if(m_nCurTab==kTAB_4){
			_forceChancelEquipState();
		}
		else
		{ 
			if (cc->getIsSeleted()){
				_toggleSeleted(false);
			}else{
				_toggleSeleted(true);
			}
		}
	}
}

void StrengthenWindow::On_Tab_Selected(cocos2d::CCObject* pSender){
	if(m_bShowIsEnd)
	{
		CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
		_selectTabItem(cc->getIDX());
	}
}

	/*
		Cell ѡ��ص��¼�
	*/
void StrengthenWindow::On_Cell_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (m_nCurTab==kTAB_1)
	{
		_cellSelected_Tab1(cc);
	}else if(m_nCurTab==kTAB_2){
		_cellSelected_Tab2(cc);
	}else if(m_nCurTab==kTAB_3){
		_cellSelected_Tab3(cc);
	}else if(m_nCurTab==kTAB_4){
		_cellSelected_Tab4(cc,true); 
	}
}

unsigned int StrengthenWindow::numberOfCellsInTableView(CCTableView *table) {
	if (m_bIsOnlyShowEquiped)
	{
		int count=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size();
		return count;
	}else{
		int count=EquipStrengthenDataHandler::get_instance2()->EquipList_.size();
		return count;
	}
}

  /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
CCSize StrengthenWindow::tableCellSizeForIndex(CCTableView *table, unsigned int idx){
	return m_szCell;
}
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
CCTableViewCell* StrengthenWindow::tableCellAtIndex(CCTableView *table, unsigned int idx) {
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}

void StrengthenWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSTRENGTHENWINDOW_CELL,cell);
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
	cc->setTarget(this,menu_selector(StrengthenWindow::On_Cell_Click_Event));
}

void StrengthenWindow::_setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell){
	BagEquipData* bb=NULL;

	if(m_bIsOnlyShowEquiped)
	{
		bb=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_[idx];
	}
	else
	{
		bb=EquipStrengthenDataHandler::get_instance2()->EquipList_[idx];
	}
	int iconID = 0;
	if (bb->RoleHeroindexEquip_ == 0)
	{
		iconID = CLIENTCONSTDATAMANGER->getValueByKey(HERO_CORNER_MARK_INDEX1);
	}
	else if (bb->RoleHeroindexEquip_ == 1)
	{
		iconID = CLIENTCONSTDATAMANGER->getValueByKey(HERO_CORNER_MARK_INDEX2);
	}
	else if (bb->RoleHeroindexEquip_ == 2)
	{
		iconID = CLIENTCONSTDATAMANGER->getValueByKey(HERO_CORNER_MARK_INDEX3);
	}
	std::string stricon= ResourceIDDataManager::get_instance2()->getDataByID(iconID);
	if (stricon!="")
	{
		NFC_setPicForCCSprite(kCELL_EQUIPED, cell, stricon.c_str());
	}
	//������װ������
	NFC_showNode(kCELL_EQUIPED,cell,bb->isEquiped_);
	//����ͼ��
	DTEquipBoard* board=(DTEquipBoard*)NFC_getNode(kCELL_EBOARD,cell);
	board->SetEquip(kHETYPE_ELIST,bb,NULL);
	//����װ������+���׼���
	if(bb->advanceLevel_>0){
		char tmp[128]="";
		string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
		sprintf(tmp,sys.c_str(),bb->template_->name_.c_str(),bb->advanceLevel_);
		NFC_setLabelString(kCELL_ENAME,cell,tmp);
	}else{
		NFC_setLabelString(kCELL_ENAME,cell,bb->template_->name_);
	}
	//��������
	CCardsStarProgress* star=(CCardsStarProgress*)NFC_getNode(kCELL_STAR,cell);
	star->SetCurcount(bb->template_->quality_ + 1);
	//����cell Idx
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
	cc->setIDX(idx);	
	if (m_nCurTab==kTAB_1)
	{
		if(idx == 0 && m_nLastCellIDX_tab1 == -1)
		{
			if (m_nLastSelectEquipId1==-1)
			{
				m_nLastSelectEquipId1 = bb->id_;
			}
		}
		
		if(m_nLastSelectEquipId1 == bb->id_)
			_cellSelected_Tab1(cc);
		else
			cc->unselected();

	}else if(m_nCurTab==kTAB_2){
		if(idx == 0 && m_nLastCellIDX_tab2 == -1)
		{
			if (m_nLastSelectEquipId2==-1)
			{
				m_nLastSelectEquipId2 = bb->id_;
			}
		}

		if (m_nLastSelectEquipId2 == bb->id_)
			_cellSelected_Tab2(cc);
		else
			cc->unselected();
	}else if(m_nCurTab==kTAB_3){
		if(idx == 0 && m_nLastCellIDX_tab3 == -1)
		{
			if (m_nLastSelectEquipId3==-1)
			{
				m_nLastSelectEquipId3 = bb->id_;
			}
		}

		if (m_nLastSelectEquipId3 == bb->id_)
			_cellSelected_Tab3(cc);
		else
			cc->unselected();
	}
	else if(m_nCurTab == kTAB_4)
	{ 
		if(idx == m_nLastCellIDX_tab4)
		{
			_cellSelected_Tab4(cc);
		}
		else
		{
			cc->unselected();
		}
	}

}


void StrengthenWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	size_t count = 0;
	if (m_bIsOnlyShowEquiped)
		count=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size();
	else
		count=EquipStrengthenDataHandler::get_instance2()->EquipList_.size();
	if(m_pTable)
	{ 
		if(!m_pTable->cellAtIndex(0))
		{
			if(m_bScrollBegin)
			{
				m_bScrollBegin=false;
				NFC_setNodeVisable(kARROW_UPMOVE,m_pRootNode,true);
				NFC_setNodeVisable(kARROW_UP,m_pRootNode,false);		
			}
		}
		else
		{ 
			if(!m_bScrollBegin)
			{
				m_bScrollBegin=true;
				NFC_setNodeVisable(kARROW_UPMOVE,m_pRootNode,false);
				NFC_setNodeVisable(kARROW_UP,m_pRootNode,true);
			} 
		}
		if(!m_pTable->cellAtIndex(count-1))
		{
			if(m_bScrollEnd)
			{
				m_bScrollEnd=false;
				NFC_setNodeVisable(kARROW_DOWNMOVE,m_pRootNode,true);
				NFC_setNodeVisable(kARROW_DOWN,m_pRootNode,false);		
			}
		}
		else
		{ 
			if(!m_bScrollEnd)
			{
				m_bScrollEnd=true;
				NFC_setNodeVisable(kARROW_DOWNMOVE,m_pRootNode,false);
				NFC_setNodeVisable(kARROW_DOWN,m_pRootNode,true);
			} 
		}
	} 
}

void StrengthenWindow::_toggleSeleted(bool isselected){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kTOGGLE,m_pRootNode);
	if (isselected)
	{
		cc->selected(true);
		cc->setIsSelected(true);
		//����ʾ��װ��
		m_bIsOnlyShowEquiped=true;
	}else{
		cc->unselected();
		cc->setIsSelected(false);
		//��ʾ����װ��
		m_bIsOnlyShowEquiped=false;
	}
	_notifySubViewDefault();
	_refreshEquipListAndCheckEquipSelected();
}

void StrengthenWindow::_cellSelected_Tab1(CMenuItemSprite* cc){
	//status
	CCTableViewCell* cell=m_pTable->cellAtIndex(m_nLastCellIDX_tab1);
	if (cell)
	{
		CMenuItemSprite* lastBtn=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
		if (lastBtn==cc){
			cc->selected(true);
			return;
		}else
			lastBtn->unselected();
	}
	cc->selected(true);
	m_nLastCellIDX_tab1=cc->getIDX();
	//Logic
	int idx=cc->getIDX();
	int equipID=0;
	if (m_bIsOnlyShowEquiped)
	{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_[idx];
		equipID=bb->id_;
	}else{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->EquipList_[idx];
		equipID=bb->id_;
	}

	m_nLastSelectEquipId1 = equipID;
	_notifySubViewEquipID(equipID);
}

void StrengthenWindow::_cellSelected_Tab2(CMenuItemSprite* cc){
	//status
	CCTableViewCell* cell=m_pTable->cellAtIndex(m_nLastCellIDX_tab2);
	if (cell)
	{
		CMenuItemSprite* lastBtn=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
		if (lastBtn==cc){
			cc->selected(true);	
			return;
		}else
			lastBtn->unselected();
	}
	cc->selected(true);
	m_nLastCellIDX_tab2=cc->getIDX();
	//Logic
	int idx=cc->getIDX();
	int equipID=0;
	if (m_bIsOnlyShowEquiped)
	{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_[idx];
		equipID=bb->id_;
	}else{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->EquipList_[idx];
		equipID=bb->id_;
	}

	m_nLastSelectEquipId2 = equipID;
	_notifySubViewEquipID(equipID);
}
void StrengthenWindow::_cellSelected_Tab3(CMenuItemSprite* cc){
	//status
	CCTableViewCell* cell=m_pTable->cellAtIndex(m_nLastCellIDX_tab3);
	if (cell)
	{
		CMenuItemSprite* lastBtn=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
		if (lastBtn==cc){
			cc->selected(true);
			return;
		}else
			lastBtn->unselected();
	}
	cc->selected(true);
	m_nLastCellIDX_tab3=cc->getIDX();
	//Logic
	int idx=cc->getIDX();
	int equipID=0;
	if (m_bIsOnlyShowEquiped)
	{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->RoleEquipList_[idx];
		equipID=bb->id_;
	}else{
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->EquipList_[idx];
		equipID=bb->id_;
	}

	m_nLastSelectEquipId3 = equipID;
	_notifySubViewEquipID(equipID);
}

void StrengthenWindow::_cellSelected_Tab4(CMenuItemSprite* cc,bool bNofity)
{
	//status
	CCTableViewCell* cell=m_pTable->cellAtIndex(m_nLastCellIDX_tab4);
	if (cell)
	{
		CMenuItemSprite* lastBtn=(CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,cell);
		if (lastBtn==cc)
		cc->selected(true);
		else
		lastBtn->unselected();
	}
	cc->selected(true);
	m_nLastCellIDX_tab4=cc->getIDX();

	if(bNofity)
	{
		//Logic
		m_bIsForceNotifySubView = true;
		int equipID=0; 
		BagEquipData* bb=EquipStrengthenDataHandler::get_instance2()->EquipList_[m_nLastCellIDX_tab4];
		equipID=bb->id_; 
		m_nLastSelectEquipId4 = equipID;
		if(equipID > 0)
		m_offSetPoint = m_pTable->getContentOffset();
		_notifySubViewEquipID(equipID);
	}  
}


//begin:reload table
void StrengthenWindow::_reloadEquipListByTab(){
	if (m_nCurTab==kTAB_1)
	{
		_reloadEquipList_lvup_afterResult();
	}else if(m_nCurTab==kTAB_2)
	{
		_reloadEquipList_progress_afterResult();
	}else if(m_nCurTab==kTAB_3){ 
		//����Ҫˢ��
		//_reloadEquipList_train();
	}else if(m_nCurTab==kTAB_4){
		//to do 
		//ˢ��ҳ�治ѡ������һ��
		_reloadEquipList_Recast();
	}

}


//�������
void StrengthenWindow::_reloadEquipList_lvup_afterResult(){
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_EquipLvUp(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex);
	_refreshEquipListAndCheckEquipSelected_setOffSet();
}

void StrengthenWindow::_reloadEquipList_lvup(){
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_EquipLvUp(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex);
	m_nLastSelectEquipId1=-1;
	m_nLastCellIDX_tab1=-1;
	_refreshEquipListAndCheckEquipSelected();
}

void StrengthenWindow::_reloadEquipList_progress(){
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_Progress(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex);
	m_nLastSelectEquipId2=-1;
	m_nLastCellIDX_tab2=-1;
	_refreshEquipListAndCheckEquipSelected();
}

void StrengthenWindow::_reloadEquipList_progress_afterResult(){
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_Progress(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex);
	_refreshEquipListAndCheckEquipSelected_setOffSet();
}

void StrengthenWindow::_reloadEquipList_train(){
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_Train(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex);
	m_nLastSelectEquipId3=-1;
	m_nLastCellIDX_tab3=-1;
	_refreshEquipListAndCheckEquipSelected();
}


void StrengthenWindow::_reloadEquipList_Recast()
{
	EquipStrengthenDataHandler::get_instance2()->LoadEquipList_Recast();
	m_nLastCellIDX_tab4 = -1;
	m_nLastSelectEquipId4 = -1;
	NFC_refreshTableWithOffSet(m_pTable,m_offSetPoint);
	_notifySubViewWhenEmpty();
	//_refreshEquipListAndCheckEquipSelected();
}
void StrengthenWindow::_clearEquipList(){
	EquipStrengthenDataHandler::get_instance2()->ClearEquipList();
}
//end


/*
	ˢ�½�Ǯ����ʯ
*/
void StrengthenWindow::_mapMoneyAndDiamond(){
	NFC_setLabelStringInt(kGOLD_LABEL,m_pRootNode,ROLEINFODATAHANDLER->m_pRIData->money_);
	NFC_setLabelStringInt(kDIAMOND_LABEL,m_pRootNode,ROLEINFODATAHANDLER->m_pRIData->jewels_);
}


	/*
		�ָ����ڲ���
	*/
void StrengthenWindow::_resetWindowParams(){
	m_bIsOnlyShowEquiped=true;
	m_nLastCellIDX_tab1 = -1;
	m_nLastCellIDX_tab2 = -1;
	m_nLastCellIDX_tab3 = -1;
	m_nLastSelectEquipId1 = -1;
	m_nLastSelectEquipId2 = -1;
	m_nLastSelectEquipId3 = -1;
	m_pTable=NULL;
	m_nCurTab=kTAB_1;
	m_szCell=CCSize(0,0);
	m_nBackWindow=-1;
	m_nLastEquipID_ToSubView=0;
	m_bIsForceNotifySubView=false;
	_clearEquipList();
	EquipmentLvUpDataHandler::get_instance2()->ClearData();
	m_bShowIsEnd = false;
}

	/*
		���б�ʱ֪ͨ��ҳ��
	*/
void StrengthenWindow::_notifySubViewWhenEmpty(){
	if (m_bIsOnlyShowEquiped)
	{
		if (EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size()==0){
			_notifySubViewEquipID(-1);
		}
	}else{
		if (m_pSubView&&EquipStrengthenDataHandler::get_instance2()->EquipList_.size()==0){
			_notifySubViewEquipID(-1);
		}
	}
}

void StrengthenWindow::_notifySubViewDefault()
{
	//�ж��Ƿ񳬳�����ҳ�ķ�Χ�������������ô����Ĭ��ѡ�У����߲�ѡ��
	int size = 0;
	if (m_nCurTab == kTAB_1)
	{
		if(m_bIsOnlyShowEquiped)
			size = EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size();
		else 
			size = EquipStrengthenDataHandler::get_instance2()->EquipList_.size();

		if(m_nLastCellIDX_tab1 >= size)
			m_nLastCellIDX_tab1 = 0;
		if(size == 0)
			m_nLastCellIDX_tab1 = -1;
	}
	else if(m_nCurTab == kTAB_2)
	{
		if(m_bIsOnlyShowEquiped)
			size = EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size();
		else 
			size = EquipStrengthenDataHandler::get_instance2()->EquipList_.size();

		if(m_nLastCellIDX_tab2 >= size)
			m_nLastCellIDX_tab2 = 0;
		if(size == 0)
			m_nLastCellIDX_tab2 = -1;
	}
	else if(m_nCurTab == kTAB_3)
	{
		if(m_bIsOnlyShowEquiped)
			size = EquipStrengthenDataHandler::get_instance2()->RoleEquipList_.size();
		else 
			size = EquipStrengthenDataHandler::get_instance2()->EquipList_.size();

		if(m_nLastCellIDX_tab3 >= size)
			m_nLastCellIDX_tab3 = 0;
		if(size == 0)
			m_nLastCellIDX_tab3 = -1;
	}
	else if(m_nCurTab == kTAB_4)
	{
		size = EquipStrengthenDataHandler::get_instance2()->EquipList_.size();
	}


	if(size == 0)
	{
		_notifySubViewEquipID(-1);
		NFC_setNodeVisable(kARROW_UPMOVE,m_pRootNode,false);
		NFC_setNodeVisable(kARROW_UP,m_pRootNode,true);	
		NFC_setNodeVisable(kARROW_DOWNMOVE,m_pRootNode,false);
		NFC_setNodeVisable(kARROW_DOWN,m_pRootNode,true);	
	}
	else
	{ 
		NFC_setNodeVisable(kEMPTY_LABEL,m_pRootNode,false);
		NFC_setNodeVisable(kARROW_UPMOVE,m_pRootNode,true);
		NFC_setNodeVisable(kARROW_UP,m_pRootNode,false);	
		NFC_setNodeVisable(kARROW_DOWNMOVE,m_pRootNode,true);
		NFC_setNodeVisable(kARROW_DOWN,m_pRootNode,false);	
	}
		
}

void StrengthenWindow::_notifySubViewEquipID(int equipID){
	if (m_pSubView&&(m_nLastEquipID_ToSubView!=equipID||m_bIsForceNotifySubView))
	{
		m_bIsForceNotifySubView=false;
		m_pSubView->EquipHasBeenSeleted(equipID);
		m_nLastEquipID_ToSubView=equipID;
	}
	_checkEquipListIsEmpty(equipID);
} 

	/*
		ˢ��װ���б��Ҿ���ûѡ��װ�������
		#�ָ�ƫ����
	*/
void StrengthenWindow::_refreshEquipListAndCheckEquipSelected_setOffSet(){
	//����Ƿ���װ����һ����ûѡ��
	_checkEquipSelected();
	//ˢ��װ���б�
	NFC_refreshTableViewAndSetOldOffset(m_pTable);
}

	/*
		ˢ��װ���б��Ҿ���ûѡ��װ�������
	*/
void StrengthenWindow::_refreshEquipListAndCheckEquipSelected(){
	//����Ƿ���װ����һ����ûѡ��
	_checkEquipSelected();
	//ˢ��װ���б�
	NFC_refreshTableView(m_pTable);
}

	/*
		����ûѡ��װ�������
	*/
void StrengthenWindow::_checkEquipSelected(){
	if (m_nCurTab==kTAB_1)
	{
		if (m_bIsOnlyShowEquiped)
		{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_RoleEquip(m_nLastSelectEquipId1))
			{
				m_nLastCellIDX_tab1=-1;
				m_nLastSelectEquipId1=-1;
			}
		}else{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_All(m_nLastSelectEquipId1))
			{
				m_nLastCellIDX_tab1=-1;
				m_nLastSelectEquipId1=-1;
			}
		}
	}else if(m_nCurTab==kTAB_2){
		if (m_bIsOnlyShowEquiped)
		{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_RoleEquip(m_nLastSelectEquipId2))
			{
				m_nLastCellIDX_tab2=-1;
				m_nLastSelectEquipId2=-1;
			}
		}else{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_All(m_nLastSelectEquipId2))
			{
				m_nLastCellIDX_tab2=-1;
				m_nLastSelectEquipId2=-1;
			}
		}
	}else if(m_nCurTab==kTAB_3){
		if (m_bIsOnlyShowEquiped)
		{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_RoleEquip(m_nLastSelectEquipId3))
			{
				m_nLastCellIDX_tab3=-1;
				m_nLastSelectEquipId3=-1;
			}
		}else{
			if (!EquipStrengthenDataHandler::get_instance2()->CheckTheEquipExisted_All(m_nLastSelectEquipId3))
			{
				m_nLastCellIDX_tab3=-1;
				m_nLastSelectEquipId3=-1;
			}
		}
	}
}

	/*
		������װ���б��Ƿ�Ϊ��
	*/
void StrengthenWindow::_checkEquipListIsEmpty(int equipID)
{
	CCLabelTTF* pEmptyLabel = (CCLabelTTF*)m_pRootNode->getChildByTag(kEMPTY_LABEL);
	if (equipID == -1)
	{
		//װ���б���װ��ʱ��
		pEmptyLabel->setString(_getShowText(m_nCurTab).c_str());
		pEmptyLabel->setVisible(true);
	}
	else
	{
		pEmptyLabel->setVisible(false);
	}
}
	/*
		��ȡҪ��ʾ������
	*/
std::string StrengthenWindow::_getShowText(int index)
{
	if (index == kTAB_1)
		return SysLangDataManager::get_instance2()->GetSysLangById(_ESEQUIPLVUP_TEXT_);
	else if (index == kTAB_2)
		return SysLangDataManager::get_instance2()->GetSysLangById(_ESEQUIPMAKEPROGRESS_TEXT_);
	else if (index == kTAB_3)
		return SysLangDataManager::get_instance2()->GetSysLangById(_ESEQUIPTRAIN_TEXT_);
	else if (index == kTAB_4)
		return SysLangDataManager::get_instance2()->GetSysLangById(_ESEQUIPBEAKDOMN_TEXT);
	return "";
}


void  StrengthenWindow::_forceChancelEquipState()
{
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kTOGGLE,m_pRootNode); 
	cc->unselected();
	cc->setIsSelected(false);
	//����ʾδװ��
	m_bIsOnlyShowEquiped = false; 	
}


void  StrengthenWindow::_activeFirstCellForRecast()
{
	cocos2d::extension::CCTableViewCell * pCellItem = m_pTable->cellAtIndex(m_nLastSelectEquipId4);
	if(pCellItem)
	{
		CMenuItemSprite * pBtn = (CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,pCellItem);
		pBtn->unselected(); 
	}
	m_nLastCellIDX_tab4 = 0;
	pCellItem = m_pTable->cellAtIndex(0);
	if(pCellItem)
	{
		CMenuItemSprite * pBtn = (CMenuItemSprite*)NFC_getMenuItem(kCELL_BGBTN,pCellItem);
		pBtn->selected(true);
		_cellSelected_Tab4(pBtn,true);
	} 

}