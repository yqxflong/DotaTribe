//Name：EmailWindow
//Function：　邮箱界面
//Written By：尹强
//Edit by: LvYunlong

#include "../include/EmailWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/ClientConstDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/FriendCheckPlayerInfoPacket.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/EffectDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/FriendDataHandler.h"
#include "../include/TimeSystem.h"
using namespace std;

#define GETALLATT_TIMEOUT 5
USING_NS_CC;
USING_NS_CC_EXT;

EmailWindow::EmailWindow()
:m_nCurIndex_system(0)
,m_nCurIndex_personal(0)
,m_pTable(NULL)
,m_pTableAttachment(NULL)
,m_pCurItem(0)
,m_CurrSubTabIndex(0)
,m_CurrEmailMenuIndex(-1)
{
	m_WindowType   = _TYPED_WINDOW_EMAIL_WINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

EmailWindow::~EmailWindow(){

}

bool  EmailWindow::Init(){
	RegisterEvent(_TYPEF_EVENT_SHOW_EMAILWINDOW_);
	RegisterEvent(_TYPEF_EVENT_HIDE_EMAILWINDOW_, true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY, true);
	return IWindow::Init();
}
	/*
		加载处理
	*/
bool  EmailWindow::Load(){
	do 
	{
		if (!IWindow::Load())
			break;
		//_initData();
		_initLayout();
		_initCell();
		_initCornerNumIcon();
		_mapBtn();
		refreshUIData();
		_setTableView(); //设置TableView
		
		return true;
	} 
	while (false);

	return false;
}
	/*
		桢更新处理
	*/
void    EmailWindow::Tick(){
	//注意 断线的时候 EMAILDATAHANDLER->m_isGettingAtt 是true
	if (EMAILDATAHANDLER->m_isGettingAtt){
		do
		{
			EMAILDATAHANDLER->GetAllATTStep();
		}while(0);
	}

	IWindow::Tick();
}
	/*
		销毁处理
	*/ 
void   EmailWindow::Destroy(){
	m_pTable = NULL;
	m_pTableAttachment = NULL;
	m_pCurItem = NULL;
	m_CurrEmailMenuIndex = -1;
	m_pRoot->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

	/*
		消息事件响应处理
	*/
void   EmailWindow:: OnEventHandler(int iEventType, std::list<std::string>& paramList){
	if (iEventType == _TYPEF_EVENT_SHOW_EMAILWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if (iEventType == _TYPEF_EVENT_HIDE_EMAILWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPEF_EVENT_UPDATE_EMAILWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		refreshUIData();
	}
	else if (iEventType == _TYPED_EVENT_RECONNECT_INGAME_NOTIFY)
	{
		EMAILDATAHANDLER->QueryEmail();
	}
}

void   EmailWindow::OnShowWindowEventHandler(std::list<std::string>& paramList){
	Show(true);
}

void  EmailWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	Destroy();
	//Fadeout(IWINDOW_FADEOUT_DURING);
}

void  EmailWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList){

	
	list<string>::iterator it=paramList.begin();
	std::string tmp = *it;
	int type = atoi(tmp.c_str());
	
	if (_ENUM_UPDATE_EMAILREMOVE_TYPE_ == type)
	{
		int emailsize = 0;
		if (getCurrentSubTabIndex()==kSYSTEM)
			emailsize = EMAILDATAHANDLER->m_vecSystemEmail.size();
		else if(getCurrentSubTabIndex()==kPERSONAL)
			emailsize = EMAILDATAHANDLER->m_vecPersonalEmail.size();

		int flag = -1;
		int willShowindex = -1;
		if (emailsize == 0)
		{
			m_CurrEmailMenuIndex = -1;
			HideSystemProtocol();
			HidePersonalProtocol();
			NFC_refreshTableView(m_pTable);
			return;
		}
		else if (emailsize == m_CurrEmailMenuIndex)
		{
			//删除最后一信件
			willShowindex = m_CurrEmailMenuIndex - 1;
			m_CurrEmailMenuIndex = -1;

			_showMailDetail(willShowindex);
		}
		else if (emailsize > m_CurrEmailMenuIndex)
		{
			willShowindex = m_CurrEmailMenuIndex;
			m_CurrEmailMenuIndex = -1;
			_showMailDetail(willShowindex);
		}
		
		if (willShowindex <= 4)
		{
			NFC_refreshTableView(m_pTable);
			tableCellAtIndex(m_pTable,willShowindex);
			return;
		}
		int pos = 0;
		if (willShowindex+3 == emailsize)
		{
			pos = 270;
		}
		else if (willShowindex+2 == emailsize)
		{
			pos = 180;
		}
		else if (willShowindex+1 == emailsize)
		{
			pos = 90;
		}
		else 
		{
			pos = 360;
		}

		NFC_refreshTableView(m_pTable);
		//
		tableCellAtIndex(m_pTable,willShowindex);
		cocos2d::CCPoint cpTableCurOffset(CCPointZero);
		cpTableCurOffset.y = -90*(emailsize-willShowindex)+pos;
		NFC_setOffsetForTableView(m_pTable,cpTableCurOffset);
	}
	else if (_ENUM_UPDATE_EMAILINFO_TYPE_ == type)
	{
		if (getCurrentSubTabIndex() == kSYSTEM)
		{
			ShowSystemProtocol(EMAILDATAHANDLER->m_pEmailInfo);
		}
		else if (getCurrentSubTabIndex() == kPERSONAL)
		{
			ShowPersonalProtocol();
		}
		NFC_setLabelString(udSENDER,m_pRoot,EMAILDATAHANDLER->m_pEmailInfo->sourceName.c_str());
		NFC_setLabelString(udDATE,m_pRoot,EMAILDATAHANDLER->m_pEmailInfo->time.c_str());
		NFC_setLabelString(udCONTENT,m_pRoot,EMAILDATAHANDLER->m_pEmailInfo->content.c_str());

		NFC_setCornerNum(udNOREADSYSEMAIL,m_pRoot,EMAILDATAHANDLER->GetSystemEmailUnreadNum());
		NFC_setCornerNum(udNOREADPERSONEMAIL,m_pRoot,EMAILDATAHANDLER->GetProsonEmailUnreadNum());
		
	}
	else if (_ENUM_UPDATE_GETATTACHMENTINFO_TYPE_ == type)
	{
		EMAILDATAHANDLER->m_pEmailInfo->ClearAttachmentList();
		NFC_showNode(udLETTERLINE,m_pRoot,false);
		NFC_showNode(udGETBTN,m_pRoot,false);
		NFC_showNode(udGETBTNTITLE,m_pRoot,false);
		NFC_refreshTableView(m_pTableAttachment);
	}
	else if (_ENUM_UPDATE_SENDEMAIL_TYPE_ == type)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_WRITEEMAILWINDOW_);
	}
	else if (_ENUM_UPDATE_EMAILLIST_TYPE_ == type){
		_initCornerNumIcon();
		selectSubTabItem(kSYSTEM);
	}
}

