//Name:EquipStrengthenDataHandler.h
//Author:尹强
//Function:装备强化

#ifndef _DOTATRIBE_EquipStrengthenDataHandler_H_
#define _DOTATRIBE_EquipStrengthenDataHandler_H_


#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <vector>

class BagEquipData;
class EquipStrengthenDataHandler : public IDataHandler,public cobra_win::Singleton2<EquipStrengthenDataHandler>
{
public:
	std::vector<BagEquipData*> RoleEquipList_;	//身上装备的列表
	std::vector<BagEquipData*> EquipList_;	//包含身上和背包的装备
	int m_HeroIndex;
public:
	EquipStrengthenDataHandler();
	virtual ~EquipStrengthenDataHandler(){};
	/*
		销毁接口
	*/
	virtual void onDestroy();
	/*
		初始化接口
	*/
	virtual bool init();

	/*
		加载装备for装备升级
	*/
	void LoadEquipList_EquipLvUp(int heroindex = 0);

	/*
		加载装备for装备进阶
	*/
	void LoadEquipList_Progress(int heroindex = 0);
	/*
		加载装备for装备洗练
	*/
	void LoadEquipList_Train(int heroindex = 0);

	/*
	   加载装备for装备分解
	*/
	void LoadEquipList_Recast();

	/*
		清空容器
	*/
	void ClearEquipList();

	/*
		是否存在该装备
		#已装备
	*/
	bool CheckTheEquipExisted_RoleEquip(int equipID);

	/*
		是否存在该装备
		#全部装备
	*/
	bool CheckTheEquipExisted_All(int equipID);
private:
	inline void _loadBagEquipsToVec(std::vector<BagEquipData*>& vec);
	inline void _removeWhiteCard(std::vector<BagEquipData*>& vec);
	inline void _removeMaxAdvancedCard(std::vector<BagEquipData*>& vec);
	inline void _removeMaxLvCard(std::vector<BagEquipData*>& vec);
	inline void _removeExpBall(std::vector<BagEquipData*>& vec);
	//装备升级专用
	inline void _removeCardInCostList(std::vector<BagEquipData*>& vec);
};

#endif