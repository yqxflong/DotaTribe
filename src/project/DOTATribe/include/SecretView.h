//Name：SecretView
//Function：秘宝商店
//Written By：lvyunlong
//Time：2013-9-11

#ifndef  _DOTATRIBE_SECRETVIEW_H_
#define  _DOTATRIBE_SECRETVIEW_H_

#include "../include/SHSubView.h"
#include <string>
#include "../include/ShopInfoDataHandler.h"

#define  LONGBLOODSTONE    28110

class SecretView :public SHSubView
	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
public:
	enum{
		udTABLEVIEW,
		udTABLEVIEWCELL,		//结点
		udColorLayer,
		udANCOMMON,
		udTEXTBG1,
		udTEXTBG2,
		udTEXTCOUNTTTF1,
		udTEXTCOUNTTTF2,
		udICONMONEY,
		udICONDIAMOND,
		udBLOODSTONE,
		udPRESTIGE,
	};
private:
	enum{
		udBG1,		//背景1
		udARROWNODE,		//箭头节点
		udBUY1,		//购买1
		udBUY2,		//购买2
		udDIAMOND1,		//宝石正价1
		udDIAMOND2,		//宝石正价2
		udDIAMONDDOWN1,		//宝石打折1
		udDIAMONDDOWN2,		//宝石打折2
		udGOLD1,		//黄金正价1
		udGOLD2,		//黄金正价2
		udGOLDDOWN1,		//黄金打折1
		udGOLDDOWN2,		//黄金打折2
		udPRESTIGE1,		//声望正价1
		udPRESTIGE2,		//声望正价2
		udPRESTIGEDOWN1,	//声望打折1
		udPRESTIGEDOWN2,	//声望打折2
		udLONGXUE1,		//龙血正价1
		udLONGXUE2,		//龙血正价2
		udLONGXUEDOWN1,	//龙血打折1
		udLONGXUEDOWN2,	//龙血打折2
		udTEXT1,		//文字框1
		udTEXT2,		//文字框2
		udTEXT3,		//文字框3
		udTEXT4,		//文字框4
		udLine1,		//文字框1
		udLine2,		//文字框2
		udBUYBTN1,		//购买按钮1
		udBUYBTN2,		//购买按钮2
		udBUYBTNGREY1,		//购买按钮灰1
		udBUYBTNGREY2,		//购买按钮灰2
		udLevelDAY1,		//等级限售1
		udLevelDAY2,		//等级限售2
		udDAY1,		//每日限售1
		udDAY2,		//每日限售2
		udLIMIT1,		//限售次数1
		udLIMIT2,		//限售次数2
		udYE1,		//正价1
		udYE2,		//正价2
		udRED1,		//打折1
		udRED2,		//打折2
		udNAME1,		//打折1
		udNAME2,		//打折2
		udVIEWDEBRIS1,		//控件1
		udVIEWDEBRIS2,		//控件2

	}CELL;

	cocos2d::CCSize m_szCell;
	cocos2d::extension::CCTableView* m_pTable;
	unsigned short	 numberOfCells;		//有多少个Cell
	int m_Curblockindex;//点击选中购买的索引	
	int m_CurLongxueBlood;
public:
	SecretView(){
		m_pTable = NULL;
		m_Curblockindex = 0;
		numberOfCells = 0;
		m_CurLongxueBlood = 0;
	};
	virtual ~SecretView(){};
private:
	inline void _initLayout();
	inline void _initData();
	inline void _initCell();
	inline void _setTableView();
	void _setLongXueText();
	void _showMoneyText();

	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	inline void _setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置按钮
	*/
	inline void _mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	/*
		所有货币缩放
	*/
	void _setAllScale(cocos2d::extension::CCTableViewCell * cell,float scale);
	/*
		隐藏所有货币
	*/
	void _setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx);
	/*
		将货币售价显示红色
	*/
	void _setRedText(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置按钮是否禁用
	*/
	void _setShopBuyEnableBtn(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		条件限制
	*/
	void _setrequireInfo(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		每日限售条件
	*/
	void _setdaylimit(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置货币类型显示
	*/
	inline void _setmoneycell(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		tips回调事件
	*/
	virtual void cancelTipsLayer();
	/*
		禁用按钮和按钮文字置灰
	*/
	inline void _enableBtnsCell(bool enabled,CCNode* cell,int blockIdx);
	/*
		按钮禁用
	*/
	inline void _enableBtnCell(int key,bool enabled,cocos2d::CCNode* cell);
	/*
		显示商品tips
	*/
	inline void _showgoodstips(ShopInfoGoodsData *data);
	/*
		来自强化窗口的回调
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	/*
		等待隐藏
	*/
	void  HideWaittingLayer();			
protected:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	virtual bool onUpdata();
	virtual bool onUpdateText();
protected:
	/*
		点击查看商品Tips界面响应
	*/
	void On_Cell_ClickEvent(cocos2d::CCObject* pSender);
	/*
		点击购买按钮
	*/
	void On_Cell_SellEvent(cocos2d::CCObject* pSender);
};

#endif