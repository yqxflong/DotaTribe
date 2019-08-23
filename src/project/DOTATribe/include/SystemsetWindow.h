//Name：系统设置界面
//Function：系统设置
//Written By：吕云龙

#ifndef  _DOTATRIBE_SYSTEMSETWINDOW_H_
#define  _DOTATRIBE_SYSTEMSETWINDOW_H_


#include "../include/IWindow.h"
#include <string>
#include "cocos-ext.h"

class SystemsetWindow : public IWindow
{
private:
	enum{
		syLayerColorBG,
		syBaseBG,
		syPlayerNameBG,
		syServerNameBG,
		syCloseBtn,
		syUSERCENTERBtn,
		syLogouBtn,
		syYinyueBtn,
		syYinxiaoBtn,
		syUSERCENTERLB,
		syLogouLB,
		syLByinyue,
		syLByinxiao,
		syCurrPlayerTTF,
		syCurrPlayerNameTTF,
		syCurrServerTTF,
		syCurrServerNameTTF,
	};
private:
	inline void _initLayout();
	inline void _mapBtns();
	inline void _setText();
private:
	cocos2d::CCNode *m_SystemNode;
	const int m_nSVZorder;
	int idx;
	bool m_isBguest;
public:
	SystemsetWindow();
	virtual ~SystemsetWindow();
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
		显示装备面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		隐藏装备面板事件处理
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);

	/*
		更新装备面板事件处理
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);

	/*
		渐隐装备面板事件处理
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

protected:
	//点击事件
	void On_Click_Event(cocos2d::CCObject* pSender);
	//用户账户管理事件
	void On_Click_User_Event(cocos2d::CCObject* pSender);
	//返回登录事件
	void On_Click_LoginBack_Event(cocos2d::CCObject* pSender);
protected:
	//音乐是开的吗
	bool IsBackgroundMusic();
	//音效是开的吗
	bool IsEffectSound();
};

#endif
