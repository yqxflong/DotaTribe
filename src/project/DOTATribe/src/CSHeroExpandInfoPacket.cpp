#include   <cocos2d.h>
#include   "../include/CSHeroExpandInfoPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>
#include	"../include/EventSystem.h"
#include	"../include/EventTyper.h"
#include	"../include/RoleHeroSkinsDataHandler.h"
#include	<include/mem/DPacket.h>
#include "../include/NFControlsManager.h"
 

CSHeroExpandInfoPacket::CSHeroExpandInfoPacket(int heroUniqueID)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
	m_nHeroUniqueID=heroUniqueID;
}

unsigned  int  CSHeroExpandInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERO_INFO_CLIENT_;
}

unsigned  int  CSHeroExpandInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) +sizeof(m_nHeroUniqueID);
}

bool  CSHeroExpandInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSHeroExpandInfoPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_nHeroUniqueID); 
	NETSYSTEM->SendPacket(pNode);
}


//////////////////////////////////////////////////////////////////////////

  
unsigned  int  SCHeroExpandInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_INFO_SERVER_;
}

unsigned  int  SCHeroExpandInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCHeroExpandInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 

	//开始同步英雄数据
	int  heorUniqueID=0;
	packet.read(heorUniqueID);
	 
	IHeroSkinItem * pHeroSkinItem=RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(heorUniqueID);
	if(pHeroSkinItem)
	pHeroSkinItem->decodePacketSynInfo(packet); 
	 
	return true;
}



unsigned  int  SCHeroExpandInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_INFO_SERVER_;
}

bool  SCHeroExpandInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroExpandInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
	{
		OnPostNotification(false);
		return false;
	}

	OnPostNotification(true);
	return true;
}

void  SCHeroExpandInfoPacketFactory::OnPostNotification(bool isSynSuccess)
{
	if(isSynSuccess)
	{ 
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_,_to_event_param_(0));
	}
	else
	{ 
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_,_to_event_param_(2));
	}
}



//////////////////////////////////////////////////////////////////////////

//请求更换英雄

CSReplaceHeroRequestPacket::CSReplaceHeroRequestPacket(int heroUniqueID,unsigned char heroPos)
{
	PushData(heroUniqueID); 
	PushData(heroPos);
}

unsigned  int  CSReplaceHeroRequestPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_REPLACE_HERO_CLIENT_;
}


//////////////////////////////////////////////////////////////////////////


unsigned  int  SCReplaceHeroPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_REPLACE_HERO_SERVER_;
}

unsigned  int  SCReplaceHeroPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCReplaceHeroPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 

	//开始同步英雄数据
	int  heorUniqueID=0;
	unsigned char heroPos = 0;
	packet.read(heroPos);
	unsigned char isnewhero = 0;
	packet.read(isnewhero);
	if(isnewhero == 0)
	{
		IHeroSkinItem * pHeroSkinItem = new IHeroSkinItem;
		pHeroSkinItem->decodePacketBaseData(packet,true);
		ROLEHEROSKINSDATAHANDLER->GetHeroVector().push_back(pHeroSkinItem);
	}
	else
	{
		packet.read(heorUniqueID);
		IHeroSkinItem * pHeroSkinItem=ROLEHEROSKINSDATAHANDLER->GetHeroVector()[heroPos];
		pHeroSkinItem->setHeroUniqueID(heorUniqueID);
		if(pHeroSkinItem)
		{ 
			pHeroSkinItem->decodePacketSynInfo(packet);
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

unsigned  int  SCReplaceHeroPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_REPLACE_HERO_SERVER_;
}

bool  SCReplaceHeroPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCReplaceHeroPacket packet;
	if (!packet.Read(pBuffer, iLen))
	return false;
	 
	OnPostNotification(true);
	return true;
}

void  SCReplaceHeroPacketFactory::OnPostNotification(bool isSynSuccess)
{ 
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_,_to_event_param_(1));
	NFC_showCommunicationWating(false);
}
