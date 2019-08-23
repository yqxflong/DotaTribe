//Name:ClimbTowerPacket
//Function: 爬塔包
//Author:fangjun
//Date:20130826
#include <cocos2d.h>
#include "../include/ClimbTowerPacket.h"
#include "../include/PacketTyper.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

/************************************************************************/
/* 进入恶魔塔                                                           */
/************************************************************************/
CSEnterTowerPacket::CSEnterTowerPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();

}

CSEnterTowerPacket::~CSEnterTowerPacket()
{
}

unsigned  int  CSEnterTowerPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTERTOWER_;

}

unsigned  int  CSEnterTowerPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSEnterTowerPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}

SCEnterTowerResultPacket::SCEnterTowerResultPacket()
{

}

SCEnterTowerResultPacket::~SCEnterTowerResultPacket()
{
}

unsigned  int  SCEnterTowerResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTERTOWER_RESULT_;
}

bool  SCEnterTowerResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	CLIMBTOWERDATAHANDLER->enterData.decodePacketData(packet);

	return true;
}


SCEnterTowerResultPacketFactory::SCEnterTowerResultPacketFactory()
{

}

SCEnterTowerResultPacketFactory::~SCEnterTowerResultPacketFactory()
{

}

unsigned  int  SCEnterTowerResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTERTOWER_RESULT_;
}


bool  SCEnterTowerResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterTowerResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	CLIMBTOWERDATAHANDLER->ToClientEnterTowerResult();

	return true;
}

CSStartTowerPacket::CSStartTowerPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}


unsigned  int  CSStartTowerPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_STARTTOWER_;
}

unsigned  int  CSStartTowerPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}


void  CSStartTowerPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCStartTowerResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_STARTTOWER_RESULT_;
}


bool  SCStartTowerResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	//读取出一个已经获取的经验数据

	int exp = 0;
	packet>>exp;
	CLIMBTOWERDATAHANDLER->enterData.gotexp = exp;

	return true;
}

unsigned  int  SCStartTowerResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_STARTTOWER_RESULT_;
}

bool  SCStartTowerResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCStartTowerResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	CLIMBTOWERDATAHANDLER->ToClientStartTowerResult();

	return	true;
}



/************************************************************************/
/* 挑战恶魔关卡                                                         */
/************************************************************************/

CSChallengeTowerPacket::CSChallengeTowerPacket(int serialId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_serialId = serialId;
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSChallengeTowerPacket::~CSChallengeTowerPacket()
{

}

unsigned  int  CSChallengeTowerPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHALLENGETOWER_;
}

unsigned  int  CSChallengeTowerPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId);
}

void  CSChallengeTowerPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	NETSYSTEM->SendPacket(pNode);
}



/************************************************************************/
/* 重置爬塔记录                                                         */
/************************************************************************/


CSResetTowerPacket::CSResetTowerPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSResetTowerPacket::~CSResetTowerPacket()
{

}

unsigned  int  CSResetTowerPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RESETTOWER_;
}

unsigned  int  CSResetTowerPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSResetTowerPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}

SCResetTowerResultPacket::SCResetTowerResultPacket()
{

}

SCResetTowerResultPacket::~SCResetTowerResultPacket()
{

}

unsigned  int  SCResetTowerResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_RESETTOWER_RESULT_;
}

bool  SCResetTowerResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	CLIMBTOWERDATAHANDLER->enterData.decodePacketData(packet);

	return true;
}

SCResetTowerResultPacketFactory::SCResetTowerResultPacketFactory()
{

}

SCResetTowerResultPacketFactory::~SCResetTowerResultPacketFactory()
{

}

unsigned  int  SCResetTowerResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_RESETTOWER_RESULT_;
}

bool  SCResetTowerResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCResetTowerResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//通知客户端重置结果收到
	CLIMBTOWERDATAHANDLER->ToClientResetTowerResult();

	return true;
}



/************************************************************************/
/* 爬塔排行榜                                                           */
/************************************************************************/
CSTowerRankPacket::CSTowerRankPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTowerRankPacket::~CSTowerRankPacket()
{

}

unsigned  int  CSTowerRankPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TOWERRANK_;
}

unsigned  int  CSTowerRankPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSTowerRankPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}

SCTowerRankResultPacket::SCTowerRankResultPacket()
{

}

SCTowerRankResultPacket::~SCTowerRankResultPacket()
{

}

unsigned  int  SCTowerRankResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TOWERRANK_RESULT_;
}

bool  SCTowerRankResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	if(CLIMBTOWERDATAHANDLER->m_pRankList != NULL)
	{
		delete CLIMBTOWERDATAHANDLER->m_pRankList;
		CLIMBTOWERDATAHANDLER->m_pRankList = NULL;
	}
	CLIMBTOWERDATAHANDLER->m_pRankList = new TowerRankList();
	CLIMBTOWERDATAHANDLER->m_pRankList->decodePacketData(packet);

	return true;
}

SCTowerRankResultPacketFactory::SCTowerRankResultPacketFactory()
{

}

