#ifndef  _DOTATRIBE_IPROCEDURE_H_
#define  _DOTATRIBE_IPROCEDURE_H_
#include <cocos2d.h>

class IProcedure: public cocos2d::CCNode 
{
public:
	enum
	{
		_TYPED_UNKOWN_PROCEDURE_,				// 未知类型
		_TYPED_LOGO_PROCEDURE_,					// LOGO显示流程(Android专用)
		_TYPED_LOADING_PROCEDURE_,				// Loading流程
		_TYPED_LOGIN_PROCEDURE_,				// 登陆流程
		_TYPED_CREATEROLEPROCEDURE_PROCEDURE_,	// 创建角色流程
		_TYPED_HOME_PROCEDURE_,					// 主场景流程
		_TYPED_SELECTMISSION_PROCEDURE_,		// 选择世界地图
		_TYPED_ATHLETICS_PROCEDURE_,			// 战斗流程
		_TYPED_ARENA_PROCEDURE_,				// 竞技场流程
		_TYPED_CLIMB_TOWER_,					// 爬塔流程（占位）
		_TYPED_TEAMBATTLE_PROCEDURE_,			//组队副本流程
		_TYPED_TRANSFORM_PROCEDURE_,			// 转换用
		_TYPED_PROCEDURE_NUMBER_,				// Procedure总数
	};

protected:
	int  m_Type;// 当前流程标示

public:
	IProcedure();
	virtual ~IProcedure();

public:
	/*
		得到当前流程标示
	*/
	int  GetType();

public:
	/*
		初始化流程
	*/
	virtual      bool     Init()	   =	0;
	/*
		逻辑桢处理
	*/
	virtual      void     Tick()       =    0;
	/*
		销毁流程
	*/
	virtual      void     Destroy()	   =	0;
		/*
		播放背景音乐
	*/
	virtual		 void	  PlayBGSound();
	/*
		关闭所有音乐
	*/
	virtual		 void	  StopAllSound();

public:
	/*
		系统输入消息响应处理
	*/
	virtual      void     OnInputEventHandler()    =    0;

public:
	/*
		系统进入后台事件响应处理
	*/
	virtual      void     OnSystemEnterBackEventHandler()      =     0;
	/*
		系统进入前台事件响应处理
	*/
	virtual      void     OnSystemEnterFrontEventHandler()     =     0;
	/* 
		系统暂停事件响应处理
	*/
	virtual      void     OnSystemPauseEventHandler()          =     0;
	/*
		系统恢复事件响应处理
	*/
	virtual      void     OnSystemResumeEventHandler()         =     0;
};


#endif
