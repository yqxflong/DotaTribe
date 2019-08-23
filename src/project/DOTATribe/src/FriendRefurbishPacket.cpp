// Name :		FriendRefurbishPacket.h
// Function:	刷新好友窗口消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendRefurbishPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/FriendDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFriendRefurbishPacket::C2SFriendRefurbishPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendRefurbishPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDREFURBISH_;
}

unsigned  int  C2SFriendRefurbishPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendRefurbishPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendRefurbishPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);


	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendRefurbishPacket::S2CFriendRefurbishPacket()
{

}

S2CFriendRefurbishPacket::~S2CFriendRefurbishPacket()
{

}

unsigned  int  S2CFriendRefurbishPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDREFURBISH_RESULT_;
}

unsigned  int  S2CFriendRefurbishPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendRefurbishPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	unsigned short tmp_len=0;
	char *tmpChar=0;

	std::vector<FriendInfoData*>::iterator iter = FriendDataHandler::get_instance2()->NominateList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = FriendDataHandler::get_instance2()->NominateList.end();
	for (;iter!=iter_end;++iter)
	{
		delete *(iter);
	}
	FriendDataHandler::get_instance2()->NominateList.clear();

	packet>>nub;
	for (int i=0;i<nub;i++)
	{
		FriendInfoData* pData = new FriendInfoData();
		packet>>pData->id;

		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		pData->name.assign(tmpChar);
		delete[] tmpChar;tmpChar=0;

		packet>>pData->level;
		packet>>pData->iconId;

		FriendDataHandler::get_instance2()->NominateList.push_back(pData);
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}


void  S2CFriendRefurbishPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendRefurbishPacketFactory::S2CFriendRefurbishPacketFactory()
{

}


S2CFriendRefurbishPacketFactory::~S2CFriendRefurbishPacketFactory()
{

}

unsigned  int S2CFriendRefurbishPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDREFURBISH_RESULT_;
}

bool S2CFriendRefurbishPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendRefurbishPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendRefurbishPacketHandler(&packet);
	return true;
}	

void S2CFriendRefurbishPacketFactory::OnS2CFriendRefurbishPacketHandler(S2CFriendRefurbishPacket* pPacket)
{

}
