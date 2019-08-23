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

#ifndef __CCSNS_DELEGATE_H__
#define __CCSNS_DELEGATE_H__

#include "CCCommon.h"
#include <string>
#include <map>
#include <vector>

NS_CC_BEGIN

/**
@brief 
The CCSNSDelegate defines a single method for
*/
class CC_DLL CCSNSDelegate
{
public:
	virtual void onLoginRennSuccess(){}
	virtual void onLoginRennFailed(std::string error){}
	virtual void onShareTextInRennSuccess(){}
	virtual void onShareTextInRennFailed(std::string error){}
	virtual void onSharePictureInRennSuccess(){}
	virtual void onSharePictureInRennFailed(std::string error){}

public:
	virtual void onLoginWeiboSuccess(){}
	virtual void onLoginWeiboFailed(std::string error){}
	virtual void onShareTextInWeiboSuccess(){}
	virtual void onShareTextInWeiboFailed(std::string error){}
	virtual void onSharePictureInWeiboSuccess(){}
	virtual void onSharePictureInWeiboFailed(std::string error){}

public:
	virtual void onLoginQQSuccess(){}
	virtual void onLoginQQFailed(std::string error){}
	virtual void onShareTextInQQSuccess(){}
	virtual void onShareTextInQQFailed(std::string error){}
	virtual void onSharePictureInQQSuccess(){}
	virtual void onSharePictureInQQFailed(std::string error){}

public:
	virtual void onLoginFacebookSuccess(){}
	virtual void onLoginFacebookFailed(std::string error){}
	virtual void onShareTextInFacebookSuccess(){}
	virtual void onShareTextInFacebookFailed(std::string error){}
	virtual void onSharePictureInFacebookSuccess(){}
	virtual void onSharePictureInFacebookFailed(std::string error){}

public:
	virtual void onLoginTwitterSuccess(){}
	virtual void onLoginTwitterFailed(std::string error){}
	virtual void onShareTextInTwitterSuccess(){}
	virtual void onShareTextInTwitterFailed(std::string error){}
	virtual void onSharePictureInTwitterSuccess(){}
	virtual void onSharePictureInTwitterFailed(std::string error){}
};

NS_CC_END

#endif
