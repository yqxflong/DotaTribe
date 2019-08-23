////////////////////////////////////////////////////////////////
//Name:	 MoveAnimation
//Auchor: 	xiaobo.wu
//Func:	 移动动画
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include    "../include/MoveAnimation.h"

#define   ENDSINGLETIME   1.0f

  
bool MoveAnimation::initWithDuration(float duration, const CCPoint& position,PCallBackVec pCallBackVec)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		m_duration=duration;
		m_endPosition = position;
		m_speedScale=1.0f;
		m_isFinish=false;
		m_pCallBackVec=pCallBackVec;
		return true;
	}
	return false;
}
MoveAnimation::~MoveAnimation()
{
	destroy();
}


void MoveAnimation::destroy()
{
	if(m_pCallBackVec!=NULL)
	{ 
		delete  m_pCallBackVec;
		m_pCallBackVec=NULL;
	}
}

CCObject* MoveAnimation::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	CCMoveTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{ 
		pCopy = (CCMoveTo*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCMoveTo();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCActionInterval::copyWithZone(pZone);
	pCopy->initWithDuration(m_fDuration, m_endPosition);

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void MoveAnimation::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_startPosition = pTarget->getPosition();
	m_delta = ccpSub(m_endPosition, m_startPosition);

}
void MoveAnimation::update(float time)
{
	if (m_pTarget)
	{
		 m_pTarget->setPosition(ccp(m_startPosition.x + m_delta.x * time,
			m_startPosition.y + m_delta.y * time));
       
		checkCallBackVec(time*m_duration/m_speedScale);
 
		if(time>(ENDSINGLETIME-FLT_EPSILON)&&!m_isFinish)
		{ 
			  m_isFinish=true; 
			 if(m_pCallBackVec!=NULL&&m_pCallBackVec->pDelegate!=NULL)
			 {
				m_pCallBackVec->pDelegate->CallBackEventProtocol(_Move_Animation_Finish_Event_,NULL);
				return ;
			 }
		}
	}
}


void  MoveAnimation::checkCallBackVec(float time)
{
	 if(m_pCallBackVec!=NULL&&m_pCallBackVec->pDelegate!=NULL)
	 {
		 size_t  sizeCount=m_pCallBackVec->callBackEventVec.size();
		 for(size_t eventIndex=0;eventIndex<sizeCount;eventIndex++)
		 {
			 PCallBackNode pCallBackNode=m_pCallBackVec->callBackEventVec.at(eventIndex);
			 if(pCallBackNode!=NULL&&!pCallBackNode->isTrigger)
			 {
			    if((pCallBackNode->triggerTime/m_speedScale)<=time)
				{
					m_pCallBackVec->pDelegate->CallBackEventProtocol(pCallBackNode->eventType,pCallBackNode);
					pCallBackNode->isTrigger=true;
					continue; 
				}
			 }
		 }
	 } 
}


void MoveAnimation::updateAnimatioSpeedScale()
{
   setDuration(m_duration/m_speedScale); 
}

void MoveAnimation::setSpeedScale(float speedScale)
{
	if(m_speedScale!=speedScale)
	{
		m_speedScale=speedScale;
		updateAnimatioSpeedScale();
	}
}

 
MoveAnimation* MoveAnimation::create(float duration, const CCPoint& position,PCallBackVec pCallBackVec/* =NULL */)
{
	MoveAnimation *pMoveAnimation = new MoveAnimation();
	if(pMoveAnimation!=NULL)
	pMoveAnimation->initWithDuration(duration, position,pCallBackVec);
    pMoveAnimation->autorelease();
	return pMoveAnimation;
}
 