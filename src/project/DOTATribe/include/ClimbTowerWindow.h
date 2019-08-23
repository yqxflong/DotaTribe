//Name ; ClimbTowerWindow
//Function : ����
//Author : fangjun
//Date: 20130827

#ifndef  _DOTATRIBE_CLIMBTOWERWINDOW_H_
#define  _DOTATRIBE_CLIMBTOWERWINDOW_H_


#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"

class ClimbTowerWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate
{
private:
	enum
	{
		right_Begin,//�Ҳ���ʾ��ʼ
		right_End,//�Ҳ���ʾ����
		right_FightResult,	//ս������
	};

	enum
	{
		rcBg = 0,
		rcReward,
		rcNameNum,
		rcFloor,
		rcLingQuBtn,
		rcLingQuLabel,
	}RewardCell;

	enum
	{
		rGreyLayer = 0,
		rBg,
		rFloorRewardLabel,//������������
		rBestFloor,//��óɼ�
		rBestFloorValue,	//��óɼ�ֵ
		rRank,//�ҵ�����
		rRankValue,//�ҵ�����ֵ
		rNextRewardLabel,//��һ�׶ν���
		rReward,
		rName,
		rLingQuBtn,
		rLingQuLabel,
		rLingQuNeed,
		rTabelView,
		rTabelCell,
		rCloseBtn,
		rBgTitle,
		rLine,
		rDownArrow,
		rDownArrowMove,
	}Reward;

	enum
	{
		fcResult = 0,
		fcFloor,//����
		fcExpGet,
		fcChaKan,
		fcChaKanLabel,
	}FightResultCell;

	enum{
		fBg = 0,
		fTableView,
		fTableCell,
		fConfirmBtn,
		fConfirmLabel,
	}FightResult;

	enum{
		bBg = 0,
		bRankListNum,
		bRankListNumValue,
		bListBtn,
		bListBtnLabel,
		bBaoXiangBtn,
		bBaoXiangEffect,
		bLine1,
		bTips,
		bLine2,
		bTimes,
		bTimesValue,
		bBuyBtn,
		bStartBtn,
		bStartLabel,
		bStartArrow,

	}Begin;

	enum{
		eBg = 0,
		eRankListNum,
		eRankListNumValue,
		eListBtn,
		eListBtnLabel,
		eBaoXiangBtn,
		eBaoXiangEffect,
		eLine1,
		eNextExp,	//��һ���þ���
		eNextExpValue,	//��һ���þ���ֵ
		eGotExp, //�ۼƻ�þ���
		eGotExpValue,//�ۼƻ�þ���ֵ
		eDesc,//˵��
		eLine2,
		eTuiJianJiNeng,
		eBlock1,
		eBlock2,
		eBlock3,
		eBox1,
		eBox2,
		eBox3,
		eResetBtnLabel,
		eResetBtn,			//���ð�ť
		eFastFightBtnLabel,
		eFastFightBtn,			//����ս����ť
		eJewelResetBtnLabel,
		eJewelResetBtn,			//��ʯ���ð�ť
		eContinueBtnLabel,
		eContinueBtn,		//������ť

		eLeftTimesBg,		//ʣ����ս�����װ�
		eLeftTimesValue,	//ʣ����ս����ֵ
	}End;

	enum{
		ctTowerBg1 = 0,
		ctTowerBg2,
		ctCloseBtn,
		ctHero,			//�ƶ��Ĺ���,masknode
		ctRightPanel,		//�Ҳ����Ĺ��ص㣬CCNode
		ctFloorNum1,	//��������1
		ctFloorNum2,	//��������2
		ctFloorNum3,	//��������3
		ctFloorNum4,	//��������3
		ctAnimationNode,	//�������ؼ�����ڵ�
		ctRewardPanel,		//����ҳ����ص�
	}Main;

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�

	cocos2d::CCNode * m_pRNode;	//�ұߵĸ��ڵ�
	cocos2d::CCNode * m_pRewardNode;	//�����ڵ�

	cocos2d::CCNode * m_pMap1;//��ͼ1
	cocos2d::CCNode * m_pMap2;//��ͼ2

	cocos2d::CCNode * m_pHero;//�ƶ���Ӣ��

	int m_iRunTickCount;	//Ӣ�ۺ͵�ͼ�ƶ�tick����
	bool m_bStartRun;		//�ƶ���־
	int m_iRunTickTime;		//Ĭ��2��,,2*FPS
	float m_fHLength;		//�ƶ����򳤶�
	float m_fVLength;		//�ƶ����򳤶�

	float m_fHeroDefaultPosx;
	float m_fHeroDefaultPosy;

	int m_iRightShowNode;//�Ҳ���ʾ����

	int m_iJumpTickCount;		//���tick����
	bool m_bStartJump;			//��̱�־
	int m_iJumpTickTime;			//���ʱ�䣬Ĭ��2�� * FPS
	float m_fJumpMapSpeed;		//��ͼ�½��ٶȣ�����/֡

	//
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//Ӣ�۽�ɫ,��������
	cocos2d::CCSprite * m_pAnimationPlayNode;//���Ŷ����ڵ�
	AnimationFileData * m_pAnimationFileData;//��Ч�ļ�
	//PAnimation_Call_Node m_pAnimationCallBack;//�ص�����
	cocos2d::CCAnimation * m_pAnimation;//����
	cocos2d::CCRepeatForever * pAnimationAction;//�ظ����Ŷ���
	CPriorityLayerColor * m_pAnimationGrayLayer;

