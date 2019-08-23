// Name :		CreateRoleProcedure.h
// Function:	角色创建流程
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _DOTATRIBE_CREATEROLEPROCEDURE_H_
#define  _DOTATRIBE_CREATEROLEPROCEDURE_H_


#include "IProcedure.h"

class  CreateRoleProcedure: public IProcedure
{
public:
	CreateRoleProcedure();
	virtual ~CreateRoleProcedure();

public:
	/*
		切换到登陆流程
	*/
	void ChangeProcedureTo(IProcedure* procedure);

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
