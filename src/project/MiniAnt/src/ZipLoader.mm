#include <platform/CCPlatformMacros.h>
#include <support/zip_support/unzip.h>
#include "../include/ZipLoader.h"
#include "../include/IAntManager.h"
#include <curl/curl.h>
#include <include/common/MD5Crypto.h>
#include <include/common/String.h>
#include <include/common/FileLoader.h>
using  namespace  miniant;
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <signal.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <Foundation/Foundation.h>
#endif


#define BUFFER_SIZE    8192

class DownLoadZipFailedEvent : public IEvent
{
public:
	int m_ErrorId;

public:
	DownLoadZipFailedEvent()
	{

	}
	virtual ~DownLoadZipFailedEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnZipFileDownLoadFailedHandler(m_ErrorId);
	}
};

class DownLoadZipSuccessedEvent : public IEvent
{
public:
	double  m_FileTotalBytes;  // 文件大小

public:
	DownLoadZipSuccessedEvent()
	{
		m_FileTotalBytes = 0;
	}
	virtual ~DownLoadZipSuccessedEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnZipFileDownLoadSucceededHandler(m_FileTotalBytes);
	}
};

class DownLoadZipProgressEvent : public IEvent
{
public:
	double  m_FileTotalBytes;  // 文件大小
	double  m_DownLoadedBytes; // 当前下载数目

public:
	DownLoadZipProgressEvent()
	{

	}
	virtual ~DownLoadZipProgressEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnZipFileDownLoadProgressHandler(m_FileTotalBytes, m_DownLoadedBytes);
	}
};

class VerifyZipFailedEvent : public IEvent
{
public:
	VerifyZipFailedEvent()
	{

	}
	virtual ~VerifyZipFailedEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnVerifyZipFileFailedHandler();
	}
};

class VerifyZipSucceededEvent : public IEvent
{
public:
	VerifyZipSucceededEvent()
	{

	}
	virtual ~VerifyZipSucceededEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnVerifyZipFileSucceededHandler();
	}
};

class UnZipStartEvent : public IEvent
{
public:
	UnZipStartEvent()
	{

	}
	virtual ~UnZipStartEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnUnZipStartHandler();
	}
};

class UnZipSuccessedEvent : public IEvent
{
public:
	UnZipSuccessedEvent()
	{

	}
	virtual ~UnZipSuccessedEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnUnZipSucceededHandler();
	}
};

class UnZipFailedEvent : public IEvent
{
public:
	int m_ErrorCode; // 错误码

public:
	UnZipFailedEvent()
	{
		m_ErrorCode = 0;
	}
	virtual ~UnZipFailedEvent()
	{

	}

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnUnZipFailedHandler(m_ErrorCode);
	}
};

ZipLoader::ZipLoader()
{
	m_InitZipLength = 0;
}

ZipLoader::~ZipLoader()
{

}

void ZipLoader::SetZipURL(std::string url)
{
	m_ZipURL = url;
}

void ZipLoader::SetZipMD5(std::string md5)
{
	m_ZipMD5 = md5;
}

static void thread_exit_handler(int sig)
{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_exit(0);
#endif
}

bool ZipLoader::create_thread()
{
	bool bRet = IThread::create_thread();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif

#if 0
	struct sigaction actions;
	memset(&actions, 0, sizeof(actions)); 
	sigemptyset(&actions.sa_mask);
	actions.sa_flags   = 0; 
	actions.sa_handler = thread_exit_handler;
	sigaction(SIGUSR1, &actions, NULL);
#endif

	return bRet;
}

static  bool  CreateDir(std::string path);
static  int   UnZip();

static  unsigned char*  GetFileData(const char* pFileName, unsigned long& iLength)
{
	FileLoader loader;
	if (!loader.load((char*)pFileName, FileLoader::_TYPED_READ_ONLY_))
		return NULL;

	iLength = loader.length();
	char* pBuffer = new char[iLength+1];
	memset(pBuffer, 0, iLength+1);
	loader.read(pBuffer, iLength);

	loader.unload();

	return (unsigned char*)pBuffer;
}

