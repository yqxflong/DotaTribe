#include <cocos2d.h>
#include "../include/WindowManager.h"
#include "../include/EngineSystem.h"
#include "../include/EventDef.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/IWindow.h"
#include "../include/UIWindowDataManager.h"
#include "../include/StartWindow.h"
#include "../include/DTTimedGrayWindow.h"
#include "../include/RoleStatusWindow.h"
#include "../include/MessageBoxWindow.h"
#include "../include/LogoWindow.h"
#include "../include/HomeWindow.h"
#include "../include/LoadingWindow.h"
#include "../include/DBSystem.h"
#include "../include/AthleticsWindow.h"
#include "../include/AthleticResultWindow.h"
#include "../include/SelectRoleWindow.h"
#include "../include/PESWindow.h"
#include "../include/LevelupNormalWindow.h"
#include "../include/SelectMissionWindow.h"
#include "../include/SelectSonMissionWindow.h"
#include "../include/MassacreWindow.h"
#include "../include/MultiReWardWindow.h"
#include "../include/SelectSkillWindow.h"
#include "../include/HerobarWindow.h"
#include "../include/SelectServerWindow.h"
#include "../include/InputNumWindow.h"
#include "../include/EquipmentSelectCardWindow.h"
#include "../include/SystemsetWindow.h"
#include "../include/ArenaWindow.h"
#include "../include/ChatWindow.h"
#include "../include/NoticeBoxWindow.h"
#include "../include/ShopWindow.h"
#include "../include/EffectWindow.h"
#include "../include/ShopinputNumWindow.h"
#include "../include/RevenueWindow.h"
#include "../include/TempleWindow.h"
#include "../include/ConvictionWindow.h"
#include "../include/HelpWindow.h"
#include "../include/StrengthenWindow.h"
#include "../include/ClimbTowerWindow.h"
#include "../include/BagWindow.h"//新背包
#include "../include/TipsWindow.h"
#include "../include/GuideWindow.h"
#include "../include/MarketWindow.h"
#include "../include/CommunicationWaittingWindow.h"
#include "../include/TeamBattleWindow.h"
#include "../include/TeamSelectWindow.h"
#include "../include/FriendWindow.h"
#include "../include/PlayerTipsWindow.h"
#include "../include/RankWindow.h"
#include "../include/EmailWindow.h"
#include "../include/PuCongWindow.h"
#include "../include/NetObjectTipsWindow.h"
#include "../include/EquipTipsWindow.h"
#include "../include/WriteEmailWindow.h"
#include "../include/ErrorTipsWindow.h"
#include "../include/MainTaskWindow.h"
#include "../include/RechargeWindow.h"
#include "../include/AnnouncementWindow.h"
#include "../include/RechargeWarnWindow.h"
#include "../include/LimitedActivityWindow.h"
#include "../include/ForcePushTaskRewardWindow.h"
#include "../include/MineAreaWindow.h"
#include "../include/HeroIllustratedWindow.h"
#include "../include/HELeadershipLvUpWindow.h"
#include "../include/HeroAdvancedWindow.h"
#include "../include/PopWindowManager.h"
#include "../include/ArenaRewardWindow.h"
#include "../include/FirstRechGiftWindow.h"
#include "../include/HeroSoulWindow.h"
 
#include "../include/NewEquipremindWindow.h"

#include "../include/BossScoreWindow.h"
 
 
//活动
#include "../include/ActivityWindow.h"
#include "../include/LevelUpRewardActivityWindow.h"
#include "../include/HeroAltarWindow.h"
#include "../include/SpringView.h"
#include "../Include/LessResourceWindow.h"
#include "../Include/VipWindow.h"
#include "../include/GainHeroWindow.h"
#include "../include/GainSoulDebriWindow.h"
#include "../include/CheckLeadershipWindow.h"
#include "../include/ShopTipsWindow.h"
#include "../include/LoginActivityWindow.h"
#include "../include/SoulTipsWindow.h"
#include "../include/GrowupPlanWindow.h"
#include "../include/VipGiftWindow.h"
#include "../include/ExchangeActivityWindow.h"
#include "../include/AppstoreWaitWindow.h"
#include "../include/GainCallItemWindow.h"
#include "../include/TenCallWindow.h"
#include "../include/TeamInfoWindow.h"
template<> WindowManager* cobra_win::Singleton2<WindowManager>::m_pMySelf = NULL;

