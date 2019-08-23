//Name : LimitedActivityWindow
//Function : 限时活动
//Author : 尹强

#include <cocos2d.h>
#include "../include/LimitedActivityWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"
#include "../include/CTableView.h"
#include "../include/CMenuItemSprite.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/LimitedActivityHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/TimeSystem.h"
#include "../include/CTableView.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/DTAwardBoard.h"
#include "../include/MaskNode.h"
#include "../include/ServerInfoDataHandler.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;
#define BETWEEN_RANGE 30.0f
#define BETWEEN_RANGE1 5.0f
LimitedActivityWindow::LimitedActivityWindow()
	:m_nCurTab(kLA_TAB1)
	,m_nCurActivityIndex(0)
	,m_pTable1(0)
	,m_pTable2(0)
	,m_lastSelectTab(NULL)
{
	m_WindowType   = _TYPED_WINDOW_LIMITEDACTIVITY_WINDOW_;
	m_pRoot_Activity=NULL;
	m_pRoot_NoticeBox=NULL;
	m_pRoot_Exchange = NULL;
}

bool LimitedActivityWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LIMITEDACTIVITYWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LIMITEDACTIVITYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_NOTICE,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);//刷新金钱消息
	RegisterEvent(_TYPED_EVENT_LIMITACTIVITY_EXCHANGE_CDKEY_RESLUT_, true);//注册监听兑换码兑换结果

	return IWindow::Init();
}

bool LimitedActivityWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLIMITEDACTIVITY,m_pRootNode);
		_mapMoneyAndDiamond();
		_checkCDKeyIsOpen();
		_defaultTab();

		LimitedActivityHandler::get_instance2()->LActivity_Query();
		return true;
	} 
	while (false);

	return false;
}


void LimitedActivityWindow::Tick()
{
	if (m_nCurTab==kLA_TAB1)
	{
		LimitedActivityHandler::get_instance2()->CaculateAllActivityTime();
	}
	IWindow::Tick();
}

void LimitedActivityWindow::Destroy()
{
	m_nCurTab=kLA_TAB1;
	m_nCurActivityIndex=0;
	m_pRoot_Activity=NULL;
	m_pRoot_NoticeBox=NULL;
	m_pRoot_Exchange = NULL;
	m_lastSelectTab = NULL;
	IWindow::Destroy();
}

void LimitedActivityWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_LIMITEDACTIVITYWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_LIMITEDACTIVITYWINDOW_)
	{
		Destroy();
	}else if(iEventType==_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_){
		if (m_nCurTab==kLA_TAB1)
		{
			//确认当前选中的itemIndex是正确的
			int count_items=LimitedActivityHandler::get_instance2()->ActivityItems_.size();
			m_nCurActivityIndex=m_nCurActivityIndex>=count_items?count_items-1:m_nCurActivityIndex;
			m_nCurActivityIndex=m_nCurActivityIndex<0?0:m_nCurActivityIndex;
			//
			NFC_refreshTableViewAndSetOldOffset(m_pTable1);
			NFC_refreshTableViewAndSetOldOffset(m_pTable2);
		}
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_NOTICE)
	{
		_loadLoginNoticeRoot();
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_){
		_mapMoneyAndDiamond();
	}
	else if(iEventType == _TYPED_EVENT_LIMITACTIVITY_EXCHANGE_CDKEY_RESLUT_)
	{
		std::string re = *paramList.begin();
		int result = atoi(re.c_str());
		//收到结果
	}
}

void LimitedActivityWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

static float ACTIVITY_TABLE_REST=80.0f;	//活动内容预留空间

