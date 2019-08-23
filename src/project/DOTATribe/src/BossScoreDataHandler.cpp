//Name:BoseScoreDataHandler.h
//Function:Boss积分系统
//Author:fangjun
//date:20140215

#include "../include/BossScorePacket.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"


void BSScoreRewardItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>index;
	packet>>minScore;
	packet>>type;
	packet>>count;
	if(type == 0)
	{
		packet>>catogory;
		packet>>templateId;

		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		name.assign(str);
		delete[] str;
		str = NULL;

		packet>>quality;
		packet>>iconId;
	}
	
	packet>>status;
}

void BSRankRewardItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>type;
	packet>>count;
	if(type == 0)
	{
		packet>>catogory;
		packet>>templateId;

		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		name.assign(str);
		delete[] str;
		str = NULL;

		packet>>quality;
		packet>>iconId;
	}

}


BSRewardData::BSRewardData()
{
	destroyData();
}
BSRewardData::~BSRewardData()
{
	destroyData();
}
void BSRewardData::destroyData()
{
	for(unsigned int i = 0; i < scoreRewardVector.size(); ++i)
	{
		delete scoreRewardVector[i];
	}
	scoreRewardVector.clear();

	for(unsigned int i = 0; i < rankRewardVector.size(); ++i)
	{
		delete rankRewardVector[i];
	}
	rankRewardVector.clear();

}

void BSRewardData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	packet>>maxScore;
	packet.read(rank);
	char count = 0;
	packet>>count;
	BSScoreRewardItem * sitem = NULL;
	for (char i = 0; i < count; ++i)
	{
		sitem = new BSScoreRewardItem();
		sitem->decodePacketData(packet);
		scoreRewardVector.push_back(sitem);
	}
	packet>>leftDrawSeconds;
	packet>>count;
	BSRankRewardItem * ritem = NULL;
	for (char i = 0; i < count; ++i)
	{
		ritem = new BSRankRewardItem();
		ritem->decodePacketData(packet);
		rankRewardVector.push_back(ritem);
	}
}

void BSRankItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;

	packet>>score;
	packet.read(rank);
	packet.read(level);
}

BSRankList::BSRankList()
{
	destroyData();
}
BSRankList::~BSRankList()
{
	destroyData();
}
void BSRankList::destroyData()
{
	for(unsigned int i = 0; i < rankVector.size(); ++i)
	{
		delete rankVector[i];
	}
	rankVector.clear();
}
void BSRankList::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	short count = 0;
	packet.read(count);
	BSRankItem * item = NULL;
	for(short i = 0; i < count; ++i)
	{
		item = new BSRankItem();
		item->decodePacketData(packet);
		rankVector.push_back(item);
	}
}


void BSBossInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>quality;
	packet>>iconId;
}

BSBossScoreData::BSBossScoreData()
{
	destroyData();
}
BSBossScoreData::~BSBossScoreData()
{
	destroyData();
}
void BSBossScoreData::destroyData()
{
	hasReward = 0;

	for(unsigned int i = 0; i < bossVector.size(); ++i)
	{
		delete bossVector[i];
	}
	bossVector.clear();

	nameVector.clear();
	scoreVector.clear();
}
void BSBossScoreData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	description.assign(str);
	delete[] str;
	str = NULL;

	packet>>status;
	packet>>leftSeconds;
	char count = 0;
	packet>>count;
	BSBossInfo * inf = NULL;
	for(char i = 0; i < count; ++i)
	{
		inf = new BSBossInfo;
		inf->decodePacketData(packet);
		bossVector.push_back(inf);
	}

	packet>>maxScore;
	packet.read(rank);
	packet.read(leftFreeTimes);
	packet.read(leftChallengeItemCount);
	packet.read(challengePrice);

	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		std::string nametemp = "";

		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		nametemp.assign(str);
		delete[] str;
		str = NULL;

		nameVector.push_back(nametemp);
	}

	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		int score = 0;
		packet>>score;
		scoreVector.push_back(score);
	}
	packet>>hasReward;
}

