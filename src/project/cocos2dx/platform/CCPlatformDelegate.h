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

#ifndef __PLATFORM_WIN32_CCPLATFORMDELEGATE_H__
#define __PLATFORM_WIN32_CCPLATFORMDELEGATE_H__

#include "platform/CCCommon.h"
#include <string>

namespace   cocos2d {

	/**
	@brief 
	The CCPlatformDelegate defines a single method for
	*/
	class CC_DLL CCPlatformDelegate
	{
	public:
		virtual void onLoginResultHandler(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
			, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "")
		{
		
		}
		virtual void onLogoutCallBack(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
			, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "")
		{

		}

		virtual void onPayResultCallBack(int sdkType, int resultCode, std::string param0 = "", std::string param1 = ""){

		}
	};

}//namespace cocos2d

#endif
