#include "../include/DOTATribeApp.h"
#include "../include/ParticleDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/DBSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


ParticleData::ParticleData()
{
	 particleEffectID=0;
	 particleEffectPlayType=0;
	 particleEffectZOrder=0;
	 memset(particleEffectFileName,0,sizeof(particleEffectFileName));
	 memset(particleEffectBoneName,0,sizeof(particleEffectBoneName));
	 particleEffectXOffSet=0.0f;
	 particleEffectYOffSet=0.0f;
	 particleEffectAngleOffSet=0;
	 particleEffectIsLocationFollow=0;
	 particleEffectIsAngleFollow=0;
	 particleEffectIsHangover=0;
	 particleEffectIsBlendMode=0;
	 particleEffectIsBindBone=false;
	 particleEffectVarianceX=0.0f;
	 particleEffectVarianceY=0.0f;
}

ParticleData::~ParticleData()
{

}

bool  ParticleData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(particleEffectID))
		return false;
	if (!parser.parser_short_value(particleEffectPlayType))
		return false;
	if (!parser.parser_int_value(particleEffectZOrder))
		return false;
	if (!parser.parser_string_value(particleEffectFileName,sizeof(particleEffectFileName)))
		return false;
	if (!parser.parser_string_value(particleEffectBoneName,sizeof(particleEffectBoneName)))
		return false;
	if (!parser.parser_float_value(particleEffectXOffSet))
		return false;
	if (!parser.parser_float_value(particleEffectYOffSet))
		return false;
	if (!parser.parser_float_value(particleEffectAngleOffSet))
		return false;
	if (!parser.parser_short_value(particleEffectIsLocationFollow))
		return false;
	if (!parser.parser_short_value(particleEffectIsAngleFollow))
		return false;
	if (!parser.parser_short_value(particleEffectIsHangover))
		return false;
	if (!parser.parser_short_value(particleEffectIsBlendMode))
		return false;
	if (!parser.parser_float_value(particleEffectVarianceX))
		return false;
	if (!parser.parser_float_value(particleEffectVarianceY))
		return false;
	  
	std::string bindBoneName=particleEffectBoneName;
	if(bindBoneName=="root"&&bindBoneName=="screen")
	{
		particleEffectIsBindBone=true;
	}
	 
	return true; 
}



template<> ParticleDataManager* cobra_win::Singleton2<ParticleDataManager>::m_pMySelf = NULL;

ParticleDataManager::ParticleDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_particleDataMap.clear();
}

ParticleDataManager::~ParticleDataManager()
{

}

ParticleData * ParticleDataManager::GetParticleDataByID(int particleEffectID)
{
	std::map<int,ParticleData* >::iterator particleIter=m_particleDataMap.find(particleEffectID);
	if(particleIter!=m_particleDataMap.end())
	{
		return particleIter->second;
	}
	return NULL; 
}


std::string   ParticleDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/particledata.txt";

	return "particledata";
} 


unsigned  int ParticleDataManager::GetSize()
{
	return m_particleDataMap.size()*sizeof(ParticleData);
}


bool  ParticleDataManager::Init()
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


void  ParticleDataManager::Tick()
{

}


void  ParticleDataManager::Destroy()
{
	std::map<int, ParticleData*>::iterator iter   = m_particleDataMap.begin();
	std::map<int, ParticleData*>::iterator iter_e = m_particleDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_particleDataMap.clear();
} 


bool  ParticleDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ParticleData* pRoleItem = (ParticleData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  ParticleDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ParticleDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	ParticleData* pItemData = new ParticleData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_particleDataMap.insert(std::map<int, ParticleData*>::value_type(pItemData->particleEffectID, pItemData));

	return true;
}












