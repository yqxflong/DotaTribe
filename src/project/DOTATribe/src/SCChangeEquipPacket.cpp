//Name：SCRoleInfoPacket
//Function：s->c 更换装备后，角色信息
//Written By：尹强
#include <cocos2d.h>
#include "../include/SCChangeEquipPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

using  namespace  cobra_win;


unsigned  int  SCChangeEquipPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHANGEEQUIP_;
}

unsigned  int  SCChangeEquipPacket::GetPacketLength()
{
	return sizeof(int);
}

/*
* 失败 ['Z''R'][n][2004][int序列号][int -1][string failureInfo]
* 成功 ['Z''R'][n][2004][int序列号][int  1][int count]{[byte type][int attrvalue]}
*/
bool  SCChangeEquipPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_serial;
	packet>>m_resultid;
	if(m_resultid==1){
		unsigned char heroPos=0;
		packet>>heroPos;
		NFC_GetHeroAttributeManager(heroPos)->decodePacketData_ChangeEquip(packet, heroPos);
		NFC_GetHeroEquipManager(heroPos)->HanldeAfterChangeEquip();
	}
	return true;
}

unsigned  int SCChangeEquipPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHANGEEQUIP_;
}

bool SCChangeEquipPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCChangeEquipPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	return true;
}