/*
	TableView Datasource
*/
cocos2d::CCSize EmailWindow::cellSizeForTable(cocos2d::extension::CCTableView *table){
	if (table == m_pTable)
	{
		return m_szCell;
	}
	else if (table == m_pTableAttachment)
	{
		return m_szCellAttachment;
	}
	
	return CCPointZero;
}
cocos2d::extension::CCTableViewCell* EmailWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx){
	int type = -1;
	if(table == m_pTable)
	{
		type = _TABLE_TYPE_QUERY_;
	}
	else if(table == m_pTableAttachment)
	{
		type = _TABLE_TYPE_ATTACHMENT_;
	}
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell,type);
	}
	_setTableCell(idx,cell,type);

	return cell;
}
unsigned int EmailWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
	if (table == m_pTable)
	{
		if (getCurrentSubTabIndex()==kSYSTEM)
			return EMAILDATAHANDLER->m_vecSystemEmail.size();
		else if(getCurrentSubTabIndex()==kPERSONAL)
			return EMAILDATAHANDLER->m_vecPersonalEmail.size();
	}
	else if (table == m_pTableAttachment)
	{
		return EMAILDATAHANDLER->m_pEmailInfo->attachmentlist.size();
	}
	return 0;
}

void EmailWindow::_initLayout(){
	CCNode* node =m_pRootNode;
	m_pRoot = CCNode::create();
	node->addChild(m_pRoot,10);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEMAILWINDOW,m_pRoot);
}

