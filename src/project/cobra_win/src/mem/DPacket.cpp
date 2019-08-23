#include "../../include/mem/DPacket.h"
#include <memory.h>
#include <string.h>
using  namespace  cobra_win;



DPacket::DPacket(char* pBuff, size_t size) : m_rPos(0)
{
	m_pBuff = pBuff;
	m_size  = size;
}

DPacket::~DPacket()
{
	clear();
}

void    DPacket::clear()
{
	m_rPos  = 0;
	m_pBuff = NULL;
	m_size  = 0;
}

char*   DPacket::get_packet_buff()  
{  
	return m_pBuff;
}

size_t  DPacket::get_read_pos()      
{ 
	return m_rPos;  
}

size_t  DPacket::size()               
{ 
	return m_size;  
}

void    DPacket::set_read_pos(size_t rPos)
{
	assert( rPos <= m_size );

	m_rPos = rPos;
}

void    DPacket::read(char* pBuff, size_t len)
{
	assert( (m_rPos+len) <= m_size );

	memcpy(pBuff, &m_pBuff[m_rPos], len);
	m_rPos += len;
}

DPacket& DPacket::operator>>(int&   value)
{
	read<int>(value);

	return *this;
}

DPacket& DPacket::operator>>(float& value)
{
	read<float>(value);

	return *this;
}

DPacket& DPacket::operator>>(char&   value)
{
	read<char>(value);

	return *this;
}

DPacket& DPacket::operator>>(bool&   value)
{
	read<bool>(value);

	return *this;
}

DPacket& DPacket::operator>>(unsigned short& value)
{
	read<unsigned short>(value);

	return *this;
}

DPacket& DPacket::operator>>(unsigned long& value)
{
	read<unsigned long>(value);

	return *this;
}

DPacket& DPacket::operator>>(unsigned char& value)
{
	read<unsigned char>(value);

	return *this;
}

DPacket& DPacket::operator>>(long long& value)
{
	read<long long>(value);

	return *this;
}
