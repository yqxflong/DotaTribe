//Name：CSEnterTranscriptRequestPacket
//Function：请求战斗数据
//Author:	Johny

#ifndef   _DOTATRIBE_CSENTERTRANSCRIPTREQUESTPACKEET_H_
#define   _DOTATRIBE_CSENTERTRANSCRIPTREQUESTPACKEET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include "../include/DotaPacket.h"

class  CSEnterTranscriptRequestPacket : public DotaPacket
{
public:
	/*
	   param1:  协议序列ID
	   param2:  副本地图ID
	   param3:  副本关卡ID
	*/
	CSEnterTranscriptRequestPacket(short mapID,short stageID);
	virtual ~CSEnterTranscriptRequestPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
};





#endif