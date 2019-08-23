// Name :		SelectSonMissionWindow.h
// Function:	С�ؿ�ѡ�񴰿�
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
		��ʾ��������2
	*/
	void ShowNewGuide_2();
private:
	/*
	   ��ʾ�ؿ�����
	*/     
	void OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		�¼�������
	*/
	static void Event_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	/*
	   ��ʼ���ؿ�����
	*/
	 void InitUILayout();
	/*
	   ��ʼ���󶨰�ť�¼�
	*/
	 void InitBindMenuSelector();
	/*
	   ����TableView
	*/
	 void SetTableView();  

	/*
	   �����б�����
	*/
	void   CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);
		
	/*
	   �����б���������
	*/
 	void   SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex); 

	/*
		��ƷTips�ص������¼�
	*/
	void  RewardTipsInfoHandler(cocos2d::CCObject * pSender);

	/*
	   �ؿ�����Cell����¼�֪ͨ
	   */
	void  CustomCellEventHandler(cocos2d::CCObject * pSender);
private:
	/*
	 TableView��֪ͨ�¼�
	*/  
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view); 

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){}; 
	 
private:
	//��̬���ڴ�����ˢ�½���
	void  UpdateUIWithData(bool isNeedLocationFullStar=true);
	//ˢ�¹ؿ�
	void  UpdateCustomView(); 
	//ˢ�¹ؿ��б����
	void  UpdateCustomCellView();
	//ˢ�½�����Ϣ����
	void  UpdateRewardInfo();
	//ˢ�°�ť״̬
	void  UpdateBtnStates();
	//ˢ�»�������
	void  UpdateCostLabel();
	//�����������
	void  CheckGuid();  

	//���½�����Ϣ���
	void  UpdateRewardInfoWithData(PRewardItemNode pRewardItemNode,int ItemUIInidex,int customID,int interIndex);

	//�������ǵȼ�
	void  UpdateCellStarNum(cocos2d::extension::CCTableViewCell * pTableCell,IByte starNum);

	//��ʾ������ͷ��������
	void  ShowGuidArrowSkeleton(bool showEnable);
	//��������ʾ�Ĺؿ�ID
	void  AnlayseInitCustomID();

	//����Ƿ���Ҫ�Զ�����
	void  CheckIsNeedAutoUp();

	//����Ƿ������ս���¸���ؿ�
	void JudgeToNextMission();

private:
	cocos2d::extension::CCTableView *   m_pCustomTable;
	cocos2d::CCSize						m_nCellSize;
	MissionInfoData	*					m_pMissionInfoData; 
	std::string							m_sMissionName;
	int									m_nMissionID;  //(ID��1��ʼ)
	int									m_nCustomID;   //(ID��1����)
	int									m_nLastClickCustomID; //�ϴε��CustomID ������1��ʼ
	int									m_nMaxCustomNum;
	int									m_nMaxCanChallenegCID;
	int									m_nReNetReConverSID;	//��¼��������ǰ����ؿ�ID
	bool								m_bCanGetFullReward;
	bool								m_bHadGotFullReward;
	bool								m_bDuringGuid;
	bool								m_bIsNeedAutoUp;	  //�Ƿ���Ҫ�Զ�����
	bool								m_bIsNeedClearMemory; //�Ƿ���Ҫ�������
	bool								m_bIsReconverReNetSID;//�Ƿ�ָ�������������
	bool								m_bIsJudgeFullAfterFight; //�ж�ȫͨ���������Ƿ���ʾ��ս��һ��
	UShort								m_nPlayerLevel;		  //������ҵȼ�

};

#endif
