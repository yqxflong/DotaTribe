//Name：CheckRoleBaseInfoPacket
//Function：c->s 查看人物基本信息
//Written By：lvyunlong
//Date:20131225

#include <cocos2d.h>
#include "../include/CheckRoleBaseInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/RoleInfoDataHandler.h"
CSCheckRoleBaseInfoPacket::CSCheckRoleBaseInfoPacket()
{

}

CSCheckRoleBaseInfoPacket::~CSCheckRoleBaseInfoPacket()
{

}

unsigned  int  CSCheckRoleBaseInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHECKROLEBASEINFO_;
}

bool  SCCheckRoleBaseInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	CHECKROLEBASEINFOHANDLER->decodePacketData(packet);

	return true;
}

unsigned  int  SCCheckRoleBaseInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECKROLEBASEINFO_RESULT_;
}

bool  SCCheckRoleBaseInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCCheckRoleBaseInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	CheckRoleBaseInfoHandler::get_instance2()->RoleBaseInfoResult();

	return true;
}