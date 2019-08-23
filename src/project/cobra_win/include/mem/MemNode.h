#ifndef  _LC_COBRA_WIN_MEMNODE_H
#define  _LC_COBRA_WIN_MEMNODE_H


#include "../common/NonCopyable.h"
#include <stdio.h>
#include <assert.h>
#include <string>

namespace  cobra_win
{


class  MemNode
{
public:
	enum
	{
		MEM_ADD_SIZE = 128,
	};

private:
	char*    m_pBuff;  // 数据缓冲区
	size_t   m_iLen;   // 数据区长度
	size_t   m_iRPos;  // 当前读指针位置
	size_t   m_iWPos;  // 当前写指针位置

public:
	MemNode();
	~MemNode();

public:
	/*
		得到缓冲区的起始位置
	*/
	char*   get_buff();
	/*
		得到缓冲区的长度大小
	*/
	size_t  size();
	/*
		得到当前写指针的位置
	*/
	size_t  get_write_pos();
	/*
		设置当前写指针的位置
	*/
	void    set_write_pos(size_t iWPos);
	/*
		得到当前读指针的位置
	*/
	size_t  get_read_pos();
	/*
		设置当前读指针的位置
	*/
	void    set_read_pos(size_t iRPos);

public:
	/*
		初始化
	*/
	void    init(size_t iSize);
	/*
		清空
	*/
	void    clear();
	/*
		压入一段字符串
	*/
	void    push(char* pBuff, size_t iLen);
	/*
		弹出一段字符串
	*/
	void    pop(char* pBuff, size_t iLen);

public:
	template <typename TYPE>
	void  push(TYPE& value)
	{
		assert(m_iWPos+sizeof(TYPE) < m_iLen);

		memcpy(m_pBuff+m_iWPos, &value, sizeof(TYPE));
		m_iWPos += sizeof(TYPE);

		m_pBuff[m_iWPos] = '\0';
	} 
	template <typename TYPE>
	void  pop(TYPE& value)
	{
		assert(m_iRPos+sizeof(TYPE) < m_iLen);

		memcpy(&value, m_pBuff+m_iRPos, sizeof(TYPE));
		m_iRPos += sizeof(TYPE);
	}
};


}


#endif
