#ifndef  _DOTATRIBE_HeroAdvancedWindow_H_
#define  _DOTATRIBE_HeroAdvancedWindow_H_
#include "../include/IWindow.h"
#include "../include/HeroAdvancedDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"

////////////////////////////////////////////////////////////////
//Name:	 HeroAdvanceWindow
//Auchor: 	xiaobo.wu
//Func:	 英雄进阶窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////


class HeroAdvancedWindow : public IWindow
{
protected:
	int m_SubType;  		//附加窗口类型
public:
	enum
	{
		_BG_MARK_,
		_BG_IMAGE_,
		_CLOSE_BTN_,
		_ADVANCED_TITLE_BG_,
		_HERO_BG_1_,
		_HERO_NODE_1_,
		_HERO_STAR_LABEL_1_,
		_Derection_BG_1_,
		_HERO_BG_2_,
		_HERO_UnLight_BG_2_,
		_HERO_EFFECT_2_,
		_HERO_NODE_2_,
		_HERO_STAR_LABEL_2_,
		_Derection_BG_2_,
		_HERO_BG_3_,
		_HERO_UnLight_BG_3_,
		_HERO_EFFECT_3_,
		_HERO_NODE_3_,
		_HERO_STAR_LABEL_3_,
		_HERO_ITEM_COMMON_BG_,
		_ITEM_OBJ_1_,
		_ITEM_NUM_1_,
		_ITEM_OBJ_2_,
		_ITEM_NUM_2_,
		_ITEM_OBJ_3_,
		_ITEM_NUM_3_,
		_ITEM_OBJ_4_,
		_ITEM_NUM_4_,
		_GOLD_NUM_,
		_GOLH_ICON_,
		_ADVANCED_BTN_,
		_DIAMON_BG_,
		_DIAMON_NUM_LABEL_,
		_GOLD_BG_,
		_GOLD_BG_LABEL_,
		_ADVANCED_LABEL_BNT_,
		_ADVANCE_COMPLETE_LABEL_,

		_HERO_ANIMATION_1_=1000,
		_HERO_ANIMATION_2_=1001,
		_HERO_ANIMATIOn_3_=1003,
	};

	enum
	{
		_UPDATE_FOR_ADVANCE_SUCCESS_TYPE_,
	};

public:
	HeroAdvancedWindow();
	virtual ~HeroAdvancedWindow();
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
	显示窗口事件
	*/
	void    OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
	公共按钮事件通知
	*/
	void   CommonBtnSelectorHandler(cocos2d::CCObject * pSender);
	protected:
	/*
	UI布局创建
	*/
	void    InitUILayOut();
	void    BindSelectorForBtn();
	void    AttachMemData();
	void    DetachMemData();
	void    AnalyseCurAdvanceData();
	void    AnalyseAdvanceNeedInfoByHeroID(int heroID);
private:
	cocos2d::CCNode *  GetRootNode();
	void   ShowAdvancedInfoByItem(HeroAdvanceSingleItem * pHeroAdvancedSingleItem);
	void   ShowAllHeroAnimation();
	void   ShowHeroAniamtionWithData(int configUIIndex,int animationIndex,cocos2d::CCNode * pParent,int shapeID);
	void   UpdatePlayerDiamonAndGold();
	void   DispatchUpdateEventHandle(int eventType);
protected:
	HeroAdvancedData *			  m_pHeroAdvanceData;
	std::vector<IHeroSkinItem *>  m_vShowHeroVector;
	HeroAdvanceSingleItem *		  m_pActiveHeroAdvanceItem;
	bool					      m_bOnlyTwoShape;
	int							  m_nAdvanceHeroIndex;
};
#endif
