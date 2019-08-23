#ifndef  _DOTATRIBE_NETSYSTEM_H_
#define  _DOTATRIBE_NETSYSTEM_H_

#include <cocos2d.h>
#include <include/common/Declare.h>
#include <include/mem/MemNode.h>
#include <include/mem/Allocator.h>
#include <include/common/Singleton.h>
#include <curl/curl.h>
#include <string>
#include <list>
using  namespace  cobra_win;

struct sockaddr;
class TCPConnectorThread;
class NetSystem : public cobra_win::Singleton2<NetSystem>
{
public:
	struct _HTTP_DATA_
	{
		int         mType;    // HTTP类型标示
		CURL*       mHandler; // Curl对象
		std::string mHeader;  // HTTP数据包头
		std::string mBuffer;  // 数据对象
		curl_slist* mList;    // 对应的HTTP Header对象数据
		MemNode*    mContent; // 数据对象MemNode
		long long   mSendTime;// 发送时间
		_HTTP_DATA_()
		{
			mType    = -1;
			mHandler = NULL;
			mList    = NULL;
			mContent = NULL;
			mSendTime= 0;
			mHeader.reserve(1024);
			mBuffer.reserve(2048);
		}
		~_HTTP_DATA_()
		{
			if (mContent != NULL)
			{
				NetSystem::get_instance2()->RecoverMemNode(mContent);
				mContent = NULL;
			}
			if (mList != NULL)
			{
				curl_slist_free_all(mList);
				mList = NULL;
			}
		}
	};

private:
	CURLM*  m_pCURLM;                      // LibCurl管理器
	std::list<MemNode*>     m_HTTPSendList;// 当前待发送的所有HTTP数据列表
	std::list<_HTTP_DATA_*> m_HTTPList;    // 当前所有HTTP链接列表
protected:
	fd_set  m_SocketReadSet;      // 套接字可读事件集合
	fd_set  m_SocketWriteSet;     // 套接字可写事件集合
	fd_set  m_SocketExceptionSet; // 套接字异常事件集合

protected:
	SOCKET  m_ConnectSocket;      // 客户端连接套接字

protected:
	unsigned int m_TempRecvLength;   // 当前接受数据数量
	char     m_TempPacketBuffer[128];// 临时接受数据包缓冲区(主要接受包头)
	unsigned int m_TempPacketLength; // 当前接受数据包大小
	MemNode* m_pTempPacketNode;      // 当前接受数据包内存块

protected:
	std::list<MemNode*> m_SendPacketList;  // 待发送包队列
	Allocator<512, 4>   m_PacketMemoryPool;// 网络数据包内存池

protected:
	TCPConnectorThread* m_pConnectThread;  // 服务器连接线程

public:
	NetSystem();
	virtual ~NetSystem();

public:
	/*
		设置DNS解析成功
	*/
	void  SetDNSSuccess();
	/*
		得到DNS解析是否成功
	*/
	bool  IsDNSSuccess();

public:
	/*
		得到连接套接字
	*/
	SOCKET&  GetConnectSocket();

public:
	/*
		从网络数据包内存池申请内存块
	*/
	MemNode* QueryMemNode(unsigned int iLen);
	/*
		回收网络数据包
	*/
	void     RecoverMemNode(MemNode* pNode);

public:
	/*
		连接失败错误提示
	*/
	void ConnnetFailHint();
	/*
		socket断开提示
	*/
	void SocketClosedHint();
	/*
		连接游戏服务器
	*/
	void  ConnectServer();
	/*
		重新连接游戏服务器
	*/
	bool ReConnectServer();

public:
	/************************************************************************/
	/* 发送TCP数据包，bEncryption字段表示是否进行加密                       */
	/* 各个项目需要注意：一般来说，加密的密钥都是通过服务器下发，以此确保每 */
	/* 个连接，每次链接都是唯一的。所以客户端，需要确保在收到服务器密钥之后 */
	/* 的所有数据包都加密，之前则不加密                                     */
	/*                                                                      */
	/* 同时注意客户端各种情况下，例如登出之后重新登陆等等时，需要重新设置加密*/
	/* 目前缺省暂定不加密，后续用时在修改成缺省加密                         */
	/************************************************************************/
	void  SendPacket(MemNode* pNode, bool bEncryption=false);
	/*
		发送HTTP数据包
	*/
	void  SendHTTPPacket(MemNode* pNode);

public:
	/*
		初始化网络系统管理器
	*/
	bool  Init();
	/*
		网络系统逻辑桢更新
	*/
	void  Tick();
	/*
		销毁网络系统管理器
	*/
	void  Destroy();


	/*
		断开网络连接
	*/
	bool DisconnectSocket();

	/*
		强行断开与游戏服务器的连接
	*/
	void ForceDisconnectWithGameServer();

public:
	/*
		关闭套接字, add by fangjun , Warning, not tested.
	*/
	void ClocsSocket();
protected:
	/*
		套接字可读事件处理
	*/
	bool  OnSocketReadEventHandler();
	/*
		套接字可写事件处理
	*/
	bool  OnSocketWriteEventHandler();
	/*
		套接字异常事件处理
	*/
	bool  OnSocketExceptionEventHandler();

private:
	/*
		连接状态Tick更新
	*/
	void  ConnectTick();

	/*
		解析一个包
	*/
	void  ParseOneReceivePacket(MemNode* pTemp);

protected:
	/*
		HTTP套接字可读事件处理
	*/
	bool  OnHTTPReadEventHandler(_HTTP_DATA_* pHTTPData);
	/*
		HTTP套接字可写事件处理
	*/
	bool  OnHTTPWriteEventHandler();
	/*
		HTTP套接字异常事件处理
	*/
	bool  OnHTTPExceptionEventHandler();

private:
	/*
		HTTP下载数据包头保存处理
	*/
	static int OnHTTPHeaderWriter(char *data, size_t size, size_t nmemb, std::string *pData);
	/*
		HTTP下载数据保存处理
	*/
	static int OnHTTPDataWriter(char *data, size_t size, size_t nmemb, std::string *pData);

public:
	friend  class  cobra_win::Singleton2<NetSystem>;
};

#define  NETSYSTEM  (NetSystem::get_instance2())


#endif