BossScoreDataHandler::BossScoreDataHandler()
{
	m_pBossScoreData = NULL;
	m_pRankList = NULL;
	m_pRewardData = NULL;
	m_iFreeTimesSync = 0;
}

BossScoreDataHandler::~BossScoreDataHandler()
{
	if(m_pBossScoreData)
	{
		delete m_pBossScoreData;
		m_pBossScoreData = NULL;
	}

	if(m_pRankList)
	{
		delete m_pRankList;
		m_pRankList = NULL;
	}

	if(m_pRewardData)
	{
		delete m_pRewardData;
		m_pRewardData = NULL;
	}


	m_iFreeTimesSync = 0;
}

void BossScoreDataHandler::onDestroy()
{

	m_iFreeTimesSync = 0;
}

void BossScoreDataHandler::OnAthleticEnd(int stageID, bool win)
{
	//ToServerEnterBoss();
}

//进入世界boss
void BossScoreDataHandler::ToServerEnterBoss()
{
	NFC_showCommunicationWating(true);
	CSEnterBossScorePacket pa;
	pa.Send();
}
void BossScoreDataHandler::ToClientEnterBossResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BOSS_ENTER_GETDATA_);
	NFC_showCommunicationWating(false);
}

//进入排行榜
void BossScoreDataHandler::ToServerEnterRank()
{
	NFC_showCommunicationWating(true);
	CSBossScoreRankPacket pa;
	pa.Send();
}
void BossScoreDataHandler::ToClientEnterRankResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BOSS_RANK_GETDATA_);
	NFC_showCommunicationWating(false);
}

//进入宝箱奖励
void BossScoreDataHandler::ToServerEnterReward()
{
	NFC_showCommunicationWating(true);
	CSBossScoreRewardPacket pa;
	pa.Send();
}
void BossScoreDataHandler::ToClientEnterRewardResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BOSS_REWARD_GETDATA_);
	NFC_showCommunicationWating(false);
}

//开始挑战
void BossScoreDataHandler::ToServerChallenge()
{
	NFC_showCommunicationWating(true);
	CSBossScoreChallengePacket pa;
	pa.Send();
}

//领取奖励
void BossScoreDataHandler::ToServerGetReward(char type, char index)
{
	NFC_showCommunicationWating(true);
	CSBossScoreGetRewardPacket pa(type, index);
	pa.Send();
}
void BossScoreDataHandler::ToClientGetRewardResult(char type, char index)
{
	if(type == 0)
	{//积分奖励
		unsigned int sz = m_pRewardData->scoreRewardVector.size();
		while(1)
		{
			if(sz == 0)
				break;
			if(m_pRewardData->scoreRewardVector[--sz]->index == index)
			{
				m_pRewardData->scoreRewardVector[sz]->status = 0;//设置已领取
				break;
			}
		}
	}
	else if(type == 1)
	{//排名奖励
		m_pRewardData->leftDrawSeconds = -1;
	}

	//检查是否还有奖励
	bool has = false;
	unsigned int i = 0;
	for(; i < m_pRewardData->scoreRewardVector.size(); ++i)
	{
		if(m_pRewardData->scoreRewardVector[i]->status == 1)
			break;
	}
	if(i < m_pRewardData->scoreRewardVector.size())
	{
		has = has || true;
	}

// 	unsigned int j = 0;
// 	for(; j < m_pRewardData->rankRewardVector.size(); ++j)
// 	{
// 		if(m_pRewardData->leftDrawSeconds == 0)
// 			break;
// 	}
// 	if(j < m_pRewardData->rankRewardVector.size())
// 	{
// 		has = has || true;
// 	}

	if(m_pRewardData->leftDrawSeconds == 0)
	{
		has = has || true;
	}

	if(has)
	{
		m_pBossScoreData->hasReward = 1;
	}
	else
	{
		m_pBossScoreData->hasReward = 0;
	}


	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BOSS_LINGQU_GETDATA_, _to_event_param_((int)type), _to_event_param_((int)index));
	NFC_showCommunicationWating(false);
}
