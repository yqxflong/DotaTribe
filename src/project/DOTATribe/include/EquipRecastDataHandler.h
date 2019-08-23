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
  property_unit_ronly(int,m_equipID,EquipID)											//װ��ID
  property_unit_ronly(int,m_defaultTemplateID,DefaultTemplateID)						//Ĭ����Ʒģ��ID
  property_unit_ronly(std::string,m_defaultName,DefaultName)							//Ĭ����Ʒ����
  property_unit_ronly(int,m_defaultIconID,DefaultIconID)								//Ĭ����ƷICONID
  property_unit_ronly(int,m_defaultLevel,DefaultLevel)									//Ĭ�ϵȼ�
  property_unit_ronly(IByte,m_defaultQuality,DefaultQuality)							    //Ĭ����ƷƷ��
  property_unit_ronly(std::vector<PRewardItemNode>,m_RewardDataList,RewardDataList)		//����������Ʒ
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