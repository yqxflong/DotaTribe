#include <platform/CCPlatformMacros.h>
#include "../include/URLLoader.h"
#include "../include/IAntManager.h"
#include <include/common/String.h>
#include <curl/curl.h>
using  namespace  miniant;
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <signal.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <Foundation/Foundation.h>
#endif


class DownLoadURLFailedEvent : public IEvent
{
public:
	int m_Tag;
	int m_ErrorId;

public:
	DownLoadURLFailedEvent() { }
	virtual ~DownLoadURLFailedEvent() { }

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnURLFileDownLoadFailedHandler(m_Tag, m_ErrorId);
	}
};

class DownLoadURLSuccessedEvent : public IEvent
{
public:
	int m_Tag;
	std::string m_Content;

public:
	DownLoadURLSuccessedEvent() { }
	virtual ~DownLoadURLSuccessedEvent() { }

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnURLFileDownLoadSucceededHandler(m_Tag, m_Content);
	}
};

class DownLoadURLProgressEvent : public IEvent
{
public:
	double  m_FileTotalBytes;  // 文件大小
	double  m_DownLoadedBytes; // 当前下载数目

public:
	DownLoadURLProgressEvent() { }
	virtual ~DownLoadURLProgressEvent() { }

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnURLFileDownLoadProgressHandler(m_FileTotalBytes, m_DownLoadedBytes);
	}
};

URLLoader::URLLoader()
{
	m_URLTag = 0;
}

URLLoader::~URLLoader()
{

}

void URLLoader::SetURL(std::string url)
{
	m_URL = url;
}

void URLLoader::SetURLTag(int tag)
{
	m_URLTag = tag;
}

static void thread_exit_handler(int sig)
{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_exit(0);
#endif
}

bool URLLoader::create_thread()
{
	m_URLContent.clear();
	m_URLContent.reserve(4096);

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

void* URLLoader::run()
{
	int errorId = 0;
	CURL* pCurl = NULL;
	struct curl_slist* headers = NULL;

	do 
	{
		pCurl = curl_easy_init();
		if (pCurl == NULL)
		{
			errorId = -1;
			break;
		}

		CURLcode ret = curl_easy_setopt(pCurl, CURLOPT_URL, m_URL.c_str());
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
			errorId = -5;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &m_URLContent);
		if (ret != CURLE_OK)
		{
			errorId = -6;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, false);
		if (ret != CURLE_OK)
		{
			errorId = -7;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, OnHTTPProgress);
		if (ret != CURLE_OK)
		{
			errorId = -8;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_PROGRESSDATA, this);
		if (ret != CURLE_OK)
		{
			errorId = -11;
			break;
		}

		if (CreateAntManager()->IsDebug())
		{
			ret = curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1);
			if (ret != CURLE_OK)
			{
				errorId = -12;
				break;
			}

			ret = curl_easy_setopt(pCurl, CURLOPT_DEBUGFUNCTION, OnHTTPDebuger);
			if (ret != CURLE_OK)
			{
				errorId = -13;
				break;
			}
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, 60*1);
		if (ret != CURLE_OK)
		{
			errorId = -12;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_LOW_SPEED_LIMIT, 1L);
		if (ret != CURLE_OK)
		{
			errorId = -13;
			break;
		}

		ret = curl_easy_setopt(pCurl, CURLOPT_LOW_SPEED_TIME, 5L);
		if (ret != CURLE_OK)
		{
			errorId = -14;
			break;
		}

		if (CreateAntManager()->IsLocation())
		{
			ret = curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);
			if (ret != CURLE_OK)
			{
				errorId = -15;
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
		ret = curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headers);
		if (ret != CURLE_OK)
		{
			errorId = -16;
			break;
		}

		ret = curl_easy_perform(pCurl);
		if (ret != CURLE_OK)
		{
			if (ret >= 0)
				errorId = ret;
			else
				errorId = -17;
			break;
		}

		int code = 0;
		ret = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &code);
		if (ret!=CURLE_OK || code!=200)
		{
			errorId = -18;
			break;
		}

		double length = 0;
		ret = curl_easy_getinfo(pCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &length);
		if (ret!=CURLE_OK || length<=0 || m_URLContent.length()!=length)
		{
			errorId = -19;
			break;
		}

		// 清除网络连接
		curl_slist_free_all(headers);
		headers = NULL;

		curl_easy_cleanup(pCurl);
		pCurl = NULL;

		// 下载更新文件成功
		DownLoadURLSuccessedEvent* pEvent = new DownLoadURLSuccessedEvent;
		pEvent->m_Content = m_URLContent;
		pEvent->m_Tag     = m_URLTag;
		CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		pthread_exit(0);
#endif
		return NULL;
	} 
	while (false);

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
	DownLoadURLFailedEvent* pEvent = new DownLoadURLFailedEvent;
	pEvent->m_ErrorId = errorId;
	pEvent->m_Tag     = m_URLTag;
	CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	pthread_exit(0);
#endif
	return NULL;
}

void URLLoader::post_close_message()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	pthread_cancel(m_hHandle);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//pthread_kill(m_hHandle, SIGUSR1);
#endif
}

int URLLoader::OnHTTPProgress(void* pPtr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	// 插入下载进度事件
	DownLoadURLProgressEvent* pEvent = new DownLoadURLProgressEvent;
	pEvent->m_FileTotalBytes = totalToDownload;
	pEvent->m_DownLoadedBytes= nowDownloaded;
	CreateAntManager()->PushEvent(pEvent);
	
	return 0;
}

int URLLoader::OnHTTPDataWriter(char* pData, size_t size, size_t nmemb, std::string* pContent)
{
	if (pContent == NULL)
		return 0;

	pContent->append(pData, size*nmemb);
	return size*nmemb;
}

int URLLoader::OnHTTPDebuger(CURL*, curl_infotype itype, char* pData, size_t size, void*)
{
	if(itype == CURLINFO_TEXT)  
	{  
		;
	}  
	else if(itype == CURLINFO_HEADER_IN)  
	{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		NSLog(@"[URLLoader HEADER_IN] = %s\n", pData);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		printf("[URLLoader HEADER_IN] = %s\n", pData);
#endif
	}  
	else if(itype == CURLINFO_HEADER_OUT)  
	{  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		NSLog(@"[URLLoader HEADER_OUT] = %s\n", pData);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		printf("[URLLoader HEADER_OUT] = %s\n", pData);
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
