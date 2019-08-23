//Name:Vip.h
//Function:Vip网络包
//Author: lvyunlong
//Date: 20131211

#include <cocos2d.h>
#include "../include/HeroteamChangePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/NFControlsManager.h"
/************************************************************************/
/* 请求VIP信息  6001,6002                                               */
/************************************************************************/
CSHeroteamChangePacket::CSHeroteamChangePacket(unsigned char index1,unsigned char index2)
{
	PushData(index1);
	PushData(index2);
}

CSHeroteamChangePacket::~CSHeroteamChangePacket()
{

}

unsigned  int  CSHeroteamChangePacket::GetPacketType()
{
	return _TYPE_PACKET_C2S_HEROTEAMCHANGE_;
}

bool  SCHeroteamChangePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//索引
	unsigned char index1 = 0;
	packet>>index1;
	unsigned char index2 = 0;
	packet>>index2;
	//交换英雄返回
	unsigned char result = 0;
	packet>>result;
	if (1 == result)
	{
		NFC_SetHeroChangeManager(index1,index2);
	}
	return true;
}

unsigned  int  SCHeroteamChangePacketFactory::GetPacketType()
{
	return _TYPE_PACKET_S2C_HEROTEAMCHANGE_RESULT_;
}

bool  SCHeroteamChangePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroteamChangePacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_TEAMINFOWINDOW_);

	return true;
}
