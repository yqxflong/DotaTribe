//Name：英雄召唤界面
//Function：英雄召唤相关
//Written By：吕云龙
//Date：20131205

#include "../include/HerobarWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/MaskNode.h"
#include "../include/SceneEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/AnimationEffect.h"
#include "../include/GuideSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/config_HomeWindow.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/FAnimationButton.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


//class: HerobarWindow
HerobarWindow::HerobarWindow()
:m_pRoot(NULL),
m_pSummonNode(NULL),
m_iPreelitetime(0),
m_iPreHolytime(0),
m_isFreeElite(0),
m_isFreeHoly(0),
m_pHolyNode(NULL),
m_isBTick(false),
m_isShowHolyNode(false),
m_strLeftTime("")
{
	m_WindowType   = _TYPED_WINDOW_HEROBAR_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

HerobarWindow::~HerobarWindow()
{

}

bool HerobarWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_HEROBARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_HEROBARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);

	return IWindow::Init();
}

bool HerobarWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		HEROSUMMONCONTROLDATAHANDLER->ToServerRequestSummonInfo();
		//关闭提示免费召唤
		ROLEINFODATAHANDLER->m_pRIData->freesummon_ = 0;
		//=======结束新功能开启=========
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR);
		return true;
	} 
	while (false);

	return false;
}

void HerobarWindow::Tick()
{
	if (m_isBTick)
	{
		_leftHolytime();
	}
	IWindow::Tick();
}

void HerobarWindow::Destroy()
{
	m_isBTick = false;
	m_iPreelitetime = 0;
	m_iPreHolytime = 0;
	m_isShowHolyNode = false;
	if (m_pSummonNode)
	{
		m_pSummonNode->removeAllChildrenWithCleanup(true);
		m_pHolyNode = NULL;
	}
	IWindow::Destroy();
}

void HerobarWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_HEROBARWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_HEROBARWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}	
	else if (iEventType == _TYPED_EVENT_UPDATE_HEROBARWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		refreshSoulStoneUIData();
	}	
}

void HerobarWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pSummonNode = CCNode::create();
	m_pSummonNode->setAnchorPoint(CCPointZero);
	m_pSummonNode->setPosition(CCPointZero);
	m_pRoot->addChild(m_pSummonNode,10);
	_initControl();
	m_pHolyNode = (MaskNode*)NFC_getNode(udHOLYNODE,m_pSummonNode);
	_mapBtn();
	refreshSoulStoneUIData();
	m_strLeftTime = SysLangDataManager::get_instance2()->GetSysLangById(6052).c_str();
}
void HerobarWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROSUMMONWINDOW,m_pSummonNode);
}

void HerobarWindow::_mapBtn()
{
	CCMenu* menu =(CCMenu*)m_pSummonNode->getChildByTag(udHEROLISTBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHEROLISTBTN);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_Summon_Event));

	menu=(CCMenu*)m_pSummonNode->getChildByTag(udQUICKCITYBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udQUICKCITYBTN);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_Event));

	menu=(CCMenu*)m_pSummonNode->getChildByTag(udHEROALTARBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHEROALTARBTN);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_Event));

	//大厅按钮
	menu=(CCMenu*)m_pSummonNode->getChildByTag(udHEROBASEBTN1);
	FAnimationButton* aButton=(FAnimationButton*)menu->getChildByTag(0);
	aButton->setIDX(udHEROBASEBTN1);
	aButton->setTarget(this,menu_selector(HerobarWindow::On_Click_HallBtn_Event));

	menu=(CCMenu*)m_pSummonNode->getChildByTag(udHEROBASEBTN2);
	aButton=(FAnimationButton*)menu->getChildByTag(0);
	aButton->setIDX(udHEROBASEBTN2);
	aButton->setTarget(this,menu_selector(HerobarWindow::On_Click_HallBtn_Event));

	menu=(CCMenu*)m_pSummonNode->getChildByTag(udHEROBASEBTN3);
	aButton=(FAnimationButton*)menu->getChildByTag(0);
	aButton->setIDX(udHEROBASEBTN3);
	aButton->setTarget(this,menu_selector(HerobarWindow::On_Click_HallBtn_Event));
}

