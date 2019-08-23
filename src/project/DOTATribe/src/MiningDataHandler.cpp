//Name:MiningDataHandler.h
//Function:挖矿
//Author:fangjun
//date:20131127

#include "cocos2d.h"
#include "../include/MiningDataHandler.h"
#include "../include/MiningPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/TimeSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MineAreaWindow.h"
#include "../include/AskForAddEnergyPacket.h"
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"
//#include "../include/IWindow.h"
#include "../include/NFToolController.h"

void HuntLieRenInfo::decodePacketData(cobra_win::DPacket & packet)
{
	NFC_ParsePacketString(packet, name);
	packet>>level;
	NFC_ParsePacketString(packet, heroLevelDesc);
	packet>>spentTili;
	packet>>index;
	packet>>isActive;
	if(isActive > 0)
	{
		packet>>probability;

		packet>>type;
		packet>>count;
		if(type == 0)
		{
			packet>>catogory;
			packet>>templateId;
			NFC_ParsePacketString(packet, itemName);
			packet>>quality;
			packet>>iconId;
		}
	}

}

HuntBoxData::HuntBoxData()
{
	type = 0;
	count = 0;
	critValue = 0;
	itemIconId = 0;
}
void HuntBoxData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>type;
	packet>>count;
	packet>>critValue;
	if(type == 0)
	{
		packet>>itemIconId;
	}
}

HuntResult::HuntResult()
{
	destroyData();
}
HuntResult::~HuntResult()
{
	destroyData();
}
void HuntResult::destroyData()
{
	needRespond = false;

	type = 0;

	for(int i = 0; i < (int)boxData.size(); ++i)
	{
		delete boxData[i];
		boxData[i] = NULL;
	}
	boxData.clear();

	playerId = 0;
	playerIsFriend = 0;
	playerName = "";
	playerLevel = 0;
	playerHeroIconId = 0;
	playerHeroShapeId = 0;
	playerHeroQuality = 0;
	playerBtlCapa = 0;

	orcName = "";
	orcLevel = 0;
	orcHeroIconId = 0;
	orcHeroShapeId = 0;
	orcHeroQuality = 0;
	orcBtlCapa = 0;

	lieRenIndex = 0;
	lieRenShapeId = 0;
}
void HuntResult::decodePackerData(cobra_win::DPacket & packet)
{
	destroyData();

	packet>>type;
	if(type == 0)
	{
		char count = 0;
		HuntBoxData * data;
		packet>>count;
		for(char i = 0; i < count; ++i)
		{
			data = new HuntBoxData();
			data->decodePacketData(packet);
			boxData.push_back(data);
		}
	}
	else if(type == 1)
	{
		packet>>playerId;
		packet>>playerIsFriend;

		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		playerName.assign(str);
		delete[] str;
		str = NULL;
			
		packet>>playerLevel;
		packet>>playerHeroIconId;
		packet>>playerHeroShapeId;
		packet>>playerHeroQuality;
		packet>>playerBtlCapa;
	}
	else if(type == 2)
	{
		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		orcName.assign(str);
		delete[] str;
		str = NULL;

		packet>>orcLevel;
		packet>>orcHeroIconId;
		packet>>orcHeroShapeId;
		packet>>orcHeroQuality;
		packet>>orcBtlCapa;
		packet>>orcBuyPrice;
	}
	else if(type == 3)
	{
		packet>>lieRenIndex;
		packet>>lieRenShapeId;
	}
}

HuntLieRen::HuntLieRen()
{
	index = 0;
	name = "";
	isActive = 0;
}
void HuntLieRen::decodePackerData(cobra_win::DPacket & packet)
{
	packet>>index;
	NFC_ParsePacketString(packet, name);
	packet>>isActive;
}

HuntData::HuntData()
{
	destroyData();
}

HuntData::~HuntData()
{
	destroyData();
}
void HuntData::destroyData()
{
	for(unsigned int i = 0; i < lieRenVector.size(); ++i)
	{
		delete lieRenVector[i];
		lieRenVector[i] = NULL;
	}
	lieRenVector.clear();

	huntTimes = 0;
	maxHuntTimes = 0;
}

