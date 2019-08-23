//Name: HuntView.cpp
//Function：寻宝
//Author: fangjun
//Date: 2013-12-4

#include "../include/HuntView.h"
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


HuntView::HuntView()
	:m_pRoot(NULL)
{

}

HuntView::~HuntView()
{

}

void HuntView::_initLayout()
{
	m_pRoot = this;

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHUNTWINDOW, m_pRoot);
	/*if(ROLEINFODATAHANDLER->m_pRIData->level_ <= HUNT_GUIDE_LEVEL)
	{
		cocos2d::extension::CCSkeletonAnimation * arrow = NFC_createGuideArrow();
		MaskNode * arrowParent = (MaskNode *)m_pRoot->getChildByTag(mGuideArrow);
		const UIViewData & ud = arrowParent->GetViewData();
		arrow->setAnchorPoint(ccp(ud.anchorx_, ud.anchory_));
		arrowParent->addChild(arrow, 100, 0);
		arrow->setVisible(true);
		arrow->setRotation(90);
	}*/

	CCSprite * sp = (CCSprite *)m_pRoot->getChildByTag(mPeoplePic);
	sp->setRotationY(180);

	_mapMainPage();

	MININGDATAHANDLER->ToServerEnterMining();

}

void HuntView::_mapMainPage()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	//寻宝按钮
	menu = (CCMenu *)m_pRoot->getChildByTag(mHuntBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mHuntBtn);
	item->setTarget(this, menu_selector(HuntView::On_Btn_Click));

	//购买按钮
	menu = (CCMenu *)m_pRoot->getChildByTag(mBuyBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mBuyBtn);
	item->setTarget(this, menu_selector(HuntView::On_Btn_Click));
}

void HuntView::_setMainPage()
{
	MiningData * data = MININGDATAHANDLER->m_pMiningData;
	if(data == NULL)
		return;

	char temp[512] = {0};
	//寻宝CD
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_HUNT_CD_).c_str(), data->lookCd);
	NFC_setLabelString(mHuntCD, m_pRoot, temp, true);

	//剩余寻宝次数
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_LEFT_HUNTTIME_).c_str(), data->leftHuntTimes, data->maxHuntTimes);
	NFC_setLabelString(mLeftHuntTime, m_pRoot, temp, true);

}

bool HuntView::onLoad()
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
void HuntView::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_7_MINERAL)){
		//======结束新功能开启=======
		NFC_setNodeVisable(mGuideArrow,m_pRoot,true);
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_7_MINERAL);
	}
}

bool HuntView::onDestroy()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);

	return true;
}

bool HuntView::onTick()
{


	return true;
}

void HuntView::OnShowWindowEventHandler(std::list<std::string>& paramList)
{

}

void HuntView::On_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;

	int tag = item->getTag();

	if(tag == mHuntBtn)
	{//寻宝功能
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MineAreaWindow::_PAGE_HUNTMINE_));
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_);
	}
	else if(tag == mBuyBtn)
	{//购买次数
		MININGDATAHANDLER->ToServerBuyHuntTimes();
	}

}

void HuntView::Function_GetEnterMiningData()
{
	_setMainPage();

}