void* ZipLoader::run()
{
	int errorId = 0;
	CURL* pCurl = NULL;
	struct curl_slist* headers = NULL;
	long long fileLength = 0;

	// 判断是断点续传还是非断点续传
	std::string path = CreateAntManager()->GetDocumentDir();
	path += _ANT_ZIP_NAME_;
	if (CreateAntManager()->IsAppendDownLoadZip())
		m_ZipFile.load((char*)path.c_str(), FileLoader::_TYPED_APPEND_WRITE_);
	else
		m_ZipFile.load((char*)path.c_str(), FileLoader::_TYPED_CLEAR_WRITE_);
	
	m_InitZipLength = m_ZipFile.length();
	do 
	{
		bool bNeedDowndLoad = true;

		// 如果为续传下载，先判断是否下载完成了
		if (CreateAntManager()->IsAppendDownLoadZip() && m_InitZipLength>0)
		{// 如果文件不为空，直接先判断MD5
			unsigned long iTemp  = 0;
			unsigned char* pTemp = GetFileData(path.c_str(), iTemp);
			std::string md5 = MD5Crypto::md5((unsigned char*)pTemp, (unsigned int)iTemp);
			if (String::compare((char*)md5.c_str(), (char*)m_ZipMD5.c_str(), false))
			{
				fileLength     = m_InitZipLength;
				bNeedDowndLoad = false;
				m_ZipFile.unload();
			}
			delete[] pTemp;
		}
		
		std::string downloadMD5 = "";
		// 是否继续下载
		if (bNeedDowndLoad)
		{
			pCurl = curl_easy_init();
			if (pCurl == NULL)
			{
				errorId = -1;
				break;
			}

			CURLcode ret = curl_easy_setopt(pCurl, CURLOPT_URL, m_ZipURL.c_str());
			if (ret != CURLE_OK)
			{
				errorId = -2;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
			if (ret != CURLE_OK)
			{
				errorId = -3;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L);
			if (ret != CURLE_OK)
			{
				errorId = -4;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, OnHTTPDataWriter);
			if (ret != CURLE_OK)
			{
				errorId = -6;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &m_ZipFile);
			if (ret != CURLE_OK)
			{
				errorId = -7;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, false);
			if (ret != CURLE_OK)
			{
				errorId = -8;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, OnHTTPProgress);
			if (ret != CURLE_OK)
			{
				errorId = -9;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_PROGRESSDATA, &m_InitZipLength);
			if (ret != CURLE_OK)
			{
				errorId = -10;
				break;
			}

			if (CreateAntManager()->IsDebug())
			{
				ret = curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1);
				if (ret != CURLE_OK)
				{
					errorId = -11;
					break;
				}

				ret = curl_easy_setopt(pCurl, CURLOPT_DEBUGFUNCTION, OnHTTPDebuger);
				if (ret != CURLE_OK)
				{
					errorId = -12;
					break;
				}
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, 60*1);
			if (ret != CURLE_OK)
			{
				errorId = -13;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_LOW_SPEED_LIMIT, 1L);
			if (ret != CURLE_OK)
			{
				errorId = -14;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_LOW_SPEED_TIME, 5L);
			if (ret != CURLE_OK)
			{
				errorId = -15;
				break;
			}

			if (CreateAntManager()->IsLocation())
			{
				ret = curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);
				if (ret != CURLE_OK)
				{
					errorId = -16;
					break;
				}
			}

			headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
			headers = curl_slist_append(headers, "Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3");
			headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
			headers = curl_slist_append(headers, "Connection: keep-alive");
			headers = curl_slist_append(headers, "Pragma: no-cache");
			headers = curl_slist_append(headers, "Cache-Control: no-cache");
			headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:28.0) Gecko/20100101 Firefox/28.0");
			if (CreateAntManager()->IsAppendDownLoadZip())
			{
				char range[128] = "";
				sprintf(range, "Range: bytes=%lld-", m_InitZipLength);
				headers = curl_slist_append(headers, range);
			}
			ret = curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headers);
			if (ret != CURLE_OK)
			{
				errorId = -17;
				break;
			}

			ret = curl_easy_perform(pCurl);
			if (ret != CURLE_OK)
			{
				if (ret >= 0)
					errorId = ret;
				else
					errorId = -18;
				break;
			}

			int code = 0;
			ret = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &code);
			if (ret!=CURLE_OK || (code!=200&&code!=206))
			{
				errorId = -19;
				break;
			}

			double length = 0;
			ret = curl_easy_getinfo(pCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &length);
			if (ret != CURLE_OK)
			{
				errorId = -20;
				break;
			}

			// 下载完毕
			curl_slist_free_all(headers);
			headers = NULL;

			curl_easy_cleanup(pCurl);
			pCurl = NULL;
			m_ZipFile.unload();

			// MD5比对
			unsigned long iTemp  = 0;
			unsigned char* pTemp = GetFileData(path.c_str(), iTemp);
			if (iTemp==0 || pTemp==NULL)
			{
				errorId = -21;
				break;
			}

			// 如果文件大小小于下载的length，说明下载为完成，失败了
			if (iTemp < length)
			{
				delete[] pTemp;
				errorId = -22;
				break;
			}

			downloadMD5 = MD5Crypto::md5((unsigned char*)pTemp, (unsigned int)iTemp);
			delete[] pTemp;

			fileLength = iTemp;
		}

		// 插入下载成功事件
		IEvent* pEvent = new DownLoadZipSuccessedEvent;
		((DownLoadZipSuccessedEvent*)pEvent)->m_FileTotalBytes = fileLength;
		CreateAntManager()->PushEvent(pEvent);

		// 进行ZIP的MD5校验
		if (!String::compare((char*)downloadMD5.c_str(), (char*)m_ZipMD5.c_str(), false))
		{
			// 解压缩失败事件
			pEvent = new VerifyZipFailedEvent;
			CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
			pthread_exit(0);
#endif
			return NULL;
		}
		
		pEvent = new VerifyZipSucceededEvent;
		CreateAntManager()->PushEvent(pEvent);

		pEvent = new UnZipStartEvent;
		CreateAntManager()->PushEvent(pEvent);

		// 解压缩文件
		int ret = UnZip();
		if (ret != 0)
		{
			// 解压缩失败事件
			pEvent = new UnZipFailedEvent;
			((UnZipFailedEvent*)pEvent)->m_ErrorCode = ret;
			CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
			pthread_exit(0);
#endif
			return NULL;
		}

		//解压缩成功事件
		pEvent = new UnZipSuccessedEvent;
		CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		pthread_exit(0);
