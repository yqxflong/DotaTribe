#include "../include/EquipRecastDataHandler.h"


EquipRecastDataInfo::EquipRecastDataInfo()
{ 
	m_equipID = 0;
	m_defaultTemplateID = 0;
	m_defaultName = "";
	m_defaultIconID = 0;
	m_defaultLevel = 0;
	m_defaultQuality = 0;
	m_RewardDataList.clear();
}

EquipRecastDataInfo::~EquipRecastDataInfo()
{ 
	size_t rewardSize = m_RewardDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,rewardSize) 
		delete m_RewardDataList.at(index);
	COMMON_END_ARRAY
	m_RewardDataList.clear();
}

void EquipRecastDataInfo::decodePacket(cobra_win::DPacket & packet)
{
	destroyData();
	packet.read(m_equipID); 
	packet.read(m_defaultTemplateID);
	NFC_ParsePacketString(packet,m_defaultName);
	packet.read(m_defaultIconID);
	packet.read(m_defaultLevel);
	packet.read(m_defaultQuality);
	IByte tempCode = 0;
	packet.read(tempCode);
	COMMON_BEIGIN_ARRAY(IByte,tempCode)
		PRewardItemNode  pRewardItemNode = new RewardItemNode();
		pRewardItemNode->decodePacketData(packet);
		m_RewardDataList.push_back(pRewardItemNode);
	COMMON_END_ARRAY
 }

  void EquipRecastDataInfo::destroyData()
  {
	  m_equipID = 0;
	  m_defaultTemplateID = 0;
	  m_defaultName = "";
	  m_defaultIconID = 0;
	  m_defaultLevel = 0;
	  size_t rewardSize = m_RewardDataList.size();
	  COMMON_BEIGIN_ARRAY(size_t,rewardSize) 
		  delete m_RewardDataList.at(index);
	  COMMON_END_ARRAY
	  m_RewardDataList.clear();
  }

//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
EquipRecastDataHandler::EquipRecastDataHandler()
{ 
	m_pEquipRecastDataInfo = NULL;
}

EquipRecastDataHandler::~EquipRecastDataHandler()
{
	if(m_pEquipRecastDataInfo)
	{
		delete m_pEquipRecastDataInfo;
		m_pEquipRecastDataInfo = NULL;
	}
}

void  EquipRecastDataHandler::decodePacket(cobra_win::DPacket & packet)
{ 
	if(!m_pEquipRecastDataInfo)
	{
		m_pEquipRecastDataInfo = new EquipRecastDataInfo();
	}
	m_pEquipRecastDataInfo->decodePacket(packet);
}
 
 
void  EquipRecastDataHandler::destroyData()
{
	if(m_pEquipRecastDataInfo)
	{
		delete m_pEquipRecastDataInfo;
		m_pEquipRecastDataInfo = NULL;
	}
}

void EquipRecastDataHandler::onDestroy()
{ 
	//todo
}

bool EquipRecastDataHandler::init()
{ 
	return true;
}

