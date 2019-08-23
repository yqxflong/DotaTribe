// Name :		AskForAddEnergyPacket.h
// Function:	请求增加/购买体力消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/AskForAddEnergyPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/MiningDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SAskForAddEnergyPacket::C2SAskForAddEnergyPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SAskForAddEnergyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ASKFORADDENERGY_;
}

unsigned  int  C2SAskForAddEnergyPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SAskForAddEnergyPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SAskForAddEnergyPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CAskForAddEnergyPacket::S2CAskForAddEnergyPacket()
{

}

S2CAskForAddEnergyPacket::~S2CAskForAddEnergyPacket()
{

}

unsigned  int  S2CAskForAddEnergyPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CAskForAddEnergyPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CAskForAddEnergyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	MININGDATAHANDLER->ToClientHuntBuyMineralResult();

	return true;
}


void  S2CAskForAddEnergyPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CAskForAddEnergyPacketFactory::S2CAskForAddEnergyPacketFactory()
{

}


S2CAskForAddEnergyPacketFactory::~S2CAskForAddEnergyPacketFactory()
{

}

unsigned  int S2CAskForAddEnergyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ASKFORADDENERGY_RESULT_;
}

bool S2CAskForAddEnergyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CAskForAddEnergyPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CAskForAddEnergyPacketHandler(&packet);
	return true;
}	

void S2CAskForAddEnergyPacketFactory::OnS2CAskForAddEnergyPacketHandler(S2CAskForAddEnergyPacket* pPacket)
{

}



/*
	购买体力
*/
C2SBuyEnergyPacket::C2SBuyEnergyPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SBuyEnergyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_BUY_ENERGY_;
}
unsigned  int  C2SBuyEnergyPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
void  C2SBuyEnergyPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}
//S2C
unsigned  int  S2CBuyEnergyPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_BUY_ENERGY_RESULT_;
}
bool  S2CBuyEnergyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	return true;
}
//工厂
unsigned  int S2CBuyEnergyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_BUY_ENERGY_RESULT_;
}
bool S2CBuyEnergyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CBuyEnergyPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CBuyEnergyPacketHandler(&packet);
	return true;
}	





/*
	清除挑战次数
*/
C2SCleanChallengeTimesPacket::C2SCleanChallengeTimesPacket(int mapid,int stageid){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_mapid = mapid;
	m_stageid = stageid;

	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SCleanChallengeTimesPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CLEAR_MAPTIMES_;
}
unsigned  int  C2SCleanChallengeTimesPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_mapid)+sizeof(m_stageid);
}
void  C2SCleanChallengeTimesPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_mapid);
	pNode->push(m_stageid);

	NETSYSTEM->SendPacket(pNode);
}
//S2C
unsigned  int  S2CCleanChallengeTimesPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLEAR_MAPTIMES_RESULT_;
}
bool  S2CCleanChallengeTimesPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接数据
	packet>>m_mapid;
	packet>>m_statesid;
	packet>>m_diamondNum;
	MissionDataHandler::get_instance2()->UpdateCustomDiamond(m_mapid,m_statesid,m_diamondNum); 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_RESET_CHALLENGETIMES_);
	NFC_showCommunicationWating(true);
	return true;
}
//工厂
unsigned  int S2CCleanChallengeTimesPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CLEAR_MAPTIMES_RESULT_;
}
bool S2CCleanChallengeTimesPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CCleanChallengeTimesPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CCleanChallengeTimesPacketHandler(&packet);
	return true;
}	