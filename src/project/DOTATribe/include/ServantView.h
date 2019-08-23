// Name ; ServantView.h
// Function���ʹ�ϵͳ
// Author : fangjun
// Date: 20131029

#ifndef _DOTATRIBE_SERVANTVIEW_H_
#define _DOTATRIBE_SERVANTVIEW_H_

#include "../include/SubView.h"

class ServantView : public SubView, cocos2d::extension::CCTableViewDataSource, cocos2d::extension::CCTableViewDelegate
{
	public:
	enum{
		_PAGE_TYPE_MASTER_0_ = 0,			//��ҳ0
		_PAGE_TYPE_MASTER_1_,				//��ҳ1
		_PAGE_TYPE_MASTER_2_,				//��ҳ2
		_PAGE_TYPE_SLAVE_0_,				//��ҳ3
		_PAGE_TYPE_SLAVE_1_,				//��ҳ4
		_PAGE_TYPE_SLAVE_2_,				//��ҳ5
	}PAGE;

private:
	enum{
		_TABLE_TYPE_ONE_ = 0,		//��һ�б�
		_TABLE_TYPE_LEFT_,			//����б�
		_TABLE_TYPE_RIGHT_,			//�Ҳ��б�
	}TABLE;

	enum{
		_MESSAGE_CATCH_FUNCTION_DOWN_ = 635,
		_MESSAGE_PLAY_FUNCTION_DOWN_ = 636,
		_MESSAGE_RESCUE_FUNCTION_DOWN_ = 637,
		_MESSAGE_REVOLT_FUNCTION_DOWN_ = 638,
		_MESSAGE_SOS_FUNCTION_DOWN_ = 639,
		_MESSAGE_IDENTITY_CHANGED_TO_SLAVE_ = 640,		//���ū����ʾ
		_MESSAGE_IDENTITI_CHANGED_TO_FREE_ = 655,		//���������
	}MESSAGE_NOTIFY;

	//����Ϊ���涨�壬begin

	enum{
		newsTTF,
		newsLine,
	}NewsCell;

	enum{
		s2Cell0Bg = 0,
		s2Cell0Icon,
		s2Cell0Name,
		s2Cell0Level,
		s2Cell0Btl,
		s2Cell0BtlValue,
		s2Cell0HelpBtn,
		s2Cell0HelpLabel,
		s2Cell1Bg,
		s2Cell1Icon,
		s2Cell1Name,
		s2Cell1Level,
		s2Cell1Btl,
		s2Cell1BtlValue,
		s2Cell1HelpBtn,
		s2Cell1HelpLabel,
	}SlavePageSOSCell;

	enum{
		s2vline = 0,
		s2Table,
		s2Cell,
		s2NoTips,
	}SlavePageSOS;

	enum{
		s1MyOwnerTitleBg = 0,
		s1MyOwnerTitle,
		s1OwnerBg,
		s1OwnerIcon,
		s1OwnerName,
		s1OwnerLevel,
		s1PlayBtn,
		s1PlayLabel,
		s1vline,
		s1Table,
		s1Cell,
	}SlavePagePlay;

	enum{
		s0RevoltTitleBg = 0,
		s0RevoltTitle,
		s0OwnerBg,
		s0OwnerIcon,
		s0OwnerName,
		s0OwnerLevel,
		s0OwnerBtl,
		s0OwnerBtlValue,
		s0RevoltBtn,
		s0RevoltLabel,
		s0BegHelp,
		s0vLine,
		s0BribeTitleBg,
		s0BribeTitle,
		s0NpcBg,
		s0NpcIcon,
		s0NpcName,
		s0NpcPrice,
		s0NpcPriceValue,
		s0NpcPriceGold,
		s0BribeBtn,
		s0BribeLabel,
	}SlavePageRevolt;

