// Name :		FriendAgreeAllPacket.h
// Function:	全部同意好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#include <cocos2d.h>
#include "../include/FriendAgreeAllPacket.h"
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


C2SFriendAgreeAllPacket::C2SFriendAgreeAllPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendAgreeAllPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDAGREEALL_;
}

unsigned  int  C2SFriendAgreeAllPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendAgreeAllPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendAgreeAllPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);


	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendAgreeAllPacket::S2CFriendAgreeAllPacket()
{

}

S2CFriendAgreeAllPacket::~S2CFriendAgreeAllPacket()
{

}

unsigned  int  S2CFriendAgreeAllPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDAGREEALL_RESULT_;
}

unsigned  int  S2CFriendAgreeAllPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendAgreeAllPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>m_result;
	if (m_result == 0)
		FriendDataHandler::get_instance2()->AgreeAll();
	return true;
}


void  S2CFriendAgreeAllPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendAgreeAllPacketFactory::S2CFriendAgreeAllPacketFactory()
{

}


S2CFriendAgreeAllPacketFactory::~S2CFriendAgreeAllPacketFactory()
{

}

unsigned  int S2CFriendAgreeAllPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDAGREEALL_RESULT_;
}

bool S2CFriendAgreeAllPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendAgreeAllPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendAgreeAllPacketHandler(&packet);
	return true;
}	

void S2CFriendAgreeAllPacketFactory::OnS2CFriendAgreeAllPacketHandler(S2CFriendAgreeAllPacket* pPacket)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ALLFRIEND_);
}
