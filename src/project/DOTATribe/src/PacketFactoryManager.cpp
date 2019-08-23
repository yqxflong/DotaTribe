#include "../include/PacketFactoryManager.h"
#include "../include/LoggerSystem.h"
#include "../include/PacketFactory.h"
#include "../include/LoginPacket.h"
#include "../include/SCRoleInfoPacket.h"
#include "../include/SCChangeEquipPacket.h"
#include "../include/SCChangeSkinPacket.h"
#include "../include/SCOffEquipPacket.h"
#include "../include/SCAthleticsDataPacket.h"
#include "../include/LevelUpPacket.h"
#include "../include/MissionPacket.h"
#include "../include/CreateRoleRandomNamePacket.h"
#include "../include/AskForRoleInfoPacket.h"
#include "../include/UpdateMissionPacket.h"
#include "../include/SCChangeSkillsResultPacket.h"
#include "../include/MassacrePacket.h"
#include "../include/SCRefreshInfoDataPacket.h"
#include "../include/SCBagSaleObjectResultPacket.h"
#include "../include/RegisterAccountPacket.h"
#include "../include/SCBagUseObjectResultPacket.h"
#include "../include/SCServerMessagePacket.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/HeroTechnologyLevelUpPacket.h"
#include "../include/EquipmentLvUpPacket.h"
#include "../include/EquipmentLvUpSelectCardPacket.h"
#include "../include/ChatPacket.h"
#include "../include/ServerListPacket.h"
#include "../include/SCRolelistPacket.h"
#include "../include/SCRegisterAccountPacket.h"
#include "../include/SCQuickAccountRegisterPacket.h"
#include "../include/AttributeLockPacket.h"
#include "../include/EquipTrainPacket.h"
#include "../include/HeartBeatPacket.h"
#include "../include/SCShopInfoPacket.h"
#include "../include/ClimbTowerPacket.h"
#include "../include/GetItemPacket.h"
#include "../include/S2CArenaInfoPacket.h"
#include "../include/FullStarRewardPacket.h"
#include "../include/RevenuePacket.h"
#include "../include/CostRevenuePacket.h"
#include "../include/S2CQAPacket.h"
#include "../include/S2CAddChallengeCountPacket.h"
#include "../include/S2CRestSkillsPacket.h"
#include "../include/SCHeroAltarBuyItemPacket.h"
#include "../include/SCErrorTipsPacket.h"
#include "../include/TeamSelectPacket.h"
#include "../include/TeamBattlePacket.h"
#include "../include/FriendPacket.h"
#include "../include/FriendAddPacket.h"
#include "../include/FriendAgreeAllPacket.h"
#include "../include/FriendAgreeSinglePacket.h"
#include "../include/FriendIgnoreAllPacket.h"
#include "../include/FriendIgnoreSinglePacket.h"
#include "../include/FriendCheckPlayerInfoPacket.h"
#include "../include/FriendDeletePacket.h"
#include "../include/FriendFightPacket.h"
#include "../include/FriendFindFriendPacket.h"
#include "../include/FriendRefurbishPacket.h"
#include "../include/S2CArenaRankPacket.h"
#include "../include/EmailPacket.h"
#include "../include/S2CArenaGifPacket.h"
#include "../include/NetObjectTipsPacket.h"
#include "../include/ServantPacket.h"
#include "../include/VersionCheckPacket.h"
#include "../include/MainTaskPacket.h"
#include "../include/RestingTechnologyPointPacket.h"
#include "../include/PayGoodsPacket.h"
#include "../include/MiningPacket.h"
#include "../include/ActivityPacket.h"
#include "../include/AskForAddEnergyPacket.h"
#include "../include/HeroAltarPacket.h"
#include "../include/HeroSummonPacket.h"
#include "../include/LessResourcePacket.h"
#include "../include/CSHeroExpandInfoPacket.h"
#include "../include/CSHeroAdvancedPacket.h"
#include "../include/EquipPromotePacket.h" 
#include "../include/SCAnnoucementPacket.h" 
#include "../include/CheckRoleBaseInfoPacket.h"
#include "../include/MultiRewardPacket.h"
#include "../include/LimitActivityPacket.h"
#include "../include/LeadershipPacket.h"
#include "../include/VipInfoPacket.h"
#include "../include/FirstRechGiftPacket.h"
#include "../include/RandomShopPacket.h"
#include "../include/HeroSoulPacket.h"
#include "../include/SoulEquipPacket.h"
#include "../include/EquipCastPacket.h"
#include "../include/NoticeGatewayPacket.h"

