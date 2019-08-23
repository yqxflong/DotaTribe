#ifndef  _LC_COBRA_WIN_EPACKET2_H
#define  _LC_COBRA_WIN_EPACKET2_H


#include "../common/NonCopyable.h"
#include <assert.h>
#include <stdlib.h>

namespace  cobra_win
{


class  EPacket2 : public NonCopyable
{
private:
	char*		m_pBuffer;     // 后备的数据缓冲区
	size_t		m_iBufferSize; // 后备数据缓冲区大小
	size_t		m_wPos;        // 当前写指针的位置

public:
	EPacket2(char* pBuffer, size_t iSize);
	~EPacket2();

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
		if ( (m_wPos+sizeof(TYPE)) > m_iBufferSize )
		{
			assert(0);
		}

		memcpy(m_pBuffer+m_wPos, (TYPE*)&value, sizeof(TYPE));
		m_wPos += sizeof(TYPE);
		m_pBuffer[m_wPos] = '\0';
	}
	/*
		压入不同数据类型的数据
	*/
	EPacket2&   operator<<(int    value);
	EPacket2&   operator<<(float  value);
	EPacket2&   operator<<(char*  pValue);
	EPacket2&   operator<<(bool   value);
	EPacket2&   operator<<(char   value);
    EPacket2&   operator<<(long long value);
	EPacket2&   operator<<(unsigned short value);
	EPacket2&   operator<<(unsigned long  value);
	EPacket2&   operator<<(unsigned char  value);
};


}


#endif
