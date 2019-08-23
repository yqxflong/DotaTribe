// Name :		NoticeGatewayPacket.h
// Function:	���ص�¼����������Ϣ��
// Author :		�۱�	
// Maintainer:  �۱� 


#include "../include/NoticeGatewayPacket.h"

#include <cocos2d.h>
#include "../include/PacketTyper.h"
#include "../include/HTTPTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"
#include "../include/ServerInfoDataHandler.h"


#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;

//////////////////////////////////////////////////////////////////////////
//							��¼����C->S								//
//////////////////////////////////////////////////////////////////////////

C2SNoticeGatewayPacket::C2SNoticeGatewayPacket(){
}

C2SNoticeGatewayPacket::~C2SNoticeGatewayPacket(){
}

unsigned int C2SNoticeGatewayPacket::GetPacketType(){
	return _TYPED_HTTP_C2S_NOTICEBOX_GATEWAY_;
}

//////////////////////////////////////////////////////////////////////////
//							��¼����S->C								//
//////////////////////////////////////////////////////////////////////////


unsigned int S2CNoticeGatewayPacket::GetPacketType(){
	return _TYPED_HTTP_S2C_NOTICEBOX_GATEWAY_;
}

unsigned int S2CNoticeGatewayPacket::GetPacketLength(){
	return sizeof(int);
}

bool S2CNoticeGatewayPacket::Read(char* pBuffer, unsigned int iLen){

	DPacket packet(pBuffer,iLen);

	ServerInfoDataHandler::get_instance2()->decodePacketData_Notice_Gateway(packet);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//							��¼����Factory								//
//////////////////////////////////////////////////////////////////////////

unsigned int S2CNoticeGatewayPacketFactory::GetPacketType(){
	return _TYPED_HTTP_S2C_NOTICEBOX_GATEWAY_;
}

bool S2CNoticeGatewayPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen){
	S2CNoticeGatewayPacket packet;
	if(!packet.Read(pBuffer,iLen))
		return false;
	ServerInfoDataHandler::get_instance2()->AfterDecodeNoticeGatewayData();
	return true;
}