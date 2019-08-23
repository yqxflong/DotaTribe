//Name：BaseObject
//Function：战斗逻辑对象管理器
//Author:	Johny

#ifndef  _DOTASTIBE_BASEOBJECTMANAGER_H
#define  _DOTASTIBE_BASEOBJECTMANAGER_H

#include <include/common/Singleton.h>
#include <list>
#include <string>
#include "../include/BaseObject.h"
 
using  namespace  cobra_win;

class  BaseObjectManager:public cobra_win::Singleton2<BaseObjectManager>
{
protected:
	std::list<BaseObject *> m_ObjectList;
public:
	BaseObjectManager();
	virtual ~BaseObjectManager();
public:	
	//@标配
	bool  Init();
	void  Tick();
	void  Destroy();
	  
	//@广播分发消息
    bool  PushCommand(int eventType,std::string attachParam);

	//@获得对象管理器数目
	int   GetObjectCount();

	//@获取对象队列引用
    std::list<BaseObject*>& GetObjectList();

	//@修改对象队列变速参数
	void  SetSpeedScale(float speedScale);

	//@强制移除内部对了所有子节点
	void  RemoveAlBaseObject();

	//@插入子节点
	void  InsertObject(BaseObject* pObject);
 
	//@删除子节点，返回指向下个子节点迭代器
	std::list<BaseObject *>::iterator  DeleteObject(BaseObject* pObject);

	//@关闭对象队列子对象使能状态
	void  PurgeAllChildren();
	 
public:
	friend  class  cobra_win::Singleton2<BaseObjectManager>;
};

#define  BASEOBJECTMANAGER  (BaseObjectManager::get_instance2())
 

#endif