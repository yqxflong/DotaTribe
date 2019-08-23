// Name :		SelectSonMissionWindow.h
// Function:	小关卡选择窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_SELECTSONMISSIONWINDOW_H_
#define  _DOTATRIBE_SELECTSONMISSIONWINDOW_H_
 
#include "IWindow.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../include/MissionDataHandler.h"
#include "../include/CMenuItemSprite.h"

class SelectSonMissionWindow : public IWindow , public cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate
{
public:
	SelectSonMissionWindow();
	virtual ~SelectSonMissionWindow();
	enum
	{
		_MISSION_SCENCE_BG_,
		_MISSION_BACK_HOME_BTN_,
		_MISSION_BACK_CUSTOM_BTN_,
		_MISSION_TITTLE_LABEL_,
		_MISSION_REWARD_LABEL_,
		_MISSION_REWARD_EXP_IMAGE_,
		_MISSION_REWARD_EXP_VALUE_,
		_MISSION_REWARD_MONEY_IMAGE_,
		_MISSION_REWARD_MONEY_VALUE_,
		_MISSION_COST_POWER_LABEL_,
		_MISSION_RESER_JEWEL_IMAGE_,
		_MISSION_PERHAPS_REWARD_LABEL_,
		_MISSION_REWARD_ITEM_0_,
		_MISSION_REWARD_ITEM_1_,
		_MISSION_REWARD_ITEM_2_,
		_MISSION_CHALLENEGE_BTN_,
		_MISSION_CHALLENEGE_LABEL_,
		_MISSION_WIPE_BTN_,
		_MISSION_WIPE_LABEL_,
		_MISSION_CLEAR_BTN_,
		_MISSION_CLEAR_LABEL_,
		_MISSION_FULLSTAR_REWARD_BTN_,
		_MISSION_FULLSTAR_REWARD_LABEL_,
		_MISSION_RIGHT_BTN_EFFECT_,
		_MISSION_LEFT_ARROWHEAD_,
		_MISSION_RIGHT_ARROWHEAD_,
		_MISSION_CUSTOM_TABLEVIEW_,
		_MISSION_CUSTOM_CELL_,
		_MISSION_LEFT_SKELETON_EFFECT_,
		_MISSION_RIGHT_SKELETON_EFFECT_, 
		_MISSION_ARROW_GUID_SKELETON_,
	};
	 
	enum
	{
		_CUSTOM_BG_,
		_CUSTOM_ADPET_NODE_,
		_CUSTOM_REWARD_NODE_,
		_CUSTOM_NAME_,
		_CUSTOM_STAR_0_,
		_CUSTOM_STAR_1_,
		_CUSTOM_STAR_2_,
		_CUSTOM_LEFT_LABEL_,
		_CUSTOM_VALUE_LABEL_,
		_CUSTOM_HIGH_LIGHT_BG_,
		_CUSTOM_BATTLE_LOGO_BG_,
		_CUSTOM_LOCK_BG_,
		_CUSTOM_OPEN_LEVEL_LABEL_,
	};
	 
public:
	virtual bool Init();
	virtual bool Load();
	virtual void Tick();
	virtual void Destroy();
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
public:
	void   CommonSelectorHandler(cocos2d::CCObject * pSender);

	/*
		显示新手引导2
	*/
	void ShowNewGuide_2();
private:
	/*
	   显示关卡场景
	*/     
	void OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		事件接收器
	*/
	static void Event_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	/*
	   初始化关卡布局
	*/
	 void InitUILayout();
	/*
	   初始化绑定按钮事件
	*/
	 void InitBindMenuSelector();
	/*
	   设置TableView
	*/
	 void SetTableView();  

	/*
	   创建列表子项
	*/
	void   CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);
		
	/*
	   设置列表子项内容
	*/
 	void   SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex); 

	/*
		物品Tips回调处理事件
	*/
	void  RewardTipsInfoHandler(cocos2d::CCObject * pSender);

	/*
	   关卡子项Cell点击事件通知
	   */
	void  CustomCellEventHandler(cocos2d::CCObject * pSender);
private:
	/*
	 TableView的通知事件
	*/  
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view); 

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){}; 
	 
private:
	//动态绑定内存数据刷新界面
	void  UpdateUIWithData(bool isNeedLocationFullStar=true);
	//刷新关卡
	void  UpdateCustomView(); 
	//刷新关卡列表界面
	void  UpdateCustomCellView();
	//刷新奖励信息界面
	void  UpdateRewardInfo();
	//刷新按钮状态
	void  UpdateBtnStates();
	//刷新花费内容
	void  UpdateCostLabel();
	//检测新手引导
	void  CheckGuid();  

	//更新奖励信息结点
	void  UpdateRewardInfoWithData(PRewardItemNode pRewardItemNode,int ItemUIInidex,int customID,int interIndex);

	//更新星星等级
	void  UpdateCellStarNum(cocos2d::extension::CCTableViewCell * pTableCell,IByte starNum);

	//显示引导箭头骨骼动画
	void  ShowGuidArrowSkeleton(bool showEnable);
	//分析该显示的关卡ID
	void  AnlayseInitCustomID();

	//检测是否需要自动递增
	void  CheckIsNeedAutoUp();

	//检测是否可以挑战到下个大关卡
	void JudgeToNextMission();

private:
	cocos2d::extension::CCTableView *   m_pCustomTable;
	cocos2d::CCSize						m_nCellSize;
	MissionInfoData	*					m_pMissionInfoData; 
	std::string							m_sMissionName;
	int									m_nMissionID;  //(ID从1开始)
	int									m_nCustomID;   //(ID从1开启)
	int									m_nLastClickCustomID; //上次点击CustomID 索引从1开始
	int									m_nMaxCustomNum;
	int									m_nMaxCanChallenegCID;
	int									m_nReNetReConverSID;	//记录断线重连前记忆关卡ID
	bool								m_bCanGetFullReward;
	bool								m_bHadGotFullReward;
	bool								m_bDuringGuid;
	bool								m_bIsNeedAutoUp;	  //是否需要自动递增
	bool								m_bIsNeedClearMemory; //是否需要清除记忆
	bool								m_bIsReconverReNetSID;//是否恢复断线重连记忆
	bool								m_bIsJudgeFullAfterFight; //判断全通关无三星是否提示挑战下一个
	UShort								m_nPlayerLevel;		  //备份玩家等级

};

#endif
