#ifndef  _DOTATRIBE_TIPSWINDOW_H
#define  _DOTATRIBE_TIPSWINDOW_H
 
#include   "IWindow.h"
#include   "../include/UIViewDataManger.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/CTouchSprite.h"
#include   <string>

////////////////////////////////////////////////////////////////
//Name:	 TipsWindow
//Auchor: 	xiaobo.wu
//Func:	 服务器应答协议窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

class TipsWindow : public IWindow  
{
protected:
	int m_SubType;   // 附加子类型
	cocos2d::CCLayer* m_pRootLayer;
public:
    enum
	{
		kGRAYLAYER,
		_TIPSUI_BG_,
		_TIPSUI_TITTLE_BG_,
		_TIPSUI_TITTLE_,
/*		_TIPSUI_CLOSE_BTN_TAG_,*/
		_TIPSUI_TEXT_TAG_,
		_TIPSUI_TYPE1_SURE_BTN_TAG_,
		_TIPSUI_TYPE1_SURE_IMAGE_TAG_,
		_TIPSUI_TYPE1_CANCEL_BTN_TAG_,
		_TIPSUI_TYPE1_CANCEL_IMAGE_TAG_,
		_TIPSUI_TYPE2_SURE_BTN_TAG_,
		_TIPSUI_TYPE2_SURE_IMAGE_TAG_,
	};
	TipsWindow();
	virtual ~TipsWindow();

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

	  
	virtual    void    Destroy();

	/*
	 显示
	*/
	virtual	   void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	virtual    void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);

	/*
	加载UI控件
	*/
    virtual    void    LoadUIControl();
 
	/*
	初始化UI布局控制
	*/
    virtual    void    InitLayout();

	/*
	 绑定UI界面中的按钮相应事件
	*/
	virtual    void    InitMapBtn();

	void  MapBtnWithTag(int tag);
	 
	virtual    void    ShowBtnWithType(char btnType);


	 
	void  HideCCNodeWithTag(int btnTag);

	void  ShowCCNodeWithTag(int tag);
	 

	virtual    void    UpdateUIWithData();


	void   MenuCallBackHandler(cocos2d::CCObject * pSender);

	cocos2d::CCLayer  *   GetRootMarkLayer();
 

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
 
	 
};
 

#endif