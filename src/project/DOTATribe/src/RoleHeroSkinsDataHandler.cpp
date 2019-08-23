//Name：RoleHeroSkinsDataHandler
//Function：英雄数据（内存）
//Author：Johny

#include  "../include/RoleHeroSkinsDataHandler.h"
#include  "../include/HeroIllustratedDataHandler.h"
#include "../include/NFToolController.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/RoleSkillsDataHandler.h"
#include "../include/RoleSoulsDataHandler.h"

IHeroSkinItem::IHeroSkinItem()
{
	m_nHeroUniqueID=0;
	m_nHeroGroupID=0;
	m_bHeroShapeLevel=0;
	m_sHeroName=""; 
	m_bHeroType=0;
	m_bHeroQualiy=0;
	m_nHeroIconID=0;
	m_nHeroShapeID=0;
	m_bIsActive=false;
	m_nHeroPower=0;
	m_nHeroQuick=0;
	m_nHeroInteligence=0;
	m_bHeroAttackGrow=0;
	m_bHeroSpeedGrow=0;
	m_bHeroHpGrow=0;
	m_bHeroMpGrow=0;
	m_nHeroBufferID=0;
	m_bHeroBufferLevel=0;
	m_nHeroBufferIconID=0;
	m_sHeroBufferName="";
	m_sHeroBufferDesc="";
	m_pAttManager=new Attribute();
	m_pEquipManager=new RoleEquipDataHandler();
	m_pSkillManager=new RoleSkillsDataHandler();
	m_pSoulsEquipManager = new IRoleSoulsEquipInfo();


	m_bIsNeedUpdate=true;
}
IHeroSkinItem::~IHeroSkinItem()
{  
	CC_SAFE_DELETE(m_pAttManager);
	CC_SAFE_DELETE(m_pEquipManager);
	CC_SAFE_DELETE(m_pSkillManager);
}

void IHeroSkinItem::decodePacketBaseData(cobra_win::DPacket & packet,bool isPlayerHero/* =false */)
{
	packet.read(m_nHeroUniqueID);
	packet.read(m_nHeroGroupID);
	packet.read(m_bHeroShapeLevel);
	NFC_ParsePacketString(packet,m_sHeroName);
    packet.read(m_bHeroType);
	packet.read(m_bHeroQualiy);
	packet.read(m_nHeroIconID);
	packet.read(m_nHeroShapeID);
	IByte existSoul = 0;
	packet.read(existSoul);
	m_bExistHeroSoul = existSoul > 0 ? true:false;
	packet.read(m_nHeroSoulChallengeLevel);  
	if(isPlayerHero)
	{
		m_bIsNeedUpdate=false;
		m_bIsActive=true;
		//@解析-英雄模板
		decodePacket_HeroTemplate(packet);
		//@解析-英雄属性
		decodePacket_HeroProp(packet);
		//@解析-装备
		decodePacket_Equip(packet);
		//@解析-技能
		decodePacket_skill(packet);
		//@解析-战魂
		decodePacket_soul(packet);
	}
	else
	{
		IByte bActive=0;
		packet.read(bActive);
		m_bIsActive=bActive>0 ? true:false;
		m_bIsNeedUpdate=true;
	}
}

//@解析-英雄模板
void IHeroSkinItem::decodePacket_HeroTemplate(cobra_win::DPacket & packet)
{ 
	packet.read(m_nHeroPower);
	packet.read(m_nHeroQuick);
	packet.read(m_nHeroInteligence);

	packet.read(m_bHeroAttackGrow);
	packet.read(m_bHeroHpGrow);
	packet.read(m_bHeroSpeedGrow);
	packet.read(m_bHeroMpGrow);

	packet.read(m_nHeroBufferID);
	if(m_nHeroBufferID>0)
	{
		packet.read(m_bHeroBufferLevel);
		packet.read(m_nHeroBufferIconID);
		NFC_ParsePacketString(packet,m_sHeroBufferName);
		NFC_ParsePacketString(packet,m_sHeroBufferDesc);
	}
	packet.read(m_nHeroStrength);
}

