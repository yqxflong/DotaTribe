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

#ifndef __SPITE_NODE_CCSCALESPRITE_H__
#define __SPITE_NODE_CCSCALESPRITE_H__

#include "CCSprite.h"
#include <string>
namespace   cocos2d {

	class CCSprite;
	class CC_DLL CCScaleSprite : public CCSprite
	{
	protected:
		bool  m_bRepeat;   // sprite repeat forever
		bool  m_bAutoPlay; // sprite auto scale when create
		float m_fInterval; // sprite auto scale interval
		float m_fMaxScale; // set max scale factor

	public:
		CCScaleSprite(void);
		virtual ~CCScaleSprite(void);

	public:
		//! play scale animation
		void play();
		//! stop scale animation
		void stop();

	public:
		//! set animation interval
		void setInterval(float interval);
		//! get animation interval
		float getInterval();
		//! set scale animation repeat
		void setRepeat(bool bRepeat);
		//! get scale animation repeat
		bool getRepeat();
		//! set scale animation auto play
		void setAutoPlay(bool bAutoPlay);
		//! get scale animation auto play
		bool getAutoPlay();
		// set max scale factor
		void setMaxScale(float maxScale);
		// get max scale factor
		float getMaxScale();

	private:
		void callback();
	};
}//namespace   cocos2d 

#endif // __SPITE_NODE_CCSPRITE_H__
