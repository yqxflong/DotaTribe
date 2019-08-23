#include "cocoa/CCGeometry.h"
#include "platform/android/CCPlatform.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

using namespace cocos2d;

extern "C" {

	void Java_org_cocos2dx_lib_Cocos2dxPlatform_onLoginResultHandler(JNIEnv*  env, jobject thiz, jint sdkType, jboolean bRet, jstring param0, jstring param1, jstring param2, jstring param3, jstring param4, jstring param5, jstring param6, jstring param7, jstring param8, jstring param9) {
		int type = sdkType;
		unsigned char b = bRet;
		const char* p0 = env->GetStringUTFChars(param0, NULL);
		const char* p1 = env->GetStringUTFChars(param1, NULL);
		const char* p2 = env->GetStringUTFChars(param2, NULL);
		const char* p3 = env->GetStringUTFChars(param3, NULL);
		const char* p4 = env->GetStringUTFChars(param4, NULL);
		const char* p5 = env->GetStringUTFChars(param5, NULL);
		const char* p6 = env->GetStringUTFChars(param6, NULL);
		const char* p7 = env->GetStringUTFChars(param7, NULL);
		const char* p8 = env->GetStringUTFChars(param8, NULL);
		const char* p9 = env->GetStringUTFChars(param9, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPlatform()->onLoginResultHandler(type, (bool)b, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);

		env->ReleaseStringUTFChars(param0, p0);
		env->ReleaseStringUTFChars(param1, p1);
		env->ReleaseStringUTFChars(param2, p2);
		env->ReleaseStringUTFChars(param3, p3);
		env->ReleaseStringUTFChars(param4, p4);
		env->ReleaseStringUTFChars(param5, p5);
		env->ReleaseStringUTFChars(param6, p6);
		env->ReleaseStringUTFChars(param7, p7);
		env->ReleaseStringUTFChars(param8, p8);
		env->ReleaseStringUTFChars(param9, p9);
	}

	void Java_org_cocos2dx_lib_Cocos2dxPlatform_onLogoutCallBack(JNIEnv*  env, jobject thiz, jint sdkType, jboolean bRet, jstring param0, jstring param1, jstring param2, jstring param3, jstring param4, jstring param5, jstring param6, jstring param7, jstring param8, jstring param9) {
		int type = sdkType;
		unsigned char b = bRet;
		const char* p0 = env->GetStringUTFChars(param0, NULL);
		const char* p1 = env->GetStringUTFChars(param1, NULL);
		const char* p2 = env->GetStringUTFChars(param2, NULL);
		const char* p3 = env->GetStringUTFChars(param3, NULL);
		const char* p4 = env->GetStringUTFChars(param4, NULL);
		const char* p5 = env->GetStringUTFChars(param5, NULL);
		const char* p6 = env->GetStringUTFChars(param6, NULL);
		const char* p7 = env->GetStringUTFChars(param7, NULL);
		const char* p8 = env->GetStringUTFChars(param8, NULL);
		const char* p9 = env->GetStringUTFChars(param9, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPlatform()->onLogoutCallBack(type, (bool)b, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);

		env->ReleaseStringUTFChars(param0, p0);
		env->ReleaseStringUTFChars(param1, p1);
		env->ReleaseStringUTFChars(param2, p2);
		env->ReleaseStringUTFChars(param3, p3);
		env->ReleaseStringUTFChars(param4, p4);
		env->ReleaseStringUTFChars(param5, p5);
		env->ReleaseStringUTFChars(param6, p6);
		env->ReleaseStringUTFChars(param7, p7);
		env->ReleaseStringUTFChars(param8, p8);
		env->ReleaseStringUTFChars(param9, p9);
	}

	void Java_org_cocos2dx_lib_Cocos2dxPlatform_onPayResultCallBack(JNIEnv*  env, jobject thiz, jint sdkType, jint resultCode, jstring param0, jstring param1) {
		int type = sdkType;
		int code = resultCode;
		const char* p0 = env->GetStringUTFChars(param0, NULL);
		const char* p1 = env->GetStringUTFChars(param1, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPlatform()->onPayResultCallBack(type, code, p0, p1);

		env->ReleaseStringUTFChars(param0, p0);
		env->ReleaseStringUTFChars(param1, p1);
	}
}
