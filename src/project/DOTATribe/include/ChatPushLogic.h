#ifndef  _DOTATRIBE_CHATPUSHLOGIC_H_
#define  _DOTATRIBE_CHATPUSHLOGIC_H_


#include <include/common/Singleton.h>
#include <cocos2d.h>
#include <list>
#include <map>
using  namespace  cobra_win;

class ChatPushLogic : public cobra_win::Singleton2<ChatPushLogic>
{

public:
	ChatPushLogic();
	virtual ~ChatPushLogic();

private:
	bool isPushing;
	std::map<int,long long> m_startTime;	
	void ResetTime();
public:
	/*
		初始化本地聊天消息推送系统管理器
	*/
	bool  Init();
	/*
		本地聊天消息推送系统更新
	*/
	void  Tick();
	/*
		聊天消息摄像头系统销毁
	*/
	void  Destroy();

public:
	/*
		开始推送消息
	*/
	void StartPushMsg(bool isFirstLogin);

public:
	friend  class  cobra_win::Singleton2<ChatPushLogic>;
};

#define  CHATPUSHLOGIC  (ChatPushLogic::get_instance2())


#endif
