#ifndef  _DOTATRIBE_ENGINESYSTEM_H_
#define  _DOTATRIBE_ENGINESYSTEM_H_


#include <include/common/Singleton.h>
#include <layers_scenes_transitions_nodes/CCScene.h>
#include <cocos2d.h>
#include <string>
#include <spine/SpineCallBackEvent.h> 
#include <vector>
#include "../include/DotaGameConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <signal.h>
#include <platform/android/jni/JniHelper.h>
#endif
 
 
#ifdef kWin32_VLD_Debug_ON
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include <platform/third_party/win32/vld/vld.h>
	#endif
#endif
 
using  namespace  cobra_win;

class  AnimationFileData;
 
class EngineSystem : public cobra_win::Singleton2<EngineSystem>
{
public:
	const  static  int  _IOS_IPHONE_DEVICE_WIDTH_       = 960;
	const  static  int  _IOS_IPHONE_DEVICE_HEIGHT_      = 640;
	const  static  int  _IOS_IPHONE_DEVICE_HEIGHT_DOTA_  = 720;
	const  static  int  _IOS_IPHONE5_DEVICE_WIDTH_      = 1136;
	const  static  int  _IOS_IPHONE5_DEVICE_HEIGHT_     = 640;
	const  static  int  _IOS_IPAD_DEVICE_WIDTH_         = 1024;
	const  static  int  _IOS_IPAD_DEVICE_HEIGHT_        = 768;

	const static int _ANDROID_3_2_DEVICE_WIDTH_ = 960;		//960
	const static int _ANDROID_3_2_DEVICE_HEIGHT_ = 720;		//720
	const static int _ANDROID_4_3_DEVICE_WIDTH_ = 1024;		//1024
	const static int _ANDROID_4_3_DEVICE_HEIGHT_ = 768;		//768
	const static int _ANDROID_15_9_DEVICE_WIDTH_ = 1280;	//960
	const static int _ANDROID_15_9_DEVICE_HEIGHT_ = 640;	//720
	const static int _ANDROID_16_9_DEVICE_WIDTH_ = 1136;	//1136
	const static int _ANDROID_16_9_DEVICE_HEIGHT_ = 640;	//640
	const static int _ANDROID_16_10_DEVICE_WIDTH_ = 1280;	//1280
	const static int _ANDROID_16_10_DEVICE_HEIGHT_ = 640;	//1280

public:
	enum
	{
		_TYPED_IOS_DEVICE_UNKOWN_,     // 未知的设备类型
		_TYPED_IOS_DEVICE_IPHONE_,     // iPhone
		_TYPED_IOS_DEVICE_IPHONE5_,    // iPhone5
		_TYPED_IOS_DEVICE_IPAD_,       // iPad
		_TYPED_IOS_DEVICE_ANDROID_,    // Android
	};

private:
	cocos2d::CCScene* m_pScene; // 场景指针
	std::set<std::string>  m_sAnimationCacheList;

private:
	static int m_nLayoutConfig;//对应DOTAGameConfig里面的设备枚举

public:
	EngineSystem();
	virtual ~EngineSystem();

public:
	//@获取操作系统
	static std::string GetOS();
    //@获取Document目录路径
    static  std::string  GetDocumentDir();
	//@创建Document子目录
	static  std::string  CreateDocumentSubDir(std::string subDir);
	//@删除Document字目录(递归删除所有的子目录)
	static  void         DeleteDocumentSubDir(std::string subDir);
    //@获取APP文件夹下面的文件路径
    static  std::string  GetAppFilePath(std::string fileName); 
	//@获取录像文件数据路径
	static  std::string  GetRecordDataPath();
	//@获得设备类型
	static  int          GetDeviceType();
	//@是否是iPad1
	static  bool         IsIPad1();
	//@是否是iPhone5
	static  bool         IsIPhone5();
	//@是否显示广告墙按钮
	static   bool        IsShowOffers();

	//@是否为1136*768
	static	bool	IsAndroid_1136_640();
	//@是否为3:2，分辨率包括960*640,480*320
	static	bool	IsAndroid_3_2();
	//@是否是4:3,分辨率是1024*768
	static	bool	IsAndroid_4_3();
	//@是否为15:9，分辨率包括800*480,1280*768
	static	bool	IsAndroid_15_9();
	//@是否为16:9，分辨率包括854*480，960*540，1280*720，1920*1080
	static	bool	IsAndroid_16_9();
	//@是否为16:10，分辨率包括1280*800，1920*1200
	static  bool    IsAndroid_16_10();
	//@是否为1024*600，此类分辨率
	static  bool    IsAndroid_1024_600();
	//@是否为1184*720，此类分辨率
	static	bool	IsAndroid_1184_720();

	//@是否为1196*720，此类分辨率
	static	bool	IsAndroid_1196_720();

public:
	//@得到引擎根场景指针
	cocos2d::CCScene* GetScene();

public:
	//@开始多点触摸功能
	void    EnableMultiTouch(bool bEnabled);
	//@打开指定URL
	void    OpenURL(char* pBuffer);
	//@截图
	bool    ScreenShot(std::string filename);

public:
	//@显示用户反馈界面
	void    ShowFeedbackDialog();

public:
	//@是否网络可用
	bool    IsNetWorkAvailable();

public:
	//@显示ADMob
	void    ShowAd(bool bShow);
	//@提示更新新版本
	void    UpdateNewVersionDialog(std::string title, std::string yes, std::string cancel);

public:
	//@清除帧动画纹理以及缓存
	void   ForceClearAnimationCache();

    //@强制进行内存回收处理
    void    FreeMemory();

	//@根据动画名称得到CCAnimation
	cocos2d::CCAnimation* GetAnimtionByName(std::string name);

	//@根据AnimateID得到CCAnimation  高效
	cocos2d::CCAnimation * GetAnimationByID(int animationID);
	 
	//@获得配置文件
	int GetLayoutConfig();

public:
	//@标配
	bool    Init();
	void    Tick();
	void    Destroy();

private:
	//@初始化场景管理器
	void    InitScene();
	//@加载系统必须的资源
    void    LoadSysResource();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
	//@初始化初始化Android的崩溃报告系统
	static void InitAndroidCrashReport();

	//@Android崩溃报告系统收到事件回调
	void AndroidSigaction(int signal, siginfo_t * info, void * reserved);
#endif

public:
	//@初始化引擎环境变量
	static   void    InitAppEnv();
	//@加载资源文件
	static   bool    LoadAppFile(char* pFileName, char*& pBuffer, unsigned int& iLength);
	//@加载用户存档文件
	static   bool    LoadTempFile(char* pFileName, char*& pBuffer, unsigned int& iLength);

private:
	//@引擎按钮操作回调处理(判断是否需要)
	static   void    OnEngineMenuItemCallbackEventHandler(std::string eventName, std::string menuItemName);

	//@骨骼动作配置加载回调接口
	static   void    OnEngineLoadSkeletonCallBackConfig(std::string skeletonUUID,int animationID,std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec);


public:
	EngineSystem* GetLuaInstance(){
		return EngineSystem::get_instance2();
	}

};

#define  ENGINESYSTEM  (EngineSystem::get_instance2())


#endif
