//Name：ServerListPacket
//Function：请求服务器列表
//Written By：尹强

#include <cocos2d.h>
#include "../include/ServerListPacket.h"
#include "../include/HttpTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/ServerInfoDataHandler.h"

CSServerListPacket::CSServerListPacket(unsigned char channelID,std::string version)
{
	PushData(channelID);
	PushData(version);
}

unsigned  int  CSServerListPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SERVERLIST_;
}


unsigned  int  SCServerListPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SERVERLIST_;
}

unsigned  int  SCServerListPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCServerListPacket::Read(char* pBuffer, unsigned int iLen)
{

	DPacket packet(pBuffer, iLen);
	SERVERINFODATAINFO->decodePacketData(packet);
	return true;
}

unsigned  int  SCServerListPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SERVERLIST_;
}

bool  SCServerListPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCServerListPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	SERVERINFODATAINFO->AfterDecodeServerList();
	return true;
}