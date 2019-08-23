//Name��CSBagUseObjectPacket
//Function��c->s ʹ����Ʒ
//Author : ����
//date : 2013-8-7

#include <cocos2d.h>
#include "../include/CSBagUseObjectPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
int m_serial;
int m_skinID;
int num;*/

CSBagUseObjectPacket::CSBagUseObjectPacket(int serial,int itemId, int itemTemplateId, int count)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serial;
	m_itemId = itemId;
	m_itemTemplateId = itemTemplateId;
	m_count = count;
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  CSBagUseObjectPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_USEOBJECT_;
}

/*
�õ����ݰ�����
*/
unsigned  int  CSBagUseObjectPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_serial) + sizeof(m_itemId) + sizeof(m_itemTemplateId) + sizeof(m_count) + sizeof(m_len);
}

/*
��ȡ�ֽ���
*/
bool  CSBagUseObjectPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  CSBagUseObjectPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);
	pNode->push(m_itemId);
	pNode->push(m_itemTemplateId);
	pNode->push(m_count);
	NETSYSTEM->SendPacket(pNode);

}

