#include "../include/DOTATribeApp.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EventTyper.h"
#include "../Include/SysLangDataManager.h"
#include <include/common/Parser.h>

using  namespace  cobra_win;
 
SceneInfoData::SceneInfoData()
{

	mId = 0;
	memset(mSceneInfoPicture, 0, sizeof(mSceneInfoPicture));
	memset(mSceneInfoPicture_tab, 0, sizeof(mSceneInfoPicture_tab));
	memset(mSceneInfoPicture_mission, 0, sizeof(mSceneInfoPicture_mission));
	memset(mSceneInfoPicture_mission_boss, 0, sizeof(mSceneInfoPicture_mission_boss));
	memset(mSceneInfoPicture_mission_reward, 0, sizeof(mSceneInfoPicture_mission_reward));
	mEffectId1 = 0; 
	mEffectId2 = 0; 
	mEffectId3 = 0;
	mSoundID = 0;
	mSceneName = 0;
}

SceneInfoData::~SceneInfoData()
{

}

bool  SceneInfoData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mId))
		return false;

	if (!parser.parser_string_value(mSceneInfoPicture, sizeof(mSceneInfoPicture)))
		return false;

	if (!parser.parser_string_value(mSceneInfoPicture_tab, sizeof(mSceneInfoPicture_tab)))
		return false;

	if (!parser.parser_string_value(mSceneInfoPicture_mission, sizeof(mSceneInfoPicture_mission)))
		return false;

	if (!parser.parser_string_value(mSceneInfoPicture_mission_boss, sizeof(mSceneInfoPicture_mission_boss)))
		return false;

	if (!parser.parser_string_value(mSceneInfoPicture_mission_reward, sizeof(mSceneInfoPicture_mission_reward)))
		return false;

	if (!parser.parser_int_value(mEffectId1))
		return false;

	if (!parser.parser_int_value(mEffectId2))
		return false;

	if (!parser.parser_int_value(mEffectId3))
		return false;

	if (!parser.parser_int_value(mSoundID))
		return false;

	if (!parser.parser_int_value(mSceneName))
		return false;

	return true; 
}


template<> SceneInfoDataManager* cobra_win::Singleton2<SceneInfoDataManager>::m_pMySelf = NULL;

SceneInfoDataManager::SceneInfoDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{

}

SceneInfoDataManager::~SceneInfoDataManager()
{

}


SceneInfoData * SceneInfoDataManager::GetCustomPassDataByID(int customsPassUniqueId)
{ 
	std::map<int,SceneInfoData*>::iterator shapeIter=m_SceneInfoDataList.find(customsPassUniqueId);
	if(shapeIter!=m_SceneInfoDataList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}


std::string    SceneInfoDataManager::GetCustomNameByID(int missionID)
{
	std::map<int,SceneInfoData*>::iterator shapeIter=m_SceneInfoDataList.find(missionID);
	if(shapeIter != m_SceneInfoDataList.end())
	{
		int sceneNameTID = shapeIter->second->mSceneName;
		return SysLangDataManager::get_instance2()->GetSysLangById(sceneNameTID);
	}
	return ""; 
}


std::string  SceneInfoDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/sceneinfodata.txt";

	return "sceneinfodata";
} 


unsigned  int SceneInfoDataManager::GetSize()
{
	return m_SceneInfoDataList.size()*sizeof(SceneInfoData);
}


bool  SceneInfoDataManager::Init()
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


void  SceneInfoDataManager::Tick()
{

}


void  SceneInfoDataManager::Destroy()
{
	std::map<int, SceneInfoData*>::iterator iter   = m_SceneInfoDataList.begin();
	std::map<int, SceneInfoData*>::iterator iter_e = m_SceneInfoDataList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_SceneInfoDataList.clear();
} 


bool  SceneInfoDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	SceneInfoData* pRoleItem = (SceneInfoData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  SceneInfoDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  SceneInfoDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	SceneInfoData* pItemData = new SceneInfoData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_SceneInfoDataList.insert(std::map<int, SceneInfoData*>::value_type(pItemData->mId, pItemData));

	return true;
}