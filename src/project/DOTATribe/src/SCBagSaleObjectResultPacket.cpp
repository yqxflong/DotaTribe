#include <cocos2d.h>
#include "../include/SCBagSaleObjectResultPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/NFControlsManager.h"
using namespace cobra_win;


unsigned  int  SCBagSaleObjectResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SALEOBJECT_;
}

unsigned  int  SCBagSaleObjectResultPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCBagSaleObjectResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	int serial = 0;
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	packet>>serial;

	//策划确认不用提示用户	0806

	return true;
}



unsigned  int  SCBagSaleObjectResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SALEOBJECT_;
}

bool  SCBagSaleObjectResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBagSaleObjectResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(true);
	return true;
}

