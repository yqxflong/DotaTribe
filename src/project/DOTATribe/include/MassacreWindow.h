// Name :		MassacreWindow.h
// Function:	扫荡窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_MASSACREWINDOW_H_
#define  _DOTATRIBE_MASSACREWINDOW_H_


#include "IWindow.h"
#include "cocos2d.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CTableView.h"
#include "../include/MassacreDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/IPopWindow.h"

class MassacreWindow : public IWindow
	,public IPopWindow
{
public:
	MassacreWindow();
	virtual ~MassacreWindow();

	enum{
		MassacreMakeLayer,
		MassacreBG,
		MassacreCloseButton,
		MassacreChoice1Button,
		MassacreChoice1Text,
		MassacreChoice2Button,
		MassacreChoice2Text,
		MassacreChoice3Button,
		MassacreChoice3Text,
		MassacreChoice4Button,
		MassacreChoice4Text,
		MassacreCountNum,
		MassacreExpImage,
		MassacreExp,
		MassacreMoneyImage,
		MassacreMoney,
		MassacreOBJ_1_,
		MassacreIconNum1,
		MassacreOBJ_10_ = 34,
		MassacreIconNum10 = 35,
		};

	enum{

		MassacreChoiceUnknow=0,
		MassacreChoice1,
		MassacreChoice2,
		MassacreChoice3,

	};

	enum{

		MassacreSelectInde1,
		MassacreSelectInde2,
		MassacreSelectInde3,
	};

	enum{
		FULL_ITEM_BEG = 0,	//endtype = 1这两种=1情况时客户端拆分的
		FULL_EQUP_BEG,		//endtype = 1
		LESS_TILI,	//体力不足	//endtype = 2
		LESS_TIME,	//次数不足	//endtype = 3
		LESS_HEROLEVEL,//	人物等级不足 //endtype = 4

	};
public:
	virtual bool Init();
	virtual bool Load();
	virtual void Tick();
	virtual void Destroy();
	virtual void ShowPopWindow();
	virtual void PopWindowDidHide();
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	
public:
	
	void UpdataItemList(MassacreData* pData);
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
	void On_Click_Close(cocos2d::CCObject* pSender);
	void On_Click_Choice(cocos2d::CCObject* pSender);
	void ShowWindow();
	void InitControl();

public:
	CCLayer* m_pRoot;
	CMenuItemSprite*		m_choice1;
	CMenuItemSprite*		m_choice2;
	CMenuItemSprite*		m_choice3;
	CMenuItemSprite*		m_choice4;
	CCSprite*		m_choicebg1;
	CCSprite*		m_choicebg2;
	CCSprite*		m_choicebg3;
	CCSprite*		m_choicebg4;	
	int				m_selectIndex;
	int				m_MassacreCount;
	int				m_Count;
	int				m_AllCount;
	int				m_IsRealMassacreCount;
	float			m_Massacre_Interval_Time;
	bool			m_IsNeedSend;
	int				m_exp;
	int				m_money;
	std::vector<ItemData>	m_ItemList;


private:
	inline StatesInfoData* _uckGetCurStates();
	inline void _uckCreateLayer();
	inline void _uckInitButton();
	inline void _uckInitBossStates();
	inline void _uckCheckIsBossStates();
	inline void _uckUpdataBossStates();
	inline bool _uckCheckIsBagFull();
	inline bool _uckCheckIsHasChallengeTimes();
	inline void _uckSetMassacreCount();
	inline void _uckClearMassacreInfo();
	inline void _uckSendMassacrePacket();
	inline void _uckSetSelectIndex(CMenuItemSprite* pItem);
	inline void _uckShowTipBox(int type);
	inline void _uckCheckIsNeedSend();
	inline void _uckSetExp();
	inline void _uckSetMoney();
	inline void _uckSetTimes();
	inline void _uckReSetTimes();
	inline void _uckUpdataItemList();
	inline void _uckAddItem(MassacreData* pData,int idx);
	inline void _uckSetItem();
	inline void _uckHiedAllItem();
	inline void _uckAddExpAndMoney();
	inline void _uckUpdataRewardInfo();
	inline void _uckUpDataMassacreInfo();
	inline void _uckUpdataTimesAndCloseWindow();
	inline void _uckUpdataTimesAndStopMassacre();
	inline void _uckUpdataTimesAndTheLastMassacre();
	//inline void _uckUpdataTimesAndContinueMassacre();
};

#endif
