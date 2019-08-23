// Name :		MultiRewardDataHandler.h
// Function:	多个奖励数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/MultiRewardDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/HomeProcedure.h"

using namespace std;


void MultiRewardDataHandler::onDestroy()
{
	std::vector<MultiRewardData*>::iterator iter =  MultiRewardDataList.begin();
	std::vector<MultiRewardData*>::iterator iter_end =  MultiRewardDataList.end();
	for(;iter!=iter_end;++iter)
	{
		delete *(iter);
	}
	MultiRewardDataList.clear();
	MultiRewardNum =0;
}
	
bool MultiRewardDataHandler::init()
{
	return true;
}
