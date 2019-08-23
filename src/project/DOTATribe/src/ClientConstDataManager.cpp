//Name£ºClientConstDataManager
//Written By£ºÒüÇ¿

#include "../include/ClientConstDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/Parser.h>
#include "../include/LoggerSystem.h"

using  namespace  cobra_win;
using namespace std;

ClientConstData::ClientConstData()
:value_(0)
{
	memset(key_,0,sizeof(key_));
}

bool  ClientConstData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if(!parser.parser_string_value(key_,sizeof(key_)))
		isErr=true;

	if (!parser.parser_int_value(value_))
		isErr=true;

	if (isErr)
	{
		LOGGERSYSTEM->LogInfo("Err: ClientConstData read Error!");
		return false;
	}
	return true; 
}

template<> ClientConstDataManager* cobra_win::Singleton2<ClientConstDataManager>::m_pMySelf = NULL;


int ClientConstDataManager::getValueByKey(const char* key){
	std::map<std::string,int>::iterator it=m_mapList.find(key);
	return it->second;
}

std::string   ClientConstDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/const.txt";

	return "const";
} 


unsigned  int ClientConstDataManager::GetSize()
{
	return m_mapList.size()*sizeof(int);
}


bool  ClientConstDataManager::Init()
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


void  ClientConstDataManager::Tick()
{

}


void  ClientConstDataManager::Destroy()
{
	m_mapList.clear();
} 


bool  ClientConstDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ClientConstData* item = (ClientConstData*)pData;
	assert(item != NULL);

	return true;
}

bool  ClientConstDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ClientConstDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	ClientConstData* pItemData = new ClientConstData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_mapList.insert(map<string,int>::value_type(pItemData->key_,pItemData->value_));
	delete pItemData;

	return true;
}