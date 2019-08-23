//Name:ClimbTowerDataHandler.cpp
//Function:爬塔管理器
//Author:fangjun
//date:20130826

#include <cocos2d.h>
#include "../include/ClimbTowerDataHandler.h"
#include "../include/ClimbTowerPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/RankWindow.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/NFControlsManager.h"

TowerTodayReward::TowerTodayReward()
{
	type = 0;
	iconId = 0;
	quality = 0;
	templateId = 0;
	name = "";
	rewardFloor = 0;
	count = 0;
	status = 0;
}

void TowerTodayReward::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>type;
	if(type == 0)
	{
		packet>>iconId;
		packet>>quality;
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
	}
	packet.read(rewardFloor);
	packet>>count;
	packet>>status;
}

void TowerReward::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>iconId;
	packet>>quality;
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

	packet>>rewardFloor;
	packet>>status;
}



TowerRewardData::TowerRewardData()
{
	destroyData();
}
TowerRewardData::~TowerRewardData()
{
	destroyData();
}
void TowerRewardData::destroyData()
{
	for(int i = 0; i < (int)todayRewardVector.size(); ++i)
	{
		delete todayRewardVector[i];
		todayRewardVector[i] = NULL;
	}
	todayRewardVector.clear();

	for(int i = 0; i < (int)towerRewardVector.size(); ++i)
	{
		delete towerRewardVector[i];
		towerRewardVector[i] = NULL;
	}
	towerRewardVector.clear();

}

void TowerRewardData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	packet.read(topFloor);
	packet>>rank;
	packet.read(curFloor);

	unsigned short count = 0;
	TowerTodayReward * today = NULL;
	packet>>count;
	for(unsigned int i = 0; i < count; ++i)
	{
		today = new TowerTodayReward();
		today->decodePacketData(packet);
		todayRewardVector.push_back(today);
	}

	TowerReward * reward = NULL;
	packet>>count;
	for(unsigned int i = 0; i < count; ++i)
	{
		reward = new TowerReward();
		reward->decodePacketData(packet);
		towerRewardVector.push_back(reward);
	}
}

TowerReward * TowerRewardData::getFirstUnOpenTowerReward()
{
	TowerReward * rr = NULL;
	int i = 0;
	while(1)
	{
		if(i >= towerRewardVector.size())
		{
			break;
		}
		if(towerRewardVector[i]->status == 1)
		{
			rr = towerRewardVector[i];
			break;
		}

		++i;
	}

	return rr;
}

void TowerFastFightResultItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>result;
	packet.read(fightFloor);
	packet>>gotExp;
	packet>>gotHonor;
}

TowerFastFightResultData::TowerFastFightResultData()
{
	destroyData();
}
TowerFastFightResultData::~TowerFastFightResultData()
{
	destroyData();
}
void TowerFastFightResultData::destroyData()
{
	for(int i = 0; i < (int)resultData.size(); ++i)
	{
		delete resultData[i];
		resultData[i] = NULL;
	}
	resultData.clear();
}


void TowerSkillItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>skillId;
	packet>>iconId;
}

EnterData::~EnterData()
{
	destroyData();
}

void EnterData::destroyData()
{
	std::vector<TowerSkillItem *>::iterator it= skillData.begin();
	std::vector<TowerSkillItem *>::iterator it_e= skillData.end();
	for(; it != it_e; ++it)
	{
		if(*it != NULL)
		{
			delete *it;
			*it = NULL;
		}
	}

	skillData.clear();
}

void EnterData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();//先清空数据

	packet>>entertype;
	if(0 == entertype)//首次
	{
		packet.read(defaultfloor);
		packet>>usedTimes;
		packet>>maxTimes;
	}

	packet.read(nowfloor);
	packet>>gotmoney;
	packet>>gotexp;
	packet>>nextmoney;
	packet>>nextexp;

	if(nextmoney == -1)
	{
		nextmoney = 0;
	}
	if(nextexp == -1)
	{
		nextexp = 0;
	}

	char count = 0;
	packet>>count;
	for(int i = 0; i < count; ++i)
	{
		TowerSkillItem * item = new TowerSkillItem();
		item->decodePacketData(packet);
		skillData.push_back(item);
	}

	packet>>rankNum;
	packet>>honor;
	packet>>jewelResetPrice;
	packet>>fastFightPrice;
	
	packet>>haveFloorReward;
	packet.read(leftChallengeTime);

	CLIMBTOWERDATAHANDLER->iPreFloor = CLIMBTOWERDATAHANDLER->iCurFloor;
	CLIMBTOWERDATAHANDLER->iCurFloor = nowfloor;//当前英雄所站的层

}

void TowerRankItem::decodePacketData(cobra_win::DPacket & packet)
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

	packet.read(level);
	packet>>score;
	packet>>floor;
}

void TowerRankList::destroyData()
{
	TowerRankItem * item = NULL;
	int size = rankVector.size();
	for(int i = 0; i < size; ++i)
	{
		item = rankVector[i];
		delete item;
		item = NULL;
	}
	rankVector.clear();
}

TowerRankList::TowerRankList()
{
	rankVector.clear();
}
TowerRankList::~TowerRankList()
{
	destroyData();
}
void TowerRankList::decodePacketData(cobra_win::DPacket & packet)
{
	unsigned short count = 0;
	packet>>count;

	TowerRankItem * item = NULL;
	for(int i = 0; i < count; ++i)
	{
		item = new TowerRankItem();
		item->decodePacketData(packet);
		rankVector.push_back(item);
	}
}


