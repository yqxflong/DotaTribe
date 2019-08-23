#include <cocos2d.h>
#include "../include/NetSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/VariableSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/TCPConnectorThread.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/PacketFactory.h"
#include "../include/PacketFactoryManager.h"
#include "../include/SysLangDataManager.h"
#include <include/net/Socket.h>
#include <include/net/WinNet.h>
#include "../include/HeartBeatDataHandler.h"
#include "../include/DebugerSystem.h"
#include "../include/NetDebuger.h"
#include "../include/TimeSystem.h"
#include <iostream>
#include "../include/DOTATribeApp.h"
#include "../include/CSCreateRolePacket.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/MessageBoxWindow.h"


// 数据包前缀大小
#define  _RECVED_PACKET_PREFIX_HEADER_ (sizeof(char)*2)
// 数据包头大小
#define  _RECVED_PACKET_HEADER_LENGTH_ (sizeof(char)*2+sizeof(int))


template<> NetSystem* cobra_win::Singleton2<NetSystem>::m_pMySelf = NULL;

NetSystem::NetSystem()
{
	m_pCURLM = NULL;
	m_HTTPList.clear();

	m_ConnectSocket = -1;

	m_pConnectThread = NULL;

	m_TempRecvLength   = 0;
	m_TempPacketLength = 0;
	memset(m_TempPacketBuffer, 0, sizeof(m_TempPacketBuffer));
	m_pTempPacketNode  = NULL;

	m_HTTPSendList.clear();
	m_SendPacketList.clear();
}

NetSystem::~NetSystem()
{

}

void NetSystem::SetDNSSuccess()
{
	bool parserServerURL = true;
	VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_, "DNS", "ParserServerURLSuccess", parserServerURL);
}

bool NetSystem::IsDNSSuccess()
{
	bool parserServerURL = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_, "DNS", "ParserServerURLSuccess", parserServerURL);
	return parserServerURL;
}

SOCKET& NetSystem::GetConnectSocket()
{
	return m_ConnectSocket;
}

MemNode* NetSystem::QueryMemNode(unsigned int iLen)
{
	return m_PacketMemoryPool.query_mem_node(iLen);
}

void NetSystem::RecoverMemNode(MemNode* pNode)
{
	pNode->clear();
	m_PacketMemoryPool.insert_mem_node(pNode);
}

void NetSystem::ConnectServer()
{
	if (m_pConnectThread != NULL)
		return;

	m_pConnectThread = new TCPConnectorThread;
	m_pConnectThread->create_thread();
}

bool NetSystem::ReConnectServer()
{
	if (m_pConnectThread == NULL){
		Socket::close_socket(m_ConnectSocket);
		m_ConnectSocket = -1;
		m_pConnectThread = new TCPConnectorThread;
		m_pConnectThread->create_thread();
		return true;
	}
	return false;
}


void NetSystem::SendPacket(MemNode* pNode, bool bEncryption)
{
	// 判断是否进行加密
	if (bEncryption)
	{
		char* pBuffer = pNode->get_buff();
		// 跳过前两个字节
		pBuffer = pBuffer+sizeof(char)*2;
		// 得到整个包长度
		int iPacketLen = *((int*)pBuffer);
		pBuffer = pBuffer+sizeof(int);

		// 获得加密密钥
		// 一般在登陆完成，收到服务器返回的加密密钥之后，保存在内存里面
		// 如果需要返回登陆界面，重新登陆的话，需要先清空，在登陆
		// 切记，登陆之前的包不加密，只有收到密钥后的所有包在加密，注意各种异常处理环节
		char buffer[1024] = "";
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_, "NET", "PacketEncryptionLen", buffer, sizeof(buffer));
		if (buffer[0] == '\0')
			return;

		// 加密数据包内容(类型+真实内容)
		unsigned int iEncryptionKeyLen = strlen(buffer);
		for (unsigned int i=0; i<pNode->get_write_pos()-sizeof(char*)-sizeof(int); i++)
		{
			char temp = pBuffer[i];
			pBuffer[i] = (char)(temp^buffer[i%iEncryptionKeyLen]);
		}
	}

	m_SendPacketList.push_back(pNode);
}

void NetSystem::SendHTTPPacket(MemNode* pNode)
{
	m_HTTPSendList.push_back(pNode);
}

