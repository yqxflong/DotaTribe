#include <cocos2d.h>
#include "../include/EquipPromotePacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/EquipPromoteDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"


#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SEquipPromotePacket::C2SEquipPromotePacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id = id;
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SEquipPromotePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUIPPROMOTE_;
}
unsigned  int  C2SEquipPromotePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
bool  C2SEquipPromotePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SEquipPromotePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);
	NETSYSTEM->SendPacket(pNode);
}
//S2C
S2CEquipPromotePacket::S2CEquipPromotePacket()
{

}
S2CEquipPromotePacket::~S2CEquipPromotePacket()
{

}
unsigned  int  S2CEquipPromotePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPPROMOTE_RESULT_;
}
unsigned  int  S2CEquipPromotePacket::GetPacketLength()
{
	return sizeof(int);
}
bool  S2CEquipPromotePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	EquipPromoteDataHandler::get_instance2()->m_Attribute_List.clear();
	EquipPromoteDataHandler::get_instance2()->m_Item_List.clear();

	packet>>EquipPromoteDataHandler::get_instance2()->m_Item_ID;
	packet>>EquipPromoteDataHandler::get_instance2()->m_Lv_IsMax;
	if (EquipPromoteDataHandler::get_instance2()->m_Lv_IsMax)
	{
		unsigned char count;
		unsigned char itemcount;
		packet>>count;
		for (int i=0;i<count;i++)
		{
			EquipPromoteData data;
			packet>>data.type;
			packet>>data.nextValue;
			EquipPromoteDataHandler::get_instance2()->m_Attribute_List.push_back(data);
		}
		packet>>itemcount;
		for (int i=0;i<itemcount;i++)
		{
			EquipPromoteItemData data;
			packet>>data.templateid;
			packet>>data.iocn;
			packet>>data.quality;
			packet>>data.needNum;
			packet>>data.hasNum;
			EquipPromoteDataHandler::get_instance2()->m_Item_List.push_back(data);
		}
		packet>>EquipPromoteDataHandler::get_instance2()->m_CostMoney;
		packet>>EquipPromoteDataHandler::get_instance2()->m_Lv_Limit;
		packet>>EquipPromoteDataHandler::get_instance2()->m_Lv_Up;
	}
	EVENTSYSTEM->PushEvent(_TEPED_EVENT_UPDATRA_EQUIPPROMOTE_);
	NFC_showCommunicationWating(false);
	return true;
}
void  S2CEquipPromotePacket::Send(){
	//S->C不需要实现发包
}
S2CEquipPromotePacketFactory::S2CEquipPromotePacketFactory()
{

}
S2CEquipPromotePacketFactory::~S2CEquipPromotePacketFactory()
{

}
unsigned  int S2CEquipPromotePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPPROMOTE_RESULT_;
}
bool S2CEquipPromotePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CEquipPromotePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CEquipPromotePacketHandler(&packet);
	return true;
}	
void S2CEquipPromotePacketFactory::OnS2CEquipPromotePacketHandler(S2CEquipPromotePacket* pPacket)
{

}



C2SSurePromotePacket::C2SSurePromotePacket(int id){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_id = id;
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SSurePromotePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SUREPROMOTE_;
}
unsigned  int  C2SSurePromotePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_id);
}
bool  C2SSurePromotePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SSurePromotePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_id);
	NETSYSTEM->SendPacket(pNode);
}
//S2C
S2CSurePromotePacket::S2CSurePromotePacket()
{

}
S2CSurePromotePacket::~S2CSurePromotePacket()
{

}
unsigned  int  S2CSurePromotePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SUREPROMOTE_RESULT_;
}
unsigned  int  S2CSurePromotePacket::GetPacketLength()
{
	return sizeof(int);
}
bool  S2CSurePromotePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	return true;
}
void  S2CSurePromotePacket::Send(){
	//S->C不需要实现发包
}
S2CSurePromotePacketFactory::S2CSurePromotePacketFactory()
{

}
S2CSurePromotePacketFactory::~S2CSurePromotePacketFactory()
{

}
unsigned  int S2CSurePromotePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SUREPROMOTE_RESULT_;
}
bool S2CSurePromotePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CSurePromotePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CSurePromotePacketHandler(&packet);
	return true;
}	
void S2CSurePromotePacketFactory::OnS2CSurePromotePacketHandler(S2CSurePromotePacket* pPacket)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_EQUIPPROMOTE_RESULT_);
}