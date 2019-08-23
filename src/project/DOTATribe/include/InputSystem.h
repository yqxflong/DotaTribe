#ifndef  _DOTATRIBE_INPUTSYSTEM_H_
#define  _DOTATRIBE_INPUTSYSTEM_H_


#include <include/common/Singleton.h>
#include "InputEvent.h"
#include <cocos2d.h>
#include <list>
using  namespace  cobra_win;

class InputSystem : public cobra_win::Singleton2<InputSystem>
{
private:
	cocos2d::CCPoint      m_TouchBeginPosition; // TOUCH开始时的位置
	std::list<InputEvent> m_InputEventQueue;    // 输入事件队列

public:
	InputSystem();
	virtual ~InputSystem();

public:
	/*
		得到TOUCH初始化位置
	*/
	cocos2d::CCPoint&      GetTouchBeginPosition();
	/*
		得到输入队列
	*/
	std::list<InputEvent>& GetInputEventQueue();

public:
	/*
		插入输入的事件
	*/
	void  AddInputEvent(InputEvent event);

public:
	/*
		初始化输入控制系统管理器
	*/
	bool  Init();
	/*
		输入控制系统逻辑桢更新
	*/
	void  Tick();
	/*
		输入控制网络系统管理器
	*/
	void  Destroy();

public:
	friend  class  cobra_win::Singleton2<InputSystem>;
};

#define  INPUTSYSTEM  (InputSystem::get_instance2())


#endif
