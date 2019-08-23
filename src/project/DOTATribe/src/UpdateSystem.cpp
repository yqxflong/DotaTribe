#include <cocos2d.h>
#include "../include/UpdateSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/EngineSystem.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/VersionCheckPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/MessageBoxWindow.h"
#include "../include/SysLangDataManager.h"
#include "../include/NetSystem.h"
#include <include/common/FileLoader.h>
#include <string>
using  namespace  cobra_win;

template<> UpdateSystem* cobra_win::Singleton2<UpdateSystem>::m_pMySelf = NULL;

UpdateSystem::UpdateSystem()
{
	ret_=-1;
	m_pAntManager = NULL;
	m_bHasUpdated = false;
	m_UpdateVersionSize = 0;
}

UpdateSystem::~UpdateSystem()
{

}

miniant::IAntManager* UpdateSystem::GetAntManager()
{
	return m_pAntManager;
}

bool UpdateSystem::IsHasUpdated()
{
	return m_bHasUpdated;
}

bool UpdateSystem::Init()
{
	//大版本更新后，清理download文件夹
	ConfirmSandBoxDownloadHasBeenCleared();

	//初始化下载器
	m_pAntManager = miniant::CreateAntManager();
	m_pAntManager->SetDocumentDir(cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath());
	m_pAntManager->SetCallbackHandler(dynamic_cast<miniant::IAntCallbackHandler*>(this));
	m_pAntManager->SetAppendDownLoadZip(true);
	m_pAntManager->SetLocation(true);
	if (DOTA_CONFIG_MODE!=kMODE_RELEASE_REAL)
	{
		m_pAntManager->SetDebug(true);
	}
	m_pAntManager->Init();

	return true;
}

void UpdateSystem::Tick()
{
	if (m_pAntManager != NULL)
	{
		m_pAntManager->Tick();
	}
}

void UpdateSystem::Destroy()
{
	m_bHasUpdated = false;
	m_UpdateVersionSize = 0;
	m_AllVersionList.clear();
	m_UpdateVersionList.clear();

	if (m_pAntManager != NULL)
	{
		DestroyAntManager();
		m_pAntManager = NULL;
	}
}
	/*
		请求版本信息
	*/
void UpdateSystem::QueryVersionInfo(){
	NFC_showCommunicationWating(true);
	SERVERINFODATAINFO->CurSendHttpPacketType_=_HTTP_STATE_DISTINCT_;
	std::string curVersion=DOTATribeApp::get_instance2()->GetVersion();

	//安卓版本时会加上分发渠道号
	curVersion = curVersion + "_" + SERVERINFODATAINFO->Get_tuiguang_ad_Channel();

	CSQueryVersionPacket packet(curVersion);
	packet.SendHttp();
}

	/*
		获取完更新信息的操作
	*/
void UpdateSystem::HandleAfterGetVersionInfo(){
	NFC_showCommunicationWating(false);
	//2.处理结束检查更新相关事宜
	if (ret_==kUSuccess)
	{
		m_bHasUpdated=false;
		_finishUnzipResource();	//放开window等加载限制
	}else if(ret_==kUNeedUpdate){
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_DOWNLOAD);
		HandleCheckVersionAndDownload();
	}else if(ret_==kUServerNotSupport){
		NFC_showMessageBoxSingle(kLOGIN_NOSURPOTHINT,SysLangDataManager::get_instance2()->GetSysLangById(594));
	}
}

//结束解压资源包，准备显示正常游戏
void UpdateSystem::_finishUnzipResource(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_SUCCESS_);
	if (UPDATESYSTEM->IsHasUpdated())
	{
		cocos2d::CCFileUtils::sharedFileUtils()->purgeCachedEntries();
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_VERSIONUPDATE_FINISHED_, _to_event_param_(true));
	}
	else
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_VERSIONUPDATE_FINISHED_, _to_event_param_(false));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	ServerInfoDataHandler::get_instance2()->QueryNoticeGatewayData();
}

	/*
		处理成功获取版本信息后
	*/
