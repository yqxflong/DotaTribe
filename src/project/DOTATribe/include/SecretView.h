//Name��SecretView
//Function���ر��̵�
//Written By��lvyunlong
//Time��2013-9-11

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
	};
private:
	enum{
		udBG1,		//����1
		udARROWNODE,		//��ͷ�ڵ�
		udBUY1,		//����1
		udBUY2,		//����2
		udDIAMOND1,		//��ʯ����1
		udDIAMOND2,		//��ʯ����2
		udDIAMONDDOWN1,		//��ʯ����1
		udDIAMONDDOWN2,		//��ʯ����2
		udGOLD1,		//�ƽ�����1
		udGOLD2,		//�ƽ�����2
		udGOLDDOWN1,		//�ƽ����1
		udGOLDDOWN2,		//�ƽ����2
		udPRESTIGE1,		//��������1
		udPRESTIGE2,		//��������2
		udPRESTIGEDOWN1,	//��������1
		udPRESTIGEDOWN2,	//��������2
		udLONGXUE1,		//��Ѫ����1
		udLONGXUE2,		//��Ѫ����2
		udLONGXUEDOWN1,	//��Ѫ����1
		udLONGXUEDOWN2,	//��Ѫ����2
		udTEXT1,		//���ֿ�1
		udTEXT2,		//���ֿ�2
		udTEXT3,		//���ֿ�3
		udTEXT4,		//���ֿ�4
		udLine1,		//���ֿ�1
		udLine2,		//���ֿ�2
		udBUYBTN1,		//����ť1
		udBUYBTN2,		//����ť2
		udBUYBTNGREY1,		//����ť��1
		udBUYBTNGREY2,		//����ť��2
		udLevelDAY1,		//�ȼ�����1
		udLevelDAY2,		//�ȼ�����2
		udDAY1,		//ÿ������1
		udDAY2,		//ÿ������2
		udLIMIT1,		//���۴���1
		udLIMIT2,		//���۴���2
		udYE1,		//����1
		udYE2,		//����2
		udRED1,		//����1
		udRED2,		//����2
		udNAME1,		//����1
		udNAME2,		//����2
		udVIEWDEBRIS1,		//�ؼ�1
		udVIEWDEBRIS2,		//�ؼ�2

	}CELL;

	cocos2d::CCSize m_szCell;
	cocos2d::extension::CCTableView* m_pTable;
	unsigned short	 numberOfCells;		//�ж��ٸ�Cell
	int m_Curblockindex;//���ѡ�й��������	
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
		���ð�ť
	*/
	inline void _mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	/*
		���л�������
	*/
	void _setAllScale(cocos2d::extension::CCTableViewCell * cell,float scale);
	/*
		�������л���
	*/
	void _setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx);
	/*
		�������ۼ���ʾ��ɫ
	*/
	void _setRedText(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		���ð�ť�Ƿ����
	*/
	void _setShopBuyEnableBtn(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		��������
	*/
	void _setrequireInfo(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		ÿ����������
	*/
	void _setdaylimit(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	/*
		���û���������ʾ
	*/
	inline void _setmoneycell(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx);
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
		��ʾ��Ʒtips
	*/
	inline void _showgoodstips(ShopInfoGoodsData *data);
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
};

#endif