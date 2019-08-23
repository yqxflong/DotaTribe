// Name ; ServantView.h
// Function：仆从系统
// Author : fangjun
// Date: 20131029

#ifndef _DOTATRIBE_SERVANTVIEW_H_
#define _DOTATRIBE_SERVANTVIEW_H_

#include "../include/SubView.h"

class ServantView : public SubView, cocos2d::extension::CCTableViewDataSource, cocos2d::extension::CCTableViewDelegate
{
	public:
	enum{
		_PAGE_TYPE_MASTER_0_ = 0,			//分页0
		_PAGE_TYPE_MASTER_1_,				//分页1
		_PAGE_TYPE_MASTER_2_,				//分页2
		_PAGE_TYPE_SLAVE_0_,				//分页3
		_PAGE_TYPE_SLAVE_1_,				//分页4
		_PAGE_TYPE_SLAVE_2_,				//分页5
	}PAGE;

private:
	enum{
		_TABLE_TYPE_ONE_ = 0,		//单一列表
		_TABLE_TYPE_LEFT_,			//左侧列表
		_TABLE_TYPE_RIGHT_,			//右侧列表
	}TABLE;

	enum{
		_MESSAGE_CATCH_FUNCTION_DOWN_ = 635,
		_MESSAGE_PLAY_FUNCTION_DOWN_ = 636,
		_MESSAGE_RESCUE_FUNCTION_DOWN_ = 637,
		_MESSAGE_REVOLT_FUNCTION_DOWN_ = 638,
		_MESSAGE_SOS_FUNCTION_DOWN_ = 639,
		_MESSAGE_IDENTITY_CHANGED_TO_SLAVE_ = 640,		//变成奴隶提示
		_MESSAGE_IDENTITI_CHANGED_TO_FREE_ = 655,		//变成自由人
	}MESSAGE_NOTIFY;

	//以下为界面定义，begin

	enum{
		newsTTF,
		newsLine,
	}NewsCell;

	enum{
		s2Cell0Bg = 0,
		s2Cell0Icon,
		s2Cell0Name,
		s2Cell0Level,
		s2Cell0Btl,
		s2Cell0BtlValue,
		s2Cell0HelpBtn,
		s2Cell0HelpLabel,
		s2Cell1Bg,
		s2Cell1Icon,
		s2Cell1Name,
		s2Cell1Level,
		s2Cell1Btl,
		s2Cell1BtlValue,
		s2Cell1HelpBtn,
		s2Cell1HelpLabel,
	}SlavePageSOSCell;

	enum{
		s2vline = 0,
		s2Table,
		s2Cell,
		s2NoTips,
	}SlavePageSOS;

	enum{
		s1MyOwnerTitleBg = 0,
		s1MyOwnerTitle,
		s1OwnerBg,
		s1OwnerIcon,
		s1OwnerName,
		s1OwnerLevel,
		s1PlayBtn,
		s1PlayLabel,
		s1vline,
		s1Table,
		s1Cell,
	}SlavePagePlay;

	enum{
		s0RevoltTitleBg = 0,
		s0RevoltTitle,
		s0OwnerBg,
		s0OwnerIcon,
		s0OwnerName,
		s0OwnerLevel,
		s0OwnerBtl,
		s0OwnerBtlValue,
		s0RevoltBtn,
		s0RevoltLabel,
		s0BegHelp,
		s0vLine,
		s0BribeTitleBg,
		s0BribeTitle,
		s0NpcBg,
		s0NpcIcon,
		s0NpcName,
		s0NpcPrice,
		s0NpcPriceValue,
		s0NpcPriceGold,
		s0BribeBtn,
		s0BribeLabel,
	}SlavePageRevolt;

	enum{
		m2Cell0Bg = 0,
		m2Cell0Icon,
		m2Cell0Name,
		m2Cell0MasterNameLabel,
		m2Cell0MasterName,
		m2Cell0MasterBtl,
		m2Cell0MasterBtlValue,
		m2Cell0RescueBtn,
		m2Cell0RescueLabel,
		m2Cell1Bg,
		m2Cell1Icon,
		m2Cell1Name,
		m2Cell1MasterNameLabel,
		m2Cell1MasterName,
		m2Cell1MasterBtl,
		m2Cell1MasterBtlValue,
		m2Cell1RescueBtn,
		m2Cell1RescueLabel,
	}MasterPageRescueCell;

	enum{
		m2TipLabel = 0,
		m2VLine,
		m2Table,
		m2Cell,
		m2NoTips,
	}MasterPageResuce;

	enum{
		m1Slave0Bg = 0,
		m1Slave0Icon,
		m1Slave0Name,
		m1Slave0Level,
		m1Slave0WorkTime,
		m1Slave0WorkTimesValue,
		m1Slave0Exp,
		m1Slave0ExpValue,
		m1Slave0ChainBtn,
		m1Slave0ChainLabel,
		m1Slave0PressBtn,
		m1Slave0PressLabel,
		m1Slave0ReleaseBtn,
		m1Slave0ReleaseLabel,
		m1Slave0CatchBtn,
		m1Slave1Bg,
		m1Slave1Icon,
		m1Slave1Name,
		m1Slave1Level,
		m1Slave1WorkTime,
		m1Slave1WorkTimesValue,
		m1Slave1Exp,
		m1Slave1ExpValue,
		m1Slave1ChainBtn,
		m1Slave1ChainLabel,
		m1Slave1PressBtn,
		m1Slave1PressLabel,
		m1Slave1ReleaseBtn,
		m1Slave1ReleaseLabel,
		m1Slave1CatchBtn,
		m1Slave2Bg,
		m1Slave2Icon,
		m1Slave2Name,
		m1Slave2Level,
		m1Slave2WorkTime,
		m1Slave2WorkTimesValue,
		m1Slave2Exp,
		m1Slave2ExpValue,
		m1Slave2ChainBtn,
		m1Slave2ChainLabel,
		m1Slave2PressBtn,
		m1Slave2PressLabel,
		m1Slave2ReleaseBtn,
		m1Slave2ReleaseLabel,
		m1Slave2CatchBtn,
		m1VLine,
		m1Table,
		m1Cell,

	}MasterPagePlay;

