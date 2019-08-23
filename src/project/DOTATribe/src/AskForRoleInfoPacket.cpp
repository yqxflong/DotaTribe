// Name :		AskForRoleInfoPacket.h
// Function:	请求人物信息数据包（登录时）
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/AskForRoleInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SAskForRoleInfoPacket::C2SAskForRoleInfoPacket(int serialnum,int playerID,int code){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	m_playerID = playerID;
	m_playerIdentifyingCode = code;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SAskForRoleInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ASKFORROLEINFO_;
}

unsigned  int  C2SAskForRoleInfoPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial)+sizeof(m_playerID)+sizeof(m_playerIdentifyingCode);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SAskForRoleInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SAskForRoleInfoPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CAskForRoleInfoPacket::S2CAskForRoleInfoPacket()
{

}

S2CAskForRoleInfoPacket::~S2CAskForRoleInfoPacket()
{

}

unsigned  int  S2CAskForRoleInfoPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CAskForRoleInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CAskForRoleInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial_;

	//收场景信息


	return true;
}


void  S2CAskForRoleInfoPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CAskForRoleInfoPacketFactory::S2CAskForRoleInfoPacketFactory()
{

}


S2CAskForRoleInfoPacketFactory::~S2CAskForRoleInfoPacketFactory()
{

}

unsigned  int S2CAskForRoleInfoPacketFactory::GetPacketType()
{
	return 0;
}

bool S2CAskForRoleInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CAskForRoleInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CAskForRoleInfoPacketHandler(&packet);
	return true;
}	

void S2CAskForRoleInfoPacketFactory::OnS2CAskForRoleInfoPacketHandler(S2CAskForRoleInfoPacket* pPacket)
{

}
