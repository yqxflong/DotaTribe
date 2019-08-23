#include "../include/IWindow.h"
#include "../include/UISystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EngineSystem.h"
#include "../include/SoundSystem.h"
#include "../include/UIWindowDataManager.h"
#include "../include/WindowManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/TimeSystem.h"
#include "../include/config_SoundSystem.h"
#include <cocos2d.h>
#include <string>

IWindow::IWindow()
{
	m_WindowType   = _TYPED_WINDOW_UNKOWN_;
	m_WindowName   = "";
	m_bModelWindow = false;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
	m_bLoaded      = false;
	m_bShow        = false;
	m_pRootNode    = NULL;
	m_bTickListener= true;
	m_TickCounter  = 0;
	m_bIsForceClearUnUseTex=true;
	m_bIsForceClearAnimation=true;
	m_ParentWindowName = "root";
}

IWindow::~IWindow()
{

}

int IWindow::GetWindowType()
{
	return m_WindowType;
}

bool IWindow::IsLoad()
{	
	return m_bLoaded;
}

cocos2d::CCNode* IWindow::GetRootNode()
{
	return m_pRootNode;
}

void IWindow::SetWindowDataByPos(std::string str, unsigned int pos)
{
	m_WindowDataList[pos] = str;
}

std::string IWindow::GetWindowDataByPos(unsigned int pos)
{
	return m_WindowDataList[pos];
}

void IWindow::SetTickListenser(bool bListenser)
{
	m_bTickListener = bListenser;
}

void IWindow::Show(bool bShow)
{

	if (m_bShow == bShow)
		return ;

	m_bShow = bShow;
	if (m_pRootNode == NULL)
		return ;

	if (bShow)
	{
		m_pRootNode->setVisible(true);
		PlayOpenSound();
	}
	else
	{
		m_pRootNode->setVisible(false);
		PlayCloseSound();
	}
}

bool IWindow::IsVisible()
{
	return m_bShow;
}

void IWindow::SetXPosition(float xPos)
{
	if (m_pRootNode == NULL)
		return ;

	m_pRootNode->setPositionX(xPos);
}

float IWindow::GetXPosition()
{
	if (m_pRootNode == NULL)
		return 0.0f;

	return m_pRootNode->getPositionX();
}

void IWindow::SetYPosition(float yPos)
{
	if (m_pRootNode == NULL)
		return ;

	m_pRootNode->setPositionY(yPos);
}

float IWindow::GetYPosition()
{
	if (m_pRootNode == NULL)
		return 0.0f;

	return m_pRootNode->getPositionY();
}

void IWindow::SetXScale(float xScale)
{
	if (m_pRootNode == NULL)
		return ;

	m_pRootNode->setScaleX(xScale);
}

void IWindow::SetYScale(float yScale)
{
	if (m_pRootNode == NULL)
		return ;

	m_pRootNode->setScaleY(yScale);
}

void IWindow::RegisterEvent(int iEventType, bool bNotifyOnlyWhenVisible)
{
	if (!bNotifyOnlyWhenVisible)
		UISYSTEM->RegisterUIEvent(iEventType, m_WindowType);
	else
		UISYSTEM->RegisterUIEvent2(iEventType, m_WindowType);
}

void IWindow::PushEvent(int iEventType)
{
	UISYSTEM->PushEvent(iEventType);
}

void IWindow::PushEvent(int iEventType, char* pArgs)
{
	assert(pArgs != NULL);

	UISYSTEM->PushEvent(iEventType, std::string(pArgs));
}

void IWindow::PlayOpenSound()
{
	UIWindowItemData* pItem = UIWindowDataManager::get_instance2()->GetWindowByType(m_WindowType);
	if (pItem==NULL || pItem->mSoundOpen == -1)
		return ;

	if (m_WindowType != _TYPED_WINDOW_ATHLETICSRESULT_)
	{
		char _soundID[64]="";
		sprintf(_soundID,"%d",pItem->mSoundOpen);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
	}
}

void IWindow::PlayCloseSound()
{
	UIWindowItemData* pItem = UIWindowDataManager::get_instance2()->GetWindowByType(m_WindowType);
	if (pItem==NULL || pItem->mSoundClose == -1)
		return ;

	if (m_WindowType != _TYPED_WINDOW_ATHLETICSRESULT_)
	{
		char _soundID[64]="";
		sprintf(_soundID,"%d",pItem->mSoundClose);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
	}
}
void IWindow::RegisterTimerFunction(float time, std::string functionName)
{
	_SCRIPT_TIMER_FUNCTION_ func;
	func.mStartTime     = m_TickCounter;
	func.mIntervalTime  = int(time*DOTATribeApp::get_instance2()->GetFPS());
	func.mScriptFunction= functionName;
}

