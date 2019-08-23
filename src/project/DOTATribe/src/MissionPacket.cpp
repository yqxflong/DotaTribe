// Name :		MissionPacket.h
// Function:	关卡消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/MissionPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/MissionDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/HomeProcedure.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SMissionPacket::C2SMissionPacket(int serialnum){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SMissionPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MISSION_;
}

unsigned  int  C2SMissionPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SMissionPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SMissionPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CMissionPacket::S2CMissionPacket()
{

}

S2CMissionPacket::~S2CMissionPacket()
{

}

unsigned  int  S2CMissionPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MISSIONRESULT_;
}

unsigned  int  S2CMissionPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CMissionPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial_;
	
	MissionDataHandler::get_instance2()->ResettingMissionInfo();

	return true;
}


void  S2CMissionPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CMissionPacketFactory::S2CMissionPacketFactory()
{

}


S2CMissionPacketFactory::~S2CMissionPacketFactory()
{

}

unsigned  int S2CMissionPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MISSIONRESULT_;
}

bool S2CMissionPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CMissionPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CMissionPacketHandler(&packet);
	return true;
}	

void S2CMissionPacketFactory::OnS2CMissionPacketHandler(S2CMissionPacket* pPacket)
{

}
