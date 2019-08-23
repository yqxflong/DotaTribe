////////////////////////////////////////////////////////////////
//Name:	 HeroSoulDataHandler
//Auchor: 	xiaobo.wu
//Func:	 英雄战魂内存数据管理器
//Maintainer: 	xiaobo.wu
//date:   2014/02/20
////////////////////////////////////////////////////////////////

#ifndef   _DOTATRIBE_HEROSOUL_DATAHANDLER_H
#define   _DOTATRIBE_HEROSOUL_DATAHANDLER_H
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h"
#include <vector>
#include <string>

class  NeedItemNode
{
	default_construct_destroy(NeedItemNode)
	property_unit_rw(IByte,m_nItemType,ItemType)
	property_unit_rw(int,m_nItemNeedCount,ItemNeedCount)
	property_unit_rw(int,m_nItemHadCount,ItemHadCount) 
	property_unit_rw(IByte,m_nItemCatogory,ItemCatogory)
	property_unit_rw(int,m_nItemTemplateID,ItemTemplateID)
	property_unit_rw(std::string,m_nItemName,ItemName)
	property_unit_rw(IByte,m_uQuality,ItemQuality)
	property_unit_rw(int,m_nItemIcon,ItemIcon)
public:
	void  decodePacket(cobra_win::DPacket & packet);
};

class  HeroSoulInfoData
{ 
   default_construct_destroy(HeroSoulInfoData)
   property_unit_rw(int,m_nHeroID,HeroUID)
   property_unit_rw(bool,m_bWinHeroSoul,IsWinHeroSoul)
   property_unit_rw(int,m_nRoBotHeroID,RoBotHeroID)
   property_unit_rw(short,m_nAdviseChallengeLevel,AdviseChallenegeLevel)
   property_unit_rw(int,m_nLeftChallengeCount,LeftChallenegtCount)

   property_unit_rw(IByte,m_nConsumeType,ConsumeType)
   property_unit_rw(short,m_nConsumeCost,ConsumeCost)   
   //////////////////////////////////////////////////////////////////////////
   property_unit_rw(int ,m_nHeroIconID,HeroIconID)
   property_unit_rw(IByte ,m_nHeroSouleLevel,HeroSoulLevel) 
   property_unit_rw(IByte ,m_nHeroSouleMaxLevel,HeroSoulMaxLevel)
   property_unit_rw(std::string ,m_nHeroTalentName,HeroTalentName)
   property_unit_rw(std::string ,m_nHeroAtributeName,HeroAtributeName)
   property_unit_rw(IByte,m_nCanActiveSoul,CanActiveHeroSoul) 
   property_unit_rwc(std::vector<NeedItemNode *>,m_vNeetItemVector,NeetItemVector)  
public:
   void  decodePacket(cobra_win::DPacket & packet); 
   void  decodeActivePacket(cobra_win::DPacket & packet);
private:
   void  init();
   void  destroy();
};
 
 
class HeroSoulDataHandler : public IDataHandler,public cobra_win::Singleton2<HeroSoulDataHandler>
{
   default_construct_vdestroy(HeroSoulDataHandler)
   property_unit_ronly(HeroSoulInfoData *,m_pHeroSoulInfoData,HeroSoleInfoData)
   property_unit_rw(int,m_pRequestHeroID,RequestHeroID)
   property_unit_rw(int,m_nBackWindowType,BackWindowType)
   property_unit_rw(int, m_nBackTab, BackTab)

public: 
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	void  deoceAllPacket(cobra_win::DPacket & packet);
	void  decodeActivePacket(cobra_win::DPacket & packet);
};
#endif