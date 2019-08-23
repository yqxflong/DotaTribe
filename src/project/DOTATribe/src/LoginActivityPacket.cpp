//Name:LoginActivityPacket
//Author: lvyunlong
//Func: Activity of login activity net packet
//Maintainer:lvyunlong

#include <cocos2d.h>
#include "../include/LoginActivityPacket.h"
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
/* 每日登陆请求信息返回           3119							        */
/************************************************************************/

bool  SCLoginActivityPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//附件信息
	unsigned char hasreward = 0;
	packet>>hasreward;
	LOGINREWARDDATAHANDLER->m_Hasreward = hasreward;
	LOGINREWARDDATAHANDLER->ToServerRewardList(packet);
	return true;
}

unsigned  int  SCLoginActivityPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_LOGINLIST_RESULT_;
}

bool  SCLoginActivityPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCLoginActivityPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LOGINACTIVITYWINDOW_);

	return true;
}

/************************************************************************/
/* 领取登陆奖励请求信息           3121  3122                             */
/************************************************************************/
CSGetLoginRewardPacket::CSGetLoginRewardPacket()
{

}

CSGetLoginRewardPacket::~CSGetLoginRewardPacket()
{	

}

unsigned  int  CSGetLoginRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_REQUEST_LOGINREWARD_;
}

bool  SCGetLoginRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	return true;
}

unsigned  int  SCGetLoginRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_LOGINREWARD_;
}

bool  SCGetLoginRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGetLoginRewardPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	LOGINREWARDDATAHANDLER->m_Hasreward = 1;
	int id = LOGINREWARDDATAHANDLER->getLoginRewardActiviId();
	ActivityInfoItem* item = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(id);
	item->setActivityOpen(0);
	if (item->getActivityOpen() == 0)
	{
		ActivityDataHandler::get_instance2()->HasSurplusActivity();
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEEFFECT_ACTIVITY_,_to_event_param_(id));
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LOGINACTIVITYWINDOW_);
	return true;
}
