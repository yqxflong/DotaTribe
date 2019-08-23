#include <cocos2d.h>
#include "../include/C2SArenaInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CPublicVarReader.h"
#include <include/mem/MemNode.h> 
  #include "../include/NFControlsManager.h"

C2SArenaInfoPacket::C2SArenaInfoPacket(int  serial)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serial;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  C2SArenaInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_INFO_CLINET_;
}

/*
得到数据包长度
*/
unsigned  int  C2SArenaInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len)+ sizeof(m_serial);
}

/*
读取字节流
*/
bool  C2SArenaInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  C2SArenaInfoPacket::Send()
{ 
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);
  
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////


C2SArenaRewardPacket::C2SArenaRewardPacket()
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
unsigned  int  C2SArenaRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_REWARD_CLIENT_;
}

/*
得到数据包长度
*/
unsigned  int  C2SArenaRewardPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

/*
读取字节流
*/
bool  C2SArenaRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  C2SArenaRewardPacket::Send()
{ 
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);  
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////



C2SChallengeCountRewardPacket::C2SChallengeCountRewardPacket(short challengeCount)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_nChallenegeCount=challengeCount;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  C2SChallengeCountRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ARENA_GET_CHALLENGECOUNT_REWARD_;
}

/*
得到数据包长度
*/
unsigned  int  C2SChallengeCountRewardPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len)+sizeof(m_nChallenegeCount);
}

/*
读取字节流
*/
bool  C2SChallengeCountRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  C2SChallengeCountRewardPacket::Send()
{ 
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);  
	pNode->push(m_nChallenegeCount);  
	NETSYSTEM->SendPacket(pNode);
}



