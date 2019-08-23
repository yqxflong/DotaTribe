#include "../../include/common/Parser.h"
#include "../../include/common/String.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
using  namespace  cobra_win;



Parser::Parser()
{
	m_pBuffer    = NULL;
	m_iBufferLen = 0;
	m_Spiter     = '\t';
	m_iRPos      = 0;
}

Parser::Parser(char* pBuffer, size_t iLen, char spiter)
{
	m_pBuffer    = pBuffer;
	m_iBufferLen = iLen;
	m_Spiter     = spiter;
	m_iRPos      = 0;
}

Parser::~Parser()
{

}

size_t Parser::get_read_pos()
{
	return m_iRPos;
}

void   Parser::set_read_pos(size_t iPos)
{
	m_iRPos = iPos;
}

void   Parser::clear()
{
	m_pBuffer    = NULL;
	m_iBufferLen = 0;
	m_iRPos      = 0;
}

void   Parser::reset(char* pBuffer, size_t iLen, char spiter)
{
	m_pBuffer    = pBuffer;
	m_iBufferLen = iLen;
	m_Spiter     = spiter;
	m_iRPos      = 0;
}

void   Parser::set_spit_char(char spiter)
{
	m_Spiter = spiter;
}

bool   Parser::parser_string_value(char* pBuffer, size_t iLen)
{
	assert( (pBuffer!=NULL) && (iLen>0) );

	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[10240] = "";
	size_t pos         = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		String::copy(pBuffer, buff, iLen);
		m_iRPos++;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_int_value(int& value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		m_iRPos++;
		int temp = 0;
		if (sscanf(buff, "%d", &temp) <= 0)
		{
			return false;
		}

		value = temp;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_float_value(float&  value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}
		
		m_iRPos++;
		float temp = 0.0f;
		if (sscanf(buff, "%f", &temp) <= 0)
		{
			return false;
		}	

		value = temp;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_char_value(char&   value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		m_iRPos++;
		char temp = '\0';
		if (sscanf(buff, "%c", &temp) <= 0)
		{
			return false;
		}

		value = temp;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_bool_value(bool&   value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		m_iRPos++;
		int _value = 0;
		if (sscanf(buff, "%u", &_value) <= 0)
		{
			return false;
		}

		value = *(bool*)&_value;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_short_value(short& value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		m_iRPos++;
		int temp = 0;
		if (sscanf(buff, "%d", &temp) <= 0)
		{
			return false;
		}

		value = temp;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

bool   Parser::parser_int64_value(long long& value)
{
	if (m_iRPos > m_iBufferLen)
		return false;

	char   buff[1024] = "";
	size_t pos        = 0;
	if (m_pBuffer[m_iRPos] != m_Spiter)
	{
		buff[pos] = *(m_pBuffer+m_iRPos);
		pos++;
		m_iRPos++;
		while( (m_pBuffer[m_iRPos]!=m_Spiter) && (m_iRPos<m_iBufferLen) )
		{
			buff[pos] = *(m_pBuffer+m_iRPos);
			pos++;
			m_iRPos++;
		}

		m_iRPos++;
		long long temp = 0;
		if (sscanf(buff, "%lld", &temp) <= 0)
		{
			return false;
		}

		value = temp;
	}
	else
	{
		m_iRPos += 1;
		return false;
	}

	return true;
}

int    Parser::parser_string_value(char* pBuffer, size_t iLen, size_t pos)
{
	assert( (pBuffer!=NULL) && (iLen>0) );

	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;
	// 字符串索引
	size_t _index  = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				pBuffer = NULL;
				return -2;
			}
			size_t _temp = _pos;
			char   _buff[10240] = "";
			while ( (m_pBuffer[_pos]!=m_Spiter) && (_pos<m_iBufferLen) )
			{
				_buff[_index++] = m_pBuffer[_pos++];
			}
			_buff[_index] = '\0';
			String::copy(pBuffer, _buff, iLen);
			return _temp;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_int_value(int& value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}
			
			int temp = 0;
			if (sscanf(m_pBuffer+_pos, "%d", &temp) <= 0)
			{
				return -1;
			}

			value = temp;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_float_value(float&  value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}
			
			float temp = 0.0f;
			if (sscanf(m_pBuffer+_pos, "%f", &temp) <= 0)
			{
				return -1;
			}

			value = temp;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_char_value(char&   value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}
			
			char temp = '\0';
			if (sscanf(m_pBuffer+_pos, "%c", &temp) <= 0)
			{
				return -1;
			}

			value = temp;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_bool_value(bool&   value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}

			int _data = 0;
			if (sscanf(m_pBuffer+_pos, "%u", &_data) <= 0)
			{
				return -1;
			}
			value = *(bool*)&_data;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_short_value(short&   value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}
			
			int temp = 0;
			if (sscanf(m_pBuffer+_pos, "%d", &temp) <= 0)
			{
				return -1;
			}

			value = temp;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}

int     Parser::parser_int64_value(long long& value, size_t pos)
{
	// 顺序的轮训这个字符串，表示当前是“第几个”元素，开始为最起始的位置，所以为0
	size_t _curPos = 0;
	// 设置当前轮训的位置
	size_t _pos    = 0;

	for (_pos=0; _pos<m_iBufferLen; _pos++)
	{
		if (_curPos == pos)
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				value = 0;
				return -2;
			}

			long long temp = 0;
			if (sscanf(m_pBuffer+_pos, "%lld", &temp) <= 0)
			{
				return -1;
			}

			value = temp;
			return _pos;
		}
		else
		{
			if (m_pBuffer[_pos] == m_Spiter)
			{
				_curPos++;
			}
		}
	}

	return -1;
}
