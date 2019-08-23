//Name：RoleStatusWindow
//Function：人物状态层
//Written By：尹强

#ifndef  _DOTATRIBE_RoleStatusWindow_H_
#define  _DOTATRIBE_RoleStatusWindow_H_

#include "IWindow.h"
#include "../include/DTRoleStatusBar.h"

class RoleStatusWindow : public IWindow
	,public DTRoleStatusBarDelegate
{
public:
	int Current_WindowType_;
private:
	enum{
		kROLESTATUSBAR,	//人物状态条占位节点
		kMainTask,		//主线任务
		kMAINTASKEFFECT,	//主线任务特效
		kSkeletonAniamtion, //任务骨骼
		kNewTaskNode,		//新任务提示
		kNewHeroNode,		//新英雄提示
//=======================
		kREAL_ROLESTATUSBAR,	//人物状态条
	};
	DTRoleStatusBar* m_pRoleStatusBar;
	int m_nShowCounter;	//显示计数器
public:
	RoleStatusWindow();
	virtual ~RoleStatusWindow(){};

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

	/*
		刷新界面
	*/
	void RefreshUI();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		接收刷新UI事件
	*/
	static void Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	/*
		DTRoleStatusBar CallBack
	*/
	virtual void AvatarClickEvent();
	virtual void SkillClickEvent();
	virtual void AddTLClickEvent();
	/*
		MainTask CallBack
	*/
	void MainTaskClickEvent(cocos2d::CCObject* pSender);
	void UpdateMainTaskHint();
	void UpdateRoleState();
protected:
	/*
		显示Top面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void _registerEvent();
	inline void _unregisterEvent();
	inline void _initLayout();
	inline void _mapRoleStatus();
	inline void _mapMainTask();
};


#endif
