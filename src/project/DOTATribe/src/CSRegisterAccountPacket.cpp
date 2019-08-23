//Name：CSRegisterAccountPacket
//Function：c->s 请求账号注册
//Written By：lvyunlong
#include <cocos2d.h>
#include "../include/CSRegisterAccountPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
*/

CSRegisterAccountPacket::CSRegisterAccountPacket(std::string accountname,std::string password)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();


	//string前加string的长度
	m_szaccountname=accountname.length();
	m_Straccountname=accountname;

	m_szpassword=password.length();
	m_Strpassword=password;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSRegisterAccountPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACCOUNT_REGISTER_;
}

/*
得到数据包长度
*/
unsigned  int  CSRegisterAccountPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_szaccountname) + sizeof(m_szpassword) + m_Straccountname.length() + m_Strpassword.length();
}

/*
读取字节流
*/
bool  CSRegisterAccountPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  CSRegisterAccountPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_szaccountname);
	char* p =const_cast<char*>(m_Straccountname.c_str());
	pNode->push(p,m_szaccountname);
	pNode->push(m_szpassword);
	p =const_cast<char*>(m_Strpassword.c_str());
	pNode->push(p,m_szpassword);
	NETSYSTEM->SendPacket(pNode);
}