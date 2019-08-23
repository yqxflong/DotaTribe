// Name :		AthleticResultWindow.h
// Function:	战斗阶段界面
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

	//显示弹窗
	virtual void ShowPopWindow();
	//弹窗已经隐藏
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
		初始化普通战斗结果数据
	*/
	void InitCustomBattleRewareData();

	/*
		初始化爬塔战斗结果数据
	*/
	void InitTowerRewardData();

	/*
		初始化竞技场战斗结果数据
	*/
	void InitArenaBattleData();

	/*
		初始化组队副本战斗结果数据
	*/
	void InitTeamBattleRewardData();

	/*
		初始化仆从奖励数据
	*/
	void InitServantRewardData();

	/*
		初始化好友切磋奖励数据
	*/
	void InitFriendBattleData();

	/*
		初始化矿洞战斗奖励
	*/
	void InitKuangDongBattleData();

	/*
		初始化Boss积分战斗奖励数据
	*/
	void InitBossScoreBattleData();

	/*
		初始化寻宝猎人战斗奖数据
	*/
	void InitHuntLieRenBattleData();

private:
	void    OnInitUISetting();

	/*
		设置结果结算面板按钮可见状态
	*/
	void SetBtnEnableStatus();
	void InitLayer();
	CCNode* getShowLayer();
	void SetScoreColor(CCMultiLineLabelTTF* pLabel,int num); //设置战力值颜色
public:
	/*
		消息事件响应处理
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
	bool  athleticsWinType;//战斗输赢状态
	int rewardNum;
	int rewardLv; 
	CCNode* m_pRoot;
	CCNode* m_pWin;
	CCNode* m_pLose;
	CCSkeletonAnimation* m_TitleSkeleton;
	CCSkeletonAnimation* m_StarSkeleton;
};
 
#endif