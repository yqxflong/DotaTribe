#include "cocoa/CCGeometry.h"
#include "platform/android/CCPayment.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

using namespace cocos2d;

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxPayment_onPayFailed(JNIEnv*  env, jobject thiz, jstring Id, jstring error) {
		const char* pId = env->GetStringUTFChars(Id, NULL);
		const char* pError = env->GetStringUTFChars(error, NULL);

        CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPayment()->onPayFailed(pId, pError);
		
		env->ReleaseStringUTFChars(Id, pId);
		env->ReleaseStringUTFChars(error, pError);
    }    

	void Java_org_cocos2dx_lib_Cocos2dxPayment_onPaySuccess(JNIEnv*  env, jobject thiz, jstring Id) {
		const char* pId = env->GetStringUTFChars(Id, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPayment()->onPaySuccess(pId, "", "");

		env->ReleaseStringUTFChars(Id, pId);
	} 

	void Java_org_cocos2dx_lib_Cocos2dxPayment_onVerifySuccess(JNIEnv*  env, jobject thiz, jstring Id) {
		const char* pId = env->GetStringUTFChars(Id, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPayment()->onVerifySuccess(pId);

		env->ReleaseStringUTFChars(Id, pId);
	} 

	void Java_org_cocos2dx_lib_Cocos2dxPayment_onVerifyFailed(JNIEnv*  env, jobject thiz, jstring Id, jstring error) {
		const char* pId = env->GetStringUTFChars(Id, NULL);
		const char* pError = env->GetStringUTFChars(error, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPayment()->onVerifyFailed(pId, pError);

		env->ReleaseStringUTFChars(Id, pId);
		env->ReleaseStringUTFChars(error, pError);
	}

	//²åÈë¶©µ¥
	void Java_org_cocos2dx_lib_Cocos2dxPayment_onInsertPayment(JNIEnv*  env, jobject thiz, jstring productId, jstring transactionId)
	{
		const char* pProductId = env->GetStringUTFChars(productId, NULL);
		const char* pTransactionId = env->GetStringUTFChars(transactionId, NULL);

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getPayment()->onInsertPayment(pProductId, pTransactionId);

		env->ReleaseStringUTFChars(productId, pProductId);
		env->ReleaseStringUTFChars(transactionId, pTransactionId);
	}
}
