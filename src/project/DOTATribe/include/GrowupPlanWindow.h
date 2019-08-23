//Name: GrowupPlanWindow
//Author: lvyunlong
//Func: Activity of growup plan window
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_GROWUPPLANWINDOW_H_
#define  _DOTATRIBE_GROWUPPLANWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ActivityDataHandler.h"

class GrowupPlanWindow : public IWindow 	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
			udBG = 0,
			udBG1,
			udTABLE,
			udTABLECELL,
			udRECHGEBTN,
			udRECHGETTF,
			udBUYBTN,
			udBUYTTF,
		};

	enum{
		_PLAN_CELLBG,
		_PLAN_LEVELGROWTTF,
		_PLAN_REACHLEVELTTF,
		_PLAN_GETMONEYTTF,
		_PLAN_DTREWARD,
		_PLAN_GETBTN,
		_PLAN_GETTFF,
		_PLAN_EFFECTBTN,
		}CELL;
private:
	int m_CurWindowActiviId;
public:
	GrowupPlanWindow();
	virtual ~GrowupPlanWindow();
public:
	cocos2d::extension::CCTableView* m_pTableAttachment;    //CCTableView控件
	cocos2d::CCSize m_szCellGift;	//附件大小
	std::string strGrowlevel;
	std::string strReachlevel;
	std::string strMoneynum;

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _initCell();
	inline void _mapBtn();
	void _initStr();
	inline void _mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setTableView(); //设置TableView
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		显示成长计划事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏成长计划事件处理
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新成长计划事件处理
	*/
	inline void  OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新成长计划按钮事件处理
	*/
	inline void  OnUpdateBtnWindowEventHandler(std::list<std::string>& paramList);
private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	void On_Click_RechgeBtn_Event(cocos2d::CCObject* pSender);
	void On_Click_BuyPlan_Event(cocos2d::CCObject* pSender);
	void On_Click_GetReward_Event(cocos2d::CCObject* pSender);
	//物品TIPS
	void On_Click_Reward_Tips_Event(cocos2d::CCObject* pSender);
};


#endif