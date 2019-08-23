// Name :		LoadingWindow.h
// Function:	Loading窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_LOADINGWINDOW_H_
#define  _DOTATRIBE_LOADINGWINDOW_H_


#include "IWindow.h"

class LoadingWindow : public IWindow
{
private:
	int m_SubType; // 附加子类型
public:
	enum
	{
		_RESTART_ATHLETICS_PROCEDURE_=10000,  //重新启动战斗流程事件枚举
		_RESTART_MISSION_PROCEDURE_=10001,	  //重新启动选择关卡流程事件
	};
	LoadingWindow();
	virtual ~LoadingWindow();
	void InitLayer();
	void randomMaxCount();
	int m_NextProcedure;
	int m_count;
	int m_maxCount;
	CCSkeletonAnimation* pSkeleton;
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


	void OnEvent(cocos2d::CCObject* obj);

	void SkipToNextProcedure();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示登陆面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新面板所有空间名称事件处理
	*/
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);
	/*
		更新加载进度条进度事件处理
	*/
	void   OnUpdateLoadingBarEventHandler(std::list<std::string>& paramList);
	/*
		更新加载进度提示文字事件处理
	*/
	void   OnUpdateLoadingTextEventHandler(std::list<std::string>& paramList);
};


#endif
