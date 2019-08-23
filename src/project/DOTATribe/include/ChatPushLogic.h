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
		��ʼ������������Ϣ����ϵͳ������
	*/
	bool  Init();
	/*
		����������Ϣ����ϵͳ����
	*/
	void  Tick();
	/*
		������Ϣ����ͷϵͳ����
	*/
	void  Destroy();

public:
	/*
		��ʼ������Ϣ
	*/
	void StartPushMsg(bool isFirstLogin);

public:
	friend  class  cobra_win::Singleton2<ChatPushLogic>;
};

#define  CHATPUSHLOGIC  (ChatPushLogic::get_instance2())


#endif
