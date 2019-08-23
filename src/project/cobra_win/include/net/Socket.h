#ifndef  _LC_COBRA_WIN_SOCKET_H
#define  _LC_COBRA_WIN_SOCKET_H


#include "../common/Declare.h"
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32) 
#include <Windows.h>
#elif (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_ANDROID) || (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_IOS)
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#endif

namespace  cobra_win
{


class  Socket 
{
public:
	/*
		设置套接字为非阻塞状态
	*/
	static   bool    set_socket_unblock(SOCKET sock);
	/*
		设置套接字为阻塞状态
	*/
	static   bool    set_socket_block(SOCKET sock);
	/*
		禁用套接字禁用Nagle算法
	*/
	static   bool    set_socket_nodelay(SOCKET sock);
	/*
		设置套接字的发送数据缓冲区大小
	*/
	static   void    set_socket_send_buffer_size(SOCKET sock, size_t len);
	/*	
		得到套接字的发送数据缓冲区大小
	*/
	static   size_t  get_socket_send_buffer_size(SOCKET sock);
	/*
		设置套接字的接受数据缓冲区大小
	*/
	static   void    set_socket_recv_buffer_size(SOCKET sock, size_t len);
	/*
		得到套接字的接受数据缓冲区大小
	*/
	static   size_t  get_socket_recv_buffer_size(SOCKET sock);
	/*
		设置套接字的发送超时时间
	*/
	static   void    set_socket_send_timeout_value(SOCKET sock, int iTimeout);
	/*
		得到套接字的发送超时时间
	*/
	static   int     get_socket_send_timeout_value(SOCKET sock);
	/*
		设置套接字的接受超时时间
	*/
	static   void    set_socket_recv_timeout_value(SOCKET sock, int iTimeout);
	/*
		得到套接字的接受超时时间
	*/
	static   int     get_socket_recv_timeout_value(SOCKET sock);
	/*
		设置套接字为可重用状态
	*/
	static   void    set_socket_reuse(SOCKET sock);
	/*
		关闭套接字
	*/
	static   void    close_socket(SOCKET sock);

public:
	/*
		创建socket
	*/
	static   SOCKET  create_tcp_socket();
	/*
		监听操作
	*/
	static   int     listen(SOCKET socket);
	/*
		连接操作
	*/
	static   int     connect(SOCKET socket, const sockaddr* name, int namelen);
	/*
		系统套接字接受操作
		-1:	操作失败，应该关闭对应套接字
		0:  暂无数据
	*/
	static   int     recv(SOCKET socket, char* pBuffer, int iBufferLen, int flags);
	/*
		系统套接字发送操作
		-1:	操作失败，应该关闭对应套接字
		0:  暂无数据
	*/
	static   int     send(SOCKET socket, char* pBuffer, int iBufferLen, int flags);
	
public:
	/*
		创建socket
	*/
	static   SOCKET  create_udp_socket();
	/*
		系统套接字接受操作
		-1:	操作失败，应该关闭对应套接字
		0:  暂无数据
	*/
	static   int     recvfrom(SOCKET socket, char* pBuffer, int iBufferLen, const sockaddr* fromAddr, int* fromAddrLen);
	/*
		系统套接字发送操作
		-1:	操作失败，应该关闭对应套接字
		0:  暂无数据
	*/
	static   int     sendto(SOCKET socket, char* pBuffer, int iBufferLen, const sockaddr* sendAddr, int sendAddrLen);

public:
	/*
		绑定操作
	*/
	static   int     bind(SOCKET socket, const sockaddr* name, int namelen);
	/*
		监听连接操作
	*/
	static   SOCKET  accept(SOCKET socket);
	/*
		Select轮询操作
	*/
	static   int     select(int number, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval* timeout);

};



}



#endif
