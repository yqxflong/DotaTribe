//Name：DTTimedGrayWindow
//Function：倒计时隔绝层
//Written By：尹强
//PS: 唯一消失途径为倒计时结束

#ifndef  _DOTATRIBE_DTTimedGrayWindow_H_
#define  _DOTATRIBE_DTTimedGrayWindow_H_

#include "IWindow.h"

class DTTimedGrayWindow : public IWindow
{
private:
	float m_fTick;
public:
	DTTimedGrayWindow();
	virtual ~DTTimedGrayWindow(){};

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
};


#endif
