#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "cocoa/CCString.h"
#include "Java_org_cocos2dx_lib_Cocos2dxHelper.h"


#define  LOG_TAG    "Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

static EditTextCallback s_pfEditTextCallback = NULL;
static void* s_ctx = NULL;

using namespace cocos2d;
using namespace std;

string g_apkPath;
string g_AndroidUDID;
string g_AndroidIMEI;
string g_AndroidMacAddr;

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(JNIEnv*  env, jobject thiz, jstring apkPath) {
        g_apkPath = JniHelper::jstring2string(apkPath);
    }

	void Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetAndroidUDID(JNIEnv*  env, jobject thiz, jstring udid) {
		g_AndroidUDID = JniHelper::jstring2string(udid);
	}

	void Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetAndroidIMEI(JNIEnv*  env, jobject thiz, jstring imei) {
		g_AndroidIMEI = JniHelper::jstring2string(imei);
	}

	void Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetAndroidMacAddr(JNIEnv*  env, jobject thiz, jstring addr) {
		g_AndroidMacAddr = JniHelper::jstring2string(addr);
	}

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jobject obj, jbyteArray text) {
        jsize  size = env->GetArrayLength(text);

        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* pBuf = (char*)malloc(size+1);
            if (pBuf != NULL) {
                memcpy(pBuf, data, size);
                pBuf[size] = '\0';
                // pass data to edittext's delegate
                if (s_pfEditTextCallback) s_pfEditTextCallback(pBuf, s_ctx);
                free(pBuf);
            }
            env->ReleaseByteArrayElements(text, data, 0);
        } else {
            if (s_pfEditTextCallback) s_pfEditTextCallback("", s_ctx);
        }
    }

}

const char * getApkPath() {
    return g_apkPath.c_str();
}

const char * getAndroidUDID() {
	return g_AndroidUDID.c_str();
}

const char * getAndroidIMEI() {
	return g_AndroidIMEI.c_str();
}

const char * getAndroidMacAddr() {
	return g_AndroidMacAddr.c_str();
}

void showDialogJNI(const char * pszMsg, const char * pszTitle) {
    if (!pszMsg) {
        return;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMsg);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void showEditTextDialogJNI(const char* pszTitle, const char* pszMessage, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback, void* ctx) {
    if (pszMessage == NULL) {
        return;
    }

    s_pfEditTextCallback = pfEditTextCallback;
    s_ctx = ctx;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showEditTextDialog", "(Ljava/lang/String;Ljava/lang/String;IIII)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMessage);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, nInputMode, nInputFlag, nReturnType, nMaxLength);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void terminateProcessJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "terminateProcess", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string getPackageNameJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxPackageName", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}

std::string getFileDirectoryJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxWritablePath", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    return ret;
}

std::string getCurrentLanguageJNI() {
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    return ret;
}

void enableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setAccelerometerIntervalJNI(float interval) {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setAccelerometerInterval", "(F)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, interval);
        t.env->DeleteLocalRef(t.classID);
    }
}

void disableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

