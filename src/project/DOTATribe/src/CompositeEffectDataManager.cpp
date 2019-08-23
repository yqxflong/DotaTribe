#include "../include/DOTATribeApp.h"
#include "../include/CompositeEffectDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


CompositeEffectData::CompositeEffectData()
{
	compositeEffectID=0;
    soundEffectID=0;
	soundEfefctTriggerTime=0.0f;
    compositeEffectCount=0;
	compositeEffectVec.clear(); 
}

CompositeEffectData::~CompositeEffectData()
{

}

bool  CompositeEffectData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(compositeEffectID))
		return false;
	if (!parser.parser_int_value(soundEffectID))
		return false;
	if (!parser.parser_float_value(soundEfefctTriggerTime))
		return false;
	if (!parser.parser_int_value(compositeEffectCount))
		return false;

	soundEfefctTriggerTime/=1000.f;

	int    effectCount=0;
	int    effectType=0;
	int    effectID=0;
	float  effectTriggerTime=0.0f;

	for(int effectIndex=0;effectIndex<_MAX_EFFECT_NODE_COUNT_;effectIndex++)
	{
		if (!parser.parser_int_value(effectType))
			return false;
		if (!parser.parser_int_value(effectID))
			return false;
		if (!parser.parser_float_value(effectTriggerTime))
			return false;
		 
		if(effectCount<compositeEffectCount)
		{
			if(effectType!=-1&&effectID!=-1)
			{
				CEffectData effectData;
				effectData.effectType=effectType;
				effectData.effectID=effectID;
				effectData.effectTriggerTime=effectTriggerTime/1000;
				compositeEffectVec.push_back(effectData);
				effectCount++;
			}
		}
	} 

	return true; 
}



template<> CompositeEffectDataManager* cobra_win::Singleton2<CompositeEffectDataManager>::m_pMySelf = NULL;

CompositeEffectDataManager::CompositeEffectDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_compositeEffectMap.clear();
}

CompositeEffectDataManager::~CompositeEffectDataManager()
{

}

CompositeEffectData * CompositeEffectDataManager::GetCompositeEffectDataByID(int compositeEffectID)
{
	std::map<int,CompositeEffectData*>::iterator effectIter=m_compositeEffectMap.find(compositeEffectID);
	if(effectIter!=m_compositeEffectMap.end())
	{
		return effectIter->second;
	}
	return NULL; 
}


std::string   CompositeEffectDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/compositeeffectdata.txt";

	return "compositeeffectdata";
} 


unsigned  int CompositeEffectDataManager::GetSize()
{
	return m_compositeEffectMap.size()*sizeof(CompositeEffectData);
}


bool  CompositeEffectDataManager::Init()
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


void  CompositeEffectDataManager::Tick()
{

}


void  CompositeEffectDataManager::Destroy()
{
	std::map<int, CompositeEffectData*>::iterator iter   = m_compositeEffectMap.begin();
	std::map<int, CompositeEffectData*>::iterator iter_e = m_compositeEffectMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_compositeEffectMap.clear();
} 


bool  CompositeEffectDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	CompositeEffectData* pRoleItem = (CompositeEffectData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  CompositeEffectDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  CompositeEffectDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	CompositeEffectData* pItemData = new CompositeEffectData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_compositeEffectMap.insert(std::map<int, CompositeEffectData*>::value_type(pItemData->compositeEffectID, pItemData));

	return true;
}












