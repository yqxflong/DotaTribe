//Name：VipFontManager
//Func:		读取Vip界面特权信息
//Written By：lvyunlong
//Date:20131126

#include "../include/VipFontDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/Parser.h>
#include "../include/LoggerSystem.h"

using  namespace  cobra_win;
using namespace std;

VipFontData::VipFontData()
:viptype_(0),
id_(0),
syslangid_(0),
fsyleid_(0)
{
	
}

bool  VipFontData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(viptype_))
		isErr=true;

	if (!parser.parser_int_value(id_))
		isErr=true;

	if (!parser.parser_int_value(syslangid_))
		isErr=true;

	if (!parser.parser_int_value(fsyleid_))
		isErr=true;

	if (isErr)
	{
		LOGGERSYSTEM->LogInfo("Err: VipFontData read Error!");
		return false;
	}
	return true; 
}

template<> VipFontManager* cobra_win::Singleton2<VipFontManager>::m_pMySelf = NULL;


std::vector<VipFontData*> VipFontManager::getDataByID(size_t idx){
	return (m_mapList.find(idx))->second; 
}

VipFontData* VipFontManager::getVipFontData(size_t idx,size_t subIdx){
	return m_mapList[idx][subIdx]; 
}

std::string   VipFontManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/vipprivilege.txt";

	return "vipprivilege";
} 


unsigned  int VipFontManager::GetSize()
{
	return m_mapList.size()*sizeof(VipFontData);
}


bool  VipFontManager::Init()
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


void  VipFontManager::Tick()
{

}

void  VipFontManager::Destroy()
{
	std::map<int,std::vector<VipFontData*> >::iterator iter = m_mapList.begin();
	while(iter!=m_mapList.end())
	{ 
		std::vector<VipFontData*> vec = iter->second;
		std::vector<VipFontData*>::iterator it_begin = vec.begin();
		std::vector<VipFontData*>::iterator it_end = vec.end();
		for (it_begin;it_begin != it_end;it_begin++)
		{
			delete (*it_begin);
			(*it_begin) = NULL;
		}
		vec.clear();
		iter++;
	}
	m_mapList.clear();
} 

bool  VipFontManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	VipFontData* item = (VipFontData*)pData;
	assert(item != NULL);

	return true;
}

bool  VipFontManager::VarifyAfterLoadAll()
{
	return true;
}

bool  VipFontManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	VipFontData* pItemData = new VipFontData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	std::map<int, std::vector<VipFontData*> >::iterator iter = m_mapList.find(pItemData->viptype_);
	if(iter == m_mapList.end())	
	{
		std::vector<VipFontData*> vec;
		vec.push_back(pItemData);
		m_mapList.insert(std::map<int, std::vector<VipFontData*> >::value_type(pItemData->viptype_, vec));
	}
	else
	{
		iter->second.push_back(pItemData);
	}

	return true;
}