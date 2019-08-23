#include  <cocos2d.h>
#include   "../include/S2CArenaRankPacket.h"
#include "../include/PacketTyper.h"
#include  <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h" 
#include "../include/LoginProcedure.h"
#include "../include/NetSystem.h" 
#include "../include/DOTATribeApp.h"
#include "../include/ArenaRankDataHandler.h"

using namespace cobra_win;
 
unsigned  int  S2CArenaRankPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENE_RANK_INFO_SERVER_;
}


unsigned  int  S2CArenaRankPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CArenaRankPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial;

	if(!LoadArenaRankData(packet))
	{ 
		return false;
	}
	return true;
}
 

bool	S2CArenaRankPacket::LoadArenaRankData(cobra_win::DPacket & packetData)
{
	if(ARENARANKDATAHANDLER!=NULL)
	{
	   if(ARENARANKDATAHANDLER->m_pArenaRankData!=NULL)
	   {
		   delete ARENARANKDATAHANDLER->m_pArenaRankData;
		   ARENARANKDATAHANDLER->m_pArenaRankData=NULL;
	   }
	   ARENARANKDATAHANDLER->m_pArenaRankData=new ArenaRankData();
	   ARENARANKDATAHANDLER->m_pArenaRankData->decodePacketData(packetData);
	}
	 
	return true;
}


unsigned  int  S2CArenaRankPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENE_RANK_INFO_SERVER_;
}


bool  S2CArenaRankPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CArenaRankPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	PostShowRankWindowNotification();

	return true;
}

void   S2CArenaRankPacketFactory::PostShowRankWindowNotification()
{ 
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_RANKWINDOW_);
}







