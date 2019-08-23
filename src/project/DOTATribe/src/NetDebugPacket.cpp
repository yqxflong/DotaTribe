// Name :		NetDebugPacket.h
// Function:	ÍøÂçdebug°ü
// Author :		ÒüÇ¿

#include "../include/NetDebugPacket.h"
#include "../include/PacketTyper.h"

CSLoginDuringPacket::CSLoginDuringPacket(long long tAuth,long long tRoleList,long long tLogin){
	short count=3;
	PushData(count);
	//
	short code_auth=_TYPED_PACKET_C2S_LOGIN_P_;
	int time_auth=(int)tAuth;
	PushData(code_auth);
	PushData(time_auth);
	//
	short code_role=_TYPED_PACKET_C2S_ROLELIST_;
	int time_role=(int)tRoleList;
	PushData(code_role);
	PushData(time_role);
	//
	short code_login=_TYPED_PACKET_C2S_ENTERGAME_;
	int time_login=(int)tLogin;
	PushData(code_login);
	PushData(time_login);
}

unsigned  int CSLoginDuringPacket::GetPacketType(){
	return _TYPED_PACKET_C2S_NETDEBUG_LOGIN_DURING_;
}