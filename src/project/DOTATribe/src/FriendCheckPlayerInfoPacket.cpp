// Name :		FriendCheckPlayerInfoPacket.h
// Function:	查看好友信息消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/FriendCheckPlayerInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/FriendDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFriendCheckPlayerInfoPacket::C2SFriendCheckPlayerInfoPacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendCheckPlayerInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDCHECKPLAYERINFO_;
}

unsigned  int  C2SFriendCheckPlayerInfoPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SFriendCheckPlayerInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendCheckPlayerInfoPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendCheckPlayerInfoPacket::S2CFriendCheckPlayerInfoPacket()
{

}

S2CFriendCheckPlayerInfoPacket::~S2CFriendCheckPlayerInfoPacket()
{

}

unsigned  int  S2CFriendCheckPlayerInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDCHECKPLAYERINFO_RESULT_;
}

unsigned  int  S2CFriendCheckPlayerInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendCheckPlayerInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//接
	unsigned short tmp_len=0;
	char *tmpChar=0;

	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.id;

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	FriendDataHandler::get_instance2()->m_SelectPlayerInfo.name.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;

	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.level;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.shapeId;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.hp;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.mp;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.minAttack;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.maxAttack;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.speed;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.hit;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.dodge;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.exposeArmor;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.armor;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.cirt;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.uncirt;
	packet>>FriendDataHandler::get_instance2()->m_SelectPlayerInfo.btlCapa;
	//显示查看信息


	NFC_showCommunicationWating(false);
	return true;
}


void  S2CFriendCheckPlayerInfoPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CFriendCheckPlayerInfoPacketFactory::S2CFriendCheckPlayerInfoPacketFactory()
{

}


S2CFriendCheckPlayerInfoPacketFactory::~S2CFriendCheckPlayerInfoPacketFactory()
{

}

unsigned  int S2CFriendCheckPlayerInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDCHECKPLAYERINFO_RESULT_;
}

bool S2CFriendCheckPlayerInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendCheckPlayerInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendCheckPlayerInfoPacketHandler(&packet);
	return true;
}	

void S2CFriendCheckPlayerInfoPacketFactory::OnS2CFriendCheckPlayerInfoPacketHandler(S2CFriendCheckPlayerInfoPacket* pPacket)
{
	NFC_showCommunicationWating(false);

	if(FriendDataHandler::get_instance2()->m_iShowedTipsWindow > 0)
	{
		if(WINDOWMANAGER->IsWindowVisible(FriendDataHandler::get_instance2()->m_iShowedTipsWindow))
		{
			EVENTSYSTEM->PushEvent(_TYPEF_EVENT_SHOW_PLAYERTIPSWINDOW_);
		}
	}
	FriendDataHandler::get_instance2()->m_iShowedTipsWindow = -1;
}
