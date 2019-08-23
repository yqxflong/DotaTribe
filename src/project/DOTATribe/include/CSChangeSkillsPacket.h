//Name： CSChangeSkillsPacket
//Function：换技能包
//Author：Johny

#ifndef   _DOTATRIBE_CSCHANGESKILLSPACKET_H_
#define   _DOTATRIBE_CSCHANGESKILLSPACKET_H_


#include "../include/DotaPacket.h"


class   CSChangeSkillsPacket : public DotaPacket
{
public: 
	CSChangeSkillsPacket(int serialID,short sourceSkillID,char sourceIndex,char targetIndex,unsigned char heroIndex);
	virtual ~CSChangeSkillsPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};
 

class  CSUnLockSkillPacket: public DotaPacket
{ 
public:
	CSUnLockSkillPacket(unsigned char skillNotchIndex);
	~CSUnLockSkillPacket();
public:
	virtual  unsigned  int  GetPacketType();
};
 

#endif