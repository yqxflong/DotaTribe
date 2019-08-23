//Name:EquipTrainPacket
//Function: 属性锁定包
//Author:fangjun
//Date:20130821
#include <cocos2d.h>
#include "../include/EquipTrainPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EquipTrainDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
////////////////////////////////////////////////////////////////////

CSEquipTrainGetLockStatus::CSEquipTrainGetLockStatus(int eqid):equipId(eqid)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSEquipTrainGetLockStatus::~CSEquipTrainGetLockStatus(){}

unsigned  int  CSEquipTrainGetLockStatus::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUIPTRAIN_GETLOCKSTATUS_;
}

unsigned  int CSEquipTrainGetLockStatus::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(equipId);
}

bool  CSEquipTrainGetLockStatus::Read(char* pBuffer, unsigned int iLen)
{
	//no need
	return true;
}

void  CSEquipTrainGetLockStatus::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(equipId);

	NETSYSTEM->SendPacket(pNode);

}

SCEquipTrainGetLockStatusResultPacket::SCEquipTrainGetLockStatusResultPacket()
{

}

SCEquipTrainGetLockStatusResultPacket::~SCEquipTrainGetLockStatusResultPacket()
{

}

unsigned  int  SCEquipTrainGetLockStatusResultPacket::GetPacketType()
{
	return _TYPED_PACEKT_S2C_EQUIPTRAIN_GETLOCKSTATUS_RESULT_;
}

unsigned  int  SCEquipTrainGetLockStatusResultPacket::GetPacketLength()
{
	return sizeof(1);
}

bool  SCEquipTrainGetLockStatusResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	//读取洗练数据
	EQUIPTRAINDATAHANDLER->decodePacketData(packet);

	NFC_showCommunicationWating(false);
	return true;
}

void  SCEquipTrainGetLockStatusResultPacket::Send()
{
	//no need
}


SCEquipTrainGetLockStatusResultPacketFactory::SCEquipTrainGetLockStatusResultPacketFactory()
{

}
SCEquipTrainGetLockStatusResultPacketFactory::~SCEquipTrainGetLockStatusResultPacketFactory()
{

}

unsigned int SCEquipTrainGetLockStatusResultPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_EQUIPTRAIN_GETLOCKSTATUS_RESULT_;
}

bool SCEquipTrainGetLockStatusResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEquipTrainGetLockStatusResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	EQUIPTRAINDATAHANDLER->ToClientGetAttributeLockStatusResult();

	return true;
}

/////////////////////////////////////////////////////////////////////

CSEquipTrainPacket::CSEquipTrainPacket(int eqid)
:equipId(eqid)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();

}
CSEquipTrainPacket::~CSEquipTrainPacket()
{

}

unsigned  int  CSEquipTrainPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EQUIPTRAIN_;
}

unsigned  int  CSEquipTrainPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(equipId);
}

bool  CSEquipTrainPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSEquipTrainPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(equipId);

	NETSYSTEM->SendPacket(pNode);
}

SCEquipTrainResultPacket::SCEquipTrainResultPacket()
{

}

SCEquipTrainResultPacket::~SCEquipTrainResultPacket()
{

}

unsigned  int  SCEquipTrainResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPTRAINRESULT_;
}

unsigned  int  SCEquipTrainResultPacket::GetPacketLength()
{
	//no need
	return sizeof(int);
}

bool  SCEquipTrainResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	//读取洗练数据
	EQUIPTRAINDATAHANDLER->m_pTrainData.decodePacketData(packet);

	NFC_showCommunicationWating(false);

	return true;
}

void  SCEquipTrainResultPacket::Send()
{
	//no need
}


SCEquipTrainResultPacketFactory::SCEquipTrainResultPacketFactory()
{

}

SCEquipTrainResultPacketFactory::~SCEquipTrainResultPacketFactory()
{

}

unsigned  int  SCEquipTrainResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EQUIPTRAINRESULT_;
}

bool  SCEquipTrainResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEquipTrainResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	//读取完数据后需要将新数据改变内存中的数据
	EQUIPTRAINDATAHANDLER->ChangeEquipAttributeByTrainResult();

	EQUIPTRAINDATAHANDLER->ToClientTrainResult();

	return true;
}