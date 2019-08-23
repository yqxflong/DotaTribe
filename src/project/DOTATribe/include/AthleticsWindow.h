//Name：AthleticsWindow
//Function：战斗窗口
//Author:	Johny

#ifndef  _DOTATRIBE_ATHLETICSWINDOW_H
#define  _DOTATRIBE_ATHLETICSWINDOW_H

#include  "IWindow.h"
#include  "../include/HeroicRole.h" 
#include "../include/WindowManager.h"
#include "../include/MaskNode.h"

class   AthleticsWindow:public IWindow
{
public:
	enum
	{
		ATHLETICS_UI_BG,
		ATHLETICS_UI_ICON,
		ATHLETICS_UI_NAME_BG,
		ATHLETICS_UI_ICON_NAME,
		ATHELTICS_UI_LEFT_MASK,
		ATHLETICS_UI_LEFT_ICON,
		ATHLETICS_UI_LEFT_INFO,
		ATHLETICS_UI_LEFT_LEVEL,
		ATHLETICS_UI_LEFT_NAME,
		ATHLETICS_UI_LEFT_TEAM,
		ATHLETICS_UI_LEFT_HP_BG,
		ATHLETICS_UI_LEFT_HP_VALUE,
		ATHLETICS_UI_LEFT_MP_BG,
		ATHLTEICS_UI_LEFT_MP_VALUE,
		ATHELTICS_UI_RIGHT_MASK,
		ATHLETICS_UI_RIGHT_ICON,
		ATHELTICS_UI_RIGHT_INFO,
		ATHLETICS_UI_RIGHT_LEVEL,
		ATHLETICS_UI_RIGHT_NAME,
		ATHLETICS_UI_RIGHT_TEAM,
		ATHLETICS_UI_RIGHT_HP_BG,
		ATHLETICS_UI_RIGHT_HP_VALUE,
		ATHLETICS_UI_RIGHT_MP_BG,
		ATHLTEICS_UI_RIGHT_MP_VALUE,
		ATHLETICS_UI_NPC_TALK_VIEW,
		ATHLETICS_UI_VIP_SKIP_CONFIG,
		ATHLETICS_UI_REPLAY_BTN,			 //重播
		ATHLETICS_UI_SPEED_BTN,				 //速度
		ATHLETICS_UI_EXIT_BTN,				 //退出
		ATHLETICS_UI_LEFT_INIT_CONFIG,
		ATHLETICS_UI_LEFT_TARGET_CONFIG,
		ATHELTICS_UI_RIGHT_INIT_CONFIG,
		ATHLETICS_UI_RIGHT_TARGET_CONFIG,
		ATHLETICS_UI_DISABLE_MARK,
		ATHLETICS_UI_STRETCHING_CONFIG,
		ATHLETICS_UI_STRETCHING_YCONFIG,
		ATHLETICS_UI_SKILL_HERONAME,		//英雄名称
		ATHLETICS_UI_SKILL_COMBAT_LABLE,	//战力
		ATHLETICS_UI_SKILL_COMBAT_VALUE, 
		ATHLETICS_UI_SKILL_ATTACK_LABLE,	//攻击
		ATHLETICS_UI_SKILL_ATTACK_VALUE,
		ATHLETICS_UI_SKILL_SPEED_LABLE,		//攻速
		ATHLETICS_UI_SKILL_SPEED_VALUE,
		ATHLETICS_UI_SKILL_HIT_LABLE,		//命中
		ATHLETICS_UI_SKILL_HIT_VALUE,
		ATHLETICS_UI_SKILL_DODGE_LABLE,		//闪避
		ATHLETICS_UI_SKILL_DODGE_VALUE,
		ATHLETICS_UI_SKILL_SUNDER_LABLE,	//破甲
		ATHLETICS_UI_SKILL_SUNDER_VALUE,	
		ATHLETICS_UI_SKILL_ARMOR_LABLE,		//护甲
		ATHLETICS_UI_SKILL_ARMOR_VALUE,
		ATHLETICS_UI_SKILL_CRIT_LABLE,		//暴击
		ATHLETICS_UI_SKILL_CRIT_VALUE,
		ATHLETICS_UI_SKILL_TENACITY_LABLE,	//韧性
		ATHLETICS_UI_SKILL_TENACITY_VALUE,
		ATHLETICS_UI_SKILL_INTERVAL,		//间隔
		ATHLETICS_UI_SKILL_START_OFFSET,	//起始偏移
		ATHLETICS_UI_SKILL_UP_CONFIG,		//第一栏配置
		ATHELTICS_UI_SKILL_DONW_CONFIG,		//第二栏配置
		ATHlETICS_UI_SKILL_RIGHT_OFFSET,	//右相对左偏移
	};

	  AthleticsWindow();
	  ~AthleticsWindow();
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

	void  InitUIConfig();
	void  BindBtnSelector();
	void  CommonBtnSelector(cocos2d::CCObject * pSender);

	//Redo按钮回调函数
	void    OnReplayHandler();

	//Speed按钮回调函数
	void    OnChangeSpeedHandler();

	//Exit按钮回调函数
	void    OnExitHandler();

	//获取窗口的子节点
	cocos2d::CCNode  *  GetAthleticsUINode(int UIIndex); 

	//获取窗口根结点
	cocos2d::CCNode  *  GetAthleticsRootNode(); 

	MaskNode *		GetAthleticsUIMarkNode(int UIIndex);
	  
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
  
};


//获取战斗UI结点
static  cocos2d::CCNode * Athletics_UI_Node(int uiIndex)
{
	AthleticsWindow * pAthleticsWindow=(AthleticsWindow *)WindowManager::get_instance2()->GetWindowByType(IWindow::_TYPED_WINDOW_ATHLETIC_);
	return pAthleticsWindow->GetAthleticsUINode(uiIndex);
}
static  cocos2d::CCNode * Athletics_UI_Root()
{
	AthleticsWindow * pAthleticsWindow=(AthleticsWindow *)WindowManager::get_instance2()->GetWindowByType(IWindow::_TYPED_WINDOW_ATHLETIC_);
	return pAthleticsWindow->GetAthleticsRootNode();
}

static  cocos2d::CCMenuItem * Athletics_BTN_Node(int uiIndex)
{
	cocos2d::CCMenu * menu=(cocos2d::CCMenu*)Athletics_UI_Node(uiIndex);
	cocos2d::CCMenuItem * cc=(cocos2d::CCMenuItem*)menu->getChildByTag(0);
	return cc;
}
static  MaskNode *  Athletics_Mask_Node(int uiIndex)
{
	AthleticsWindow * pAthleticsWindow=(AthleticsWindow *)WindowManager::get_instance2()->GetWindowByType(IWindow::_TYPED_WINDOW_ATHLETIC_);
	return pAthleticsWindow->GetAthleticsUIMarkNode(uiIndex);
}
 
#endif