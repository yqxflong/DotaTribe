/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCScaleSprite.h"
#include "CCDirector.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include <string.h>

using namespace std;
namespace   cocos2d {
	CCScaleSprite::CCScaleSprite()
	{
		m_bRepeat   = false;
		m_bAutoPlay = false;
		m_fInterval = 1.0f;
		m_fMaxScale = 1.5f;
	}

	CCScaleSprite::~CCScaleSprite()
	{
		this->stopAllActions();
	}

	//! play animation
	void CCScaleSprite::play()
	{
		stop();

		CCActionInterval* pScale     = CCScaleBy::create(m_fInterval, m_fMaxScale);
		CCActionInterval* pScaleBack = pScale->reverse();
		this->runAction(CCSequence::create(pScale, pScaleBack, cocos2d::CCCallFunc::create(this, callfunc_selector(CCScaleSprite::callback)), NULL));
	}

	//! stop animation
	void CCScaleSprite::stop()
	{
		this->stopAllActions();
		this->setScale(1.0f);
	}

	//! set animation interval
	void CCScaleSprite::setInterval(float interval)
	{
		m_fInterval = interval;
		if (m_bAutoPlay)
			play();
	}

	//! get animation interval
	float CCScaleSprite::getInterval()
	{
		return m_fInterval;
	}

	//! set animation repeat
	void CCScaleSprite::setRepeat(bool bRepeat)
	{
		m_bRepeat = bRepeat;
		if (m_bAutoPlay)
			play();
	}

	//! get animation repeat
	bool CCScaleSprite::getRepeat()
	{
		return m_bRepeat;
	}

	//! set animation auto play
	void CCScaleSprite::setAutoPlay(bool bAutoPlay)
	{
		m_bAutoPlay = bAutoPlay;
		if (m_bAutoPlay)
			play();
	}

	//! get animation auto play
	bool CCScaleSprite::getAutoPlay()
	{
		return m_bAutoPlay;
	}

	void CCScaleSprite::setMaxScale(float maxScale)
	{
		m_fMaxScale = maxScale;
	}

	float CCScaleSprite::getMaxScale()
	{
		return m_fMaxScale;
	}

	void CCScaleSprite::callback()
	{
		stop();
		if (m_bRepeat)
			play();
	}

}//namespace   cocos2d 
