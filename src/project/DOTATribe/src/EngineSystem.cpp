#include <cocos2d.h>
#include <cocos-ext.h>
#include <include/common/String.h>
#include "../include/Common.h"
#include "../include/TimeSystem.h"
#include "../include/EngineSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/DBSystem.h"
#include "../include/PreLoadResourceDataManager.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/IProcedure.h"


template<> EngineSystem* cobra_win::Singleton2<EngineSystem>::m_pMySelf = NULL;

int EngineSystem::m_nLayoutConfig = -1;

EngineSystem::EngineSystem()
{
	m_pScene = NULL;
	m_sAnimationCacheList.clear();

}

EngineSystem::~EngineSystem()
{

}

std::string  EngineSystem::GetRecordDataPath()
{
	return "resource/recorddata/";
}

bool EngineSystem::IsAndroid_1136_640()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 11.36f * iHeight;
	int num2 = 6.40f * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(num1 == num2)
	{
		return true;
	}

	return false;
}

bool EngineSystem::IsAndroid_3_2()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 3 * iHeight;
	int num2 = 2 * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(num1 == num2)
	{
		return true;
	}

	return false;
}


bool EngineSystem::IsAndroid_4_3()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 4 * iHeight;
	int num2 = 3 * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);
	if(num1 == num2)
	{
		return true;
	}
	return false;
}

bool EngineSystem::IsAndroid_15_9()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 15 * iHeight;
	int num2 = 9 * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
	{
		return true;
	}

	return false;
}

bool EngineSystem::IsAndroid_16_9()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 16 * iHeight;
	int num2 = 9 * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
		return true;

	return false;
}

bool    EngineSystem::IsAndroid_16_10()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 16 * iHeight;
	int num2 = 10 * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
	{
		return true;
	}

	return false;
}

bool    EngineSystem::IsAndroid_1024_600()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	// 设置多分辨率相关的配置信息
	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 10.24f * iHeight;
	int num2 = 6.00f * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
	{
		return true;
	}

	return false;
}

bool	EngineSystem::IsAndroid_1184_720()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 11.84f * iHeight;
	int num2 = 7.20f * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
	{
		return true;
	}

	return false;
}

bool	EngineSystem::IsAndroid_1196_720()
{
	if (EngineSystem::GetDeviceType() != EngineSystem::_TYPED_IOS_DEVICE_ANDROID_)
		return false;

	int iWidth  = int(cocos2d::CCDirector::sharedDirector()->getWinSize().width);
	int iHeight = int(cocos2d::CCDirector::sharedDirector()->getWinSize().height);
	int num1 = 11.96f * iHeight;
	int num2 = 7.20f * iWidth;
	CCLOG("Android CCDirector::sharedDirector() [%d _ %d]  calculate [%d ? %d]\n", iWidth, iHeight, num1, num2);

	if(abs(num1 - num2) < 20)
	{
		return true;
	}

	return false;
}

void EngineSystem::ShowFeedbackDialog()
{
	cocos2d::CCDirector::sharedDirector()->getSystem()->showFeedbackDialog();
}

bool EngineSystem::IsNetWorkAvailable()
{
	return cocos2d::CCDirector::sharedDirector()->getSystem()->isNetworkAvailable();
}

void EngineSystem::ShowAd(bool bShow)
{
	cocos2d::CCDirector::sharedDirector()->getAd()->showAd(bShow);
}

cocos2d::CCScene* EngineSystem::GetScene()
{
	return m_pScene;
}

//@清除动画缓存
void  EngineSystem::ForceClearAnimationCache()
{
	std::set<std::string>::const_iterator plist_iter=m_sAnimationCacheList.begin();
	while(plist_iter!=m_sAnimationCacheList.end())
	{  
		_TRACE_UNLOAD_PLIST_((*plist_iter).c_str())		
		cocos2d::CCAnimationCache::sharedAnimationCache()->removeAnimationByName(GetAnimationNameFromPlistOrPng(*plist_iter).c_str());
		++plist_iter;
	}
	m_sAnimationCacheList.clear();
}

//@清除retaincount为1的纹理贴图
void EngineSystem::FreeMemory()
{ 
	cocos2d::CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}


//@获取指定动画by AnimationName
//#如果不在缓存中，需要从plist载入SpriteFrame,组合成Animation
cocos2d::CCAnimation* EngineSystem::GetAnimtionByName(std::string name)
{
	cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimationCache::sharedAnimationCache()->animationByName(name.c_str());
	if (pAnimation == NULL)
	{
		AnimationFileData* pData = AnimationFileDataManager::get_instance2()->GetAnimationByName(name);

		cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pData->mAnimationFileName);
		m_sAnimationCacheList.insert(pData->mAnimationFileName);
		cocos2d::CCArray* pArray = new cocos2d::CCArray;

		for (int i=0; i<pData->mAnimationFrameCount; i++)
		{
			char buffer[128] = "";
			sprintf(buffer, "%s_%02d.png", pData->mAnimationPrefix, i+1);
			cocos2d::CCSpriteFrame* spriteFrame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
			if(spriteFrame!=NULL)
			pArray->addObject(spriteFrame);
		}
		pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(pArray, pData->mAnimationIntervalTime);
		cocos2d::CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, pData->mAnimationName);

		pArray->removeAllObjects();
		delete pArray;
	}

	return pAnimation;
}

