////////////////////////////////////////////////////////////////
//Name:	 HeroSoulDataHandler
//Auchor: 	xiaobo.wu
//Func:	 英雄战魂内存数据管理器
//Maintainer: 	xiaobo.wu
//date:   2014/02/20
////////////////////////////////////////////////////////////////
#include "../include/HeroSoulDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"
 
NeedItemNode::NeedItemNode()
{
	m_nItemType = 0;
	m_nItemNeedCount = 0;
	m_nItemHadCount = 0;
	m_nItemCatogory = 0;
	m_nItemTemplateID = 0;
	m_nItemName = "";
	m_uQuality = 0;
	m_nItemCatogory = 0;
}
NeedItemNode::~NeedItemNode()
{ 
}
  
void  NeedItemNode::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_nItemType);
	packet.read(m_nItemNeedCount);
	packet.read(m_nItemHadCount); 
	if(m_nItemType == 0)
	{
		packet.read(m_nItemCatogory);
		packet.read(m_nItemTemplateID);
		NFC_ParsePacketString(packet,m_nItemName);
		packet.read(m_uQuality);
		packet.read(m_nItemIcon);
	} 
}

//////////////////////////////////////////////////////////////////////////

HeroSoulInfoData::HeroSoulInfoData()
{
	init();
}

HeroSoulInfoData::~HeroSoulInfoData()
{
	destroy();
}
 
void  HeroSoulInfoData::init()
{
	m_nHeroID = 0;
	m_bWinHeroSoul = false;
	m_nRoBotHeroID = 0;
	m_nAdviseChallengeLevel = 0;
	m_nLeftChallengeCount = 0;
	m_nConsumeType = 0;
	m_nConsumeCost = 0;
	m_nHeroIconID = 0;
	m_nHeroSouleLevel = 0;
	m_nHeroSouleMaxLevel = 0;
	m_nHeroTalentName = "";
	m_nHeroAtributeName = "";
	m_nCanActiveSoul = 0;
	m_vNeetItemVector.clear();
}
void  HeroSoulInfoData::destroy()
{
	size_t vectorSize = m_vNeetItemVector.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorSize)
		NeedItemNode * pNeedItemNode = m_vNeetItemVector.at(index);
	if(pNeedItemNode)
		delete pNeedItemNode;
	COMMON_END_ARRAY
		m_vNeetItemVector.clear();
}

void HeroSoulInfoData::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_nHeroID);
	IByte  hadWinHeroSoul = 0;
	packet.read(hadWinHeroSoul);
	if(hadWinHeroSoul == 0)
	{
		m_bWinHeroSoul = false; 
		packet.read(m_nRoBotHeroID);
		packet.read(m_nAdviseChallengeLevel);
		packet.read(m_nLeftChallengeCount);
		packet.read(m_nConsumeType);
		packet.read(m_nConsumeCost);
	}
	else
	{
		m_bWinHeroSoul = true;
		packet.read(m_nHeroIconID);
		packet.read(m_nHeroSouleLevel);
		packet.read(m_nHeroSouleMaxLevel);
		NFC_ParsePacketString(packet,m_nHeroTalentName);
		NFC_ParsePacketString(packet,m_nHeroAtributeName);  
		packet.read(m_nCanActiveSoul);
		short needItemCount = 0;
		packet.read(needItemCount);
		COMMON_BEIGIN_ARRAY(short,needItemCount)
			NeedItemNode * pNeedItemNode = new NeedItemNode();
			if(pNeedItemNode)
			{
				pNeedItemNode->decodePacket(packet);
				m_vNeetItemVector.push_back(pNeedItemNode);
			}
		COMMON_END_ARRAY
	}  
}
 
void  HeroSoulInfoData::decodeActivePacket(cobra_win::DPacket & packet)
{
	destroy();
	init(); 
	m_bWinHeroSoul = true;
	packet.read(m_nHeroIconID);
	packet.read(m_nHeroSouleLevel);
	packet.read(m_nHeroSouleMaxLevel);
	NFC_ParsePacketString(packet,m_nHeroTalentName);
	NFC_ParsePacketString(packet,m_nHeroAtributeName);  
	packet.read(m_nCanActiveSoul);
	short needItemCount = 0;
	packet.read(needItemCount);
	COMMON_BEIGIN_ARRAY(short,needItemCount)
		NeedItemNode * pNeedItemNode = new NeedItemNode();
	if(pNeedItemNode)
	{
		pNeedItemNode->decodePacket(packet);
		m_vNeetItemVector.push_back(pNeedItemNode);
	}
	COMMON_END_ARRAY 
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
HeroSoulDataHandler::HeroSoulDataHandler()
{
	m_pHeroSoulInfoData = NULL;
	m_pRequestHeroID = 0;
	m_nBackWindowType = 0;
}

HeroSoulDataHandler::~HeroSoulDataHandler()
{ 
	if(m_pHeroSoulInfoData)
	{
		delete m_pHeroSoulInfoData;
		m_pHeroSoulInfoData =NULL;
	}
}

void HeroSoulDataHandler::handlePacket(IPacket* packet)
{ 
}

bool HeroSoulDataHandler::init()
{ 
	return true;
}

void HeroSoulDataHandler::onDestroy()
{ 
}

void  HeroSoulDataHandler::deoceAllPacket(cobra_win::DPacket & packet)
{
	if(m_pHeroSoulInfoData)
	{
		delete m_pHeroSoulInfoData;
		m_pHeroSoulInfoData =NULL;
	}
	m_pHeroSoulInfoData = new HeroSoulInfoData();
	m_pHeroSoulInfoData->decodePacket(packet);
}

void  HeroSoulDataHandler::decodeActivePacket(cobra_win::DPacket & packet)
{
	if(!m_pHeroSoulInfoData)
	{
		m_pHeroSoulInfoData = new HeroSoulInfoData();
	}
	m_pHeroSoulInfoData->decodeActivePacket(packet); 
}