////////////////////////////////////////////////////////////////
//Name:	 GradualColorAction
//Auchor: 	xiaobo.wu
//Func:	 颜色RGBA特效渐变动画(支持变速控制)
//Maintainer: 	xiaobo.wu
//date:  2013/07/28
////////////////////////////////////////////////////////////////
#include "../include/GradualColorAction.h"

GradualColorAction* GradualColorAction::create(float duration, GLubyte red, GLubyte green, GLubyte blue,GLubyte opacity)
{
	GradualColorAction *pTintTo = new GradualColorAction();
	pTintTo->initWithDuration(duration, red, green, blue,opacity);
	pTintTo->autorelease();

	return pTintTo;
}

bool GradualColorAction::initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue,GLubyte opacity)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		m_fSpeedScale=1.0f;
		m_to = ccc3(red, green, blue);
		m_toOpacity=opacity;
		return true;
	}

	return false;
}
 
void GradualColorAction::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
	if (pRGBAProtocol)
	{
		m_from = pRGBAProtocol->getColor();
		m_fromOpacity=pRGBAProtocol->getOpacity();
	} 
}

void GradualColorAction::update(float time)
{
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(m_pTarget);
	if (pRGBAProtocol)
	{
		pRGBAProtocol->setColor(ccc3(GLubyte(m_from.r + (m_to.r - m_from.r) * time), 
			(GLbyte)(m_from.g + (m_to.g - m_from.g) * time),
			(GLbyte)(m_from.b + (m_to.b - m_from.b) * time)));
		pRGBAProtocol->setOpacity(GLubyte(m_fromOpacity+(m_toOpacity-m_fromOpacity)*time));
	}    
}


void GradualColorAction::step(float dt)
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


void GradualColorAction::setSpeedScale(float speedScale)
{
	m_fSpeedScale=speedScale;
}