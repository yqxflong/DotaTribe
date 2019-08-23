//Name：CSAttestaAccountPacket
//Function：c->s 账号认证请求
//Written By：lvyunlong
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

	//string前加string的长度
	m_szaccountname=accountname.length();
	m_Straccountname=accountname;
	m_key = key;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSRolelistPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ROLELIST_;
}

/*
得到数据包长度
*/
unsigned  int  CSRolelistPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_key) +sizeof(m_len) + sizeof(m_szaccountname) + m_Straccountname.length();
}

/*
读取字节流
*/
bool  CSRolelistPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
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