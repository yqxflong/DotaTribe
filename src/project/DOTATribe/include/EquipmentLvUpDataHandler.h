//Name:EquipmentLvUpDataHandler.h
//Author:尹强
//Function:装备升级控制器

#ifndef _DOTATRIBE_EQUIPMENTLVUPDATAHANDLER_H_
#define _DOTATRIBE_EQUIPMENTLVUPDATAHANDLER_H_


#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

class EquipCardsStructure
{
public:
	BagEquipData* data;
	bool isSelected;
};

class EquipSwallowData
{
public:
	int equipId;					//装备Id
	unsigned char swallowType;		//吞噬类型
	int addExp;						//吞噬获得经验
	int useMoney;					//花费

public:
	void decodePacket(cobra_win::DPacket & packet);
};

class EquipmentLvUpData
{
public:
	int level;						//装备等级
	int equipExp;				//装备经验
	int equipMaxExp;			//装备最大经验
	int mainAttriMin;			//主属性最小
	int mainAttriMax;			//主属性最大
	Attribute attribute;		//通用属性
	Attribute attributeMax;		//通用属性最大值
	unsigned short swallowCount;	//吞噬数量
	int	changeValue;				//转换率
	int	changeValueMax;				//最大转换率
	std::vector<EquipSwallowData *>		swallowData;//吞噬数据
//2028

public:
	EquipmentLvUpData();
	~EquipmentLvUpData();

	void decodePacket(cobra_win::DPacket & packet);
};


class EquipmentLvUpDataHandler : public IDataHandler,public cobra_win::Singleton2<EquipmentLvUpDataHandler>
{
public:
	int selectedEquipId;

	BagEquipData selectEquip_StoreOnly;//非完整拷贝数据

	std::vector<int> vecEquipCostCard;	//数据是借来的，来自背包的数据，无需new和delete
	
	std::vector<int> vecEquipCostMoney;

	int needMoneyAll;

	EquipmentLvUpData * equipLvUpData;

public:
	EquipmentLvUpDataHandler();
	virtual ~EquipmentLvUpDataHandler();

	virtual void handlePacket(IPacket* packet);

	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
		清除数据
	*/
	void ClearData();
	/*
		初始化接口
	*/
	virtual bool init();

	/*
		获得选择Id的装备
	*/
	BagEquipData * GetEquipById(int id);

	/*
		判断选中的卡牌中是否含有紫色卡牌
	*/
	bool HasPurpleCard();
	/*
		判断选中的卡牌中是否含有紫色卡牌
	*/
	bool HasOrangeCard();

	/*
		选卡后和服务器通讯，取得每件物品花费的金钱
	*/
	void toServerSelectCard();

	/*
		升级，和服务器通讯，取得吞噬结果
	*/
	void toServerLvUp();

	/*
		拷贝存储，将from按照数据拷贝到to
	*/
	void CopyStore(BagEquipData * to,const BagEquipData * from);

	/*
		升级之后，需要将升级的结果赋值到内存中响应装备的数据区
	*/
	void ChangeEquipInfoByLvUpResult();

	/*
		从消耗列表里去掉吃掉的卡牌
	*/
	void RemoveCardsFromCostList();

	/*
		处理装备升级后事宜
	*/
	void HandleAfterEquipLvup();

	/*
		检查是否在消耗列表里
	*/
	bool isInCostList(int equipID);

	/*
		检查是否在升级列表里
	*/
	bool isInMainList(int equipID);

	/*
		检查cost列表是否有已装备的
	*/
	void checkCostList();

	/*
		检查花费是否足够
	*/
	bool isMoneyEnough();
	//
	/*
		重置所需花费
	*/
	void ResetMoney();
	/*
		初始化装备升级素材列表
	*/
	std::vector<EquipCardsStructure> GetEquipCostCardList();
	/*
		主卡的等级是否满足升级条件
	*/
	bool IsMainCardMeetLevelCondition();
	/*
		获取主卡
	*/
	BagEquipData* GetMainCard();
};

#define EQUIPMENTLVUPDATAHANDLER (EquipmentLvUpDataHandler::get_instance2())

#endif