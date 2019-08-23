#include <cocos2d.h>
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/EngineSystem.h"
#include <include/common/Console.h>
#include <stdarg.h>
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#include <fcntl.h>
#endif

template<> LoggerSystem* cobra_win::Singleton2<LoggerSystem>::m_pMySelf = NULL;

LoggerSystem::LoggerSystem()
{
	m_bConsoleLogGate  = false;
	m_iConsoleLogLevel = _TYPED_TRACE_LOGGER_;
	m_pConsoleLogger   = NULL;

	m_bFileLogGate     = false;
	m_iFileLogLevel    = _TYPED_TRACE_LOGGER_;
	m_pFileLogger      = NULL;
}

LoggerSystem::~LoggerSystem()
{

}

void LoggerSystem::LogTrace(char* pTrace, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[TRACE]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pTrace);
	vsprintf(buffer+pos, pTrace, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_TRACE_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_TRACE_LOGGER_)
		{
			m_pConsoleLogger->write(buffer);

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogDebug(char* pDebug, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[DEBUG]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pDebug);
	vsprintf(buffer+pos, pDebug, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_DEBUG_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_DEBUG_LOGGER_)
		{
			// 设置控制台打印颜色
			Console::set_text_color(Console::_TYPED_TEXT_YELLOW_COLOR_);

			// 写入
			m_pConsoleLogger->write(buffer);

			// 恢复控制台打印颜色
			Console::reset_text_color();

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogInfo(char* pInfo, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[INFO]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pInfo);
	vsprintf(buffer+pos, pInfo, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_INFO_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_INFO_LOGGER_)
		{
			m_pConsoleLogger->write(buffer);

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogProf(char* pProf, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[PROF]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pProf);
	vsprintf(buffer+pos, pProf, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_PROF_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_PROF_LOGGER_)
		{
			m_pConsoleLogger->write(buffer);

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogWaring(char* pWaring, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[WARING]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pWaring);
	vsprintf(buffer+pos, pWaring, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_WARING_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_WARING_LOGGER_)
		{
			m_pConsoleLogger->write(buffer);

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogError(char* pError, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[ERROR]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pError);
	vsprintf(buffer+pos, pError, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_ERROR_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_ERROR_LOGGER_)
		{
			// 设置控制台打印颜色
			Console::set_text_color(Console::_TYPED_TEXT_GREEN_COLOR_);

			// 写入
			m_pConsoleLogger->write(buffer);

			// 恢复控制台打印颜色
			Console::reset_text_color();

			CCLOG("%s", buffer);
		}
	}
}

void LoggerSystem::LogFatal(char* pFatal, ...)
{
	char buffer[10240] = "";
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);
	int pos  = sprintf(buffer, "[FATAL]%02d:%02d:%02d : ", pTm->tm_hour,pTm->tm_min,pTm->tm_sec);

	va_list ap;
	va_start(ap, pFatal);
	vsprintf(buffer+pos, pFatal, ap);
	va_end(ap);

	if (m_bFileLogGate)
	{
		if (m_iFileLogLevel <= _TYPED_FATAL_LOGGER_)
		{
			m_pFileLogger->write(buffer);
		}	
	}

	if (m_bConsoleLogGate)
	{
		if (m_iConsoleLogLevel <= _TYPED_FATAL_LOGGER_)
		{
			// 设置控制台打印颜色
			Console::set_text_color(Console::_TYPED_TEXT_RED_COLOR_);

			// 写入
			m_pConsoleLogger->write(buffer);

			// 恢复控制台打印颜色
			Console::reset_text_color();

			CCLOG("%s", buffer);
		}
	}
}

bool LoggerSystem::Init()
{
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "ConsoleLogMode", m_bConsoleLogGate);
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "ConsoleLogLevel", m_iConsoleLogLevel);
	if (m_iConsoleLogLevel<_TYPED_TRACE_LOGGER_ || m_iConsoleLogLevel>_TYPED_FATAL_LOGGER_)
	{
		m_iConsoleLogLevel = _TYPED_ERROR_LOGGER_;
	}

	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "FileLogMode", m_bFileLogGate);
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "FileLogLevel", m_iFileLogLevel);
	if (m_iFileLogLevel<_TYPED_TRACE_LOGGER_ || m_iFileLogLevel>_TYPED_FATAL_LOGGER_)
	{
		m_iFileLogLevel = _TYPED_ERROR_LOGGER_;
	}

	char FileLogName[1024] = "DOTATribeApp";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "FileLogName", FileLogName, sizeof(FileLogName));

	char FileLogExtName[1024] = "lc";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "FileLogExtName", FileLogExtName, sizeof(FileLogExtName));

	int FileLogMaxSize = 1024*1024*500;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_LOGGER_, "Log", "FileLogMaxSize", FileLogMaxSize);
	if (FileLogMaxSize<=1024 || FileLogMaxSize>=1024*1024*1024)
	{
		FileLogMaxSize = 1024*1024*500;
	}

	if (m_bFileLogGate)
	{
		m_pFileLogger   = new FileLogger;

		std::string str = EngineSystem::GetDocumentDir();
		m_pFileLogger->set_log_floder_name((char*)str.c_str());
		m_pFileLogger->set_log_sub_name(FileLogName);
		m_pFileLogger->set_log_ext_name(FileLogExtName);
		if (!m_pFileLogger->open_log_file())
		{
			delete m_pFileLogger;
			m_pFileLogger = NULL;
			m_bFileLogGate = false;
		}
	}

	if (m_bConsoleLogGate)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// 在Win32下面，创建一个Console，方便实时显示调试信息
		AllocConsole();
		int nCrt = int(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT));
		FILE* pStdout = _fdopen(nCrt, "w");
		*stdout = *pStdout;
		setvbuf(stdout, NULL, _IONBF, 0);
#endif

		m_pConsoleLogger = new ConsoleLogger;
	}

	CCLOG("LoggerSystem Init Success\n");
	return true;
}

void LoggerSystem::Tick()
{

}

void LoggerSystem::Destroy()
{
	if (m_bConsoleLogGate)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// 在Win下面，释放手动创建的Console
		fclose(stdout);
		FreeConsole();
#endif

		if (m_pConsoleLogger != NULL)
		{
			delete m_pConsoleLogger;
			m_pConsoleLogger = NULL;
		}
	}

	CCLOG("LoggerSystem Destroy Success\n");
	if (!m_bFileLogGate)
		return ;

	if (m_pFileLogger != NULL)
	{
		m_pFileLogger->close_log_file();
		delete m_pFileLogger;
		m_pFileLogger = NULL;
	}
}
