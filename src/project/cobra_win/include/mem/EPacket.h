#ifndef  _LC_COBRA_WIN_EPACKET_H
#define  _LC_COBRA_WIN_EPACKET_H


#include "../common/NonCopyable.h"
#include <assert.h>
#include <vector>
#include <stdlib.h>

namespace  cobra_win
{


class  EPacket : public NonCopyable
{
private:
	std::vector<char>  m_buff;  // 后备的数据缓冲区
	size_t             m_wPos;  // 当前写指针的位置

public:
	EPacket();
	/*
		设置其初始化缓冲区大小
	*/
	EPacket(size_t size);
	~EPacket();

public:
	/*
		得到内部缓冲区首地址
	*/
	char*    get_packet_buff();
	/*
		得到当前写指针的位置
	*/
	size_t   get_write_pos();
	/*
		得到数据区内所有有效数据的长度
	*/
	size_t   size();
	/*
		设置写指针的位置
	*/
	void     set_write_pos(size_t wPos);
	/*
		添加一定长度的数据
	*/
	void     append(char* pBuff, size_t len);
	/*
		清空数据
	*/
	void     clear();
	/*
		添加任意类型的数据
	*/
	template <typename TYPE>
	void     append(TYPE& value)
	{
		m_buff.resize(m_wPos+sizeof(TYPE)+1);
		memcpy((char*)&m_buff[0]+m_wPos, (TYPE*)&value, sizeof(TYPE));
		m_wPos += sizeof(TYPE);
	}
	/*
		压入不同数据类型的数据
	*/
	EPacket&   operator<<(int    value);
	EPacket&   operator<<(float  value);
	EPacket&   operator<<(char*  pValue);
	EPacket&   operator<<(bool   value);
	EPacket&   operator<<(char   value);
    EPacket&   operator<<(long long value);
	EPacket&   operator<<(unsigned short value);
	EPacket&   operator<<(unsigned long  value);
	EPacket&   operator<<(unsigned char  value);
};


}



#endif
