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

#ifndef __PLATFORM_WIN32_CCSYSTEM_H__
#define __PLATFORM_WIN32_CCSYSTEM_H__

#include "platform/CCCommon.h"
#include "platform/CCSystemDelegate.h"
#include <string>

namespace   cocos2d {

class CC_DLL CCSystem
{
private:
	CCSystemDelegate* m_pDelegate;

public:
    CCSystem();
    ~CCSystem();

public:
    void setDelegate(CCSystemDelegate* pDelegate);

public:
	bool isNetworkAvailable();

public:
	std::string getDeviceUUID();
	std::string getDeviceIMEI();
	std::string getDeviceMacAddr();

public:
	void setSysLang(int lang);
	void showFeedbackDialog();
	void openPengYou();
	void openMoreGame();
	void openURL(std::string url);
	void openWebDialog(int type, std::string url);

public:
	void forceUpdate(std::string url);

public:
	void onAppExit();
	void onWebDialogClose(int type);
	void onNetworkChanged();
	void onNetworkDisConnected();
	void onQueryAppServerPushId(std::string pushId);
};

}//namespace cocos2d

#endif
