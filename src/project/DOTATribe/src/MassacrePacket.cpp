// Name :		MassacrePacket.h
// Function:	É¨µ´ÏûÏ¢°ü
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/MassacrePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/WindowManager.h"
#include "../include/MissionDataHandler.h"
#include "../include/MassacreDataHandler.h"
#include "../include/MassacreWindow.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SMassacrePacket::C2SMassacrePacket(int mapid ,int stageid){
	int serial=0;
	PushData(serial);
	PushData(mapid);
	PushData(stageid);
};

unsigned  int  C2SMassacrePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASSACRE_;
}

unsigned  int  S2CMassacrePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASSACRERESULT_;
}

unsigned  int  S2CMassacrePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CMassacrePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	MassacreDataHandler::get_instance2()->decodePacketData(packet);

	return true;
}

unsigned  int S2CMassacrePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASSACRERESULT_;
}

bool S2CMassacrePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CMassacrePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	return true;
}
