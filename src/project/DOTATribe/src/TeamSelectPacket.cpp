//Name:TeamSelectPacket
//Function: ��Ӹ�����ӽ���
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
/* ��ȡ�����б���Ϣ                                                     */
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
	//��ȡ����
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//�ؿ�id
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

	//�¼��׳�
	TEAMBATTLEDATAHANDLER->ToClientEnterTeamSelectResult();

	return true;
}


unsigned  int SCTeamSelectGetListPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_TEAMLIST_;
}

bool  SCTeamSelectGetListPacket::Read(char* pBuffer, unsigned int iLen)
{
	//��ȡ����
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

	//�¼��׳�
	TEAMBATTLEDATAHANDLER->ToClientGetTeamList();

	return true;
}


/************************************************************************/
/* ������ߴ�������                                                     */
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
	//��ȡ����
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//�յ��ҵĶ���
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

	//�¼��׳�������ҵĶ�����Ϣ
	TEAMBATTLEDATAHANDLER->ToClientJoinTeamResult();

	return true;
}


/************************************************************************/
/* �رն����б��ҵĶ���ˢ��                                           */
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
/* �Ƴ���Ա��-1��ɢ���飻-2�뿪���飻 >0�Ƴ�                            */
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
/* �Ƴ���Ա���Ա��Ƴ���Ա�ķ���                                         */
/************************************************************************/
unsigned  int SCTeamSelectBeRemovedPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TEAMSELECT_BEREMOVED_;
}

bool  SCTeamSelectBeRemovedPacket::Read(char* pBuffer, unsigned int iLen)
{
	//��ȡ����
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	char removedType = 0;
	packet>>removedType;

	//�¼��׳�
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
/* �ı��ս˳��						                                      */
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
/* ��ʼ�ؿ�                                                             */
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


