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
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
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
		loginJNI(isExpired);
	}

	void CCPlatform::logout()
	{
		logoutJNI();
	}
	
	void CCPlatform::companyLogoFinished()
	{
		companyLogoFinishedJNI();
	}

	void CCPlatform::ShowSDKCenter()
	{
		ShowSDKCenterJNI();
	}

	void CCPlatform::ShowSuspendWindow(bool status)
	{
		ShowSuspendWindowJNI(status);
	}

	void CCPlatform::PayGoods(float price,std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
		, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
	{
		PayGoodsJNI(price, param0.c_str(), param1.c_str(), param2.c_str(), param3.c_str(), param4.c_str(), param5.c_str(), param6.c_str(), param7.c_str(), param8.c_str(), param9.c_str());
	}

	void CCPlatform::ShareTo_WeChat_PengYouQuan(std::string title,std::string description,std::string imgPath){
		;
	}

	void CCPlatform::SharePlayerAccountInfo(std::string serverName, std::string roleName, int serverId, int roleId, int roleLevel, int vipLevel)
	{
		SharePlayerAccountInfoJNI(serverName.c_str(), roleName.c_str(), serverId, roleId, roleLevel, vipLevel);
	}

	/*
		=================================Call Back===========================
	*/
	void CCPlatform::onLoginResultHandler(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
		, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
	{
		if (m_pDelegate == NULL)
			return;

		m_pDelegate->onLoginResultHandler(sdkType, bSuccess, param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	}

	void CCPlatform::onLogoutCallBack(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
		, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
	{
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

