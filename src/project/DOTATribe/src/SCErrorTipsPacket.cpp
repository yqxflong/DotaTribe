#include <cocos2d.h>
#include "../include/SCErrorTipsPacket.h" 
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h" 
#include "../include/NFControlsManager.h"
 
using  namespace  cobra_win;
 
unsigned  int  SCErrorTipsPacket::GetPacketType()
{
	return  _TYPED_PACKET_S2C_MESSAGE_PROMPT_SERVER_;
}

unsigned  int  SCErrorTipsPacket::GetPacketLength()
{
	return  sizeof(int);
}
 
 
bool  SCErrorTipsPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	unsigned short tmp_len = 0;
	char * tmpChar=NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	m_smsg.assign(tmpChar);
	delete [] tmpChar;
	tmp_len=0;
	 
	return true;
}

std::string  &  SCErrorTipsPacket::GetServerMessage()
{
	return m_smsg;
}

unsigned  int SCErrorTipsPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MESSAGE_PROMPT_SERVER_;
}

bool SCErrorTipsPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCErrorTipsPacket packet;
	if(!packet.Read(pBuffer, iLen))
	return false;
	PostNotification(packet);
	//取消转圈
	NFC_showCommunicationWating(false);
	return true;
}	

void   SCErrorTipsPacketFactory::PostNotification(SCErrorTipsPacket &packet)
{
	NFC_showErrorTips_2(packet.GetServerMessage());
}

