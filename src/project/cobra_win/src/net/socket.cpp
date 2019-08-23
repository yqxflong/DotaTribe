#include "../../include/common/Declare.h"
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
#include <WinSock2.h>
#include <Windows.h>
#include <assert.h>
#else
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/errno.h>
#endif
#include "../../include/net/Socket.h"
using  namespace  cobra_win;



bool    Socket::set_socket_unblock(SOCKET sock)
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	int opt = 1;
	if (ioctlsocket(sock, FIONBIO, (u_long FAR*)&opt) == 0)
		return true;
#else
	int flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags | O_NONBLOCK);
#endif

	return false;
}

bool    Socket::set_socket_block(SOCKET sock)
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	int opt = 0;
	if (ioctlsocket(sock, FIONBIO, (u_long FAR*)&opt) == 0)
		return true;
#else
	int flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags & (~O_NONBLOCK));
#endif

	return false;
}

bool    Socket::set_socket_nodelay(SOCKET sock)
{
	int flag = 1;
	int ret = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
	if (ret == -1)
		return false;

	return true;
}

void    Socket::set_socket_send_buffer_size(SOCKET sock, size_t len)
{
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&len, sizeof(len));
}

size_t  Socket::get_socket_send_buffer_size(SOCKET sock)
{
	int size = 0;
	int len = sizeof(int);
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, &len);
#else
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, (socklen_t*)&len);
#endif
	return (size_t)size;
}

void    Socket::set_socket_recv_buffer_size(SOCKET sock, size_t len)
{
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&len, sizeof(len));
}

size_t  Socket::get_socket_recv_buffer_size(SOCKET sock)
{
	int size = 0;
	int len = sizeof(int);
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, &len);
#else
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, (socklen_t*)&len);
#endif
	return (size_t)size;
}

void    Socket::set_socket_send_timeout_value(SOCKET sock, int iTimeout)
{
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&iTimeout, sizeof(iTimeout));
}

int     Socket::get_socket_send_timeout_value(SOCKET sock)
{
	int size = 0;
	int len = sizeof(int);
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	getsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&size, &len);
#else
	getsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&size, (socklen_t*)&len);
#endif

	return size;
}

void    Socket::set_socket_recv_timeout_value(SOCKET sock, int iTimeout)
{
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeout, sizeof(iTimeout));
}

int     Socket::get_socket_recv_timeout_value(SOCKET sock)
{
	int size = 0;
	int len = sizeof(int);
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	getsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&size, &len);
#else
	getsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&size, (socklen_t*)&len);
#endif
	return size;
}

void    Socket::set_socket_reuse(SOCKET sock)
{
	int reuse = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int));
}

void    Socket::close_socket(SOCKET sock)
{
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	closesocket(sock);
#else
    close(sock);
#endif
}

SOCKET  Socket::create_tcp_socket()
{
	SOCKET ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ret == INVALID_SOCKET)
		return -1;
#else
	return ::socket(AF_INET, SOCK_STREAM, 0);
#endif

	return ret;
}

int     Socket::listen(SOCKET socket)
{
	return ::listen(socket, 1);
}

int     Socket::connect(SOCKET socket, const sockaddr* name, int namelen)
{
	return ::connect(socket, name, namelen);
}

int     Socket::recv(SOCKET socket, char* pBuffer, int iBufferLen, int flags)
{
	int ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::recv(socket, pBuffer, iBufferLen, flags);
	if (ret == 0)
	{
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		if (WSAEWOULDBLOCK == WSAGetLastError())
			return 0;
	}
#else
	ret = ::recv(socket, pBuffer, iBufferLen, flags);
	if (ret < 0)
		if (errno == EAGAIN)
			ret = 0;
#endif

	return ret;
}

int     Socket::send(SOCKET socket, char* pBuffer, int iBufferLen, int flags)
{
	int ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::send(socket, pBuffer, iBufferLen, flags);
	if (ret == 0)
	{
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		if (WSAEWOULDBLOCK == WSAGetLastError())
			return 0;
	}
#else
	ret = ::send(socket, pBuffer, iBufferLen, flags);
	if (ret < 0)
		if (errno == EAGAIN)
			ret = 0;
#endif

	return ret;
}

SOCKET  Socket::create_udp_socket()
{
	SOCKET ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (ret == INVALID_SOCKET)
		return -1;
#else
	return ::socket(AF_INET, SOCK_DGRAM, 0);
#endif

	return ret;
}

int     Socket::recvfrom(SOCKET socket, char* pBuffer, int iBufferLen, const sockaddr* fromAddr, int* fromAddrLen)
{
	int ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::recvfrom(socket, pBuffer, iBufferLen, 0, (struct sockaddr*)fromAddr, fromAddrLen);
	if (ret == 0)
	{
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		if (WSAEWOULDBLOCK == WSAGetLastError())
			return 0;
	}
#else
	ret = ::recvfrom(socket, pBuffer, iBufferLen, 0, (struct sockaddr*)fromAddr, (socklen_t*)fromAddrLen);
	if (ret < 0)
		if (errno == EAGAIN)
			ret = 0;

	return ret;
#endif

	return ret;
}

int     Socket::sendto(SOCKET socket, char* pBuffer, int iBufferLen, const sockaddr* sendAddr, int sendAddrLen)
{
	int ret = -1;
#if (COBRA_TARGET_PLATFORM==COBRA_PLATFORM_WIN32)
	ret = ::sendto(socket, pBuffer, iBufferLen, 0, (struct sockaddr*)sendAddr, sendAddrLen);
	if (ret == 0)
	{
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		if (WSAEWOULDBLOCK == WSAGetLastError())
			return 0;
	}
#else
	ret = ::sendto(socket, pBuffer, iBufferLen, 0, (struct sockaddr*)sendAddr, sendAddrLen);
	if (ret < 0)
		if (errno == EAGAIN)
			ret = 0;
#endif

	return ret;
}

int     Socket::select(int number, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval* timeout)
{
	return ::select(number, readfds, writefds, exceptfds, (struct timeval*)timeout);
}

SOCKET  Socket::accept(SOCKET socket)
{
	return ::accept(socket, NULL, NULL);
}

int     Socket::bind(SOCKET socket, const sockaddr* name, int namelen)
{
	return ::bind(socket, name, namelen);
}
