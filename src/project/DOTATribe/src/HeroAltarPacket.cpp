//Name:HeroAltarPacket
//Function: 英雄献祭相关协议
//Author:lvyunlong
//Date:20131202

#include <cocos2d.h>
#include "../include/HeroAltarPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include  "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/NFControlsManager.h"
#include <map>
#include <vector>
using namespace std;

/************************************************************************/
/* 请求充值列表和返回	                                                    */
/************************************************************************/
CSHeroTotemInfoPacket::CSHeroTotemInfoPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSHeroTotemInfoPacket::~CSHeroTotemInfoPacket()
{

}

unsigned  int  CSHeroTotemInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROTOTEMINFO_;
}

unsigned  int  CSHeroTotemInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) +  + sizeof(m_len);
}

void  CSHeroTotemInfoPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}


unsigned  int  SCHeroTotemInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTOTEMINFO_RESULT_;
}

unsigned  int  SCHeroTotemInfoPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeroTotemInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}

void SCHeroTotemInfoPacket::_readInfo(cobra_win::DPacket &packet)
{
	HEROALTARCONTROLDATAHANDLER->ClearTotemInfoList();
	unsigned char size = 0;
	packet>>size;
	
	for (unsigned char i=0;i<size;i++)
	{
		TotemData* temp = new TotemData();
		temp->decodeTemplatePacketData(packet);
		HEROALTARCONTROLDATAHANDLER->m_TotemDataList.push_back(temp);
	}
}

unsigned  int  SCHeroTotemInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROTOTEMINFO_RESULT_;
}

bool  SCHeroTotemInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroTotemInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ALTARWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 请求献祭信息和服务器返回献祭信息										*/
/************************************************************************/

CSHeroAltarInfoPacket::CSHeroAltarInfoPacket()
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSHeroAltarInfoPacket::~CSHeroAltarInfoPacket()
{

}

unsigned  int  CSHeroAltarInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HEROALTARINFO_;
}

unsigned  int  CSHeroAltarInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSHeroAltarInfoPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCHeroAltarInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROALATRINFO_RESULT_;
}

unsigned  int  SCHeroAltarInfoPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeroAltarInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCHeroAltarInfoPacket::_readInfo(cobra_win::DPacket &packet)
{
	HEROALTARCONTROLDATAHANDLER->ClearAltarInfoList();
	unsigned char size = 0;
	packet>>size;
	std::map<int ,AltarData*> tempmap;
	for (unsigned char i=0;i<size;i++)
	{
		AltarData* temp = new AltarData();
		temp->decodeTemplatePacketData(packet);
		tempmap.insert(std::map<int ,AltarData*>::value_type(temp->expadd_,temp));
	}
	std::map<int ,AltarData*>::iterator posbegin = tempmap.begin();
	std::map<int ,AltarData*>::iterator posend = tempmap.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		HEROALTARCONTROLDATAHANDLER->m_AltarDataList.push_back((*posbegin).second);
	}
}

unsigned  int  SCHeroAltarInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROALATRINFO_RESULT_;
}

bool  SCHeroAltarInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroAltarInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEDEBRIS_ALTARWINDOW_);
	return true;
}

/************************************************************************/
/* 客户端发送献祭碎片信息和服务器返回碎片献祭结果信息						*/
/************************************************************************/

CSHeroDebrisAltarPacket::CSHeroDebrisAltarPacket(unsigned char type,unsigned char count)
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_type = type;
	m_count = count;

	m_len = GetPacketLength();
}

CSHeroDebrisAltarPacket::~CSHeroDebrisAltarPacket()
{
	
}

unsigned  int  CSHeroDebrisAltarPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_HERODEBRISALTAR_;
}

unsigned  int  CSHeroDebrisAltarPacket::GetPacketLength()
{
	unsigned int leng = 0;

	std::vector<DebrisData*>::iterator  posbegin = HEROALTARCONTROLDATAHANDLER->m_ClickDebriList.begin();
	std::vector<DebrisData*>::iterator  posend = HEROALTARCONTROLDATAHANDLER->m_ClickDebriList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			if ((*posbegin)->count_ != 0)
			{
				leng += sizeof((*posbegin)->itemId_);
				leng += sizeof((*posbegin)->count_);
			}
		}
	}

	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_type)+ sizeof(m_count) + leng;
}

void  CSHeroDebrisAltarPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_type);
	pNode->push(m_count);

	std::vector<DebrisData*>::iterator  posbegin = HEROALTARCONTROLDATAHANDLER->m_ClickDebriList.begin();
	std::vector<DebrisData*>::iterator  posend = HEROALTARCONTROLDATAHANDLER->m_ClickDebriList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			if ((*posbegin)->count_ != 0)
			{
				pNode->push((*posbegin)->itemId_);
				pNode->push((*posbegin)->count_);
			}
		}
	}
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCHeroDebrisAltarPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERODEBRISALTAR_RESULT_;
}

unsigned  int  SCHeroDebrisAltarPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCHeroDebrisAltarPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCHeroDebrisAltarPacket::_readInfo(cobra_win::DPacket &packet)
{
	unsigned char type = 0;
	packet>>type;

	TotemData* data = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[type];
	if (data == NULL)
		return;
	packet>>data->level_;
	packet>>data->exp_;
	packet>>data->maxExp_;
	packet>>data->addvalue_;
	packet>>data->nextValue_;
}

unsigned  int  SCHeroDebrisAltarPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HERODEBRISALTAR_RESULT_;
}

bool  SCHeroDebrisAltarPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroDebrisAltarPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ALTARWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 请求献祭 每级最大经验的表/player/xianji.xlsx<br>						*/
/************************************************************************/

CSAltarCheckInfoTablePacket::CSAltarCheckInfoTablePacket()
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSAltarCheckInfoTablePacket::~CSAltarCheckInfoTablePacket()
{

}

unsigned  int  CSAltarCheckInfoTablePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ALTARCHECKINFOTABLE_;
}

unsigned  int  CSAltarCheckInfoTablePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSAltarCheckInfoTablePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCAltarCheckInfoTablePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ALTARCHECKINFOTABLE_RESULT_;
}

unsigned  int  SCAltarCheckInfoTablePacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCAltarCheckInfoTablePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCAltarCheckInfoTablePacket::_readInfo(cobra_win::DPacket &packet)
{
	unsigned short size = 0;
	packet>>size;
	for (unsigned char i=0;i<size;i++)
	{
		AltarCheckData* temp = new AltarCheckData();
		temp->decodeTemplatePacketData(packet);
		HEROALTARCONTROLDATAHANDLER->m_pCheckAltarTable.insert(std::map<int ,AltarCheckData*>::value_type(temp->level_,temp));
	}
}

unsigned  int  SCAltarCheckInfoTablePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ALTARCHECKINFOTABLE_RESULT_;
}

bool  SCAltarCheckInfoTablePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAltarCheckInfoTablePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI

	return true;
}