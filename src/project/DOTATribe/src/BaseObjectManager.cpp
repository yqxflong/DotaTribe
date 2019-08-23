////////////////////////////////////////////////////////////////
//Name:	 BaseObjectManager
//Auchor: 	xiaobo.wu
//Func:	 战斗逻辑对象管理器
//Maintainer: 	xiaobo.wu
//date:   2014/01/02
////////////////////////////////////////////////////////////////
#include  <cocos2d.h>
#include "../include/LoggerSystem.h"
#include  "../include/BaseObjectManager.h"
#include  "../include/AthleticsSceneManager.h"


template<> BaseObjectManager* cobra_win::Singleton2<BaseObjectManager>::m_pMySelf = NULL;

BaseObjectManager::BaseObjectManager()
{
   m_ObjectList.clear(); 
}

BaseObjectManager::~BaseObjectManager()
{
	m_pMySelf=NULL;
}

bool  BaseObjectManager::Init()
{
   m_ObjectList.clear();
   CCLOG("BaseObjectManager Init Success!");
   return true;
}

void BaseObjectManager::Tick()
{
	std::list<BaseObject *>::iterator beginIter=m_ObjectList.begin();
	while(beginIter!=m_ObjectList.end())
	{
		if((*beginIter)->IsValid())
		{
			(*beginIter)->Tick();
		}
		else
		{
			//销毁
			beginIter=DeleteObject(*beginIter);
		}
		if(beginIter==m_ObjectList.end())
		{
			return ;
		}
		beginIter++;
	}
}

void  BaseObjectManager::Destroy()
{ 
	std::list<BaseObject *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		(*baseIter)->Destroy();
		delete (*baseIter);
		baseIter++;
	}
	m_ObjectList.clear(); 
}

bool  BaseObjectManager::PushCommand(int eventType,std::string attachParam)
{
	std::list<BaseObject *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		if((*baseIter)->IsValid())
		{
			 (*baseIter)->OnCommandHanlder(eventType,attachParam);
		}
		baseIter++;
	}
	return true;
}

void  BaseObjectManager::SetSpeedScale(float speedScale)
{
	std::list<BaseObject *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		if((*baseIter)->IsValid())
		{
			(*baseIter)->SetSpeedScale(speedScale);
		}
		baseIter++;
	}
}


int   BaseObjectManager::GetObjectCount()
{
    return m_ObjectList.size();
}



std::list<BaseObject*>& BaseObjectManager::GetObjectList()
{
    return  m_ObjectList;
}


void  BaseObjectManager::RemoveAlBaseObject()
{
	std::list<BaseObject *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		(*baseIter)->Destroy();
		delete (*baseIter);
		baseIter++;
	}
	m_ObjectList.clear();
}

void  BaseObjectManager::InsertObject(BaseObject* pObject)
{
   if(pObject!=NULL)
   {
	    m_ObjectList.push_back(pObject);
   }
}


void  BaseObjectManager::PurgeAllChildren()
{

	 std::list<BaseObject *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		if((*baseIter)!=NULL)
		{
			(*baseIter)->SetIsValid(false);
		}
		baseIter++;
	}  
}


std::list<BaseObject *>::iterator    BaseObjectManager::DeleteObject(BaseObject* pObject)
{
	std::list<BaseObject *>::iterator  objectIter=m_ObjectList.begin();
	while(objectIter!=m_ObjectList.end())
	{
        if((*objectIter)==pObject)
		{
            (*objectIter)->Destroy();
			delete (*objectIter);
			objectIter=m_ObjectList.erase(objectIter);
			CCLOG("success Delete Object!");
			return objectIter;
		}
        objectIter++;
	}
	return  m_ObjectList.end();
}

 
 
