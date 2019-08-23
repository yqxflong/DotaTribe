// Name : RechargeWarnWindow.h
// Function:充值提示绑定账号对话框窗口
// Author : lvyunlong
// Date: 20131119

#include "../include/RechargeWarnWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/IAPSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

RechargeWarnWindow::RechargeWarnWindow()
:m_pRoot(NULL),
m_pWarnBoxNode(NULL)
{
	m_WindowType = _TYPED_WINDOW_RECHARGEWARN_WINDOW_;
	m_bModelWindow = true;
}

RechargeWarnWindow::~RechargeWarnWindow()
{

}

bool RechargeWarnWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_RECHARGEWARNWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_, true);

	return IWindow::Init();
}

bool RechargeWarnWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();

		return true;
	}
	while (false);

	return false;
}

void RechargeWarnWindow::Tick()
{
	IWindow::Tick();
}

void RechargeWarnWindow::Destroy()
{
	if (m_pWarnBoxNode != NULL)
		m_pWarnBoxNode->removeAllChildrenWithCleanup(true);
	m_pWarnBoxNode = NULL;
	IWindow::Destroy();
}

void RechargeWarnWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_RECHARGEWARNWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}


void RechargeWarnWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void RechargeWarnWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void RechargeWarnWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pWarnBoxNode = CCNode::create();
	m_pWarnBoxNode->setAnchorPoint(CCPointZero);
	m_pWarnBoxNode->setPosition(CCPointZero);
	m_pRoot->addChild(m_pWarnBoxNode,10);
	_initControl();
	_mapBtn();
}


void RechargeWarnWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kRECHARGEWARNWINDOW,m_pWarnBoxNode);
}

void RechargeWarnWindow::_mapBtn()
{
	CCMenu *menu = (CCMenu*)m_pWarnBoxNode->getChildByTag(udCloseBtn);
	CMenuItemSprite* cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCloseBtn);
	cc->setTarget(this,menu_selector(RechargeWarnWindow::On_Click_ColseBtn));//关闭按钮

	menu = (CCMenu*)m_pWarnBoxNode->getChildByTag(udMENU1);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udMENU1);
	cc->setTarget(this,menu_selector(RechargeWarnWindow::On_Click_BtnClick));//关闭按钮

	menu = (CCMenu*)m_pWarnBoxNode->getChildByTag(udMENU2);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udMENU2);
	cc->setTarget(this,menu_selector(RechargeWarnWindow::On_Click_BtnClick));//关闭按钮

}

void RechargeWarnWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  = cc->getIDX();
	if (idx == udCloseBtn)
	{
		PushEvent(_TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_);
		return;
	}
	else if (idx == udMENU1)
	{
		PayGoodsData* pData = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[PAYGOODSCONTROLDATAHANDLER->m_CurVistorPayIndex];
		if (pData == NULL)
			return;
		
		IAPSYSTEM->BuyProductById(pData->goodsRegisterId_);
		PushEvent(_TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_);
		return;
	}
	else if (idx == udMENU2)
	{
		return;
#ifdef kENABLE_PLATFORM_APPSTORE
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ACCOUNTBINDWINDOW_);
#endif
		return;
	}
}

void RechargeWarnWindow::On_Click_ColseBtn(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_RECHARGEWARNWINDOW_);
}