//Name:ShopTipsDataHandler
//Function:…ÃµÍTips ˝æ›
//Author:lvyunlong
//date:20140214

#include <cocos2d.h>
#include "../include/ShopTipsDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"


ShopTipsData::ShopTipsData()
{
	name_ = "";
	price_ = 0;
	description_ = "";
	moneytype_ = 0;
}

ShopTipsData::~ShopTipsData()
{

}

ShopTipsDataHandler::ShopTipsDataHandler()
{
	m_pTips = NULL;
}

ShopTipsDataHandler::~ShopTipsDataHandler()
{
	CC_SAFE_DELETE((m_pTips));
}

void ShopTipsDataHandler::handlePacket(IPacket* packet)
{

}

void ShopTipsDataHandler::onDestroy()
{

}

bool ShopTipsDataHandler::init()
{
	m_pTips = new ShopTipsData;
	return true;
}