//Name： RoleSkillsDataHandler
//Function：管理英雄的技能
//Author：Johny

#include    "../include/RoleSkillsDataHandler.h"
#include    "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"

void skillItem_tag::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(skillID);
	packet.read(skillIconID);
	packet.read(skillType);
	packet.read(mpConsumer);
	packet.read(ispro);  
	 
	NFC_ParsePacketString(packet,skillDescription);
	NFC_ParsePacketString(packet,skillDescription2);
	NFC_ParsePacketString(packet,skillTriggerRate);
	NFC_ParsePacketString(packet,skillTriggerCondition);

}

void skillItem_tag::decodeSyncPacketData(cobra_win::DPacket & packet)
{
	packet.read(skillIconID);
	packet.read(skillType);
	packet.read(mpConsumer);
	packet.read(ispro);  

	NFC_ParsePacketString(packet,skillDescription);
	NFC_ParsePacketString(packet,skillDescription2);
	NFC_ParsePacketString(packet,skillTriggerRate);
	NFC_ParsePacketString(packet,skillTriggerCondition);
}


void skill_desc_node_tag::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(skillType);
	packet.read(mpConsumer);
	packet.read(ispro);  
	NFC_ParsePacketString(packet,description);
	NFC_ParsePacketString(packet,skillDescription2);
	NFC_ParsePacketString(packet,skillTriggerRate);
	NFC_ParsePacketString(packet,skillTriggerCondition); 
}

void skillnotouch_tag::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(index);
	packet.read(level);
	packet.read(skillID); 
	if(skillID > 0)
	{
		packet.read(skillIconID); 
	}
}
void skillnotouch_tag::decodeSyncNotchPacket(cobra_win::DPacket & packet)
{
	packet.read(level);
	packet.read(skillID);
	if(skillID > 0)
	{
		packet.read(skillIconID); 
		if(!pSkillDescNode)
		{
			pSkillDescNode = new Skill_Desc_Node();
		} 
		pSkillDescNode->decodePacketData(packet); 
	} 
}

void skillnotouch_tag::copyFromBgSkillItem(PSkillItem pSkillItem)
{
	skillIconID = pSkillItem->skillIconID;
	if(pSkillDescNode)
	{
		pSkillDescNode->skillType = pSkillItem->skillType;
		pSkillDescNode->mpConsumer = pSkillItem->mpConsumer;
		pSkillDescNode->ispro = pSkillItem->ispro;
		pSkillDescNode->description = pSkillItem->skillDescription;
		pSkillDescNode->skillDescription2 = pSkillItem->skillDescription2;
		pSkillDescNode->skillTriggerRate = pSkillItem->skillTriggerRate;
		pSkillDescNode->skillTriggerCondition = pSkillItem->skillTriggerCondition;
	} 
}
 


RoleSkillsDataHandler::RoleSkillsDataHandler()
{
	 m_bIsUnLockSixthSkill = false;
	 m_nLastActiveSkillID = -1;
	 m_pRoleSkillsData=new RoleSkillsData();
}

