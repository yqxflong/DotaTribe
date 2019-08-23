// Name :		ActivityPacket.h
// Function:	活动数据消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/ActivityPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ActivityDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/NFControlsManager.h"


#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SActivityPacket::C2SActivityPacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SActivityPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_;
}

unsigned  int  C2SActivityPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SActivityPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SActivityPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CActivityPacket::S2CActivityPacket()
{

}

S2CActivityPacket::~S2CActivityPacket()
{

}

unsigned  int  S2CActivityPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RESULT_;
}

unsigned  int  S2CActivityPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CActivityPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;  
	ActivityDataHandler::get_instance2()->decodePacket(packet);  
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ACTIVITYWINDOW_,"0");
	return true;
}


void  S2CActivityPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CActivityPacketFactory::S2CActivityPacketFactory()
{

}


S2CActivityPacketFactory::~S2CActivityPacketFactory()
{

}

unsigned  int S2CActivityPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RESULT_;
}

bool S2CActivityPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CActivityPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CActivityPacketHandler(&packet);
	return true;
}	

void S2CActivityPacketFactory::OnS2CActivityPacketHandler(S2CActivityPacket* pPacket)
{

}


/************************************************************************/
/*=====================选择活动=================
/************************************************************************/
C2SChioseActivityPacket::C2SChioseActivityPacket(int index){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_index = index;
	//最后获取长度
	m_len=GetPacketLength();
};
unsigned  int  C2SChioseActivityPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHIOSE_ACTIVITY_;
}
unsigned  int  C2SChioseActivityPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_index);
}
bool  C2SChioseActivityPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SChioseActivityPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_index);
	NETSYSTEM->SendPacket(pNode);
}
/************************************************************************/
/*=====================泡温泉=================
/************************************************************************/
C2SInSpringPacket::C2SInSpringPacket()
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	//最后获取长度
	m_len=GetPacketLength();

}
unsigned  int  C2SInSpringPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_SPING_IN;
}
unsigned  int  C2SInSpringPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
}
bool  C2SInSpringPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SInSpringPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	NETSYSTEM->SendPacket(pNode);
}
//S2C
S2CInSpringPacket::S2CInSpringPacket()
{

}
S2CInSpringPacket::~S2CInSpringPacket()
{

}

unsigned  int  S2CInSpringPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_SPRING_RESULT_;
}

unsigned  int  S2CInSpringPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CInSpringPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//接
	SpringActivityDataHandler::get_instance2()->decodePacket(packet); 
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_SPEING_);
	return true;
}


void  S2CInSpringPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CInSpringPacketFactory::S2CInSpringPacketFactory()
{

}


S2CInSpringPacketFactory::~S2CInSpringPacketFactory()
{

}

unsigned  int S2CInSpringPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_SPRING_RESULT_;
}

bool S2CInSpringPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CInSpringPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CInSpringPacketHandler(&packet);
	return true;
}	

void S2CInSpringPacketFactory::OnS2CInSpringPacketHandler(S2CInSpringPacket* pPacket)
{

}
/************************************************************************/
/* 领取温泉奖励返回                                                      */
/************************************************************************/
S2CSpringRewardPacket::S2CSpringRewardPacket()
{ 
}
S2CSpringRewardPacket::~S2CSpringRewardPacket()
{ 
}

bool  S2CSpringRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	SpringActivityDataHandler::get_instance2()->setSpringIsOpen(1);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ACTIVITYWINDOW_SPEING_);
	unsigned int id = SpringActivityDataHandler::get_instance2()->getSpringActiviId();
	ActivityInfoItem * pActivityInfo = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(id);
	pActivityInfo->setActivityOpen(0);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEEFFECT_ACTIVITY_,_to_event_param_(id));
	ActivityDataHandler::get_instance2()->HasSurplusActivity();
	

	return true;
}

void  S2CSpringRewardPacket::Send(){
	//S->C不需要实现发包
}

S2CSpringRewardPacketFactory::S2CSpringRewardPacketFactory()
{ 
}


S2CSpringRewardPacketFactory::~S2CSpringRewardPacketFactory()
{ 
}

unsigned  int S2CSpringRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_SPRINGREWARD_RESULT_;
}

bool S2CSpringRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CSpringRewardPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	return true;
}	

/************************************************************************/
/*=====================升级奖励=================
/************************************************************************/

S2CLevelUpRewardInfoPacket::S2CLevelUpRewardInfoPacket()
{ 
}
S2CLevelUpRewardInfoPacket::~S2CLevelUpRewardInfoPacket()
{ 
}

unsigned  int  S2CLevelUpRewardInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_LEVELUPREWARD_;
}

unsigned  int  S2CLevelUpRewardInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CLevelUpRewardInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	LevelUpRewardActivityDataHandler::get_instance2()->DecodePacket(packet);
	
	return true;
}
 
void  S2CLevelUpRewardInfoPacket::Send(){
	//S->C不需要实现发包
}

//////////////////////////////////////////////////////////////////////////
S2CLevelUpRewardInfoPacketFactory::S2CLevelUpRewardInfoPacketFactory()
{ 
}


