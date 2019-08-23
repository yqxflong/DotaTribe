// Name ; NetObjectTipsWindow.h
// Function：由网络的物品tips窗口
// Author : fangjun
// Date: 20131014

#include "../include/NetObjectTipsWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"


using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

NetObjectTipsWindow::NetObjectTipsWindow()
:m_pRoot(NULL),
m_ShowTipsType(0)
{
	m_WindowType = _TYPED_WINDOW_NETOBJECTTIPSWINDOW_;
	m_bModelWindow = false;
}

NetObjectTipsWindow::~NetObjectTipsWindow()
{

}

bool NetObjectTipsWindow::Init()
{	RegisterEvent(_TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_NETOBJECTTIPSWINDOW_, true);

	return IWindow::Init();
}

bool NetObjectTipsWindow::Load()
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

void NetObjectTipsWindow::Tick()
{
	IWindow::Tick();
}

void NetObjectTipsWindow::Destroy()
{
	m_ShowTipsType = 0;
	IWindow::Destroy();
}

void NetObjectTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_NETOBJECTTIPSWINDOW_)
	{
		Destroy();
	}
}


void NetObjectTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if (paramList.size()>0)
	{
		std::list<std::string>::iterator it = paramList.begin();
		m_ShowTipsType = atoi((*it).c_str());
	}
}

void NetObjectTipsWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kOBJECTTIPS,m_pRoot);
	CPriorityLayerColor* pColor = (CPriorityLayerColor*)NFC_getNode(udPRIORITYLAYER,m_pRoot);
	pColor->setDelegate(this);
	_initValue(NETOBJECTTIPSDATAHANDLER->m_pObjectTips);
	_mapBtn();
}

void NetObjectTipsWindow::_mapBtn()
{
	NFC_bindSelectorForBtn(udSALEBTN,m_pRoot,this,menu_selector(NetObjectTipsWindow::On_Sale_Event));
}

void NetObjectTipsWindow::_initValue(NetObjectTips* data)
{
	NFC_setLabelString(udNAME,m_pRoot,data->name.c_str());
	char tmp[128];
	sprintf(tmp,"%d",data->level);
	NFC_setLabelString(udLVVALUE,m_pRoot,tmp);
	sprintf(tmp,"%d",data->price);
	std::string str = tmp;
	int i  = str.length();
	CCSprite* icon = (CCSprite*)NFC_getNode(udPRICEICON,m_pRoot);
	icon->setPositionX(icon->getPositionX()+i*10);
	NFC_setLabelString(udPRICEVALUE,m_pRoot,tmp);
	NFC_setLabelString(udSTATEMENT,m_pRoot,data->description.c_str());
	NFC_setNodeVisable(udSALEBTN,m_pRoot,data->isSalebtn_);
	NFC_setNodeVisable(udSALETTF,m_pRoot,data->isSalebtn_);	
}

void NetObjectTipsWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NETOBJECTTIPSWINDOW_);
}

void NetObjectTipsWindow::On_Sale_Event(cocos2d::CCObject * pSender)
{
	if (NETOBJECTTIPSDATAHANDLER->m_pObjectTips->isSalebtn_)
	{
		if (NETOBJECTTIPSDATAHANDLER->m_pObjectTips->pEquip_ != NULL)
		{
			BAGEQUIPDATAHANDLER->saleObject(NETOBJECTTIPSDATAHANDLER->m_pObjectTips->objectId, 1);
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->pEquip_ = NULL;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->isSalebtn_ = false;
			PushEvent(_TYPED_EVENT_HIDE_NETOBJECTTIPSWINDOW_);
		}
	}
}