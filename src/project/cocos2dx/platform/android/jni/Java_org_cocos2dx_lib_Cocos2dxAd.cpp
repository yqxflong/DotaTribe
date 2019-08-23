#include "cocoa/CCGeometry.h"
#include "platform/android/CCAd.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

using namespace cocos2d;

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxAd_onReceiveYouMiPoint(JNIEnv*  env, jobject thiz, jint x) {
        CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receiveYoumiPoints(x);
    }    

	void Java_org_cocos2dx_lib_Cocos2dxAd_onReceiveDianJoyPoint(JNIEnv*  env, jobject thiz, jint x) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receiveDianjoyPoints(x);
	}   

	void Java_org_cocos2dx_lib_Cocos2dxAd_onReceiveImmobPoint(JNIEnv*  env, jobject thiz, jint x) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receiveImmobPoints(x);
	}   

	void Java_org_cocos2dx_lib_Cocos2dxAd_onReceiveTapjoyPoint(JNIEnv*  env, jobject thiz, jint x) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receiveTapjoyPoints(x);
	}   

	void Java_org_cocos2dx_lib_Cocos2dxAd_onReceiveDomobPoint(JNIEnv*  env, jobject thiz, jint x) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receiveDomobPoints(x);
	}   

	void Java_org_cocos2dx_lib_Cocos2dxAd_onReceive91Point(JNIEnv*  env, jobject thiz, jint x) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getAd()->receive91Points(x);
	}   
}
