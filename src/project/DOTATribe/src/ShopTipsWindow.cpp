// Name : ShopTipsWindow
// Function：商店物品tips窗口
// Author : lvyunlong
// Date: 20140214

#include "../include/ShopTipsWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"


using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

ShopTipsWindow::ShopTipsWindow()
{
	m_WindowType = _TYPED_WINDOW_SHOPTIPSWINDOW_;
	m_bModelWindow = false;
}

ShopTipsWindow::~ShopTipsWindow()
{

}

bool ShopTipsWindow::Init()
{	
	RegisterEvent(_TYPED_EVENT_SHOW_SHOPTIPSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SHOPTIPSWINDOW_, true);

	return IWindow::Init();
}

bool ShopTipsWindow::Load()
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

void ShopTipsWindow::Tick()
{
	IWindow::Tick();
}

void ShopTipsWindow::Destroy()
{
	if (m_pRootNode)
	{
		m_pRootNode->removeAllChildrenWithCleanup(true);
	}
	IWindow::Destroy();
}

void ShopTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_SHOPTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_SHOPTIPSWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}


void ShopTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void ShopTipsWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void ShopTipsWindow::_initLayout()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPTIPS,m_pRootNode);
	CPriorityLayerColor* pColor = (CPriorityLayerColor*)NFC_getNode(udPRIORITYLAYER,m_pRootNode);
	pColor->setDelegate(this);
	_initValue(SHOPTIPSDATAHANDLER->m_pTips);
}

void ShopTipsWindow::_initValue(ShopTipsData* data)
{
	NFC_setLabelString(udNAME,m_pRootNode,data->name_.c_str());
	char tmp[128];
	sprintf(tmp,"%d",data->price_);
	std::string str = tmp;
	int i  = str.length();
	CCSprite* icon = (CCSprite*)NFC_getNode(udPRICEICON,m_pRootNode);
	icon->setPositionX(icon->getPositionX()+i*10);
	_setMoneyType(data->moneytype_);
	NFC_setLabelString(udPRICEVALUE,m_pRootNode,tmp);
	NFC_setLabelString(udSTATEMENT,m_pRootNode,data->description_.c_str());
}

void ShopTipsWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SHOPTIPSWINDOW_);
}

void ShopTipsWindow::_setMoneyType(int itype)
{
	cocos2d::CCTexture2D* pTexture = NULL;
	if (itype == _TYPE_GOLD_)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_ICONGOLD_TIPS);
	}
	else if (itype == _TYPE_JEWEL_)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_ICONDIAMOND_TIPS);
	}
	else if (itype == _TYPE_PRESTIGE_)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_ICONPRESTIGE_TIPS);
	}
	else if (itype == _TYPE_EXCHANGE_ITEM_)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_ICONLONGXUE_TIPS);
	}
	CCSprite* icon = (CCSprite*)NFC_getNode(udPRICEICON,m_pRootNode);
	icon->setTexture(pTexture);
}