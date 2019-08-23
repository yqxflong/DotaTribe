// Name :SoulTipsWindow.h
// Function：战魂tips窗口
// Author : lvyunlong
// Date: 20140224

#include "../include/SoulTipsWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/SoulEquipPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/NFControlsManager.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

SoulTipsWindow::SoulTipsWindow()
{
	m_WindowType = _TYPED_WINDOW_SOULTIPSWINDOW_;
	m_bModelWindow = false;
	m_Heroindex = 0;
}

SoulTipsWindow::~SoulTipsWindow()
{

}

bool SoulTipsWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SOULTIPSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SOULTIPSWINDOW_, true);

	return IWindow::Init();
}

bool SoulTipsWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();

		return true;
	}
	while (false);

	return false;
}

void SoulTipsWindow::Tick()
{
	IWindow::Tick();
}

void SoulTipsWindow::Destroy()
{
	m_pRootNode->removeAllChildrenWithCleanup(true);
	m_pNeedSoulData = NULL;
	IWindow::Destroy();
}	

void SoulTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_SOULTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_SOULTIPSWINDOW_)
	{
		Destroy();
	}
}

void SoulTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(paramList.size() > 0)
	{
		std::list<std::string>::iterator it = paramList.begin();
		std::string stridx = *it;
		int id = 0;
		sscanf(stridx.c_str(), "%d", &id);
		m_soulBufferID = id;
		it++;
		std::string strType = *it;
		int type = 0;
		sscanf(strType.c_str(),"%d", &type);
		m_soulType = type;
		if (type == _SOULTIPS_OWNER_)
		{
			it++;
			std::string strindex = *it;
			m_Heroindex = atoi(strindex.c_str());

			it++;
			std::string strtype = *it;
			int SoulType = atoi(strtype.c_str());
			if (SoulType == _SOUL_HERO_TYPE_)
			{
				IHeroSkinItem* pHeroSkin = NFC_GetTeamHero(m_Heroindex);
				if (pHeroSkin == NULL)
					return;
				m_pNeedSoulData = pHeroSkin->getBuffIdByHeroItem(m_soulBufferID);
			}
			else if (SoulType == _SOUL_DB_TYPE_)
			{
				m_pNeedSoulData = ROLESOULSDATAHANDLE->getHeroSoulItemByID(m_soulBufferID);
			}		
		}	
		else if( type == _SOULTIPS_OTHER_)
		{
			std::vector<IHeroSoulItem*>::iterator it = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.souls.begin();
			std::vector<IHeroSoulItem*>::iterator end = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.souls.end();
			for(;it != end;it++){
				if( (*it)->getHeroSoulBufferID() == m_soulBufferID ){
					m_pNeedSoulData = (*it);
					break;
				}
			}
		}

		if( !m_pNeedSoulData)
			return;
		setBtnshow();
		setInfoTips();
	
	}
	Show(true);
}

void SoulTipsWindow::setBtnshow()
{
	if( m_soulType == _SOULTIPS_OWNER_){
	//-1 为未装备 其他为装备
		if (m_pNeedSoulData->getHeroSoulEquipIndex() == -1)
		{
			NFC_setNodeVisable(_SOULTIPS_EQUIPEDBTN,m_pRootNode,true);
			NFC_setNodeVisable(_SOULTIPS_EQUIPEDTTF,m_pRootNode,true);
		}
		else
		{
			NFC_setNodeVisable(_SOULTIPS_UNLOADBTN,m_pRootNode,true);
			NFC_setNodeVisable(_SOULTIPS_UNLOADTTF,m_pRootNode,true);
		}
	}
	else if( m_soulType == _SOULTIPS_OTHER_){
		NFC_setNodeVisable(_SOULTIPS_EQUIPEDBTN,m_pRootNode,false);
		NFC_setNodeVisable(_SOULTIPS_EQUIPEDTTF,m_pRootNode,false);
		NFC_setNodeVisable(_SOULTIPS_UNLOADBTN,m_pRootNode,false);
		NFC_setNodeVisable(_SOULTIPS_UNLOADTTF,m_pRootNode,false);
	}
}

void SoulTipsWindow::setInfoTips()
{
	//名字
	NFC_setLabelString(_SOULTIPS_NAME,m_pRootNode,m_pNeedSoulData->getHeroSoulBufferName());
	//图标
	std::string strpath = NFC_getFileFromResourceID(m_pNeedSoulData->getHeroSoulBufferIconID());
	NFC_setPicForCCSprite(_SOULTIPS_SOULICON,m_pRootNode,strpath.c_str());
	//等级
	char buff[1024]={0};
	if (m_pNeedSoulData->getHeroSoulCurLevel() == 0)
	{
		sprintf(buff, SysLangDataManager::get_instance2()->GetSysLangById(6091).c_str());
		NFC_setNodeVisable(_SOULTIPS_EQUIPEDBTN, m_pRootNode, false);
		NFC_setNodeVisable(_SOULTIPS_UNLOADBTN, m_pRootNode, false);
		NFC_setNodeVisable(_SOULTIPS_EQUIPEDTTF, m_pRootNode, false);
		NFC_setNodeVisable(_SOULTIPS_UNLOADTTF, m_pRootNode, false);
	}
	else
	{
		sprintf(buff, SysLangDataManager::get_instance2()->GetSysLangById(6071).c_str(), m_pNeedSoulData->getHeroSoulCurLevel(), m_pNeedSoulData->getHeroSoulMaxLevel());
	}
	
	NFC_setLabelString(_SOULTIPS_LEVEL,m_pRootNode,buff);
	//附加
	NFC_setLabelString(_SOULTIPS_ADDITTION,m_pRootNode,m_pNeedSoulData->getHeroSoulAtributeName());
}

void SoulTipsWindow::_initLayout()
{
	_initControl();
	_mapBtn();
}

void SoulTipsWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROSOULTIPSWINDOW,m_pRootNode);
	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pRootNode->getChildByTag(_SOULTIPS_PRIORITY);
	p->setDelegate(this);
}

void SoulTipsWindow::_mapBtn()
{
	CCMenu* menu=(CCMenu*)m_pRootNode->getChildByTag(_SOULTIPS_EQUIPEDBTN);
	CMenuItemSprite*cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(SoulTipsWindow::On_Check_Equip_Event));

	menu=(CCMenu*)m_pRootNode->getChildByTag(_SOULTIPS_CLOSEBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(SoulTipsWindow::On_Check_Close_Event));

	menu=(CCMenu*)m_pRootNode->getChildByTag(_SOULTIPS_UNLOADBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(SoulTipsWindow::On_Check_Disboard_Event));
}

/*
	装备按钮
*/
void SoulTipsWindow::On_Check_Equip_Event(cocos2d::CCObject* pSender)
{
	C2SEquipHeroSoulPacket   equipSoulPacket(m_Heroindex, m_soulBufferID);
	equipSoulPacket.Send();
	//装备
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SOULTIPSWINDOW_);
}

/*
	关闭按钮
*/
void SoulTipsWindow::On_Check_Close_Event(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SOULTIPSWINDOW_);
}

void SoulTipsWindow::On_Check_Disboard_Event(cocos2d::CCObject* pSender)
{
	C2SUnEquipHeroSoulPacket  unEquipHeroPacket(m_Heroindex,m_soulBufferID,m_pNeedSoulData->getHeroSoulEquipIndex());
	unEquipHeroPacket.Send();
	//卸下
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SOULTIPSWINDOW_);
	
}
/*
	CPriorityLayerColor Delegate
*/
void SoulTipsWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SOULTIPSWINDOW_);
}


