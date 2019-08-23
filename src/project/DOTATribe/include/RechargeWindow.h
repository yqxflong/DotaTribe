// Name : RechargeWindow.h
// Function:��ֵ����
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

	cocos2d::CCNode* m_pRoot;	  //��ǰ���ڽڵ�	
	cocos2d::CCNode* m_pRechargeNode;//��ֵAutococo�ڵ�
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
	��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		��ʾ��ֵ����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		���س�ֵ����¼�����
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		���³�ֵ����¼�����
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_ColseBtn(cocos2d::CCObject* pSender);

	void On_Click_BtnClick(cocos2d::CCObject* pSender);
	/*
		�׳尴ť����
	*/
	void On_Click_FirstRechBtn(cocos2d::CCObject* pSender);
public:
	/*
		ˢ����ʯ
	*/
	void refreshDiamondUIData();
};

#endif