#include "../include/LoginActivityPacket.h"
#include "../include/BossScorePacket.h"
#include "../include/GrowupPlanPacket.h"
#include "../include/PacketHelper.h"
#include "../include/LuaSystem.h"
#include "../include/VipGiftPacket.h"
#include "../include/CheckPlayerInfoPacket.h"
#include "../include/CheckOpenFun.h"
#include "../include/HeroteamChangePacket.h"
PacketFactoryManager::PacketFactoryManager()
{
	m_PacketFactoryList.clear();
}

PacketFactoryManager::~PacketFactoryManager()
{

}

void PacketFactoryManager::RegisterFactory(IPacketFactory* pPacketFactory)
{
	m_PacketFactoryList[pPacketFactory->GetPacketType()] = pPacketFactory;
}

IPacketFactory* PacketFactoryManager::GetPacketFactoryByType(unsigned int type)
{
	IPacketFactory* temp = NULL;
	std::map<int, IPacketFactory*>::iterator iter = m_PacketFactoryList.find(type);
	if (iter == m_PacketFactoryList.end())
	{
		if(LUASYSTEM->IsLuaPacket(type))
			temp = m_PacketFactoryList.find(_TYPE_PACKET_S2C_LUA_)->second;
	}
	else
	{
		temp = iter->second;
	}

	return temp;
}

