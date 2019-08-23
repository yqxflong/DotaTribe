#ifndef  _MINIANT_URLLOADER_H_
#define  _MINIANT_URLLOADER_H_


#include <include/thread/IThread.h>
#include <curl/curl.h>
#include <string>

namespace  miniant
{

class URLLoader : public cobra_win::IThread
{
public:
	int         m_URLTag; // 待下载的URL Tag标志位
	std::string m_URL;    // 待下载的URL

public:
	std::string m_URLContent;// 版本文件内容

public:
	/*
		设置待下载的URL地址
	*/
	void  SetURL(std::string url);
	/*
		设置待下载URL的tag标志位
	*/
	void  SetURLTag(int tag);

public:
	URLLoader();
	virtual ~URLLoader();

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
	/*
		调试器回调接口处理
	*/
	static    int    OnHTTPDebuger(CURL*, curl_infotype itype, char* pData, size_t size, void*);
};


}


#endif
