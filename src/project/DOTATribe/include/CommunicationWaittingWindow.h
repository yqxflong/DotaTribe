#ifndef _DOTATRIBE_COMMUNICATIONWAITTINGWINDOW_H_
#define _DOTATRIBE_COMMUNICATIONWAITTINGWINDOW_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器通信等待窗口  公共接口
//date:   2013/09/13
///////////////////////////////////////////////// 

#include "IWindow.h"


 
class CommnunicationWattingWindow: public IWindow{
private:
	enum{
		kGRAYLAYER,
		kANISPRITE,	//转动的精灵
	};
	float m_fTimerSecond;//窗口超时时长
	bool m_bCheckTimeOut;//是否检查超时
public:
	CommnunicationWattingWindow();
	virtual ~CommnunicationWattingWindow(){};

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

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	void   OnStartTimer();	//开始计时
	void   OnStopTimer();	//结束计时

	double  waitTimeDuration;   //等待超时时间
	bool   isStartTimer;        //是否开始计时
	long long  startTimerCount; //启动时间戳
};

#endif