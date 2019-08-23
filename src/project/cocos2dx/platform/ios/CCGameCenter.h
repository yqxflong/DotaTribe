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

#ifndef __PLATFORM_IOS_CCGAMECENTER_H__
#define __PLATFORM_IOS_CCGAMECENTER_H__

#include "platform/CCCommon.h"
#include "platform/CCGameCenterDelegate.h"
#include <string>

namespace   cocos2d {

	class CC_DLL CCGameCenter
	{
	public:
		CCGameCenterDelegate* m_pGameCenterDelegate;

	public:
		CCGameCenter();
		~CCGameCenter();

	public:
		void setDelegate(CCGameCenterDelegate* pDelegate);

	public:
		bool isAvailable();

	public:
		void authenticate();

	public:
		void showLeaderBoard(std::string category);
		void reportGameScore(std::string category, long long score);
		void submitAchievement(std::string identifier, double percentComplete);

	public:
		virtual void onAuthenticateUserSucceed();
		virtual void onAuthenticateUserFailed(std::string error);
        
		virtual void onReportScoreSucceed();
		virtual void onReportScoreFailed(std::string error);
        
		virtual void onSubmitAchievementSucceed();
		virtual void onSubmitAchievementFailed(std::string error);
        
		virtual void onCloseLeaderboard();
		virtual void onCloseAchievementsView();
	};

}//namespace cocos2d

#endif
