
#ifndef  _DOTASTIBE_MESSAGEPACKETMANAGER_H
#define  _DOTASTIBE_MESSAGEPACKETMANAGER_H


#include <include/common/Singleton.h>
#include <list>
#include <map>
#include "../include/MessagePacket.h"


using  namespace  cobra_win;

class  MessagePacketManager:public cobra_win::Singleton2<MessagePacketManager>
{
public:
	std::list<MessagePacket *> m_ObjectList;

public:
	MessagePacketManager();
	virtual ~MessagePacketManager();

public:
	MessagePacket *GetObjectById(int objectId);

	bool  PushCommand(int EventTypeID,void * ptr);

	int   GetObjectCount();

	std::list<MessagePacket*>& GetObjectList();

	void  RemoveAlBaseObject();

	void  InsertObject(MessagePacket* pObject);

	std::list<MessagePacket*>::iterator DeleteObject(MessagePacket* pObject);

	void  PurgeAllChildren();

	void  DeleteAllObject();

	bool  Init();

	void  Tick();

	void  Destroy();

	char*  ParserDataFromServer();    // 将server的数据格式统一解析到内存中
	virtual  std::string   GetName();
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

public:
	friend  class  cobra_win::Singleton2<MessagePacketManager>;
};

#define  MESSAGEPACKETMANAGER  (MessagePacketManager::get_instance2())


#endif