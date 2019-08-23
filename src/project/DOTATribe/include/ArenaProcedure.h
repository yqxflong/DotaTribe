#ifndef  _DOTATRIBE_ARENAPROCEDURE_H_
#define  _DOTATRIBE_ARENAPROCEDURE_H_

#include "../include/IProcedure.h"
#include <string>
 
class  ArenaProcedure: public IProcedure
{ 
protected:
	int  m_SubType;       // 当前所属子流程
	bool m_bInputEnabled; // 是否处于可输入状态

protected:
	long long m_LogicTickCounter; // 计时器
public:
	ArenaProcedure();
	virtual ~ArenaProcedure();
public:
	/*
		得到当前子流程
	*/
	int   GetSubType();

public:

	void OnChangeProcedureToHome(); 

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