WindowManager::WindowManager()
{
	m_WindowList.clear();
}

WindowManager::~WindowManager()
{

}

IWindow* WindowManager::GetWindowByType(int iWindowType)
{
	std::map<int, IWindow*>::iterator iter = m_WindowList.find(iWindowType);
	if (iter == m_WindowList.end())
		return NULL;

	return iter->second;
}

bool WindowManager::IsWindowVisible(int iWindowType)
{
	std::map<int, IWindow*>::iterator iter = m_WindowList.find(iWindowType);
	if (iter == m_WindowList.end())
		return false;

	return iter->second->IsVisible();
}

bool   WindowManager::IsWindowLoad(int iWindowType)
{
	std::map<int, IWindow*>::iterator iter = m_WindowList.find(iWindowType);
	if (iter == m_WindowList.end())
		return false;

	return iter->second->IsLoad();
}


void WindowManager::HideAllWindow(bool bVisible)
{
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsLoad())
		{
			iter->second->Show(bVisible);
		}
	}
}

	/*
		销毁所有窗口
	*/
void WindowManager::DestroyAllWindow(){
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsLoad())
		{
			iter->second->Destroy();
		}
	}
}
/*
	销毁所有可视窗口
*/
void WindowManager::DestroyAllVisibleWindow()
{
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsVisible())
		{
			iter->second->Destroy();
		}
	}
}

/*
	销毁所有可视窗口除了某一窗口
*/
void WindowManager::DestroyAllVisibleWindow(int iType)
{
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsVisible() && iter->second->GetWindowType() != iType)
		{
			iter->second->Destroy();
		}
	}
}

size_t WindowManager::GetWindowCount()
{
	return m_WindowList.size();
}

IWindow* WindowManager::GetWindowByIndex(size_t iIndex)
{
	if (iIndex >= m_WindowList.size())
		return NULL;

	std::map<int, IWindow*>::iterator iter = m_WindowList.begin();
	for (size_t i=0; i!=iIndex; ++i)
	{
		++iter;
	}
	return iter->second;
}

std::map<int, IWindow*>& WindowManager::GetWindowList()
{
	return m_WindowList;
}

static  void  init_ui_window(IWindow* pWindow)
{
	WINDOWMANAGER->m_WindowList.insert(std::map<int, IWindow*>::value_type(pWindow->GetWindowType(), pWindow));
	pWindow->Init();
	return;
}

bool WindowManager::Init()
{
	//初始化弹窗管理器
	new PopWindowManager();
	PopWindowManager::get_instance2()->Init();
	//
	//需要开机初始化的窗口
	m_WindowList.clear();
	init_ui_window(new LogoWindow());
	init_ui_window(new StartWindow());
	init_ui_window(new MessageBoxWindow());
	init_ui_window(new CommnunicationWattingWindow());
	//注册更新结束通知
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_VERSIONUPDATE_FINISHED_, WindowManager::OnVersionUpdateFinishedEventHandler, "");
	return true;
}

void WindowManager::Tick()
{
	//弹窗管理器的tick
	PopWindowManager::get_instance2()->Tick();
	//所有窗口的tick
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsLoad())
		{
			iter->second->Tick();
		}
	}
}

void WindowManager::Destroy()
{
	//销毁弹窗管理器
	if(PopWindowManager::get_instance2()){
		PopWindowManager::get_instance2()->Destroy();
		delete PopWindowManager::get_instance2();
	}
	//销毁所有窗口
	std::map<int, IWindow*>::iterator iter   = m_WindowList.begin();
	std::map<int, IWindow*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->IsLoad())
		{
			iter->second->Destroy();
		}

		delete iter->second;
	}
	m_WindowList.clear();
}

void WindowManager::OnVersionUpdateFinishedEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList)
{
	// 注册c/c++窗口
	init_ui_window(new LoadingWindow());
	init_ui_window(new DTTimedGrayWindow());
	init_ui_window(new RoleStatusWindow());
	init_ui_window(new HomeWindow());
	init_ui_window(new AthleticsWindow());
	init_ui_window(new AthleticsResultWindow());
	init_ui_window(new SelectRoleWindow());
	init_ui_window(new StrengthenWindow());
	init_ui_window(new LevelupNormalWindow());
	init_ui_window(new PESWindow());
	init_ui_window(new SelectSkillWindow());
	init_ui_window(new SelectMissionWindow());
	init_ui_window(new SelectSonMissionWindow());
	init_ui_window(new MassacreWindow());
	init_ui_window(new MultiReWardWindow());
	init_ui_window(new HerobarWindow());
	init_ui_window(new SelectServerWindow());
	init_ui_window(new InputNumWindow());
	init_ui_window(new EquipmentSelectCardWindow());
	init_ui_window(new SystemsetWindow());
	init_ui_window(new ArenaWindow());
	init_ui_window(new ChatWindow());
	init_ui_window(new NoticeBoxWindow());
	init_ui_window(new ShopWindow());
	init_ui_window(new EffectWindow());
	init_ui_window(new ClimbTowerWindow());
	init_ui_window(new BagWindow());
	init_ui_window(new GuideWindow());
	init_ui_window(new ShopinputNumWindow());
	init_ui_window(new TipsWindow());
	init_ui_window(new RevenueWindow());
	init_ui_window(new TempleWindow());
	init_ui_window(new ConvictionWindow());
	init_ui_window(new MarketWindow());
	init_ui_window(new TeamBattleWindow());
	init_ui_window(new TeamSelectWindow());
	init_ui_window(new FriendWindow());
	init_ui_window(new PlayerTipsWindow());
	init_ui_window(new RankWindow());
	init_ui_window(new EmailWindow());
	init_ui_window(new PuCongWindow());
	init_ui_window(new NetObjectTipsWindow());
	init_ui_window(new EquipTipsWindow());
	init_ui_window(new WriteEmailWindow());
	init_ui_window(new ErrorTipsWindow());
	init_ui_window(new HelpWindow());
	init_ui_window(new MainTaskWindow());
	init_ui_window(new AnnouncementWindow());
	init_ui_window(new RechargeWindow());
	init_ui_window(new RechargeWarnWindow());
	init_ui_window(new LimitedActivityWindow());
	init_ui_window(new ForcePushTaskRewardWindow());
	init_ui_window(new VipWindow());
	init_ui_window(new MineAreaWindow());
	init_ui_window(new ActivityWindow());
	init_ui_window(new HeroAltarWindow());
	init_ui_window(new SpringView());
	init_ui_window(new HeroIllustratedWindow());
	//init_ui_window(new yingxiongtujianWindow());
	init_ui_window(new LessResourceWindow());
	init_ui_window(new HELeadershipLvUpWindow());
	init_ui_window(new HeroAdvancedWindow());

	init_ui_window(new GainHeroWindow());
	init_ui_window(new GainSoulDebriWindow());
	init_ui_window(new CheckLeadershipWindow());
	init_ui_window(new ArenaRewardWindow());
 
	init_ui_window(new FirstRechGiftWindow());
	init_ui_window(new NewEquipremindWindow());
	init_ui_window(new LevelUpRewardActivityWindow());
	init_ui_window(new ShopTipsWindow());
	init_ui_window(new HeroSoulWindow());
	 
	init_ui_window(new LoginActivityWindow());
	init_ui_window(new GrowupPlanWindow());
	init_ui_window(new BossScoreWindow());
	init_ui_window(new SoulTipsWindow());

	init_ui_window(new ExchangeActivityWindow());
	init_ui_window(new AppstoreWaitWindow());

	init_ui_window(new VipGiftWindow());
	init_ui_window(new GainCallItemWindow());
	init_ui_window(new TenCallWindow());
	init_ui_window(new TeamInfoWindow());
}