// Name :		SelectMissionProcedure.h
// Function:	关卡选择流程
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_SELECTMISSIONPROCEDUER_H_
#define  _DOTATRIBE_SELECTMISSIONPROCEDUER_H_


#include "IProcedure.h"

class  SelectMissionProcedure: public IProcedure
{
public:
	SelectMissionProcedure();
	virtual ~SelectMissionProcedure();

	int m_showWindow;
	int m_skipWindow;
	int m_skipTabNum;
public:
	/*
		切换世界地图
	*/
	void ChangeProcedureTo(IProcedure* procedure);

	/*
		切换到关卡选择
	*/
	void ChangeToSelectSonMissionProcedure();

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

public:
	/*
		系统输入消息响应处理
	*/
	virtual      void     OnInputEventHandler();

public:
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

	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};

#endif
