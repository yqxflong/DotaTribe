//Name：ListenProxyObject
//Function： 监听代理类，用于消息的反射，解耦两个类
//Author:	Johny

#include "../include/ListenProxyObject.h"
#include "../include/EventSystem.h"

 
ListenProxyObject::ListenProxyObject()
{
	objectType_=UNKOWN_OBJECT_TYPE;
	m_pNoticeDelegate=NULL;  
	m_cProxyType=_LISTEN_PROXY_UNKONW_TYPE_;
	m_attachEventType=_LISTEN_PROXY_UNKONW_TYPE_;
}

ListenProxyObject::~ListenProxyObject()
{ 
	Destroy();
}
void ListenProxyObject::Destroy()
{
	m_attachEventType=-1;
	m_pNoticeDelegate=NULL;  
	m_cProxyType=_LISTEN_PROXY_UNKONW_TYPE_;
}


void ListenProxyObject::OnCommandHanlder(int EventTypeID)
{
	if(m_pNoticeDelegate!=NULL)
	{ 
		m_pNoticeDelegate->OnCommandHanlder(EventTypeID,_to_event_param_(m_cProxyType),_to_event_param_(m_attachEventType));
	} 
}

void ListenProxyObject::OnCommandHanlder(int EventTypeID,std::string attachParam)
{    
	if(m_pNoticeDelegate!=NULL)
	{
		//代理类型 附加类型参数 底层附加参数
		m_pNoticeDelegate->OnCommandHanlder(EventTypeID,_to_event_param_(m_cProxyType),_to_event_param_(m_attachEventType),attachParam);
	}
}
 
void ListenProxyObject::OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2)
{
	if(m_pNoticeDelegate!=NULL)
	{ 
		m_pNoticeDelegate->OnCommandHanlder(EventTypeID,_to_event_param_(m_cProxyType),_to_event_param_(m_attachEventType),attachParam1,attachParam2);
	}
}
 
ListenProxyObject * ListenProxyObject::CreateListenProxyObject(int proxyType,BaseObject * pNoticeDelegate)
{
	 ListenProxyObject *  pListenProxyObject=new ListenProxyObject();
	 if(pListenProxyObject&&pListenProxyObject->InitListenProxyObject(proxyType,pNoticeDelegate))
	 {     
		 return pListenProxyObject;
	 } 
	 if(pListenProxyObject)
	 {
		 delete pListenProxyObject;
		 pListenProxyObject=NULL;
	 }
	 return NULL;
}

bool   ListenProxyObject::InitListenProxyObject(int proxyType,BaseObject * pNoticeDelegate)
{ 
	if(pNoticeDelegate!=NULL&&pNoticeDelegate->IsValid())
	{ 
		m_pNoticeDelegate=pNoticeDelegate;
		m_cProxyType=proxyType;
		return true;
	}
	return false;
}

void		  ListenProxyObject::RegisterNoticeDelegate(BaseObject * pNoticeDelegate)
{
	if(m_pNoticeDelegate!=pNoticeDelegate)
	{
		m_pNoticeDelegate=pNoticeDelegate;
	}
}

void          ListenProxyObject::UnRegisterNoticeDelegate()
{
	m_pNoticeDelegate=NULL;
}
 
BaseObject * ListenProxyObject::GetNoticeDelegate()
{
	return m_pNoticeDelegate;
}

void		ListenProxyObject::SetAttachEventType(int attachEventType)
{ 
	m_attachEventType=attachEventType;
}




 