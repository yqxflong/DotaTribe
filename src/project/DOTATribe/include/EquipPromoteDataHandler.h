#ifndef _DOTATRIBE_EquipPromoteDataHandler_H_
#define _DOTATRIBE_EquipPromoteDataHandler_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

struct EquipPromoteData
{
	unsigned char	type;
	int nextValue;

};

struct EquipPromoteItemData
{
	int templateid;
	int iocn;
	unsigned char	quality;
	int needNum;
	int hasNum;
};

class EquipPromoteDataHandler : public IDataHandler, public cobra_win::Singleton2<EquipPromoteDataHandler>
{
public:
		int m_Item_ID;
		unsigned char	m_Lv_IsMax;
		unsigned short	m_Lv_Up;
		int m_Lv_Limit;
		int m_CostMoney;
		std::vector<EquipPromoteData> m_Attribute_List;
		std::vector<EquipPromoteItemData> m_Item_List;
public:
	EquipPromoteDataHandler();
	virtual ~EquipPromoteDataHandler();
	virtual void onDestroy();
	virtual bool init();

};

#endif