#include "../../include/mem/EPacket2.h"
#include <memory.h>
#include <string.h>
using  namespace  cobra_win;



EPacket2::EPacket2(char* pBuffer, size_t iSize) : m_wPos(0)
{
	assert( (pBuffer!=NULL) && (iSize>0) );

	m_pBuffer     = pBuffer;
	m_iBufferSize = iSize-1;
	m_pBuffer[0]  = '\0';
}

EPacket2::~EPacket2()
{

}

void    EPacket2::clear()
{
	m_wPos = 0;
	m_pBuffer[0] = '\0';
}

char*   EPacket2::get_packet_buff()  
{  
	return m_pBuffer;
}

size_t  EPacket2::get_write_pos()     
{ 
	return m_wPos;   
}

size_t  EPacket2::size()               
{ 
	return m_wPos; 
}

void    EPacket2::set_write_pos(size_t wPos)
{
	assert(wPos <= m_iBufferSize);

	m_wPos = wPos;
	m_pBuffer[m_wPos] = '\0';
}

void    EPacket2::append(char* pBuff, size_t len)
{
	assert(pBuff != NULL);

	if ( (m_wPos+len) > m_iBufferSize )
	{
		assert(0);
	}

	memcpy((char*)m_pBuffer+m_wPos, pBuff, len);
	m_wPos += len;
	m_pBuffer[m_wPos] = '\0';
}

EPacket2& EPacket2::operator<<(int value)
{
	append((char*)&value, sizeof(int));

	return *this;
}

EPacket2& EPacket2::operator<<(float value)
{
	append((char*)&value, sizeof(float));

	return *this;
}

EPacket2& EPacket2::operator<<(char*  pValue)
{
	append((char*)pValue, strlen(pValue));

	return *this;
}

EPacket2& EPacket2::operator<<(char   value)
{
	append((char*)&value, sizeof(char));

	return *this;
}

EPacket2& EPacket2::operator<<(bool   value)
{
	append((char*)&value, sizeof(bool));

	return *this;
}

EPacket2& EPacket2::operator<<(unsigned short value)
{
	append((char*)&value, sizeof(unsigned short));

	return *this;
}

EPacket2& EPacket2::operator<<(unsigned long value)
{
	append((char*)&value, sizeof(unsigned long));

	return *this;
}

EPacket2& EPacket2::operator<<(unsigned char value)
{
	append((char*)&value, sizeof(unsigned char));

	return *this;
}

EPacket2& EPacket2::operator<<(long long value)
{
	append((char*)&value, sizeof(long long));

	return *this;
}
