#ifndef  _DOTATRIBE_EVENTSYSTEM_H_
#define  _DOTATRIBE_EVENTSYSTEM_H_


#include <include/common/Singleton.h>
#include "EventDef.h"
#include <string>
using  namespace  cobra_win;

extern  std::string  _to_event_param_(bool);
extern  std::string  _to_event_param_(char);
extern  std::string  _to_event_param_(unsigned char);
extern  std::string  _to_event_param_(short);
extern  std::string  _to_event_param_(unsigned short);
extern  std::string  _to_event_param_(int);
extern  std::string  _to_event_param_(unsigned int);
extern  std::string  _to_event_param_(float);
extern  std::string  _to_event_param_(double);
extern  std::string  _to_event_param_(char*);
extern  std::string  _to_event_param_(const char*);
extern  std::string  _to_event_param_(long long);

class EventSystem : public cobra_win::Singleton2<EventSystem>
{
public:
	struct _DELAY_EVENT_INFO_
	{
		int mEventId;
		std::list<std::string> mEventParamList;

		_DELAY_EVENT_INFO_()
		{
			mEventId = 0;
		}
	};

private:
	std::map<int, _EVENT_> m_EventHandlerList; // 注册的事件响应处理列表

private:
	std::list<_DELAY_EVENT_INFO_> m_EventListQueue; // 当前输入的事件队列

public:
	EventSystem();
	virtual ~EventSystem();

public:
	/*
		注册事件
	*/
	void   RegisterEventHandler(int iEventType, pEventHandler pMyEventHandler);
	/*
		注册事件
	*/
	void   RegisterEventHandler(int iEventType, pEventHandler pMyEventHandler, std::string owerData);
	/*
		取消注册
	*/
	void   UnRegisterEventHandler(int iEventType, pEventHandler pMyEventHandler);

public:
	/*
		插入事件
	*/
	void   PushEvent(int iEventType);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8);
	/*
		插入事件
	*/
	void   PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9);

public:
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8);
	/*
		插入事件
	*/
	void   PushEvent2(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9);

public:
	/*
		初始化事件响应处理系统
	*/
	bool   Init();
	/*
		事件响应处理系统桢更新
	*/
	void   Tick();
	/*
		销毁事件响应处理系统
	*/
	void   Destroy();

public:
	friend  class  cobra_win::Singleton2<EventSystem>;
};

#define  EVENTSYSTEM  (EventSystem::get_instance2())


#endif