void HuntData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();

	packet.read(huntTimes);
	packet.read(maxHuntTimes);

	unsigned char count = 0;
	packet>>count;
	HuntLieRen * lieren = NULL;
	for(char i = 0; i < count; ++i)
	{
		lieren = new HuntLieRen();
		lieren->decodePackerData(packet);
		lieRenVector.push_back(lieren);
	}
}

DragonOwnerData::DragonOwnerData()
{
	index = 0;
	playerId = 0;
	playerName = "";
	playerLevel = 0;
	heroIconId = 0;
	heroQuality = 0;
	btlCapa = 0;
	miningFriendCount = 0;
	friendCount = 0;
	isFriend = 0;
	isMining = 0;
	workedTime = 0;
	outPut = 0;
}
void DragonOwnerData::workTick()
{
	if(workedTime < 0 && isMining > 0)
		return;

	long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	long long during = nowtime - tickBegin;
	int seconds = (int)(during / 1000000);
	if(seconds >= 1)
	{
		tickBegin = nowtime;
		workedTime++;
		if(workedTime % 60 == 0)
			outPut += outPutPerMin;
	}
}
void DragonOwnerData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>index;
	packet>>playerId;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	playerName.assign(str);
	delete[] str;
	str = NULL;

	packet>>playerLevel;
	packet>>heroIconId;
	packet>>heroQuality;
	packet>>btlCapa;
	packet>>miningFriendCount;
	packet>>friendCount;
	packet>>isFriend;
	packet>>isMining;
	if(isMining == 1)
	{
		packet>>workedTime;
		packet>>outPut;
		packet>>outPutPerMin;
		tickBegin = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	}
}

DragonAreaData::DragonAreaData()
{
	destroyData();
}
DragonAreaData::~DragonAreaData()
{
	destroyData();
}
void DragonAreaData::destroyData()
{
	challengePrice = 0;

	for (int i = 0; i < (int)mineOwnerData.size(); ++i)
	{
		delete mineOwnerData[i];
		mineOwnerData[i] = NULL;
	}
	mineOwnerData.clear();
}
void DragonAreaData::decodePackerData(cobra_win::DPacket & packet)
{
	destroyData();

	packet>>slaveCount;		//当前奴隶数量
	packet>>maxSlaveCount;		//最大奴隶数量
	packet>>improve;			//金币效率加成（*100）

	packet>>challengePrice;

	char count = 0;
	DragonOwnerData * data;
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		data = new DragonOwnerData();
		data->decodePacketData(packet);
		if (data->isMining == 1 || data->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
		{
			IWindow* window=WINDOWMANAGER->GetWindowByType(IWindow::_TYPED_WINDOW_MINEAREA_WINDOW_);
			MineAreaWindow* theWindow=dynamic_cast<MineAreaWindow*>(window);
			theWindow->m_iDragonSelectOwner = i;
		}
		
		mineOwnerData.push_back(data);
	}
}

DwarvenSitData::DwarvenSitData()
{
	index = 0;
	isNull = 0;
	playerId = 0;
	playerName = "";
	playerLevel = 0;
	heroIconId = 0;
	heroQuality = 0;
	workedTime = 0;
	param = 0;
}

void DwarvenSitData::workTick()
{
	if(isNull > 0)
		return;

	if(workedTime < 0)
		return;

	long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	long long during = nowtime - tickBegin;
	int seconds = (int)(during / 1000000);
	if(seconds >= 1)
	{
		tickBegin = nowtime;
		workedTime++;
		if(playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
		{
			if(workedTime % 60 == 0)
				param += outPutPerMin;
		}
		
	}
}

void DwarvenSitData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>index;
	packet>>isNull;
	if(isNull == 0)
	{
		packet>>playerId;

		unsigned short strlen = 0;
		char * str = NULL;
		packet>>strlen;
		str = new char[strlen+1];
		packet.read(str,strlen);
		str[strlen] = '\0';
		playerName.assign(str);
		delete[] str;
		str = NULL;

		packet>>playerLevel;
		packet>>heroIconId;
		packet>>heroQuality;
		packet>>workedTime;
		packet>>param;
		packet>>outPutPerMin;

		tickBegin = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	}
}

