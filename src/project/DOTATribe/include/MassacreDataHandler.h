// Name :		MassacreDataHandler.h
// Function:	扫荡数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_MASSACREDATAHANDLER_H
#define   _DOTATRIBE_MASSACREDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

struct ItemData
{
	std::string     itemName;
	unsigned char	itemCount;
	int				itemID;
	int				iconID;
	unsigned char	quality;
	unsigned char	isEquip;	//1可装备 0不可装备（可以叠加）
};

struct MassacreData
{
	int     money;
	int		roleExp;
	int		shapeExp;
	unsigned char itemCount;
	std::vector<ItemData*> ItemDataList;
};

class MassacreDataHandler:public IDataHandler,public cobra_win::Singleton2<MassacreDataHandler>{
public:
	unsigned char MassacreCount;
	unsigned char EndType;//0成功, 1背包满, 2体力不足, 3扫荡次数不够, 4人物等级不够
	std::vector<MassacreData*> MassacreDataList;
public:
	MassacreDataHandler();
	virtual ~MassacreDataHandler(){};
	virtual bool init();
	virtual void onDestroy();
	//
	void ToServerPacket(int missionid,int stateid);
	void decodePacketData(cobra_win::DPacket & packet);
	void AfterDecodePacket();
	bool getCanForceCloseState();
	void setToForceCloseInitState();
public:
	bool MassacreCanForceClose;
};
#endif