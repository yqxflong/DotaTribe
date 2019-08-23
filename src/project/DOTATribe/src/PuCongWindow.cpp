//Name：Pucong
//Function：仆从窗口
//Author ： 方骏

#include "../include/PuCongWindow.h"
#include "../include/WindowManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ServantView.h"
#include "../include/VariableSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/config_HomeWindow.h"
#include "../include/GuideSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MiningView.h"
#include "../include/HuntView.h"
#include "../include/MiningDataHandler.h"
#include "../include/config_HomeWindow.h"
#include "../include/MessageBoxWindow.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


PuCongWindow::PuCongWindow()
:m_pSubView(0)
,m_nSVZorder(10)
,m_nBackWindow(-1)
{
	m_WindowType   = _TYPED_WINDOW_PUCONG_WINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

PuCongWindow::~PuCongWindow()
{
	m_pSubView=0;
}

bool PuCongWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
	RegisterEvent(_TYPED_EVENT_UPDATE_PUCONGWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_PUCONGWINDOW_, true);

	//矿洞部分
	RegisterEvent(_TYPED_EVENT_MINING_ENTERMINING_GETDATA_, true);


	//奴隶部分
	RegisterEvent(_TYPED_EVENT_SERVANT_PLAYER_IDENTITYCHANGED_, true);//用于身份变化
	RegisterEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERCATCH_GETDATA_, true);	//奴隶主进入抓捕
	RegisterEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERPLAY_GETDATA_, true);		//奴隶主进入互动
	RegisterEvent(_TYPED_EVENT_SERVANT_MASTER_PLAYSUCCESS_GETDATA_, true);	//奴隶主互动成功
	RegisterEvent(_TYPED_EVENT_SERVANT_MASTER_NEWS_COME_, true);				//奴隶主新闻到来
	RegisterEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERRESCUE_GETDATA_, true);	//奴隶主进入解救
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERREVOLT_GETDATA_, true);	//奴隶进入反抗
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_BRIBESUCCESS_GETDATA_, true);	//奴隶贿赂成功
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERPLAY_GETDATA_, true);		//奴隶进入互动
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_NEWS_COME_, true);				//奴隶主新闻到来
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_PLAYSUCCESS_GETDATA_, true);	//奴隶互动成功
	RegisterEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERSOS_GETDATA_, true);		//奴隶进入求救界面
	RegisterEvent(_TYPED_EVENT_SERVANT_COMFIRM_IDENTITYCHANGED_, true);		//确认身份切换

	RegisterEvent(_TYPED_EVENT_BUYHUNTTIMES_GETDATA_, true);			//购买寻宝次数

	return IWindow::Init();
}

bool PuCongWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_checkNewFunc();
		_loadWindowControls();
		return true;
	} 
	while (false);

	return false;
}

	/*
		检查新功能开启
	*/
void PuCongWindow::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_3_LABOR)){
		//======结束新功能开启=======
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_3_LABOR);
	}
}

void PuCongWindow::Tick()
{
	if(m_pSubView)
		m_pSubView->onTick();

	IWindow::Tick();
}

void PuCongWindow::Destroy()
{
	if(m_pSubView){
		m_pSubView->onDestroy();
		m_pSubView=0;
	}


	IWindow::Destroy();
}

void PuCongWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_PUCONGWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_PUCONGWINDOW_)
	{

	}
	else if(iEventType == _TYPED_EVENT_HIDE_PUCONGWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_FADEOUT_PUCONGWINDOW_)
	{

	}
	else if(iEventType == _TYPED_EVENT_MINING_ENTERMINING_GETDATA_)
	{
		//矿洞数据
		if(dynamic_cast<MiningView *>(m_pSubView))
		{
			MiningView * view = (MiningView *)m_pSubView;
			view->Function_GetEnterMiningData();
		}
		else if(dynamic_cast<HuntView *>(m_pSubView))
		{
			HuntView * view = (HuntView *)m_pSubView;
			view->Function_GetEnterMiningData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_PLAYER_IDENTITYCHANGED_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_IdentityChanged(paramList);
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_MASTER_ENTERCATCH_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetMasterEnterCatchData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_MASTER_ENTERPLAY_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetMasterEnterPlayData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_MASTER_PLAYSUCCESS_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetMasterPlaySuccess();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_MASTER_NEWS_COME_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetMasterNews();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_MASTER_ENTERRESCUE_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetMasterEnterResceuData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_ENTERREVOLT_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlaveEnterRevoltData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_BRIBESUCCESS_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlaveBribeSuccess();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_ENTERPLAY_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlaveEnterPlayData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_NEWS_COME_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlaveNews();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_PLAYSUCCESS_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlavePlaySuccess();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_SLAVE_ENTERSOS_GETDATA_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_GetSlaveEnterSOSData();
		}
	}
	else if(iEventType == _TYPED_EVENT_SERVANT_COMFIRM_IDENTITYCHANGED_)
	{
		if(dynamic_cast<ServantView *>(m_pSubView))
		{
			ServantView * view = (ServantView *)m_pSubView;
			view->Function_ConfirmIdentityChanged();
		}
	}
	else if(iEventType == _TYPED_EVENT_BUYHUNTTIMES_GETDATA_)
	{
		MININGDATAHANDLER->ToServerEnterMining();
	}
}

void PuCongWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	string tmp;
	if (paramList.size()>0){
		tmp=*it++;
		int ntabNum=atoi(tmp.c_str());
		selectTabItem(ntabNum);//选中的分页
		if (paramList.size()>1){
			tmp=*it++;
			m_nBackWindow=atoi(tmp.c_str());//回退的页面
		}
		if (paramList.size()>2){
			m_strParam1=*it++;//返回页面的分页
		}
	}else{
		if(ROLEINFODATAHANDLER->m_pRIData->level_ >= _LV_HOMEWINDOW_NEWSCENE_MINING)
		{
			selectTabItem(HLW_HUNT);
		}
		else if(ROLEINFODATAHANDLER->m_pRIData->level_ >= _LV_HOMEWINDOW_NEWSCENE_HUNT)
		{
			selectTabItem(HLW_HUNT);
		}
		else
		{
			selectTabItem(HLW_SERVANT);
		}
	}
}

void PuCongWindow::_loadWindowControls(){
	
	m_pRoot=m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kPUCONGWINDOW, m_pRoot);
	_mapBtn();
}

void PuCongWindow::_mapBtn()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	menu = (CCMenu *)m_pRoot->getChildByTag(pCloseBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(PuCongWindow::On_Close_Window));

	menu = (CCMenu *)m_pRoot->getChildByTag(pMiningTab);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(PuCongWindow::On_Tab_Selected));
	item->setIDX(HLW_MINING);

	menu = (CCMenu *)m_pRoot->getChildByTag(pHuntTab);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(PuCongWindow::On_Tab_Selected));
	item->setIDX(HLW_HUNT);

	menu = (CCMenu *)m_pRoot->getChildByTag(pServantTab);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(PuCongWindow::On_Tab_Selected));
	item->setIDX(HLW_SERVANT);

}

void PuCongWindow::_loadSubViews(unsigned int idx){
	LOGGERSYSTEM->LogInfo("PuCongWindow::_loadSubViews==begin");
	const CCSize &winsz=CCDirector::sharedDirector()->getWinSize();
	CCNode* root=m_pRootNode;
	if(idx == HLW_MINING)
	{
		if(m_pSubView){
			if(typeid(* m_pSubView) == typeid(MiningView))
				return;
			else
				m_pSubView->onDestroy();
		}
		m_pSubView=new MiningView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
	else if(idx == HLW_HUNT)
	{
		if(m_pSubView){
			if(typeid(* m_pSubView) == typeid(HuntView))
				return;
			else
				m_pSubView->onDestroy();
		}
		m_pSubView=new HuntView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
	else if (idx==HLW_SERVANT){
		if(m_pSubView){
			if(typeid(* m_pSubView) == typeid(ServantView))
				return;
			else
				m_pSubView->onDestroy();
		}
		m_pSubView=new ServantView();
		m_pSubView->onLoad();
		root->addChild(m_pSubView,m_nSVZorder);
	}
	LOGGERSYSTEM->LogInfo("PuCongWindow::_loadSubViews==end");
}

void PuCongWindow::selectTabItem(unsigned int index)
{
	if(index == HLW_MINING)
	{
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(pMiningTab);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->selected(true);

		menu = (CCMenu *)m_pRoot->getChildByTag(pHuntTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
		menu = (CCMenu *)m_pRoot->getChildByTag(pServantTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
	}
	else if(index == HLW_SERVANT)
	{
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(pServantTab);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->selected(true);

		menu = (CCMenu *)m_pRoot->getChildByTag(pMiningTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
		menu = (CCMenu *)m_pRoot->getChildByTag(pHuntTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
	}
	else if(index == HLW_HUNT)
	{
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(pHuntTab);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->selected(true);

		menu = (CCMenu *)m_pRoot->getChildByTag(pMiningTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
		menu = (CCMenu *)m_pRoot->getChildByTag(pServantTab);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->unselected();
	}


	_loadSubViews(index);
}

void PuCongWindow::On_Close_Window(cocos2d::CCObject* pSender){
	LOGGERSYSTEM->LogInfo("On_Close_Window");

	if(dynamic_cast<ServantView *>(m_pSubView))
	{
		ServantView * view = (ServantView *)m_pSubView;
		view->Function_OnClose();
	}
	
	if (m_nBackWindow>=0)
	{
		EVENTSYSTEM->PushEvent(m_nBackWindow,m_strParam1);
		m_nBackWindow = -1;
	}else{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_);

	//1.干掉所有effect
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);
}

void PuCongWindow::On_Tab_Selected(cocos2d::CCObject* pSender){
	LOGGERSYSTEM->LogInfo("onTabSelected==begin");

	CMenuItemSprite * sp = (CMenuItemSprite *)pSender;
	int idx = sp->getIDX();

	if(idx == HLW_MINING)
	{
		if(ROLEINFODATAHANDLER->m_pRIData->level_ < _LV_HOMEWINDOW_NEWSCENE_MINING)
		{//35，采矿页面
			char temp[1024] = {0};
			std::sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2036).c_str(), _LV_HOMEWINDOW_NEWSCENE_MINING);
			NFC_showMessageBoxSingle(kDEFAULT, temp);

			return;
		}
	}
	else if(idx == HLW_SERVANT)
	{
		if(ROLEINFODATAHANDLER->m_pRIData->level_ < _LV_HOMEWINDOW_NEWSCENE_SERVANT)
		{//27,苦工页面
			char temp[1024] = {0};
			std::sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2037).c_str(), _LV_HOMEWINDOW_NEWSCENE_SERVANT);
			NFC_showMessageBoxSingle(kDEFAULT, temp);
			return;
		}
	}

	selectTabItem(idx);

	LOGGERSYSTEM->LogInfo("onTabSelected==end");

}
