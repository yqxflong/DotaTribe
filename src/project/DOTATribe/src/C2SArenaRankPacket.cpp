#ifndef  _DOTATRIBE_C2SARENARANKPACKET_H_
#define  _DOTATRIBE_C2SARENARANKPACKET_H_
 
#include <cocos2d.h>
#include "../include/C2SArenaRankPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NFControlsManager.h"


C2SArenaRankPacket::C2SArenaRankPacket(int  serial)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serial;
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  C2SArenaRankPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_RANK_INFO_CLIENT_;
}

/*
�õ����ݰ�����
*/
unsigned  int  C2SArenaRankPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_serial);
}

/*
��ȡ�ֽ���
*/
bool  C2SArenaRankPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  C2SArenaRankPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	NETSYSTEM->SendPacket(pNode);
}

#endif