//@获取指定动画by AnimationID
cocos2d::CCAnimation * EngineSystem::GetAnimationByID(int animationID)
{
	AnimationFileData* pData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
	return GetAnimtionByName(pData->mAnimationName);
	 
}


int EngineSystem::GetLayoutConfig()
{
	return m_nLayoutConfig;
}



void EngineSystem::Tick()
{
	
}

void EngineSystem::Destroy()
{
	cocos2d::CCDirector::sharedDirector()->registerMenuItemEventCallback(NULL);
	m_pScene = NULL;
    ForceClearAnimationCache();
	LOGGERSYSTEM->LogInfo("Destroy EngineSystem Success\n");
}

void EngineSystem::InitScene()
{
	m_pScene = cocos2d::CCScene::create();
	cocos2d::CCDirector::sharedDirector()->runWithScene(m_pScene);
}

void EngineSystem::LoadSysResource()
{
	//@加载预加载资源，伴随游戏生命周期
	for (unsigned int i=0; i<PreLoadResourceDataManager::get_instance2()->GetPreLoadResourceNumber(); i++)
	{
		PreLoadResourceItemData* pItem = PreLoadResourceDataManager::get_instance2()->GetItemDataByPos(i);
		if (pItem->mType == 0)
		{
			_TRACE_LOADING_PLIST_(pItem->mFileName);
		}
		else if (pItem->mType == 1)
		{
			_TRACE_LOADING_IMAGE_(pItem->mFileName);
		}
	}
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void EngineSystem::InitAndroidCrashReport()
{
	CCLOG("EngineSystem::InitAndroidCrashReport --- begin");

	struct sigaction handler;
	memset(&handler, 0, sizeof(struct sigaction));
// 	handler.sa_sigaction = AndroidSigaction;
// 	handler.sa_flags = SA_RESETHAND;

#define CATCHSIG(TAG) sigaction(TAG, &handler, &old_sa[TAG])

// 	CATCHSIG(SIGILL);
// 	CATCHSIG(SIGABRT);
// 	CATCHSIG(SIGBUS);
// 	CATCHSIG(SIGFPE);
// 	CATCHSIG(SIGSEGV);
// 	CATCHSIG(SIGSTKFLT);
// 	CATCHSIG(SIGPIPE);

	CCLOG("EngineSystem::InitAndroidCrashReport --- end");
}

void EngineSystem::AndroidSigaction(int signal, siginfo_t * info, void * reserved)
{
// 	if(!g_env)
// 	{
// 		return;
// 	}
// 	jclass classID = g_env->FindClass("DOTATribe");
// 	if(!classID)
// 	{
// 		return;
// 	}
// 	jmethodID methodID = g_env->GetStaticMethodID(classID, "gameSoCrashed", "()V");
// 	if(!methodID)
// 	{
// 		return;
// 	}
// 	g_env->CallStaticVoidMethod(classID, methodID);
// 	old_sa[signal].sa_handler(signal);
}
#endif


void   EngineSystem::OnEngineLoadSkeletonCallBackConfig(std::string skeletonUUID,int animationID,std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec)
{  
	//判断当前是否为战斗流程
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_ATHLETICS_PROCEDURE_)
	return ;
	if(!skeletonUUID.empty()&&animationID!=-1&&pcallBackVec!=NULL)
	{
		int  shapeID=atoi(skeletonUUID.c_str());

		DBSystem::get_instance2()->LoadSkeletonTriggerConfig(shapeID,animationID,pcallBackVec);
	}   
}

bool EngineSystem::LoadAppFile(char* pFileName, char*& pBuffer, unsigned int& iLength)
{
	assert(pFileName != NULL);
	assert(strlen(pFileName) > 0);

	unsigned long iTemp = 0;
	unsigned char* pTemp = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(pFileName, "rb", &iTemp);
	if (iTemp==0 || pTemp==NULL)
		return false;

	pBuffer = (char*)pTemp;
	iLength = (unsigned int)iTemp;

	return true;
}

bool EngineSystem::LoadTempFile(char* pFileName, char*& pBuffer, unsigned int& iLength)
{
	assert(pFileName != NULL);
	assert(strlen(pFileName) > 0);

	std::string filepath = EngineSystem::GetDocumentDir();
	filepath += pFileName;

	FileLoader loader;
	if (!loader.load((char*)filepath.c_str(), FileLoader::_TYPED_READ_ONLY_))
		return false;

	// 读取文件内容
	iLength = loader.length();
	pBuffer = new char[iLength+1];
	memset(pBuffer, 0, iLength+1);
	loader.read(pBuffer, iLength);
	loader.unload();

	return true;
}
