
#include <cocos2d.h>
#include  "../include/C2SChallengePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CPublicVarReader.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"
#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SChallengePacket::C2SChallengePacket(int targetID){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=ROLEINFODATAHANDLER->updateRoleAthleticsSerialID();
	m_targetID=targetID;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SChallengePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_CHALLENGE_CLIENT_;
}

unsigned  int  C2SChallengePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial)+sizeof(m_targetID);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SChallengePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SChallengePacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);
	pNode->push(m_targetID);
 	
	NETSYSTEM->SendPacket(pNode);
}


 