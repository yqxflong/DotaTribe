#include "../include/DOTATribeApp.h"
#include "../include/FrameAnimateDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/DBSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


FrameAnimateData::FrameAnimateData()
{
	frameAnimateEffectID=0;
	frameAnimateEffectPlayType=0;
	frameAnimateEffectZOrder=0;
	frameAnimateEffectAnimationID=0;
	memset(frameAnimateEffectBoneName,0,sizeof(frameAnimateEffectBoneName));
	frameAnimateEffectXOffSet=0.0f;
	frameAnimateEffectYOffSet=0.0f;
	frameAnimateEffectAngleOffSet=0.0f;
	frameAnimateIsLocationFollow=0;
	frameAnimateIsAngleFollow=0;
	frameAnimateIsBoneBindEffect=false;
}

FrameAnimateData::~FrameAnimateData()
{

}

bool  FrameAnimateData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(frameAnimateEffectID))
		return false;
	if (!parser.parser_short_value(frameAnimateEffectPlayType))
		return false;
	if (!parser.parser_int_value(frameAnimateEffectZOrder))
		return false;
	if (!parser.parser_int_value(frameAnimateEffectAnimationID))
		return false;
	if (!parser.parser_string_value(frameAnimateEffectBoneName,sizeof(frameAnimateEffectBoneName)))
		return false;
	if (!parser.parser_float_value(frameAnimateEffectXOffSet))
		return false;
	if (!parser.parser_float_value(frameAnimateEffectYOffSet))
		return false;
	if (!parser.parser_float_value(frameAnimateEffectAngleOffSet))
		return false;
	if (!parser.parser_short_value(frameAnimateIsLocationFollow))
		return false;
	if (!parser.parser_short_value(frameAnimateIsAngleFollow))
		return false;

	std::string  bindBoneName=frameAnimateEffectBoneName;

	if(bindBoneName!="root"&&bindBoneName!="screen")
	{
		frameAnimateIsBoneBindEffect=true;
	}

	  
	return true; 
}



template<> FrameAnimateDataManager* cobra_win::Singleton2<FrameAnimateDataManager>::m_pMySelf = NULL;

FrameAnimateDataManager::FrameAnimateDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_frameAnimateDataMap.clear();
}

FrameAnimateDataManager::~FrameAnimateDataManager()
{

}

FrameAnimateData * FrameAnimateDataManager::GetFrameAnimateDataByID(int frameAniamtionEffectID)
{
	std::map<int,FrameAnimateData*>::iterator effectIter=m_frameAnimateDataMap.find(frameAniamtionEffectID);
	if(effectIter!=m_frameAnimateDataMap.end())
	{
		return effectIter->second;
	}
	return NULL; 
}


std::string   FrameAnimateDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/frameanimatedata.txt";

	return "frameanimatedata";
} 


unsigned  int FrameAnimateDataManager::GetSize()
{
	return m_frameAnimateDataMap.size()*sizeof(FrameAnimateData);
}


bool  FrameAnimateDataManager::Init()
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


void  FrameAnimateDataManager::Tick()
{

}


void  FrameAnimateDataManager::Destroy()
{
	std::map<int, FrameAnimateData*>::iterator iter   = m_frameAnimateDataMap.begin();
	std::map<int, FrameAnimateData*>::iterator iter_e = m_frameAnimateDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_frameAnimateDataMap.clear();
} 


bool  FrameAnimateDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	FrameAnimateData* pItemData = (FrameAnimateData*)pData;
	assert(pItemData != NULL);
	return true;

}

bool  FrameAnimateDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  FrameAnimateDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	FrameAnimateData* pItemData = new FrameAnimateData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_frameAnimateDataMap.insert(std::map<int, FrameAnimateData*>::value_type(pItemData->frameAnimateEffectID, pItemData));

	return true;
}












