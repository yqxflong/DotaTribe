// Name :		HeroTechnologyDataHandler.h
// Function:	信仰数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_HEROTECHNOLOGYDATAHANDLER_H
#define   _DOTATRIBE_HEROTECHNOLOGYDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>

struct HeroTechnology
{
	int Tag;
	unsigned char id;						//科技模版id<br>
	std::string name;						//科技名字<br>
	int icon;								//科技图标<br>
	int costPoints;							//升级所需科技点数<br>
	unsigned short level;					//科技等级<br>
	unsigned char attriType;				//影响属性类型<br>
	unsigned short addValue;				//影响属性数值<br>
	unsigned short nextLevelAddValue;		//下一级影响属性数值 -1表示已经到顶级<br>
};

class HeroTechnologyDataHandler:public IDataHandler,public cobra_win::Singleton2<HeroTechnologyDataHandler>{
public:

	int score;								//科技点数<br>
	unsigned short maxLevel;				//最大科技等级上限<br>
	unsigned char count;					//科技数量<br>

	unsigned char TechnologyID;				//科技ID
	int TechnologyNeedTime;					//科技所需时间

	float Lasttime;							//上一次时间
	bool IsAsk;
	bool IsFirstAsk;
	int UpdateTechnologyID;					//科技ID
	int	UpdateTechnologyTime;				//科技时间


	unsigned char m_free_pray_times;		//免费祈愿次数
	int	m_pray_cost;						//祈愿消耗
	std::vector<HeroTechnology*> HeroTechnologyList;
	float m_View_PosY;
	int m_TabNum;
	int m_ReturnWindow;
	int m_HideWindow;
	int m_ReturnTabNum;
public:
	HeroTechnologyDataHandler();
	virtual ~HeroTechnologyDataHandler();
	HeroTechnology* GetTechnologyByID(int id);
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
};
#endif