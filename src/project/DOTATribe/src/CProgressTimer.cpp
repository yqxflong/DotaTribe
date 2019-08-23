//Name：CProgressTimer
//Function：扩展的进度条
//Written By：lvyunlong


#include "../include/CProgressTimer.h"
#include "../include/NFControlsManager.h"

USING_NS_CC;


CProgressTimer* CProgressTimer::create(const char *pszFileName,float time)
{
	CProgressTimer* cc=new CProgressTimer();
	if (cc&&cc->init(pszFileName,time))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}
bool CProgressTimer::init(const char *pszFileName,float time)
{
	CCSprite* cc_inner=CCSprite::create();
	cc_inner->setProperty("File",pszFileName);
	if (CCProgressTimer::initWithSprite(cc_inner))
	{
		setType(kCCProgressTimerTypeBar);
		//    Setup for a bar starting from the left since the midpoint is 1 for the x
		setMidpoint(ccp(0,0));
		//    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
		setBarChangeRate(ccp(1, 0));

		m_Duration_ = time;
		return true;
	}
	return false;
}

void CProgressTimer::setDelegate(CProgressTimerDelegate *Delegate)
{
	m_pDelegate = Delegate;
}

void CProgressTimer::setRunSchedule(float posbegin,float posend,int times)
{
	stopAllActions();
	if (times == 0)
	{
		CCFiniteTimeAction*  action = CCSequence::create(
			CCProgressFromTo::create(m_Duration_,posbegin,posend),
			CCCallFunc::create(this, callfunc_selector(CProgressTimer::RunFinish)), 
			NULL);
		runAction(action);
	}
	else
	{
		//升满当前级别
		cocos2d::CCArray* arr = cocos2d::CCArray::create();
		CCFiniteTimeAction*  action = CCSequence::create(
			CCProgressFromTo::create(m_Duration_,posbegin,100), 
			CCCallFunc::create(this, callfunc_selector(CProgressTimer::NextLevel)), 
			NULL);
		arr->addObject(action);

		int i =1;
		for (i;i<times;i++)
		{
			CCFiniteTimeAction*  action1 = CCSequence::create(
				CCProgressFromTo::create(m_Duration_,0,100), 
				CCCallFunc::create(this, callfunc_selector(CProgressTimer::NextLevel)), 
				NULL);
			arr->addObject(action1);
		}
		CCFiniteTimeAction*  action2 = CCSequence::create(
			CCProgressFromTo::create(m_Duration_,0,posend), 
			CCCallFunc::create(this, callfunc_selector(CProgressTimer::RunFinish)), 
			NULL);
		arr->addObject(action2);
		runAction(CCSequence::create(arr));
	}
}

void CProgressTimer::RunFinish()
{
	if (m_pDelegate)
	{
		m_pDelegate->CallBack_RunFinish();
	}
}
void CProgressTimer::NextLevel()
{
	if (m_pDelegate)
	{
		m_pDelegate->CallBack_NextLevel();
	}
}