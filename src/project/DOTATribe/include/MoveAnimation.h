#ifndef  _DOTATRIBE_MOVEANIMATION_H_
#define  _DOTATRIBE_MOVEANIMATION_H_
#include   <cocos2d.h>

////////////////////////////////////////////////////////////////
//Name:	 MoveAnimation
//Auchor: 	xiaobo.wu
//Func:	 移动动画
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
using namespace cocos2d;

#define  MAXCALLBACKEVENTNUM    3
#define  _Move_Animation_Finish_Event_    4

 
class MoveAnimationCallBackProtocol
{
public:
	virtual  void   CallBackEventProtocol(int eventType,void * ptrParam)=0;
};

 
typedef  struct  callbacknode_tag
{
    bool  isTrigger;
	char  attachParam;
	float triggerTime;
	int   eventType;
public:
	callbacknode_tag()
	{
		isTrigger=false;
		attachParam=0;
		triggerTime=0.0f;
		eventType=-1;
	}
}CallBackNode,*PCallBackNode;

 
typedef struct  callbackvec_tag
{
     MoveAnimationCallBackProtocol  * pDelegate;
	 std::vector<PCallBackNode>    callBackEventVec;
public:
	callbackvec_tag()
	{
        pDelegate=NULL;
		callBackEventVec.clear();
	}
	~callbackvec_tag()
	{
	   pDelegate=NULL;
       size_t  eventSize=callBackEventVec.size();
	   for(size_t eventIndex=0;eventIndex<eventSize;eventIndex++)
	   {
		   delete callBackEventVec.at(eventIndex);;
	   }
	   callBackEventVec.clear();
	}
}CallBackVec,*PCallBackVec;

/*
移动动画类
*/
class   MoveAnimation :public cocos2d::CCMoveTo
{ 
public:
	bool initWithDuration(float duration, const CCPoint& position,PCallBackVec pCallBackVec);
	virtual ~MoveAnimation();
	virtual  void  destroy();																     	/*注意销毁时*/
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);
	virtual void updateAnimatioSpeedScale();
	virtual void setSpeedScale(float speedScale); 
public:
	static MoveAnimation* create(float duration, const CCPoint& position,PCallBackVec pCallBackVec=NULL);
protected:
	void    checkCallBackVec(float time);
protected:
	CCPoint m_endPosition;
	CCPoint m_startPosition;
	CCPoint m_delta;	
	float   m_duration;
	float   m_speedScale;
	bool	m_isFinish;
	PCallBackVec  m_pCallBackVec;
}; 



#endif