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
#ifndef __MISC_NODE_CCPROGRESS_BAR_H__
#define __MISC_NODE_CCPROGRESS_BAR_H__

#include "sprite_nodes/CCSprite.h"

NS_CC_BEGIN

/**
 * @addtogroup misc_nodes
 * @{
 */

/**
 @brief CCProgressBar is a subclass of CCNode.
 It renders the inner sprite according to the percentage.
 The progress can be Radial, Horizontal or vertical.
 @since v0.99.1
 */
class CC_DLL CCProgressTimer;
class CC_DLL CCProgressBar : public CCSprite
{
public:
    CCProgressBar();
    virtual ~CCProgressBar(void);

public:
	virtual bool init();

public:
	// set progress bar image file
	void  setProgressInnerFileName(std::string fileName);
	// set progress bar image frame
	void  setProgressInnerFrameName(std::string fileName);
	// set progress inner x offset
	void  setProgressXInnerOffset(float offset);
	// get progress inner x offset
	float getProgressXInnerOffset();
	// set progress inner y offset
	void  setProgressYInnerOffset(float offset);
	// get progress inner y offset
	float getProgressYInnerOffset();
	// set percent
	void  setPercent(float per);
	// get percent
	float getPercent();

protected:
	float m_XInnerOffset; // inner x offset
	float m_YInnerOffset; // inner y offset

protected:
	CCProgressTimer* m_pProgressTimer;

public:
	static  CCProgressBar*  create();
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__MISC_NODE_CCPROGRESS_BAR_H__
