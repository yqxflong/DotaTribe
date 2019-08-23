#ifndef  _LC_COBRA_WIN_DPACKET_H
#define  _LC_COBRA_WIN_DPACKET_H


#include "../common/NonCopyable.h"
#include <assert.h>
#include <stdlib.h>

namespace  cobra_win
{


class  DPacket : public NonCopyable
{
private:
	char*     m_pBuff;  // 真实的数据缓冲区
	size_t    m_size;   // 需要解码的缓冲区大小
	size_t    m_rPos;   // 当前读指针的位置

public:
	/*
		设置初始化缓冲区
	*/
	DPacket(char* pBuff, size_t size);
	~DPacket();

public:
	/*
		得到内部缓冲区的首地址 
	*/
	char*    get_packet_buff();
	/*
		得到当前读指针的位置
	*/
	size_t   get_read_pos();
	/*
		得到数据区的大小
	*/
	size_t   size();
	/*
		设置读指针的位置
	*/
	void     set_read_pos(size_t rPos);
	/*
		读取一定长度的字符串
	*/
	void     read(char* pBuff, size_t len);
	/*
		清空数据
	*/
	void     clear();
	/*
		读取一种格式的数据，并且把当前的读指针做相应的移动
	*/
	template <typename TYPE>
	void  read(TYPE& value)
	{
		assert( (m_rPos+sizeof(TYPE))<=m_size );
		value = *(TYPE*)(m_pBuff+m_rPos);
		m_rPos   += sizeof(TYPE);
	}
	/*	
		弹出不同类型的数据
	*/
	DPacket&   operator>>(int&    value);
	DPacket&   operator>>(float&  value);
	DPacket&   operator>>(char&   value);
	DPacket&   operator>>(bool&   value);
    DPacket&   operator>>(long long& value);
	DPacket&   operator>>(unsigned short& value);
	DPacket&   operator>>(unsigned long&  value);
	DPacket&   operator>>(unsigned char&  value);
};


}


#endif