DwarvenAreaData::DwarvenAreaData()
{
	destroyData();
}
DwarvenAreaData::~DwarvenAreaData()
{
	destroyData();
}
void DwarvenAreaData::destroyData()
{
	slaveCount = 0;
	maxSlaveCount = 0;
	improve = 0;
	leftLootMoney = 0;

	for(int i = 0; i < (int)sitData.size(); ++i)
	{
		delete sitData[i];
		sitData[i] = NULL;
	}
	sitData.clear();

}
void DwarvenAreaData::decodePackerData(cobra_win::DPacket & packet)
{
	destroyData();

	packet>>slaveCount;
	packet>>maxSlaveCount;
	packet>>improve;
	packet >> leftLootMoney;

	char count = 0;
	DwarvenSitData * data = NULL;
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		data = new DwarvenSitData();
		data->decodePacketData(packet);
		sitData.push_back(data);
	}
}

GoblinAreaData::GoblinAreaData()
{
	slaveCount = 0;
	maxSlaveCount = 0;
	improve = 0;
	workedTime = 0;
	outPut = 0;
}
void GoblinAreaData::workTick()
{
	if(workedTime < 0)
		return;

	long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	long long during = nowtime - tickBegin;
	int seconds = (int)(during / 1000000);
	if(seconds >= 1)
	{
		tickBegin = nowtime;
		workedTime++;

		if(workedTime % 60 == 0)
			outPut += outPutPerMin;
	}
}
void GoblinAreaData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>slaveCount;
	packet>>maxSlaveCount;
	packet>>improve;
	packet>>workedTime;
	packet>>outPut;
	packet>>outPutPerMin;

	tickBegin = TimeSystem::get_instance2()->GetCurrentMicroSecond();
}

MineAreaData::MineAreaData()
{
	areaType = 0;
	maxMiningTime = 0;
	outPut = 0;
	isMining = 0;
}
void MineAreaData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>areaType;
	packet>>maxMiningTime;
	packet>>outPut;
	packet>>isMining;
}

MiningData::MiningData()
{
	destroyData();
}
MiningData::~MiningData()
{
	destroyData();
}
void MiningData::destroyData()
{
	for(int i = 0; i < (int)mineArea.size(); ++i)
	{
		delete mineArea[i];
		mineArea[i] = NULL;
	}
	mineArea.clear();
}
void MiningData::decodePackerData(cobra_win::DPacket & packet)
{
	destroyData();

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	mineDesc.assign(str);
	delete[] str;
	str = NULL;

	MineAreaData * data = NULL;
	char count = 0;
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		data = new MineAreaData();
		data->decodePacketData(packet);
		mineArea.push_back(data);
	}

	packet.read(leftHuntTimes);
	packet.read(maxHuntTimes);
	packet>>lookCd;
}


/************************************************************************/
/* This is DataHandler                                                  */
/************************************************************************/

MiningDataHandler::MiningDataHandler()
{
	m_pMiningData = NULL;		//挖矿主界面数据
	m_pGoblinAreaData = NULL;				//地精矿区数据
	m_pDwarvenAreaData = NULL;			//矮人矿区数据
	m_pDragonAreaData = NULL;				//巨龙矿区数据

	m_pHuntData = NULL;							//寻宝界面信息
	m_pHuntResult = NULL;						//寻宝结果
	m_pHuntLieRenData = NULL;

	m_bNeedOpenTipsPage2 = false;

	m_isFBDragon = false;
}