#endif
		return NULL;
	} 
	while (false);

	m_ZipFile.unload();

	if (headers != NULL)
	{
		curl_slist_free_all(headers);
		headers = NULL;
	}

	if (pCurl != NULL)
	{
		curl_easy_cleanup(pCurl);
		pCurl = NULL;
	}

	// 插入失败事件
	DownLoadZipFailedEvent* pEvent = new DownLoadZipFailedEvent;
	pEvent->m_ErrorId = errorId;
	CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	pthread_exit(0);
#endif
	return NULL;
}

void ZipLoader::post_close_message()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	pthread_cancel(m_hHandle);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//pthread_kill(m_hHandle, SIGUSR1);
#endif
}

int ZipLoader::OnHTTPProgress(void* pPtr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	long initLen = *(long*)pPtr;

	// 插入下载进度事件
	DownLoadZipProgressEvent* pEvent = new DownLoadZipProgressEvent;
	pEvent->m_FileTotalBytes = totalToDownload+initLen;
	pEvent->m_DownLoadedBytes= nowDownloaded+initLen;
	CreateAntManager()->PushEvent(pEvent);

	return 0;
}

int ZipLoader::OnHTTPDataWriter(char* pData, size_t size, size_t nmemb, void* pFile)
{
	if (pData == NULL)
		return 0;

	((FileLoader*)pFile)->write(pData, size*nmemb);
	return size*nmemb;
}