bool  NetSystem::Init()
{
	do 
	{
		// 初始化系统网络模块
		if (!WinNet::init_network())
			break;

		// 初始化网络数据包内存池
		m_PacketMemoryPool.init_allocator(16);

		// 初始化
		CURLcode ret = curl_global_init(CURL_GLOBAL_ALL);
		if (ret != CURLE_OK)
			break;

		m_pCURLM = curl_multi_init();
		if (m_pCURLM == NULL)
			break;

		int maxConnect = 1024;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "MaxConnect", maxConnect);
		CURLMcode ret2 = curl_multi_setopt(m_pCURLM, CURLMOPT_MAXCONNECTS, (long)maxConnect);
		if (ret2 != CURLM_OK)
			break;

		long waitTime = 0;
		ret2 = curl_multi_timeout(m_pCURLM, &waitTime);
		if (ret2 != CURLM_OK)
			break;

		/*
			初始化PacketFactoryManager
		*/
		PacketFactoryManager::get_instance()->Init();
		LOGGERSYSTEM->LogInfo("Init NetSystem Success\n");

		//
		return true;
	} 
	while (false);

	LOGGERSYSTEM->LogInfo("Init NetSystem Failed\n");
	return false;
}

void  NetSystem::Tick()
{

#ifdef HEART_BEAT
	//心跳检测
	if (SERVERINFODATAINFO->CanResetCounter_HeartCheck())
		HEARTBEATDATAHANDLER->setNoReplyCount(0);
	else
		HEARTBEATDATAHANDLER->doTickCheckLogic();
#endif
	
	do 
	{
		// 判断所有HTTP连接
		fd_set readSet;
		fd_set writeSet;
		fd_set exceptionSet;
		FD_ZERO(&readSet);
		FD_ZERO(&writeSet);
		FD_ZERO(&exceptionSet);

		int number = 0;
		int max    = 0;
		CURLMcode ret = curl_multi_perform(m_pCURLM, &number);
		if (ret != CURLM_OK)
			break;

		if (number)
		{			
			if (curl_multi_fdset(m_pCURLM, &readSet, &writeSet, &exceptionSet, &max))
				break;

			if (max == -1)
				break;

			struct timeval interval;
			interval.tv_sec  = 0;
			interval.tv_usec = 0;
			int ret = Socket::select(max+1, &readSet, &writeSet, &exceptionSet, &interval);
			if (ret == 0)
				break;
			else if (ret == -1)
				break;
		}	

		CURLMsg* pMSG = NULL;
		int msgNumber = 0;
		while ((pMSG=curl_multi_info_read(m_pCURLM, &msgNumber)))
		{
			if (pMSG->msg == CURLMSG_DONE)
			{
				CURL* pTemp = pMSG->easy_handle;
				std::list<_HTTP_DATA_*>::iterator iter   = m_HTTPList.begin();
				std::list<_HTTP_DATA_*>::iterator iter_e = m_HTTPList.end();
				for ( ; iter!=iter_e; ++iter)
				{
					if ((*iter)->mHandler == pTemp)
					{
						OnHTTPReadEventHandler((*iter));

						delete (*iter);
						m_HTTPList.erase(iter);
						break;
					}	
				}

				curl_multi_remove_handle(m_pCURLM, pTemp);
				curl_easy_cleanup(pTemp);
			}
		}
		// 如果HTTP列表为空了，则可以下发后面的消息了
		OnHTTPWriteEventHandler();
	} 
	while (false);
	ConnectTick();
	if (m_pConnectThread != NULL)
		return;

	// 如果已经断开连接，则不进行逻辑Tick
	if (m_ConnectSocket == -1)
		return;

	// 连接事件轮询监听
	FD_ZERO(&m_SocketReadSet);
	FD_SET(m_ConnectSocket, &m_SocketReadSet);
	FD_ZERO(&m_SocketWriteSet);
	FD_SET(m_ConnectSocket, &m_SocketWriteSet);
	FD_ZERO(&m_SocketExceptionSet);
	FD_SET(m_ConnectSocket, &m_SocketExceptionSet);

	struct timeval interval;
	interval.tv_sec  = 0;
	interval.tv_usec = 0;
	int ret = Socket::select(m_ConnectSocket+1, &m_SocketReadSet, &m_SocketWriteSet, &m_SocketExceptionSet, &interval);
	if (ret == 0)
		return;
	else if (ret == -1)
		return;

	do 
	{
		if (FD_ISSET(m_ConnectSocket, &m_SocketReadSet))
		{
			if (!OnSocketReadEventHandler())
				break;
			//如果解包时需要断socket的话，直接返回
			if (m_ConnectSocket==-1)
				break;
		}
		if (FD_ISSET(m_ConnectSocket, &m_SocketWriteSet))
		{
			if (!OnSocketWriteEventHandler())
				break;
		}
		if (FD_ISSET(m_ConnectSocket, &m_SocketExceptionSet))
		{
			if (!OnSocketExceptionEventHandler())
				break;
		}
	} 
	while (false);
}

