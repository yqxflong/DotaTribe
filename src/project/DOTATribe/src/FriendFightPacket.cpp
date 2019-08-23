// Name :		FriendFightPacket.h
// Function:	与好友切磋消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendFightPacket.h"
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


C2SFriendFightPacket::C2SFriendFightPacket(int serverid,int playerid){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serverid =serverid;
	m_playerid = playerid;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendFightPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDFIGHE_;
}

unsigned  int  C2SFriendFightPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serverid)+sizeof(m_playerid);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendFightPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendFightPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serverid);
	pNode->push(m_playerid);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendFightPacket::S2CFriendFightPacket()
{

}

S2CFriendFightPacket::~S2CFriendFightPacket()
{

}

unsigned  int  S2CFriendFightPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CFriendFightPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendFightPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	return true;
}


void  S2CFriendFightPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendFightPacketFactory::S2CFriendFightPacketFactory()
{

}


S2CFriendFightPacketFactory::~S2CFriendFightPacketFactory()
{

}

unsigned  int S2CFriendFightPacketFactory::GetPacketType()
{
	return 0;
}

bool S2CFriendFightPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendFightPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendFightPacketHandler(&packet);
	return true;
}	

void S2CFriendFightPacketFactory::OnS2CFriendFightPacketHandler(S2CFriendFightPacket* pPacket)
{

}
