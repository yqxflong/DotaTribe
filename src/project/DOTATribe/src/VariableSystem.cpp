//Name: VariableSystem
//Func: 读写Xml文件
//Author: CY

#include <cocos2d.h>
#include "../include/VariableSystem.h"
#include "../include/EngineSystem.h"
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <assert.h>
#include <support/tinyxml2/tinyxml2.h>
using  namespace  cobra_win;
using namespace tinyxml2;


template<> VariableSystem* cobra_win::Singleton2<VariableSystem>::m_pMySelf = NULL;

VariableSystem::VariableSystem()
{
	m_VaribleList.clear();
}

VariableSystem::~VariableSystem()
{

}

char* VariableSystem::GetConfigName(ConfigType FileType)
{
	std::map<ConfigType, std::string>::iterator iter = m_ConfigFileList.find(FileType);
	if (iter == m_ConfigFileList.end())
		return NULL;

	return (char*)(iter->second.c_str());
}

bool VariableSystem::LoadConfigByType(ConfigType FileType, char* pFileName)
{
	assert(pFileName != NULL);

	// 删除已经加载该类型文件的信息
	std::multimap<std::string, _VARIBLE_*>::iterator iter   = m_VaribleList.begin();
	std::multimap<std::string, _VARIBLE_*>::iterator iter_e = m_VaribleList.end();
	for ( ; iter!=iter_e; )
	{
		std::multimap<std::string, _VARIBLE_*>::iterator temp = iter;
		++iter;

		if (temp->second->mFileType == FileType)
		{
			m_VaribleList.erase(temp);
		}
	}

	// 更新改类型文件的名称
	std::map<ConfigType, std::string>::iterator iter2 = m_ConfigFileList.find(FileType);
	if (iter2 == m_ConfigFileList.end())
	{
		m_ConfigFileList.insert(std::map<ConfigType, std::string>::value_type(FileType, pFileName));
	}
	else
	{
		iter2->second = pFileName;
	}

	LoadConfigFile(FileType, pFileName);

	return true;
}

void VariableSystem::UnLoadConfigByType(ConfigType FileType)
{

}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, bool& bValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_bool_value(bValue))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, int& iValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_int_value(iValue))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, long long& iValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_int64_value(iValue))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, float& fValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_float_value(fValue))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, char& value)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_char_value(value))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::GetVariable(ConfigType FileType, char* pSection, char* pKey, char* pValue, unsigned int iValueLen)
{
	assert(pSection != NULL);
	assert(pKey != NULL);
	assert(pValue != NULL);
	assert(iValueLen > 0);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				size_t iLen = sizeof(iter->second->mValue);
				if (iValueLen < sizeof(iter->second->mValue))
					iLen = iValueLen;

				Parser parser(iter->second->mValue, sizeof(iter->second->mValue), '\0');
				if (!parser.parser_string_value(pValue, iLen))
					return false;

				return true;
			}
		}
	} 
	while(false);

	return false;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, bool bValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%u", bValue);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%u", bValue);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, int iValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%d", iValue);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%d", iValue);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, long long iValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%lld", iValue);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%lld", iValue);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, float fValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%f", fValue);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%f", fValue);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, char value)
{
	assert(pSection != NULL);
	assert(pKey != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%c", value);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%c", value);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::SetVariable(ConfigType FileType, char* pSection, char* pKey, char* pValue)
{
	assert(pSection != NULL);
	assert(pKey != NULL);
	assert(pValue != NULL);

	do 
	{
		typedef std::multimap<std::string, _VARIBLE_*> VaribleMap;
		std::pair<VaribleMap::const_iterator, VaribleMap::const_iterator> myPair = m_VaribleList.equal_range(pKey);
		if (myPair.first == myPair.second)
			break;

		VaribleMap::const_iterator iter = myPair.first;
		for ( ; iter!=myPair.second; ++iter)
		{
			if (iter->second->mFileType==FileType && String::compare(iter->second->mSection, pSection, false))
			{
				memset(iter->second->mValue, 0, sizeof(iter->second->mValue));
				sprintf(iter->second->mValue, "%s", pValue);
				SaveConfigByType(FileType);

				return true;
			}
		}
	} 
	while(false);

	_VARIBLE_* pVarible = new _VARIBLE_;
	pVarible->mFileType = FileType;
	String::copy(pVarible->mSection, pSection, sizeof(pVarible->mSection));
	String::copy(pVarible->mKey, pKey, sizeof(pVarible->mKey));
	sprintf(pVarible->mValue, "%s", pValue);
	m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(pKey, pVarible));
	SaveConfigByType(FileType);

	return true;
}

bool VariableSystem::Init()
{
	std::string file = "account.xml";
	LoadConfigByType(_TYPED_CONFIG_ACCOUNT_, (char*)file.c_str());

	file = "resource/config/log.xml";
	LoadConfigByType(_TYPED_CONFIG_LOGGER_, (char*)file.c_str());

	file = "resource/config/system.xml";
	LoadConfigByType(_TYPED_CONFIG_SYSTEM_, (char*)file.c_str());

	m_ConfigFileList.insert(std::map<ConfigType, std::string>::value_type(_TYPED_CONFIG_MEM_, ""));

	CCLOG("VariableSystem Init Success\n");
	return true;
}