cocos2d::CCSize LimitedActivityWindow::cellSizeForTable(CCTableView *table){
	if (table==m_pTable1)
	{
		CCNode* node=NFC_getNode(kLA_CELL_L,m_pRoot_Activity);
		return node->getContentSize();
	}else{
		ActivityItem& item=LimitedActivityHandler::get_instance2()->ActivityItems_[m_nCurActivityIndex];
		vector<ActivityAward> &awards=item.ActivityAwards_;
		m_fContentHeight=_getActivityTimeAndDesctiptionHeight()+awards.size()*_getOneAwardBarHeight()+ACTIVITY_TABLE_REST;
		return CCSizeMake(0.0f,m_fContentHeight);
	}
}
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
cocos2d::extension::CCTableViewCell* LimitedActivityWindow::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell,table);
	}
	_setTableCell(idx,cell,table);

	return cell;
}
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
unsigned int LimitedActivityWindow::numberOfCellsInTableView(CCTableView *table){
	if (table==m_pTable1)
	{
		return LimitedActivityHandler::get_instance2()->ActivityItems_.size();
	}else{
		if(LimitedActivityHandler::get_instance2()->ActivityItems_.size()>0){
			return 1;
		}else
			return 0;
		
	}
}


void LimitedActivityWindow::editBoxReturn(CCEditBox* editBox)
{

}

//load Subview Root
void LimitedActivityWindow::_loadActivityRoot(){
	_unloadLoginNoticeRoot();
	_unloadExchangeRoot();
	m_pRoot_Activity=CCNode::create();
	m_pRootNode->addChild(m_pRoot_Activity);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLIMITEDACTIVITY_ACTVITY,m_pRoot_Activity);
	_mapTable();
	_mapBtn();
}

void LimitedActivityWindow::_loadLoginNoticeRoot(){
	_unloadActivityRoot();
	_unloadExchangeRoot();
	m_pRoot_NoticeBox=CCLayer::create();
	m_pRootNode->addChild(m_pRoot_NoticeBox);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLIMITEDACTIVITY_NOTICEBOX,m_pRoot_NoticeBox);
	_mapContent();
}

void LimitedActivityWindow::_loadExchangeRoot()
{
	_unloadActivityRoot();
	_unloadLoginNoticeRoot();
	m_pRoot_Exchange=CCNode::create();
	m_pRootNode->addChild(m_pRoot_Exchange);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLIMITEDACTIVITY_EXCHANGE, m_pRoot_Exchange);

	_mapExchange();
}

void LimitedActivityWindow::_unloadActivityRoot(){
	if (m_pRoot_Activity)
	{
		m_pRoot_Activity->removeFromParentAndCleanup(true);
		m_pRoot_Activity=NULL;
		m_pTable1=NULL;
		m_pTable2=NULL;
	}
}

void LimitedActivityWindow::_unloadLoginNoticeRoot(){
	if (m_pRoot_NoticeBox)
	{
		m_pRoot_NoticeBox->removeFromParentAndCleanup(true);
		m_pRoot_NoticeBox=NULL;
	}
}

void LimitedActivityWindow::_unloadExchangeRoot()
{
	if (m_pRoot_Exchange)
	{
		m_pRoot_Exchange->removeFromParentAndCleanup(true);
		m_pRoot_Exchange=NULL;
	}
}

