//Name：DOTATribeApp
//Function：游戏C++层总入口
//Author：Johny

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/DotaGameConfig.h"
#include "../include/DBSystem.h"
#include "../include/ProfSystem.h"
#include "../include/DebugerSystem.h"
#include "../include/EngineSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/GuideSystem.h"
#include "../include/UISystem.h"
#include "../include/IAPSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/NetSystem.h"
#include "../include/NotifySystem.h"
#include "../include/SoundSystem.h"
#include "../include/TimeSystem.h"
#include "../include/VariableSystem.h"
#include "../include/IProcedure.h"
#include "../include/LogoProcedure.h"
#include "../include/LoadingProcedure.h"
#include "../include/LoginProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/AthleticsProcedure.h"
#include "../include/SysLangDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/CreateRoleProcedure.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/ArenaProcedure.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/DataHandlerSystem.h"
#include "../include/NodeFactoryManager.h"
#include "../include/WindowManager.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/PopWindowManager.h"
#include "../include/LuaSystem.h"
#include "../include/UpdateSystem.h"
using  namespace  cocos2d;


template<> DOTATribeApp* cobra_win::Singleton2<DOTATribeApp>::m_pMySelf = NULL;

DOTATribeApp::DOTATribeApp()
{
	m_pLogoProcedure      = NULL;
	m_pLoadingProcedure   = NULL;
	m_pLoginProcedure     = NULL;
	m_pHomeProcedure	  = NULL;
	m_pAthleticsProcudure = NULL;
	m_pSelectCustomsPassProcedure	  = NULL;
	m_pCreateRoleProcedure = NULL;
	m_pSelectMissionProcedure = NULL;
	m_pTeamBattleProcedure = NULL;
	m_pPreProcedure    = NULL;
	m_pActiveProcedure = NULL;
	m_bRun             = true;
}

DOTATribeApp::~DOTATribeApp()
{

	CCScriptEngineManager::sharedManager()->purgeSharedManager();
}

std::string DOTATribeApp::GetVersion()
{
	return DGC_GetGameVersion();
}

void DOTATribeApp::SetRun(bool bRun)
{
	m_bRun = bRun;
}

int DOTATribeApp::GetFPS()
{
	int fps = 30;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "FPS", fps);

	if (fps < 20)
		fps = 20;
	else if (fps > 60)
		fps = 60;

	return fps;
}

int DOTATribeApp::GetAppWidth()
{
	return int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
}

int DOTATribeApp::GetAppHeight()
{
	return int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
}


//@游戏重置,用于断线重连，重新登陆等
void DOTATribeApp::ResetAllGame(){
	DOTATribeApp::get_instance2()->GetActiveProcedure()->Destroy();
	ClearAllWindow();
	ClearAllData();
	DOTATribeApp::get_instance2()->ForceFreeMemory();
}

//@清除所有游戏界面
void DOTATribeApp::ClearAllWindow(){
	//停止新手引导
	GUIDESYSTEM->StopGuide();
	WindowManager::get_instance2()->DestroyAllWindow();
	PopWindowManager::get_instance2()->ClearPopWindowList();
}

void DOTATribeApp::ClearAllVisibleWindow(){

	WindowManager::get_instance2()->DestroyAllVisibleWindow();
}

/*
	清除游戏界面所有可见窗口除了某一窗口
*/
void DOTATribeApp::ClearAllVisibleWindow(int iType)
{
	WindowManager::get_instance2()->DestroyAllVisibleWindow(iType);
}
/*
	清除所有游戏数据
*/
void DOTATribeApp::ClearAllData(){
	DATAHANDLERSYSTEM->DestroyAllDataHandler();
}


void DOTATribeApp::SetActiveProcedure(IProcedure* pProcedure)
{

	if (pProcedure==NULL || m_pActiveProcedure==pProcedure)
	return ;
	m_pPreProcedure    = m_pActiveProcedure;
	m_pActiveProcedure = pProcedure;
}

