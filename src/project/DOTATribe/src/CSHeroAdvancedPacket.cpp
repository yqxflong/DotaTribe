#include   <cocos2d.h>
#include   "../include/CSHeroAdvancedPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>
#include	"../include/EventSystem.h"
#include	"../include/EventTyper.h"
#include	"../include/RoleHeroSkinsDataHandler.h"
#include	"../include/HeroAdvancedDataHandler.h"
#include	<include/mem/DPacket.h>
#include "../include/NFControlsManager.h"


CSHeroAdvancedPacket::CSHeroAdvancedPacket(int heroGroupID)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
	m_heroGroupId=heroGroupID;
}

unsigned  int  CSHeroAdvancedPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERO_ADVANCED_REQUIRE_CLIENT_;
}

unsigned  int  CSHeroAdvancedPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) +sizeof(m_heroGroupId);
}

bool  CSHeroAdvancedPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSHeroAdvancedPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_heroGroupId); 
	NETSYSTEM->SendPacket(pNode);
}


//////////////////////////////////////////////////////////////////////////


unsigned  int  SCHeroAdvancedPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_ADVANCE_REQUIRE_SERVER_;
}

unsigned  int  SCHeroAdvancedPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCHeroAdvancedPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;  

	HEROADVANCEDATAHANDLER->decodePacketData(packet);
	  
	return true;
}



unsigned  int  SCHeroAdvancedPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_ADVANCE_REQUIRE_SERVER_;
}

bool  SCHeroAdvancedPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroAdvancedPacket packet;
	if (!packet.Read(pBuffer, iLen))
	return false;
	OnPostNotification();
	return true;
}

void  SCHeroAdvancedPacketFactory::OnPostNotification()
{  
   EVENTSYSTEM->PushEvent2(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_,_to_event_param_(3));
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

 
CSHeroAdvanceVerifyPacket::CSHeroAdvanceVerifyPacket(int heroGroupID)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
	m_heroGroupId=heroGroupID;
}

unsigned  int  CSHeroAdvanceVerifyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERO_ADVANCE_CLIENT_;
}

unsigned  int  CSHeroAdvanceVerifyPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) +sizeof(m_heroGroupId);
}

bool  CSHeroAdvanceVerifyPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSHeroAdvanceVerifyPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_heroGroupId); 
	NETSYSTEM->SendPacket(pNode);
}


//////////////////////////////////////////////////////////////////////////


unsigned  int  SCHeroAdvanceVerifyPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_ADVANCE_SERVER_;
}

unsigned  int  SCHeroAdvanceVerifyPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCHeroAdvanceVerifyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;   
	return true;
}



unsigned  int  SCHeroAdvanceVerifyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_ADVANCE_SERVER_;
}

bool  SCHeroAdvanceVerifyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroAdvanceVerifyPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	OnPostNotification();
	return true;
}

void  SCHeroAdvanceVerifyPacketFactory::OnPostNotification()
{   
	//to do
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_UPDATE_HeroAdvancedWindow_,_to_event_param_(0));	 
}
