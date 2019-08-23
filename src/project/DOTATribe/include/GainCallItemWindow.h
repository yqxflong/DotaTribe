//Name : GainCallItemWindow
//Function : 获得召唤物品窗口
//Author : lvyunlong
//Date: 20140522

#ifndef  _DOTATRIBE_GAINCALLITEMWINDOW_H_
#define  _DOTATRIBE_GAINCALLITEMWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/IPopWindow.h"
class GainCallItemWindow : public IWindow, public CPriorityLayerColorDelegate,public IPopWindow
{
private:
	enum{
			udPRIORITY = 0,
			udMAINBG,
			udTITLE,
			udDTAWARDBOARD,
			udCLOSETTF,
			udTITLE1,
			udEFFECT,
			udNAME,
		};
	cocos2d::CCNode* m_pRoot;
	GainHeroOrDebriData* m_pGainData;
public:
	GainCallItemWindow();
	virtual ~GainCallItemWindow();
	
private:
	inline void _initLayout();

	inline void _initControl();

	inline void _setInfoData();
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

	void ShowWindow();
	//显示弹窗
	virtual void ShowPopWindow();
	//弹窗已经隐藏
	virtual void PopWindowDidHide();
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		显示获得英雄面板事件处理	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏获得英雄面板事件处理	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
public:
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
};


#endif