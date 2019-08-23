// Name :		FriendDeletePacket.h
// Function:	删除好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendDeletePacket.h"
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


C2SFriendDeletePacket::C2SFriendDeletePacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendDeletePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDDELETE_;
}

unsigned  int  C2SFriendDeletePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendDeletePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendDeletePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendDeletePacket::S2CFriendDeletePacket()
{

}

S2CFriendDeletePacket::~S2CFriendDeletePacket()
{

}

unsigned  int  S2CFriendDeletePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDDELETE_RESULT_;
}

unsigned  int  S2CFriendDeletePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendDeletePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	packet>>m_id;
	FriendDataHandler::get_instance2()->DeleteFriend(m_id);
	return true;
}


void  S2CFriendDeletePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendDeletePacketFactory::S2CFriendDeletePacketFactory()
{

}


S2CFriendDeletePacketFactory::~S2CFriendDeletePacketFactory()
{

}

unsigned  int S2CFriendDeletePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDDELETE_RESULT_;
}

bool S2CFriendDeletePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendDeletePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendDeletePacketHandler(&packet);
	return true;
}	

void S2CFriendDeletePacketFactory::OnS2CFriendDeletePacketHandler(S2CFriendDeletePacket* pPacket)
{

}
