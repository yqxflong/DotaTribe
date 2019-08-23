//Name：LocalPlayerDataManager
//Function：管理玩家本地数据，存于硬盘，MD5校验
//Maintain：尹强
#include <cocos2d.h>
#include "../include/LocalPlayerDataManager.h"
#include "../include/DOTATribeApp.h"
#include "../include/EngineSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DBSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
#include <map>
#include "../include/PayGoodsControlDataHandler.h"
using  namespace  cobra_win;
using namespace std;


//======================================SDKLoginParam==========================//
void SDKLoginParam::Save(cobra_win::EPacket & packet)
{
	int len = 0;
	packet<<m_iSdkType;
	len = m_Param0.length();
	packet<<len;
	packet.append((char *)m_Param0.c_str(), len);
	len = m_Param1.length();
	packet<<len;
	packet.append((char *)m_Param1.c_str(), len);
	len = m_Param2.length();
	packet<<len;
	packet.append((char *)m_Param2.c_str(), len);
	len = m_Param3.length();
	packet<<len;
	packet.append((char *)m_Param3.c_str(), len);
	len = m_Param4.length();
	packet<<len;
	packet.append((char *)m_Param4.c_str(), len);
	len = m_Param5.length();
	packet<<len;
	packet.append((char *)m_Param5.c_str(), len);
	len = m_Param6.length();
	packet<<len;
	packet.append((char *)m_Param6.c_str(), len);
	len = m_Param7.length();
	packet<<len;
	packet.append((char *)m_Param7.c_str(), len);
	len = m_Param8.length();
	packet<<len;
	packet.append((char *)m_Param8.c_str(), len);
	len = m_Param9.length();
	packet<<len;
	packet.append((char *)m_Param9.c_str(), len);
}

void SDKLoginParam::Load(cobra_win::DPacket & packet)
{
	char tmp[1024]="";
	int len=0;

	packet>>m_iSdkType;

	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param0 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param1 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param2 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param3 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param4 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param5 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param6 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param7 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param8 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param9 = tmp;
}

int SDKLoginParam::PacketLength()
{
	return sizeof(m_iSdkType) + sizeof(unsigned short) + m_Param0.length() + sizeof(unsigned short) + m_Param1.length() + sizeof(unsigned short) + m_Param2.length()
		 + sizeof(unsigned short) + m_Param3.length() + sizeof(unsigned short) + m_Param4.length() + sizeof(unsigned short) + m_Param5.length()
		  + sizeof(unsigned short) + m_Param6.length() + sizeof(unsigned short) + m_Param7.length() + sizeof(unsigned short) + m_Param8.length()
		   + sizeof(unsigned short) + m_Param9.length();
}

