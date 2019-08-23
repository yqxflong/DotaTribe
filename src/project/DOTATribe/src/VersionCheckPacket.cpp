//Name��VersionCheckPacket
//Function���汾����
//Written By����ǿ

#include <cocos2d.h>
#include "../include/VersionCheckPacket.h"
#include "../include/HTTPTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/DPacket.h>
#include "../include/UpdateSystem.h"
/************************************************************************/
/* ��ȡ�汾��Ϣ					                                                                */
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
	���հ汾��Ϣ
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
	���հ汾��Ϣ����
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