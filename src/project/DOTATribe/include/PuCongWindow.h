//Name : PuCongWindow
//Function : 仆从
//Author : 方骏

#ifndef _DOTATRIBE_PUCONGWINDOW_H_
#define _DOTATRIBE_PUCONGWINDOW_H_

#include "../include/IWindow.h"
#include "../include/SubView.h"
#include "cocos-ext.h"

class PuCongWindow : public IWindow
{
private:
	enum
	{
		pBg = 0,
		pBoard,
		pCloseBtn,
		pHuntTab,
		pHuntTabTTF,
		pServantTab,
		pServantTabTTF,
		pMiningTab,
		pMiningTabTTF,
	};

private:
	SubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;

	cocos2d::CCNode * m_pRoot; 

public:
	enum{
		HLW_MINING = 0,		//挖矿
		HLW_HUNT = 1,		//矿洞寻宝
		HLW_SERVANT = 2,	//仆从分页
	};
	PuCongWindow();
	virtual ~PuCongWindow();

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
	inline void _checkNewFunc();
	inline void _loadWindowControls();
	inline void _mapBtn();
	inline void _loadSubViews(unsigned int idx);
	inline void selectTabItem(unsigned int index);
private:
	/*
		关闭窗口事件
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);

	/*
		tab回调
	*/
	virtual void On_Tab_Selected(cocos2d::CCObject* pSender);

};


#endif