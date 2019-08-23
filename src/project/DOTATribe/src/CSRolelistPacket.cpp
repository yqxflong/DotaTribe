//Name��CSAttestaAccountPacket
//Function��c->s �˺���֤����
//Written By��lvyunlong
#include <cocos2d.h>
#include "../include/CSRolelistPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
*/

CSRolelistPacket::CSRolelistPacket(std::string accountname,int key)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();

	//stringǰ��string�ĳ���
	m_szaccountname=accountname.length();
	m_Straccountname=accountname;
	m_key = key;
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  CSRolelistPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ROLELIST_;
}

/*
�õ����ݰ�����
*/
unsigned  int  CSRolelistPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_key) +sizeof(m_len) + sizeof(m_szaccountname) + m_Straccountname.length();
}

/*
��ȡ�ֽ���
*/
bool  CSRolelistPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  CSRolelistPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	
	pNode->push(m_szaccountname);
	char* p =const_cast<char*>(m_Straccountname.c_str());
	pNode->push(p,m_szaccountname);
	pNode->push(m_key);
	NETSYSTEM->SendPacket(pNode);
}