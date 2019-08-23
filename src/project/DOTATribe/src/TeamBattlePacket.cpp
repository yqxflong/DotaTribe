//Name:TeamSelectPacket
//Function: 组队副本主界面
//Author:李茜
//Date:2013-09-23

#include <cocos2d.h>
#include "../include/TeamBattlePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/TeamBattleDataHandler.h"


/************************************************************************/
/* 获取组队副本信息                                                     */
/************************************************************************/

CSTeamBattleGetDataPacket::CSTeamBattleGetDataPacket() 
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTeamBattleGetDataPacket::~CSTeamBattleGetDataPacket()
{

}

unsigned  int  CSTeamBattleGetDataPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMBATTLESETDATA_;
}

unsigned  int  CSTeamBattleGetDataPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSTeamBattleGetDataPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}


unsigned  int SCTeamBattleGetDataPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMBATTLEGETDATA_RESULT_;
}


bool  SCTeamBattleGetDataPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取组队副本所有数据
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(TEAMBATTLEDATAHANDLER->m_pTeamBattleData == NULL)
	{
		TEAMBATTLEDATAHANDLER->m_pTeamBattleData = new TTeamBattleData();
	}
	TEAMBATTLEDATAHANDLER->m_pTeamBattleData->decodePacketData(packet);

	return true;
}


unsigned  int  SCTeamBattleGetDataPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMBATTLEGETDATA_RESULT_;
}

bool  SCTeamBattleGetDataPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamBattleGetDataPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_GETDATA_RESULT_);

	TEAMBATTLEDATAHANDLER->ToClientEnterTeamBattleResult();

	return true;
}


CSTeamBattleResetDataPacket::CSTeamBattleResetDataPacket(unsigned char fubenId):m_fubenId(fubenId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTeamBattleResetDataPacket::~CSTeamBattleResetDataPacket()
{

}

unsigned  int  CSTeamBattleResetDataPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMBATTLERESET_;
}

unsigned  int  CSTeamBattleResetDataPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_fubenId);
}


void CSTeamBattleResetDataPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_fubenId);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCTeamBattleResetDataResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMBATTLERESET_RESULT_;
}

bool  SCTeamBattleResetDataResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	//重置的关卡数据
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	unsigned char gateId;
	packet>>gateId;

	TGateItem * tgi = TEAMBATTLEDATAHANDLER->GetGateInfoById(gateId);
	if(tgi)
		tgi->nowStage = 0;

	return true;
}

unsigned  int SCTeamBattleResetDataResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMBATTLERESET_RESULT_;
}

bool  SCTeamBattleResetDataResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamBattleResetDataResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	TEAMBATTLEDATAHANDLER->ToClientResetGateResult();

	return true;
}



CSTeamBattleGateRewardPacket::CSTeamBattleGateRewardPacket(unsigned char gateId, char rewardTag):m_gateId(gateId), m_rewardTag(rewardTag)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTeamBattleGateRewardPacket::~CSTeamBattleGateRewardPacket()
{

}

unsigned  int  CSTeamBattleGateRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMBATTLE_GATEREWARD_;
}

unsigned  int  CSTeamBattleGateRewardPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_gateId) + sizeof(m_rewardTag);
}


void CSTeamBattleGateRewardPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_gateId);
	pNode->push(m_rewardTag);
	NETSYSTEM->SendPacket(pNode);
}

CSAskSlaveListPacket::CSAskSlaveListPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
unsigned  int  CSAskSlaveListPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_ASKSLAVELIST_;
}
unsigned  int  CSAskSlaveListPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn);
}
void  CSAskSlaveListPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCTeamBattleGateRewardResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMBATTLE_GATEREWARD_RESULT_;
}

bool  SCTeamBattleGateRewardResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	TEAMBATTLEDATAHANDLER->ToClientGateRewardResult();

	return true;
}


unsigned  int  SCAskSlaveListResultPacket::GetPacketType()
{
	return _TYPED_PACEKT_S2C_TEAMSELECT_ASKSLAVELIST_RESULT_;
}

bool  SCAskSlaveListResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(TEAMBATTLEDATAHANDLER->m_pSlaveList == NULL)
	{
		TEAMBATTLEDATAHANDLER->m_pSlaveList = new TSlaveList();
	}
	TEAMBATTLEDATAHANDLER->m_pSlaveList->decodePacketData(packet);

	return true;
}

unsigned  int  SCAskSlaveListResultPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_TEAMSELECT_ASKSLAVELIST_RESULT_;
}

bool  SCAskSlaveListResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAskSlaveListResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	TEAMBATTLEDATAHANDLER->ToClientGetSlaveList();
	return true;
}

CSHireSlavePacket::CSHireSlavePacket(int playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_playerId = playerId;
}

unsigned  int  CSHireSlavePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_HIRE_SLAVE_;
}

unsigned  int  CSHireSlavePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_playerId);
}

void  CSHireSlavePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_playerId);
	NETSYSTEM->SendPacket(pNode);
}

CSAskMercenaryListPacket::CSAskMercenaryListPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
unsigned  int  CSAskMercenaryListPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_ASKMERCENARYLIST_;
}
unsigned  int  CSAskMercenaryListPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn);
}
void  CSAskMercenaryListPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCAskMercenaryListResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_ASKMERCENARYLIST_RESULT_;
}

bool  SCAskMercenaryListResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(TEAMBATTLEDATAHANDLER->m_pMercenaryList == NULL)	
	{
		TEAMBATTLEDATAHANDLER->m_pMercenaryList = new TMercenaryList();
	}
	TEAMBATTLEDATAHANDLER->m_pMercenaryList->decodePacketData(packet);

	return true;
}

unsigned  int  SCAskMercenaryListResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_ASKMERCENARYLIST_RESULT_;
}

bool  SCAskMercenaryListResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAskMercenaryListResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	TEAMBATTLEDATAHANDLER->ToClientGetMercenaryList();
	return true;
}

CSHireMercenaryPacket::CSHireMercenaryPacket(int playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_playerId = playerId;
}

unsigned  int  CSHireMercenaryPacket::GetPacketType()
{
	return _TYPED_PACEKT_C2S_TEAMSELECT_HIRE_MERCENARY_;
}

unsigned  int  CSHireMercenaryPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_playerId);
}

void  CSHireMercenaryPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_playerId);
	NETSYSTEM->SendPacket(pNode);
}