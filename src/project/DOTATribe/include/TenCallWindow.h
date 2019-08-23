//Name : TenCallWindow
//Function : 十连抽召唤窗口
//Author : lvyunlong
//Date: 20140522

#ifndef  _DOTATRIBE_TENCALLWINDOW_H_
#define  _DOTATRIBE_TENCALLWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/HeroSummonControlDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/IPopWindow.h"

class TenCallWindow : public IWindow 
	,public IPopWindow
{
private:
	enum{
			TEN_PRIORITY = 0,
			TEN_DTAWARD,
			TEN_DTHEROICON,
			TEN_HEROTYPE,
			TEN_HAVEICON,
			TEN_NEWICON,
			TEN_NAMEFRAME,
			TEN_NAMETTF,
			TEN_START,
			udHEROLISTBTN =81,
			udHEROLISTTEXT,
		};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCLayer* m_pLayer;
public:
	TenCallWindow();
	virtual ~TenCallWindow();
	
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _setHeroType(int index,int type,cocos2d::CCNode * pParent);
	inline void _setStarRank();
	inline void _setHeroBoard(int type);
	inline void _setAwardBoard();
	void _setinfodata();
	void _mapBtn();
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
public:
	void On_Click_Enevnt(cocos2d::CCObject* pSender);

	void On_Click_Summon_Event(cocos2d::CCObject* pSender);

};


#endif