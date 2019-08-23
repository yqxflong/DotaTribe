//Name：DotaGameConfig
//Function：游戏级别的配置表

#ifndef  _DOTATRIBE_DotaGameConfig_H_
#define  _DOTATRIBE_DotaGameConfig_H_
#include <string>
#include "../include/VariableSystem.h"

//***************************出包前必须确认****************************
//#################调试模式设置###################
enum{
	kMODE_DEBUG=0,			//windows上开发
	kMODE_RELEASE_INNER,	//内部发布
	kMODE_RELEASE_REAL,		//正式发布
};
static int DOTA_CONFIG_MODE=kMODE_DEBUG;

//#################上线平台的设置###################
#define kENABLE_PLATFORM_PC				
//#define kENABLE_PLATFORM_SDKIOS
//#define kENABLE_PLATFORM_SDKANDROID


//#################VLD内存泄露检测开关##############
//#define kWin32_VLD_Debug_ON			//开启Win32内存检测开关

////////////////Lua系统开关///////////////////
#define kENABLE_PLATFORM_LUA


//@资源加密设置
#define kENCRYPTIONED_KEY		"com.cyou.mrd.dotatribeimage87564"
#define kENCRYPTIONED_LENGTH	200

//***************************出包前必须确认****************************


	

//#################WIN下的设备设置###################
enum WIN_DEVICE_TYPE{
	kDEVICE_IPAD=0,
	kDEVICE_IPHONE5,
	kDEVICE_IPHONE,
	kDEVICE_ANDROID,
	KDEVICE_ANDROID16_10,
};

//读取WIN下的分辨率类型
//Windows专用
static int DGC_GetDeviceType_Win32(){
	int ret=0;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "WIN_DEVICE_TYPE",ret);
	return ret;
}
//读取安卓模拟器宽
static void DGC_GetAndroidSimulatorWidth_Win32(int & width, int & height)
{
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "WIN_ANDROID_WIDTH", width);
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "WIN_ANDROID_HEIGHT", height);
}

//#################读取系统配置表###################
//先查看account中的版本号，如果为空则检查system表中的
//account中的版本号为升级之后的版本号，system中的版本号为下载app时初始的
static std::string DGC_GetGameVersion(){
	std::string curVersion="";
	//from system.xml
	char version1[128] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Version", version1, sizeof(version1));
	std::string strVersion1=version1;
	//from account.xml
	char version2[128] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version2, sizeof(version2));
	std::string strVersion2=version2;
	//
	if (strVersion2.length()==0||strVersion2.compare(strVersion1)<0){
		curVersion=version1;
	}else{
		curVersion=version2;
	}
	return curVersion;
}

//直接读取此包初始的版本号
static std::string DGC_GetGameVersion_System(){
	std::string curVersion="";
	//from system.xml
	char version1[128] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Version", version1, sizeof(version1));
	std::string strVersion1=version1;

	return strVersion1;
}

//#################PP平台专属#################
//默认充值100块钱
static int CHANEL_PP_RECHARGEAMOUNT_DEFAULT=100;

#endif
