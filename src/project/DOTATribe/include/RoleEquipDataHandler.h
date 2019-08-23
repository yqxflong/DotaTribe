//Name： RoleEquipDataHandler
//Function：管理英雄的装备
//Author：Johny

#ifndef   _DOTATRIBE_ROLEEQUIPDATAHANDLER_H
#define   _DOTATRIBE_ROLEEQUIPDATAHANDLER_H

#include "../include/IDataHandler.h"
#include "../include/BagEquipDataHandler.h"
#include <map>
#include <cocos2d.h>


class RoleEquipData{
public:
	unsigned char index_;						//装备索引位置<br>
	unsigned char hasEquip_;					//0无 1有<br>
	BagEquipData* equipdata_;				//装备数据
	RoleEquipData(){
		equipdata_=0;
	}

	RoleEquipData(BagEquipData * bed)
	{
		equipdata_ = bed;
		equipdata_->isEquiped_ = 1;
	}

	virtual ~RoleEquipData(){
		if (!equipdata_)return;
		delete equipdata_;
	}

	void refreshEquipData(BagEquipData * bed);
};

class RoleEquipDataHandler:public IDataHandler{
private:
	int m_offequip_type;
public:
	std::map<int,RoleEquipData*> m_mapEquipList;
	int HeroEquip_Tab_IsSelected;	//英雄装备界面，正在选中的页签
public:
	RoleEquipDataHandler();
	virtual ~RoleEquipDataHandler(){};

	virtual bool init();
	virtual void onDestroy();

	void decodePacketData(cobra_win::DPacket & packet);

	BagEquipData * getEquipById(int id);

	BagEquipData * getEquipByType(int etype);

	//获得所有的人物装备
	std::vector<BagEquipData*> getRoleEquips();

	/*
		按照规则排序装备
		Type	
	*/
	std::vector<BagEquipData*> getRoleEquipsByType();

	/*
		排序：强化装备专用
		1.品质（大到小）  2.type(小到大)   3.等级(大到小)
	*/
	std::vector<BagEquipData*> getRoleEquipsForStrengthen();
	 
	/*
		获取一件默认的升级装备
	*/
	BagEquipData* GetDefaultRoleEquip_EquipLvup();

	/*
		检查是否有可以升级的装备
	*/
	bool CheckAllRoleEquipsCanTopup();

public:
	//begin:卸装备相关
	void OffEquip_Request(int equipid,int heroPos);
	void decodePacketData_OffEquip(cobra_win::DPacket & packet);
	void HanldeAfterOffEquip();
	void OffEquip_Local(int equipType);
	//end

	//begin:更换装备
	void ChangeEquip_Request(int equipid,int heroPos);
	void decodePacketData_ChangeEquip(cobra_win::DPacket & packet);
	void HanldeAfterChangeEquip();
	//end
};

#endif