// Name :		CostRevenuePacket.h
// Function:	点金消耗消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/CostRevenuePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SCostRevenuePacket::C2SCostRevenuePacket(int type,int countType){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_type = type;
	m_countType = countType;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SCostRevenuePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_COSTREVENUE_;
}

unsigned  int  C2SCostRevenuePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_type)+sizeof(m_countType);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SCostRevenuePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SCostRevenuePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_type);
	pNode->push(m_countType);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CCostRevenuePacket::S2CCostRevenuePacket()
{

}

S2CCostRevenuePacket::~S2CCostRevenuePacket()
{

}

unsigned  int  S2CCostRevenuePacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CCostRevenuePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CCostRevenuePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_type;
	packet>>m_countType;
	return true;
}


void  S2CCostRevenuePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CCostRevenuePacketFactory::S2CCostRevenuePacketFactory()
{

}


S2CCostRevenuePacketFactory::~S2CCostRevenuePacketFactory()
{

}

unsigned  int S2CCostRevenuePacketFactory::GetPacketType()
{
	return 0;
}

bool S2CCostRevenuePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CCostRevenuePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CCostRevenuePacketHandler(&packet);
	return true;
}	

void S2CCostRevenuePacketFactory::OnS2CCostRevenuePacketHandler(S2CCostRevenuePacket* pPacket)
{

}
