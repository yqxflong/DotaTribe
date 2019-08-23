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
		;
	}

	void CCAd::showYoumiOfferWall()
	{
		;
	}

	void CCAd::showDianjoyOfferWall()
	{
		;
	}

	void CCAd::showImmobOfferWall()
	{
		;
	}

	void CCAd::showTapjoyOfferWall()
	{
		;
	}

	void CCAd::showDomobOfferWall()
	{
		;
	}

	void CCAd::show91OfferWall()
	{
		;
	}

	void CCAd::pushDianjoyAd()
	{	
		;
	}

	void CCAd::queryYoumiPoints()
	{
		;
	}

	void CCAd::queryDianjoyPoints()
	{
		;
	}

	void CCAd::queryImmobPoints()
	{
		;
	}

	void CCAd::queryTapjoyPoints()
	{
		;
	}

	void CCAd::queryDomobPoints()
	{
		;
	}

	void CCAd::query91Points()
	{
		;
	}

	void CCAd::updateYoumiPoints()
	{
		;
	}

	void CCAd::updateDianjoyPoints()
	{
		;
	}

	void CCAd::updateImmobPoints()
	{
		;
	}

	void CCAd::updateTapjoyPoints()
	{
		;
	}

	void CCAd::updateDomobPoints()
	{
		;
	}

	void CCAd::update91Points()
	{
		;
	}

	void CCAd::spendYoumiPoints(int amount)
	{
		;
	}

	void CCAd::spendDianjoyPoints(int amount)
	{
		;
	}

	void CCAd::spendImmobPoints(int amount)
	{
		;
	}

	void CCAd::spendTapjoyPoints(int amount)
	{
		;
	}

	void CCAd::spendDomobPoints(int amount)
	{
		;
	}

	void CCAd::spend91Points(int amount)
	{
		;
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

