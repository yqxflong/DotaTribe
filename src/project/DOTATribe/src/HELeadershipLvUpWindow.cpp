//Name：MessageBoxWindow
//Function：信息弹窗
//Written By：尹强

#include <cocos2d.h>
#include "../include/HELeadershipLvUpWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFAnimationController.h"
#include "../include/PopWindowManager.h"

using namespace std;
USING_NS_CC;

HELeadershipLvUpWindow::HELeadershipLvUpWindow()
{
	m_WindowType   = _TYPEF_WINDOW_LEADERSHIPLVUPWINDOW_;
	m_bModelWindow = true;
	m_pRootLayer=NULL;
}

bool HELeadershipLvUpWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LEADERSHIPLVUPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LEADERSHIPLVUPWINDOW_, true);

	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_LEADERSHIP_LVUP);
	return IWindow::Init();
}

void HELeadershipLvUpWindow::_initLayout(){
	m_pRootLayer=CCLayer::create();
	m_pRootLayer->setAnchorPoint(ccp(0.5,0.5));
	m_pRootLayer->setPosition(CCPointZero);
	m_pRootNode->addChild(m_pRootLayer);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLEADERSHIPLVUPWINDOW,m_pRootLayer);
	//transfer gray
	CCNode* gray=NFC_getNode(kGRAYLAYER,m_pRootLayer);
	gray->removeFromParentAndCleanup(false);
	m_pRootNode->addChild(gray);
}

void HELeadershipLvUpWindow::_mapBtn(){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN,m_pRootLayer);
	cc->setTarget(this,menu_selector(HELeadershipLvUpWindow::On_Click_Event));
}

void HELeadershipLvUpWindow::_setContent(){
	char tmp[512]="";
	string sys;
	//begin:hint
	int level=LeadershipHandler::get_instance2()->level_;
	sys=SysLangDataManager::get_instance2()->GetSysLangById(745);
	sprintf(tmp,sys.c_str(),level);
	NFC_setLabelString(kHINT,m_pRootLayer,tmp);
	memset(tmp,0,sizeof(tmp));
	//end

	//begin:herolv
	int oldherolv = LeadershipHandler::get_instance2()->oldherolv_;
	int newherolv = LeadershipHandler::get_instance2()->newherolv_;

	NFC_setLabelStringInt(kHEROLV_BASE,m_pRootLayer,oldherolv);

	NFC_setLabelStringInt(kHEROLV_NEW,m_pRootLayer,newherolv);

	//end

	//begin:hp
	int oldhp=LeadershipHandler::get_instance2()->oldhp_;
	int addhp=LeadershipHandler::get_instance2()->addhp_;
	
	NFC_setLabelStringInt(kIMPROVE1_BASE,m_pRootLayer,oldhp);

	NFC_setLabelStringInt(kIMPROVE1_NEW,m_pRootLayer,oldhp+addhp);
	//end
	//begin:mp
	int oldmp=LeadershipHandler::get_instance2()->oldmp_;
	int addmp=LeadershipHandler::get_instance2()->addmp_;
	
	NFC_setLabelStringInt(kIMPROVE2_BASE,m_pRootLayer,oldmp);

	NFC_setLabelStringInt(kIMPROVE2_NEW,m_pRootLayer,oldmp+addmp);
	//end
	//begin:min att
	int oldmin=LeadershipHandler::get_instance2()->oldminattack_;
	int addmin=LeadershipHandler::get_instance2()->addminattack_;

	int oldmax=LeadershipHandler::get_instance2()->oldmaxattack_;
	int addmax=LeadershipHandler::get_instance2()->addmaxattack_;

	sprintf(tmp,"%d-%d",oldmin,oldmax);
	NFC_setLabelString(kIMPROVE3_BASE,m_pRootLayer,tmp);
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%d-%d",oldmin+addmin,oldmax+addmax);
	NFC_setLabelString(kIMPROVE3_NEW,m_pRootLayer,tmp);
	//end
}

bool HELeadershipLvUpWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();
		_mapBtn();
		_setContent();
		return true;
	} 
	while (false);

	return false;
}

void HELeadershipLvUpWindow::Tick()
{
	IWindow::Tick();
}

void HELeadershipLvUpWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	IWindow::Destroy();
}

//需要子类继承并重写
void HELeadershipLvUpWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
void HELeadershipLvUpWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void HELeadershipLvUpWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LEADERSHIPLVUPWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LEADERSHIPLVUPWINDOW_)
	{
		Destroy();
	}
}

	/*
		展示自己的窗口
	*/
void HELeadershipLvUpWindow::ShowWindow(){
	Show(true);
	NFC_Action_fallDown(m_pRootLayer);
}

void HELeadershipLvUpWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void HELeadershipLvUpWindow::On_Click_Event(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_LEADERSHIPLVUPWINDOW_);
}