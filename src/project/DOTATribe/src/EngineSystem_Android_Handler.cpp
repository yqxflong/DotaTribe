#include "../include/DOTATribeApp.h"
#include "../include/EngineSystem.h"
#include "../include/VariableSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventDef.h"
#include "../include/EventSystem.h"
#include <cocos2d.h>
#include <spine/SpineCallBackEvent.h>
#include "../include/DotaGameConfig.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

std::string EngineSystem::GetOS(){
	return "ANDROID";
}

std::string EngineSystem::GetDocumentDir()
{
	return cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
}

std::string EngineSystem::CreateDocumentSubDir(std::string subDir)
{
	std::string dir = GetDocumentDir()+subDir;

	mode_t processMask = umask(0);
	int ret = mkdir(dir.c_str(), S_IRUSR|S_IWUSR|S_IXUSR|S_IRWXU|S_IRWXG|S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
		return "";

	return dir;
}

void EngineSystem::DeleteDocumentSubDir(std::string subDir)
{
	std::string dir = GetDocumentDir()+subDir;

	std::string command = "rm -r ";
	// Path may include space.
	command += "\"" + dir + "\"";
	system(command.c_str());
}

std::string EngineSystem::GetAppFilePath(std::string fileName)
{
	return fileName;
}

int EngineSystem::GetDeviceType()
{
	return _TYPED_IOS_DEVICE_ANDROID_;
}

bool EngineSystem::IsIPad1()
{
	return false;
}

bool EngineSystem::IsIPhone5()
{
	return false;
}

bool EngineSystem::IsShowOffers()
{
	return true;
}

void EngineSystem::EnableMultiTouch(bool bEnabled)
{

}

void EngineSystem::OpenURL(char* pBuffer)
{

}

bool EngineSystem::ScreenShot(std::string filename)
{
	return true;
}

void EngineSystem::UpdateNewVersionDialog(std::string title, std::string yes, std::string cancel)
{

}

bool EngineSystem::Init()
{
	do
	{
		// 是否显示帧率
		bool bShowFPS = DOTA_CONFIG_MODE==kMODE_DEBUG?true:false;
		//是否加密资源
		bool bResourceEncryptioned = true;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "ResourceEncryptioned", bResourceEncryptioned);

		//@初始化导演信息
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		//@加密设置
		pDirector->setResEncryptioned(bResourceEncryptioned);
		pDirector->setResEncryptionedKey(kENCRYPTIONED_KEY);
		pDirector->setResEncryptionedLength(kENCRYPTIONED_LENGTH);
		//@字体设置
		pDirector->setDefaultFontName("resource/font/DFPYuanMXBold-B5.ttf");
		pDirector->setDefaultFontSize(20);
		//@其他
		pDirector->setDisplayStats(bShowFPS);
		pDirector->setProjection(cocos2d::kCCDirectorProjection2D);
		pDirector->setAnimationInterval(1.0f/DOTATribeApp::get_instance2()->GetFPS());

		//@注册骨骼动作配置加载接口
		cocos2d::extension::RegisterSkeletonCallBackEventHandler(OnEngineLoadSkeletonCallBackConfig);

		//@初始化场景
		InitScene();
		//@预加载资源
		LoadSysResource();

		//@设置所有动画Sprite播放间隔
		float interval = 0.3f;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "AnimationSpritePlayInterval", interval);
		pDirector->setAnimationSpritePlayInterval(interval);


		LOGGERSYSTEM->LogInfo("Init EngineSystem Success\n");
		return true;
	}
	while (false);

	LOGGERSYSTEM->LogFatal("Init EngineSystem Failed!!!\n");
	return false;
}

void EngineSystem::InitAppEnv()
{
	CCLOG("dota crashsystem begin");

	InitAndroidCrashReport();

	CCLOG("dota crashsystem end");

	CCLOG("dota InitAppEnv -- begin");
	// 创建游戏导演类
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->setOpenGLView(cocos2d::CCEGLView::sharedOpenGLView());

	// 设置分辨率
	std::vector<std::string> searchList;

	if(IsAndroid_3_2())
	{//use iphone resource
		m_nLayoutConfig = kDEVICE_IPHONE;
		CCLOG("InitAppEnv is 3/2");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_3_2_DEVICE_WIDTH_, (float)_ANDROID_3_2_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}
	else if(IsAndroid_4_3())
	{
		m_nLayoutConfig = kDEVICE_IPAD;
		CCLOG("InitAppEnv is 4/3");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_4_3_DEVICE_WIDTH_, (float)_ANDROID_4_3_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}
	else if(IsAndroid_15_9() || EngineSystem::IsAndroid_1024_600() || EngineSystem::IsAndroid_1184_720() || EngineSystem::IsAndroid_1196_720())
	{//use 15:9
		m_nLayoutConfig = kDEVICE_ANDROID;
		CCLOG("InitAppEnv is 15/9");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_15_9_DEVICE_WIDTH_, (float)_ANDROID_15_9_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}
	else if(IsAndroid_16_9() || IsAndroid_1136_640())
	{//use iphone5 resource
		m_nLayoutConfig = kDEVICE_IPHONE5;
		CCLOG("InitAppEnv is 16/9");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_16_9_DEVICE_WIDTH_, (float)_ANDROID_16_9_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}
	else if(EngineSystem::IsAndroid_16_10())
	{//16:10, 1280*800
		m_nLayoutConfig = KDEVICE_ANDROID16_10;
		CCLOG("InitAppEnv is 16/10");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_16_10_DEVICE_WIDTH_, (float)_ANDROID_16_10_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}
	else
	{//use iphone resource for default
		m_nLayoutConfig = kDEVICE_IPHONE;
		CCLOG("InitAppEnv is default iphone");
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_3_2_DEVICE_WIDTH_, (float)_ANDROID_3_2_DEVICE_HEIGHT_, kResolutionFixedHeight);
	}

	//@增加读取路径download
	std::string dir = CreateDocumentSubDir("download/");
	searchList.push_back(dir);
	cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(searchList);

	CCLOG("dota InitAppEnv -- end");
}


#endif