MiningDataHandler::~MiningDataHandler()
{
	if(m_pMiningData)
	{
		delete m_pMiningData;
		m_pMiningData = NULL;
	}
	if(m_pGoblinAreaData)
	{
		delete m_pGoblinAreaData;
		m_pGoblinAreaData = NULL;
	}
	if(m_pDwarvenAreaData)
	{
		delete m_pDwarvenAreaData;
		m_pDwarvenAreaData = NULL;
	}
	if(m_pDragonAreaData)
	{
		delete m_pDragonAreaData;
		m_pDragonAreaData = NULL;
	}
	if(m_pHuntData)
	{
		delete m_pHuntData;
		m_pHuntData = NULL;
	}
	if(m_pHuntResult)
	{
		delete m_pHuntResult;
		m_pHuntResult = NULL;
	}
	if(m_pHuntLieRenData)
	{
		delete m_pHuntLieRenData;
		m_pHuntLieRenData = NULL;
	}
}

void MiningDataHandler::onDestroy()
{

}

void MiningDataHandler::OnAthleticEnd(int type, bool win)
{
	int area = 0;
	if(type == 1)
	{
		area = MineAreaWindow::_PAGE_DWARVENAREA_;
	}
	else if(type == 2)
	{
		area = MineAreaWindow::_PAGE_DRAGONAREA_;
		if (win)
		{
			MININGDATAHANDLER->m_isFBDragon = true;
		}	
	}
	else if(type == 3 || type == 4)
	{
		area = MineAreaWindow::_PAGE_HUNTMINE_;
	}
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(area));

}

void  MiningDataHandler::OnHuntLieRenQiangDuoAthleticEnd(bool qiangduoWin)
{
	if(qiangduoWin == false)
		m_bNeedOpenTipsPage2 = true;
}

//进入采矿
void MiningDataHandler::ToServerEnterMining()
{
	CSEnterMiningPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientEnterMiningResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_ENTERMINING_GETDATA_);
	NFC_showCommunicationWating(false);
}

//进入地精矿区
void MiningDataHandler::ToServerEnterGoblinArea()
{
	CSEnterGoblinAreaPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientEnterGoblinAreaResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_ENTERGOBLINAREA_GETDATA_);

	NFC_showCommunicationWating(false);
}

//结束采集
void MiningDataHandler::ToServerStopMining()
{
	CSStopMiningPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientStopMiningResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_STOPMINING_GETDATA_);

	NFC_showCommunicationWating(false);
}

//进入矮人矿区
void MiningDataHandler::ToServerEnterDwarvenArea()
{
	CSEnterDwarvenAreaPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientEnterDwarvenAreaResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_ENTERDWARVENAREA_GETDATA_);

	NFC_showCommunicationWating(false);
}

//矮人矿区抢矿位
void MiningDataHandler::ToServerDwarvenLoot(char index)
{
	CSDwarvenLootPacket pa(index);
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientDwarvenLootResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_DWARVEN_LOOT_GETDATA_);

	NFC_showCommunicationWating(false);
}

//进入巨人矿区
void MiningDataHandler::ToServerEnterDragonArea()
{
	CSEnterDragonAreaPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientEnterDragonAreaResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_ENTERDRAGONAREA_GETDATA_);

	NFC_showCommunicationWating(false);
}

//挑战巨人矿区的矿主
void MiningDataHandler::ToServerDragonChallengeOwner(char index)
{
	CSDragonChallengeOwnerPacket pa(index);
	pa.Send();

	NFC_showCommunicationWating(true);
}

//开始采矿
void MiningDataHandler::ToServerStartMining(char type, char index)
{
	CSStartMiningPacket pa(type, index);
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientStartMiningResult(char type, char index)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_STARTMINING_GETDATA_, _to_event_param_((int)type), _to_event_param_((int)index));

	NFC_showCommunicationWating(false);
}

//进入寻宝
void MiningDataHandler::ToServerEnterHuntMining()
{
	CSEnterHuntPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientEnterHuntMiningResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_ENTERHUNTMINING_GETDATA_);

	NFC_showCommunicationWating(false);
}

