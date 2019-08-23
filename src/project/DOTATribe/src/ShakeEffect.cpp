////////////////////////////////////////////////////////////////
//Name:	 ShakeEffect
//Auchor: 	qiang.yin
//Func:	 震动动画
//Maintainer: 	xiaobo.wu
//date:   2014/01/02
////////////////////////////////////////////////////////////////
#include   "../include/ShakeEffect.h"
#include "../include/CameraShakeDataManager.h"
#include "../include/PreCCMoveTo.h"

ShakeEffect::ShakeEffect()
{
  m_startPosition=CCPointZero;
  m_bIsFinish=false;
  m_fHalfCircleTime=0.0f;
  m_fShakeX=0.0f;
  m_fShakeY=0.0f;
  m_fSpeedScale=1.0f;
  seq=NULL;
}
 
ShakeEffect * ShakeEffect::CreateShakeEffect(int shakeID)
{   
	ShakeEffect *  pShakeEffect=new ShakeEffect();
	if(pShakeEffect&&pShakeEffect->InitShakeEffect(shakeID))
	{
		 pShakeEffect->autorelease();
		 return  pShakeEffect;
	}
	if(pShakeEffect!=NULL)
	{ 
		delete pShakeEffect;
		pShakeEffect=NULL;
	}
	return NULL;
}


bool  ShakeEffect::InitShakeEffect(int shakeID)
{ 
	assert(shakeID>0);
	CameraShakeData* dd=CameraShakeDataManager::get_instance2()->GetCamerShakeDataByID(shakeID);
#if 1
	if(!CCActionInterval::initWithDuration((float)(dd->containTime_*1.0/1000)))
		  return false;
	m_fShakeX=dd->shakeX_;
	m_fShakeY=dd->shakeY_;
	m_fHalfCircleTime= (float)(dd->halfCircleTime_*1.0/1000);
#else
	if(!CCActionInterval::initWithDuration(1.0))
		return false;
	m_fShakeX=3;
	m_fShakeY=-3;
	m_fHalfCircleTime=0.1;
#endif
	return true;
}

void ShakeEffect::step(float dt)
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


/*
	开始播放动画
*/
void  ShakeEffect::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_startPosition = pTarget->getPosition();
	_playEffect();
}
/*
	播放时间到，停止
*/
void  ShakeEffect::stop(void)
{
	m_bIsFinish=true;
	if(m_pTarget!=NULL)
	m_pTarget->setPosition(m_startPosition);
	if(seq!=NULL)
	{
		seq->stop();
		seq->setForceDelete(true);
		seq=NULL;
	}
	
	CCActionInterval::stop();
}

void ShakeEffect::setSpeedScale(float speedScale)
{
	m_fSpeedScale=speedScale;
}


void ShakeEffect::_playEffect(){
	if(m_bIsFinish)
		return ;
	if (!m_pTarget)return;
	m_bIsFinish=false;
	CCActionInterval* move1=PreCCMoveBy::create(m_fHalfCircleTime,ccp(m_fShakeX,m_fShakeY));
	CCActionInterval* move2=PreCCMoveBy::create(m_fHalfCircleTime*2,ccp(-2*m_fShakeX,-2*m_fShakeY));
	CCActionInterval* move3=PreCCMoveBy::create(m_fHalfCircleTime,ccp(m_fShakeX,m_fShakeY));
	CCCallFunc* callfunc=CCCallFunc::create(this,callfunc_selector(ShakeEffect::CALLFUNC_EVENT));
	seq=CCSequence::create(CCArray::create(move1,move2,move3,callfunc,NULL));
	CCPoint cp=m_pTarget->getPosition();
	m_pTarget->runAction(seq);
}

void ShakeEffect::CALLFUNC_EVENT(){
	_playEffect();
}


