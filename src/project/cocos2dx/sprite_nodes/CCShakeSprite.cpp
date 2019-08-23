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

#include "CCShakeSprite.h"
#include "CCDirector.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include <string.h>

using namespace std;
namespace   cocos2d {

	CCShakeSprite::CCShakeSprite()
	{
		m_bRepeat   = false;
		m_bAutoPlay = false;
		m_fInterval = 1.0f;
		m_fXMoveLength = 5.0f;
		m_fYMoveLength = 5.0f;
	}

	CCShakeSprite::~CCShakeSprite()
	{
		this->stopAllActions();
	}

	//! play animation
	void CCShakeSprite::play()
	{
		stop();

		CCActionInterval* pMoveBy = CCMoveBy::create(m_fInterval, CCPoint(m_fXMoveLength, m_fYMoveLength));
		CCActionInterval* pMoveByBack = pMoveBy->reverse();
		this->runAction(CCSequence::create(pMoveBy, pMoveByBack, cocos2d::CCCallFunc::create(this, callfunc_selector(CCShakeSprite::callback)), NULL));
	}

	//! stop animation
	void CCShakeSprite::stop()
	{
		this->stopAllActions();
	}

	//! set animation interval
	void CCShakeSprite::setInterval(float interval)
	{
		m_fInterval = interval;
		if (m_bAutoPlay)
			play();
	}

	//! get animation interval
	float CCShakeSprite::getInterval()
	{
		return m_fInterval;
	}

	//! set animation repeat
	void CCShakeSprite::setRepeat(bool bRepeat)
	{
		m_bRepeat = bRepeat;
		if (m_bAutoPlay)
			play();
	}

	//! get animation repeat
	bool CCShakeSprite::getRepeat()
	{
		return m_bRepeat;
	}

	//! set animation auto play
	void CCShakeSprite::setAutoPlay(bool bAutoPlay)
	{
		m_bAutoPlay = bAutoPlay;
		if (m_bAutoPlay)
			play();
	}

	//! get animation auto play
	bool CCShakeSprite::getAutoPlay()
	{
		return m_bAutoPlay;
	}

	void CCShakeSprite::setXMoveLength(float xLen)
	{
		m_fXMoveLength = xLen;
	}

	float CCShakeSprite::getXMoveLength()
	{
		return m_fXMoveLength;
	}

	void CCShakeSprite::setYMoveLength(float yLen)
	{
		m_fYMoveLength = yLen;
	}

	float CCShakeSprite::getYMoveLength()
	{
		return m_fYMoveLength;
	}

	void CCShakeSprite::callback()
	{
		stop();
		if (m_bRepeat)
			play();
	}

}//namespace   cocos2d 
