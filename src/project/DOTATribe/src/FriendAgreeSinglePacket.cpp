// Name :		FriendAgreeSinglePacket.h
// Function:	同意单个好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#include <cocos2d.h>
#include "../include/FriendAgreeSinglePacket.h"
#include "../include/FriendDataHandler.h"
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


C2SFriendAgreeSinglePacket::C2SFriendAgreeSinglePacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendAgreeSinglePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDAGREESINGLE_;
}

unsigned  int  C2SFriendAgreeSinglePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendAgreeSinglePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendAgreeSinglePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendAgreeSinglePacket::S2CFriendAgreeSinglePacket()
{
}

S2CFriendAgreeSinglePacket::~S2CFriendAgreeSinglePacket()
{

}

unsigned  int  S2CFriendAgreeSinglePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDAGREESINGLE_RESULT_;
}

unsigned  int  S2CFriendAgreeSinglePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendAgreeSinglePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>m_id;
	FriendDataHandler::get_instance2()->AgreeSingle(m_id);
	return true;
}


void  S2CFriendAgreeSinglePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendAgreeSinglePacketFactory::S2CFriendAgreeSinglePacketFactory()
{

}


S2CFriendAgreeSinglePacketFactory::~S2CFriendAgreeSinglePacketFactory()
{

}

unsigned  int S2CFriendAgreeSinglePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDAGREESINGLE_RESULT_;
}

bool S2CFriendAgreeSinglePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendAgreeSinglePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendAgreeSinglePacketHandler(&packet);
	return true;
}	

void S2CFriendAgreeSinglePacketFactory::OnS2CFriendAgreeSinglePacketHandler(S2CFriendAgreeSinglePacket* pPacket)
{

}
