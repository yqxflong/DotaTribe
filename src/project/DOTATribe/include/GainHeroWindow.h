//Name : GainHeroWindow
//Function : 获得英雄窗口
//Author : lvyunlong
//Date: 20131206

#ifndef  _DOTATRIBE_GAINHEROWINDOW_H_
#define  _DOTATRIBE_GAINHEROWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CProgressTimer.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"

class GainHeroWindow : public IWindow 
	,public IPopWindow
	,public CProgressTimerDelegate
	, public CPriorityLayerColorDelegate
	,public AnimationEffectCallBackProtocol
{
private:
	enum{
			udPRIORITY = 0,
			udNEWHEROEFFECTNODE,
			udMAINBG,
			udHEROMASKNODE,
			udTITLE, 
			udSTARRANKTEXT,
			udHEROTYPE,
			udMOMENTUM,
			udLEADERSHIPTEXT,
			udLEADERSHIPVALUE,
			udSCHEDULEBG,
			udSCHEDULE,
			udCLICKCLOSETEXT,
			udHERONAME,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pGHeroNode;
	GainHeroOrDebriData* m_pGainData;
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;//骨骼动作
	CProgressTimer *m_pProgress;	//献祭界面进度条
	int m_CurViewHeroLV;
	bool m_isBGainBtn;
	bool m_isEffectTime;
public:
	GainHeroWindow();
	virtual ~GainHeroWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _setStarRank();
	inline void _setHeroType(int type);
	inline void _setShowHeroDaiji(int heroid);
	inline void _initProgressTimer();
	inline void _setProgress(GainHeroOrDebriData* pData);
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
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		显示获得英雄面板事件处理	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void ShowWindow();
	/*
		隐藏获得英雄面板事件处理	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

public:
	void On_Click_Enevnt(cocos2d::CCObject* pSender);
public:
	/*
		英雄等级的回调
	*/
	void CallbackTTF();
	/*
		按钮是否可按
	*/
	void CallbackBtnEnable();
	/*
		判断是否是四星英雄
	*/
	void StarRankShow();
public:
	virtual void CallBack_NextLevel();
	virtual void CallBack_RunFinish();
public:
	/*
		AnimationEffectCallBackProtocol Delegate
	*/
	virtual void EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

};


#endif