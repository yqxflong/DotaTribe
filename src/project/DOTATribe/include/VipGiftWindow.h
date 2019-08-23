//Name:VipGiftWindow
//Author: lvyunlong
//Func: Activity of vip gift
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_VIPGIFTWINDOW_H_
#define  _DOTATRIBE_VIPGIFTWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ActivityDataHandler.h"
class VipGiftWindow : public IWindow 	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
			udBGBIG = 0,
			udBG1,
			udEXPLAINTTF,
			udTABLE,
			udTABLECELL,
			udARROWLEFT,
			udARROWRIGHT,
			udARROWLEFTMOVE,
			udARROWRIGHTMOVE,
		};

	enum{
		CELL_VIPBG,
		CELL_NAMETTF,
		CELL_GIFTBOXBTN,
		CELL_GIFTBOXBG1,
		CELL_GIFTBOXICON,
		CELL_COSTPRICE,
		CELL_COSTPRICEICON,
		CELL_COSTMONEY,
		CELL_COSTMONEYBG,
		CELL_OFFERPRICE,
		CELL_OFFERPRICEICON,
		CELL_OFFERMONEY,
		CELL_OFFERMONEYBG,
		CELL_BUYBTN,
		CELL_BUYBTNTTF,
	}CELL;
private:
	int m_CurWindowActiviId;
	IByte m_CurBuyVipLevel;
public:
	VipGiftWindow();
	virtual ~VipGiftWindow();
public:
	cocos2d::extension::CCTableView* m_pTable;    //CCTableView控件
	cocos2d::CCSize m_szCellGift;	//附件大小
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _initCell();
	inline void _mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setTableView(); //设置TableView
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	void _setVipBox(VipGiftItem *data,cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	
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

	/*
		显示VIP礼包事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏VIP礼包事件处理
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新VIP礼包事件处理
	*/
	inline void  OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		返回VIP礼包事件处理
	*/
	inline void  OnBackQAWindowEventHandler(std::list<std::string>& paramList);
private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	void On_Click_Buy_Enevnt(cocos2d::CCObject* pSender);
	/*
		查看奖励按钮回调
	*/
	void On_CheckItem_Click(cocos2d::CCObject* pSender);
};


#endif