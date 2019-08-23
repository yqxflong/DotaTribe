/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#ifndef __CCSHADOWLABELTTF_H__
#define __CCSHADOWLABELTTF_H__

#include "CCLabelTTF.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */



/** @brief CCLabelTTF is a subclass of CCTextureNode that knows how to render text labels
 *
 * All features from CCTextureNode are valid in CCLabelTTF
 *
 * CCLabelTTF objects are slow. Consider using CCLabelAtlas or CCLabelBMFont instead.
 *
 * Custom ttf file can be put in assets/ or external storage that the Application can access.
 * @code
 * CCLabelTTF *label1 = CCLabelTTF::create("alignment left", "A Damn Mess", fontSize, blockSize, 
 *                                          kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
 * CCLabelTTF *label2 = CCLabelTTF::create("alignment right", "/mnt/sdcard/Scissor Cuts.ttf", fontSize, blockSize,
 *                                          kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
 * @endcode
 *
 */
class CC_DLL CCShadowLabelTTF : public CCLabelTTF
{
public:
    CCShadowLabelTTF();
    virtual ~CCShadowLabelTTF();
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

