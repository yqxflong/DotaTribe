// Name :		FriendIgnoreSinglePacket.h
// Function:	忽略单个申请消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendIgnoreSinglePacket.h"
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


C2SFriendIgnoreSinglePacket::C2SFriendIgnoreSinglePacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendIgnoreSinglePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDIGNORESINGLE_;
}

unsigned  int  C2SFriendIgnoreSinglePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendIgnoreSinglePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendIgnoreSinglePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendIgnoreSinglePacket::S2CFriendIgnoreSinglePacket()
{

}

S2CFriendIgnoreSinglePacket::~S2CFriendIgnoreSinglePacket()
{

}

unsigned  int  S2CFriendIgnoreSinglePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDIGNORESINGLE_RESULT_;
}

unsigned  int  S2CFriendIgnoreSinglePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendIgnoreSinglePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>m_id;
	FriendDataHandler::get_instance2()->IgnoreSingle(m_id);
	return true;
}


void  S2CFriendIgnoreSinglePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendIgnoreSinglePacketFactory::S2CFriendIgnoreSinglePacketFactory()
{

}


S2CFriendIgnoreSinglePacketFactory::~S2CFriendIgnoreSinglePacketFactory()
{

}

unsigned  int S2CFriendIgnoreSinglePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDIGNORESINGLE_RESULT_;
}

bool S2CFriendIgnoreSinglePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendIgnoreSinglePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendIgnoreSinglePacketHandler(&packet);
	return true;
}	

void S2CFriendIgnoreSinglePacketFactory::OnS2CFriendIgnoreSinglePacketHandler(S2CFriendIgnoreSinglePacket* pPacket)
{

}
