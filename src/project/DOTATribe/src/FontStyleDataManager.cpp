//Name：FontStyleDataManager
//Func:		用于读取字体样式
//Written By：尹强

#include "../include/FontStyleDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/Parser.h>
#include "../include/LoggerSystem.h"

using  namespace  cobra_win;
using namespace std;

FSData::FSData()
:idx_(0)
,fontsize_(0)
,colorR_(0)
,colorG_(0)
,colorB_(0)
{
	memset(fontname_,0,sizeof(fontname_));
}

bool  FSData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if(!parser.parser_int_value(idx_))
		isErr=true;

	if(!parser.parser_string_value(fontname_,sizeof(fontname_)))
		isErr=true;

	if(!parser.parser_float_value(fontsize_))
		isErr=true;

	if(!parser.parser_int_value(colorR_))
		isErr=true;

	if(!parser.parser_int_value(colorG_))
		isErr=true;

	if(!parser.parser_int_value(colorB_))
		isErr=true;

	if (isErr)
	{
		LOGGERSYSTEM->LogInfo("Err:  FSData read Error!");
		return false;
	}
	return true; 
}

template<> FontStyleDataManager* cobra_win::Singleton2<FontStyleDataManager>::m_pMySelf = NULL;


FSData* FontStyleDataManager::getDataByID(int idx){
	std::map<int,FSData*>::iterator it=m_map.find(idx);
	if(it!=m_map.end())
	{
		return it->second;
	}
	return NULL; 
}

std::string   FontStyleDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/fontstyle.txt";

	return "fontstyle";
} 


unsigned  int FontStyleDataManager::GetSize()
{
	return m_map.size()*sizeof(FSData);
}


bool  FontStyleDataManager::Init()
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


void  FontStyleDataManager::Tick()
{

}


void  FontStyleDataManager::Destroy()
{
	std::map<int, FSData*>::iterator iter   = m_map.begin();
	while(iter!=m_map.end())
	{ 
		delete iter->second;
		iter++;
	}
	m_map.clear();
} 


bool  FontStyleDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	FSData* item = (FSData*)pData;
	assert(item != NULL);

	return true;
}

bool  FontStyleDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  FontStyleDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	FSData* pItemData = new FSData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_map.insert(std::map<int, FSData*>::value_type(pItemData->idx_, pItemData));

	return true;
}