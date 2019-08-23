// Name ; NetObjectTipsWindow.h
// Function�����������Ʒtips����
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
	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�
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
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		�ڸǲ�ص�
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		����ť��Ӧ�¼�
	*/
	void  On_Sale_Event(cocos2d::CCObject * pSender);
};


#endif
