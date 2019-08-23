#ifndef  _MINIANT_VERSIONLOADER_H_
#define  _MINIANT_VERSIONLOADER_H_


#include <include/thread/IThread.h>
#include <string>

namespace  miniant
{

class VersionLoader : public cobra_win::IThread
{
public:
	std::string m_VersionURL; // 版本文件存放URL

public:
	std::string m_VersionContent;// 版本文件内容

public:
	/*
		设置版本文件URL地址
	*/
	void  SetVersionURL(std::string url);

public:
	VersionLoader();
	virtual ~VersionLoader();

public:
	/*
		创建线程
	*/
	bool  create_thread();

public:
	/*
		线程处理函数
	*/
	virtual   void*  run();
	/*
		发起关闭消息
	*/
	virtual   void   post_close_message();

private:
	/*
		HTTP下载进度处理
	*/
	static    int    OnHTTPProgress(void* pPtr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);
	/*
		HTTP下载数据保存处理
	*/
	static    int    OnHTTPDataWriter(char* pData, size_t size, size_t nmemb, std::string* pContent);
};


}


#endif
