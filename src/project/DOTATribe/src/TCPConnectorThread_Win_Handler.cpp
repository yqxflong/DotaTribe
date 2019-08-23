#include <cocos2d.h> 
#include "../include/TCPConnectorThread.h" 
#include "../include/VariableSystem.h" 
#include "../include/NetSystem.h" 
#include <include/net/Socket.h> 
#include "../include/CSMapTable.h" 
#include "../include/LoggerSystem.h" 
#include "../include/DOTATribeApp.h" 
#include "../include/ServerInfoDataHandler.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

/*
	开机走2次，第一次是连接网关，第二次是连接游戏服务器
*/
void* TCPConnectorThread::run()
{
	do 
	{
		const char* serverip = SERVERINFODATAINFO->getCurServerIP();
		std::string str1 = serverip;
		std::string str2 = "111.206.12.161";
		if (str1 == str2)
		{
			serverip = "10.127.133.26";
		}
		int serverport=SERVERINFODATAINFO->getCurPort();
		char serverURL[1024]="";
		strcpy(serverURL,serverip);
		int serverPort =serverport;
		
		struct hostent* pPtr = gethostbyname(serverURL);
		if (pPtr == NULL)
		{
			SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_);
			break;
		}

		if (pPtr->h_addrtype != AF_INET)
		{
			SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_);
			break;
		}

		char* pIP = inet_ntoa(*(struct in_addr*)*pPtr->h_addr_list);
		if (pIP == NULL)
		{
			SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_);
			break;
		}

		sockaddr_in serverAddr; 
		serverAddr.sin_family      = AF_INET;
		serverAddr.sin_addr.s_addr = inet_addr(pIP);
		serverAddr.sin_port        = htons(serverPort);

		SOCKET& sock = NETSYSTEM->GetConnectSocket();
		sock = Socket::create_tcp_socket();
		if (sock == INVALID_SOCKET)
		{
			sock = -1;
			SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_);
			break;
		}

		int ret = Socket::connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		if (ret == SOCKET_ERROR)
		{
			sock = -1;
			SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_);
			break;
		}

		SetThreadState(TCPConnectorThread::_TYPED_THREAD_EXIT_SUCCESS_);
	} 
	while (false);

	return NULL;
}


#endif
