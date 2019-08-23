#ifndef  _LC_COBRA_WIN_FILELOGGER_H
#define  _LC_COBRA_WIN_FILELOGGER_H


#include "../common/Lock.h"
#include "ILogger.h"
#include "../common/FileLoader.h"
#include <stdio.h>
#include <time.h>

namespace  cobra_win
{


class  FileLogger : public ILogger
{
private:
	FileLoader  m_FileLoader;        // 文件操作类
	char        m_pFolderName[1024]; // 所在目录名
	char        m_SubName[1024];     // 文件前缀
	char        m_ExtName[1024];     // 文件后缀
	bool        m_bExtTime;          // 是否在文件名末尾追加当前时间
	long  long  m_FileMaxSize;       // 文件最大长度
	tm*         m_pTm;               // 保留的时间
	EmptyLock   m_myLock;            // 串行化锁

public:
	FileLogger();
	virtual  ~FileLogger();

public:
	/*
		设置日志文件的目录
	*/
	void   set_log_floder_name(char* pName);
	/*
		设置日志文件的前缀文件名
	*/
	void   set_log_sub_name(char* pSubName);
	/*
		设置日志文件的后缀文件名
	*/
	void   set_log_ext_name(char* pExtName);
	/*
		设置日志文件名是否追加当前时间
	*/
	void   set_log_ext_time(bool bExtTime);
	/*
		得到日志文件名是否追加当前时间
	*/
	bool   get_log_ext_time();
	/*
		设置日志文件最大长度(超过之后自动删除)
	*/
	void   set_log_max_size(long long maxSize);

public:
	/*
		打开文件
	*/
	bool   open_log_file();
	/*
		关闭日志
	*/
	void   close_log_file();

public:
	/*
		写入文件
	*/
	virtual   bool   write(char* pPtr);
};


}


#endif
