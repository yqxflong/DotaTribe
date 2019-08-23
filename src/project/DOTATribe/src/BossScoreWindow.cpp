//Name ; BossScoreWindow
//Function : boss积分
//Author : fangjun
//Date: 20140218

#include "../include/BossScoreWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/DTAwardBoard.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/RankWindow.h"
#include "../include/TimeSystem.h"
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>


BossScoreWindow::BossScoreWindow()
:m_pRoot(NULL)
,m_pRewardNode(NULL)
,m_pPageTimer(NULL)
,m_pRewardTimer(NULL)
,m_pTableReward(NULL)
,m_bScrollEnd(false)
{
	m_WindowType = _TYPED_WINDOW_BOSSSCORE_;
	m_bModelWindow = false;
}
BossScoreWindow::~BossScoreWindow()
{
	m_pRoot = NULL;
	m_pRewardNode = NULL;
	m_pPageTimer = NULL;
	m_pRewardTimer = NULL;
	m_pTableReward = NULL;
}

void BossScoreWindow::_initLayout()
{
	m_pRoot= m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBOSSSCOREWINDOW, m_pRoot);

	_mapBtn();

	m_pRewardNode = (CCNode *)m_pRoot->getChildByTag(bRewardPanel);
	m_pPageTimer = (CCLabelTTF *)m_pRoot->getChildByTag(bTimeValue);

	CheckHaveFloorReward();
}

void BossScoreWindow::_mapBtn()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	menu = (CCMenu *)m_pRoot->getChildByTag(bCloseBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bCloseBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(bRewardBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bRewardBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(bRankBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bRankBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(bChallengeBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bChallengeBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_Btn_Click));

}

void BossScoreWindow::_setPage()
{
	BSBossScoreData * data = BOSSSCOREDATAHANDLER->m_pBossScoreData;
	if(!data)
		return;

	//说明
	NFC_setLabelString(bDesc, m_pRoot, data->description, true);
	//剩余活动时间
	if(data->status > 0)//活动进行中
		NFC_setLabelString(bTimeCount, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(2061), true);
	else
		NFC_setLabelString(bTimeCount, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(2062), true);
	//倒计时
	if(data->status < 1)
	{//活动关闭状态，挑战按钮不可用
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(bChallengeBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(bChallengeBtn);
		item->setEnabled(false);
		
		//隐藏挑战按钮
		NFC_showNode(bChallengeBtn, m_pRoot, false);
		NFC_showNode(bChallengeBtnLabel, m_pRoot, false);
	}
	else
	{
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(bChallengeBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(bChallengeBtn);
		item->setEnabled(true);

		//显示挑战按钮
		NFC_showNode(bChallengeBtn, m_pRoot, true);
		NFC_showNode(bChallengeBtnLabel, m_pRoot, true);
	}
	//战士
	DTAwardBoard * dtab = NULL;
	for(unsigned int i = 0; i < data->bossVector.size() - 1; ++i)
	{
		dtab = (DTAwardBoard *)m_pRoot->getChildByTag(bSoldier1 + i);
		dtab->ChangeObject(data->bossVector[i]->quality, data->bossVector[i]->iconId, 1);
		dtab->setVisible(true);
		dtab->setContentScale((float)CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
		dtab->setEnabled(false);
	}
	for(unsigned int i = data->bossVector.size(); i < 4; ++i)
	{
		dtab = (DTAwardBoard *)m_pRoot->getChildByTag(bSoldier1 + i);
		dtab->setVisible(false);
	}
	//BOSS
	NFC_setPicForCCSprite(bBossIcon, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(data->bossVector[data->bossVector.size() - 1]->iconId), true);
	NFC_setPicScale(bBossIcon, m_pRoot, 1.1f);
	//评分
	char temp[512] = "";
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2070).c_str(), data->maxScore);
	NFC_setLabelString(bTopScore, m_pRoot, temp, true);
	//排名
	std::string rank = SysLangDataManager::get_instance2()->GetSysLangById(2071);
	if(data->rank > 0)
	{
		sprintf(temp, "%d", data->rank);
		rank.append(temp);
	}
	else
	{
		rank.append(SysLangDataManager::get_instance2()->GetSysLangById(2072));
	}
	NFC_setLabelString(bNowRank, m_pRoot, rank, true);
	//战斗评分
	int total = 0;
	for(unsigned int i = 0; i < data->scoreVector.size(); ++i)
	{
		total += data->scoreVector[i];
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2068).c_str(), data->nameVector[i].c_str(), data->scoreVector[i]);
		NFC_setLabelString(bHit1 + i, m_pRoot, temp, true);
	}
	for(unsigned int i = data->scoreVector.size(); i < 5; ++i)
	{
		NFC_showNode(bHit1 + i, m_pRoot, false);
	}
	//总评分
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2069).c_str(), total);
	NFC_setLabelString(bTotalScore, m_pRoot, temp, true);
	//挑战次数
	if(data->status < 1)
	{
		NFC_showNode(bCostTime, m_pRoot, false);
		NFC_showNode(bFreeTime, m_pRoot, false);
	}
	else
	{
		if(data->leftFreeTimes > 0)
		{
			NFC_showNode(bCostTime, m_pRoot, false);
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2065).c_str(), data->leftFreeTimes);
			NFC_setLabelString(bFreeTime, m_pRoot, temp, true);
		}
		else
		{
			NFC_showNode(bFreeTime, m_pRoot, false);
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2066).c_str(), data->leftChallengeItemCount, data->challengePrice);
			NFC_setLabelString(bCostTime, m_pRoot, temp, true);
		}
	}



	//宝箱奖励特效
	CheckHaveFloorReward();

}

