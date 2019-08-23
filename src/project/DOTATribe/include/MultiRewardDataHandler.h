// Name :		MultiRewardDataHandler.h
// Function:	多个奖励数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef _DOTATRIBE_MULTIREWARDDATAHANDLER_H_
#define _DOTATRIBE_MULTIREWARDDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

struct MultiRewardData
{
	int				type; //类型 0:物品 1:金钱 2: 经验 3:钻石 4:声望 5:体力
	int				itemid;
	std::string		name;
	int				iconid;
	int				quality;	
	int				num;
};	

class MultiRewardDataHandler : public IDataHandler, public cobra_win::Singleton2<MultiRewardDataHandler>
{
public:

	unsigned short MultiRewardNum;
	std::vector<MultiRewardData*> MultiRewardDataList;
	MultiRewardDataHandler(){};
	virtual ~MultiRewardDataHandler(){};
	virtual void onDestroy();
	virtual bool init();

};

#endif