
#ifndef  _DOTATRIBE_EQUIPPROMOTEVIEW_H_
#define  _DOTATRIBE_EQUIPPROMOTEVIEW_H_


#include "../include/SubView.h"
#include "cocos2d.h"
#include <string>
#include "../include/AnimationEffect.h"

class EquipPromoteView : public HLSubView, AnimationEffectCallBackProtocol
{
public:
	enum
	{
		EquipPromoteView_BG,
		EquipPromoteView_Line1_1,
		EquipPromoteView_Line1_2,
		EquipPromoteView_Line1_3,
		EquipPromoteView_Line1_4,
		EquipPromoteView_Line2_1,
		EquipPromoteView_Line2_2,
		EquipPromoteView_Line2_3,
		EquipPromoteView_Line2_4,
		EquipPromoteView_Line3_1,
		EquipPromoteView_Line3_2,
		EquipPromoteView_Line3_3,
		EquipPromoteView_Line3_4,
		EquipPromoteView_Line4_1,
		EquipPromoteView_Line4_2,
		EquipPromoteView_Line4_3,
		EquipPromoteView_Line4_4,
		EquipPromoteView_Line5_1,
		EquipPromoteView_Line5_2,
		EquipPromoteView_Line5_3,
		EquipPromoteView_Line5_4,
		EquipPromoteView_Item1,
		EquipPromoteView_Item1_Num,
		EquipPromoteView_Item2,
		EquipPromoteView_Item2_Num,
		EquipPromoteView_Button,
		EquipPromoteView_Button_Label,
		EquipPromoteView_Gold_Icon,
		EquipPromoteView_Gold,
		EquipPromoteView_LV_Limit,
		EquipPromoteView_Max_LV_Label,
		EquipPromoteAnimationMaskNode,//动画挂载点
	};

	enum
	{
		EquipPromoteView_Empty,
		EquipPromoteView_Line1,
		EquipPromoteView_Line2,
		EquipPromoteView_Line3,
		EquipPromoteView_Line4,
	};
public:
	EquipPromoteView();
	virtual ~EquipPromoteView();
public:
	bool m_IsCanPromote;
	bool m_IsFirstIn;
	int	m_CurEquipID;
	int ArrcrystalitemID[5];
	int m_CurEquipLv;
	int m_CurEquipLine1;
	int m_CurEquipLine2;
	int m_CurEquipLine3;
	int m_CurEquipLine4;
	virtual	bool	onLoad();
	virtual	bool    onTick();
	virtual	bool    onDestroy();
	virtual	void	EquipHasBeenSeleted(int equipID);
	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
	void On_Promote(cocos2d::CCObject* pSender);
	void On_Btn_Tips(cocos2d::CCObject* pSender);
	void initLayer();
	int	GetCurAttribute(int index);
	int	GetCurItemLv();
	void UpdataPromoteInfo();
	void _initLocalData();
	void _updataLocalData();
	void _updataInfoLine1();
	void _updataAttributeInfo();
	void _updataHideUnuseAttributeInfo();
	void _updataItemInfo();
	void _updataHideUnuseItemInfo();
	void _updataCostMoneyInfo();
	void _updataLvLimitInfo();
	void _updataButtonInfo();
	void _updataIsMaxLv();
	void _updataEmpty();
	void _MapBtnTips();

public:
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
};


#endif

