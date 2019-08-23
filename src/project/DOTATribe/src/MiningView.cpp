//Name: MiningView.cpp
//Function：挖矿
//Author: fangjun
//Date: 2013-11-26

#include "../include/MiningView.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/TimeSystem.h"
#include "../include/MineAreaWindow.h"
#include "../include/MiningDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/GuideSystem.h"
USING_NS_CC;
USING_NS_CC_EXT;


MiningView::MiningView()
	:m_pRoot(NULL)
{

}

MiningView::~MiningView()
{

}

void MiningView::_initLayout()
{
	m_pRoot = this;

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMININGWINDOW, m_pRoot);
	_mapMainPage();

	MININGDATAHANDLER->ToServerEnterMining();

}

void MiningView::_mapMainPage()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	
	menu = (CCMenu *)m_pRoot->getChildByTag(mBtn1);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mBtn1);
	item->setTarget(this, menu_selector(MiningView::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(mBtn2);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mBtn2);
	item->setTarget(this, menu_selector(MiningView::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(mBtn3);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mBtn3);
	item->setTarget(this, menu_selector(MiningView::On_Btn_Click));

}

void MiningView::_setMainPage()
{
	MiningData * data = MININGDATAHANDLER->m_pMiningData;
	if(data == NULL)
		return;

	char temp[512] = {0};
	//矿区说明
	NFC_setLabelString(mMineDesc, m_pRoot, data->mineDesc, true);

	if(data->mineArea.size() >= 3)
	{
		//地精矿区
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_TIME_).c_str(), data->mineArea[0]->maxMiningTime);
		NFC_setLabelString(mTime1, m_pRoot, temp, true);
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_OUTPUT_).c_str(), data->mineArea[0]->outPut);
		NFC_setLabelString(mOutPut1, m_pRoot, temp, true);
		if (data->mineArea[0]->isMining)
		{
			NFC_setLabelString(mBtnLabel1, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(6045).c_str());
		}
		

		//矮人矿区
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_TIME_).c_str(), data->mineArea[1]->maxMiningTime);
		NFC_setLabelString(mTime2, m_pRoot, temp, true);
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_OUTPUT_).c_str(), data->mineArea[1]->outPut);
		NFC_setLabelString(mOutPut2, m_pRoot, temp, true);
		if (data->mineArea[1]->isMining)
		{
			NFC_setLabelString(mBtnLabel2, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(6045).c_str());
		}
		
		//巨龙矿区
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_TIME_).c_str(), data->mineArea[2]->maxMiningTime);
		NFC_setLabelString(mTime3, m_pRoot, temp, true);
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_OUTPUT_).c_str(), data->mineArea[2]->outPut);
		NFC_setLabelString(mOutPut3, m_pRoot, temp, true);
		if (data->mineArea[2]->isMining)
		{
			NFC_setLabelString(mBtnLabel3, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(6045).c_str());
		}
	}
}

bool MiningView::onLoad()
{
	if(CCNode::init()){
		setPosition(CCPointZero);
		this->autorelease();

		_initLayout();
		_checkNewFunc();
		return true;
	}

	return false;
}

	/*
		检查新功能开启
	*/
void MiningView::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE)){
		//======结束新功能开启=======
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE);
	}
}

bool MiningView::onDestroy()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);

	return true;
}

bool MiningView::onTick()
{


	return true;
}

void   MiningView::OnShowWindowEventHandler(std::list<std::string>& paramList)
{

}

void MiningView::On_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;

	int tag = item->getTag();

	if(tag == mBtn1)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MineAreaWindow::_PAGE_GOBLINAREA_));
	}
	else if(tag == mBtn2)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MineAreaWindow::_PAGE_DWARVENAREA_));
	}
	else if(tag == mBtn3)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MineAreaWindow::_PAGE_DRAGONAREA_));
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_);
}

void MiningView::Function_GetEnterMiningData()
{
	_setMainPage();

}
