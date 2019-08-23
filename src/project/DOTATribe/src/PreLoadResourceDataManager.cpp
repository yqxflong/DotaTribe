#include <cocos2d.h>
#include "../include/PreLoadResourceDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


PreLoadResourceItemData::PreLoadResourceItemData()
{
	mType = -1;
	memset(mFileName, 0, sizeof(mFileName));
}

PreLoadResourceItemData::~PreLoadResourceItemData()
{

}

bool PreLoadResourceItemData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(id))
		return false;

	if (!parser.parser_int_value(mType))
		return false;

	if (!parser.parser_string_value(mFileName, sizeof(mFileName)))
		return false;

	return true;
}

template<> PreLoadResourceDataManager* cobra_win::Singleton2<PreLoadResourceDataManager>::m_pMySelf = NULL;

PreLoadResourceDataManager::PreLoadResourceDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_ResourceList.clear();
}

PreLoadResourceDataManager::~PreLoadResourceDataManager()
{

}

unsigned int PreLoadResourceDataManager::GetPreLoadResourceNumber()
{
	return m_ResourceList.size();
}

PreLoadResourceItemData* PreLoadResourceDataManager::GetItemDataByPos(unsigned int pos)
{
	assert(pos >= 0);
	assert(pos < m_ResourceList.size());

	return m_ResourceList[pos];
}

std::string PreLoadResourceDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/preloadresource.txt";

	return "preloadresource";
}

unsigned  int  PreLoadResourceDataManager::GetSize()
{
	return m_ResourceList.size()*sizeof(PreLoadResourceItemData);
}

bool  PreLoadResourceDataManager::Init()
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

void  PreLoadResourceDataManager::Tick()
{

}

void  PreLoadResourceDataManager::Destroy()
{
	std::vector<PreLoadResourceItemData*>::iterator iter   = m_ResourceList.begin();
	std::vector<PreLoadResourceItemData*>::iterator iter_e = m_ResourceList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete (*iter);
	}
	m_ResourceList.clear();
}

bool  PreLoadResourceDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	PreLoadResourceItemData* pResourceItem = (PreLoadResourceItemData*)pData;
	assert(pResourceItem != NULL);

	if (pResourceItem->mType!=_TYPED_RESOURCE_PLIST_ && pResourceItem->mType!=_TYPED_RESOURCE_IMAGE_)
		return false;

	if (pResourceItem->mFileName[0] == '\0')
		return false;

	return true;
}

bool  PreLoadResourceDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  PreLoadResourceDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	PreLoadResourceItemData* pItemData = new PreLoadResourceItemData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_ResourceList.push_back(pItemData);
	return true;
}
