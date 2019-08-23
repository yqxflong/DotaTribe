#include "../include/LocalAthleticsDataManager.h"
#include "../include/CPublicVarReader.h"
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

using  namespace  cobra_win;
using namespace std;

const std::string  templateKey = "%d_%d";
 
void  LocalAthleticsDataManager::PushAthleticsDPacket(DPacket & packet,int mapID,int stageID)
{  
		char localStrKey[16]={0};
		sprintf(localStrKey,templateKey.c_str(),mapID,stageID);
		m_lastLocalKey = localStrKey;
		std::map<std::string,PCacheBuffer>::iterator local_iter = m_vSaveDataPacketVector.find(m_lastLocalKey);
		if(local_iter != m_vSaveDataPacketVector.end())
		{
			delete (local_iter->second);
			m_vSaveDataPacketVector.erase(local_iter);
		}
	 
		PCacheBuffer cacheBuffer = new CacheBuffer(packet,mapID,stageID);
		m_vSaveDataPacketVector.insert(std::map<std::string,PCacheBuffer>::value_type(m_lastLocalKey,cacheBuffer));
		 
		SaveToFile();  
}

PCacheBuffer LocalAthleticsDataManager::GetAthleticsDPacket(int mapID,int stageID)
{
	char localStrKey[16]={0};
	sprintf(localStrKey,templateKey.c_str(),mapID,stageID);
	m_lastLocalKey = localStrKey;
	std::map<std::string,PCacheBuffer>::iterator local_iter = m_vSaveDataPacketVector.find(m_lastLocalKey);
	if(local_iter != m_vSaveDataPacketVector.end())
	{
		return local_iter->second;
	}
	CCLOG("Can't Not Find AthleticsDPacket For:  %s",m_lastLocalKey.c_str());
	return NULL;
}



/*
	设置需要存盘
*/
void  LocalAthleticsDataManager::SetNeedSaveToDisk(bool saveEnable)
{ 
	m_bIsNeedSaveToDisk = saveEnable;
}

/*
	设置是否追加存盘
*/
void LocalAthleticsDataManager::SetNeedAppendSave(bool appendSaveEnable)
{  
	m_bIsNeedAppendSave = appendSaveEnable;
}

std::string LocalAthleticsDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "localathleticsdata";

	return "localathleticsdata";
}
  
unsigned int LocalAthleticsDataManager::GetSize()
{
	return sizeof(LocalAthleticsDataManager);
}
 
bool LocalAthleticsDataManager::Init()
{ 
	do 
	{
		if (!LoadFromFile())
			break; 
		return true;
	} 
	while(false); 
	return false;
}

void LocalAthleticsDataManager::Tick()
{
	if (!m_bIsNeedSaveToDisk)
		return ; 
	SaveToFile();
	m_bIsNeedSaveToDisk = false;
}

void LocalAthleticsDataManager::Destroy()
{
	if(getEnableLocalAthletiData())
	{
		SaveToFile();
	}
	std::map<std::string,PCacheBuffer>::iterator cache_iter = m_vSaveDataPacketVector.begin();
	while(cache_iter!=m_vSaveDataPacketVector.end())
	{ 
		delete cache_iter->second;
		++cache_iter;
	}
	m_vSaveDataPacketVector.clear();
}

bool LocalAthleticsDataManager::Reload()
{
	return true;
}

bool LocalAthleticsDataManager::LoadFromFile()
{
	char* pBuffer     = NULL;
	unsigned int  iFileLength = 0; 
	try
	{ 
		std::string relativePath = EngineSystem::get_instance2()->GetRecordDataPath()+GetName();
		std::string filePath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(relativePath.c_str()); 
		EngineSystem::get_instance2()->LoadAppFile((char *)filePath.c_str(),pBuffer,iFileLength);
		/*
		pBuffer = LoadDBFile(filePath, iFileLength);
		*/ 
		if(!pBuffer)
		{
			CCLOG("Load File LocalAthleticsDataFile Faild ! File Path : %s",filePath.c_str());
			return false;
		}
		 
		//读取文件信息
		DPacket packet(pBuffer, iFileLength+1);
		LoadFromFileA(pBuffer+packet.get_read_pos(), iFileLength-packet.get_read_pos());
  
	}
	catch (...)
	{
		;
	}

	if (pBuffer)
	{
		delete []pBuffer;
	}
	return true;
}

bool LocalAthleticsDataManager::LoadFromDB()
{
	do 
	{
		return true;
	}
	while (false);

	return false;
}

bool LocalAthleticsDataManager::Varify(IData* pData)
{
	return true;
}

bool LocalAthleticsDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool LocalAthleticsDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	return true;
}

char* LocalAthleticsDataManager::LoadDBFile(std::string fileName, long& length)
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
	 
	return pBuffer;
}


void  LocalAthleticsDataManager::SaveDataToPacket(EPacket & packet)
{
	if(!m_vSaveDataPacketVector.empty())
	{ 
		size_t packetCount = m_vSaveDataPacketVector.size();
		packet.append(packetCount); 
		std::map<std::string,PCacheBuffer>::iterator cache_iter = m_vSaveDataPacketVector.begin();
		while(cache_iter != m_vSaveDataPacketVector.end())
		{
			size_t packetSize = cache_iter->second->m_nSize;
			int  packetMapID =  cache_iter->second->m_nMapID;
			int  packetStageID = cache_iter->second->m_nStageID;
			packet.append(packetMapID);
			packet.append(packetStageID);
			packet.append(packetSize);
			packet.append(cache_iter->second->m_pBuffer,packetSize);
			++cache_iter;
		} 
	}
}


void LocalAthleticsDataManager::SaveToFile()
{
	if(m_vSaveDataPacketVector.empty())
	return ;
	EPacket packet;
    SaveDataToPacket(packet); 
	//// 增加md5存档校验码
	//std::string md5Key = MD5Crypto::md5((unsigned char*)packet.get_packet_buff(), packet.size());
	//packet.append((char*)md5Key.c_str(), md5Key.length()); 
	// 更新备份文件
	  
	try
	{
		//// 先进行解密
		//DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetLocalDataEncryptionKey().c_str(), packet.get_packet_buff(), packet.size());
		std::string reletivePath = EngineSystem::get_instance2()->GetRecordDataPath()+GetName();
		std::string filePath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(reletivePath.c_str());
	
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


/*
	同步到初始状态(一般文件校验失败，则直接设置为初始状态)
*/
void LocalAthleticsDataManager::SynToInitialization()
{ 
}

/*
	加载存档文件
*/
bool LocalAthleticsDataManager::LoadFromFileA(char* pBuffer, unsigned int iBufferLen)
{
	try
	{
		//// 创建解包器
		DPacket packet(pBuffer, iBufferLen+1); 
		size_t totalCacheDataCount = 0;
		packet.read(totalCacheDataCount);
		int    mapID = 0;
		int	   stageID = 0;
		size_t packetSize = 0;
		for(size_t cacheIndex = 0; cacheIndex < totalCacheDataCount; cacheIndex++)
		{ 
			packet.read(mapID);
			packet.read(stageID);
			packet.read(packetSize);
			PCacheBuffer  pCacheBuffer = new CacheBuffer(packet,packetSize,mapID,stageID);
			char localStrKey[16]={0};
			sprintf(localStrKey,templateKey.c_str(),mapID,stageID);
			m_lastLocalKey = localStrKey;
			m_vSaveDataPacketVector.insert(std::map<std::string,PCacheBuffer>::value_type(m_lastLocalKey,pCacheBuffer));
		}  
	}
	catch (...)
	{
		return false;
	} 
	return true;
}
 
 