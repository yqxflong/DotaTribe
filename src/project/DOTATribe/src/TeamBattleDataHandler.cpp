//Name:TeamBattleDataHandler.cpp
//Function:组队副本
//Author:fangjun
//date:20130922

#include "cocos2d.h"
#include "../include/TeamBattleDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/TeamSelectPacket.h"
#include "../include/TeamBattlePacket.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CheckPlayerInfoPacket.h"
#include "../include/NFControlsManager.h"

void TMercenaryItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	skinName.assign(str);
	delete[] str;
	str = NULL;

	char enhanceLevel = 0;
	packet>>enhanceLevel;
	packet>>btlCapa;

	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	playerName.assign(str);
	delete[] str;
	str = NULL;

	packet>>hirePrice;
	packet>>pvpRank;
	packet.read(playerLevel);
}

TMercenaryList::TMercenaryList()
{
	destroyData();
}

TMercenaryList::~TMercenaryList()
{
	destroyData();
}

void TMercenaryList::destroyData()
{
	for(unsigned int i = 0; i < mercenaryVector.size(); ++i)
	{
		delete mercenaryVector[i];
		mercenaryVector[i] = NULL;
	}
	mercenaryVector.clear();
}

void TMercenaryList::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	char count = 0;
	packet>>count;
	TMercenaryItem * item = NULL;
	for(int i = 0; i < count; ++i)
	{
		item = new TMercenaryItem();
		item->decodePacketData(packet);
		mercenaryVector.push_back(item);
	}
}

void TSlaveItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	skinName.assign(str);
	delete[] str;
	str = NULL;


	char enhanceLevel = 0;
	packet>>enhanceLevel;

	packet>>btlCapa;

	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	playerName.assign(str);
	delete[] str;
	str = NULL;

	packet.read(leftMinute);
	packet.read(playerLevel);
}

TSlaveList::TSlaveList()
{
	destroyData();
}

TSlaveList::~TSlaveList()
{
	destroyData();
}

void TSlaveList::destroyData()
{
	for(unsigned int i = 0; i < slaveVector.size(); ++i)
	{
		delete slaveVector[i];
		slaveVector[i] = NULL;
	}
	slaveVector.clear();
}

void TSlaveList::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	char count = 0;
	packet>>count;
	TSlaveItem * item = NULL;
	for(int i = 0; i < count; ++i)
	{
		item = new TSlaveItem();
		item->decodePacketData(packet);
		slaveVector.push_back(item);
	}
}

void TRewardItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>iconId;
	packet>>catogory;
	packet>>quality;
	packet>>templateId;
}

void TGateItem::destroyData()
{
	TRewardItem * ri = NULL;
	int size = rewardVector.size();
	for(int i = 0; i < size; ++i)
	{
		ri = rewardVector[i];
		if(ri)
		{
			delete ri;
			ri = NULL;
		}
	}
	rewardVector.clear();
}

TGateItem::TGateItem()
{
	gateId = -1;
	minLevel = -1;
	nowStage = -1;
	maxStage = -1;
	totalPlayer = 0;
	rewardVector.clear();
	canSelect = false;
}

TGateItem::~TGateItem()
{
	destroyData();
}

void TGateItem::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	packet>>gateId;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	gateName.assign(str);
	delete[] str;
	str = NULL;

	packet>>iconId;

	packet>>minLevel;
	packet>>mIspreMappass;
	packet>>nowStage;
	packet>>maxStage;
	packet>>totalPlayer;

	packet>>rewardNeedVipLevel0;
	packet>>rewardCostJewel0;
	packet>>rewardNeedVipLevel1;
	packet>>rewardCostJewel1;
	packet>>rewardNeedVipLevel2;
	packet>>rewardCostJewel2;

	char count = 0;
	TRewardItem * ri = NULL;
	packet>>count;
	for(int i = 0; i < count; ++i)
	{
		ri = new TRewardItem();
		ri->decodePacketData(packet);
		rewardVector.push_back(ri);
	}
}

