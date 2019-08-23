// Name :		NetDebugPacket.h
// Function:	ÍøÂçdebug°ü
// Author :		ÒüÇ¿

#ifndef _PACKET_NetDebugPacket_H_
#define _PACKET_NetDebugPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"

class CSLoginDuringPacket : public DotaPacket
{
public:
	CSLoginDuringPacket(long long tAuth,long long tRoleList,long long tLogin);
	virtual ~CSLoginDuringPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};


#endif