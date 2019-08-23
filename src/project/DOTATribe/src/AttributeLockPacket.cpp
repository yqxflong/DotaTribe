//Name:AttributeLockPacket
//Function: 属性锁定包
//Author:fangjun
//Date:20130821
#include <cocos2d.h>
#include "../include/AttributeLockPacket.h"
#include "../include/EquipTrainDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"


/************************************************************************/
/* 属性加锁部分                                                                     */
/************************************************************************/
CSAttributeLockPacket::CSAttributeLockPacket(int serial, int eqid, unsigned char attriIndex)
:serial(serial)
,equipId(eqid)
,attriIndex(attriIndex)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSAttributeLockPacket::~CSAttributeLockPacket()
{
}

unsigned  int  CSAttributeLockPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ATTRIBUTELOCK_;
}

unsigned  int  CSAttributeLockPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(serial) + sizeof(equipId) + sizeof(attriIndex);
}

bool  CSAttributeLockPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSAttributeLockPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(serial);
	pNode->push(equipId);
	pNode->push(attriIndex);

	NETSYSTEM->SendPacket(pNode);
}


SCAttributeLockResultPacket::SCAttributeLockResultPacket()
{

}
SCAttributeLockResultPacket::~SCAttributeLockResultPacket()
{

}

unsigned  int  SCAttributeLockResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ATTRIBUTELOCKRESULT_;
}

unsigned  int  SCAttributeLockResultPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCAttributeLockResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//读取加锁属性信息
	EQUIPTRAINDATAHANDLER->m_pLock.decodePacketData(packet);

	return true;
}

void  SCAttributeLockResultPacket::Send()
{
}

SCAttributeLockResultPacketFactory::SCAttributeLockResultPacketFactory()
{

}

SCAttributeLockResultPacketFactory::~SCAttributeLockResultPacketFactory()
{

}

unsigned  int  SCAttributeLockResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ATTRIBUTELOCKRESULT_;
}

bool  SCAttributeLockResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAttributeLockResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//改变存储中当前装备的锁状态
	if(EQUIPTRAINDATAHANDLER->m_pLock.equipId == EQUIPTRAINDATAHANDLER->GetCurEquipId())
		EQUIPTRAINDATAHANDLER->AddLock(EQUIPTRAINDATAHANDLER->m_pLock.attributeIndex);

	
	EQUIPTRAINDATAHANDLER->ToClientLockAttributeResult();

	return true;
}


/************************************************************************/
/* 属性解锁部分                                                                     */
/************************************************************************/

CSAttributeUnLockPacket::CSAttributeUnLockPacket(int s, int eid, int index)
:serial(s)
,equipId(eid)
,attriIndex(index)
{
	m_head[0]='Z';
	m_head[1]='R';

	m_pn = GetPacketType();
	m_len = GetPacketLength();

}

CSAttributeUnLockPacket::~CSAttributeUnLockPacket()
{

}

unsigned  int  CSAttributeUnLockPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ATTRIBUTEUNLOCK_;
}

unsigned  int  CSAttributeUnLockPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn) + sizeof(serial) + sizeof(equipId) + sizeof(attriIndex);
}

bool  CSAttributeUnLockPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void CSAttributeUnLockPacket:: Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(serial);
	pNode->push(equipId);
	pNode->push(attriIndex);

	NETSYSTEM->SendPacket(pNode);
}


SCAttributeUnLockResultPacket::SCAttributeUnLockResultPacket()
{

}
SCAttributeUnLockResultPacket::~SCAttributeUnLockResultPacket()
{

}
unsigned  int  SCAttributeUnLockResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ATTRIBUTEUNLOCKRESULT_;
}
unsigned  int  SCAttributeUnLockResultPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCAttributeUnLockResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//读取加锁属性信息
	EQUIPTRAINDATAHANDLER->m_pUnLock.decodePacketData(packet);

	return true;
}

void  SCAttributeUnLockResultPacket::Send()
{
//no
}


SCAttributeUnLockResultPacketFactory::SCAttributeUnLockResultPacketFactory()
{
	
}

SCAttributeUnLockResultPacketFactory::~SCAttributeUnLockResultPacketFactory()
{

}

unsigned  int  SCAttributeUnLockResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ATTRIBUTEUNLOCKRESULT_;
}


bool  SCAttributeUnLockResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAttributeUnLockResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	//改变存储中当前装备的锁状态
	if(EQUIPTRAINDATAHANDLER->m_pUnLock.equipId == EQUIPTRAINDATAHANDLER->GetCurEquipId())
		EQUIPTRAINDATAHANDLER->DeleteLock(EQUIPTRAINDATAHANDLER->m_pUnLock.attributeIndex);
	
	EQUIPTRAINDATAHANDLER->ToClientUnLockAttributeResult();

	return true;
}