void TTeamBattleData::destroyData()
{
	TGateItem * gi = NULL;
	int size = gateVector.size();
	for(int i = 0; i < size; ++i)
	{
		gi = gateVector[i];
		if(gi)
		{
			delete gi;
			gi = NULL;
		}
	}
	gateVector.clear();
}

TTeamBattleData::TTeamBattleData()
{
	challengeTimes = 0;
	maxChallengeTimes = 0;

	gateVector.clear();
}

TTeamBattleData::~TTeamBattleData()
{
	destroyData();
	challengeTimes = -1;
	maxChallengeTimes = -1;
}

void TTeamBattleData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>challengeTimes;
	packet>>maxChallengeTimes;
	unsigned short count = 0;
	packet>>count;
	TGateItem * gi = NULL;
	for(int i = 0; i < count; ++i)
	{
		gi = new TGateItem();
		gi->decodePacketData(packet);
		gateVector.push_back(gi);
	}

}

void TTeamStageData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>stageId;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	stageName.assign(str);
	delete[] str;
	str = NULL;
}

void TTeamListItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>teamId;
	packet>>leaderPlayerId;
	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//名字
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	leaderName.assign(str);
	delete[] str;
	str = NULL;
	packet>>memberCount;
}

void TTeamListData::destroyData()
{
	TTeamListItem * item = NULL;
	int size = teamVector.size();
	for(int i = 0; i < size; ++i)
	{
		item = teamVector[i];
		delete item;
		item = NULL;
	}
	teamVector.clear();
}

TTeamListData::TTeamListData()
{
	//teamVector.clear();
	destroyData();
}

TTeamListData::~TTeamListData()
{
	destroyData();
}

void TTeamListData::decodePacketData(cobra_win::DPacket & packet)
{	
	destroyData();
	char count = 0;
	TTeamListItem * item = NULL;
	packet>>count;
	for(int i = 0; i < count; ++i)
	{
		item = new TTeamListItem();
		item->decodePacketData(packet);
		teamVector.push_back(item);
	}
}

void TMyTeamMember::decodePacketData(cobra_win::DPacket & packet)
{
	unsigned short strlen = 0;
	char * str = NULL;

	packet>>gameUnitType;
	packet>>isLeader;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	markName.assign(str);
	delete[] str;
	str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	skinName.assign(str);
	delete[] str;
	str = NULL;
	char enhanceLevel = 0;
	packet>>enhanceLevel;
	packet>>btlCapacity;
	packet>>iconId;
	packet>>quality;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	playerName.assign(str);
	delete[] str;
	str = NULL;
	packet>>playerId;
}

void TMyTeamData::destroyData()
{
	TMyTeamMember * item = NULL;
	int size = memberVector.size();
	for(int i = 0; i < size; ++i)
	{
		item = memberVector[i];
		delete item;
		item = NULL;
	}
	memberVector.clear();
	isIamLeader = -1;
}

TMyTeamData::TMyTeamData()
{
	memberVector.clear();
}

TMyTeamData::~TMyTeamData()
{
	destroyData();
}

void TMyTeamData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>isIamLeader;
	char count = 0;
	packet>>count;
	TMyTeamMember * item = NULL;
	for(int i = 0; i < count; ++i)
	{
		item = new TMyTeamMember();
		item->decodePacketData(packet);
		item->index = i;
		memberVector.push_back(item);
	}
}


