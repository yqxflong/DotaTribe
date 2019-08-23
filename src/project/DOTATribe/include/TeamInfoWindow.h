// Name : TeamInfoWindow.h
// Function:队伍信息窗口
// Author : lvyunlong
// Date: 20140610

#ifndef  _DOTATRIBE_TEAMINFOWINDOW_H_
#define  _DOTATRIBE_TEAMINFOWINDOW_H_

#include "IWindow.h"
#include "../include/CPublicVarReader.h"
#include <cocos2d.h>
#include <cocos-ext.h>


class TeamInfoWindow : public IWindow
{
private:
	enum{
			udBG = 0,
			udBG1,
			udSHADOWBG,
			udCOMMANDNODE,
			udTITLEBG,
			udTITLEICON,
			udPROMPTTTF,
			udEXCHANGEHEROBTN1,
			udEXCHANGEHEROBTN2,
			udCLOSEBTN,
			udHERONODE1,
			udHERONODE2,
			udHERONODE3,
			udHERONUM1,
			udHERONUM2,
			udHERONUM3,
		};

	enum{
			HI_STAR,
			HI_BG,
			HI_LOCK,
			HI_OPENLEVEL,
			HI_NAMEBG,
			HI_HERONAMETTF,
			HI_STRENGTHTTF,
			HI_STRNEGTHICON,
			HI_EXCHANGE_HEROBTN,
			HI_EXCHANGE_HEROTTF,
			HI_EXCHANGE_EQUIPBTN,
			HI_EXCHANGE_EQUIPTTF,
			HI_EXCHANGE_SOULBTN,
			HI_EXCHANGE_SOULTTF,
			HI_EXCHANGE_SKILLBTN,
			HI_EXCHANGE_SKILLTTF,
			HI_HEROMASKNODE,
			HI_EXCHANGE_HEROBTN1,
			HI_EXCHANGE_HEROTTF1,
		};
public:
	TeamInfoWindow();
	virtual ~TeamInfoWindow();
public:
	int m_nBackWindowType;
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _initControl();
	void _setheroinfo();
	void _mapHeroInfoBtn(int index);
	void _setRoleInfoNode();
	void _setShowHeroDaiji(int index,int heroid,CCNode* node);
	void _setHeroInfoVisible(int index,CCNode* node);
	void _setEXTeamBtn();
private:
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonArray[3];	//英雄角色3角色
public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		显示面板事件处理	
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏面板事件处理	
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新面板事件处理	
	*/
	inline void  OnUpDateWindowEventHandler(std::list<std::string>& paramList);
private:
	void On_Check_ClickBtn(cocos2d::CCObject * pSender);

	void On_Close_ClickBtn(cocos2d::CCObject * pSender);

	void On_Click_EXHero_Event(cocos2d::CCObject * pSender);

	void On_Click_EXEquip_Event(cocos2d::CCObject * pSender);

	void On_Click_EXSkill_Event(cocos2d::CCObject * pSender);

	void On_Click_EXSoul_Event(cocos2d::CCObject * pSender);

	bool _isSoulFuncOpen();

};

#endif