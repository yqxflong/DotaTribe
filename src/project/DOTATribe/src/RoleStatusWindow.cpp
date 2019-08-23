//Name：RoleStatusWindow
//Function：人物状态层
//Written By：尹强

#include "../include/RoleStatusWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"
#include "../include/WindowManager.h"
#include "../include/GuideSystem.h"
#include <list>
#include <string>
#include "../include/MainTaskDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/PESWindow.h"
#include "../include/CSimpleActionSprite.h"
#include "../include/NewEquipremindDataHandler.h"

using namespace std;

RoleStatusWindow::RoleStatusWindow()
:m_pRoleStatusBar(0)
,Current_WindowType_(0)
,m_nShowCounter(0){
	m_WindowType   = _TYPED_WINDOW_ROLESTATUS_;
}

bool RoleStatusWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ROLESTATUSWINDOW_, true);
	

	return IWindow::Init();
}

bool RoleStatusWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		_mapRoleStatus();
		_mapMainTask();

		_registerEvent();
		return true;
	} 
	while (false);

	return false;
}

void RoleStatusWindow::Tick()
{
	if (m_pRoleStatusBar)
		m_pRoleStatusBar->Tick();

	IWindow::Tick();
}

void RoleStatusWindow::Destroy()
{
	m_nShowCounter--;
	if (m_nShowCounter<=0)
	{
		_unregisterEvent();
		Current_WindowType_=0;
		m_pRoleStatusBar->removeFromParent();
		m_pRoleStatusBar=NULL;

		IWindow::Destroy();
	}
}

	/*
		刷新界面
	*/
void RoleStatusWindow::RefreshUI(){
	//人物状态条刷新
	if (m_pRoleStatusBar)
		m_pRoleStatusBar->Refresh();

    UpdateRoleState();
	//更新任务提示
	UpdateMainTaskHint();
}

void RoleStatusWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_ROLESTATUSWINDOW_)
	{
		UpdateRoleState();
		UpdateMainTaskHint();
		OnShowWindowEventHandler(paramList);
		m_nShowCounter++;
	}
	else if (iEventType == _TYPED_EVENT_HIDE_ROLESTATUSWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_ROLESTATUSWINDOW_)
	{
		UpdateRoleState();
		UpdateMainTaskHint();
	}
}

void RoleStatusWindow::Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	IWindow* window=WINDOWMANAGER->GetWindowByType(_TYPED_WINDOW_ROLESTATUS_);
	RoleStatusWindow* theWindow=dynamic_cast<RoleStatusWindow*>(window);
	assert(theWindow!=NULL);
	theWindow->RefreshUI();
}

void RoleStatusWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	assert(paramList.size()>0);//必须传当前窗口枚举
	string param1=*it++;
	Current_WindowType_=atoi(param1.c_str());
}

void RoleStatusWindow::_registerEvent(){
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_REFRESH_UPDATEUI_,Event_RefreshUI_Handler);
}

void RoleStatusWindow::_unregisterEvent(){
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_REFRESH_UPDATEUI_,Event_RefreshUI_Handler);
}

void RoleStatusWindow::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kROLESTATUSWINDOW,m_pRootNode);

}

void RoleStatusWindow::_mapRoleStatus(){
	CCNode* node=NFC_getNode(kROLESTATUSBAR,m_pRootNode);
	m_pRoleStatusBar=DTRoleStatusBar::create();
	m_pRoleStatusBar->setTag(kREAL_ROLESTATUSBAR);
	m_pRoleStatusBar->ResetPropertyByNode(node);
	m_pRoleStatusBar->setDelegate(this);
	m_pRootNode->addChild(m_pRoleStatusBar);
}

void RoleStatusWindow::_mapMainTask(){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kMainTask,m_pRootNode);
	cc->setIDX(kMainTask);
	cc->setTarget(this,menu_selector(RoleStatusWindow::MainTaskClickEvent));
}

	/*.
		DTRoleStatusBar CallBack
	*/
