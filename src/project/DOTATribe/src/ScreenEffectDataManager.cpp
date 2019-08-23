#include <cocos2d.h>
#include    "../include/ScreenEffectDataManager.h"
#include    "../include/DOTATribeApp.h"
#include    "../include/DBSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;

  

ScreenEffectData::ScreenEffectData()
{
    screenEffectID=0;
    screenEffectZOrder=0;
	memset(screenEffectColorStr,0,sizeof(screenEffectColorStr));
	screenEffectFadeInTime=0.0f;
	screenEffectDurationTime=0.0f;
	screenEffectFadeOutTime=0.0f;
}

ScreenEffectData::~ScreenEffectData()
{
 
}

cocos2d::ccColor4B  ScreenEffectData::GetScreenEffectColor()
{
	std::string totalValue=screenEffectColorStr;
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



bool  ScreenEffectData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(screenEffectID))
		return false;

	if (!parser.parser_int_value(screenEffectZOrder))
		return false;

	if (!parser.parser_string_value(screenEffectColorStr,sizeof(screenEffectColorStr)))
		return false;

	if (!parser.parser_float_value(screenEffectFadeInTime))
		return false;

	if (!parser.parser_float_value(screenEffectDurationTime))
		return false;

	if (!parser.parser_float_value(screenEffectFadeOutTime))
		return false;
 
	return true; 
}
 


template<> ScreenEffectDataManager* cobra_win::Singleton2<ScreenEffectDataManager>::m_pMySelf = NULL;

ScreenEffectDataManager::ScreenEffectDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_screenEffectMapList.clear();
}

ScreenEffectDataManager::~ScreenEffectDataManager()
{

}

ScreenEffectData * ScreenEffectDataManager::GetScreenEffectByID(int screenEffectID)
{
	std::map<int,ScreenEffectData*>::iterator effectIter=m_screenEffectMapList.find(screenEffectID);
	if(effectIter!=m_screenEffectMapList.end())
	{
		return effectIter->second;
	}
	return NULL; 
}


std::string   ScreenEffectDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/screeneffect.txt";

	return "screeneffect";
} 


unsigned  int ScreenEffectDataManager::GetSize()
{
	return m_screenEffectMapList.size()*sizeof(ScreenEffectData);
}


bool  ScreenEffectDataManager::Init()
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


void  ScreenEffectDataManager::Tick()
{

}


void  ScreenEffectDataManager::Destroy()
{
	std::map<int, ScreenEffectData*>::iterator iter   = m_screenEffectMapList.begin();
	std::map<int, ScreenEffectData*>::iterator iter_e = m_screenEffectMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_screenEffectMapList.clear();
} 


bool  ScreenEffectDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ScreenEffectData* pRoleItem = (ScreenEffectData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  ScreenEffectDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ScreenEffectDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	ScreenEffectData* pItemData = new ScreenEffectData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_screenEffectMapList.insert(std::map<int, ScreenEffectData*>::value_type(pItemData->screenEffectID, pItemData));

	return true;
}