void EmailWindow::_initCell()
{
	CCNode* cell = NFC_getNode(udLEFTTABLECELL,m_pRoot);
	m_szCell = cell->getContentSize();

	cell = NFC_getNode(udLEFTTABLECELL1,m_pRoot);
	m_szCellAttachment = cell->getContentSize();
}

void EmailWindow::_initCornerNumIcon()
{
	int num = EMAILDATAHANDLER->GetSystemEmailUnreadNum();
	NFC_setCornerNum(udNOREADSYSEMAIL,m_pRoot,num);
	num = EMAILDATAHANDLER->GetProsonEmailUnreadNum();
	NFC_setCornerNum(udNOREADPERSONEMAIL,m_pRoot,num);
}

void EmailWindow::_setTableView()
{
	if (m_pTable)
		m_pTable->removeAllChildrenWithCleanup(true);
	if (m_pTableAttachment)
		m_pTableAttachment->removeAllChildrenWithCleanup(true);
	
	m_pTable = (CCTableView*)m_pRoot->getChildByTag(udLEFTTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);

	m_pTableAttachment = (CCTableView*)m_pRoot->getChildByTag(udLEFTTABLE1);
	m_pTableAttachment->setDataSource(this);
	m_pTableAttachment->setDelegate(this);
	m_pTableAttachment->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	m_pTableAttachment->setTouchEnabled(true);
	m_pTableAttachment->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);

}


void EmailWindow::_layoutForSystem(){
	NFC_refreshTableView(m_pTable);	
	m_CurrEmailMenuIndex = -1;
}
void EmailWindow::_layoutForPersonal(){
	NFC_refreshTableView(m_pTable);	
	m_CurrEmailMenuIndex = -1;
}

void EmailWindow::_showMailDetail(int index){

	EmailListData* data = NULL;

	if (getCurrentSubTabIndex() == kSYSTEM)
	{
		data = EMAILDATAHANDLER->m_vecSystemEmail[index];
		if (data==NULL)
			return;
	}
	else if (getCurrentSubTabIndex() == kPERSONAL)
	{
		data = EMAILDATAHANDLER->m_vecPersonalEmail[index];
		if (data==NULL)
			return;
	}
	data->hasread = _TYPE_ALREADY_READ_;
	if (m_CurrEmailMenuIndex == index)
		return;
	//获得索引之后做处理
	if (m_CurrEmailMenuIndex == -1)
	{
		m_CurrEmailMenuIndex = index;
	}
	CCNode* node = m_pTable->cellAtIndex(m_CurrEmailMenuIndex);
	if(node != NULL)
	{
		NFC_showNode(udCELLSELECTICON,node,false);
	}
	m_CurrEmailMenuIndex = index;
	node = m_pTable->cellAtIndex(m_CurrEmailMenuIndex);
	if (node != NULL)
	{
		NFC_showNode(udCELLSELECTICON,node,true);
		NFC_setPicForCCSprite(udCELLMAILICON,node,EMAIL_POENED_ICON);	
	}
	//显示系统信息控件
	EMAILDATAHANDLER->CheckEmailToServer(data->mailID_);

}


