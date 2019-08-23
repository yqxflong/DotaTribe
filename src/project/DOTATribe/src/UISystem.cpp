#include "../include/UISystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include "../include/VariableSystem.h"
#include "../include/EventDef.h"
#include "../include/EventSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/EngineSystem.h"
#include "../include/UILayer.h"
#include <cocos2d.h>
#include "../include/ProfSystem.h"
#include "../include/EventTyper.h"
#include <CocoStudio/Trigger/ObjectFactory.h>


template<> UISystem* cobra_win::Singleton2<UISystem>::m_pMySelf = NULL;
bool UISystem::GLOBAL_MENUITEM_ENABLED=true;
bool UISystem::GLOBAL_UICLEAR_ENABLED=false;

UISystem::UISystem()
{
	m_pUILayer = NULL;

}

UISystem::~UISystem()
{

}

cocos2d::CCLayer* UISystem::GetUILayer()
{
	return m_pUILayer;
}

void UISystem::OnInputEventHandler()
{

}

void UISystem::RegisterUIEvent(int iEventType, int iWindowType)
{
	char buffer[1024] = "";
	sprintf(buffer, "%d", iWindowType);
	EVENTSYSTEM->RegisterEventHandler(iEventType, OnUISystemEventHandler, buffer);
}

void UISystem::RegisterUIEvent2(int iEventType, int iWindowType)
{
	char buffer[1024] = "";
	sprintf(buffer, "%d", iWindowType);
	EVENTSYSTEM->RegisterEventHandler(iEventType, OnUISystemEventHandler2, buffer);
}

void UISystem::RegisterUIEvent(int iEventType)
{
	EVENTSYSTEM->RegisterEventHandler(iEventType, OnUISystemEventHandler, "");
}

void UISystem::PushEvent(int iEventType)
{
	EVENTSYSTEM->PushEvent(iEventType);
}

void UISystem::PushEvent(int iEventType, std::string param0)
{
	EVENTSYSTEM->PushEvent(iEventType, param0);
}

bool UISystem::Init()
{
	do 
	{
		// 创建根窗口节点
		m_pUILayer = new cyouUILayer();
		m_pUILayer->init();
		m_pUILayer->autorelease();
		m_pUILayer->setAnchorPoint(cocos2d::CCPointZero);
		ENGINESYSTEM->GetScene()->addChild(m_pUILayer);

		// 创建并初始化窗口管理器
		new WindowManager;
		WINDOWMANAGER->Init();

		//注册事件
		//
		//1.启用全局按钮
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_ENABLE_GLOBAL_MENUITEM,OnEnabelGlobalMenuitemEventHandler);



		LOGGERSYSTEM->LogInfo("Init UISystem Success\n");
		return true;
	} 
	while(false);

	LOGGERSYSTEM->LogInfo("Init UISystem Failed\n");
	return false;
}

void UISystem::Tick()
{
	WINDOWMANAGER->Tick();
}

	/*
		逻辑桢更新
		#DotaTribeApp::Tick 第一个分发的接口
	*/
void UISystem::Tick_First(){
	if (GLOBAL_MENUITEM_ENABLED==false)
		GLOBAL_MENUITEM_ENABLED=true;
	if(GLOBAL_UICLEAR_ENABLED==true)
	{   
		if(DOTATribeApp::get_instance2()->m_pActiveProcedure->GetType()!=IProcedure::_TYPED_ATHLETICS_PROCEDURE_)
		{
			DOTATribeApp::get_instance2()->ForceFreeMemory();
		}
		GLOBAL_UICLEAR_ENABLED=false;
	}
 
}

void UISystem::Destroy()
{
	//恢复到初始值
	GLOBAL_MENUITEM_ENABLED=true;
	GLOBAL_UICLEAR_ENABLED=false;

	// 销毁窗口管理器
	if (WINDOWMANAGER != NULL)
	{
		WINDOWMANAGER->Destroy();
		delete WINDOWMANAGER;
	}

	// 销毁UI根窗口
	if (m_pUILayer != NULL)
	{
		ENGINESYSTEM->GetScene()->removeChild(m_pUILayer, true);
		m_pUILayer = NULL;
	}

	// 销毁CocoStudio的Factory实例
	cocos2d::extension::ObjectFactory::getInstance()->destroyInstance();

	LOGGERSYSTEM->LogInfo("Destroy UISystem Success\n");
}

	/*
		getter：GLOBAL_MENUITEM_ENABLED
	*/
bool UISystem::Get_Global_menuitem_enabled(){
	return GLOBAL_MENUITEM_ENABLED;
}
	/*
		setter：GLOBAL_MENUITEM_ENABLED
	*/
void UISystem::Set_Global_menuitem_enabled(bool enabled){
	GLOBAL_MENUITEM_ENABLED=enabled;
}

bool UISystem::Get_Global_UIClear_Enable(){
	return GLOBAL_UICLEAR_ENABLED;
}

void  UISystem::Set_Global_UIClear_Enable(bool enabled){
	GLOBAL_UICLEAR_ENABLED=enabled;
}


void UISystem::OnUISystemEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList)
{
	if (owerData != "")
	{
		int iWindowType = 0;
		sscanf(owerData.c_str(), "%d", &iWindowType);
		IWindow* pWindow = WINDOWMANAGER->GetWindowByType(iWindowType);
		if (pWindow == NULL)
			return ;

		if (!pWindow->IsLoad())
			pWindow->Load();

		pWindow->OnEventHandler(iEventType, paramList);
	}

	return ;
}

void UISystem::OnUISystemEventHandler2(int iEventType, std::string owerData, std::list<std::string>& paramList)
{
	if (owerData != "")
	{
		int iWindowType = 0;
		sscanf(owerData.c_str(), "%d", &iWindowType);
		IWindow* pWindow = WINDOWMANAGER->GetWindowByType(iWindowType);
		if (pWindow == NULL)
			return ;

		if (!pWindow->IsLoad())
			return;

		pWindow->OnEventHandler(iEventType, paramList);
	}

	return ;
}

	/*
		启用全局按钮的事件
	*/
void  UISystem::OnEnabelGlobalMenuitemEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	GLOBAL_MENUITEM_ENABLED=true;
}