bool IWindow::Init()
{
	UIWindowItemData* pWindowItem = UIWindowDataManager::get_instance2()->GetWindowByType(this->GetWindowType());
	m_bModelWindow = pWindowItem->mIsModelWindow;
	m_WindowZOrder = pWindowItem->mWindowZOrder;
	m_WindowName   = pWindowItem->mWindowName;

	LOGGERSYSTEM->LogInfo("Init UI Window, WindowType=%d, WindowName=%s\n", m_WindowType, m_WindowName.c_str());
	return true;
}

bool IWindow::Load()
{
	do 
	{
		//这一帧取消所有按钮事件==CPriorityMenu
		//下一帧恢复
		UISYSTEM->Set_Global_menuitem_enabled(false);
		//创建根节点
		m_pRootNode=CCNode::create();
		m_pRootNode->setPosition(CCPointZero);
		UISYSTEM->GetUILayer()->addChild(m_pRootNode, m_WindowZOrder);
		m_pRootNode->setVisible(false);
		// 注册消息处理事件
		if (m_bModelWindow)
		{
			cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_pRootNode->getPriority(), true);
		}

		//加载资源Plist
		LoadPlistForWindow();

		m_bLoaded = true;
	} 
	while (false);

	LOGGERSYSTEM->LogInfo("Load UI Window, WindowType=%d, WindowName=%s\n", m_WindowType, m_WindowName.c_str());
	return true;
}

void IWindow::Tick()
{
	m_TickCounter++;
}

void IWindow::Destroy()
{
	do 
	{
		PlayCloseSound();
		// 删除所有该窗口绑定的c++定时回调函数
		m_bRunning = false;
		unscheduleAllSelectors();
		// 卸载消息处理事件
		if (m_bModelWindow)
		{
			cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		}
		// 从父节点删除当前窗口
		if (m_pRootNode != NULL)
		{
			m_pRootNode->removeAllChildrenWithCleanup(true);
			UISYSTEM->GetUILayer()->removeChild(m_pRootNode, true);
			m_pRootNode = NULL;
		}

		m_bShow   = false;
		m_bLoaded = false;
	}
	while (false);

	//清除资源plist
	UnloadPlistForWindow();

	if(m_bIsForceClearAnimation)
	{
		DOTATribeApp::get_instance2()->ForceClearAnimationCache();
	}
	
	UISystem::get_instance2()->Set_Global_UIClear_Enable(true);

	LOGGERSYSTEM->LogInfo("UnLoad UI Window, WindowType=%d, WindowName=%s\n", m_WindowType, m_WindowName.c_str());
}

	/*
		加载窗口所需图片资源plist
	*/
void IWindow::LoadPlistForWindow(){
	//加载指定资源Plist
	UIWindowItemData* pWindowItem = UIWindowDataManager::get_instance2()->GetWindowByType(this->GetWindowType());
	if (strlen(pWindowItem->mBGImageResourceName)>0)
	{
		_TRACE_LOADING_PLIST_(pWindowItem->mBGImageResourceName)
	}
	if (strlen(pWindowItem->mUIResourceName)>0)
	{
		_TRACE_LOADING_PLIST_(pWindowItem->mUIResourceName)	
	}
}
	/*
		清除窗口所需图片资源plist
	*/
void IWindow::UnloadPlistForWindow(){
	//强行清除图片资源
	if(m_bIsForceClearAnimation)
		DOTATribeApp::get_instance2()->ForceClearAnimationCache();
	if(m_bIsForceClearUnUseTex)
		DOTATribeApp::get_instance2()->ForceFreeMemory(); 
	//卸载指定资源Plist
	UIWindowItemData* pWindowItem = UIWindowDataManager::get_instance2()->GetWindowByType(this->GetWindowType());
	if (pWindowItem->mIsBGImageReleaseWhenWindowDestroy&&strlen(pWindowItem->mBGImageResourceName)>0)
	{
		_TRACE_UNLOAD_PLIST_(pWindowItem->mBGImageResourceName)
	}
	if (pWindowItem->mIsUIImageReleaseWhenWindowDestroy&&strlen(pWindowItem->mUIResourceName)>0)
	{
		_TRACE_UNLOAD_PLIST_(pWindowItem->mUIResourceName)	
	}
}

bool IWindow::ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	return m_bModelWindow;
}

void IWindow::ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{

}

void IWindow::ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{

}

void IWindow::ccTouchCancel(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{

}
