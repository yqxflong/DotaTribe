
// Name :		ActivityDataManager.h
// Function:	活动数据管理器
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/DOTATribeApp.h"
#include "../include/ActivityDataManager.h"
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


Activity::Activity()
{ 
	m_nActivityType = 0; 										//活动类型 
	m_nActivityWindowID = 0;									//窗口ID  
	
	m_nUseLua = 0;
	m_nShowEventId = -1;
	m_nHideEventId = -1;
}

Activity::~Activity()
{ 
}

bool  Activity::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(m_nActivityType))
		return false;

	if (!parser.parser_int_value(m_nActivityWindowID))
		return false; 
 
	if(!parser.parser_int_value(m_nUseLua))
		return false;

	if(!parser.parser_int_value(m_nShowEventId))
		return false;

	if(!parser.parser_int_value(m_nHideEventId))
		return false;

	if(!parser.parser_int_value(m_nShowActivityBg))
		return false;

	return true; 
}


template<> ActivityManager* cobra_win::Singleton2<ActivityManager>::m_pMySelf = NULL;

ActivityManager::ActivityManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{

}

ActivityManager::~ActivityManager()
{

}


Activity * ActivityManager::GetDataByType(int Id)
{ 
	std::map<int,Activity*>::iterator shapeIter=m_ActivityList.find(Id);
	if(shapeIter!=m_ActivityList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}
 
std::string  ActivityManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/activity.txt";

	return "activity";
} 


unsigned  int ActivityManager::GetSize()
{
	return m_ActivityList.size()*sizeof(Activity);
}
 
bool  ActivityManager::Init()
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


void  ActivityManager::Tick()
{ 
}


void  ActivityManager::Destroy()
{
	std::map<int, Activity*>::iterator iter   = m_ActivityList.begin();
	std::map<int, Activity*>::iterator iter_e = m_ActivityList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_ActivityList.clear();
} 


bool  ActivityManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	Activity* pRoleItem = (Activity*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  ActivityManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ActivityManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	 Activity* pItemData = new  Activity;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false; 
	m_ActivityList.insert(std::map<int,  Activity*>::value_type(pItemData->m_nActivityType, pItemData));

	return true;
}