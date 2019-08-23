//Name : 分类ID维护表
//Function : ID与string的对应
//Author : 方骏
//Data : 2013-7-29

#include <cocos2d.h>
#include "../include/IDStringDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include "../include/VariableSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>
#include <string>
#include "../include/SysLangDataManager.h"

IDStringData::IDStringData()
	:mTag(0)
	,mSubTag(0)
{

}

bool  IDStringData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mTag))
		return false;

	if(!parser.parser_int_value(mSubTag))
		return false;

//================读取sysid,再取字符串===========//
	int sysid=0;
	if (!parser.parser_int_value(sysid))
		return false;
	mString =SysLangDataManager::get_instance2()->GetSysLangById(sysid);

	return true;
}

template<> IDStringDataManager* cobra_win::Singleton2<IDStringDataManager>::m_pMySelf = NULL;

IDStringDataManager::IDStringDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_IDStringDataList.clear();
}

IDStringDataManager::~IDStringDataManager()
{

}


std::string IDStringDataManager::GetIDStringByID(int tag, int subTag)
{
	std::map<int, std::vector<std::string> >::iterator iter = m_IDStringDataList.find(tag);
	if (iter == m_IDStringDataList.end())
		return "";

	std::vector<std::string> vec = iter->second;

	if(subTag < (int)vec.size())
	{
		return vec[subTag];
	}

	return "";
}
std::string IDStringDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/idstring.txt";

	return "idstring";
}

unsigned  int IDStringDataManager::GetSize()
{
	return m_IDStringDataList.size();
}

bool  IDStringDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}

		return true;
	} 
	while(false);

	return false;
}

void  IDStringDataManager::Tick()
{

}

void  IDStringDataManager::Destroy()
{
	std::map<int, std::vector<std::string> >::iterator iter   = m_IDStringDataList.begin();
	std::map<int, std::vector<std::string> >::iterator iter_e = m_IDStringDataList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		iter->second.clear();
	}
	m_IDStringDataList.clear();
}

bool IDStringDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	IDStringData* pItem = (IDStringData*)pData;
	assert(pItem != NULL);

	return true;
}

bool IDStringDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  IDStringDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	IDStringData* pItemData = new IDStringData;
	do 
	{
		if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
			break;

		if (!Varify(pItemData))
			break;

		std::map<int, std::vector<std::string> >::iterator iter = m_IDStringDataList.find(pItemData->mTag);
		if(iter == m_IDStringDataList.end())	
		{
			std::vector<std::string> vec;
			vec.push_back(pItemData->mString);
			m_IDStringDataList.insert(std::map<int, std::vector<std::string> >::value_type(pItemData->mTag, vec));
		}
		else
		{
			iter->second.push_back(pItemData->mString);
		}

		delete pItemData;
		return true;
	}
	while (false);

	delete pItemData;
	return false;
}
