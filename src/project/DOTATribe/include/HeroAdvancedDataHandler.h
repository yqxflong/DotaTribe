#ifndef	_DOTATRIBE_HeroAdvancedDataHandler_H_
#define _DOTATRIBE_HeroAdvancedDataHandler_H_
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  �����ڴ�����
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
	����Ӣ�۽�����������
	*/
	void  sendHeroAdvancedNeedRequest(int heroGroupID);
	
	/*
	�������ݰ�
	*/
	void  decodePacketData(cobra_win::DPacket & packet);

	/*
	�����ڴ�����
	*/
	void  destroyMemData();
	 
    /*
	���ͽ���������֤����
	*/
	void  sendHeroAdvancedVerify(int heroGroupID);
};

#define HEROADVANCEDATAHANDLER	 (HeroAdvancedDataHandler::get_instance2())

#endif
