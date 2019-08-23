// Name :		LevelUpDataHandler.h
// Function:	角色升级数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_LEVELUPDATAHANDLER_H
#define   _DOTATRIBE_LEVELUPDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>

struct LevelUpData
{
	unsigned short	lv;
	int		skill1;
	int		skill2;
	int		point;
	int		professionalskill;
	int		functionID;

	LevelUpData()
	{
		functionID = -1;
		skill1 = -1;
		skill2 = -1;
	}
};

class LevelUpDataHandler:public IDataHandler,public cobra_win::Singleton2<LevelUpDataHandler>{
public:
std::vector<LevelUpData*> LevelUpDataList;
bool m_showIsNeed;
bool m_showFlag;
public:
	LevelUpDataHandler();
	virtual ~LevelUpDataHandler();
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	bool   isEmpty();
};
#endif