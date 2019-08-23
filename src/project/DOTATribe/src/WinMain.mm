#include "../include/WinMain.h"
#include "../include/DOTATribeApp.h"
#include "../include/CrashReportSystem.h"
#include "../include/DotaGameConfig.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

static bool get_module_folder_path(char* pPath, size_t iLen)
{
	int ret = (int)GetModuleFileName(NULL, pPath, (DWORD)iLen);
	if ( (ret==0) || (ret==iLen))
		return false;

	for (size_t i=strlen(pPath)-1; i>=0; i--)
	{
		switch( pPath[i] )
		{
		case	'/':
		case	'\\':
			pPath[i+1] = '\0';
			return true;
			break;
		}
	}

	return false;
}

static bool chg_module_folder(char* pPath)
{
	if (_chdir(pPath) != 0)
		return false;

	return true;
}

static inline void enable_mem_leak_check()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

int _tWinMain_With_CPPException(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	do 
	{
		char path[1024] = "";
		if (!get_module_folder_path(path, sizeof(path)))
			break;

		if (!chg_module_folder(path))
			break;

		DOTATribeApp myApp;
		cocos2d::CCApplication::sharedApplication()->run();
		return 0;
	}
	while (false);

	return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _DEBUG
		enable_mem_leak_check();
		_CrtSetBreakAlloc(0);
#endif

	
	
	if(DOTA_CONFIG_MODE==kMODE_RELEASE_INNER){
		//进入结构化异常块
		__try
		{
			return _tWinMain_With_CPPException(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		}
		__except (CrashReportSystem::OnProcessExceptionHandler((void*)GetExceptionInformation()), TerminateProcess(GetCurrentProcess(), 0), EXCEPTION_EXECUTE_HANDLER) {}
	}else
		return _tWinMain_With_CPPException(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}

#endif





#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>

int main(int argc, char *argv[]) 
{
	if(DOTA_CONFIG_MODE==kMODE_RELEASE_INNER){
		// 注册异常回调事件接口
		signal(SIGQUIT, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGILL, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGTRAP, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGABRT, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGEMT, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGFPE, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGBUS, CrashReportSystem::OnProcessExceptionHandler2);
	    signal(SIGSEGV, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGSYS, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGPIPE, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGALRM, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGXCPU, CrashReportSystem::OnProcessExceptionHandler2);
		signal(SIGXFSZ, CrashReportSystem::OnProcessExceptionHandler2);
	}

	// 初始化全局的App管理器对象
	// 不需要在手动的释放，因为在销毁的时候会自动的释放
	DOTATribeApp* pApp = new DOTATribeApp;

	// 创建自动释放池
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	int retVal = UIApplicationMain(argc, argv, nil, @"DOTATribeAppController");
	// 释放自动释放池
	[pool release];

	return retVal;
}

#endif