ClimbTowerDataHandler::ClimbTowerDataHandler()
{
	iCurFloor = -1;
	iPreFloor = -1;
	fightResult = 0;

	m_pFastFightResultData = NULL;

	m_pRankList = NULL;
	m_pRewardData = NULL;
}

ClimbTowerDataHandler::~ClimbTowerDataHandler()
{
	if(m_pRankList!=NULL)
	{ 
		delete m_pRankList;
		m_pRankList=NULL;
	}

	if(!m_pFastFightResultData)
	{
		delete m_pFastFightResultData;
		m_pFastFightResultData = NULL;
	}

	if(m_pRewardData != NULL)
	{
		delete m_pRewardData;
		m_pRewardData = NULL;
	}
}

void ClimbTowerDataHandler::onDestroy()
{
	if(!m_pFastFightResultData)
	{
		delete m_pFastFightResultData;
		m_pFastFightResultData = NULL;
	}

	if(m_pRewardData != NULL)
	{
		delete m_pRewardData;
		m_pRewardData = NULL;
	}

	if(m_pRankList != NULL)
	{
		delete m_pRankList;
		m_pRankList = NULL;
	}
}

//进入恶魔塔
void ClimbTowerDataHandler::ToServerEnterTower()
{
	CSEnterTowerPacket packet;
	packet.Send();

}

void ClimbTowerDataHandler::ToClientEnterTowerResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERTOWER_RESULT_);
}

void ClimbTowerDataHandler::ToServerStartTower()
{
	CSStartTowerPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}
void ClimbTowerDataHandler::ToClientStartTowerResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_START_TOWER_TIMES_);
}

//挑战关卡
void ClimbTowerDataHandler::ToServerChallengeTower()
{
	CSChallengeTowerPacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID());
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientChallengeTowerResult()
{
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_CHALLENGETOWER_RESULT);

}

//重置爬塔记录
void ClimbTowerDataHandler::ToServerResetTower()
{
	CSResetTowerPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientResetTowerResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_RESETTOWER_RESULT_);
}

void ClimbTowerDataHandler::ToServerRankList()
{
	CSTowerRankPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientRankListResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_RANKWINDOW_, _to_event_param_(RankWindow::_RANK_TYPE_TOWER_));

	NFC_showCommunicationWating(false);
}

void ClimbTowerDataHandler::ToServerFastFight()
{
	if(m_pRewardData)
	{
		delete m_pRewardData;
		m_pRewardData = NULL;
	}

	CSTowerFastFightPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientFastFightWinResult()
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_FASTFIGHT_GETDATA_);
}

void ClimbTowerDataHandler::ToServerJewelReset()
{
	CSTowerJewelResetPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientJewelResetResult()
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_JEWELRESET_GETDATA_);
}

void ClimbTowerDataHandler::ToServerEnterReward()
{
	CSTowerRewardPacket pa;
	pa.Send();
	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientEnterRewardResult()
{
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_REWARD_GETDATA_);
}

void ClimbTowerDataHandler::ToServerGetReward(char type, unsigned short floor)
{
	CSTowerGetRewardPacket pa(type, floor);
	pa.Send();
	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientGetRewardResult(char type, unsigned short floor)
{
	NFC_showCommunicationWating(false);
	int idx = 0;
	if(type == 0)
	{
		idx = m_pRewardData->todayRewardVector.size();
		while(1)
		{
			if(idx == 0)
				break;
			if(m_pRewardData->todayRewardVector[--idx]->rewardFloor == floor)
			{
				m_pRewardData->todayRewardVector[idx]->status = 0;//设置已领取
				break;
			}
		}
	}
	else
	{
		idx = m_pRewardData->towerRewardVector.size();
		while(1)
		{
			if(idx == 0)
				break;
			if(m_pRewardData->towerRewardVector[--idx]->rewardFloor == floor)
			{
				m_pRewardData->towerRewardVector[idx]->status = 0;//设置已领取
				break;
			}
		}
	}

	//此处需要判断是否所有奖励均已领取，并且设置塔数据奖励领取
	int i = 0;
	for(; i < m_pRewardData->todayRewardVector.size(); ++i)
	{
		if(m_pRewardData->todayRewardVector[i]->status == 1)
			break;
	}
	if(i == m_pRewardData->todayRewardVector.size())
		enterData.haveFloorReward = 0;


	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_GETREWARD_GETDATA_, _to_event_param_((int)type), _to_event_param_((int)idx));
}

void ClimbTowerDataHandler::ToServerBuyClimbTowerTimes()
{
	CSBuyClimbTowerTimesPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void ClimbTowerDataHandler::ToClientBuyClimbTowerTimesResult()
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BUYCLIMBTOWERTIMES_GETDATA_);
}

//计算是否有免费次数
// bool ClimbTowerDataHandler::HasFreeTimes()
// {
// 	bool b = false;
// 	if(enterData.maxfreetimes - enterData.freetimes > 0)
// 	{
// 		b = true;
// 	}
// 
// 	return b;
// }

//计算是否有道具次数
// bool ClimbTowerDataHandler::HasPayTimes()
// {
// 	bool b = false;
// 
// 	if(enterData.maxpaytimes - enterData.paytimes > 0)
// 	{
// 		b = true;
// 	}
// 
// 	return b;
// }

