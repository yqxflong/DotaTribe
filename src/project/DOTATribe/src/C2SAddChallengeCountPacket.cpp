#include <cocos2d.h>
#include   "../include/C2SAddChallengeCountPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   "../include/EventSystem.h"
#include   "../include/EventTyper.h"
#include   <include/mem/MemNode.h>
#include   <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SAddChallenegeCountPacket::C2SAddChallenegeCountPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SAddChallenegeCountPacket::GetPacketType()
{
	return _TYPEF_PACKET_C2S_ARENA_ADD_CHALLENGECOUNT_CLIENT_;
}

unsigned  int  C2SAddChallenegeCountPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SAddChallenegeCountPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SAddChallenegeCountPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	NETSYSTEM->SendPacket(pNode);
}


 