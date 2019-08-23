#include  <cocos2d.h>
#include  "../include/SoulEquipPacket.h"
#include  "../include/PacketTyper.h"
#include  "../include/NetSystem.h"
#include  "../include/EventSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/RoleInfoDataHandler.h"
#include  "../include/HeroSoulDataHandler.h"
#include  "../include/RoleSoulsDataHandler.h"
#include   <include/mem/MemNode.h>
#include   <include/mem/EPacket.h>
#include   <include/mem/DPacket.h>
#include "../include/NFControlsManager.h"
 
using  namespace  cobra_win;
 
//////////////////////////////////////////////////////////////////////////
//  战魂开锁请求
//////////////////////////////////////////////////////////////////////////
C2SUnLockHeroSoulPacket::C2SUnLockHeroSoulPacket(char equipIndex, unsigned char heroindex) {
	m_head[0]='Z';
	m_head[1]='R';
	m_uEquipIndex = equipIndex;
	m_heroindex = heroindex;
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SUnLockHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_UNLOCK_CLIENT_;
}

unsigned  int  C2SUnLockHeroSoulPacket::GetPacketLength()
{
	unsigned int  packetLengt=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_uEquipIndex)+sizeof(m_heroindex);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SUnLockHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SUnLockHeroSoulPacket::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_heroindex);
	pNode->push(m_uEquipIndex); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//  服务器返回 解锁战魂索引
//////////////////////////////////////////////////////////////////////////
 
unsigned  int  S2CUnLockHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SOUL_UNLOCK_SERVER_;
}

unsigned  int  S2CUnLockHeroSoulPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CUnLockHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	unsigned char index = 0;
	packet >> index;
	//to do

	IHeroSkinItem* heroskin = NFC_GetTeamHero(index);
	if (heroskin)
	{
		heroskin->getSoulsEquipManager()->decodeUnLockEquipPacket(packet);
	}
	//@RoleSoulsDataHandler::get_instance2()->decodeUnLockEquipPacket(packet);
	return true;
} 

unsigned  int  S2CUnLockHeroSoulPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SOUL_UNLOCK_SERVER_;
}

bool  S2CUnLockHeroSoulPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CUnLockHeroSoulPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;   
    // to do
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_HEROSOUL_VIEW_,_to_event_param_(0));
	return true;
}

//////////////////////////////////////////////////////////////////////////
//  请求装备 战魂
//////////////////////////////////////////////////////////////////////////
C2SEquipHeroSoulPacket::C2SEquipHeroSoulPacket(unsigned char heroindex,int heroSoulBufferID) {
	m_head[0]='Z';
	m_head[1]='R';
	m_nHeroSoulBufferID = heroSoulBufferID;
	m_heroindex = heroindex;
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SEquipHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUP_SOUL_CLIENT_;
}

unsigned  int  C2SEquipHeroSoulPacket::GetPacketLength()
{
	unsigned int  packetLengt = sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_nHeroSoulBufferID) + sizeof(m_heroindex);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SEquipHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SEquipHeroSoulPacket::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_heroindex);
	pNode->push(m_nHeroSoulBufferID); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//  服务器 装备战魂 返回
//////////////////////////////////////////////////////////////////////////
 
unsigned  int  S2CEquipHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUP_SOUL_SERVER_;
}

unsigned  int  S2CEquipHeroSoulPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CEquipHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
    //to do
	RoleSoulsDataHandler::get_instance2()->decodeSoulChangePacket(packet);
	return true;
} 

unsigned  int  S2CEquipHeroSoulPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUP_SOUL_SERVER_;
}

bool  S2CEquipHeroSoulPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CEquipHeroSoulPacket packet;
	if (!packet.Read(pBuffer, iLen))
	return false;    
	//to do
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_HEROSOUL_VIEW_,_to_event_param_(1));
	return true;
}
 
 
//////////////////////////////////////////////////////////////////////////
//  请求 卸载 战魂
//////////////////////////////////////////////////////////////////////////
C2SUnEquipHeroSoulPacket::C2SUnEquipHeroSoulPacket(unsigned char HeroIndex, int heroSoulBufferID, char equipIndex) {
	m_head[0]='Z';
	m_head[1]='R';
	m_nHeroSoulBufferID = heroSoulBufferID; 
	m_cEquipIndex = equipIndex;
	m_HeroIndex = HeroIndex;
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SUnEquipHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_UNEQUP_SOUL_CLIENT_;
}

unsigned  int  C2SUnEquipHeroSoulPacket::GetPacketLength()
{
	unsigned int  packetLengt = sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_nHeroSoulBufferID) + sizeof(m_cEquipIndex) + sizeof(m_HeroIndex);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SUnEquipHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SUnEquipHeroSoulPacket::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_HeroIndex);
	pNode->push(m_nHeroSoulBufferID); 
	pNode->push(m_cEquipIndex); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//   服务器返回 卸载 英雄战魂
////////////////////////////////////////////////////////////////////////// 
unsigned  int  S2CUnEquipHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_UNEQUP_SOUL_SERVER_;
}

unsigned  int  S2CUnEquipHeroSoulPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CUnEquipHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;  
	//to do
	RoleSoulsDataHandler::get_instance2()->decodeSoulUnChangePacket(packet);
	return true;
} 

unsigned  int  S2CUnEquipHeroSoulPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_UNEQUP_SOUL_SERVER_;
}

bool  S2CUnEquipHeroSoulPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CUnEquipHeroSoulPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;   
	//to do 
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_HEROSOUL_VIEW_,_to_event_param_(2));
	return true;
}

