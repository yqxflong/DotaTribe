//Name£ºSCRegisterAccountPacket
//Function£ºs->c »ØÓ¦ÕËºÅ×¢²á
//Author : lvyunlong

#include <cocos2d.h>
#include "../include/NFControlsManager.h"
#include "../include/SCRegisterAccountPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/MessageBoxWindow.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
using namespace cobra_win;


unsigned  int  SCRegisterAccountPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACCOUNT_REGISTER_;
}

unsigned  int  SCRegisterAccountPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCRegisterAccountPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>result_;
	return true;
}


unsigned  int  SCRegisterAccountPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACCOUNT_REGISTER_;
}

bool  SCRegisterAccountPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRegisterAccountPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

