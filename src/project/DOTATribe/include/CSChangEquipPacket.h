//Name��CSChangeEquipPacket
//Function��c->s ����װ��
//Written By����ǿ
#ifndef  _PACKECT_CSCREATEROLE_H_
#define  _PACKECT_CSCREATEROLE_H_

#include "../include/DotaPacket.h"

class CSChangeEquipPacket : public DotaPacket
{
public:
	CSChangeEquipPacket(int serial,int equipid,int heroPos=0);
	virtual ~CSChangeEquipPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};


#endif

