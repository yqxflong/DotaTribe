//Name:NetObjectTipsDataHandler.cpp
//Function:网络物品tips数据管理器
//Author:fangjun
//date:20131014

#include <cocos2d.h>
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NetObjectTipsPacket.h"
#include "../include/WindowManager.h"
#include "../include/NFControlsManager.h"

NetObjectTips::NetObjectTips()
{
	name = "";
	level = 0;
	price = 0;
	description = "";
	pEquip_ = NULL;
	isSalebtn_ = false;
}
NetObjectTips::~NetObjectTips()
{
	name = "";
	level = 0;
	price = 0;
	description = "";
	pEquip_ = NULL;
	isSalebtn_ = false;
}

void NetObjectTips::decodePacketData(cobra_win::DPacket & packet)
{
	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//名字
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;
	
	packet.read(level);
	packet>>price;

	packet>>strlen;//说明
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	description.assign(str);
	delete[] str;
	str = NULL;

	pEquip_ = NULL;
	isSalebtn_ = false;
}

NetObjectTipsDataHandler::NetObjectTipsDataHandler()
{
	m_pObjectTips = NULL;
	m_iShowedTipsWindow = -1;
	m_pObjectTips = new NetObjectTips;
	m_templateId = 0;
}

NetObjectTipsDataHandler::~NetObjectTipsDataHandler()
{
	if(m_pObjectTips != NULL)
	{
		delete m_pObjectTips;
		m_pObjectTips = NULL;
	}
	ClearTipsDataList();
}

void NetObjectTipsDataHandler::handlePacket(IPacket* packet)
{

}

void NetObjectTipsDataHandler::onDestroy()
{

}

bool NetObjectTipsDataHandler::init()
{
	return true;
}

void NetObjectTipsDataHandler::ToServerGetObjectTips(int templateId, int windowType)
{
	m_iShowedTipsWindow = windowType;
	m_templateId = templateId;
	std::map<int ,NetObjectTips* >::iterator it= m_NettipsList.find(m_templateId);
	if (it == m_NettipsList.end())
	{
		CSNetObjectTipsPacket packet(templateId);
		packet.Send();
		NFC_showCommunicationWating(true);
	}
	else
	{
		AssignTipsData(m_pObjectTips,it->second);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_);
	}
}

void NetObjectTipsDataHandler::ToClientGetObjectTips()
{
	NFC_showCommunicationWating(false);
	SaveQueryTipsData();
	if(m_iShowedTipsWindow > 0)
	{
		if(WINDOWMANAGER->IsWindowVisible(m_iShowedTipsWindow))
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_);
		}
	}

	m_iShowedTipsWindow = -1;
}


void NetObjectTipsDataHandler::SaveQueryTipsData()
{
	std::map<int ,NetObjectTips* >::iterator it= m_NettipsList.find(m_templateId);
	if (it == m_NettipsList.end())
	{
		//当前没有该物品templateId
		NetObjectTips* tipsdata = new NetObjectTips();
		AssignTipsData(tipsdata,m_pObjectTips);
		m_NettipsList.insert(std::map<int ,NetObjectTips* >::value_type(m_templateId,tipsdata));
	}
}

void NetObjectTipsDataHandler::AssignTipsData(NetObjectTips* lvalue,NetObjectTips* rvalue)
{
	lvalue->isSalebtn_ = rvalue->isSalebtn_;
	lvalue->level = rvalue->level;
	lvalue->name = rvalue->name;
	lvalue->objectId = rvalue->objectId;
	lvalue->pEquip_ = rvalue->pEquip_;
	lvalue->price = rvalue->price;
	lvalue->description = rvalue->description;
}

void NetObjectTipsDataHandler::ClearTipsDataList()
{
	std::map<int ,NetObjectTips* >::iterator it_beg = m_NettipsList.begin();
	std::map<int ,NetObjectTips* >::iterator it_end = m_NettipsList.end();
	for (it_beg;it_beg!=it_end;it_beg++)
	{
		if (it_beg->second)
		{
			CC_SAFE_DELETE(it_beg->second);
		}
	}
}