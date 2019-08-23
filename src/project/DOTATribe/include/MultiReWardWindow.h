// Name :		MultiReWardWindow.h
// Function:	多个奖励窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_MULTIREWARDWINDOW_H_
#define  _DOTATRIBE_MULTIREWARDWINDOW_H_


#include "IWindow.h"
#include "cocos2d.h"
#include "../include/CTableView.h"
#include "../include/UIViewDataManger.h"
#include "../include/MultiRewardDataHandler.h"
#include "../include/IPopWindow.h"

class MultiReWardWindow : public IWindow
	,public IPopWindow
	,public CCScrollViewDelegate
{
public:
	MultiReWardWindow();
	virtual ~MultiReWardWindow();

	enum{
			MultiReward_MaskLayer,
			MultiReward_BG,
			MultiReward_GETGOODSTITLE,
			MultiReward_PREVIEWTITLE,
			MultiReward_SureButton,
			MultiReward_SureButtonLabel,
			MultiReward_ArrowUp,
			MultiReward_ArrowDown,
			MultiReward_ScrollLayer,
			MultiReward_CellBG1,
			MultiReward_CellObject1,
			MultiReward_CellName1,
			MultiReward_CellNum1,
			MultiReward_CellBG2,
			MultiReward_CellObject2,
			MultiReward_CellName2,
			MultiReward_CellNum2,
		};
	enum
	{
		//类型 0:物品 1:金钱 2: 经验 3:钻石 4:声望 5:体力
		Type_Item,
		Type_Menoy,
		Type_Exp,
		Type_Diamond,
		Type_Pregist,
		Type_Energy,
	};

	enum
	{
		SysLang_Item,
		SysLang_Menoy=4021,
		SysLang_Exp,
		SysLang_Diamond,
		SysLang_Pregist,
		SysLang_Energy,
	};


	CCLayer* m_pRoot;
	CScrollView* scroll;

	bool			m_scrollflag;
	bool			m_isFirstIn;
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

public:
	/*
		消息事件响应处理
	*/
	virtual void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
private:
	/*
		显示大厅面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void ShowWindow();
	/*
		初始化界面
	*/
	void InitLayer();
	void OnUpdateRewardInfo();
	void setArrow(CCScrollView* view);
	void On_Click_Close(cocos2d::CCObject* pSender);
	void ReSetData(MultiRewardData* data);
	float InitRewardList(CCLayer* layer);
	int _getQualityByData(MultiRewardData* data);
	void _chooseTitle();
	//滑动回调
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view){};
};

#endif
