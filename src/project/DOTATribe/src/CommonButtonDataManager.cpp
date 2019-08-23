#include <cocos2d.h>
#include "../include/CommonButtonDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


CommonButtonItemData::CommonButtonItemData()
{
	memset(mButtonName, 0, sizeof(mButtonName));
	memset(mSoundName, 0, sizeof(mSoundName));
}

CommonButtonItemData::~CommonButtonItemData()
{

}

bool CommonButtonItemData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(id))
		return false;

	if (!parser.parser_string_value(mButtonName, sizeof(mButtonName)))
		return false;

	parser.parser_string_value(mSoundName, sizeof(mSoundName));

	return true;
}

template<> CommonButtonDataManager* cobra_win::Singleton2<CommonButtonDataManager>::m_pMySelf = NULL;

CommonButtonDataManager::CommonButtonDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_CommonButtonList.clear();
}	

CommonButtonDataManager::~CommonButtonDataManager()
{

}

CommonButtonItemData* CommonButtonDataManager::GetCommonButtonByName(std::string name)
{
	std::map<std::string, CommonButtonItemData*>::iterator iter = m_CommonButtonList.find(name);
	if (iter == m_CommonButtonList.end())
		return NULL;

	return iter->second;
}

std::string CommonButtonDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/commonbutton.txt";

	return "commonbutton";
}

unsigned  int CommonButtonDataManager::GetSize()
{
	return m_CommonButtonList.size()*sizeof(CommonButtonItemData);
}

bool  CommonButtonDataManager::Init()
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

void  CommonButtonDataManager::Tick()
{

}

void  CommonButtonDataManager::Destroy()
{
	std::map<std::string, CommonButtonItemData*>::iterator iter   = m_CommonButtonList.begin();
	std::map<std::string, CommonButtonItemData*>::iterator iter_e = m_CommonButtonList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_CommonButtonList.clear();
}

bool  CommonButtonDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	CommonButtonItemData* pButtonItem = (CommonButtonItemData*)pData;
	assert(pButtonItem != NULL);

	if (pButtonItem->mButtonName[0] == '\0')
		return false;

	return true;
}

bool  CommonButtonDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  CommonButtonDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	CommonButtonItemData* pItemData = new CommonButtonItemData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_CommonButtonList.insert(std::map<std::string, CommonButtonItemData*>::value_type(pItemData->mButtonName, pItemData));
	return true;
}
