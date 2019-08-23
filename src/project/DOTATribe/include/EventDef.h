#ifndef  _DOTATRIBE_EVENTDEF_H_
#define  _DOTATRIBE_EVENTDEF_H_


#include <string>
#include <list>
#include <map>

/*
	事件响应系统回调函数,仅为静态函数static
*/
typedef  void  (*pEventHandler)(int iEventType, std::string owerData, std::list<std::string>& paramList);

/*
	事件响应系统事件定义
*/
struct _EVENT_
{
public:
	int mEventID; // 事件ID
	std::multimap<pEventHandler, std::string> mEventHandlerList; // 事件对应的处理函数列表

public:
	_EVENT_()
	{
		mEventID = 0;
		mEventHandlerList.clear();
	}
};


#endif
