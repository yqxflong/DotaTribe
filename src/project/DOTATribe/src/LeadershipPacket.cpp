//Name:LeadershipPacket
//Function: 主线任务包
//Author:尹强

#include "../include/LeadershipPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NetSystem.h"
#include <include/mem/DPacket.h>
#include "../include/RoleInfoDataHandler.h"

/************************************************************************/
/*=====================统率力升级请求=================
/************************************************************************/
CSLeadershipLvupPacket::CSLeadershipLvupPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

unsigned  int  CSLeadershipLvupPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_LEADERSHIPLVUP_;
}
unsigned  int  CSLeadershipLvupPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}
void  CSLeadershipLvupPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);

	NETSYSTEM->SendPacket(pNode);
}


unsigned  int  SCLeadershipLvupPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LEADERSHIPLVUP_;
}

bool  SCLeadershipLvupPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	LeadershipHandler::get_instance2()->decodePacketData(packet);
	return true;
}


unsigned  int  SCLeadershipLvupPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_LEADERSHIPLVUP_;
}

bool  SCLeadershipLvupPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCLeadershipLvupPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	LeadershipHandler::get_instance2()->HandleAfterResult();
	return true;
}