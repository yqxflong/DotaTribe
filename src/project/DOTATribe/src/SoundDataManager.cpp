#include <cocos2d.h>
#include "../include/SoundDataManager.h"
#include "../include/DOTATribeApp.h"
#include "../include/EngineSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DBSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <SimpleAudioEngine.h>
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>

using  namespace  cobra_win;

SoundData::SoundData()
{
	id=0;
	soundType=0;
	soundID=0;
	soundIsCycle=false;
	memset(soundName,0,sizeof(soundName));
	soundVolume=0;

}

SoundData::~SoundData()
{

}

bool  SoundData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(id))
		return false;

	if (!parser.parser_int_value(soundType))
		return false;

	if (!parser.parser_int_value(soundID))
		return false;

	if (!parser.parser_bool_value(soundIsCycle))
		return false;

	if (!parser.parser_string_value(soundName,sizeof(soundName)))
		return  false;

	if (!parser.parser_int_value(soundVolume))
		return false;

	return true; 
}



template<> SoundDataManager* cobra_win::Singleton2<SoundDataManager>::m_pMySelf = NULL;

SoundDataManager::SoundDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_soundDataMap.clear();
}

SoundDataManager::~SoundDataManager()
{
}

SoundData * SoundDataManager::GetSoundData(int id)
{
	std::map<int, SoundData*>::iterator soudIter=m_soundDataMap.find(id);
	if(soudIter!=m_soundDataMap.end())
	{
		return soudIter->second;
	}
	return NULL; 
}


std::string   SoundDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/sounddata.txt";

	return "sounddata";
} 


unsigned  int SoundDataManager::GetSize()
{
	return m_soundDataMap.size()*sizeof(SoundData);
}


bool  SoundDataManager::Init()
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


void  SoundDataManager::Tick()
{

}


void  SoundDataManager::Destroy()
{
	std::map<int, SoundData*>::iterator iter   = m_soundDataMap.begin();
	std::map<int, SoundData*>::iterator iter_e = m_soundDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_soundDataMap.clear();
} 


bool  SoundDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	SoundData* pRoleItem = (SoundData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  SoundDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  SoundDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	SoundData* pItemData = new SoundData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_soundDataMap.insert(std::map<int,SoundData*>::value_type(pItemData->id,pItemData));

	return true;
}













