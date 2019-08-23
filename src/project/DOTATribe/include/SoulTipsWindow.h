// Name :SoulTipsWindow.h
// Function：战魂tips窗口
// Author : lvyunlong
// Date: 20140224

#ifndef  _DOTATRIBE_SOULTIPSWINDOW_H_
#define  _DOTATRIBE_SOULTIPSWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/RoleSoulsDataHandler.h"

enum{
	_SOULTIPS_OWNER_ = 0,
	_SOULTIPS_OTHER_
};

enum{
	_SOUL_DB_TYPE_ = 0,
	_SOUL_HERO_TYPE_,
};

class SoulTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum{
		_SOULTIPS_PRIORITY = 0,//遮盖层
		_SOULTIPS_BG,		//背景
		_SOULTIPS_NAME,			//名字
		_SOULTIPS_SOULFRAME,	//底框
		_SOULTIPS_SOULICON,		//战魂图标
		_SOULTIPS_LEVEL,		//等级
		_SOULTIPS_ADDITTION,	//附加1
		_SOULTIPS_EQUIPEDBTN,	//装备按钮
		_SOULTIPS_EQUIPEDTTF,	//装备按钮文字
		_SOULTIPS_UNLOADBTN,	//卸载按钮
		_SOULTIPS_UNLOADTTF,	//卸载按钮文字
		_SOULTIPS_CLOSEBTN,	//关闭按钮
	}SOULTIPS;


	IHeroSoulItem * m_pNeedSoulData;
	int m_soulBufferID;
	int m_soulType;
	unsigned char m_Heroindex;
public:
	SoulTipsWindow();
	virtual ~SoulTipsWindow();

private:
	inline void _initLayout();
	/*
		初始化控件
	*/
	inline void _initControl();

	void _mapBtn();

	void setBtnshow();
	void setInfoTips();
public:
	virtual    bool    Init();

	virtual    bool    Load();

	virtual    void    Tick();

	virtual    void    Destroy();

public:
	/*
	消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
	show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		CPriorityLayerColor Delegate
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		装备按钮
	*/
	void On_Check_Equip_Event(cocos2d::CCObject* pSender);
	/*
		关闭按钮
	*/
	void On_Check_Close_Event(cocos2d::CCObject* pSender);

	/*
		卸下按钮
	*/
	void On_Check_Disboard_Event(cocos2d::CCObject* pSender);
};


#endif