void VariableSystem::Tick()
{

}

void VariableSystem::Destroy()
{
	// 保存用户文件
	SaveConfigByType(_TYPED_CONFIG_ACCOUNT_);

	// 删除所有配置项
	std::multimap<std::string, _VARIBLE_*>::iterator iter   = m_VaribleList.begin();
	std::multimap<std::string, _VARIBLE_*>::iterator iter_e = m_VaribleList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_VaribleList.clear();

	// 删除配置类型与文件的映射表
	m_ConfigFileList.clear();

	CCLOG("VariableSystem Destroy Success\n");
}

void VariableSystem::SaveConfigByType(ConfigType FileType)
{
	if (FileType == _TYPED_CONFIG_ACCOUNT_)
	{
		std::string path = EngineSystem::GetDocumentDir()+"account.xml";
		SaveConfigFile(_TYPED_CONFIG_ACCOUNT_, (char*)path.c_str());
	}
}

bool VariableSystem::LoadConfigFile(ConfigType FileType, std::string FileName)
{
	unsigned int iLength = 0;
	char* pFileBuffer = NULL;

	try
	{
		if (FileType == _TYPED_CONFIG_ACCOUNT_)
		{
			if (!EngineSystem::LoadTempFile((char*)FileName.c_str(), pFileBuffer, iLength))
				return false;			
		}else{
			if (!EngineSystem::LoadAppFile((char*)FileName.c_str(), pFileBuffer, iLength))
				return false;	
		}

		//解析Xml内容
		tinyxml2::XMLDocument pDocument;
		pDocument.Parse((const char*)pFileBuffer);

		if (pFileBuffer != NULL)
		{
			delete []pFileBuffer;
			pFileBuffer = NULL;
		}

		tinyxml2::XMLElement* pElement=pDocument.RootElement();
		while (pElement != NULL)
		{
			char buffer[1024] = "";
			String::copy(buffer, (char*)pElement->Value(), sizeof(buffer));

			tinyxml2::XMLElement* pChildElement=pElement->FirstChildElement();
			while (pChildElement != NULL)
			{
				char key[1024] = "";
				String::copy(key, (char*)pChildElement->Value(), sizeof(key));

				char value[1024] = "";
				String::copy(value, (char*)pChildElement->Attribute("value"), sizeof(value));

				_VARIBLE_* pVarible = new _VARIBLE_;
				pVarible->mFileType = FileType;
				String::copy(pVarible->mSection, buffer, sizeof(pVarible->mSection));
				String::copy(pVarible->mKey, key, sizeof(pVarible->mKey));
				String::copy(pVarible->mValue, value, sizeof(pVarible->mValue));
				m_VaribleList.insert(std::multimap<std::string, _VARIBLE_*>::value_type(key, pVarible));

				pChildElement = pChildElement->NextSiblingElement();
			}

			pElement = pElement->NextSiblingElement();
		}
	}
	catch (...)
	{
		if (pFileBuffer != NULL)
		{
			delete []pFileBuffer;
			pFileBuffer = NULL;
		}
		return false;
	}

	return true;
}

void VariableSystem::SaveConfigFile(ConfigType FileType, std::string FileName)
{
	std::map<std::string, _VARIBLE_*>      SectionList;
	std::multimap<std::string, _VARIBLE_*> KeyValueMap;
	std::multimap<std::string, _VARIBLE_*>::iterator iter   = m_VaribleList.begin();
	std::multimap<std::string, _VARIBLE_*>::iterator iter_e = m_VaribleList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second->mFileType == FileType)
		{
			SectionList.insert(std::map<std::string, _VARIBLE_*>::value_type(iter->second->mSection, iter->second));
			KeyValueMap.insert(std::multimap<std::string, _VARIBLE_*>::value_type(iter->second->mSection, iter->second));
		}
	}

	try
	{
		static  char*  XMLHeader = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";

		char text[102400] = "";
		sprintf(text, "%s", XMLHeader);

		std::map<std::string, _VARIBLE_*>::iterator iter   = SectionList.begin();
		std::map<std::string, _VARIBLE_*>::iterator iter_e = SectionList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			std::string SectionName = iter->first;

			sprintf(text, "%s<%s>\n", text, SectionName.c_str());

			std::pair<std::multimap<std::string, _VARIBLE_*>::const_iterator, std::multimap<std::string, _VARIBLE_*>::const_iterator> myPair = KeyValueMap.equal_range(SectionName);
			std::multimap<std::string, _VARIBLE_*>::const_iterator iter2 = myPair.first;
			for ( ; iter2!=myPair.second; ++iter2)
			{
				sprintf(text, "%s	<%s value=\"%s\"/>\n", text, iter2->second->mKey, iter2->second->mValue);
			}

			sprintf(text, "%s</%s>\n", text, SectionName.c_str());
		}

		tinyxml2::XMLDocument doc(FileName.c_str());
		doc.Parse(text);
		doc.SaveFile(FileName.c_str());
	}
	catch (...)
	{
		return ;
	}
}
