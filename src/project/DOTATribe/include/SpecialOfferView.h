//Name��SpecialOfferView
//Function������̵�
//Written By:lvyunlong
//Time��2013-9-11

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
		udTABLEVIEWCELL,		//���
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
		udBG1,		//����1
		udBUY1,		//����1
		udBUY2,		//����2
		udDIAMOND1,		//��ʯ����1
		udDIAMOND2,		//��ʯ����2
		udGOLD1,		//�ƽ�����1
		udGOLD2,		//�ƽ�����2
		udPRESTIGE1,		//��������1
		udPRESTIGE2,		//��������2
		udLONGXUE1,		//��Ѫ����1
		udLONGXUE2,		//��Ѫ����2
		udTEXT1,		//���ۿ�1
		udTEXT2,		//���ۿ�2
		udBUYBTN1,		//����ť1
		udBUYBTN2,		//����ť2
		udBUYBTNGREY1,		//����ť��1
		udBUYBTNGREY2,		//����ť��2
		udLIMIT1,		//ʣ���������1
		udLIMIT2,		//ʣ���������2
		udYE1,		//����1
		udYE2,		//����2
		udNAME1,		//����1
		udNAME2,		//����2
		udVIEWDEBRIS1,		//�ؼ�1
		udVIEWDEBRIS2,		//�ؼ�2

	}CELL;

	enum
	{
		udDESCRIBE,	//����
		udADBOARD,	//�����̵���
		udNEXTGOODSTIMETEXT,	//ʱ����������
		udNEXTGOODSTIMEBG,		//ʱ�����������׿�
		udNEXTGOODSTIMENUM,		//ʣ��ʱ��
		udNEXTGOODSTIMENUMBG,	//ʣ��ʱ��׿�
		udINFOTEXT,				//ˢ����Ϣ
		udREFRESHMENU,			//ˢ�°�ť
	}RANDOMNODE;
	cocos2d::CCSize m_szCell;
	cocos2d::extension::CCTableView* m_pTable;
	unsigned short	 numberOfCells;		//�ж��ٸ�Cell
	MaskNode* m_RandomInfonode;
	int m_Curblockindex;//���ѡ�й��������	
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
		������������
	*/
	void _setMoneyText();
	void _showMoneyText();
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	inline void _setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		���ð�ť
	*/
	inline void _mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		����ˢ�°�ť
	*/
	void _mapRefBtn();
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	/*
		�������л���
	*/
	void _setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx);
	/*
		�������ۼ���ʾ��ɫ
	*/
	void _setRedText(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		����cell�Ƿ���ʾ
	*/
	void _setNodeVisible(cocos2d::CCNode* cell,int key,bool isShow);
	/*
		���ð�ť�Ƿ����
	*/
	void _setShopBuyEnableBtn(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		��������
	*/
	void _setrequireInfo(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		���û���������ʾ
	*/
	inline void _setmoneycell(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		tips�ص��¼�
	*/
	virtual void cancelTipsLayer();
	/*
		���ð�ť�Ͱ�ť�����û�
	*/
	inline void _enableBtnsCell(bool enabled,CCNode* cell,int blockIdx);
	/*
		��ť����
	*/
	inline void _enableBtnCell(int key,bool enabled,cocos2d::CCNode* cell);
	/*
		��ť�����û�
	*/
	inline void _enableBtnTitleCell(int key,bool enabled,cocos2d::CCNode* cell);
	/*
		��ʾ��Ʒtips
	*/
	inline void _showgoodstips(RandomGoodsData *data);
	/*
		ʣ��ʱ�������ʾ
	*/
	inline void LeftTimeUpdate(int lefttimes);
	/*
		ʣ��ˢ������ʾ
	*/
	inline void ShowRefreshBall(int num);
	/*
		����ǿ�����ڵĻص�
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
		�ȴ�����
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
		����鿴��ƷTips������Ӧ
	*/
	void On_Cell_ClickEvent(cocos2d::CCObject* pSender);
	/*
		�������ť
	*/
	void On_Cell_SellEvent(cocos2d::CCObject* pSender);
	/*
		ˢ�°�ť
	*/
	void On_Refresh_Event(cocos2d::CCObject* pSender);
};

#endif