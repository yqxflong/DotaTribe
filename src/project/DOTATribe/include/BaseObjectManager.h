//Name��BaseObject
//Function��ս���߼����������
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
	//@����
	bool  Init();
	void  Tick();
	void  Destroy();
	  
	//@�㲥�ַ���Ϣ
    bool  PushCommand(int eventType,std::string attachParam);

	//@��ö����������Ŀ
	int   GetObjectCount();

	//@��ȡ�����������
    std::list<BaseObject*>& GetObjectList();

	//@�޸Ķ�����б��ٲ���
	void  SetSpeedScale(float speedScale);

	//@ǿ���Ƴ��ڲ����������ӽڵ�
	void  RemoveAlBaseObject();

	//@�����ӽڵ�
	void  InsertObject(BaseObject* pObject);
 
	//@ɾ���ӽڵ㣬����ָ���¸��ӽڵ������
	std::list<BaseObject *>::iterator  DeleteObject(BaseObject* pObject);

	//@�رն�������Ӷ���ʹ��״̬
	void  PurgeAllChildren();
	 
public:
	friend  class  cobra_win::Singleton2<BaseObjectManager>;
};

#define  BASEOBJECTMANAGER  (BaseObjectManager::get_instance2())
 

#endif