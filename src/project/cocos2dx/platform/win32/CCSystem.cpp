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
#include <stdio.h>
#include <Windows.h>
#include <iptypes.h>
#include <iphlpapi.h>

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
		return "";
	}

	std::string CCSystem::getDeviceIMEI()
	{
		return "";
	}

	std::string CCSystem::getDeviceMacAddr()
	{
		// 获取本地的MAC地址
		IP_ADAPTER_INFO AdapterInfo[16];
		DWORD dwBufLen = sizeof(AdapterInfo);
		DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
		if (dwStatus != ERROR_SUCCESS)
			return "win32-unkown";

		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		char buffer[128] = "";
		sprintf(buffer, "%02X-%02X-%02X-%02X-%02X-%02X", 
			pAdapterInfo->Address[0], pAdapterInfo->Address[1], pAdapterInfo->Address[2], pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
		return buffer;
	}

	void CCSystem::setSysLang(int lang)
	{

	}

	void CCSystem::showFeedbackDialog()
	{
		
	}

	bool CCSystem::isNetworkAvailable()
	{
		return true;
	}

	void CCSystem::openPengYou()
	{

	}

	void CCSystem::openMoreGame()
	{

	}

	void CCSystem::openURL(std::string url)
	{
		::ShellExecute(NULL, NULL, url.c_str(), NULL, NULL, SW_SHOWNORMAL); 
	}

	void CCSystem::openWebDialog(int type, std::string url)
	{
		::ShellExecute(NULL, NULL, url.c_str(), NULL, NULL, SW_SHOWNORMAL); 
	}

	void CCSystem::forceUpdate(std::string url)
	{
		::ShellExecute(NULL, NULL, url.c_str(), NULL, NULL, SW_SHOWNORMAL); 
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

