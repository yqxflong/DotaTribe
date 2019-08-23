// Name :		SelectMissionWindow.h
// Function:	世界地图窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_SELECTMISSIONWINDOW_H_
#define  _DOTATRIBE_SELECTMISSIONWINDOW_H_


#include "IWindow.h"
#include "../include/CMenuItemSprite.h"
class SelectMissionWindow : public IWindow
{
public:
	enum
	{
		Mission_BG1,
		Mission_BG2,
		Mission_BG3,
		Mission_Return,
		Mission_Item1,
		Mission_Item2,
		Mission_Item3,
		Mission_Item4,
		Mission_Item5,
		Mission_Item6,
		Mission_Item7,
		Mission_Item8,
		Mission_Item9,
		Mission_Item10,
		Mission_Item11,
		Mission_Item12,
		Mission_Item13,
		Mission_Item14,
		Mission_Item15,
		Mission_Effect,
		Mission_Arrow1,
		Mission_Arrow2,
		Mission_Arrow3,
		Mission_Arrow4,
		Mission_Arrow5,
		Mission_Arrow6,
		Mission_Arrow7,
		Mission_Arrow8,
		Mission_Arrow9,
		Mission_Arrow10,
		Mission_Arrow11,
		Mission_Arrow12,
		Mission_Arrow13,
		Mission_Arrow14,
		Mission_NameBG,
		Mission_end,
	};
	SelectMissionWindow();
	virtual ~SelectMissionWindow();

public:
	CCLayer* m_pRoot;
	CCPoint m_BeginPos;
	CCPoint m_EndPos;
	float   m_MoveLength;
	CCScrollView *scroll;
	
public:
	virtual bool Init();
	virtual bool Load();
	virtual void Tick();
	virtual void Destroy();
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);

	void OnSceneButtonClick(cocos2d::CCObject* pSender);
	void OnReturnHomeButtonClick(cocos2d::CCObject* pSender);
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
	void InitMission();
	float GetOffsetX();
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);


private:
	inline void _uckCreateScrollView();
	inline void _uckCreateLayerout();
	inline void _uckHideAllBuildingAndSetTarget();
	inline void _uckShowOpenBuilding();
	inline void _uckHideAllWay();
	inline void _uckShowOpenWay();
	inline void _uckSetReturnButton();
	inline void _uckSetEffectPos(CCPoint point);
	inline void _uckSetBuildingNameBG(CMenuItemSprite* pItem);
	inline void _uckSetBuildingName(int missionID,CMenuItemSprite* pItem);
};

#endif
