/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Lam Pham

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCProgressBar.h"
#include "CCProgressTimer.h"
#include "CCDirector.h"
NS_CC_BEGIN


CCProgressBar::CCProgressBar()
{
	m_pProgressTimer = NULL;
	m_XInnerOffset = 4.0f;
	m_YInnerOffset = 4.0f;
}

CCProgressBar::~CCProgressBar(void)
{
	if (m_pProgressTimer != NULL)
	{
		this->removeChild(m_pProgressTimer, true);
		m_pProgressTimer = NULL;
	}
}

bool CCProgressBar::init()
{
	return CCSprite::init();
}

// set progress bar image file
void CCProgressBar::setProgressInnerFileName(std::string fileName)
{
	if (m_pProgressTimer != NULL)
	{
		this->removeChild(m_pProgressTimer, true);
		m_pProgressTimer = NULL;
	}

	m_pProgressTimer = cocos2d::CCProgressTimer::create(CCSprite::create(fileName.c_str()));
	m_pProgressTimer->setType(cocos2d::kCCProgressTimerTypeBar);
	m_pProgressTimer->setMidpoint(cocos2d::CCPoint(0, 0));
	m_pProgressTimer->setBarChangeRate(cocos2d::CCPoint(1, 0));
	m_pProgressTimer->setAnchorPoint(CCPointMake(0.0f, 0.0f));

	const cocos2d::CCRect& rect  = this->getTextureRect();
	const cocos2d::CCRect& rect2 = m_pProgressTimer->getSprite()->getTextureRect();
	{
		float xScale = (rect.size.width-m_XInnerOffset)/rect2.size.width;
		float yScale = (rect.size.height-m_YInnerOffset)/rect2.size.height;

		m_pProgressTimer->setScaleX(xScale);
		m_pProgressTimer->setScaleY(yScale);
	}

	m_pProgressTimer->setPositionX(m_XInnerOffset/2.0f);
	m_pProgressTimer->setPositionY(m_YInnerOffset/2.0f);
	this->addChild(m_pProgressTimer, 1);
}

// set progress bar image frame
void CCProgressBar::setProgressInnerFrameName(std::string fileName)
{
	if (m_pProgressTimer != NULL)
	{
		this->removeChild(m_pProgressTimer, true);
		m_pProgressTimer = NULL;
	}

	m_pProgressTimer = cocos2d::CCProgressTimer::create(CCSprite::createWithSpriteFrameName(fileName.c_str()));
	m_pProgressTimer->setType(cocos2d::kCCProgressTimerTypeBar);
	m_pProgressTimer->setMidpoint(cocos2d::CCPoint(0, 0));
	m_pProgressTimer->setBarChangeRate(cocos2d::CCPoint(1, 0));
	m_pProgressTimer->setAnchorPoint(CCPointMake(0.0f, 0.0f));

	const cocos2d::CCRect& rect  = this->getTextureRect();
	const cocos2d::CCRect& rect2 = m_pProgressTimer->getSprite()->getTextureRect();
	{
		float xScale = (rect.size.width-m_XInnerOffset)/rect2.size.width;
		float yScale = (rect.size.height-m_YInnerOffset)/rect2.size.height;

		m_pProgressTimer->setScaleX(xScale);
		m_pProgressTimer->setScaleY(yScale);
	}

	m_pProgressTimer->setPositionX(m_XInnerOffset/2.0f);
	m_pProgressTimer->setPositionY(m_YInnerOffset/2.0f);
	this->addChild(m_pProgressTimer, 1);
}

// set progress inner x offset
void CCProgressBar::setProgressXInnerOffset(float offset)
{
	m_XInnerOffset = offset;
	if (m_pProgressTimer != NULL)
	{
		const cocos2d::CCRect& rect  = this->getTextureRect();
		const cocos2d::CCRect& rect2 = m_pProgressTimer->getSprite()->getTextureRect();
		float xScale = (rect.size.width-offset)/rect2.size.width;

		m_pProgressTimer->setScaleX(xScale);
		m_pProgressTimer->setPositionX(m_XInnerOffset/2.0f);
	}
}

// get progress inner x offset
float CCProgressBar::getProgressXInnerOffset()
{
	return m_XInnerOffset;
}

// set progress inner y offset
void CCProgressBar::setProgressYInnerOffset(float offset)
{
	m_YInnerOffset = offset;
	if (m_pProgressTimer != NULL)
	{
		const cocos2d::CCRect& rect  = this->getTextureRect();
		const cocos2d::CCRect& rect2 = m_pProgressTimer->getSprite()->getTextureRect();
		float yScale = (rect.size.height-offset)/rect2.size.height;

		m_pProgressTimer->setScaleY(yScale);
		m_pProgressTimer->setPositionY(m_YInnerOffset/2.0f);
	}
}

// get progress inner y offset
float CCProgressBar::getProgressYInnerOffset()
{
	return m_YInnerOffset;
}

void CCProgressBar::setPercent(float per)
{
	if (m_pProgressTimer != NULL)
	{
		m_pProgressTimer->setPercentage(per);
	}
}

float CCProgressBar::getPercent()
{
	if (m_pProgressTimer == NULL)
		return 0;

	return m_pProgressTimer->getPercentage();
}

CCProgressBar* CCProgressBar::create()
{
	CCProgressBar *pProgressBar = new CCProgressBar();
	if (pProgressBar->init())
	{
		pProgressBar->autorelease();
	}
	else
	{
		delete pProgressBar;
		pProgressBar = NULL;
	}        

	return pProgressBar;
}


NS_CC_END
