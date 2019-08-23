// Name :		FriendAddPacket.h
// Function:	���Ӻ�����Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#include <cocos2d.h>
#include "../include/FriendAddPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/MiningDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SFriendAddPacket::C2SFriendAddPacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id=id;
	//����ȡ����
	m_len=GetPacketLength();
};

unsigned  int  C2SFriendAddPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FRIENDADD_;
}

unsigned  int  C2SFriendAddPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
/*
	C->S����Ҫʵ��Read����
*/
bool  C2SFriendAddPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SFriendAddPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CFriendAddPacket::S2CFriendAddPacket()
{

}

S2CFriendAddPacket::~S2CFriendAddPacket()
{

}

unsigned  int  S2CFriendAddPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDADD_RESULT_;
}

unsigned  int  S2CFriendAddPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CFriendAddPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//��
	return true;
}


void  S2CFriendAddPacket::Send(){
	//S->C����Ҫʵ�ַ���
}

//����
S2CFriendAddPacketFactory::S2CFriendAddPacketFactory()
{

}


S2CFriendAddPacketFactory::~S2CFriendAddPacketFactory()
{

}

unsigned  int S2CFriendAddPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FRIENDADD_RESULT_;
}

bool S2CFriendAddPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CFriendAddPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CFriendAddPacketHandler(&packet);
	return true;
}	

void S2CFriendAddPacketFactory::OnS2CFriendAddPacketHandler(S2CFriendAddPacket* pPacket)
{
	//���ٻص����ɿ�ļӺ�����
	//MININGDATAHANDLER->ToClientAskFriendResult();
}