//公告
void LimitedActivityWindow::_mapContent(){
	CScrollView* cc=(CScrollView*)NFC_getNode(kLA_NOTICE_SCROLL,m_pRoot_NoticeBox);
	std::vector<NoticeData>::const_reverse_iterator it1= LimitedActivityHandler::get_instance2()->m_ContentVector.rbegin();
	std::vector<NoticeData>::const_reverse_iterator itend= LimitedActivityHandler::get_instance2()->m_ContentVector.rend();
	CCLayerColor* layer =(CCLayerColor*)cc->getContainer();
	MaskNode* mNodeTitleIcon = (MaskNode*)NFC_getNode(kLA_NOTICE_TITLEICON,m_pRoot_NoticeBox);
	MaskNode* mNodeContent = (MaskNode*)NFC_getNode(kLA_NOTICE_CONTENTTEXT,m_pRoot_NoticeBox);
	MaskNode* mNodeTitleTTF = (MaskNode*)NFC_getNode(kLA_NOTICE_TITLETEXT,m_pRoot_NoticeBox);
	MaskNode* mNodeline = (MaskNode*)NFC_getNode(kLA_NOTICE_LINE,m_pRoot_NoticeBox);
	float heiht = 0.0f;
	float sizeheight = 0.0f;
	size_t vecsize = LimitedActivityHandler::get_instance2()->m_ContentVector.size();
	size_t index = 1;
	for (;it1!=itend;it1++)
	{
		CCLayerColor* bg = CCLayerColor::create();
		bg->setAnchorPoint(ccp(0.5,0.5f));
		CCLabelTTF* ttf1 = (CCLabelTTF*)NFC_createLabelMutilineByViewData(bg,mNodeContent->GetViewData());
		ttf1->setString((*it1).mContent.c_str());
		bg->setContentSize(CCSizeMake(900,ttf1->getContentSize().height));
		bg->setPositionY(bg->getContentSize().height+heiht);
		sizeheight+=bg->getContentSize().height+BETWEEN_RANGE1;
		heiht += (bg->getContentSize().height+BETWEEN_RANGE1);
		layer->addChild(bg);

		bg =CCLayerColor::create();
		bg->setAnchorPoint(ccp(0.5f,0.5f));
		CCSprite* title = NFC_createSpriteByViewData(bg,mNodeTitleIcon->GetViewData());
		title->setAnchorPoint(ccp(0.5,0.5));
		bg->setContentSize(title->getContentSize());
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_createLabelByViewData(title,mNodeTitleTTF->GetViewData());
		ttf->setString((*it1).mTitle.c_str());
		bg->setPositionY(bg->getContentSize().height/2+heiht);
		sizeheight+=bg->getContentSize().height+BETWEEN_RANGE;
		heiht += (bg->getContentSize().height+BETWEEN_RANGE);

		if (index<vecsize)
		{
			CCSprite* title = NFC_createSpriteByViewData(bg,mNodeline->GetViewData());
			title->setPositionY((bg->getContentSize().height/2+10.0f));
		}
		layer->addChild(bg);
		index++;
	}

	if (sizeheight<cc->getViewSize().height)
	{
		sizeheight = cc->getViewSize().height;
	}
	else
	{
		sizeheight -= BETWEEN_RANGE;
	}
	layer->setContentSize(CCSizeMake(cc->getViewSize().width,sizeheight));
	cc->resizeContent(layer);
}

//活动
void LimitedActivityWindow::_mapTable(){
	m_pTable1=(CTableView*)NFC_getNode(kLA_TABLE1,m_pRoot_Activity);
	m_pTable1->setDataSource(this);
	NFC_refreshTableView(m_pTable1);
	m_pTable2=(CTableView*)NFC_getNode(kLA_TABLE2,m_pRoot_Activity);
	m_pTable2->setDataSource(this);
	NFC_refreshTableView(m_pTable2);
}

void LimitedActivityWindow::_mapBtn(){
	//Tab Item
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_TAB1,m_pRootNode);
	cc->setIDX(kLA_TAB1);
	cc->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Event));
	cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_TAB2,m_pRootNode);
	cc->setIDX(kLA_TAB2);
	cc->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Event));
	cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_TAB3,m_pRootNode);
	cc->setIDX(kLA_TAB3);
	cc->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Event));
	//Button
	cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_CLOSE,m_pRootNode);
	cc->setIDX(kLA_CLOSE);
	cc->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Event));
}

