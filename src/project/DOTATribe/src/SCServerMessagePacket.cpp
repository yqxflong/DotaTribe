#include <cocos2d.h>
#include "../include/SCServerMessagePacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include <string>
#include "../include/MessageBoxWindow.h"
#include "../include/EmailDataHandler.h"

using namespace cobra_win;


unsigned  int  SCServerMessagePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SERVERMESSAGE_;
}

unsigned  int  SCServerMessagePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCServerMessagePacket::Read(char* pBuffer, unsigned int iLen)
{
	int stayTime = 0;
	unsigned short strlen = 0;
	char * str = NULL;
	//接收到服务器信息
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	packet>>stayTime;
	packet>>strlen;
	str = new char[strlen + 1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	strMessage_=str;
	delete []str;


	return true;
}



unsigned  int  SCServerMessagePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SERVERMESSAGE_;
}

bool  SCServerMessagePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCServerMessagePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	if (packet.strMessage_ == SysLangDataManager::get_instance2()->GetSysLangById(129) && EMAILDATAHANDLER->m_isGettingAtt == true)
	{
		EMAILDATAHANDLER->GetAllATTStepDone();
	}
	else
		NFC_showCommunicationWating(false);
	
	NFC_showMessageBox(kSERVERMESSAGEPACKET,packet.strMessage_);
	return true;
}

