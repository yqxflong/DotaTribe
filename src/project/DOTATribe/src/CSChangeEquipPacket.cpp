//Name：CSChangeEquipPacket
//Function：c->s 更换装备
//Written By：尹强

#include "../include/CSChangEquipPacket.h"
#include "../include/PacketTyper.h"

CSChangeEquipPacket::CSChangeEquipPacket(int serial,int equipid,int heroPos){
	PushData(serial);
	PushData(equipid);
	PushData((unsigned char)heroPos);
};

unsigned  int  CSChangeEquipPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHANGEEQUIP_;
}