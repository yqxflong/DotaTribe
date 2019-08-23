// Name : HeroAltarWindow.h
// Function:英雄献祭窗口
// Author : lvyunlong
// Date: 20131130

#ifndef  _DOTATRIBE_HEROALTARWINDOW_H_
#define  _DOTATRIBE_HEROALTARWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/CTableView.h"
#include "../include/CProgressTimer.h"
#include "../include/CPriorityLayerColor.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class HeroAltarWindow : public IWindow ,public CProgressTimerDelegate, public CPriorityLayerColorDelegate
{
private:
	enum{
		udPRIORITYLAYER = 0,
		udSCENEEFFECT,
		udMAINBG,
		udBOTTOMBG,
		udTITLETEXTBG,
		udTITLETEXT,
		udQUICKCITYBTN,
		udHEROSUMMONBTN,
		udLEVELTEXTBG1,
		udLEVELTEXTBG2,
		udLEVELTEXTBG3,
		udLEVELTEXT1,
		udLEVELTEXT2,
		udLEVELTEXT3,
		udTOTEMTEXT1,
		udTOTEMTEXT2,
		udTOTEMTEXT3,
		udADDTEXT1,
		udADDTEXT2,
		udADDTEXT3,
		udSCHEDULEBG1,
		udSCHEDULEBG2,
		udSCHEDULEBG3,
		udSCHEDULE1,
		udSCHEDULE2,
		udSCHEDULE3,
		udMASKNODE1,
		udMASKNODE2,
		udMASKNODE3,
		udTOTEMICON1,
		udTOTEMICON2,
		udTOTEMICON3,
		udALTARBTN1,
		udALTARBTN2,
		udALTARBTN3,
		udALTARBTNTTF1,
		udALTARBTNTTF2,
		udALTARBTNTTF3,
	};

	enum
	{
		udVIEWPRIORITYBG,
		udVIEWMAINBG,
		udVIEWTITLETEXT,
		udVIEWTITLELEVELTEXT,
		udVIEWSUREBTN,
		udVIEWCANCELBTN,
		udVIEWSUREBTNTEXT,
		udVIEWCANCELBTNTEXT,
		udVIEWDEBRIS1,
		udVIEWDEBRIS2,
		udVIEWDEBRIS3,
		udVIEWDEBRIS4,
		udVIEWDEBRIS5,
		udVIEWDEBRIS6,
		udVIEWDEBRISCOUNTTTF1,
		udVIEWDEBRISCOUNTTTF2,
		udVIEWDEBRISCOUNTTTF3,
		udVIEWDEBRISCOUNTTTF4,
		udVIEWDEBRISCOUNTTTF5,
		udVIEWDEBRISCOUNTTTF6,
		udVIEWSCHEDULEBG1,
		udVIEWSCHEDULE1,
		udVIEWCURSTRENGTEXT,
		udVIEWNEXTSTRENGTEXT,
		udVIEWALTARTEXT,
	}DEBRISNODE;

	cocos2d::CCNode* m_pRoot;				//当前窗口节点	
	cocos2d::CCNode* m_pHAltarNode;			//献祭Autococo节点
	cocos2d::CCNode* m_pDebrisNode;			//碎片献祭节点
	int m_CurAltarType;						//当前献祭类型
	CProgressTimer *m_pProgress;	//献祭界面进度条
	int m_ViewHerolevel;					//英雄在献祭界面等级
	int m_ViewHeroCurExp;					//英雄在献祭界面经验
	int m_ViewHeroLaterlevel;				//点击碎片后的献祭级别
	float mAlatrlaterPos;					//献祭后的位置
	bool m_isBAltarDebriBtn;				//魂碎片按钮是否可按	
	int ArrTopNextValue[3];					//满级之后标志
	int m_Soulstonetype;
public:
	HeroAltarWindow();
	virtual ~HeroAltarWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _mapViewBtn();
	inline void _setText();
	inline void _setExp();
	inline void _setBtnViable();
	inline void _initProgressTimer();
	void _setProgress(int expvalue);
	void _setJump();
public:
	void SetfontByViplevel(int level);
	void ShowDebrisView(int type);
	void CallbackTTF(int level);
	void CallbackBtnEnable();
	void setLevelTop();

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

public:
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
private:
	/*
		显示图腾面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏图腾面板事件处理
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新图腾面板事件处理
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新献祭碎片面板事件处理
	*/
	inline void OnUpdateDebrisWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新献祭之后界面面板事件处理
	*/
	inline void OnUpdateOverWindowEventHandler(std::list<std::string>& paramList);
	/*
		回调献祭之后是否献祭
	*/
	inline void OnCallBackWindowEventHandler(std::list<std::string>& paramList);
	/*
		批量输入框后回调
	*/
	inline void OnInputWindowEventHandler(std::list<std::string>& paramList);
public:
	void On_Click_Event(cocos2d::CCObject* pSender);

	void On_Click_AltarBtn_Event(cocos2d::CCObject* pSender);

	void On_Click_DebrisBtn_Event(cocos2d::CCObject* pSender);

	void On_Click_DebrisView_Enevnt(cocos2d::CCObject* pSender);
public:
	virtual void CallBack_NextLevel();
	virtual void CallBack_RunFinish();
};

#endif
