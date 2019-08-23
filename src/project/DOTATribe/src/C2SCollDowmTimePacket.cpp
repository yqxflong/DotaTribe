
#include <cocos2d.h>
#include   "../include/C2SCollDowmTimePacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>
#include   <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SCollTimePacket::C2SCollTimePacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SCollTimePacket::GetPacketType()
{
	return _TYPEF_PACKET_C2S_ARENA_CLEAR_COLLDOWNTIME_CLIENT_;
}

unsigned  int  C2SCollTimePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SCollTimePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SCollTimePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	NETSYSTEM->SendPacket(pNode);
}


 