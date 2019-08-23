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
#ifndef __Java_org_cocos2dx_lib_Cocos2dxHelper_H__
#define __Java_org_cocos2dx_lib_Cocos2dxHelper_H__

#include <string>

typedef void (*EditTextCallback)(const char* pText, void* ctx);

extern const char * getApkPath();
extern const char * getAndroidUDID();
extern const char * getAndroidIMEI();
extern const char * getAndroidMacAddr();
extern void showDialogJNI(const char * pszMsg, const char * pszTitle);
extern void showEditTextDialogJNI(const char* pszTitle, const char* pszContent, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback, void* ctx);
extern void terminateProcessJNI();
extern std::string getCurrentLanguageJNI();
extern std::string getPackageNameJNI();
extern std::string getFileDirectoryJNI();
extern void enableAccelerometerJNI();
extern void disableAccelerometerJNI();
extern void setAccelerometerIntervalJNI(float interval);
// functions for CCUserDefault
extern bool getBoolForKeyJNI(const char* pKey, bool defaultValue);
extern int getIntegerForKeyJNI(const char* pKey, int defaultValue);
extern float getFloatForKeyJNI(const char* pKey, float defaultValue);
extern double getDoubleForKeyJNI(const char* pKey, double defaultValue);
extern std::string getStringForKeyJNI(const char* pKey, const char* defaultValue);
extern void setBoolForKeyJNI(const char* pKey, bool value);
extern void setIntegerForKeyJNI(const char* pKey, int value);
extern void setFloatForKeyJNI(const char* pKey, float value);
extern void setDoubleForKeyJNI(const char* pKey, double value);
extern void setStringForKeyJNI(const char* pKey, const char* value);

// functions for the thrid part
extern void enableAdJNI();
extern void disableAdJNI();

extern void showYoumiOfferWallJNI();
extern void showDianjoyOfferWallJNI();
extern void showImmobOfferWallJNI();
extern void showTapjoyOfferWallJNI();
extern void showDomobOfferWallJNI();
extern void show91OfferWallJNI();
extern void pushDianjoyAdJNI();

extern void queryYoumiPointsJNI();
extern void queryDianjoyPointsJNI();
extern void queryImmobPointsJNI();
extern void queryTapjoyPointsJNI();
extern void queryDomobPointsJNI();
extern void query91PointsJNI();

extern void updateYoumiPointsJNI();
extern void updateDianjoyPointsJNI();
extern void updateImmobPointsJNI();
extern void updateTapjoyPointsJNI();
extern void updateDomobPointsJNI();
extern void update91PointsJNI();

extern void spendYoumiPointsJNI(int amount);
extern void spendDianjoyPointsJNI(int amount);
extern void spendImmobPointsJNI(int amount);
extern void spendTapjoyPointsJNI(int amount);
extern void spendDomobPointsJNI(int amount);
extern void spend91PointsJNI(int amount);

extern void loginRennJNI();
extern void shareTextInRennJNI(const char * pText);
extern void sharePictureInRennJNI(const char * pFile, const char * pText);
extern void loginWeiboJNI();
extern void shareTextInWeiboJNI(const char * pText);
extern void sharePictureInWeiboJNI(const char * pFile, const char * pText);
extern void loginQQJNI();
extern void shareTextInQQJNI(const char * pText);
extern void sharePictureInQQJNI(const char * pFile, const char * pText);
extern void loginFacebookJNI();
extern void shareTextInFacebookJNI(const char * pText);
extern void sharePictureInFacebookJNI(const char * pFile, const char * pText);
extern void loginTwitterJNI();
extern void shareTextInTwitterJNI(const char * pText);
extern void sharePictureInTwitterJNI(const char * pFile, const char * pText);

extern void payJNI(const char * pProductId, const char * pProductName, const char * pProductDesc, float productMoney, int chargePoint, const char * pIAPId);
extern void verifyJNI(const char * pIAPId);

extern void setSysLangJNI(int type);
extern void openPengYouJNI();
extern void openMoreGameJNI();
extern void openURLJNI(const char* pURL);
extern void openWebDialogJNI(int type, const char* pURL);
extern void forceUpdateJNI(const char* pURL);

extern void androidAppExitJNI();

extern void behaviorLogEventJNI(const char* pEventId, const char* pText);
extern void behaviorLogEventWithLabelJNI(const char* pEventId, const char* pText, const char* pLable);
extern void behaviorBeginLogEventJNI(const char* pEventId, const char* pText);
extern void behaviorEndLogEventJNI(const char* pEventId, const char* pText);

extern void showFeedbackDialogJNI();

extern void isGameCenterAvailableJNI();
extern void authenticateGameCenterJNI();
extern void showLeaderBoardJNI(const char* pCategory);
extern void reportGameScoreJNI(const char* pCategory, long long score);
extern void submitAchievementJNI(const char* pIdentifier, double percentComplete);

extern void loginJNI(bool isExpired);
extern void logoutJNI();

extern void companyLogoFinishedJNI();

extern void ShowSDKCenterJNI();
extern void ShowSuspendWindowJNI(bool status);
extern void PayGoodsJNI(float price,const char * param0, const char *  param1, const char *  param2, const char *  param3, const char *  param4, const char *  param5, const char *  param6, const char *  param7, const char *  param8, const char *  param9);

extern void SharePlayerAccountInfoJNI(const char * serverName, const char * roleName, int serverId, int roleId, int roleLevel, int vipLevel);

#endif /* __Java_org_cocos2dx_lib_Cocos2dxHelper_H__ */
