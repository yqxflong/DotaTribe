// Name :		ConvictionWindow.h
// Function:	ÐÅÑö´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_CONVICTIONWINDOW_H_
#define  _DOTATRIBE_CONVICTIONWINDOW_H_

#include "IWindow.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/HeroTechnologyDataHandler.h"
class ConvictionWindow : public IWindow,CPriorityLayerColorDelegate
{
public:
	ConvictionWindow();
	virtual ~ConvictionWindow();
	enum
	{
		Conviction_LEFT_BG,
		Conviction_POINT_BG,
		Conviction_POINT_LABEL,
		Conviction_POINT,
		Conviction_PERSON,
		Conviction_PRAY_BUTTON,
		Conviction_PRAY_BUTTON_LABEL,
		Conviction_PRAY_ARROW,
		Conviction_DIAMOND_COST,
		Conviction_DIAMOND_COST_IMAGE,
		Conviction_PRAY_FREE_TIMES_BG,
		Conviction_PRAY_FREE_TIMES,
		Conviction_INFO_LINE_1,
		Conviction_INFO_LINE_2,
		Conviction_INFO_LINE_3,
		Conviction_LVUP_BUTTON,
		Conviction_LVUP_BUTTON_LABEL,
		Conviction_ARROW_LEFT,
		Conviction_ARROW_RIGHT,
		Conviction_PAGE_BG,
		Conviction_PAGE_LABEL,
		Conviction_RESTING_BUTTON,
		Conviction_RESTING_BUTTON_LABEL,

		Conviction_IMAGE_1_BG,
		Conviction_IMAGE_1_ICON,
		Conviction_IMAGE_1_GREY_LAYER,
		Conviction_IMAGE_1_TOUCH_LAYER,
		Conviction_IMAGE_1_SELECT_FRAME,
		Conviction_IMAGE_1_NOOK_BG,
		Conviction_IMAGE_1_NOOK_LABEL,
		Conviction_IMAGE_1_NAME_LV,
		Conviction_IMAGE_2_BG,
	};
	void InitLayer();
public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:
	int m_Cur_Page;
	int m_Total_Page;
	int m_Select_Index;
	CCSprite* m_lastSelect;
	CMenuItemSprite* m_RestingButton;

	void On_Click_Resetting(cocos2d::CCObject* pSender);
	void On_Click_LvUp(cocos2d::CCObject* pSender);
	void On_Click_Pray(cocos2d::CCObject* pSender);
	void On_Click_Page(cocos2d::CCObject* pSender);


	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);
	
	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	virtual void	touchEvent(CPriorityLayerColor* pLayerColor);
private:
	void _checkNewFunc();
	inline void _uckInitButton();
	inline void _uckSetSelect(CPriorityLayerColor* pLayerColor);
	inline void _uckUpdataPageInfo();
	inline void _uckUpdataConvictionInfo();
	inline void _uckUpdataConvictionPoint();
	inline void _uckUpdataConvictionIcon();
	inline void _uckUpdataRestingButton();
	inline void _uckUpdatePrayCost();
	inline void _uckSendResettingPacket();
	inline void _uckSendLvUpPacket();
	inline void _uckSendPrayPacket();
	inline void _uckSetPage(CMenuItemSprite* pItem);

	inline void _uckHideConvictionInfo();
	inline void _uckSetConvictionInfo();
	inline void _uckCheckConvictionIsMaxLv();
	inline void _uckCheckPrayFreeTimes();
	inline void _uckSetPrayCostPoint();
	inline void _uckSetPrayButton();
	inline void _uckSendGetTechnologyPointPacket();

	inline void _uckSetTechnologyCell(int key,int index);
	inline void _uckHideTechnologyCell(int key);
	inline void _uckSetTechnologyBG(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyIcon(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyGreyLayer(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyTouchLayer(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologySelectFrame(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyNookBG(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyNookLv(HeroTechnology* pTechnologyData,int key);
	inline void _uckSetTechnologyNameAndLv(HeroTechnology* pTechnologyData,int key);
};


#endif
