//Name:FirstRechGiftPacket
//Author: lvyunlong
//Func: Activity of first recharge get gift net packet
//Maintainer:lvyunlong

#include <cocos2d.h>
#include "../include/FirstRechGiftPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/ActivityDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/ActivityPacket.h"
/************************************************************************/
/* 首充活动礼包请求信息          2215  2216                              */
/************************************************************************/
CSFirstRechInfoPacket::CSFirstRechInfoPacket()
{

}

CSFirstRechInfoPacket::~CSFirstRechInfoPacket()
{	

}

unsigned  int  CSFirstRechInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FIRSTRECHGIFT_;
}

bool  SCFirstRechInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//附件信息
	FIRSTRECHDATAHANDLER->ReadGiftListInfo(packet);
	return true;
}

unsigned  int  SCFirstRechInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FIRSTRECHGIFT_RESULT_;
}

bool  SCFirstRechInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCFirstRechInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FIRSTRECHGIFTWINDOW_);

	return true;
}

/************************************************************************/
/* 领取首充礼包请求信息           2217  2218                             */
/************************************************************************/
CSGetFirstGiftPacket::CSGetFirstGiftPacket()
{

}

CSGetFirstGiftPacket::~CSGetFirstGiftPacket()
{	
	
}

unsigned  int  CSGetFirstGiftPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_GETFIRSTRECH_;
}

bool  SCGetFirstGiftPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	return true;
}

unsigned  int  SCGetFirstGiftPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETFIRSTRECH_RESULT_;
}

bool  SCGetFirstGiftPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGetFirstGiftPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);

	unsigned int id = FIRSTRECHDATAHANDLER->getFirstRechActiviId();
	ActivityInfoItem * pActivityInfo = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(id);
	pActivityInfo->setActivityOpen(0);
	ActivityDataHandler::get_instance2()->HasSurplusActivity();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_DELETE_ACTIVITY_);

	return true;
}

