//Name:BagWindowPacket
//Function:背包系统的通讯包
//Author:fangjun
//Date:20130909
#include <cocos2d.h>
#include "../include/BagWindowPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>

unsigned int CSOpenLockBagPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_OPEN_LOCKBAG_;
}

unsigned int CSOpenLockBagPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_iBagIndex);
}

void CSOpenLockBagPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_iBagType);
	pNode->push(m_iBagIndex);
	NETSYSTEM->SendPacket(pNode);
}