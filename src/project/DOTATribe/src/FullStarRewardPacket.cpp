// Name :		FullStarRewardPacket.h
// Function:	关卡领取全三星奖励消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FullStarRewardPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/WindowManager.h"
#include "../include/MissionDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFullStarRewardPacket::C2SFullStarRewardPacket(int mapID){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_mapID =mapID;


	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFullStarRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETFULLSTARREWARD_;
}

unsigned  int  C2SFullStarRewardPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_mapID);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFullStarRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFullStarRewardPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_mapID);


	
	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFullStarRewardPacket::S2CFullStarRewardPacket()
{

}

S2CFullStarRewardPacket::~S2CFullStarRewardPacket()
{

}

unsigned  int  S2CFullStarRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETFULLSTARREWARDRESULT_;
}

unsigned  int  S2CFullStarRewardPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFullStarRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//收信息
	packet>>m_mapID;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_REWARDBOX_);

	return true;
}


void  S2CFullStarRewardPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFullStarRewardPacketFactory::S2CFullStarRewardPacketFactory()
{

}


S2CFullStarRewardPacketFactory::~S2CFullStarRewardPacketFactory()
{

}

unsigned  int S2CFullStarRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETFULLSTARREWARDRESULT_;
}

bool S2CFullStarRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFullStarRewardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFullStarRewardPacketHandler(&packet);
	return true;
}	

void S2CFullStarRewardPacketFactory::OnS2CFullStarRewardPacketHandler(S2CFullStarRewardPacket* pPacket)
{

}
