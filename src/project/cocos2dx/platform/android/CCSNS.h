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

#ifndef __PLATFORM_ANDROID_CCSNS_H__
#define __PLATFORM_ANDROID_CCSNS_H__

#include "platform/CCCommon.h"
#include "platform/CCSNSDelegate.h"

namespace   cocos2d {

class CC_DLL CCSNS
{
private:
	CCSNSDelegate* m_pSNSDelegate;

public:
    CCSNS();
    ~CCSNS();

public:
    void setDelegate(CCSNSDelegate* pDelegate);

public:
	void loginRenn();
	void shareTextInRenn(std::string text);
	void sharePictureInRenn(std::string file, std::string text);
	void loginWeibo();
	void shareTextInWeibo(std::string text);
	void sharePictureInWeibo(std::string file, std::string text);
	void loginQQ();
	void shareTextInQQ(std::string text);
	void sharePictureInQQ(std::string file, std::string text);
	void loginFacebook();
	void shareTextInFacebook(std::string text);
	void sharePictureInFacebook(std::string file, std::string text);
	void loginTwitter();
	void shareTextInTwitter(std::string text);
	void sharePictureInTwitter(std::string file, std::string text);

public:
	void onLoginRennSuccess();
	void onLoginRennFailed(std::string error);
	void onShareTextInRennSuccess();
	void onShareTextInRennFailed(std::string error);
	void onSharePictureInRennSuccess();
	void onSharePictureInRennFailed(std::string error);

public:
	void onLoginWeiboSuccess();
	void onLoginWeiboFailed(std::string error);
	void onShareTextInWeiboSuccess();
	void onShareTextInWeiboFailed(std::string error);
	void onSharePictureInWeiboSuccess();
	void onSharePictureInWeiboFailed(std::string error);

public:
	void onLoginQQSuccess();
	void onLoginQQFailed(std::string error);
	void onShareTextInQQSuccess();
	void onShareTextInQQFailed(std::string error);
	void onSharePictureInQQSuccess();
	void onSharePictureInQQFailed(std::string error);

public:
	void onLoginFacebookSuccess();
	void onLoginFacebookFailed(std::string error);
	void onShareTextInFacebookSuccess();
	void onShareTextInFacebookFailed(std::string error);
	void onSharePictureInFacebookSuccess();
	void onSharePictureInFacebookFailed(std::string error);

public:
	void onLoginTwitterSuccess();
	void onLoginTwitterFailed(std::string error);
	void onShareTextInTwitterSuccess();
	void onShareTextInTwitterFailed(std::string error);
	void onSharePictureInTwitterSuccess();
	void onSharePictureInTwitterFailed(std::string error);
};

}//namespace cocos2d

#endif
