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
#include "CCSNS.h"
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
    CCSNS::CCSNS() : m_pSNSDelegate(NULL)
    {
    }

    CCSNS::~CCSNS() 
    {

    }

    void CCSNS::setDelegate(CCSNSDelegate* pDelegate) 
    {
        m_pSNSDelegate = pDelegate;
    }

	void CCSNS::loginRenn()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	}

	void CCSNS::shareTextInRenn(std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"shareText"];
	}

	void CCSNS::sharePictureInRenn(std::string file, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* fileString = [NSString stringWithUTF8String:file.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:textString,@"shareText",fileString,@"shareFileName",nil];
	}

	void CCSNS::loginWeibo()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	}

	void CCSNS::shareTextInWeibo(std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"shareText"];
	}

	void CCSNS::sharePictureInWeibo(std::string file, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* fileString = [NSString stringWithUTF8String:file.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:textString,@"shareText",fileString,@"shareFileName",nil];
	}

	void CCSNS::loginQQ()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	}

	void CCSNS::shareTextInQQ(std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"shareText"];
	}

	void CCSNS::sharePictureInQQ(std::string file, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* fileString = [NSString stringWithUTF8String:file.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:textString,@"shareText",fileString,@"shareFileName",nil];
	}

	void CCSNS::loginFacebook()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	}

	void CCSNS::shareTextInFacebook(std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"shareText"];
	}

	void CCSNS::sharePictureInFacebook(std::string file, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* fileString = [NSString stringWithUTF8String:file.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:textString,@"shareText",fileString,@"shareFileName",nil];
	}

	void CCSNS::loginTwitter()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	}

	void CCSNS::shareTextInTwitter(std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"shareText"];
	}

	void CCSNS::sharePictureInTwitter(std::string file, std::string text)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:text.c_str()];
		NSString* fileString = [NSString stringWithUTF8String:file.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:textString,@"shareText",fileString,@"shareFileName",nil];
	}

	void CCSNS::onLoginRennSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginRennSuccess();
	}

	void CCSNS::onLoginRennFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginRennFailed(error);
	}

	void CCSNS::onShareTextInRennSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInRennSuccess();
	}

	void CCSNS::onShareTextInRennFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInRennFailed(error);
	}

	void CCSNS::onSharePictureInRennSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInRennSuccess();
	}

	void CCSNS::onSharePictureInRennFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInRennFailed(error);
	}

	void CCSNS::onLoginWeiboSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginWeiboSuccess();
	}

	void CCSNS::onLoginWeiboFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginWeiboFailed(error);
	}

	void CCSNS::onShareTextInWeiboSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInWeiboSuccess();
	}

	void CCSNS::onShareTextInWeiboFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInWeiboFailed(error);
	}

	void CCSNS::onSharePictureInWeiboSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInWeiboSuccess();
	}

	void CCSNS::onSharePictureInWeiboFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInWeiboFailed(error);
	}

	void CCSNS::onLoginQQSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginQQSuccess();
	}

	void CCSNS::onLoginQQFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginQQFailed(error);
	}

	void CCSNS::onShareTextInQQSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInQQSuccess();
	}

	void CCSNS::onShareTextInQQFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInQQFailed(error);
	}

	void CCSNS::onSharePictureInQQSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInQQSuccess();
	}

	void CCSNS::onSharePictureInQQFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInQQFailed(error);
	}

	void CCSNS::onLoginFacebookSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginFacebookSuccess();
	}

	void CCSNS::onLoginFacebookFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginFacebookFailed(error);
	}

	void CCSNS::onShareTextInFacebookSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInFacebookSuccess();
	}

	void CCSNS::onShareTextInFacebookFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInFacebookFailed(error);
	}

	void CCSNS::onSharePictureInFacebookSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInFacebookSuccess();
	}

	void CCSNS::onSharePictureInFacebookFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInFacebookFailed(error);
	}

	void CCSNS::onLoginTwitterSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginTwitterSuccess();
	}

	void CCSNS::onLoginTwitterFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onLoginTwitterFailed(error);
	}

	void CCSNS::onShareTextInTwitterSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInTwitterSuccess();
	}

	void CCSNS::onShareTextInTwitterFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onShareTextInTwitterFailed(error);
	}

	void CCSNS::onSharePictureInTwitterSuccess()
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInTwitterSuccess();
	}

	void CCSNS::onSharePictureInTwitterFailed(std::string error)
	{
		if (m_pSNSDelegate == NULL)
			return;

		m_pSNSDelegate->onSharePictureInTwitterFailed(error);
	}
} // end of namespace cococs2d

