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
#include "CCBehavior.h"
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
	CCBehavior::CCBehavior()
	{

	}

	CCBehavior::~CCBehavior()
	{

	}

	void CCBehavior::logEvent(std::string eventId, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* idString = [NSString stringWithUTF8String:eventId.c_str()];
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:idString,@"EventId",textString,@"Text",nil];
		[center postNotificationName:_TYPED_COCOS2D_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCBehavior::logEvent(std::string eventId, std::string text, std::string label)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* idString = [NSString stringWithUTF8String:eventId.c_str()];
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* labelString = [NSString stringWithUTF8String:label.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:idString,@"EventId",textString,@"Text",labelString,@"Label",nil];
		[center postNotificationName:_TYPED_COCOS2D_LOG_PLAYER_BEHAVIOR_EVENT_NAME_WITH_LABEL_ object:nil userInfo:dict];
	}

	void CCBehavior::beginEvent(std::string eventId, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* idString = [NSString stringWithUTF8String:eventId.c_str()];
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:idString,@"EventId",textString,@"Text",nil];
		[center postNotificationName:_TYPED_COCOS2D_BEGIN_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCBehavior::endEvent(std::string eventId, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* idString = [NSString stringWithUTF8String:eventId.c_str()];
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:idString,@"EventId",textString,@"Text",nil];
		[center postNotificationName:_TYPED_COCOS2D_END_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil userInfo:dict];
	}	

} // end of namespace cococs2d