void RoleStatusWindow::AvatarClickEvent(){
	int backwindow=0;
	NEWEQUIPREMINDDATAHANDLER->HideClearData();
	if (Current_WindowType_==_TYPED_WINDOW_HOME_)
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_HOMEWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_CLIMBWINDOW_){
		PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_TEAMBATTLEWINDOW_){
		PushEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_SELECTSONMISSION_){
		PushEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
		//功能开启下一步
		GUIDESYSTEM->Next();
	}else if(Current_WindowType_==_TYPED_WINDOW_ARENAWINDOW_){
		PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
		backwindow=_TYPEF_EVENT_SHOW_ARENAWINDOW_;
	}
	else if(Current_WindowType_ == _TYPED_WINDOW_MINEAREA_WINDOW_)
	{
		PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		backwindow = _TYPED_EVENT_SHOW_MINEAREAWINDOW_;
	}
	else if(Current_WindowType_ == _TYPED_WINDOW_BOSSSCORE_)
	{
		PushEvent(_TYPED_EVENT_HIDE_BOSSSCOREWINDOW_);
		backwindow = _TYPED_EVENT_SHOW_BOSSSCOREWINDOW_;
	}
	ROLEINFODATAHANDLER->m_pRIData->bHadNewHeroTips=false;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_, _to_event_param_(backwindow));
}

void RoleStatusWindow::SkillClickEvent(){
	int backwindow=0;
	if (Current_WindowType_==_TYPED_WINDOW_HOME_){
		PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_); 
		backwindow=_TYPED_EVENT_SHOW_HOMEWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_CLIMBWINDOW_){
		PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_); 
		backwindow=_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_TEAMBATTLEWINDOW_){
		PushEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_SELECTSONMISSION_){
		PushEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_);
		backwindow=_TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
	}else if(Current_WindowType_==_TYPED_WINDOW_ARENAWINDOW_){
		PushEvent(_TYPEF_EVENT_HIDE_ARENAWINDOW_);
		backwindow=_TYPEF_EVENT_SHOW_ARENAWINDOW_;
	}
	else if(Current_WindowType_ == _TYPED_WINDOW_MINEAREA_WINDOW_)
	{
		PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		backwindow = _TYPED_EVENT_SHOW_MINEAREAWINDOW_;
	}
	else if(Current_WindowType_ == _TYPED_WINDOW_BOSSSCORE_)
	{
		PushEvent(_TYPED_EVENT_HIDE_BOSSSCOREWINDOW_);
		backwindow = _TYPED_EVENT_SHOW_BOSSSCOREWINDOW_;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,_to_event_param_(backwindow));
}

void RoleStatusWindow::AddTLClickEvent(){
	ROLEINFODATAHANDLER->AddTL_Request();
}

/*
任务系统入口
*/
void RoleStatusWindow::MainTaskClickEvent(cocos2d::CCObject* pSender){ 
	//cocos2d::CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	MAINTASKDATAHANDLER->ToServerEnterMainTask();
	MainTaskDataHandler::get_instance2()->m_bHadNewTask=false;
	UpdateMainTaskHint();
	//==========新手引导===========
	GUIDESYSTEM->Next();
}

void RoleStatusWindow::UpdateMainTaskHint()
{
	if(MainTaskDataHandler::get_instance2()->m_bHadNewTask)
	{  
		NFC_setActionSpriteEnable(kNewTaskNode,m_pRootNode,true); 
	}
	else
	{ 
		NFC_setActionSpriteEnable(kNewTaskNode,m_pRootNode,false);
	}

	if(ROLEINFODATAHANDLER->m_pRIData->finishTaskCounts_ > 0)
	{
		NFC_showNode(kMAINTASKEFFECT, m_pRootNode, true);
	}
	else
	{
		NFC_showNode(kMAINTASKEFFECT, m_pRootNode, false);
	}
}


void RoleStatusWindow::UpdateRoleState()
{ 
	if(ROLEINFODATAHANDLER->m_pRIData->bHadNewHeroTips)
	{
		NFC_setActionSpriteEnable(kNewHeroNode,m_pRootNode,true); 
	}
	else
	{
		NFC_setActionSpriteEnable(kNewHeroNode,m_pRootNode,false); 
	} 
} 