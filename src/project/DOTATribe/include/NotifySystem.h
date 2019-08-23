#ifndef  _DOTATRIBE_NOTIFYSYSTEM_H_
#define  _DOTATRIBE_NOTIFYSYSTEM_H_


#include <include/common/Singleton.h>
using  namespace  cobra_win;

class NotifySystem : public cobra_win::Singleton2<NotifySystem>
{
public:
	enum
	{
		_TYPED_NOTIFY_UNKOWN_, // 未知类型的提醒
		_TYPED_NOTIFY_DAILY_,  // 每日定时提醒
		_TYPED_NOTIFY_TIME_,   // 定时提醒
		_TYPED_NOTIFY_FULLTL_,	//满体力提醒
	};

public:
	NotifySystem();
	virtual ~NotifySystem();

public:
	//@系统进入后台事件响应处理
	void  OnSystemEnterBackEventHandler();
	//@系统进入前台事件响应处理
	void  OnSystemEnterFrontEventHandler();

public:
	//@标配
	bool  Init();
	void  Tick();
	void  Destroy();

private:
	//@清空所有消息
	void  ClearAllNotification();
	//@重新注册所有的通知事件
	void  RegisterAllNotification();
};

#define  NOTIFYSYSTEM  (NotifySystem::get_instance2())


#endif
