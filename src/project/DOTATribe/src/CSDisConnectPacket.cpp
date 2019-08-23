//Name��CSDisConnectPacket
//Function��c->s ����Ͽ�����
//Written By��lvyunlong

#include <cocos2d.h>
#include "../include/CSDisConnectPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

CSDisConnectPacket::CSDisConnectPacket()
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
unsigned  int  CSDisConnectPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_DISCONNECT_CLIENT_;
}

/*
�õ����ݰ�����
*/
unsigned  int  CSDisConnectPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) ;
}

/*
��ȡ�ֽ���
*/
bool  CSDisConnectPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  CSDisConnectPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}