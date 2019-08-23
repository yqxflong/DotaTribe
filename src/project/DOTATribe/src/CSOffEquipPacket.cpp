//Name£ºCSOffEquipPacket
//Function£ºc->s Ð¶µô×°±¸
//Written By£ºÒüÇ¿

#include "../include/CSOffEquipPacket.h"
#include "../include/PacketTyper.h"

CSOffEquipPacket::CSOffEquipPacket(int serial,int equipid,int heroPos){
	PushData(serial);
	PushData(equipid);
	PushData((unsigned char)heroPos);
};

unsigned  int  CSOffEquipPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_OFFEQUIP_;
}