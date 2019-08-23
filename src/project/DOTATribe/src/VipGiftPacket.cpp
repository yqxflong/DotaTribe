//Name:VipGiftPacket
//Author: lvyunlong
//Func: Activity of vip gift net packet
//Maintainer:lvyunlong

#include <cocos2d.h>
#include "../include/VipGiftPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/ActivityDataHandler.h"
#include "../include/NFControlsManager.h"

/************************************************************************/
/* VIP礼包请求信息           2219  2220		                            */
/************************************************************************/
CSVipGiftInfoPacket::CSVipGiftInfoPacket()
{
	
}

CSVipGiftInfoPacket::~CSVipGiftInfoPacket()
{	

}

unsigned  int  CSVipGiftInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_VIPGIFT_;
}

bool  SCVipGiftInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//Vip链表信息
	VIPGIFTACTIVITYHANDLER->decodePacket(packet);
	VIPGIFTACTIVITYHANDLER->ShowActiviVipList();
	return true;
}

unsigned  int  SCVipGiftInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_VIPGIFT_RESILT;
}

bool  SCVipGiftInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCVipGiftInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_VIPGIFTWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* Vip礼包购买请求信息           2221  2222                              */
/************************************************************************/
CSVipGiftBuyPacket::CSVipGiftBuyPacket(IByte viplevel)
{
	PushData(viplevel);
}

CSVipGiftBuyPacket::~CSVipGiftBuyPacket()
{	

}

unsigned  int  CSVipGiftBuyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_VIPGIFTBUY_;
}

bool  SCVipGiftBuyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	unsigned char level = 0;
	packet>>level;
	VIPGIFTACTIVITYHANDLER->RemoveData(level);
	return true;
}

unsigned  int  SCVipGiftBuyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_VIPGIFTBUY_RESILT;
}

bool  SCVipGiftBuyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCVipGiftBuyPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	if (VIPGIFTACTIVITYHANDLER->m_ActiviVipShowList.size() == 0)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_DELETE_ACTIVITY_);
		return true;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_VIPGIFTWINDOW_);
	return true;
}


/************************************************************************/
/* Vip礼包预览           2223 2224				                        */
/************************************************************************/

CSVipGiftPreViewPacket::CSVipGiftPreViewPacket(int preview)
{
	PushData(preview);
}

CSVipGiftPreViewPacket::~CSVipGiftPreViewPacket()
{

}

unsigned  int  CSVipGiftPreViewPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_VIPGIFT_PREVIEW_;
}
