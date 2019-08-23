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

#include "CCSpriteBatchNode.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "include/ccConfig.h"
#include "CCAnimationSprite.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "textures/CCTextureCache.h"
#include "support/CCPointExtension.h"
#include "cocoa/CCGeometry.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCAffineTransform.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include "CCDirector.h"
#include <string.h>

using namespace std;
namespace   cocos2d {

	CCAnimationSprite::CCAnimationSprite()
	{
		m_pAnimationSprite   = NULL;
		m_pAnimationName     = "";
		m_AnimationInterval  = CCDirector::sharedDirector()->getAnimationSpritePlayInterval();
		m_AnimationFrameCount= 0;
		m_AnimationRepeat    = true;
		m_bAutoPlay          = false;
	}

	CCAnimationSprite::~CCAnimationSprite()
	{
		if (m_pAnimationSprite != NULL)
		{
			m_pAnimationSprite->stopAllActions();
			this->removeChild(m_pAnimationSprite, true);
			m_pAnimationSprite = NULL;
		}
	}

	//! play animation
	void CCAnimationSprite::play()
	{
		if (m_AnimationFrameCount == 0)
			return;

		if (m_pAnimationName.size() == 0)
			return;


		if (m_pAnimationSprite != NULL)
		{
			m_pAnimationSprite->stopAllActions();
			this->removeChild(m_pAnimationSprite, true);
			m_pAnimationSprite = NULL;
		}

		cocos2d::CCArray* pAnimFrames = cocos2d::CCArray::create();
		{
			for(unsigned int i=1; i<=m_AnimationFrameCount; i++) 
			{
				char buffer[128] = "";
				sprintf(buffer, "%s_%02d.png", m_pAnimationName.c_str(), i);
				cocos2d::CCSpriteFrame* pTemp = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
				pAnimFrames->addObject(pTemp);
			}
			setAnimationSprite(cocos2d::CCSprite::createWithSpriteFrame((cocos2d::CCSpriteFrame*)pAnimFrames->objectAtIndex(0)));

			cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(pAnimFrames, m_AnimationInterval);
			cocos2d::CCAnimate*   pAnimate   = cocos2d::CCAnimate::create(pAnimation);
			if (m_AnimationRepeat)
			{
				cocos2d::CCActionInterval* pSeq = (cocos2d::CCActionInterval*)(cocos2d::CCSequence::create(pAnimate, NULL));
				m_pAnimationSprite->runAction(cocos2d::CCRepeatForever::create(pSeq));
			}
			else
			{
				cocos2d::CCAction* pAction = cocos2d::CCSequence::create(pAnimate, cocos2d::CCCallFunc::create(this, callfunc_selector(cocos2d::CCAnimationSprite::callback)), NULL);
				m_pAnimationSprite->runAction(pAction);
			}

		}
		pAnimFrames->release();
	}

	//! stop animation
	void CCAnimationSprite::stop()
	{
		if (m_pAnimationSprite != NULL)
		{
			m_pAnimationSprite->stopAllActions();
			this->removeChild(m_pAnimationSprite, true);
			m_pAnimationSprite = NULL;
		}
	}

	CCSprite* CCAnimationSprite::getAnimationSprite()
	{
		return m_pAnimationSprite;
	}

	//! set animation name
	void CCAnimationSprite::setAnimationName(std::string name)
	{
		m_pAnimationName = name;
		if (m_bAutoPlay)
			play();
	}

	//! get animation name
	std::string CCAnimationSprite::getAnimationName()
	{
		return m_pAnimationName;
	}	

	//! set animation interval
	void CCAnimationSprite::setAnimationInterval(float interval)
	{
		m_AnimationInterval = interval;
		if (m_bAutoPlay)
			play();
	}

	//! get animation interval
	float CCAnimationSprite::getAnimationInterval()
	{
		return m_AnimationInterval;
	}

	void CCAnimationSprite::setAnimationFrameCount(unsigned int num)
	{
		m_AnimationFrameCount = num;
		if (m_bAutoPlay)
			play();
	}

	unsigned int CCAnimationSprite::getAnimationFrameCount()
	{
		return m_AnimationFrameCount;
	}

	//! set animation repeat
	void CCAnimationSprite::setAnimationRepeat(bool bRepeat)
	{
		m_AnimationRepeat = bRepeat;
		if (m_bAutoPlay)
			play();
	}

	//! get animation repeat
	bool CCAnimationSprite::getAnimationRepeat()
	{
		return m_AnimationRepeat;
	}

	//! set animation auto play
	void CCAnimationSprite::setAnimationAutoPlay(bool bAutoPlay)
	{
		m_bAutoPlay = bAutoPlay;
		if (m_bAutoPlay)
			play();
	}

	//! get animation auto play
	bool CCAnimationSprite::getAnimationAutoPlay()
	{
		return m_bAutoPlay;
	}

	void CCAnimationSprite::callback()
	{
		stop();
	}

	bool CCAnimationSprite::init()
	{
		setAnchorPoint(ccp(0.5f, 0.5f));
		return true;
	}

	void CCAnimationSprite::setAnimationSprite(CCSprite* pSprite)
	{
		if (m_pAnimationSprite != NULL)
		{
			m_pAnimationSprite->stopAllActions();
			removeChild(m_pAnimationSprite, true);
			m_pAnimationSprite = NULL;
		}

		m_pAnimationSprite = pSprite;
		m_pAnimationSprite->setAnchorPoint(CCPoint(0.5f, 0.5f));
		m_pAnimationSprite->setPosition(CCPoint(m_pAnimationSprite->getContentSize().width/2, m_pAnimationSprite->getContentSize().height/2));

		addChild(m_pAnimationSprite);
		this->setContentSize(m_pAnimationSprite->getContentSize());
	}

}//namespace   cocos2d 
