#include <cocos2d.h>
#include "../include/C2SArenaGifPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NFControlsManager.h"
  
C2SArenaGifPacket::C2SArenaGifPacket()
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  C2SArenaGifPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_GET_REWARD_CLIENT_;
}

/*
�õ����ݰ�����
*/
unsigned  int  C2SArenaGifPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn);
}

/*
��ȡ�ֽ���
*/
bool  C2SArenaGifPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  C2SArenaGifPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 

	NETSYSTEM->SendPacket(pNode);
}