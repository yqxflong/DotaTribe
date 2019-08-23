// Name : HeroIllustratedWindow
// Function:英雄图鉴窗口
// Author : Johny


#ifndef  _DOTATRIBE_HeroIllustratedWindow_H_
#define  _DOTATRIBE_HeroIllustratedWindow_H_

#include "cocos-ext.h"
#include "IWindow.h"
#include "HeroIllustratedDataHandler.h"

using  namespace  cocos2d;
using namespace cocos2d::extension;

class HeroIllustratedWindow : public IWindow , public cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate
{
protected:
		int m_nBackType;  			//附加窗口类型
		int m_nHeroPos;				//英雄在队伍中的位置
public:
	enum
	{
		_BG_MARK_,
		_BG_IMAGE_,
		_CLOSE_BTN_,
		_SWITCH_BTN_,
		_ALL_HERO_BG_,
		_ALL_HERO_CONTAIN_,
		_ALL_HERO_BTN_,
		_ALL_HERO_LABEL_,
		_POWER_HERO_BTN_,
		_POWER_HERO_LABEL_,
		_QUICK_HERO_BTN_,
		_QUICK_HERO_LABEL_,
		_INTELIGENCE_HERO_BTN_,
		_INTELIGENCE_HERO_LABEL_,
		_HERO_TABLE_VIEW_,
		_STAR_CELL_NODE_,
		_HERO_CELL_NODE_,
		_HERO_ANIMATION_CONFIG_,
		_HERO_NAME_LABEL_,
		_HERO_LEVEL_,
		_HERO_LEVEL_NUM_,
		_HERO_STAR_LABEL_,
		_HERO_POWER_LABEL_,
		_HERO_POWER_NUM_,
		_HERO_QUICK_LABEL_,
		_HERO_QUICK_NUM_,
		_HERO_INTELIGENCE_LABEL_,
		_HERO_INTELIGENCE_NUM_,
		_HERO_ATTACKGROW_LABEL_,
		_HERO_ATTACK_PASS_BG_,
		_HERO_ATTACK_INTERPASS_BG_,
		_HERO_HPGROW_NUM_,
		_HERO_HP_PASS_BG_,
		_HERO_HP_INTERPASS_BG_,
		_HERO_SPEEDGROW_NUM_,
		_HERO_SPEEDGROW_BG_,
		_HERO_SPEDDGROW_INTERPASS_BG_,
		_HERO_MPGROW_NUM_,
		_HERO_MPGROW_BG_,
		_HERO_MPGROW_INTERPASS_BG_,
		_HERO_BUFFER_NAME_,
		_HERO_BUFFER_DESC_NAME_,			//Buffer 描述
		_HERO_DESC_BTN_,
		_HERO_DESC_LABEL_,
		_HERO_EXPAND_BTN_,
		_HERO_EXPAND_LABEL_,
		_HERO_TIPS1_LABEL_,
		_HERO_TIPS2_LABEL_,
		_HERO_TIPS3_LABEL_,
		_HERO_TIPS4_LABEL_,
		_HERO_CHANGE_BTN_,
		_HERO_CHANGR_LABEL_,
		_HERO_ADVANCE_BTN_,
		_HERO_ADVANCE_LABEL_,
		_HERO_TIPS_MARK_BG_,
		_HERO_CALL_HERO_LABEL_,
		_HERO_HERO_SOUL_BTN_,		//英雄战魂按钮
		_HERO_ANIMATION_NODE_=1000,
	};

	enum
	{
		_STAR_BG_,
		_STAT_PROGRESS_,

	};
	enum
	{
		_HIGHT_LIGHT_BG_,
		_HERO_ICON_,
		_HERO_TYPE_,
		_HERO_NAME_BG_,
		_HERO_NAME_CELL_LABEL_,
		_HIGHT_LIGHT_BG_2,
		_HERO_ICON_2,
		_HERO_TYPE_2,
		_HERO_NAME_BG_2,
		_HERO_NAME_CELL_LABEL_2,
		_HIGHT_LIGHT_BG_3,
		_HERO_ICON_3,
		_HERO_TYPE_3,
		_HERO_NAME_BG_3,
		_HERO_NAME_CELL_LABEL_3,
		_HIGHT_LIGHT_BG_4,
		_HERO_ICON_4,
		_HERO_TYPE_4,
		_HERO_NAME_BG_4,
		_HERO_NAME_CELL_LABEL_4,
	};
	enum
	{

