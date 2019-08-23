//Name:NewEquipremindWindow
//Author: lvyunlong
//Func: 新装备提醒功能
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_NEWEQUIPREMINDWINDOW_H_
#define  _DOTATRIBE_NEWEQUIPREMINDWINDOW_H_

#include "IWindow.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/CPublicVarReader.h"
#include <cocos2d.h>
#include <cocos-ext.h>


class NewEquipremindWindow : public IWindow
{
private:
	enum{
			udBG = 0,
			udQUALITY,
			udEQUIPICON,
			udEFFECT,
			udDESCRIBE, 
			udCHECKBTN,
			udCHECKBTNTEXT,
			udCLOSEBTN,
		};
public:
	NewEquipremindWindow();
	virtual ~NewEquipremindWindow();
public:
	BagEquipData *m_pEquip;
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setEquipicon();
	inline void _setQualityicon();
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

	/*
		显示获得英雄面板事件处理	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏获得英雄面板事件处理	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
private:
	void On_Check_ClickBtn(cocos2d::CCObject * pSender);

	void On_Close_ClickBtn(cocos2d::CCObject * pSender);
};


#endif