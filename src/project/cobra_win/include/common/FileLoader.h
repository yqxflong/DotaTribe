#ifndef  _LC_COBRA_WIN_FILELOADER2_H_
#define  _LC_COBRA_WIN_FILELOADER2_H_


#include "NonCopyable.h"
#include <stdio.h>

namespace  cobra_win
{


class  FileLoader : public  NonCopyable
{
public:
	enum
	{
		_TYPED_UNKOWN_,
		_TYPED_READ_ONLY_,           // 原生读
		_TYPED_CLEAR_WRITE_,         // 清除写
		_TYPED_APPEND_WRITE_,        // 附加写
		_TYPED_READ_CLEAR_WRITE_,    // 清除读写
		_TYPED_READ_APPEND_WRITE_,   // 附加读写
	};

private:
	FILE*   m_pFile;
	int     m_OperatorType;

public:
	FileLoader();
	~FileLoader();

public:
	/*
		得到当前文件的操作类型
	*/
	int     type();
	/*
		得到当前文件的大小
	*/
	long    length();

public:
	/*
		加载文件
	*/
	bool    load(char* pFileName, int iType);
	/*
		卸载文件
	*/
	void    unload();

public:
	/*
		设置当前文件操作指针位置(从文件开始位置算起)
	*/
	void    seek(unsigned long iPos);
	/*
		得到当前文件操作指针位置
	*/
	long    tell();
	/*
		读取指定字节的数据
		0 : 表示到达文件结尾
		    否则表示读取的字节数量
	*/
	size_t  read(char* pBuffer, size_t iLen);
	/*
		写入文件
	*/
	void    write(char* pBuffer, size_t iLen);
	/*
		写入文件
	*/
	void    write(char* pBuffer);
	/*
		强制写回文件
	*/
	void    flush();
};


}

#endif