	enum{
		m2Cell0Bg = 0,
		m2Cell0Icon,
		m2Cell0Name,
		m2Cell0MasterNameLabel,
		m2Cell0MasterName,
		m2Cell0MasterBtl,
		m2Cell0MasterBtlValue,
		m2Cell0RescueBtn,
		m2Cell0RescueLabel,
		m2Cell1Bg,
		m2Cell1Icon,
		m2Cell1Name,
		m2Cell1MasterNameLabel,
		m2Cell1MasterName,
		m2Cell1MasterBtl,
		m2Cell1MasterBtlValue,
		m2Cell1RescueBtn,
		m2Cell1RescueLabel,
	}MasterPageRescueCell;

	enum{
		m2TipLabel = 0,
		m2VLine,
		m2Table,
		m2Cell,
		m2NoTips,
	}MasterPageResuce;

	enum{
		m1Slave0Bg = 0,
		m1Slave0Icon,
		m1Slave0Name,
		m1Slave0Level,
		m1Slave0WorkTime,
		m1Slave0WorkTimesValue,
		m1Slave0Exp,
		m1Slave0ExpValue,
		m1Slave0ChainBtn,
		m1Slave0ChainLabel,
		m1Slave0PressBtn,
		m1Slave0PressLabel,
		m1Slave0ReleaseBtn,
		m1Slave0ReleaseLabel,
		m1Slave0CatchBtn,
		m1Slave1Bg,
		m1Slave1Icon,
		m1Slave1Name,
		m1Slave1Level,
		m1Slave1WorkTime,
		m1Slave1WorkTimesValue,
		m1Slave1Exp,
		m1Slave1ExpValue,
		m1Slave1ChainBtn,
		m1Slave1ChainLabel,
		m1Slave1PressBtn,
		m1Slave1PressLabel,
		m1Slave1ReleaseBtn,
		m1Slave1ReleaseLabel,
		m1Slave1CatchBtn,
		m1Slave2Bg,
		m1Slave2Icon,
		m1Slave2Name,
		m1Slave2Level,
		m1Slave2WorkTime,
		m1Slave2WorkTimesValue,
		m1Slave2Exp,
		m1Slave2ExpValue,
		m1Slave2ChainBtn,
		m1Slave2ChainLabel,
		m1Slave2PressBtn,
		m1Slave2PressLabel,
		m1Slave2ReleaseBtn,
		m1Slave2ReleaseLabel,
		m1Slave2CatchBtn,
		m1VLine,
		m1Table,
		m1Cell,

	}MasterPagePlay;

	enum{
		mc0Bg = 0,
		mc0Icon,
		mc0Name,
		mc0Level,
		mc0Idt,
		mc0IdtValue,
		mc0CatchBtn,
		mc0CatchBtnLabel,
	}MasterPageCatchCell;
	enum{
		m0WinBg = 0,
		m0LossBg,
		m0WinLabel,
		m0LossLabel,
		m0VLine,
		m0TableView0,//���tabelview
		m0Cell0,
		m0TableView1,//�Ҳ�tabelview
		m0Cell1,
		m0LeftNoTips,
		m0RightNoTips,
	}MasterPageCatch;

	enum{
		mBg = 0,
		mPage0Label,
		mPage0Btn,
		mPage1Label,
		mPage1Btn,
		mPage2Label,
		mPage2Btn,
		mLeftTimesTTF,
		mLeftTimesValue,
		mLeftTimesBg,
		mViewNode,
	}MainPage;
	//end	

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�
	cocos2d::CCNode * m_pViewRoot;//������ҳ��Ľڵ�

	cocos2d::extension::CCTableView * m_pTable;			//���б�ʱʹ��
	cocos2d::extension::CCTableView * m_pLeftTable;		//˫�б�ʱ������б�
	cocos2d::extension::CCTableView * m_pRightTable;	//˫�б�ʱ���Ҳ��б�

	cocos2d::CCSize m_szCELL;			//���б�ʱ��cell�ߴ�
	cocos2d::CCSize m_szCELLLeft;		//˫�б�ʱ�����cell�ߴ�
	cocos2d::CCSize m_szCELLRight;		//˫�б�ʱ���Ҳ�cell�ߴ�

	cocos2d::CCMenuItemSprite * m_pSelectSubPage;//ѡ��ķ��水ť������ȡ���ϴ�ѡ��
	int m_iPageType;		//ҳ����������//��PAGEö����

public:
	ServantView();
	virtual ~ServantView();

private:
	inline void _initLayout();
	inline void _mapMainPage();
	inline void _initDefaultPage();
	inline void _setSelectPageTab();//��ʾѡ���ҳ��ǩ
	inline void _showViewPage();//��ʾ�·�ҳ�棬ÿ���л����Ӵ˷����л��ײ�ҳ��
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell, int tableType);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx, int tableType);

	//��ʾ�ͱ궨��ť
	inline void _showMasterCatchPage(cocos2d::CCNode * parent);
	inline void _showMasterPlayPage(cocos2d::CCNode * parent);
	inline void _showMasterRescuePage(cocos2d::CCNode * parent);
	inline void _showSlaveRevoltPage(cocos2d::CCNode * parent);
	inline void _showSlavePlayPage(cocos2d::CCNode * parent);
	inline void _showSlaveSOSPage(cocos2d::CCNode * parent);
	//��������
	inline void _setMasterCatchPage();
	inline void _setMasterPlayPage();
	inline void _setMasterRescuePage();
	inline void _setSlaveRevoltPage();
	inline void _setSlavePlayPage();
	inline void _setSlaveSOSPage();

	//�����Ӧ������Ҫ������
	inline void _requestShowPageData();

public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();

private:
	/*
		ū������
	*/
	void SlaveWorkTick();

	/*
		��Ϸ��ȴ
	*/
	void CatchCdTick();
public:
	/*
	��Ϣ�¼���Ӧ����
	*/

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private:
	/*
	show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	//ս������ʱ��ʾ��Ӧ�Ľ���
	void AthleticBackShow();

public:
	//�����水ť����
	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	//ū����ץ������
	void On_MasterCatchPage_Btn_Click(cocos2d::CCObject * pSender);

	//ū���������������
	void On_MasterPlayPage_Btn_Click(cocos2d::CCObject * pSender);

	//ū������Ƚ������
	void On_MasterRescuePage_Btn_Click(cocos2d::CCObject * pSender);

	//ū�������������
	void On_SlaveRevoltPage_Btn_Click(cocos2d::CCObject * pSender);

	//ū�������������
	void On_SlavePlayPage_Btn_Click(cocos2d::CCObject * pSender);

	//ū����Ƚ������
	void On_SlaveSOSPage_Btn_Click(cocos2d::CCObject * pSender);

public:
	//��ý���ץ��ū������
	void Function_GetMasterEnterCatchData();

	//��ý����ū������ҳ������
	void Function_GetMasterEnterPlayData();
	void Function_GetMasterPlaySuccess();

	//���ū������������
	void Function_GetMasterNews();

	//��ý�����ҳ������
	void Function_GetMasterEnterResceuData();

	//��ý��뷴��ҳ������
	void Function_GetSlaveEnterRevoltData();
	
	//���ū����¸�ɹ���Ϣ
	void Function_GetSlaveBribeSuccess();

	//��ý����ū��������ҳ������
	void Function_GetSlaveEnterPlayData();
	void Function_GetSlavePlaySuccess();

	//���ū����������
	void Function_GetSlaveNews();

	//��ý������ҳ������
	void Function_GetSlaveEnterSOSData();

	//����л���������Ӧ���ݲ��л�����
	void Function_ConfirmIdentityChanged();

	//�������л�
	void Function_IdentityChanged(std::list<std::string> & paramList);

	//�󴰿ڵĹرջص�
	void Function_OnClose();



};


#endif