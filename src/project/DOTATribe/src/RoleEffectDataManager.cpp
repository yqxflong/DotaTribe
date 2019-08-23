#include "../include/DOTATribeApp.h"
#include "../include/RoleEffectDataManager.h"
#include  "../include/DBSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


RoleEffectData::RoleEffectData()
{ 
    roleEffectID=0;
	memset(roleEffectColorStr,0,sizeof(roleEffectColorStr));
	roleEffectDurationTime=0.0f;
	roleEffectFadeInTime=0.0f;
	roleEffectFadeOutTime=0.0f;
} 

RoleEffectData::~RoleEffectData()
{

}

bool  RoleEffectData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(roleEffectID))
		return false;

	if(!parser.parser_string_value(roleEffectColorStr,sizeof(roleEffectColorStr)))
		return false;

	if (!parser.parser_float_value(roleEffectFadeInTime))
		return false;

	if (!parser.parser_float_value(roleEffectDurationTime))
		return false;

	if (!parser.parser_float_value(roleEffectFadeOutTime))
		return false;
 
	return true; 
}



cocos2d::ccColor4B  RoleEffectData::GetRoleEffectColor()
{
	std::string totalValue=roleEffectColorStr;
	int   delimiterPos=totalValue.find('-');
	std::string rValue=totalValue.substr(0,delimiterPos);
	int   delemiterPos2=delimiterPos;
	delimiterPos=totalValue.find('-',delimiterPos+1);
	std::string gValue=totalValue.substr(delemiterPos2+1,delimiterPos-delemiterPos2-1);
	int   delemiterPos3=delimiterPos;
	delemiterPos2=totalValue.find('-',delimiterPos+1);
	std::string bValue=totalValue.substr(delemiterPos3+1,delemiterPos2-delemiterPos3-1);

	std::string aValue=totalValue.substr(delemiterPos2+1, totalValue.size()-delemiterPos2);

	cocos2d::ccColor4B  bufferColor;
	bufferColor.r=atoi(rValue.c_str());
	bufferColor.g=atoi(gValue.c_str());
	bufferColor.b=atoi(bValue.c_str());
	bufferColor.a=atoi(aValue.c_str());
	return  bufferColor;
}
  

template<> RoleEffectDataManager* cobra_win::Singleton2<RoleEffectDataManager>::m_pMySelf = NULL;

RoleEffectDataManager::RoleEffectDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_roleEffectDataMapList.clear();
}

RoleEffectDataManager::~RoleEffectDataManager()
{

}

RoleEffectData * RoleEffectDataManager::GetRoleEffectDataByID(int roleEffectID)
{
	std::map<int,RoleEffectData*>::iterator roleEffectIter=m_roleEffectDataMapList.find(roleEffectID);
	if(roleEffectIter!=m_roleEffectDataMapList.end())
	{
		return roleEffectIter->second;
	}
	return NULL; 
}


std::string   RoleEffectDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/roleeffect.txt";

	return "roleeffect";
} 


unsigned  int RoleEffectDataManager::GetSize()
{
	return m_roleEffectDataMapList.size()*sizeof(RoleEffectData);
}


bool  RoleEffectDataManager::Init()
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


void  RoleEffectDataManager::Tick()
{

}


void  RoleEffectDataManager::Destroy()
{
	std::map<int, RoleEffectData*>::iterator iter   = m_roleEffectDataMapList.begin();
	std::map<int, RoleEffectData*>::iterator iter_e = m_roleEffectDataMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_roleEffectDataMapList.clear();
} 


bool  RoleEffectDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	RoleEffectData* pRoleItem = (RoleEffectData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  RoleEffectDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  RoleEffectDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	RoleEffectData* pItemData = new RoleEffectData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_roleEffectDataMapList.insert(std::map<int, RoleEffectData*>::value_type(pItemData->roleEffectID, pItemData));

	return true;
}












