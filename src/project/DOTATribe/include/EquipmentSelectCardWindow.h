//Name：EquipMentSelectWindow
//Function：选择装备素材
//Written By：尹强

#ifndef  _DOTATRIBE_EQUIPMENTSELECTCARDWINDOW_H_
#define  _DOTATRIBE_EQUIPMENTSELECTCARDWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include "../include/EquipmentLvUpDataHandler.h"

class BagEquipData;
class EquipmentSelectCardWindow:public IWindow
	, cocos2d::extension::CCTableViewDataSource
{
private:
	enum{
		udGRAYLAYER,
		udBG,
		udTITLE,
		udCLOSEBTN,
		udCONFIRMLB,
		udCONFIRMBTN,
		udTOGGLE1,
		udTOGGLE2,
		udTOGGLE3,
		udTOGGLE1_BG1,
		udTOGGLE1_BG2,
		udTOGGLE1_BG3,
		udTOGGLE1_BG1_LABEL,
		udTOGGLE1_BG2_LABEL,
		udTOGGLE1_BG3_LABEL,
		hTABLE,
		hTABLECELL,
		hCOUNTER,
		hCOUNTERBG,
		hCOUNTER_TITLE,
	}WINDOW;
	enum{
		cellBG1,
		cellBG2,
		cellBG3,
		cellITEMBOARD1,
		cellITEMBOARD2,
		cellITEMBOARD3,
		cellNAME1,
		cellNAME2,
		cellNAME3,
		cellTYPE1,
		cellTYPE2,
		cellTYPE3,
		cellSELECT1_BG,
		cellSELECT2_BG,
		cellSELECT3_BG,
		cellSELECT1,
		cellSELECT2,
		cellSELECT3,
		cellSTAR1,
		cellSTAR2,
		cellSTAR3,
	}CELL;

	cocos2d::CCNode * m_pWRootNode;	//当前窗口节点，用于挂载当前窗口
	int m_nShowWindow;			//离开时去哪个window

	cocos2d::CCSize m_nCellSize;	//cell的大小
	cocos2d::extension::CCTableView* m_pTable;

	std::vector<EquipCardsStructure> m_vecCardList;

	int  m_nCurCount;//当前选中的数量
	int m_nTotalCount;//总数

public:
	EquipmentSelectCardWindow();
	virtual ~EquipmentSelectCardWindow(){};

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

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		隐藏面板事件处理
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void _initData();
	inline void _initLayout();
	inline void _mapTable();
	inline void _mapBtn();

	void _createTableCell(cocos2d::extension::CCTableViewCell * cell);

	void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);

	void _setBlockInfo(cocos2d::CCNode * block, int idx);

	void _setBlockStar( int key,cocos2d::CCNode * block,BagEquipData* bb);

	void _setSelectPicVisible(cocos2d::CCNode * cell, int idx, bool visible);

	

	void _setBlockVisiable(cocos2d::CCNode * block, int blockidx, bool visiable);

	//获取当前选中的个数
	void _checkCurTickCount();
	//显示当前选中的个数 
	void _showCurTickCount();

	//卡牌过滤
	void On_Toggle_Click_Event(cocos2d::CCObject * pSender);
	/*
		检查全选状态
	*/
	inline void _checkTickAll();

	/*
		cell中block的相应函数
	*/
	void On_Click_Block(cocos2d::CCObject * pSender);

	void _setToggleSelect(int key, bool selected);

private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

protected:
	virtual void On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
