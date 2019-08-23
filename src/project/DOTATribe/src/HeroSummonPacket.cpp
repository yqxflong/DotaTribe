//Name:HeroSummonPacket
//Function: 英雄召唤相关协议
//Author:lvyunlong
//Date:20131205

#include <cocos2d.h>
#include "../include/HeroSummonPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include  "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/NFControlsManager.h"
#include <map>
using namespace std;

/************************************************************************/
/* 请求进入英雄召唤信息		                                            */
/************************************************************************/
CSHeroSummonInfoPacket::CSHeroSummonInfoPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSHeroSummonInfoPacket::~CSHeroSummonInfoPacket()
{

}

unsigned  int  CSHeroSummonInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROSUMMONINFO_;
}

unsigned  int  CSHeroSummonInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) +  + sizeof(m_len);
}

void  CSHeroSummonInfoPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}


unsigned  int  SCHeroSummonInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROSUMMONINFO_RESULT_;
}

unsigned  int  SCHeroSummonInfoPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeroSummonInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}

void SCHeroSummonInfoPacket::_readInfo(cobra_win::DPacket &packet)
{
	HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->decodePacketData(packet);
}

unsigned  int  SCHeroSummonInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROSUMMONINFO_RESULT_;
}

bool  SCHeroSummonInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroSummonInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//刷新进入召唤界面
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_HEROBARWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 请求进行英雄召唤														*/
/************************************************************************/

CSHeroSoulSummonPacket::CSHeroSoulSummonPacket(unsigned char type,unsigned char times,unsigned char freetype)
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_type = type;
	m_times = times;
	m_freetype = freetype;
	m_len = GetPacketLength();
}

CSHeroSoulSummonPacket::~CSHeroSoulSummonPacket()
{

}

unsigned  int  CSHeroSoulSummonPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROCALL_;
}

unsigned  int  CSHeroSoulSummonPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_type) + sizeof(m_times) + sizeof(m_freetype);
}

void  CSHeroSoulSummonPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_type);
	pNode->push(m_times);
	pNode->push(m_freetype);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCHeroSoulSummonPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROCALL_RESULT_;
}

unsigned  int  SCHeroSoulSummonPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeroSoulSummonPacket::Read(char* pBuffer, unsigned int iLen)
{
	
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCHeroSoulSummonPacket::_readInfo(cobra_win::DPacket &packet)
{
	unsigned char type = 0;
	packet>>type;
	if (type == COMMON_SUMMON)
	{
		HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->mFirstSummon = 1;
	}
	unsigned char size = 0;
	packet>>size;
	int lefttime = 0;
	if (size==1)
	{
		packet>>lefttime;
		if (type == GOLD_SUMMON)
		{
			HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1] = lefttime;
		}
	}
	int iCallType = 0;
	if (type == 1)
	{
		iCallType = type;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_HEROBARWINDOW_,_to_event_param_(iCallType));
	HEROSUMMONCONTROLDATAHANDLER->ClearGainList();
	
	for (int i=0;i<size;i++)
	{
		GainHeroOrDebriData* temp = new GainHeroOrDebriData();
		temp->decodePacketData(packet);
		HEROSUMMONCONTROLDATAHANDLER->m_pGainList.push_back(temp);
	}
}

unsigned  int  SCHeroSoulSummonPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROCALL_RESULT_;
}

bool  SCHeroSoulSummonPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroSoulSummonPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//显示获得英雄的界面
	NFC_showCommunicationWating(false);
	HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
	return true;
}

/************************************************************************/
/* 十连抽获得英雄														*/
/************************************************************************/
unsigned  int  SCTenCallPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TENCALL_RESULT_;
}

unsigned  int  SCTenCallPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCTenCallPacket::Read(char* pBuffer, unsigned int iLen)
{

	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCTenCallPacket::_readInfo(cobra_win::DPacket &packet)
{
	unsigned char type = 0;
	packet>>type;
	if (type == COMMON_SUMMON)
	{
		HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->mFirstSummon = 1;
	}
	unsigned char size = 0;
	packet>>size;
	int lefttime = 0;
	packet>>lefttime;
	if (size==1)
	{
		if (type == GOLD_SUMMON)
		{
			HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1] = lefttime;
		}
	}
	int iCallType = 0;
	if (type == 1)
	{
		iCallType = type;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_HEROBARWINDOW_,_to_event_param_(iCallType));
	HEROSUMMONCONTROLDATAHANDLER->m_pTenCallList.clear();

	for (int i=0;i<size;i++)
	{
		TenCallGainData temp;
		temp.decodePacketData(packet);
		HEROSUMMONCONTROLDATAHANDLER->m_pTenCallList.push_back(temp);
	}
}

unsigned  int  SCSCTenCallPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TENCALL_RESULT_;
}

bool  SCSCTenCallPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTenCallPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//显示获得英雄的界面
	NFC_showCommunicationWating(false);
	//HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TENCALLWINDOW_);
	return true;
}


/************************************************************************/
/* 使用物品获得英雄														*/
/************************************************************************/

unsigned  int  SCUserItemGainHeroPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_USERITEM_GAINHERO_;
}

unsigned  int  SCUserItemGainHeroPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCUserItemGainHeroPacket::Read(char* pBuffer, unsigned int iLen)
{

	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}

void SCUserItemGainHeroPacket::_readInfo(cobra_win::DPacket &packet)
{
	HEROSUMMONCONTROLDATAHANDLER->ClearGainList();
	GainHeroOrDebriData* temp = new GainHeroOrDebriData();
	temp->decodePacketData(packet);
	HEROSUMMONCONTROLDATAHANDLER->m_pGainList.push_back(temp);
}

unsigned  int  SCUserItemGainHeroPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_USERITEM_GAINHERO_;
}

bool  SCUserItemGainHeroPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCUserItemGainHeroPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//显示获得英雄的界面
	HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
	return true;
}
