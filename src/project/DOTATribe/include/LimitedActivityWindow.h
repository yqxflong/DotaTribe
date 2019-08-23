//Name : LimitedActivityWindow
//Function : ��ʱ�
//Author : ��ǿ

#ifndef _DOTATRIBE_LimitedActivityWindow_H_
#define _DOTATRIBE_LimitedActivityWindow_H_


#include "../include/IWindow.h"
#include <cocos-ext.h>
#include "../include/CMenuItemSprite.h"

class ActivityItem;
class LimitedActivityWindow : public IWindow
	,public cocos2d::extension::CCTableViewDataSource, cocos2d::extension::CCEditBoxDelegate
{
private:
	enum{
		kLA_BG,
		kLA_CLOSE,
		kLA_DIAMOND,
		kLA_GOLD,
		kLA_DIAMOND_VALUE,
		kLA_GOLD_VALUE,
		kLA_TAB1,
		kLA_TAB2,
		kLA_TAB3,
		kLA_TAB1_TITLE,
		kLA_TAB2_TITLE,
		kLA_TAB3_TITLE,
	}kRoot;

	enum{
		kLA_DECORATION,
		kLA_TABLE1,
		kLA_TABLE2,
		kLA_CELL_L,

		//�洢�����
		kLA_R_CELL_TITLEBG1,
		kLA_R_CELL_SUBTITLE1,
		kLA_R_CELL_TITLEVALUE1,
		kLA_R_CELL_TITLEBG2,
		kLA_R_CELL_SUBTITLE2,
		kLA_R_CELL_TITLEVALUE2,
		kLA_R_CELL_TITLESPACE,
		//��̬��,�����������bg֮��
		kLA_R_CELL_AWARD_BG,
		kLA_R_CELL_AWARD,	//��Ʒ���
		kLA_R_CELL_AWARD_COUNT,
		kLA_R_CELL_AWARD_PROMPT,
		kLA_R_CELL_AWARD_BTN,
		kLA_R_CELL_AWARD_BG_SPACE,
	}kAcitvity;

	enum{
		kLA_LEFT_CELL_TXT,
		kLA_LEFT_CELL_BTN,
		kLA_LEFT_CELL_HINT,
	}kActivity_leftCell;

	enum{
		kLA_NOTICE_DECORATION,
		kLA_NOTICE_SCROLL,
		kLA_NOTICE_TITLETEXT,
		kLA_NOTICE_CONTENTTEXT,
		kLA_NOTICE_TITLEICON,
		kLA_NOTICE_LINE,
	}kNoticeBox;

	enum{
		KA_EXCHANGE_BG,					//����
		KA_EXCHANGE_BG2,					//����2
		KA_EXCHANGE_EDITBOX,			//�����
		KA_EXCHANGE_CONFIRMBTN,			//ȷ�ϰ�ť
		KA_EXCHANGE_CONFIRMBTNLABEL,	//ȷ���ύ����
	};

	int m_nCurTab;		//��ǰҳǩ��
//==========�ҳ===========
	cocos2d::CCNode* m_pRoot_Activity;
	cocos2d::CCLayer*  m_pRoot_NoticeBox;
	cocos2d::CCNode* m_pRoot_Exchange;
	int m_nCurActivityIndex;	//��ǰ�����
	cocos2d::extension::CCTableView* m_pTable1;
	cocos2d::extension::CCTableView* m_pTable2;
	float m_fContentHeight;	//�ұ߻���ݸ߶�
	cocos2d::CCLabelTTF* m_pATime;	//�ʱ��

	CMenuItemSprite* m_lastSelectTab;//�ϴ�ѡ�а�ť
public:
	LimitedActivityWindow();
	virtual ~LimitedActivityWindow(){};

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

protected:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		��ʾ����¼�����
	*/
	inline void OnShowWindowEventHandler(std::list<std::string>& paramList);

	//��ť�¼�
	void On_Click_Event(cocos2d::CCObject* pSender);

	//���cell��ť�¼�
	void On_Click_Cell_L_Event(cocos2d::CCObject* pSender);
	//�ұ�cell ��ȡ��ť�¼�
	void On_Click_Cell_R_Event(cocos2d::CCObject* pSender);
	//�ұ�cell TIPS��ť
	void On_Click_Cell_Tips_Event(cocos2d::CCObject* pSender);

	//�һ����水ť�¼�
	void On_Exchange_Btn_Click(cocos2d::CCObject * pSender);
	
private:
	void _checkCDKeyIsOpen();		


private:
	//load Subview Root
	inline void _loadActivityRoot();
	inline void _loadLoginNoticeRoot();
	void _loadExchangeRoot();
	//unload SubView Root
	void _unloadActivityRoot();
	void _unloadLoginNoticeRoot();
	void _unloadExchangeRoot();

	//����
	inline void _mapContent();
	//�
	inline void _mapTable();
	inline void _mapBtn();
	//�һ�
	inline void _mapExchange();
	//��
	inline void _mapMoneyAndDiamond();
	inline void _defaultTab();
	//cell
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table);
	inline void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table);
	inline void _setTableCell_ActivityList(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table);
	inline void _setTableCell_ActivityContent(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,cocos2d::extension::CCTableView* table);

	//create content
	inline float _createSub1(cocos2d::CCNode* cell,float posy,const ActivityItem& item);
	inline float _createSub2(cocos2d::CCNode* cell,float posy,const ActivityItem& item);
	inline void _createAwards(cocos2d::CCNode* cell,float posy,const ActivityItem& item);


	//tools func
	inline float _getActivityTimeAndDesctiptionHeight();
	inline float _getOneAwardBarHeight();
public:
	  virtual CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void editBoxReturn(CCEditBox* editBox);
};

#endif