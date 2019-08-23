// Name :		CreateRoleRandomNamePacket.h
// Function:	角色随机姓名消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#include <cocos2d.h>
#include "../include/CreateRoleRandomNamePacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/PacketTyper.h"
#include "../include/IProcedure.h"
#include "../include/NetSystem.h"
#include "../include/IWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/WindowManager.h"
#include "../include/SelectRoleWindow.h"
#include "../include/CreateRoleRandomNameDataHandler.h"
#include "../include/CreateRoleProcedure.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SCreateRoleRandomNamePacket::C2SCreateRoleRandomNamePacket(int serialnum){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SCreateRoleRandomNamePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CREATEROLERANDOMNAME_;
}

unsigned  int  C2SCreateRoleRandomNamePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SCreateRoleRandomNamePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SCreateRoleRandomNamePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CCreateRoleRandomNamePacket::S2CCreateRoleRandomNamePacket()
{

}

S2CCreateRoleRandomNamePacket::~S2CCreateRoleRandomNamePacket()
{

}

unsigned  int  S2CCreateRoleRandomNamePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CREATEROLERANDOMNAMERESULT_;
}

unsigned  int  S2CCreateRoleRandomNamePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CCreateRoleRandomNamePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial_;

	//收场景信息
	char *tmpChar=0;
	unsigned short tmp_len=0;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	m_playerName.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;

	CreateRoleRandomNameDataHandler::get_instance2()->SetPlayerName(m_playerName);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_UI_TEXT_);

	
	return true;
}


void  S2CCreateRoleRandomNamePacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CCreateRoleRandomNamePacketFactory::S2CCreateRoleRandomNamePacketFactory()
{

}


S2CCreateRoleRandomNamePacketFactory::~S2CCreateRoleRandomNamePacketFactory()
{

}

unsigned  int S2CCreateRoleRandomNamePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CREATEROLERANDOMNAMERESULT_;
}

bool S2CCreateRoleRandomNamePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CCreateRoleRandomNamePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CCreateRoleRandomNamePacketHandler(&packet);
	return true;
}	

void S2CCreateRoleRandomNamePacketFactory::OnS2CCreateRoleRandomNamePacketHandler(S2CCreateRoleRandomNamePacket* pPacket)
{

}
