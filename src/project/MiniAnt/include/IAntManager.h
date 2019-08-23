#ifndef  _MINIANT_IANTMANAGER_H_
#define  _MINIANT_IANTMANAGER_H_


/*
* Copyright(c) Cyou.MRD2013
*
* 文件名称: IAntManager
* 文件标识:
* 摘    要: 蚂蚁下载器，主要对下载器对外接口进行描述说明
*
* 当前版本: 1.0.6
* 1.0.2版本增加了是否续点下载的开关，默认不支持续点下载（在某些WIFI情况下，续点下载总是导致CURLE_PARTIAL_FILE而失败）
* 1.0.3版本增加了下载速率的控制，如果下载速度小于1秒/秒，则在10秒内终止连接
* 1.0.4版本增加了调试器功能，玩家可以通过接口开启HTTP上行和下行的具体数据
* 1.0.5版本增加了下载重定向的处理：发现在部分WIFi情况下，正常的下载会被location掉(服务器返回都是没问题的)，所以增加该接口
* 1.0.6版本彻底修复了续点下载的问题，同时解决了续点下载出错时，通过MD5校验来检查的处理(外层可以直接删除坏死的下载包)
* 1.0.7版本彻底将XML文件的解析放在外层出去，下载器内部仅仅进行网络.xml和.txt等文本文件的下载，不解析
*
* 作    者: 关中刀客
* 完成时间: 2013年09月11日
*/

#include <string>
#include <list>
#include <map>

namespace  miniant
{


#define  _ANT_DOWNLOAD_DIR_  "download/"
#define  _ANT_ZIP_NAME_      "tempcyou.zip"

class Versions
{
public:
	std::string mVersion;       // 版本号
	bool        mNeedUpdate;    // 是否需要更新
	std::string mZipURL;        // 对应ZIP资源包地址
	std::string mZipMD5;        // ZIP资源包MD5
	float       mZipSize;       // ZIP资源包的大小(MB)
	bool        mNeedAppUpdate; // 是否需要App强制更新
	std::string mAppUpdateURL;  // 强制下载的地址(IOS为App Store地址；Android为各渠道apk包地址)

public:
	Versions()
	{
		mNeedUpdate    = false;
		mNeedAppUpdate = false;
		mZipSize       = 0.0f;
	}
};


class IEvent
{
public:
	IEvent() {}
	virtual ~IEvent() {}

public:
	/*
		事件处理操作
	*/
	virtual  void  OnEventHandler()   =   0;
};

class IAntCallbackHandler
{
public:
	IAntCallbackHandler() {}
	virtual ~IAntCallbackHandler() {}

public:
	/*
		URL文本文件下载失败事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadFailedHandler(int urlTag, int errorCode)         =   0;
	/*
		URL文本文件下载成功事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadSucceededHandler(int urlTag, std::string text)   =   0; 
	/*
		URL文本文件下载进度事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadProgressHandler(double total, double downloaded) =   0;

public:
	/*
		ZIP文件下载失败事件处理
	*/
	virtual  void  OnZipFileDownLoadFailedHandler(int errorCode)                     =   0;
	/*
		ZIP文件下载成功事件处理
	*/
	virtual  void  OnZipFileDownLoadSucceededHandler(double length)                  =   0;
	/*
		ZIP文件下载进度事件处理
	*/
	virtual  void  OnZipFileDownLoadProgressHandler(double total, double downloaded) =   0;
	/*
		ZIP文件MD5值校验成功事件处理
	*/
	virtual  void  OnVerifyZipFileFailedHandler()                                    =   0;
	/*
		ZIP文件MD5值校验失败事件处理
	*/
	virtual  void  OnVerifyZipFileSucceededHandler()                                 =   0;
	/*
		ZIP文件解压事件处理
	*/
	virtual  void  OnUnZipStartHandler()                                             =   0;
	/*
		ZIP文件解压失败事件处理
	*/
	virtual  void  OnUnZipFailedHandler(int errorCode)                               =   0;
	/*
		ZIP文件解压成功事件处理
	*/
	virtual  void  OnUnZipSucceededHandler()                                         =   0;

public:
	/*
		指定文件MD5校验成功事件处理
	*/
	virtual  void  OnVerifyFileFailedHandler(std::string fileName)                   =   0;
	/*
		指定文件MD5校验失败事件处理
	*/
	virtual  void  OnVerifyFileSucceededHandler()                                    =   0;
};

class IAntManager
{
public:
	IAntManager() {}
	virtual ~IAntManager() {}

public:
	/************************************************************************/
	/* 设置下载器内部读写文件的根目录                                       */
	/************************************************************************/
	virtual  void  SetDocumentDir(std::string dir)            =   0;
	/************************************************************************/
	/* 获取下载器内部读写文件的根目录                                       */
	/************************************************************************/
	virtual  std::string  GetDocumentDir()                    =   0;
	/************************************************************************/
	/* 设置是否支持续点下载ZIP包                                            */
	/* (在某些WIFI情况下，发现如果携带HTTP的Range标签头，则总是返回         */
	/* CURLE_PARTIAL_FILE而无法下载，所以增加该接口)                        */

