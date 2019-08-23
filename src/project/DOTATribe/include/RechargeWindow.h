// Name : RechargeWindow.h
// Function:充值窗口
// Author : lvyunlong
// Date: 20131118

#ifndef  _DOTATRIBE_RECHARGEWINDOW_H_
#define  _DOTATRIBE_RECHARGEWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class RechargeWindow : public IWindow
{
private:
	enum{
		udPriorityBG = 0,
		udBG,
		udPriorityLayerColor,
		udSceneEffect,
		udFIRSTRECHEFFECT,
		udFIRSTRECHTEXT,
		udFIRSTBTN,
		udCloseBtn,
		udMENU1,
		udMENU2,
		udMENU3,
		udMENU4,
		udMENU5,
		udMENU6,
		udVIPEFFECT,
		udVIPBTN,
		udVIPBTNTEXT,
		udTTFNAME1,
		udTTFNAME2,
		udTTFNAME3,
		udTTFNAME4,
		udTTFNAME5,
		udTTFNAME6,
		udTTFPRICE1,
		udTTFPRICE2,
		udTTFPRICE3,
		udTTFPRICE4,
		udTTFPRICE5,
		udTTFPRICE6,
		udTTFNUM1,
		udTTFNUM2,
		udTTFNUM3,
		udTTFNUM4,
		udTTFNUM5,
		udTTFNUM6,
		udRECHARGETOVIPTEXT,
		udEFFECTRECHARGE,
		udTUIJIAN1,
		udDESCRIBE1,
		udTUIJIAN2,
		udDESCRIBE2,
		udTUIJIAN3,
		udDESCRIBE3,
	};

	cocos2d::CCNode* m_pRoot;	  //当前窗口节点	
	cocos2d::CCNode* m_pRechargeNode;//充值Autococo节点
	bool m_bIsPayTick;
	int m_PayTickCount;
	int m_PayGoodsIndex;
public:
	RechargeWindow();
	virtual ~RechargeWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _setTextName();
	inline void _setTextNum();
	inline void _setTextPrice();
	inline void _setTextVip();
	void _setFirstRech(int sum);
	void _setDoubleView();

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
		显示充值面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏充值面板事件处理
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新充值面板事件处理
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_ColseBtn(cocos2d::CCObject* pSender);

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
	/*
		首冲按钮奖励
	*/
	void On_Click_FirstRechBtn(cocos2d::CCObject* pSender);
public:
	/*
		刷新钻石
	*/
	void refreshDiamondUIData();
};

#endif
