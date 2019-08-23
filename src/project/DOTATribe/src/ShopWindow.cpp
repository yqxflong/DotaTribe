//Name : ShopWindow
//Function : 商店
//Author : 吕云龙

#include "../include/ShopWindow.h"
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




ShopWindow::ShopWindow()
:m_pSubView(0)
,m_nSVZorder(10)
,m_nBackWindow(-1)
{
	m_WindowType   = _TYPED_WINDOW_SHOPWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

ShopWindow::~ShopWindow()
{
	m_pSubView=NULL;
}

bool ShopWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SHOPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SHOPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_RANDOMMARKETPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_SHOP_BUY_COUNTERSIGN, true);
	
	return IWindow::Init();
}

bool ShopWindow::Load()
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

void ShopWindow::Tick()
{
	IWindow::Tick();
	if(m_pSubView)
		m_pSubView->onTick();
}

void ShopWindow::Destroy()
{
	m_nBackWindow = -1;
	
    if(m_pSubView){
 		m_pSubView->onDestroy();
 		m_pSubView=0;
 	}
	m_pRootNode->removeAllChildrenWithCleanup(true);

	IWindow::Destroy();
}

void ShopWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_SHOPWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SHOPWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_RANDOMMARKETPWINDOW_)
	{
		OnUpdataWindowEventHandler(paramList);
	}
	if (m_pSubView)
	{
		m_pSubView->EventWindowCallBack(iEventType,paramList);
	}
}

void ShopWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	//第一个参数为子界面
	std::list<std::string>::iterator it=paramList.begin();
	string tmp;
	if (paramList.size()>0){
		tmp=*it++;
		int ntabNum=atoi(tmp.c_str());
		_selectTabItem(ntabNum);
		if (paramList.size()>1){
			tmp=*it++;
			m_nBackWindow=atoi(tmp.c_str());
		}
		if (paramList.size()>2){
			m_strParam1=*it++;
		}
	}else{
		_selectTabItem(0);
	}
}

void ShopWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	//Fadeout(IWINDOW_FADEOUT_DURING);
	Destroy();
}

void ShopWindow::OnUpdataWindowEventHandler(std::list<std::string>& paramList)
{
	if (m_pSubView!=NULL)
	{
		m_pSubView->onDestroy();
		PushEvent(_TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_);
		PushEvent(_TYPED_EVENT_HIDE_SHOPTIPSWINDOW_);
		RANDOMSHOPDATAHANDLER->ToServerRandomShopInfoPacket();
		m_pSubView=new SpecialOfferView();
		m_pSubView->onLoad();
		m_pRootNode->addChild(m_pSubView,m_nSVZorder);
	}
}

void ShopWindow::_initLayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPWINDOW,m_pRootNode);
}

void ShopWindow::_loadSubView(unsigned int idx){

	CCNode* root=m_pRootNode;
	if (idx == 0)
	{
		if(m_pSubView)
		{
			if(typeid(* m_pSubView) == typeid(SpecialOfferView))
				return;
			else
				m_pSubView->onDestroy();
		}
		RANDOMSHOPDATAHANDLER->ToServerRandomShopInfoPacket();
		m_pSubView=new SpecialOfferView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
	else if (idx == 1)
	{
		if(m_pSubView)
		{
			if(typeid(* m_pSubView) == typeid(ShopView))
				return;
			else
				m_pSubView->onDestroy();
		}
		SHOPINFODATAHANDLER->m_shopId = PRESTIGE_SHOP;
		SHOPINFODATAHANDLER->ToServerShopInfoPacket();
		m_pSubView=new ShopView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
	//秘宝商店
	/*else if(idx == 1)//秘宝商店
	{
		if(_checkOpenMBShop()){
			if(m_pSubView)
			{
				if(typeid(* m_pSubView) == typeid(SecretView))
					return;
				else
					m_pSubView->onDestroy();
			}
			SHOPINFODATAHANDLER->m_shopId = SECRET_SHOP;
			SHOPINFODATAHANDLER->ToServerShopInfoPacket();
			m_pSubView=new SecretView();
			m_pSubView->onLoad();
			root->addChild(m_pSubView,m_nSVZorder);
		}
	}*/
}

void ShopWindow::_mapBtn()
{
	CMenuItemSprite* cc = NULL;
	//close
	cc=(CMenuItemSprite*)NFC_getMenuItem(udCLOSEBTN,m_pRootNode);
	cc->setIDX(udCLOSEBTN);
	cc->setTarget(this,menu_selector(ShopWindow::On_Close_Window));

	for (int i=udTAB1;i<=udTAB2;i++)
	{
		cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(ShopWindow::On_Tab_Selected));
	}
}

void ShopWindow::On_Close_Window(cocos2d::CCObject* pSender){
	LOGGERSYSTEM->LogInfo("On_Close_Window");
	if (m_nBackWindow>=0)
	{
		if (m_strParam1.length()>0)
			EVENTSYSTEM->PushEvent(m_nBackWindow,m_strParam1);
		else
			EVENTSYSTEM->PushEvent(m_nBackWindow);
	}else{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SHOPWINDOW_);
}

void ShopWindow::On_Tab_Selected(cocos2d::CCObject* pSender)
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

/*
	检查是否开启秘宝商店
*/
bool ShopWindow::_checkOpenMBShop(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MIBAOSHOP))
	{
		string str2=SysLangDataManager::get_instance2()->GetSysLangById(590);
		char tmp[128]={0};
		sprintf(tmp,str2.c_str(),_LV_HOMEWINDOW_NEWSCENE_MIBAOSHOP);
		NFC_showMessageBox(kDEFAULT,tmp);
		_selectTabItem(0);//还原成第一个选中的状态
		return false;
	}
	return true;
}


//选中某个标签
void ShopWindow::_selectTabItem(unsigned int idx){
	_resetAllHighlight();
	_highlightTabItem(idx);
	_loadSubView(idx);
}

/*
	取消所有页签选中
*/
void ShopWindow::_resetAllHighlight(){
	for (int i=udTAB1;i<=udTAB2;i++)
	{
		CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->unselected();
	}
}

//点亮页签
void ShopWindow::_highlightTabItem(unsigned int type){
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
