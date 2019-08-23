// Name : RechargeWindow.h
// Function:充值窗口
// Author : lvyunlong
// Date: 20131118

#include "../include/RechargeWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/IAPSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/WindowManager.h"
#include "../include/VipControlDataHandler.h"
#include "../include/ActivityDataHandler.h"
#include "../include/ActivityPacket.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

RechargeWindow::RechargeWindow()
:m_pRoot(NULL),
m_pRechargeNode(NULL)
{
	m_WindowType = _TYPED_WINDOW_RECHARGE_WINDOW_;
	m_bModelWindow = true;
	m_bIsPayTick = false;
	m_PayTickCount = 0;
	m_PayGoodsIndex = 0;
}

RechargeWindow::~RechargeWindow()
{

}

bool RechargeWindow::Init()
{	
	RegisterEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_RECHARGEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_RECHARGEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ADDTIONPAYWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_VIPTEXT_RECHARGEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_DOUBLE_RECHARGEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);

	return IWindow::Init();
}

bool RechargeWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		VIPCONTROLDATAHANDLER->ToServerVIPInfo();
		if (PAYGOODSCONTROLDATAHANDLER->m_isBPaylist)
			PushEvent(_TYPED_EVENT_UPDATE_RECHARGEWINDOW_);
		else
			PAYGOODSCONTROLDATAHANDLER->ToServerRechargeListPacket(SERVERINFODATAINFO->Get_Channel_ID());

		PAYGOODSCONTROLDATAHANDLER->ToServerDoublePayInfo();
		return true;
	}
	while (false);

	return false;
}

void RechargeWindow::Tick()
{
	IWindow::Tick();

	if (m_bIsPayTick)
	{
		m_PayTickCount++;
		if (m_PayTickCount>10) //防止购买窗口没弹出来逻辑帧已经走到这了
		{
			m_PayTickCount = 0;
			PAYGOODSCONTROLDATAHANDLER->m_isBIAPTick = true;
			PAYGOODSCONTROLDATAHANDLER->m_IAPTickCount = 0;
			m_bIsPayTick = false;
		}
	}
}

void RechargeWindow::Destroy()
{
	m_bIsPayTick = false;
	m_PayTickCount = 0;
	m_PayGoodsIndex = 0;
	if (m_pRechargeNode != NULL)
		m_pRechargeNode->removeAllChildrenWithCleanup(true);
	m_pRechargeNode = NULL;
	IWindow::Destroy();
}

void RechargeWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_RECHARGEWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_RECHARGEWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_RECHARGEWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_ADDTIONPAYWINDOW_)
	{
		//android下才有的事件
		PayGoodsData* pData = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[m_PayGoodsIndex];
		if (pData!=NULL)
		{
			//调用sdk支付
			IAPSYSTEM->SdkBuyProductById(pData->goodsRegisterId_);
		}
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_VIPTEXT_RECHARGEWINDOW_)
	{
		_setTextVip();
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		refreshDiamondUIData();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_DOUBLE_RECHARGEWINDOW_)
	{
		_setDoubleView();
	}
}


void RechargeWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void RechargeWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	//Fadeout(IWINDOW_FADEOUT_DURING);
	Destroy();
}

void RechargeWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	_setTextName();
	_setTextNum();
	_setTextPrice();
	//_setTextVip();
}

void RechargeWindow::_setTextName()
{
	int index = 0;
	int size = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList.size();
	for (index;index<size;index++)
	{
		NFC_setLabelString(index+udTTFNAME1,m_pRechargeNode,PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[index]->goodsName_);
	}
	
}
void RechargeWindow::_setTextNum()
{
	int index = 0;
	int size = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList.size();
	for (index;index<size;index++)
	{
		NFC_setLabelStringInt(index+udTTFNUM1,m_pRechargeNode,PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[index]->goodNumber_);
	}	
}
void RechargeWindow::_setTextPrice()
{
	int index = 0;
	int size = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList.size();
	for (index;index<size;index++)
	{
		float flo = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[index]->goodsPrice_;
		char buffer[64] = {0};
		sprintf(buffer,"%s%.2f",SysLangDataManager::get_instance2()->GetSysLangById(6022).c_str(),flo);
		CCLabelTTF*	ttf = (CCLabelTTF*)NFC_getNode(index+udTTFPRICE1,m_pRechargeNode);
		ttf->setString(buffer);
	}
}

void RechargeWindow::_setTextVip()
{
	if (ROLEINFODATAHANDLER->m_pRIData->vipLevel_ == 10)
	{
		NFC_setNodeVisable(udRECHARGETOVIPTEXT,m_pRechargeNode,false);
	}
	else
	{
		char buff[64]={0};
		int surplusexp = VIPCONTROLDATAHANDLER->m_maxExp - VIPCONTROLDATAHANDLER->m_exp;
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(912).c_str(),surplusexp,ROLEINFODATAHANDLER->m_pRIData->vipLevel_+1);
		NFC_setLabelString(udRECHARGETOVIPTEXT,m_pRechargeNode,buff);
	}
}

void RechargeWindow::_setFirstRech(int sum)
{
	bool isfirst = false;
	if (sum>0)
		isfirst = false;
	else
		isfirst = true;
	NFC_showNode(udFIRSTRECHEFFECT,m_pRechargeNode,isfirst);
	//NFC_showNode(udFIRSTRECHTEXT,m_pRechargeNode,isfirst);
	NFC_showNode(udFIRSTBTN,m_pRechargeNode,isfirst);
}

