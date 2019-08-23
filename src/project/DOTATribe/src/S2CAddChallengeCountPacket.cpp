#include  <cocos2d.h>
#include  "../include/S2CAddChallengeCountPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include  "../include/AddChallengeDataHandler.h"

using  namespace  cobra_win;


unsigned  int  S2CAddChallengeCountPacket::GetPacketType()
{
	return _TYPEF_PACKET_S2C_ARENA_ADD_CHALLENGECOUNT_SERVER_;
}

unsigned  int  S2CAddChallengeCountPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CAddChallengeCountPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	if(AddChallengeDataHandler::get_instance2()!=NULL)	 
	packet.read(AddChallengeDataHandler::get_instance2()->addChallenegeCount); 
	 
	return true;

} 


unsigned  int S2CAddChallengeCountPacketFactory::GetPacketType()
{
	return _TYPEF_PACKET_S2C_ARENA_ADD_CHALLENGECOUNT_SERVER_;
}

bool S2CAddChallengeCountPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CAddChallengeCountPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	OnFinishCallBackHandler();
	return true;
}	 

void  S2CAddChallengeCountPacketFactory::OnFinishCallBackHandler()
{
	//发出消息更新ArenaUI
	EventSystem::get_instance2()->PushEvent(_TYPEF_EVENT_UPDATE_ADDCHALLENGE_);
}