//@解析-英雄属性
void IHeroSkinItem::decodePacket_HeroProp(cobra_win::DPacket & packet){
	IByte atributeCount=0;
	packet.read(atributeCount);
	m_pAttManager->mapPropertyList_.clear();
	IByte attrType=0;
	int   attrValue=0;
	COMMON_BEIGIN_ARRAY(IByte,atributeCount)
		packet.read(attrType);
		packet.read(attrValue);
		m_pAttManager->mapPropertyList_.insert(std::map<int,int>::value_type(attrType,attrValue));
	COMMON_END_ARRAY
}
//@解析-装备
void IHeroSkinItem::decodePacket_Equip(cobra_win::DPacket & packet){
	m_pEquipManager->decodePacketData(packet);
}
//@解析-技能
void IHeroSkinItem::decodePacket_skill(cobra_win::DPacket & packet){
	m_pSkillManager->decodeRoleSkillsPacket(packet);
}
//@解析-战魂
void IHeroSkinItem::decodePacket_soul(cobra_win::DPacket & packet)
{
	m_pSoulsEquipManager->decodePacket(packet);
}

void IHeroSkinItem::decodePacketSynInfo(cobra_win::DPacket & packet)
{ 
	packet.read(m_nHeroGroupID);
	packet.read(m_bHeroShapeLevel);
	NFC_ParsePacketString(packet,m_sHeroName);
	packet.read(m_bHeroType);
	packet.read(m_bHeroQualiy);
	packet.read(m_nHeroIconID);
	packet.read(m_nHeroShapeID);
	IByte existSoul = 0;
	packet.read(existSoul);
	m_bExistHeroSoul = existSoul > 0 ? true:false;
	packet.read(m_nHeroSoulChallengeLevel);  
	packet.read(m_nHeroPower);
	packet.read(m_nHeroQuick);
	packet.read(m_nHeroInteligence);
	packet.read(m_bHeroAttackGrow); 
	packet.read(m_bHeroHpGrow);
	packet.read(m_bHeroSpeedGrow);
	packet.read(m_bHeroMpGrow);
	packet.read(m_nHeroBufferID);
	if(m_nHeroBufferID>0)
	{
		packet.read(m_bHeroBufferLevel);
		packet.read(m_nHeroBufferIconID);
		NFC_ParsePacketString(packet,m_sHeroBufferName);
		NFC_ParsePacketString(packet,m_sHeroBufferDesc);
	}
	packet.read(m_nHeroStrength);
	m_bIsNeedUpdate=false;
	
}

IHeroSoulItem* IHeroSkinItem::getBuffIdByHeroItem(int buffid)
{
	std::vector<IHeroSoulItem *>::iterator it = m_pSoulsEquipManager->getHeroSoulEquipList().begin();
	std::vector<IHeroSoulItem *>::iterator it_end = m_pSoulsEquipManager->getHeroSoulEquipList().end();
	for (it;it != it_end;it++)
	{
		if ((*it)->getHeroSoulBufferID() == buffid)
		{
			return *it;
		}
	}
	return NULL;
}

void IHeroSkinItem::resetExpandInfo()
{
	m_nHeroPower=0;
	m_nHeroQuick=0;
	m_nHeroInteligence=0;

	m_bHeroAttackGrow=0;
	m_bHeroSpeedGrow=0;
	m_bHeroHpGrow=0;
	m_bHeroMpGrow=0;
	  
	m_nHeroBufferID=0;
	m_bHeroBufferLevel=0;
	m_nHeroBufferIconID=0;
	m_sHeroBufferName="";
	m_sHeroBufferDesc="";

	m_bIsNeedUpdate=true;
}

 

RoleHeroSkinsDataHandler::RoleHeroSkinsDataHandler()
{
	m_vecHeroList.clear();
	m_mHeroSkinsDB.clear();

}
RoleHeroSkinsDataHandler::~RoleHeroSkinsDataHandler()
{

}

size_t RoleHeroSkinsDataHandler::TeamHeroCount(){
	return m_vecHeroList.size();
}
bool RoleHeroSkinsDataHandler::HasTeamHero(int idx){
	return idx<m_vecHeroList.size();
}


