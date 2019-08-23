// Name :		LessResourcePacket.h
// Function:	资源不足消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/LessResourcePacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LessResourceDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SLessResourcePacket::C2SLessResourcePacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SLessResourcePacket::GetPacketType()
{
	return 0;
}

unsigned  int  C2SLessResourcePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SLessResourcePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SLessResourcePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CLessResourcePacket::S2CLessResourcePacket()
{

}

S2CLessResourcePacket::~S2CLessResourcePacket()
{

}

unsigned  int  S2CLessResourcePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LESSRESOURCE_RESULT_;
}

unsigned  int  S2CLessResourcePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CLessResourcePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	LessResourceDataHandler::get_instance2()->decodePacketHandler(packet);
 
	return true;
}


void  S2CLessResourcePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CLessResourcePacketFactory::S2CLessResourcePacketFactory()
{

}


S2CLessResourcePacketFactory::~S2CLessResourcePacketFactory()
{

}

unsigned  int S2CLessResourcePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_LESSRESOURCE_RESULT_;
}

bool S2CLessResourcePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CLessResourcePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CLessResourcePacketHandler(&packet);
	return true;
}	

void S2CLessResourcePacketFactory::OnS2CLessResourcePacketHandler(S2CLessResourcePacket* pPacket)
{

}


/************************************************************************/
/*=====================购买不足=================
/************************************************************************/
C2SChioseLessResourcePacket::C2SChioseLessResourcePacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SChioseLessResourcePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LESSRESOURCE_BUY_;
}
unsigned  int  C2SChioseLessResourcePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
bool  C2SChioseLessResourcePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SChioseLessResourcePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

//S2C
S2CChioseLessResourcePacket::S2CChioseLessResourcePacket()
{

}

S2CChioseLessResourcePacket::~S2CChioseLessResourcePacket()
{

}

unsigned  int  S2CChioseLessResourcePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LESSRESOURCE_BUY_RESULT_;
}

unsigned  int  S2CChioseLessResourcePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CChioseLessResourcePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LESSRESOURCEWINDOW_); 
	LessResourceDataHandler::get_instance2()->JumpToVIP();
	
	return true;
}


void  S2CChioseLessResourcePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CChioseLessResourcePacketFactory::S2CChioseLessResourcePacketFactory()
{

}


S2CChioseLessResourcePacketFactory::~S2CChioseLessResourcePacketFactory()
{

}

unsigned  int S2CChioseLessResourcePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_LESSRESOURCE_BUY_RESULT_;
}

bool S2CChioseLessResourcePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CChioseLessResourcePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CChioseLessResourcePacketHandler(&packet);
	return true;
}	

void S2CChioseLessResourcePacketFactory::OnS2CChioseLessResourcePacketHandler(S2CChioseLessResourcePacket* pPacket)
{

}