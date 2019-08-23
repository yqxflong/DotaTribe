// Name :		PersonalChatPacket.h
// Function:	私聊消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/PersonalChatPacket.h"
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


C2SPersonalChatPacket::C2SPersonalChatPacket(std::string name,std::string text){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();

	m_szname =name.length();
	m_name = name;
	m_sztext=text.length();
	m_text = text;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SPersonalChatPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_PERSONALCHAT_;
}

unsigned  int  C2SPersonalChatPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_szname)+m_name.length()+sizeof(m_sztext)+m_text.length();
}
/*
	C->S不需要实现Read函数
*/
bool  C2SPersonalChatPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SPersonalChatPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	pNode->push(m_szname);
	char* pName =const_cast<char*>(m_name.c_str());
	pNode->push(pName,m_szname);

	pNode->push(m_sztext);
	char* pText =const_cast<char*>(m_text.c_str());
	pNode->push(pText,m_sztext);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CPersonalChatPacket::S2CPersonalChatPacket()
{

}

S2CPersonalChatPacket::~S2CPersonalChatPacket()
{

}

unsigned  int  S2CPersonalChatPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CPersonalChatPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CPersonalChatPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	return true;
}


void  S2CPersonalChatPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CPersonalChatPacketFactory::S2CPersonalChatPacketFactory()
{

}


S2CPersonalChatPacketFactory::~S2CPersonalChatPacketFactory()
{

}

unsigned  int S2CPersonalChatPacketFactory::GetPacketType()
{
	return 0;
}

bool S2CPersonalChatPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CPersonalChatPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CPersonalChatPacketHandler(&packet);
	return true;
}	

void S2CPersonalChatPacketFactory::OnS2CPersonalChatPacketHandler(S2CPersonalChatPacket* pPacket)
{

}
