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

#ifndef __PLATFORM_WIN32_CCAD_H__
#define __PLATFORM_WIN32_CCAD_H__

#include "platform/CCCommon.h"
#include "platform/CCAdDelegate.h"

namespace   cocos2d {

class CC_DLL CCAd
{
private:
	CCAdDelegate* m_pAdDelegate;

public:
    CCAd();
    ~CCAd();

public:
    void setDelegate(CCAdDelegate* pDelegate);

public:
	void showAd(bool bShow);
	void showYoumiOfferWall();
	void showDianjoyOfferWall();
	void showImmobOfferWall();
	void showTapjoyOfferWall();
	void showDomobOfferWall();
	void show91OfferWall();
	void pushDianjoyAd();

public:
	void queryYoumiPoints();
	void queryDianjoyPoints();
	void queryImmobPoints();
	void queryTapjoyPoints();
	void queryDomobPoints();
	void query91Points();

public:
	void updateYoumiPoints();
	void updateDianjoyPoints();
	void updateImmobPoints();
	void updateTapjoyPoints();
	void updateDomobPoints();
	void update91Points();

public:
	void spendYoumiPoints(int amount);
	void spendDianjoyPoints(int amount);
	void spendImmobPoints(int amount);
	void spendTapjoyPoints(int amount);
	void spendDomobPoints(int amount);
	void spend91Points(int amount);

public:
	void receiveYoumiPoints(int amount);
	void receiveDianjoyPoints(int amount);
	void receiveImmobPoints(int amount);
	void receiveTapjoyPoints(int amount);
	void receiveDomobPoints(int amount);
	void receive91Points(int amount);
};

}//namespace cocos2d

#endif
