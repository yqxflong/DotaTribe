//Name：SCRolelistPacket
//Function：s->c 回应角色列表
//Author : lvyunlong

#include <cocos2d.h>
#include "../include/SCRolelistPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/LoginProcedure.h"
#include "../include/NetSystem.h"
#include "../include/CSEnterGamePacket.h"
#include "../include/DOTATribeApp.h"
using namespace cobra_win;


unsigned  int  SCRolelistPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ROLELIST_;
}


unsigned  int  SCRolelistPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCRolelistPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	SERVERINFODATAINFO->decodePacketData_Rolelist(packet);
	return true;
}

unsigned  int  SCRolelistPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ROLELIST_;
}

bool  SCRolelistPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRolelistPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	SERVERINFODATAINFO->HandleAfterRoleList();
	return true;
}

