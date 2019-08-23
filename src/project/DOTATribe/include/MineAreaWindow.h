//Name : MineAreaWindow
//Function : ��
//Author : ����
//Date: 20131128

#ifndef _DOTATRIBE_MINEAREA_WINDOW_H_
#define _DOTATRIBE_MINEAREA_WINDOW_H_

#include "../include/IWindow.h"
#include "cocos-ext.h"
#include "../include/CMenuItemSprite.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"

class MineAreaWindow : public IWindow, public AnimationEffectCallBackProtocol
{
public:
	enum
	{
		_PAGE_UNKNOW_ = 0,
		_PAGE_GOBLINAREA_ = 1,		//�ؾ�����
		_PAGE_DWARVENAREA_ = 2,		//���˿���
		_PAGE_DRAGONAREA_ = 3,		//��������
		_PAGE_HUNTMINE_ = 4,		//Ѱ����
	}PAGE;

	enum{
		_STRING_SLAVE_LABEL_ = 916,//ū������
		_STRING_GOLD_LABEL_ = 917,//���Ч��
		_STRING_START_MINING_ = 921,//��ʼ�ɼ�
		_STRING_STOP_MINING_ = 922,//�����ɼ�
		_STRING_LEFT_QIANG_TIMES_ = 6097,//�����λ����%d
		_STRING_QIANGKUANGWEI_ = 924,//����λ
		_STRING_OWNER_NAME_ = 925,//��������
		_STRING_OWNER_CAPA_ = 926,//����ս����
		_STRING_FIGHT_ = 927,//��ս
		_STRING_MINING_ = 928,//�ɼ�
		_STRING_MINING_FRIEND_ = 929,//�ɿ������
		_STRING_CAPA_LABEL_ = 527,	//ս��
		_STRING_TOTALOUTPUT_LABEL = 920,//�ۼƻ��
		_STRING_OWNER_NOT_FRIEND_ = 930,//���������ҵĺ���

		_STRING_HUNT_SAYINGBEGIN_NPC_ = 12000,			//Ѱ����������Ҫ��Ұ��˵�Ļ����漴��ʼ
		_STRING_HUNT_SAYINGBEGIN_HUMAN_ = 12005,	//Ѱ����������Ҫ�����˵�Ļ����漴��ʼ
		_STRING_HUNT_ADDFRIEND_ = 931,			//�Ӻ���
		_STRING_HUNT_QIANGDUO_ = 932,			//����
		_STRING_HUNT_QUZHU_ = 933,				//����
		_STRING_HUNT_BUYMINRAL_ = 934,			//�����ʯ
		_STRING_HUNT_MEET_ = 935,				//Ѱ������������%d(ս����%d)
		_STRING_HUNT_HELLOFRIEND_ = 936,		//���к�
		_STRING_HUNT_BUYMINRALPRICE_ = 937,			//�����ʯ�۸�

		_STRING_NOT_MINING_ = 938,				//���ٲɿ�
	};

private:
	enum{
		gBg = 0,
		gBoard,
		gGrey,
		gMinePic,
		gMineName,
		gSitBg,
		gSitMyTip,
		gSitQuality,
		gSitLevelBg,
		gSitLevel,
		gSitName,
		gSitNameValue,
		gSitNameBg,
		gSitTime,
		gSitTimeValue,
		gSitTimeBg,
		gSitTotal,
		gSitTotalValue,
		gSitTotalBg,
		gStartStopBtn,
		gStartStopLabel,
		gQuickBackHomeBtn,
		gBackUpBtn,
	}Goblin;

	enum{
		dBg,
		dBoard,
		dGrey,
		dMinePic,
		dMineName,
		dLeftArrow,
		dRightArrow,
		dLeftTimeBg,
		dLeftTimeLabel,
		dLeftTimeMoney,
		dPageBg,
		dPageLabel,
		dQuickBackHomeBtn,
		dBackUpBtn,
		dSitBg0,
		dSitMyTip0,
		dSitQuality0,
		dSitLevelBg0,
		dSitLevel0,
		dSitName0,
		dSitNameValue0,
		dSitNameBg0,
		dSitTime0,
		dSitTimeValue0,
		dSitTimeBg0,
		dSitTotal0,
		dSitTotalValue0,
		dSitTotalBg0,
		dStartStopBtn0,
		dStartStopLabel0,
		dSitBg1,
		dSitMyTip1,
		dSitQuality1,
		dSitLevelBg1,
		dSitLevel1,
		dSitName1,
		dSitNameValue1,
		dSitNameBg1,
		dSitTime1,
		dSitTimeValue1,
		dSitTimeBg1,
		dSitTotal1,
		dSitTotalValue1,
		dSitTotalBg1,
		dStartStopBtn1,
		dStartStopLabel1,
		dSitBg2,
		dSitMyTip2,
		dSitQuality2,
		dSitLevelBg2,
		dSitLevel2,
		dSitName2,
		dSitNameValue2,
		dSitNameBg2,
		dSitTime2,
		dSitTimeValue2,
		dSitTimeBg2,
		dSitTotal2,
		dSitTotalValue2,
		dSitTotalBg2,
		dStartStopBtn2,
		dStartStopLabel2,
		dSitBg3,
		dSitMyTip3,
		dSitQuality3,
		dSitLevelBg3,
		dSitLevel3,
		dSitName3,
		dSitNameValue3,
		dSitNameBg3,
		dSitTime3,
		dSitTimeValue3,
		dSitTimeBg3,
		dSitTotal3,
		dSitTotalValue3,
		dSitTotalBg3,
		dStartStopBtn3,
		dStartStopLabel3,

	}Dwarven;

