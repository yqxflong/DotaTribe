#include <cocos2d.h>
#include   "../include/C2SResetSkillsPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   <include/mem/MemNode.h>
#include	"../include/EventSystem.h"
#include	"../include/EventTyper.h"



C2SRestRoleSkillsPacket::C2SRestRoleSkillsPacket(unsigned char index)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
	m_SkillIndex = index;
}

unsigned  int  C2SRestRoleSkillsPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RESET_SKILLS_CLIENT_;
}

unsigned  int  C2SRestRoleSkillsPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_SkillIndex);
}

bool  C2SRestRoleSkillsPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SRestRoleSkillsPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_SkillIndex); 

	NETSYSTEM->SendPacket(pNode);
}