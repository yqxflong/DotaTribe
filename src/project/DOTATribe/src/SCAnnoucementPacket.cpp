#include <cocos2d.h>
#include "../include/SCAnnoucementPacket.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/LoggerSystem.h"
#include  "../include/IProcedure.h"
#include  "../include/PacketTyper.h"
#include  "../include/NetSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/EventSystem.h"
#include  "../include/VariableSystem.h"
#include  "../include/AnnouncementDataHandler.h"
#include   <include/mem/DPacket.h> 

#include  "../include/CPublicVarReader.h"

unsigned  int  SCAnnoucementPacket::GetPacketType()
{
	return  _TYPED_PACKET_S2C_ANNOUNCEMENT_MESSAGE_SERVER_;
}

bool  SCAnnoucementPacket::Read(char* pBuffer, unsigned int iLen)
{ 
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	AnnoucementDataHandler::get_instance2()->decodePacket(packet);
	return true;
}

//////////////////////////////////////////////////////////////////////////
  
unsigned  int  SCAnnoucementPacketFactory::GetPacketType()
{
	return  _TYPED_PACKET_S2C_ANNOUNCEMENT_MESSAGE_SERVER_;
} 
/*
数据包处理操作
*/
bool  SCAnnoucementPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAnnoucementPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	return true;
}
 
 