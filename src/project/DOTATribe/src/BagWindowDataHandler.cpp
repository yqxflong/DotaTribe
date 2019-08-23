//Name:BagWindowDataHandler.cpp
//Function:背包数据管理器
//Author:fangjun
//date:20130903

#include <cocos2d.h>
#include "../include/BagWindowDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/BagWindowPacket.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

BagWindowDataHandler::BagWindowDataHandler()
{
	DATA_RightPanel = NULL;
	DATA_Window = NULL;
}

BagWindowDataHandler::~BagWindowDataHandler()
{

}


void BagWindowDataHandler::SetData(CPageScroll * page, BagWindow * window)
{
	DATA_RightPanel = page;
	DATA_Window = window;
}

void BagWindowDataHandler::handlePacket(IPacket* packet)
{

}

void BagWindowDataHandler::onDestroy()
{

}

bool BagWindowDataHandler::init()
{
	return true;
}

void BagWindowDataHandler::ToServerOpenLockBag(int bagType, int bagindex)
{
	CSOpenLockBagPacket packet(bagType, bagindex);
	packet.Send();
}

int BagWindowDataHandler::IsBagFull()
{
	if(BAGOTHEROBJECTHANDLER->m_vecList.size() > (unsigned int)(BAGOTHEROBJECTHANDLER->m_bagMaxCount - 3))
	{
		return BAG_ITEM;
	}
	if(BAGEQUIPDATAHANDLER->m_vecList.size() > (unsigned int)(BAGEQUIPDATAHANDLER->m_bagMaxCount - 3))
	{
		return BAG_EQUIP;
	}
	//if(BAGSKINDATAHANDLER->m_vecList.size() > (unsigned int)(BAGSKINDATAHANDLER->m_bagMaxCount - 3))
	//{
	//	return BAG_SKIN;
	//}

	return -1;
}

	/*
		处理关闭背包响应操作
	*/
void BagWindowDataHandler::HandleCloseBag(){
	//1.干掉所有effect
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);
}