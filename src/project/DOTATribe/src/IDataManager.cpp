#include <cocos2d.h>
#include "../include/IDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/DBSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


std::string  _rich_text_parser_(std::string text)
{
	static  std::map<std::string, std::string>  sEscapeSequenceList;
	sEscapeSequenceList.clear();
	if (sEscapeSequenceList.size() == 0)
	{
		size_t npos = text.find("<a");
		if (npos == std::string::npos)
		{//无富文本字符串，则将"<br>"替换成 "\n"
			sEscapeSequenceList.insert(std::map<std::string, std::string>::value_type("<br>", "\n"));
		}
		else
		{//有富文本字符串，则将"<br>"替换成 "\r"
			sEscapeSequenceList.insert(std::map<std::string, std::string>::value_type("<br>", "\r"));
		}
	}

	std::string str = text;
	std::map<std::string, std::string>::iterator iter   = sEscapeSequenceList.begin();
	std::map<std::string, std::string>::iterator iter_e = sEscapeSequenceList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		std::string key   = iter->first;
		std::string value = iter->second;

		do 
		{
			std::string::size_type pos = str.find(key, 0);
			if (pos == str.npos)
				break;

			std::string::iterator tempIter = str.begin();
			tempIter = tempIter+pos;

			str.replace(tempIter, tempIter+key.size(), value);
		} 
		while (true);
	}

	return str;
}

IData::IData()
{

}

IData::~IData()
{

}

IDataManager::IDataManager(bool bLoadFromDB, bool bEncryption)
{
	m_bLoadFromDB = bLoadFromDB;
	m_bEncryption = bEncryption;
}

IDataManager::~IDataManager()
{

}

bool IDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
			if (!LoadFromDB())
				break;
		else
			if (!LoadFromFile())
				break;

		return true;
	} 
	while(false);

	return false;
}

void IDataManager::Tick()
{

}

void IDataManager::Destroy()
{

}

bool IDataManager::Reload()
{
	// 先销毁
	Destroy();

	// 在重新加载
	return Init();
}

bool IDataManager::LoadFromFile()
{
	char*        pBuffer = NULL;
	unsigned int iLength = 0;
	// 加载文件
	if (!EngineSystem::LoadAppFile((char*)GetName().c_str(), pBuffer, iLength))
		return false;

	// 先进行解密
	if (m_bEncryption)
		DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetEncryptionKey().c_str(), pBuffer, iLength);

	// 构建DPacket解包器
	DPacket packet(pBuffer, iLength+1);

	// 跳过第一行
	char   buffer[10240] = "";
	size_t pos = 0;
	do 
	{
		if (pos == sizeof(buffer))
			return false;

		if (packet.get_read_pos() >= packet.size())
			return false;

		packet.read(buffer+pos, 1);
		if (pos>0 && *(buffer+pos)=='\r')
			break;

		pos++;
	}
	while(true);

	// 逐行读取解析
	do 
	{
		char   buffer[10240] = "";
		size_t num           = 0;
		bool   reset         = false;

		{
			size_t pos = 0;
			do 
			{
				if (pos == sizeof(buffer))
				{
					reset = true;
					break;
				}

				if (packet.get_read_pos() >= packet.size())
					break;

				packet.read(buffer+pos, 1);
				if (pos>0 && *(buffer+pos)=='\n')
				{
					if (*(buffer+pos-1) == '\r')
					{
						*(buffer+pos-1) = '\0';
					}

					*(buffer+pos) = '\0';
					num = pos;
					break;
				}

				pos++;
			}
			while(true);
		}

		if (reset || num<=2)
			break;

		if (!LoadData(buffer, num-1))
		{
			delete pBuffer;
			return false;
		}

	}
	while (true);

	delete pBuffer;
	return true;
}

bool IDataManager::LoadFromDB()
{
	char*        pBuffer = NULL;
	unsigned int iLength = 0;
	// 加载数据库表
	if (!DBSystem::LoadDBTable((char*)GetName().c_str(), pBuffer, iLength))
		return false;

	// 先进行解密
	if (m_bEncryption)
		DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetEncryptionKey().c_str(), pBuffer, iLength);

	// 构建DPacket解包器
	DPacket packet(pBuffer, iLength+1);

	// 跳过第一行
	char   buffer[10240] = "";
	size_t pos = 0;
	do 
	{
		if (pos == sizeof(buffer))
			return false;

		if (packet.get_read_pos() >= packet.size())
			return false;

		packet.read(buffer+pos, 1);
		if (pos>0 && *(buffer+pos)=='\r')
			break;

		pos++;
	}
	while(true);

	// 逐行读取解析
	do 
	{
		char   buffer[10240] = "";
		size_t num           = 0;
		bool   reset         = false;

		{
			size_t pos = 0;
			do 
			{
				if (pos == sizeof(buffer))
				{
					reset = true;
					break;
				}

				if (packet.get_read_pos() >= packet.size())
					break;

				packet.read(buffer+pos, 1);
				if (pos>0 && *(buffer+pos)=='\n')
				{
					if (*(buffer+pos-1) == '\r')
					{
						*(buffer+pos-1) = '\0';
					}

					*(buffer+pos) = '\0';
					num = pos;
					break;
				}

				pos++;
			}
			while(true);
		}

		if (reset || num<=2)
			break;

		if (!LoadData(buffer, num-1))
			return false;

		;
	}
	while (true);

	delete []pBuffer;
	return true;
}
