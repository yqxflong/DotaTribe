//Name:ShopTipsDataHandler
//Function:…ÃµÍTips ˝æ›
//Author:lvyunlong
//date:20140214

#ifndef _DOTATRIBE_SHOPTIPSDATAHANDLER_H_
#define _DOTATRIBE_SHOPTIPSDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include <string>
#include <map>

class ShopTipsData
{
public:
	ShopTipsData();
	~ShopTipsData();
public:
	std::string name_;
	int price_;
	std::string description_;
	int moneytype_;
};

class ShopTipsDataHandler: public IDataHandler, public cobra_win::Singleton2<ShopTipsDataHandler>{
public:
	ShopTipsData * m_pTips;
public:
	ShopTipsDataHandler();
	virtual ~ShopTipsDataHandler();
protected:

	virtual void handlePacket(IPacket* packet);

	virtual void onDestroy();

	virtual bool init();

public:
};

#define SHOPTIPSDATAHANDLER (ShopTipsDataHandler::get_instance2())

#endif