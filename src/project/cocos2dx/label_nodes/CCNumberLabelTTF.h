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
#ifndef __CCNUMBERLABELTTF_H__
#define __CCNUMBERLABELTTF_H__

#include "CCSingleLineLabelTTF.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup singleline label
 * @{
 */


class CC_DLL CCNumberLabelTTF : public CCSingleLineLabelTTF
{
protected:
	int  m_TarNumber;
	int  m_ShowNumber;
	bool m_bAnimationLabel;
	float m_AnimationInterval;
	
protected:
	CCAction* m_pAnimationAction;

public:
    CCNumberLabelTTF();
    virtual ~CCNumberLabelTTF();

public:
    /** changes the string to render
    * @warning Changing the string is as expensive as creating a new CCLabelTTF. To obtain better performance use CCLabelAtlas
    */
    virtual void setString(const char *label);

public:
    void setNumber(int number);
	int  getNumber();
	void setIsAnimationLabel(bool bAnimation);
	bool getIsAnimationLabel();
	void setAnimationInterval(float interval);
	float getAnimationInterval();

protected:
	void callback();
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

