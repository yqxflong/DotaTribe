//Name£ºSCQuickAccountRegisterPacket
//Function£ºs->c ACCOUNT_FAST_REGISTER_SERVER 
//Author : lvyunlong

#include <cocos2d.h>
#include "../include/SCQuickAccountRegisterPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/NetSystem.h"
#include "../include/CSEnterGamePacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/CSRolelistPacket.h"
#include "../include/VariableSystem.h"

using namespace std;
using namespace cobra_win;


unsigned  int  SCQuickAccountRegisterPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FAST_REGISTER_SERVER_;
}


unsigned  int  SCQuickAccountRegisterPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCQuickAccountRegisterPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	SERVERINFODATAINFO->decodePacketData_QuickRegister(packet);
	return true;
}

unsigned  int  SCQuickAccountRegisterPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FAST_REGISTER_SERVER_;
}

bool  SCQuickAccountRegisterPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCQuickAccountRegisterPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	SERVERINFODATAINFO->HandleAfterQuickRegister();
	return true;
}

