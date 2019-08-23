// Name :		RevenueWindow.h
// Function:	µã½ð´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_REVENUEWINDOW_H_
#define  _DOTATRIBE_REVENUEWINDOW_H_


#include "IWindow.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
using namespace std;
class RevenueWindow : public IWindow,public AnimationEffectCallBackProtocol
{
public:
	RevenueWindow();
	virtual ~RevenueWindow(){};
	enum{

		RevenueBG,
		RevenueDiamondBG,
		RevenueDiamondEFFECT,
		RevenueDiamond,
		RevenueCloseButton,
		RevenueLv,
		RevenueExp,
		RevenueExpBG,
		RevenueExpSlip,
		RevenueExpValue,
		RevenueTip1,
		RevenueTip2,
		RevenueButton1,
		RevenueButton1Label,
		RevenueButton1Icon,
		RevenueButton1IconValue,
		RevenueCoolTime,
		//RevenueButton2,
		//RevenueButton2Label,
		//RevenueButton2Cost,
		//RevenueButton2Icon,
		RevenueButton3,
		RevenueButton3Label,
		RevenueButton3Cost,
		RevenueButton3Icon,

	};
	enum
	{
		Revenue_Free_Type,
		Revenue_Low_Type,
		Revenue_High_Type,
	};

	void InitLayer();
public:
	
	int	m_RevenueType;
	int	tempTime;
	bool	m_playEffect;
	bool	IsNeedUpdata;
	float					m_lastTime;
	CCLayer*				m_MyRootLayer;
	CPriorityLayerColor*	m_SmallLayer;
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:
	void	On_Close(cocos2d::CCObject* pSender);
	void	On_SingleClick(cocos2d::CCObject* pSender);
	void	UpdateRevenueInfo();
	void	CoolTimeTick();
	void	UpdataCoolTime(int second);
	void	PlaySceneFrameEffect(int sceneFrameEffectID);
	void	OnShowWindowEventHandler(std::list<std::string>& paramList);
	string	GetTimeString(int second);
	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	virtual void	EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

private:
	inline void _uckSetMarkLayerAndInitLayer();
	inline void _uckInitButton();	
	inline void _uckPlayEffect();
	inline void _uckFreeTimesSign();
	inline void _uckLv();
	inline void _uckExp();
	inline void _uckCoolTime();
	inline void _uckButton();
	inline void _uckSelectButton(CCMenuItemSprite* pItem);
};


#endif
