//Name：CSChangeSkinPacket
//Function：c->s 更换外套
//Written By：尹强
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
	//最后获取长度
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
	C->S不需要实现Read函数
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