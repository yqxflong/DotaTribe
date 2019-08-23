#include "../../include/mem/EPacket.h"
using  namespace  cobra_win;




EPacket::EPacket() : m_wPos(0)
{
	m_buff.reserve(2048);
	m_buff.resize(1);
}

EPacket::EPacket(size_t size) : m_wPos(0)
{
	m_buff.reserve(size);
	m_buff.resize(1);
}		

EPacket::~EPacket()
{
	clear();
}

void    EPacket::clear()
{
	m_wPos = 0;
	m_buff.clear();
	m_buff.resize(1);
}

char*   EPacket::get_packet_buff()  
{  
	return (char*)&m_buff[0];
}

size_t  EPacket::get_write_pos()     
{ 
	return m_wPos;   
}

size_t  EPacket::size()               
{ 
	return m_wPos; 
}

void    EPacket::set_write_pos(size_t wPos)
{
	assert(m_wPos < m_buff.size());

	m_wPos = wPos;
	m_buff.resize(m_wPos+1);
	m_buff[m_wPos] = '\0';
}

void    EPacket::append(char* pBuff, size_t len)
{
	assert(pBuff != NULL);

	m_buff.resize(m_wPos+len+1);
	memcpy((char*)&m_buff[0]+m_wPos, pBuff, len);
	m_wPos += len;
}

EPacket& EPacket::operator<<(int value)
{
	append((char*)&value, sizeof(int));

	return *this;
}

EPacket& EPacket::operator<<(float value)
{
	append((char*)&value, sizeof(float));

	return *this;
}

EPacket& EPacket::operator<<(char*  pValue)
{
	append((char*)pValue, strlen(pValue));

	return *this;
}

EPacket& EPacket::operator<<(char   value)
{
	append((char*)&value, sizeof(char));

	return *this;
}

EPacket& EPacket::operator<<(bool   value)
{
	append((char*)&value, sizeof(bool));

	return *this;
}

EPacket& EPacket::operator<<(unsigned short value)
{
	append((char*)&value, sizeof(unsigned short));

	return *this;
}

EPacket& EPacket::operator<<(unsigned long value)
{
	append((char*)&value, sizeof(unsigned long));

	return *this;
}

EPacket& EPacket::operator<<(unsigned char  value)
{
	append((char*)&value, sizeof(unsigned char));

	return *this;
}

EPacket& EPacket::operator<<(long long value)
{
	append((char*)&value, sizeof(long long));

	return *this;
}
