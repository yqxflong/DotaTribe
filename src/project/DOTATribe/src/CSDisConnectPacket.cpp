//Name：CSDisConnectPacket
//Function：c->s 请求断开网络
//Written By：lvyunlong

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
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSDisConnectPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_DISCONNECT_CLIENT_;
}

/*
得到数据包长度
*/
unsigned  int  CSDisConnectPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) ;
}

/*
读取字节流
*/
bool  CSDisConnectPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  CSDisConnectPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}