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
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  C2SArenaGifPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_GET_REWARD_CLIENT_;
}

/*
得到数据包长度
*/
unsigned  int  C2SArenaGifPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn);
}

/*
读取字节流
*/
bool  C2SArenaGifPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
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