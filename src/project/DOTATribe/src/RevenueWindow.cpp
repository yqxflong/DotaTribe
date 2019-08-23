// Name :		RevenueWindow.h
// Function:	点金窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/RevenueWindow.h"
#include "../include/EngineSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/UIViewDataManger.h"
#include "../include/RevenueDataHandler.h"
#include "../Include/CostRevenuePacket.h"
#include "../include/TimeSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/FrameAnimateDataManager.h"
#include "../include/AnimationFileDataManager.h"
#include "cocos-ext.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>
using  namespace  cocos2d;

#define  Revenue_Effect 2036
#define  Revenue_EffectSound 73

#define SlipWidth 317 
#define	SlipHeight 22
RevenueWindow::RevenueWindow()
{
	m_WindowType = _TYPED_WINDOW_REVENUE_;
	m_RevenueType= -1;
	m_lastTime = 0.0f;
	m_playEffect = false;
	IsNeedUpdata = true;
}
bool RevenueWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_REVENUEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_REVENUEWINDOW_, true);
	return IWindow::Init();
}
bool RevenueWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		InitLayer();
		return true;
	} 
	while (false);

	return false;
}
void RevenueWindow::Tick()
{
	CoolTimeTick();
	IWindow::Tick();
}
void RevenueWindow::Destroy()
{
	m_RevenueType= -1;
	m_lastTime = 0.0f;
	m_playEffect = false;
	IsNeedUpdata = true;
	IWindow::Destroy();
}
void RevenueWindow::InitLayer()
{
	_uckSetMarkLayerAndInitLayer();
	_uckInitButton();

}
void RevenueWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_REVENUEWINDOW_);	
}
void RevenueWindow::On_SingleClick(cocos2d::CCObject* pSender)
{
	NFC_showCommunicationWating(true);
	_uckSelectButton((CCMenuItemSprite*)pSender);
}
void RevenueWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_REVENUEWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_REVENUEWINDOW_)
	{
		PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
		Destroy();
	}
}
void RevenueWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	UpdateRevenueInfo();
	NFC_showCommunicationWating(false);
	if(m_pRootNode->isVisible())
		return;
	Show(true);
	NFC_Action_fallDown(m_MyRootLayer);
}
void RevenueWindow::UpdateRevenueInfo()
{
	_uckPlayEffect();
	_uckFreeTimesSign();
	_uckLv();
	_uckExp();
	_uckCoolTime();
	_uckButton();		
}
void RevenueWindow::CoolTimeTick()
{
	if (RevenueDataHandler::get_instance2()->m_coolTime >0)
	{
		float time =TimeSystem::get_instance2()->GetLastTickTime();
		m_lastTime += time;
		if (m_lastTime>1)
		{
			int second = (int)m_lastTime;
			m_lastTime -= second;
			RevenueDataHandler::get_instance2()->m_coolTime -= second; 
			UpdataCoolTime(RevenueDataHandler::get_instance2()->m_coolTime);
		}
	}
}
void RevenueWindow::UpdataCoolTime(int scened)
{
	CCLabelTTF* pLabel = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueCoolTime);
	char _time[128]="";
	sprintf(_time,SysLangDataManager::get_instance2()->GetSysLangById(145).c_str(),GetTimeString(scened).c_str());
	pLabel->setString(_time);
	if (RevenueDataHandler::get_instance2()->m_coolTime <= 0)
	{
		pLabel->setVisible(false);
		IsNeedUpdata = true;
		CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton1);
		CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		ptempItem->setEnabled(true);
	}
}
void RevenueWindow::PlaySceneFrameEffect(int sceneFrameEffectID)
{
	if(sceneFrameEffectID!=-1)
	{     
		cocos2d::CCSprite * pEffectNode=NULL;
		AnimationFileData *  pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(sceneFrameEffectID);
		cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimtionByName(pAnimationFileData->mAnimationName);
		if(pAnimation!=NULL)
		{
			pEffectNode=cocos2d::CCSprite::create();
			if(pEffectNode!=NULL)
			{     
				pEffectNode->setScale(pAnimationFileData->mAnimationScale);
				//设置相对坐标位置
				pEffectNode->setPositionX(cocos2d::CCDirector::sharedDirector()->getWinSize().width/2);
				pEffectNode->setPositionY(cocos2d::CCDirector::sharedDirector()->getWinSize().height/2);

				CCAnimationEffect   *  pAnimationEffect=CCAnimationEffect::create(pEffectNode,pAnimation,this);
				if(pAnimationEffect!=NULL)
				{ 
					m_pRootNode->addChild(pEffectNode);
					pEffectNode->runAction(pAnimationEffect);
				}			
			} 
		}
	} 
}
void RevenueWindow::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	if(eventType==_Animation_Effect_Finish_Event_)
	{
		animationNode->removeFromParentAndCleanup(true);
		animationNode = NULL;
		return ;
	}
}
string RevenueWindow::GetTimeString(int allsecond)
{
	std::string time;
	int hour;
	int minute;
	int second;
	hour = allsecond/3600;
	allsecond = allsecond -(3600*hour);
	minute = allsecond/60;
	allsecond = allsecond -(60*minute);
	second =allsecond;

	char hour_[128] = "";
	if (hour>9)
		sprintf(hour_,"%d:",hour);
	else
		sprintf(hour_,"0%d:",hour);

	char minute_[128] = "";
	if (minute>9)
		sprintf(minute_,"%d:",minute);
	else
		sprintf(minute_,"0%d:",minute);

	char second_[128] = "";
	if (second>9)
		sprintf(second_,"%d",second);
	else
		sprintf(second_,"0%d",second);

	char time_[128] = "";
	sprintf(time_,"%s%s%s",hour_,minute_,second_);

	time = time_;
	return time;
}
void RevenueWindow::_uckSetMarkLayerAndInitLayer()
{
	CCNode *pNode =m_pRootNode;
	CPriorityLayerColor* pBGLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),cocos2d::CCDirector::sharedDirector()->getWinSize().width,cocos2d::CCDirector::sharedDirector()->getWinSize().height,kPRIORITYLOW-5);
	pBGLayer->setAnchorPoint(CCPointZero);
	pBGLayer->setPosition(CCPointZero);
	pNode->addChild(pBGLayer);

	m_MyRootLayer = CCLayer::create();
	m_MyRootLayer->setAnchorPoint(ccp(0.5,0.5));
	pNode->addChild(m_MyRootLayer);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kREVENUEWINDOW,m_MyRootLayer);
}
void RevenueWindow::_uckInitButton()
{
	//初始化按钮
	CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueCloseButton);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(RevenueWindow::On_Close));

	ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton1);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(RevenueWindow::On_SingleClick));

	//ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton2);
	//ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	//ptempItem->setTarget(this,menu_selector(RevenueWindow::On_SingleClick));

	ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton3);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(RevenueWindow::On_SingleClick));
}
void RevenueWindow::_uckSelectButton(CCMenuItemSprite* pItem)
{
	int type;
	if (pItem->getParent()->getTag() == RevenueButton1)
		type = Revenue_Free_Type;
	//else if(pItem->getParent()->getTag() == RevenueButton2)
	//	type = Revenue_Low_Type;
	else if(pItem->getParent()->getTag() == RevenueButton3)
		type = Revenue_High_Type;

	C2SCostRevenuePacket crpacket(type,0);
	crpacket.Send();
	m_playEffect = true;
}
void RevenueWindow::_uckPlayEffect()
{
	//播放特效
	if (m_playEffect)
	{
		m_playEffect = false;
		PlaySceneFrameEffect(Revenue_Effect);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(Revenue_EffectSound)); 
	}
}
void RevenueWindow::_uckFreeTimesSign()
{
	//内部免费次数角标
	if (RevenueDataHandler::get_instance2()->m_FreeTimes > 0)
	{
		m_MyRootLayer->getChildByTag(RevenueButton1Icon)->setVisible(true);
		m_MyRootLayer->getChildByTag(RevenueButton1IconValue)->setVisible(true);
		char _times[128]="";
		sprintf(_times,"%d",RevenueDataHandler::get_instance2()->m_FreeTimes);
		CCLabelTTF* pLabel = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueButton1IconValue);
		pLabel->setString(_times);
		CCLabelTTF* pLabelTime = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueCoolTime);
		pLabelTime->setVisible(true);
	}
	else
	{
		m_MyRootLayer->getChildByTag(RevenueButton1Icon)->setVisible(false);
		m_MyRootLayer->getChildByTag(RevenueButton1IconValue)->setVisible(false);
		CCLabelTTF* pLabelTime = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueCoolTime);
		pLabelTime->setVisible(false);
	}
}
void RevenueWindow::_uckLv()
{
	//等级
	
	char _lv[128]="";
	sprintf(_lv,"Lv:%d",RevenueDataHandler::get_instance2()->m_Level);
	CCLabelTTF* pLabelLv = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueLv);
	pLabelLv->setString(_lv);
}
void RevenueWindow::_uckExp()
{
	//经验值
	char _expValue[128]="";
	sprintf(_expValue,"%d/%d",RevenueDataHandler::get_instance2()->m_Exp,RevenueDataHandler::get_instance2()->m_maxExp);
	CCLabelTTF* pLabelExp = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueExpValue);
	pLabelExp->setString(_expValue);

	//经验条
	CCSprite* pSprite = (CCSprite*)m_MyRootLayer->getChildByTag(RevenueExpSlip);
	pSprite->setTextureRect(CCRectMake(0,0.5,SlipWidth*(RevenueDataHandler::get_instance2()->m_Exp*1.0f/RevenueDataHandler::get_instance2()->m_maxExp),SlipHeight));

}
void RevenueWindow::_uckCoolTime()
{
	//冷却时间
	CCLabelTTF* pLabelTime = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueCoolTime);
	if(RevenueDataHandler::get_instance2()->m_coolTime >0&& RevenueDataHandler::get_instance2()->m_FreeTimes>0)
	{
		if (IsNeedUpdata)
		{
			char _time[128]="";
			sprintf(_time,SysLangDataManager::get_instance2()->GetSysLangById(145).c_str(),GetTimeString(RevenueDataHandler::get_instance2()->m_coolTime).c_str());
			pLabelTime->setString(_time);
			IsNeedUpdata = false;
		}
		pLabelTime->setVisible(true);
	}
	else
	{
		pLabelTime = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueCoolTime);
		pLabelTime->setVisible(false);
	}
}
void RevenueWindow::_uckButton()
{
	//高级野区消耗
	char _h_cost_Value[128]="";
	sprintf(_h_cost_Value,"%d",RevenueDataHandler::get_instance2()->m_highCost);
	CCLabelTTF* pLabelHight = (CCLabelTTF*)m_MyRootLayer->getChildByTag(RevenueButton3Cost);
	pLabelHight->setString(_h_cost_Value);
	pLabelHight->setVisible(true);
	CCSprite* pIconHigeht = (CCSprite*)m_MyRootLayer->getChildByTag(RevenueButton3Icon);
	pIconHigeht->setVisible(true);
	//高级野区按钮
	if (RevenueDataHandler::get_instance2()->m_highCost < 0)
	{
		CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton3);
		CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		ptempItem->setEnabled(false);
		pLabelHight->setVisible(false);
		pIconHigeht->setVisible(false);
	}


	//试试运气按钮
	if(RevenueDataHandler::get_instance2()->m_FreeTimes > 0)
	{
		if (RevenueDataHandler::get_instance2()->m_coolTime >0)
		{
			CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton1);
			CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
			ptempItem->setEnabled(false);
		}
		else
		{
			CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton1);
			CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
			ptempItem->setEnabled(true);
		}
	}
	else
	{
		CCMenu* ptemp = (CCMenu*)m_MyRootLayer->getChildByTag(RevenueButton1);
		CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
		ptempItem->setEnabled(false);
	}
}