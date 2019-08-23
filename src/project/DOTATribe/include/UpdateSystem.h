#ifndef  _DOTATRIBE_UPDATESYSTEM_H_
#define  _DOTATRIBE_UPDATESYSTEM_H_

#include <include/common/Singleton.h>
#include <include/IAntManager.h>
#include <include/mem/DPacket.h>
#include <string>
#include <list>
using  namespace  cobra_win;
using  namespace  miniant;

class UpdateSystem : public miniant::IAntCallbackHandler, public cobra_win::Singleton2<UpdateSystem>
{
private:
	enum{
		kUSuccess=0,
		kUNeedUpdate,
		kUServerNotSupport,
	};
private:
	//结束解压资源包
	void _finishUnzipResource();
public:
	unsigned char ret_;		//0.成功	1.小版本更新   2.大版本更新   3.版本在当前服务器不支持，不可以进入游戏<br>
	std::string appUpdateURL_;		//appstore 下载地址
	int totalCount_;	//下载文件总数
protected:
	miniant::IAntManager* m_pAntManager;     // 蚂蚁更新下载器对象

protected:
	std::list<Versions> m_AllVersionList;    // 客户端所有版本信息列表

protected:
	int m_UpdateVersionSize;                 // 客户端待更新的版本信息个数
	std::list<Versions> m_UpdateVersionList; // 客户端待更新的版本信息列表

protected:
	bool m_bHasUpdated; // 是否更新了

public:
	UpdateSystem();
	virtual ~UpdateSystem();

public:
	/*
		获得蚂蚁更新下载器对象
	*/
	miniant::IAntManager* GetAntManager();
	/*
		是否资源更新了
	*/
	bool  IsHasUpdated();

public:
	bool  Init();
	void  Tick();
	void  Destroy();
	/*
		解析获取版本信息包
	*/
	void decodePacketData(cobra_win::DPacket & packet);

	/*
		请求版本信息
	*/
	void QueryVersionInfo();
	/*
		获取完更新信息的操作
	*/
	void HandleAfterGetVersionInfo();
	/*
		检测版本更新
	*/
	void HandleCheckVersionAndDownload();

	/*
		开始在线更新
	*/
	void StartUpdateOnline();

	/*
		准备Appstore下载
	*/
	void HandleAppStoreDownload();

	/*
		确保大版本更新时，download文件夹已经删除
	*/
	void ConfirmSandBoxDownloadHasBeenCleared();

public:
	/*
		URL文本文件下载失败事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadFailedHandler(int urlTag, int errorCode){};
	/*
		URL文本文件下载成功事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadSucceededHandler(int urlTag, std::string text){}; 
	/*
		URL文本文件下载进度事件处理(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadProgressHandler(double total, double downloaded){};
public:
	/*
		ZIP文件下载失败事件处理
	*/
	virtual  void  OnZipFileDownLoadFailedHandler(int errorCode);
	/*
		ZIP文件下载成功事件处理
	*/
	virtual  void  OnZipFileDownLoadSucceededHandler(double length);
	/*
		ZIP文件下载进度事件处理
	*/
	virtual  void  OnZipFileDownLoadProgressHandler(double total, double downloaded);
	/*
		ZIP文件MD5值校验成功事件处理
	*/
	virtual  void  OnVerifyZipFileFailedHandler();
	/*
		ZIP文件MD5值校验失败事件处理
	*/
	virtual  void  OnVerifyZipFileSucceededHandler();
	/*
		ZIP文件解压事件处理
	*/
	virtual  void  OnUnZipStartHandler();
	/*
		ZIP文件解压失败事件处理
	*/
	virtual  void  OnUnZipFailedHandler(int errorCode);
	/*
		ZIP文件解压成功事件处理
	*/
	virtual  void  OnUnZipSucceededHandler();

public:
	//@指定文件MD5校验成功事件处理
	virtual  void  OnVerifyFileFailedHandler(std::string fileName){};
	//@指定文件MD5校验失败事件处理
	virtual  void  OnVerifyFileSucceededHandler(){};


	UpdateSystem* GetLuaInstance(){
		return UpdateSystem::get_instance2();
	}
};

#define  UPDATESYSTEM  (UpdateSystem::get_instance2())


#endif