	enum{
		nBg,
		nBoard,
		nGrey,
		nMinePic,
		nMineName,
		nQuickBackHomeBtn,
		nBackUpBtn,
		nOwnerBg0,
		nOwnerQuality0,
		nOwnerLvBg0,
		nOwnerLv0,
		nOwnerNameBg0,
		nOwnerName0,
		nOwnerBg1,
		nOwnerQuality1,
		nOwnerLvBg1,
		nOwnerLv1,
		nOwnerNameBg1,
		nOwnerName1,
		nOwnerBg2,
		nOwnerQuality2,
		nOwnerLvBg2,
		nOwnerLv2,
		nOwnerNameBg2,
		nOwnerName2,
		nOwnerBg3,
		nOwnerQuality3,
		nOwnerLvBg3,
		nOwnerLv3,
		nOwnerNameBg3,
		nOwnerName3,

		nOwnerName,
		nOwnerCapa,
		nOwnerDesc,

		nOwnerTiaoZhan,//show or not
		nOwnerTiaoZhanLabel,
		nOwnerJewelPic,
		nOwnerJewelLabel,

		nOwnerCaiKuang,
		nOwnerCaiKuangLabel,

		nSitBg,//show or not
		nSitMyTip,
		nSitIcon,
		nSitLevelBg,
		nSitLevel,
		nSitName,
		nSitNameValue,
		nSitNameBg,
		nSitTime,
		nSitTimeValue,
		nSitTimeBg,
		nSitTotal,
		nSitTotalValue,
		nSitTotalBg,
		nStartStopBtn,
		nSrartStopLabel,

	}Dragon;

	enum{
		hMap0,
		hMap1,
		hGreyLine,
		hBianKuang,
		hHeroMask,
		hEffectMask,
		hMonsterMask,
		hProgress,
		hProgressBg,
		hProgressLabel,
		hDesc,
		hHuntBtn,
		hQuickBackHomeBtn,
		hBackUpBtn,
		hGrey,
		hTipBg,
		hTipIcon,
		hTipSay,
		hTipMeet,//����ս��
		hTipBtn0,
		hTipBtn0Label,
		hTipBtn1,
		hTipBtn1Label,
		hTipBuyMinralPrice,//�����ʯ�۸�
		hTipBuyMinralJewelPic,	//��ʯͼ��
		hLieRen0,//װ������
		hLieRen1,//��������
		hLieRen2,//��ʯ����
		hLieRen3,//��Ӣ����
		hLieRenMask0,//װ������
		hLieRenMask1,//��������
		hLieRenMask2,//��ʯ����
		hLieRenMask3,//��Ӣ����
		hGrey2,					//������
		hTipBg2,				//�ᱦ����
		hTipTitle2,				//�ᱦ����
		hTipLevelDesc2,			//�ȼ�˵��
		hTipDesc2,				//˵��
		hProability2,			//����ɹ�����
		hTipLine2,				//�ָ���
		hTipNoLieRenLabel2,		//û������˵������
		hTipAwardBoard2,		//�������
		hTipAwardName2,			//��������
		hTipNoBtn2,				//�������ᰴť
		hTipNoBtnLabel2,		//������������
		hTipYesBtn2,			//���ᰴť
		hTipYesBtnLabel2,		//���ᰴť����
		hTipSpentLabel2,		//���Ứ��
		hTipCloseBtn2,				//������ϸ��Ϣ����Ĺر�
	}Hunt;

private:
	int m_iShowPage;

	int m_iBackWindow;
	cocos2d::CCNode * m_pRoot; 

	int m_iDwarvenShowPage;//���˿���ʾ�Ľ���

	CMenuItemSprite * m_pDragonSelectOwner;//ѡ�е�ӵ����

	//Ѱ������Ҫ�Ķ����ڵ�	//begin
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//Ӣ�۽�ɫ,��������
	cocos2d::CCSprite * m_pAnimationPlayNode;//���Ŷ����ڵ�
	AnimationFileData * m_pAnimationFileData;//��Ч�ļ�
	cocos2d::CCAnimation * m_pAnimation;//����
	cocos2d::CCRepeatForever * pAnimationAction;//�ظ����Ŷ���
	CPriorityLayerColor * m_pAnimationGrayLayer;
	bool m_bHeroRun;//Ӣ�ۿ�ʼ��
	int m_iRunTickTime;//Ĭ���ܶ�ʱ��
	int m_iRunTickCount;//�ܶ���ʱ��
	CCNode * m_pHuntMap0;//��ͼ0
	CCNode * m_pHuntMap1;//��ͼ1
	bool m_bBoxOpen;//�����ڿ���״̬
	int m_iOpenTickTime;//���俪����ʱ

	cocos2d::CCNode * m_pLieRenJiHuoAnimation0;//ѭ������
	cocos2d::CCNode * m_pLieRenJiHuoAnimation1;//ѭ������
	cocos2d::CCNode * m_pLieRenJiHuoAnimation2;//ѭ������
	cocos2d::CCNode * m_pLieRenJiHuoAnimation3;//ѭ������
	cocos2d::CCNode * m_pLieRenKaiQiAnimation;//���ζ���
	//end
public:
	int m_iDragonSelectOwner;//ѡ�е�ӵ����

	unsigned char m_iLieRenSelected;//��ǰ�򿪵���������
public:
	MineAreaWindow();
	virtual ~MineAreaWindow();

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

	/*
		��������¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

private:
	/*
		���Ƶ�ǰҳ��
	*/
	inline void _initLayout();

	/*
		���õ�ǰҳ�������ʾ����
	*/
	inline void _setPage();

	inline void _setGoblinPage();
	inline void _setDwarvenPage();
	inline void _setDragonPage();
	inline void _setDragonRightPart();

	inline void _setHuntPage();
	inline void _setHuntTipPage();//������ͨ�����Ի���
	inline void _showHuntTipPage(bool show);
	inline void _setHuntTipPage2();//�����¼������Ի���
	inline void _showHuntTipPage2(bool show);

	inline void _clearMonster();
	inline void _playHuntMeetAnimation();
	inline void _initHuntHero();
	inline void _initHuntMap();
	inline void _heroHuntRun();
	inline void _moveHuntMap();

	inline void _workTick();
	/*
		�����Ӱ
	*/
	inline void _addShadow(cocos2d::CCNode* node);
	void _createGrayLayer();
	void _removeGrayLayer();

	/*
		�󶨰�ť
	*/
	inline void _mapBtn();

	/*
		������Ӧҳ������
	*/
	inline void _requestData();

	//����ҳ�漤��״̬��Ч
	void _setLieRenJiHuoAnimation();


public:
	void HuntAnimationCallBackFunction();
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
public:
	//���յ�����ؾ�������Ϣ
	void Function_GetEnterGoblinData();

	//���յ����밫�˿�����Ϣ
	void Function_GetEnterDwarvenData();

	//���յ��������������Ϣ
	void Function_GetEnterDragonData();

	//���յ�����Ѱ����Ϣ
	void Function_GetEnterHuntData();

	//���յ�ֹͣ�ɿ���
	void Function_GetStopMiningResult();

	//���յ���ʼ�ɿ���
	void Function_GetStartMiningResult();

	//���յ�Ѱ���������
	void Function_GetHuntingResult();

	//���յ����к����
	void Function_GetHelloFriendResult();

	//���յ�����ԭ����
	void Function_GetBuyMinralResult();

	//���յ�������ѽ��
	void Function_GetAskFriendResult();

	//���յ����˿�������λ�������Ľ��
	void Function_GetDwarvenLootResult();

	//ȷ�ϰ��˿�����Ϣˢ�µ���
	void Function_GetDwarvenPageInfoChangedConfirm();

	//Ѱ����Ϊʹ������Ʒ����������
	void Function_HuntLeftTimeUpdate(int lefttime);

	//Ѱ���鿴������ϸ��Ϣ���
	void Function_HuntLieRenChaKan();

	//Ѱ����������ĳ������
	void Function_HuntLieRenQiangDuoNo();

	
private:
	/*
		�ؾ�����ҳ���¼�
	*/
	void On_GoblinArea_Click(cocos2d::CCObject * pSender);

	/*
		���˿����¼�
	*/
	void On_DwarvenArea_Click(cocos2d::CCObject * pSender);

	/*
		���������¼�
	*/
	void On_DragonArea_Click(cocos2d::CCObject * pSender);

	/*
		Ѱ���¼�
	*/
	void On_HuntMine_Click(cocos2d::CCObject * pSender);

	/*
		�����¼�
	*/
	void On_Help(cocos2d::CCObject* pSender);

};

#endif