void NetSystem::Destroy()
{
	// 清空列表
	std::list<_HTTP_DATA_*>::iterator iter   = m_HTTPList.begin();
	std::list<_HTTP_DATA_*>::iterator iter_e = m_HTTPList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		curl_multi_remove_handle(m_pCURLM, (*iter)->mHandler);
		curl_easy_cleanup((*iter)->mHandler);
		delete (*iter);
	}
	m_HTTPList.clear();

	// 清空管理器
	if (m_pCURLM != NULL)
	{
		curl_multi_cleanup(m_pCURLM);
		m_pCURLM = NULL;
	}
	curl_global_cleanup();

	Socket::close_socket(m_ConnectSocket);
	m_ConnectSocket = -1;

	// 销毁ConnectThread
	if (m_pConnectThread != NULL)
	{
		delete m_pConnectThread;
		m_pConnectThread = NULL;
	}

	// 释放临时接受数据包信息
	m_TempPacketLength = 0;
	m_TempRecvLength   = 0;
	memset(m_TempPacketBuffer, 0, sizeof(m_TempPacketBuffer));
	if (m_pTempPacketNode != NULL)
	{
		RecoverMemNode(m_pTempPacketNode);
		m_pTempPacketNode=NULL;
	}

	// 清空HTTP待发送队列
	std::list<MemNode*>::iterator iter2   = m_HTTPSendList.begin();
	std::list<MemNode*>::iterator iter2_e = m_HTTPSendList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		delete (*iter2);
	}
	m_HTTPSendList.clear();

	// 清空待发送队列
	iter2   = m_SendPacketList.begin();
	iter2_e = m_SendPacketList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		delete (*iter2);
	}
	m_SendPacketList.clear();

	// 销毁网络数据包内存池
	m_PacketMemoryPool.destroy_allocator();
	WinNet::destroy_network();

	//释放PacketFactoryManager
	PacketFactoryManager::get_instance()->Destroy();

	LOGGERSYSTEM->LogInfo("Destroy NetSystem Success\n");
}

void NetSystem::ClocsSocket()
{
	if (m_ConnectSocket!=-1)
	{
		OnSocketExceptionEventHandler();
	}
}

void NetSystem::ConnectTick()
{
	if (m_pConnectThread != NULL)
	{
		int state = m_pConnectThread->GetThreadState();
		if (state == TCPConnectorThread::_TYPED_THREAD_RUNING_)
		{// 连接中...
			/*
				提示用户，正在连接服务器
			*/
			LOGGERSYSTEM->LogInfo("NetSystem::ConnectTick====CONNECTING!");
		}
		else if (state == TCPConnectorThread::_TYPED_THREAD_EXIT_FAILED_)
		{// 连接失败
			LOGGERSYSTEM->LogInfo("NetSystem::ConnectTick====FAIL!");
			delete m_pConnectThread;
			m_pConnectThread = NULL;
			ConnnetFailHint();
		}
		else if (state == TCPConnectorThread::_TYPED_THREAD_EXIT_SUCCESS_){// 连接成功
			LOGGERSYSTEM->LogInfo("NetSystem::ConnectTick====SUCCESS!");
			/*
				=====固定操作，非逻辑=====
			*/
			{
				delete m_pConnectThread;
				m_pConnectThread = NULL;
				// 设置可重用性
				Socket::set_socket_reuse(m_ConnectSocket);
				// 设置接受缓冲区大小(128K)
				Socket::set_socket_recv_buffer_size(m_ConnectSocket, 128*1024);
				// 设置发送缓冲区大小(128K)
				Socket::set_socket_send_buffer_size(m_ConnectSocket, 128*1024);
				// 设置为非阻塞式连接
				Socket::set_socket_unblock(m_ConnectSocket);
			}
			/*
				处理网络连接后相关事宜
			*/
			SERVERINFODATAINFO->HandleCurrentOperationAfterConnetNetwork();
		}
	}
}

	/*
		解析一个包
	*/
