// Name :CheckLeadershipWindow
// Function：查看统率力窗口
// Author : lvyunlong
// Date: 20131223

#include "../include/CheckLeadershipWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

CheckLeadershipWindow::CheckLeadershipWindow()
	:m_pRoot(NULL)
{
	m_WindowType = _TYPED_WINDOW_CHECKLEADERSHIPWINDOW_;
	m_bModelWindow = false;
}

CheckLeadershipWindow::~CheckLeadershipWindow()
{

}

bool CheckLeadershipWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_CHECKLEADERSHIPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_CHECKLEADERSHIPWINDOW_, true);

	return IWindow::Init();
}

bool CheckLeadershipWindow::Load()
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

void CheckLeadershipWindow::Tick()
{
	IWindow::Tick();
}

void CheckLeadershipWindow::Destroy()
{
	IWindow::Destroy();
}

void CheckLeadershipWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_CHECKLEADERSHIPWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_CHECKLEADERSHIPWINDOW_)
	{
		Destroy();
	}
}


void CheckLeadershipWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void CheckLeadershipWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCHECKLEADERSHIPWINDOW,m_pRoot);
	CPriorityLayerColor* pColor = (CPriorityLayerColor*)NFC_getNode(udPRIORITYLAYER,m_pRoot);
	pColor->setDelegate(this);
	_initValue(ROLEINFODATAHANDLER->m_pRIData);
	_mapBtn();
}

void CheckLeadershipWindow::_mapBtn()
{
	NFC_bindSelectorForBtn(udCLOSEBTN,m_pRoot,this,menu_selector(CheckLeadershipWindow::On_Close_Event));
}

void CheckLeadershipWindow::_initValue(RoleInfoData* data)
{
	//当前统率力
	char buff[64] = {0};
	std::string sys =SysLangDataManager::get_instance2()->GetSysLangById(5014);
	int leadership = data->honorLevel_;
	sprintf(buff,sys.c_str(),leadership);
	NFC_setLabelString(udCURLEADERVALUE,m_pRoot,buff);
	memset(buff,0,sizeof(buff));
	//出战英雄等级
	NFC_setLabelStringInt(udCURHEROLVVALUE,m_pRoot,CHECKROLEBASEINFOHANDLER->m_HeroLv);
	//基础HP
	NFC_setLabelStringInt(udBASEHPVALUE,m_pRoot,CheckRoleBaseInfoHandler::get_instance2()->m_BaseHP);
	//基础MP
	NFC_setLabelStringInt(udBASEMPVALUE,m_pRoot,CheckRoleBaseInfoHandler::get_instance2()->m_BaseMP);
	//基础攻击
	sprintf(buff,"%d-%d",CheckRoleBaseInfoHandler::get_instance2()->m_BaseMinAtk,CheckRoleBaseInfoHandler::get_instance2()->m_BaseMaxAtk);
	NFC_setLabelString(udBASEATTACKVALUE,m_pRoot,buff);
}

void CheckLeadershipWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHECKLEADERSHIPWINDOW_);
}

void CheckLeadershipWindow::On_Close_Event(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHECKLEADERSHIPWINDOW_);
}