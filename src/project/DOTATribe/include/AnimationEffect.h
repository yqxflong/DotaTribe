#ifndef   _DOTATRIBE_COMPMENT_ANIMATIONEFFECT_H_
#define   _DOTATRIBE_COMPMENT_ANIMATIONEFFECT_H_
 
//////////////////////////////////////////////////////////////////////////
//Name: AnimationEffect
//Auchor: xiaobo.wu
//Func: 帧动画特效(支持变速播放)
//Maintainer: xiaobo.wu
//date:   2013/08/07
//////////////////////////////////////////////////////////////////////////

#include <cocos2d.h>

using namespace  cocos2d;

 
  
#define   _Animation_Effect_Finish_Event_      0x10000				//动画播放完毕回调事件类型
#define   _Animation_Timer_Triger_Event_	   0x10001				//定时任务回调事件类型
#define   _Animation_Timer_Triger_Event_02_	   0x10002				//定时任务2回调事件类型



 
enum
{
	_ANIMATION_DEFULAT_UNVALID_VALUE_=-1,		//默认非法值
};


/*
动画特效回调子类型
*/
typedef struct callback_node_tag
{
	bool   isTrigger;
	int    attachParam;
	int    eventType;
	float  callBackTime;
public:
	callback_node_tag()
	{
		callBackTime=0.0f;
		eventType=_ANIMATION_DEFULAT_UNVALID_VALUE_;
		isTrigger=false;
		attachParam=_ANIMATION_DEFULAT_UNVALID_VALUE_;
	}
}CallBack_Node,*PCallBack_Node;


/*
动画特效回调 协议
param1: 事件类型
param2:	动画宿主结点
param3: 定时回调数据
*/ 
class  AnimationEffectCallBackProtocol
{
public:
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)=0;
};

/*
动画特效 回调结点Vector
*/
typedef  struct  animation_call_node_tag
{
	std::vector<PCallBack_Node> callBackVec;
public: 
	animation_call_node_tag()
	{
		callBackVec.clear();
	}
	~animation_call_node_tag()
	{
		size_t callBackCount=callBackVec.size();
		for(size_t index=0;index<callBackCount;index++)
		{
			delete  callBackVec.at(index);
		}
		callBackVec.clear();
	}
}Animation_CALL_Node,*PAnimation_Call_Node;
  

 /*
  回调特效动画
 */
class    CCAnimationEffect : public cocos2d::CCAnimate
{
public:
	CCAnimationEffect();
	virtual ~CCAnimationEffect();
   bool	    initWithAnimation(cocos2d::CCNode * panimationNode,CCAnimation * pAnimation,AnimationEffectCallBackProtocol * animationEffectDelegate=NULL,PAnimation_Call_Node  pAnimationCall=NULL);
   void     setAnimationEffectCallDelegate(AnimationEffectCallBackProtocol * animationEffectDelegate);   
   virtual  void  startWithTarget(CCNode *pTarget);
   virtual  void  stop();
   virtual  void  update(float t);
   virtual  bool  isDone(void);
   virtual  void  step(float dt);
   virtual  CCActionInterval * reverse();
   virtual  void  setSpeedScale(float speedScaleValue);
   virtual  void  setAnimationNode(cocos2d::CCNode * pAnimationNode);
   virtual  cocos2d::CCNode * getAnimationNode();
   void  setUnLoopAutoRemove(bool bAutoRemoveEnable);
   bool	 getUnLoopAutoRemove();
public:
	static CCAnimationEffect *  create(cocos2d::CCNode * panimationNode,CCAnimation *pAnimation,AnimationEffectCallBackProtocol * animationEffectDelegate=NULL,PAnimation_Call_Node  pAnimationCall=NULL);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, m_pAnimation, Animation)

protected:
	virtual  void  checkCallBackVec(float time);
protected:
	/*
	 单轮播放时间
	*/
	float m_fSingleDuration; 
	/*
	  每帧动画播放时间点
	*/
	std::vector<float>*  m_pSplitTimes;			
	/*
	 当前帧动画索引
	*/
	int                  m_nNextFrame;
    /* 
     起始帧纹理
    */
	CCSpriteFrame*       m_pOrigFrame;
	/*
	 当前动画的循环次数
	*/
	unsigned int         m_uExecutedLoops;

	/*
	 回调事件队列
	*/
	PAnimation_Call_Node  m_pAnimation_Call_Node;

	/*
	注册动画回调事件代理
	*/
	AnimationEffectCallBackProtocol * m_pDelegate;				//宿主指针

	/*
     速度系数
	*/
	float   m_fSpeedScale;	

	/*
	是否完成
	*/
	bool    m_bIsFinishCall;

	/*
	动画结点 用于回调传递
	*/
	cocos2d::CCNode *  m_pAnimationNode;

	/*
	是否播放完毕自动删除
	*/
	bool   m_bAutoRemove;
};
 


#endif
