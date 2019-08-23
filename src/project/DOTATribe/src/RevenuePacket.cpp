// Name :		RevenuePacket.h
// Function:	点金消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/RevenuePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../Include/RevenueDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SRevenuePacket::C2SRevenuePacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SRevenuePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_REVENUE_;
}

unsigned  int  C2SRevenuePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SRevenuePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SRevenuePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);


	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CRevenuePacket::S2CRevenuePacket()
{

}

S2CRevenuePacket::~S2CRevenuePacket()
{

}

unsigned  int  S2CRevenuePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_REVENUERESULT_;
}

unsigned  int  S2CRevenuePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CRevenuePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>RevenueDataHandler::get_instance2()->m_Level;
	packet>>RevenueDataHandler::get_instance2()->m_Exp;
	packet>>RevenueDataHandler::get_instance2()->m_maxExp;
	packet>>RevenueDataHandler::get_instance2()->m_FreeTimes;
	packet>>RevenueDataHandler::get_instance2()->m_coolTime;
	packet>>RevenueDataHandler::get_instance2()->m_lowCost;
	packet>>RevenueDataHandler::get_instance2()->m_highCost;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_REVENUEWINDOW_);
	return true;
}


void  S2CRevenuePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CRevenuePacketFactory::S2CRevenuePacketFactory()
{

}


S2CRevenuePacketFactory::~S2CRevenuePacketFactory()
{

}

unsigned  int S2CRevenuePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_REVENUERESULT_;
}

bool S2CRevenuePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CRevenuePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CRevenuePacketHandler(&packet);
	return true;
}	

void S2CRevenuePacketFactory::OnS2CRevenuePacketHandler(S2CRevenuePacket* pPacket)
{

}
