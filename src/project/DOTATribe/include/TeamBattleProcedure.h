//Name:TeamBattleProcedure
//Function:组队副本流程
//Author:fangjun
//Date:20130918

#ifndef  _DOTATRIBE_TEAMBATTLEPROCEDURE_H_
#define  _DOTATRIBE_TEAMBATTLEPROCEDURE_H_

#include "IProcedure.h"

class  TeamBattleProcedure: public IProcedure
{
public:
	enum{
		_TEAMBATTLE_STATE_UNKNOW_,		//未知状态
		_TEAMBATTLE_STATE_SELECTGATE_,	//选择组队副本的关卡
		_TEAMBATTLE_STATE_WAITTEAMER_,	//组队
		_TEAMBATTLE_STATE_STARTFIFHT_,	//开始战斗

	};

private:
	int m_nowState;			//当前所在状态
	int m_backWindow;		//关闭回退页面


public:
	TeamBattleProcedure();
	virtual ~TeamBattleProcedure();

public:
	virtual      bool     Init();

	virtual      void     Tick();

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

public:
	/*
		设置回退页面
	*/
	void SetBackWindow(int backwindowId);

	/*
		获得指定状态的数据
	*/
	void GetProvideStateData(int stateEnumId);

	/*
		转换当前状态至
	*/
	void ChangeNowState(int stateEnumId);

	/*
		获得当前流程中子状态
	*/
	int GetNowState();

	/*
		跳转流程至Home
	*/
	void ChangeProcedureToHomeWithLoading();

	/*
		跳转流程至竞技场
	*/
	void ChangeProcedureToAthletic();

	/*
		disconnect with TeamBattleProcedure
	*/
	void DisconnectNetworkHandler();

	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};

#endif
