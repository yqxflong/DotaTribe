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
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
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
		loginRennJNI();
	}

	void CCSNS::shareTextInRenn(std::string text)
	{
		shareTextInRennJNI(text.c_str());
	}

	void CCSNS::sharePictureInRenn(std::string file, std::string text)
	{
		sharePictureInRennJNI(file.c_str(), text.c_str());
	}

	void CCSNS::loginWeibo()
	{
		loginWeiboJNI();
	}

	void CCSNS::shareTextInWeibo(std::string text)
	{
		shareTextInWeiboJNI(text.c_str());
	}

	void CCSNS::sharePictureInWeibo(std::string file, std::string text)
	{
		sharePictureInWeiboJNI(file.c_str(), text.c_str());
	}

	void CCSNS::loginQQ()
	{
		loginQQJNI();
	}

	void CCSNS::shareTextInQQ(std::string text)
	{
		shareTextInQQJNI(text.c_str());
	}

	void CCSNS::sharePictureInQQ(std::string file, std::string text)
	{
		sharePictureInQQJNI(file.c_str(), text.c_str());
	}

	void CCSNS::loginFacebook()
	{
		loginFacebookJNI();
	}

	void CCSNS::shareTextInFacebook(std::string text)
	{
		shareTextInFacebookJNI(text.c_str());
	}

	void CCSNS::sharePictureInFacebook(std::string file, std::string text)
	{
		sharePictureInFacebookJNI(file.c_str(), text.c_str());
	}

	void CCSNS::loginTwitter()
	{
		loginTwitterJNI();
	}

	void CCSNS::shareTextInTwitter(std::string text)
	{
		shareTextInTwitterJNI(text.c_str());
	}

	void CCSNS::sharePictureInTwitter(std::string file, std::string text)
	{
		sharePictureInTwitterJNI(file.c_str(), text.c_str());
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

