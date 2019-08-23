#include "CCNumberLabelTTF.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
using namespace cocos2d;

CCNumberLabelTTF::CCNumberLabelTTF()
{
	m_TarNumber = 0;
	m_ShowNumber= 0;
	m_bAnimationLabel = true;
	m_AnimationInterval = 0.05f;

	m_pAnimationAction = NULL;
}

CCNumberLabelTTF::~CCNumberLabelTTF()
{
	if (m_pAnimationAction != NULL)
	{
		stopAction(m_pAnimationAction);
		m_pAnimationAction = NULL;
	}
}

void CCNumberLabelTTF::setString(const char *string)
{
	CCAssert(string != NULL, "Invalid string");

	if (m_string.compare(string))
	{
		m_string = string;
		m_RichTextList.clear();

		this->updateTexture();
	}
}

void CCNumberLabelTTF::setNumber(int number)
{
	if (m_pAnimationAction != NULL)
	{
		stopAction(m_pAnimationAction);
		m_pAnimationAction = NULL;
	}
	
	m_ShowNumber = m_TarNumber;
	if (m_TarNumber == number)
		return;
	
	m_TarNumber = number;
	if (m_bAnimationLabel)
	{
		m_pAnimationAction = cocos2d::CCSequence::create(cocos2d::CCDelayTime::create(m_AnimationInterval), cocos2d::CCCallFunc::create(this, callfunc_selector(cocos2d::CCNumberLabelTTF::callback)), NULL);
		runAction(m_pAnimationAction);
	}
	else
	{
		char buffer[128] = "";
		sprintf(buffer, "%d", m_TarNumber);
		setString(buffer);
	}
}

int CCNumberLabelTTF::getNumber()
{
	return m_TarNumber;
}

void CCNumberLabelTTF::setIsAnimationLabel(bool bAnimation)
{
	m_bAnimationLabel = bAnimation;
}

bool CCNumberLabelTTF::getIsAnimationLabel()
{
	return m_bAnimationLabel;
}

void CCNumberLabelTTF::setAnimationInterval(float interval)
{
	m_AnimationInterval = interval;
}

float CCNumberLabelTTF::getAnimationInterval()
{
	return m_AnimationInterval;
}

void CCNumberLabelTTF::callback()
{
	if (m_ShowNumber == m_TarNumber)
	{
		stopAction(m_pAnimationAction);
		m_pAnimationAction = NULL;
		return;
	}
	
	m_ShowNumber = m_ShowNumber+(m_TarNumber-m_ShowNumber)/abs(m_TarNumber-m_ShowNumber);
	
	char buffer[128] = "";
	sprintf(buffer, "%d", m_ShowNumber);
	setString(buffer);

	m_pAnimationAction = cocos2d::CCSequence::create(cocos2d::CCDelayTime::create(m_AnimationInterval), cocos2d::CCCallFunc::create(this, callfunc_selector(cocos2d::CCNumberLabelTTF::callback)), NULL);
	runAction(m_pAnimationAction);
}
