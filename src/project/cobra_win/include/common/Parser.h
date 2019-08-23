#ifndef  _LC_COBRA_WIN_PARSER_H
#define  _LC_COBRA_WIN_PARSER_H


#include <stdio.h>

namespace  cobra_win
{


class  Parser
{
private:
	char*   m_pBuffer;
	size_t  m_iBufferLen;
	char    m_Spiter;
	size_t  m_iRPos;

public:
	Parser();
	Parser(char* pBuffer, size_t iLen, char spiter);
	~Parser();

public:
	/*
		得到当前读指针位置
	*/
	size_t   get_read_pos();
	/*
		设置当前读指针位置
	*/
	void     set_read_pos(size_t iPos);
	/*
		清空缓冲区并且将“读文件的指针位置”设置成开始位置
	*/
	void     clear();
	/*
		重新设置数据
	*/
	void     reset(char* pBuffer, size_t iLen, char spiter);
	/*
		设置分割符号
	*/
	void     set_spit_char(char spiter);

public:
	/*
		读取字符串,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_string_value(char* pBuffer, size_t iLen);
	/*
		读取INT,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_int_value(int&    value);
	/*
		读取FLOAT,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_float_value(float&  value);
	/*
		读取字符,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_char_value(char&   value);
	/*
		读取布尔变量,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_bool_value(bool&   value);
	/*
		读取SHORT,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_short_value(short&  value);
	/*
		读取LONG LONG,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	bool     parser_int64_value(long long& value);

public:
	// 所有元素的开始为0号元素，然后为1号元素，2号元素.......
	// 警告：可户端必须对函数返回值进行分析。
	// -1表示出现了问题
	// -2表示这个位置没有真实的值，为空
	// >=0表示所要找的哪个元素在这个字符串中的开始地址
	/*
		读取指定位置的字符串,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_string_value(char* pBuffer, size_t iLen, size_t pos);
	/*
		读取指定位置的INT,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_int_value(int&    value, size_t pos);
	/*
		读取指定位置的FLOAT,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_float_value(float&  value, size_t pos);
	/*
		读取指定位置的字符,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_char_value(char&   value, size_t pos);
	/*
		读取指定位置的布尔变量,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_bool_value(bool&   value, size_t pos);
	/*
		读取指定位置的WORD,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_short_value(short&   value, size_t pos);
	/*
		读取指定位置的LONG LONG,“读位置”自动的移动到下一个"单位元"数据的位置上面
	*/
	int      parser_int64_value(long long&  value, size_t pos);
};


}


#endif
