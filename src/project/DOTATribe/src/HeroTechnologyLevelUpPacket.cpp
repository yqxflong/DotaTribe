// Name :		HeroTechnologyLevelUpPacket.h
// Function:	信仰升级消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/HeroTechnologyLevelUpPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/HeroTechnologyDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SHeroTechnologyLevelUpPacket::C2SHeroTechnologyLevelUpPacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id =id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SHeroTechnologyLevelUpPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROTECHNOLOGYLEVELUP_;
}

unsigned  int  C2SHeroTechnologyLevelUpPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SHeroTechnologyLevelUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SHeroTechnologyLevelUpPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);
	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CHeroTechnologyLevelUpPacket::S2CHeroTechnologyLevelUpPacket()
{

}

S2CHeroTechnologyLevelUpPacket::~S2CHeroTechnologyLevelUpPacket()
{

}

unsigned  int  S2CHeroTechnologyLevelUpPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTECHNOLOGYLEVELUPRESULT_;
}

unsigned  int  S2CHeroTechnologyLevelUpPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CHeroTechnologyLevelUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);

	
	packet>>m_len;
	packet>>m_pn;

	unsigned short tmp_len=0;
	char *tmpChar=0;

	////收场景信息
	packet>>HeroTechnologyDataHandler::get_instance2()->score;
	packet>>HeroTechnologyDataHandler::get_instance2()->maxLevel;
	packet>>HeroTechnologyDataHandler::get_instance2()->TechnologyID;
	HeroTechnology *pData =HeroTechnologyDataHandler::get_instance2()->GetTechnologyByID(HeroTechnologyDataHandler::get_instance2()->TechnologyID);
	
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	pData->name.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;

	packet>>pData->icon;
	packet>>pData->costPoints;;
	packet>>pData->level;
	packet>>pData->attriType;
	packet>>pData->addValue;
	packet>>pData->nextLevelAddValue;


	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_CONVICTIONWINDOW_);
	return true;
}


void  S2CHeroTechnologyLevelUpPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CHeroTechnologyLevelUpPacketFactory::S2CHeroTechnologyLevelUpPacketFactory()
{

}


S2CHeroTechnologyLevelUpPacketFactory::~S2CHeroTechnologyLevelUpPacketFactory()
{

}

unsigned  int S2CHeroTechnologyLevelUpPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTECHNOLOGYLEVELUPRESULT_;
}

bool S2CHeroTechnologyLevelUpPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CHeroTechnologyLevelUpPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CHeroTechnologyLevelUpPacketHandler(&packet);
	return true;
}	

void S2CHeroTechnologyLevelUpPacketFactory::OnS2CHeroTechnologyLevelUpPacketHandler(S2CHeroTechnologyLevelUpPacket* pPacket)
{

}
