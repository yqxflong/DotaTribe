#ifndef _DOTATRIBE_EQUIPRECASTDATAHANDLER_H
#define _DOTATRIBE_EQUIPRECASTDATAHANDLER_H

#include <include/common/Singleton.h>
#include <include/mem/DPacket.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h" 
#include "../include/CommonDataDef.h" 
 
#include <vector>
#include <string>

class EquipRecastDataInfo
{
  default_construct_destroy(EquipRecastDataInfo)
  property_unit_ronly(int,m_equipID,EquipID)											//装备ID
  property_unit_ronly(int,m_defaultTemplateID,DefaultTemplateID)						//默认物品模板ID
  property_unit_ronly(std::string,m_defaultName,DefaultName)							//默认物品名称
  property_unit_ronly(int,m_defaultIconID,DefaultIconID)								//默认物品ICONID
  property_unit_ronly(int,m_defaultLevel,DefaultLevel)									//默认等级
  property_unit_ronly(IByte,m_defaultQuality,DefaultQuality)							    //默认物品品质
  property_unit_ronly(std::vector<PRewardItemNode>,m_RewardDataList,RewardDataList)		//其他奖励物品
public:
  void decodePacket(cobra_win::DPacket & packet);
private:
  void destroyData();
};

 
class EquipRecastDataHandler : public IDataHandler, public cobra_win::Singleton2<EquipRecastDataHandler>
{ 
	default_construct_vdestroy(EquipRecastDataHandler)
	property_unit_ronly(EquipRecastDataInfo*,m_pEquipRecastDataInfo,EquipRecastDataInfos)
public:
	virtual void onDestroy();
	virtual bool init();
public:
	void  decodePacket(cobra_win::DPacket & packet); 
	void  destroyData();
};

#endif