#include <cocos2d.h>
#include "../include/CheckOpenFun.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServerInfoDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;

C2SCheckOpenFunPacket::C2SCheckOpenFunPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SCheckOpenFunPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHECK_OPEN_FUNCTION_; 
}

unsigned  int  C2SCheckOpenFunPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SCheckOpenFunPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SCheckOpenFunPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CCheckOpenFunPacket::S2CCheckOpenFunPacket()
{

}

S2CCheckOpenFunPacket::~S2CCheckOpenFunPacket()
{

}

unsigned  int  S2CCheckOpenFunPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_OPEN_FUNCTION_; 
}

unsigned  int  S2CCheckOpenFunPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CCheckOpenFunPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	ServerInfoDataHandler::get_instance2()->decodePacketData_CheckOpenFunction(packet);

	return true;
}


void  S2CCheckOpenFunPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CCheckOpenFunPacketFactory::S2CCheckOpenFunPacketFactory()
{

}


S2CCheckOpenFunPacketFactory::~S2CCheckOpenFunPacketFactory()
{

}

unsigned  int S2CCheckOpenFunPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_OPEN_FUNCTION_;
}

bool S2CCheckOpenFunPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CCheckOpenFunPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CCheckOpenFunPacketHandler(&packet);
	return true;
}	

void S2CCheckOpenFunPacketFactory::OnS2CCheckOpenFunPacketHandler(S2CCheckOpenFunPacket* pPacket)
{
	NFC_showCommunicationWating(false);
}
