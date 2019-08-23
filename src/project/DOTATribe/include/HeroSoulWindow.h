#ifndef  _DOTATRIBE_HEROSOULWINDOW_H_
#define  _DOTATRIBE_HEROSOULWINDOW_H_

#include "../include/IWindow.h" 
#include "../include/HeroAdvancedDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/HeroSoulDataHandler.h"
#include "../include/AnimationEffect.h"




////////////////////////////////////////////////////////////////
//Name:	 HeroSoulWindow
//Auchor: 	xiaobo.wu
//Func:	 英雄战魂激活窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

class HeroSoulWindow : public IWindow ,public  AnimationEffectCallBackProtocol
{
protected:
	int m_SubType;  		//附加窗口类型
private:
	enum 
	{
		_UI_BG_MARK_,
		_UI_BG_,
		_UI_HELP_BTN_,
		_UI_CLOSE_BTN_,
		_UI_TITLE_BG_,
		_UI_TITLE_LABEL_, 
		_UI_CHALLENEGE_LABEL_,
		_UI_CHALLENEGE_BG_,
		_UI_CHALLENEGE_ROLE_BG_,
		_UI_ROLE_CONFIG_NODE_,
		_UI_CHALLENGE_COUNT_BG_,
		_UI_CHALLENGE_COUNT_LABEL_,
		_UI_CHALLENGE_COUNT_VALUE_,
		_UI_ADVISE_CHALLENGE_LEVEL_,
		_UI_CHALLENGE_BTN_,
		_UI_CHALLENGE_LABEL_,
		_UI_CHALLENGE_NEED_COUNT_,
		_UI_CHALLENGE_NEED_IMAGE_,
		_UI_DIAMONDS_BG_,
		_UI_DIAMONDS_LABEL_,
		_UI_GOLD_BG_,
		_UI_GOLD_LABEL_,
		//////////////////////////////////////////////////////////////////////////
		_UI_ACTIVE_UP_BG_,
		_UI_ACTIVE_HERO_ICON_,
		_UI_ACTIVE_TALENT_LABEL_,
		_UI_ACTIVE_TALENT_VALUE_,
		_UI_ACTIVE_ATRIBUTE_LABEL_,
		_UI_ACTIVE_ATRIBUTE_VALUE_,
		_UI_ACTIVE_STATS_,
		_UI_ACTIVE_RIGHTNOW_USE_BTN_,
		_UI_ACTIVE_RIGHTNOW_USE_LABEL_,
		_UI_ACTIVE_DONW_BG_,
		_UI_ACTIVE_ADVANCE_LABEL_,
		_UI_ACTIVE_ITEM_1_,
		_UI_ACTIVE_ITEM_1_VALUE_,
		_UI_ACTIVE_ITEM_2_,
		_UI_ACTIVE_ITEM_2_VALUE_,
		_UI_ACTIVE_ITEM_3_,
		_UI_ACTIVE_ITEM_3_VALUE_,
		_UI_ACTIVE_ITEM_4_,
		_UI_ACTIVE_ITEM_4_VALUE_,
		_UI_ACTIVE_ACTIVE_BTN_,
		_UI_ACTIVE_ACTIVE_LABEL_,
		_UI_ACTIVE_FULLLEVEL_LABEL_,
		
		_UI_ROLE_NODE_=1000,
 	}; 
	enum
	{
		_ACTIVE_MSG_CAN_ACTIVE_,
		_ACTIVE_MSG_FULL_LEVEL_,
		_ACTIVE_MSG_NEED_ADVANCE_HERO_,
		_ACTIVE_MSG_NEED_ITEM_,
	};
public:
	HeroSoulWindow();
	virtual ~HeroSoulWindow();
public:
	/*
	初始化 注册窗口事件
	*/
	virtual    bool    Init();
	/*
	加载窗口Layout
	*/
	virtual    bool    Load();
	/*
	窗口帧
	*/
	virtual    void    Tick();
	/*
	窗口销毁
	*/
	virtual    void    Destroy();
	public:
	/*
	事件处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
	特效回调事件通知
	*/
	virtual    void    EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

	/*
	显示窗口事件
	*/
	void    OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
	公共按钮事件通知
	*/
	void    CommonBtnSelectorHandler(cocos2d::CCObject * pSender);

protected:	 
	void    ShowWindowWithType(); 
	void    InitHeroSoulChallengeView();
	void    InitHeroSoulActiveView();
	void    UpdateDiamondAndGold();
	void    InitUILayOut();
	void    BindSelectorForBtn();
	void    AttachMemData();
	void    DetachMemData(); 
private: 
	void    DispatchUpdateEventHandle(int eventType);
	void    ShowNeedItemICON(int uiIndex,NeedItemNode * pNeedItemNode);
	void    ShowNeedItemValue(int uiIndex,NeedItemNode * pNeedItemNode);
	void    SendActiveHeroSoul();
	void    OnPlayActiveEffect();
protected: 
	HeroSoulInfoData *		m_pHeroSoulInfoData;
	bool					m_bIsActiveHeroSoulType;
	bool					m_isNeedShowActivieEffect;
	int						m_BackWindow;
	int						m_BackTab;
	int						m_BackView;
};
#endif