// functions for CCUserDefault
bool getBoolForKeyJNI(const char* pKey, bool defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBoolForKey", "(Ljava/lang/String;Z)Z")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

int getIntegerForKeyJNI(const char* pKey, int defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getIntegerForKey", "(Ljava/lang/String;I)I")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

float getFloatForKeyJNI(const char* pKey, float defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getFloatForKey", "(Ljava/lang/String;F)F")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jfloat ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

double getDoubleForKeyJNI(const char* pKey, double defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDoubleForKey", "(Ljava/lang/String;D)D")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jdouble ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, stringArg);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

std::string getStringForKeyJNI(const char* pKey, const char* defaultValue)
{
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getStringForKey", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(defaultValue);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, stringArg2);
        ret = JniHelper::jstring2string(str);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(str);
        
        return ret;
    }
    
    return defaultValue;
}

void setBoolForKeyJNI(const char* pKey, bool value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBoolForKey", "(Ljava/lang/String;Z)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setIntegerForKeyJNI(const char* pKey, int value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setIntegerForKey", "(Ljava/lang/String;I)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setFloatForKeyJNI(const char* pKey, float value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFloatForKey", "(Ljava/lang/String;F)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setDoubleForKeyJNI(const char* pKey, double value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDoubleForKey", "(Ljava/lang/String;D)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setStringForKeyJNI(const char* pKey, const char* value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setStringForKey", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
    }
}

void enableAdJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAd", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void disableAdJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAd", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showYoumiOfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showYoumiOfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showDianjoyOfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDianjoyOfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showImmobOfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showImmobOfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showTapjoyOfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showTapjoyOfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showDomobOfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDomobOfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void show91OfferWallJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "show91OfferWall", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void pushDianjoyAdJNI()
{

}

void queryYoumiPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "queryYoumiPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void queryDianjoyPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "queryDianjoyPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void queryImmobPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "queryImmobPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void queryTapjoyPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "queryTapjoyPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void queryDomobPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "queryDomobPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void query91PointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "query91Points", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void updateYoumiPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateYoumiPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void updateDianjoyPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateDianjoyPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void updateImmobPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateImmobPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void updateTapjoyPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateTapjoyPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void updateDomobPointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateDomobPoints", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void update91PointsJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "update91Points", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spendYoumiPointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spendYoumiPoints", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spendDianjoyPointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spendDianjoyPoints", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spendImmobPointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spendImmobPoints", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spendTapjoyPointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spendTapjoyPoints", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spendDomobPointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spendDomobPoints", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void spend91PointsJNI(int amount)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "spend91Points", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, amount);
		t.env->DeleteLocalRef(t.classID);
	}
}

void loginRennJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginRenn", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void shareTextInRennJNI(const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "shareTextInRenn", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void sharePictureInRennJNI(const char * pFile, const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePictureInRenn", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pFile);
		jstring stringArg2;
		stringArg2 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void loginWeiboJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginWeibo", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void shareTextInWeiboJNI(const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "shareTextInWeibo", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void sharePictureInWeiboJNI(const char * pFile, const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePictureInWeibo", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pFile);
		jstring stringArg2;
		stringArg2 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void loginQQJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginQQ", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void shareTextInQQJNI(const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "shareTextInQQ", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void sharePictureInQQJNI(const char * pFile, const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePictureInQQ", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pFile);
		jstring stringArg2;
		stringArg2 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void loginFacebookJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginFacebook", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void shareTextInFacebookJNI(const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "shareTextInFacebook", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void sharePictureInFacebookJNI(const char * pFile, const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePictureInFacebook", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pFile);
		jstring stringArg2;
		stringArg2 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void loginTwitterJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginTwitter", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void shareTextInTwitterJNI(const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "shareTextInTwitter", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void sharePictureInTwitterJNI(const char * pFile, const char * pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePictureInTwitter", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pFile);
		jstring stringArg2;
		stringArg2 = t.env->NewStringUTF(pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void payJNI(const char * pProductId, const char * pProductName, const char * pProductDesc, float productMoney, int chargePoint, const char * pIAPId)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "pay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)V")) {
		jstring stringArg1;
		jstring stringArg2;
		jstring stringArg3;
		jstring stringArg4;
		stringArg1 = t.env->NewStringUTF(pProductId);
		stringArg2 = t.env->NewStringUTF(pProductName);
		stringArg3 = t.env->NewStringUTF(pProductDesc);
		stringArg4 = t.env->NewStringUTF(pIAPId);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, stringArg3, stringArg4, productMoney, chargePoint, 0);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(stringArg3);
		t.env->DeleteLocalRef(stringArg4);
		t.env->DeleteLocalRef(t.classID);
	}
}

void verifyJNI(const char * pIAPId)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "verify", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pIAPId);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void openURLJNI(const char* pURL)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openURL", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pURL);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void forceUpdateJNI(const char* pURL)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "forceUpdate", "(Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pURL);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void androidAppExitJNI()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "androidAppExit", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void setSysLangJNI(int type)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setSysLang", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, type);
		t.env->DeleteLocalRef(t.classID);
	}
}

void openPengYouJNI()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openPengYou", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void openMoreGameJNI()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openMoreGame", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void openWebDialogJNI(int type, const char* pURL)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openWebDialog", "(Ljava/lang/String;I)V")) {
		jstring stringArg1;
		stringArg1 = t.env->NewStringUTF(pURL);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, type);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void behaviorLogEventJNI(const char* pEventId, const char* pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "behaviorLogEvent", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		//stringArg1 = t.env->NewStringUTF(pEventId);
		stringArg1 = JniHelper::newUTFString(t, pEventId);
		jstring stringArg2;
		//stringArg2 = t.env->NewStringUTF(pText);
		stringArg2 = JniHelper::newUTFString(t, pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void behaviorLogEventWithLabelJNI(const char* pEventId, const char* pText, const char* pLable)
{
	JniMethodInfo t;
	LOGD("behavior pEventId:%s, pText:%s, pLabel:%s", pEventId, pText, pLable);
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "behaviorLogEventWithLabel", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		stringArg1 = JniHelper::newUTFString(t, pEventId);
		jstring stringArg2;
		stringArg2 = JniHelper::newUTFString(t, pText);
		jstring stringArg3;
		stringArg3 = JniHelper::newUTFString(t, pLable);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, stringArg3);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(stringArg3);
		t.env->DeleteLocalRef(t.classID);
	}
}

