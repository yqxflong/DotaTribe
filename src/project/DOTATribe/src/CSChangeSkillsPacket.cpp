//Name： CSChangeSkillsPacket
//Function：换技能包
//Author：Johny


#include   "../include/CSChangeSkillsPacket.h"
#include "../include/PacketTyper.h"

CSChangeSkillsPacket::CSChangeSkillsPacket(int serialID,short sourceSkillID,char sourceIndex,char targetIndex,unsigned char heroIndex)
{ 
	PushData(serialID);
	PushData(sourceSkillID);
	PushData(sourceIndex);
	PushData(targetIndex);
	PushData(heroIndex);
}

unsigned  int  CSChangeSkillsPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHANGESKILLS_ ;
}

CSUnLockSkillPacket::CSUnLockSkillPacket(unsigned char skillNotchIndex)
{ 
	PushData(skillNotchIndex);
}
CSUnLockSkillPacket::~CSUnLockSkillPacket()
{ 
}

unsigned  int  CSUnLockSkillPacket::GetPacketType()
{
  return _TYPED_PACKET_C2S_UNLOCK_SKILL_CLIENT_; 
}
  