void LimitedActivityWindow::_mapExchange()
{
	//输入框
	cocos2d::extension::CCEditBox * m_pEditBox = (CCEditBox *)m_pRoot_Exchange->getChildByTag(KA_EXCHANGE_EDITBOX);
	m_pEditBox->setMaxLength(100);
	m_pEditBox->setInputMode(kEditBoxInputModeSingleLine);
	m_pEditBox->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBox->setDelegate(this);
	m_pEditBox->setTouchPriority(kPRIORITYMID - 1);

	FSData * d = FONTSTYLEDATAMANAGER->getDataByID(116);
	if(d)
	{
		m_pEditBox->setFontName(d->fontname_);
		m_pEditBox->setFontColor(ccc3(d->colorR_, d->colorG_, d->colorB_));
		m_pEditBox->setFontSize(d->fontsize_);
	}

	m_pEditBox->setPlaceHolder(SysLangDataManager::get_instance2()->GetSysLangById(2059).c_str());


	//按钮
	CCMenu * menu = (CCMenu *)m_pRoot_Exchange->getChildByTag(KA_EXCHANGE_CONFIRMBTN);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(KA_EXCHANGE_CONFIRMBTN);
	item->setTarget(this, menu_selector(LimitedActivityWindow::On_Exchange_Btn_Click));
}

//主
void LimitedActivityWindow::_mapMoneyAndDiamond(){
	NFC_setLabelStringInt(kLA_GOLD_VALUE,m_pRootNode,ROLEINFODATAHANDLER->m_pRIData->money_);
	NFC_setLabelStringInt(kLA_DIAMOND_VALUE,m_pRootNode,ROLEINFODATAHANDLER->m_pRIData->jewels_);
}

void LimitedActivityWindow::_defaultTab(){
	//Tab
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_TAB1,m_pRootNode);
	cc->selected(true);
	m_lastSelectTab = cc;
	m_nCurTab=kLA_TAB1;
	//
	_loadActivityRoot();
}

void LimitedActivityWindow::_checkCDKeyIsOpen(){
	std::vector<FunctionData>::iterator iter = SERVERINFODATAINFO->m_FunctionDatas.begin();
	std::vector<FunctionData>::iterator iter_end = SERVERINFODATAINFO->m_FunctionDatas.end();
	for(; iter != iter_end; ++iter){
		if ( (*iter).functionId == _FUNCTION_CDKEY_ ){
			if ( (*iter).isOpen == true ){
				NFC_showNode(kLA_TAB3,m_pRootNode,true);
				NFC_showNode(kLA_TAB3_TITLE,m_pRootNode,true);
			}
			else{
				NFC_showNode(kLA_TAB3,m_pRootNode,false);
				NFC_showNode(kLA_TAB3_TITLE,m_pRootNode,false);
			}
			break;
		}
	}

}

void LimitedActivityWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table){
	if (table==m_pTable1){
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLIMITEDACTIVITY_CELL_L,cell);
	}else{
		cell->removeAllChildrenWithCleanup(true);
	}
}
void LimitedActivityWindow::_setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table){
	if (table==m_pTable1)
	{
		_setTableCell_ActivityList(idx,cell,table);
	}else{
		_setTableCell_ActivityContent(idx,cell,table);
	}
}

//==================左边的活动列表================================//
void LimitedActivityWindow::_setTableCell_ActivityList(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table){
	//按钮
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kLA_LEFT_CELL_BTN,cell);
	cc->setIDX(idx);
	cc->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Cell_L_Event));
	if (m_nCurActivityIndex==idx)
	{
		cc->selected(true);
	}else{
		cc->unselected();
	}
	//活动名
	ActivityItem& item=LimitedActivityHandler::get_instance2()->ActivityItems_[idx];
	NFC_setLabelString(kLA_LEFT_CELL_TXT,cell,item.name_);
	//提示
	bool showHint=item.hasAwardActive();
	NFC_showNode(kLA_LEFT_CELL_HINT,cell,showHint);
	if (showHint)
	{
		NFC_resumeActionsForSceneSprite(kLA_LEFT_CELL_HINT,cell);
	}
}