bool  PacketFactoryManager::Init()
{
	RegisterFactory(new SCLoginPacketFactory());
	RegisterFactory(new SCNoticePacketFactory());
	RegisterFactory(new SCForceDisConnectPacketFactory());
	RegisterFactory(new SCRoleInfoPacketFactory());
	RegisterFactory(new SCChangeEquipPacketFactory());
	RegisterFactory(new SCChangeSkinPacketFactory());
	RegisterFactory(new SCOffEquipPacketFactory());
	RegisterFactory(new SCAthleticsDataPacketFactory());
	RegisterFactory(new S2CLevelUpPacketFactory());
	RegisterFactory(new S2CMissionPacketFactory());
	//RegisterFactory(new SCRefreshRoleInfoPacketFactory());//as protocol 2002 delete,this handler cannot be register.
	RegisterFactory(new S2CCreateRoleRandomNamePacketFactory());
	//RegisterFactory(new S2CAskForRoleInfoPacketFactory());
	RegisterFactory(new S2CUpdateMissionPacketFactory());
	RegisterFactory(new S2CMassacrePacketFactory());
	RegisterFactory(new SCRefreshInfoDataPacketFactory());
	RegisterFactory(new SCChangeSkillsResultPacketFactory());
	RegisterFactory(new SCBagSaleObjectResultPacketFactory());
	//RegisterFactory(new S2CRegisterAccountPacketFactory());
	RegisterFactory(new SCBagUseObjectResultPacketFactory());
	RegisterFactory(new SCServerMessagePacketFactory());
	RegisterFactory(new S2CHeroTechnologyPacketFactory());
	RegisterFactory(new S2CGetTechnologyPointPacketFactory());
	//RegisterFactory(new S2CAddTechnologyPointPacketFactory());
	RegisterFactory(new S2CHeroTechnologyLevelUpPacketFactory());
	RegisterFactory(new S2CFullStarRewardPacketFactory());
	RegisterFactory(new SCEquipmentLvUpPacketFactory());
	RegisterFactory(new SCEquipmentLvUpSelectCardPacketFactory());
	
	RegisterFactory(new SCHeartBeatResultPacketFactory());

	RegisterFactory(new S2CChatPacketFactory());

	RegisterFactory(new SCServerListPacketFactory());
	RegisterFactory(new SCRolelistPacketFactory());
	RegisterFactory(new SCRegisterAccountPacketFactory());
	RegisterFactory(new SCQuickAccountRegisterPacketFactory());
	RegisterFactory(new SCAttributeLockResultPacketFactory());
	RegisterFactory(new SCAttributeUnLockResultPacketFactory());
	RegisterFactory(new SCEquipTrainResultPacketFactory());
	RegisterFactory(new SCEquipTrainGetLockStatusResultPacketFactory());
	RegisterFactory(new SCShopInfoPacketFactory());
	RegisterFactory(new SCShopBuyPacketFactory());
	RegisterFactory(new SCEnterTowerResultPacketFactory());
	RegisterFactory(new SCStartTowerResultPacketFactory());
	RegisterFactory(new SCResetTowerResultPacketFactory());
	RegisterFactory(new SCTowerRankResultPacketFactory());
	RegisterFactory(new SCGetItemPacketFactory());
	RegisterFactory(new S2CArenaInfoPacketFactory());
	RegisterFactory(new S2CQAPacketFactory());
	RegisterFactory(new S2CAddChallengeCountPacketFactory());
	 

	RegisterFactory(new S2CRevenuePacketFactory());
	//RegisterFactory(new S2CCostRevenuePacketFactory());
	RegisterFactory(new S2CRestRoleSkillsPacketFactory());
	RegisterFactory(new SCHeroAltarBuyItemPacketFactory());
	
	
	RegisterFactory(new SCTeamBattleGetDataPacketFactory());
	RegisterFactory(new SCTeamBattleResetDataResultPacketFactory());
	RegisterFactory(new SCTeamSelectEnterResultPacketFactory());
	RegisterFactory(new SCTeamSelectGetListPacketFactory());
	RegisterFactory(new SCTeamSelectJoinTeamResultPacketFactory());
	RegisterFactory(new SCTeamSelectBeRemovedPacketFactory());
	RegisterFactory(new SCAskSlaveListResultPacketFactory());
	RegisterFactory(new SCAskMercenaryListResultPacketFactory());
	RegisterFactory(new SCTeamBattleGateRewardResultPacketFactory());

	RegisterFactory(new S2CFriendPacketFactory());
	RegisterFactory(new S2CUpdataFriendPacketFactory());
	RegisterFactory(new S2CFriendFindFriendPacketFactory());
	RegisterFactory(new S2CFriendAddPacketFactory());
	RegisterFactory(new S2CFriendAgreeAllPacketFactory());
	RegisterFactory(new S2CFriendAgreeSinglePacketFactory());
	RegisterFactory(new S2CFriendCheckPlayerInfoPacketFactory());
	RegisterFactory(new S2CFriendDeletePacketFactory());
	RegisterFactory(new S2CFriendFightPacketFactory());
	RegisterFactory(new S2CFriendIgnoreAllPacketFactory());
	RegisterFactory(new S2CFriendIgnoreSinglePacketFactory());
	RegisterFactory(new S2CFriendRefurbishPacketFactory());
	RegisterFactory(new S2CRestingTechnologyPointPacketFactory());
	RegisterFactory(new SCEmailListPacketFactory());
	RegisterFactory(new SCEmailSendPacketFactory());
	RegisterFactory(new SCGetEmailAttPacketFactory());
	RegisterFactory(new SCRemoveEmailPacketFactory());
	RegisterFactory(new S2CArenaGifPacketFactory());
	RegisterFactory(new SCNetObjectTipsResultPacketFactory());
	RegisterFactory(new SCCheckEmailPacketFactory());
	RegisterFactory(new SCMasterEnterCatchResultPacketFactory());
	RegisterFactory(new SCMasterEnterPlayResultPacketFactory());
	RegisterFactory(new SCMasterPlayResultPacketFactory());
	RegisterFactory(new SCMasterNewsPacketFactory());
	RegisterFactory(new SCMasterEnterRescueResultPacketFactory());
	RegisterFactory(new SCSlaveEnterRevoltResultPacketFactory());
	RegisterFactory(new SCSlaveBribeResultPacketFactory());
	RegisterFactory(new SCSlaveEnterPlayResultPacketFactory());
	RegisterFactory(new SCSlavePlayResultPacketFactory());
	RegisterFactory(new SCSlaveNewsPacketFactory());
	RegisterFactory(new SCSlaveEnterSOSResultPacketFactory());
	RegisterFactory(new SCQueryVersionPacketFactory());
	RegisterFactory(new SCErrorTipsPacketFactory());

	RegisterFactory(new SCEnterMainTaskResultPacketFactory());
	RegisterFactory(new SCTaskFinishReceiptPacketFactory());
	RegisterFactory(new SCPushTaskFinishRewardPacketFactory());

	RegisterFactory(new SCPayItemListPacketFactory());
	RegisterFactory(new SCPaySurePacketFactory());
	RegisterFactory(new SCLActivityPacketFactory());
	RegisterFactory(new SCLActivityGetAwardPacketFactory());

	RegisterFactory(new SCEnterMiningResultPacketFactory());
	RegisterFactory(new SCEnterGoblinResultPacketFactory());
	RegisterFactory(new SCStopMiningResultPacketFactory());
	RegisterFactory(new SCEnterDwarvenResultPacketFactory());
	RegisterFactory(new SCEnterDragonResultPacketFactory());
	RegisterFactory(new SCStartMiningResultPacketFactory());
	RegisterFactory(new SCEnterHuntResultPacketFactory());
	RegisterFactory(new SCHuntMiningResultPacketFactory());
	RegisterFactory(new SCHuntHelloMoneyResultPacketFactory());
	//RegisterFactory(new SCHuntBuyMineralResultPacketFactory());
	RegisterFactory(new SCHuntLieRenChaKanResultPacketFactory());
	RegisterFactory(new SCHuntLieRenQiangDuoResultPacketFactory());
	RegisterFactory(new SCDwarvenLootResultPacketFactory());

	RegisterFactory(new S2CAskForAddEnergyPacketFactory());
	RegisterFactory(new S2CBuyEnergyPacketFactory());
	RegisterFactory(new S2CCleanChallengeTimesPacketFactory());
	
	RegisterFactory(new S2CLessResourcePacketFactory());
	RegisterFactory(new S2CChioseLessResourcePacketFactory());
	
	RegisterFactory(new S2CActivityPacketFactory());
	RegisterFactory(new S2CInSpringPacketFactory()); 
	RegisterFactory(new S2CLevelUpRewardInfoPacketFactory());
	RegisterFactory(new S2CLevelUpRewardRecepitPacketFactory()); 
	 
	RegisterFactory(new SCHeroTotemInfoPacketFactory());

	RegisterFactory(new SCHeroAltarInfoPacketFactory());
	RegisterFactory(new SCHeroDebrisAltarPacketFactory());

	RegisterFactory(new SCHeroSummonInfoPacketFactory());
	RegisterFactory(new SCHeroSoulSummonPacketFactory());
	RegisterFactory(new SCHeroExpandInfoPacketFactory());
	 
	RegisterFactory(new SCLeadershipLvupPacketFactory());
	RegisterFactory(new SCReplaceHeroPacketFactory());

	RegisterFactory(new SCAltarCheckInfoTablePacketFactory());

	RegisterFactory(new SCHeroAdvancedPacketFactory());
    RegisterFactory(new SCHeroAdvanceVerifyPacketFactory());

	RegisterFactory(new SCTowerJewelResetResultPacketFactory());
	RegisterFactory(new SCTowerFastFightResultPacketFactory());
	RegisterFactory(new SCTowerRewardResultPacketFactory());
	RegisterFactory(new SCTowerGetRewardResultPacketFactory());

	RegisterFactory(new S2CEquipPromotePacketFactory());
	RegisterFactory(new S2CSurePromotePacketFactory());

	RegisterFactory(new SCVipInfoPacketFactory());
	RegisterFactory(new SCVipRewardPacketFactory());

	RegisterFactory(new SCBuyClimbTowerTimesPacketFactory());
	RegisterFactory(new SCBuyHuntTimesPacketFactory());
	RegisterFactory(new SCUserItemGainHeroPacketFactory());
	RegisterFactory(new SCAnnoucementPacketFactory());
	RegisterFactory(new SCCheckRoleBaseInfoPacketFactory());
	RegisterFactory(new S2CMultiRewardPacketFactory());
	RegisterFactory(new SCAndroidPayInfoPacketFactory());
	RegisterFactory(new S2CArenaRankPacketFactory());
	RegisterFactory(new S2CArenaRewardPacketFactory());
	RegisterFactory(new S2CChallenegeCountRewardPacketFactory());
	 
	RegisterFactory(new SCFirstRechInfoPacketFactory());
	RegisterFactory(new SCExchangePacketFactory());
	RegisterFactory(new SCGetFirstGiftPacketFactory());
	RegisterFactory(new SCRandomShopInfoPacketFactory());
	RegisterFactory(new SCRandomShopBuyPacketFactory());
	RegisterFactory(new SCRandomShopRefreshPacketFactory());
	RegisterFactory(new S2CHeroSoulInfoPacketFactory());
	RegisterFactory(new S2CActiveHeroSoulPacketFactory);
	RegisterFactory(new S2CUnLockHeroSoulPacketFactory);
	RegisterFactory(new S2CEquipHeroSoulPacketFactory);
	RegisterFactory(new S2CUnEquipHeroSoulPacketFactory);
	 

	RegisterFactory(new SCLoginActivityPacketFactory());
	RegisterFactory(new SCGetLoginRewardPacketFactory());

	RegisterFactory(new SCEnterBossScoreResultPacketFactory());
	RegisterFactory(new SCBossScoreRankResultPacketFactory());
	RegisterFactory(new SCBossScoreRewardResultPacketFactory());
	RegisterFactory(new SCBossScoreGetRewardResultPacketFactory());

	RegisterFactory(new SCGrowupPlanInfoPacketFactory());
	RegisterFactory(new SCBuyGrowupPlanPacketFactory());
	RegisterFactory(new SCGetGrowupPlanRewardPacketFactory());

	RegisterFactory(new S2CExchangeInfoPacketFactory());
	RegisterFactory(new S2CExchangeExchangePacketFactory());
	RegisterFactory(new SCEquipRecastInfoPacketFactory());
	RegisterFactory(new SCEquipRecastDoPacketFactory());

	RegisterFactory(new S2CSpringRewardPacketFactory());
	
	RegisterFactory(new PacketHelper_RecievedPacket());

	RegisterFactory(new S2CNoticeGatewayPacketFactory());
	RegisterFactory(new SCVipGiftInfoPacketFactory());
	RegisterFactory(new SCVipGiftBuyPacketFactory());

	RegisterFactory(new S2CCheckPlayerInfoPacketFactory());
	RegisterFactory(new S2CCheckOpenFunPacketFactory());

	RegisterFactory(new SCSCDoublePayInfoPacketFactory());

	RegisterFactory(new SCSCTenCallPacketFactory());

	RegisterFactory(new SCHeroteamChangePacketFactory());

	LOGGERSYSTEM->LogInfo("Init PacketFactoryManager Success\n");
	return true;
}

void  PacketFactoryManager::Tick()
{

}

void  PacketFactoryManager::Destroy()
{
	std::map<int, IPacketFactory*>::iterator iter   = m_PacketFactoryList.begin();
	std::map<int, IPacketFactory*>::iterator iter_e = m_PacketFactoryList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_PacketFactoryList.clear();

	LOGGERSYSTEM->LogInfo("Destroy PacketFactoryManager Success\n");
}