void BossScoreWindow::_showRewardPage()
{
	if(!m_pRewardNode)
		return;

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::KBOSSSCOREREWARDWINDOW, m_pRewardNode);

	m_pRewardTimer = (CCLabelTTF *)m_pRewardNode->getChildByTag(rLingQuTimeCount);

	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	menu = (CCMenu *)m_pRewardNode->getChildByTag(rCloseBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(rCloseBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_RewardBtn_Click));

	menu = (CCMenu *)m_pRewardNode->getChildByTag(rLingQuBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(rLingQuBtn);
	item->setTarget(this, menu_selector(BossScoreWindow::On_RewardBtn_Click));

	DTAwardBoard * dtab = NULL;

	dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward1);
	dtab->setTag(rReward1);
	dtab->setTarget(this, menu_selector(BossScoreWindow::On_RewardBtn_Click));
	
	dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward2);
	dtab->setTag(rReward2);
	dtab->setTarget(this, menu_selector(BossScoreWindow::On_RewardBtn_Click));

}

void BossScoreWindow::_hideRewardPage()
{
	if(!m_pRewardNode)
		return;

	m_pRewardNode->removeAllChildrenWithCleanup(true);

	m_pRewardTimer = NULL;
}

void BossScoreWindow::_setRewardPage()
{
	//设置左侧奖励列表
	CCNode * node = m_pRewardNode->getChildByTag(rTableCell);
	m_sTableSize = node->getContentSize();


	m_pTableReward =(CCTableView*)m_pRewardNode->getChildByTag(rTable);
	m_pTableReward->setDataSource(this);
	m_pTableReward->setDelegate(this);
	m_pTableReward->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);//竖向
	m_pTableReward->setTouchEnabled(true);
	m_pTableReward->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTableReward);

	//设置右侧排名奖励信息
	BSRewardData * data = BOSSSCOREDATAHANDLER->m_pRewardData;
	char temp[512] = "";
	//最高评分
	sprintf(temp, "%d", data->maxScore);
	NFC_setLabelString(rScoreValue, m_pRewardNode, temp, true);
	//排名
	if(data->rank > 0)
		sprintf(temp, "%d", data->rank);
	else
		sprintf(temp, "%s", SysLangDataManager::get_instance2()->GetSysLangById(2072).c_str());
	NFC_setLabelString(rRankValue, m_pRewardNode, temp, true);
	//倒计时
	
	if(data->leftDrawSeconds == 0)
	{//可领取
		CCMenu * menu = (CCMenu *)m_pRewardNode->getChildByTag(rLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rLingQuBtn);
		item->setEnabled(true);
		NFC_showNode(rLingQuTimeCount, m_pRewardNode, false);
	}
	else if(data->leftDrawSeconds > 0)
	{//不可领取
		CCMenu * menu = (CCMenu *)m_pRewardNode->getChildByTag(rLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rLingQuBtn);
		item->setEnabled(false);
		NFC_showNode(rLingQuTimeCount, m_pRewardNode, true);
	}
	else
	{//没有奖励，将排名奖励隐藏
		for(int i = rReward1; i <= rRewardDesc; ++i)
		{
			NFC_showNode(i, m_pRewardNode, false);
		}
	}

	BSRankRewardItem * reward = NULL;
	DTAwardBoard * dtab = NULL;
	//奖励物品
	for(unsigned int i = 0; i < data->rankRewardVector.size(); ++i)
	{
		dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward1 + i);
		dtab->setVisible(true);
		reward = data->rankRewardVector[i];

		if(reward->type == kDT_AWARD_OBJECT)
		{//物品
			dtab->ChangeObject(reward->quality, reward->iconId, reward->count);
			dtab->setEnabled(true);
			dtab->setIDX(reward->templateId);
		}
		else if(reward->type == kDT_AWARD_MONEY)
		{//金钱
			dtab->ChangeObject(_GOLD_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD), reward->count);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
		}
		else if(reward->type == kDT_AWARD_EXP)
		{//经验
			dtab->ChangeObject(_EXP_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP), reward->count);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
		}
		else if(reward->type == kDT_AWARD_DIAMOND)
		{//钻石
			dtab->ChangeObject(_DIAMOND_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND), reward->count);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
		}
		else if(reward->type == kDT_AWARD_PRESTIGE)
		{//声望
			dtab->ChangeObject(_PREGIST_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE), reward->count);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
		}
		else if(reward->type == kDT_AWARD_POWER)
		{//体力
			dtab->ChangeObject(_POWER_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG), reward->count);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
		}
	}
	for(unsigned int i = data->rankRewardVector.size(); i < 2; ++i)
	{
		dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward1 + i);
		dtab->setVisible(false);
	}

	if(data->leftDrawSeconds < 0)
	{//显示奖励框为空白
		for(unsigned int i = 0; i < 2; ++i)
		{
			dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward1 + i);
			dtab->setVisible(true);
			dtab->ChangeObject();
		}
	}
}

