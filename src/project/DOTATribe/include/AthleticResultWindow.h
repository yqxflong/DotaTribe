// Name :		AthleticResultWindow.h
// Function:	ս���׶ν���
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_ATHLETICSRESULTWINDOW_H
#define  _DOTATRIBE_ATHLETICSRESULTWINDOW_H

#include "IWindow.h"
#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/HeroicRole.h"
#include "../include/AthleticsSceneManager.h"
#include  "spine/spine-cocos2dx.h" 
#include  "spine/SpineCallBackEvent.h"
#include "../include/IPopWindow.h"

using namespace cocos2d::extension;


class   AthleticsResultWindow :public IWindow,public IPopWindow,public SkeletonCallBackProtocol
{
public:
	enum
	{
		_Result_MarkLayer_,
		_Result_WinBG_,         
		_Result_WinTitle_,         
		_Result_WinStar_,    
		_Result_WinText_,    
		_Result_WinExp_,   
		_Result_WinExpValue_,   
		_Result_WinMoney_,   
		_Result_WinMoneyValue_,   
		_Result_WinShengWang_,   
		_Result_WinShengWangValue_,  
		_Result_WinItem1OBJ_,
		_Result_WinItem1Num_,
		_Result_WinItem2OBJ_,   
		_Result_WinItem2Num_,   
		_Result_WinItem3OBJ_,
		_Result_WinItem3Num_,
		_Result_WinRePlayButton_,
		_Result_WinRePlayButtonLabel_,
		_Result_WinSureButton_,
		_Result_WinSureButtonLabel_,
		_Result_LoseBG_,
		_Result_LoseTitle_,
		_Result_LoseText_,
		_Result_LoseEquipAppraise_,
		_Result_LoseEquipAppraiseValue_,
		//_Result_LoseSkillButton_,
		_Result_LoseHeroButton_,
		_Result_LoseEquipButton_,
		_Result_LoseRePlayButton_,
		_Result_LoseRePlayButtonLabel_,
		_Result_LoseTryAgainButton_,
		_Result_LoseTryAgainButtonLabel_,
		_Result_LoseSureButton_,
		_Result_LoseSureButtonLabel_,
		_Result_LostPrestigeImage_,
		_Result_LostPrestigeValue_,
		_Result_End_,
	};
	enum
	{
		_ENUM_ZERO_,
		_ENUM_ONE_,         
		_ENUM_TWO_,         
		_ENUM_THREE,          
	};
	  AthleticsResultWindow();
	  ~AthleticsResultWindow();
public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick(); 
	virtual    void    Destroy();

	//��ʾ����
	virtual void ShowPopWindow();
	//�����Ѿ�����
	virtual void PopWindowDidHide();

	void  OnRePlayClick(CCObject * pSender);
	void  OnFightAgainClick(CCObject * pSender);
	void  OnExitClick(CCObject * pSender);

	void  OnBackToChangeHeroClick(CCObject * pSender);
	void  OnBackToSkillClick(CCObject * pSender);
	void  OnBackToEmployClick(CCObject * pSender);
	void  _fallDown(cocos2d::CCNode* actionNode);
	void  _fallDownCallBack();

	void  InitData();

	/*
		��ʼ����ͨս���������
	*/
	void InitCustomBattleRewareData();

	/*
		��ʼ������ս���������
	*/
	void InitTowerRewardData();

	/*
		��ʼ��������ս���������
	*/
	void InitArenaBattleData();

	/*
		��ʼ����Ӹ���ս���������
	*/
	void InitTeamBattleRewardData();

	/*
		��ʼ���ʹӽ�������
	*/
	void InitServantRewardData();

	/*
		��ʼ�������д轱������
	*/
	void InitFriendBattleData();

	/*
		��ʼ����ս������
	*/
	void InitKuangDongBattleData();

	/*
		��ʼ��Boss����ս����������
	*/
	void InitBossScoreBattleData();

	/*
		��ʼ��Ѱ������ս��������
	*/
	void InitHuntLieRenBattleData();

private:
	void    OnInitUISetting();

	/*
		���ý��������尴ť�ɼ�״̬
	*/
	void SetBtnEnableStatus();
	void InitLayer();
	CCNode* getShowLayer();
	void SetScoreColor(CCMultiLineLabelTTF* pLabel,int num); //����ս��ֵ��ɫ
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	void ShowWindow();
	void    skeletonTriggerCallHandler(int eventType,int animationID,cocos2d::extension::PSkeletonCallBack_Node  pSkeletonCallBackNode);
	void    boneBindEffectCallHandler(int eventType,BoneEfectData & boneEffectData){};

protected:
	std::string rewardOneImage;
	std::string rewardOneValue;
	std::string rewardTwoImage;
	std::string rewardTwoValue;
	std::string rewardThreeValue;
	std::string levelUpNeedExp;
	std::string rewardInfo;
	int  obj_quality_1;
	int  obj_quality_2;
	int  obj_quality_3;
	int	 obj_icon_1;
	int	 obj_icon_2;
	int	 obj_icon_3;
	int rewardGoodsOneNum;
	int rewardGoodsTwoNum;
	int rewardGoodsThreeNum;
	int rewardGoodsTypeOne;
	int rewardGoodsTypeTwo;
	int rewardGoodsTypeThree;
	bool  athleticsWinType;//ս����Ӯ״̬
	int rewardNum;
	int rewardLv; 
	CCNode* m_pRoot;
	CCNode* m_pWin;
	CCNode* m_pLose;
	CCSkeletonAnimation* m_TitleSkeleton;
	CCSkeletonAnimation* m_StarSkeleton;
};
 
#endif