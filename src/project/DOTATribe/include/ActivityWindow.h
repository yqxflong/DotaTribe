// Name :		ActivityWindow.h
// Function:	活动窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_ACTIVITYWINDOW_H_
#define  _DOTATRIBE_ACTIVITYWINDOW_H_

#include "IWindow.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CTableView.h"

class ActivityWindow : public IWindow,public CCScrollViewDelegate
{
public:
	ActivityWindow();
	virtual ~ActivityWindow();
	enum
	{
		ActivityBG,
		ActivityBG_SMALL,
		Activity_CLOSE,
		Activity_View,
		Activity_Frame,
		Activity_NAMETTF,
		uiArrowUp,
		uiArrowDown,
		uiArrowMoveUp,
		uiArrowMoveDown,
		
	};

	enum
	{
		Activity_FIRST_TAB_,
		Activity_SECOND_TAB_,
	};
public:
	CScrollView*			m_scrollView;
	CCLayerColor*			m_scrollLayer;
	CCSprite*				m_Frame;

	std::vector<CCLayerColor*>	m_LayerList;
	std::map<int,CCSprite*>  m_MapCSpriteEffEct;
	unsigned short m_CurActivityType;
	CMenuItemSprite* m_Tab_One;
	CMenuItemSprite* m_Tab_Two;
	IWindow* m_showWindow;
	int m_nHideLastWindowEventId;//上一个需要隐藏窗口的事件Id
	int m_tabNum;
	bool m_Reroad;
	bool m_scrollflag;
	bool m_isFirstIn;
public:
	void InitLayer();
	void InitTab();
	void DeleteCurActivity();
public:
	CMenuItemSprite* m_RecharMenu;
public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:
	virtual void scrollViewDidZoom(CCScrollView* view){};
	virtual void scrollViewDidScroll(CCScrollView* view);

	void SetArrowState(CCScrollView* view);
public:

	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	void On_Chiose_Activity(cocos2d::CCObject* pSender);
	void On_Close(cocos2d::CCObject* pSender);
	void On_SelectTab(cocos2d::CCObject* pSender);
private:

	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);
	void   OnUpdateTempleUI(std::list<std::string>& paramList);
	void   OnUpdateEffectUI(std::list<std::string>& paramList);
};


#endif
