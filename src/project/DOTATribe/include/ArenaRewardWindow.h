#include "../include/IWindow.h"
 
#ifndef  _DOTATRIBE_ARENAREWARD_H_
#define  _DOTATRIBE_ARENAREWARD_H_

////////////////////////////////////////////////////////////////
//Name:	 ArenaRewardWindow
//Auchor: 	xiaobo.wu
//Func:	 竞技场奖励窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include  "IWindow.h"
#include   "../include/UIViewDataManger.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/ArenaInfoDataHandler.h"
#include   "../include/CTimeLabel.h"
#include   <string>
 
class ArenaRewardWindow : public IWindow, public  cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate ,public CTimerEventProtocol
{ 
public: 
	//主UI索引配置
	enum
	{ 
		_ARENAREWARD_BG_TAG_,
		_ARENAREWARD_CLOSE_BTN_TAG_,
		_ARENAREWARD_TITLE_TAG_,
		_ARENAREWARD_LEFT_TITLE_TAG_,
		_ARENAREWARD_LEFT_TABLE_TAG_,
		_ARENAREWARD_LEFT_CELL_TAG_,
		_ARENAREWARD_RIGHT_RANK_LABLE_TAG_,
		_ARENAREWARD_RIGHT_RANK_VALUE_TAG_,
		_AREWAREWARD_RIGHT_SEGMENT_1_TAG_,
		_ARENAREWARD_RIGHT_COMBAT_RECORD_LABLE_TAG_, 
		_ARENAREWARD_RIGHT_COMBAT_RECORD_CONTENT_TAG_,
		_ARENAREWARD_RIGHT_ODDS_LABLE_TAG_,
		_ARENAREWARD_RIGHT_ODDS_CONTENT_TAG_,
		_ARENAREWARD_RIGHT_SEGMENT_2_TAG_,
		_ARENAREWARD_RIGHT_TITLE_TAG_,
		_ARENAREWARD_RIGHT_OBJ_1_TAG_,
		_ARENAREWARD_RIGHT_NUM_1_TAG_,
		_ARENAREWARD_RIGHT_OBJ_2_TAG_,
		_ARENAREWARD_RIGHT_NUM_2_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,
		_ARENAREWARD_RIGHT_REWARD_LABLE_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TIME_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TIPS_TAG_,
		_ARENAREWARD_GRAP_COLOR_TAG_,
		_ARENAREWARD_GROW_TAG_,
		_ARENAREWARD_GROW_TAG_ARROWMOVE_,
	}; 
	enum
	{
		_CHANLLENGE_CELL_BG_TAG_,
		_CHALLENEGE_REWARD_OBJ_TAG_,
		_CHALLENEGE_REWARD_CONTENT_TAG_,
		_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_,
		_CHALLENEGE_TASK_CONTENT_FOLLOW_TAG_,
		_CHALLENEGE_REWARD_BTN_TAG_,
		_CHALLENEGE_REWARD_LABEL_TAG_,
	};
	ArenaRewardWindow();
	virtual ~ArenaRewardWindow(); 
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

	/*
	加载UI控件
	*/
    virtual    void    LoadUIControl();

	/*
	绑定内存数据
	*/
	void    InitData();

	/*
	销毁内存数据
	*/
	void    DestroyData();

  
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		窗口显示时间通知
	*/
	void			   OnShowWindowEventHandler(std::list<std::string>& paramList);
 
	/*
	    按钮相应事件处理
	*/
	void			   CommonMenuSelector(cocos2d::CCObject * pSender);

	/*
	  Table Cell 按钮回调事件
	*/
	void			   CommonCellMenuSelector(cocos2d::CCObject * pSender);

	/*
		绑定UI按钮事件
	*/
	void			   InitBindMenuSelector();
	 
	/*
		设置窗口
	*/
	void			   SetTableView();

	/*
		创建列表子项
	*/
	void			   CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);
		
	/*
		设置列表子项内容
	*/
 	void			   SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	/*
		倒计时label回调
	*/
	virtual   void	   TimerEventHandler(int eventType,std::string attachParam);
	 
private:
	/*
	 TableView的通知事件
	*/  
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private: 
	/*
	   刷新tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		 tb->reloadData();
	     tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}

	void  updateUIWithData();

	void  updateRankRewardData();

	void  dispatchReceiptCode(int receiptCode);

	void  showRewardMenuItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode);
	void  showRewardSpriteItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode);

private:
	cocos2d::CCNode	 *				   m_pViewRoot;
	cocos2d::extension::CCTableView *  m_pTable; 
	cocos2d::CCSize					   m_szCELL;
	bool							   m_bScrollEnd;
	ArenaRewardData *				   m_pArenaRewardData;
	int								   m_nMaxRewardSize;
	unsigned int					   m_nLastRequestCellIndex;
};

#endif
