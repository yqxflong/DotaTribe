//Name：SCOffEquipPacket
//Function：s->c 卸掉装备后，角色信息
//Written By：尹强
#include <cocos2d.h>
#include "../include/SCOffEquipPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

using  namespace  cobra_win;


unsigned  int  SCOffEquipPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_OFFEQUIP_;
}

unsigned  int  SCOffEquipPacket::GetPacketLength()
{
	return sizeof(int);
}

/*
* 失败 不走此流程，走统一处理异常流程
* 成功 ['Z''R'][n][2008][int序列号][int  1][byte count]{[byte type][int attrvalue]} 
*/
bool  SCOffEquipPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_serial;
	unsigned char heroPos=0;
	packet>>heroPos;

	NFC_GetHeroEquipManager(heroPos)->decodePacketData_OffEquip(packet);
	NFC_GetHeroAttributeManager(heroPos)->decodePacketData_ChangeEquip(packet,heroPos);
	NFC_GetHeroEquipManager(heroPos)->HanldeAfterOffEquip();
	return true;
}

unsigned  int SCOffEquipPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_OFFEQUIP_;
}

bool SCOffEquipPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCOffEquipPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	return true;
}
