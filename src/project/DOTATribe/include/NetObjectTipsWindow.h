// Name ; NetObjectTipsWindow.h
// Function：由网络的物品tips窗口
// Author : fangjun
// Date: 20131014

#ifndef  _DOTATRIBE_NETOBJECTTIPSWINDOW_H_
#define  _DOTATRIBE_NETOBJECTTIPSWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/CPriorityLayerColor.h"
class NetObjectTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum{
		udPRIORITYLAYER,
		udMAINBG,
		udNAME,
		udLV,
		udLVVALUE,
		udPRICE,
		udPRICEVALUE,
		udPRICEICON,
		udSTATEMENT,
		udSALEBTN,
		udSALETTF,
	};

private:
	cocos2d::CCNode* m_pRoot;//窗口根节点
	int m_ShowTipsType;
public:
	NetObjectTipsWindow();
	virtual ~NetObjectTipsWindow();

private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _initValue(NetObjectTips* data);
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
		遮盖层回调
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		购买按钮响应事件
	*/
	void  On_Sale_Event(cocos2d::CCObject * pSender);
};


#endif
