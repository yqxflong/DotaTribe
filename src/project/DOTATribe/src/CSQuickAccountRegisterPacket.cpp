//Name：CSQuickRegisterPacket
//Function：c->s 请求快速注册
//Written By：lvyunlong
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


	//string前加string的长度

	m_szdeviceId=deviceId.length();
	m_StrdeviceId=deviceId;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSQuickAccountRegisterPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FAST_REGISTER_CLIENT_;
}

/*
得到数据包长度
*/
unsigned  int  CSQuickAccountRegisterPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_szdeviceId) + m_StrdeviceId.length();
}

/*
读取字节流
*/
bool  CSQuickAccountRegisterPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
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