	enum{
		mc0Bg = 0,
		mc0Icon,
		mc0Name,
		mc0Level,
		mc0Idt,
		mc0IdtValue,
		mc0CatchBtn,
		mc0CatchBtnLabel,
	}MasterPageCatchCell;
	enum{
		m0WinBg = 0,
		m0LossBg,
		m0WinLabel,
		m0LossLabel,
		m0VLine,
		m0TableView0,//左侧tabelview
		m0Cell0,
		m0TableView1,//右侧tabelview
		m0Cell1,
		m0LeftNoTips,
		m0RightNoTips,
	}MasterPageCatch;

	enum{
		mBg = 0,
		mPage0Label,
		mPage0Btn,
		mPage1Label,
		mPage1Btn,
		mPage2Label,
		mPage2Btn,
		mLeftTimesTTF,
		mLeftTimesValue,
		mLeftTimesBg,
		mViewNode,
	}MainPage;
	//end	

	cocos2d::CCNode* m_pRoot;//窗口根节点
	cocos2d::CCNode * m_pViewRoot;//挂载子页面的节点

	cocos2d::extension::CCTableView * m_pTable;			//单列表时使用
	cocos2d::extension::CCTableView * m_pLeftTable;		//双列表时，左侧列表
	cocos2d::extension::CCTableView * m_pRightTable;	//双列表时，右侧列表

	cocos2d::CCSize m_szCELL;			//单列表时，cell尺寸
	cocos2d::CCSize m_szCELLLeft;		//双列表时，左侧cell尺寸
	cocos2d::CCSize m_szCELLRight;		//双列表时，右侧cell尺寸

	cocos2d::CCMenuItemSprite * m_pSelectSubPage;//选择的分面按钮，方便取消上次选中
	int m_iPageType;		//页面内容种类//从PAGE枚举中

public:
	ServantView();
	virtual ~ServantView();

private:
	inline void _initLayout();
	inline void _mapMainPage();
	inline void _initDefaultPage();
	inline void _setSelectPageTab();//显示选择的页标签
	inline void _showViewPage();//显示下方页面，每次切换均从此方法切换底部页面
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell, int tableType);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx, int tableType);

	//显示和标定按钮
	inline void _showMasterCatchPage(cocos2d::CCNode * parent);
	inline void _showMasterPlayPage(cocos2d::CCNode * parent);
	inline void _showMasterRescuePage(cocos2d::CCNode * parent);
	inline void _showSlaveRevoltPage(cocos2d::CCNode * parent);
	inline void _showSlavePlayPage(cocos2d::CCNode * parent);
	inline void _showSlaveSOSPage(cocos2d::CCNode * parent);
	//设置内容
	inline void _setMasterCatchPage();
	inline void _setMasterPlayPage();
	inline void _setMasterRescuePage();
	inline void _setSlaveRevoltPage();
	inline void _setSlavePlayPage();
	inline void _setSlaveSOSPage();

	//请求对应界面需要的数据
	inline void _requestShowPageData();

public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();

private:
	/*
		奴隶工作
	*/
	void SlaveWorkTick();

	/*
		调戏冷却
	*/
	void CatchCdTick();
public:
	/*
	消息事件响应处理
	*/

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private:
	/*
	show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	//战斗归来时显示对应的界面
	void AthleticBackShow();

public:
	//主界面按钮操作
	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶主抓捕操作
	void On_MasterCatchPage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶主互动界面操作
	void On_MasterPlayPage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶主解救界面操作
	void On_MasterRescuePage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶反抗界面操作
	void On_SlaveRevoltPage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶互动界面操作
	void On_SlavePlayPage_Btn_Click(cocos2d::CCObject * pSender);

	//奴隶求救界面操作
	void On_SlaveSOSPage_Btn_Click(cocos2d::CCObject * pSender);

public:
	//获得进入抓捕奴隶数据
	void Function_GetMasterEnterCatchData();

	//获得进入和奴隶互动页面数据
	void Function_GetMasterEnterPlayData();
	void Function_GetMasterPlaySuccess();

	//获得奴隶主新闻推送
	void Function_GetMasterNews();

	//获得进入解救页面数据
	void Function_GetMasterEnterResceuData();

	//获得进入反抗页面数据
	void Function_GetSlaveEnterRevoltData();
	
	//获得奴隶贿赂成功消息
	void Function_GetSlaveBribeSuccess();

	//获得进入和奴隶主互动页面数据
	void Function_GetSlaveEnterPlayData();
	void Function_GetSlavePlaySuccess();

	//获得奴隶新闻推送
	void Function_GetSlaveNews();

	//获得进入求救页面数据
	void Function_GetSlaveEnterSOSData();

	//身份切换，请求响应数据并切换界面
	void Function_ConfirmIdentityChanged();

	//获得身份切换
	void Function_IdentityChanged(std::list<std::string> & paramList);

	//大窗口的关闭回调
	void Function_OnClose();



};


#endif