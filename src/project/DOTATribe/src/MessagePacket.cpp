
#include "../include/MessagePacket.h"

MessagePacket::MessagePacket()
{
	m_ObjectType = UNKOWN_MESSAGEPACKET_TYPE;
	m_LogicTickCount = 0;
	m_isValid = true;
	m_ObjectSubID = 0;
}

MessagePacket::~MessagePacket()
{
	m_ObjectType = UNKOWN_MESSAGEPACKET_TYPE;
}


int MessagePacket::GetObjectType()
{
	return m_ObjectType;
}

void   MessagePacket::SetObjectType(int ObjectType)
{
	if(m_ObjectType != ObjectType)
	{
		m_ObjectType = ObjectType;
	}
}

void MessagePacket::Tick()
{
	++m_LogicTickCount;
}


bool MessagePacket::IsValid()
{
	return m_isValid;
}

void MessagePacket::SetIsValid(bool isValid)
{
	if(m_isValid != isValid)
	{
		m_isValid = isValid;
	}
}

void MessagePacket::SetSubObjectID(int subObjectId)
{
	if(m_ObjectSubID != subObjectId)
	{
		m_ObjectSubID = subObjectId;
	}
}


int MessagePacket::GetSubObjectID()
{
	return  m_ObjectSubID;
}

