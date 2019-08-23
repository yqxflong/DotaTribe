// Name : RechargeWarnWindow.h
// Function:充值提示绑定账号对话框窗口
// Author : lvyunlong
// Date: 20131119

#ifndef  _DOTATRIBE_RECHARGEWARNWINDOW_H_
#define  _DOTATRIBE_RECHARGEWARNWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class RechargeWarnWindow : public IWindow
{
private:
	enum{
		udGRAYLAYER,
		udBOXBG,
		udMenuTTF1,
		udMenuTTF2,
		udMENU1,
		udMENU2,
		udCloseBtn,
		udTITLE,
	};

	cocos2d::CCNode* m_pRoot;	  //当前窗口节点	
	cocos2d::CCNode* m_pWarnBoxNode;//充值绑定Autococo节点
public:
	RechargeWarnWindow();
	virtual ~RechargeWarnWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();

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

	void   OnHideWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_ColseBtn(cocos2d::CCObject* pSender);

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
};

#endif