void BossScoreWindow::CheckHaveFloorReward()
{
	bool b = false;

	if(BOSSSCOREDATAHANDLER->m_pBossScoreData)
		BOSSSCOREDATAHANDLER->m_pBossScoreData->hasReward > 0 ? b = true : b = false;

	NFC_showNode(bRewardEffect, m_pRoot, b);
}

bool    BossScoreWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_BOSSSCOREWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_BOSSSCOREWINDOW_, true);

	RegisterEvent(_TYPED_EVENT_BOSS_ENTER_GETDATA_, true);		//注册进入boss信息返回
	RegisterEvent(_TYPED_EVENT_BOSS_RANK_GETDATA_, true);		//注册进入排行榜信息返回
	RegisterEvent(_TYPED_EVENT_BOSS_REWARD_GETDATA_, true);		//注册进入奖励信息返回
	RegisterEvent(_TYPED_EVENT_BOSS_LINGQU_GETDATA_, true);		//注册领取奖励信息返回

	return IWindow::Init();
}

bool    BossScoreWindow::Load()
{
	if(!IWindow::Load())
		return false;

	_initLayout();

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_, _to_event_param_(_TYPED_WINDOW_BOSSSCORE_));

	return true;
}

void   BossScoreWindow::Tick()
{
	char temp[512] = {0};

	//主界面显示计时
	if(m_pPageTimer)
	{
		BSBossScoreData * data = BOSSSCOREDATAHANDLER->m_pBossScoreData;
		if(data && data->leftSeconds >= 0)
		{
			long long now = TimeSystem::get_instance2()->GetCurrentMicroSecond();
			long long during = now - data->tickBeginTime;
			int seconds = (int)(during / 1000000);
			if(seconds >= 1)
			{
				data->tickBeginTime = now;
				data->leftSeconds -= seconds;
				if(data->leftSeconds >= 0)
				{
					sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2063).c_str(), data->leftSeconds / 3600, (data->leftSeconds % 3600) / 60, (data->leftSeconds % 3600) % 60);
					NFC_setLabelString(m_pPageTimer, temp);
				}
				if(data->leftSeconds <= 0)
				{
					BOSSSCOREDATAHANDLER->ToServerEnterBoss();
				}
			}
		}
	}

	//奖励界面计时
	if(m_pRewardTimer)
	{
		BSRewardData * data = BOSSSCOREDATAHANDLER->m_pRewardData;
		if(data && data->leftDrawSeconds > 0)
		{
			long long now = TimeSystem::get_instance2()->GetCurrentMicroSecond();
			long long during = now - data->tickBeginTime;
			int seconds = (int)(during / 1000000);
			if(seconds >= 1)
			{
				data->tickBeginTime = now;
				data->leftDrawSeconds -= seconds;
				if(data->leftDrawSeconds >= 0)
				{
					sprintf(temp, "%02d:%02d:%02d", data->leftDrawSeconds / 3600, (data->leftDrawSeconds % 3600) / 60, (data->leftDrawSeconds % 3600) % 60);
					NFC_setLabelString(m_pRewardTimer, temp);
				}
				if(data->leftDrawSeconds <= 0)
				{
					BOSSSCOREDATAHANDLER->ToServerEnterReward();
				}
			}
		}
	}
	IWindow::Tick();
}

