//Name : ShopWindow
//Function : 商店
//Author : 吕云龙

#ifndef  _DOTATRIBE_SHOPWINDOW_H_
#define  _DOTATRIBE_SHOPWINDOW_H_


#include "../include/IWindow.h"
#include "../include/ShopView.h"
#include "../include/SecretView.h"
#include "../include/SpecialOfferView.h"
#include <string>
#include "cocos-ext.h"

#define TAB_VIEW_INDEX_0_		0
#define TAB_VIEW_INDEX_1_		1


#define  PRESTIGE_SHOP	0
#define  SECRET_SHOP	1

class ShopWindow : public IWindow
{
private:
	enum
	{
		udMAINBG,
		udTAB1,
		udTAB2,
		udCLOSEBTN,
	};
private:
	SHSubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;
public:
	ShopWindow();
	virtual ~ShopWindow();
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
	inline void _initLayout();
	inline void _loadSubView();
	inline void _mapBtn();
	
public:
	void _selectTabItem(unsigned int idx);

	void _loadSubView(unsigned int idx);

	void _resetAllHighlight();
	void _highlightTabItem(unsigned int idx);

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示商店面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		隐藏商店面板事件处理
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		渐隐商店面板事件处理
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);
	/*
		刷新随机商店事件处理
	*/
	inline void OnUpdataWindowEventHandler(std::list<std::string>& paramList);
private:

	void selectSubTabItem(int idx);

public:

	void On_Tab_Selected(cocos2d::CCObject* pSender);

private:
	/*
		关闭窗口事件
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);
	/*
		检查是否开启秘宝商店
	*/
	bool _checkOpenMBShop();
};


#endif
