// Name :		HeroTechnologyPacket.h
// Function:	信仰消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/HeroTechnologyPacket.h"
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


C2SHeroTechnologyPacket::C2SHeroTechnologyPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SHeroTechnologyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROTECHNOLOGY_;
}

unsigned  int  C2SHeroTechnologyPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SHeroTechnologyPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SHeroTechnologyPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CHeroTechnologyPacket::S2CHeroTechnologyPacket()
{
	IsNeedChangeScene = -1;
}

S2CHeroTechnologyPacket::~S2CHeroTechnologyPacket()
{

}

unsigned  int  S2CHeroTechnologyPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTECHNOLOGYRESULT_;
}

unsigned  int  S2CHeroTechnologyPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CHeroTechnologyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	unsigned short tmp_len=0;
	char *tmpChar=0;

	////收场景信息
	packet>>IsNeedChangeScene;
	packet>>HeroTechnologyDataHandler::get_instance2()->score;
	packet>>HeroTechnologyDataHandler::get_instance2()->maxLevel;
	packet>>HeroTechnologyDataHandler::get_instance2()->count;
	for (int i=0;i<HeroTechnologyDataHandler::get_instance2()->count;i++)
	{
		HeroTechnology *pData;
		
		if ((int)HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList.size()> i && HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[i]!= NULL)
			pData = HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[i];
		else
			pData= new HeroTechnology();
		packet>>pData->id;

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

		if ((int)HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList.size() <= i || HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList[i] == NULL)
			HeroTechnologyDataHandler::get_instance2()->HeroTechnologyList.push_back(pData);

	}
	//if (HeroTechnologyDataHandler::get_instance2()->m_HideWindow == 0)	
	//	EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	//else
	//	EVENTSYSTEM->PushEvent(HeroTechnologyDataHandler::get_instance2()->m_HideWindow);
	//NFC_showCommunicationWating(false);	
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_CONVICTIONWINDOW_);	
	return true;
}


void  S2CHeroTechnologyPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CHeroTechnologyPacketFactory::S2CHeroTechnologyPacketFactory()
{

}


S2CHeroTechnologyPacketFactory::~S2CHeroTechnologyPacketFactory()
{

}

unsigned  int S2CHeroTechnologyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTECHNOLOGYRESULT_;
}

bool S2CHeroTechnologyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CHeroTechnologyPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CHeroTechnologyPacketHandler(&packet);
	return true;
}	

void S2CHeroTechnologyPacketFactory::OnS2CHeroTechnologyPacketHandler(S2CHeroTechnologyPacket* pPacket)
{

}


//ADDdTechnologyPoint
C2SAddTechnologyPointPacket::C2SAddTechnologyPointPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SAddTechnologyPointPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ADDTECHNOLOGYPOINT_;
}

unsigned  int  C2SAddTechnologyPointPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SAddTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SAddTechnologyPointPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CAddTechnologyPointPacket::S2CAddTechnologyPointPacket()
{
	IsNeedChangeScene = -1;
}

S2CAddTechnologyPointPacket::~S2CAddTechnologyPointPacket()
{

}

unsigned  int  S2CAddTechnologyPointPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CAddTechnologyPointPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CAddTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	return true;
}


void  S2CAddTechnologyPointPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CAddTechnologyPointPacketFactory::S2CAddTechnologyPointPacketFactory()
{

}


S2CAddTechnologyPointPacketFactory::~S2CAddTechnologyPointPacketFactory()
{

}

unsigned  int S2CAddTechnologyPointPacketFactory::GetPacketType()
{
	return 0;
}

bool S2CAddTechnologyPointPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CAddTechnologyPointPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CAddTechnologyPointPacketHandler(&packet);
	return true;
}	

void S2CAddTechnologyPointPacketFactory::OnS2CAddTechnologyPointPacketHandler(S2CAddTechnologyPointPacket* pPacket)
{

}



//GetdTechnologyPoint
C2SGetTechnologyPointPacket::C2SGetTechnologyPointPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SGetTechnologyPointPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_GETTECHNOLOGYPOINT_;
}

unsigned  int  C2SGetTechnologyPointPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SGetTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SGetTechnologyPointPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CGetTechnologyPointPacket::S2CGetTechnologyPointPacket()
{
	IsNeedChangeScene = -1;
}

S2CGetTechnologyPointPacket::~S2CGetTechnologyPointPacket()
{

}

unsigned  int  S2CGetTechnologyPointPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETTECHNOLOGYPOINT_RESULT;
}

unsigned  int  S2CGetTechnologyPointPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CGetTechnologyPointPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//
	packet>>HeroTechnologyDataHandler::get_instance2()->m_free_pray_times;
	packet>>HeroTechnologyDataHandler::get_instance2()->m_pray_cost;
	packet>>HeroTechnologyDataHandler::get_instance2()->score;

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_PRAY_COST);
	return true;
}


void  S2CGetTechnologyPointPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CGetTechnologyPointPacketFactory::S2CGetTechnologyPointPacketFactory()
{

}


S2CGetTechnologyPointPacketFactory::~S2CGetTechnologyPointPacketFactory()
{

}

unsigned  int S2CGetTechnologyPointPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETTECHNOLOGYPOINT_RESULT;
}

bool S2CGetTechnologyPointPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CGetTechnologyPointPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CGetTechnologyPointPacketHandler(&packet);
	return true;
}	

void S2CGetTechnologyPointPacketFactory::OnS2CGetTechnologyPointPacketHandler(S2CGetTechnologyPointPacket* pPacket)
{

}