SCTowerRankResultPacketFactory::~SCTowerRankResultPacketFactory()
{

}

unsigned  int  SCTowerRankResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TOWERRANK_RESULT_;
}

bool  SCTowerRankResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTowerRankResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//通知客户端重置结果收到
	CLIMBTOWERDATAHANDLER->ToClientRankListResult();

	return true;
}


/************************************************************************/
/* 爬塔,钻石重置                                                           */
/************************************************************************/
CSTowerJewelResetPacket::CSTowerJewelResetPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

CSTowerJewelResetPacket::~CSTowerJewelResetPacket()
{

}

unsigned  int  CSTowerJewelResetPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CLIMBTOWER_JEWELRESET_;
}

unsigned  int  CSTowerJewelResetPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSTowerJewelResetPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);

	NETSYSTEM->SendPacket(pNode);
}

bool  SCTowerJewelResetResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix, 2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	return true;
}


unsigned  int  SCTowerJewelResetResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLIMBTOWER_JEWELRESET_RESULT_;
}

bool  SCTowerJewelResetResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTowerRankResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//通知客户端重置结果收到
	CLIMBTOWERDATAHANDLER->ToClientJewelResetResult();

	return true;
}

/************************************************************************/
/* 爬塔,快速爬塔                                                        */
/************************************************************************/
CSTowerFastFightPacket::CSTowerFastFightPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

CSTowerFastFightPacket::~CSTowerFastFightPacket()
{

}

unsigned  int  CSTowerFastFightPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CLIMBTOWER_FASTFIGHT_;
}

unsigned  int  CSTowerFastFightPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSTowerFastFightPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);

	NETSYSTEM->SendPacket(pNode);
}

bool  SCTowerFastFightResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix, 2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	TowerFastFightResultItem * result = new TowerFastFightResultItem();
	result->decodePacketData(packet);

	if(CLIMBTOWERDATAHANDLER->m_pFastFightResultData == NULL)
	{
		CLIMBTOWERDATAHANDLER->m_pFastFightResultData = new TowerFastFightResultData();
	}
	CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData.push_back(result);

	return true;
}


unsigned  int  SCTowerFastFightResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLIMBTOWER_FASTFIGHT_RESULT_;
}

bool  SCTowerFastFightResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTowerFastFightResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//通知客户端重置结果收到
	CLIMBTOWERDATAHANDLER->ToClientFastFightWinResult();

	return true;
}

/************************************************************************/
/* 爬塔,奖励列表                                                        */
/************************************************************************/
CSTowerRewardPacket::CSTowerRewardPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

CSTowerRewardPacket::~CSTowerRewardPacket()
{

}

unsigned  int  CSTowerRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CLIMBTOWER_REWARD_;
}

unsigned  int  CSTowerRewardPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}

void  CSTowerRewardPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);

	NETSYSTEM->SendPacket(pNode);
}

bool  SCTowerRewardResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix, 2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	if(CLIMBTOWERDATAHANDLER->m_pRewardData == NULL)
	{
		CLIMBTOWERDATAHANDLER->m_pRewardData = new TowerRewardData();
	}
	CLIMBTOWERDATAHANDLER->m_pRewardData->decodePacketData(packet);

	return true;
}


unsigned  int  SCTowerRewardResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLIMBTOWER_REWARD_DATA_;
}

bool  SCTowerRewardResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTowerRewardResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//通知客户端重置结果收到
	CLIMBTOWERDATAHANDLER->ToClientEnterRewardResult();

	return true;
}


/************************************************************************/
/* 爬塔,领取某层奖励                                                    */
/************************************************************************/
CSTowerGetRewardPacket::CSTowerGetRewardPacket(char type, unsigned short floor)
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	m_iType = type;
	m_iFloor = floor;
}

CSTowerGetRewardPacket::~CSTowerGetRewardPacket()
{

}

unsigned  int  CSTowerGetRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CLIMBTOWER_GETREWARD_;
}

unsigned  int  CSTowerGetRewardPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(m_iType) + sizeof(m_iFloor);
}

void  CSTowerGetRewardPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(m_iType);
	pNode->push(m_iFloor);

	NETSYSTEM->SendPacket(pNode);
}

bool  SCTowerGetRewardResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix, 2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	char type = 0;
	unsigned short floor = 0;
	packet>>type;
	packet>>floor;

	CLIMBTOWERDATAHANDLER->ToClientGetRewardResult(type, floor);

	return true;
}


unsigned  int  SCTowerGetRewardResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLIMBTOWER_GETREWARD_RESULT_;
}

bool  SCTowerGetRewardResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTowerGetRewardResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
		

	return true;
}

unsigned  int  CSBuyClimbTowerTimesPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_BUY_CLIMBTOWER_TIME_;
}


unsigned  int  SCBuyClimbTowerTimesPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_BUY_CLIMBTOWER_TIME_RESULT_;
}


bool SCBuyClimbTowerTimesPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	CLIMBTOWERDATAHANDLER->ToClientBuyClimbTowerTimesResult();

	return true;
}
