//Name：系统设置界面
//Function：系统设置
//Written By：吕云龙


#include "../include/SystemsetWindow.h"
#include "../include/DotaGameConfig.h"
#include "../include/UIViewDataManger.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/SoundSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/CMenuItemSprite.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/TimeSystem.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


SystemsetWindow::SystemsetWindow()
:m_SystemNode(0)
,m_nSVZorder(10)
,m_isBguest(false)
{
	m_WindowType   = _TYPED_WINDOW_SYSTEMSETWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

SystemsetWindow::~SystemsetWindow()
{
	m_SystemNode = NULL;
}

bool SystemsetWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SYSTEMSETWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SYSTEMSETWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SYSTEMSETWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_SYSTEMSETWINDOW_, true);

	return IWindow::Init();
}

bool SystemsetWindow::Load()
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

void SystemsetWindow::Tick()
{
	IWindow::Tick();
}

void SystemsetWindow::Destroy()
{
	m_isBguest = false;
	m_SystemNode->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void SystemsetWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_SYSTEMSETWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SYSTEMSETWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_SYSTEMSETWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_FADEOUT_SYSTEMSETWINDOW_)
	{
		OnFadeoutWindowEventHandler(paramList);
	}
}

void SystemsetWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);	
}

void SystemsetWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	Destroy();
}

void SystemsetWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList){
	
}

void SystemsetWindow::OnFadeoutWindowEventHandler(std::list<std::string>& paramList){

}

void SystemsetWindow::_initLayout()
{
	CCNode* node =m_pRootNode;
	node->setPosition(CCPointZero);
	node->setAnchorPoint(CCPointZero);

	m_SystemNode = CCNode::create();
	m_SystemNode->setPosition(CCPointZero);
	m_SystemNode->setAnchorPoint(CCPointZero);
	node->addChild(m_SystemNode,10);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSYSTEMSETWINDOW,m_SystemNode);
	//创建按钮控件
	_mapBtns();
	//设置文字
	_setText();
}
void SystemsetWindow::_mapBtns()
{
	bool bBackgroundMusic = IsBackgroundMusic();
	bool bEffectSount = IsEffectSound();

	CCMenu* menu = (CCMenu*)m_SystemNode->getChildByTag(syCloseBtn);
	CMenuItemSprite*cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(syCloseBtn);
	cc->setTarget(this,menu_selector(SystemsetWindow::On_Click_Event));

	menu=(CCMenu*)m_SystemNode->getChildByTag(syUSERCENTERBtn);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(syUSERCENTERBtn);
	cc->setTarget(this,menu_selector(SystemsetWindow::On_Click_User_Event));

	menu=(CCMenu*)m_SystemNode->getChildByTag(syLogouBtn);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(syLogouBtn);
	cc->setTarget(this,menu_selector(SystemsetWindow::On_Click_LoginBack_Event));


	//音乐按钮
	menu = (CCMenu*)m_SystemNode->getChildByTag(syYinyueBtn);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(syYinyueBtn);
	cc->setTarget(this,menu_selector(SystemsetWindow::On_Click_Event));
	cc->setIsSelected(bBackgroundMusic);
	if (bBackgroundMusic)
		cc->selected(true);
	else
		cc->unselected();
	//音效按钮
	menu = (CCMenu*)m_SystemNode->getChildByTag(syYinxiaoBtn);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(syYinxiaoBtn);
	cc->setTarget(this,menu_selector(SystemsetWindow::On_Click_Event));
	cc->setIsSelected(bEffectSount);
	if (bEffectSount)
		cc->selected(true);
	else
		cc->unselected();
}

void SystemsetWindow::_setText()
{
	CCLabelTTF* ttf = (CCLabelTTF*)m_SystemNode->getChildByTag(syCurrPlayerNameTTF);
	ttf->setString(ROLEINFODATAHANDLER->m_pRIData->name_.c_str());

	ttf = (CCLabelTTF*)m_SystemNode->getChildByTag(syCurrServerNameTTF);
	ttf->setString(SERVERINFODATAINFO->getCurServerName());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	NFC_setLabelString(syUSERCENTERLB, m_SystemNode, SysLangDataManager::get_instance2()->GetSysLangById(2082));
#endif
}


void SystemsetWindow::On_Click_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite*cc =(CMenuItemSprite*)pSender;
	int index = cc->getIDX();

	if (index == syCloseBtn)
	{
		PushEvent(_TYPED_EVENT_HIDE_SYSTEMSETWINDOW_);
	}
	else if (index == syYinyueBtn)
	{
		bool belse = cc->getIsSeleted();
		belse = !belse;
		cc->setIsSelected(belse);
		if (belse)
			cc->selected(true);
		else
			cc->unselected();

		SOUNDSYSTEM->MuteBackgroundMusic(belse);
	}
	else if (index == syYinxiaoBtn)
	{
		bool belse = cc->getIsSeleted();
		belse = !belse;
		cc->setIsSelected(belse);
		if (belse)
			cc->selected(true);
		else
			cc->unselected();

		SOUNDSYSTEM->MuteEffectSound(belse);
	}
}

//用户账户管理事件
void SystemsetWindow::On_Click_User_Event(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("Window_SYSTEMBTN",_COMMON_BTN_CLICK_INTERVAL_);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SERVERINFODATAINFO->LogoutSdk();
#else
	LOGGERSYSTEM->LogInfo("SyssetGuestView ：syUSERCENTERBtn");
	SERVERINFODATAINFO->ShowSdkCenter();
#endif

#ifdef	kENABLE_PLATFORM_PC
	SERVERINFODATAINFO->LogoutAccountInfo();
#endif
}
//返回登录事件
void SystemsetWindow::On_Click_LoginBack_Event(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("Window_SYSTEMBTN",_COMMON_BTN_CLICK_INTERVAL_);
	LOGGERSYSTEM->LogInfo("SyssetGuestView ：LogouBtn");
	SERVERINFODATAINFO->LogoutGame();
}

bool SystemsetWindow::IsBackgroundMusic()
{
	return SOUNDSYSTEM->IsBackgroundMusicMute();
}

bool SystemsetWindow::IsEffectSound()
{
	return SOUNDSYSTEM->IsEffectSoundMute();
}