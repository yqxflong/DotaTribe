// Name :		ChatPacket.h
// Function:	聊天消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/ChatPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ChatDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SChatPacket::C2SChatPacket(int type,int id,std::string text){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_type =type;
	m_id = id;
	m_sztext=text.length();
	m_text = text;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SChatPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHAT_;
}

unsigned  int  C2SChatPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_type)+sizeof(m_id)+sizeof(m_sztext)+m_text.length();
}
/*
	C->S不需要实现Read函数
*/
bool  C2SChatPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SChatPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	pNode->push(m_type);
	pNode->push(m_id);

	pNode->push(m_sztext);
	char* p =const_cast<char*>(m_text.c_str());
	pNode->push(p,m_sztext);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CChatPacket::S2CChatPacket()
{
	m_dataType=_CHAR_DATA_UNKONW_TYPE_;
}

S2CChatPacket::~S2CChatPacket()
{

}

unsigned  int  S2CChatPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHATRESULT_;
}

unsigned  int  S2CChatPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CChatPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	 
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	unsigned short tmp_len=0;
	char *tmpChar=0;
	 
	packet.read(m_dataType);
	 
	//聊天数据
	ChatData* pChatData = new ChatData();
	pChatData->m_Type=m_dataType;
	packet>>pChatData->m_sendPlayerID;

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	pChatData->m_sendPlayerName.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;
		 

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	pChatData->m_time.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;

	packet>>pChatData->m_receivePlayerID;

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	pChatData->m_receivePlayerName.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;


	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	pChatData->m_text.assign(tmpChar);
	delete[] tmpChar;tmpChar=0;

	ChatDataHandler::get_instance2()->InsertChatData(pChatData);
	 
	 
	return true;
}


void  S2CChatPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CChatPacketFactory::S2CChatPacketFactory()
{

}


S2CChatPacketFactory::~S2CChatPacketFactory()
{

}

unsigned  int S2CChatPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHATRESULT_;
}

bool S2CChatPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CChatPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CChatPacketHandler(&packet);
	return true;
}	

void S2CChatPacketFactory::OnS2CChatPacketHandler(S2CChatPacket* pPacket)
{

}