TeamBattleDataHandler::TeamBattleDataHandler()
{
	m_pTeamBattleData = new TTeamBattleData();
	m_pTeamListData = new TTeamListData();
	m_pTeamStageData = NULL;
	m_pMyTeamData = NULL;
	//m_pMyTeamData = new TMyTeamData();
	m_iMyTeamId = -1;
	m_iStartGateIdx = -1;
	m_bHaveGateReward = false;
	m_bOneMsgIsCoolDowning = false;
	m_lCoolDownTimeCount = 0;

	m_pSlaveList = NULL;
	m_pMercenaryList = NULL;

}
TeamBattleDataHandler::~TeamBattleDataHandler()
{
	if(m_pTeamBattleData)
	{
		delete m_pTeamBattleData;
		m_pTeamBattleData = NULL;
	}
	if(m_pTeamListData)
	{
		delete m_pTeamListData;
		m_pTeamListData = NULL;
	}
	if(m_pTeamStageData)
	{
		delete m_pTeamStageData;
		m_pTeamStageData = NULL;
	}
	if(m_pMyTeamData)
	{
		delete m_pMyTeamData;
		m_pMyTeamData = NULL;
	}
	if(m_pSlaveList)
	{
		delete m_pSlaveList;
		m_pSlaveList = NULL;
	}
	if(m_pMercenaryList)
	{
		delete m_pMercenaryList;
		m_pMercenaryList = NULL;
	}
}

void TeamBattleDataHandler::onDestroy()
{
	m_iStartGateIdx = -1;
	m_iMyTeamId = -1;
	m_iStartGateIdx = -1;

	m_bHaveGateReward = false;

	if(m_pTeamBattleData)
	{
		m_pTeamBattleData->destroyData();
	}
	if(m_pTeamListData)
	{
		m_pTeamListData->destroyData();
	}
	if(m_pTeamStageData)
	{
		delete m_pTeamStageData;
		m_pTeamStageData = NULL;
	}
	if(m_pMyTeamData)
	{
		delete m_pMyTeamData;
		m_pMyTeamData = NULL;
	}
	if(m_pSlaveList)
	{
		delete m_pSlaveList;
		m_pSlaveList = NULL;
	}
	if(m_pMercenaryList)
	{
		delete m_pMercenaryList;
		m_pMercenaryList = NULL;
	}
}

// Message * TeamBattleDataHandler::HandleMsg(Message messge)
// {
// 	Message * rpy = NULL;
// 	switch(messge.what)
// 	{
// 	case _MSG_TEAMBATTLE_GetSelectGateInfo_:{
// 		rpy = new Message();
// 		rpy->userData = GetSelectGateInfo();
// 		}break;
// 	case _MSG_TEAMBATTLE_GetMyTeamData_:{
// 		rpy = new Message();
// 		rpy->userData = m_pMyTeamData;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetNowStageId_MaxStage_:{
// 		rpy = new Message();
// 		rpy->arg0 = m_pTeamStageData->stageId;
// 		rpy->arg1 = GetSelectGateInfo()->maxStage;
// 		}break;
// 	case _MSG_TEAMBATTLE_SetHaveGateReward_:{
// 		m_bHaveGateReward = true;//有通关奖励
// 		}break;
// 	case _MSG_TEAMBATTLE_GetMyTeamId_:{
// 		rpy = new Message();
// 		rpy->arg0 = m_iMyTeamId;
// 		}break;
// 	case _MSG_TEAMBATTLE_ClearMyTeamData_:{
// 		DestroyMyTeam();
// 		}break;
// 	case _MSG_TEAMBATTLE_GetHaveGateReward_:{
// 		rpy = new Message();
// 		rpy->arg0 = m_bHaveGateReward;
// 		}break;
// 	case _MSG_TEAMBATTLE_ClearGateReward_:{
// 		m_bHaveGateReward = false;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetGateVectorSize_:{
// 		rpy = new Message();
// 		rpy->arg0 = m_pTeamBattleData->gateVector.size();
// 		}break;
// 	case _MSG_TEAMBATTLE_GetOldGateTableOffset_:{
// 		rpy = new Message();
// 		rpy->userData = &m_fOldGateTableOffset;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetOldGateTableWidth_:{
// 		rpy = new Message();
// 		rpy->userData = &m_fOldGateTableWidth;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetSelectGateIdx_:{
// 		rpy = new Message();
// 		rpy->arg0 = m_iStartGateIdx;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetOneKeyCoolDownStatu_:{
// 		rpy = new Message();
// 		rpy->userData = &m_bOneMsgIsCoolDowning;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetCoolDownTimeCount_:{
// 		rpy = new Message();
// 		rpy->userData = &m_lCoolDownTimeCount;
// 		}break;
// 	case _MSG_TEAMBATTLE_GetTeamStageData_:{
// 		rpy = new Message();
// 		rpy->userData = m_pTeamStageData;
// 		}break;
// 	case _MSG_TEAMBATTLE_SETSTARTGATEIDX_:{
// 		m_iStartGateIdx = messge.arg0;
// 		}break;
// 	}
// 
// 	return rpy;
// }