void HerobarWindow::_setNeedSoulCount()
{
	char buff[64]={0};
	sprintf(buff,"%d",HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->consumeCount[0]);
	NFC_setLabelString(udSOULNEEDCOUNTTTF1,m_pSummonNode,buff);
/*
	memset(buff,0,sizeof(buff));
	sprintf(buff,"%d",HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->consumeCount[1]);
	NFC_setLabelString(udSOULNEEDCOUNTTTF2,m_pSummonNode,buff);*/
	memset(buff,0,sizeof(buff));
	sprintf(buff,"%d",HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->consumeCount[1]);
	NFC_setLabelString(udSOULNEEDCOUNTTTF3,m_pSummonNode,buff);
}

void HerobarWindow::_leftHolytime()
{
	if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1] < 0)
	{
		m_isFreeHoly = 1;
		return;
	}
	else
	{
		long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
		long long during = nowtime - m_iPreHolytime;
		if (nowtime<m_iPreelitetime)
		{
			m_isBTick = false;
			return;
		}
		int seconds = (int)(during / 1000000);
		if(seconds >= 1)
		{
			m_iPreHolytime = nowtime;
			HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1]-=seconds;
			if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1] <= 0)
			{
				//显示免费
				m_isFreeHoly = 1;
				setFreeHoly(true);
				if (m_isShowHolyNode)
				{
					showHolyoneMoney(false);
				}
				return;
			}
			m_isFreeHoly = 0;
			int time = HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1];
			LeftTimeUpdate(m_pSummonNode,time,udHOLYTIMETTF);
			if (m_isShowHolyNode)
			{
				showHolyoneMoney(true);
			}
		}
	}
}

void HerobarWindow::LeftTimeUpdate(cocos2d::CCNode* node,int time,int key)
{
	char buff[512]={0};
	sprintf(buff, m_strLeftTime.c_str(), time / 3600, (time % 3600) / 60, (time % 3600) % 60);
	NFC_setLabelString(key,node,buff,true);
}

void HerobarWindow::initHolyNode()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROHOLYNODE,m_pHolyNode);
	_mapHolyBtn();
	m_isShowHolyNode = true;
	char buff[256]={0};
	sprintf(buff,"%d",HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->tenRecruitConsumeCount);
	NFC_setLabelString(udHOLYTENCALLMONET,m_pHolyNode,buff);
	memset(buff,0,sizeof(buff));
	sprintf(buff,"%d",HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->consumeCount[1]);
	NFC_setLabelString(udHOLYONEPRICETTF,m_pHolyNode,buff);
	if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1] <= 0)
	{
		showHolyoneMoney(false);
	}
	else
	{
		showHolyoneMoney(true);
	}
}

void HerobarWindow::_mapHolyBtn()
{
	//一次
	CCMenu* menu =(CCMenu*)m_pHolyNode->getChildByTag(udHOLYCALLONEBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHOLYCALLONEBTN);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_HolyBtn));
	//十次
	menu=(CCMenu*)m_pHolyNode->getChildByTag(udHOLYCALLTENBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHOLYCALLTENBTN);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_HolyBtn));
	//关闭按钮
	menu=(CCMenu*)m_pHolyNode->getChildByTag(udHOLYCLOSEBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(HerobarWindow::On_Click_Holy_CloseBtn));
}

void HerobarWindow::showHolyoneMoney(bool type)
{	
	NFC_showNode(udHOLYFREETTTF,m_pHolyNode,!type);
	NFC_showNode(udHOLYONEPRICETTF,m_pHolyNode,type);
	NFC_showNode(udHOLYONEMONEYICON,m_pHolyNode,type);
}

void HerobarWindow::setFreeElite(bool isfree)
{
	/*NFC_setNodeVisable(udFREEELITECALLTTF,m_pSummonNode,isfree);
	NFC_setNodeVisable(udELITETIMELTTF,m_pSummonNode,!isfree);
	NFC_setNodeVisable(udSOULSTORNICON2,m_pSummonNode,!isfree);
	NFC_setNodeVisable(udSOULNEEDCOUNTTTF2,m_pSummonNode,!isfree);*/

}
void HerobarWindow::setFreeHoly(bool isfree)
{
	NFC_setNodeVisable(udFREEHOLYCALLTTF,m_pSummonNode,isfree);
	NFC_setNodeVisable(udHOLYTIMETTF,m_pSummonNode,!isfree);
	NFC_setNodeVisable(udSOULSTORNICON3,m_pSummonNode,!isfree);
	NFC_setNodeVisable(udSOULNEEDCOUNTTTF3,m_pSummonNode,!isfree);
}

void HerobarWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void HerobarWindow::OnHideWindowEventHandler(std::list<std::string>& paramList){
	Destroy();
}

void HerobarWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList){

	if (paramList.size()>0)
	{
		std::list<std::string>::iterator it = paramList.begin();
		int itype = atoi((*it).c_str());
		if (itype == 1)
		{
			m_isShowHolyNode = false;
			if (m_pHolyNode)
			{
				m_pHolyNode->removeAllChildrenWithCleanup(true);
			}
		}
	}
	
	if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->mFirstSummon == 0)
		NFC_setNodeVisable(udJIANTOUMOVE,m_pSummonNode,true);
	else
		NFC_setNodeVisable(udJIANTOUMOVE,m_pSummonNode,false);

	//NFC_setNodeVisable(udPRIORITYLAYER,m_pSummonNode,false);

	//NFC_setNodeVisable(udSCENEEFFECT,m_pSummonNode,false);
	
	_setNeedSoulCount();
	m_isBTick = true;
	m_iPreelitetime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	m_iPreHolytime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
/*
	if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1]<=0)
	{
		m_isFreeElite = 1;
		//显示本次免费
		setFreeElite(true);
	}
	else
	{
		m_isFreeElite = 0;
		setFreeElite(false);
		LeftTimeUpdate(m_pSummonNode,HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1],udELITETIMELTTF);
	}*/
	if (HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1]<=0)
	{
		m_isFreeHoly = 1;
		//显示本次免费
		setFreeHoly(true);
	}
	else
	{
		m_isFreeHoly = 0;
		setFreeHoly(false);
		LeftTimeUpdate(m_pSummonNode,HEROSUMMONCONTROLDATAHANDLER->m_pSunmonInfoData->leftTime[1],udHOLYTIMETTF);
	}

}

void HerobarWindow::refreshSoulStoneUIData()
{
	int count = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(CLIENTCONSTDATAMANGER->getValueByKey(SOULSTONE_TEMPLATEID));
	char buff[1024]={0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6054).c_str(),count);
	NFC_setLabelString(udHAVESOULNUM,m_pSummonNode,buff);
	
	NFC_setLabelStringInt(udJEWELCOUNT,m_pSummonNode,ROLEINFODATAHANDLER->m_pRIData->jewels_);
}

void HerobarWindow::On_Click_Summon_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udHEROLISTBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HEROBARWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_,_to_event_param_(IWindow::_TYPED_WINDOW_HEROBAR_));
		//======新手引导======
		GUIDESYSTEM->Next();
	}
}

void HerobarWindow::On_Click_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udQUICKCITYBTN)
	{
		PushEvent(_TYPED_EVENT_HIDE_HEROBARWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if (index == udHEROALTARBTN)
	{
		if (_LV_HOMEWINDOW_NEWSCENE_HEROALTAR >RoleInfoDataHandler::get_instance2()->m_pRIData->level_)
		{
			char commonStr[128]={0}; 
			std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(7000);
			sprintf(commonStr,advanceTips.c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROALTAR);
			NFC_showMessageBoxSingle(kDEFAULT,commonStr); 
			return ; 
		}
		PushEvent(_TYPED_EVENT_HIDE_HEROBARWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_ALTARWINDOW_);
	}
}

void HerobarWindow::On_Click_HallBtn_Event(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("CallHeroCard",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	FAnimationButton* cc=(FAnimationButton*)pSender;
	int index = cc->getIDX();

	if (index == udHEROBASEBTN1)
	{
		HEROSUMMONCONTROLDATAHANDLER->ToServerCallHero(0,ONCE_TAKECARD,0);
	}
	else if (index == udHEROBASEBTN2)
	{
		HEROSUMMONCONTROLDATAHANDLER->ToServerCallHero(1,ONCE_TAKECARD,m_isFreeElite);
	}
	else if (index == udHEROBASEBTN3)
	{
		initHolyNode();
	}
}

void HerobarWindow::On_Click_HolyBtn(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("HolyBtn",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udHOLYCALLONEBTN)
	{
		HEROSUMMONCONTROLDATAHANDLER->ToServerCallHero(1,ONCE_TAKECARD,m_isFreeHoly);
	}
	else if (index == udHOLYCALLTENBTN)
	{
		HEROSUMMONCONTROLDATAHANDLER->ToServerCallHero(1,TEN_TAKECARD,0);
	}
}

void HerobarWindow::On_Click_Holy_CloseBtn(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("HolyClose",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	m_isShowHolyNode = false;
	if (m_pHolyNode)
	{
		m_pHolyNode->removeAllChildrenWithCleanup(true);
	}
}