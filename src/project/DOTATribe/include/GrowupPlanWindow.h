//Name: GrowupPlanWindow
//Author: lvyunlong
//Func: Activity of growup plan window
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_GROWUPPLANWINDOW_H_
#define  _DOTATRIBE_GROWUPPLANWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ActivityDataHandler.h"

class GrowupPlanWindow : public IWindow 	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
			udBG = 0,
			udBG1,
			udTABLE,
			udTABLECELL,
			udRECHGEBTN,
			udRECHGETTF,
			udBUYBTN,
			udBUYTTF,
		};

	enum{
		_PLAN_CELLBG,
		_PLAN_LEVELGROWTTF,
		_PLAN_REACHLEVELTTF,
		_PLAN_GETMONEYTTF,
		_PLAN_DTREWARD,
		_PLAN_GETBTN,
		_PLAN_GETTFF,
		_PLAN_EFFECTBTN,
		}CELL;
private:
	int m_CurWindowActiviId;
public:
	GrowupPlanWindow();
	virtual ~GrowupPlanWindow();
public:
	cocos2d::extension::CCTableView* m_pTableAttachment;    //CCTableView�ؼ�
	cocos2d::CCSize m_szCellGift;	//������С
	std::string strGrowlevel;
	std::string strReachlevel;
	std::string strMoneynum;

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _initCell();
	inline void _mapBtn();
	void _initStr();
	inline void _mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setTableView(); //����TableView
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
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
		��ʾ�ɳ��ƻ��¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		���سɳ��ƻ��¼�����
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		���³ɳ��ƻ��¼�����
	*/
	inline void  OnUpdateWindowEventHandler(std::list<std::string>& paramList);
	/*
		���³ɳ��ƻ���ť�¼�����
	*/
	inline void  OnUpdateBtnWindowEventHandler(std::list<std::string>& paramList);
private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	void On_Click_RechgeBtn_Event(cocos2d::CCObject* pSender);
	void On_Click_BuyPlan_Event(cocos2d::CCObject* pSender);
	void On_Click_GetReward_Event(cocos2d::CCObject* pSender);
	//��ƷTIPS
	void On_Click_Reward_Tips_Event(cocos2d::CCObject* pSender);
};


#endif