void EmailWindow::_mapBtn(){
//~Tab
	CCMenu* tabmenu=(CCMenu*)NFC_getNode(udTAB1,m_pRoot);
	CMenuItemSprite *item = (CMenuItemSprite *)tabmenu->getChildByTag(0);
	item->setTag(udTAB1);
	item->setTarget(this, menu_selector(EmailWindow::On_TabIndex_Click));


	tabmenu=(CCMenu*)NFC_getNode(udTAB2,m_pRoot);
	item = (CMenuItemSprite *)tabmenu->getChildByTag(0);
	item->setTag(udTAB2);
	item->setTarget(this, menu_selector(EmailWindow::On_TabIndex_Click));

//~closeBtn

	CCMenu* menuClose = (CCMenu*)NFC_getNode(udCLOSEBTN,m_pRoot);
	CMenuItemSprite *itemClose = (CMenuItemSprite *)menuClose->getChildByTag(0);
	itemClose->setIDX(udCLOSEBTN);
	itemClose->setTarget(this, menu_selector(EmailWindow::On_Event_Click));
//~
	CCMenu* menu=(CCMenu*)NFC_getNode(udWRITEBTN,m_pRoot);
	CCMenuItem* cc=(CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_WriteBtn_Click));
//~
	menu=(CCMenu*)NFC_getNode(udCHECKINFOBTN,m_pRoot);
	cc=(CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_CheckInfoBtn_Click));
//~
	menu=(CCMenu*)NFC_getNode(udREMOVEBTN,m_pRoot);
	cc=(CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_RemoveBtn_Click));
//~
	menu=(CCMenu*)NFC_getNode(udGETBTN,m_pRoot);
	cc=(CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_GetBtn_Click));
//~
	menu=(CCMenu*)NFC_getNode(udREPLYBTN,m_pRoot);
	cc=(CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_ReplyBtn_Click));

	menu = (CCMenu*)NFC_getNode(udGETALLBTN, m_pRoot);
	cc = (CCMenuItem*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EmailWindow::On_GetAllBtn_Click));
}

//Tableview
void EmailWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell,int tabletype){
	if (tabletype == _TABLE_TYPE_QUERY_)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEMAILWINDOWCELL,cell);
	}
	else if (tabletype == _TABLE_TYPE_ATTACHMENT_)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEMAILWINDOWATTACHMENTCELL,cell);
	}
	
}

void EmailWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,int tabletype){
	if (tabletype == _TABLE_TYPE_QUERY_)
	{
		_mapCellQueryBtn(idx,cell);
		if (m_CurrEmailMenuIndex== -1)
		{
			NFC_showNode(udCELLSELECTICON,cell,false);
		}
		else
		{
			if (m_CurrEmailMenuIndex == idx)
			{
				NFC_showNode(udCELLSELECTICON,cell,true);
			}
			else
			{
				NFC_showNode(udCELLSELECTICON,cell,false);
			}
		}
	
		if (getCurrentSubTabIndex()==kSYSTEM)
		{
			EmailListData *dd=EMAILDATAHANDLER->m_vecSystemEmail[idx];
			if (dd->hasread == _TYPE_ALREADY_READ_)
			{
				NFC_setPicForCCSprite(udCELLMAILICON,cell,EMAIL_POENED_ICON);
			}
			else
			{
				NFC_setPicForCCSprite(udCELLMAILICON,cell,EMAIL_CLOSE_ICON);
			}
	
			NFC_setLabelString(udCELLMAILTITLE,cell,dd->title_.c_str());
		}else if(getCurrentSubTabIndex()==kPERSONAL){
			EmailListData *dd=EMAILDATAHANDLER->m_vecPersonalEmail[idx];
			if (dd->hasread == _TYPE_ALREADY_READ_)
			{
				NFC_setPicForCCSprite(udCELLMAILICON,cell,EMAIL_POENED_ICON);
			}
			else
			{
				NFC_setPicForCCSprite(udCELLMAILICON,cell,EMAIL_CLOSE_ICON);
			}
			NFC_setLabelString(udCELLMAILTITLE,cell,dd->title_.c_str());
		}
	}
	else if (tabletype == _TABLE_TYPE_ATTACHMENT_)
	{
		EmailListDataObject *data = NULL;
		data = EMAILDATAHANDLER->m_pEmailInfo->attachmentlist[idx];
		assert(data != NULL);
		char buff[32]={0};
		int count = data->count_;
		sprintf(buff,"%d",count);
		NFC_setLabelString(udINFOCELLNUM,cell,buff);
		_mapCellAttachmentBtn(idx,cell);
		//设置当前附件图标
		_setAttachmenticon(data,cell);
	}	
}

