#include "../../include/common/Console.h"
#include "../../include/common/Declare.h"
#include <stdio.h>
#include <assert.h>
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <Windows.h>
#endif
using  namespace  cobra_win;


void    Console::set_console_title(char* pConsoleTitle)
{
	assert(pConsoleTitle != NULL);

#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	SetConsoleTitle(pConsoleTitle);
#endif
}

bool    Console::get_console_title(char* pBuffer, unsigned long iLen)
{
	assert(pBuffer!=NULL && iLen>0);

#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	DWORD ret = GetConsoleTitle(pBuffer, iLen);
	if (ret == 0)
		return false;
#endif

	return true;
}

void    Console::show(char* pBuffer)
{
	assert(pBuffer != NULL);

	printf("%s\n", pBuffer);
}

#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
static WORD WinColorFG[] =
{
	// BLACK
	0,   
	// RED
	FOREGROUND_RED,
	// GREEN
	FOREGROUND_GREEN,
	// BROWN
	FOREGROUND_RED | FOREGROUND_GREEN,
	// BLUE
	FOREGROUND_BLUE, 
	// MAGENTA
	FOREGROUND_RED | FOREGROUND_BLUE, 
	// CYAN
	FOREGROUND_GREEN | FOREGROUND_BLUE,  
	// WHITE
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	// YELLOW
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	// RED_BOLD
	FOREGROUND_RED | FOREGROUND_INTENSITY,
	// GREEN_BOLD
	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	// BLUE_BOLD
	FOREGROUND_BLUE | FOREGROUND_INTENSITY,             
	// MAGENTA_BOLD
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	// CYAN_BOLD
	FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	// WHITE_BOLD
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};
#endif

void    Console::set_text_color(_CONSOLE_TEXT_COLOR_ color)
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != NULL)
	{
		SetConsoleTextAttribute(hConsole, WinColorFG[color]);
	}
#endif
}

void    Console::reset_text_color()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != NULL)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
#endif
}
