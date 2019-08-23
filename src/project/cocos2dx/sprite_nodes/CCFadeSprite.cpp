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

#include "CCFadeSprite.h"
#include "CCDirector.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include <string.h>

using namespace std;
namespace   cocos2d {
	CCFadeSprite::CCFadeSprite()
	{
		m_bRepeat   = false;
		m_bAutoPlay = false;
		m_fInterval = 1.0f;
	}

	CCFadeSprite::~CCFadeSprite()
	{
		this->stopAllActions();
	}

	//! stop animation
	void CCFadeSprite::stop()
	{
		this->stopAllActions();
	}

	//! set animation interval
	void CCFadeSprite::setInterval(float interval)
	{
		m_fInterval = interval;
		if (m_bAutoPlay)
			play();
	}

	//! get animation interval
	float CCFadeSprite::getInterval()
	{
		return m_fInterval;
	}

	//! set animation repeat
	void CCFadeSprite::setRepeat(bool bRepeat)
	{
		m_bRepeat = bRepeat;
		if (m_bAutoPlay)
			play();
	}

	//! get animation repeat
	bool CCFadeSprite::getRepeat()
	{
		return m_bRepeat;
	}

	//! set animation auto play
	void CCFadeSprite::setAutoPlay(bool bAutoPlay)
	{
		m_bAutoPlay = bAutoPlay;
		if (m_bAutoPlay)
			play();
	}

	//! get animation auto play
	bool CCFadeSprite::getAutoPlay()
	{
		return m_bAutoPlay;
	}

	void CCFadeSprite::callback()
	{
		stop();
		if (m_bRepeat)
			play();
	}

	//! play animation
	void CCFadeInSprite::play()
	{
		stop();

		this->setOpacity(0);
		CCActionInterval* pFade     = CCFadeIn::create(m_fInterval);
		CCActionInterval* pFadeBack = pFade->reverse();
		this->runAction(CCSequence::create(pFade, pFadeBack, cocos2d::CCCallFunc::create(this, callfunc_selector(CCFadeSprite::callback)), NULL));
	}

	//! play animation
	void CCFadeOutSprite::play()
	{
		stop();

		this->setOpacity(255);
		CCActionInterval* pFade     = CCFadeOut::create(m_fInterval);
		CCActionInterval* pFadeBack = pFade->reverse();
		this->runAction(CCSequence::create(pFade, pFadeBack, cocos2d::CCCallFunc::create(this, callfunc_selector(CCFadeSprite::callback)), NULL));
	}

}//namespace   cocos2d 