#include "cocoa/CCGeometry.h"
#include "platform/android/CCSNS.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

using namespace cocos2d;

extern "C" {


	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginRennSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginRennSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginRennFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginRennFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInRennSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInRennSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInRennFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInRennFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInRennSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInRennSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInRennFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInRennFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginWeiboSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginWeiboSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginWeiboFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginWeiboFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInWeiboSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInWeiboSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInWeiboFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInWeiboFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInWeiboSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInWeiboSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInWeiboFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInWeiboFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginQQSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginQQSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginQQFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginQQFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInQQSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInQQSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInQQFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInQQFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInQQSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInQQSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInQQFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInQQFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginFacebookSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginFacebookSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginFacebookFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginFacebookFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInFacebookSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInFacebookSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInFacebookFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInFacebookFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInFacebookSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInFacebookSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInFacebookFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInFacebookFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginTwitterSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginTwitterSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onLoginTwitterFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onLoginTwitterFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInTwitterSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInTwitterSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onShareTextInTwitterFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onShareTextInTwitterFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInTwitterSuccess(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInTwitterSuccess();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSNS_onSharePictureInTwitterFailed(JNIEnv*  env, jobject thiz, jstring error) {
		const char* pszText = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSNS()->onSharePictureInTwitterFailed(pszText);

		env->ReleaseStringUTFChars(error, pszText);
	}

}
