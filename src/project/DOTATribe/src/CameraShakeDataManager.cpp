#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/DOTATribeApp.h"
#include "../include/CameraShakeDataManager.h"
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


CameraShakeData::CameraShakeData()
{
	shakeItemID_=0;                     //震动ID
	halfCircleTime_=0;					//半周期时间
	shakeItemType_=0;                   //震动类型
	shakeX_=0.0;           //左右的振幅
	shakeY_=0.0;           //上下振幅
	containTime_=0;					   //震动持续时间 
}

CameraShakeData::~CameraShakeData()
{

}

bool  CameraShakeData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(shakeItemID_))
		return false;

	if (!parser.parser_int_value(halfCircleTime_))
		return false;

	if (!parser.parser_int_value(shakeItemType_))
		return false;

	if (!parser.parser_float_value(shakeX_))
		return false;

	if (!parser.parser_float_value(shakeY_))
		return false;

	if (!parser.parser_int_value(containTime_))
		return false;

	return true; 
}



template<> CameraShakeDataManager* cobra_win::Singleton2<CameraShakeDataManager>::m_pMySelf = NULL;

CameraShakeDataManager::CameraShakeDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_CameraShakeDataMap_.clear();
}

CameraShakeDataManager::~CameraShakeDataManager()
{

}

CameraShakeData * CameraShakeDataManager::GetCamerShakeDataByID(int skillItemID)
{
	std::map<int,CameraShakeData*>::iterator bulletIter=m_CameraShakeDataMap_.find(skillItemID);
	if(bulletIter!=m_CameraShakeDataMap_.end())
	{
		return bulletIter->second;
	}
	return NULL; 
}



std::string   CameraShakeDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/camerashakedata.txt";

	return "camerashakedata";
} 


unsigned  int CameraShakeDataManager::GetSize()
{
	return m_CameraShakeDataMap_.size()*sizeof(CameraShakeData);
}


bool  CameraShakeDataManager::Init()
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


void  CameraShakeDataManager::Tick()
{

}


void  CameraShakeDataManager::Destroy()
{
	std::map<int, CameraShakeData*>::iterator iter   = m_CameraShakeDataMap_.begin();
	std::map<int, CameraShakeData*>::iterator iter_e = m_CameraShakeDataMap_.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_CameraShakeDataMap_.clear();
} 


bool  CameraShakeDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	CameraShakeData* pRoleItem = (CameraShakeData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  CameraShakeDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  CameraShakeDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	CameraShakeData* pItemData = new CameraShakeData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_CameraShakeDataMap_.insert(std::map<int, CameraShakeData*>::value_type(pItemData->shakeItemID_, pItemData));

	return true;
}












