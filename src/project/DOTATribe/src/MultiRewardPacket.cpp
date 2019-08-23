// Name :		MultiRewardPacket.h
// Function:	多个奖励消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/MultiRewardPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/MultiRewardDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>


#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SMultiRewardPacket::C2SMultiRewardPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SMultiRewardPacket::GetPacketType()
{
	return 0;
}
unsigned  int  C2SMultiRewardPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SMultiRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SMultiRewardPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}
//S2C
S2CMultiRewardPacket::S2CMultiRewardPacket()
{

}
S2CMultiRewardPacket::~S2CMultiRewardPacket()
{

}
unsigned  int  S2CMultiRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MULTIREWARD_RESULT_;
}
unsigned  int  S2CMultiRewardPacket::GetPacketLength()
{
	return sizeof(int);
}
bool  S2CMultiRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	unsigned short tmp_len=0;
	char *tmpChar=0;

	std::vector<MultiRewardData*>::iterator iter =  MultiRewardDataHandler::get_instance2()->MultiRewardDataList.begin();
	std::vector<MultiRewardData*>::iterator iter_end =  MultiRewardDataHandler::get_instance2()->MultiRewardDataList.end();
	for(;iter!=iter_end;++iter)
	{
		delete *(iter);
	}
	MultiRewardDataHandler::get_instance2()->MultiRewardDataList.clear();

	packet>>MultiRewardDataHandler::get_instance2()->MultiRewardNum;
	for (int i=0;i<MultiRewardDataHandler::get_instance2()->MultiRewardNum;i++)
	{
		MultiRewardData* pData = new MultiRewardData;
		packet>>pData->type;
		packet>>pData->itemid;

		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		pData->name.assign(tmpChar);
		delete[] tmpChar;tmpChar=0;

		packet>>pData->iconid;
		packet>>pData->quality;	
		packet>>pData->num;

		MultiRewardDataHandler::get_instance2()->MultiRewardDataList.push_back(pData);
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MULTIREWARDWINDOW_);
	return true;
}
void  S2CMultiRewardPacket::Send(){
	//S->C不需要实现发包
}
//工厂
S2CMultiRewardPacketFactory::S2CMultiRewardPacketFactory()
{

}
S2CMultiRewardPacketFactory::~S2CMultiRewardPacketFactory()
{

}
unsigned  int S2CMultiRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MULTIREWARD_RESULT_;
}
bool S2CMultiRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CMultiRewardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CMultiRewardPacketHandler(&packet);
	return true;
}	
void S2CMultiRewardPacketFactory::OnS2CMultiRewardPacketHandler(S2CMultiRewardPacket* pPacket)
{

}
