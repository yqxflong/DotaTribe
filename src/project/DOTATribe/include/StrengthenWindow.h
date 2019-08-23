//Name : StrengthenWindow
//Function : 装备的一系列强化
//Author : 尹强

#ifndef _DOTATRIBE_StrengthenWindow_H_
#define _DOTATRIBE_StrengthenWindow_H_

#include "../include/IWindow.h"
#include "../include/SubView.h"

//页签索引
static int ESTREN_TAB1=1;
static int ESTREN_TAB2=2;
static int ESTREN_TAB3=3;

class CMenuItemSprite;
class BagEquipData;
class StrengthenWindow : public IWindow
						,public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	enum{
		kBG,
		kBG_2,
		kARROW_UP,
		kARROW_UPMOVE,
		kARROW_DOWN,
		kARROW_DOWNMOVE,
		kDECORATION,
		kHELP,
		kCLOSE,
		kDIAMONDBAR,
		kGOLDBAR,
		kDIAMOND_LABEL,
		kGOLD_LABEL,
		kTAB_1,
		kTAB_1_LABEL,
		kTAB_2,
		kTAB_2_LABEL,
		kTAB_3,
		kTAB_3_LABEL,
		kTAB_4,
		kTAB_4_LABEL,
		kTABLE,
		kCELLNODE,
		kTOGGLE,
		kTOGGLEBAR,
		kTOGGLE_LABEL,
		kEMPTY_LABEL,
	};
	enum{
		kCELL_BGBTN,
		kCELL_EBOARD,
		kCELL_EQUIPED,
		kCELL_ENAME,
		kCELL_STAR,
	};
	int m_nCurTab;		//当前选的Tab==枚举中的Tab
	HLSubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;
	cocos2d::CCSize m_szCell;		//cell大小
	cocos2d::extension::CCTableView* m_pTable;		//左边装备列表
	bool m_bIsOnlyShowEquiped;		//记录是否仅显示已装备
	int m_nLastCellIDX_tab1;				//记录上个cell=tab1
	int m_nLastCellIDX_tab2;				//记录上个cell=tab2
	int m_nLastCellIDX_tab3;				//记录上个cell=tab3
	int m_nLastCellIDX_tab4;				//记录上个cell=tab4

	int m_nLastSelectEquipId1;
	int m_nLastSelectEquipId2;
	int m_nLastSelectEquipId3;
	int m_nLastSelectEquipId4;

	int m_HeroIndex;
	//记录上次发的给子页面的equipID
	int m_nLastEquipID_ToSubView;
	bool m_bIsForceNotifySubView;		//是否强行通知子页面

	bool m_bShowIsEnd;		//显示结束

public:
	enum{
		ESEQUIPLVUP,		//装备升级
		ESEQUIPMAKEPROGRESS,	//装备进阶
		ESEQUIPTRAIN,			//装备洗练
	};
	StrengthenWindow();
	virtual ~StrengthenWindow(){};

public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();

protected:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		显示面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		渐隐面板事件处理
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void _initLayout();
	inline void _initEmptyLabel();
	inline void _mapBtn();
	inline void _mapTable();
	inline void _resetAllHighlight();
	inline void _highlightTabItem(unsigned int idx);
	inline void _loadSubView(unsigned int idx);
	inline void _selectTabItem(unsigned int idx);
	
	//begin:cell
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell);
	//end


	inline void _toggleSeleted(bool isselected);
	inline void _cellSelected_Tab1(CMenuItemSprite* cc);
	inline void _cellSelected_Tab2(CMenuItemSprite* cc);
	inline void _cellSelected_Tab3(CMenuItemSprite* cc);
	inline void _cellSelected_Tab4(CMenuItemSprite* cc,bool bNofity=false);

	//begin:handle equiplist
	inline void _reloadEquipListByTab();
	inline void _reloadEquipList_lvup();
	inline void _reloadEquipList_lvup_afterResult();
	inline void _reloadEquipList_progress();
	inline void _reloadEquipList_progress_afterResult();
	inline void _reloadEquipList_train();
	inline void _reloadEquipList_Recast();
	inline void _clearEquipList();
	//end

	//refresh Money and diamond
	inline void _mapMoneyAndDiamond();

	/*
		恢复窗口参数
	*/
	inline void _resetWindowParams();

	/*
		空列表时通知子页面
	*/
	inline void _notifySubViewWhenEmpty();

	/*
		在列表改变或者默认时通知子页面
	*/
	inline void _notifySubViewDefault();

	/*
		通知子页面选中的装备id
	*/
	inline void _notifySubViewEquipID(int equipID);

	/*
		刷新装备列表且纠正没选中装备的情况
	*/
	void _refreshEquipListAndCheckEquipSelected();

	/*
		刷新装备列表且纠正没选中装备的情况
		#恢复偏移量
	*/
	void _refreshEquipListAndCheckEquipSelected_setOffSet();

	/*
		纠正没选中装备的情况
	*/
	void _checkEquipSelected();

	/*
		检测左边装备列表是否为空
	*/
	void _checkEquipListIsEmpty(int equipID);
	
	/*
		获取要显示的文字
	*/
	std::string _getShowText(int index);

	/*
	    强制取消勾选已装备按钮
		*/
	void  _forceChancelEquipState();

	void  _activeFirstCellForRecast();
protected:
	/*
		按钮事件
	*/
	void On_Click_Event(cocos2d::CCObject* pSender);
	/*
		tab回调
	*/
	void On_Tab_Selected(cocos2d::CCObject* pSender);

	/*
		Cell 选择回调事件
	*/
	void On_Cell_Click_Event(cocos2d::CCObject* pSender);

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

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	bool					m_bScrollBegin;
	bool					m_bScrollEnd;
	cocos2d::CCPoint		m_offSetPoint;
};


#endif