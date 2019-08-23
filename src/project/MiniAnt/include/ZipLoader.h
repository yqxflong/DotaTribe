#ifndef  _MINIANT_ZIPLOADER_H_
#define  _MINIANT_ZIPLOADER_H_


#include <include/thread/IThread.h>
#include <include/common/FileLoader.h>
#include <curl/curl.h>
#include <string>
using  namespace  cobra_win;

namespace  miniant
{

class ZipLoader : public cobra_win::IThread
{
public:
	std::string m_ZipURL; // Zip文件存放URL
	std::string m_ZipMD5; // Zip文件MD5校验码

public:
	FileLoader  m_ZipFile;// ZIP文件

public:
	long  long  m_InitZipLength; // 初试时ZIP文件长度

public:
	/*
		设置Zip文件URL地址
	*/
	void  SetZipURL(std::string url);
	/*
		设置Zip文件MD5校验码
	*/
	void  SetZipMD5(std::string md5);

public:
	ZipLoader();
	virtual ~ZipLoader();

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
	static    int    OnHTTPDataWriter(char* pData, size_t size, size_t nmemb, void* pFile);
	/*
		调试器回调接口处理
	*/
	static    int    OnHTTPDebuger(CURL*, curl_infotype itype, char* pData, size_t size, void*);
};


}


#endif
