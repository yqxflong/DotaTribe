//Name：CallFuncAction
//Function：自定义事件回调动画
//Author:	Johny

#ifndef   _DOTATRIBE_CALLFUNCACTION_H_ 
#define   _DOTATRIBE_CALLFUNCACTION_H_

#include  <cocos2d.h>

using namespace cocos2d;
 
class   CallFunctionProtocol
{
public:
	virtual void  CallFunctionHandler(int eventType,void * attachParam)=0;
};

class  CallFuncAction : public CCActionInstant //<NSCopying>
{
public:
    CallFuncAction()
    {
	   m_pCallFuncDelegate=NULL;
	   m_pattachParam=NULL;
	   m_nEventType=-1;
    }
    virtual ~CallFuncAction();
	 
    static CallFuncAction * create(int eventType,CallFunctionProtocol * pCallFuncDelegate,void * attachParam=NULL);
	   
    virtual bool initWithTarget(int eventType,CallFunctionProtocol* pCallFuncDelegate,void * attachParam=NULL);
 
    virtual void execute();

	virtual void  stop(void);
 
	virtual void update(float time); 

    inline CallFunctionProtocol* getCallFuncDelegate()
    {
         return m_pCallFuncDelegate;
    }

    inline void setCallFuncDelegate(CallFunctionProtocol* pCallFuncDelegate)
    {
       m_pCallFuncDelegate=pCallFuncDelegate;
    }
     
protected: 
    CallFunctionProtocol  *  m_pCallFuncDelegate;
	void * m_pattachParam;
	int m_nEventType;
	bool m_bIsFinish;
};
 
#endif