#include "../../include/mem/Memory.h"
#include "../../include/common/Declare.h"
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <assert.h>
#include <conio.h>
#include <crtdbg.h>
#endif
using  namespace  cobra_win;


void   Memory::enable_mem_leak_check()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
}

