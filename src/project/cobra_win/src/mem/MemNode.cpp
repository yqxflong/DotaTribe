#include "../../include/mem/MemNode.h"
#include "../../include/mem/Malloc.h"
using  namespace  cobra_win;



MemNode::MemNode()
{
	m_pBuff = NULL;
	m_iLen  = 0;
	m_iRPos = 0;
	m_iWPos = 0;
}

MemNode::~MemNode()
{
	if (m_pBuff != NULL)
	{
		Malloc::delete_buff(m_pBuff);
		m_pBuff = NULL;
	}
}	

char*   MemNode::get_buff()
{
	return m_pBuff;
}

size_t  MemNode::size()
{
	return m_iLen-MEM_ADD_SIZE;
}

size_t  MemNode::get_write_pos()
{
	return m_iWPos;
}

void    MemNode::set_write_pos(size_t iWPos)
{
	assert(iWPos < m_iLen);

	m_iWPos = iWPos;
	m_pBuff[m_iWPos] = '\0';
}

size_t  MemNode::get_read_pos()
{
	return m_iRPos;
}

void    MemNode::set_read_pos(size_t iRPos)
{
	assert(iRPos < m_iLen);

	m_iRPos = iRPos;
}

void    MemNode::init(size_t iSize)
{
	if (m_pBuff == NULL)
	{
		m_iLen     = iSize+MEM_ADD_SIZE;
		m_pBuff    = Malloc::new_buff(m_iLen);
		m_pBuff[0] = '\0';
	}
	m_iWPos = 0;
	m_iRPos = 0;
}

void    MemNode::clear()
{
	m_iWPos    = 0;
	m_iRPos    = 0;
	m_pBuff[0] = '\0';
}

void    MemNode::pop(char* pBuff, size_t iLen)
{
	assert(m_iRPos+iLen < m_iLen);

	memcpy(pBuff, m_pBuff+m_iRPos, iLen);
	m_iRPos += iLen;
}

void    MemNode::push(char* pBuff, size_t iLen)
{
	assert(m_iWPos+iLen < m_iLen);

	memcpy(m_pBuff+m_iWPos, pBuff, iLen);
	m_iWPos += iLen;
	m_pBuff[m_iWPos] = '\0';
}
