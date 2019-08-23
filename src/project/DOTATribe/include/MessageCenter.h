#ifndef _MVP_MessageCenter_H_
#define _MVP_MessageCenter_H_

#include "../include/Message.h"
#include <vector>
#include <map>
#include <list>
#include <include/common/Singleton.h>

class MessageCenter : public cobra_win::Singleton2<MessageCenter>
{
private:
	std::map<int, Handler *> m_mapHandlers;

	std::list<Message> m_listMessage; 

public:
	MessageCenter();

	~MessageCenter();

	bool Init();

	void Tick();

	void Destroy();

public:
	bool RegisterHandler(Handler * handler);

	void InsertMessage(Message message);

	void Notify(Handler * host);

};

#endif
