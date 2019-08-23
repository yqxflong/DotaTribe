#include "CCImmovableMenu.h"
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
#include "CCImmovableMenu.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"
#include "cocoa/CCInteger.h"
#include <vector>
#include <stdarg.h>

using namespace std;

NS_CC_BEGIN

CCImmovableMenu::CCImmovableMenu()
{
	m_fXMoveLimitDiff = 10.0f;
	m_fYMoveLimitDiff = 10.0f;
}

CCImmovableMenu::~CCImmovableMenu()
{

}

// set x move limit diff
void CCImmovableMenu::setXMoveLimitDiff(float diff)
{
	m_fXMoveLimitDiff = diff;
}

// get x move limit diff
float CCImmovableMenu::getXMoveLimitDiff()
{
	return m_fXMoveLimitDiff;
}

// set y move limit diff
void CCImmovableMenu::setYMoveLimitDiff(float diff)
{
	m_fYMoveLimitDiff = diff;
}

// get y move limit diff
float CCImmovableMenu::getYMoveLimitDiff()
{
	return m_fYMoveLimitDiff;
}

CCMenu* CCImmovableMenu::create()
{
	return CCImmovableMenu::create(NULL, NULL);
}

CCMenu * CCImmovableMenu::create(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);

	CCMenu *pRet = CCImmovableMenu::createWithItems(item, args);

	va_end(args);

	return pRet;
}

CCMenu* CCImmovableMenu::createWithArray(CCArray* pArrayOfItems)
{
	CCMenu *pRet = new CCImmovableMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

CCMenu* CCImmovableMenu::createWithItems(CCMenuItem* item, va_list args)
{
	CCArray* pArray = NULL;
	if( item )
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	return CCImmovableMenu::createWithArray(pArray);
}

CCMenu* CCImmovableMenu::createWithItem(CCMenuItem* item)
{
	return CCImmovableMenu::create(item, NULL);
}

bool CCImmovableMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return CCMenu::ccTouchBegan(touch, event);
}

void CCImmovableMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CCMenu::ccTouchEnded(touch, event);
}

void CCImmovableMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CCMenu::ccTouchCancelled(touch, event);
}

void CCImmovableMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");

	CCPoint startPoint   = touch->getStartLocation();
	CCPoint currentPoint = touch->getLocation();
	if (fabs(startPoint.x-currentPoint.x) >= m_fXMoveLimitDiff)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}

		return;
	}

	if (fabs(startPoint.y-currentPoint.y) >= m_fYMoveLimitDiff)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}

		return;
	}

	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}
	}
}


NS_CC_END
