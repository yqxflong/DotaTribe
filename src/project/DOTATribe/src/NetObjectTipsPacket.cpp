//Name:NetObjectTipsPacket
//Function: 网络物品tips
//Author:方骏
//Date:20131014

#include <cocos2d.h>
#include "../include/NetObjectTipsPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NetObjectTipsDataHandler.h"


CSNetObjectTipsPacket::CSNetObjectTipsPacket(int templateId) 
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_iTemplateId = templateId;
}

CSNetObjectTipsPacket::~CSNetObjectTipsPacket()
{

}

unsigned  int  CSNetObjectTipsPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_NETOBJECTTIPS_;
}

unsigned  int  CSNetObjectTipsPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_iTemplateId);
}

void  CSNetObjectTipsPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_iTemplateId);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int SCNetObjectTipsResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_NETOBJECTTIPS_RESULT_;
}


bool  SCNetObjectTipsResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	//读取组队副本所有数据
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(NETOBJECTTIPSDATAHANDLER->m_pObjectTips == NULL)
	{
		NETOBJECTTIPSDATAHANDLER->m_pObjectTips = new NetObjectTips();
	}

	NETOBJECTTIPSDATAHANDLER->m_pObjectTips->decodePacketData(packet);

	return true;
}


unsigned  int  SCNetObjectTipsResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_NETOBJECTTIPS_RESULT_;
}

bool  SCNetObjectTipsResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCNetObjectTipsResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	
	NETOBJECTTIPSDATAHANDLER->ToClientGetObjectTips();

	return true;
}