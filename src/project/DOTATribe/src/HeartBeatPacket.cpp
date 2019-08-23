//Name:HeartBeatPacket
//Function: 心跳检测包
//Author:fangjun
//Date:20130819
#include <cocos2d.h>
#include "../include/HeartBeatDataHandler.h"
#include "../include/HeartBeatPacket.h"
#include "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>

CSHeartBeatPacket::CSHeartBeatPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSHeartBeatPacket::~CSHeartBeatPacket()
{
}

unsigned  int  CSHeartBeatPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEARTBEAT_;
}

unsigned  int  CSHeartBeatPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

bool  CSHeartBeatPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSHeartBeatPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}


SCHeartBeatResultPacket::SCHeartBeatResultPacket()
{

}

SCHeartBeatResultPacket::~SCHeartBeatResultPacket()
{

}

unsigned  int  SCHeartBeatResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEARTBEATRESULT_;
}

unsigned  int  SCHeartBeatResultPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeartBeatResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	//调用HeartBeatDataHandler中的解包
	HEARTBEATDATAHANDLER->decodePacketData(packet);

	return true;
}

void  SCHeartBeatResultPacket::Send()
{
	//no need
}


SCHeartBeatResultPacketFactory::SCHeartBeatResultPacketFactory()
{

}

SCHeartBeatResultPacketFactory::~SCHeartBeatResultPacketFactory()
{

}

unsigned  int  SCHeartBeatResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEARTBEATRESULT_;
}

bool  SCHeartBeatResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeartBeatResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	return true;
}
