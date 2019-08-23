//Name ; TeamBattleWindow
//Function：组队副本窗口
//Author : fangjun
//Date: 20130918

#ifndef  _DOTATRIBE_TEAMBATTLEWINDOW_H_
#define  _DOTATRIBE_TEAMBATTLEWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/MaskNode.h"

class TeamBattleWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
		tBg = 0,
		tBoardBg,
		tCloseBtn,
		tHelpBtn,
		tTodayTimes,
		tShopBtn,
		tShopBtnLabel,
		tLeftArrow,
		tRightArrow,
		tLeftMOVEArrow,
		tRightMOVEArrow,
		tClearTips,
		tReward1,
		tReward2,
		tReward3,
		tReward4,
		tStartBtn,//开始或者继续按钮
		tStartBtnLabel,
		tStartArrow,
		tResetBtn,
		tResetBtnLabel,
		tCostTips,
		tGateTableView,
		tGateTableCell,
		tGateRewardNode,//通关奖励挂载点
		tGateSelectFile,//副本选中亮框
	}Gate;

	enum{
		cBg,
		cGatePic,
		cGatePicGrey,
		cNameBg,
		cName,
		cPeople,
		cProgress,
		cNeedLevel,
		cPREPASSBG,
		cPREPASSTTF,
	}Cell;

	enum{
		rGreyColor,		//灰层
		rBg,			//背景
		rDescription,	//说明
		rTimeCount,		//倒计时时间
		rTongTTFBg,		//铜宝箱字背景
		rTongTTF,		//铜宝箱字
		rTongPic,		//铜宝箱图
		rTongSelectPic,	//选中框
		rTongPrice,		//铜宝箱价格
		rYingTTFBg,		//银宝箱字背景
		rYingTTF,		//银宝箱字
		rYingPic,		//银宝箱图
		rYingSelectPic,	//选中框
		rYingPrice,		//银质宝箱花费钻石数
		rYingJewelPic,	//钻石图
		rJinTTFBg,		//金宝箱字背景
		rJinTTF,		//金宝箱字
		rJinPic,		//金宝箱图
		rJinSelectPic,	//选中框
		rNeedVipBG,		//需要vip
		rNeedVip,		//需要vip值
		rJinPrice,		//银质宝箱花费钻石数
		rJinJewelPic,	//钻石图
	}GateReward;

	cocos2d::CCNode* m_pRoot;//窗口根节点
	cocos2d::extension::CCTableView* m_pTable;
	cocos2d::CCSize m_szCELL;

	bool bGateRewardTick;	//关卡奖励的tick
	int iGateRewardTimeCount;//用于关卡通关奖励

	int iselectgateidx;//当前页面选中的，不用来存储

	std::string gate_normal_board;
	std::string gate_select_board;

	char m_iSelectTongGuanJiangLiType;//选择的通关奖励类型

	MaskNode * m_gateRewardNode;
public:
	TeamBattleWindow();
	virtual ~TeamBattleWindow();

private:
	inline void _checkNewFunc();
	inline void _initLayout();
	inline void _mapLayout();
	inline void _setTableView();
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);

	inline void _refreshRight(int gateIdx);
	inline void _setTTFText(int key, const char * text);
	inline void _setTTFText(int key, int text);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char *  picpath);

	inline void _showGateRewardPage();
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

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

	//通关奖励界面弹出及自动点击释放
	void TickGateReward();

private:
	/*
	show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
// 
// 	/*
// 	服务器Data事件处理
// 	*/
// 	void OnTeamBattleEventHandler(std::list<std::string>& paramList);

	/*
	Refresh金钱等处理
	*/
	//void OnRefreshWindowEventHandler(std::list<std::string>& paramList);

	void On_Btn_Click(cocos2d::CCObject * pSender);

	void On_Btn_CellClick(cocos2d::CCObject * pSender);

	void On_Btn_RewardClick(cocos2d::CCObject * pSender);//某个副本通关奖励显示大宝箱点击事件

	void On_Gate_RewardTipsClick(cocos2d::CCObject * pSender);//关卡展示界面显示奖励tips
private:
	/*
	刷新tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb)const {
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}

public:
	void Function_SetTeamBattleDate();
	void Function_TeamBattleReset();

	void Function_GetTongGuanJiangLiResult();
};


#endif
