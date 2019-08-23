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
#include "CCSystem.h"
#include "Cocos2dEventTyper.h"
#include "CCDirector.h"
#include "ccMacros.h"
#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <Foundation/Foundation.h>
#import <Foundation/NSValue.h>
#import <UIKit/UIDevice.h>
#include <stdio.h>
#include <netdb.h>
#include <dlfcn.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if_dl.h>


namespace cocos2d
{
    CCSystem::CCSystem() : m_pDelegate(NULL)
    {
    }

    CCSystem::~CCSystem() 
    {

    }

    void CCSystem::setDelegate(CCSystemDelegate* pDelegate) 
    {
        m_pDelegate = pDelegate;
    }

	std::string CCSystem::getDeviceUUID()
	{
		double version = [[UIDevice currentDevice].systemVersion doubleValue];
		if (version >= 6.0f)
		{
			NSString* uniqueIdentifier = [[[UIDevice currentDevice] identifierForVendor] UUIDString];

			std::string UUID;
			UUID = [uniqueIdentifier UTF8String];
			return UUID;
		}
		
		return "";
	}

	std::string CCSystem::getDeviceIMEI()
	{
		return "";
	}

	std::string CCSystem::getDeviceMacAddr()
	{
		do 
		{
			int                 mib[6];
			size_t              len;
			char                *buf;
			unsigned char       *ptr;
			struct if_msghdr    *ifm;
			struct sockaddr_dl  *sdl;

			mib[0] = CTL_NET;
			mib[1] = AF_ROUTE;
			mib[2] = 0;
			mib[3] = AF_LINK;
			mib[4] = NET_RT_IFLIST;

			if ((mib[5] = if_nametoindex("en0")) == 0) {
				NSLog(@"Error: if_nametoindex error\n");
				break;
			}

			if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
				NSLog(@"Error: sysctl, take 1\n");
				break;
			}    
			if ((buf = (char*)malloc(len)) == NULL) {
				NSLog(@"Could not allocate memory. error!\n");
				break;
			}

			if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
				NSLog(@"Error: sysctl, take 2");
				free(buf);
				break;
			}

			ifm = (struct if_msghdr *)buf;
			sdl = (struct sockaddr_dl *)(ifm + 1);
			ptr = (unsigned char *)LLADDR(sdl);

			char buffer[1024] = "";
			sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
			free(buf);

			return buffer;
		} 
		while (false);

		return "";
	}

	void CCSystem::setSysLang(int lang)
	{
		
	}

	void CCSystem::showFeedbackDialog()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_SHOW_FEEDBACK_DIALOG_EVENT_NAME_ object:nil];
	}

	bool CCSystem::isNetworkAvailable()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		
		NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:0],@"isAvailable",nil];
		[center postNotificationName:_TYPED_COCOS2D_CHECK_NETWORK_EVENT_NAME_ object:nil userInfo:dict];
	
		NSNumber* num = [dict objectForKey:@"isAvailable"];
		return [num intValue]==1;
	}

	void CCSystem::openPengYou()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_SHOW_PENGYOU_DIALOG_EVENT_NAME_ object:nil];
	}

	void CCSystem::openMoreGame()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_SHOW_MOREGAME_EVENR_NAME_ object:nil];
	}

	void CCSystem::openURL(std::string url)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* textString = [NSString stringWithUTF8String:url.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"url"];
		[center postNotificationName:_TYPED_COCOS2D_OPEN_URL_EVENR_NAME_ object:nil userInfo:dict];
	}

	void CCSystem::openWebDialog(int type, std::string url)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSNumber* typeNumber = [NSNumber numberWithInt:type];
		NSString* textString = [NSString stringWithUTF8String:url.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:typeNumber,@"type",textString,@"url",nil];
		[center postNotificationName:_TYPED_COCOS2D_OPEN_WEBDIALOG_EVENR_NAME_ object:nil userInfo:dict];
	}

	void CCSystem::forceUpdate(std::string url)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSString* textString = [NSString stringWithUTF8String:url.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"url"];
		[center postNotificationName:_TYPED_COCOS2D_FORCE_UPDATE_EVENR_NAME_ object:nil userInfo:dict];
	}

	void CCSystem::onAppExit()
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onAppExit();
	}

	void CCSystem::onWebDialogClose(int type)
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onWebDialogClose(type);
	}

	void CCSystem::onNetworkChanged()
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onNetworkChanged();
	}

	void CCSystem::onNetworkDisConnected()
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onNetworkDisConnected();
	}

	void CCSystem::onQueryAppServerPushId(std::string pushId)
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onQueryAppServerPushId(pushId);
	}

} // end of namespace cococs2d

