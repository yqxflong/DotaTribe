// Name :		LoadingAnimationDataManager.h
// Function:	Loading界面数据管理
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/DOTATribeApp.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DBSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


LoadingAnimationData::LoadingAnimationData()
{

	mId=0;
	mProcedureId=0;
	mIsNeedAnimation=0;
	mBackgroundSuondID=0;
}

LoadingAnimationData::~LoadingAnimationData()
{

}

bool  LoadingAnimationData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mId))
		return false;

	if (!parser.parser_int_value(mProcedureId))
		return false;

	if (!parser.parser_int_value(mIsNeedAnimation))
		return false;

	if (!parser.parser_int_value(mBackgroundSuondID))
		return false;

	return true; 
}


template<> LoadingAnimationManager* cobra_win::Singleton2<LoadingAnimationManager>::m_pMySelf = NULL;

LoadingAnimationManager::LoadingAnimationManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{

}

LoadingAnimationManager::~LoadingAnimationManager()
{

}


LoadingAnimationData * LoadingAnimationManager::GeLoadingAnimationDataByID(int Id)
{

	std::map<int,LoadingAnimationData*>::iterator shapeIter=m_LoadingAnimationList.find(Id);
	if(shapeIter!=m_LoadingAnimationList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}


std::string  LoadingAnimationManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/loadinganimation.txt";

	return "loadinganimation";
} 


unsigned  int LoadingAnimationManager::GetSize()
{
	return m_LoadingAnimationList.size()*sizeof(LoadingAnimationData);
}


bool  LoadingAnimationManager::Init()
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


void  LoadingAnimationManager::Tick()
{

}


void  LoadingAnimationManager::Destroy()
{
	std::map<int, LoadingAnimationData*>::iterator iter   = m_LoadingAnimationList.begin();
	std::map<int, LoadingAnimationData*>::iterator iter_e = m_LoadingAnimationList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_LoadingAnimationList.clear();
} 


bool  LoadingAnimationManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	LoadingAnimationData* pRoleItem = (LoadingAnimationData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  LoadingAnimationManager::VarifyAfterLoadAll()
{
	return true;
}

bool  LoadingAnimationManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	LoadingAnimationData* pItemData = new LoadingAnimationData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_LoadingAnimationList.insert(std::map<int, LoadingAnimationData*>::value_type(pItemData->mProcedureId, pItemData));

	return true;
}