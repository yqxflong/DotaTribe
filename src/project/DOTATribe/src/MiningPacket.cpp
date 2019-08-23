//Name:MiningPacket.h
//Function:挖矿网络包
//Author: fangjun
//Date: 20131127

#include "../include/MiningPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/MiningDataHandler.h"
#include "../include/TimeSystem.h"
#include "../include/SysLangDataManager.h"

CSEnterMiningPacket::CSEnterMiningPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int CSEnterMiningPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_MINING_;
}

unsigned  int CSEnterMiningPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSEnterMiningPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCEnterMiningResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pMiningData == NULL)
	{
		MININGDATAHANDLER->m_pMiningData = new MiningData();
	}
	MININGDATAHANDLER->m_pMiningData->decodePackerData(packet);

	return true;
}

unsigned  int  SCEnterMiningResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_MINING_RESULT_;
}

bool  SCEnterMiningResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterMiningResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientEnterMiningResult();

	return true;
}



CSEnterGoblinAreaPacket::CSEnterGoblinAreaPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int CSEnterGoblinAreaPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_GOBLINAREA_;
}

unsigned  int CSEnterGoblinAreaPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSEnterGoblinAreaPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCEnterGoblinResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pGoblinAreaData == NULL)
	{
		MININGDATAHANDLER->m_pGoblinAreaData = new GoblinAreaData();
	}
	MININGDATAHANDLER->m_pGoblinAreaData->decodePacketData(packet);

	return true;
}

unsigned  int  SCEnterGoblinResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_GOBLINAREA_RESULT_;
}

bool  SCEnterGoblinResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterGoblinResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientEnterGoblinAreaResult();

	return true;
}

//=====================================================================

/************************************************************************/
/* 结束采集  2175，2176                                                 */
/************************************************************************/
CSStopMiningPacket::CSStopMiningPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSStopMiningPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_STOP_MINING_;
}

unsigned  int  CSStopMiningPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSStopMiningPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCStopMiningResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	
	return true;
}

unsigned  int  SCStopMiningResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_STOP_MINING_RESULT_;
}

bool  SCStopMiningResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCStopMiningResultPacket packet;
	if(!packet.Read(pBuffer,iLen))
		return false;

	MININGDATAHANDLER->ToClientStopMiningResult();

	return true;
}

/************************************************************************/
/* 矮人矿区   2177,2178                                                  */
/************************************************************************/
CSEnterDwarvenAreaPacket::CSEnterDwarvenAreaPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSEnterDwarvenAreaPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_DWARVENAREA_;
}

unsigned  int  CSEnterDwarvenAreaPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSEnterDwarvenAreaPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCEnterDwarvenResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pDwarvenAreaData == NULL)
	{
		MININGDATAHANDLER->m_pDwarvenAreaData = new DwarvenAreaData();
	}
	MININGDATAHANDLER->m_pDwarvenAreaData->decodePackerData(packet);
	

	return true;
}

unsigned  int SCEnterDwarvenResultPacketFactory:: GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_DWARVENAREA_RESULT_;
}

bool  SCEnterDwarvenResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterDwarvenResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientEnterDwarvenAreaResult();

	return true;
}


/************************************************************************/
/* 矮人矿区抢矿位  2179	，走战斗返回                                    */
/************************************************************************/
CSDwarvenLootPacket::CSDwarvenLootPacket(char index)
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	serial = 0;
	m_Index = index;
}
unsigned  int  CSDwarvenLootPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_DWARVENAREA_LOOT_;
}
unsigned  int  CSDwarvenLootPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(m_Index) + sizeof(serial);
}
void  CSDwarvenLootPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(serial);
	pNode->push(m_Index);
	NETSYSTEM->SendPacket(pNode);
}


bool  SCDwarvenLootResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	return true;
}

unsigned  int  SCDwarvenLootResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_DWARVENAREA_LOOT_RESULT_;
}

bool  SCDwarvenLootResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCDwarvenLootResultPacket pa;
	if(!pa.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientDwarvenLootResult();

	return true;
}

/************************************************************************/
/* 巨龙矿区   2181,2182                                                */
/************************************************************************/
CSEnterDragonAreaPacket::CSEnterDragonAreaPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSEnterDragonAreaPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_DRAGONAREA_;
}

unsigned  int  CSEnterDragonAreaPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSEnterDragonAreaPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCEnterDragonResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pDragonAreaData == NULL)
	{
		MININGDATAHANDLER->m_pDragonAreaData = new DragonAreaData();
	}
	MININGDATAHANDLER->m_pDragonAreaData->decodePackerData(packet);

	return true;
}

unsigned  int  SCEnterDragonResultPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_ENTER_DRAGONAREA_RESULT_;
}

bool  SCEnterDragonResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterDragonResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientEnterDragonAreaResult();

	return true;
}


/************************************************************************/
/* 挑战矿主  2183,返回走战斗                                                  */
/************************************************************************/
CSDragonChallengeOwnerPacket::CSDragonChallengeOwnerPacket(char index)
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	serial = 0;
	m_Index = index;
}

unsigned  int  CSDragonChallengeOwnerPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_DRAGON_CHALLENGEOWNER_;
}

unsigned  int  CSDragonChallengeOwnerPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(m_Index) + sizeof(serial);
}

void  CSDragonChallengeOwnerPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(serial);
	pNode->push(m_Index);
	NETSYSTEM->SendPacket(pNode);
}


