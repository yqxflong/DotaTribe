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
#include "CCAd.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <stdio.h>

namespace cocos2d
{
    CCAd::CCAd() : m_pAdDelegate(NULL)
    {
    }

    CCAd::~CCAd() 
    {

    }

    void CCAd::setDelegate(CCAdDelegate* pDelegate) 
    {
        m_pAdDelegate = pDelegate;
    }

	void CCAd::showAd(bool bShow)
	{
		if (bShow)
		{        
			enableAdJNI();
		}
		else
		{
			disableAdJNI();
		}
	}

	void CCAd::showYoumiOfferWall()
	{
		showYoumiOfferWallJNI();
	}

	void CCAd::showDianjoyOfferWall()
	{
		showDianjoyOfferWallJNI();
	}

	void CCAd::showImmobOfferWall()
	{
		showImmobOfferWallJNI();
	}

	void CCAd::showTapjoyOfferWall()
	{
		showTapjoyOfferWallJNI();
	}

	void CCAd::showDomobOfferWall()
	{
		showDomobOfferWallJNI();
	}

	void CCAd::show91OfferWall()
	{
		show91OfferWallJNI();
	}

	void CCAd::pushDianjoyAd()
	{	
		pushDianjoyAdJNI();
	}

	void CCAd::queryYoumiPoints()
	{
		queryYoumiPointsJNI();
	}

	void CCAd::queryDianjoyPoints()
	{
		queryDianjoyPointsJNI();
	}

	void CCAd::queryImmobPoints()
	{
		queryImmobPointsJNI();
	}

	void CCAd::queryTapjoyPoints()
	{
		queryTapjoyPointsJNI();
	}

	void CCAd::queryDomobPoints()
	{
		queryDomobPointsJNI();
	}

	void CCAd::query91Points()
	{
		query91PointsJNI();
	}

	void CCAd::updateYoumiPoints()
	{
		updateYoumiPointsJNI();
	}

	void CCAd::updateDianjoyPoints()
	{
		updateDianjoyPointsJNI();
	}

	void CCAd::updateImmobPoints()
	{
		updateImmobPointsJNI();
	}

	void CCAd::updateTapjoyPoints()
	{
		updateTapjoyPointsJNI();
	}

	void CCAd::updateDomobPoints()
	{
		updateDomobPointsJNI();
	}

	void CCAd::update91Points()
	{
		update91PointsJNI();
	}

	void CCAd::spendYoumiPoints(int amount)
	{
		spendYoumiPointsJNI(amount);
	}

	void CCAd::spendDianjoyPoints(int amount)
	{
		spendDianjoyPointsJNI(amount);
	}

	void CCAd::spendImmobPoints(int amount)
	{
		spendImmobPointsJNI(amount);
	}

	void CCAd::spendTapjoyPoints(int amount)
	{
		spendTapjoyPointsJNI(amount);
	}

	void CCAd::spendDomobPoints(int amount)
	{
		spendDomobPointsJNI(amount);
	}

	void CCAd::spend91Points(int amount)
	{
		spend91PointsJNI(amount);
	}

	void CCAd::receiveYoumiPoints(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceiveYoumiPoints(amount);
	}

	void CCAd::receiveDianjoyPoints(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceiveDianjoyPoints(amount);
	}

	void CCAd::receiveImmobPoints(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceiveImmobPoints(amount);
	}

	void CCAd::receiveTapjoyPoints(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceiveTapjoyPoints(amount);
	}

	void CCAd::receiveDomobPoints(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceiveDomobPoints(amount);
	}

	void CCAd::receive91Points(int amount)
	{
		if (m_pAdDelegate == NULL)
			return;

		m_pAdDelegate->onReceive91Points(amount);
	}

} // end of namespace cococs2d