IProcedure* DOTATribeApp::GetActiveProcedure()
{
	return m_pActiveProcedure;
}

IProcedure*  DOTATribeApp::GetProcedure(int idx)
{
	switch(idx)
	{
	case IProcedure::_TYPED_LOGO_PROCEDURE_:
		return	m_pLogoProcedure;
	case IProcedure::_TYPED_LOADING_PROCEDURE_:
		return	m_pLoadingProcedure;
	case IProcedure::_TYPED_LOGIN_PROCEDURE_:
		return	m_pLoginProcedure;
	case IProcedure::_TYPED_HOME_PROCEDURE_:
		return	m_pHomeProcedure;
	case IProcedure::_TYPED_ATHLETICS_PROCEDURE_:
		return	m_pAthleticsProcudure;
	case IProcedure::_TYPED_CREATEROLEPROCEDURE_PROCEDURE_:
		return	m_pCreateRoleProcedure;
	case IProcedure::_TYPED_SELECTMISSION_PROCEDURE_:
		return	m_pSelectMissionProcedure;
	case IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_:
		return m_pTeamBattleProcedure;
	case IProcedure::_TYPED_ARENA_PROCEDURE_:
		return m_pArenaProcedure;
	default:
		return NULL;
	}
}

	/*
		检查当前流程与欲切换流程相同
	*/
bool DOTATribeApp::IsActiveProcedureEqualNextProcedure(int nextProcedure){
	return GetProcedure(nextProcedure)==m_pActiveProcedure;
}

	/*
		检查当前流程与欲切换流程相同
	*/
bool DOTATribeApp::IsActiveProcedureEqualNextProcedure(IProcedure* nextProcedure){
	return nextProcedure==m_pActiveProcedure;
}

/*
	检查当前流程是否为登陆流程
*/
bool DOTATribeApp::IsLoginProcedureAsActiveProcedure(){
	return GetActiveProcedure()==m_pLoginProcedure;
}

/*
	检查当前流程是否为创建角色流程
*/
bool DOTATribeApp::IsCreateRoleProcedureAsActiveProcedure(){
	return GetActiveProcedure()==m_pCreateRoleProcedure;
}

/*
	检查当前流程是否为大厅流程
*/
bool DOTATribeApp::IsHomeProcedureAsActiveProcedure()
{
	return GetActiveProcedure()==m_pHomeProcedure;
}

/*
	检查当前流程是否为组队副本流程
*/
bool DOTATribeApp::IsTeamBattleAsActiveProcedure()
{
	return GetActiveProcedure()==m_pTeamBattleProcedure;
}

/*
	检查当前流程是否为世界地图流程
*/
bool DOTATribeApp::IsSelectMissionAsActiveProcedure()
{
	return GetActiveProcedure()==m_pSelectMissionProcedure;
}

/*
	检查当前流程是否为竞技场流程
*/
bool DOTATribeApp::IsArenaAsActiveProcedure()
{
	return GetActiveProcedure()==m_pArenaProcedure;
}

void DOTATribeApp::ForceFreeMemory()
{
	ENGINESYSTEM->FreeMemory();
}


void  DOTATribeApp::ForceClearAnimationCache()
{
	ENGINESYSTEM->ForceClearAnimationCache();
}

void DOTATribeApp::VerifyIAPList(float dt)
{
	IAPSYSTEM->VerifyIAPIdentifier();
}

void DOTATribeApp::DelayForCYSDK(float time)
{
    SERVERINFODATAINFO->DelayForCYSDK();
}

