//Name：PlayerTipsWindow
//Function：玩家好友tips
//Written By：李茜
//Maintainer:  zhoushaonan, shaobing
//Time:2013-9-18

#ifndef  _DOTATRIBE_PLAYERTIPSWINDOW_H_
#define  _DOTATRIBE_PLAYERTIPSWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/FontStyleDataManager.h"
#include "../include/DTEquipBoard.h"

class PlayerTipsWindow : public IWindow,public CPriorityLayerColorDelegate,public DTEquipBoardDelegate
{
private:
	enum{
		MASKCCP = 0,			//遮罩层
		MASKSMALL,				//遮罩层（小）
		udBG,					//背景
		udCLOSEBTN,				//关闭按钮
		udSKELETONNODE,			//骨骼动画结点
		udPLAYERNAME,			//玩家名字
		udLVVALUE,				//等级值
		udABILITYVALUE,			//战力值
		udHP,					//HP
		udHPVALUE,				//HP值
		udMP,					//MP
		udMPVALUE,				//MP值
		udATTACK,				//攻击
		udATTACKVALUE,			//攻击值
		udSPEED,				//速度
		udSPEEDVALUE,			//速度值
		udHIT,					//命中
		udHITVALUE,				//命中值
		udSUNDER,				//破甲
		udSUNDERVALUE,			//破甲值
		udGRIT,					//暴击
		udGRITVALUE,			//暴击值
		udDODGE,				//Dodge闪避
	    udDODGEVALUE,			//闪避值
		udARMOR,				//Armor护甲
		udARMORVALUE,			//护甲值
		udTOUGHNESS,			//Toughness韧性
		udTOUGHNESSVALUE,		//韧性值
		udLINELEFT,				//分割线（左侧）
		udEQUIPTABBTN,			//装备TAB按钮
		udSOULTABBTN,			//战魂TAB按钮
		udEQUIPTABBTNLABEL,		//装备LABEL
		udSOULTABBTNLABEL,		//战魂LABEL
		udBOARD_1,				//武器BOARD
		udBOARD_2,				//衣服BOARD
		udBOARD_3,				//戒指BOARD
		udBOARD_4,				//鞋子BOARD
		udBOARD_5,				//圣物BOARD
		udBOARD_6,				//法球BOARD
		udBOARD_7,				//头盔BOARD
		udBOARD_8,				//饰品BOARD
		udLINERIGHT_1,			//分割线（右一）
		udLINERIGHT_2,			//分割线（右二）
		udSTR,					//力量
		udSTRVALUE,				//力量值
		udAGI,					//敏捷
		udAGIVALUE,				//敏捷值
		udINT,					//智力
		udINTVALUE,				//智力值
		udSKILL_1,				//技能1
		udSKILL_2,				//技能2
		udSKILL_3,				//技能3
		udSKILL_4,				//技能4
		udSKILL_5,				//技能5
		udSKILL_6,				//技能6
		udSKILL_7,				//技能7
		udSKILL_8,				//技能8
		udADDFRIENDBTN,			//加好友按钮
		udADDFRIENDLABEL,		//加好友LABEL
		udSOUL_1,				//英魂1
		udSOUL_2,				//英魂2
		udSOUL_3,				//英魂3
		udSOUL_4,				//英魂4
		udHERONAME,				//英雄名
		udSKILL_KUANG_1,		//技能1外框
		udSKILL_KUANG_2,		//技能2外框
		udSKILL_KUANG_3,		//技能3外框
		udSKILL_KUANG_4,		//技能4外框
		udSKILL_KUANG_5,		//技能5外框
		udSKILL_KUANG_6,		//技能6外框
		udSKILL_KUANG_7,		//技能7外框
		udSKILL_KUANG_8,		//技能8外框
		udSTAR_DATA,			//星级数据


	};
	enum{
		_kTAB1_,
		_kTAB2_
	};
	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pNode;
;public:
	PlayerTipsWindow();
	virtual ~PlayerTipsWindow();
	void On_Close(cocos2d::CCObject* pSender);
	void On_AddFriend(cocos2d::CCObject* pSender);

private:
	/*
		_initLayout
	*/
	inline void _initLayout();
	/*
		_initData. 设置标签页，按钮等
	*/
	inline void _initData();
	/*
		_setMask, 设置遮罩层
	*/
	inline void _setMask();
	/*
		_createSkeleton，设置英雄骨骼动画 
	*/
	inline void _createSkeleton();
	/*
		_setInfo，设置具体信息
	*/	
	inline void _setInfo();
	/*
		_setEquipInfo，设置装备信息
	*/
	inline void _setEquipInfo();
	/*
		_setSkillInfo，设置技能信息
	*/
	inline void _setSkillInfo();
	/*
		_setSoulInfo，设置战魂信息
	*/
	inline void _setSoulInfo();
	/*
		_setStarts，设置星数
	*/
	inline void _setStars();

	inline void _setTTFText(int key, const char * text);
	inline void _setTTFText(int key, int text);

	/*
		选择标签页CallBack
	*/
	inline void On_TabSelected(cocos2d::CCObject* pSender);

	int currentTab;	//当前标签页, kTab1, kTab2

private:
	CMenuItemSprite* m_equipTabItem;	//Equip Tab
	CMenuItemSprite* m_soulTabItem;		//Soul Tab
	CCLabelTTF*	m_equipTabLabel;		//Equip Tab Label
	CCLabelTTF* m_soulTabLabel;			//Soul Tab Label
	FSData* m_selectedFont;				//Tab Selected Font
	FSData* m_unselectedFont;			//Tab Unselected Font
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

	//
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);

	void touchEvent(CPriorityLayerColor* pLayerColor);

	/*
		点击装备图标CallBack 
	*/
	virtual void CallBack_ClickEquip(int type, int equipId);
	/*
		点击战魂图标CallBack
	*/
	void OnSoulIconClick(cocos2d::CCObject* pSender);
};


#endif
