//Name:GetItemPacket
//Function: 获得物品效果数据来源
//Author:尹强
#include <cocos2d.h>
#include "../include/GetItemPacket.h"
#include "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>
#include "../include/EffectDataHandler.h"

unsigned  int  SCGetItemPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETITEM_;
}

unsigned  int  SCGetItemPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCGetItemPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	EFFECTDATAHANDLER->decodePacketData(packet);

	return true;
}

unsigned  int  SCGetItemPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETITEM_;
}

bool  SCGetItemPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGetItemPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	EFFECTDATAHANDLER->HandleAfterOnePacket();
	return true;
}
