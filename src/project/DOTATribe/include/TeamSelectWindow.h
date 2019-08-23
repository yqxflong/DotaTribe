//Name ; TeamBattleWindow
//Function����Ӹ�������
//Author : fangjun
//Date: 20130918

#ifndef  _DOTATRIBE_TEAMSELECTWINDOW_H_
#define  _DOTATRIBE_TEAMSELECTWINDOW_H_

#include "../include/IWindow.h"
#include "../include/CDragSprite.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
// #include "../include/AnimationEffect.h"
// #include "../include/AnimationFileDataManager.h"

class TeamSelectWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate, CDragSpriteDelegate
{
private:
	enum{
		mBg = 0,
		mQuality,
		mPlayerName,
		mSkinName,
		mLevel,
		mBtlCapa,
		mBtlCapaValue,
		mGoldIcon,
		mPriceValue,
		mHireBtn,
		mHireBtnLabel,
	}MercenaryCell;
	enum{
		sBg = 0,
		sQuality,
		sPlayerName,
		sSkinName,
		sLevel,
		sBtlCapa,
		sBtlCapaValue,
		sLeftTime,
		sLeftTimeValue,
		sCallBtn,
		sCallBtnLabel,
	}SlaveCell;
	enum{
		vBg = 0,
		vTitle,
		vCloseBtn,
		vTabelview,
		vCell,
	}ViewList;
	enum{
		_VIEW_PAGE_SLAVE_ = 0,//ū���б�
		_VIEW_PAGE_MERCENARY_,//Ӷ���б�
	}ViewPageKind;
	enum{
		 udBG = 0,//����
		 udBoardBG,//�װ�
		 udFUBENNAMETTF,	//��������
		 udCLOSEBTN,		//�رհ�ť
		 udBEGINBTN,//��ʼ��ť
		 udBEGINTTF,//��ʼ��ť��
		 udLEAVEBTN,//�뿪��ť
		 udLEAVETTF,//�뿪��ť��
		 udDESTROYTEAMBTN,//��ɢ���鰴ť
		 udDESTROYTEAMTTF,//��ɢ���鰴ť��
		 udBUILDTEAMBTN,//�������鰴ť
		 udBUILDTEAMTTF,//�������鰴ť��
		 udONEMSGBTN,//һ��������ť
		 udONEMSGBG,//һ������������Ҳ���ɰ�ť
		 udONEMSGBTNTTF,	//һ��������ť��
		 udPLAYERBG1,	//��ұ���1
		 udQUALITY1,//����ͷ������ͼ1
		 udSKINNAME1,//��������1
		 udZHANLIVALUE1,//ս��ֵ1
		 udPLAYERNAME1,//��������1
		 udSOCIAL1,//����ϵ1
		 udPLAYERBG2,	//��ұ���2
		 udQUALITY2,//����ͷ������ͼ2
		 udSKINNAME2,//��������2
		 udZHANLIVALUE2,//ս��ֵ2
		 udPLAYERNAME2,//��������2
		 udSOCIAL2,//����ϵ2
		 udPLAYERBG3,	//��ұ���3
		 udQUALITY3,//����ͷ������ͼ3
		 udSKINNAME3,//��������3
		 udZHANLIVALUE3,//ս��ֵ3
		 udPLAYERNAME3,//��������3
		 udSOCIAL3,//����ϵ3
		 udROMOVEBTN1,//�Ƴ���ť1
		 udROMOVETTF1,//�Ƴ���ť��1
		 udCHECKBTN1,//�鿴��ť1
		 udCHECKTTF1,//�鿴��ť��1
		 udROMOVEBTN2,//�Ƴ���ť2
		 udROMOVETTF2,//�Ƴ���ť��2
		 udCHECKBTN2,//�鿴��ť2
		 udCHECKTTF2,//�鿴��ť��2
		 udROMOVEBTN3,//�Ƴ���ť3
		 udROMOVETTF3,//�Ƴ���ť��3
		 udCHECKBTN3,//�鿴��ť3
		 udCHECKTTF3,//�鿴��ť��3
		 ud1DOWNBTN,		//1����
		 ud2UPBTN,			//2����
		 ud2DOWNBTN,		//2����
		 ud3UPBTN,			//3����
		 udTableView,
		 udTableCell,
		 udMaskNode,	//�����Ĺ�Ӷū����Ӷ�����ص�
		}Main;
	enum{
		udCELLBG,//CELL��ͼ
		udTEAMLEADER,//�ӳ�����
		udNUM,
		udMEMBERNUM,//�����������
		udJOINBTN,//���밴ť
		udJOINTTF,//���밴ť��
	}Cell;

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�
	cocos2d::extension::CCTableView* m_pTeamTable;
	cocos2d::extension::CCTableView * m_pSlaveTable;//��������slave
	cocos2d::extension::CCTableView * m_pMercenaryTable;//��������mercenary
	//bool m_bIsNowSlaveTable;//��ǰ��ū���б�

	cocos2d::CCSize m_szTeamCell;
	cocos2d::CCSize m_szSlaveCell;
	cocos2d::CCSize m_szMercenaryCell;

	cocos2d::CCNode * onekey0;//����0
	cocos2d::CCNode * onekey1;//����1
	cocos2d::CCNode * onekey2;//��������


	const int _TAG_CHENG_;//tag�����ֻΪ�������б���

public:
	TeamSelectWindow();
	virtual ~TeamSelectWindow();

private:
	inline void _initLayout();
	
	inline void _initData();

	inline void _setTableView();
	inline void _createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell,int idx);

	void _createGrayLayer();
	void _removeGrayLayer();
	inline void _mapBtn();

public:
	void _removeMember(int idx);//�Ƴ��ŵڼ��Ķ�Ա
	void _checkMemberInfo(int idx);//�鿴�ŵڼ��Ķ�Ա
	void _refreshMyTeamShow();//ˢ�������ڶ�����ʾ
	void _switchTwoMember(int firstIdx, int secondIdx);
	void _refreshBtnFunc();//ˢ�½���ײ���ť״̬

	void _hireSlave();		//��Ӷū��
	void _hireMercenary();	//��ӶӶ��
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

private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		ˢ��
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);

public:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

public:
	/*
		DragSprite����
	*/
	virtual void clickEvent(int idx,int type=0);
	virtual bool containsTheCopy(cocos2d::CCSprite* copy,int type=0);

private:
	/*
		ˢ��tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb)const {
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
public:
	void On_Btn_Click(cocos2d::CCObject* pSender);

	void On_JoinTeam_Click(cocos2d::CCObject* pSender);

	void On_View_Close_Click(cocos2d::CCObject* pSender);

	void On_Slave_Hire_Click(cocos2d::CCObject* pSender);

	void On_Mercenary_Hire_Click(cocos2d::CCObject* pSender);

public:
	/*
		��õ�ǰ�ؿ�����Ϣ
	*/
	void Function_GetNowStageData();

	/*
		��ö����б����ݣ�ˢ�¶����б�
	*/
	void Function_GetTeamListData();

	/*
		����Լ����ڶ�������, ˢ�����ڶ�������
	*/
	void Function_GetMyTeamData();
	
	/*
		������֪ͨ�ұ����ˣ���
	*/
	void Function_BeRemovedFromTeam(int removedType, int isLeader);

	/*
		���ū���б�
	*/
	void Function_GetSlaveList();

	/*
		���Ӷ���б�
	*/
	void Function_GetMercenaryList();
};


#endif