		_HERO_START_1=0,
		_HERO_START_2=6,
		_HERO_START_3=12,
		_HERO_START_4=18,
		_HERO_CELL_END_=19,
		_HERO_CELL_NUN_=5,
	};

	//内部更新数据事件枚举
	enum
	{
		_UPDATE_FOR_HERO_EXPAND_TYPE_,					//刷新扩展信息通知
		_UPDATE_FOR_SUCCESS_REPLACE_HERO_TYPE_,			//更换英雄成功通知
		_UPDATE_FOR_ERROR_TYPE_,						//更换英雄错误通知
		_UPDATE_FOR_ENTER_ADVANCE_TYPE_,				//进入英雄进阶通知
		_UPDATE_FOR_HERO_SOUL_TYPE_,					//进入英雄战魂通知
	};
	 
	HeroIllustratedWindow();
	virtual ~HeroIllustratedWindow();
public:
	//@Standard
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
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

	/*
	Cell按钮点击事件通知
	*/
	void   CellBtnSelectorHandler(cocos2d::CCObject * pSender);

protected:
	/*
	 Table View 相关接口
	*/
	//绑定TableView
	void  setTableView();
	 
	/*
	  创建TableCell中的数据
	*/
	virtual    void    createTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	/*
      根据索引设置Cell的内容
	*/
	virtual    void    setTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex,bool isNeedCear=false);

	/*
	获取指定Cell的高宽
	*/
	virtual    cocos2d::CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	 
	/*
	获得指定Cell
	*/
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

	/*
	容器Cell总数
	*/
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	/*
	容器Cell点击事件
	*/
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){}
	  
	/*
	滚动完毕回调
	*/
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	/*
	缩放完毕回调
	*/
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	/*
	刷新TableView
	*/
	void  refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	//to do
	void  refreshTableViewOffCount(cocos2d::extension::CCTableView* tb,int heroCellCount,int starCellCount) const 
	{
		tb->reloadData(); 
		tb->setContentOffset(ccp(0,-tb->getContainer()->getContentSize().height+m_StarCellSize.height*starCellCount+m_HeroCellSize.height*heroCellCount));
	}

protected:
	/*
	UI布局创建
	*/
	void    InitUILayOut();
	void    BindSelectorForBtn();
	void    AttachMemData();
	void    DetachMemData();
	void    InitDefaultSetting();
	void    ChangeIllustatedTabType(int illustratedType);
	void    UpdateHeroCellListWithType();
	void    ChangeSwitchBtn();
	IHeroCellItem *	 GetCellTypeFromConfig(int cellIndex,cocos2d::CCSize & cellSize);
	IHeroCellItem *  GetCellTypeFromCellIndex(std::vector<IHeroCellItem *> & cellItem,int cellIndex);
	unsigned int     GetNumberCellsList();
	void     RemoveHeroCellFromTableCell(cocos2d::extension::CCTableViewCell* cell ,int exsitNum);
	void     SetHeroCellItem(int cellIndex,cocos2d::extension::CCTableViewCell* cell ,int cellItemIndex,IHeroSkinItem * pHeroSkinItem);

	void     ChangeCellItemState(int cellIndex,int cellItemIndex,int heroID);
	void	 ShowHeroExpandInfoLayer();
	void	 UpdateHeroAnimation(int heroShapeID);     
	void     ShowDetailedHeroInfo();
	void     CallInDetailedHeroInfo();
	void	 UpdateChangeHeroBtnState(); 
	void	 UpdateAdvanceHeroBtnState();
	void     DispatchUpdateEventHandler(int eventType);
	void     CheckCellListEmptyEvent(int illustrateType);
	void     CalActiveHeroCelllConfig(int illustrateType);
	void     SetCallNewHeroLayerVisiable(bool isVisiable);
	void     UpdateHeroSoulBtnState();

private:
	cocos2d::CCNode *   GetRootNode();
	cocos2d::extension::CCTableView *	m_pTable;
	cocos2d::CCSize     m_StarCellSize;
	cocos2d::CCSize     m_HeroCellSize;
	int					m_bCurIllustatedType;
	bool				m_bIsShowAllDB;
	int				    m_nActiveCellIndex;
	int					m_nActiveCellItemIndex;
	int					m_nActiveHeroID;
	int					m_nHeroCellOffSetCount;
	int					m_nStarCellOffSetCount;
};
#endif
