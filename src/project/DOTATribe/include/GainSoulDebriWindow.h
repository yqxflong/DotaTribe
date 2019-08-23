//Name : GainSoulDebriWindow
//Function : 获得灵魂碎片窗口
//Author : lvyunlong
//Date: 20131208

#ifndef  _DOTATRIBE_GAINSOULDEBRIWINDOW_H_
#define  _DOTATRIBE_GAINSOULDEBRIWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"
class GainSoulDebriWindow : public IWindow, public CPriorityLayerColorDelegate,public AnimationEffectCallBackProtocol,public IPopWindow
{
private:
	enum{
			udPRIORITY = 0,
			udMAINBG,
			udHEROMASKNODE,
			udHEROMASKNODE1,
			udTITLE, 
			udSTARRANKTEXT,
			udHEROTYPE,
			udDESCRIBE,
			udCHANGEDESCRIBE,
			udSURETEXT,
			udHERONAME,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pGSoulNode;
	GainHeroOrDebriData* m_pGainData;
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;//骨骼动作
	bool m_isTouch;
public:
	GainSoulDebriWindow();
	virtual ~GainSoulDebriWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setStarRank();
	inline void _setHeroType(int type);
	inline void _setShowHeroDaiji(int heroid);
	inline void _setText();
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

	/*
		AnimationEffectCallBackProtocol Delegate
	*/
	virtual void EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

};


#endif