/************************************************************************/
/* 开始采矿    2185,2186                                                */
/************************************************************************/
CSStartMiningPacket::CSStartMiningPacket(char mineAreaType, char index)
{
	PushData(mineAreaType);
	PushData(index);
}

unsigned  int  CSStartMiningPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_START_MINING_;
}

bool  SCStartMiningResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	char type = 0;
	char index = 0;

	packet>>type;
	packet>>index;

	MININGDATAHANDLER->ToClientStartMiningResult(type, index);

	return true;

}

unsigned  int  SCStartMiningResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_START_MINING_RESULT_;
}

bool  SCStartMiningResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCStartMiningResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}


/************************************************************************/
/* 寻宝界面   2187,2188                                                  */
/************************************************************************/
CSEnterHuntPacket::CSEnterHuntPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSEnterHuntPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_HUNT_;
}

unsigned  int  CSEnterHuntPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSEnterHuntPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCEnterHuntResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pHuntData == NULL)
	{
		MININGDATAHANDLER->m_pHuntData = new HuntData();
	}
	MININGDATAHANDLER->m_pHuntData->decodePacketData(packet);

	return true;
}

unsigned  int  SCEnterHuntResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_HUNT_RESULT_;
}

bool  SCEnterHuntResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterHuntResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientEnterHuntMiningResult();

	return true;
}

/************************************************************************/
/* 开始寻宝  2187,2188                                                  */
/************************************************************************/
CSHuntMiningPacket::CSHuntMiningPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSHuntMiningPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNTMINING_;
}

unsigned  int  CSHuntMiningPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void CSHuntMiningPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCHuntMiningResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pHuntResult == NULL)
	{
		MININGDATAHANDLER->m_pHuntResult = new HuntResult();
	}
	MININGDATAHANDLER->m_pHuntResult->decodePackerData(packet);

	return true;
}

unsigned  int  SCHuntMiningResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HUNTMINING_RESULT_;
}

bool  SCHuntMiningResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHuntMiningResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientHuntMiningResult();

	return true;
}

/************************************************************************/
/* 抢夺/驱逐   2191，返回走战斗                                         */
/************************************************************************/
CSHuntGrabPacket::CSHuntGrabPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	serial = 0;
}

unsigned  int  CSHuntGrabPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNTGRAB_;
}

unsigned  int  CSHuntGrabPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(serial);
}

void  CSHuntGrabPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(serial);
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 加好友/打招呼后领钱  2193,2194                                       */
/************************************************************************/
CSHuntHelloMoneyPacket::CSHuntHelloMoneyPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSHuntHelloMoneyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNT_HELLOMONEY_;
}

unsigned  int  CSHuntHelloMoneyPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSHuntHelloMoneyPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

bool  SCHuntHelloMoneyResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	return true;
}

unsigned  int  SCHuntHelloMoneyResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HUNT_HELLOMONEY_RESULT_;
}

bool  SCHuntHelloMoneyResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHuntHelloMoneyResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	MININGDATAHANDLER->ToClientHuntHelloMoneyResult();

	return true;
}

unsigned  int  CSBuyHuntTimesPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_BUY_HUNT_TIME_;
}


unsigned  int  SCBuyHuntTimesPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_BUY_HUNT_TIME_RESULT_;
}

bool  SCBuyHuntTimesPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	MININGDATAHANDLER->ToClientBuyHuntTimesResult();

	return true;
}


CSHuntLieRenChaKan::CSHuntLieRenChaKan(unsigned char index)
{
	PushData(index);
}

unsigned int CSHuntLieRenChaKan::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNT_LIEREN_CHAKAN_;
}

bool  SCHuntLieRenChaKanResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(MININGDATAHANDLER->m_pHuntLieRenData == NULL)
	{
		MININGDATAHANDLER->m_pHuntLieRenData = new HuntLieRenInfo();
	}
	MININGDATAHANDLER->m_pHuntLieRenData->decodePacketData(packet);

	return true;
}

unsigned  int  SCHuntLieRenChaKanResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HUNT_LIEREN_CHAKAN_RESULT_;
}

bool  SCHuntLieRenChaKanResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHuntLieRenChaKanResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
	{
		return false;
	}

	MININGDATAHANDLER->ToClientChaKanLieRenResult();

	return true;
}

/*
	寻宝特殊事件放弃寻宝，2249， 2250
*/
CSHuntLieRenQiangDuoNo::CSHuntLieRenQiangDuoNo(unsigned char index)
{
	PushData(index);
}

unsigned int CSHuntLieRenQiangDuoNo::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNT_LIEREN_QIANGDUO_NO_;
}

bool  SCHuntLieRenQiangDuoResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	unsigned char index = 0;
	packet>>index;

	MININGDATAHANDLER->ToClientQiangDuoLieRenNoResult(index);

	return true;
}

unsigned  int  SCHuntLieRenQiangDuoResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HUNT_LIEREN_QIANGDUO_NO_RESULT_;
}

bool  SCHuntLieRenQiangDuoResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHuntLieRenQiangDuoResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}


/*
	寻宝特殊事件开始寻宝，2251
*/
CSHuntLieRenQiangDuoYes::CSHuntLieRenQiangDuoYes(unsigned char index)
{
	PushData(index);
}

unsigned int CSHuntLieRenQiangDuoYes::GetPacketType()
{
	return _TYPED_PACKET_C2S_HUNT_LIEREN_QIANGDUO_YES_;
}