static bool orderByVersionId(Versions obj1, Versions obj2)
{
	if (obj1.mVersion.compare(obj2.mVersion) <= 0)
		return true;

	return false;
}

void UpdateSystem::HandleCheckVersionAndDownload(){
	m_AllVersionList.sort(orderByVersionId);
	std::string version;

	char version2[1024] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version2, sizeof(version2));
	version = version2;


	// 根据当前版本判断是否需要更新
	std::list<Versions>::iterator iter   = m_AllVersionList.begin();
	std::list<Versions>::iterator iter_e = m_AllVersionList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		Versions temp = *iter;
		if (temp.mVersion.compare(version) > 0)
		{
			if (temp.mNeedUpdate)
			{
				m_UpdateVersionList.push_back(temp);
			}
		}
	}

	// 无需下载，直接进行文件校验吧
	if (m_UpdateVersionList.size() == 0)
	{
		m_bHasUpdated = false;
		_finishUnzipResource();
		return;
	}

	// 判断是否需要强制更新版本
	do 
	{
		bool bAppUpdate = false;
		std::list<Versions>::iterator iter = m_UpdateVersionList.begin();
		std::list<Versions>::iterator iter_e = m_UpdateVersionList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			Versions temp = *iter;
			if (temp.mNeedAppUpdate)
			{
				bAppUpdate = true;
				appUpdateURL_ = temp.mAppUpdateURL;
				break;
			}
		}

		if (!bAppUpdate)
			break;

		//提示到商店更新
		NFC_showMessageBoxSingle(kLOGIN_APPSTOREHINT,SysLangDataManager::get_instance2()->GetSysLangById(593));
		return;
	} 
	while (false);

	//提示小版本更新
	NFC_showMessageBox(kLOGIN_UPDATEHINT,SysLangDataManager::get_instance2()->GetSysLangById(592));
}

//开始小版本更新
void UpdateSystem::StartUpdateOnline(){
	// 开始下载
	m_bHasUpdated = true;
	m_UpdateVersionSize = m_UpdateVersionList.size();
	m_pAntManager->DownLoadZipFile(m_UpdateVersionList.front().mZipURL, m_UpdateVersionList.front().mZipMD5);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(m_UpdateVersionSize),_to_event_param_(totalCount_));
}

	/*
		准备Appstore下载
	*/
void UpdateSystem::HandleAppStoreDownload(){
	// 注意：
	// IOS下面所有版本强制更新一般都去统一的App Store地址
	// Android下面，如果只维护一个更新的apk包，则直接使用任何一个版本的mAppUpdateURL即可
	// 否则，需要使用当前最新版本的mAppUpdateURL来下载
#ifdef kENABLE_PLATFORM_SDKIOS
	NFC_quitGame();
#else
	cocos2d::CCDirector::sharedDirector()->getSystem()->forceUpdate(appUpdateURL_); 
#endif
}


	/*
		确保大版本更新时，download文件夹已经删除
	*/
void UpdateSystem::ConfirmSandBoxDownloadHasBeenCleared(){
	char version1[1024] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Version", version1, sizeof(version1));

	char version2[1024] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version2, sizeof(version2));
	//
	//如果刚做了大版本更新，则清理download文件夹
	if (version2[0]!='\0' && std::string(version2).compare(version1) < 0){
		// 先删除download目录
		ENGINESYSTEM->DeleteDocumentSubDir(_ANT_DOWNLOAD_DIR_);
		ENGINESYSTEM->CreateDocumentSubDir(_ANT_DOWNLOAD_DIR_);


		// 删除ZIP文件
		std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
		zipName = zipName+_ANT_ZIP_NAME_;
		FileLoader loader;
		loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
		loader.unload();

		// 已大版本更新，则在account中设置当前系统版本号
		VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version1);
	}
}