//寻宝
void MiningDataHandler::ToServerHuntMining()
{
	CSHuntMiningPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientHuntMiningResult()
{
	if(m_pHuntResult && m_pHuntResult->type == 1)
	{
		m_pHuntResult->needRespond = true;//当遇到人物时需要界面反馈
	}
	else
	{
		m_pHuntResult->needRespond = false;
	}

	if(m_pHuntResult->type == 3)
	{
		//将当前遭遇到的节点状态激活
		for(unsigned int i = 0; i < MININGDATAHANDLER->m_pHuntData->lieRenVector.size(); ++i)
		{
			if(MININGDATAHANDLER->m_pHuntData->lieRenVector[i]->index == MININGDATAHANDLER->m_pHuntResult->lieRenIndex)
			{
				MININGDATAHANDLER->m_pHuntData->lieRenVector[i]->isActive = 1;
			}
		}
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_HUNTMININGRESULT_GETDATA_);

	NFC_showCommunicationWating(false);
}

//抢夺、驱逐
void MiningDataHandler::ToServerHuntGrab()
{
	CSHuntGrabPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

//加好友，打招呼后领钱
void MiningDataHandler::ToServerHuntHelloMoney()
{
	CSHuntHelloMoneyPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientHuntHelloMoneyResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_HUNTHELLOMONEY_GETDATA_);

	NFC_showCommunicationWating(false);
}

void MiningDataHandler::ToClientAskFriendResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_HUNTASKFORFRIEND_GETDATA_);
}

//花费钻石直接买物品
void MiningDataHandler::ToServerHuntBuyMineral()
{
	C2SAskForAddEnergyPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientHuntBuyMineralResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_MINING_HUNTBUYMINERAL_GETDATA_);

	NFC_showCommunicationWating(false);
}

void MiningDataHandler::ToServerBuyHuntTimes()
{
	CSBuyHuntTimesPacket pa;
	pa.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientBuyHuntTimesResult()
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_BUYHUNTTIMES_GETDATA_);
}


void MiningDataHandler::ToServerChaKanLieRen(unsigned char index)
{
	CSHuntLieRenChaKan packet(index);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientChaKanLieRenResult()
{
	NFC_showCommunicationWating(false);

	//获得某个猎人信息，对客服端这个猎人信息矫正
	for(unsigned int i = 0; i < m_pHuntData->lieRenVector.size(); ++i)
	{
		if(m_pHuntData->lieRenVector[i]->index == m_pHuntLieRenData->index)
		{
			m_pHuntData->lieRenVector[i]->isActive = m_pHuntLieRenData->isActive;
		}
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVNET_HUNT_LIEREN_CHAKAN_GETDATA_);
}

void MiningDataHandler::ToServerQiangDuoLieRenNo(unsigned char index)
{
	CSHuntLieRenQiangDuoNo packet(index);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void MiningDataHandler::ToClientQiangDuoLieRenNoResult(unsigned char index)
{
	//需要将内存中猎人状态数据清空
	if(m_pHuntData)
	{
		for(unsigned int i = 0; i < m_pHuntData->lieRenVector.size(); ++i)
		{
			if(m_pHuntData->lieRenVector[i]->index == index)
			{
				m_pHuntData->lieRenVector[i]->isActive = 0;
			}
		}
	}

	NFC_showCommunicationWating(false);

	//需要通知界面清除当前被取消激活状态猎人的特效
	int arg = index;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_GETDATA_, _to_event_param_(arg));
}

//开始抢夺猎人
void MiningDataHandler::ToServerQiangDuoLieRenYes(unsigned char index)
{
	CSHuntLieRenQiangDuoYes packet(index);
	packet.Send();

	NFC_showCommunicationWating(true);
}

int MiningDataHandler::PlayerinMineIndex()
{
	if (m_pDwarvenAreaData == NULL)
		return 0;
	int index = 0;
	std::vector<DwarvenSitData *>::iterator it_begin = m_pDwarvenAreaData->sitData.begin();
	std::vector<DwarvenSitData *>::iterator it_end = m_pDwarvenAreaData->sitData.end();
	for (;it_begin != it_end;it_begin++)
	{
		
		if (*it_begin)
		{
			if ((*it_begin)->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
			{
				return index;
			}
		}
		index++;
	}
	return 0;
}