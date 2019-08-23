#include <cocos2d.h>
#include   "../include/C2SBattleRecordPacket.h"
#include   "../include/RoleInfoDataHandler.h"
#include   "../include/PacketTyper.h"
#include   "../include/NetSystem.h"
#include   "../include/EventSystem.h"
#include   "../include/EventTyper.h"
#include   "../include/CPublicVarReader.h"
#include   <include/mem/MemNode.h>
#include "../include/NFControlsManager.h"

C2SBattleRecordPacket::C2SBattleRecordPacket(int battleID)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=ROLEINFODATAHANDLER->updateRoleAthleticsSerialID();
	m_battleID=battleID;
	//最后获取长度
	m_len=GetPacketLength();
}

unsigned  int  C2SBattleRecordPacket::GetPacketType()
{
	return _TYPEF_PACKET_C2S_ARENA_HISTORY_BATTLEINFO_CLEINT_;
}

unsigned  int  C2SBattleRecordPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_serial)+sizeof(m_battleID);
}

bool  C2SBattleRecordPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

 void  C2SBattleRecordPacket::Send()
 {
	 NFC_showCommunicationWating(true);
	 MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	 pNode->push(m_head, sizeof(m_head));
	 pNode->push(m_len);
	 pNode->push(m_pn);
	 pNode->push(m_serial);
	 pNode->push(m_battleID);
	  
	 NETSYSTEM->SendPacket(pNode);
 }