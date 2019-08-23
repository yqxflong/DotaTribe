#include <cocos2d.h>
#include   "../include/S2CArenaInfoPacket.h"
#include "../include/PacketTyper.h"
#include  <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/LoginProcedure.h"
#include "../include/NetSystem.h"
#include "../include/CSEnterGamePacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include "../include/ArenaInfoDataHandler.h"

using namespace cobra_win;


unsigned  int  S2CArenaInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2S_ARENA_INFO_SERVER_;
}


unsigned  int  S2CArenaInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CArenaInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial;


	//如果当前的流程为竞技场流程册 直接退出不进行
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_ARENA_PROCEDURE_)
	{  
		return false;
	}
	if(!LoadArenaInfoData(packet))
	{ 
		return false;
	}
	return true;
}



bool	S2CArenaInfoPacket::LoadArenaInfoData(cobra_win::DPacket & packetData)
{
	if(ArenaInfoDataHandler::get_instance2()!=NULL)
	{
        if(ArenaInfoDataHandler::get_instance2()->PArenaInfoData!=NULL)
		{
			ArenaInfoDataHandler::get_instance2()->PArenaInfoData->destroy();
			delete 	ArenaInfoDataHandler::get_instance2()->PArenaInfoData;
			ArenaInfoDataHandler::get_instance2()->PArenaInfoData=NULL;
		}
  
		ArenaInfoDataHandler::get_instance2()->PArenaInfoData=new ArenaInfoData();
		if(ArenaInfoDataHandler::get_instance2()->PArenaInfoData!=NULL)
		ArenaInfoDataHandler::get_instance2()->PArenaInfoData->decodePacketData(packetData);	
 	}
     return true;
}
 

unsigned  int  S2CArenaInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2S_ARENA_INFO_SERVER_;
}
 

bool  S2CArenaInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CArenaInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	PostShowArenaSceneNotification();
    
	return true;
}

void   S2CArenaInfoPacketFactory::PostShowArenaSceneNotification()
{ 
	char athleticsProcedure[8]={0};
	sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_ARENA_PROCEDURE_);
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);
 
}


//////////////////////////////////////////////////////////////////////////

unsigned  int  S2CArenaRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_REWARD_SERVER_;
}
 
unsigned  int  S2CArenaRewardPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CArenaRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	 
 
	if(!LoadArenaRewardData(packet))
	{ 
		return false;
	}
	return true;
}

 
bool	S2CArenaRewardPacket::LoadArenaRewardData(cobra_win::DPacket & packetData)
{ 
	ArenaRewardDataHandler::get_instance2()->decodePacketData(packetData); 
	return true;
} 

//////////////////////////////////////////////////////////////////////////

unsigned  int  S2CArenaRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_REWARD_SERVER_;
}
 
bool  S2CArenaRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CArenaRewardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	PostShowArenaRewardNotification(); 
	return true;
}

void   S2CArenaRewardPacketFactory::PostShowArenaRewardNotification()
{  
	 EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_ARENAREWARDWINDOW_);
}

//////////////////////////////////////////////////////////////////////////
 
unsigned  int  S2CChallenegeCountRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_GET_CHALLENGECOUNT_REWARD_;
}

unsigned  int  S2CChallenegeCountRewardPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CChallenegeCountRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	 
	if(!LoadConfimData(packet))
	{ 
		return false;
	}
	return true;
}


bool	S2CChallenegeCountRewardPacket::LoadConfimData(cobra_win::DPacket & packetData)
{   
	short   receiptResult=0;
	packetData.read(receiptResult);
	if(receiptResult==0)
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_ARENAREWARDWINDOW_,_to_event_param_(0));
	else
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_ARENAREWARDWINDOW_,_to_event_param_(1));
	return true;
} 

//////////////////////////////////////////////////////////////////////////

unsigned  int  S2CChallenegeCountRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ARENA_GET_CHALLENGECOUNT_REWARD_;
}

bool  S2CChallenegeCountRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CChallenegeCountRewardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	return true;
}

 
 
