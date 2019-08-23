#ifndef  _MINIANT_VERIFYTHREAD_H_
#define  _MINIANT_VERIFYTHREAD_H_


#include <include/thread/IThread.h>
#include <string>
#include <map>

namespace  miniant
{

class VerifyThread : public cobra_win::IThread
{
public:
	std::map<std::string, std::string> m_VerifyList; // 校验文件列表

public:
	/*
		设置待校验的文件信息
	*/
	void  SetVerifyFileList(std::map<std::string, std::string> fileList);

public:
	VerifyThread();
	virtual ~VerifyThread();

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
};


}


#endif
