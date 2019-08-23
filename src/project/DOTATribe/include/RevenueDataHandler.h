// Name :		RevenueDataHandler.h
// Function:	点金数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_REVENUEDATAHANDLER_H
#define   _DOTATRIBE_REVENUEDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>

class RevenueDataHandler:public IDataHandler,public cobra_win::Singleton2<RevenueDataHandler>{
public:
	unsigned short m_Level;
	int m_Exp;
	int m_maxExp;
	unsigned char m_FreeTimes;
	int m_coolTime;
	int m_lowCost;
	int m_highCost;
	
	bool m_showArrow;
public:
	RevenueDataHandler();
	virtual ~RevenueDataHandler();
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
};
#endif