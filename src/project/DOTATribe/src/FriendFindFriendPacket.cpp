// Name :		FriendFindFriendPacket.h
// Function:	查找好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendFindFriendPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/FriendDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFriendFindFriendPacket::C2SFriendFindFriendPacket(std::string name){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();

 	m_szname =name.length();
	m_name = name;

	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendFindFriendPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDFRINDFRIEND_;
}

unsigned  int  C2SFriendFindFriendPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_szname)+m_name.length();
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendFindFriendPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendFindFriendPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_szname);
	char* pName =const_cast<char*>(m_name.c_str());
	pNode->push(pName,m_szname);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendFindFriendPacket::S2CFriendFindFriendPacket()
{

}

S2CFriendFindFriendPacket::~S2CFriendFindFriendPacket()
{

}

unsigned  int  S2CFriendFindFriendPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDFRINDFRIEND_RESULT_;
}

unsigned  int  S2CFriendFindFriendPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendFindFriendPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	unsigned short tmp_len=0;
	char *tmpChar=0;

	packet>>FriendDataHandler::get_instance2()->m_FindPlayer.id;


	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	FriendDataHandler::get_instance2()->m_FindPlayer.name.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;


	packet>>FriendDataHandler::get_instance2()->m_FindPlayer.level;
	packet>>FriendDataHandler::get_instance2()->m_FindPlayer.iconId;
	FriendDataHandler::get_instance2()->m_IsFindPlayer = true;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FINDFRIENDWINDOW_);
	return true;
}


void  S2CFriendFindFriendPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendFindFriendPacketFactory::S2CFriendFindFriendPacketFactory()
{

}


S2CFriendFindFriendPacketFactory::~S2CFriendFindFriendPacketFactory()
{

}

unsigned  int S2CFriendFindFriendPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDFRINDFRIEND_RESULT_;
}

bool S2CFriendFindFriendPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendFindFriendPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendFindFriendPacketHandler(&packet);
	return true;
}	

void S2CFriendFindFriendPacketFactory::OnS2CFriendFindFriendPacketHandler(S2CFriendFindFriendPacket* pPacket)
{

}
