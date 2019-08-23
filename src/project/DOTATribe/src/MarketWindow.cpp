//Name : MarketWindow
//Function : 商城
//Author : 吕云龙
//最后修时间 20131210

#include "../include/MarketWindow.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/config_HomeWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/WindowManager.h"
#include "../include/SysLangDataManager.h"

using namespace std;

USING_NS_CC;




MarketWindow::MarketWindow()
:m_pSubView(0)
,m_nSVZorder(10)
,m_nBackWindow(-1)
{
	m_WindowType   = _TYPED_WINDOW_MARKETWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

MarketWindow::~MarketWindow()
{
	m_pSubView=NULL;
}

bool MarketWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MARKETPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_MARKETPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_MARKETPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_SHOP_BUY_COUNTERSIGN, true);

	return IWindow::Init();
}

bool MarketWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();
		_mapBtn();
		return true;
	} 
	while (false);

	return false;
}

void MarketWindow::Tick()
{
	IWindow::Tick();
	if(m_pSubView)
		m_pSubView->onTick();
}

void MarketWindow::Destroy()
{
	m_nBackWindow = -1;
	
    if(m_pSubView){
 		m_pSubView->onDestroy();
 		m_pSubView=0;
 	}
	m_pRootNode->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void MarketWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_MARKETPWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_MARKETPWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	if (m_pSubView)
	{
		m_pSubView->EventWindowCallBack(iEventType,paramList);
	}
}

void MarketWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	//第一个参数为子界面
	std::list<std::string>::iterator it=paramList.begin();
	string tmp;
	if (paramList.size()>0){
		tmp=*it++;
		int ntabNum=atoi(tmp.c_str());
		if (paramList.size()>1){
			tmp=*it++;
			m_nBackWindow=atoi(tmp.c_str());
		}
		if (paramList.size()>2){
			m_strParam1=*it++;
		}
		_selectTabItem(ntabNum);
	}else{
		_selectTabItem(0);
	}
}

void MarketWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	//Fadeout(IWINDOW_FADEOUT_DURING);
	Destroy();
}

void MarketWindow::_initLayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMARKETWINDOW,m_pRootNode);
}

void MarketWindow::_loadSubView(unsigned int idx){

	CCNode* root=m_pRootNode;
	if(idx == 0)
	{
		if(m_pSubView)
		{
			if(typeid(* m_pSubView) == typeid(BoutiqueView))
				return;
			else
				m_pSubView->onDestroy();
		}
		SHOPINFODATAHANDLER->m_shopId = BOUTIQUE_MARKET;
		SHOPINFODATAHANDLER->ToServerShopInfoPacket();
		m_pSubView=new BoutiqueView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
}

void MarketWindow::_mapBtn()
{
	CMenuItemSprite* cc = NULL;
	//close
	cc=(CMenuItemSprite*)NFC_getMenuItem(udCLOSEBTN,m_pRootNode);
	cc->setIDX(udCLOSEBTN);
	cc->setTarget(this,menu_selector(MarketWindow::On_Close_Window));

	for (int i=udTAB1;i<=udTAB2;i++)
	{
		cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(MarketWindow::On_Tab_Selected));
	}
}

void MarketWindow::On_Close_Window(cocos2d::CCObject* pSender){
	LOGGERSYSTEM->LogInfo("On_Close_Window");
	if(m_nBackWindow==_TYPED_EVENT_SHOW_STRENTHENWINDOW_){
		EVENTSYSTEM->PushEvent(_TEPED_EVENT_EQUIPLVUP_AFTER_CHOOSECOST_);
	}else if (m_nBackWindow>=0){
		if (m_strParam1.length()>0)
			EVENTSYSTEM->PushEvent(m_nBackWindow,m_strParam1);
		else
			EVENTSYSTEM->PushEvent(m_nBackWindow);
	}else{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MARKETPWINDOW_);
}

void MarketWindow::On_Tab_Selected(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx = cc->getIDX();
	int type = 0;
	if (idx == udTAB1)
	{
		type = TAB_VIEW_INDEX_0_;
	}
	else if (idx == udTAB2)
	{
		type = TAB_VIEW_INDEX_1_;
	}
	_selectTabItem(type);
}


//选中某个标签
void MarketWindow::_selectTabItem(unsigned int idx){
	_resetAllHighlight();
	_highlightTabItem(idx);
	_loadSubView(idx);
}

/*
	取消所有页签选中
*/
void MarketWindow::_resetAllHighlight(){
	for (int i=udTAB1;i<=udTAB2;i++)
	{
		CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->unselected();
	}
}

//点亮页签
void MarketWindow::_highlightTabItem(unsigned int type){
	int idx = 0;
	if (type == TAB_VIEW_INDEX_0_)
	{
		idx = udTAB1;
	}
	else if (type == TAB_VIEW_INDEX_1_)
	{
		idx = udTAB2;
	}

	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(idx,m_pRootNode);
	cc->selected(true);
}
