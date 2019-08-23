
#ifndef _DOTATRIBE_MAINTASKWINDOW_H_
#define _DOTATRIBE_MAINTASKWINDOW_H_

#include "../include/IWindow.h"
#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/NFControlsManager.h"
#include "../include/MainTaskDataHandler.h"
using  namespace  cocos2d;
using namespace cocos2d::extension;

class MainTaskWindow : public IWindow, public  cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
	    _TASKUI_BG_TAG_,
		_TASKUI_CLOSE_BTN_TAG_,
		_TASKUI_TASK_TABLEVIEW_TAG_,
		_TASKUI_TASK_CELL_TAG_,
		_TASKUI_TSAK_TILE_BG_TAG_,
		_TASKUI_TASK_TILE_LABEL_TAG_,
		_TASKUI_TASK_CONTENT_TAG_,
		_TASKUI_TASK_GOTO_BTN_TAG_,
		_TASKUI_REWARD_TILE_BG_TAG_,
		_TASKUI_REWARD_LABEL_TAG_,
		_TASKUI_REWARD_MARK_TAG_,
		_TASKUI_REWARD1_OBJ_TAG_,
		_TASKUI_REWARD1_NUM_TAG_,
		_TASKUI_REWARD2_OBJ_TAG_,
		_TASKUI_REWARD2_NUM_TAG_,
		_TASKUI_REWARD3_OBJ_TAG_,
		_TASKUI_REWARD3_NUM_TAG_,
		_TASKUI_REWARD_BTN_TAG_,
		_TASKUI_REWARD_CONTENT_TAG_,
		_TASKUI_DIAMOND_BG_TAG_,
		_TASKUI_DIAMOND_NUM_TAG_,
		_TASKUI_GOLD_BG_TAG_,
		_TASKUI_GLOG_NUM_TAG_,
		_TASKUI_GRAY_COLOR_LAYER_TAG_,
		_TASKUI_BG_MARK_TAG_,
		_TASKUI_BG_IMAGE_TAG_,
		_TASKUI_BG_GOTO_BTN_EFFECT_TAG_,
	};

	enum
	{
		_TASK_CELL_BTN_TAG_,
		_TASK_CELL_CONTENT_TAG_,
	};
public:
	MainTaskWindow();
	virtual ~MainTaskWindow();

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
	void    CommonBtnCallBackHandler(cocos2d::CCObject * pSender);
	void    TaskCellClickHandler(cocos2d::CCObject * pSender);
	void	setMenuSprite(CMenuItemSprite* pMenuItem,std::string nameImageName);

	//奖品点击事件
	void OnAwardClicked(cocos2d::CCObject* pSender);
protected:
	/*
	 Table View 相关接口
	*/
	//绑定TableView
	void  SetTableView();
	 
	/*
	  创建TableCell中的数据
	*/
	virtual    void    CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);

	/*
      根据索引设置Cell的内容
	*/
	virtual    void    SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	/*
	或许Cell的高宽
	*/
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);

	/*
	获得指定Cell
	*/
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

	/*
	容器Cell总数
	*/
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	/*
	容器Cell点击事件
	*/
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){}


	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){}

 
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){}

	virtual void ActiveCellItemWithCellIndex(int cellIndex);
	  
	/*
	滚动完毕回调
	*/
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	/*
	缩放完毕回调
	*/
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	/*
	刷新TableView
	*/
	void  refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	void  refreshTableViewOffCount(cocos2d::extension::CCTableView* tb,int interCount) const 
	{
		tb->reloadData();
		tb->setContentOffset(ccp(0,-m_szCELL.height*interCount));
	}
protected:
	/*
		消息事件响应处理
	*/
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		显示面板事件处理
	*/
	inline void OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		渐隐面板事件处理
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void		initUILayout();
	inline void		mapStaticBtn();
	inline void		attachTaskData();
	inline void     bindSelectorBtnByTag(int nodeTag);
	inline void     BindSelectorForTouchSprite(int signID);
	inline void		DispatchUpdateEvent(int updateAttachParam);
	inline void     HideAllTaskContent();

private:
	/*
		获得任务界面数据的更新界面操作
	*/
	void Function_GetMainTaskData();
 
	/*
	  关闭
	*/
	void  CloseHanlder();

	/*
	领取奖励
	*/
	void  RewardHandler();

	/*
	 设置Cell状态
	*/
	void  SetCellBtnState(CCTableViewCell * pTableCell,unsigned int cellIndex);
	/*
	 更新Cell状态
	*/
	bool  ActiveCellBtnState(cocos2d::CCObject * pSender);

	void  SetMenuState(bool isVisiable,int nodeTag);

	void  ShowTaskLayerWithCellBtn();
	 
	void  ShowGuidWithTaskItem(MainTaskItem * pTaskItem);

	void  ShowTaskRewardInfo(MainTaskItem * pTaskItem);
	 
	void  SetNodeVisiableByTag(bool isVisiable,int nodeTag);

	void  GetRewardBgAndIconTagByIndex(size_t & index,int & bgIconTag,int & IconTag,int & numTag);

	void  ShowStartTaskLayer();

	void  GoToGuidModuleHandler();

	void  DispatchSwitchModule(int moduleType, std::string param);

	void  UpdateTaskDataAndUI(bool bhadNextTask);

	void  UpdateDiamondAndGold();

private:
	cocos2d::extension::CCTableView *  m_pTable;
	cocos2d::CCSize					   m_szCELL;
	int								   m_nActiveTaskIndex;
	int								   m_nBackWindow;				//回退页面
	cocos2d::CCNode*				   m_pRoot;						//窗口根节点
	MainTaskData *					   m_pMainTaskData;				//任务内存数据句柄
	MainTaskItem *					   m_pActiveTaskItem;			//当前激活的获得;
	int								   m_nStartFinishCellIndex;		//获取启动以及完成任务的Cell索引
	bool							   m_isNeedToShowTips;
	   
};


#endif