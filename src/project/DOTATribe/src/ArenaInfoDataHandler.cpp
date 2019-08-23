#include   <cocos2d.h>
#include   "../include/ArenaInfoDataHandler.h"
 

/*
挑战目标结点
*/
void ChallgeNode::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceID);
	NFC_ParsePacketString(packet,name);
	packet.read(level);
	packet.read(iconID);
	packet.read(btlCapacity);
	packet.read(rank);

}

/*
历史战斗记录结点
*/
void HistoryArenaNode::decodePacketData(cobra_win::DPacket & packet)
{
 	packet.read(battleID);
	packet.read(distime);  //单位毫妙
	distime/=1000;
	packet.read(sourceID);
	NFC_ParsePacketString(packet,sourceName);
	packet.read(sourceRank);
	packet.read(targetID);
	NFC_ParsePacketString(packet,targetName);
	packet.read(targetRank);
	packet.read(isWin);
  
}

/*
竞技场信息数据
*/
void ArenaInfoData::decodePacketData(cobra_win::DPacket & packet)
{ 
    packet.read(winCount);
	packet.read(loseCount);
	packet.read(leftChallengeCount); 
	packet.read(historyArenaCount); 
	COMMON_BEIGIN_ARRAY(IByte,historyArenaCount)
		PHistoryArenaNode pHistoryArene=new HistoryArenaNode();
		if(pHistoryArene)
		{
			pHistoryArene->decodePacketData(packet);
			historyArenaList.push_back(pHistoryArene);
		}
	COMMON_END_ARRAY
		 
	packet.read(challengeEnemyCount); 
	COMMON_BEIGIN_ARRAY(IByte,challengeEnemyCount)
		PChallgeNode pChangeNode=new ChallgeNode();
		if(pChangeNode)
		{
			pChangeNode->decodePacketData(packet);
			challgeList.push_back(pChangeNode);
		} 
	COMMON_END_ARRAY
		 
}


template<> ArenaInfoDataHandler * cobra_win::Singleton2<ArenaInfoDataHandler>::m_pMySelf = NULL;

ArenaInfoDataHandler::ArenaInfoDataHandler()
{
	init();	
}

ArenaInfoDataHandler::~ArenaInfoDataHandler()
{
	if(PArenaInfoData!=NULL)
	{
		PArenaInfoData->destroy();
		delete PArenaInfoData;
		PArenaInfoData=NULL;
	} 
}

bool ArenaInfoDataHandler::init()
{
	 PArenaInfoData=NULL;
	 return true;
}
 
void  ArenaInfoDataHandler::onDestroy()
{ 
	//to do
}
  
void ArenaInfoDataHandler::handlePacket(IPacket* packet)
{
	//to do
}
 
void  ArenaInfoDataHandler::decodeLastArenaTime(cobra_win::DPacket & packetData)
{ 
	int lastArenaTime = 0;
	packetData.read(lastArenaTime);
	if(PArenaInfoData)
	{
		PArenaInfoData->leftChallengeCount = (short)lastArenaTime;
	} 
	EventSystem::get_instance2()->PushEvent2(_TYPEF_EVENT_UPDATE_ARENEWINDOW_,_to_event_param_(0));
}


//////////////////////////////////////////////////////////////////////////

 
void ChallengeRewardData::decodePacketData(cobra_win::DPacket & packet)
{
	IByte  rewardGotValue = 0;
	packet.read(rewardGotValue);
	rewardHadGot = rewardGotValue > 0 ? true:false;
	packet.read(rewardChanllengeCount);
	if(rewardItemData)
	rewardItemData->decodePacketData(packet);
}

ArenaRewardData::ArenaRewardData()
{
	m_nLastArenaRank = 0;
	m_arenaChallengeCount=0;
	m_arenaHadReward=false;
	m_arenaGetRewardDistance=0;
	m_arenaRankRewardVector.clear();
	m_arenaChallengeRewardVector.clear();
}

ArenaRewardData::~ArenaRewardData()
{
	size_t vectorSize = m_arenaRankRewardVector.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorSize)
		delete m_arenaRankRewardVector.at(index);
	COMMON_END_ARRAY
	m_arenaRankRewardVector.clear();

	vectorSize = m_arenaChallengeRewardVector.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorSize)
		delete m_arenaChallengeRewardVector.at(index);
	COMMON_END_ARRAY
	m_arenaChallengeRewardVector.clear();
}

void ArenaRewardData::decodePacketData(cobra_win::DPacket & packet)
{
	 packet.read(m_arenaChallengeCount);
	 packet.read(m_nLastArenaRank);
	 IByte  hasReward = 0;
	 packet.read(hasReward);
	 m_arenaHadReward = hasReward >0 ? true :false;
	 packet.read(m_arenaGetRewardDistance);
	 m_arenaGetRewardDistance /= 1000;
	 IByte vectorSize=0;
	 packet.read(vectorSize);
	 COMMON_BEIGIN_ARRAY(IByte,vectorSize)
		 PRewardItemNode pRankDataItem=new RewardItemNode();
	     pRankDataItem->decodePacketData(packet);
		 m_arenaRankRewardVector.push_back(pRankDataItem);
	 COMMON_END_ARRAY

	packet.read(vectorSize);
	COMMON_BEIGIN_ARRAY(IByte,vectorSize)
	     PChallengeRewardData pChallengeRewardData=new ChallengeRewardData();
	     pChallengeRewardData->decodePacketData(packet);
	     m_arenaChallengeRewardVector.push_back(pChallengeRewardData);
	COMMON_END_ARRAY
		  
}


//////////////////////////////////////////////////////////////////////////

ArenaRewardDataHandler::ArenaRewardDataHandler()
{
	m_ArenaRewardData=NULL;
}

ArenaRewardDataHandler::~ArenaRewardDataHandler()
{
	if(m_ArenaRewardData)
	{
		delete m_ArenaRewardData;
		m_ArenaRewardData=NULL;
	}
}

void ArenaRewardDataHandler::handlePacket(IPacket* packet)
{ 
}

void ArenaRewardDataHandler::onDestroy()
{ 
}

void  ArenaRewardDataHandler::decodePacketData(cobra_win::DPacket & packetData)
{ 
	 if(m_ArenaRewardData)
	 {
		 delete m_ArenaRewardData;
		 m_ArenaRewardData=NULL;
	 }
	 m_ArenaRewardData=new ArenaRewardData();
	 m_ArenaRewardData->decodePacketData(packetData); 
}
 
bool  ArenaRewardDataHandler::init()
{
   return true;
}