void NetSystem::ParseOneReceivePacket(MemNode* pTemp){
	assert(pTemp!=NULL);
	if (pTemp->size() >= (_RECVED_PACKET_HEADER_LENGTH_+sizeof(short)))
	{
		unsigned short packetType = *((unsigned short*)(pTemp->get_buff()+_RECVED_PACKET_HEADER_LENGTH_));
		IPacketFactory* pFactory = PacketFactoryManager::get_instance()->GetPacketFactoryByType(packetType);
		if (pFactory != NULL)
		{
			pFactory->OnPacketHandler(pTemp->get_buff(), pTemp->size());
		}
		else
		{
			LOGGERSYSTEM->LogError("NET:	UnRegister Packet Factory, Packet Type=%u", packetType);
		}
	}	
}

bool NetSystem::OnSocketReadEventHandler()
{
	while (true)
	{
		/*
			解析包头
		*/
		if (m_TempRecvLength < _RECVED_PACKET_HEADER_LENGTH_)
		{
			int recvLen = _RECVED_PACKET_HEADER_LENGTH_-m_TempRecvLength;
			int ret = Socket::recv(m_ConnectSocket, m_TempPacketBuffer+m_TempRecvLength, recvLen, 0);
			if (ret < 0)
			{// 读取出错了
				goto RECV_FAILED;
			}
			else if (ret == 0)
			{
				goto RECV_END;
			}

			m_TempRecvLength += ret;
			if (ret < recvLen)
			{// 数据包没有完全读物完，继续读
				continue;
			}

			m_TempPacketLength = *((int*)(m_TempPacketBuffer+_RECVED_PACKET_PREFIX_HEADER_));
			m_pTempPacketNode = QueryMemNode(m_TempPacketLength);
			m_pTempPacketNode->push(m_TempPacketBuffer, m_TempRecvLength);
			memset(m_TempPacketBuffer, 0, sizeof(m_TempPacketBuffer));
		}

		/*
			解析包身
		*/
		do 
		{
			int recvLen = m_TempPacketLength-m_TempRecvLength;
			int ret = Socket::recv(m_ConnectSocket, m_pTempPacketNode->get_buff()+m_pTempPacketNode->get_write_pos(), recvLen, 0);
			if (ret < 0)
			{// 读取出错了
				goto RECV_FAILED;
			}
			else if (ret == 0)
			{
				goto RECV_END;
			}

			m_pTempPacketNode->set_write_pos(m_pTempPacketNode->get_write_pos()+ret);
			m_TempRecvLength += ret;
			if (m_TempRecvLength == m_TempPacketLength)
			{
				//即时解析这个包
				ParseOneReceivePacket(m_pTempPacketNode);
				// 清理该包相关参数;
				m_TempRecvLength   = 0;
				m_TempPacketLength = 0;
				RecoverMemNode(m_pTempPacketNode);
				m_pTempPacketNode  = NULL;
				break;
			}
		} 
		while (true);
	}

RECV_FAILED:
	OnSocketExceptionEventHandler();
	return false;

RECV_END:
	return true;
}

bool NetSystem::OnSocketWriteEventHandler()
{
	while (true)
	{
		// 没有可发送数据，直接退出
		if (m_SendPacketList.size() <= 0)
			goto SEND_END;

		std::list<MemNode*>::iterator iter   = m_SendPacketList.begin();
		std::list<MemNode*>::iterator iter_e = m_SendPacketList.end();
		for ( ; iter!=iter_e; )
		{
			std::list<MemNode*>::iterator temp = iter;
			++iter;

			MemNode* pNode = (*temp);
			char*    pBuffer = pNode->get_buff();
			/*
				多了2个字节，so删掉最后一个
			*/
			//int packetLen = *((int*)(pBuffer+_RECVED_PACKET_PREFIX_HEADER_))+_RECVED_PACKET_PREFIX_HEADER_;
			int packetLen = *((int*)(pBuffer+_RECVED_PACKET_PREFIX_HEADER_));
			int ret = Socket::send(m_ConnectSocket, pNode->get_buff()+pNode->get_read_pos(), packetLen-pNode->get_read_pos(), 0);
			if (ret < 0)
			{// 发送失败
				goto SEND_FAILED;
			}
			else if (ret == 0)
			{
				goto SEND_END;
			}

			pNode->set_read_pos(pNode->get_read_pos()+ret);
			if (pNode->get_read_pos() == packetLen)
			{// 回收该节点
				RecoverMemNode(pNode);
				m_SendPacketList.erase(temp);
			}
		}
	}
	
SEND_FAILED:
	OnSocketExceptionEventHandler();
	return false;

SEND_END:
	return true;
}

	/*
		强行断开与游戏服务器的连接
	*/