IHeroSkinItem *  RoleHeroSkinsDataHandler::GetCurHeroSkinItem(int pos)
{
	if (pos<m_vecHeroList.size())
		return  m_vecHeroList[pos];

	return NULL;
}
 
   
void  RoleHeroSkinsDataHandler::ChangeHeroByPos(IHeroSkinItem * pHeroSkinItem,int pos)
{
	if(pHeroSkinItem&&m_vecHeroList[pos]->getHeroUniqueID()!=pHeroSkinItem->getHeroUniqueID())
	{
		m_vecHeroList[pos]=pHeroSkinItem;
	}
}

//@查看英雄是否已在队伍中
bool RoleHeroSkinsDataHandler::IsHeroInTeam(int uniqueID){
	for (size_t pos = 0;pos<m_vecHeroList.size();pos++)
	{
		if(m_vecHeroList[pos]->getHeroUniqueID() == uniqueID)
			return true;
	}

	return false;
}



IHeroSkinItem *  RoleHeroSkinsDataHandler::GetHeroSkinItemByID(int heroiUniqueID)
{
	std::map<int,IHeroSkinItem *>::iterator hero_iter=m_mHeroSkinsDB.find(heroiUniqueID);
	if(hero_iter!=m_mHeroSkinsDB.end())
	{
		return hero_iter->second;
	}
	return NULL;
}
/*
获取英雄外套总数
*/
size_t			 RoleHeroSkinsDataHandler::GetHeroSkinsNum()
{
	return  m_mHeroSkinsDB.size();
}

size_t            RoleHeroSkinsDataHandler::GetActiveHeroSkinsNum()
{
	size_t activeNum=0;
	std::map<int,IHeroSkinItem *>::iterator hero_iter=m_mHeroSkinsDB.begin();
	while(hero_iter!=m_mHeroSkinsDB.end())
	{
		if(hero_iter->second->getIsActived())
		{
			activeNum++;
		}
		hero_iter++;
	} 
	return activeNum;
}

//@解析一个英雄包
void RoleHeroSkinsDataHandler::decodePacket_One_HeroSkinsData(cobra_win::DPacket & packet,bool isPlayerHeroSkin,unsigned int idx){
	IHeroSkinItem* pHeroSkinItem=new IHeroSkinItem;
	pHeroSkinItem->decodePacketBaseData(packet,isPlayerHeroSkin);
	if(isPlayerHeroSkin)
	{
		m_vecHeroList.push_back(pHeroSkinItem);
	}else{
		std::map<int,IHeroSkinItem *>::iterator hero_iter=m_mHeroSkinsDB.find(pHeroSkinItem->getHeroUniqueID());
		if(hero_iter==m_mHeroSkinsDB.end())
		{
			m_mHeroSkinsDB.insert(std::map<int,IHeroSkinItem *>::value_type(pHeroSkinItem->getHeroUniqueID(),pHeroSkinItem));
		} 
	}
}

//@解包-队伍中的英雄
void RoleHeroSkinsDataHandler::decodePacket_TeamHero(cobra_win::DPacket & packet)
{ 
	unsigned char count=0;
	packet>>count;
	_clearTeamHero();

	for (unsigned i=0;i<count;i++)
	{
		decodePacket_One_HeroSkinsData(packet,true,i);
	}
}

//@解包-英雄库
void RoleHeroSkinsDataHandler::decodePacket_HeroDB(cobra_win::DPacket & packet){
	UShort otherHeroSkinsCount=0;
	packet.read(otherHeroSkinsCount);
	COMMON_BEIGIN_ARRAY(UShort,otherHeroSkinsCount)
		decodePacket_One_HeroSkinsData(packet,false,0);
	COMMON_END_ARRAY
		ROLEHEROSKINSDATAHANDLER->parseHeroSkinsDBCompleteCall();
}

//@解析英雄库后，通知界面刷新
void   RoleHeroSkinsDataHandler::parseHeroSkinsDBCompleteCall()
{
	//重组英雄图鉴数据
	HEROILLUSTRATEDDATAHANDLER->ReInitData();
	//解析英雄数据库完成
	std::map<int,IHeroSkinItem *>::iterator hero_iter=m_mHeroSkinsDB.begin();
	while(hero_iter!=m_mHeroSkinsDB.end())
	{ 
	   HEROILLUSTRATEDDATAHANDLER->getHeroCellListFactory()->AddChild(hero_iter->second);
	   ++hero_iter;
	} 
	HEROILLUSTRATEDDATAHANDLER->getHeroCellListFactory()->UpdateAndSort();
}



