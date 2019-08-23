//Name ; BossScoreWindow
//Function : boss积分
//Author : fangjun
//Date: 20140218


#ifndef _DOTATRIBE_BOSSSCORE_H_
#define _DOTATRIBE_BOSSSCORE_H_

#include "../include/IWindow.h"
#include <cocos2d.h>
#include <string>


class BossScoreWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
		cBg,
		cItem,
		cNameNum,
		cDestiction,
		cScore,
		cLingQuBtn,
		cLingQuBtnLabel,
	}CELL;

	enum{
		rGrey,
		rBg,
		rScoreRewardLabel,
		rScore,
		rScoreValue,
		rRank,
		rRankValue,
		rRankReward,
		rReward1,
		rReward2,
		rLingQuBtn,
		rLingQuBtnLabel,
		rLingQuTimeCount,
		rRewardDesc,
		rTable,
		rTableCell,
		rCloseBtn,
		rBgTitle,
		rLine,
		rMoreArrow,
		rMoreArrowMove,

	}REWARD;

	enum{
		bBg1,
		bBg2,
		bTitleBg,
		bTitle,
		bDesc,
		bTimeCount,
		bTimeValue,
		bSoldier1,
		bSoldier2,
		bSoldier3,
		bSoldier4,
		bBossBg,
		bBossIcon,
		bBossKuang,
		bBoard,
		bTopScore,
		bNowRank,
		bRankBtn,
		bRankBtnLabel,
		bScore,
		bHit1,
		bHit2,
		bHit3,
		bHit4,
		bHit5,
		bTotalScore,
		bChallengeBtn,
		bChallengeBtnLabel,
		bFreeTime,
		bCostTime,
		bRewardBtn,
		bRewardEffect,//宝箱按钮特效
		bCloseBtn,
		bRewardPanel,//奖励页面挂载点
	}PAGE;

private:
	cocos2d::CCNode * m_pRoot;
	cocos2d::CCNode * m_pRewardNode;

	cocos2d::CCSize m_sTableSize;

	cocos2d::CCLabelTTF * m_pPageTimer;
	cocos2d::CCLabelTTF * m_pRewardTimer;

	cocos2d::extension::CCTableView * m_pTableReward;
	bool							   m_bScrollEnd;

public:
	BossScoreWindow();
	virtual ~BossScoreWindow();

private:
	void _initLayout();
	void _mapBtn();
	void _setPage();

	void _showRewardPage();
	void _hideRewardPage();
	void _setRewardPage();

	//判断显示宝箱按钮的状态
	void CheckHaveFloorReward();
public:
	virtual    bool    Init();

	virtual    bool    Load();

	virtual    void    Tick();

	virtual    void    Destroy();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

public:
	void _createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell, int cellIdx);

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){		};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){		};

private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void On_Btn_Click(cocos2d::CCObject* pSender);

	void On_RewardBtn_Click(cocos2d::CCObject * pSender);
	void On_RewardCellBtn_Click(cocos2d::CCObject * pSender);

private:
	/*
		获取积分页面数据，设置界面
	*/
	void Function_EnterBossScore();

	/*
		获取排行榜页面数据，设置界面
	*/
	void Function_EnterRank();

	/*
		获取奖励界面数据，设置奖励信息
	*/
	void Function_EnterReward();

	/*
		领取奖励后的反馈
	*/
	void Function_GetRewardResult(char type, char index);

};


#endif
