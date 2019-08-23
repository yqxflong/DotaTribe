#include "../include/CrashReportSystem.h"
#include "../include/EngineSystem.h"
#include <cocos2d.h>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>

void CrashReportSystem::OnProcessExceptionHandler(void* pExp)
{

}

void CrashReportSystem::OnProcessExceptionHandler2(int sigl)
{
	do 
	{
		std::string str = "";

		void* arrayList[128];
		int count = backtrace(arrayList, 128);
		char** pStr = backtrace_symbols(arrayList, count);
		if (pStr == NULL)
			break;

		for (int i=0; i<count; i++)
		{
			str += pStr[i];
			str += "\n";
		}

		if (str.size() <= 0)
			break;

		// ¼ÇÂ¼ÈÕÖ¾
		char buffer[1024] = "";
		time_t t = time(NULL);
		tm* pTm  = localtime(&t);
		sprintf(buffer, "[TRACE]%02d:%02d:%02d : \n", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

		std::string logFile = EngineSystem::GetDocumentDir();
		logFile += "exception.cyou";
		FILE* pFile = fopen(logFile.c_str(), "ab");
		if (pFile == NULL)
			break;

		fwrite(buffer, strlen(buffer), 1, pFile);
		fwrite(str.c_str(), str.size(), 1, pFile);
		fclose(pFile);
	} 
	while (false);

	exit(1);
}


#endif