void    RoleHeroSkinsDataHandler::ResetHeroExpandInfo()
{ 
	if(m_vecHeroList.size()>0)
	{
		std::map<int,IHeroSkinItem *>::iterator  hero_iter=m_mHeroSkinsDB.begin();
		while(hero_iter!=m_mHeroSkinsDB.end())
		{
			for (size_t i=0;i<m_vecHeroList.size();i++)
			{
				if(hero_iter->second->getHeroUniqueID()!=m_vecHeroList[i]->getHeroUniqueID())
				{
					hero_iter->second->resetExpandInfo();
				}
			}
			++hero_iter;
		}
	}
}

bool	RoleHeroSkinsDataHandler::JudgeHeroAdvancedEnable(IHeroSkinItem * pHeroSkinItem)
{    
	 std::map<int,IHeroSkinItem *>::iterator  hero_iter=m_mHeroSkinsDB.begin();
	 bool isSecondExsitAndUnActive=false;
	 bool isThridExsitAndUnActive=false;
	 while(hero_iter!=m_mHeroSkinsDB.end())
	 {  
		 if(hero_iter->second->getHeroGroupID()==pHeroSkinItem->getHeroGroupID())
		 { 
			 HERO_ILLUSTRATED_ADVANCED_MAP.insert(std::map<int,IHeroSkinItem *>::value_type(hero_iter->second->getHeroShapeLevel(),hero_iter->second));
			 if(hero_iter->second->getHeroShapeLevel()==(pHeroSkinItem->getHeroShapeLevel()+1))
			 { 
				 isSecondExsitAndUnActive=!hero_iter->second->getIsActived();
			 }
			 if(hero_iter->second->getHeroShapeLevel()==(pHeroSkinItem->getHeroShapeLevel()+2))
			 { 
				 isThridExsitAndUnActive=!hero_iter->second->getIsActived();
			 }
		 } 
		 ++hero_iter;
	 } 
	 if(isSecondExsitAndUnActive||isThridExsitAndUnActive)
	 {
		 return true;
	 }
	 else
	 {
		 HERO_ILLUSTRATED_ADVANCED_MAP.clear();
		 return false;
	 }
}

void RoleHeroSkinsDataHandler::SetHeroVector(std::vector<IHeroSkinItem *> herolist)
{
	m_vecHeroList.swap(herolist);
}

std::vector<IHeroSkinItem *>& RoleHeroSkinsDataHandler::GetHeroVector()
{
	return m_vecHeroList;
}

void RoleHeroSkinsDataHandler::handlePacket(IPacket* packet) 
{
}
void RoleHeroSkinsDataHandler::onDestroy()
{
	_clearHeroDB();
	_clearTeamHero();
}
bool RoleHeroSkinsDataHandler::init()
{
	IHeroSkinItem * pHeroSkinItem = new IHeroSkinItem;
	if (pHeroSkinItem != NULL)
	{
		if (m_vecHeroList.size() == 0)
		{
			m_vecHeroList.push_back(pHeroSkinItem);
		}
	}
	return true;
}

void RoleHeroSkinsDataHandler::_clearHeroDB(){
	std::map<int,IHeroSkinItem *>::iterator it=m_mHeroSkinsDB.begin();
	for (;it!=m_mHeroSkinsDB.end();it++)
	{
		if (it->second!=NULL)
		{
			delete it->second;
		}
	}
	m_mHeroSkinsDB.clear();
}

void RoleHeroSkinsDataHandler::_clearTeamHero(){

	std::vector<IHeroSkinItem *>::iterator it = m_vecHeroList.begin();
	std::vector<IHeroSkinItem *>::iterator it_end = m_vecHeroList.end();
	for (it;it != it_end;it++)
	{
		CC_SAFE_DELETE(*it);
	}
	m_vecHeroList.clear();
}
