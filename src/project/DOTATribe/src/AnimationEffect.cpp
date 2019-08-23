//////////////////////////////////////////////////////////////////////////
//Name: AnimationEffect
//Auchor: xiaobo.wu
//Func: 帧动画特效(支持变速播放)
//Maintainer: xiaobo.wu
//date:   2013/08/07
//////////////////////////////////////////////////////////////////////////
#include    <cocos2d.h>
#include    "../include/AnimationEffect.h"

 /*
  回调特效动画
 */
USING_NS_CC;

#define    SingleEffectTime  1.0f


CCAnimationEffect::CCAnimationEffect()
{
	 m_pSplitTimes=new std::vector<float>;
	 m_pAnimation=NULL;
	 m_nNextFrame=0;
	 m_pOrigFrame=NULL;
	 m_uExecutedLoops=0;
	 m_pDelegate=NULL;
	 m_pAnimation_Call_Node=NULL;
	 m_fSpeedScale=1.0f;
	 m_fSingleDuration=0.0f;
	 m_bIsFinishCall=false;
	 m_bAutoRemove=false;
}

CCAnimationEffect::~CCAnimationEffect()
{
	if(m_pAnimation_Call_Node)
	{
		delete m_pAnimation_Call_Node;
		m_pAnimation_Call_Node=NULL;
	}
	CC_SAFE_RELEASE(m_pAnimation);
	CC_SAFE_RELEASE(m_pOrigFrame);	
	CC_SAFE_DELETE(m_pSplitTimes);

}

bool  CCAnimationEffect::initWithAnimation(cocos2d::CCNode * panimationNode,CCAnimation * pAnimation,AnimationEffectCallBackProtocol * animationEffectDelegate/* =NULL */,PAnimation_Call_Node pAnimationCall/* =NULL */)
{
    CCAssert( pAnimation!=NULL, "Animate: argument Animation must be non-NULL");
	m_fSingleDuration = pAnimation->getDuration();											//全局单轮时间之后 千万不要改动
	m_pAnimation_Call_Node=pAnimationCall;
	m_pDelegate=animationEffectDelegate;
	m_pAnimationNode=panimationNode;
	if ( CCActionInterval::initWithDuration(m_fSingleDuration * pAnimation->getLoops() ) ) 
	{
		m_nNextFrame = 0;
		setAnimation(pAnimation);
		m_pOrigFrame = NULL;
		m_uExecutedLoops = 0;
		m_pSplitTimes->reserve(pAnimation->getFrames()->count());
		float accumUnitsOfTime = 0;
		float newUnitOfTimeValue = m_fSingleDuration / pAnimation->getTotalDelayUnits();
		CCArray* pFrames = pAnimation->getFrames();
		CCARRAY_VERIFY_TYPE(pFrames, CCAnimationFrame*);
		CCObject* pObj = NULL;
		CCARRAY_FOREACH(pFrames, pObj)
		{
			CCAnimationFrame* frame = (CCAnimationFrame*)pObj;
			float value = (accumUnitsOfTime * newUnitOfTimeValue) / m_fSingleDuration;
			accumUnitsOfTime += frame->getDelayUnits();
			m_pSplitTimes->push_back(value);
		}    
		return true;
	}
	return false;
}

 

void  CCAnimationEffect::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	CCSprite *pSprite = (CCSprite*)(pTarget);

	CC_SAFE_RELEASE(m_pOrigFrame);

	if (m_pAnimation->getRestoreOriginalFrame())
	{
		m_pOrigFrame = pSprite->displayFrame();
		m_pOrigFrame->retain();
	}
	m_nNextFrame = 0;
	m_uExecutedLoops = 0;
}

void  CCAnimationEffect::stop()
{
	if (m_pAnimation->getRestoreOriginalFrame() && m_pTarget)
	{
		((CCSprite*)(m_pTarget))->setDisplayFrame(m_pOrigFrame);
	}
	CCActionInterval::stop();
}


void  CCAnimationEffect::step(float dt)
{
	if (m_bFirstTick)
	{
		m_bFirstTick = false;
		m_elapsed = 0;
	}
	else
	{
		m_elapsed += dt*m_fSpeedScale;
	}

	this->update(MAX (0,                                  // needed for rewind. elapsed could be negative
		MIN(1, m_elapsed /
		MAX(m_fDuration, FLT_EPSILON)   // division by 0
		)
		)
		);
}


bool  CCAnimationEffect::isDone(void)
{  
	if(m_elapsed >= m_fDuration)
	{ 
		m_bIsFinishCall=false;
		if(m_pAnimation_Call_Node!=NULL&&m_pDelegate!=NULL)
		{
			size_t  eventCount=m_pAnimation_Call_Node->callBackVec.size();
			for(size_t eventIndex=0;eventIndex<eventCount;eventIndex++)
			{
				if(m_pAnimation_Call_Node->callBackVec.at(eventIndex)!=NULL)
				{
					m_pAnimation_Call_Node->callBackVec.at(eventIndex)->isTrigger=false;
				}
			}
		}
		return true;
	}
	return false;
}

