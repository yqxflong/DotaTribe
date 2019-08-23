#include "cocos2d.h"
#include "../include/HeroAdvancedDataHandler.h"
#include "../include/CSHeroAdvancedPacket.h"

IItem::IItem()
{  
	m_nTemplateID=0;
	m_bQualiy=0;
	m_nIconID=0;
	m_nNum=0;
}

IItem::~IItem()
{ 
}
void IItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(m_nTemplateID);
	packet.read(m_bQualiy);
	packet.read(m_nIconID);
	packet.read(m_nNum);
}

//////////////////////////////////////////////////////////////////////////
 
HeroAdvanceSingleItem::HeroAdvanceSingleItem()
{
	m_nHeroUniqueID=0;
	m_bNeddMoneyNum=0;
	m_bItemNum=0;
	m_vItemsVector.clear();
}

HeroAdvanceSingleItem::~HeroAdvanceSingleItem()
{
	size_t itemCount=m_vItemsVector.size();
	COMMON_BEIGIN_ARRAY(size_t,itemCount)
		delete m_vItemsVector.at(index);
	COMMON_END_ARRAY
	m_vItemsVector.clear();
}


void HeroAdvanceSingleItem::decodePacketData(cobra_win::DPacket & packet)
{    
	packet.read(m_nHeroUniqueID);
	packet.read(m_bNeddMoneyNum);
	packet.read(m_bItemNum);
	COMMON_BEIGIN_ARRAY(IByte,m_bItemNum)
		IItem * pItemData=new IItem();
		pItemData->decodePacketData(packet);
		m_vItemsVector.push_back(pItemData);
	COMMON_END_ARRAY
}

//////////////////////////////////////////////////////////////////////////


HeroAdvancedData::HeroAdvancedData(void)
{
	m_vAdvancedVector.clear();
}
 
HeroAdvancedData::~HeroAdvancedData()
{
	destroyMemData();
}
 
void  HeroAdvancedData::destroyMemData()
{   
	size_t advanceCount=m_vAdvancedVector.size();
	COMMON_BEIGIN_ARRAY(size_t,advanceCount)
		delete m_vAdvancedVector.at(index);
	COMMON_END_ARRAY
	m_vAdvancedVector.clear();
}

void  HeroAdvancedData::decodePacketData(cobra_win::DPacket & packet)
{   
	destroyMemData();
	IByte heroCount=0;
	packet.read(heroCount);
	COMMON_BEIGIN_ARRAY(IByte,heroCount)
		HeroAdvanceSingleItem * pHeroAdvanceSingleItem=new HeroAdvanceSingleItem();
		pHeroAdvanceSingleItem->decodePacketData(packet);
		m_vAdvancedVector.push_back(pHeroAdvanceSingleItem);
	COMMON_END_ARRAY
}

//////////////////////////////////////////////////////////////////////////

 
HeroAdvancedDataHandler::HeroAdvancedDataHandler()
{
	m_pHeroAdvanceData=NULL;
}

HeroAdvancedDataHandler::~HeroAdvancedDataHandler()
{
	if(m_pHeroAdvanceData)
	{
		delete m_pHeroAdvanceData;
		m_pHeroAdvanceData=NULL;
	}
}
 
void HeroAdvancedDataHandler::onDestroy()
{ 
}

bool HeroAdvancedDataHandler::init()
{
	return true;
}



void  HeroAdvancedDataHandler::decodePacketData(cobra_win::DPacket & packet)
{
	if(m_pHeroAdvanceData==NULL)
	{   
		m_pHeroAdvanceData=new HeroAdvancedData();
	}
	m_pHeroAdvanceData->decodePacketData(packet);
}

void  HeroAdvancedDataHandler::sendHeroAdvancedNeedRequest(int heroGroupID)
{
	CSHeroAdvancedPacket  heroAdvancePacket(heroGroupID);
	heroAdvancePacket.Send();
}


void  HeroAdvancedDataHandler::destroyMemData()
{
	if(m_pHeroAdvanceData)
	m_pHeroAdvanceData->destroyMemData();
}

void  HeroAdvancedDataHandler::sendHeroAdvancedVerify(int heroGroupID)
{ 
	CSHeroAdvanceVerifyPacket  heroAdvanceVerfiyPacket(heroGroupID);
	heroAdvanceVerfiyPacket.Send();
}