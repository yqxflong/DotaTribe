#ifndef  _DOTATRIBE_LOGOPROCEDURE_H_
#define  _DOTATRIBE_LOGOPROCEDURE_H_


#include "IProcedure.h"

class LogoProcedure : public IProcedure
{
public:
	LogoProcedure();
	virtual ~LogoProcedure();

public:
	/*
		跳转到下一个流程
	*/
	void  ChangeToNextProcedure();

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
};


#endif
