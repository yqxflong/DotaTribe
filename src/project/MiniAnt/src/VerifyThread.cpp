#include <platform/CCPlatformMacros.h>
#include "../include/VerifyThread.h"
#include "../include/IAntManager.h"
#include <include/common/MD5Crypto.h>
#include <include/common/String.h>
#include <include/common/FileLoader.h>
using  namespace  miniant;
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <signal.h>
#endif

class VerifySucceedEvent : public IEvent
{
public:
	VerifySucceedEvent() { }
	virtual ~VerifySucceedEvent() { }

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnVerifyFileSucceededHandler();
	}
};

class VerifyFailedEvent : public IEvent
{
public:
	std::string m_InvalidFile; // 校验错误的文件名称

public:
	VerifyFailedEvent() { }
	virtual ~VerifyFailedEvent() { }

public:
	virtual  void  OnEventHandler()
	{
		IAntCallbackHandler* pHandler = CreateAntManager()->GetCallbackHandler();
		if (pHandler == NULL)
			return;

		pHandler->OnVerifyFileFailedHandler(m_InvalidFile);
	}
};

VerifyThread::VerifyThread()
{

}

VerifyThread::~VerifyThread()
{

}

void VerifyThread::SetVerifyFileList(std::map<std::string, std::string> fileList)
{
	m_VerifyList = fileList;
}

static void thread_exit_handler(int sig)
{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_exit(0);
#endif
}

bool VerifyThread::create_thread()
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

void* VerifyThread::run()
{
	std::string invalidFileName = "";
	do 
	{
		bool bError = false;
		std::map<std::string, std::string>::iterator iter   = m_VerifyList.begin();
		std::map<std::string, std::string>::iterator iter_e = m_VerifyList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			std::string file = iter->first;
			std::string md5  = iter->second;

			// 加载指定文件
			unsigned long iTemp  = 0;
			unsigned char* pTemp = GetFileData(file.c_str(), iTemp);
			if (iTemp==0 || pTemp==NULL)
			{
				bError = true;
				invalidFileName = file;
				break;
			}

			std::string tempMD5 = MD5Crypto::md5((unsigned char*)pTemp, (unsigned int)iTemp);
			if (!String::compare((char*)tempMD5.c_str(), (char*)md5.c_str(), false))
			{
				delete[] pTemp;
				bError = true;
				invalidFileName = file;
				break;
			}

			delete[] pTemp;
		}

		// 是否出错了
		if (bError)
			break;

		// MD5校验成功通过
		VerifySucceedEvent* pEvent = new VerifySucceedEvent;
		CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
		pthread_exit(0);
#endif
		return NULL;
	} 
	while (false);

	// MD5校验成功失败
	VerifyFailedEvent* pEvent = new VerifyFailedEvent;
	pEvent->m_InvalidFile = invalidFileName;
	CreateAntManager()->PushEvent(pEvent);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	pthread_exit(0);
#endif

	return NULL;
}

void VerifyThread::post_close_message()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	pthread_cancel(m_hHandle);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//pthread_kill(m_hHandle, SIGUSR1);
#endif
}
