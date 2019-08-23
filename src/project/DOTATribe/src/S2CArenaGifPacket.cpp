#include <cocos2d.h>
#include "../include/S2CArenaGifPacket.h"
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
#include "../include/ArenaInfoDataHandler.h"

using namespace cobra_win;


unsigned  int  S2CArenaGifPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_GET_REWARD_SERVER_;
}


unsigned  int  S2CArenaGifPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CArenaGifPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 

	if(!LoadArenaGifData(packet))
	{ 
		return false;
	}
	return true;
}



bool	S2CArenaGifPacket::LoadArenaGifData(cobra_win::DPacket & packetData)
{

	if(ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas())
	{
		int  arenaRewardDistanceTime=0;
		packetData.read(arenaRewardDistanceTime);
		arenaRewardDistanceTime/=1000;
		ArenaRewardDataHandler::get_instance2()->getArenaRewardDatas()->setArenaGetRewardDistance(arenaRewardDistanceTime);
		return true;
	}  
	return false;
}


unsigned  int  S2CArenaGifPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_GET_REWARD_SERVER_;
}


bool  S2CArenaGifPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CArenaGifPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	PostNotification(); 
	return true;
}

void   S2CArenaGifPacketFactory::PostNotification()
{   
	EventSystem::get_instance2()->PushEvent(_TYPEF_EVENT_UPDATE_REWARDDISTANCE_);
}