void EmailWindow::_setAttachmenticon(EmailListDataObject *data,cocos2d::extension::CCTableViewCell* cell)
{
	switch(data->type_)
	{
	case kDT_AWARD_OBJECT:
		{
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(data->quality_,data->iconId_);
			dd->setEnabled(true);
			if(data->catogory == kBAGSKIN){
				dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
			}
			else{
				dd->setContentScale(1.0f);
			}
		}
		break;
	case kDT_AWARD_MONEY:
		{
			int quality=_GOLD_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD); 
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(quality,iconID);
			dd->setEnabled(false);
		}
		break;
	case kDT_AWARD_EXP:	
		{
			int quality=_EXP_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP); 
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(quality,iconID);
			dd->setEnabled(false);
		}
		break;
	case kDT_AWARD_DIAMOND:
		{
			int quality=_DIAMOND_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND); 
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(quality,iconID);
			dd->setEnabled(false);
		}
		break;
	case kDT_AWARD_PRESTIGE:
		{
			int quality=_PREGIST_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE); 
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(quality,iconID);
			dd->setEnabled(false);
		}
		break;
	case kDT_AWARD_POWER:
		{
			int quality=_POWER_QUALITY_RESID_;
			int iconID = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG); 
			DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
			dd->ChangeObject(quality,iconID);
			dd->setEnabled(false);
		}
		break;
	default:
		break;
	}
}

void EmailWindow::On_TabIndex_Click(cocos2d::CCObject * pSender){
	CCMenuItem* cc=(CCMenuItem*)pSender;
	if (cc->getTag()==udTAB1)
	{
		if (getCurrentSubTabIndex() == kSYSTEM)
			return;
		selectSubTabItem(kSYSTEM);	
	}	
	else if(cc->getTag()==udTAB2)
	{
		if (getCurrentSubTabIndex() == kPERSONAL)
			return;
		selectSubTabItem(kPERSONAL);
	}	
}

void EmailWindow::On_Event_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udCLOSEBTN)
	{
		PushEvent(_TYPEF_EVENT_HIDE_EMAILWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
}

void EmailWindow::On_WriteBtn_Click(cocos2d::CCObject * pSender){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_WRITEEMAILWINDOW_);
	
}
void EmailWindow::On_CheckInfoBtn_Click(cocos2d::CCObject * pSender){

	FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(EMAILDATAHANDLER->m_pEmailInfo->sourceId, _TYPED_WINDOW_EMAIL_WINDOW_);
}
void EmailWindow::On_RemoveBtn_Click(cocos2d::CCObject * pSender){
	if (getCurrentSubTabIndex()==kSYSTEM)
	{
		int Attachmentnum = EMAILDATAHANDLER->m_pEmailInfo->attachmentlist.size();
		if (Attachmentnum == 0)
		{
			EMAILDATAHANDLER->RemoveEmail(EMAILDATAHANDLER->m_pEmailInfo->mailID_,kSYSTEM);
		}
		else
		{
			NFC_showMessageBox(kEMAIL_REMOVE_MESSAGE,SysLangDataManager::get_instance2()->GetSysLangById(680).c_str());
		}
		
	}else if(getCurrentSubTabIndex()==kPERSONAL){
		EMAILDATAHANDLER->RemoveEmail(EMAILDATAHANDLER->m_pEmailInfo->mailID_,kPERSONAL);
	}
}
void EmailWindow::On_GetBtn_Click(cocos2d::CCObject * pSender){
	EmailListData *dd=EMAILDATAHANDLER->m_vecSystemEmail[m_CurrEmailMenuIndex];
	EMAILDATAHANDLER->GetATT(dd->mailID_);
}
void EmailWindow::On_ReplyBtn_Click(cocos2d::CCObject * pSender){

	if (m_CurrEmailMenuIndex == -1)
		return;

	std::string str =  EMAILDATAHANDLER->m_pEmailInfo->sourceName;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_WRITEEMAILWINDOW_,str);
}