void  CCAnimationEffect::update(float t)
{
	if( t < 1.0f ) {
		t *= m_pAnimation->getLoops(); 
		unsigned int loopNumber = (unsigned int)t;
		if( loopNumber > m_uExecutedLoops ) {
			m_nNextFrame = 0;
			m_uExecutedLoops++;
		}
		t = fmodf(t, 1.0f);
	}

	checkCallBackVec(t*m_pAnimation->getDuration());  //侦测当前的定时回调逻辑

	if(t==SingleEffectTime&&!m_bIsFinishCall)
	{
		m_bIsFinishCall=true;
		if(m_pDelegate)
		m_pDelegate->EffectCallBackEventHandler(_Animation_Effect_Finish_Event_,m_pAnimationNode,NULL);
		if(m_bAutoRemove)
		{ m_pAnimationNode->removeFromParentAndCleanup(true);
		  return ;
		}
	}

	CCArray* frames = m_pAnimation->getFrames();
	unsigned int numberOfFrames = frames->count();
	CCSpriteFrame *frameToDisplay = NULL;

	for( unsigned int i=m_nNextFrame; i < numberOfFrames; i++ ) {
		float splitTime = m_pSplitTimes->at(i);

		if( splitTime <= t ) {
			CCAnimationFrame* frame = (CCAnimationFrame*)frames->objectAtIndex(i);
			frameToDisplay = frame->getSpriteFrame();
			((CCSprite*)m_pTarget)->setDisplayFrame(frameToDisplay);
			m_nNextFrame = i+1;
		}
		// Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
		else {
			break;
		}
	}
}



void  CCAnimationEffect::checkCallBackVec(float time)
{
	if(m_pAnimation_Call_Node!=NULL&&m_pDelegate!=NULL)
	{
		size_t callBackCount=m_pAnimation_Call_Node->callBackVec.size();
		for(size_t index=0;index<callBackCount;index++)
		{
			PCallBack_Node pCallBackNode=m_pAnimation_Call_Node->callBackVec.at(index);
			if(pCallBackNode!=NULL&&!pCallBackNode->isTrigger)
			{ 
				if(pCallBackNode->callBackTime<=time)
				{
					m_pDelegate->EffectCallBackEventHandler(pCallBackNode->eventType,m_pAnimationNode,pCallBackNode);
					pCallBackNode->isTrigger=true;
					continue; 
				}
			}
		}
	}
}

  

void   CCAnimationEffect::setAnimationEffectCallDelegate(AnimationEffectCallBackProtocol * animationEffectDelegate)
{
	if(m_pDelegate!=animationEffectDelegate)
	{
		m_pDelegate=animationEffectDelegate;
	}
}



void  CCAnimationEffect::setSpeedScale(float speedScaleValue)
{
	m_fSpeedScale=speedScaleValue;
}

void  CCAnimationEffect::setAnimationNode(cocos2d::CCNode * pAnimationNode)
{
	m_pAnimationNode=pAnimationNode;
}
cocos2d::CCNode * CCAnimationEffect::getAnimationNode()
{
	return m_pAnimationNode;
}
 

CCActionInterval * CCAnimationEffect::reverse()
{
	CCArray* pOldArray = m_pAnimation->getFrames();
	CCArray* pNewArray = CCArray::createWithCapacity(pOldArray->count());

	CCARRAY_VERIFY_TYPE(pOldArray, CCAnimationFrame*);

	if (pOldArray->count() > 0)
	{
		CCObject* pObj = NULL;
		CCARRAY_FOREACH_REVERSE(pOldArray, pObj)
		{
			CCAnimationFrame* pElement = (CCAnimationFrame*)pObj;
			if (! pElement)
			{
				break;
			}

			pNewArray->addObject((CCAnimationFrame*)(pElement->copy()->autorelease()));
		}
	}

	CCAnimation *newAnim = CCAnimation::create(pNewArray, m_pAnimation->getDelayPerUnit(), m_pAnimation->getLoops());
	newAnim->setRestoreOriginalFrame(m_pAnimation->getRestoreOriginalFrame());
	return create(m_pAnimationNode,newAnim);
}

CCAnimationEffect *  CCAnimationEffect::create(cocos2d::CCNode * panimationNode,CCAnimation *pAnimation,AnimationEffectCallBackProtocol * animationEffectDelegate/* =NULL */,PAnimation_Call_Node pAnimationCall/* =NULL */)
{
	 CCAnimationEffect * pAnimationEffect=new CCAnimationEffect();
	 if(pAnimationEffect&&pAnimationEffect->initWithAnimation(panimationNode,pAnimation,animationEffectDelegate,pAnimationCall))
	 {
		 pAnimationEffect->autorelease();
		 return pAnimationEffect;
	 }
	 if(pAnimationEffect!=NULL)
	 {
		 delete pAnimationEffect;
		 pAnimationEffect=NULL;
	 }
	 return  NULL;
}

void  CCAnimationEffect::setUnLoopAutoRemove(bool bAutoRemoveEnable)
{
	m_bAutoRemove=bAutoRemoveEnable;
}
bool  CCAnimationEffect::getUnLoopAutoRemove()
{
	return m_bAutoRemove;
}


 

