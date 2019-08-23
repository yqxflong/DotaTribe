#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/DotaGameConfig.h"
#include "../include/EngineSystem.h"
#include "../include/VariableSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventDef.h"
#include "../include/EventSystem.h"
#include <spine/SpineCallBackEvent.h>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>


static bool get_module_folder_path(char* pPath, size_t iLen)
{
	int ret = (int)GetModuleFileName(NULL, pPath, (DWORD)iLen);
	if ( (ret==0) || (ret==iLen))
		return false;

	for (size_t i=strlen(pPath)-1; i>=0; i--)
	{
		switch( pPath[i] )
		{
		case	'/':
		case	'\\':
			pPath[i+1] = '\0';
			return true;
			break;
		}
	}

	return false;
}

	/*
		获取操作系统
	*/
std::string EngineSystem::GetOS(){
	return "OTHER";
}

std::string EngineSystem::GetDocumentDir()
{
	char buffer[1024] = "";
	get_module_folder_path(buffer, sizeof(buffer));

	return buffer;
}

std::string EngineSystem::CreateDocumentSubDir(std::string subDir)
{
	std::string dir = GetDocumentDir()+subDir;
	::CreateDirectory(dir.c_str(), NULL);

	return dir;
}

void EngineSystem::DeleteDocumentSubDir(std::string subDir)
{
	std::string command = "rd /s /q ";
	// Path may include space.
	command += "\"" + subDir + "\"";
	system(command.c_str());
}

std::string EngineSystem::GetAppFilePath(std::string fileName)
{
	return "./"+fileName;
}

int EngineSystem::GetDeviceType()
{
	int type=DGC_GetDeviceType_Win32();
	switch(type){
		case kDEVICE_IPAD:
			return _TYPED_IOS_DEVICE_IPAD_;
		case kDEVICE_IPHONE:
			return _TYPED_IOS_DEVICE_IPHONE_;
		case kDEVICE_IPHONE5:
			return _TYPED_IOS_DEVICE_IPHONE5_;
		case kDEVICE_ANDROID:
			return _TYPED_IOS_DEVICE_ANDROID_;
		default:
			return _TYPED_IOS_DEVICE_IPAD_;
	}
}

bool EngineSystem::IsIPad1()
{
	return false;
}

bool EngineSystem::IsIPhone5()
{
	return GetDeviceType()==_TYPED_IOS_DEVICE_IPHONE5_;
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
		pDirector->setDefaultFontName("Heiti SC");
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
	//@初始化windows窗口大小
	if (_TYPED_IOS_DEVICE_IPHONE_ == GetDeviceType())
	{
		cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize((float)_IOS_IPHONE_DEVICE_WIDTH_, (float)_IOS_IPHONE_DEVICE_HEIGHT_);
	}
	else if (_TYPED_IOS_DEVICE_IPHONE5_ == GetDeviceType())
	{
		cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize((float)_IOS_IPHONE5_DEVICE_WIDTH_, (float)_IOS_IPHONE5_DEVICE_HEIGHT_);
	}
	else if (_TYPED_IOS_DEVICE_IPAD_ == GetDeviceType())
	{
		cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize((float)_IOS_IPAD_DEVICE_WIDTH_, (float)_IOS_IPAD_DEVICE_HEIGHT_);
	}
	else if (_TYPED_IOS_DEVICE_ANDROID_ == GetDeviceType())
	{
		int width = 0;
		int height = 0;
		DGC_GetAndroidSimulatorWidth_Win32(width, height);
		cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize((float)width, (float)height);
	}

	//@设置openglview
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->setOpenGLView(cocos2d::CCEGLView::sharedOpenGLView());


	//@设置屏幕分辨率
	std::vector<std::string> searchList;
	if (_TYPED_IOS_DEVICE_IPHONE_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPHONE;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_IOS_IPHONE_DEVICE_WIDTH_, (float)_IOS_IPHONE_DEVICE_HEIGHT_DOTA_, kResolutionFixedHeight);
	}
	else if (_TYPED_IOS_DEVICE_IPHONE5_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPHONE5;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_IOS_IPHONE5_DEVICE_WIDTH_, (float)_IOS_IPHONE5_DEVICE_HEIGHT_, kResolutionShowAll);
	}
	else if (_TYPED_IOS_DEVICE_IPAD_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPAD;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_IOS_IPAD_DEVICE_WIDTH_, (float)_IOS_IPAD_DEVICE_HEIGHT_, kResolutionShowAll);
	}
	else if (_TYPED_IOS_DEVICE_ANDROID_ == GetDeviceType())
	{
		std::string dir;

		if(EngineSystem::IsAndroid_3_2())
		{//phone4
			m_nLayoutConfig = kDEVICE_IPHONE;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_3_2_DEVICE_WIDTH_, (float)_ANDROID_3_2_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
		else if(EngineSystem::IsAndroid_4_3())
		{//ipad
			m_nLayoutConfig = kDEVICE_IPAD;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_4_3_DEVICE_WIDTH_, (float)_ANDROID_4_3_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
		else if(EngineSystem::IsAndroid_15_9() || EngineSystem::IsAndroid_1024_600() || EngineSystem::IsAndroid_1184_720() || EngineSystem::IsAndroid_1196_720())
		{//用15:9
			m_nLayoutConfig = kDEVICE_ANDROID;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_15_9_DEVICE_WIDTH_, (float)_ANDROID_15_9_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
		else if(EngineSystem::IsAndroid_16_9() || EngineSystem::IsAndroid_1136_640())
		{//phone5
			m_nLayoutConfig = kDEVICE_IPHONE5;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_16_9_DEVICE_WIDTH_, (float)_ANDROID_16_9_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
		else if(EngineSystem::IsAndroid_16_10())
		{//16:10, 1280*800
			m_nLayoutConfig = KDEVICE_ANDROID16_10;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_16_10_DEVICE_WIDTH_, (float)_ANDROID_16_10_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
		else
		{
			m_nLayoutConfig = kDEVICE_IPHONE;
			cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize((float)_ANDROID_3_2_DEVICE_WIDTH_, (float)_ANDROID_3_2_DEVICE_HEIGHT_, kResolutionFixedHeight);
		}
	}

	//@增加读取路径download
	std::string dir = CreateDocumentSubDir("download/");
	searchList.push_back(dir);
	cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(searchList);
}


#endif