void TeamBattleDataHandler::ClearMyTeamData()
{
	m_pMyTeamData->destroyData();

}

TGateItem * TeamBattleDataHandler::GetSelectGateInfo()
{
	if(m_iStartGateIdx >= 0 && m_iStartGateIdx < (int)m_pTeamBattleData->gateVector.size())
		return m_pTeamBattleData->gateVector[m_iStartGateIdx];

	return NULL;
}

TGateItem * TeamBattleDataHandler::GetGateInfoById(int gateId)
{
	if(gateId < (int)m_pTeamBattleData->gateVector.size())
	{
		for(int i = 0; i < (int)m_pTeamBattleData->gateVector.size(); ++i)
		{
			if(m_pTeamBattleData->gateVector[i]->gateId == gateId)
			{
				return m_pTeamBattleData->gateVector[i];
			}
		}
	}
	return NULL;
}

TGateItem * TeamBattleDataHandler::GetGateInfoByIdx(int gateIdx)
{
	if(gateIdx >= 0 && gateIdx < (int)m_pTeamBattleData->gateVector.size())
		return m_pTeamBattleData->gateVector[gateIdx];

	return NULL;
}

int TeamBattleDataHandler::GetMaxCanStartGateIdx()
{
	unsigned int i = 0;
	for(; i < m_pTeamBattleData->gateVector.size(); ++i)
	{
		if(ROLEINFODATAHANDLER->m_pRIData->level_ < m_pTeamBattleData->gateVector[i]->minLevel)
			break;
	}
	return i - 1;
}

void TeamBattleDataHandler::DestroyMyTeam()
{
	if(m_pMyTeamData)
	{
		delete m_pMyTeamData;
		m_pMyTeamData = NULL;
	}
}

int TeamBattleDataHandler::GetMyTeamLeaderId()
{
	if(m_pMyTeamData)
	{
		for(unsigned int i = 0; i < m_pMyTeamData->memberVector.size(); ++i)
		{
			if(m_pMyTeamData->memberVector[i]->isLeader > 0)
				return m_pMyTeamData->memberVector[i]->playerId;
		}
	}

	return -1;
}

void TeamBattleDataHandler::ToServerEnterTeamBattle()
{
	//进入多人副本，获得数据
	CSTeamBattleGetDataPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToClientEnterTeamBattleResult()
{
	//将倒数第一个不能开始的关卡判定为可选中查看
	int level = ROLEINFODATAHANDLER->m_pRIData->level_;
	int i = 0;
	for(; i < TEAMBATTLEDATAHANDLER->m_pTeamBattleData->gateVector.size(); ++i)
	{
		TEAMBATTLEDATAHANDLER->m_pTeamBattleData->gateVector[i]->canSelect = true;
		if(level < TEAMBATTLEDATAHANDLER->m_pTeamBattleData->gateVector[i]->minLevel)
		{
			break;
		}
	}


	//获得数据，通知客户端刷新
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_GETDATA_RESULT_);

	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerResetGate()
{
	TGateItem * tgi = GetSelectGateInfo();
	if(tgi)
	{
		CSTeamBattleResetDataPacket packet(tgi->gateId);
		packet.Send();
		NFC_showCommunicationWating(true);
	}
}

void TeamBattleDataHandler::ToClientResetGateResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_RESET_RESULT_);

	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerEnterTeamSelect()
{
	TGateItem * tgi = GetSelectGateInfo();
	if(tgi)
	{
		CSTeamSelectEnterPacket packet(tgi->gateId);
		packet.Send();
	}

	NFC_showCommunicationWating(true);
}


