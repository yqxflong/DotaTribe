#ifndef  _DOTATRIBE_ARENAWINDOW_H_
#define  _DOTATRIBE_ARENAWINDOW_H_

////////////////////////////////////////////////////////////////
//Name:	 ArenaWindow
//Auchor: 	xiaobo.wu
//Func:	 竞技场窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include "IWindow.h"
#include   "../include/UIViewDataManger.h"
#include   "cocos-ext.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/CTouchSprite.h"
#include   <string>
#include   "../include/ArenaInfoDataHandler.h"
 


using  namespace  cocos2d;
  
typedef  struct  arenacelldata_tag
{
    bool  isWinArena;
	std::string  arenaDescription;
	int   fuchongSessionID;
	int   dequeueSessionID;
public:
arenacelldata_tag()
{
	isWinArena=false;
	arenaDescription="";
	fuchongSessionID=0;
	dequeueSessionID=0;
}
}ArenaCellData,*PArenaCellData;


class ArenaWindow : public IWindow, public  cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate,public CTouchSpriteDelegate
{
private:
	int m_iBackWindow;//回退页面
	std::string m_iBackSubview;//回退页面的子页面
protected:
	int m_SubType;   // 附加子类型
public:
   
	//主UI索引配置
	enum
	{
		_ARENA_PREBG_TAG_,
		_ARENA_BG_TAG_,
		_ARENA_HELP_BTN_TAG_,
		_ARENA_CLOSE_BTN_TAG_,
		_ARENA_TITLE_BOX_TAG_,
		_ARENA_TITLE_COTENT_TAG_,
		_ARENA_ADD_LABEL_BG_TAG_,
		_ARENA_ADD_LABEL_TAG_,
		_ARENA_ADD_NUMBER_TAG_,
		_ARENA_ADD_BTN_TAG_,
		_ARENA_PLAYER_NAME_TAG_,
		_ARENA_LEVEL_BG_TAG_,
		_ARENA_LEVEL_NUMBER_TAG_,
		_ARENA_HEAD_BG_TAG_,
		_ARENA_HEAD_BTN_TAG_,
		_ARENA_RANK_BG_TAG_,
		_ARENA_RANK_NUMBER_TAG_,
		_ARENA_POWER_NUMBER_TAG_,
		_AERNA_FIGHT_BTN_TAG_,
		_ARENA_FIGHT_CONTENT_TAG_,

		 
		_ARENA_PLAYER_RANK_BG_TAG_=60,
		_AERNA_PLAYER_RANK_LABEL_TAG_,
		_ARENA_PLAYER_RANK_NUM_TAG_,
		_ARENA_PLAYER_RECORD_BG_TAG_,
		_ARENA_PLAYER_RECORD_LABEL_TAG_,
		_AERNA_PLAYER_RECORD_NUMBER_TAG_,
			 
		_ARENA_RANK_BTN_TAG_,
		_ARENA_RANK_LABEL_TAG_,
		 
		_ARENA_RECORD_BG_TAG_,
		_ARENA_RECORD_CONTAIN_TAG_,
		_ARENA_RECORD_CELL_TAG_,

		_ARENA_REWARD_BTN_TAG_, 
		_ARENA_REWARD_HINT_TAG_,

		_ARENA_PRESTIGE_BG_TAG_,
		_ARENA_PRESITGE_LABEL_TAG_,
		_ARENA_PRESITGE_VALUE_TAG_,

		_ARENA_PRESTIGE_SHOP_BTN_TAG_,
		_ARENA_ARROW_MOVE_TAG_,

	};
	//头像按钮
	enum
	{
		_Arena_ChangleRole_Index_0_=14,
		_Arena_ChangleRole_Index_1_=24,
		_Arena_ChangleRole_Index_2_=34,
		_Arena_ChangleRole_Index_3_=44,
		_Arena_ChangleRole_Index_4_=54,
	};
	//发起挑战按钮
	enum
	{
		_Arena_ChangleRole_Fight_0_=18,
		_Arena_ChangleRole_Fight_1_=28,
		_Arena_ChangleRole_Fight_2_=38,
		_Arena_ChangleRole_Fight_3_=48,
		_Arena_ChangleRole_Fight_4_=58,
	}; 

