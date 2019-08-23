// Name :		RestingTechnologyPointPacket.h
// Function:	重置信仰点数消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/RestingTechnologyPointPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/HeroTechnologyPacket.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SRestingTechnologyPointPacket::C2SRestingTechnologyPointPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();

	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SRestingTechnologyPointPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RESTINGTECHNOLOGYPOINT_;
}

unsigned  int  C2SRestingTechnologyPointPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SRestingTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SRestingTechnologyPointPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CRestingTechnologyPointPacket::S2CRestingTechnologyPointPacket()
{

}

S2CRestingTechnologyPointPacket::~S2CRestingTechnologyPointPacket()
{

}

unsigned  int  S2CRestingTechnologyPointPacket::GetPacketType()
{
	return _TYPED_PACEKT_S2C_RESTINGTECHNOLOGYPOINT_RESULT_;
}

unsigned  int  S2CRestingTechnologyPointPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CRestingTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	
	C2SHeroTechnologyPacket crpacket;
	crpacket.Send();
	NFC_showCommunicationWating(true);
	return true;
}


void  S2CRestingTechnologyPointPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CRestingTechnologyPointPacketFactory::S2CRestingTechnologyPointPacketFactory()
{

}


S2CRestingTechnologyPointPacketFactory::~S2CRestingTechnologyPointPacketFactory()
{

}

unsigned  int S2CRestingTechnologyPointPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_RESTINGTECHNOLOGYPOINT_RESULT_;
}

bool S2CRestingTechnologyPointPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CRestingTechnologyPointPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CRestingTechnologyPointPacketHandler(&packet);
	return true;
}	

void S2CRestingTechnologyPointPacketFactory::OnS2CRestingTechnologyPointPacketHandler(S2CRestingTechnologyPointPacket* pPacket)
{

}
