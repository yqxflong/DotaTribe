#include "../../include/common/Declare.h"
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <WinSock2.h>
#include <Windows.h>
#endif
#include "../../include/net/WinNet.h"
using  namespace  cobra_win;



bool   WinNet::init_network()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
		return false;
#endif

	return true;
}

void   WinNet::destroy_network()
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	WSACleanup(); 
#endif
}