int ZipLoader::OnHTTPDebuger(CURL*, curl_infotype itype, char* pData, size_t size, void*)
{
	if(itype == CURLINFO_TEXT)  
	{  
		;
	}  
	else if(itype == CURLINFO_HEADER_IN)  
	{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		NSLog(@"[ZipLoader HEADER_IN] = %s\n", pData);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		printf("[ZipLoader HEADER_IN] = %s\n", pData);
#endif
	}  
	else if(itype == CURLINFO_HEADER_OUT)  
	{  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		NSLog(@"[ZipLoader HEADER_OUT] = %s\n", pData);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		printf("[ZipLoader HEADER_OUT] = %s\n", pData);
#endif
	}  
	else if(itype == CURLINFO_DATA_IN)  
	{  
		;
	}  
	else if(itype == CURLINFO_DATA_OUT)  
	{  
		;
	}  

	return 0;
}

static bool CreateDir(std::string path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	mode_t processMask = umask(0);
	int ret = mkdir(path.c_str(), S_IRUSR|S_IWUSR|S_IXUSR|S_IRWXU|S_IRWXG|S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
		return false;

	return true;
#else
	BOOL ret = CreateDirectoryA(path.c_str(), NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
		return false;

	return true;
#endif
}

static int UnZip()
{
	std::string path = CreateAntManager()->GetDocumentDir();
	path += _ANT_ZIP_NAME_;
	unzFile pZipFile = cocos2d::unzOpen(path.c_str());
	if (pZipFile == NULL)
	{
		return -1;
	}

	// Get info about the zip file
	cocos2d::unz_global_info global_info;
	if (cocos2d::unzGetGlobalInfo(pZipFile, &global_info) != UNZ_OK)
	{
		cocos2d::unzClose(pZipFile);
		return -2;
	}

	// Loop to extract all files.
	char readBuffer[BUFFER_SIZE] = "";
	for (unsigned long i = 0; i<global_info.number_entry; ++i)
	{
		// Get info about current file.
		cocos2d::unz_file_info fileInfo;
		char fileName[512] = "";
		if (unzGetCurrentFileInfo(pZipFile, &fileInfo, fileName, sizeof(fileName), NULL, 0, NULL, 0) != UNZ_OK)
		{
			cocos2d::unzClose(pZipFile);
			return -3;
		}

		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength-1] == '/')
		{// Entry is a direcotry, so create it.
			std::string dirPath = CreateAntManager()->GetDocumentDir();
			dirPath += _ANT_DOWNLOAD_DIR_;
			dirPath += fileName;
			if (!CreateDir(dirPath))
			{
				cocos2d::unzClose(pZipFile);
				return -4;
			}
		}
		else
		{
			// Open current file.
			if (cocos2d::unzOpenCurrentFile(pZipFile) != UNZ_OK)
			{
				cocos2d::unzClose(pZipFile);
				return -5;
			}

			// Create a file to store current file.
			std::string filePath = CreateAntManager()->GetDocumentDir();
			filePath += _ANT_DOWNLOAD_DIR_;
			filePath += fileName;
			FileLoader loader;
			if (!loader.load((char*)filePath.c_str(), FileLoader::_TYPED_CLEAR_WRITE_))
			{
				loader.unload();
				cocos2d::unzCloseCurrentFile(pZipFile);
				cocos2d::unzClose(pZipFile);
				return -6;
			}
			loader.unload();

			if (!loader.load((char*)filePath.c_str(), FileLoader::_TYPED_READ_APPEND_WRITE_))
			{
				loader.unload();
				cocos2d::unzCloseCurrentFile(pZipFile);
				cocos2d::unzClose(pZipFile);
				return -7;
			}

			int error = UNZ_OK;
			do
			{
				error = cocos2d::unzReadCurrentFile(pZipFile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					loader.unload();
					cocos2d::unzCloseCurrentFile(pZipFile);
					cocos2d::unzClose(pZipFile);
					return -8;
				}

				if (error > 0)
					loader.write(readBuffer, error);
			} 
			while(error > 0);

			loader.unload();
		}

		cocos2d::unzCloseCurrentFile(pZipFile);

		// Goto next entry listed in the zip file.
		if ((i+1) < global_info.number_entry)
		{
			if (cocos2d::unzGoToNextFile(pZipFile) != UNZ_OK)
			{
				cocos2d::unzClose(pZipFile);
				return -9;
			}
		}
	}

	cocos2d::unzClose(pZipFile);
	return 0;
}
