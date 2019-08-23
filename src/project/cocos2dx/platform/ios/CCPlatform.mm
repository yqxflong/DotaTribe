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
#include "CCPlatform.h"
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
    CCPlatform::CCPlatform() : m_pDelegate(NULL)
    {
    }

    CCPlatform::~CCPlatform() 
    {

    }

    void CCPlatform::setDelegate(CCPlatformDelegate* pDelegate) 
    {
        m_pDelegate = pDelegate;
    }

	void CCPlatform::login(bool isExpired)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSMutableDictionary* userinfo=[NSMutableDictionary dictionary];
        NSString* strExpired=[NSString stringWithFormat:@"%d",isExpired?1:0];
        [userinfo setValue:strExpired forKey:@"isExpired"];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_LOGIN_ object:nil userInfo:userinfo];
	}

	void CCPlatform::logout()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_LOGOUT_ object:nil];
	}

	void CCPlatform::ShowSDKCenter(){
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_SHOWCENTER_ object:nil];
	}

	void CCPlatform::ShowSuspendWindow(bool status)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
        NSMutableDictionary* userinfo=[NSMutableDictionary dictionary];
        [userinfo setValue:[NSString stringWithFormat:@"%d",status==true?1:0] forKey:@"status"];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_SHOWTOOLBAR_ object:nil userInfo:userinfo];
	}

	void CCPlatform::PayGoods(float price,std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
		, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9){
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
        NSMutableDictionary* userinfo=[NSMutableDictionary dictionary];
        [userinfo setValue:[NSString stringWithFormat:@"%f",price] forKey:@"price"];
        [userinfo setValue:[NSString stringWithUTF8String:param0.c_str()] forKey:@"param0"];
        [userinfo setValue:[NSString stringWithUTF8String:param1.c_str()] forKey:@"param1"];
        [userinfo setValue:[NSString stringWithUTF8String:param2.c_str()] forKey:@"param2"];
        [userinfo setValue:[NSString stringWithUTF8String:param3.c_str()] forKey:@"param3"];
        [userinfo setValue:[NSString stringWithUTF8String:param4.c_str()] forKey:@"param4"];
        [userinfo setValue:[NSString stringWithUTF8String:param5.c_str()] forKey:@"param5"];
        [userinfo setValue:[NSString stringWithUTF8String:param6.c_str()] forKey:@"param6"];
        [userinfo setValue:[NSString stringWithUTF8String:param7.c_str()] forKey:@"param7"];
        [userinfo setValue:[NSString stringWithUTF8String:param8.c_str()] forKey:@"param8"];
        [userinfo setValue:[NSString stringWithUTF8String:param9.c_str()] forKey:@"param9"];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_PAYGOODS_ object:nil userInfo:userinfo];
	}


	void CCPlatform::ShareTo_WeChat_PengYouQuan(std::string title,std::string description,std::string imgPath){
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		NSMutableDictionary* userinfo=[NSMutableDictionary dictionary];
		[userinfo setValue:[NSString stringWithUTF8String:title.c_str()] forKey:@"title"];
		[userinfo setValue:[NSString stringWithUTF8String:description.c_str()] forKey:@"description"];
		[userinfo setValue:[NSString stringWithUTF8String:imgPath.c_str()] forKey:@"imgPath"];
		[center postNotificationName:_TYPED_COCOS2D_PLATFORM_SHARETO_WECHAT_PENGYOUQUAN_ object:nil userInfo:userinfo];
	}

	void CCPlatform::SharePlayerAccountInfo(std::string serverName, std::string roleName, int serverId, int roleId, int roleLevel, int vipLevel)
	{
		
	}

	/*
		========================================Call Back====================================
	*/
	void CCPlatform::onLoginResultHandler(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
		, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onLoginResultHandler(sdkType, bSuccess, param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	}

	void CCPlatform::onLogoutCallBack(int sdkType, bool bSuccess,std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
                                      , std::string param5, std::string param6, std::string param7, std::string param8, std::string param9){
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onLogoutCallBack(sdkType, bSuccess, param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	}

	void CCPlatform::onPayResultCallBack(int sdkType, int resultCode, std::string param0,std::string param1){
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onPayResultCallBack(sdkType, resultCode, param0, param1);
	}

} // end of namespace cococs2d

