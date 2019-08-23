//Name��CSQuickRegisterPacket
//Function��c->s �������ע��
//Written By��lvyunlong
#include <cocos2d.h>
#include "../include/CSQuickAccountRegisterPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
*/

CSQuickAccountRegisterPacket::CSQuickAccountRegisterPacket(std::string deviceId)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();


	//stringǰ��string�ĳ���

	m_szdeviceId=deviceId.length();
	m_StrdeviceId=deviceId;
	//����ȡ����
	m_len=GetPacketLength();
}

/*
�õ����ݰ�����
*/
unsigned  int  CSQuickAccountRegisterPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FAST_REGISTER_CLIENT_;
}

/*
�õ����ݰ�����
*/
unsigned  int  CSQuickAccountRegisterPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_szdeviceId) + m_StrdeviceId.length();
}

/*
��ȡ�ֽ���
*/
bool  CSQuickAccountRegisterPacket::Read(char* pBuffer, unsigned int iLen)
{
	//���ӷ�������ȡ
	return true;
}

/*
�����ֽ���
*/
void  CSQuickAccountRegisterPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_szdeviceId);
	char* p =const_cast<char*>(m_StrdeviceId.c_str());
	pNode->push(p,m_szdeviceId);

	NETSYSTEM->SendPacket(pNode);
}