void RechargeWindow::_setDoubleView()
{
	for (int i=0;i<3;i++)
	{
		if (PAYGOODSCONTROLDATAHANDLER->m_ShowDoubleArray[i] == 0)
		{
			NFC_setNodeVisable(udTUIJIAN1+i*2,m_pRechargeNode,false);
			NFC_setNodeVisable(udDESCRIBE1+i*2,m_pRechargeNode,false);
		}
		else
		{
			NFC_setNodeVisable(udTUIJIAN1+i*2,m_pRechargeNode,true);
			NFC_setNodeVisable(udDESCRIBE1+i*2,m_pRechargeNode,true);
		}
	}
}

void RechargeWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pRechargeNode = CCNode::create();
	m_pRechargeNode->setAnchorPoint(CCPointZero);
	m_pRechargeNode->setPosition(CCPointZero);
	m_pRoot->addChild(m_pRechargeNode,10);
	_initControl();
	if(ROLEINFODATAHANDLER->m_pRIData->vipreward_)
		NFC_showNode(udVIPEFFECT,m_pRechargeNode,true);
	else
		NFC_showNode(udVIPEFFECT,m_pRechargeNode,false);
	_mapBtn();
	refreshDiamondUIData();
	_setFirstRech(ROLEINFODATAHANDLER->m_pRIData->accumuRechNum);
}


void RechargeWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kRECHARGEWINDOW,m_pRechargeNode);
}

void RechargeWindow::_mapBtn()
{
	CCMenu *menu = (CCMenu*)m_pRechargeNode->getChildByTag(udCloseBtn);
	CMenuItemSprite* cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCloseBtn);
	cc->setTarget(this,menu_selector(RechargeWindow::On_Click_ColseBtn));//关闭按钮

	for (int i =udMENU1;i<=udMENU6;i++)
	{
		menu = (CCMenu*)m_pRechargeNode->getChildByTag(i);
		cc = (CMenuItemSprite*)menu->getChildByTag(0);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(RechargeWindow::On_Click_BtnClick));//物品按钮6
	}

	menu = (CCMenu*)m_pRechargeNode->getChildByTag(udVIPBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udVIPBTN);
	cc->setTarget(this,menu_selector(RechargeWindow::On_Click_BtnClick));//去VIP按钮

	menu = (CCMenu*)m_pRechargeNode->getChildByTag(udFIRSTBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udFIRSTBTN);
	cc->setTarget(this,menu_selector(RechargeWindow::On_Click_FirstRechBtn));//首充按钮
	
}


void RechargeWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  = cc->getIDX();
	int index = 0;
	m_bIsPayTick = true;
	BTN_INTERVAL("PayGoodsBtn",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	if (idx == udMENU1)
	{
		m_PayGoodsIndex = 0;
	}
	else if (idx == udMENU2)
	{
		m_PayGoodsIndex = 1;
	}
	else if (idx == udMENU3)
	{
		m_PayGoodsIndex = 2;
	}
	else if (idx == udMENU4)
	{
		m_PayGoodsIndex = 3;
	}
	else if (idx == udMENU5)
	{
		m_PayGoodsIndex = 4;
	}
	else if (idx == udMENU6)
	{
		m_PayGoodsIndex = 5;
	}
	else if (idx == udVIPBTN)
	{
		PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
		PushEvent(_TYPED_EVENT_SHOW_VIPWINDOW_);
		PushEvent(_TYPED_EVENT_HIDE_RECHARGEWINDOW_);
		return;
	}
	PayGoodsData* pData = PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList[m_PayGoodsIndex];
	if (pData == NULL)
		return;

//WARNING:有问题,kENABLE_PLATFORM_SDKIOS  与  kENABLE_PLATFORM_APPSTORE并存
//建议去掉 kENABLE_PLATFORM_APPSTORE
#ifdef kENABLE_PLATFORM_SDKIOS		//ios Sdk
	IAPSYSTEM->SdkBuyProductById(pData->goodsRegisterId_);
#endif

#ifdef kENABLE_PLATFORM_SDKANDROID	//安卓sdk
	PAYGOODSCONTROLDATAHANDLER->ToServerAdditionPayInfo();
#endif
}

void RechargeWindow::On_Click_FirstRechBtn(cocos2d::CCObject* pSender)
{
	//首充跳转礼包
	FIRSTRECHDATAHANDLER->m_isRechGift = true;
	PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
	NFC_showCommunicationWating(true);
	PushEvent(_TYPED_EVENT_HIDE_RECHARGEWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_);
	C2SActivityPacket packet;
	packet.Send();

}

void RechargeWindow::On_Click_ColseBtn(cocos2d::CCObject* pSender)
{
	PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
	PushEvent(_TYPED_EVENT_HIDE_RECHARGEWINDOW_);
	if (DOTATribeApp::get_instance2()->IsHomeProcedureAsActiveProcedure())
	{
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else
	{
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
	}
}

void RechargeWindow::refreshDiamondUIData()
{
	//刷新钻石接口先占时留着
	_setFirstRech(ROLEINFODATAHANDLER->m_pRIData->accumuRechNum);
	VIPCONTROLDATAHANDLER->ToServerVIPInfo();
}