//Name：VersionCheckPacket
//Function：版本检查包
//Written By：尹强

#include <cocos2d.h>
#include "../include/VersionCheckPacket.h"
#include "../include/HTTPTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/DPacket.h>
#include "../include/UpdateSystem.h"
/************************************************************************/
/* 获取版本信息					                                                                */
/************************************************************************/

CSQueryVersionPacket::CSQueryVersionPacket(std::string myVersion)
{
	PushData(myVersion);
}

unsigned  int  CSQueryVersionPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_VERSIONCHECK_;
}

/*
	接收版本信息
*/
unsigned  int  SCQueryVersionPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_VERSIONCHECK_;
}

unsigned  int  SCQueryVersionPacket::GetPacketLength()
{
	return sizeof(1);
}

bool  SCQueryVersionPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	UPDATESYSTEM->decodePacketData(packet);
	return true;
}
/*
	接收版本信息工厂
*/
unsigned int SCQueryVersionPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_VERSIONCHECK_;
}

bool SCQueryVersionPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCQueryVersionPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	UPDATESYSTEM->HandleAfterGetVersionInfo();
	return true;
}