void    BossScoreWindow::Destroy()
{
	PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	m_pPageTimer = NULL;
	m_pRewardTimer = NULL;
	m_pTableReward = NULL;

	IWindow::Destroy();
}

void BossScoreWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_BOSSSCOREWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_BOSSSCOREWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_FADEOUT_BOSSSCOREWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_BOSS_ENTER_GETDATA_)
	{
		Function_EnterBossScore();
	}
	else if(iEventType == _TYPED_EVENT_BOSS_RANK_GETDATA_)
	{
		Function_EnterRank();
	}
	else if(iEventType == _TYPED_EVENT_BOSS_REWARD_GETDATA_)
	{
		Function_EnterReward();
	}
	else if(iEventType == _TYPED_EVENT_BOSS_LINGQU_GETDATA_)
	{
		std::string first = *(paramList.begin());
		std::string second = *(++paramList.begin());
		int type = atoi(first.c_str());
		int index = atoi(second.c_str());

		Function_GetRewardResult((char)type, (char)index);
	}
}


void BossScoreWindow::On_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == bCloseBtn)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_BOSSSCOREWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if(tag == bChallengeBtn)
	{
		BOSSSCOREDATAHANDLER->ToServerChallenge();
	}
	else if(tag == bRankBtn)
	{
		//请求排行榜数据
		BOSSSCOREDATAHANDLER->ToServerEnterRank();
	}
	else if(tag == bRewardBtn)
	{
		//显示排行榜页面

		//请求数据
		BOSSSCOREDATAHANDLER->ToServerEnterReward();
		_showRewardPage();
	}

}


void BossScoreWindow::On_RewardBtn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == rCloseBtn)
	{//关闭窗口
		_hideRewardPage();
	}
	else if(tag == rLingQuBtn)
	{//领取排名奖励
		BOSSSCOREDATAHANDLER->ToServerGetReward(1, 0);
	}
	else if(tag == rReward1 || tag == rReward2)
	{//奖励tips
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(item->getIDX(), _TYPED_WINDOW_BOSSSCORE_);
	}
}


void BossScoreWindow::On_RewardCellBtn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == cLingQuBtn)
	{
		int index = item->getIDX();

		BOSSSCOREDATAHANDLER->ToServerGetReward(0, (char)index);
	}
	else if(tag == cItem)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(item->getIDX(), _TYPED_WINDOW_BOSSSCORE_);
	}


}

void BossScoreWindow::_createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell)
{
	if(cell)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBOSSSCOREREWARDCELL, cell);

		CCMenu * menu = (CCMenu *)cell->getChildByTag(cLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(cLingQuBtn);
		item->setTarget(this, menu_selector(BossScoreWindow::On_RewardCellBtn_Click));

		DTAwardBoard * dtab = (DTAwardBoard *)cell->getChildByTag(cItem);
		dtab->setTag(cItem);
		dtab->setTarget(this, menu_selector(BossScoreWindow::On_RewardCellBtn_Click));
	}
}

