#include <cocos2d.h>
#include "../include/SCBagUseObjectResultPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
using namespace cobra_win;


unsigned  int  SCBagUseObjectResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_USEOBJECT_;
}

unsigned  int  SCBagUseObjectResultPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCBagUseObjectResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	int serial = 0;
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	packet>>serial;

	//策划确认不用提示用户	0807

	return true;
}



unsigned  int  SCBagUseObjectResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_USEOBJECT_;
}

bool  SCBagUseObjectResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBagUseObjectResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	return true;
}