void EmailWindow::On_GetAllBtn_Click(cocos2d::CCObject *pSender){
	CCLOG("GetAllBtn Clicked!!!!");
	EMAILDATAHANDLER->m_IsGetAllMaillist = true;
	EMAILDATAHANDLER->QueryEmail();
}



void EmailWindow::selectTabItem(int idx){
	
}

void EmailWindow::selectSubTabItem(int idx)
{
	m_CurrEmailMenuIndex = -1;
	/*HidePersonalProtocol();
	HideSystemProtocol();*/
	if (idx == kSYSTEM)
	{
		HideSystemProtocol();
		HidePersonalProtocol();
	}
	else if (idx == kPERSONAL)
	{
		HideSystemProtocol();
	}
	CCMenu* menu=(CCMenu*)m_pRoot->getChildByTag(udTAB1+idx);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(udTAB1+idx);
	if (m_pCurItem){
		//还原成未选中
		m_pCurItem->unselected();
	}
	cc->selected(true);
	m_CurrSubTabIndex=idx;
	On_Tab_Sub_Selected(idx);
	m_pCurItem=cc;

}

void EmailWindow::On_Tab_Sub_Selected(int idx)
{
	if (idx == getCurrentSubTabIndex())
	{
		_layoutForSystem();
	}
	else if (idx == getCurrentSubTabIndex())
	{
		_layoutForPersonal();
	}
}

void EmailWindow::_mapCellQueryBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
	CCMenu* menu=(CCMenu*)cell->getChildByTag(udCELLBG);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(idx);
	cc->setTarget(this,menu_selector(EmailWindow::On_Check_Email));
}

void EmailWindow::_mapCellAttachmentBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell)
{
#if 0
	CCMenu* menu=(CCMenu*)cell->getChildByTag(udINFOCELLBG);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(idx);
	cc->setTarget(this,menu_selector(EmailWindow::On_CheckAttach_Click));
#endif
	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udINFOCELL_OBJ_);
	dd->setIDX(idx);
	dd->setTarget(this,menu_selector(EmailWindow::On_CheckAttach_Click));
}

void EmailWindow::On_Check_Email(cocos2d::CCObject* pSender)
{	
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;	
	int index = cc->getIDX();
	_showMailDetail(index);
}

void EmailWindow::On_CheckAttach_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;	
	int index = cc->getIDX();
	EmailListDataObject* data = EMAILDATAHANDLER->m_pEmailInfo->attachmentlist[index];
	if (data == NULL)
		return;
	
	if (data->type_ == kEFFECT_TYPE_OBJECT)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(data->templateId_, _TYPED_WINDOW_EMAIL_WINDOW_);
	}
}

