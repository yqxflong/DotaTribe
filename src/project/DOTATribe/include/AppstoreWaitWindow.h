//Name：AppstoreWaitWindow
//Function：Appstore等待支付框
//Written By：lvyunlong

#ifndef  _DOTATRIBE_APPSTOREWAITWINDOW_H_
#define  _DOTATRIBE_APPSTOREWAITWINDOW_H_

#include "IWindow.h"

class AppstoreWaitWindow : public IWindow
{
private:
	enum{
		udGRAYLAYER,
		udSENCE,
	};
	cocos2d::CCNode* m_pRoot;
public:
	AppstoreWaitWindow();
	virtual ~AppstoreWaitWindow();
private:
	inline void _initLayout();
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
	/*
		隐藏支付窗口
	*/
	void   OnHideWindowEventHandler(std::list<std::string>& paramList);

};


#endif
