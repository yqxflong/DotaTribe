//Name：LogoWindow
//Function：展示Logo，只有安卓用
//Author：尹强
#ifndef  _DOTATRIBE_LOGOWINDOW_H_
#define  _DOTATRIBE_LOGOWINDOW_H_


#include "IWindow.h"
#include "../include/CSprite.h"

class LogoWindow : public IWindow
{
	enum{
		tLayer = 0,
		tLogo,
	};
private:
	int  m_LogicTickCounter; // LOGO界面定时器 

	bool m_bChangeLogo;		//是否改变显示第二张logo

	CSprite * m_pLogo;	//logo

public:
	LogoWindow();
	virtual ~LogoWindow();

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
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示Top面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
};


#endif
