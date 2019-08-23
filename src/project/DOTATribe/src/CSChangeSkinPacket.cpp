//Name��CSChangeSkinPacket
//Function��c->s ��������
//Written By����ǿ
#include <cocos2d.h>
#include "../include/CSChangeSkinPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

#include <stdlib.h>
#include <iostream>
using namespace std;
using  namespace  cobra_win;


CSChangeSkinPacket::CSChangeSkinPacket(int serial,int skinID){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serial;
	m_skinID=skinID;
	//����ȡ����
	m_len=GetPacketLength();
};

unsigned  int  CSChangeSkinPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHANGESKIN_;
}

unsigned  int  CSChangeSkinPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial)+sizeof(m_skinID);
}
/*
	C->S����Ҫʵ��Read����
*/
bool  CSChangeSkinPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSChangeSkinPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);
	pNode->push(m_skinID);

	NETSYSTEM->SendPacket(pNode);
}