#include <cocos2d.h> 
#include "../include/EngineSystem.h"
#include "../include/VariableSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventTyper.h"
#include "../include/EventDef.h"
#include "../include/EventSystem.h"
#include <spine/SpineCallBackEvent.h> 
#include "../include/DotaGameConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#include <EAGLView.h>
#include <Foundation/NSFileManager.h>
#include <UIKit/UIKit.h>
#include <dirent.h>

#include <sys/stat.h>

std::string EngineSystem::GetOS(){
	return "IOS";
}

std::string EngineSystem::GetDocumentDir()
{
	NSArray* pPathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSAllDomainsMask, YES);
	if ([pPathArray count] <= 0)
		return "";

	NSString* pDocumentPath = [pPathArray objectAtIndex:0];
	const char* pPath = [pDocumentPath UTF8String];
	if (pPath==NULL || strlen(pPath)==0)
		return "";

	if (pPath[strlen(pPath)-1] == '/')
		return pPath;

	char buffer[1024] = "";
	sprintf(buffer, "%s/", pPath);
	return buffer;
}

std::string EngineSystem::CreateDocumentSubDir(std::string subDir)
{
	std::string dir = GetDocumentDir()+subDir;
	NSString* myDir = [NSString stringWithUTF8String:dir.c_str()];

	BOOL isDir = YES;
	NSFileManager *fileManager = [NSFileManager defaultManager];
	BOOL existed = [fileManager fileExistsAtPath:myDir isDirectory:&isDir];
	if (isDir != YES)
		return "";

	if (existed == YES) 
		return dir;

	[fileManager createDirectoryAtPath:myDir withIntermediateDirectories:YES attributes:nil error:nil];
	return dir;
}

void EngineSystem::DeleteDocumentSubDir(std::string subDir)
{
	if (subDir.size() <= 0)
		return;

	std::string dir = GetDocumentDir()+subDir;
	[[NSFileManager defaultManager] removeItemAtPath:[NSString stringWithUTF8String:dir.c_str()] error:nil];
}

std::string EngineSystem::GetAppFilePath(std::string fileName)
{
	NSString* pNSFileName = [NSString stringWithUTF8String:fileName.c_str()];
	NSString* pAppDir     = [[NSBundle mainBundle] resourcePath];
	NSString* pFileName   = [pAppDir stringByAppendingPathComponent:pNSFileName];

	return [pFileName UTF8String];
}

int EngineSystem::GetDeviceType()
{
	static int type = _TYPED_IOS_DEVICE_UNKOWN_;
	if (type == _TYPED_IOS_DEVICE_UNKOWN_)
	{
		if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPhone)
		{
			if (IsIPhone5())
				type = _TYPED_IOS_DEVICE_IPHONE5_;
			else
				type = _TYPED_IOS_DEVICE_IPHONE_;
		}
		else if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad)
		{
			type = _TYPED_IOS_DEVICE_IPAD_;
		}
	}

	return type;
}

bool EngineSystem::IsIPhone5()
{
	return ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size):NO);
}

bool EngineSystem::IsIPad1()
{
	if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad)
	{
		return ![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera];
	}
	
	return false;
}

bool EngineSystem::IsShowOffers()
{
	NSDate*     date  = [NSDate date];  
	NSCalendar* sys   = [NSCalendar  currentCalendar];  
	NSUInteger  flags = NSYearCalendarUnit|NSMonthCalendarUnit|NSDayCalendarUnit|NSHourCalendarUnit|NSMinuteCalendarUnit|NSSecondCalendarUnit;  
	NSDateComponents* sysComps = [sys components:flags fromDate:date];
	int sysYear = [sysComps year];
	int sysMonth= [sysComps month];
	int sysDay  = [sysComps day];
	int sysHour = [sysComps hour];
	int sysMinute = [sysComps minute];
	if (sysYear < 2013)
		return false;
	
	if (sysYear > 2013)
		return true;
		
	if (sysMonth < 7)
		return false;
	
	if (sysMonth > 7)
		return true;
	
	if (sysDay < 5)
		return false;
		
	if (sysDay > 5)
		return true;
		
	if (sysHour >= 12)
		return true;
		
	return false;
}

void EngineSystem::EnableMultiTouch(bool bEnabled)
{
	if (bEnabled)
	{
		[[EAGLView sharedEGLView] setMultipleTouchEnabled:YES];
	}
	else 
	{
		[[EAGLView sharedEGLView] setMultipleTouchEnabled:NO];
	}
}

void EngineSystem::OpenURL(char* pBuffer)
{
	if (pBuffer==NULL || strlen(pBuffer)==0)
		return;

	NSString* url = [NSString stringWithCString:pBuffer];
	[[UIApplication sharedApplication]openURL:[NSURL URLWithString:url]];
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
		pDirector->setDefaultFontName("DFPYuanMXBold-B5");
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
	// 创建游戏导演类
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->setOpenGLView(cocos2d::CCEGLView::sharedOpenGLView());
	
	// 设置多分辨率相关的配置信息
	std::vector<std::string> searchList;
	if (_TYPED_IOS_DEVICE_IPHONE_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPHONE;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(_IOS_IPHONE_DEVICE_WIDTH_, _IOS_IPHONE_DEVICE_HEIGHT_DOTA_, kResolutionFixedHeight);
	}
	else if (_TYPED_IOS_DEVICE_IPHONE5_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPHONE5;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(_IOS_IPHONE5_DEVICE_WIDTH_, _IOS_IPHONE5_DEVICE_HEIGHT_, kResolutionShowAll);
	}
	else if (_TYPED_IOS_DEVICE_IPAD_ == GetDeviceType())
	{
		m_nLayoutConfig = kDEVICE_IPAD;
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(_IOS_IPAD_DEVICE_WIDTH_, _IOS_IPAD_DEVICE_HEIGHT_, kResolutionShowAll);
	}
	

	//@增加读取路径download
	std::string dir = CreateDocumentSubDir("download/");
	searchList.push_back(dir);
	cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(searchList);
}


#endif
