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

#ifndef __SPITE_NODE_CCANIMATIONSPRITE_H__
#define __SPITE_NODE_CCANIMATIONSPRITE_H__

#include "base_nodes/CCNode.h"
#include <string>
namespace   cocos2d {

	class CCSprite;
	class CC_DLL CCAnimationSprite : public CCNode
	{
	protected:
		CCSprite*    m_pAnimationSprite;  // animation sprite
		std::string  m_pAnimationName;    // animation name
		float        m_AnimationInterval; // animation interval
		unsigned int m_AnimationFrameCount; // animation frame number
		bool         m_AnimationRepeat;  // animation repeat forever
		bool         m_bAutoPlay;        // animation auto play

	public:
		CCAnimationSprite(void);
		virtual ~CCAnimationSprite(void);

	public:
		//! play animation
		void play();
		//! stop animation
		void stop();

	public:
		//! get animation sprite
		CCSprite* getAnimationSprite();
		//! set animation sprite
		void setAnimationSprite(CCSprite* pSprite);

	public:
		//! set animation name
		void setAnimationName(std::string name);
		//! get animation name
		std::string getAnimationName();
		//! set animation interval
		void setAnimationInterval(float interval);
		//! get animation interval
		float getAnimationInterval();
		//! set animation frame count
		void setAnimationFrameCount(unsigned int num);
		//! get animation frame count
		unsigned int getAnimationFrameCount();
		//! set animation repeat
		void setAnimationRepeat(bool bRepeat);
		//! get animation repeat
		bool getAnimationRepeat();
		//! set animation auto play
		void setAnimationAutoPlay(bool bAutoPlay);
		//! get animation auto play
		bool getAnimationAutoPlay();

	public:
		virtual bool init();

	private:
		void callback();

	};
}//namespace   cocos2d 

#endif // __SPITE_NODE_CCSPRITE_H__
