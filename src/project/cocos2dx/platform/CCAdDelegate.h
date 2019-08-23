/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CCAD_DELEGATE_H__
#define __CCAD_DELEGATE_H__

#include "CCCommon.h"

NS_CC_BEGIN

/**
@brief 
The CCAdbDelegate defines a single method for
*/
class CC_DLL CCAdDelegate
{
public:
	virtual void onReceiveYoumiPoints(int amount){}
	virtual void onReceiveDianjoyPoints(int amount){}
	virtual void onReceiveImmobPoints(int amount){}
	virtual void onReceiveTapjoyPoints(int amount){};
	virtual void onReceiveDomobPoints(int amount){};
	virtual void onReceive91Points(int amount){};
};

NS_CC_END

#endif
