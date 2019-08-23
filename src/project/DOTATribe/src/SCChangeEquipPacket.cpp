//Name��SCRoleInfoPacket
//Function��s->c ����װ���󣬽�ɫ��Ϣ
//Written By����ǿ
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
* ʧ�� ['Z''R'][n][2004][int���к�][int -1][string failureInfo]
* �ɹ� ['Z''R'][n][2004][int���к�][int  1][int count]{[byte type][int attrvalue]}
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
