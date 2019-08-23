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
#include "CCGameCenter.h"
#include <stdio.h>


namespace cocos2d
{
	CCGameCenter::CCGameCenter()
	{
		m_pGameCenterDelegate = NULL;
	}

	CCGameCenter::~CCGameCenter() 
	{

	}

	void CCGameCenter::setDelegate(CCGameCenterDelegate* pDelegate)
	{
		m_pGameCenterDelegate = pDelegate;
	}

	bool CCGameCenter::isAvailable()
	{
		return true;
	}

	void CCGameCenter::authenticate()
	{

	}

	void CCGameCenter::showLeaderBoard(std::string category)
	{

	}

	void CCGameCenter::reportGameScore(std::string category, long long score)
	{

	}

	void CCGameCenter::submitAchievement(std::string identifier, double percentComplete)
	{

	}

	void CCGameCenter::onAuthenticateUserSucceed()
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onAuthenticateUserSucceed();
	}

	void CCGameCenter::onAuthenticateUserFailed(std::string error)
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onAuthenticateUserFailed(error);
	}
        
	void CCGameCenter::onReportScoreSucceed()
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onReportScoreSucceed();
	}

	void CCGameCenter::onReportScoreFailed(std::string error)
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onReportScoreFailed(error);
	}
        
	void CCGameCenter::onSubmitAchievementSucceed()
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onSubmitAchievementSucceed();
	}

	void CCGameCenter::onSubmitAchievementFailed(std::string error)
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onSubmitAchievementFailed(error);
	}
        
	void CCGameCenter::onCloseLeaderboard()
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onCloseLeaderboard();
	}

	void CCGameCenter::onCloseAchievementsView()
	{
		if (m_pGameCenterDelegate == NULL)
			return;

		m_pGameCenterDelegate->onCloseAchievementsView();
	}

} // end of namespace cococs2d

