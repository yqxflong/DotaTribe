//Name:EquipTrainDataHandler
//Function:装备洗练
//Author:	fangjun
//Date:20130820

#ifndef _DOTATRIBE_EQUIPTRAIN_DATAHANDLER_H_
#define _DOTATRIBE_EQUIPTRAIN_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/BagEquipDataHandler.h"
#include <vector>
#include "../include/CSMapTable.h"

class AttributeLock{
public:
	int serial;
	int equipId;					//装备Id
	unsigned char attributeIndex;	//属性索引

public:
	void decodePacketData(cobra_win::DPacket & packet);

};

class TrainData{
public:
	int equipId;
	Attribute attribute;		//通用属性
	Attribute attributeMax;	//通用属性最大值

	char moneyEnough;		//可以进行下一条洗练

public:
	void decodePacketData(cobra_win::DPacket & packet);

};

class EquipTrainDataHandler : public IDataHandler, public cobra_win::Singleton2<EquipTrainDataHandler>{
public:
	std::vector<int> m_vecEquipId;//玩家拥有的装备的Id

	AttributeLock m_pLock;//锁定的，接收到的
	AttributeLock m_pUnLock;//解锁，接收到的

	TrainData m_pTrainData;//装备洗练数据，接收到的

	std::vector<int> m_vecEquipLockStatus;//装备的锁定情况

	int m_iAttriPrice;//单挑属性洗练价格

	std::map<int, int> m_mapAttributeLockPosition;//锁与属性位置对应点，add at 20130830; 其中key为锁id，value为物品属性index
	
	std::map<int, int> m_mapOneKeyTrainLastAttribute;//一键洗练中上次的属性
	std::map<int, int> m_mapOneKeyTrainLastAttributeMax;//一键洗练中上次的属性
	std::map<int, int> m_mapOneKeyAttributeLockPosition;//一键洗练中上次属性锁和属性的位置对应点

private:
	int m_iCurEquipId;	//当前选择洗练的装备

public:
	EquipTrainDataHandler();
	virtual ~EquipTrainDataHandler();

	int GetCurEquipId();

	void SetCurEquipId(int id);//切换当前装备时需要将装备的锁状态清空

public:
	void decodePacketData(cobra_win::DPacket & packet);


	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy(){};

	virtual bool init(){	return true;	};

public:

	//锁定属性
	void ToServerLockAttribute(int serial, int equipId, int attriIndex);
	void ToClientLockAttributeResult();

	//解锁属性
	void ToServerUnLockAttribute(int serial, int equipId, int attriIndex);
	void ToClientUnLockAttributeResult();
	
	//洗练
	void ToServerTrain(int equipId);
	void ToClientTrainResult();

	//获得装备锁状态
	void ToServerGetAttributeLockStatus(int equipId);
	void ToClientGetAttributeLockStatusResult();

	//获得当前装备的锁状态
	void ToServerGetCurrentAttributeLockStatus();

	BagEquipData * GetEquipById(int id);

	BagEquipData * GetCurEquip();

	void AddLock(unsigned char index);

	void DeleteLock(unsigned char index);

	//通过获得的洗练结果改变内存中装备的数据
	void ChangeEquipAttributeByTrainResult();

	//判断一个装备是否能够进行一键洗练
	bool IsCurEquipCanOneKeyTrain();

	/*
		清除数据
	*/
	void ClearData();
};

#define EQUIPTRAINDATAHANDLER (EquipTrainDataHandler::get_instance2())

#endif