//Name：LoginProcedure
//Function：登录流程，游戏第一个流程
//Written By：尹强

#ifndef  _DOTATRIBE_LOGINPROCEDURE_H_
#define  _DOTATRIBE_LOGINPROCEDURE_H_


#include "IProcedure.h"

class LoginProcedure : public IProcedure
{
public:
	LoginProcedure();
	virtual ~LoginProcedure();

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

	/*
		切换到对应的流程
	*/
	void  ChangeProcedureTo(IProcedure* procedure);

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
