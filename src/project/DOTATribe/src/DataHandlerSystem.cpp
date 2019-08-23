#include <cocos2d.h>
#include "../include/DataHandlerSystem.h"
#include "../include/LoggerSystem.h"
//
#include "../include/RoleInfoDataHandler.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/AthleticProcedureDataHandler.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/CreateRoleRandomNameDataHandler.h"
#include "../include/MassacreDataHandler.h"
#include "../include/BagTemplateBaseHandler.h"
#include "../include/HeroTechnologyDataHandler.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/HeartBeatDataHandler.h"
#include "../include/ChatDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/EquipTrainDataHandler.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/EffectDataHandler.h"
#include "../include/ShopInfoDataHandler.h"
#include "../include/ArenaInfoDataHandler.h"
#include "../include/QADataHandler.h"
#include "../include/ClearCoolTimeDataHandler.h"
#include "../include/AddChallengeDataHandler.h"
#include "../include/PESEquipDataHandler.h"
#include "../include/BagWindowDataHandler.h"
#include "../include/RevenueDataHandler.h"
#include "../include/TeamBattleDataHandler.h"
#include "../include/FriendDataHandler.h"
#include "../include/ArenaRankDataHandler.h"
#include "../include/EmailDataHandler.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/ServantDataHandler.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/LimitedActivityHandler.h"
#include "../include/ActivityDataHandler.h"
#include "../include/MiningDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/HeroIllustratedDataHandler.h"
#include "../include/HeroAdvancedDataHandler.h"
#include "../include/EquipPromoteDataHandler.h"
#include "../include/EquipStrengthenDataHandler.h"
#include "../include/VipControlDataHandler.h"
#include "../include/AnnouncementDataHandler.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/HeroSoulDataHandler.h"
  
#include "../include/LessResourceDataHandler.h"
#include "../include/MultiRewardDataHandler.h" 
#include "../include/ShopTipsDataHandler.h"
#include "../include/RoleSoulsDataHandler.h"

#include "../include/EquipRecastDataHandler.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/ShareDataHandler.h"

template<> DataHandlerSystem* cobra_win::Singleton2<DataHandlerSystem>::m_pMySelf = NULL;

DataHandlerSystem::DataHandlerSystem()
{
	m_DataHandlerList.clear();
}

DataHandlerSystem::~DataHandlerSystem()
{

}

void DataHandlerSystem::RegisterDataManager(IDataHandler* pDataHandler)
{
	assert(pDataHandler != NULL);

	m_DataHandlerList.push_back(pDataHandler);
}

bool DataHandlerSystem::Init()
{
	// 注册数据管理器
	RegisterDataManager(new RoleInfoDataHandler());
	RegisterDataManager(new BagEquipDataHandler());
	RegisterDataManager(new BagOtherObjectHandler());
	RegisterDataManager(new AthleticProcedureDataHandler());
	RegisterDataManager(new LevelUpDataHandler());
	RegisterDataManager(new MissionDataHandler());
	RegisterDataManager(new CreateRoleRandomNameDataHandler());
	RegisterDataManager(new MassacreDataHandler());
	RegisterDataManager(new BagTemplateBaseHandler());
	RegisterDataManager(new HeroTechnologyDataHandler());
	RegisterDataManager(new EquipmentLvUpDataHandler());
	RegisterDataManager(new HeartBeatDataHandler());
	RegisterDataManager(new ChatDataHandler());
	RegisterDataManager(new ServerInfoDataHandler());
	RegisterDataManager(new EquipTrainDataHandler());
	RegisterDataManager(new ClimbTowerDataHandler());
	RegisterDataManager(new EffectDataHandler());
	RegisterDataManager(new ShopInfoDataHandler());
	RegisterDataManager(new RandomShopDataHandler());
	RegisterDataManager(new ArenaInfoDataHandler());
	RegisterDataManager(new QADataHandler());
	RegisterDataManager(new ClearCoolTimeDataHandler());
	RegisterDataManager(new AddChallengeDataHandler());
	RegisterDataManager(new BagWindowDataHandler());
	RegisterDataManager(new RevenueDataHandler());
	RegisterDataManager(new TeamBattleDataHandler());
	RegisterDataManager(new FriendDataHandler());
	RegisterDataManager(new PESEquipDataHandler());
	RegisterDataManager(new ArenaRankDataHandler());
	RegisterDataManager(new EmailDataHandler());
	RegisterDataManager(new NetObjectTipsDataHandler());
	RegisterDataManager(new ServantDataHandler());
	RegisterDataManager(new MainTaskDataHandler());
	RegisterDataManager(new PayGoodsControlDataHandler());
	RegisterDataManager(new LimitedActivityHandler());
	RegisterDataManager(new ActivityDataHandler());
	RegisterDataManager(new MiningDataHandler());
	RegisterDataManager(new RoleHeroSkinsDataHandler());
	RegisterDataManager(new HeroAltarControlDataHandler());
	RegisterDataManager(new HeroSummonControlDataHandler());
	RegisterDataManager(new HeroIllustratedDataHandler());
	RegisterDataManager(new HeroAdvancedDataHandler());
	RegisterDataManager(new EquipPromoteDataHandler());
	RegisterDataManager(new EquipStrengthenDataHandler());
	RegisterDataManager(new VipControlDataHandler());
 
	RegisterDataManager(new LessResourceDataHandler());
	RegisterDataManager(new MultiRewardDataHandler());
	RegisterDataManager(new LeadershipHandler());
	RegisterDataManager(new CheckRoleBaseInfoHandler());
	RegisterDataManager(new AnnoucementDataHandler());
	RegisterDataManager(new ArenaRewardDataHandler());
	RegisterDataManager(new FirstRechDataHandler());
	RegisterDataManager(new LevelUpRewardActivityDataHandler());
	 
	RegisterDataManager(new HeroSoulDataHandler());
	  
	RegisterDataManager(new NewEquipremindDataHandler());
	RegisterDataManager(new ShopTipsDataHandler());
	RegisterDataManager(new RoleSoulsDataHandler());
	RegisterDataManager(new LoginRewardDataHandler());
	RegisterDataManager(new SpringActivityDataHandler());

	 

	RegisterDataManager(new BossScoreDataHandler());
	RegisterDataManager(new GrowupPlanDataHandler());

	RegisterDataManager(new ExchangeActivityDataHandler());
	RegisterDataManager(new EquipRecastDataHandler());
	RegisterDataManager(new VipGiftActivityHandler());
	RegisterDataManager(new ShareDataHandler());
	 

	// 初始化所有的数据管理器
	std::list<IDataHandler*>::iterator iter   = m_DataHandlerList.begin();
	std::list<IDataHandler*>::iterator iter_e = m_DataHandlerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (!(*iter)->init())
		{
			LOGGERSYSTEM->LogFatal("Init DataHandlerSystem Failed");
			return false;
		}
	}

	return true;
}

void DataHandlerSystem::Tick()
{
}

void DataHandlerSystem::Destroy()
{
	//DestroyAllDataHandler();
	std::list<IDataHandler*>::iterator iter   = m_DataHandlerList.begin();
	std::list<IDataHandler*>::iterator iter_e = m_DataHandlerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		(*iter)->onDestroy();
		delete (*iter);
	}

	m_DataHandlerList.clear();
}

	/*
		销毁所有数据handler
	*/
void DataHandlerSystem::DestroyAllDataHandler(){
	std::list<IDataHandler*>::iterator iter   = m_DataHandlerList.begin();
	std::list<IDataHandler*>::iterator iter_e = m_DataHandlerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		(*iter)->onDestroy();
	}
}