//==================右边的活动详细信息================================//
void LimitedActivityWindow::_setTableCell_ActivityContent(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table){
	cell->removeAllChildrenWithCleanup(true);
	const ActivityItem& item=LimitedActivityHandler::get_instance2()->ActivityItems_[m_nCurActivityIndex];
	float posy=m_fContentHeight;
	//sub 1
	posy=_createSub1(cell,posy,item);
	//sub 2
	posy=_createSub2(cell,posy,item);
	/*
		The Award List on the right
	*/
	_createAwards(cell,posy,item);
}

//create Activity Name
float LimitedActivityWindow::_createSub1(cocos2d::CCNode* cell,float posy,const ActivityItem& item){
	//space
	MaskNode* node_space=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLESPACE,m_pRoot_Activity);
	float space=node_space->GetViewData().height_;
	//=sub1bg
	MaskNode* node_sub1bg=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEBG1,m_pRoot_Activity);
	CCSprite* sub1bg=NFC_createSpriteByViewData(cell,node_sub1bg->GetViewData());
	sub1bg->setPositionY(posy);
	//=end sub1bg
	const CCSize& sub1bgsz=sub1bg->getContentSize();
	//=sub1title
	MaskNode* node_sub1title=(MaskNode*)NFC_getNode(kLA_R_CELL_SUBTITLE1,m_pRoot_Activity);
	CCLabelTTF* sub1title=NFC_createLabelByViewData(sub1bg,node_sub1title->GetViewData());
	sub1title->setPosition(ccp(sub1bgsz.width/2,sub1bgsz.height/2));
	//=end sub1title
	posy-=sub1bgsz.height+space;
	//=sub1value
	MaskNode* node_sub1value=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEVALUE1,m_pRoot_Activity);
	CCLabelTTF* sub1value=NFC_createLabelByViewData(cell,node_sub1value->GetViewData());
	sub1value->setPositionY(posy);
	//换算时间。。
	list<int> ll=TIME_getDayhrmin(item.second_);
	list<int>::iterator it=ll.begin();
	int day=*it++;
	int hr=*it++;
	int min=*it;
	//end
	char time[256]="";
	sprintf(time,SysLangDataManager::get_instance2()->GetSysLangById(55).c_str(),day,hr,min);
	sub1value->setString(time);
	//=end sub1value

	posy-=sub1value->getContentSize().height+space;
	return posy;
}

//create Activity Description
float LimitedActivityWindow::_createSub2(cocos2d::CCNode* cell,float posy,const ActivityItem& item){
	//space
	MaskNode* node_space=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLESPACE,m_pRoot_Activity);
	float space=node_space->GetViewData().height_;
	//=sub2bg
	MaskNode* node_sub2bg=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEBG2,m_pRoot_Activity);
	CCSprite* sub2bg=NFC_createSpriteByViewData(cell,node_sub2bg->GetViewData());
	sub2bg->setPositionY(posy);
	//=end sub2bg
	const CCSize& sub2bgsz=sub2bg->getContentSize();
	//=sub2title
	MaskNode* node_sub2title=(MaskNode*)NFC_getNode(kLA_R_CELL_SUBTITLE2,m_pRoot_Activity);
	CCLabelTTF* sub2title=NFC_createLabelByViewData(sub2bg,node_sub2title->GetViewData());
	sub2title->setPosition(ccp(sub2bgsz.width/2,sub2bgsz.height/2));
	//=end sub2title
	posy-=sub2bgsz.height+space;
	//=sub2value
	MaskNode* node_sub2value=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEVALUE2,m_pRoot_Activity);
	CCLabelTTF* sub2value=NFC_createLabelByViewData(cell,node_sub2value->GetViewData());
	sub2value->setDimensions(CCSizeMake(node_sub2value->GetViewData().width_,0));
	sub2value->setPositionY(posy);
	sub2value->setString(item.description_.c_str());
	//=end sub2value

	posy-=sub2value->getContentSize().height+space;
	return posy;
}

