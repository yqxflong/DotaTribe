//Name:GrowupPlanPacket
//Author: lvyunlong
//Func: Activity of grow up plan activity net packet
//Maintainer:lvyunlong

#include <cocos2d.h>
#include "../include/GrowupPlanPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/ActivityDataHandler.h"
#include "../include/NFControlsManager.h"
/************************************************************************/
/* 每日登陆请求信息返回           3123							        */
/************************************************************************/

bool  SCGrowupPlanInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//附件信息
	GROWUPPLANDATAHANDLER->ReceiveGrowupInfo(packet);
	return true;
}

unsigned  int  SCGrowupPlanInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_GROWUPPLAN_;
}

bool  SCGrowupPlanInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGrowupPlanInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_GROWUPPLANACTIVITYWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 购买成长计划请求信息           3124  3125                             */
/************************************************************************/
CSBuyGrowupPlanPacket::CSBuyGrowupPlanPacket()
{

}

CSBuyGrowupPlanPacket::~CSBuyGrowupPlanPacket()
{	

}

unsigned  int  CSBuyGrowupPlanPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_REQUEST_BUYGROWPLANREWARD_;
}

bool  SCBuyGrowupPlanPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	return true;
}

unsigned  int  SCBuyGrowupPlanPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_BUYGROWPLANREWARD_;
}

bool  SCBuyGrowupPlanPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBuyGrowupPlanPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	GROWUPPLANDATAHANDLER->m_isBuyPlan = 1;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_GROWUPPLANACTIVITYWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 领取成长计划奖励请求信息           3126  3127						    */
/************************************************************************/
CSGetGrowupPlanRewardPacket::CSGetGrowupPlanRewardPacket(int level)
{
	PushData(level);
}

CSGetGrowupPlanRewardPacket::~CSGetGrowupPlanRewardPacket()
{	

}

unsigned  int  CSGetGrowupPlanRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_REQUEST_GETGROWPLAN_;
}

bool  SCGetGrowupPlanRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	int level = 0;
	packet>>level;

	GROWUPPLANDATAHANDLER->GetPlanRewardBack(level);

	return true;
}

unsigned  int  SCGetGrowupPlanRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_GETGROWPLAN_;
}

bool  SCGetGrowupPlanRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGetGrowupPlanRewardPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	return true;
}