void NetSystem::ForceDisconnectWithGameServer(){
	DisconnectSocket();
	SocketClosedHint();
}

/*
	断开网络连接
*/
bool NetSystem::DisconnectSocket(){
	LOGGERSYSTEM->LogInfo("========NetSystem::DisconnectSocket========");
	// 关闭套接字
	Socket::close_socket(m_ConnectSocket);
	m_ConnectSocket = -1;
	
	// 回收发送缓冲区
	std::list<MemNode*>::iterator iter   = m_SendPacketList.begin();
	std::list<MemNode*>::iterator iter_e = m_SendPacketList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		(*iter)->clear();
		RecoverMemNode((*iter));
	}
	m_SendPacketList.clear();

	return true;
}

/*
	网络出现异常，需要处理
	#自行断开时不会走的
*/
bool NetSystem::OnSocketExceptionEventHandler()
{
	if(DisconnectSocket()){
		//******************网络遇到异常，已经全部释放结束*******************//
		LOGGERSYSTEM->LogInfo("!!!!!!!!!!!!NetSystem::OnSocketExceptionEventHandler!!!!!!!!");
		LOGGERSYSTEM->LogInfo("The Socket Has Been Killed!!!");
		LOGGERSYSTEM->LogInfo("!!!!!!!!!!!!NetSystem::OnSocketExceptionEventHandler!!!!!!!!");
		//
		SocketClosedHint();
		return true;
	}

	return false;
}

/*
	
*/
bool NetSystem::OnHTTPReadEventHandler(_HTTP_DATA_* pHTTPData)
{
	do 
	{
		// 获得返回的标示信息
		int code = 0;
		CURLcode ret = curl_easy_getinfo(pHTTPData->mHandler, CURLINFO_RESPONSE_CODE, &code);
		if (ret!=CURLM_OK || code!=200)
		{
			LOGGERSYSTEM->LogInfo("NET: On HTTP Read Event Handler End, get response code=%d error\n", code);
			break;
		}

		// 获得content length，并校验
		double length = 0;
		ret = curl_easy_getinfo(pHTTPData->mHandler, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &length);
		if (ret!=CURLM_OK || length<=0 || pHTTPData->mBuffer.length()!=length)
		{
			LOGGERSYSTEM->LogInfo("NET: On HTTP Read Event Handler End, get content length=%d error\n", length);
			break;
		}

		// 获取opcode
		int pos = pHTTPData->mHeader.find("packetType: ");
		if (pos == std::string::npos)
		{
			LOGGERSYSTEM->LogInfo("NET: On HTTP Read Event Handler End, can not find opcode\n");
			break;
		}

		// 交给对应的管理器解析
		unsigned short packetType = 0;
		sscanf(pHTTPData->mHeader.c_str()+pos+strlen("packetType: "), "%hu", &packetType);
		IPacketFactory* pFactory = PacketFactoryManager::get_instance()->GetPacketFactoryByType(packetType);
		if (pFactory != NULL)
		{
			pFactory->OnPacketHandler((char*)(pHTTPData->mBuffer.c_str()), pHTTPData->mBuffer.size());
		}
		else
		{
			LOGGERSYSTEM->LogError("NET:	UnRegister HTTP Packet Factory, Packet Type=%u", packetType);
		}

		return true;
	} 
	while (false);

	OnHTTPExceptionEventHandler();
	return false;
}

