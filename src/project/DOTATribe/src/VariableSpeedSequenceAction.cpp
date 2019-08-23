/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  变速序列组合动画  (漏洞 不支持单一动画 必须多个动画组合)
//date:   2013/10/28
///////////////////////////////////////////////// 
#include "../include/VariableSpeedSequenceAction.h"

//#include "../cocos2dx/actions/CCActionInterval.cpp"

VariableSpeedSequenceAction* VariableSpeedSequenceAction::createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{ 
	VariableSpeedSequenceAction *pSequence = new VariableSpeedSequenceAction();
	pSequence->initWithTwoActions(pActionOne, pActionTwo);
	pSequence->autorelease();

	return pSequence;
}

VariableSpeedSequenceAction* VariableSpeedSequenceAction::create(CCFiniteTimeAction *pAction1, ...)
{
	//@获取多个参数的列表
	va_list params;
	va_start(params, pAction1);

	VariableSpeedSequenceAction *pRet = VariableSpeedSequenceAction::createWithVariableList(pAction1, params);

	va_end(params);

	return pRet;
}

VariableSpeedSequenceAction* VariableSpeedSequenceAction::createWithVariableList(CCFiniteTimeAction *pAction1, va_list args)
{
	
	CCFiniteTimeAction *pNow;
	CCFiniteTimeAction *pPrev = pAction1;
	bool bOneAction = true;

	while (pAction1)
	{
		//@va_arg每次取完参数，后续依次返回剩下参数
		pNow = va_arg(args, CCFiniteTimeAction*);
		if (pNow)
		{
			pPrev = createWithTwoActions(pPrev, pNow);
			bOneAction = false;
		}
		else
		{
			// If only one action is added to VariableSpeedSequenceAction, make up a VariableSpeedSequenceAction by adding a simplest finite time action.
			if (bOneAction)
			{
				//pPrev = createWithTwoActions(pPrev, ExtraAction::create());
			}
			break;
		}
	}

	return ((VariableSpeedSequenceAction*)pPrev);
}

VariableSpeedSequenceAction* VariableSpeedSequenceAction::create(CCArray* arrayOfActions)
{
	VariableSpeedSequenceAction* pRet = NULL;
	do 
	{
		unsigned  int count = arrayOfActions->count();
		CC_BREAK_IF(count == 0);

		CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);

		if (count > 1)
		{
			for (unsigned int i = 1; i < count; ++i)
			{
				prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
			}
		}
		else
		{
			// If only one action is added to VariableSpeedSequenceAction, make up a VariableSpeedSequenceAction by adding a simplest finite time action.
			//prev = createWithTwoActions(prev, ExtraAction::create());
		}
		pRet = (VariableSpeedSequenceAction*)prev;
	}while (0);
	return pRet;
}

bool VariableSpeedSequenceAction::initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
	m_fSpeedScale=1.0f;
	CCAssert(pActionOne != NULL, "");
	CCAssert(pActionTwo != NULL, "");

	float d = pActionOne->getDuration() + pActionTwo->getDuration();
	CCActionInterval::initWithDuration(d);

	m_pActions[0] = pActionOne;
	pActionOne->retain();

	m_pActions[1] = pActionTwo;
	pActionTwo->retain();

	return true;
}
 

VariableSpeedSequenceAction::~VariableSpeedSequenceAction(void)
{
	CC_SAFE_RELEASE(m_pActions[0]);
	CC_SAFE_RELEASE(m_pActions[1]);
}

void VariableSpeedSequenceAction::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_split = m_pActions[0]->getDuration() / m_fDuration;
	m_last = -1;
}

void VariableSpeedSequenceAction::stop(void)
{
	if( m_last != - 1)
	{
		m_pActions[m_last]->stop();
	}

	CCActionInterval::stop();
}

void VariableSpeedSequenceAction::update(float t)
{
	if(m_bIsForceDelete)
		return ;
	int found = 0;
	float new_t = 0.0f;

	if( t < m_split ) {
		// action[0]
		found = 0;
		if( m_split != 0 )
			new_t = t / m_split;
		else
			new_t = 1;

	} else {
		// action[1]
		found = 1;
		if ( m_split == 1 )
			new_t = 1;
		else
			new_t = (t-m_split) / (1 - m_split );
	}

	if ( found==1 ) {

		if( m_last == -1 ) {
			// action[0] was skipped, execute it.
			m_pActions[0]->startWithTarget(m_pTarget);
			m_pActions[0]->update(1.0f);
			m_pActions[0]->stop();
		}
		else if( m_last == 0 )
		{
			// switching to action 1. stop action 0.
			m_pActions[0]->update(1.0f);
			m_pActions[0]->stop();
		}
	}
	else if(found==0 && m_last==1 )
	{
		// Reverse mode ?
		// XXX: Bug. this case doesn't contemplate when _last==-1, found=0 and in "reverse mode"
		// since it will require a hack to know if an action is on reverse mode or not.
		// "step" should be overriden, and the "reverseMode" value propagated to inner Sequences.
		m_pActions[1]->update(0);
		m_pActions[1]->stop();
	}
	// Last action found and it is done.
	if( found == m_last && m_pActions[found]->isDone() )
	{
		return;
	}

	// Last action found and it is done
	if( found != m_last )
	{
		m_pActions[found]->startWithTarget(m_pTarget);
	}
	m_pActions[found]->update(new_t);
	m_last = found;
}

CCActionInterval* VariableSpeedSequenceAction::reverse(void)
{
	return VariableSpeedSequenceAction::createWithTwoActions(m_pActions[1]->reverse(), m_pActions[0]->reverse());
}

void VariableSpeedSequenceAction::step(float dt)
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

void VariableSpeedSequenceAction::setSpeedScale(float speedScale)
{
	m_fSpeedScale=speedScale;
}
























