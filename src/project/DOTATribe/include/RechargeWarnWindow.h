// Name : RechargeWarnWindow.h
// Function:��ֵ��ʾ���˺ŶԻ��򴰿�
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

	cocos2d::CCNode* m_pRoot;	  //��ǰ���ڽڵ�	
	cocos2d::CCNode* m_pWarnBoxNode;//��ֵ��Autococo�ڵ�
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
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void   OnHideWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_ColseBtn(cocos2d::CCObject* pSender);

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
};

#endif