/*
	发送队列里的一个Http包
*/
bool NetSystem::OnHTTPWriteEventHandler()
{
	// 如果没有待发送的列表，则不需要发送
	if (m_HTTPSendList.size() <= 0)
		return true;

	MemNode* pMemNode = m_HTTPSendList.front();
	m_HTTPSendList.pop_front();

	/*
		url地址
	*/
	char buffer[1024] = "http://www.baidu.com";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "GateWayURL", buffer, sizeof(buffer));
	do 
	{
		CURLcode ret = CURLE_OK;

		_HTTP_DATA_* pHTTPData = new _HTTP_DATA_;
		unsigned short tempType = 0;
		pMemNode->pop<unsigned short>(tempType);
		pHTTPData->mType = tempType;

		pHTTPData->mHandler = curl_easy_init();
		if (pHTTPData->mHandler == NULL)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, init easy curl error\n");
			break;
		}

		pHTTPData->mList = curl_slist_append(pHTTPData->mList, "IsEncode: 0");
		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_HTTPHEADER, pHTTPData->mList);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl http header error=%d\n", ret);
			break;
		}

		char opcode[128] = "";
		sprintf(opcode, "packetType: %d", pHTTPData->mType);
		pHTTPData->mList = curl_slist_append(pHTTPData->mList, opcode);
		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_HTTPHEADER, pHTTPData->mList);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl http header error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_URL, buffer);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl url error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_HEADERFUNCTION, OnHTTPHeaderWriter);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl header function error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_WRITEFUNCTION, OnHTTPDataWriter);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl write function error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_WRITEHEADER, &pHTTPData->mHeader);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl write header buffer error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_WRITEDATA, &pHTTPData->mBuffer);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl write data buffer error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_POST, 1);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl post error=%d\n", ret);
			break;
		}

		pHTTPData->mContent = pMemNode;
		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_POSTFIELDS, pHTTPData->mContent->get_buff()+pHTTPData->mContent->get_read_pos());
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl post data error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_POSTFIELDSIZE, pHTTPData->mContent->get_write_pos()-pHTTPData->mContent->get_read_pos());
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl post data error=%d\n", ret);
			break;
		}

		int connectTime = 30;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "ServerConnectTime", connectTime);
		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_CONNECTTIMEOUT, connectTime);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl conenct time error=%d\n", ret);
			break;
		}

		int transferTime = 300;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "ServerTransferTime", transferTime);
		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_TIMEOUT, transferTime);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl transfer time error=%d\n", ret);
			break;
		}

		ret = curl_easy_setopt(pHTTPData->mHandler, CURLOPT_FORBID_REUSE, 1);
		if (ret != CURLE_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, set easy curl reuse error=%d\n", ret);
			break;
		}

		CURLMcode ret2 = curl_multi_add_handle(m_pCURLM, pHTTPData->mHandler);
		if (ret2 != CURLM_OK)
		{
			LOGGERSYSTEM->LogInfo("NET: Starting Send Failed, add multi handler error=%d\n", ret2);
			break;
		}

		// 增加发送时间戳
		pHTTPData->mSendTime = TimeSystem::GetCurrentMicroSecond();
		m_HTTPList.push_back(pHTTPData);
		return true;
	} 
	while (false);

	return true;
}

bool NetSystem::OnHTTPExceptionEventHandler()
{
	LOGGERSYSTEM->LogInfo("NetSystem::OnHTTPExceptionEventHandler---HttpError!!");

	// HTTP网络连接异常处理
	// 各个项目需要在该处增加对应的处理
	SERVERINFODATAINFO->HandleHttpConnectFail();
	return true;
}

int NetSystem::OnHTTPDataWriter(char *data, size_t size, size_t nmemb, std::string *pData)
{
	if (pData == NULL)
		return 0;

	pData->append(data, size*nmemb);
	return size*nmemb;
}

int NetSystem::OnHTTPHeaderWriter(char *data, size_t size, size_t nmemb, std::string *pData)
{
	if (pData == NULL)
		return 0;

	pData->append(data, size*nmemb);
	return size*nmemb;
}

	/*
		连接失败错误提示
	*/
void NetSystem::ConnnetFailHint(){
	SERVERINFODATAINFO->HandleSocketConnectFail();
}

	/*
		socket断开提示
	*/
void NetSystem::SocketClosedHint(){
	SERVERINFODATAINFO->NotifySocketClosed();
}

