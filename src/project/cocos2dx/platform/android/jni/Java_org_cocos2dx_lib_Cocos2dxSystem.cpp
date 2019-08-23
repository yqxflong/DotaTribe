#include "cocoa/CCGeometry.h"
#include "platform/android/CCSystem.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

using namespace cocos2d;

extern "C" {


	void Java_org_cocos2dx_lib_Cocos2dxSystem_onAppExit(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSystem()->onAppExit();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSystem_onWebDialogClose(JNIEnv*  env, jobject thiz, jint type) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSystem()->onWebDialogClose(type);
	}

	void Java_org_cocos2dx_lib_Cocos2dxSystem_onNetworkChanged(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSystem()->onNetworkChanged();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSystem_onNetworkDisConnected(JNIEnv*  env, jobject thiz) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSystem()->onNetworkDisConnected();
	}

	void Java_org_cocos2dx_lib_Cocos2dxSystem_onQueryAppServerPushId(JNIEnv*  env, jobject thiz, jstring param) {
		std::string _param0 = JniHelper::jstring2string(param);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getSystem()->onQueryAppServerPushId(_param0);
	}


}
