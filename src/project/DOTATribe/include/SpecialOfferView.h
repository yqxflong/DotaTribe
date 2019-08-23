//Name：SpecialOfferView
//Function：随机商店
//Written By:lvyunlong
//Time：2013-9-11

#ifndef  _DOTATRIBE_SPECIALOFFERVIEW_H_
#define  _DOTATRIBE_SPECIALOFFERVIEW_H_

#include "../include/SHSubView.h"
#include <string>
#include "../include/ShopInfoDataHandler.h"
#include "../include/MaskNode.h"

class SpecialOfferView :public SHSubView
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
		udMASKNODE,
	};
private:
	enum{
		udBG1,		//背景1
		udBUY1,		//购买1
		udBUY2,		//购买2
		udDIAMOND1,		//宝石正价1
		udDIAMOND2,		//宝石正价2
		udGOLD1,		//黄金正价1
		udGOLD2,		//黄金正价2
		udPRESTIGE1,		//声望正价1
		udPRESTIGE2,		//声望正价2
		udLONGXUE1,		//龙血正价1
		udLONGXUE2,		//龙血正价2
		udTEXT1,		//正价框1
		udTEXT2,		//正价框2
		udBUYBTN1,		//购买按钮1
		udBUYBTN2,		//购买按钮2
		udBUYBTNGREY1,		//购买按钮灰1
		udBUYBTNGREY2,		//购买按钮灰2
		udLIMIT1,		//剩余次数文字1
		udLIMIT2,		//剩余次数文字2
		udYE1,		//正价1
		udYE2,		//正价2
		udNAME1,		//名字1
		udNAME2,		//名字2
		udVIEWDEBRIS1,		//控件1
		udVIEWDEBRIS2,		//控件2

	}CELL;

	enum
	{
		udDESCRIBE,	//描述
		udADBOARD,	//神秘商店广告
		udNEXTGOODSTIMETEXT,	//时间文字描述
		udNEXTGOODSTIMEBG,		//时间文字描述底框
		udNEXTGOODSTIMENUM,		//剩余时间
		udNEXTGOODSTIMENUMBG,	//剩余时间底框
		udINFOTEXT,				//刷新信息
		udREFRESHMENU,			//刷新按钮
	}RANDOMNODE;
	cocos2d::CCSize m_szCell;
	cocos2d::extension::CCTableView* m_pTable;
	unsigned short	 numberOfCells;		//有多少个Cell
	MaskNode* m_RandomInfonode;
	int m_Curblockindex;//点击选中购买的索引	
	long long m_Pretime;
public:
	SpecialOfferView(){
		m_pTable = NULL;
		m_Curblockindex = 0;
		numberOfCells = 0;
		m_RandomInfonode = NULL;
		m_Pretime = 0;
	};
	virtual ~SpecialOfferView(){};
private:
	inline void _initLayout();
	inline void _initData();
	inline void _initCell();
	inline void _setTableView();
	/*
		设置声望个数
	*/
	void _setMoneyText();
	void _showMoneyText();
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	inline void _setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置按钮
	*/
	inline void _mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置刷新按钮
	*/
	void _mapRefBtn();
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	/*
		隐藏所有货币
	*/
	void _setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx);
	/*
		将货币售价显示红色
	*/
	void _setRedText(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置cell是否显示
	*/
	void _setNodeVisible(cocos2d::CCNode* cell,int key,bool isShow);
	/*
		设置按钮是否禁用
	*/
	void _setShopBuyEnableBtn(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		条件限制
	*/
	void _setrequireInfo(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		设置货币类型显示
	*/
	inline void _setmoneycell(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
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
		按钮文字置灰
	*/
	inline void _enableBtnTitleCell(int key,bool enabled,cocos2d::CCNode* cell);
	/*
		显示商品tips
	*/
	inline void _showgoodstips(RandomGoodsData *data);
	/*
		剩余时间更新显示
	*/
	inline void LeftTimeUpdate(int lefttimes);
	/*
		剩余刷新球显示
	*/
	inline void ShowRefreshBall(int num);
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
	/*
		刷新按钮
	*/
	void On_Refresh_Event(cocos2d::CCObject* pSender);
};

#endif