//Name��CSOffEquipPacket
//Function��c->s ж��װ��
//Written By����ǿ
#ifndef  _PACKECT_CSOFFEQUIPPACKET_H_
#define  _PACKECT_CSOFFEQUIPPACKET_H_

#include "../include/DotaPacket.h"

class CSOffEquipPacket : public DotaPacket
{
public:
	CSOffEquipPacket(int serial,int equipid,int heroPos);
	virtual ~CSOffEquipPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};


#endif

