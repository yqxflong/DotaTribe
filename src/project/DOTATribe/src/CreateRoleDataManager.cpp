// Name :		CreateRoleDataManager.h
// Function:	��ɫ����������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/DOTATribeApp.h"
#include "../include/CreateRoleDataManager.h"
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


CreateRoleData::CreateRoleData()
{
	mRoleIndexID = 0;								//��ɫ����ID
	mRoleModelID = 0;								//��ɫģ��ID
	mRoleShapeID = 0;								//��ɫģ��ID
	mRoleSelectedAnimationID = 0;					//ѡ�ж���ID
	mRoleDisabledAnimationID = 0;					//δѡ�ж���ID
	mRoleEntranceAnimationID = 0;					//��������ID
	mRoleLeaveAnimationID = 0;						//�볡����ID
	mRoleDescribeInfoID =0;						//��ɫ������ϢID     
}

CreateRoleData::~CreateRoleData()
{

}

bool  CreateRoleData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mRoleIndexID))
		return false;

	if (!parser.parser_int_value(mRoleModelID))
		return false;

	if (!parser.parser_int_value(mRoleShapeID))
		return false;

	if (!parser.parser_int_value(mRoleSelectedAnimationID))
		return false;

	if (!parser.parser_int_value(mRoleDisabledAnimationID))
		return false;

	if (!parser.parser_int_value(mRoleEntranceAnimationID))
		return false;

	if (!parser.parser_int_value(mRoleLeaveAnimationID))
		return false;

	if (!parser.parser_int_value(mRoleDescribeInfoID))
		return false;

	return true; 
}


template<> CreateRoleDataManager* cobra_win::Singleton2<CreateRoleDataManager>::m_pMySelf = NULL;

CreateRoleDataManager::CreateRoleDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{

}

CreateRoleDataManager::~CreateRoleDataManager()
{

}


CreateRoleData * CreateRoleDataManager::GetCreateRoleDataByID(int roleIndexId)
{

	std::map<int,CreateRoleData*>::iterator shapeIter=m_CreateRoleDataMapList.find(roleIndexId);
	if(shapeIter!=m_CreateRoleDataMapList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}

std::string   CreateRoleDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/createrole.txt";

	return "createrole";
} 


unsigned  int CreateRoleDataManager::GetSize()
{
	return m_CreateRoleDataMapList.size()*sizeof(CreateRoleData);
}


bool  CreateRoleDataManager::Init()
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


void  CreateRoleDataManager::Tick()
{

}


void  CreateRoleDataManager::Destroy()
{
	std::map<int, CreateRoleData*>::iterator iter   = m_CreateRoleDataMapList.begin();
	std::map<int, CreateRoleData*>::iterator iter_e = m_CreateRoleDataMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_CreateRoleDataMapList.clear();
} 


bool  CreateRoleDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	CreateRoleData* pRoleItem = (CreateRoleData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  CreateRoleDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  CreateRoleDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	CreateRoleData* pItemData = new CreateRoleData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_CreateRoleDataMapList.insert(std::map<int, CreateRoleData*>::value_type(pItemData->mRoleIndexID, pItemData));

	return true;
}