S2CLevelUpRewardInfoPacketFactory::~S2CLevelUpRewardInfoPacketFactory()
{ 
}

unsigned  int S2CLevelUpRewardInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_LEVELUPREWARD_;
}

bool S2CLevelUpRewardInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CLevelUpRewardInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	S2CPacketNotification();
	return true;
}	

void S2CLevelUpRewardInfoPacketFactory::S2CPacketNotification()
{
	//to do
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_UPDATE_LEVELUPREWARDACTIVITYWINDOW_,_to_event_param_(0));
}



C2SGetLevelUpRewardPacket::C2SGetLevelUpRewardPacket(int rewardLevel)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_nRewardLevel = rewardLevel;
	//最后获取长度
	m_len=GetPacketLength();

}
unsigned  int  C2SGetLevelUpRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ACTIVITY_REQUEST_LEVELUPREWARD_;
}
unsigned  int  C2SGetLevelUpRewardPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_nRewardLevel);
}
bool  C2SGetLevelUpRewardPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SGetLevelUpRewardPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength()); 
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_nRewardLevel);
	NETSYSTEM->SendPacket(pNode);
}
 
//////////////////////////////////////////////////////////////////////////


S2CLevelUpRewardRecepitPacket::S2CLevelUpRewardRecepitPacket()
{  
}
S2CLevelUpRewardRecepitPacket::~S2CLevelUpRewardRecepitPacket()
{ 
}
unsigned  int  S2CLevelUpRewardRecepitPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_LEVELUPREWARD_;
}

unsigned  int  S2CLevelUpRewardRecepitPacket::GetPacketLength()
{
	return  sizeof(int);
}

bool  S2CLevelUpRewardRecepitPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	//to do 领取奖励回执消息 
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_LEVELUPREWARDACTIVITYWINDOW_,_to_event_param_(1));
	return true;
}

S2CLevelUpRewardRecepitPacketFactory::S2CLevelUpRewardRecepitPacketFactory()
{ 
}

S2CLevelUpRewardRecepitPacketFactory::~S2CLevelUpRewardRecepitPacketFactory()
{ 
}

unsigned  int S2CLevelUpRewardRecepitPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ACTIVITY_RECEIPT_LEVELUPREWARD_;
}

bool S2CLevelUpRewardRecepitPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CLevelUpRewardRecepitPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	return true;
}	


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
  
S2CExchangeInfoPacket::S2CExchangeInfoPacket()
{  
}
S2CExchangeInfoPacket::~S2CExchangeInfoPacket()
{ 
}
unsigned  int  S2CExchangeInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EXCHANGE_INFO_SERVER_;
}

unsigned  int  S2CExchangeInfoPacket::GetPacketLength()
{
	return  sizeof(int);
}

bool  S2CExchangeInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	ExchangeActivityDataHandler::get_instance2()->decodePacket(packet);
	return true;
}

S2CExchangeInfoPacketFactory::S2CExchangeInfoPacketFactory()
{ 
}

S2CExchangeInfoPacketFactory::~S2CExchangeInfoPacketFactory()
{ 
}

unsigned  int S2CExchangeInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EXCHANGE_INFO_SERVER_;
}

bool S2CExchangeInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CExchangeInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;  

	return true;
}	

//////////////////////////////////////////////////////////////////////////
 
C2SExchangeExchangePacket::C2SExchangeExchangePacket(short activityID,short exchangeID)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType(); 
	m_nActivityID =  activityID;
	m_nExchangeID =  exchangeID;
	//最后获取长度
	m_len=GetPacketLength();

}
unsigned  int  C2SExchangeExchangePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EXCHANGE_EXCHANGE_CLIENT_;
}
unsigned  int  C2SExchangeExchangePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_nActivityID)+sizeof(m_nExchangeID);
}
bool  C2SExchangeExchangePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}
void  C2SExchangeExchangePacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength()); 
	NFC_showCommunicationWating(true);
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_nActivityID);
	pNode->push(m_nExchangeID);
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
 
S2CExchangeExchangePacket::S2CExchangeExchangePacket()
{  
}
S2CExchangeExchangePacket::~S2CExchangeExchangePacket()
{ 
}
unsigned  int  S2CExchangeExchangePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EXCHANGE_EXCHANGE_SERVER_;
}

unsigned  int  S2CExchangeExchangePacket::GetPacketLength()
{
	return  sizeof(int);
}

bool  S2CExchangeExchangePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	ExchangeActivityDataHandler::get_instance2()->decodeExchangeSuccessPacket(packet);
	return true;
}

S2CExchangeExchangePacketFactory::S2CExchangeExchangePacketFactory()
{ 
}

S2CExchangeExchangePacketFactory::~S2CExchangeExchangePacketFactory()
{ 
}

unsigned  int S2CExchangeExchangePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EXCHANGE_EXCHANGE_SERVER_;
}

bool S2CExchangeExchangePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CExchangeExchangePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;   
	return true;
}	