	/* 默认支持续点下载                                                     */
	/************************************************************************/
	virtual  void  SetAppendDownLoadZip(bool bAppendDownLoad) =   0;
	/************************************************************************/
	/* 获取是否支持续点下载ZIP包                                            */
	/************************************************************************/
	virtual  bool  IsAppendDownLoadZip()                      =   0;
	/************************************************************************/
	/* 设置是否开启调试器                                                   */
	/* 方便输出上行下行的Http Header&Body信息                               */

	/* 默认关闭调试器                                                       */
	/************************************************************************/
	virtual  void  SetDebug(bool bDebug)                      =   0;
	/************************************************************************/
	/* 是否开启调试器                                                       */
	/************************************************************************/
	virtual  bool  IsDebug()                                  =   0;
	/************************************************************************/
	/* 设置是否启用重定向功能(Location)                                     */
	/* (在部分WIFi情况下，下载的信息会被location到另外的地址，导致正常的下载*/
	/* ,总是出现302的问题，估增加该接口)                                    */

	/* 设置是否启用重定向功能(Location)                                     */
	/************************************************************************/
	virtual  void  SetLocation(bool bLocation)                =   0;
	/************************************************************************/
	/* 是否开启重定向功能                                                   */
	/************************************************************************/
	virtual  bool  IsLocation()                               =   0;

public:
	/************************************************************************/
	/*  设置下载更新事件回调接口                                            */
	/*  使用者需要实现对应的事件回调接口，然后设置事件回调指针              */
	/************************************************************************/
	virtual  void  SetCallbackHandler(IAntCallbackHandler* pCallbackHandler)    =   0;
	/************************************************************************/
	/*  得到下载更新时间回调接口                                            */
	/************************************************************************/
	virtual  IAntCallbackHandler* GetCallbackHandler()                          =   0;

public:
	/************************************************************************/
	/*  下载URL文本文件(.txt or .xml)                                       */
	/*  urlTag：表示URL唯一的类型，下载失败或工程后根据tag区分，由外层指定  */
	/*  url：表示下载的URL地址                                              */

	/*  内部多线程下载URL，所以外层切记禁止一时刻进行多次下载，需要确保多个 */
	/*  URL地址一个下载完成之后再进行下一个的下载操作                       */
	/************************************************************************/
	virtual  bool  DownLoadURLFile(int urlTag, std::string url)                 =   0;
	/************************************************************************/
	/*  下载ZIP资源包                                                       */
	/*  提供ZIP的URL和MD5值，内部下载后会进行MD5比对，然后解压缩            */
	/************************************************************************/
	virtual  bool  DownLoadZipFile(std::string url, std::string md5)            =   0;
	/************************************************************************/
	/*  进行指定文件列表MD5校验                                             */

	/*  参数MAP信息如下：                                                   */
	/*      Key：文件名称                                                   */
	/*      Value：文件对应的MD5                                            */
	/************************************************************************/
	virtual  bool  VerifyFileList(std::map<std::string, std::string> checkList) =   0;

public:
	/************************************************************************/
	/* 插入下载更新事件                                                     */
	/************************************************************************/
	virtual  void  PushEvent(IEvent* pEvent)                                    =   0;

public:
	/*
		初始化蚂蚁下载器
	*/
	virtual  void  Init()      =   0;
	/*
		蚂蚁下载器逻辑帧更新
	*/
	virtual  void  Tick()      =   0;
	/*
		销毁蚂蚁下载器
	*/
	virtual  void  Destroy()   =   0;
};

/*
	创建蚂蚁下载器
*/
extern  IAntManager*  CreateAntManager();
/*
	销毁蚂蚁下载器
*/
extern  void          DestroyAntManager();


}


#endif
