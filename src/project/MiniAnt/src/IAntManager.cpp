#include <include/common/Lock.h>
#include <include/common/Guard.h>
#include "../include/IAntManager.h"
#include "../include/URLLoader.h"
#include "../include/ZipLoader.h"
#include "../include/VerifyThread.h"
#include <assert.h>
#include <list>
using  namespace  miniant;


namespace  miniant
{


class MiniAntManager : public IAntManager
{
protected:
	std::string m_DocumentDir; // 系统读写目录

protected:
	IAntCallbackHandler* m_pAntCallbackHandler; // 蚂蚁下载器事件回调处理

protected:
	bool           m_bDebug;           // 是否开启调试器模式
	bool           m_bAppendDownLoad;  // 是否续点下载ZIP文件
	bool           m_bLocation;        // 是否支持重定位

protected:
	URLLoader*     m_pURLLoader;       // URL文件下载器
	ZipLoader*     m_pZipLoader;       // ZIP资源包下载器
	VerifyThread*  m_pVerifyThread;    // 文件校验线程

protected:
	std::list<IEvent*>    m_EventList;     // 蚂蚁下载器事件队列
	cobra_win::ThreadLock m_EventListLock; // 蚂蚁下载器事件队列锁

public:
	MiniAntManager();
	virtual ~MiniAntManager();

public:
	/************************************************************************/
	/* 设置下载器内部读写文件的根目录                                       */
	/************************************************************************/
	virtual  void  SetDocumentDir(std::string dir);
	/************************************************************************/
	/* 获取下载器内部读写文件的根目录                                       */
	/************************************************************************/
	virtual  std::string  GetDocumentDir();
	/************************************************************************/
	/* 设置是否支持续点下载ZIP包                                            */
	/* (在某些WIFI情况下，发现如果携带HTTP的Range标签头，则总是返回         */
	/* CURLE_PARTIAL_FILE而无法下载，所以增加该接口)                        */

	/* 默认不支持续点下载                                                   */
	/************************************************************************/
	virtual  void  SetAppendDownLoadZip(bool bAppendDownLoad);
	/************************************************************************/
	/* 获取是否支持续点下载ZIP包                                            */
	/************************************************************************/
	virtual  bool  IsAppendDownLoadZip();
	/************************************************************************/
	/* 设置是否开启调试器                                                   */
	/* 方便输出上行下行的Http Header&Body信息                               */

	/* 默认关闭调试器                                                       */
	/************************************************************************/
	virtual  void  SetDebug(bool bDebug);
	/************************************************************************/
	/* 是否开启调试器                                                       */
	/************************************************************************/
	virtual  bool  IsDebug();
	/************************************************************************/
	/* 设置是否启用重定向功能(Location)                                     */
	/* (在部分WIFi情况下，下载的信息会被location到另外的地址，导致正常的下载*/
	/* ,总是出现302的问题，估增加该接口)                                    */

