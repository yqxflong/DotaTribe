//Name:EquipLvUpSelectCardPacket.h
//Author;fangjun
//Function:装备升级选卡包

#include <cocos2d.h>
#include "../include/EquipmentLvUpSelectCardPacket.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/PacketTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

CSEquipmentLvUpSelectCardPacket::CSEquipmentLvUpSelectCardPacket(int swallowCount, std::vector<int> & allid)
:m_SwallowCount(swallowCount)
,m_SwallowEquipId(allid)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len = GetPacketLength();

}

CSEquipmentLvUpSelectCardPacket::~CSEquipmentLvUpSelectCardPacket()
{
	m_SwallowEquipId.clear();
}


unsigned  int  CSEquipmentLvUpSelectCardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUIPLEVELUP_SELECTCARD_;
}

unsigned  int  CSEquipmentLvUpSelectCardPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_SwallowCount) + m_SwallowEquipId.size() * sizeof(int);
}


bool  CSEquipmentLvUpSelectCardPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSEquipmentLvUpSelectCardPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_SwallowCount);
	if(m_SwallowCount != m_SwallowEquipId.size())
		return;
	for(int i = 0; i < (int)m_SwallowEquipId.size(); ++i)
	{
		pNode->push(m_SwallowEquipId[i]);
	}

	NETSYSTEM->SendPacket(pNode);
}



SCEquipmentLvUpSelectCardPacket::SCEquipmentLvUpSelectCardPacket()
{

}

SCEquipmentLvUpSelectCardPacket::~SCEquipmentLvUpSelectCardPacket()
{

}

unsigned  int  SCEquipmentLvUpSelectCardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPLEVELUP_SELECTCARD_RESULT_;
}

unsigned  int  SCEquipmentLvUpSelectCardPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCEquipmentLvUpSelectCardPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	unsigned short count = 0;
	int cost = 0;
	packet>>count;

	EQUIPMENTLVUPDATAHANDLER->needMoneyAll = 0;

	for(int i = 0; i < count; ++i)
	{
		int money = 0;
		packet>>money;
		EQUIPMENTLVUPDATAHANDLER->needMoneyAll += money;//全部money
		EQUIPMENTLVUPDATAHANDLER->vecEquipCostMoney.push_back(money);
	}

	return true;
}

void  SCEquipmentLvUpSelectCardPacket::Send()
{
	//不需要

}

SCEquipmentLvUpSelectCardPacketFactory::SCEquipmentLvUpSelectCardPacketFactory()
{

}
SCEquipmentLvUpSelectCardPacketFactory::~SCEquipmentLvUpSelectCardPacketFactory()
{

}

unsigned  int SCEquipmentLvUpSelectCardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPLEVELUP_SELECTCARD_RESULT_;
}

bool  SCEquipmentLvUpSelectCardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEquipmentLvUpSelectCardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	EVENTSYSTEM->PushEvent(_TEPED_EVENT_EQUIPLVUP_GET_COSTMONEY_);

	return true;
}