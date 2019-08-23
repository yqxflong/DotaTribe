#include "../include/EquipCastPacket.h"
#include "../include/EquipRecastDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/EquipsRecastSubView.h"
//////////////////////////////////////////////////////////////////////////
//		����װ��������Ϣ                                   */
//////////////////////////////////////////////////////////////////////////

CSEquipRecastInfoPacket::CSEquipRecastInfoPacket(int equipID)
{
	PushData(equipID);
}

CSEquipRecastInfoPacket::~CSEquipRecastInfoPacket()
{

}
 

//////////////////////////////////////////////////////////////////////////
//  ����װ����������Ϣ
//////////////////////////////////////////////////////////////////////////
 
bool SCEquipRecastInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	EquipRecastDataHandler::get_instance2()->decodePacket(packet);
 	return true;
}

bool  SCEquipRecastInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
    SCEquipRecastInfoPacket  packet;
	if(!packet.Read(pBuffer,iLen))
	{ 
		return false;
	}
	//todo Post Event 
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_EQUIPRECAST_UPDATE_,_to_event_param_(EquipsRecastSubView::_EQUIP_CAST_UPDATE_EQUIP_INFO_));
	return true;
}


//////////////////////////////////////////////////////////////////////////
// ����װ��װ������	   
//////////////////////////////////////////////////////////////////////////

CSEquipRecastDoPacket::CSEquipRecastDoPacket(int equipID)
{ 
   PushData(equipID);
}

CSEquipRecastDoPacket::~CSEquipRecastDoPacket()
{ 

}
 

//////////////////////////////////////////////////////////////////////////
// ����������װ�������ɹ�
//////////////////////////////////////////////////////////////////////////

bool SCEquipRecastDoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn; 
	//EquipRecastDataHandler::get_instance2()->decodeSuccessRecastPacket(packet);
	return true;
}

bool SCEquipRecastDoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEquipRecastDoPacket  packet;
	if(!packet.Read(pBuffer,iLen))
	{ 
		return false;
	}
	//Post Event 
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_EQUIPRECAST_UPDATE_,_to_event_param_(EquipsRecastSubView::_RQUIP_CAST_UPDATE_EQUIP_SUCCESS_DO_));
	return true;
}



