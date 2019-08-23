//Name:EquipLvUpPacket.h
//Author;fangjun
//Function:装备升级包
#include <cocos2d.h>
#include "../include/EquipmentLvUpPacket.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/PacketTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"

CSEquipmentLvUpPacket::CSEquipmentLvUpPacket(int equipid,int swallowCount, std::vector<int> & allid)
:m_EquipId(equipid)
,m_SwallowCount(swallowCount)
,m_SwallowEquipId(allid)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len = GetPacketLength();

}

CSEquipmentLvUpPacket::~CSEquipmentLvUpPacket()
{
	m_SwallowEquipId.clear();
}


unsigned  int  CSEquipmentLvUpPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUIPMENTLVUP_;
}

unsigned  int  CSEquipmentLvUpPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(m_EquipId) + sizeof(m_SwallowCount) + m_SwallowEquipId.size() * sizeof(int);
}


bool  CSEquipmentLvUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSEquipmentLvUpPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_EquipId);
	pNode->push(m_SwallowCount);
	for(int i = 0; i < (int)m_SwallowEquipId.size(); ++i)
	{
		pNode->push(m_SwallowEquipId[i]);
	}

	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCEquipmentLvUpPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPMENTLVUP_RESULT_;
}

unsigned  int  SCEquipmentLvUpPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCEquipmentLvUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取数据
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(EQUIPMENTLVUPDATAHANDLER->equipLvUpData == NULL)
	{
		EQUIPMENTLVUPDATAHANDLER->equipLvUpData = new EquipmentLvUpData();
	}
	EQUIPMENTLVUPDATAHANDLER->equipLvUpData->decodePacket(packet);

	return true;
}

unsigned  int SCEquipmentLvUpPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPMENTLVUP_RESULT_;
}

bool  SCEquipmentLvUpPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEquipmentLvUpPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//通知界面升级结果
	EQUIPMENTLVUPDATAHANDLER->HandleAfterEquipLvup();

	EVENTSYSTEM->PushEvent2(_TEPED_EVENT_EQUIPLVUP_GET_LVUPRESULT_);

	return true;
}