void SDKLoginParam::SendParam(MemNode* pNode)
{
	unsigned short size = 0;
	char * buff = NULL;
	pNode->push(m_iSdkType);

	size = m_Param0.length();
	buff = const_cast<char*>(m_Param0.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param1.length();
	buff = const_cast<char*>(m_Param1.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param2.length();
	buff = const_cast<char*>(m_Param2.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param3.length();
	buff = const_cast<char*>(m_Param3.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param4.length();
	buff = const_cast<char*>(m_Param4.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param4.length();
	buff = const_cast<char*>(m_Param5.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param6.length();
	buff = const_cast<char*>(m_Param6.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param7.length();
	buff = const_cast<char*>(m_Param7.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param8.length();
	buff = const_cast<char*>(m_Param8.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param9.length();
	buff = const_cast<char*>(m_Param9.c_str());
	pNode->push(size);
	pNode->push(buff, size);

}

//======================================GameLoginParam==========================//
void GameLoginParam::Save(cobra_win::EPacket & packet)
{
	int len = 0;
	len = m_Param0.length();
	packet<<len;
	packet.append((char *)m_Param0.c_str(), len);
	len = m_Param1.length();
	packet<<len;
	packet.append((char *)m_Param1.c_str(), len);
}

void GameLoginParam::Load(cobra_win::DPacket & packet)
{
	char tmp[128]="";
	int len=0;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param0 = tmp;
	packet>>len;
	packet.read(tmp, len);
	tmp[len] = '\0';
	m_Param1 = tmp;
}

int GameLoginParam::PacketLength()
{
	return sizeof(unsigned short) + m_Param0.length() + sizeof(unsigned short) + m_Param1.length();
}

void GameLoginParam::SendParam(MemNode* pNode)
{
	unsigned short size = 0;
	char * buff = NULL;
	size = m_Param0.length();
	buff = const_cast<char*>(m_Param0.c_str());
	pNode->push(size);
	pNode->push(buff, size);
	size = m_Param1.length();
	buff = const_cast<char*>(m_Param1.c_str());
	pNode->push(size);
	pNode->push(buff, size);
}

//======================================LocalPlayerDataManager==========================//
template<> LocalPlayerDataManager* cobra_win::Singleton2<LocalPlayerDataManager>::m_pMySelf = NULL;

void LocalPlayerDataManager::SetSdkLoginParam(SDKLoginParam & loginParam)
{
	this->m_SdkLoginParam.m_iSdkType = loginParam.m_iSdkType;
	this->m_SdkLoginParam.m_Param0 = loginParam.m_Param0;
	this->m_SdkLoginParam.m_Param1 = loginParam.m_Param1;
	this->m_SdkLoginParam.m_Param2 = loginParam.m_Param2;
	this->m_SdkLoginParam.m_Param3 = loginParam.m_Param3;
	this->m_SdkLoginParam.m_Param4 = loginParam.m_Param4;
	this->m_SdkLoginParam.m_Param5 = loginParam.m_Param5;
	this->m_SdkLoginParam.m_Param6 = loginParam.m_Param6;
	this->m_SdkLoginParam.m_Param7 = loginParam.m_Param7;
	this->m_SdkLoginParam.m_Param8 = loginParam.m_Param8;
	this->m_SdkLoginParam.m_Param9 = loginParam.m_Param9;
}

SDKLoginParam LocalPlayerDataManager::GetSdkLoginParam()
{
	return this->m_SdkLoginParam;
}

void LocalPlayerDataManager::SetGameLoginParam(GameLoginParam & loginParam)
{
	this->m_GameLoginParam.m_Param0 = loginParam.m_Param0;
	this->m_GameLoginParam.m_Param1 = loginParam.m_Param1;
}

GameLoginParam LocalPlayerDataManager::GetGameLoginParam()
{
	return this->m_GameLoginParam;
}

void LocalPlayerDataManager::NeedSaveToDisk()
{
	m_bNeedSaveToDisk = true;
}

std::string LocalPlayerDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "localdata_2";

	return "localdata_2";
}

std::string LocalPlayerDataManager::GetTempName()
{
	if (!m_bLoadFromDB)
		return "localdatatemp_2";

	return "localdatatemp_2";
}

unsigned int LocalPlayerDataManager::GetSize()
{
	return sizeof(LocalPlayerDataManager);
}

void LocalPlayerDataManager::OnSystemEnterBackEventHandler()
{

}

void LocalPlayerDataManager::OnSystemEnterFrontEventHandler()
{

}

void LocalPlayerDataManager::OnSystemPauseEventHandler()
{

}

void LocalPlayerDataManager::OnSystemResumeEventHandler()
{

}

bool LocalPlayerDataManager::Init()
{

	do 
	{
		if (!LoadFromFile())
			break;

		OnSystemResumeEventHandler();		
		return true;
	} 
	while(false);

	return false;
}

void LocalPlayerDataManager::Tick()
{
	if (!m_bNeedSaveToDisk)
		return ;
	
	SaveToFile();
	m_bNeedSaveToDisk = false;
}

void LocalPlayerDataManager::Destroy()
{
	SaveToFile();
}

bool LocalPlayerDataManager::Reload()
{
	return true;
}

bool LocalPlayerDataManager::LoadFromFile()
{
	char* pBuffer     = NULL;
	long  iFileLength = 0;

	try
	{
		do 
		{
			std::string filePath = EngineSystem::GetDocumentDir()+GetName();
			pBuffer = LoadDBFile(filePath, iFileLength);
			if (pBuffer != NULL)
				break;

			filePath = EngineSystem::GetDocumentDir()+GetTempName();
			pBuffer = LoadDBFile(filePath, iFileLength);
			if (pBuffer != NULL)
				break;

			return true;
		} 
		while (false);
		
		//读取文件信息
		DPacket packet(pBuffer, iFileLength+1);
		LoadFromFile(pBuffer+packet.get_read_pos(), iFileLength-packet.get_read_pos());
	}
	catch (...)
	{
		;
	}

	if (pBuffer != NULL)
	{
		delete []pBuffer;
	}
	return true;
}

bool LocalPlayerDataManager::LoadFromDB()
{
	do 
	{
		return true;
	}
	while (false);

	return false;
}

bool LocalPlayerDataManager::Varify(IData* pData)
{
	return true;
}

bool LocalPlayerDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool LocalPlayerDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	return true;
}

char* LocalPlayerDataManager::LoadDBFile(std::string fileName, long& length)
{
	FileLoader loader;
	if (!loader.load((char*)fileName.c_str(), FileLoader::_TYPED_READ_ONLY_))
	{
		loader.unload();
		return NULL;
	}

	length = loader.length();
	if (length <= (sizeof(char)*32+sizeof(int)))
	{
		loader.unload();
		return NULL;
	}
	
	// 读取文件信息
	char* pBuffer = new char[length+1];
	memset(pBuffer, 0, length+1);
	loader.read(pBuffer, length);
	loader.unload();

	// 先进行解密
	DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetLocalDataEncryptionKey().c_str(), pBuffer, length);

	// 判断文件是否完整
	std::string md5Key = MD5Crypto::md5((unsigned char*)pBuffer, length-32);
	if (md5Key.compare(pBuffer+length-32) != 0)
	{
		delete[] pBuffer;
		return NULL;
	}

	return pBuffer;
}

void LocalPlayerDataManager::SaveToFile()
{
	EPacket packet;
	
	// 保存帐号信息
	m_SdkLoginParam.Save(packet);
	m_GameLoginParam.Save(packet);
	_saveIAP_Param(packet);
	_saveServerID_Param(packet);

	// 增加md5存档校验码
	std::string md5Key = MD5Crypto::md5((unsigned char*)packet.get_packet_buff(), packet.size());
	packet.append((char*)md5Key.c_str(), md5Key.length());

	// 更新备份文件
	try
	{
		do 
		{
			std::string filePath = EngineSystem::GetDocumentDir();
			filePath += GetName();
			FileLoader loader;
			if (!loader.load((char*)filePath.c_str(), FileLoader::_TYPED_READ_ONLY_))
			{
				loader.unload();
				break;
			}

			int fileLength = loader.length();
			char* pBuffer = new char[fileLength+1];
			memset(pBuffer, 0, fileLength+1);
			loader.read(pBuffer, fileLength);
			loader.unload();

			filePath = EngineSystem::GetDocumentDir();
			filePath += GetTempName();
			if (!loader.load((char*)filePath.c_str(), FileLoader::_TYPED_CLEAR_WRITE_))
			{
				loader.unload();
				delete []pBuffer;
				break;
			}

			loader.write(pBuffer, fileLength);
			loader.unload();
			delete []pBuffer;
		}
		while (false);
	}
	catch (...)
	{
		;
	}

	try
	{
		// 先进行解密
		DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetLocalDataEncryptionKey().c_str(), packet.get_packet_buff(), packet.size());

		std::string filePath = EngineSystem::GetDocumentDir();
		filePath += GetName();

		FileLoader loader;
		if (!loader.load((char*)filePath.c_str(), FileLoader::_TYPED_CLEAR_WRITE_))
			return ;

		loader.write(packet.get_packet_buff(), packet.size());
		loader.unload();
	}
	catch (...)
	{
		;
	}
}

void LocalPlayerDataManager::SynToInitialization()
{

}

bool LocalPlayerDataManager::LoadFromFile(char* pBuffer, unsigned int iBufferLen)
{
	try
	{
		// 创建解包器
		DPacket packet(pBuffer, iBufferLen+1);

		// 加载帐号信息
		m_SdkLoginParam.Load(packet);
		m_GameLoginParam.Load(packet);
		_loadIAP_Param(packet);
		_loadServerID_Param(packet);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void LocalPlayerDataManager::SetLastIAPServerId(std::string serverId)
{
	if (m_LastIAPServerId.compare(serverId) == 0)
		return;

	m_LastIAPServerId = serverId;
	NeedSaveToDisk();
}

std::string LocalPlayerDataManager::GetLastIAPServerId()
{
	return m_LastIAPServerId;
}

void LocalPlayerDataManager::SetLastIAPPlayerId(std::string playerId)
{
	if (m_LastIAPPlayerId.compare(playerId) == 0)
		return;

	m_LastIAPPlayerId = playerId;
	NeedSaveToDisk();
}

std::string LocalPlayerDataManager::GetLastIAPPlayerId()
{
	return m_LastIAPPlayerId;
}

void LocalPlayerDataManager::InsertPayment(std::string serverId, std::string playerId, std::string productId, int goodsId, std::string transactionId, std::string transactionReceipt)
{
	_LOCAL_PLAYER_UNVERIFY_IAP_ payment;
	payment.mPlatform = _LOCAL_PLAYER_UNVERIFY_IAP_::_IAP_PLATFORM_IOS_;
	payment.mServerId = serverId;
	payment.mPlayerId = playerId;
	payment.mProductId= productId;
	payment.mGoodsId  = goodsId;
	payment.mTransactionId = transactionId;
	payment.mTransactionReceipt = transactionReceipt;
	m_UnVerifyIAPList.insert(std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::value_type(transactionId, payment));

	// 防止数据丢失，直接保存文件
	SaveToFile();
}

void LocalPlayerDataManager::InsertPayment(std::string serverId, std::string playerId, std::string productId, std::string transactionId)
{
	_LOCAL_PLAYER_UNVERIFY_IAP_ payment;
	payment.mPlatform = _LOCAL_PLAYER_UNVERIFY_IAP_::_IAP_PLATFORM_ANDROID_;
	payment.mServerId = serverId;
	payment.mPlayerId = playerId;
	payment.mProductId= productId;
	payment.mTransactionId = transactionId;
	m_UnVerifyIAPList.insert(std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::value_type(transactionId, payment));

	// 防止数据丢失，直接保存文件
	SaveToFile();
}

void LocalPlayerDataManager::DeletePayment(std::string transactionId)
{
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter = m_UnVerifyIAPList.find(transactionId);
	if (iter == m_UnVerifyIAPList.end())
		return ;

	// 删除订单
	m_UnVerifyIAPList.erase(iter);
	// 防止数据丢失，直接保存文件
	SaveToFile();
}

void  LocalPlayerDataManager::ServerSuccessCheckOrder(std::string transactionId)
{
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter = m_UnVerifyIAPList.find(transactionId);
	if (iter == m_UnVerifyIAPList.end())
		return ;
	_LOCAL_PLAYER_UNVERIFY_IAP_ temp = iter->second;

	PayGoodsData* data = PAYGOODSCONTROLDATAHANDLER->ByRegisterIdFindGoodsData(temp.mProductId);
	if(data == NULL)
		return;
	cocos2d::CCDirector::sharedDirector()->getPayment()->onServerSureOrder(temp.mProductId,data->goodsName_,data->goodsPrice_,temp.mTransactionId);
}

std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>& LocalPlayerDataManager::GetUnVerifyIAPList()
{
	return m_UnVerifyIAPList;
}


//插入需要保存的服务器ID，和插入的时间(s)
void LocalPlayerDataManager::InsertServerID(int sid,long long time){
	_LOCAL_SERVER_ID_ serverid;
	serverid.id_=sid;
	serverid.lasttime_=time;
	std::map<int,_LOCAL_SERVER_ID_>::iterator it=m_listLocalServerID.find(sid);
	if (it==m_listLocalServerID.end())
	{
		m_listLocalServerID.insert(std::map<int,_LOCAL_SERVER_ID_>::value_type(sid,serverid));
	}else{
		it->second=serverid;
	}

	SaveToFile();
}

//获取最新的4个serverid list
std::list<int> LocalPlayerDataManager::GetLatestServerIDList(){
	map<int,_LOCAL_SERVER_ID_>::iterator iter=m_listLocalServerID.begin();

	map<long long,int> tmp_map;
	tmp_map.clear();
	//tmp_map 将根据time 自动排序
	for (;iter!=m_listLocalServerID.end();iter++)
	{
		tmp_map.insert(map<long long,int>::value_type(iter->second.lasttime_,iter->first));
	}

	list<int> ret;
	ret.clear();
	std::map<long long,int>::reverse_iterator tmpIter=tmp_map.rbegin();
	int i=0;
	//取出前4个最大的时间的服务器ID
	for (;tmpIter!=tmp_map.rend();tmpIter++)
	{
		if (i>=4)
			break;
		ret.push_back(tmpIter->second);
		i++;
	}

	return ret;
}

void LocalPlayerDataManager::_saveServerID_Param(cobra_win::EPacket & packet){
	int sidSize=m_listLocalServerID.size();
	packet<<sidSize;
	std::map<int, _LOCAL_SERVER_ID_>::iterator iter   = m_listLocalServerID.begin();
	for (;iter!=m_listLocalServerID.end();iter++)
	{
		_LOCAL_SERVER_ID_ temp = iter->second;
		packet<<temp.id_;
		packet<<temp.lasttime_;
	}
}

void LocalPlayerDataManager::_saveIAP_Param(cobra_win::EPacket & packet){
	// 保存最后一次支付的服务器Id
	int serverIdLen = m_LastIAPServerId.size();
	packet<<serverIdLen;
	if (serverIdLen > 0)
	{
		packet.append((char*)m_LastIAPServerId.c_str(), serverIdLen);
	}

	// 保存最后一次支付的玩家Id
	int playerIdLen = m_LastIAPPlayerId.size();
	packet<<playerIdLen;
	if (playerIdLen > 0)
	{
		packet.append((char*)m_LastIAPPlayerId.c_str(), playerIdLen);
	}

	// 保存支付订单列表
	int paymentListSize = m_UnVerifyIAPList.size();
	packet<<paymentListSize;
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter   = m_UnVerifyIAPList.begin();
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter_e = m_UnVerifyIAPList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		_LOCAL_PLAYER_UNVERIFY_IAP_ temp = iter->second;

		// 保存支付平台类型
		packet<<temp.mPlatform;
		// 保存服务器Id长度
		int serverIdLen = temp.mServerId.size();
		packet<<serverIdLen;
		if (serverIdLen > 0)
		{// 保存服务器Id
			packet.append((char*)temp.mServerId.c_str(), serverIdLen);
		}
		// 保存玩家Id长度
		int playerIdLen = temp.mPlayerId.size();
		packet<<playerIdLen;
		if (playerIdLen > 0)
		{// 保存玩家Id长度
			packet.append((char*)temp.mPlayerId.c_str(), playerIdLen);
		}
		// 保存商品GoodsId
		packet<<temp.mGoodsId;
		// 保存商品Id长度
		int productIdLen = temp.mProductId.size();
		packet<<productIdLen;
		if (productIdLen > 0)
		{// 保存商品Id
			packet.append((char*)temp.mProductId.c_str(), productIdLen);
		}
		// 保存商品订单长度
		int transIdLen = temp.mTransactionId.size();
		packet<<transIdLen;
		if (transIdLen > 0)
		{// 保存商品订单
			packet.append((char*)temp.mTransactionId.c_str(), transIdLen);
		}
		// 保存商品订单回执信息长度
		int transReceiptLen = temp.mTransactionReceipt.size();
		packet<<transReceiptLen;
		if (transReceiptLen > 0)
		{// 保存商品订单回执信息
			packet.append((char*)temp.mTransactionReceipt.c_str(), transReceiptLen);
		}
		// 保存ChargePoint
		packet<<temp.mChargePoint;
		// 保存支付校验失败的次数
		packet<<temp.mVerifyFailedCount;
	}
}

void LocalPlayerDataManager::_loadIAP_Param(cobra_win::DPacket & packet){
	// 加载最后一次支付的服务器Id
	int serverIdLen = 0;
	packet>>serverIdLen;
	if (serverIdLen > 0)
	{
		char* pBuffer = new char[serverIdLen+1];
		memset(pBuffer, 0, serverIdLen+1);

		packet.read(pBuffer, serverIdLen);

		m_LastIAPServerId = pBuffer;
		delete []pBuffer;
	}

	// 加载最后一次支付的玩家Id
	int playerIdLen = 0;
	packet>>playerIdLen;
	if (playerIdLen > 0)
	{
		char* pBuffer = new char[playerIdLen+1];
		memset(pBuffer, 0, playerIdLen+1);

		packet.read(pBuffer, playerIdLen);

		m_LastIAPPlayerId = pBuffer;
		delete []pBuffer;
	}

	// 加载本地未校验订单列表
	int paymentListSize = 0;
	packet>>paymentListSize;
	for (int i=0; i<paymentListSize; i++)
	{
		_LOCAL_PLAYER_UNVERIFY_IAP_ temp;

		// 加载支付平台类型
		packet>>temp.mPlatform;
		// 加载服务器Id长度
		int serverIdLen = 0;
		packet>>serverIdLen;
		if (serverIdLen > 0)
		{// 加载服务器Id
			char* pBuffer = new char[serverIdLen+1];
			memset(pBuffer, 0, serverIdLen+1);

			packet.read(pBuffer, serverIdLen);

			temp.mServerId = pBuffer;
			delete []pBuffer;
		}
		// 加载玩家Id长度
		int playerIdLen = 0;
		packet>>playerIdLen;
		if (playerIdLen > 0)
		{// 加载玩家Id长度
			char* pBuffer = new char[playerIdLen+1];
			memset(pBuffer, 0, playerIdLen+1);

			packet.read(pBuffer, playerIdLen);

			temp.mPlayerId = pBuffer;
			delete []pBuffer;
		}
		// 加载商品GoodsId
		packet>>temp.mGoodsId;
		// 加载商品Id长度
		int productIdLen = 0;
		packet>>productIdLen;
		if (productIdLen > 0)
		{// 加载商品Id
			char* pBuffer = new char[productIdLen+1];
			memset(pBuffer, 0, productIdLen+1);

			packet.read(pBuffer, productIdLen);

			temp.mProductId = pBuffer;
			delete []pBuffer;
		}
		// 加载商品订单长度
		int transIdLen = 0;
		packet>>transIdLen;
		if (transIdLen > 0)
		{// 加载商品订单
			char* pBuffer = new char[transIdLen+1];
			memset(pBuffer, 0, transIdLen+1);

			packet.read(pBuffer, transIdLen);

			temp.mTransactionId = pBuffer;
			delete []pBuffer;
		}
		// 加载商品订单回执信息长度
		int transReceiptLen = 0;
		packet>>transReceiptLen;
		if (transReceiptLen > 0)
		{// 加载商品订单回执信息
			char* pBuffer = new char[transReceiptLen+1];
			memset(pBuffer, 0, transReceiptLen+1);

			packet.read(pBuffer, transReceiptLen);

			temp.mTransactionReceipt = pBuffer;
			delete []pBuffer;
		}
		// 加载ChargePoint
		packet>>temp.mChargePoint;
		// 加载支付校验失败的次数
		packet>>temp.mVerifyFailedCount;

		// 插入订单
		m_UnVerifyIAPList.insert(std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>::value_type(temp.mTransactionId, temp));
	}
}

void LocalPlayerDataManager::_loadServerID_Param(cobra_win::DPacket & packet){
	// 加载本地未校验订单列表
	int sidSize = 0;
	packet>>sidSize;
	for (int i=0; i<sidSize; i++)
	{
		_LOCAL_SERVER_ID_ temp;
		packet>>temp.id_;
		packet>>temp.lasttime_;

		m_listLocalServerID.insert(std::map<int,_LOCAL_SERVER_ID_>::value_type(temp.id_,temp));
	}
}