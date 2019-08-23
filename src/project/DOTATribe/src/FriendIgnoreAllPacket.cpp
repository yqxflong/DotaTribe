// Name :		FriendIgnoreAllPacket.h
// Function:	忽略所有申请消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendIgnoreAllPacket.h"
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


C2SFriendIgnoreAllPacket::C2SFriendIgnoreAllPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendIgnoreAllPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDIGNOREALL_;
}

unsigned  int  C2SFriendIgnoreAllPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendIgnoreAllPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendIgnoreAllPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);


	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendIgnoreAllPacket::S2CFriendIgnoreAllPacket()
{

}

S2CFriendIgnoreAllPacket::~S2CFriendIgnoreAllPacket()
{

}

unsigned  int  S2CFriendIgnoreAllPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDIGNOREALL_RESULT_;
}

unsigned  int  S2CFriendIgnoreAllPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendIgnoreAllPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>m_result;
	if (m_result == 0)
		FriendDataHandler::get_instance2()->IgnoreAll();
	return true;
}


void  S2CFriendIgnoreAllPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendIgnoreAllPacketFactory::S2CFriendIgnoreAllPacketFactory()
{

}


S2CFriendIgnoreAllPacketFactory::~S2CFriendIgnoreAllPacketFactory()
{

}

unsigned  int S2CFriendIgnoreAllPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDIGNOREALL_RESULT_;
}

bool S2CFriendIgnoreAllPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendIgnoreAllPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendIgnoreAllPacketHandler(&packet);
	return true;
}	

void S2CFriendIgnoreAllPacketFactory::OnS2CFriendIgnoreAllPacketHandler(S2CFriendIgnoreAllPacket* pPacket)
{

}
