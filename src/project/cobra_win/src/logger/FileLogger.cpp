#include "../../include/logger/FileLogger.h"
#include <string.h>
using  namespace  cobra_win;


FileLogger::FileLogger() : m_bExtTime(true)
{
	memset(m_pFolderName, 0, sizeof(m_pFolderName));
	memset(m_SubName, 0, sizeof(m_SubName));
	memset(m_ExtName, 0, sizeof(m_ExtName));
	strcpy(m_ExtName, "xyz");

	m_FileMaxSize = 1024*1024;
}

FileLogger::~FileLogger()
{
	close_log_file();
}

void   FileLogger::set_log_floder_name(char* pName)
{
	memset(m_pFolderName, 0, sizeof(m_pFolderName));
    strcpy(m_pFolderName, pName);
}

void   FileLogger::set_log_sub_name(char* pSubName)
{
	memset(m_SubName, 0, sizeof(m_SubName));
	strcpy(m_SubName, pSubName);
}

void   FileLogger::set_log_ext_name(char* pExtName)
{
	memset(m_ExtName, 0, sizeof(m_ExtName));
	strcpy(m_ExtName, pExtName);
}

void   FileLogger::set_log_ext_time(bool bExtTime)
{
	m_bExtTime = bExtTime;
}

bool   FileLogger::get_log_ext_time()
{
	return m_bExtTime;
}

void   FileLogger::set_log_max_size(long long maxSize)
{
	if (maxSize <= 1024)
		return;

	m_FileMaxSize = maxSize;
}

bool   FileLogger::open_log_file()
{
	char filename[1024] = "";
	if (m_bExtTime)
	{
		time_t t = time(NULL);
		m_pTm    = localtime(&t);
		sprintf(filename, "%s%s-%02d%02d%02d.%s", m_pFolderName, m_SubName, m_pTm->tm_year+1900, m_pTm->tm_mon+1, m_pTm->tm_mday, m_ExtName);
	}
	else
	{
		sprintf(filename, "%s%s.%s", m_pFolderName, m_SubName, m_ExtName);
	}
	
	if (!m_FileLoader.load(filename, FileLoader::_TYPED_APPEND_WRITE_))
		return false;

	// 判断文件大小
	long long fileSize = m_FileLoader.length();
	if (fileSize >= m_FileMaxSize)
	{
		m_FileLoader.unload();

		if (!m_FileLoader.load(filename, FileLoader::_TYPED_CLEAR_WRITE_))
			return false;
		m_FileLoader.unload();

		if (!m_FileLoader.load(filename, FileLoader::_TYPED_APPEND_WRITE_))
			return false;
	}

	return true;
}

void   FileLogger::close_log_file()
{
	m_myLock.lock();

	m_FileLoader.unload();

	m_myLock.unlock();
}

bool   FileLogger::write(char* pPtr)
{
	time_t t = time(NULL);
	tm* pTm  = localtime(&t);

	m_myLock.lock();

	m_FileLoader.write(pPtr);
	m_FileLoader.flush();

	m_myLock.unlock();
	return true;
}
