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
	//��汾���º�����download�ļ���
	ConfirmSandBoxDownloadHasBeenCleared();

	//��ʼ��������
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
		����汾��Ϣ
	*/
void UpdateSystem::QueryVersionInfo(){
	NFC_showCommunicationWating(true);
	SERVERINFODATAINFO->CurSendHttpPacketType_=_HTTP_STATE_DISTINCT_;
	std::string curVersion=DOTATribeApp::get_instance2()->GetVersion();

	//��׿�汾ʱ����Ϸַ�������
	curVersion = curVersion + "_" + SERVERINFODATAINFO->Get_tuiguang_ad_Channel();

	CSQueryVersionPacket packet(curVersion);
	packet.SendHttp();
}

	/*
		��ȡ�������Ϣ�Ĳ���
	*/
void UpdateSystem::HandleAfterGetVersionInfo(){
	NFC_showCommunicationWating(false);
	//2.��������������������
	if (ret_==kUSuccess)
	{
		m_bHasUpdated=false;
		_finishUnzipResource();	//�ſ�window�ȼ�������
	}else if(ret_==kUNeedUpdate){
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_DOWNLOAD);
		HandleCheckVersionAndDownload();
	}else if(ret_==kUServerNotSupport){
		NFC_showMessageBoxSingle(kLOGIN_NOSURPOTHINT,SysLangDataManager::get_instance2()->GetSysLangById(594));
	}
}

//������ѹ��Դ����׼����ʾ������Ϸ
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
		����ɹ���ȡ�汾��Ϣ��
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


	// ���ݵ�ǰ�汾�ж��Ƿ���Ҫ����
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

	// �������أ�ֱ�ӽ����ļ�У���
	if (m_UpdateVersionList.size() == 0)
	{
		m_bHasUpdated = false;
		_finishUnzipResource();
		return;
	}

	// �ж��Ƿ���Ҫǿ�Ƹ��°汾
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

		//��ʾ���̵����
		NFC_showMessageBoxSingle(kLOGIN_APPSTOREHINT,SysLangDataManager::get_instance2()->GetSysLangById(593));
		return;
	} 
	while (false);

	//��ʾС�汾����
	NFC_showMessageBox(kLOGIN_UPDATEHINT,SysLangDataManager::get_instance2()->GetSysLangById(592));
}

//��ʼС�汾����
void UpdateSystem::StartUpdateOnline(){
	// ��ʼ����
	m_bHasUpdated = true;
	m_UpdateVersionSize = m_UpdateVersionList.size();
	m_pAntManager->DownLoadZipFile(m_UpdateVersionList.front().mZipURL, m_UpdateVersionList.front().mZipMD5);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(m_UpdateVersionSize),_to_event_param_(totalCount_));
}

	/*
		׼��Appstore����
	*/
void UpdateSystem::HandleAppStoreDownload(){
	// ע�⣺
	// IOS�������а汾ǿ�Ƹ���һ�㶼ȥͳһ��App Store��ַ
	// Android���棬���ֻά��һ�����µ�apk������ֱ��ʹ���κ�һ���汾��mAppUpdateURL����
	// ������Ҫʹ�õ�ǰ���°汾��mAppUpdateURL������
#ifdef kENABLE_PLATFORM_SDKIOS
	NFC_quitGame();
#else
	cocos2d::CCDirector::sharedDirector()->getSystem()->forceUpdate(appUpdateURL_); 
#endif
}


	/*
		ȷ����汾����ʱ��download�ļ����Ѿ�ɾ��
	*/
void UpdateSystem::ConfirmSandBoxDownloadHasBeenCleared(){
	char version1[1024] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Version", version1, sizeof(version1));

	char version2[1024] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version2, sizeof(version2));
	//
	//��������˴�汾���£�������download�ļ���
	if (version2[0]!='\0' && std::string(version2).compare(version1) < 0){
		// ��ɾ��downloadĿ¼
		ENGINESYSTEM->DeleteDocumentSubDir(_ANT_DOWNLOAD_DIR_);
		ENGINESYSTEM->CreateDocumentSubDir(_ANT_DOWNLOAD_DIR_);


		// ɾ��ZIP�ļ�
		std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
		zipName = zipName+_ANT_ZIP_NAME_;
		FileLoader loader;
		loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
		loader.unload();

		// �Ѵ�汾���£�����account�����õ�ǰϵͳ�汾��
		VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", version1);
	}
}

/**
         * �汾��鷵��<br>
         * byte ret 0�汾���� ��1�汾��Ҫ���£�2�汾�ڵ�ǰ��������֧�֣������Խ�����Ϸ��
         * if(ret == 1){<br>
         * short count ��Ҫ���µİ汾����<br>
         * for(count){<br>
         * String newversion �°汾��<br>
         * byte type 0��С�汾��Դ���£� 1��汾�����������ء�<br>
         *String md5 <br>
         * String url ��Դ��ַ<br>
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
			if (type==0)//С�汾
				theVersion.mNeedUpdate=true;
			else
				theVersion.mNeedAppUpdate=true;
			//md5
			NFC_ParsePacketString(packet,theVersion.mZipMD5);
			//url
			std::string theURL;
			NFC_ParsePacketString(packet,theURL);
			if (type==1)//��汾
				theVersion.mAppUpdateURL=theURL;
			theVersion.mZipURL=theURL;
			m_UpdateVersionList.push_back(theVersion);
		}
		totalCount_=m_UpdateVersionList.size();
	}
}

/*
	ErrorCode: -14 ΪMD5У�����
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
	Ŀǰû�ô�
*/
void UpdateSystem::OnVerifyZipFileFailedHandler()
{
#if 0
	// ZIP�ļ������⣬��ʱ���������ذ�
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

	// ZIP�ļ������⣬��ʱ���������ذ�
	std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	zipName = zipName+_ANT_ZIP_NAME_;
	FileLoader loader;
	loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	loader.unload();
}

void UpdateSystem::OnUnZipSucceededHandler()
{
	std::string version = m_UpdateVersionList.front().mVersion;

	// ɾ��ZIP�ļ�
	std::string zipName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	zipName = zipName+_ANT_ZIP_NAME_;
	FileLoader loader;
	loader.load((char*)zipName.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	loader.unload();

	// ���浱ǰ�汾��Ϣ
	VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "Version", "Version", (char*)version.c_str());

	// ��������
	m_UpdateVersionList.pop_front();
	if (m_UpdateVersionList.size() == 0){
		//����ȫ�����
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(0),_to_event_param_(totalCount_));
		_finishUnzipResource();
		//����������Ϸ��ʾ
		NFC_showMessageBoxSingle(kUPDATE_FINISH,SysLangDataManager::get_instance2()->GetSysLangById(1217));
		return;
	}
	m_pAntManager->DownLoadZipFile(m_UpdateVersionList.front().mZipURL, m_UpdateVersionList.front().mZipMD5);
	int count=m_UpdateVersionList.size();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,_to_event_param_(count),_to_event_param_(totalCount_));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_SUCCESS_);
}
