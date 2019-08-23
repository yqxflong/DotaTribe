//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The RoleStatus Bar will be put in many scenes
//	  PS: The anchor is (0.5,0.5)

#ifndef _DOTA_DTROLESTATUSBAR_H_
#define _DOTA_DTROLESTATUSBAR_H_

#include <cocos2d.h>

class DTRoleStatusBarDelegate{
public:
	virtual void AvatarClickEvent()=0;
	virtual void SkillClickEvent()=0;
	virtual void AddTLClickEvent()=0;
};

class DTRoleStatusBar:public cocos2d::CCNode{
public:
	DTRoleStatusBar();
	virtual ~DTRoleStatusBar();
	static DTRoleStatusBar* create();
	bool init();
	void setDelegate(DTRoleStatusBarDelegate* pDel);
	//
	void Tick();
	void Tick_Battle();
	void Refresh();
	void ResetPropertyByNode(cocos2d::CCNode* node);
protected:
	void On_Click_Event(cocos2d::CCObject* pSender);
private:
	enum{
		kSTATUSBG,
		kAVATARBOTTOM,
		kAVATAR,
		kLVVALUE,
		kDIAMOND,
		kMONEY,
		kZL,
		kTL,
		kNAME,
		kEXPBAR,
		kUPDATEZL_TIME,
		kADDBTN,
	};
	DTRoleStatusBarDelegate* m_pDelegate;
	bool m_isBTickBattle;		//当前是否更新战力
	int m_iTickBattleNum;		//需要Tick的战力数
	int m_iCurBatCapacity;		//当前人物战力
	int m_addBatMean;
private:
	inline void _initLayout();
	inline void _refreshData();
	inline void _setRoleLv();
	inline void _setRoleAvatar();
	inline void _setName();
	inline void _setZL();
	inline void _setExp();
	inline void _setTL();
	inline void _setGold();
	inline void _setDiamond();

	//
	inline void _mapBtns();
};

#endif