bool DOTATribeApp::Init()
{
	do 
	{
		// 初始化CCNode
		onEnter();

		// 设置接收事件
		CCDirector::sharedDirector()->getSystem()->setDelegate(dynamic_cast<cocos2d::CCSystemDelegate*>(this));

		// 初始化随机数生成器
		srand((unsigned)time(NULL));

		// 初始化配置系统管理器
		new VariableSystem;
		if (!VARIABLESYSTEM->Init())
			break;

		// 创建并初始化下载更新系统
		new UpdateSystem;
		UPDATESYSTEM->Init();

		// 初始化应用程序引擎层环境变量
		EngineSystem::InitAppEnv();

		// 初始化日志系统管理器
		new LoggerSystem;
		if (!LOGGERSYSTEM->Init())
			break;

		// 初始化性能统计系统管理器
		new ProfSystem;
		if (!PROFSYSTEM->Init())
			break;

	/*	_BEGIN_PROF_CHUNK_("LuaSystem::Init()")
			// 初始化音效管理器
		new LuaSystem;
		if (!LUASYSTEM->Init())
			break;
		_END_PROF_CHUNK_()*/

		_BEGIN_PROF_CHUNK_("TimeSystem::Init()")
		// 初始化时间系统管理器
		new TimeSystem;
		if (!TIMESYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("EventSystem::Init()")
		// 初始化事件响应处理系统
		new EventSystem;
		if (!EVENTSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("DBSystem::Init()")
		// 初始化数据管理系统管理器
		new DBSystem;
		if (!DBSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("DataHandler::Init()")
		/*
			初始化内存数据管理器
		*/
		new DataHandlerSystem();
		if (!DATAHANDLERSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("NetSystem::Init()")
		// 初始化网络系统管理器
		new NetSystem;
		if (!NETSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("EngineSystem::Init()")
		// 初始化引擎系统管理器
		new EngineSystem;
		if (!ENGINESYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("SoundSystem::Init()")
		// 初始化音效管理器
		new SoundSystem;
		if (!SOUNDSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("UISystem::Init()")
		// 初始化UI系统管理器
		new UISystem;
		if (!UISYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("GuideSystem::Init()")
		// 初始化新手引导系统管理器
		new GuideSystem;
		if (!GUIDESYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("IAPSystem::Init()")
		// 初始化IAP交易系统管理器
		new IAPSystem;
		if (!IAPSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()

		_BEGIN_PROF_CHUNK_("NotifySystem::Init()")
		// 初始化本地通知系统管理器
		new NotifySystem;
		if (!NOTIFYSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()


		_BEGIN_PROF_CHUNK_("DebugerSystem::Init()")
		// 初始化调试器管理器
		new DebugerSystem;
		if (!DEBUGERSYSTEM->Init())
			break;
		_END_PROF_CHUNK_()
 
		/*
			=======初始化流程======
		*/
		m_pLogoProcedure      = new LogoProcedure;
		m_pLoadingProcedure   = new LoadingProcedure;
		m_pLoginProcedure     = new LoginProcedure;
		m_pHomeProcedure    =	 new HomeProcedure;
		m_pAthleticsProcudure = new AthleticsProcedure;
		m_pTeamBattleProcedure = new TeamBattleProcedure;
		m_pCreateRoleProcedure = new CreateRoleProcedure;
		m_pSelectMissionProcedure = new SelectMissionProcedure;
		m_pArenaProcedure = new ArenaProcedure;
		/*
			检查设备，进入相应的流程
		*/
		if (EngineSystem::GetDeviceType()==EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)//安卓
		{
			//先启动Logo流程
			m_pPreProcedure    = m_pLogoProcedure;
			m_pActiveProcedure = m_pLogoProcedure;
			m_pActiveProcedure->Init();
		}
		else{//iOS
				/*
					登陆流程包含：
					1.检查更新
					2.更新
					3.选服务器
					4.登陆
				*/
				m_pPreProcedure    = m_pLoginProcedure;
				m_pActiveProcedure = m_pLoginProcedure;
				m_pActiveProcedure->Init();
		}

		// 注册游戏帧循环
		schedule(schedule_selector(DOTATribeApp::Tick));

#if 0
		// 进行定时验证IA订单的操作
		float verifyIAPInterval = 10.0f;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "VerifyIAPListInterval", verifyIAPInterval);
		schedule(schedule_selector(DOTATribeApp::VerifyIAPList), verifyIAPInterval);
#endif

		// 设置游戏默认语言
		int type = SysLangDataManager::_TYPED_SYSLANG_CN_;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SYS", "SysLangType", type);
		cocos2d::CCDirector::sharedDirector()->getSystem()->setSysLang(type);

		LOGGERSYSTEM->LogInfo("Init DOTATribeApp Success\n");
		return true;
	} 
	while(false);

	return false;
}

void DOTATribeApp::Tick(float interval)
{
	//
	UISYSTEM->Tick_First();
	//切换流程
	if (m_pActiveProcedure != m_pPreProcedure)
	{
		m_pPreProcedure->Destroy();
		m_pActiveProcedure->Init();

		m_pPreProcedure = m_pActiveProcedure;
		
		//检查装备提醒窗口是否显示
		NEWEQUIPREMINDDATAHANDLER->DetectRemindShow();
	}
	// 当前处理流程桢更新
	m_pActiveProcedure->Tick();

	//LUA
//	LUASYSTEM->Tick();

	//更新系统
	UPDATESYSTEM->Tick();

	// 时间系统管理器帧更新
	TIMESYSTEM->Tick(interval);
	// 配置系统管理器桢更新
	VARIABLESYSTEM->Tick();
	// 日志系统管理器桢更新
	LOGGERSYSTEM->Tick();
	// 性能统计系统帧更新
	PROFSYSTEM->Tick();
	// 网络管理系统帧更新
	NETSYSTEM->Tick();
	// 事件响应处理系统桢更新
	EVENTSYSTEM->Tick();
	// 数据管理系统帧更新
	DBSYSTEM->Tick();
	// 引擎系统管理器桢更新
	ENGINESYSTEM->Tick();
	// 音效管理器桢更新
	SOUNDSYSTEM->Tick();
	// UI系统管理器桢更新
	UISYSTEM->Tick();
	// 新手引导系统管理器帧更新
	GUIDESYSTEM->Tick();
	// IAP交易系统管理器帧更新
	IAPSYSTEM->Tick();
	// 本地通知系统管理器帧更新
	NOTIFYSYSTEM->Tick();
	// 调试器管理器帧更新
	DEBUGERSYSTEM->Tick();
	// 对象管理器逻辑帧更新

	// 是否终止程序
	if (!m_bRun)
	{
		Destroy();
	}
}

void DOTATribeApp::Destroy()
{
	

	// 对当前正在激活的流程进行销毁，释放必要资源
	if (m_pActiveProcedure != NULL)
	{
		m_pActiveProcedure->Destroy();
		m_pPreProcedure    = NULL;
		m_pActiveProcedure = NULL;
	}

	// 删除LOGO流程处理
	if (m_pLogoProcedure != NULL)
	{
		delete m_pLogoProcedure;
		m_pLogoProcedure = NULL;
	}

	// 删除Loading处理流程
	if (m_pLoadingProcedure != NULL)
	{
		delete m_pLoadingProcedure;
		m_pLoadingProcedure = NULL;
	}

	// 删除登陆流程处理
	if (m_pLoginProcedure != NULL)
	{
		delete m_pLoginProcedure;
		m_pLoginProcedure = NULL;
	}

	// 删除主场景流程处理
	if (m_pHomeProcedure != NULL)
	{
		delete m_pHomeProcedure;
		m_pHomeProcedure = NULL;
	}

	// 删除战斗流程处理
	if (m_pAthleticsProcudure != NULL)
	{
		delete m_pAthleticsProcudure;
		m_pAthleticsProcudure = NULL;
	}

	//删除创建人物流程处理
	if (m_pCreateRoleProcedure != NULL)
	{
		delete m_pCreateRoleProcedure;
		m_pCreateRoleProcedure = NULL;
	}

	
	//删除组队副本流程处理
	if (m_pTeamBattleProcedure != NULL)
	{
		delete m_pTeamBattleProcedure;
		m_pTeamBattleProcedure = NULL;
	}

	//删除世界地图流程处理
	if (m_pSelectMissionProcedure != NULL)
	{
		delete m_pSelectMissionProcedure;
		m_pSelectMissionProcedure = NULL;
	}

	//删除世界地图流程处理
	if (m_pArenaProcedure != NULL)
	{
		delete m_pArenaProcedure;
		m_pArenaProcedure = NULL;
	}
	 
	// 销毁调试器管理器
	if (DEBUGERSYSTEM != NULL)
	{
		DEBUGERSYSTEM->Destroy();
		delete DEBUGERSYSTEM;
	}

	// 销毁本地通知系统管理器
	if (NOTIFYSYSTEM != NULL)
	{
		NOTIFYSYSTEM->Destroy();
		delete NOTIFYSYSTEM;
	}

	// 销毁IAP交易系统管理器
	if (IAPSYSTEM != NULL)
	{
		IAPSYSTEM->Destroy();
		delete IAPSYSTEM;
	}

	// 销毁引导引导系统管理器
	if (GUIDESYSTEM != NULL)
	{
		GUIDESYSTEM->Destroy();
		delete GUIDESYSTEM;
	}

	// 销毁UI系统管理器
	if (UISYSTEM != NULL)
	{
		UISYSTEM->Destroy();
		delete UISYSTEM;
	}

	// 销毁音效管理器
	if (SOUNDSYSTEM != NULL)
	{
		SOUNDSYSTEM->Destroy();
		delete SOUNDSYSTEM;
	}

	// 销毁引擎系统管理器
	if (ENGINESYSTEM != NULL)
	{
		ENGINESYSTEM->Destroy();
		delete ENGINESYSTEM;
	}

	// 销毁数据系统管理器
	if (DBSYSTEM != NULL)
	{
		DBSYSTEM->Destroy();
		delete DBSYSTEM;
	}

	//销毁数据系统管理器
	if (DATAHANDLERSYSTEM != NULL)
	{
		DATAHANDLERSYSTEM->Destroy();
		delete DATAHANDLERSYSTEM;
	}

	// 销毁事件响应处理系统
	if (EVENTSYSTEM != NULL)
	{
		EVENTSYSTEM->Destroy();
		delete EVENTSYSTEM;
	}

	// 销毁网络系统
	if (NETSYSTEM != NULL)
	{
		NETSYSTEM->Destroy();
		delete NETSYSTEM;
	}

	// 销毁时间系统管理器
	if (TIMESYSTEM != NULL)
	{
		TIMESYSTEM->Destroy();
		delete TIMESYSTEM;
	}

	// 销毁配置系统管理器
	if (VARIABLESYSTEM != NULL)
	{
		VARIABLESYSTEM->Destroy();
		delete VARIABLESYSTEM;
	}

	// 销毁性能统计系统
	if (PROFSYSTEM != NULL)
	{
		PROFSYSTEM->Destroy();
		delete PROFSYSTEM;
	}

	//AutoCocos管理器，测试阶段
	if (ACNODEFACTORYMANAGER!=NULL)
	{
		ACNODEFACTORYMANAGER->OnDestroy();
		//delete ACNODEFACTORYMANAGER;
	}

	//LUA
/*
	if(LUASYSTEM != NULL)
	{
		LUASYSTEM->Destroy();
		delete LUASYSTEM;
	}*/

	// 释放下载更新系统
	if (UPDATESYSTEM)
	{
		UPDATESYSTEM->Destroy();
		delete UPDATESYSTEM;
	}

	// 销毁日志系统管理器
	if (LOGGERSYSTEM != NULL)
	{
		LOGGERSYSTEM->Destroy();
		delete LOGGERSYSTEM;
	}
	 
	cocos2d::CCDirector::sharedDirector()->end();
	 
}

void DOTATribeApp::onAppExit()
{
	Destroy();
}

void DOTATribeApp::onWebDialogClose(int type)
{

}

void DOTATribeApp::onNetworkChanged()
{
	// 至少需要判断当前客户端是否已经登录游戏中还是在登陆界面未登陆状态
	// 未登陆的话，不用做任何事情；登陆的话，需要断开当前网络提示玩家......
	SERVERINFODATAINFO->NotifyNetworkChanged();
}

void DOTATribeApp::onNetworkDisConnected()
{
	// 至少需要判断当前客户端是否已经登录游戏中还是在登陆界面未登陆状态
	// 未登陆的话，无需提示；登陆的话，需要断开当前网络提示玩家......
	SERVERINFODATAINFO->NotifyNetworkChanged();
}

void DOTATribeApp::onQueryAppServerPushId(std::string pushId)
{
	// 此处各个项目需要按照实际需求增加对应的处理逻辑
	// 至少需要判断当前客户端是否已经登录游戏中还是在登陆界面未登陆状态
	// 未登陆的话，需要保存该唯一Id，等登陆之后发送给服务器
	// 登陆的话，直接发送给服务器保存即可
}

void DOTATribeApp::applicationDidPaused()
{
	m_pActiveProcedure->OnSystemPauseEventHandler();
	SOUNDSYSTEM->OnPauseEventHandler();
	cocos2d::CCDirector::sharedDirector()->pause();
}

void DOTATribeApp::applicationDidResumed()
{
	cocos2d::CCDirector::sharedDirector()->resume();
	m_pActiveProcedure->OnSystemResumeEventHandler();
	SOUNDSYSTEM->OnResumeEventHandler();
}

bool DOTATribeApp::applicationDidFinishLaunching()
{
	bool ret = Init();
	if (!ret)
	{
		delete this;
		exit(0);
	}
	return ret;
}

void DOTATribeApp::applicationDidEnterBackground()
{
	//通知系统进入后台的操作
	if (NOTIFYSYSTEM!=NULL)
	{
		NOTIFYSYSTEM->OnSystemEnterBackEventHandler();
	}

	// 在Win32下面，因为resize了窗口会提前调用这个地方，所以加上
	// 必要的判断 
	if (m_pActiveProcedure == NULL)
		return;

	// 音效系统处理
	// 解决IOS下面莫名其妙切后台音效消失的问题
	if (SOUNDSYSTEM != NULL)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SOUNDSYSTEM->Destroy();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SOUNDSYSTEM->OnEnterBackgroundEventHandler();
#endif
	}

	m_pActiveProcedure->OnSystemEnterBackEventHandler();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	cocos2d::CCDirector::sharedDirector()->stopAnimation();
#endif
	cocos2d::CCDirector::sharedDirector()->pause();
}

void DOTATribeApp::applicationWillEnterForeground()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// 在Win32下面，因为resize了窗口会提前调用这个地方，所以加上
	// 必要的判断 
	if (m_pActiveProcedure == NULL)
		return;
#endif

	cocos2d::CCDirector::sharedDirector()->resume();

	//通知系统进入前台的操作
	if (NOTIFYSYSTEM!=NULL)
	{
		NOTIFYSYSTEM->OnSystemEnterFrontEventHandler();
	}

	// 音效系统处理
	// 解决IOS下面莫名其妙切后台音效消失的问题
	if (SOUNDSYSTEM != NULL)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SOUNDSYSTEM->Init();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SOUNDSYSTEM->OnEnterForegroundEventHandler();
#endif
	}
	//动画恢复
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	cocos2d::CCDirector::sharedDirector()->startAnimation();
#endif
	//
	m_pActiveProcedure->OnSystemEnterFrontEventHandler();
}