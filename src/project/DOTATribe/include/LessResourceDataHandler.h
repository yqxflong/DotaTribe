// Name :		LessResourceDataHandler.h
// Function:	资源不足数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef _DOTATRIBE_LessResourceDataHandler_H_
#define _DOTATRIBE_LessResourceDataHandler_H_

#include <include/common/Singleton.h>
#include <include/mem/DPacket.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h" 
#include <vector>
#include <string>

struct DoingData
{
	unsigned char	isOpen;
	unsigned char   id;
public:
	DoingData()
	{
		isOpen = 0;
		id = 0;
	}
	void  decodePacketData(cobra_win::DPacket & packet)
	{
		packet.read(isOpen);
		packet.read(id);
	}
};

class LessResourceDataHandler : public IDataHandler, public cobra_win::Singleton2<LessResourceDataHandler>
{
private:
	//VIP跳转枚举
	enum
	{
		Type_None,
		Type_Vip,
	};
	enum
	{
		_LESS_UNKONW_TYPE_,			//未知不足类型
		_LESS_POWER_TYPE_,			//体力不足
		_LESS_TOWER_TYPE_,			//试练塔不足
		_LESS_ARENA_TYPE_,			//竞技次数不足
		_LESS_TREASUREHUNT_TYPE_,	//寻宝不足
		_LESS_TEAM_TYPE_,			//远古寻迹不足
	};

public:
		IByte			type;				//资源类型 1：体力 2：试炼次数 3：竞技次数 4：寻宝次数 5：遗迹次数
		std::string		tips;				//补充资源方法提示
		IByte			jumpID;				//跳转界面 0,不用 1：vip
		IByte			hasNext;			//是否需要
		int				itemId;				//物品ID
		int				iconId;				//物体图标ID
		IByte			quality;			//物品品质
		std::string		name;				//物品名称
		std::string		description;		//描述
		UShort			leftCount;		    //物品剩余数
		int				leftUseTime;		//剩余使用次数
		 
	std::vector<DoingData*> DoingDataList;
	LessResourceDataHandler();
	virtual ~LessResourceDataHandler();
	virtual void onDestroy();
	virtual bool init();
	void JumpToVIP();
public:
	void  decodePacketHandler(cobra_win::DPacket & packet);
protected:
	void  destroyMemData();
};

#endif