#ifndef  _LC_COBRA_WIN_CONSOLE_H
#define  _LC_COBRA_WIN_CONSOLE_H


namespace  cobra_win
{


class  Console
{
public:
	enum  _CONSOLE_TEXT_COLOR_
	{
		_TYPED_TEXT_BLACK_COLOR_,
		_TYPED_TEXT_RED_COLOR_,
		_TYPED_TEXT_GREEN_COLOR_,
		_TYPED_TEXT_BROWN_COLOR_,
		_TYPED_TEXT_BLUE_COLOR_,
		_TYPED_TEXT_MAGENTA_COLOR_,
		_TYPED_TEXT_CYAN_COLOR_,
		_TYPED_TEXT_GREY_COLOR_,
		_TYPED_TEXT_YELLOW_COLOR_,
		_TYPED_TEXT_LRED_COLOR_,
		_TYPED_TEXT_LGREEN_COLOR_,
		_TYPED_TEXT_LBLUE_COLOR_,
		_TYPED_TEXT_LMAGENTA_COLOR_,
		_TYPED_TEXT_LCYAN_COLOR_,
		_TYPED_TEXT_WHITE_COLOR_
	};

public:
	/*
		设置控制台标题
	*/
	static    void    set_console_title(char* pConsoleTitle);
	/*
		得到控制台标题
	*/
	static    bool    get_console_title(char* pBuffer, unsigned long iLen);
	/*
		打印信息
	*/
	static    void    show(char* pBuffer);
	/*
		设置输出字符串的颜色
	*/
	static    void    set_text_color(_CONSOLE_TEXT_COLOR_ color);
	/*
		恢复输出字符串的颜色为默认值
	*/
	static    void    reset_text_color();
};


}


#endif
