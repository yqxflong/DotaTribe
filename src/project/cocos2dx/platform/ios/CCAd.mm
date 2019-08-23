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
#include "Cocos2dEventTyper.h"
#include "CCDirector.h"
#include "ccMacros.h"
#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <Foundation/Foundation.h>
#import <Foundation/NSValue.h>
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
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		if (bShow)
		{
			 [center postNotificationName:_TYPED_COCOS2D_SHOW_AD_EVENT_NAME_ object:nil];
			 return;
		}
	
		[center postNotificationName:_TYPED_COCOS2D_HIDE_AD_EVENT_NAME_ object:nil];
	}

	void CCAd::showYoumiOfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_YOUMI_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::showDianjoyOfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_DIANJOY_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::showImmobOfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_IMMOB_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::showTapjoyOfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_TAPJOY_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::showDomobOfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_DOMOB_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::show91OfferWall()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SHOW_91_OFFERWALL_EVENT_NAME_ object:nil];
	}

	void CCAd::queryYoumiPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_YOUMI_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::queryDianjoyPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_DIANJOY_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::queryImmobPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_IMMOB_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::queryTapjoyPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_TAPJOY_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::queryDomobPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_DOMOB_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::query91Points()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_QUERY_91_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::updateYoumiPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_YOUMI_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::updateDianjoyPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_DIANJOY_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::updateImmobPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_IMMOB_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::updateTapjoyPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_TAPJOY_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::updateDomobPoints()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_DOMOB_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::update91Points()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_UPDATE_91_POINTS_EVENT_NAME_ object:nil];
	}

	void CCAd::spendYoumiPoints(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_YOUMI_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
	}

	void CCAd::spendDianjoyPoints(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_DIANJOY_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
	}

	void CCAd::spendImmobPoints(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_IMMOB_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
	}

	void CCAd::spendTapjoyPoints(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_TAPJOY_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
	}

	void CCAd::spendDomobPoints(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_DOMOB_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
	}

	void CCAd::spend91Points(int amount)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
//		[center postNotificationName:_TYPED_COCOS2D_SPEND_91_POINTS_EVENT_NAME_ object:[NSNumber numberWithInt:amount]];
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

