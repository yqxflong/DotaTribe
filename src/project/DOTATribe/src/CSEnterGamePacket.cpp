//Name��CSEnterGamePacket
//Function��c->s ���������Ϸ
//Written By��lvyunlong

#include <cocos2d.h>
#include "../include/CSEnterGamePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
int m_serial;
unsigned char m_gachaType;
unsigned char m_gachaTarget;
*/

CSEnterGamePacket::CSEnterGamePacket(int id,std::string accountName)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_RoleId = id;
	m_szaccountName = accountName.length();
	m_accountName = accountName;
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  CSEnterGamePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTERGAME_;
}

/*
�õ����ݰ�����
*/
unsigned  int  CSEnterGamePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_RoleId) + sizeof(m_szaccountName) + m_accountName.length();
}

/*
��ȡ�ֽ���
*/
bool  CSEnterGamePacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  CSEnterGamePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_RoleId);
	
	pNode->push(m_szaccountName);
	char* p =const_cast<char*>(m_accountName.c_str());
	pNode->push(p,m_szaccountName);

	NETSYSTEM->SendPacket(pNode);
}