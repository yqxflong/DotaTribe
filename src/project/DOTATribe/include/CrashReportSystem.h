#ifndef  _FIGHTTRIBE_CRASHREPORTSYSTEM_H_
#define  _FIGHTTRIBE_CRASHREPORTSYSTEM_H_


#include <include/common/Singleton.h>
using  namespace  cobra_win;

class CrashReportSystem
{
public:
	/*
		异常统计回调函数
	*/
	static  void  OnProcessExceptionHandler(void* pException);
	/*
		异常捕获处理
	*/
	static  void  OnProcessExceptionHandler2(int sigl);
};


#endif