/**
         * 版本检查返回<br>
         * byte ret 0版本正常 ，1版本需要更新，2版本在当前服务器不支持，不可以进入游戏；
         * if(ret == 1){<br>
         * short count 需要更新的版本数量<br>
         * for(count){<br>
         * String newversion 新版本号<br>
         * byte type 0，小版本资源更新； 1大版本更新重新下载。<br>
         *String md5 <br>
         * String url 资源地址<br>
         * }<br>
         * }<br>
         */
void UpdateSystem::decodePacketData(cobra_win::DPacket & packet){
	m_UpdateVersionList.clear();
	char *tmpChar=NULL;
	packet>>ret_;
	if (ret_==kUNeedUpdate)
	{
		unsigned short count;
		packet>>count;
		for (int i=0;i<count;i++)
		{
			Versions theVersion;
			//new version
			NFC_ParsePacketString(packet,theVersion.mVersion);
			//type
			unsigned char type;
			packet>>type;
			if (type==0)//小版本
				theVersion.mNeedUpdate=true;
			else
				theVersion.mNeedAppUpdate=true;
			//md5
			NFC_ParsePacketString(packet,theVersion.mZipMD5);
			//url
			std::string theURL;
			NFC_ParsePacketString(packet,theURL);
			if (type==1)//大版本
				theVersion.mAppUpdateURL=theURL;
			theVersion.mZipURL=theURL;
			m_UpdateVersionList.push_back(theVersion);
		}
		totalCount_=m_UpdateVersionList.size();
	}
}

/*
	ErrorCode: -14 为MD5校验错误
*/
void UpdateSystem::OnZipFileDownLoadFailedHandler(int errorCode)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_FAILED_);
}

void UpdateSystem::OnZipFileDownLoadSucceededHandler(double length)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_PROGRESS_, _to_event_param_(100));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_SUCCESS_);
}

void UpdateSystem::OnZipFileDownLoadProgressHandler(double total, double downloaded)
{
	if (total <= 0.1f)
		return;

	float precent = (float)((downloaded/total)*100.0f);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_PROGRESS_, _to_event_param_(precent));
}

/*
	目前没用处
*/
void UpdateSystem::OnVerifyZipFileFailedHandler()
{
#if 0
	// ZIP文件有问题，到时候重新下载吧
	std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	zipName = zipName+_ANT_ZIP_NAME_;
	FileLoader loader;
	loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	loader.unload();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_FAILED_);
#endif
}

void UpdateSystem::OnVerifyZipFileSucceededHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_SUCCESS_);
}

void UpdateSystem::OnUnZipStartHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_BEGIN_UNZIP_ZIPFILE_);
}

void UpdateSystem::OnUnZipFailedHandler(int errorCode)
{
	LOGGERSYSTEM->LogInfo("UnZip Failed, errorCode=%d", errorCode);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_FAILED_);

	// ZIP文件有问题，到时候重新下载吧
	std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	zipName = zipName+_ANT_ZIP_NAME_;
	FileLoader loader;
	loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	loader.unload();
}

void UpdateSystem::OnUnZipSucceededHandler()
{
	std::string version = m_UpdateVersionList.front().mVersion;

	// 删除ZIP文件
	std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	zipName = zipName+_ANT_ZIP_NAME_;
	FileLoader loader;
	loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	loader.unload();

	// 保存当前版本信息
	VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", (char*)version.c_str());

	// 继续下载
	m_UpdateVersionList.pop_front();
	if (m_UpdateVersionList.size() == 0){
		//下载全部完成
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(0),_to_event_param_(totalCount_));
		_finishUnzipResource();
		//弹出重启游戏提示
		NFC_showMessageBoxSingle(kUPDATE_FINISH,SysLangDataManager::get_instance2()->GetSysLangById(1217));
		return;
	}
	m_pAntManager->DownLoadZipFile(m_UpdateVersionList.front().mZipURL, m_UpdateVersionList.front().mZipMD5);
	int count=m_UpdateVersionList.size();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(count),_to_event_param_(totalCount_));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_SUCCESS_);
}