void behaviorBeginLogEventJNI(const char* pEventId, const char* pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "behaviorBeginLogEvent", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		//stringArg1 = t.env->NewStringUTF(pEventId);
		stringArg1 = JniHelper::newUTFString(t, pEventId);
		jstring stringArg2;
		//stringArg2 = t.env->NewStringUTF(pText);
		stringArg2 = JniHelper::newUTFString(t, pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void behaviorEndLogEventJNI(const char* pEventId, const char* pText)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "behaviorEndLogEvent", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringArg1;
		//stringArg1 = t.env->NewStringUTF(pEventId);
		stringArg1 = JniHelper::newUTFString(t, pEventId);
		jstring stringArg2;
		//stringArg2 = t.env->NewStringUTF(pText);
		stringArg2 = JniHelper::newUTFString(t, pText);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showFeedbackDialogJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showFeedbackDialog", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void isGameCenterAvailableJNI()
{

}

void authenticateGameCenterJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "authenticateGameCenter", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void showLeaderBoardJNI(const char* pCategory)
{

}

void reportGameScoreJNI(const char* pCategory, long long score)
{

}

void submitAchievementJNI(const char* pIdentifier, double percentComplete)
{

}

void loginJNI(bool isExpired)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginPlatform", "(Z)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, isExpired);
		t.env->DeleteLocalRef(t.classID);
	}
}

void logoutJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "logoutPlatform", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void companyLogoFinishedJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "companyLogoFinished", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ShowSDKCenterJNI()
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showSDKCenter", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ShowSuspendWindowJNI(bool status)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showSuspendWindow", "(Z)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, status);
		t.env->DeleteLocalRef(t.classID);
	}
}

void PayGoodsJNI(float price,const char * param0, const char *  param1, const char *  param2, const char *  param3, const char *  param4, const char *  param5, const char *  param6, const char *  param7, const char *  param8, const char *  param9)
{

	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "payGoods", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;F)V")) {
		
		jstring stringArg0;
		stringArg0 = JniHelper::newUTFString(t, param0);
		jstring stringArg1;
		stringArg1 = JniHelper::newUTFString(t, param1);
		jstring stringArg2;
		stringArg2 = JniHelper::newUTFString(t, param2);
		jstring stringArg3;
		stringArg3 = JniHelper::newUTFString(t, param3);
		jstring stringArg4;
		stringArg4 = JniHelper::newUTFString(t, param4);
		jstring stringArg5;
		stringArg5 = JniHelper::newUTFString(t, param5);
		jstring stringArg6;
		stringArg6 = JniHelper::newUTFString(t, param6);
		jstring stringArg7;
		stringArg7 = JniHelper::newUTFString(t, param7);
		jstring stringArg8;
		stringArg8 = JniHelper::newUTFString(t, param8);
		jstring stringArg9;
		stringArg9 = JniHelper::newUTFString(t, param9);

		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg0, stringArg1, stringArg2, stringArg3, stringArg4, stringArg5, stringArg6, stringArg7, stringArg8, stringArg9, price);
		t.env->DeleteLocalRef(stringArg0);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(stringArg2);
		t.env->DeleteLocalRef(stringArg3);
		t.env->DeleteLocalRef(stringArg4);
		t.env->DeleteLocalRef(stringArg5);
		t.env->DeleteLocalRef(stringArg6);
		t.env->DeleteLocalRef(stringArg7);
		t.env->DeleteLocalRef(stringArg8);
		t.env->DeleteLocalRef(stringArg9);
		t.env->DeleteLocalRef(t.classID);
	}

}

void SharePlayerAccountInfoJNI(const char * serverName, const char * roleName, int serverId, int roleId, int roleLevel, int vipLevel)
{
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "sharePlayerAccountInfo", "(Ljava/lang/String;Ljava/lang/String;IIII)V")) {
		jstring stringArg0;
		stringArg0 = JniHelper::newUTFString(t, serverName);
		jstring stringArg1;
		stringArg1 = JniHelper::newUTFString(t, roleName);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg0, stringArg1, serverId, roleId, roleLevel, vipLevel);
		t.env->DeleteLocalRef(stringArg0);
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}