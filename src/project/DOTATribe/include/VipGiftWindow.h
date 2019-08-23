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
	cocos2d::extension::CCTableView* m_pTable;    //CCTableView�ؼ�
	cocos2d::CCSize m_szCellGift;	//������С
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _initCell();
	inline void _mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setTableView(); //����TableView
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	void _setVipBox(VipGiftItem *data,cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	
public:
	/*
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		��ʾVIP����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		����VIP����¼�����
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		����VIP����¼�����
	*/
	inline void  OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		����VIP����¼�����
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
		�鿴������ť�ص�
	*/
	void On_CheckItem_Click(cocos2d::CCObject* pSender);
};


#endif