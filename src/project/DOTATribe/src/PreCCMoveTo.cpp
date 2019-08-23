////////////////////////////////////////////////////////////////
//Name:	 PreCCMoveTo
//Auchor: 	xiaobo.wu
//Func:	 优化后的CCMoveto
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include   "../include/PreCCMoveTo.h"


PreCCMoveTo* PreCCMoveTo::create(float duration, const CCPoint& position)
{
	PreCCMoveTo *pMoveTo = new PreCCMoveTo();
	pMoveTo->initWithDuration(duration, position);
	pMoveTo->autorelease();

	return pMoveTo;
}

bool PreCCMoveTo::initWithDuration(float duration, const CCPoint& position)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		m_endPosition = position;
		return true;
	}

	return false;
}

CCObject* PreCCMoveTo::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	PreCCMoveTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (PreCCMoveTo*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new PreCCMoveTo();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	pCopy->initWithDuration(m_fDuration, m_endPosition);

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void PreCCMoveTo::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_startPosition = pTarget->getPosition();
	m_delta = ccpSub(m_endPosition, m_startPosition);
}

void PreCCMoveTo::update(float time)
{
	if (m_pTarget)
	{
		m_pTarget->setPosition(ccp(m_startPosition.x + m_delta.x * time,
			m_startPosition.y + m_delta.y * time));
	}
}



//////////////////////////////////////////////////////////////////////////


PreCCMoveBy* PreCCMoveBy::create(float duration, const CCPoint& position)
{
	PreCCMoveBy *pMoveBy = new PreCCMoveBy();
	pMoveBy->initWithDuration(duration, position);
	pMoveBy->autorelease();

	return pMoveBy;
}

bool PreCCMoveBy::initWithDuration(float duration, const CCPoint& position)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		m_delta = position;
		return true;
	}

	return false;
}
 

void PreCCMoveBy::startWithTarget(CCNode *pTarget)
{
	CCPoint dTmp = m_delta;
	PreCCMoveTo::startWithTarget(pTarget);
	m_delta = dTmp;
}

CCActionInterval* PreCCMoveBy::reverse(void)
{
	return CCMoveBy::create(m_fDuration, ccp(-m_delta.x, -m_delta.y));
}