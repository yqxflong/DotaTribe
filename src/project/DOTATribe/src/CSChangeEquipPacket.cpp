//Name��CSChangeEquipPacket
//Function��c->s ����װ��
//Written By����ǿ

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