void  TeamBattleDataHandler::ToClientEnterTeamSelectResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMSELECTWINDOW_);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_GETSTAGEDATA_RESULT_);

	NFC_showCommunicationWating(false);

}

void TeamBattleDataHandler::ToClientGetTeamList()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_GETTEAMLIST_);

	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerJoinTeam()
{
	CSTeamSelectJoinTeamPacket packet(m_iMyTeamId);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToClientJoinTeamResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_GETMYTEAM_);

	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerStopTeamSync()
{
	CSTeamSelectStopTeamSyncPacket packet;
	packet.Send();

}

void TeamBattleDataHandler::ToServerRemoveMember(int playerId)
{
	CSTeamSelectRemoveMemberPacket packet(playerId);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToClientBeRemoved(char removedType)
{
	//在收到这个包时表明自己已经不在上一个队伍中，故上一个队伍的所有数据需要被清空
	int isLeader = m_pMyTeamData->isIamLeader;
	int type = removedType;
	if(m_pMyTeamData)
	{
		delete m_pMyTeamData;
		m_pMyTeamData = NULL;
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_BEREMOVED_, _to_event_param_(type), _to_event_param_(isLeader));

	NFC_showCommunicationWating(false);
}


void TeamBattleDataHandler::ToServerStartStage()
{
	CSTeamSelecStartStagePacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID());
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToServerReorderMyTeam(std::vector<int> & playerIdVec)
{
	CSTeamSelectReorderTeamPacket packet(playerIdVec);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToServerSwitchMemberPlace(int arg0, int arg1)
{
	//交换这两个队员,两次交换是为了不改变内存中的数据排列顺序

	TMyTeamMember * temp = m_pMyTeamData->memberVector[arg0];
	m_pMyTeamData->memberVector[arg0] = m_pMyTeamData->memberVector[arg1];
	m_pMyTeamData->memberVector[arg1] = temp;

	int size = m_pMyTeamData->memberVector.size();

	std::vector<int> playerIdVec;
	TMyTeamMember * tmtm = NULL;
	for(int j = 0; j < size; ++j)
	{
		tmtm = m_pMyTeamData->memberVector[j];
		playerIdVec.push_back(tmtm->index);
	}

	temp = m_pMyTeamData->memberVector[arg0];
	m_pMyTeamData->memberVector[arg0] = m_pMyTeamData->memberVector[arg1];
	m_pMyTeamData->memberVector[arg1] = temp;

	TEAMBATTLEDATAHANDLER->ToServerReorderMyTeam(playerIdVec);
}

void TeamBattleDataHandler::ToServerGateReward(char rewardTag)
{
	TGateItem * tgi = GetSelectGateInfo();
	if(tgi)
	{
		CSTeamBattleGateRewardPacket packet(tgi->gateId, rewardTag);
		packet.Send();
		NFC_showCommunicationWating(true);
	}
}

void TeamBattleDataHandler::ToClientGateRewardResult()
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_GETTONGGUANJIANGLI_RESULT_);
}

void TeamBattleDataHandler::ToServerGetPlayerInfo(int playerid)
{
	C2SCheckPlayerInfoPacket pack(playerid);
	pack.Send();
}

void TeamBattleDataHandler::ToServerGetSlaveList()
{
	CSAskSlaveListPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToClientGetSlaveList()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_GETSLAVElIST_RESULT_);
	
	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerGetMercenaryList()
{
	CSAskMercenaryListPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToClientGetMercenaryList()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMSELECT_GETMERCENARYLIST_RESULT_);
	
	NFC_showCommunicationWating(false);
}

void TeamBattleDataHandler::ToServerRendSlave(int playerId)
{
	CSHireSlavePacket packet(playerId);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void TeamBattleDataHandler::ToServerRendMercenary(int playerId)
{
	CSHireMercenaryPacket packet(playerId);
	packet.Send();

	NFC_showCommunicationWating(true);
}