// Name : ShopTipsWindow
// Function���̵���Ʒtips����
// Author : lvyunlong
// Date: 20140214

#ifndef  _DOTATRIBE_SHOPTIPSWINDOW_H_
#define  _DOTATRIBE_SHOPTIPSWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/ShopTipsDataHandler.h"
#include "../include/CPriorityLayerColor.h"

class ShopTipsWindow : public IWindow, public CPriorityLayerColorDelegate
{
private:
	enum{
		udPRIORITYLAYER = 0,
		udMAINBG,
		udNAME,
		udPRICE,
		udPRICEVALUE,
		udPRICEICON,
		udSTATEMENT,
	};
public:
	ShopTipsWindow();
	virtual ~ShopTipsWindow();

private:
	inline void _initLayout();
	inline void _initValue(ShopTipsData* data);
	inline void _setMoneyType(int itype);
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
		�����¼�����
	*/
	void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		�ڸǲ�ص�
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
};


#endif
