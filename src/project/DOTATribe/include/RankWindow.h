#ifndef _DOTATRIBE_RANKWINDOW_H_
#define _DOTATRIBE_RANKWINDOW_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  排行榜  公共
//date:   2013/09/13
///////////////////////////////////////////////// 
#include    "IWindow.h"
#include	<cocos-ext.h>
#include    <cocos2d.h>
#include	"../include/UIViewDataManger.h"
#include    "../include/EventTyper.h"
#include    "../include/CMenuItemSprite.h"
#include    "../include/ArenaRankDataHandler.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/BossScoreDataHandler.h"
 
 
class RankWindow: public IWindow ,public  cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate
{
public:
	enum
	{
		_RANKINGLIST_BG_TAG_,
		_RANKINGLIST_CLOSE_BTN_TAG_,
		_RANKINGLIST_TABLE_TAG_,
		_RANKINGLIST_TABLE_CELL_TAG_,
		_RANKINGLIST_GRAPLAYER_TAG_,
	};

	enum
	{
		_RANKCELL_RANK_NUMBER_BG_TAG_,
		_RANKCELL_RANK_NUMBER_VALUE_TAG_,
		_RANKCELL_RANK_ROLE_HEAD_BG_TAG_,
		_RANKCELL_RANK_ROLE_HEAD_TAG_,
		_RANKCELL_RANK_BG_TXT_TAG_,
		_RANKCELL_RANK_ROLENAME_,
		_RANKCELL_RANK_ROLELEVEL_,
		_RANKCELL_RANK_ROLEBLT_,
		_RANLCELL_RANK_LOOKOVER_BTN_,
	};
	enum{
		_RANK_TYPE_AREANA_ = 0,
		_RANK_TYPE_TOWER_ = 1,
		_RANK_TYPE_BOSS_ = 2,

	};//排行榜类型

	RankWindow();
	virtual ~RankWindow(){};

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
	初始化UI布局控制
	*/
    virtual    void    InitLayout();

	/*
	 绑定UI界面中的按钮相应事件
	*/
	virtual    void    InitStaticMapBtn();

	/*
	加载TableView
	*/
	virtual    void    SetTableView();

	/*
	 初始化UI数据  
	*/
	virtual    void    InitData();

	/*
	销毁UI内存数据
	*/
	virtual    void	   DestroyData();
	  
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	//按钮回调事件通知 
	void   CallBackBtnClickHandler(cocos2d::CCObject * pSender);

	//查看人物信息事件
	void   LookOverRoleInfoSelector(cocos2d::CCObject * pSender);

protected:
	
	virtual    void    CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);

	virtual    void    SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	virtual    void    SetRankNumber(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
	virtual    void    SetRankRoleIconID(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
	virtual    void    SetRankRoleName(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
	virtual    void    SetRankRoleLevel(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
	virtual    void    SetRankRoleBltValue(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
	virtual	   void	   SetRankRoleLookOverBtn(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);


	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private:
 
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		 tb->reloadData();
	     tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	} 
private:
	cocos2d::extension::CCTableView *  m_pTable;
	cocos2d::CCSize m_szCELL;

private:
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	cocos2d::CCNode *  m_pViewRoot;
	int m_tRankType;					//排行榜类型
	ArenaRankData * m_pArenaRankData;
	TowerRankList * m_pTowerRankList; 
	BSRankList * m_pBossRankList;
};

#endif