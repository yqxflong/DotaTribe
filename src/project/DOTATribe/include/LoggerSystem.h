#ifndef  _DOTATRIBE_LOGGERSYSTEM_H_
#define  _DOTATRIBE_LOGGERSYSTEM_H_


#include <include/logger/FileLogger.h>
#include <include/Logger/ConsoleLogger.h>
#include <include/common/Singleton.h>
using  namespace  cobra_win;

class LoggerSystem : public cobra_win::Singleton2<LoggerSystem>
{
public:
	enum  
	{
		_TYPED_TRACE_LOGGER_,   // trace类型日志
		_TYPED_DEBUG_LOGGER_,   // debug类型日志
		_TYPED_INFO_LOGGER_,    // info类型日志
		_TYPED_PROF_LOGGER_,    // 性能统计的Prof类型日志
		_TYPED_WARING_LOGGER_,  // waring类型日志
		_TYPED_ERROR_LOGGER_,   // error类型日志
		_TYPED_FATAL_LOGGER_    // fatal类型日志
	};
    
private:
	bool             m_bConsoleLogGate;
	int              m_iConsoleLogLevel;
	ConsoleLogger*   m_pConsoleLogger;
	bool             m_bFileLogGate;
	int              m_iFileLogLevel;
	FileLogger*      m_pFileLogger;

public:
	LoggerSystem();
	virtual ~LoggerSystem();
    
public:
	//@标配
	bool     Init();
	void     Tick();
	void     Destroy();

//@Lua
public:
	//@记录trace信息
	void     LogTrace(char* pTrace, ...);
	//@记录debug信息
	void     LogDebug(char* pDebug, ...);
	//@记录info信息
	void     LogInfo(char* pInfo, ...);
	//@记录Prof信息
	void     LogProf(char* pWaring, ...);
	//@记录waring信息
	void     LogWaring(char* pWaring, ...);
	//@记录error信息
	void     LogError(char* pError, ...);
	//@记录fatal信息
	void     LogFatal(char* pFatal, ...);

	LoggerSystem* GetLuaInstance(){
		return LoggerSystem::get_instance2();
	}

};

#define  LOGGERSYSTEM  (LoggerSystem::get_instance2())


#endif
