//Name：HomeProcedure
//Function：主场景流程
//Written By：尹强

#ifndef  _DOTATRIBE_HOMEPROCEDURE_H_
#define  _DOTATRIBE_HOMEPROCEDURE_H_

#include "IProcedure.h"

class HomeProcedure : public IProcedure
{
private:
	int m_showWindow;
	bool m_bIsFristTime;
	int m_nSubViewType;
public:
	HomeProcedure();
	virtual ~HomeProcedure();
public:
	/*
		是否可以进入指定场景
	*/
	bool  IsCanEnterScene(int sceneId);
	/*
		切换流程
	*/
	void  ChangeProcedureTo(IProcedure* procedure);

	/*
		切换流程至组队副本
	*/
	void ChangeProcedureToTeamBattle();

	/*
		设置切换流程时跳转向的页面
	*/
	void SetShowWindow(int iWindowEventId);

	/*
	   设置子窗口类型
	*/
	void SetSubViewType(int nSubViewType);

public:
	/*
		初始化流程
	*/
	virtual      bool     Init();
	/*
		逻辑桢处理
	*/
	virtual      void     Tick();
	/*
		销毁流程
	*/
	virtual      void     Destroy();

protected:
	/*
		系统输入消息响应处理
	*/
	virtual      void     OnInputEventHandler();
	/*
		系统进入后台事件响应处理
	*/
	virtual      void     OnSystemEnterBackEventHandler();
	/*
		系统进入前台事件响应处理
	*/
	virtual      void     OnSystemEnterFrontEventHandler();
	/* 
		系统暂停事件响应处理
	*/
	virtual      void     OnSystemPauseEventHandler();
	/*
		系统恢复事件响应处理
	*/
	virtual      void     OnSystemResumeEventHandler();

public:
	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};


#endif
