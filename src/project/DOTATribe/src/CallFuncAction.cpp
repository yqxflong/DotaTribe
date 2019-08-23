//Name：CallFuncAction
//Function：自定义事件回调动画
//Author:	Johny

#include "../include/CallFuncAction.h"
#include <cocos2d.h>

 
CallFuncAction * CallFuncAction::create(int eventType,CallFunctionProtocol * pCallFuncDelegate,void * attachParam/* =NULL */) 
{
	CallFuncAction *pRet = new CallFuncAction();
	if (pRet && pRet->initWithTarget(eventType,pCallFuncDelegate,attachParam)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

 
bool CallFuncAction::initWithTarget(int eventType,CallFunctionProtocol* pCallFuncDelegate,void * attachParam/* =NULL */) {
	if(pCallFuncDelegate!=NULL)
	{
		m_bIsFinish=false;
		m_pCallFuncDelegate=pCallFuncDelegate;
		m_pattachParam=attachParam;
		m_nEventType=eventType;
		return true;
	}
	return false;
}

CallFuncAction::~CallFuncAction(void)
{
	 m_pCallFuncDelegate=NULL;
	 m_pattachParam=NULL;
	 /* if(m_pattachParam!=NULL)
	 {
	 delete m_pattachParam;
	 m_pattachParam=NULL;
	 }*/
	 m_nEventType=-1;
}
 

void CallFuncAction::update(float time) {
	CC_UNUSED_PARAM(time);
	this->execute();
}

void  CallFuncAction::stop(void)
{
	m_bIsFinish=true;
}

void CallFuncAction::execute() {
	if(!m_bIsFinish)
	{
		if (m_pCallFuncDelegate) {
			m_bIsFinish=true; 
			m_pCallFuncDelegate->CallFunctionHandler(m_nEventType,m_pattachParam);
		}	 
	}
	
}