	/* 设置是否启用重定向功能(Location)                                     */
	/************************************************************************/
	virtual  void  SetLocation(bool bLocation);
	/************************************************************************/
	/* 是否开启重定向功能                                                   */
	/************************************************************************/
	virtual  bool  IsLocation();

public:
	/*
		下载版本更新文件
	*/
	virtual  bool  DownLoadURLFile(int urlTag, std::string url);
	/*
		下载ZIP资源包
	*/
	virtual  bool  DownLoadZipFile(std::string url, std::string md5);
	/*
		进行执行文件列表MD5校验
	*/
	virtual  bool  VerifyFileList(std::map<std::string, std::string> checkList);

public:
	/*
		设置下载更新事件回调接口
	*/
	virtual  void  SetCallbackHandler(IAntCallbackHandler* pCallbackHandler);
	/*
		得到下载更新时间回调接口
	*/
	virtual  IAntCallbackHandler* GetCallbackHandler();

public:
	/*
		插入下载更新事件
	*/
	virtual  void  PushEvent(IEvent* pEvent);

public:
	/*
		初始化蚂蚁下载器
	*/
	virtual  void  Init();
	/*
		蚂蚁下载器逻辑帧更新
	*/
	virtual  void  Tick();
	/*
		销毁蚂蚁下载器
	*/
	virtual  void  Destroy();
};


MiniAntManager::MiniAntManager()
{
	m_pAntCallbackHandler = NULL;
	m_bAppendDownLoad     = true;
	m_bDebug              = false;
	m_bLocation           = true;

	m_pURLLoader    = NULL;
	m_pZipLoader    = NULL;
	m_pVerifyThread = NULL;
}

MiniAntManager::~MiniAntManager()
{

}

bool MiniAntManager::DownLoadURLFile(int urlTag, std::string url)
{
	m_pURLLoader->SetURLTag(urlTag);
	m_pURLLoader->SetURL(url);
	m_pURLLoader->create_thread();

	return true;
}

bool MiniAntManager::DownLoadZipFile(std::string url, std::string md5)
{
	m_pZipLoader->SetZipURL(url);
	m_pZipLoader->SetZipMD5(md5);
	m_pZipLoader->create_thread();

	return true;
}

bool MiniAntManager::VerifyFileList(std::map<std::string, std::string> checkList)
{
	m_pVerifyThread->SetVerifyFileList(checkList);
	m_pVerifyThread->create_thread();

	return true;
}

void MiniAntManager::SetDocumentDir(std::string dir)
{
	m_DocumentDir = dir;
}

std::string MiniAntManager::GetDocumentDir()
{
	return m_DocumentDir;
}

void MiniAntManager::SetAppendDownLoadZip(bool bAppendDownLoad)
{
	m_bAppendDownLoad = bAppendDownLoad;
}

bool MiniAntManager::IsAppendDownLoadZip()
{
	return m_bAppendDownLoad;
}

void MiniAntManager::SetDebug(bool bDebug)
{
	m_bDebug = bDebug;
}

bool MiniAntManager::IsDebug()
{
	return m_bDebug;
}

void MiniAntManager::SetLocation(bool bLocation)
{
	m_bLocation = bLocation;
}

bool MiniAntManager::IsLocation()
{
	return m_bLocation;
}

void MiniAntManager::SetCallbackHandler(IAntCallbackHandler* pCallbackHandler)
{
	m_pAntCallbackHandler = pCallbackHandler;
}

IAntCallbackHandler* MiniAntManager::GetCallbackHandler()
{
	return m_pAntCallbackHandler;
}

void MiniAntManager::PushEvent(IEvent* pEvent)
{
	m_EventListLock.lock();

	m_EventList.push_back(pEvent);

	m_EventListLock.unlock();
}

void MiniAntManager::Init()
{
	m_pURLLoader = new URLLoader;
	assert(m_pURLLoader != NULL);

	m_pZipLoader     = new ZipLoader;
	assert(m_pZipLoader != NULL);

	m_pVerifyThread  = new VerifyThread;
	assert(m_pVerifyThread != NULL);
}

void MiniAntManager::Tick()
{
	// 为防止逻辑操作阻塞网络事件，所以先全部拷贝出来在处理
	std::list<IEvent*> tempList;
	{
		m_EventListLock.lock();

		std::list<IEvent*>::iterator iter   = m_EventList.begin();
		std::list<IEvent*>::iterator iter_e = m_EventList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			tempList.push_back(*iter);
		}
		m_EventList.clear();

		m_EventListLock.unlock();
	}

	// 事件处理
	std::list<IEvent*>::iterator iter   = tempList.begin();
	std::list<IEvent*>::iterator iter_e = tempList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		IEvent* pEvent = *iter;
		pEvent->OnEventHandler();

		delete pEvent;
	}
}

void MiniAntManager::Destroy()
{
	if (m_pURLLoader != NULL)
	{
		m_pURLLoader->post_close_message();
		delete m_pURLLoader;
		m_pURLLoader = NULL;
	}

	if (m_pZipLoader != NULL)
	{
		m_pZipLoader->post_close_message();
		delete m_pZipLoader;
		m_pZipLoader = NULL;
	}

	if (m_pVerifyThread != NULL)
	{
		m_pVerifyThread->post_close_message();
		delete m_pVerifyThread;
		m_pVerifyThread = NULL;
	}

	// 删除所有事件
	m_EventListLock.lock();
	std::list<IEvent*>::iterator iter   = m_EventList.begin();
	std::list<IEvent*>::iterator iter_e = m_EventList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete *iter;
	}
	m_EventList.clear();
	m_EventListLock.unlock();
}


static  IAntManager*  s_pAntManager = NULL;
IAntManager*  CreateAntManager()
{
	if (s_pAntManager == NULL)
	{
		s_pAntManager = new MiniAntManager;
	}

	return s_pAntManager;
}

void  DestroyAntManager()
{
	if (s_pAntManager != NULL)
	{
		s_pAntManager->Destroy();
		delete s_pAntManager;
		s_pAntManager = NULL;
	}
}


}

