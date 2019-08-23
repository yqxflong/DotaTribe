#include "../../include/common/FileLoader.h"
#include <string.h>
#include <assert.h>
using  namespace  cobra_win;


FileLoader::FileLoader() : m_pFile(NULL)
{
	m_OperatorType = _TYPED_UNKOWN_;
}

FileLoader::~FileLoader()
{	
	unload();
}

int    FileLoader::type()
{
	return m_OperatorType;
}

long   FileLoader::length()
{
	assert(m_pFile != NULL);

	if (m_pFile == NULL)
		return 0;

	long current = ftell(m_pFile);

	fseek(m_pFile, 0, SEEK_END);
	long length = ftell(m_pFile);
	fseek(m_pFile, current, SEEK_SET);

	return length;
}

bool   FileLoader::load(char* pFileName, int iType)
{
	assert(pFileName != NULL);

	switch (iType)
	{
	case _TYPED_READ_ONLY_:
		m_pFile = fopen(pFileName, "rb");
		break;
	case _TYPED_CLEAR_WRITE_:
		m_pFile = fopen(pFileName, "wb");
		break;
	case _TYPED_APPEND_WRITE_:
		m_pFile = fopen(pFileName, "ab");
		break;
	case _TYPED_READ_CLEAR_WRITE_:
		m_pFile = fopen(pFileName, "wb+");
		break;
	case _TYPED_READ_APPEND_WRITE_:
		m_pFile = fopen(pFileName, "ab+");
		break;
	default:
		assert(0);
	}
	
	if (m_pFile == NULL)
		return false;

	if (length() > 0XEFFFFFFF)
	{
		unload();
		assert(0);
		return false;
	}

	m_OperatorType = iType;

	return true;
}

void   FileLoader::unload()
{
	if (m_pFile != NULL)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}

	m_OperatorType = _TYPED_UNKOWN_;
}

void   FileLoader::seek(unsigned long iPos)
{
	assert(m_pFile != NULL);

	if (m_pFile == NULL)
		return;

	fseek(m_pFile, iPos, SEEK_SET);
}

long   FileLoader::tell()
{
	assert(m_pFile != NULL);

	if (m_pFile == NULL)
		return 0;

	return ftell(m_pFile);
}

size_t  FileLoader::read(char* pBuffer, size_t iLen)
{
	assert( (pBuffer!=NULL) && (iLen!=0) && (m_pFile!=NULL) );

	if (m_pFile == NULL)
		return 0;

	return fread(pBuffer, 1, iLen, m_pFile);
}

void   FileLoader::write(char* pBuffer, size_t iLen)
{
	assert( (pBuffer!=NULL) && (iLen!=0) && (m_pFile!=NULL) );

	if (m_pFile == NULL)
		return;

	fwrite(pBuffer, 1, iLen, m_pFile);
}

void   FileLoader::write(char* pBuffer)
{
	assert( (pBuffer!=NULL) && (m_pFile!=NULL) );

	if (m_pFile == NULL)
		return;

	write(pBuffer, strlen(pBuffer));
}

void   FileLoader::flush()
{
	assert(m_pFile != NULL);

	if (m_pFile == NULL)
		return;

	fflush(m_pFile);
}
