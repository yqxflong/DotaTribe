// Name :		CheckPlayerInfoPacket.h
// Function:	查看好友信息消息包
// Author :		邵兵	
// Maintainer:  邵兵 

#include <cocos2d.h>
#include "../include/CheckPlayerInfoPacket.h"
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


C2SCheckPlayerInfoPacket::C2SCheckPlayerInfoPacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SCheckPlayerInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHECK_PLAYER_INFO_CLIENT; 
}

unsigned  int  C2SCheckPlayerInfoPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SCheckPlayerInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SCheckPlayerInfoPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CCheckPlayerInfoPacket::S2CCheckPlayerInfoPacket()
{

}

S2CCheckPlayerInfoPacket::~S2CCheckPlayerInfoPacket()
{

}

unsigned  int  S2CCheckPlayerInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_PLAYER_INFO_CLIENT; 
}

unsigned  int  S2CCheckPlayerInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CCheckPlayerInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	LOGGERSYSTEM->LogDebug("Start Receive CheckPlayerInfo");
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	FriendDataHandler::get_instance2()->decodeCheckPlayerDataPacket(packet);
	//接

	/*
#if 1
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
#endif
	*/


	NFC_showCommunicationWating(false);
	return true;
}


void  S2CCheckPlayerInfoPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CCheckPlayerInfoPacketFactory::S2CCheckPlayerInfoPacketFactory()
{

}


S2CCheckPlayerInfoPacketFactory::~S2CCheckPlayerInfoPacketFactory()
{

}

unsigned  int S2CCheckPlayerInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_PLAYER_INFO_CLIENT;
}

bool S2CCheckPlayerInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CCheckPlayerInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CCheckPlayerInfoPacketHandler(&packet);
	return true;
}	

void S2CCheckPlayerInfoPacketFactory::OnS2CCheckPlayerInfoPacketHandler(S2CCheckPlayerInfoPacket* pPacket)
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
