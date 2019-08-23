//Name:TeamSelectPacket
//Function: 组队副本组队界面
//Author:fangjun
//Date:20130923

#include <cocos2d.h>
#include "../include/TeamSelectPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/TeamBattleDataHandler.h"
#include "../include/LoggerSystem.h"

/************************************************************************/
/* 获取队伍列表信息                                                     */
/************************************************************************/

CSTeamSelectEnterPacket::CSTeamSelectEnterPacket(int gateId) : m_gateId(gateId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTeamSelectEnterPacket::~CSTeamSelectEnterPacket()
{

}

unsigned  int  CSTeamSelectEnterPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECTENTER_;
}

unsigned  int  CSTeamSelectEnterPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_gateId);
}

void  CSTeamSelectEnterPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_gateId);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int SCTeamSelectEnterResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECTENTER_RESULT_;
}


bool  SCTeamSelectEnterResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//关卡id
// 	if(TEAMBATTLE_DATAHANDLER->m_pTeamStageData != NULL)
// 	{
// 		delete TEAMBATTLE_DATAHANDLER->m_pTeamStageData;
// 		TEAMBATTLE_DATAHANDLER->m_pTeamStageData = NULL;
// 	}
// 	TEAMBATTLE_DATAHANDLER->m_pTeamStageData = new TTeamStageData();
// 	TEAMBATTLE_DATAHANDLER->m_pTeamStageData->decodePacketData(packet);

	if(TEAMBATTLEDATAHANDLER->m_pTeamStageData == NULL)
	{
		TEAMBATTLEDATAHANDLER->m_pTeamStageData = new TTeamStageData();
	}
	TEAMBATTLEDATAHANDLER->m_pTeamStageData->decodePacketData(packet);

	return true;
}


unsigned  int  SCTeamSelectEnterResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECTENTER_RESULT_;
}

bool  SCTeamSelectEnterResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamSelectEnterResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//事件抛出
	TEAMBATTLEDATAHANDLER->ToClientEnterTeamSelectResult();

	return true;
}


unsigned  int SCTeamSelectGetListPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_TEAMLIST_;
}

bool  SCTeamSelectGetListPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(TEAMBATTLEDATAHANDLER->m_pTeamListData == NULL)
	{
		LOGGERSYSTEM->LogInfo("SCTeamSelectGetListPacket----TEAMBATTLEDATAHANDLER->m_pTeamListData = NULL\n");
		TEAMBATTLEDATAHANDLER->m_pTeamListData = new TTeamListData();

	}
	TEAMBATTLEDATAHANDLER->m_pTeamListData->decodePacketData(packet);

	return true;
}

unsigned  int  SCTeamSelectGetListPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_TEAMLIST_;
}

bool  SCTeamSelectGetListPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamSelectGetListPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//事件抛出
	TEAMBATTLEDATAHANDLER->ToClientGetTeamList();

	return true;
}


/************************************************************************/
/* 加入或者创建队伍                                                     */
/************************************************************************/
CSTeamSelectJoinTeamPacket::CSTeamSelectJoinTeamPacket(int teamId) : m_teamId(teamId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSTeamSelectJoinTeamPacket::~CSTeamSelectJoinTeamPacket()
{

}

unsigned  int  CSTeamSelectJoinTeamPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_JOINTEAM_;
}

unsigned  int  CSTeamSelectJoinTeamPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_teamId);
}

void  CSTeamSelectJoinTeamPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_teamId);
	NETSYSTEM->SendPacket(pNode);
}


unsigned  int SCTeamSelectJoinTeamResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_JOINTEAMRESULT_;
}


bool  SCTeamSelectJoinTeamResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//收到我的队伍
// 	if(TEAMBATTLE_DATAHANDLER->m_pMyTeamData)
// 	{
// 		delete TEAMBATTLE_DATAHANDLER->m_pMyTeamData;
// 	}
// 	TEAMBATTLE_DATAHANDLER->m_pMyTeamData = new TMyTeamData();
// 	TEAMBATTLE_DATAHANDLER->m_pMyTeamData->decodePacketData(packet);

	if(TEAMBATTLEDATAHANDLER->m_pMyTeamData == NULL)
	{
		TEAMBATTLEDATAHANDLER->m_pMyTeamData = new TMyTeamData();
	}
	TEAMBATTLEDATAHANDLER->m_pMyTeamData->decodePacketData(packet);

	return true;
}


unsigned  int  SCTeamSelectJoinTeamResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_JOINTEAMRESULT_;
}

bool  SCTeamSelectJoinTeamResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamSelectJoinTeamResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//事件抛出，获得我的队伍信息
	TEAMBATTLEDATAHANDLER->ToClientJoinTeamResult();

	return true;
}


/************************************************************************/
/* 关闭队伍列表及我的队伍刷新                                           */
/************************************************************************/
CSTeamSelectStopTeamSyncPacket::CSTeamSelectStopTeamSyncPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
unsigned  int  CSTeamSelectStopTeamSyncPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_STOPTEAMSYNC_;
}

unsigned  int  CSTeamSelectStopTeamSyncPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSTeamSelectStopTeamSyncPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 移除队员，-1解散队伍；-2离开队伍； >0移除                            */
/************************************************************************/
CSTeamSelectRemoveMemberPacket::CSTeamSelectRemoveMemberPacket(int playerId):m_playerId(playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
unsigned  int  CSTeamSelectRemoveMemberPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_REMOVEMEMBER_;
}

unsigned  int  CSTeamSelectRemoveMemberPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_playerId);
}

void  CSTeamSelectRemoveMemberPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_playerId);
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 移除队员，对被移除队员的反馈                                         */
/************************************************************************/
unsigned  int SCTeamSelectBeRemovedPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_BEREMOVED_;
}

bool  SCTeamSelectBeRemovedPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	char removedType = 0;
	packet>>removedType;

	//事件抛出
	TEAMBATTLEDATAHANDLER->ToClientBeRemoved(removedType);

	return true;
}


unsigned  int  SCTeamSelectBeRemovedPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_BEREMOVED_;
}

bool  SCTeamSelectBeRemovedPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTeamSelectBeRemovedPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 改变出战顺序						                                      */
/************************************************************************/
CSTeamSelectReorderTeamPacket::CSTeamSelectReorderTeamPacket(std::vector<int> & vec):m_playerIdVector(vec)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	count = (unsigned char)m_playerIdVector.size();
}
unsigned  int  CSTeamSelectReorderTeamPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_REORDERTEAM_;
}

unsigned  int  CSTeamSelectReorderTeamPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(count) + sizeof(int) * m_playerIdVector.size();
}

void  CSTeamSelectReorderTeamPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(count);
	for(int i = 0; i < count; ++i)
	{
		pNode->push(m_playerIdVector[i]);
	}
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 开始关卡                                                             */
/************************************************************************/
CSTeamSelecStartStagePacket::CSTeamSelecStartStagePacket(int serialId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_serialId = serialId;
}
unsigned  int  CSTeamSelecStartStagePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_TEAMSELECT_START_STAGE_;
}

unsigned  int  CSTeamSelecStartStagePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId);
}

void  CSTeamSelecStartStagePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	NETSYSTEM->SendPacket(pNode);
}