void EmailWindow::ShowSystemProtocol(EmailInfoData* data)
{
	NFC_showNode(udREMOVEBTN,m_pRoot,true);
	NFC_showNode(udREMOVEBTNTITLE,m_pRoot,true);
	
	if (data->attachmentlist.size())
	{
		
		NFC_showNode(udGETBTN,m_pRoot,true);
		NFC_showNode(udGETBTNTITLE,m_pRoot,true);
		NFC_showNode(udLETTERLINE,m_pRoot,true);
	}
	else
	{
		NFC_showNode(udLETTERLINE,m_pRoot,false);
		NFC_showNode(udGETBTN,m_pRoot,false);
		NFC_showNode(udGETBTNTITLE,m_pRoot,false);
		NFC_showNode(udLETTERLINE,m_pRoot,false);
	}
	NFC_refreshTableView(m_pTableAttachment);
	NFC_showNode(udCHECKINFOBTN,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTNTITLE,m_pRoot,false);

	NFC_showNode(udSENDER,m_pRoot,true);
	NFC_showNode(udCHECKFRITEXTBG,m_pRoot,true);
	NFC_showNode(udSENDERTEXT,m_pRoot,true);
	NFC_showNode(udDATE,m_pRoot,true);
	NFC_showNode(udCONTENT,m_pRoot,true);
}
void EmailWindow::HideSystemProtocol()
{
	NFC_showNode(udREMOVEBTN,m_pRoot,false);
	NFC_showNode(udREMOVEBTNTITLE,m_pRoot,false);
	NFC_showNode(udGETBTN,m_pRoot,false);
	NFC_showNode(udGETBTNTITLE,m_pRoot,false);
	NFC_showNode(udLETTERLINE,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTN,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTNTITLE,m_pRoot,false);
	NFC_showNode(udSENDER,m_pRoot,false);
	NFC_showNode(udCHECKFRITEXTBG,m_pRoot,false);
	NFC_showNode(udSENDERTEXT,m_pRoot,false);
	NFC_showNode(udDATE,m_pRoot,false);
	NFC_showNode(udCONTENT,m_pRoot,false);
	
	//NFC_showNode(udGETALLBTN,m_pRoot,false);
	//NFC_showNode(udGETALLBTNTITLE,m_pRoot,false);

	EMAILDATAHANDLER->m_pEmailInfo->ClearAttachmentList();
	NFC_refreshTableView(m_pTableAttachment);
}
void EmailWindow::ShowPersonalProtocol()
{
	NFC_showNode(udREMOVEBTN,m_pRoot,true);
	NFC_showNode(udREMOVEBTNTITLE,m_pRoot,true);
	NFC_showNode(udREPLYBTN,m_pRoot,true);
	NFC_showNode(udREPLYBTNTITLE,m_pRoot,true);
	NFC_showNode(udLETTERLINE,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTN,m_pRoot,true);
	NFC_showNode(udCHECKINFOBTNTITLE,m_pRoot,true);

	NFC_showNode(udSENDER,m_pRoot,true);
	NFC_showNode(udCHECKFRITEXTBG,m_pRoot,true);
	NFC_showNode(udSENDERTEXT,m_pRoot,true);
	NFC_showNode(udDATE,m_pRoot,true);
	NFC_showNode(udCONTENT,m_pRoot,true);

}
void EmailWindow::HidePersonalProtocol()
{
	NFC_showNode(udREMOVEBTN,m_pRoot,false);
	NFC_showNode(udREMOVEBTNTITLE,m_pRoot,false);
	NFC_showNode(udREPLYBTN,m_pRoot,false);
	NFC_showNode(udREPLYBTNTITLE,m_pRoot,false);
	NFC_showNode(udLETTERLINE,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTN,m_pRoot,false);
	NFC_showNode(udCHECKINFOBTNTITLE,m_pRoot,false);

	NFC_showNode(udSENDER,m_pRoot,false);
	NFC_showNode(udCHECKFRITEXTBG,m_pRoot,false);
	NFC_showNode(udSENDERTEXT,m_pRoot,false);
	NFC_showNode(udDATE,m_pRoot,false);
	NFC_showNode(udCONTENT,m_pRoot,false);

	//NFC_showNode(udGETALLBTN,m_pRoot,true);
	//NFC_showNode(udGETALLBTNTITLE,m_pRoot,true);
	EMAILDATAHANDLER->m_pEmailInfo->ClearAttachmentList();
}


void EmailWindow::refreshUIData()
{
	char tmp[64] ={0};
	sprintf(tmp,"%d",ROLEINFODATAHANDLER->m_pRIData->money_);
	NFC_setLabelString(udMONEYTEXTTTF,m_pRoot,tmp);
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%d",ROLEINFODATAHANDLER->m_pRIData->jewels_);
	NFC_setLabelString(udDIAMONDTEXTTTF,m_pRoot,tmp);
}