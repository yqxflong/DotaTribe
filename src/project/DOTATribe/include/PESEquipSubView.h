//Name：PESEquipWindow
//Function：给英雄装备
//Written By：尹强
//AnchorPoint:  (0.5,0.5) can not change

#ifndef  _DOTATRIBE_PESEQUIPSUBVIEW_H_
#define  _DOTATRIBE_PESEQUIPSUBVIEW_H_

#include "../include/HeroWindowSubView.h"
#include "../include/BagEquipDataHandler.h"
#include "spine/spine-cocos2dx.h"
#include "../include/CTouchSprite.h"
#include "../include/CMenuItemSprite.h"
#include "../include/DTEquipBoard.h"

struct _EQUIPITEM_{
	int starCount_;
	BagEquipData *equipdata_;

	_EQUIPITEM_(){
		starCount_=-1;
		equipdata_=NULL;
	}
};

class HEHeroPropertyNode;

class PESEquipSubView :public HeroWindowSubView,public cocos2d::extension::CCTableViewDataSource
	,public DTEquipBoardDelegate
{
private:
	enum{
		kBG,
		kBTN_STRENGTHEN_BTN,
		kBOTTOM_NODE,
		kBOARD_1,
		kBOARD_2,
		kBOARD_3,
		kBOARD_4,
		kBOARD_5,
		kBOARD_6,
		kBOARD_7,
		kBOARD_8,
		kHERO,
		kSTAR,
		kNAME,
		kEQUIPCOUNT_BG,
		kEQUIPCOUNT,
		kLINKNODE,	//无装备链接占位点
		kTABLE,
		kTABLECELL_SUBTITLE,
		kTABLECELL,
	}WINDOW;
	enum{
		//begin:Equip
		kCELLBG,
		kCELLBOARD,
		kCELLEQUIPNAME,
		kCELLMAINPROP,		//主属性
		kCELLEQUIPSCOREVALUE,
		kCELLBTN,
		kCELLBTN_LABEL,
		kCELLSCOREARROW,		//战力箭头
		kCELLTYPE,		//装备类型
		//end
		//begin:Title
		kCELL_TITLE_BG,			//背景
		kCELL_TITLE_STAR,		//星级
		//end
	};

	//@当前英雄idx
	int m_nCurHeroIdx;
	HEHeroPropertyNode* m_pBottomNode;
	cocos2d::CCNode* m_pLinkNode;
	cocos2d::extension::CCTableView* m_pTable;		//右边装备列表界面
	//
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//英雄角色
	cocos2d::CCSize m_szCELL_ITEM;			//装备的cell大小
	cocos2d::CCSize m_szCELL_TITLE;			//title的cell大小
	cocos2d::CCPoint m_cpTableCurOffset;		//当前列表的offset
	float m_fTableCurHeight;		//当前列表的内容高度
	std::vector<_EQUIPITEM_> m_vecList;		//local的背包装备数据
public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	virtual void onChangeTabIndex(int idx);
public:
	PESEquipSubView();
	virtual ~PESEquipSubView(){};
	/*
		装备一件装备
	*/
	void equipEquipmentByID(int id,int heroIdx=0);		//instance id

private:		
	void _initLayout();			//初始化布局，需要再create之后调用
	void _mapBtn();
	void _mapTable();
	//@根据idx刷新界面对应英雄数据
	void _refreshHeroByIdx(int idx);
	void _refreshData();
	void _refreshBagEquip();
	void _refreshEquipCount();
//begin:英雄属性
	void _refreshHeroNameAndStarLv(int idx=0);
	void _refreshRoleEquip(int idx=0);
	void _refreshHeroShape(int idx=0);
//end
	//
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	//
	void _setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setCellEquip(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipType(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipName(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipMainProp(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipScore(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipScoreArrow(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipBtn(int idx,BagEquipData* ed,cocos2d::CCNode* cell);
	void _mapCellBtn(cocos2d::CCNode* cell);
	//
	//begin:setcell for expball
	void _setCellExpBall_Descrip(BagEquipData* ed,cocos2d::CCNode* cell);
	//end
	//
	//
	//@显示英雄详细信息
	void _showHeroDetailNode();

	//@更改英雄信息模块信息
	void _refreshHeroDetailNodeInfo(int tabidx);

	//请求服务器卸掉装备
	void _request4leaveEquip(int etype);

	//根据装备id给人物换装
	void _equipEquipment(int idx);

	/*
		刷新空装备链接
	*/
	void _refreshLinkNode();

	/*
		Cell 显示title
	*/
	void _cell_showTitle(cocos2d::CCNode* cell);

	/*
		Cell 显示装备
	*/
	void _cell_showEquip(cocos2d::CCNode* cell);

	/*
		Cell 显示经验珠
	*/
	void _cell_showExpBall(cocos2d::CCNode* cell);


	/*
		刷新装备列表，但是记住原来位置
	*/
	void _refreshTableViewButRememberOldPos();
	
protected:
	  /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     * 
     * @return number of cells
     */
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
public:
	void On_Click_Event(cocos2d::CCObject* pSender);

	/*
		强化按钮
	*/
	void On_Click_Streng_Event(cocos2d::CCObject* pSender);
	/*
		装备icon点击回调
	*/
	virtual void CallBack_ClickEquip(int type,int equipID);

	//装备按钮点击事件
	void On_Cell_Click_Event(cocos2d::CCObject* pSender);

	/*
		刷新身上装备
	*/
	void On_RefreshRoleEquip();

	/*
		刷新装备列表
	*/
	void On_RefreshEquipList();

	/*
		Tips回调装备
	*/
	void On_Tips_CallBack_Equip(int idx);
	/*
		Tips回调卸载
	*/
	void On_Tips_CallBack_Disboard(int type);

	/*
		主窗口的通知
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
};


#endif
