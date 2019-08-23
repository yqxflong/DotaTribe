#ifndef   _DOTATRIBE_FORCEPUSHTASKREWARD_WINDOW_H_
#define   _DOTATRIBE_FORCEPUSHTASKREWARD_WINDOW_H_

////////////////////////////////////////////////////////////////
//Name:	 ForcePushTaskRewardWindow
//Auchor: 	xiaobo.wu
//Func:	 强制推送任务奖励窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include "IWindow.h"
#include   "cocos-ext.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/MainTaskDataHandler.h"
#include   "../include/IPopWindow.h"
 
class ForcePushTaskRewardWindow : public IWindow, public IPopWindow
{ 
public:
	enum
	{
		_UI_BG_TAG_,
		_UI_CLOSE_BTN_TAG_,
		_UI_TASK_TILE_TAG_,
		_UI_TASK_ITEM1_OBJ_TAG_,
		_UI_TASK_ITEM1_NUM_TAG_,
		_UI_TASK_ITEM2_OBJ_TAG_,
		_UI_TASK_ITEM2_NUM_TAG_,
		_UI_TASK_ITEM3_OBJ_TAG_,
		_UI_TASK_ITEM3_NUM_TAG_,
		_UI_TASK_REWARD_BTN_TAG_,
		_UI_TASK_REWARD_LABEL_TAG_,

	};
	ForcePushTaskRewardWindow();
	virtual ~ForcePushTaskRewardWindow();
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

	//显示弹窗
	virtual void ShowPopWindow();
	//弹窗已经隐藏
	virtual void PopWindowDidHide();
	 
	/*
	*/
	void   DestroyWinAndMemData(bool isNeedToClear);
public:
	void    initUIAndData();
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	void			   btnSelectorHandler(cocos2d::CCObject * pSender);

	//奖品点击事件
	void OnAwardClicked(cocos2d::CCObject* pSender);
protected:
	bool    attachMemData();
	void    initUILayout();
	void    updateUIWithMemData();
	void    detachMemData();
private:  
	void    OnShowWindowEventHandler();
	void	ShowWindow();
	cocos2d::CCNode * GetWindowRootLayer();
	void    bindStaticBtn();
	void    bindSelectorForBtn(int btnUIIndex);
	void    bindSelectorForTouchSprite(int spriteUIIndex);
	void    setNodeVisiableByTag(bool isVisiable,int nodeUIIndex);
	void	getRewardBgAndIconTagByIndex(size_t & index,int & bgIconTag,int & IconTag,int & numTag);
	void    ShowTaskRewardInfo();
	void    rewardHandler();
	bool	willLevelUp();
private:
	PromptRewardInfoData * m_pActiveRewardItem;
	bool				   m_bIsShowingReward;
	bool				   m_getReward;
	
};
 


#endif