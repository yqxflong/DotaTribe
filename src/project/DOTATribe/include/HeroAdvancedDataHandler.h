#ifndef	_DOTATRIBE_HeroAdvancedDataHandler_H_
#define _DOTATRIBE_HeroAdvancedDataHandler_H_
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  进阶内存数据
//date:   2013/12/07
///////////////////////////////////////////////// 

#include <include/common/Singleton.h>
#include <include/mem/DPacket.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h"
 
class  IItem
{
	default_construct_destroy(IItem)
	property_unit_ronly(int,m_nTemplateID,TemplateID)
	property_unit_ronly(IByte,m_bQualiy,Qualiy)
	property_unit_ronly(int,m_nIconID,IconID)
	property_unit_ronly(int,m_nNum,Num)
public:
	void decodePacketData(cobra_win::DPacket & packet);
	 
};

class  HeroAdvanceSingleItem
{
	default_construct_destroy(HeroAdvanceSingleItem)
	property_unit_ronly(int,m_nHeroUniqueID,HeroUniqueID)
	property_unit_ronly(int,m_bNeddMoneyNum,NeedMoneyNum)
	property_unit_ronly(IByte,m_bItemNum,ItemNum)
	property_unit_ronly(std::vector<IItem *>,m_vItemsVector,ItemsVector)
public:
 void  decodePacketData(cobra_win::DPacket & packet);
};

class HeroAdvancedData
{
	default_construct_destroy(HeroAdvancedData)
	property_unit_ronly(std::vector<HeroAdvanceSingleItem *>,m_vAdvancedVector,AdvancedVector)
public:
  void  decodePacketData(cobra_win::DPacket & packet);
  void  destroyMemData();
};


class  HeroAdvancedDataHandler : public IDataHandler, public cobra_win::Singleton2<HeroAdvancedDataHandler>
{
	default_construct_vdestroy(HeroAdvancedDataHandler)
	property_unit_ronly(HeroAdvancedData *,m_pHeroAdvanceData,HeroAdvancedData)
protected:
	virtual void handlePacket(IPacket* packet){};
	virtual void onDestroy();
	virtual bool init();
public:
	/*
	发送英雄进阶所需请求
	*/
	void  sendHeroAdvancedNeedRequest(int heroGroupID);
	
	/*
	解析数据包
	*/
	void  decodePacketData(cobra_win::DPacket & packet);

	/*
	销毁内存数据
	*/
	void  destroyMemData();
	 
    /*
	发送进阶数据验证请求
	*/
	void  sendHeroAdvancedVerify(int heroGroupID);
};

#define HEROADVANCEDATAHANDLER	 (HeroAdvancedDataHandler::get_instance2())

#endif
