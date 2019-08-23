// Name :		FriendPacket.h
// Function:	好友消息
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/FriendPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/FriendDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFriendPacket::C2SFriendPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIEND_;
}

unsigned  int  C2SFriendPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);


	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendPacket::S2CFriendPacket()
{

}

S2CFriendPacket::~S2CFriendPacket()
{

}

unsigned  int  S2CFriendPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDA_RESULT_;
}

unsigned  int  S2CFriendPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	
	FriendDataHandler::get_instance2()->onDestroy();
	unsigned short tmp_len=0;
	char *tmpChar=0;
	packet>>FriendDataHandler::get_instance2()->m_MaxFriendNum;
	packet>>FriendDataHandler::get_instance2()->m_FriendNum;
	unsigned short nub = FriendDataHandler::get_instance2()->m_FriendNum;
	//好友
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

		FriendDataHandler::get_instance2()->MyFriendList.push_back(pData);
	}
	packet>>nub;
	for (int i=0;i<nub;i++)
	{
		FriendInfoData* pData = new FriendInfoData();
		packet>>pData->id;
		CCLOG("%d",pData->id);
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		pData->name.assign(tmpChar);
		delete[] tmpChar;tmpChar=0;

		packet>>pData->level;
		packet>>pData->iconId;
		CCLOG("%d",pData->iconId);
		FriendDataHandler::get_instance2()->ApplyList.push_back(pData);
	}
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
	if (DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType() != IProcedure::_TYPED_HOME_PROCEDURE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_FRIENDWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
	}
	else
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_FRIENDWINDOW_);
	}

	return true;
}


void  S2CFriendPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendPacketFactory::S2CFriendPacketFactory()
{

}


S2CFriendPacketFactory::~S2CFriendPacketFactory()
{

}

unsigned  int S2CFriendPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDA_RESULT_;
}

bool S2CFriendPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendPacketHandler(&packet);
	return true;
}	

void S2CFriendPacketFactory::OnS2CFriendPacketHandler(S2CFriendPacket* pPacket)
{

}


//S2C
S2CUpdataFriendPacket::S2CUpdataFriendPacket()
{

}
S2CUpdataFriendPacket::~S2CUpdataFriendPacket()
{

}
unsigned  int  S2CUpdataFriendPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_UPDATAFRIEND_RESULT_;
}
unsigned  int  S2CUpdataFriendPacket::GetPacketLength()
{
	return sizeof(int);
}
bool  S2CUpdataFriendPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ALLFRIEND_);
	return true;
}
void  S2CUpdataFriendPacket::Send(){
	//S->C不需要实现发包
}
//工厂
S2CUpdataFriendPacketFactory::S2CUpdataFriendPacketFactory()
{

}
S2CUpdataFriendPacketFactory::~S2CUpdataFriendPacketFactory()
{

}
unsigned  int S2CUpdataFriendPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_UPDATAFRIEND_RESULT_;
}
bool S2CUpdataFriendPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CUpdataFriendPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CUpdataFriendPacketHandler(&packet);
	return true;
}	
void S2CUpdataFriendPacketFactory::OnS2CUpdataFriendPacketHandler(S2CUpdataFriendPacket* pPacket)
{

}