//create Activity's Awards
void LimitedActivityWindow:: _createAwards(cocos2d::CCNode* cell,float posy,const ActivityItem& item){
	int count=item.ActivityAwards_.size();
	for (int i=0;i<count;i++)
	{
		const ActivityAward& award=item.ActivityAwards_[i];
		/*
			bg is the rootnode for other controls on it,
			so just ajudge the positon of bg can layout the awards bar
		*/
		MaskNode* node_bg=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_BG,m_pRoot_Activity);
		CCSprite* bg=NFC_createSpriteByViewData(cell,node_bg->GetViewData());
		bg->setPositionY(posy);

//begin:奖品
		int quality=LimitedActivityHandler::get_instance2()->GetAwardQuality(award);
		int iconid=LimitedActivityHandler::get_instance2()->GetAwardIconID(award);
		MaskNode* node_item=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD,m_pRoot_Activity);
		const UIViewData& data_item=node_item->GetViewData();
		DTAwardBoard* dd=NFC_createDTAwardBoardByViewData(bg,data_item);
		dd->ChangeObject(quality,iconid);
		if (LimitedActivityHandler::get_instance2()->NeedAwardTips(award))
		{
			dd->setIDX(i);
			dd->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Cell_Tips_Event));
		}
		//count
		MaskNode* node_count=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_COUNT,m_pRoot_Activity);
		CCLabelTTF* count=NFC_createLabelByViewData(bg,node_count->GetViewData());
		NFC_setLabelStringInt(count,award.amount_);
		//propt
		MaskNode* node_propt=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_PROMPT,m_pRoot_Activity);
		CCLabelTTF* propt=NFC_createLabelByViewData(bg,node_propt->GetViewData());
		NFC_setLabelString(propt,award.prompt_);
//end:奖品
		//btn
		MaskNode* node_btn=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_BTN,m_pRoot_Activity);
		CMenuItemSprite* btn=NFC_createCLabelButtonByViewData(bg,node_btn->GetViewData());
		btn->setIDX(i);
		btn->setTarget(this,menu_selector(LimitedActivityWindow::On_Click_Cell_R_Event));
		//
		if (award.canReceive_==1)
		{
			btn->setVisible(true);
		}else{
			btn->setVisible(false);
		}

		posy-=_getOneAwardBarHeight();
	}
}

/*
	window上按钮的事件
*/
void LimitedActivityWindow::On_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if(cc->getIDX()==kLA_CLOSE){
		PushEvent(_TYPED_EVENT_HIDE_LIMITEDACTIVITYWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}else if(cc->getIDX()==kLA_TAB1){
		if (m_nCurTab!=kLA_TAB1){
			cc->selected(true);
			if(m_lastSelectTab)
				m_lastSelectTab->unselected();
			m_lastSelectTab = cc;
			m_nCurTab=kLA_TAB1;
			_loadActivityRoot();
		}
	}else if(cc->getIDX()==kLA_TAB2){
		if (m_nCurTab!=kLA_TAB2)
		{
			cc->selected(true);
			if(m_lastSelectTab)
				m_lastSelectTab->unselected();
			m_lastSelectTab = cc;
			m_nCurTab=kLA_TAB2;
			SERVERINFODATAINFO->LoginNotice_Request(true);
		}
	}else if(cc->getIDX()==kLA_TAB3){
		if (m_nCurTab!=kLA_TAB3)
		{
			cc->selected(true);
			if(m_lastSelectTab)
				m_lastSelectTab->unselected();
			m_lastSelectTab = cc;
			m_nCurTab=kLA_TAB3;
			_loadExchangeRoot();
		}
	}
}

