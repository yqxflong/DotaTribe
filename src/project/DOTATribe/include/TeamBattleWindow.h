//Name ; TeamBattleWindow
//Function����Ӹ�������
//Author : fangjun
//Date: 20130918

#ifndef  _DOTATRIBE_TEAMBATTLEWINDOW_H_
#define  _DOTATRIBE_TEAMBATTLEWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include <string>
#include "../include/MaskNode.h"

class TeamBattleWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
		tBg = 0,
		tBoardBg,
		tCloseBtn,
		tHelpBtn,
		tTodayTimes,
		tShopBtn,
		tShopBtnLabel,
		tLeftArrow,
		tRightArrow,
		tLeftMOVEArrow,
		tRightMOVEArrow,
		tClearTips,
		tReward1,
		tReward2,
		tReward3,
		tReward4,
		tStartBtn,//��ʼ���߼�����ť
		tStartBtnLabel,
		tStartArrow,
		tResetBtn,
		tResetBtnLabel,
		tCostTips,
		tGateTableView,
		tGateTableCell,
		tGateRewardNode,//ͨ�ؽ������ص�
		tGateSelectFile,//����ѡ������
	}Gate;

	enum{
		cBg,
		cGatePic,
		cGatePicGrey,
		cNameBg,
		cName,
		cPeople,
		cProgress,
		cNeedLevel,
		cPREPASSBG,
		cPREPASSTTF,
	}Cell;

	enum{
		rGreyColor,		//�Ҳ�
		rBg,			//����
		rDescription,	//˵��
		rTimeCount,		//����ʱʱ��
		rTongTTFBg,		//ͭ�����ֱ���
		rTongTTF,		//ͭ������
		rTongPic,		//ͭ����ͼ
		rTongSelectPic,	//ѡ�п�
		rTongPrice,		//ͭ����۸�
		rYingTTFBg,		//�������ֱ���
		rYingTTF,		//��������
		rYingPic,		//������ͼ
		rYingSelectPic,	//ѡ�п�
		rYingPrice,		//���ʱ��仨����ʯ��
		rYingJewelPic,	//��ʯͼ
		rJinTTFBg,		//�����ֱ���
		rJinTTF,		//������
		rJinPic,		//����ͼ
		rJinSelectPic,	//ѡ�п�
		rNeedVipBG,		//��Ҫvip
		rNeedVip,		//��Ҫvipֵ
		rJinPrice,		//���ʱ��仨����ʯ��
		rJinJewelPic,	//��ʯͼ
	}GateReward;

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�
	cocos2d::extension::CCTableView* m_pTable;
	cocos2d::CCSize m_szCELL;

	bool bGateRewardTick;	//�ؿ�������tick
	int iGateRewardTimeCount;//���ڹؿ�ͨ�ؽ���

	int iselectgateidx;//��ǰҳ��ѡ�еģ��������洢

	std::string gate_normal_board;
	std::string gate_select_board;

	char m_iSelectTongGuanJiangLiType;//ѡ���ͨ�ؽ�������

	MaskNode * m_gateRewardNode;
public:
	TeamBattleWindow();
	virtual ~TeamBattleWindow();

private:
	inline void _checkNewFunc();
	inline void _initLayout();
	inline void _mapLayout();
	inline void _setTableView();
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);

	inline void _refreshRight(int gateIdx);
	inline void _setTTFText(int key, const char * text);
	inline void _setTTFText(int key, int text);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char *  picpath);

	inline void _showGateRewardPage();
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

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

	//ͨ�ؽ������浯�����Զ�����ͷ�
	void TickGateReward();

private:
	/*
	show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
// 
// 	/*
// 	������Data�¼�����
// 	*/
// 	void OnTeamBattleEventHandler(std::list<std::string>& paramList);

	/*
	Refresh��Ǯ�ȴ���
	*/
	//void OnRefreshWindowEventHandler(std::list<std::string>& paramList);

	void On_Btn_Click(cocos2d::CCObject * pSender);

	void On_Btn_CellClick(cocos2d::CCObject * pSender);

	void On_Btn_RewardClick(cocos2d::CCObject * pSender);//ĳ������ͨ�ؽ�����ʾ�������¼�

	void On_Gate_RewardTipsClick(cocos2d::CCObject * pSender);//�ؿ�չʾ������ʾ����tips
private:
	/*
	ˢ��tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb)const {
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}

public:
	void Function_SetTeamBattleDate();
	void Function_TeamBattleReset();

	void Function_GetTongGuanJiangLiResult();
};


#endif