void BossScoreWindow::_setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell, int cellIdx)
{
	if(cell)
	{
		if(!BOSSSCOREDATAHANDLER->m_pRewardData)
			return;
		BSScoreRewardItem * reward = BOSSSCOREDATAHANDLER->m_pRewardData->scoreRewardVector[cellIdx];
		if(!reward)
			return;

		char temp[512] = "";
		//物品
		DTAwardBoard * dtab = (DTAwardBoard *)cell->getChildByTag(cItem);
		dtab->setIDX(reward->templateId);
		if(reward->type == kDT_AWARD_OBJECT)
		{//物品
			dtab->ChangeObject(reward->quality, reward->iconId, 1);
			dtab->setEnabled(true);
		}
		else if(reward->type == kDT_AWARD_MONEY)
		{//金钱
			dtab->ChangeObject(_GOLD_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD), 1);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
		}
		else if(reward->type == kDT_AWARD_EXP)
		{//经验
			dtab->ChangeObject(_EXP_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP), 1);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
		}
		else if(reward->type == kDT_AWARD_DIAMOND)
		{//钻石
			dtab->ChangeObject(_DIAMOND_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND), 1);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
		}
		else if(reward->type == kDT_AWARD_PRESTIGE)
		{//声望
			dtab->ChangeObject(_PREGIST_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE), 1);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
		}
		else if(reward->type == kDT_AWARD_POWER)
		{//体力
			dtab->ChangeObject(_POWER_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG), 1);
			dtab->setEnabled(false);
			reward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
		}
		//物品名,数量
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(7008).c_str(), reward->name.c_str(), reward->count);
		NFC_setLabelString(cNameNum, cell, temp);
		//目标积分
		if(BOSSSCOREDATAHANDLER->m_pRewardData->maxScore >= reward->minScore)
		{
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2073).c_str(), BOSSSCOREDATAHANDLER->m_pRewardData->maxScore, reward->minScore);
		}
		else
		{
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2074).c_str(), BOSSSCOREDATAHANDLER->m_pRewardData->maxScore, reward->minScore);
		}
		NFC_setLabelString(cScore, cell, temp, true);
		//按钮状态
		CCMenu * menu = (CCMenu *)cell->getChildByTag(cLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(cLingQuBtn);
		if(reward->status == 0)
		{//已领取
			NFC_setLabelString(cLingQuBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2014), true);
			item->setEnabled(false);
		}
		else if(reward->status == 1)
		{//可领取
			NFC_setLabelString(cLingQuBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2010), true);
			item->setEnabled(true);
			item->setIDX(reward->index);
		}
		else if(reward->status == 2)
		{//不可领取
			NFC_setLabelString(cLingQuBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2015), true);
			item->setEnabled(false);
		}

	}
}

void BossScoreWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	if(m_pTableReward)
	{ 
		if(!m_pTableReward->cellAtIndex(BOSSSCOREDATAHANDLER->m_pRewardData->scoreRewardVector.size()-1))
		{
			if(m_bScrollEnd)
			{
				m_bScrollEnd=false;
				//显示
				NFC_setNodeVisable(rMoreArrowMove,m_pRewardNode,true);
				NFC_setNodeVisable(rMoreArrow,m_pRewardNode,false);				
				//((CCGrapSprite *)m_pViewRoot->getChildByTag(_ARENAREWARD_GROW_TAG_))->setGrapTexture(false);
			}
		}
		else
		{ 
			if(!m_bScrollEnd)
			{
				m_bScrollEnd=true;
				//置灰
				NFC_setNodeVisable(rMoreArrowMove,m_pRewardNode,false);
				NFC_setNodeVisable(rMoreArrow,m_pRewardNode,true);	
				//((CCGrapSprite *)m_pViewRoot->getChildByTag(_ARENAREWARD_GROW_TAG_))->setGrapTexture(true);
			} 
		}
	} 
}

cocos2d::CCSize BossScoreWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_sTableSize;
}

cocos2d::extension::CCTableViewCell* BossScoreWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(table, cell);
	}

	_setTableCell(table, cell, idx);

	return cell;
}

unsigned int BossScoreWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(!BOSSSCOREDATAHANDLER->m_pRewardData)
		return 0;
	
	return BOSSSCOREDATAHANDLER->m_pRewardData->scoreRewardVector.size();

}

void BossScoreWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	BOSSSCOREDATAHANDLER->ToServerEnterBoss();
}

void BossScoreWindow::Function_EnterBossScore()
{
	_setPage();
}

void BossScoreWindow::Function_EnterRank()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_RANKWINDOW_, _to_event_param_(RankWindow::_RANK_TYPE_BOSS_));
}

void BossScoreWindow::Function_EnterReward()
{
	_setRewardPage();
}

void BossScoreWindow::Function_GetRewardResult(char type, char index)
{
	//判断类型
	if(type == 0)
	{
		//日常奖励
		cocos2d::extension::CCTableViewCell * cell = m_pTableReward->cellAtIndex(index);
		if(cell)
		{
			CCMenu * menu = (CCMenu *)cell->getChildByTag(cLingQuBtn);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(cLingQuBtn);
			item->setEnabled(false);
			NFC_setLabelString(cLingQuBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2014), true);
		}
	}
	else
	{
		//终身奖励
		BOSSSCOREDATAHANDLER->ToServerEnterReward();
	}

	//检查是否有未领取的层级奖励
	CheckHaveFloorReward();
}