	int _jumptickfloor;//��Ծʱ�Ĳ���

	cocos2d::CCSize m_szCELLFightResult;	//����ս��
	cocos2d::CCSize m_szCellReward;			//����

	cocos2d::extension::CCTableView * m_pTableFightResult;
	cocos2d::extension::CCTableView * m_pTableReward;

	int m_iFastFightRound;		//����ս���غϼ���
	bool m_bInFashFightMode;	//�ڿ���ս��ģʽ
public:
	ClimbTowerWindow();
	virtual ~ClimbTowerWindow();
private:
	inline void _checkNewFunc();
	inline void _initLayout();
	inline void _mapMainPageBtn();

	inline void _tickRun();
	inline void _tickJump();
	inline void _setHeroPosition(float posx);
	inline void _setMapPosition(cocos2d::CCNode * map, float posy, cocos2d::CCNode * anotherMap);
	inline void _setJumpMapPosition(cocos2d::CCNode * map, float posy, int floor);

	inline void _initMapHero();
	inline void _refreshMapHero();//����ÿ�ν�����ҳ�����Ӣ�ۺ͵�ͼλ�ü���ͼ����
	inline void _createMapFloorNum(cocos2d::CCNode * hangParent, int maskNodeTag, cocos2d::CCNode * maskParent);
	inline void _setMapNum(cocos2d::CCNode * map, int floor1, int floor2, int floor3, int floor4);
	
	inline void _setText(int tag, cocos2d::CCNode * parent, const char * text);
	inline void _setText(int tag, cocos2d::CCNode * parent, int num);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath);
	inline void _enableBtn(int tag, cocos2d::CCNode * parent, bool enable);
	inline void _setVisible(int tag, cocos2d::CCNode * parent, bool visible);

	inline void _setMainPageInfo();
	
	void ShowBeginPage();
	inline void _mapBeginPageBtn();
	inline void	_setBeginPageInfo();

	void ShowEndPage();
	inline void _mapEndPageBtn();
	inline void	_setEndPageInfo();

	void ShowFightResultPage();
	inline void _mapFightResultPageBtn();
	inline void _setFightResultPageInfo();

	void ShowRewardPage();
	void _mapRewardPageBtn();
	void _setRewardPageInfo();
	void _setRewardPageNext();//���õ�ǰ��Ҫ��ȡ���½׶�������

	inline void _setBox();//�����Ƽ�������ʾ

	void BeginChallengeTower();//��ʼ��ս��

	void On_BeginPage_Btn_Click(cocos2d::CCObject* pSender);		//�Ҳ���ҳ��1
	void On_EndPage_Btn_Click(cocos2d::CCObject* pSender);			//�Ҳ���ҳ��2
	void On_FightResultPage_Btn_Click(cocos2d::CCObject* pSender);	//�Ҳ���ҳ��3
	void On_RewardPage_Btn_Click(cocos2d::CCObject* pSender);		//�Ҳ���ҳ��4
	void On_RewardPageCell_Btn_Click(cocos2d::CCObject* pSender);

	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	void EnterTower();//������,������ʾ�Ҳ����

	void _createGrayLayer();
	void _removeGrayLayer();

	//��Ч���
	inline void _initAnimationEffect();//��ʼ����Ч����
	//���Ŷ���
	inline void PlayEffect();

	//��̹���
	inline void FirstJump();

	//�ж��Ƿ���Ҫ��ʾӢ������
	void CheckIfNeedLvUp();

	//�ж���ʾ���䰴ť��״̬
	void CheckHaveFloorReward();

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

public:
	void _createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell, int cellIdx);

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){		};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){		};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){		};
private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		Refresh��Ǯ�ȴ���
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);



private:
	/*
		��������������ⲿ����
	*/
	void Function_EnterTower();

	/*
		��ս�������壬middle�����ⲿ����
	*/
	void Function_ChallengeTowerEnd();

	/*
		��������������ⲿ����
	*/
	void Function_ResetTower();

	/*
		ȷ��ʹ�õ������Ӵ���ȷ���¼�
	*/
	//void Function_ComfirmPaytime();

	/*
		ȷ�Ͻ����̳ǹ������
	*/
	//void Function_ComfirmEnterShop();

	/*
		ȷ������
	*/
	void Function_ComfirmReset();

	/*
		��ʾ���Բ���������
	*/
	void Function_NotifyHeroRun();

	/*
		��ʼ������ʾ�д������Կ�ʼ��
	*/
	void Function_StartTower();

	/*
		��ÿ���ս�����
	*/
	void Function_GetFastFightResult();

	/*
		��ʯ���ý��
	*/
	void Function_JewelResetResult();

	/*
		��ý���չʾ����
	*/
	void Function_EnterRewardData();

	/*
		��ȡĳ�������ķ���
	*/
	void Function_GetRewardResult(char type, int idx);

	/*
		���������ڿ�������ʱ��Ҫ��������һ������
	*/
	void Function_LostRetryFastFight();

};


#endif
