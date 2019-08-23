//Name:Vip.h
//Function:Vip�����
//Author: lvyunlong
//Date: 20131211

#include <cocos2d.h>
#include "../include/VipInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/VipControlDataHandler.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
/************************************************************************/
/* ����VIP��Ϣ  1220,1221                                               */
/************************************************************************/
CSVipInfoPacket::CSVipInfoPacket()
{
	
}

CSVipInfoPacket::~CSVipInfoPacket()
{

}

unsigned  int  CSVipInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERO_VIPINFO_CLIENT_;
}

bool  SCVipInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//VIp��Ϣ
	packet>>VIPCONTROLDATAHANDLER->m_exp;
	packet>>VIPCONTROLDATAHANDLER->m_maxExp;
	packet>>VIPCONTROLDATAHANDLER->m_isBGetReward; 
	return true;
}

unsigned  int  SCVipInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_VIPINFO_RESULT_;
}

bool  SCVipInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCVipInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_VIPWINDOW_);
	if(WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_RECHARGE_WINDOW_))
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_VIPTEXT_RECHARGEWINDOW_);
	}
	return true;
}

/************************************************************************/
/* ����VIP��ȡ����  1224,1225                                            */
/************************************************************************/
CSVipRewardPacket::CSVipRewardPacket()
{

}

CSVipRewardPacket::~CSVipRewardPacket()
{

}

unsigned  int  CSVipRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERO_GETREWARD_CLIENT_;
}

bool  SCVipRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	return true;
}

unsigned  int  SCVipRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERO_GETREWARD_RESULT_;
}

bool  SCVipRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCVipRewardPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_VIPWINDOW_,_to_event_param_(1));
	return true;
}

