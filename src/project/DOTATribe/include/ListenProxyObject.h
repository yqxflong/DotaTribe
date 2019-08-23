//Name：ListenProxyObject
//Function： 监听代理类，用于消息的反射，解耦两个类
//Author:	Johny

#ifndef  _DOTATRIBE_LISTEN_PROXY_OBJ_H
#define  _DOTATRIBE_LISTEN_PROXY_OBJ_H

#include "../include/BaseObject.h"
 
class    ListenProxyObject: public BaseObject
{    
public:
	enum
	{
		_LISTEN_PROXY_UNKONW_TYPE_=-1,  //未知代理类型
	};
	ListenProxyObject();
	virtual ~ListenProxyObject();
	virtual  void Destroy();
	virtual  void OnCommandHanlder(int EventTypeID);
	virtual  void OnCommandHanlder(int EventTypeID,std::string attachParam);
	virtual  void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2);
	static ListenProxyObject * CreateListenProxyObject(int proxyType,BaseObject * pNoticeDelegate);
public:
	void		  RegisterNoticeDelegate(BaseObject * pNoticeDelegate);
	void          UnRegisterNoticeDelegate();
	BaseObject *  GetNoticeDelegate();
	void		  SetAttachEventType(int attachEventType);
protected:
	bool		  InitListenProxyObject(int proxyType,BaseObject * pNoticeDelegate);
private:
	BaseObject	*  m_pNoticeDelegate;  
	int			   m_cProxyType;
	int			   m_attachEventType;
};
#endif