#include "../include/LimitActivityPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/MemNode.h>
#include <include/mem/DPacket.h>

CSExchangePacket::CSExchangePacket(std::string cdkey)
{
	PushData(cdkey);
}

unsigned  int  CSExchangePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EXCHANGE_CDKEY_;
}

bool  SCExchangePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	char result = 0;
	packet>>result;

	return true;
}

unsigned  int SCExchangePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EXCHANGE_CDKEY_RESULT_;
}

bool  SCExchangePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCExchangePacket pa;
	if(!pa.Read(pBuffer, iLen))
	{
		return false;
	}

	return true;
}