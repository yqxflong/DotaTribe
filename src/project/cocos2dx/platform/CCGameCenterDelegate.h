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

#ifndef __CCGAMECENTER_DELEGATE_H__
#define __CCGAMECENTER_DELEGATE_H__

#include "CCCommon.h"
#include <string>
#include <map>
#include <vector>

NS_CC_BEGIN

/**
@brief 
The CCGameCenterDelegate defines a single method for
*/
class CC_DLL CCGameCenterDelegate
{
public:
    virtual void onAuthenticateUserSucceed(){};
    virtual void onAuthenticateUserFailed(std::string error){};
        
    virtual void onReportScoreSucceed(){};
    virtual void onReportScoreFailed(std::string error){};
        
    virtual void onSubmitAchievementSucceed(){};
    virtual void onSubmitAchievementFailed(std::string error){};
        
    virtual void onCloseLeaderboard(){};
    virtual void onCloseAchievementsView(){};
};

NS_CC_END

#endif