	//cell索引配置
	enum
	{
		_ArenaCell_WINOrFAILL_BG_TAG_,
		_ArenaCell_Description_Label_TAG_,
		_ArenaCell_Dequeue_Btn_TAG_,
		_ArenaCell_Dequeue_Label_TAG_,
	};
	
 
	enum
	{
		_Arena_Challenege_Unit_Count_=10,
		_Arena_Start_Challenge_Tag_=10,
		_Arena_End_Challenege_Tag_=59,
	};

	enum
	{
		_Arena_Play_Rank_UnChange_,	 //名次不变
		_Arena_Play_Rank_Low_,		 //名次降低
		_Arena_Play_Rank_Hight_,	 //名次升高
	};

	enum
	{
		_Arena_Fail_Type_,
		_Arena_Win_Type_,
	};


	ArenaWindow();
	virtual ~ArenaWindow();

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
	 触摸事件 挑战人物事件通知
	*/
	virtual void rangeTouched(cocos2d::CCObject* pSender);
	  
	void	UpdateChallengeListUI();
 
 
	/*
	  创建TableCell中的数据
	*/
	virtual    void    CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);

	/*
      根据索引设置Cell的内容
	*/
	virtual    void    SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
				 

	/*
	设置TableCell的背景Image
	*/
	void    SetCellImage(cocos2d::extension::CCTableViewCell * pTableCell,bool isWinResult);

	/*
	设置Cell的描述文字
	*/
	void    SetCellDescription(cocos2d::extension::CCTableViewCell * pTableCell,std::string discription);

  
	/*
	设置查看按钮
	*/
	void    SetCellDequeueBtn(cocos2d::extension::CCTableViewCell * pTableCell,int cellIndex);
 
	/*
	 更新UI数据
	*/
	void    UpdateUIWithData();
	  

	float   GetCurSysMinuteTime();

	float	GetMinuteFromSecond(int second);
 
	int     GetDelayDayCountFromArena(float curMinute,float distanceMinute);

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:

	/*
		检查奖励提示
	*/
	void _checkAwardHint();

	/*
	发起战斗请求
	*/
	void   OnSendFightRequestHandler(int index);

	/*
		检查新功能开启
	*/
	inline void _checkNewFunc();
	/*
		显示Top面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新面板所有控件名称事件处理
	*/
	void   OnUpdateEventHandler(std::list<std::string>& paramList);
 	 
 
    /*公共按钮回调接口*/
	void  CallBackBtnClickHandler(cocos2d::CCObject * pSender);

	/*
	启动和禁用宝箱按钮事件
	*/
	void  SetGifBoxEnableState(bool isEnableTouch);
	

	/*
     复仇按钮点击事件
	*/
	void   CallBackFuChouBtn(cocos2d::CCObject * pSender);

	/*
	 查看历史竞技记录事件
	*/
	void   CallBackShowArenaBtn(cocos2d::CCObject * pSender);
 

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

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

	/*
	更新当前剩余挑战次数
	*/
	void  UpdateLastArenaTime();
  
private: 
	cocos2d::CCNode *				   m_pBaseNode;
	cocos2d::extension::CCTableView *  m_pTable;
	std::vector<PHistoryArenaNode>     m_historyArenaVec;
	cocos2d::CCSize					   m_szCELL;
	bool							   isNeedToUpdateTimeForReward;
	int								   preWidnowEnumType;  
	int								   tmpPlayInstanceID;
	bool							   m_bIsInitlayout;
	std::map<int,int>				   m_mStaticBtnMap;
};

#endif