RoleSkillsDataHandler::~RoleSkillsDataHandler()
{
	if(m_pRoleSkillsData!=NULL)
	{
		delete m_pRoleSkillsData;
		m_pRoleSkillsData=NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void RoleSkillsDataHandler::onDestroy()
{  
	m_nLastActiveSkillID=-1;
}
 
bool RoleSkillsDataHandler::init()
{ 
	return true;
}

void RoleSkillsDataHandler::handlePacket(IPacket* packet)
{
    //to to
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*
清理技能数据
*/
bool   RoleSkillsDataHandler::ReInitSkillsData()
{ 
	m_nLastActiveSkillID=-1;
	if(m_pRoleSkillsData)
	{ 
		delete m_pRoleSkillsData;
		m_pRoleSkillsData=NULL;
	}
	m_pRoleSkillsData=new RoleSkillsData();
	if(m_pRoleSkillsData)
	return true;

	return false;
}

 
/*
设置激活技能
*/
void RoleSkillsDataHandler::setLastActiveSkillID(int newActiveSkillID)
{
	if(m_nLastActiveSkillID!=-1)
	{
		m_nLastActiveSkillID=newActiveSkillID;
	}
}

/*
重置最新技能
*/
void RoleSkillsDataHandler::resetLastActiveSkillID()
{
	m_nLastActiveSkillID=-1;
}

PSkillItem   RoleSkillsDataHandler::getSkillItemInfoByID(int skillID)
{
	if(m_pRoleSkillsData)
	{
		size_t skillBagCount = m_pRoleSkillsData->skillBagList.size();
		COMMON_BEIGIN_ARRAY(size_t,skillBagCount)
			if(m_pRoleSkillsData->skillBagList.at(index)->skillID == skillID)
			return m_pRoleSkillsData->skillBagList.at(index);
		COMMON_END_ARRAY
	} 
	return NULL;
}

/*
获取当前最新技能图标ID
*/
int RoleSkillsDataHandler::getLastActiveSkillID()
{
	return m_nLastActiveSkillID;
}

/*
解析角色技能信息
*/
void    RoleSkillsDataHandler::decodeRoleSkillsPacket(cobra_win::DPacket & packet)
{
	 destroyMemData();
	 m_pRoleSkillsData = new RoleSkillsData();
	 //背包技能
	 packet.read(m_pRoleSkillsData->skillItemCount);
	 IByte isActivite = 0;
	 COMMON_BEIGIN_ARRAY(short,m_pRoleSkillsData->skillItemCount)
		 PSkillItem  pSkillItem = new SkillItem(); 
		 pSkillItem->decodePacketData(packet);
		 packet.read(isActivite);
		 pSkillItem->isActive = isActivite;
	     m_pRoleSkillsData->skillBagList.push_back(pSkillItem);
	 COMMON_END_ARRAY

    //技能凹槽
	 packet.read(m_pRoleSkillsData->skillNotouchCount);
	 COMMON_BEIGIN_ARRAY(short,m_pRoleSkillsData->skillNotouchCount)
		 PSkillNotoch  pSkillNotch = new SkillNotouch(); 
		 pSkillNotch->decodePacketData(packet); 
	     if(pSkillNotch->skillID > 0)
	     {
			 PSkill_Desc_Node pSkillDescNode=new Skill_Desc_Node(); 
			 pSkillDescNode->decodePacketData(packet);
			 pSkillNotch->pSkillDescNode = pSkillDescNode; 
		 } 
		 m_pRoleSkillsData->skillNotchList.push_back(pSkillNotch);
	 COMMON_END_ARRAY 
}
 
/*
解析同步技能信息
*/
void    RoleSkillsDataHandler::decodeSyncSkillItemPacket(cobra_win::DPacket & packet)
{  
	if(m_pRoleSkillsData)
	{
		short  updateSkillID = 0;
		packet.read(updateSkillID);
		size_t  skillItemCounts = m_pRoleSkillsData->skillBagList.size();
		COMMON_BEIGIN_ARRAY(size_t,skillItemCounts)
			 if(m_pRoleSkillsData->skillBagList.at(index)->skillID == updateSkillID)
			 {
				 m_pRoleSkillsData->skillBagList.at(index)->decodeSyncPacketData(packet);
				 m_pRoleSkillsData->skillBagList.at(index)->isActive = 1;
				 //检测是否需要刷新技能凹槽
				 size_t skillNotchSize = m_pRoleSkillsData->skillNotchList.size();
				 for(size_t notchIndex = 0;notchIndex < skillNotchSize ; notchIndex++)
				 { 
					 if(m_pRoleSkillsData->skillNotchList.at(notchIndex)->skillID == updateSkillID)
					 {   
						 m_pRoleSkillsData->skillNotchList.at(notchIndex)->copyFromBgSkillItem(m_pRoleSkillsData->skillBagList.at(index));
						 break;
					 }
				 }
				 break;
			 }
		COMMON_END_ARRAY
	 }
}
/*
解析同步技能凹槽
*/
void    RoleSkillsDataHandler::decodeSyncSkillNotchItemPacket(cobra_win::DPacket & packet)
{
	if(m_pRoleSkillsData)
	{
		IByte locationIndex = 0;
		packet.read(locationIndex);
		size_t skillNotchCount = m_pRoleSkillsData->skillNotchList.size();
		COMMON_BEIGIN_ARRAY(size_t,skillNotchCount)
			if(m_pRoleSkillsData->skillNotchList.at(index)->index == locationIndex)
			{ 
				m_pRoleSkillsData->skillNotchList.at(index)->decodeSyncNotchPacket(packet); 
				break;
			}
		COMMON_END_ARRAY 
	}
}

/*
同步技能凹槽修改信息
*/
void    RoleSkillsDataHandler::decodeSynSkillNotchsChangePacket(cobra_win::DPacket & packet)
{ 
	 IByte  changeSkillsCount = 0;
	 IByte  locationIndex = 0;
	 packet.read(changeSkillsCount);
	 for(IByte skillIndex = 0 ;skillIndex < changeSkillsCount ; skillIndex++)
	 {
		 packet.read(locationIndex);
		 size_t skillNotchCount = m_pRoleSkillsData->skillNotchList.size();
		 COMMON_BEIGIN_ARRAY(size_t,skillNotchCount)
			 if(m_pRoleSkillsData->skillNotchList.at(index)->index == locationIndex)
			 { 
				 m_pRoleSkillsData->skillNotchList.at(index)->decodeSyncNotchPacket(packet); 
				 break;
 			 }
		 COMMON_END_ARRAY
	 }
}
 
/*
同步角色解锁第六格技能
*/
void    RoleSkillsDataHandler::decodeSynUnLockSixthSkill(cobra_win::DPacket & packet)
{
	IByte  unLockValue = 0;
	packet.read(unLockValue);
	m_bIsUnLockSixthSkill = unLockValue>0 ? true:false;
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_UNLOCK_SKILLNOTCH_SELECTWINDOW_);
}


void    RoleSkillsDataHandler::destroyMemData()
{
	m_nLastActiveSkillID=-1;
	if(m_pRoleSkillsData)
	{
		delete m_pRoleSkillsData;
		m_pRoleSkillsData = NULL;
	}
}


 