//左边cell按钮事件
void LimitedActivityWindow::On_Click_Cell_L_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx = cc->getIDX();
	if (idx!=m_nCurActivityIndex)
	{
		CTableView* table=(CTableView*)NFC_getNode(kLA_TABLE1,m_pRoot_Activity);
		//将上一个按钮取消选中
		cocos2d::extension::CCTableViewCell * cell= table->cellAtIndex(m_nCurActivityIndex);
		if(cell)
		{
			CMenuItemSprite* last=(CMenuItemSprite*)NFC_getMenuItem(kLA_LEFT_CELL_BTN,cell);
			last->unselected();
		}
		//选中当前按钮
		cc->selected(true);
		m_nCurActivityIndex = idx;
		LimitedActivityHandler::get_instance2()->CurShowActivityID_=LimitedActivityHandler::get_instance2()->ActivityItems_[idx].id_;
		NFC_refreshTableView(m_pTable2);
	}
}

//右边cell 领取按钮事件
void LimitedActivityWindow::On_Click_Cell_R_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int awardIdx=cc->getIDX();
	ActivityItem& item=LimitedActivityHandler::get_instance2()->ActivityItems_[m_nCurActivityIndex];
	vector<ActivityAward>& awardList=item.ActivityAwards_;
	const ActivityAward& award=awardList[awardIdx];
	//tell server to get the award
	LimitedActivityHandler::get_instance2()->GetAwardFromServer(item.id_,award.rewardID_);
}

//右边cell TIPS事件
void LimitedActivityWindow::On_Click_Cell_Tips_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int awardIdx=cc->getIDX();
	ActivityItem& item=LimitedActivityHandler::get_instance2()->ActivityItems_[m_nCurActivityIndex];
	vector<ActivityAward>& awardList=item.ActivityAwards_;
	const ActivityAward& award=awardList[awardIdx];
	if (award.templateId_ != 0)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(award.templateId_, _TYPED_WINDOW_LIMITEDACTIVITY_WINDOW_);
	}
	
}

void LimitedActivityWindow::On_Exchange_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == KA_EXCHANGE_CONFIRMBTN)
	{
		//兑换码确认按钮
		cocos2d::extension::CCEditBox * m_pEditBox = (CCEditBox *)m_pRoot_Exchange->getChildByTag(KA_EXCHANGE_EDITBOX);
		string cdkey = m_pEditBox->getText();
		//发送 cdkey
		LimitedActivityHandler::get_instance2()->ToServerExchangeCdkey(cdkey);
	}
}

//=====================================tools func============================//
//获取活动时间+活动介绍的高度
float LimitedActivityWindow::_getActivityTimeAndDesctiptionHeight(){
	float height=0.0f;
	//=sub1bg
	MaskNode* node_sub1bg=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEBG1,m_pRoot_Activity);
	height+=NFC_getHeightOfSprite(node_sub1bg->GetViewData().filepath_);
	//=sub1value
	MaskNode* node_sub1value=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEVALUE1,m_pRoot_Activity);
	height+=NFC_getHeightOfLabel(0.0f,node_sub1value->GetViewData().labelstring_);
	//=sub2bg
	MaskNode* node_sub2bg=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEBG2,m_pRoot_Activity);
	height+=NFC_getHeightOfSprite(node_sub2bg->GetViewData().filepath_);
	//=sub2value
	MaskNode* node_sub2value=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLEVALUE2,m_pRoot_Activity);
	height+=NFC_getHeightOfLabel(node_sub2value->GetViewData().width_,node_sub2value->GetViewData().labelstring_);
	//=space
	MaskNode* node_space=(MaskNode*)NFC_getNode(kLA_R_CELL_TITLESPACE,m_pRoot_Activity);
	height+=node_space->GetViewData().height_*4;

	return height;
}

//获取一个奖励条的高度+间距
float LimitedActivityWindow::_getOneAwardBarHeight(){
	float height=0.0f;
	//bg
	MaskNode* node_bg=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_BG,m_pRoot_Activity);
	height+=NFC_getHeightOfSprite(node_bg->GetViewData().filepath_);
	//space
	MaskNode* node_space=(MaskNode*)NFC_getNode(kLA_R_CELL_AWARD_BG_SPACE,m_pRoot_Activity);
	height+=node_space->GetViewData().height_;

	return height;
}